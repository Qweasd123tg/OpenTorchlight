#!/usr/bin/env python3
"""Crash before rename and competing writers against the real POSIX SaveStore."""
import argparse
import subprocess
import tempfile
import time
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--probe',required=True);p.add_argument('--fixture',required=True)
a=p.parse_args()
with tempfile.TemporaryDirectory(prefix='opentorchlight-atomic-') as root:
    saves=Path(root)/'saves'
    def command(mode):return [a.probe,a.fixture,str(saves),mode]
    subprocess.run(command('write'),check=True,timeout=30)
    before=(saves/'hero-test.otc').read_bytes()
    crashed=subprocess.run(command('crash-temp'),check=False,timeout=30)
    assert crashed.returncode==42,crashed.returncode
    assert (saves/'hero-test.otc').read_bytes()==before,'pre-rename crash replaced live save'
    subprocess.run(command('read'),check=True,timeout=30)
    workers=[subprocess.Popen(command('race-a')),subprocess.Popen(command('race-b'))]
    try:
        deadline=time.monotonic()+20
        while not all((saves/(m+'.ready')).exists() for m in ('race-a','race-b')):
            if time.monotonic()>deadline or any(w.poll() is not None for w in workers):raise RuntimeError('writers failed to reach barrier')
            time.sleep(.01)
        (saves/'go').write_text('start',encoding='ascii')
        codes=sorted(w.wait(timeout=30) for w in workers)
        assert codes==[0,3],('expected exactly one commit and one stale-revision rejection',codes)
    finally:
        for worker in workers:
            if worker.poll() is None:worker.kill();worker.wait()
    subprocess.run(command('read-revision-2'),check=True,timeout=30)
print('Atomic checkpoint passed: pre-rename process crash preserves bytes; two competing writers yield one commit, one revision conflict.')
