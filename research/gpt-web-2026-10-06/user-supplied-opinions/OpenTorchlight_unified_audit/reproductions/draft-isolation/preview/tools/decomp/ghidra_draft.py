#!/usr/bin/env python3
"""Draft C++ from Ghidra with recovered types.

    python3 tools/decomp/ghidra_draft.py analyze            # once: import + auto-analysis (long)
    python3 tools/decomp/ghidra_draft.py drafts AIFlag.cpp  # types + decompile + C++ cleanup
    python3 tools/decomp/ghidra_draft.py drafts --all       # every game TU (long; run in background)
    python3 tools/decomp/ghidra_draft.py stale              # drafts made with other types/scripts/ELF
    python3 tools/decomp/ghidra_draft.py drafts --stale     # remake only those

`drafts` exports class layouts from tools/decomp/layout.py and the recovered
headers as Ghidra structures, applies them as `this` types, decompiles every
function of the TU and writes build-decomp/drafts/<TU>/<address>.c (raw) and
draft.cpp (cleaned). Drafts are input for writing decomp/src, never compiled
into the hybrid as is.

Ghidra and its project live in $OTL_GHIDRA_WORK (default /var/tmp/opentorchlight-ghidra).
Ghidra needs a JDK 21 in $OTL_DECOMP_CACHE/jdk/jdk-21*/ (Adoptium tarball;
the system often has only a JRE).
"""
from __future__ import annotations

import argparse
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import toolchain  # noqa: E402

ROOT = elfdb.ROOT
# Ghidra rejects project paths with dot-directories and its logging breaks on
# non-ASCII install paths, so both live under a plain ASCII work directory.
WORK = Path(os.environ.get("OTL_GHIDRA_WORK", "/var/tmp/opentorchlight-ghidra"))
GHIDRA_HOME = Path(os.environ.get("GHIDRA_HOME", WORK / "ghidra_12.1.3_PUBLIC"))
SCRIPTS = ROOT / "tools" / "ghidra"
OUT = ROOT / "build-decomp" / "drafts"


def workspace():
    if not (GHIDRA_HOME / "support" / "analyzeHeadless").exists():
        raise SystemExit(f"unpack the pinned Ghidra archive (build-source-cache/ghidra/*.zip) into {WORK}")
    base = WORK / "work"
    for sub in ("project", "config", "cache", "io"):
        (base / sub).mkdir(parents=True, exist_ok=True)
    return base


def headless(args, log_name, background=False):
    base = workspace()
    env = dict(os.environ, XDG_CONFIG_HOME=str(base / "config"), XDG_CACHE_HOME=str(base / "cache"))
    # Ghidra needs a full JDK (it compiles scripts); the system may only have a JRE.
    jdks = sorted((toolchain.cache_dir() / "jdk").glob("jdk-21*/bin/javac"))
    if jdks:
        env["JAVA_HOME"] = str(jdks[-1].parent.parent)
        env["PATH"] = f"{jdks[-1].parent}:{env['PATH']}"
    env.setdefault("GHIDRA_HEADLESS_MAXMEM", "5G")
    cmd = [str(GHIDRA_HOME / "support" / "analyzeHeadless"), str(base / "project"), "Torchlight", *args,
           "-log", str(base / f"{log_name}.log"), "-scriptlog", str(base / f"{log_name}.script.log")]
    return subprocess.run(cmd, env=env, check=False)


def analyze():
    base = workspace()
    if (base / "project" / "Torchlight.gpr").exists():
        raise SystemExit(f"project exists: {base / 'project'}")
    result = headless(["-import", str(elfdb.default_elf()), "-max-cpu", "3", "-analysisTimeoutPerFile", "14400"],
                      "analyze")
    return result.returncode


WRITTEN = ("function", "ctor", "dtor", "static")
# Everything a draft depends on besides the types: a change makes every draft stale.
DRAFT_TOOLS = (ROOT / "tools" / "decomp" / "ghidra" / "DecompDrafts.java", Path(__file__),
               ROOT / "tools" / "decomp" / "types_export.py", ROOT / "tools" / "decomp" / "layout.py")


def _digest(data):
    import hashlib
    return hashlib.sha256(data if isinstance(data, bytes) else data.encode()).hexdigest()[:16]


def tools_digest():
    return _digest(b"".join(p.read_bytes() for p in DRAFT_TOOLS if p.exists()))


def class_digests(types, names):
    import json
    return {n: _digest(json.dumps(types[n], sort_keys=True)) for n in sorted(names) if n in types}


def used_classes(types, texts, scopes):
    """Classes whose layout a TU's drafts were decompiled with: the TU's own and every one they name."""
    words = set()
    for text in texts:
        words.update(re.findall(r"\b[A-Za-z_]\w*\b", text))
    return (words | set(scopes)) & set(types)


def prototype_digest(prototypes, addresses):
    """Digest of the header prototypes of the given functions (types_export.py)."""
    return _digest(json.dumps({a: prototypes[a] for a in sorted(addresses) if a in prototypes}, sort_keys=True))


def _input_state(tu, db=None, types=None):
    """("fresh" | "stale" | "unknown", reasons) for build-decomp/drafts/<TU>."""
    import json
    meta = OUT / tu / "inputs.json"
    if not meta.exists():
        return "unknown", ["no inputs.json: made before drafts were fingerprinted"]
    data = json.loads(meta.read_text())
    db = db or elfdb.load_db()
    types = types if types is not None else _types()
    reasons = []
    if data.get("elf") != db["original_elf_sha256"]:
        reasons.append("another ELF")
    if data.get("tools") != tools_digest():
        reasons.append("decompiler scripts changed")
    if "prototypes" in data:
        tu_id = next(t["id"] for t in db["tus"] if t["name"] == tu)
        own = [a for a, f in db["functions"].items() if f["tu"] == tu_id]
        if data["prototypes"] != prototype_digest(_prototypes(), own):
            reasons.append("method prototypes changed")
    now = class_digests(types, data.get("classes", {}))
    changed = sorted(n for n, d in data.get("classes", {}).items() if now.get(n) != d)
    if changed:
        reasons.append("types changed: " + ", ".join(changed[:8]) + (" ..." if len(changed) > 8 else ""))
    return ("stale" if reasons else "fresh"), reasons



def raw_status(path):
    """Export health, not a correctness judgement of the decompiled C."""
    if not path.is_file():
        return "missing"
    text = path.read_text(errors="replace")
    # Mask quoted literals first: diagnostic-looking string contents are not failures.
    token = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*', re.S)
    comments = []
    def mask(match):
        value = match.group(0)
        if value.startswith(("/*", "//")):
            comments.append(value)
        return " " * len(value)
    body = token.sub(mask, text)
    if re.search(r"\bDECOMPILATION FAILED\b", "\n".join(comments)) or any(
            re.match(r"//\s*(failed:|no function\b)", c, re.I) for c in comments):
        return "failed"
    if "{" not in body or "}" not in body:
        return "no-body"
    return "ok"


def draft_state(tu, db=None, types=None):
    """An error comment, empty or missing export is never a fresh usable draft."""
    state, reasons = _input_state(tu, db, types)
    if state == "unknown":
        return state, reasons
    db = db or elfdb.load_db()
    tu_id = next(t["id"] for t in db["tus"] if t["name"] == tu)
    bad = [(f["address"], raw_status(OUT / tu / "raw" / (f["address"] + ".c")))
           for f in db["functions"].values() if f["tu"] == tu_id and f["kind"] in WRITTEN]
    bad = [(address, status) for address, status in bad if status != "ok"]
    if bad:
        reasons.append("incomplete raw exports: " + ", ".join(a + " " + s for a, s in bad[:8])
                       + (" ..." if len(bad) > 8 else ""))
    return ("stale" if reasons else "fresh"), reasons


def _types():
    import json
    path = ROOT / "build-decomp" / "types.json"
    if not path.exists():
        subprocess.run([sys.executable, str(ROOT / "tools" / "decomp" / "types_export.py")], check=True)
    return json.loads(path.read_text())["classes"]


def _prototypes():
    path = ROOT / "build-decomp" / "types.json"
    return json.loads(path.read_text()).get("prototypes", {}) if path.exists() else {}


def stale(all_tus=False):
    db = elfdb.load_db()
    types = _types()
    out = []
    for d in sorted(p for p in OUT.iterdir() if (p / "raw").is_dir()):
        state, reasons = draft_state(d.name, db, types)
        if state == "stale" or (all_tus and state == "unknown"):
            out.append(d.name)
            print(f"{d.name:40} {state}: {'; '.join(reasons)}")
    return out


def drafts(tus, timeout=120, retry_failed=False):
    import shutil
    if not isinstance(timeout, int) or isinstance(timeout, bool) or timeout <= 0:
        raise SystemExit("--timeout must be a positive number of seconds")
    db = elfdb.load_db()
    subprocess.run([sys.executable, str(ROOT / "tools" / "decomp" / "types_export.py")], check=True)
    data = json.loads((ROOT / "build-decomp" / "types.json").read_text())
    if os.environ.get("OTL_DRAFT_PROTOTYPES") == "0":
        data.pop("prototypes", None)
    types, prototypes = data["classes"], data.get("prototypes", {})
    names = {t["id"]: t["name"] for t in db["tus"]}
    if tus == ["--all"]:
        tus = [t["name"] for t in db["tus"] if t["kind"] == "game"]
    wanted = {t["id"] for t in db["tus"] if t["name"] in tus}
    if len(wanted) != len(set(tus)):
        raise SystemExit(f"unknown TU among {tus}")
    funcs = [f for f in db["functions"].values() if f["tu"] in wanted and f["kind"] in WRITTEN]
    # A selective retry may keep good outputs ONLY when their inputs are current.
    # Changed/unknown fingerprints force the entire requested TU to be regenerated.
    if retry_failed:
        current = {tu: os.environ.get("OTL_DRAFT_PROTOTYPES") != "0" and
                   _input_state(tu, db, types)[0] == "fresh" for tu in tus}
        funcs = [f for f in funcs if not current[names[f["tu"]]] or
                 raw_status(OUT / names[f["tu"]] / "raw" / (f["address"] + ".c")) != "ok"]
    if not funcs:
        print("no pending exports for the requested TUs")
        return 0
    base = workspace()
    run_root = base / "io"
    run_root.mkdir(parents=True, exist_ok=True)
    # Never delete another worker's inputs. Keep the directory for diagnosis.
    io = Path(tempfile.mkdtemp(prefix="drafts-", dir=run_root))
    (io / "scripts").mkdir()
    shutil.copy(ROOT / "tools" / "decomp" / "ghidra" / "DecompDrafts.java", io / "scripts")
    (io / "types.json").write_text(json.dumps(data))
    (io / "targets.txt").write_text("".join(f"{f['address']}\n" for f in funcs))
    log_name = io.name
    result = headless(["-process", "Torchlight.bin.x86_64", "-noanalysis", "-readOnly",
                       "-scriptPath", str(io / "scripts"),
                       "-postScript", "DecompDrafts.java", str(io / "types.json"), str(io / "targets.txt"),
                       str(io / "out"), str(timeout)], log_name)
    if result.returncode:
        raise SystemExit("Ghidra failed; see " + str(base / (log_name + ".log")))
    statuses = {}
    touched = {names[f["tu"]] for f in funcs}
    for f in funcs:
        raw = io / "out" / f"{f['address']}.c"
        tu_dir = OUT / names[f["tu"]] / "raw"
        tu_dir.mkdir(parents=True, exist_ok=True)
        dest = tu_dir / f"{f['address']}.c"
        # Do not leave an older successful body in place when this run emitted nothing.
        if raw.is_file():
            shutil.copy(raw, dest)
        else:
            dest.write_text("// failed: expected output was not emitted\n")
        statuses[f["address"]] = raw_status(dest)
    for tu in touched:
        tu_id = next(t["id"] for t in db["tus"] if t["name"] == tu)
        own = [a for a, f in db["functions"].items() if f["tu"] == tu_id]
        items = [(OUT / tu / "raw" / (f["address"] + ".c"), f.get("scope") or "")
                 for f in db["functions"].values() if f["tu"] == tu_id and f["kind"] in WRITTEN]
        # Include the unchanged good exports too, preserving all known type dependencies.
        classes = used_classes(types, [p.read_text(errors="replace") for p, _ in items if p.is_file()],
                               [s.split("::")[0] for _, s in items])
        (OUT / tu / "inputs.json").write_text(json.dumps({
            "elf": db["original_elf_sha256"], "tools": tools_digest(),
            "classes": class_digests(types, classes), "prototypes": prototype_digest(prototypes, own)}, indent=1))
    (io / "status.json").write_text(json.dumps({"timeout_seconds": timeout, "functions": statuses}, indent=1))
    good = sum(s == "ok" for s in statuses.values())
    print(f"{good}/{len(funcs)} exports contain a body; {len(funcs) - good} incomplete; run: {io}")
    return 0 if good == len(funcs) else 1


def find_definition(text, f):
    """(start, end) of the definition of f in a source file, or None."""
    import ghidra_cpp
    qualified = f["demangled"].split("(")[0]
    want = len([p for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void"])
    want_types = [_param_type(p) for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void"]
    fallback = None
    for m in re.finditer(rf"(?m)^[^\n;{{}}#/]*\b{re.escape(qualified)}\s*\(", text):
        start = m.start()
        depth, i = 1, m.end()
        while i < len(text) and depth:
            depth += {"(": 1, ")": -1}.get(text[i], 0)
            i += 1
        params = [p for p in ghidra_cpp.split_args(text[m.end():i - 1]) if p.strip() not in ("", "void")]
        brace = text.find("{", i)
        if len(params) != want or brace < 0 or ";" in text[i:brace]:
            continue
        depth, j = 1, brace + 1
        while j < len(text) and depth:
            depth += {"{": 1, "}": -1}.get(text[j], 0)
            j += 1
        # Overloads with the same arity: the parameter types decide (ReadFile(FILE*) vs ReadFile(wstring)).
        if [_param_type(p, named=True) for p in params] == want_types:
            return start, j
        fallback = fallback or (start, j)
    return fallback


def _param_type(param, named=False):
    """Comparable spelling of a parameter type: `const std::wstring& name` == `std::basic_string<...> const&`."""
    p = re.sub(r"\s*=.*$", "", param.strip())
    if named:
        p = re.sub(r"(?<=[\w*&>\s])\s*\b[A-Za-z_]\w*\s*(\[\d*\])?$", lambda m: m.group(1) or "", p)
    p = re.sub(r"std::basic_string<wchar_t,\s*std::char_traits<wchar_t>,\s*std::allocator<wchar_t>\s*>", "std::wstring", p)
    p = re.sub(r"\b_IO_FILE\b", "FILE", p)
    p = re.sub(r"std::basic_string<char,\s*std::char_traits<char>,\s*std::allocator<char>\s*>", "std::string", p)
    const = bool(re.search(r"\bconst\b", p.split("*")[0]))
    p = re.sub(r"\bconst\b", "", p.split("*")[0]) + ("*" * p.count("*")) + ("&" if p.endswith("&") else "")
    p = re.sub(r"\s+|&(?=\*)", "", p.replace("&", "")) + ("&" if param.strip().rstrip().endswith("&") or "&" in param.split(")")[-1] else "")
    return ("const " if const else "") + p


_STDERR = []
# Drafts still touch TArrayList internals; open access while measuring only.
EXTRA = ("-Dprivate=public", "-Dprotected=public")


def captured():
    text = "".join(_STDERR)
    _STDERR.clear()
    return "\n".join(l for l in text.splitlines() if "error" in l)[:3000]


def measure(tus):
    class Tee:
        def write(self, data):
            _STDERR.append(data)

        def flush(self):
            pass
    sys.stderr = Tee()
    """Swap each recovered function for its converted Ghidra draft; compile and compare."""
    import tempfile
    import ghidra_cpp
    import objdiff
    db = elfdb.load_db()
    original = objdiff.Original(db=db)
    methods, signatures, enums = ghidra_cpp.known_methods(db), ghidra_cpp.signatures_of(db), ghidra_cpp.parse_enums()
    totals = {}
    for tu in tus:
        source = ROOT / "decomp" / "src" / tu
        text = source.read_text()
        tu_id = next(t["id"] for t in db["tus"] if t["name"] == tu)
        for f in sorted((f for f in db["functions"].values() if f["tu"] == tu_id and f["kind"] in WRITTEN
                         and not any(n.endswith("D0Ev") for n in f["names"])),
                        key=lambda f: f["address"]):
            raw = OUT / tu / "raw" / f"{f['address']}.c"
            span = find_definition(text, f)
            if not raw.exists() or not span:
                status = "no-draft" if not raw.exists() else "not-located"
            else:
                draft = ghidra_cpp.convert(raw.read_text(), methods, f, signatures, enums)
                # Keep the recovered signature (and initializer list); measure the body only.
                body = draft[draft.find("\n{"):] if "\n{" in draft else draft
                head = text[span[0]:span[1]]
                signature = head[:head.find("{")].rstrip()
                inside = signature[signature.find("(") + 1:]
                inside = inside[:ghidra_cpp.closing_paren(inside)]
                names = [re.findall(r"(\w+)\s*(?:\[\d*\])?$", p.strip()) for p in ghidra_cpp.split_args(inside)]
                for i, n in enumerate(names, 1):
                    if n:
                        body = re.sub(rf"\bparam_{i}\b", n[0], body)
                draft = signature + body
                (OUT / tu / "cpp").mkdir(parents=True, exist_ok=True)
                (OUT / tu / "cpp" / f"{f['address']}.cpp").write_text(draft)
                _STDERR.clear()
                with tempfile.TemporaryDirectory(prefix="otl-pilot-") as tmp:
                    trial = Path(tmp) / tu
                    trial.write_text(text[:span[0]] + draft + text[span[1]:])
                    try:
                        result = objdiff.compare_source(trial, original, extra=EXTRA)
                        rows = [r for r in result["functions"] if r.get("address") == f["address"]]
                        status = rows[0]["status"] if rows else "missing"
                        if status == "DIFF":
                            status = f"DIFF {rows[0].get('score', 0):.0%}"
                    except BaseException as error:  # compile errors raise SystemExit
                        status = "compile-error"
                        errors = (OUT / tu / "errors")
                        errors.mkdir(parents=True, exist_ok=True)
                        (errors / f"{f['address']}.txt").write_text(draft + "\n/*\n" + captured() + "\n*/\n")
            key = status.split()[0]
            totals[key] = totals.get(key, 0) + 1
            print(f"{tu:30} {f['address']} {status:14} {f['demangled'][:70]}")
    print(totals)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    sub.add_parser("analyze")
    d = sub.add_parser("drafts")
    d.add_argument("tus", nargs="*")
    d.add_argument("--all", action="store_true", help="every game TU")
    s = sub.add_parser("stale", help="TUs whose drafts were made with other types, scripts or ELF")
    s.add_argument("--unknown", action="store_true", help="also those made before fingerprinting")
    d.add_argument("--stale", action="store_true", help="every TU `stale` lists")
    d.add_argument("--retry-failed", action="store_true", help="retry missing/failed exports; changed inputs force whole-TU refresh")
    d.add_argument("--timeout", type=int, default=120, help="seconds per function, including retry attempts")
    m = sub.add_parser("measure")
    m.add_argument("tus", nargs="+")
    args = parser.parse_args()
    if args.command == "analyze":
        return analyze()
    if args.command == "measure":
        return measure(args.tus)
    if args.command == "stale":
        stale(args.unknown)
        return 0
    if args.stale:
        tus = stale()
        if not tus:
            print("no stale drafts")
            return 0
        return drafts(tus, timeout=args.timeout, retry_failed=args.retry_failed)
    return drafts(["--all"] if getattr(args, "all", False) else args.tus,
                  timeout=args.timeout, retry_failed=args.retry_failed)


if __name__ == "__main__":
    sys.exit(main() or 0)
