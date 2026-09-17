#!/usr/bin/env python3
"""Frozen unchanged-fresh v2 output migrates with HP effects applied exactly once."""
from pathlib import Path
import argparse
import hashlib
import json
import subprocess
import tempfile
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--probe',type=Path,required=True)
p.add_argument('--fixture',type=Path,required=True)
a=p.parse_args()
source=Path(__file__).resolve().parent/'fixtures'
manifest=json.loads((source/'vitals-v2-provenance.json').read_text())
with tempfile.TemporaryDirectory(prefix='ot-v2-vitals-') as directory:
    for name, info in manifest['fixtures'].items():
        raw=bytes.fromhex((source/name).read_text())
        if hashlib.sha256(raw).hexdigest()!=info['binary_sha256'] or len(raw)!=info['bytes']:
            raise ValueError('frozen v2 fixture changed: '+name)
        file=Path(directory)/(name+'.otc');file.write_bytes(raw)
        subprocess.run([str(a.probe.resolve()),'--legacy',str(a.fixture.resolve()),str(file)],
                       check=True,timeout=40)
print('PASS: two level fixtures from the unchanged-fresh v2 writer -> current format, no refill and no double bonus')
