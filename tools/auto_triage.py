#!/usr/bin/env python3
"""Partition the original 17k-function list into practical reverse-engineering queues.

This tool does NOT claim game completion and never edits function-transfer.json.
Its purpose is to stop scheduling compiler glue, exact mechanical wrappers, and
repeated families as if they were independent gameplay features.

Primary work classes are mutually exclusive so counts can be added safely:
  compiler_glue          compiler-generated ctor/dtor registration wrappers
  external_source_first  third-party code where source matching is cheaper than RE
  modified_library       bundled/modified library boundary (CEGUI needs delta review)
  editor_tooling         editor/FLTK surface, defer for playable-game milestone
  descriptor_binding     generated/repetitive descriptor registration glue
  exact_leaf             tiny function with directly decoded leaf semantics
  exact_routing          thunk/forwarder; review moves to the target function
  lifecycle_wrapper      trivial destructor wrapper; target/base owns semantics
  binding_mechanical     repetitive property binding accessors/setters
  technical_symbol       name-identified thunk/destructor/factory/singleton not tiny
  family_batch           game method belongs to a reusable method-name family
  manual                 no safe reduction found yet

The categories are scheduling aids, not proof that the original behaviour is
ported, wired, or compared.
"""
from __future__ import annotations
import argparse, csv, json, re
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
THUNK_PREFIXES = ("non-virtual thunk to ", "virtual thunk to ", "covariant return thunk to ")


def strip_thunk(symbol: str) -> str:
    for p in THUNK_PREFIXES:
        if symbol.startswith(p):
            return symbol[len(p):]
    return symbol


def load_rows(root: Path) -> list[dict]:
    with (root / "research/coverage.tsv").open(newline="", encoding="utf-8") as fh:
        return [r for r in csv.DictReader(fh, delimiter="\t") if not r["address"].startswith("port:")]


def method_name(symbol: str) -> str | None:
    base = strip_thunk(symbol)
    m = re.search(r"(?:^|\s)([A-Za-z_]\w*)::([^:( ]+)\(", base)
    return m.group(2) if m else None


def class_name(symbol: str) -> str | None:
    base = strip_thunk(symbol)
    m = re.search(r"(?:^|\s)([A-Za-z_]\w*)::[^:( ]+\(", base)
    return m.group(1) if m else None


def game_style(symbol: str) -> bool:
    return re.match(r"^C[A-Za-z0-9_]+::", strip_thunk(symbol)) is not None


def compiler_glue(symbol: str) -> bool:
    return bool(
        re.match(r"^__tcf_\d+", symbol)
        or symbol.startswith("__static_initialization_and_destruction_0")
        or symbol.startswith("global constructors keyed to ")
        or symbol.startswith("global destructors keyed to ")
    )


def source_boundary(symbol: str) -> str | None:
    base = strip_thunk(symbol)
    if base.startswith("ParticleUniverse::"):
        return "ParticleUniverse"
    if base.startswith("Ogre::"):
        return "Ogre"
    if base.startswith("std::") or base.startswith("__gnu_cxx::"):
        return "libstdc++/STL"
    return None


def modified_library(symbol: str) -> str | None:
    base = strip_thunk(symbol)
    if base.startswith("CEGUI::"):
        return "CEGUI"
    return None


def editor_tooling(symbol: str) -> bool:
    base = strip_thunk(symbol)
    return bool(
        re.match(r"^(?:Fl(?:_|::)|fl_|Fl_)", base)
        or re.match(r"^CEditor[A-Za-z0-9_]*::", base)
        or base.startswith("Editor")
        or "CEditorScene*" in base
        or "CEditorBaseObject*" in base
        or re.match(r"^(?:draw_|fl_)", base)
    )


def descriptor_binding_glue(symbol: str) -> bool:
    """Registration helpers generated in large descriptor families.

    These functions can still matter to the original editor/descriptor system,
    but they should be inspected as one registration template rather than as
    dozens of gameplay algorithms.
    """
    base = strip_thunk(symbol)
    return bool(re.match(r"^(?:Set|Get)_C[A-Za-z0-9_]+DescriptorParam\d+\(", base))


def technical_symbol(symbol: str) -> str | None:
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


def load_tiny(root: Path) -> dict[str, dict]:
    path = root / "research/tiny-functions.json"
    if not path.is_file():
        return {}
    data = json.loads(path.read_text(encoding="utf-8"))
    return {r["address"].lower(): r for r in data.get("functions", [])}


def build_family_map(rows: list[dict], min_family: int) -> dict[str, dict]:
    groups: dict[str, list[dict]] = defaultdict(list)
    for r in rows:
        if not game_style(r["symbol"]):
            continue
        meth = method_name(r["symbol"])
        if meth:
            groups[meth].append(r)
    out = {}
    for meth, members in groups.items():
        if len(members) < min_family:
            continue
        for r in members:
            out[r["address"].lower()] = {"method": meth, "members": len(members)}
    return out


def classify(row: dict, tiny: dict[str, dict], families: dict[str, dict]) -> tuple[str, dict, str]:
    address = row["address"].lower()
    symbol = row["symbol"]
    if compiler_glue(symbol):
        return "compiler_glue", {}, "no_individual_pass"
    source = source_boundary(symbol)
    if source:
        return "external_source_first", {"library": source}, "source_match_first"
    lib = modified_library(symbol)
    if lib:
        return "modified_library", {"library": lib}, "source_plus_binary_delta"
    if editor_tooling(symbol):
        return "editor_tooling", {}, "defer_for_playable_game"
    if descriptor_binding_glue(symbol):
        return "descriptor_binding", {}, "batch_representative"

    t = tiny.get(address)
    if t and t.get("kind") != "unclassified":
        tier = t.get("review_tier", "")
        mapping = {
            "leaf_exact": ("exact_leaf", "no_individual_pass"),
            "routing_exact": ("exact_routing", "no_individual_pass"),
            "lifecycle_wrapper": ("lifecycle_wrapper", "batch_or_target_review"),
            "binding_mechanical": ("binding_mechanical", "batch_representative"),
        }
        if tier in mapping:
            kind, action = mapping[tier]
            return kind, {"tiny_kind": t.get("kind"), "tiny_meta": t.get("meta", {})}, action

    tech = technical_symbol(symbol)
    if tech:
        return "technical_symbol", {"technical_kind": tech}, "batch_or_target_review"
    fam = families.get(address)
    if fam:
        return "family_batch", fam, "batch_representative"
    return "manual", {}, "manual_reverse"


def build(root: Path, min_family: int) -> dict:
    rows = load_rows(root)
    tiny = load_tiny(root)
    families = build_family_map(rows, min_family)
    out = []
    counts = Counter(); actions = Counter(); libraries = Counter()
    for r in rows:
        kind, meta, action = classify(r, tiny, families)
        counts[kind] += 1; actions[action] += 1
        if "library" in meta: libraries[meta["library"]] += 1
        out.append({
            "address": r["address"], "symbol": r["symbol"], "subsystem": r.get("subsystem", ""),
            "current_status": r.get("status", ""), "work_class": kind,
            "recommended_action": action, "meta": meta,
        })
    no_individual = actions["no_individual_pass"] + actions["defer_for_playable_game"]
    payload = {
        "schema": 1,
        "meaning": "Scheduling triage only. No work class promotes port/wired/compared status.",
        "total_functions": len(rows),
        "primary_classes": dict(counts.most_common()),
        "recommended_actions": dict(actions.most_common()),
        "external_source_candidates": dict(libraries.most_common()),
        "headline": {
            "no_individual_deep_reverse_now": no_individual,
            "source_match_before_reverse": actions["source_match_first"] + actions["source_plus_binary_delta"],
            "batch_before_individual": actions["batch_representative"] + actions["batch_or_target_review"],
            "manual_reverse_remaining": actions["manual_reverse"],
        },
        "functions": out,
    }
    return payload


def render(data: dict) -> str:
    h = data["headline"]
    lines = [
        "# Automatic function triage", "",
        "> Scheduling reduction only. These counts are not game-completion percentages and never promote function-transfer stages.", "",
        f"Original function addresses: **{data['total_functions']}**.", "",
        "## Primary mutually-exclusive work classes", "",
        "| Class | Functions |", "|---|---:|",
    ]
    for k,v in data["primary_classes"].items(): lines.append(f"| `{k}` | {v} |")
    lines += ["", "## What this means for the queue", "",
              f"- No individual deep-reverse pass needed at this stage: **{h['no_individual_deep_reverse_now']}**.",
              f"- Match public/bundled source before reversing machine code: **{h['source_match_before_reverse']}**.",
              f"- Review as a family/target instead of one function at a time: **{h['batch_before_individual']}**.",
              f"- Still falls through to individual/manual reverse: **{h['manual_reverse_remaining']}**.", "",
              "The categories above are mutually exclusive, so these headline counts can be added. A forwarding wrapper still depends on its target; a destructor wrapper does not prove the base destructor is trivial.", "",
              "## External-source candidates", ""]
    for k,v in data["external_source_candidates"].items(): lines.append(f"- `{k}`: {v}")
    lines += ["", "## Recommended use", "",
              "1. Do not schedule `compiler_glue`, exact tiny wrappers, or editor-tooling functions as standalone feature work.",
              "2. Source-match third-party libraries before any decompilation effort.",
              "3. For `technical_symbol` and `family_batch`, choose representatives and preserve per-member deltas.",
              "4. Spend neural deep-reverse time on the remaining `manual` queue and on integration gaps discovered by scenarios.", ""]
    return "\n".join(lines)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--min-family", type=int, default=4)
    ap.add_argument("--json", type=Path)
    ap.add_argument("--out", type=Path)
    args = ap.parse_args()
    data = build(args.root.resolve(), args.min_family)
    text = render(data)
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True); args.out.write_text(text, encoding="utf-8"); print("wrote", args.out)
    else:
        print(text)
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True); args.json.write_text(json.dumps(data, ensure_ascii=False, indent=2)+"\n", encoding="utf-8"); print("wrote", args.json)
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
