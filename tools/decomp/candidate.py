#!/usr/bin/env python3
"""Compile and accept a deterministic full-TU candidate without model calls.

    python3 tools/decomp/candidate.py T.cpp --input candidate/T.cpp
    python3 tools/decomp/candidate.py T.cpp --provider trial

Diagnostics and rejected bodies stay in build-decomp/attempts. --publish
requires final MATCH for all definitions, followed by the whole headless suite.
Trial builds with permissive flags are never acceptance evidence.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re

import elfdb
import evidence
import objdiff
import promote
import publication


def failure_class(message):
    """Stable cause groups for repairing shared rules instead of paying per body."""
    lines = [line for line in message.splitlines() if "error:" in line]
    normalized = re.sub(r"(?:/[^\s:]+)+:\d+(?::\d+)?", "<source>", "\n".join(lines) or message)
    normalized = re.sub(r"\b(?:param_|local_|uVar|iVar|pVar)\w*\b", "<temporary>", normalized)
    return hashlib.sha256(normalized.encode()).hexdigest()[:16], normalized


def evaluate(tu, source, publish=False, root=elfdb.ROOT, stage=None, incremental=False):
    db = elfdb.load_db()
    if tu not in {t["name"] for t in db["tus"] if t["kind"] == "game"}:
        raise ValueError(f"unknown game TU: {tu}")
    candidate = Path(source).read_bytes()
    inputs = evidence.input_digest(db)
    proposal = json.dumps(publication.tree_state(stage.path), sort_keys=True).encode() if stage else b""
    key = hashlib.sha256(tu.encode() + b"\0" + candidate + inputs.encode() + proposal).hexdigest()
    failures = root / "build-decomp/candidate-failures"
    failures.mkdir(parents=True, exist_ok=True)
    cached = failures / f"{key}.json"
    if cached.exists():
        result = json.loads(cached.read_text())
        result["cached_failure"] = True
        return result
    stage = stage or publication.Stage(root)
    target = stage.path / "decomp/src" / tu
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(candidate)
    result = {"schema": 1, "tu": tu, "provider": "deterministic", "attempt": str(stage.path),
              "input_digest": inputs, "candidate_sha256": hashlib.sha256(candidate).hexdigest(),
              "published": False}
    try:
        with stage.activate():
            os.environ["OTL_EXTRA_INCLUDE"] = str(stage.path / "build-decomp/include-gen")
            original = objdiff.Original(db=db)
            diagnostic = objdiff.compare_source(target, original, quiet=True)
            promote.promote(target, regenerate=False)
            os.environ.pop("OTL_EXTRA_INCLUDE", None)
            final = objdiff.compare_source(target, original, quiet=True)
            result.update(diagnostic_object=diagnostic["object_digest"], final_object=final["object_digest"],
                          final_object_changed=diagnostic["object_digest"] != final["object_digest"],
                          functions=final["functions"], unknown=final.get("unknown", []))
            definitions = [r for r in final["functions"] if r["status"] != "MISSING" and not r.get("weak")]
            prior = {}
            if incremental and (root / "decomp/src" / tu).exists():
                # Compare the actual original context, with its actual hand headers.
                saved_root, saved_extra = os.environ.pop("OTL_INCLUDE_ROOT", None), os.environ.pop("OTL_EXTRA_INCLUDE", None)
                try:
                    prior = {r["address"]: r for r in objdiff.compare_source(root / "decomp/src" / tu, original, quiet=True)["functions"]
                             if r.get("address") and r["status"] != "MISSING" and not r.get("weak")}
                finally:
                    if saved_root is not None:
                        os.environ["OTL_INCLUDE_ROOT"] = saved_root
                    if saved_extra is not None:
                        os.environ["OTL_EXTRA_INCLUDE"] = saved_extra
            added = [r for r in definitions if r.get("address") not in prior]
            result["new_matched"] = [r["address"] for r in added if r.get("address") and r["status"] == "MATCH"]
            preserved = preserve_existing(root / "decomp/src" / tu, target, prior, definitions, db) if prior else True
            if (not definitions or not added or any(r["status"] != "MATCH" for r in added)
                    or not preserved or final.get("unknown")):
                result["status"] = "DIFF"
                result["reason"] = "final TU requires behavioral evidence; instruction percentage cannot publish it"
            else:
                result["status"] = "MATCH"
        if publish and result["status"] == "MATCH":
            stage.validate()
            if evidence.input_digest(db) != inputs:
                raise RuntimeError("inputs changed during candidate validation")
            result["files"] = stage.publish()
            result["published"] = True
    except (SystemExit, RuntimeError) as error:
        result["status"] = "ERROR"
        result["reason"] = str(error)
        result["failure_class"], result["compiler_diagnostics"] = failure_class(str(error))
    (stage.path / "result.json").write_text(json.dumps(result, indent=1, ensure_ascii=False) + "\n")
    if result["status"] != "MATCH":
        temporary = cached.with_suffix(f".{os.getpid()}.tmp")
        temporary.write_text(json.dumps(result, indent=1, ensure_ascii=False))
        os.replace(temporary, cached)
    return result


def preserve_existing(before, after, prior, definitions, db):
    """Do not replace existing source bodies or change their compiler context silently."""
    import mutate
    old, new = before.read_text(), after.read_text()
    old_mask, new_mask = mutate.mask(old), mutate.mask(new)
    final = {r["address"]: r for r in definitions if r.get("address")}
    for address, row in prior.items():
        other = final.get(address)
        if not other or (row["status"] == "MATCH" and other["status"] != "MATCH"):
            return False
        if row["status"] != "MATCH":
            if row.get("code") != other.get("code") or row.get("metadata_reasons") != other.get("metadata_reasons"):
                return False
            function = db["functions"].get(address)
            if function and function.get("kind") == "compiler":
                continue  # no source definition; identical normalized code/data and metadata above
            a = mutate.definition(old, old_mask, function) if function else None
            b = mutate.definition(new, new_mask, function) if function else None
            if not a or not b or old[a[0]:a[1] + 1] != new[b[0]:b[1] + 1]:
                return False
    return True


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("tu")
    parser.add_argument("--input", type=Path)
    parser.add_argument("--provider", choices=("trial",), help="use the converted TU from draft_trial.py")
    parser.add_argument("--publish", action="store_true")
    args = parser.parse_args()
    if bool(args.input) == bool(args.provider):
        parser.error("choose exactly one deterministic provider: --input or --provider trial")
    import parallel
    if args.publish and (owner := parallel.owned_by_others(args.tu)):
        parser.error(f"{args.tu} belongs to {owner}; set OTL_OWNER")
    source = args.input or elfdb.ROOT / "build-decomp/trial" / args.tu
    if args.provider:
        import ghidra_draft
        state, reasons = ghidra_draft.draft_state(args.tu, elfdb.load_db())
        if state != "fresh":
            parser.error(f"draft provider unavailable ({state}): {'; '.join(reasons)}")
    result = evaluate(args.tu, source, args.publish)
    print(json.dumps(result, indent=1, ensure_ascii=False))
    return 0 if result["status"] == "MATCH" else 1


if __name__ == "__main__":
    raise SystemExit(main())
