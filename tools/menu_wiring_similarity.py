#!/usr/bin/env python3
"""Rank createMenus implementations by mechanically extracted CEGUI-wiring similarity.

This complements raw ASM clustering: createMenus bodies are usually not instruction-
identical, yet they often implement the same higher-level window/slot pattern.
The output is a candidate list only; it never declares semantic equivalence.
"""
from __future__ import annotations
import argparse
import json
from itertools import combinations
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def leaf_handler(symbol: str) -> str:
    name = symbol.split("(", 1)[0].split("::")[-1]
    return name[7:] if name.startswith("handle_") else name


def features(f: dict) -> set[str]:
    out = {f"creates:{f.get('creates', 0)}"}
    for k in f.get("static_keys", []):
        out.add("key:" + k.casefold())
    for _addr, symbol in f.get("subscriptions", []):
        out.add("handler:" + leaf_handler(symbol).casefold())
    for _slot, bound in f.get("counter_loops", []):
        out.add("loop:" + str(bound))
    # Dynamic searches matter structurally even when their names are runtime-generated.
    if f.get("dynamic_searches"):
        out.add("dynamic-searches:" + str(f["dynamic_searches"]))
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--report", type=Path, default=ROOT / "research/batch-menu-pass.json")
    ap.add_argument("--threshold", type=float, default=0.50)
    ap.add_argument("--out", type=Path)
    args = ap.parse_args()
    data = json.loads(args.report.read_text(encoding="utf-8"))
    funcs = [f for f in data.get("functions", []) if f.get("method") == "createMenus"]
    pairs = []
    for a, b in combinations(funcs, 2):
        A, B = features(a), features(b)
        score = len(A & B) / len(A | B) if A or B else 1.0
        if score >= args.threshold:
            pairs.append((score, a, b, sorted(A & B), sorted(A - B), sorted(B - A)))
    pairs.sort(key=lambda x: (-x[0], x[1]["class"], x[2]["class"]))
    lines = ["# createMenus wiring similarity", "",
             "> Mechanical candidate ranking from extracted window keys, handler roles, loop bounds and creation counts. Similarity is NOT proof that two menus have identical semantics.", "",
             f"Functions: **{len(funcs)}**. Pairs at threshold ≥ {args.threshold:.2f}: **{len(pairs)}**.", ""]
    for score, a, b, shared, only_a, only_b in pairs:
        lines += [f"## {a['class']} ↔ {b['class']} — {score:.2f}", "",
                  "Shared: " + (", ".join(f"`{x}`" for x in shared[:24]) or "—"), "",
                  f"Only {a['class']}: " + (", ".join(f"`{x}`" for x in only_a[:18]) or "—"), "",
                  f"Only {b['class']}: " + (", ".join(f"`{x}`" for x in only_b[:18]) or "—"), ""]
    if not pairs:
        lines.append("No candidates at this threshold.")
    text = "\n".join(lines) + "\n"
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text, encoding="utf-8")
        print(f"wrote {args.out} ({len(pairs)} candidate pairs)")
    else:
        print(text, end="")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
