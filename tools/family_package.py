#!/usr/bin/env python3
"""Create one review packet for a repeated original method family.

The point is to analyse a family once, then keep an explicit delta table for
members.  This does not claim identical semantics just because names match.

Example:
  python3 tools/family_package.py setOpen --out build-verification/setOpen.md
  python3 tools/family_package.py updateLayout --subsystem frontend --out /tmp/updateLayout.md
"""
from __future__ import annotations

import argparse
import csv
import json
import re
from functools import lru_cache
from collections import Counter
from pathlib import Path
from automation_state import validate_output
from transfer_contract import completion, in_scope, load_scope

ROOT = Path(__file__).resolve().parents[1]


def addr(raw: str) -> str:
    return f"0x{int(raw, 16):08x}"


def method(symbol: str) -> str | None:
    m = re.search(r"(?:^|\s)([A-Za-z_]\w*)::([^:( ]+)\(", symbol)
    return m.group(2) if m else None


def cls(symbol: str) -> str:
    m = re.search(r"(?:^|\s)([A-Za-z_]\w*)::[^:( ]+\(", symbol)
    return m.group(1) if m else "?"


def transfer(root: Path) -> dict[str, dict]:
    p = root / "research/function-transfer.json"
    return json.loads(p.read_text(encoding="utf-8")).get("functions", {}) if p.is_file() else {}


@lru_cache(maxsize=4)
def search_corpus(root: Path, bases: tuple[str, ...], suffixes: frozenset[str]) -> tuple:
    corpus = []
    for base in bases:
        path = root / base
        if not path.exists():
            continue
        for f in sorted(path.rglob("*")):
            if not f.is_file() or f.suffix.lower() not in suffixes:
                continue
            try:
                text = f.read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            corpus.append((str(f.relative_to(root)), f.name.lower(), text.lower()))
    return tuple(corpus)


def file_mentions(root: Path, needle: str, bases: list[str], suffixes: set[str], limit: int = 12) -> list[str]:
    return [relative for relative, filename, text in search_corpus(root, tuple(bases), frozenset(suffixes))
            if needle.lower() in text or needle.lower().replace("0x", "") in filename][:limit]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("method")
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--subsystem", default="")
    ap.add_argument("--scope", choices=("ui", "all"), default="ui")
    ap.add_argument("--class-regex", default="")
    ap.add_argument("--out", type=Path)
    args = ap.parse_args()
    root = args.root.resolve()
    scope = load_scope(root, args.scope)
    if args.out:
        validate_output(root, args.out)
    tx = transfer(root)
    rows = []
    with (root / "research/coverage.tsv").open(newline="", encoding="utf-8") as fh:
        for r in csv.DictReader(fh, delimiter="\t"):
            if r["address"].startswith("port:") or method(r["symbol"]) != args.method:
                continue
            if not in_scope(r["symbol"], r["address"], scope):
                continue
            if args.subsystem and r["subsystem"] != args.subsystem:
                continue
            if args.class_regex and not re.search(args.class_regex, cls(r["symbol"])):
                continue
            a = addr(r["address"])
            e = tx.get(a, {})
            s = e.get("stages", {})
            rows.append({
                "address": a, "class": cls(r["symbol"]), "symbol": r["symbol"],
                "subsystem": r["subsystem"], "incoming": r["incoming"], "outgoing": r["outgoing"],
                "status": r["status"],
                "analyzed": bool(s.get("analyzed")), "ported": bool(s.get("ported")),
                "wired": bool(s.get("wired")), "compared": bool(s.get("compared")),
                "evidence": e.get("evidence", r.get("evidence", "")),
                "implementation": e.get("implementation", r.get("implementation", "")),
                "notes": e.get("notes", ""),
                "completion": completion(e, root),
                "source_files": file_mentions(root, a, ["research/decompiled-core", "research/decompiled", "research/disassembly"], {".c", ".asm", ".txt", ".md"}),
            })
    rows.sort(key=lambda r: int(r["address"], 16))
    if not rows:
        raise SystemExit(f"no original methods named {args.method!r} in scope")
    if len(rows) > 64:
        raise SystemExit("family exceeds 64 members; narrow --class-regex or --subsystem")
    subs = Counter(r["subsystem"] for r in rows)
    lines = [f"# Family packet: `{args.method}`", "",
             f"Members: **{len(rows)}**. Subsystems: " + ", ".join(f"{k}={v}" for k,v in subs.most_common()) + ".", "",
             "> Same method name is a batching hint, not proof of identical behavior. Pick a representative, then record every member delta. A/P/W/C are bounded stages, not full closure.", "",
             "## Member matrix", "",
             "| Address | Class | Subsystem | A | P | W | C | Evidence/source |", "|---|---|---|:---:|:---:|:---:|:---:|---|"]
    for r in rows:
        src = r["source_files"][0] if r["source_files"] else (r["evidence"] or "—")
        lines.append(f"| `{r['address']}` | `{r['class']}` | {r['subsystem']} | {'✓' if r['analyzed'] else ''} | {'✓' if r['ported'] else ''} | {'✓' if r['wired'] else ''} | {'✓' if r['compared'] else ''} | `{src}` |")
    lines += ["", "## Whole-function acceptance", ""]
    lines += [f"- `{r['address']}`: {r['completion']['status']}; " +
              ("; ".join(r['completion']['open_items'] + r['completion']['errors']) or
               "No explicit open items here; consult the full review, not just stage flags.") for r in rows]
    lines += ["", "## Delta checklist (fill per member; do not infer from the representative)", "",
              "For each member record: early exits; field writes; constants; loop bounds; resource names; direct/indirect callees; event subscriptions; RNG source/order; ownership/lifetime; error path; side effects; caller wiring.", "",
              "## Suggested workflow", "",
              "1. Choose the best-evidenced member as representative.",
              "2. Extract a common skeleton only after comparing at least two members.",
              "3. Encode member differences as data/profile fields when semantics match.",
              "4. Keep exceptions separate instead of growing flags indefinitely.",
              "5. Wire the family into a real scenario before researching another large family.", ""]
    out = "\n".join(lines)
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(out, encoding="utf-8")
        print(f"wrote {args.out} ({len(rows)} members)")
    else:
        print(out)
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
