#!/usr/bin/env python3
"""Write then reload rewards in different native processes, using authored data."""
import argparse
import subprocess
import tempfile
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--probe',required=True,type=Path)
p.add_argument('--fixture',required=True,type=Path)
a=p.parse_args()
with tempfile.TemporaryDirectory(prefix='ot-rewards-') as directory:
    for mode in ['write','read','read']:
        subprocess.run([str(a.probe.resolve()),str(a.fixture.resolve()),directory,mode],check=True,timeout=30)
print('PASS: separate-process reward/vitals/point/rolled-gold restoration; repeat reads do not duplicate rewards')
