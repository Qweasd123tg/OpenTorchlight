#!/usr/bin/env python3
"""Package existing scoped implementations, including partially wired effects.

Uses one shared function index. Does not restart research or infer closure.
"""
from __future__ import annotations
import argparse
import json
from pathlib import Path

from automation_state import validate_output, write_json
from function_package import render_markdown
from prepare_family_packet import build_evidence
from work_frontier import build

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--group", required=True, help="shared implementation from work_frontier")
    ap.add_argument("--out", type=Path, required=True)
    ap.add_argument("--scope", choices=("ui", "all"), default="ui")
    ap.add_argument("--callsites", type=Path)
    args = ap.parse_args()
    out = args.out.resolve()
    try:
        validate_output(ROOT, out, [args.callsites] if args.callsites else [], directory=True)
        if out.exists() and (not out.is_dir() or any(out.iterdir())):
            raise ValueError("output must be a new or empty directory")
        if args.callsites and not args.callsites.is_file():
            raise ValueError("explicit callsite index does not exist")
        data = build(ROOT, None, 4, scope_name=args.scope)
        group = next((g for g in data["near_term"]["integration_groups"]
                      if g["implementation_group"] == args.group), None)
        if group is None:
            raise ValueError(f"no open integration/review group in {args.scope}: {args.group}")
        addresses = [m["address"] for m in group["members"]]
        _, document = build_evidence(ROOT, addresses, args.callsites)
        out.mkdir(parents=True, exist_ok=True)
        write_json(out / "functions.json", document)
        functions = out / "functions"
        functions.mkdir()
        for packet in document["functions"]:
            (functions / (packet["address"] + ".md")).write_text(
                render_markdown({**document, "functions": [packet]}), encoding="utf-8")
        summary = {"schema": 2, "implementation_group": args.group, "scope": args.scope,
                   "members": addresses, "evidence_index_loads": 1,
                   "source_fingerprint": document["source_fingerprint"]["sha256"],
                   "meaning": "Review existing full-function gaps; wired slice flags do not close effects."}
        write_json(out / "summary.json", summary)
        entry = [
            f"# Existing implementation: {args.group}", "",
            "Reuse the recorded implementation; inspect original code again only for a concrete unresolved contract.",
            "Read one functions/*.md card at a time; full batch evidence is in functions.json.",
            "Consume every original effect in the real application, or keep its exact omission explicitly open.",
            "Already-wired slices may still require integration: do not use four stage flags as full closure.",
            "Preserve per-member field/call/library differences; compare the translation with pinned ASM/library contracts.",
            "Trace production callers, fields and consumers; build affected code and run narrow known-contract checks.",
            "Use an original harness/trace for a concrete unresolved question.",
            "UI clicks, screenshots, frame and end-to-end scenarios are separate explicitly user-requested work.",
            "Update completion only after a full review; this packet does not promote any state.", "",
            *[f"- [{a}](functions/{a}.md)" for a in addresses],
        ]
        (out / "ENTRY.md").write_text("\n".join(entry) + "\n", encoding="utf-8")
        print(f"packet {out}: {len(addresses)} existing functions, one evidence index")
    except (OSError, ValueError) as exc:
        ap.exit(2, f"integration packet: {exc}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
