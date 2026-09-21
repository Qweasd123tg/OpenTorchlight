#!/usr/bin/env python3
"""Cluster repeated original methods by normalized machine-code shape.

This is a *candidate generator*, not an equivalence proof.  It removes concrete
addresses, immediates and object-field displacements, then groups functions that
have the same instruction skeleton.  Near matches are reported separately.

Why useful: a 20-member family with 14 exact skeleton matches should normally be
reviewed as one representative + a delta table, not as 14 independent reverse-
engineering tasks.

Examples:
  python3 tools/asm_family_cluster.py setOpen --elf /path/Torchlight.bin.x86_64
  python3 tools/asm_family_cluster.py handle_CloseButton --elf "$TORCHLIGHT_ORIGINAL_ELF" --out /tmp/close.md
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
from difflib import SequenceMatcher
from pathlib import Path
from automation_state import validate_output
from transfer_contract import in_scope, load_scope

ROOT = Path(__file__).resolve().parents[1]
PINNED_SHA256 = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
SYM_RE = re.compile(r"^([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([TtWw])\s+(.+)$")


def method(symbol: str) -> str | None:
    m = re.search(r"(?:^|\s)([A-Za-z_]\w*)::([^:( ]+)\(", symbol)
    return m.group(2) if m else None


def cls(symbol: str) -> str:
    m = re.search(r"(?:^|\s)([A-Za-z_]\w*)::[^:( ]+\(", symbol)
    return m.group(1) if m else "?"


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as fh:
        while True:
            b = fh.read(1024 * 1024)
            if not b:
                break
            h.update(b)
    return h.hexdigest()


def symbols_for(name: str, class_regex: str, scope_name: str = "ui") -> list[dict]:
    out = []
    cre = re.compile(class_regex) if class_regex else None
    scope = load_scope(ROOT, scope_name)
    for line in (ROOT / "research/original-symbols.txt").read_text(encoding="utf-8", errors="replace").splitlines():
        m = SYM_RE.match(line.strip())
        if not m:
            continue
        address, size, _typ, symbol = m.groups()
        if not in_scope(symbol, address, scope):
            continue
        if method(symbol) != name:
            continue
        c = cls(symbol)
        if cre and not cre.search(c):
            continue
        out.append({"address": int(address, 16), "size": int(size, 16), "symbol": symbol, "class": c})
    # aliases can duplicate an address; prefer longest symbol and max size.
    by = {}
    for row in out:
        cur = by.get(row["address"])
        if cur is None or (row["size"], len(row["symbol"])) > (cur["size"], len(cur["symbol"])):
            by[row["address"]] = row
    return sorted(by.values(), key=lambda r: r["address"])


def dump_text(elf: Path, start: int, size: int) -> str:
    if size <= 0:
        raise ValueError(f"No sized original body at 0x{start:x}")
    cmd = ["objdump", "-d", "--no-show-raw-insn", f"--start-address={start}", f"--stop-address={start+size}", str(elf)]
    p = subprocess.run(cmd, check=True, capture_output=True, text=True)
    return p.stdout


def instructions(assembly: str) -> list[str]:
    ins = []
    for line in assembly.splitlines():
        m = re.match(r"\s*[0-9a-f]+:\s+([a-zA-Z][a-zA-Z0-9.]*)\s*(.*)$", line)
        if not m:
            continue
        mnemonic, operands = m.groups()
        operands = operands.split("#", 1)[0].strip()
        ins.append(mnemonic + (" " + operands if operands else ""))
    return ins


def dump(elf: Path, start: int, size: int) -> list[str]:
    return instructions(dump_text(elf, start, size))


def normalize_instruction(text: str, semantic_calls: bool = False) -> str:
    mnemonic, _, ops = text.partition(" ")
    # Calls: optionally preserve callee symbol class/method; otherwise only call shape.
    if mnemonic.startswith("call"):
        if semantic_calls:
            sm = re.search(r"<([^>]+)>", ops)
            target = sm.group(1).split("@", 1)[0] if sm else "indirect"
            target = re.sub(r"\+0x[0-9a-f]+$", "", target)
            return f"{mnemonic} CALL:{target}"
        return f"{mnemonic} CALL"
    if mnemonic.startswith("j"):
        return f"{mnemonic} BR"
    # Strip symbolic comments/targets then normalize constants and object offsets.
    ops = re.sub(r"<[^>]+>", "SYM", ops)
    ops = re.sub(r"\$-?0x[0-9a-f]+", "IMM", ops)
    ops = re.sub(r"\$-?[0-9]+", "IMM", ops)
    # RIP-relative data and ordinary struct/stack displacements.
    ops = re.sub(r"-?0x[0-9a-f]+\(%rip\)", "DATA(%rip)", ops)
    ops = re.sub(r"-?0x[0-9a-f]+\((%[a-z0-9]+)(?:,([^)]*))?\)",
                 lambda m: "DISP(" + m.group(1) + (("," + m.group(2)) if m.group(2) else "") + ")", ops)
    # bare absolute values (e.g. movabs or address materialisation)
    ops = re.sub(r"(?<![%a-z0-9])0x[0-9a-f]+", "ADDR", ops)
    return mnemonic + (" " + ops if ops else "")


def fingerprint(seq: list[str]) -> str:
    return hashlib.sha256("\n".join(seq).encode()).hexdigest()[:16]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("method")
    ap.add_argument("--elf", type=Path, required=True)
    ap.add_argument("--class-regex", default="^C", help="default: game-style C* classes")
    ap.add_argument("--scope", choices=("ui", "all"), default="ui")
    ap.add_argument("--near", type=float, default=None,
                    help="opt-in quadratic near-shape comparisons; exact grouping is the default")
    ap.add_argument("--max-members", type=int, default=64)
    ap.add_argument("--assembly-dir", type=Path, help="keep the same decoded member bodies for delta review")
    ap.add_argument("--out", type=Path)
    ap.add_argument("--json", type=Path, help="machine-readable cluster report")
    args = ap.parse_args()
    if args.near is not None and not 0 < args.near <= 1:
        ap.error("--near must be in (0, 1]")
    if not 1 <= args.max_members <= 64:
        ap.error("--max-members must be in 1..64; split larger families explicitly")
    for path in (args.out, args.json, args.assembly_dir):
        if path:
            validate_output(ROOT, path, [args.elf], directory=path == args.assembly_dir)
    if args.out and args.json and args.out.resolve() == args.json.resolve():
        ap.error("--out and --json must differ")
    if sha256(args.elf) != PINNED_SHA256:
        raise SystemExit("ELF fingerprint mismatch; refusing to compare a different build")
    rows = symbols_for(args.method, args.class_regex, args.scope)
    if not rows:
        raise SystemExit(f"no methods named {args.method!r}")
    if len(rows) > args.max_members:
        ap.error(f"{len(rows)} members exceed budget {args.max_members}; narrow --class-regex")
    if args.assembly_dir:
        args.assembly_dir.mkdir(parents=True, exist_ok=True)
    for r in rows:
        assembly = dump_text(args.elf, r["address"], r["size"])
        if args.assembly_dir:
            destination = args.assembly_dir / f"0x{r['address']:08x}.asm"
            validate_output(ROOT, destination, [args.elf])
            destination.write_text(assembly, encoding="utf-8")
        raw = instructions(assembly)
        if not raw:
            raise ValueError(f"Empty disassembly at 0x{r['address']:x}; not an equivalent empty function")
        r["raw_count"] = len(raw)
        r["shape"] = [normalize_instruction(x, False) for x in raw]
        r["semantic"] = [normalize_instruction(x, True) for x in raw]
        r["shape_hash"] = fingerprint(r["shape"])
        r["semantic_hash"] = fingerprint(r["semantic"])
    groups = {}
    for r in rows:
        groups.setdefault(r["shape_hash"], []).append(r)
    clusters = sorted(groups.values(), key=lambda g: (-len(g), g[0]["address"]))
    near = []
    # Only compare cluster representatives; avoids quadratic blow-up on duplicates.
    reps = [g[0] for g in clusters]
    for i, a in enumerate(reps):
        if args.near is None:
            break
        for b in reps[i+1:]:
            ratio = SequenceMatcher(a=a["shape"], b=b["shape"], autojunk=False).ratio()
            if ratio >= args.near:
                near.append((ratio, a, b))
    near.sort(key=lambda x: (-x[0], x[1]["address"], x[2]["address"]))
    lines = [f"# ASM family clusters: `{args.method}`", "",
             f"Pinned ELF `{PINNED_SHA256}`. Members: **{len(rows)}**; exact normalized-shape clusters: **{len(clusters)}**.", "",
             "> Exact normalized shape removes constants, addresses and field displacements. It is a strong batching hint, NOT semantic equivalence. Member deltas still need review.", "",
             "## Exact shape clusters", ""]
    for n, g in enumerate(clusters, 1):
        lines.append(f"### Cluster {n}: {len(g)} member(s), shape `{g[0]['shape_hash']}`")
        sem = len(set(x["semantic_hash"] for x in g))
        lines.append(f"Instruction count: {g[0]['raw_count']}; semantic-call variants inside cluster: {sem}.")
        for r in g:
            lines.append(f"- `0x{r['address']:08x}` `{r['symbol']}` semantic `{r['semantic_hash']}`")
        lines.append("")
    lines += ["## Near-shape cluster pairs", ""]
    if near:
        for ratio, a, b in near[:40]:
            lines.append(f"- {ratio:.3f}: `0x{a['address']:08x}` {a['class']} ↔ `0x{b['address']:08x}` {b['class']}")
    else:
        lines.append("Not requested (use --near to opt in)." if args.near is None else "None at the selected threshold.")
    lines += ["", "## Use", "",
              "Start with the largest exact cluster. Compare constants, field offsets, call targets and callers per member; encode true deltas as profile data. Split any semantic exception instead of adding guessed flags.", ""]
    text = "\n".join(lines)
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text, encoding="utf-8")
        print(f"wrote {args.out}")
    else:
        print(text)
    if args.json:
        payload = {
            "schema": 1,
            "method": args.method,
            "scope": args.scope,
            "near_threshold": args.near,
            "elf_sha256": PINNED_SHA256,
            "members": len(rows),
            "clusters": [
                {
                    "shape_hash": g[0]["shape_hash"],
                    "instruction_count": g[0]["raw_count"],
                    "members": [
                        {"address": f"0x{r['address']:08x}", "symbol": r["symbol"],
                         "class": r["class"], "semantic_hash": r["semantic_hash"]}
                        for r in g
                    ],
                }
                for g in clusters
            ],
            "near_pairs": [
                {"ratio": ratio, "left": f"0x{a['address']:08x}",
                 "right": f"0x{b['address']:08x}"}
                for ratio, a, b in near[:100]
            ],
        }
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(payload, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(f"wrote {args.json}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
