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
from contextlib import contextmanager
import fcntl
import hashlib
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
    for sub in ("project", "config", "cache", "jobs"):
        (base / sub).mkdir(parents=True, exist_ok=True)
    return base


@contextmanager
def file_lock(path):
    """Serialize writers; unique job IO does not make a shared Ghidra project safe."""
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("a") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        try:
            yield
        finally:
            fcntl.flock(lock, fcntl.LOCK_UN)


def job_dir(base, name):
    # Keep logs and failed export artifacts for diagnosis; never delete another job's IO.
    return Path(tempfile.mkdtemp(prefix=name + "-", dir=base / "jobs"))


def headless(args, log_name, background=False, job=None, locked=False):
    base = workspace()
    job = job or job_dir(base, log_name)
    env = dict(os.environ, XDG_CONFIG_HOME=str(base / "config"), XDG_CACHE_HOME=str(base / "cache"))
    jdks = sorted((toolchain.cache_dir() / "jdk").glob("jdk-21*/bin/javac"))
    if jdks:
        env["JAVA_HOME"] = str(jdks[-1].parent.parent)
        env["PATH"] = f"{jdks[-1].parent}:{env['PATH']}"
    env.setdefault("GHIDRA_HEADLESS_MAXMEM", "5G")
    cmd = [str(GHIDRA_HOME / "support" / "analyzeHeadless"), str(base / "project"), "Torchlight", *args,
           "-log", str(job / f"{log_name}.log"), "-scriptlog", str(job / f"{log_name}.script.log")]
    if locked:
        return subprocess.run(cmd, env=env, check=False)
    with file_lock(base / "project.lock"):
        return subprocess.run(cmd, env=env, check=False)


def analyze():
    base = workspace()
    with file_lock(base / "project.lock"):
        if (base / "project" / "Torchlight.gpr").exists():
            raise SystemExit(f"project exists: {base / 'project'}")
        result = headless(["-import", str(elfdb.default_elf()), "-max-cpu", "3", "-analysisTimeoutPerFile", "14400"],
                          "analyze", locked=True)
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


def shaping_functions(db, tu_id, insns=None):
    """The TU's functions and every function they call or tail-jump to directly: Ghidra decompiles
    each call with the callee's prototype, so a callee in another TU changes the drafts too."""
    import layout
    insns = insns if insns is not None else layout.load_insns(db)
    own = {a for a, f in db["functions"].items() if f["tu"] == tu_id}
    out = set(own)
    for a in own:
        for _, mnemonic, ops, _ in insns.get(a, ()):
            if mnemonic.startswith(("call", "jmp")) and re.fullmatch(r"[0-9a-f]+", ops):
                target = f"{int(ops, 16):#x}"
                if target in db["functions"]:
                    out.add(target)
    return out


DRAFT_SCHEMA = 3
EXPORT_STATUSES = frozenset(("COMPLETE", "TIMEOUT", "TYPE_ERROR", "NO_BODY"))


def types_fingerprint(data):
    """Conservative closure: bases, fields, all vtables and signatures share one versioned hash."""
    payload = json.dumps({"schema": 1, "types": data}, sort_keys=True, separators=(",", ":"))
    return hashlib.sha256(payload.encode()).hexdigest()


def export_types():
    """Refresh for every API invocation, even when types.json exists or this process exported before."""
    with file_lock(ROOT / "build-decomp" / "types-export.lock"):
        subprocess.run([sys.executable, str(ROOT / "tools" / "decomp" / "types_export.py")], check=True)
        return json.loads((ROOT / "build-decomp" / "types.json").read_text())


def draft_state(tu, db=None, types=None, insns=None, addresses=None):
    """Fresh only if every requested body completed and still matches its versioned receipt."""
    meta = OUT / tu / "inputs.json"
    if not meta.exists():
        return "unknown", ["no inputs.json: made before drafts were fingerprinted"]
    try:
        data = json.loads(meta.read_text())
    except (ValueError, OSError):
        return "stale", ["unreadable inputs.json"]
    db = db or elfdb.load_db()
    snapshot = export_types() if types is None else types
    # Existing Python callers may supply just the classes mapping.
    if "classes" not in snapshot:
        snapshot = {"classes": snapshot, "prototypes": _prototypes(), "vtables": _vtables()}
    reasons = []
    if data.get("schema") != DRAFT_SCHEMA:
        reasons.append("unversioned or obsolete draft receipt")
    if data.get("elf") != db["original_elf_sha256"]:
        reasons.append("another ELF")
    if data.get("tools") != tools_digest():
        reasons.append("decompiler scripts changed")
    if data.get("types_fingerprint") != types_fingerprint(snapshot):
        reasons.append("type/layout/vtable/prototype inputs changed")
    tu_id = next(t["id"] for t in db["tus"] if t["name"] == tu)
    expected = {a for a, f in db["functions"].items()
                if f["tu"] == tu_id and f.get("kind", "function") in WRITTEN}
    if addresses is not None:
        requested = {hex(int(a, 16)) for a in addresses}
        if not requested or not requested <= expected:
            raise ValueError("requested addresses are not written functions of this TU")
        expected = requested
    exports = data.get("exports", {})
    if (not expected or not expected <= set(exports) or (addresses is None and set(exports) != expected)):
        reasons.append("requested function export set incomplete")
    for address in sorted(expected):
        receipt = exports.get(address, {})
        raw = OUT / tu / "raw" / f"{address}.c"
        if receipt.get("status") != "COMPLETE":
            reasons.append(f"{address}: {receipt.get('status', 'NO_BODY')}")
        elif not raw.exists() or hashlib.sha256(raw.read_bytes()).hexdigest() != receipt.get("raw_sha256"):
            reasons.append(f"{address}: missing or changed raw body")
    return ("stale" if reasons else "fresh"), reasons


def _types():
    return export_types()["classes"]


def _prototypes():
    path = ROOT / "build-decomp" / "types.json"
    return json.loads(path.read_text()).get("prototypes", {}) if path.exists() else {}


def _vtables():
    path = ROOT / "build-decomp" / "types.json"
    return json.loads(path.read_text()).get("vtables", {}) if path.exists() else {}


def stale(all_tus=False):
    import layout
    db = elfdb.load_db()
    types = export_types()
    insns = layout.load_insns(db)
    out = []
    for d in sorted(p for p in OUT.iterdir() if (p / "raw").is_dir()) if OUT.exists() else []:
        state, reasons = draft_state(d.name, db, types, insns)
        if state == "stale" or (all_tus and state == "unknown"):
            out.append(d.name)
            print(f"{d.name:40} {state}: {'; '.join(reasons)}")
    return out


def read_export(out, address):
    """Only an explicit COMPLETE record with a real body may become usable raw C."""
    raw = out / f"{address}.c"
    status_file = out / f"{address}.status.json"
    try:
        receipt = json.loads(status_file.read_text())
    except (OSError, ValueError):
        return {"status": "NO_BODY", "error": "no valid export status"}
    if receipt.get("status") not in EXPORT_STATUSES:
        return {"status": "NO_BODY", "error": "unknown export status"}
    if receipt["status"] == "COMPLETE":
        if not raw.exists() or not raw.read_text(errors="replace").strip() or "{" not in raw.read_text(errors="replace"):
            return {"status": "NO_BODY", "error": "COMPLETE export has no body"}
        receipt["raw_sha256"] = hashlib.sha256(raw.read_bytes()).hexdigest()
    return receipt


def drafts(tus, timeout=120, retries=0, addresses=None):
    import shutil
    if timeout <= 0 or retries < 0:
        raise ValueError("timeout must be positive and retries nonnegative")
    db = elfdb.load_db()
    data = export_types()
    base = workspace()
    draft_tools = tools_digest()
    job = job_dir(base, "drafts")
    io = job / "io"
    (io / "scripts").mkdir(parents=True)
    shutil.copy(ROOT / "tools" / "decomp" / "ghidra" / "DecompDrafts.java", io / "scripts")
    if os.environ.get("OTL_DRAFT_PROTOTYPES") == "0":
        data.pop("prototypes", None)
    (io / "types.json").write_text(json.dumps(data))
    names = {t["id"]: t["name"] for t in db["tus"]}
    if tus == ["--all"]:
        tus = [t["name"] for t in db["tus"] if t["kind"] == "game"]
    wanted = {t["id"] for t in db["tus"] if t["name"] in tus}
    if len(wanted) != len(set(tus)) or not wanted:
        raise SystemExit(f"unknown or empty TU selection: {tus}")
    funcs = [f for f in db["functions"].values() if f["tu"] in wanted and f["kind"] in WRITTEN]
    if addresses is not None:
        chosen = {hex(int(a, 16)) for a in addresses}
        if not chosen or not chosen <= {f["address"] for f in funcs}:
            raise ValueError("requested addresses are outside the selected TUs")
        funcs = [f for f in funcs if f["address"] in chosen]
    pending = funcs
    receipts, raw_paths = {}, {}
    for attempt in range(retries + 1):
        attempt_dir = io / f"attempt-{attempt}"
        attempt_dir.mkdir()
        targets = attempt_dir / "targets.txt"
        targets.write_text("".join(f"{f['address']}\n" for f in pending))
        out = attempt_dir / "out"
        result = headless(["-process", "Torchlight.bin.x86_64", "-noanalysis", "-readOnly",
                           "-scriptPath", str(io / "scripts"), "-postScript", "DecompDrafts.java",
                           str(io / "types.json"), str(targets), str(out), str(timeout * (2 ** attempt))],
                          f"drafts-{attempt}", job=job)
        for f in pending:
            address = f["address"]
            receipt = read_export(out, address) if not result.returncode else {
                "status": "NO_BODY", "error": f"headless exit {result.returncode}"}
            receipt["attempt"] = attempt + 1
            receipt["timeout_seconds"] = timeout * (2 ** attempt)
            receipts[address] = receipt
            if receipt["status"] == "COMPLETE":
                raw_paths[address] = out / f"{address}.c"
        pending = [f for f in pending if receipts[f["address"]]["status"] == "TIMEOUT"]
        if not pending:
            break
    # Receipt is written last under a publication lock. Any intermediate body mismatch is stale.
    with file_lock(OUT / ".publish.lock"):
        for tu in tus:
            tu_dir = OUT / tu
            (tu_dir / "raw").mkdir(parents=True, exist_ok=True)
            exports = {f["address"]: receipts[f["address"]] for f in funcs if names[f["tu"]] == tu}
            for address, receipt in exports.items():
                destination = tu_dir / "raw" / f"{address}.c"
                if receipt["status"] == "COMPLETE":
                    temporary = destination.with_suffix(".c.new")
                    shutil.copy(raw_paths[address], temporary)
                    os.replace(temporary, destination)
                elif destination.exists():
                    destination.unlink()  # never leave an earlier body looking like this failed export
            stamp = {"schema": DRAFT_SCHEMA, "elf": db["original_elf_sha256"], "tools": draft_tools,
                     "types_fingerprint": types_fingerprint(data), "exports": exports, "job": str(job)}
            temporary = tu_dir / "inputs.json.new"
            temporary.write_text(json.dumps(stamp, indent=1))
            os.replace(temporary, tu_dir / "inputs.json")
    failed = sum(r["status"] != "COMPLETE" for r in receipts.values())
    print(f"{len(funcs) - failed}/{len(funcs)} complete functions -> {OUT}; logs: {job}")
    return 1 if failed else 0


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
    d.add_argument("--timeout", type=int, default=int(os.environ.get("OTL_DRAFT_TIMEOUT", "120")),
                   help="seconds per function; retries double this budget")
    d.add_argument("--retries", type=int, default=int(os.environ.get("OTL_DRAFT_RETRIES", "0")),
                   help="retry timed out functions only")
    d.add_argument("--all", action="store_true", help="every game TU")
    d.add_argument("--address", action="append", help="export only these original addresses; full TU stays incomplete")
    s = sub.add_parser("stale", help="TUs whose drafts were made with other types, scripts or ELF")
    s.add_argument("--unknown", action="store_true", help="also those made before fingerprinting")
    d.add_argument("--stale", action="store_true", help="every TU `stale` lists")
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
        return drafts(tus, args.timeout, args.retries, args.address)
    return drafts(["--all"] if getattr(args, "all", False) else args.tus, args.timeout, args.retries, args.address)


if __name__ == "__main__":
    sys.exit(main() or 0)
