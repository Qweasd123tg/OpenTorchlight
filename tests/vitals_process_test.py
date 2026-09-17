#!/usr/bin/env python3
"""Exercise v3 HP effects/recovery across two fresh OS processes."""
from pathlib import Path
import argparse
import subprocess
import tempfile
p = argparse.ArgumentParser(description=__doc__)
p.add_argument('--probe', required=True, type=Path)
p.add_argument('--fixture', required=True, type=Path)
a=p.parse_args()
with tempfile.TemporaryDirectory(prefix='ot-vitals-') as directory:
    for mode in ('write', 'read'):
        subprocess.run([str(a.probe.resolve()), '--process', str(a.fixture.resolve()), directory, mode],
                       check=True, timeout=40)
print('PASS: v3 vitals survive fresh-process load without refilling or double-buffing')
