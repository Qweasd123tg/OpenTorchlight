#!/usr/bin/env python3
"""Core gate: the function registry must reflect the port.

Runs tools/audit_registry_sync.py. Unbounded @0xADDR references produce a
warning-only burn-down list. Stale coverage, invalid stages, and malformed or
stale explicit whole-function acceptance fail. No semantic proof is inferred.
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
