#!/usr/bin/env python3
"""Build a practical next-work queue from the existing reverse-engineering data.

This is deliberately NOT a progress percentage.  It answers three questions:
  1. What is already ported but still not wired/compared?  (cheap integration wins)
  2. Which original method names form reusable families?    (batch candidates)
  3. How much of the raw function list is obvious bookkeeping/noise? (do not count it as game tasks)

Inputs are read-only: coverage.tsv, function-transfer.json, original-symbols.txt,
original callgraph/callsites when present.  The tool never promotes statuses.

Examples:
  python3 tools/work_frontier.py --out research/work-frontier.md --json research/work-frontier.json
  python3 tools/work_frontier.py --subsystem frontend --top 40
"""
from __future__ import annotations

import argparse
import csv
import json
import re
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def load_coverage(root: Path) -> list[dict]:
    with (root / "research/coverage.tsv").open(newline="", encoding="utf-8") as fh:
        return list(csv.DictReader(fh, delimiter="\t"))


def load_transfer(root: Path) -> dict[str, dict]:
    path = root / "research/function-transfer.json"
    if not path.is_file():
        return {}
    return json.loads(path.read_text(encoding="utf-8")).get("functions", {})


def addr_key(raw: str) -> str:
    raw = raw.strip().lower()
    if raw.startswith("port:"):
        return raw
    return f"0x{int(raw, 16):08x}"


def method_name(symbol: str) -> str | None:
    # Ignore prefixes used by nm for thunks while still classifying them separately.
    m = re.search(r"(?:^|\s)([A-Za-z_][\w:]*)::([^:( ]+)\(", symbol)
    return m.group(2) if m else None


def class_name(symbol: str) -> str | None:
    m = re.search(r"(?:^|\s)([A-Za-z_]\w*)::[^:( ]+\(", symbol)
    return m.group(1) if m else None


def game_style(symbol: str) -> bool:
    """Torchlight game classes are predominantly C*; exclude bundled vendor namespaces
    from the default batching queue without pretending they are irrelevant forever."""
    base = symbol
    if "thunk to " in base:
        base = base.split("thunk to ", 1)[1]
    return re.match(r"^C[A-Za-z0-9_]+::", base) is not None


def technical_kind(symbol: str) -> str | None:
    low = symbol.lower()
    if "thunk to " in low:
        return "thunk"
    if "::~" in symbol:
        return "destructor"
    meth = method_name(symbol) or ""
    if meth in {"getSingleton", "getSingletonPtr"}:
        return "singleton_accessor"
    if meth in {"CreateObject", "DestroyObject"}:
        return "factory_wrapper"
    if re.match(r"^(?:Get_get|Set_set)", meth):
        return "binding_accessor"
    return None


def stages(entry: dict | None) -> tuple[bool, bool, bool, bool]:
    s = (entry or {}).get("stages", {})
    return tuple(bool(s.get(k)) for k in ("analyzed", "ported", "wired", "compared"))


def intish(value: str, default: int = 0) -> int:
    try:
        return int(value)
    except (TypeError, ValueError):
        return default


def floatish(value: str, default: float = 0.0) -> float:
    try:
        return float(value)
    except (TypeError, ValueError):
        return default


def implementation_group(item: dict) -> str:
    raw = item.get("implementation", "") or ""
    # First concrete project source path is a good batching key for shared helpers.
    m = re.search(r"(?:^|[;,( ]+)((?:src|include)/[^;,) ]+)", raw)
    if m:
        return m.group(1)
    return item["address"]


def build(root: Path, subsystem: str | None, min_family: int, include_vendor: bool = False) -> dict:
    rows = [r for r in load_coverage(root) if not r["address"].startswith("port:")]
    if subsystem:
        rows = [r for r in rows if r.get("subsystem") == subsystem]
    transfer = load_transfer(root)

    integration = []
    comparison = []
    analyzed_only = []
    families: dict[str, list[dict]] = defaultdict(list)
    noise = Counter()

    for r in rows:
        address = addr_key(r["address"])
        entry = transfer.get(address)
        a, p, w, c = stages(entry)
        item = {
            "address": address,
            "symbol": r["symbol"],
            "subsystem": r.get("subsystem", ""),
            "status": r.get("status", ""),
            "priority": floatish(r.get("priority", "0")),
            "incoming": intish(r.get("incoming", "0")),
            "outgoing": intish(r.get("outgoing", "0")),
            "stages": {"analyzed": a, "ported": p, "wired": w, "compared": c},
            "implementation": (entry or {}).get("implementation", r.get("implementation", "")),
            "tests": (entry or {}).get("tests", r.get("tests", "")),
            "notes": (entry or {}).get("notes", ""),
        }
        if p and not w:
            integration.append(item)
        if w and not c:
            comparison.append(item)
        if a and not p:
            analyzed_only.append(item)

        kind = technical_kind(r["symbol"])
        if kind:
            noise[kind] += 1
        meth = method_name(r["symbol"])
        if meth and (include_vendor or game_style(r["symbol"])):
            families[meth].append(item)

    # Families are suggestions only.  Score favours reuse and current evidence,
    # but penalises groups that are almost entirely technical wrappers.
    fam_rows = []
    for meth, members in families.items():
        if len(members) < min_family:
            continue
        tech = sum(technical_kind(m["symbol"]) is not None for m in members)
        traced = sum(any(m["stages"].values()) for m in members)
        ported = sum(m["stages"]["ported"] for m in members)
        wired = sum(m["stages"]["wired"] for m in members)
        compared = sum(m["stages"]["compared"] for m in members)
        subs = Counter(m["subsystem"] for m in members)
        # Benefit proxy, not a completion metric.
        reuse_score = len(members) * 4 + traced * 3 + ported * 2 - tech * 3
        fam_rows.append({
            "method": meth,
            "members": len(members),
            "technical_members": tech,
            "tracked": traced,
            "ported": ported,
            "wired": wired,
            "compared": compared,
            "reuse_score": reuse_score,
            "subsystems": dict(subs.most_common()),
            "examples": [{"address": m["address"], "symbol": m["symbol"]} for m in members[:8]],
        })

    integration.sort(key=lambda x: (-x["priority"], -x["incoming"], x["address"]))
    comparison.sort(key=lambda x: (-x["priority"], -x["incoming"], x["address"]))
    integration_groups_map: dict[str, list[dict]] = defaultdict(list)
    for item in integration:
        integration_groups_map[implementation_group(item)].append(item)
    integration_groups = [
        {"implementation_group": key, "members": members}
        for key, members in integration_groups_map.items()
    ]
    integration_groups.sort(key=lambda g: (-len(g["members"]), g["implementation_group"]))
    analyzed_only.sort(key=lambda x: (-x["priority"], -x["incoming"], x["address"]))
    fam_rows.sort(key=lambda x: (-x["reuse_score"], -x["members"], x["method"]))

    tiny = {}
    tiny_path = root / "research/tiny-functions.json"
    if tiny_path.is_file():
        try:
            tj = json.loads(tiny_path.read_text(encoding="utf-8"))
            tiny = {k: v for k, v in tj.get("counts", {}).items() if k != "unclassified"}
        except (ValueError, OSError, TypeError):
            tiny = {}

    return {
        "schema": 1,
        "meaning": "Work-selection aid only. Counts are not product completion percentages.",
        "scope": {"subsystem": subsystem or "all", "functions": len(rows)},
        "technical_noise": dict(noise),
        "tiny_mechanical_shapes": tiny,
        "near_term": {
            "ported_not_wired": integration,
            "integration_groups": integration_groups,
            "wired_not_compared": comparison,
            "analyzed_not_ported": analyzed_only,
        },
        "families": fam_rows,
    }


def render(data: dict, top: int) -> str:
    lines = [
        "# Work frontier",
        "",
        "> This is a prioritisation aid, not a readiness percentage. It never promotes function-transfer stages.",
        "",
        f"Scope: **{data['scope']['functions']}** original function addresses; subsystem `{data['scope']['subsystem']}`.",
        "",
        "## Cheap wins: implementation exists but integration is incomplete",
        "",
    ]
    rows = data["near_term"]["ported_not_wired"][:top]
    if not rows:
        lines.append("None in this scope.")
    else:
        lines += ["| Address | Function | Subsystem | Compared? |", "|---|---|---|---|"]
        for r in rows:
            lines.append(f"| `{r['address']}` | `{r['symbol']}` | {r['subsystem']} | {'yes' if r['stages']['compared'] else 'no'} |")
    groups = data["near_term"].get("integration_groups", [])
    if groups:
        lines += ["", "### Collapse those cheap wins into integration packets", "",
                  "| Shared implementation | Functions |", "|---|---:|"]
        for g in groups:
            lines.append(f"| `{g['implementation_group']}` | {len(g['members'])} |")
    lines += ["", "## Wired but comparison debt remains", ""]
    rows = data["near_term"]["wired_not_compared"][:top]
    if not rows:
        lines.append("None in this scope.")
    else:
        lines += ["| Address | Function | Subsystem |", "|---|---|---|"]
        for r in rows:
            lines.append(f"| `{r['address']}` | `{r['symbol']}` | {r['subsystem']} |")
    lines += ["", "## Reusable method families", "",
              "These are candidates for one representative analysis + a per-member delta table. Similar names are not proof of identical semantics.", "",
              "| Method | Members | Tracked | Ported | Wired | Compared | Technical |", "|---|---:|---:|---:|---:|---:|---:|"]
    for f in data["families"][:top]:
        lines.append(f"| `{f['method']}` | {f['members']} | {f['tracked']} | {f['ported']} | {f['wired']} | {f['compared']} | {f['technical_members']} |")
    lines += ["", "## Raw-list noise that should not be scheduled as one feature each", ""]
    for k, v in sorted(data["technical_noise"].items(), key=lambda kv: (-kv[1], kv[0])):
        lines.append(f"- `{k}`: {v}")
    tiny = data.get("tiny_mechanical_shapes", {})
    if tiny:
        lines += ["", "### Tiny machine-code shapes already mechanically classified", ""]
        for k, v in sorted(tiny.items(), key=lambda kv: (-kv[1], kv[0])):
            lines.append(f"- `{k}`: {v}")
        lines.append("These still need caller/field review, but should normally be processed by pattern rather than scheduled one by one.")
    lines += ["", "Recommended order: **ported→wired**, then **wired→compared**, then a high-reuse family. Do not expand the global registry merely to increase coverage counts.", ""]
    return "\n".join(lines)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--subsystem", default="")
    ap.add_argument("--min-family", type=int, default=4)
    ap.add_argument("--top", type=int, default=30)
    ap.add_argument("--include-vendor", action="store_true",
                    help="include bundled Ogre/CEGUI/ParticleUniverse/etc method families")
    ap.add_argument("--out", type=Path)
    ap.add_argument("--json", type=Path)
    args = ap.parse_args()
    data = build(args.root.resolve(), args.subsystem or None, args.min_family, args.include_vendor)
    text = render(data, args.top)
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text, encoding="utf-8")
        print(f"wrote {args.out}")
    else:
        print(text)
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(f"wrote {args.json}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
