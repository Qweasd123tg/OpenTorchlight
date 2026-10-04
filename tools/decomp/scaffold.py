#!/usr/bin/env python3
"""Prepare a work packet for one original translation unit.

Writes build-decomp/scaffold/<TU>/ (ignored):
  PACKET.md        functions, classes, vtables, TU data, status of decomp/src/<TU>
  asm/*.s          original disassembly per function (demangled)
  skeleton.cpp     signatures in original order; reference only, never compiled
  ghidra-targets.txt  input for tools/ghidra/ExportTargetDecompilations.java

The packet is navigation. Writing decomp/src/<TU> is the actual work; a function
counts when objdiff and the hybrid self-tests say so.

    python3 tools/decomp/scaffold.py RunicCore.cpp
    python3 tools/decomp/scaffold.py --list [--max-functions 10]
"""
from __future__ import annotations

import argparse
import json
import shutil
from collections import defaultdict
from pathlib import Path
import re
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import elfimage  # noqa: E402
import calls as calltrace  # noqa: E402
import layout as layouts  # noqa: E402
import objdiff  # noqa: E402

ROOT = elfdb.ROOT
OUT = ROOT / "build-decomp" / "scaffold"
SRC = ROOT / "decomp" / "src"
WRITTEN = ("function", "ctor", "dtor", "static")


def tu_by_name(db, name):
    matches = [t for t in db["tus"] if t["name"].lower() == name.lower()]
    if len(matches) != 1:
        raise SystemExit(f"no unique TU named {name}")
    return matches[0]


def list_tus(db, max_functions):
    by_tu = defaultdict(list)
    for f in db["functions"].values():
        by_tu[f["tu"]].append(f)
    rows = []
    for t in db["tus"]:
        if t["kind"] != "game":
            continue
        own = [f for f in by_tu[t["id"]] if f["kind"] in WRITTEN]
        if not own or (max_functions and len(own) > max_functions):
            continue
        done = (SRC / t["name"]).exists()
        rows.append((len(own), sum(f["size"] for f in own), t["name"], done))
    for count, size, name, done in sorted(rows):
        print(f"{count:4} functions {size:7} bytes  {name}{'  [decomp/src exists]' if done else ''}")


def disassemble(elf, f):
    start = int(f["address"], 16)
    return subprocess.run(["objdump", "-d", "-C", "-w", "--no-show-raw-insn",
                           f"--start-address={start:#x}", f"--stop-address={start + f['size']:#x}", str(elf)],
                          capture_output=True, text=True, check=True, env={"LC_ALL": "C", "PATH": "/usr/bin:/bin"}).stdout


def annotate(asm, image):
    """Append literal contents for immediates and RIP targets pointing into .rodata."""
    out = []
    for line in asm.splitlines():
        targets = [int(m, 16) for m in re.findall(r"#\s*([0-9a-f]+)\b", line)]
        targets += [int(m, 16) for m in re.findall(r"\$0x([0-9a-f]+)", line)]
        notes = []
        for address in targets:
            section = image.section_at(address)
            if not section or not section.name.startswith(".rodata"):
                continue
            try:
                raw = image.read(address, 512)
            except ValueError:
                continue
            text = objdiff.printable_string(raw)
            if text is not None:
                notes.append(text + '"' if text.startswith('L"') else f'"{text}"')
            else:
                notes.append("bytes " + raw[:8].hex())
        out.append(line + ("    ; " + " ".join(notes) if notes else ""))
    return "\n".join(out) + "\n"


def trial_build(tu, funcs, out):
    """trial.cpp and generated headers: what tools/decomp/draft_trial.py got to compile."""
    lines = []
    gen = ROOT / "build-decomp" / "include-gen"
    classes = sorted({(f.get("scope") or "").split("::")[0] for f in funcs} - {""})
    have = [c for c in classes if (gen / f"{c}.h").exists()]
    if have:
        lines += ["## Generated headers", "",
                  "`build-decomp/include-gen/` has a header for every class without a hand-written one: bases,",
                  "virtuals in vtable order, fields at the original offsets (sizes and offsets checked by the",
                  "compiler), return types from Ghidra. Start the class header from it: move it to",
                  "`decomp/include/<Class>.h`, name the fields, drop the gaps you understand.", ""]
        lines += [f"- `build-decomp/include-gen/{c}.h`" for c in have] + [""]
    trial = ROOT / "build-decomp" / "trial" / tu["name"]
    summary = ROOT / "build-decomp" / "trial" / "summary.json"
    if trial.exists():
        shutil.copy(trial, out / "trial.cpp")
        statuses = json.loads(summary.read_text()).get(tu["name"], {}) if summary.exists() else {}
        lines += ["## Trial build", "",
                  "`trial.cpp`: the Ghidra drafts that compile against the generated headers (with",
                  "-fpermissive). Status per function from objdiff; compile errors name the first problem.", ""]
        for f in funcs:
            if f["address"] in statuses:
                lines.append(f"- `{f['address']}` {f['demangled'][:70]}: {statuses[f['address']][:110]}")
        lines.append("")
    return lines


def ghidra_drafts(db, tu, funcs, out):
    """ghidra.cpp: converted Ghidra drafts of the TU, when tools/decomp/ghidra_draft.py has run."""
    raw_dir = ROOT / "build-decomp" / "drafts" / tu["name"] / "raw"
    if not raw_dir.exists():
        return []
    import ghidra_cpp
    methods, signatures, enums = ghidra_cpp.known_methods(db), ghidra_cpp.signatures_of(db), ghidra_cpp.parse_enums()
    parts = []
    for f in funcs:
        raw = raw_dir / f"{f['address']}.c"
        if f["kind"] in WRITTEN and raw.exists() and not any(n.endswith("D0Ev") for n in f["names"]):
            try:
                parts.append(f"// {f['address']} {f['demangled']}\n" +
                             ghidra_cpp.convert(raw.read_text(), methods, f, signatures, enums))
            except Exception as error:  # a draft is optional
                parts.append(f"// {f['address']}: conversion failed: {error}\n")
    (out / "ghidra.cpp").write_text("// Ghidra drafts with recovered types, converted by tools/decomp/ghidra_cpp.py.\n"
                                   "// Not compiled. Inlined TArrayList/std::string code may still be expanded.\n\n"
                                   + "\n".join(parts))
    import ghidra_draft
    state, reasons = ghidra_draft.draft_state(tu["name"], db)
    warning = ([f"**Stale drafts** ({'; '.join(reasons)}): field names and types in them may be outdated; "
                "trust the headers, or remake them with `ghidra_draft.py drafts --stale`.", ""]
               if state == "stale" else [])
    return ["## Ghidra drafts", ""] + warning + [
            f"`ghidra.cpp`: {len(parts)} functions decompiled with the recovered types and converted to C++.",
            "Start from them instead of the ASM; verify with objdiff and self-tests.", ""]


def static_init_order(funcs, data, elf):
    """TU-local objects in the order the static initializer constructs them, with known headers."""
    inits = [f for f in funcs if f["kind"] == "compiler" and ("__static_initialization" in f["demangled"]
                                                             or "global constructors" in f["demangled"])]
    by_addr = {int(g["address"], 16): g for g in data}
    order = []
    for f in inits:
        for m in re.finditer(r"(?:#\s*|\$0x)([0-9a-f]+)", disassemble(elf, f)):
            g = by_addr.get(int(m.group(1), 16))
            if g and g["demangled"] not in order:
                order.append(g["demangled"])
    if not order:
        return []
    headers = {"std::__ioinit": "<iostream> (через заголовки OGRE)"}
    for h in sorted((ROOT / "decomp" / "include").glob("*.h")):
        text = h.read_text(errors="replace")
        for name in order:
            bare = name.split("::")[-1]
            if name not in headers and re.search(rf"\b{re.escape(bare)}\b\s*(\[|=|;|\()", text):
                headers[name] = h.name
    out = ["## Static initializer order", "",
           "Objects in construction order: the `#include` order of the TU must reproduce it.", ""]
    for name in order:
        out.append(f"- `{name}`" + (f" — `{headers[name]}`" if name in headers else " — header not recovered yet"))
    return out + [""]


def safe_name(text):
    return re.sub(r"[^A-Za-z0-9_]+", "_", text).strip("_")[:120]


def packet(db, tu, elf):
    funcs = sorted((f for f in db["functions"].values() if f["tu"] == tu["id"]),
                   key=lambda f: int(f["address"], 16))
    out = OUT / tu["name"]
    (out / "asm").mkdir(parents=True, exist_ok=True)
    image = elfimage.load(elf)
    classes = sorted({f["scope"] for f in funcs if f["scope"] and f["kind"] in WRITTEN})
    data = [g for g in db["globals"] if g.get("file") == tu["name"]]
    lines = [f"# {tu['name']} (TU {tu['id']})", "",
             f"Original ELF `{db['original_elf_sha256']}`; range {tu['start'] and hex(tu['start'])}.."
             f"{tu['end'] and hex(tu['end'])}; {tu['functions']} functions, {tu['bytes']} bytes.", "",
             f"Decomp source: `decomp/src/{tu['name']}` "
             f"({'exists' if (SRC / tu['name']).exists() else 'not started'}).", "",
             "Fields marked hint/confidence are heuristics from tools/decomp/elfdb.py.", "",
             "## Functions", "", "| address | size | kind | TU confidence | return hint | function |",
             "|---|---:|---|---|---|---|"]
    targets = []
    skeleton = [f"// Reference skeleton for {tu['name']} in original address order. Not compiled.",
                "// Return types are not encoded in mangled names: verify against callers and ASM.", ""]
    for f in funcs:
        hint = f.get("return_hint", {}).get("kind", "")
        slots = ", ".join(f"{v['class']}[{v['slot']}]" for v in f.get("vslots", [])[:3])
        extra = f" (virtual: {slots}{'...' if len(f.get('vslots', [])) > 3 else ''})" if slots else ""
        lines.append(f"| {f['address']} | {f['size']} | {f['kind']} | {f['tu_confidence']} | {hint} | "
                     f"`{f['demangled']}`{extra} |")
        name = f"{f['address']}_{safe_name(f['demangled'])}"
        (out / "asm" / f"{name}.s").write_text(annotate(disassemble(elf, f), image))
        if f["kind"] != "compiler":
            targets.append(f"{f['address']} {safe_name(f['mangled']).lower()[:100]}")
        if f["kind"] in WRITTEN:
            skeleton.append(f"// {f['address']} size {f['size']} {f['kind']}"
                            + (f", return hint {hint}" if hint else ""))
            skeleton.append(f"// {f['demangled']}")
            skeleton.append("")
    lay = layouts.Layout(db, layouts.load_insns(db, elf))
    tracer = calltrace.Tracer(db)
    (out / "calls").mkdir(exist_ok=True)
    traced = 0
    for f in funcs:
        if f["size"] >= 200 and f["kind"] != "inline_or_template":
            trace = tracer.trace(f)
            if trace:
                traced += 1
                name = f"{f['address']}_{safe_name(f['demangled'])}"
                (out / "calls" / f"{name}.txt").write_text(
                    f"// {f['demangled']} ({f['size']} bytes): calls in address order\n" + "\n".join(trace) + "\n")
    field_names = {}
    (out / "draft").mkdir(exist_ok=True)
    for name in classes:
        if name not in db["classes"]:
            continue
        try:
            start, size, rows = lay.rows(name)
        except Exception as error:  # draft only; never block the packet
            print(f"layout {name}: {error}", file=sys.stderr)
            continue
        field_names[name] = {off: fname for off, fd, ctype, note, fname in rows}
        (out / "draft" / f"{name.lstrip('C') or name}.h").write_text(lay.header(name))
    trivial = 0
    for f in funcs:
        if f["kind"] in WRITTEN and f.get("scope") in field_names:
            body = lay.trivial_body(f, field_names[f["scope"]])
            if body:
                trivial += 1
                ret = "" if f["kind"] in ("ctor", "dtor") else lay.return_type(f) + " "
                params = layouts.split_params(f.get("params") or "")
                sig = f["demangled"]
                if body.count("value") and len(params) == 1:
                    sig = sig.replace(f"({f['params']})", f"({params[0]} value)")
                skeleton += [f"// draft body ({f['address']}); verify with objdiff", f"{ret}{sig}", body, ""]
    lines += ["", "## Layout drafts", "",
              "Generated by `tools/decomp/layout.py`: names come from accessors and editor property",
              "functions (`CXDescriptor::Get_get…`), types from instruction forms. Draft headers are in",
              f"`draft/`; {trivial} trivial bodies are in `skeleton.cpp`. Verify before use.", "",
              f"`calls/` has call traces with resolved arguments for {traced} larger functions",
              "(`tools/decomp/calls.py`): read them before the full ASM.", ""]
    for name in classes:
        if name in field_names:
            lines += [lay.table(name), ""]
    lines += ["", "## Classes", ""]
    for name in classes:
        c = db["classes"].get(name, {})
        bases = ", ".join(f"{b['class']} @+{b['offset']:#x}{' virtual' if b['virtual'] else ''}"
                          for b in c.get("bases", [])) or "none / not polymorphic"
        sizes = ", ".join(f"{k} bytes at {', '.join(v)}" for k, v in c.get("size_observed", {}).items()) or "none"
        lines += [f"### {name}", "", f"- bases (RTTI): {bases}", f"- allocation sizes before ctor (hint): {sizes}",
                  f"- methods in binary: {len(c.get('methods', []))}; TUs: {c.get('tus', {})}"]
        vt = db["vtables"].get(name)
        if vt:
            by_addr = db["functions"]
            for gi, group in enumerate(vt["groups"]):
                lines.append(f"- vtable group {gi} (offset to top {group['offset_to_top']}):")
                for si, slot in enumerate(group["slots"]):
                    if isinstance(slot, str) and slot in by_addr:
                        label = by_addr[slot]["demangled"]
                    else:
                        label = str(slot)
                    lines.append(f"  - [{si}] {label}")
        lines.append("")
    lines += ghidra_drafts(db, tu, funcs, out)
    lines += trial_build(tu, funcs, out)
    lines += static_init_order(funcs, data, elf)
    lines += ["## TU-local data", "", "| address | size | section | symbol |", "|---|---:|---|---|"]
    lines += [f"| {g['address']} | {g['size']} | {g['section']} | `{g['demangled']}` |" for g in data]
    (out / "PACKET.md").write_text("\n".join(lines) + "\n")
    (out / "skeleton.cpp").write_text("\n".join(skeleton) + "\n")
    (out / "ghidra-targets.txt").write_text("\n".join(targets) + "\n")
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("tu", nargs="?")
    parser.add_argument("--list", action="store_true")
    parser.add_argument("--max-functions", type=int, default=0)
    parser.add_argument("--elf", type=Path, default=elfdb.default_elf())
    args = parser.parse_args()
    db = elfdb.load_db()
    if args.list:
        list_tus(db, args.max_functions)
        return
    if not args.tu:
        parser.error("TU name or --list")
    out = packet(db, tu_by_name(db, args.tu), args.elf)
    print(f"wrote {out.relative_to(ROOT)}/PACKET.md")


if __name__ == "__main__":
    main()
