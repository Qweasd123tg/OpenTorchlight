#!/usr/bin/env python3
"""Core gate: the function registry must reflect the port.

Runs tools/audit_registry_sync.py. Any @0xADDR cited in src/include/tests
without a reviewed coverage-boundaries entry fails, as does a stale
coverage.tsv or an invalid function-transfer.json.
"""
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
child = subprocess.run([sys.executable, str(ROOT / "tools/audit_registry_sync.py"),
                        "--root", str(ROOT)], capture_output=True, text=True)
print(child.stdout, end="")
print(child.stderr, end="", file=sys.stderr)
if child.returncode:
    print("registry_sync: FAILED (registry drift; see above)")
    raise SystemExit(1)
print("registry_sync: registry reflects the port")
