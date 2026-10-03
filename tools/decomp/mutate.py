#!/usr/bin/env python3
"""Mutation check of the generated differential self-tests.

    python3 tools/decomp/mutate.py                 # every function with a passing autotest
    python3 tools/decomp/mutate.py 0x988020 ...    # chosen functions (original addresses)

A passing autotest says the decompiled function behaves like the original on
the generated inputs; it does not say the inputs reach the function's
branches. This tool plants small faults in a copy of decomp/src (flipped
comparisons and logic operators, +/- swaps, literal + 1, removed `!`, removed
statements) and checks that the test notices them.

Mutants that do not compile, or compile to the same code as the original
function, are dropped. The rest run in rounds: one mutant per function per
round, never two in a round when one function's test can reach the other's
changed code. A test is strong when it kills enough of its mutants; the
result goes to build-decomp/mutation.json.
"""
from __future__ import annotations

import argparse
import hashlib
from concurrent.futures import ThreadPoolExecutor
import json
import os
from pathlib import Path
import random
import re
import shutil
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import autotest  # noqa: E402
import elfdb  # noqa: E402
import ghidra_cpp  # noqa: E402
import hybrid  # noqa: E402
import toolchain  # noqa: E402

ROOT = elfdb.ROOT
SRC = ROOT / "decomp" / "src"
WORK = ROOT / "build-decomp" / "mutate"
RESULT = ROOT / "build-decomp" / "mutation.json"
ACCEPTED = ROOT / "decomp" / "autotests.json"
MAX_MUTANTS = 10
PROBES = 24
STRONG = 0.8

# "Type name = ...;", "Type* name;", "std::wstring name(...);" (removing one only breaks the build).
DECLARATION = re.compile(r"(?!(?:delete|throw|goto|case|else)\b)(?:[A-Za-z_][\w:<>,]*(?:\s*[*&]+\s*|\s+))+"
                         r"[A-Za-z_]\w*\s*(?:=|;|\(|\[)")
OPERATORS = [(" < ", " <= "), (" <= ", " < "), (" > ", " >= "), (" >= ", " > "),
             (" == ", " != "), (" != ", " == "), (" && ", " || "), (" || ", " && "),
             (" + ", " - "), (" - ", " + "), (" += ", " -= "), (" -= ", " += "),
             ("++", "--"), ("--", "++")]


# -- source -------------------------------------------------------------------
def mask(text):
    """Text with comments and string/char literals blanked (offsets kept)."""
    out = list(text)

    def blank(i, j):
        for k in range(i, j):
            if out[k] != "\n":
                out[k] = " "

    i, n = 0, len(text)
    while i < n:
        if text.startswith("//", i):
            j = text.find("\n", i)
            j = n if j < 0 else j
            blank(i, j)
            i = j
        elif text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            blank(i, j)
            i = j
        elif text[i] in "\"'":
            j = i + 1
            while j < n and text[j] not in (text[i], "\n"):
                j += 2 if text[j] == "\\" else 1
            blank(i + 1, j)
            i = j + 1
        else:
            i += 1
    return "".join(out)


def matching(text, at, open_, close):
    depth = 0
    for i in range(at, len(text)):
        if text[i] == open_:
            depth += 1
        elif text[i] == close:
            depth -= 1
            if depth == 0:
                return i
    return -1


def definition(text, masked, f):
    """(body start, body end) of f's definition in a TU source, or None."""
    qual = f["demangled"].split("(")[0]
    want = len([p for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void"])
    found = []
    for m in re.finditer(r"(?m)^[\w:<>,*&\s]*?" + re.escape(qual) + r"\s*\(", masked):
        close = matching(masked, m.end() - 1, "(", ")")
        brace, semi = masked.find("{", close), masked.find(";", close)
        if close < 0 or brace < 0 or (0 <= semi < brace):
            continue
        params = masked[m.end():close].strip()
        count = 0 if params in ("", "void") else len(ghidra_cpp.split_args(params))
        found.append((count, brace, matching(masked, brace, "{", "}")))
    exact = [x for x in found if x[0] == want]
    if len(exact) != 1:
        return None
    return exact[0][1], exact[0][2]


def mutation_points(text, masked, start, end):
    points = []
    body = masked[start:end]
    for old, new in OPERATORS:
        for m in re.finditer(re.escape(old), body):
            points.append((start + m.start(), start + m.end(), new))
    for m in re.finditer(r"!(?!=)", body):
        points.append((start + m.start(), start + m.end(), ""))
    for m in re.finditer(r"(?<![\w.])(\d+)(?![\w.])", body):
        points.append((start + m.start(), start + m.end(), str(int(m.group(1)) + 1)))
    for m in re.finditer(r"\b(true|false)\b", body):
        points.append((start + m.start(), start + m.end(), "false" if m.group(1) == "true" else "true"))
    for m in re.finditer(r"(?m)^[ \t]*([^\s{}][^\n{}]*;)[ \t]*$", body):
        statement = m.group(1)
        if re.match(r"(return|break|continue)\b", statement) or DECLARATION.match(statement):
            continue
        points.append((start + m.start(1), start + m.end(1), ";"))
    return points


def body_digest(db, f):
    """Digest of f's definition in decomp/src, or None when it cannot be located."""
    tu = next((t["name"] for t in db["tus"] if t["id"] == f["tu"]), None)
    source = next(iter(SRC.rglob(tu)), None) if tu else None
    if not source:
        return None
    text = source.read_text()
    span = definition(text, mask(text), f)
    if not span:
        return None
    return hashlib.sha256(text[span[0]:span[1] + 1].encode()).hexdigest()[:16]


def load_accepted():
    return json.loads(ACCEPTED.read_text()) if ACCEPTED.exists() else {}


def record(db, functions, results):
    """Strong tests into decomp/autotests.json; weak or failed ones out of it."""
    accepted = load_accepted()
    for f in functions:
        r = results.get(f["address"], {})
        if r.get("strong"):
            accepted[f["address"]] = {"name": f["demangled"], "killed": r["killed"], "tried": r["tried"],
                                      "source": body_digest(db, f)}
        else:
            accepted.pop(f["address"], None)
    ACCEPTED.write_text(json.dumps(dict(sorted(accepted.items())), indent=1, ensure_ascii=False) + "\n")
    print(f"{ACCEPTED.relative_to(ROOT)}: {len(accepted)} functions")


def describe(text, point):
    a, b, new = point
    line = text.count("\n", 0, a) + 1
    return f"line {line}: '{text[a:b].strip()}' -> '{new.strip()}'"


# -- assembly -----------------------------------------------------------------
def functions_in_asm(text):
    """Normalized body of every function in a GCC .s file (local labels renamed,
    referenced .LC constants inlined)."""
    lines = text.splitlines()
    data, current = {}, None
    for line in lines:
        m = re.match(r"^(\.LC\d+):$", line)
        if m:
            current = m.group(1)
            data[current] = []
        elif current and (re.match(r"^\S+:$", line) or line.strip().startswith((".section", ".text"))):
            current = None
        elif current:
            data[current].append(line.strip())
    names = set(re.findall(r"\.type\s+([^,\s]+),\s*@function", text))
    out, name, body = {}, None, []
    for line in lines:
        if name is None:
            m = re.match(r"^([^\s:]+):$", line)
            if m and m.group(1) in names:
                name, body = m.group(1), []
            continue
        if re.match(rf"^\s*\.size\s+{re.escape(name)},", line):
            labels = {}

            def rename(m):
                tok = m.group(0)
                if tok in data:
                    return "<" + ";".join(data[tok]) + ">"
                return labels.setdefault(tok, f".L#{len(labels)}")
            out[name] = "\n".join(re.sub(r"\.L\w+", rename, l) for l in body)
            name = None
        else:
            body.append(line)
    return out


def references(asm_functions, known):
    """Function -> functions of ours it calls or takes the address of."""
    return {name: {t for t in re.findall(r"[\w.$@]+", body) if t in known and t != name}
            for name, body in asm_functions.items()}


# -- the run ------------------------------------------------------------------
class Mutant:
    def __init__(self, target, point, text):
        self.target, self.point, self.what = target, point, describe(text, point)
        self.affected = set()


def probe(source, text, mutant, baseline, slot):
    """Compiles the mutated TU; fills mutant.affected, False when invalid or equivalent."""
    a, b, new = mutant.point
    path = WORK / "probe" / str(slot) / source.name
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text[:a] + new + text[b:])
    try:
        toolchain.compile_source(path, path.with_suffix(".s"), ["-I", str(hybrid.HYBRID)], assembly=True, quiet=True)
    except SystemExit:
        return False
    after = functions_in_asm(path.with_suffix(".s").read_text())
    mutant.affected = {n for n in set(after) | set(baseline) if after.get(n) != baseline.get(n)}
    return bool(mutant.affected & set(mutant.target["names"]))


def stats(report):
    out = {}
    for line in report:
        m = re.match(r"\s+stats (\S+) same (\d+) both-failed (\d+) different (\d+)", line)
        if m:
            out[m.group(1)] = tuple(int(x) for x in m.groups()[1:])
    return out


def build_and_test(src, tests, names, out):
    os.environ["OTL_SELFTEST_TIMEOUT"] = str(60 + 12 * len(names))
    blob, loader = hybrid.build(out=out, verbose=False, src=src, tests=tests)
    code, report = hybrid.selftest(blob, loader, only=",".join(names))
    return stats(report), report


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("addresses", nargs="*")
    parser.add_argument("--max", type=int, default=MAX_MUTANTS, help="mutants per function")
    parser.add_argument("--accept", action="store_true",
                        help=f"record strong tests in {ACCEPTED.relative_to(ROOT)} (check.py accepts them)")
    parser.add_argument("--record", action="store_true",
                        help=f"only record the last run ({RESULT.relative_to(ROOT)}) in {ACCEPTED.relative_to(ROOT)}")
    args = parser.parse_args()
    if args.record:
        db = elfdb.load_db()
        results = json.loads(RESULT.read_text())
        return record(db, [db["functions"][a] for a in results if "tried" in results[a]], results)
    shutil.rmtree(WORK, ignore_errors=True)
    WORK.mkdir(parents=True)
    toolchain.CC_CACHE = WORK / "cc-cache"  # mutated sources would only litter the shared cache

    gen = autotest.Generator()
    db = gen.db
    functions = ([db["functions"][hex(int(a, 16))] for a in args.addresses] if args.addresses
                 else autotest.diff_functions(db))
    functions = list({f["address"]: f for f in functions}.values())
    made, _ = gen.write(functions)
    tests = sorted(autotest.OUT.glob("*.cpp"))
    tag = lambda f: f"auto_{f['address'][2:]}"  # noqa: E731

    print(f"baseline: {len(made)} autotests")
    base, report = build_and_test(SRC, tests, [tag(f) for f in made], WORK / "base")
    targets = [f for f in made if tag(f) in base and base[tag(f)][2] == 0 and base[tag(f)][0] >= autotest.MIN_COMPLETED]
    print(f"  {len(targets)} pass with at least {autotest.MIN_COMPLETED} completed cases")

    # Our functions, their code and what they reach.
    tu_names = {t["id"]: t["name"] for t in db["tus"]}
    sources = {p.name: p for p in SRC.rglob("*.cpp")}
    asm = {}
    for name in sources:
        s = WORK / "base" / f"{Path(name).stem}.s"
        asm[name] = functions_in_asm(s.read_text()) if s.exists() else {}
    known = {n for funcs in asm.values() for n in funcs}
    calls = {}
    for funcs in asm.values():
        calls.update(references(funcs, known))

    def reach(f):
        seen, todo = set(), [n for n in f["names"] if n in known]
        while todo:
            n = todo.pop()
            if n not in seen:
                seen.add(n)
                todo += calls.get(n, ())
        return seen

    # Candidate mutants per target, compiled in parallel.
    queues, results = {}, {}
    jobs = []
    for f in targets:
        source = sources.get(tu_names.get(f["tu"], ""))
        if not source:
            results[f["address"]] = {"error": "no source"}
            continue
        text = source.read_text()
        masked = mask(text)
        span = definition(text, masked, f)
        if not span:
            results[f["address"]] = {"error": "definition not found"}
            continue
        points = mutation_points(text, masked, *span)
        random.Random(int(f["address"], 16)).shuffle(points)
        for p in points[:PROBES]:
            jobs.append((f, source, text, Mutant(f, p, text)))
    print(f"probing {len(jobs)} candidate mutants")
    with ThreadPoolExecutor(4) as pool:
        valid = list(pool.map(lambda j: probe(j[1], j[2], j[3], asm[j[1].name], id(j[3])), jobs))
    for (f, source, text, m), ok in zip(jobs, valid):
        q = queues.setdefault(f["address"], [])
        if ok and len(q) < args.max:
            m.source, m.reach = source, None
            q.append(m)
    reaches = {f["address"]: reach(f) for f in targets}

    # Rounds.
    done = {a: [] for a in queues}
    round_no = 0
    while any(queues.values()):
        round_no += 1
        chosen = []
        for address, q in queues.items():
            if not q:
                continue
            m = q[0]
            if all(not (reaches[address] & c.affected) and not (reaches[c.target["address"]] & m.affected)
                   for c in chosen):
                chosen.append(q.pop(0))
        src = WORK / "src"
        shutil.rmtree(src, ignore_errors=True)
        shutil.copytree(SRC, src)
        by_file = {}
        for m in chosen:
            by_file.setdefault(m.source.relative_to(SRC), []).append(m)
        for rel, ms in by_file.items():
            text = (SRC / rel).read_text()
            for m in sorted(ms, key=lambda m: -m.point[0]):
                a, b, new = m.point
                text = text[:a] + new + text[b:]
            (src / rel).write_text(text)
        try:
            got, _ = build_and_test(src, tests, [tag(m.target) for m in chosen], WORK / "round")
        except SystemExit as error:
            got = {}
            print(f"  round {round_no}: build failed: {error}")
        for m in chosen:
            s = got.get(tag(m.target))
            outcome = "error" if s is None else "killed" if s[2] else "survived"
            done[m.target["address"]].append({"mutant": m.what, "outcome": outcome, "stats": s})
        print(f"round {round_no}: {len(chosen)} mutants, ", end="")
        print(
              f"{sum(1 for m in chosen if (got.get(tag(m.target)) or (0, 0, 0))[2])} killed", flush=True)

    for f in targets:
        rows = done.get(f["address"], [])
        tried = [r for r in rows if r["outcome"] != "error"]
        killed = sum(r["outcome"] == "killed" for r in tried)
        results.setdefault(f["address"], {}).update(
            name=f["demangled"], tried=len(tried), killed=killed,
            score=round(killed / len(tried), 2) if tried else None,
            strong=bool(tried) and killed / len(tried) >= STRONG, mutants=rows)
    RESULT.write_text(json.dumps(results, indent=1, ensure_ascii=False))
    if args.accept:
        record(db, functions, results)
    strong = [a for a, r in results.items() if r.get("strong")]
    print(f"\n{len(strong)} of {len(targets)} tests are strong (kill >= {STRONG:.0%} of mutants)")
    for address, r in sorted(results.items()):
        if "error" in r and "tried" not in r:
            print(f"  {address} {db['functions'][address]['demangled'][:50]}: {r['error']}")
            continue
        print(f"  {address} {r['name'][:50]:50} {r['killed']}/{r['tried']}")
        for row in r["mutants"]:
            if row["outcome"] == "survived":
                print(f"      survived {row['mutant']}")
    shutil.rmtree(WORK / "probe", ignore_errors=True)


if __name__ == "__main__":
    main()
