#!/usr/bin/env python3
"""Two separate executables; no shared in-memory campaign or original resources."""
import argparse
import subprocess
import tempfile
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--probe',required=True)
p.add_argument('--fixture',required=True)
a=p.parse_args()
with tempfile.TemporaryDirectory(prefix='opentorchlight-save-process-') as d:
    saves=Path(d)/'saves'
    subprocess.run([a.probe,a.fixture,str(saves),'write'],check=True)
    subprocess.run([a.probe,a.fixture,str(saves),'read'],check=True)
print('Separate-process save/load passed for the supplied PAK; not original save-format compatibility.')
