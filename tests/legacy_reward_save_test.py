#!/usr/bin/env python3
"""Frozen original large-7 writer output -> current checkpoint version. NOT original Torchlight saves."""
import argparse
import hashlib
import subprocess
import tempfile
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--probe',required=True,type=Path)
p.add_argument('--upgrade',required=True,type=Path)
p.add_argument('--fixture',required=True,type=Path)
a=p.parse_args()
source=Path(__file__).resolve().parent/'fixtures/checkpoint-v1.hex'
raw=bytes.fromhex(source.read_text())
EXPECTED='d9b7a52e09b53be9c9233c1f6f46923d309bce2258eb0d2344fa34ae915abade'
if hashlib.sha256(raw).hexdigest()!=EXPECTED:raise ValueError('frozen v1 fixture hash mismatch')
with tempfile.TemporaryDirectory(prefix='ot-legacy-rewards-') as directory:
    save=Path(directory)/'hero-test.otc';save.write_bytes(raw)
    subprocess.run([str(a.probe.resolve()),str(a.fixture.resolve()),directory,'read'],check=True,timeout=30)
    subprocess.run([str(a.upgrade.resolve()),str(save)],check=True,timeout=30)
    subprocess.run([str(a.probe.resolve()),str(a.fixture.resolve()),directory,'read'],check=True,timeout=30)
print('PASS: v1 and upgraded checkpoint load the same legacy inventory, floor, vitals and wallet in fresh processes')
