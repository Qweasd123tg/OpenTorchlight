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
from concurrent.futures import ThreadPoolExecutor
import json
import os
from pathlib import Path
import random
import re
import shutil
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import autotest  # noqa: E402
import elfdb  # noqa: E402
import evidence  # noqa: E402
import ghidra_cpp  # noqa: E402
import hybrid  # noqa: E402
import objdiff  # noqa: E402
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


def canonical_parameter(parameter, named=False):
    """Conservative spelling normalization for ordinary C++ parameter types.

    Used only to disambiguate same-arity overloads. Complex declarators or
    unresolved aliases remain unmatched rather than selecting another body.
    """
    p = parameter.strip()
    p = p.replace(autotest.WSTRING, "std::wstring")
    if named:
        p = re.sub(r"\s*=.*$", "", p)
        # Strip a name only after a pointer/reference or a separated type.
        m = re.search(r"([*&]\s*|\s+)([A-Za-z_]\w*)$", p)
        if m and m.group(2) not in {"int", "long", "short", "char", "double", "float", "const", "volatile", "unsigned", "signed"}:
            p = p[:m.start(2)].strip()
    p = re.sub(r"^(.+?)\s+const\s*([*&].*)$", r"const \1\2", p)
    return re.sub(r"\s+", "", p)


def definition(text, masked, f):
    """(body start, body end) of f's definition in a TU source, or None."""
    qual = f["demangled"].split("(")[0]
    want = len([p for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void"])
    found = []
    wanted_types = [canonical_parameter(p) for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void"]
    for m in re.finditer(r"(?m)^[\w:<>,*&\s]*?" + re.escape(qual) + r"\s*\(", masked):
        close = matching(masked, m.end() - 1, "(", ")")
        brace, semi = masked.find("{", close), masked.find(";", close)
        if close < 0 or brace < 0 or (0 <= semi < brace):
            continue
        params = masked[m.end():close].strip()
        count = 0 if params in ("", "void") else len(ghidra_cpp.split_args(params))
        types = [canonical_parameter(p, named=True) for p in ghidra_cpp.split_args(params) if p and p != "void"]
        found.append((count, brace, matching(masked, brace, "{", "}"), types))
    exact = [x for x in found if x[0] == want]
    if len(exact) != 1:
        exact = [x for x in exact if x[3] == wanted_types]
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


def code_digests(db, functions):
    """Instruction-similarity keys, retained for diagnostic callers only."""
    return {address: row["code"] for address, row in compiled_evidence(db, functions).items()}


def compiled_evidence(db, functions):
    """Full TU objects, including data/EH/relocations, not just instructions."""
    original = objdiff.Original(db=db)
    names = {t["id"]: t["name"] for t in db["tus"]}
    sources = {p.name: p for p in SRC.rglob("*.cpp")}
    out = {}
    for tu in sorted({names[f["tu"]] for f in functions if names.get(f["tu"]) in sources}):
        unit = objdiff.compare_source(sources[tu], original, quiet=True)
        for row in unit["functions"]:
            if row.get("code") and row.get("address") and not row.get("weak"):
                out[row["address"]] = {"code": row["code"], "object_digest": row.get("object_digest")}
    return out


def load_accepted():
    return json.loads(ACCEPTED.read_text()) if ACCEPTED.exists() else {}


def record(db, functions, results):
    """Publish only evidence still bound to the inputs actually tested."""
    accepted = load_accepted()
    versioned = [f for f in functions if (results.get(f["address"], {}).get("evidence") or {}).get("schema") == evidence.SCHEMA]
    inputs = evidence.input_digest(db) if versioned else None
    builds = compiled_evidence(db, versioned) if versioned else {}
    if versioned and evidence.input_digest(db) != inputs:
        raise SystemExit("inputs changed while recording mutation evidence; rerun the check")
    for f in functions:
        r = results.get(f["address"], {})
        build = builds.get(f["address"], {})
        fresh = evidence.current(r, build.get("object_digest"), inputs)
        generated = (r.get("evidence") or {}).get("parameters", {}).get("hand") is False
        if r.get("strong") and fresh and generated and r.get("code_at_test") == build.get("code"):
            accepted[f["address"]] = {"name": f["demangled"], "killed": r["killed"], "tried": r["tried"],
                                      "code": r["code_at_test"], "evidence": r["evidence"]}
        else:
            if r.get("strong"):
                print(f"stale mutation evidence: {f['address']}; rerun it on the current inputs")
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
        m = re.match(r"\s*stats (\S+) same (\d+) both-failed (\d+) different (\d+)(?: incomplete (\d+))?", line)
        if m:
            out[m.group(1)] = tuple(int(x or 0) for x in m.groups()[1:])
    return out


def generated_outcome(value):
    if value is None or value[3]:
        return "error"
    if value[2]:
        return "killed"
    return "survived" if value[0] >= autotest.MIN_COMPLETED else "error"


def verdicts(report):
    """Test name -> passed, from the loader's PASS/FAIL lines."""
    out = {}
    for line in report:
        m = re.match(r"tlhybrid: (\S+)\s+(PASS|FAIL) \(", line)
        if m:
            out[m.group(1)] = m.group(2) == "PASS"
    return out


def build_and_test(src, tests, names, out):
    os.environ["OTL_SELFTEST_TIMEOUT"] = str(60 + 12 * len(names))
    blob, loader = hybrid.build(out=out, verbose=False, src=src, tests=tests)
    try:
        code, report = hybrid.selftest(blob, loader, only=",".join(sorted(set(names))))
    except subprocess.TimeoutExpired:
        return {}, ["timeout"]  # a hang outside a forked child: the tests noticed something
    return stats(report), report


def hand_coverage(db):
    """Function address -> names of the hand-written tests whose file declares it with TL_ORIGINAL."""
    out = {}
    by_name = {}
    for a, f in db["functions"].items():
        for n in f["names"]:
            by_name[n] = a
    for test in sorted(hybrid.TESTS.glob("*.cpp")):
        text = test.read_text(errors="replace")
        names = re.findall(r"^TL_TEST\((\w+)\)", text, re.M)
        for mangled in re.findall(r'TL_ORIGINAL\([^;]*?"(_Z\w+)"\)', text, re.S):
            if mangled in by_name:
                out.setdefault(by_name[mangled], set()).update(names)
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("addresses", nargs="*")
    parser.add_argument("--max", type=int, default=MAX_MUTANTS, help="mutants per function")
    parser.add_argument("--accept", action="store_true",
                        help=f"record strong tests in {ACCEPTED.relative_to(ROOT)} (check.py accepts them)")
    parser.add_argument("--hand", action="store_true",
                        help="check the hand-written tests in decomp/hybrid/tests (TL_ORIGINAL) instead of "
                             "generated ones; addresses default to every DIFF function they cover")
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

    if args.hand:
        db = elfdb.load_db()
        coverage = hand_coverage(db)
        functions = ([db["functions"][hex(int(a, 16))] for a in args.addresses] if args.addresses
                     else [f for f in autotest.diff_functions(db) if f["address"] in coverage])
        functions = [f for f in {f["address"]: f for f in functions}.values() if f["address"] in coverage]
        tests = sorted(hybrid.TESTS.glob("*.cpp"))
        covering = lambda f: sorted(coverage[f["address"]])  # noqa: E731
        print(f"baseline: {len(functions)} functions under hand-written tests")
        tested_inputs = evidence.input_digest(db)
        tested_builds = compiled_evidence(db, functions)
        _, report = build_and_test(SRC, tests, [n for f in functions for n in covering(f)], WORK / "base")
        passed = verdicts(report)
        targets = [f for f in functions if all(passed.get(n) for n in covering(f))]
        print(f"  {len(targets)} with passing tests")
    else:
        gen = autotest.Generator()
        db = gen.db
        functions = ([db["functions"][hex(int(a, 16))] for a in args.addresses] if args.addresses
                     else autotest.diff_functions(db))
        functions = list({f["address"]: f for f in functions}.values())
        made, _ = gen.write(functions)
        tests = sorted(autotest.OUT.glob("*.cpp"))
        covering = lambda f: [f"auto_{f['address'][2:]}"]  # noqa: E731
        print(f"baseline: {len(made)} autotests")
        tested_inputs = evidence.input_digest(db)
        tested_builds = compiled_evidence(db, made)
        base, report = build_and_test(SRC, tests, [n for f in made for n in covering(f)], WORK / "base")
        targets = [f for f in made if covering(f)[0] in base and base[covering(f)[0]][2] == 0
                   and base[covering(f)[0]][3] == 0
                   and base[covering(f)[0]][0] >= autotest.MIN_COMPLETED]
        print(f"  {len(targets)} pass with at least {autotest.MIN_COMPLETED} completed cases")

    if evidence.input_digest(db) != tested_inputs:
        raise SystemExit("inputs changed during baseline testing; rerun on a stable snapshot")
    parameters = {"max_mutants": args.max, "probes": PROBES, "strong_threshold": STRONG,
                  "cases": autotest.CASES, "min_completed": autotest.MIN_COMPLETED,
                  "budget_seconds": autotest.BUDGET_SECONDS, "hand": args.hand}

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
            if not q or (chosen and getattr(q[0], "alone", False)):
                continue
            m = q[0]
            # One mutant per test: a failure must point at a single mutant.
            if all(not (reaches[address] & c.affected) and not (reaches[c.target["address"]] & m.affected)
                   and not set(covering(m.target)) & set(covering(c.target)) for c in chosen):
                chosen.append(q.pop(0))
                if getattr(m, "alone", False):
                    break
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
            got, report = build_and_test(src, tests, [n for m in chosen for n in covering(m.target)], WORK / "round")
        except SystemExit as error:
            got, report = {}, []
            print(f"  round {round_no}: build failed: {error}")
        passed = verdicts(report)
        for m in chosen:
            names = covering(m.target)
            if args.hand:
                s = None
                if any(n not in passed for n in names):
                    # The run died (a crash outside a forked child): retry the mutant alone.
                    if len(chosen) > 1 and not getattr(m, "alone", False):
                        m.alone = True
                        queues[m.target["address"]].insert(0, m)
                        continue
                    outcome = "killed" if report else "error"
                else:
                    outcome = "survived" if all(passed[n] for n in names) else "killed"
            else:
                s = got.get(names[0])
                outcome = generated_outcome(s)
            # Symbol scans cannot prove independence through indirect calls.
            # Batch discoveries are cheap candidates; only an isolated kill is evidence.
            if outcome == "killed" and len(chosen) > 1:
                m.alone = True
                queues[m.target["address"]].insert(0, m)
                continue
            done[m.target["address"]].append({"mutant": m.what, "outcome": outcome, "stats": s,
                                               "isolated": len(chosen) == 1})
        print(f"round {round_no}: {len(chosen)} mutants, ", end="")
        print(
              f"{sum(1 for m in chosen if done[m.target['address']] and done[m.target['address']][-1]['mutant'] == m.what and done[m.target['address']][-1]['outcome'] == 'killed')} killed", flush=True)

    unchanged = evidence.input_digest(db) == tested_inputs
    for f in targets:
        rows = done.get(f["address"], [])
        tried = [r for r in rows if r["outcome"] != "error"]
        killed = sum(r["outcome"] == "killed" for r in tried)
        results.setdefault(f["address"], {}).update(
            name=f["demangled"], tried=len(tried), killed=killed,
            score=round(killed / len(tried), 2) if tried else None,
            strong=unchanged and bool(tried) and killed / len(tried) >= STRONG, mutants=rows,
            code_at_test=tested_builds.get(f["address"], {}).get("code"))
        build = tested_builds.get(f["address"], {})
        if unchanged and build.get("object_digest"):
            results[f["address"]]["evidence"] = evidence.tested(build["object_digest"], tested_inputs, parameters)
    if not unchanged:
        print("inputs changed during mutation testing; results are diagnostic only and cannot be recorded")
    RESULT.write_text(json.dumps(results, indent=1, ensure_ascii=False))
    if args.accept and not args.hand:
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
