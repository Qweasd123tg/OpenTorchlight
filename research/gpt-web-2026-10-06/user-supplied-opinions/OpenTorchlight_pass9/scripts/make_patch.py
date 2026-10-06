#!/usr/bin/env python3
"""Produce an opt-in patch against the uploaded snapshot; never edits the repository."""
import argparse,difflib,pathlib
p=argparse.ArgumentParser();p.add_argument('repo',type=pathlib.Path);p.add_argument('out',type=pathlib.Path);a=p.parse_args()
pyrel='tools/decomp/ghidra_draft.py';jrel='tools/decomp/ghidra/DecompDrafts.java'
old=(a.repo/pyrel).read_text();new=old
new=new.replace('import sys\n','import sys\nimport tempfile\n',1)
new=new.replace('def draft_state(tu, db=None, types=None):','def _input_state(tu, db=None, types=None):',1)
start=new.index('\ndef _types():')
helpers='''
def raw_status(path):
    """Export health, not a correctness judgement of the decompiled C."""
    if not path.is_file():
        return "missing"
    text = path.read_text(errors="replace")
    # Mask quoted literals first: diagnostic-looking string contents are not failures.
    token = re.compile(r'"(?:\\\\.|[^"\\\\])*"|\\\'(?:\\\\.|[^\\\'\\\\])*\\\'|/\\*.*?\\*/|//[^\\n]*', re.S)
    comments = []
    def mask(match):
        value = match.group(0)
        if value.startswith(("/*", "//")):
            comments.append(value)
        return " " * len(value)
    body = token.sub(mask, text)
    if re.search(r"\\bDECOMPILATION FAILED\\b", "\\n".join(comments)) or any(
            re.match(r"//\\s*(failed:|no function\\b)", c, re.I) for c in comments):
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

'''
new=new[:start]+'\n'+helpers+new[start:]
start=new.index('def drafts(tus):');end=new.index('\ndef find_definition(',start)
new=new[:start]+'''def drafts(tus, timeout=120, retry_failed=False):
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
    (io / "targets.txt").write_text("".join(f"{f['address']}\\n" for f in funcs))
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
            dest.write_text("// failed: expected output was not emitted\\n")
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

''' +new[end:]
new=new.replace('    d.add_argument("--stale", action="store_true", help="every TU `stale` lists")','''    d.add_argument("--stale", action="store_true", help="every TU `stale` lists")
    d.add_argument("--retry-failed", action="store_true", help="retry missing/failed exports; changed inputs force whole-TU refresh")
    d.add_argument("--timeout", type=int, default=120, help="seconds per function, including retry attempts")''')
new=new.replace('return drafts(tus)\n    drafts(["--all"] if getattr(args, "all", False) else args.tus)',
'''return drafts(tus, timeout=args.timeout, retry_failed=args.retry_failed)
    return drafts(["--all"] if getattr(args, "all", False) else args.tus,
                  timeout=args.timeout, retry_failed=args.retry_failed)''')
oldj=(a.repo/jrel).read_text();newj=oldj.replace('// Arguments: <types.json> <targets.txt: one hex address per line> <output dir>', '// Arguments: <types.json> <targets.txt: one hex address per line> <output dir> [timeout seconds]')
newj=newj.replace('        String[] args = getScriptArgs();','''        String[] args = getScriptArgs();
        if (args.length < 3 || args.length > 4) {
            throw new IllegalArgumentException("types.json targets.txt output-dir [timeout-seconds]");
        }
        final int timeoutSeconds = args.length == 4 ? Integer.parseInt(args[3]) : 120;
        if (timeoutSeconds <= 0) {
            throw new IllegalArgumentException("timeout-seconds must be positive");
        }''',1).replace('callback.setTimeout(120);','callback.setTimeout(timeoutSeconds);')
for rel,body in [(pyrel,new),(jrel,newj)]:
 out=a.out/'preview'/rel;out.parent.mkdir(parents=True,exist_ok=True);out.write_text(body)
compile(new,pyrel,'exec')
patch=''.join(difflib.unified_diff(old.splitlines(True),new.splitlines(True),fromfile='a/'+pyrel,tofile='b/'+pyrel))
patch+=''.join(difflib.unified_diff(oldj.splitlines(True),newj.splitlines(True),fromfile='a/'+jrel,tofile='b/'+jrel))
(a.out/'patches').mkdir(exist_ok=True)
(a.out/'patches'/'draft-retry-isolation.patch').write_text(patch)
print('Generated patch; Python syntax OK;',len(patch.splitlines()),'patch lines')
