#!/usr/bin/env python3
"""New->authored Town walk/save -> second process load/travel/restart -> third verify."""
import argparse
import subprocess
import tempfile
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--probe', required=True)
p.add_argument('--fixture', required=True)
a=p.parse_args()
with tempfile.TemporaryDirectory(prefix='opentorchlight-frontend-cycle-') as directory:
    for phase in ('write','read','verify'):
        subprocess.run([a.probe,a.fixture,str(Path(directory)/'saves'),phase],check=True,timeout=45)
print('Three independent processes completed the authored-resource frontend/campaign cycle.')
