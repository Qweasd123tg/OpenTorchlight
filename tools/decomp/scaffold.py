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
from collections import defaultdict
from pathlib import Path
import re
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402

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


def safe_name(text):
    return re.sub(r"[^A-Za-z0-9_]+", "_", text).strip("_")[:120]


def packet(db, tu, elf):
    funcs = sorted((f for f in db["functions"].values() if f["tu"] == tu["id"]),
                   key=lambda f: int(f["address"], 16))
    out = OUT / tu["name"]
    (out / "asm").mkdir(parents=True, exist_ok=True)
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
        (out / "asm" / f"{name}.s").write_text(disassemble(elf, f))
        if f["kind"] != "compiler":
            targets.append(f"{f['address']} {safe_name(f['mangled']).lower()[:100]}")
        if f["kind"] in WRITTEN:
            skeleton.append(f"// {f['address']} size {f['size']} {f['kind']}"
                            + (f", return hint {hint}" if hint else ""))
            skeleton.append(f"// {f['demangled']}")
            skeleton.append("")
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
