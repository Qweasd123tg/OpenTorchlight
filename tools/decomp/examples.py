#!/usr/bin/env python3
"""Worked examples for the model: Ghidra drafts next to the accepted source.

    python3 tools/decomp/examples.py            # rebuild build-decomp/examples.json
    python3 tools/decomp/examples.py 0xe16df0   # show the examples chosen for a function

Every accepted function (MATCH or self-test, from build-decomp/progress.json
written by check.py) of up to MAX_SIZE bytes becomes an example: its converted
Ghidra draft and its definition in decomp/src. For a new function, choose()
returns the examples whose drafts share the most informative identifiers
(calls, library internals, constants) with its draft, within a size budget.
"""
from __future__ import annotations

import argparse
import json
import math
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import ghidra_cpp  # noqa: E402
import mutate  # noqa: E402

ROOT = elfdb.ROOT
OUT = ROOT / "build-decomp" / "examples.json"
DRAFTS = ROOT / "build-decomp" / "drafts"
MAX_SIZE = 1500
NOISE = re.compile(rf"{ghidra_cpp.TEMP}|param_\d+|LAB_\w+|switchD_\w+|caseD_\w+|"
                   r"if|else|while|do|for|return|break|goto|void|int|long|char|short|float|double|bool|"
                   r"unsigned|signed|const|this|NULL|true|false|std|wchar_t|sizeof")


def features(draft):
    return sorted({t for t in re.findall(r"[A-Za-z_]\w*|0x[0-9a-f]+", draft) if not NOISE.fullmatch(t)})


def accepted_addresses(db):
    progress = json.loads((ROOT / "build-decomp" / "progress.json").read_text())
    if "accepted" in progress:
        return set(progress["accepted"])
    import check
    rows = [r for u in progress["units"] for r in u["functions"] if r.get("address")]
    return ({r["address"] for r in rows if r["status"] == "MATCH"}
            | ({r["address"] for r in rows if r["status"] == "DIFF"} & check.shadow_covered(db)))


def converted_draft(db, f, helpers):
    tu = next(t["name"] for t in db["tus"] if t["id"] == f["tu"])
    raw = DRAFTS / tu / "raw" / f"{f['address']}.c"
    if not raw.exists():
        return None
    try:
        return ghidra_cpp.convert(raw.read_text(errors="replace"), *helpers[:1], f, *helpers[1:])
    except Exception:  # noqa: BLE001
        return None


def source_of(db, f):
    tu = next(t["name"] for t in db["tus"] if t["id"] == f["tu"])
    path = next(iter(mutate.SRC.rglob(tu)), None)
    if not path:
        return None
    text = path.read_text()
    span = mutate.definition(text, mutate.mask(text), f)
    if not span:
        return None
    qual = f["demangled"].split("(")[0]
    start = text.rfind(qual, 0, span[0])
    if start < 0:
        return None
    return text[text.rfind("\n", 0, start) + 1:span[1] + 1]


def build():
    db = elfdb.load_db()
    helpers = (ghidra_cpp.known_methods(db), ghidra_cpp.signatures_of(db), ghidra_cpp.parse_enums())
    out = []
    for address in sorted(accepted_addresses(db)):
        f = db["functions"].get(address)
        if not f or f["size"] > MAX_SIZE:
            continue
        draft, source = converted_draft(db, f, helpers), source_of(db, f)
        if draft and source:
            out.append({"address": address, "name": f["demangled"], "size": f["size"],
                        "draft": draft, "source": source, "features": features(draft)})
    OUT.write_text(json.dumps(out, indent=1, ensure_ascii=False))
    return out


def load():
    return json.loads(OUT.read_text()) if OUT.exists() else []


def choose(examples, draft, exclude=(), budget=6000, limit=3):
    """The most similar examples (idf-weighted shared identifiers) that fit in budget chars."""
    if not examples:
        return []
    df = {}
    for e in examples:
        for t in e["features"]:
            df[t] = df.get(t, 0) + 1
    idf = {t: math.log(len(examples) / n) for t, n in df.items()}
    want = set(features(draft))
    scored = []
    for e in examples:
        if e["address"] in exclude or e["name"] in exclude:
            continue
        have = set(e["features"])
        shared = sum(idf.get(t, 0) for t in want & have)
        norm = math.sqrt(sum(idf.get(t, 0) for t in have) or 1)
        scored.append((shared / norm, e))
    scored.sort(key=lambda x: -x[0])
    out, used = [], 0
    for score, e in scored:
        cost = len(e["draft"]) + len(e["source"])
        if score <= 0 or len(out) >= limit:
            break
        if used + cost <= budget:
            out.append(e)
            used += cost
    return out


def render(chosen):
    return "\n\n".join(f"Draft:\n```cpp\n{e['draft'].strip()}\n```\nAccepted source:\n```cpp\n{e['source'].strip()}\n```"
                       for e in chosen)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("address", nargs="?")
    args = parser.parse_args()
    if not args.address:
        out = build()
        print(f"{len(out)} examples in {OUT.relative_to(ROOT)}")
        return
    db = elfdb.load_db()
    f = db["functions"][args.address]
    helpers = (ghidra_cpp.known_methods(db), ghidra_cpp.signatures_of(db), ghidra_cpp.parse_enums())
    draft = converted_draft(db, f, helpers) or ""
    print(render(choose(load(), draft, exclude={f["address"]})))


if __name__ == "__main__":
    main()
