#!/usr/bin/env python3
"""Find the FIRST exact state/render/RNG/pixel difference, never a whole-screen similarity score.
These files are port regression evidence. This utility does not authenticate an
original capture or promote self-generated output to original-game equivalence.
"""
from __future__ import annotations
import argparse
import json
from pathlib import Path
from typing import Any


def first_difference(left: Any, right: Any, path: str = "$") -> dict | None:
    if type(left) is not type(right):
        return {"path": path, "expected": left, "actual": right, "reason": "type differs"}
    if isinstance(left, dict):
        if left.keys() != right.keys():
            return {"path": path, "missing": sorted(left.keys()-right.keys()),
                    "unexpected": sorted(right.keys()-left.keys()), "reason": "field set differs"}
        for key in sorted(left):
            diff = first_difference(left[key], right[key], path + "." + key)
            if diff:
                return diff
    elif isinstance(left, list):
        if len(left) != len(right):
            return {"path": path, "expected_length": len(left), "actual_length": len(right),
                    "reason": "sequence length differs"}
        for index, (a, b) in enumerate(zip(left, right)):
            diff = first_difference(a, b, f"{path}[{index}]")
            if diff:
                return diff
    elif left != right:
        return {"path": path, "expected": left, "actual": right, "reason": "value differs"}
    return None


def compare(left: Path, right: Path) -> dict:
    if not left.is_dir() or not right.is_dir():
        raise ValueError("both inputs must be scenario output directories")
    # Pixel-exact replay is meaningful only in a fixed, stated runtime. A changed
    # native library is allowed: this is precisely how a code regression is found.
    if not (left/"environment.json").is_file() or not (right/"environment.json").is_file():
        raise ValueError("missing scenario provenance: environment.json is required on both sides")
    if (left/"environment.json").exists() and (right/"environment.json").exists():
        a=json.loads((left/"environment.json").read_text()); b=json.loads((right/"environment.json").read_text())
        for key in ("pak_sha256","script_sha256","graphics"):
            if not a.get(key) or not b.get(key):
                raise ValueError("incomplete scenario provenance: " + key)
            diff=first_difference(a.get(key),b.get(key),"environment."+key)
            if diff:
                return {"status":"INCOMPARABLE","first_difference":diff,"evidence":"port-regression-not-original"}
        if a.get("status")!="PASSED" or b.get("status")!="PASSED":
            raise ValueError("cannot compare a failed/incomplete scenario as a successful baseline")
    priorities=(("*.state.json","state"),("*.render.json","render-state"),
                ("*.image.json","image-metadata"),("rng.jsonl","RNG-order"),
                ("*.rgba","pixels"),("*.actor-mask.bin","object-contribution"))
    files=0
    for pattern, boundary in priorities:
        aa={p.name:p for p in left.glob(pattern)};bb={p.name:p for p in right.glob(pattern)}
        if aa.keys()!=bb.keys():
            return {"status":"FAILED","evidence":"port-regression-not-original","boundary":boundary,
                    "missing":sorted(aa.keys()-bb.keys()),"unexpected":sorted(bb.keys()-aa.keys())}
        for name in sorted(aa):
            files+=1
            raw_a=aa[name].read_bytes();raw_b=bb[name].read_bytes()
            if name.endswith(".json"):
                diff=first_difference(json.loads(raw_a),json.loads(raw_b))
            elif name.endswith(".jsonl"):
                diff=first_difference([json.loads(x) for x in raw_a.splitlines() if x],
                                      [json.loads(x) for x in raw_b.splitlines() if x])
            else:
                diff=None
                if raw_a!=raw_b:
                    index=next((i for i,(a,b) in enumerate(zip(raw_a,raw_b)) if a!=b),min(len(raw_a),len(raw_b)))
                    diff={"byte_offset":index,"expected_size":len(raw_a),"actual_size":len(raw_b),
                          "expected":raw_a[index] if index<len(raw_a) else None,
                          "actual":raw_b[index] if index<len(raw_b) else None}
                    meta=left/(name.removesuffix(".rgba")+".image.json")
                    if name.endswith(".rgba") and meta.exists():
                        w,h=json.loads(meta.read_text())["viewport"]
                        diff.update(x=index//4%w,y_from_bottom=index//4//w,
                                    y_from_top=h-1-index//4//w,channel="RGBA"[index%4])
            if diff:
                return {"status":"FAILED","evidence":"port-regression-not-original",
                        "boundary":boundary,"file":name,"first_difference":diff,"files_compared":files}
    if not files:
        raise ValueError("empty comparison: no state/render/RNG/pixel files")
    return {"status":"PASSED","evidence":"port-regression-not-original","files_compared":files,
            "comparison":"exact; no numeric or image tolerance"}


def main() -> int:
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument("left",type=Path);p.add_argument("right",type=Path)
    p.add_argument("--report",type=Path)
    a=p.parse_args()
    try: result=compare(a.left,a.right)
    except (OSError,ValueError,TypeError) as exc: result={"status":"FAILED","error":str(exc)}
    text=json.dumps(result,indent=2,ensure_ascii=False)+"\n"
    print(text,end="")
    if a.report:
        if a.report.exists():p.error("report exists; do not overwrite previous evidence")
        if any(a.report.resolve().is_relative_to(d.resolve()) for d in (a.left,a.right)):
            p.error("comparison report must be outside both input bundles")
        a.report.write_text(text)
    return 0 if result["status"]=="PASSED" else 1
if __name__=="__main__":raise SystemExit(main())
