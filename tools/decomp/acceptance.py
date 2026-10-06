"""Bind executed comparison receipts to the complete final object and inputs."""
import json
from pathlib import Path
import re

import evidence

POLICY_VERSION = 1


def comparison_bindings(db, units, report, root, inputs_digest=None):
    import check
    covered = check.shadow_covered(db, report)
    inputs = inputs_digest or evidence.input_digest(db, root=root)
    objects = {row["address"]: unit.get("object_digest")
               for unit in units for row in unit["functions"]
               if row.get("address") and not row.get("weak") and row["status"] not in ("MISSING", "EXTRA")}
    fixtures = {}
    for line in report:
        match = re.fullmatch(r"\s+coverage (\w+) (0x[0-9a-f]+) completed (\d+) different (\d+) incomplete (\d+)", line)
        if match and match.group(2) in covered:
            fixtures.setdefault(match.group(2), []).append(match.group(1))
    return {address: {"policy": POLICY_VERSION, "method": "executed-call-pair",
                      "original_elf_sha256": db["original_elf_sha256"],
                      "evidence": evidence.tested(objects[address], inputs,
                                                  {"fixtures": sorted(set(fixtures[address])), "runtime_abi": 2})}
            for address in covered if objects.get(address)}


def load_comparisons(root, db):
    """Remember actual behavioral acceptance, including when its inputs became stale.

    A changed environment requires fresh evidence; it must not silently turn a
    previously compared function into an unprotected unknown definition.
    Legacy accepted lists and TL_ORIGINAL declarations never enter this set.
    """
    path = Path(root) / "build-decomp/progress.json"
    try:
        report = json.loads(path.read_text())
    except (OSError, ValueError):
        return {}
    return {address: row for address, row in report.get("comparison_evidence", {}).items()
            if address in db["functions"] and row.get("policy") == POLICY_VERSION
            and row.get("method") == "executed-call-pair"
            and row.get("original_elf_sha256") == db["original_elf_sha256"]
            and row.get("evidence", {}).get("schema") == evidence.SCHEMA
            and row["evidence"].get("object_digest") and row["evidence"].get("inputs_digest")}


def prior_compared(root, db):
    return set(load_comparisons(root, db))
