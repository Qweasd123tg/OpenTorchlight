"""Shared code-first scope and whole-function acceptance contract.

Legacy stages describe bounded work. They NEVER imply whole-function closure.
This validates a reviewer's explicit claim and its input freshness; it cannot
prove semantic equivalence, completeness of a review, or fidelity of a library.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re

STAGES = ("analyzed", "ported", "wired", "compared")
REVIEW_AREAS = ("branches", "state", "calls_and_effects", "library_contracts",
                "family_deltas", "integration", "original_comparison")
SHA256 = re.compile(r"[0-9a-f]{64}\Z")


def load_scope(root: Path, name: str = "ui") -> dict:
    if name == "all":
        return {"name": "all", "class_prefixes": [], "entry_addresses": []}
    if name != "ui":
        raise ValueError(f"Unknown code-first scope: {name}")
    path = root / "research/ui-contour.json"
    data = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(data.get("class_prefixes"), list) or not data["class_prefixes"]:
        raise ValueError("UI scope needs explicit class_prefixes")
    if not all(isinstance(p, str) and p for p in data["class_prefixes"]):
        raise ValueError("UI scope class_prefixes must be nonempty strings")
    return {**data, "name": name, "path": "research/ui-contour.json",
            "sha256": hashlib.sha256(path.read_bytes()).hexdigest()}


def in_scope(symbol: str, address: str, scope: dict) -> bool:
    if scope["name"] == "all":
        return True
    if int(address, 16) in {int(a, 16) for a in scope.get("entry_addresses", [])}:
        return True
    base = symbol.split("thunk to ", 1)[-1]
    owner = base.split("::", 1)[0]
    return any(owner.startswith(prefix) for prefix in scope["class_prefixes"])


def completion(entry: dict | None, root: Path, hashes: dict | None = None) -> dict:
    """Report unassessed/partial/reviewed_full/stale/invalid without mutation."""
    if entry is not None and not isinstance(entry, dict):
        return {"status": "invalid", "open_items": [], "errors": ["transfer entry must be an object"]}
    record = (entry or {}).get("completion")
    if record is None:
        return {"status": "unassessed", "open_items": [], "errors": [],
                "meaning": "No whole-function acceptance; legacy stages are bounded claims."}
    errors: list[str] = []
    if (not isinstance(record, dict) or not isinstance(record.get("status"), str) or
            record["status"] not in {"partial", "full"}):
        return {"status": "invalid", "open_items": [],
                "errors": ["completion.status must be partial or full"]}
    pending = record.get("open_items")
    if not isinstance(pending, list) or not all(isinstance(x, str) and x.strip() for x in pending):
        errors.append("completion.open_items must be an explicit list of nonempty strings")
        pending = []
    if record["status"] == "partial":
        if not pending:
            errors.append("partial completion needs at least one explicit open item")
        return {"status": "invalid" if errors else "partial", "open_items": pending, "errors": errors}

    if pending:
        errors.append("full completion cannot have open items")
    stages = (entry or {}).get("stages", {})
    if not isinstance(stages, dict) or not all(stages.get(stage) is True for stage in STAGES):
        errors.append("full completion requires all four stages, not just a helper implementation")
    review = record.get("review", {})
    if not isinstance(review, dict):
        review = {}
    for area in REVIEW_AREAS:
        if not isinstance(review.get(area), str) or not review[area].strip():
            errors.append(f"full completion needs review.{area} evidence (or a justified non-applicability)")

    inputs = record.get("inputs")
    if not isinstance(inputs, dict) or not inputs:
        errors.append("full completion needs inputs: repository-relative file -> SHA-256")
        inputs = {}
    if not any(isinstance(p, str) and p.startswith(("src/", "include/")) for p in inputs):
        errors.append("full completion must pin implementation inputs under src/ or include/")
    if not any(isinstance(p, str) and p.startswith("tests/") for p in inputs):
        errors.append("full completion must pin regression/comparison test inputs")
    stale: list[str] = []
    hashes = {} if hashes is None else hashes
    for relative, expected in inputs.items():
        if (not isinstance(relative, str) or Path(relative).is_absolute() or
                ".." in Path(relative).parts or
                not isinstance(expected, str) or not SHA256.fullmatch(expected)):
            errors.append(f"invalid completion input: {relative!r}")
            continue
        path = root / relative
        if not path.resolve().is_relative_to(root.resolve()) or path.is_symlink():
            errors.append(f"completion input must be a local regular file: {relative}")
            continue
        if relative not in hashes:
            try:
                hashes[relative] = hashlib.sha256(path.read_bytes()).hexdigest()
            except OSError:
                hashes[relative] = None
        if hashes[relative] != expected:
            stale.append(f"completion input changed or missing: {relative}")
    return {"status": "invalid" if errors else "stale" if stale else "reviewed_full",
            "open_items": pending, "errors": errors + stale,
            "meaning": "Validated explicit reviewer claim; not an automated semantic proof."}
