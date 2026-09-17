#!/usr/bin/env python3
"""Read a checkpoint produced by unchanged large-12, then continue with the current binary."""
import hashlib,json,shutil,subprocess,sys,tempfile
from pathlib import Path
root=Path(__file__).resolve().parent/'fixtures/legacy-v4'
p=root/'potions.otc'
metadata=json.loads((root/'provenance.json').read_text())
assert hashlib.sha256(p.read_bytes()).hexdigest()==metadata['save_sha256']
assert int.from_bytes(p.read_bytes()[8:12],'little')==4
with tempfile.TemporaryDirectory(prefix='ot-v4-') as name:
    target=Path(name)/'potions.otc';shutil.copyfile(p,target)
    subprocess.run([sys.argv[1],'--read',sys.argv[2],name],check=True)
    # The old read-only migration path must not rewrite the input automatically.
    assert target.read_bytes()==p.read_bytes()
print('PASS: unchanged v4 writer -> current reader; original file is unchanged')
