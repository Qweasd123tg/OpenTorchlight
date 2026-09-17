#!/usr/bin/env python3
"""Unchanged large-11 v3 file -> v4 -> independent-process continuation."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import tempfile
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--probe',type=Path,required=True);p.add_argument('--fixture',type=Path,required=True)
a=p.parse_args();root=Path(__file__).resolve().parent/'fixtures'
info=json.loads((root/'legacy-v3-provenance.json').read_text())
raw=bytes.fromhex((root/'legacy-v3-gameplay.hex').read_text())
if len(raw)!=info['bytes'] or hashlib.sha256(raw).hexdigest()!=info['binary_sha256']:raise ValueError('frozen v3 bytes changed')
if hashlib.sha256(a.fixture.read_bytes()).hexdigest()!=info['fixture_sha256']:raise ValueError('v3 source fixture data changed; review migration, do not silently regenerate')
if hashlib.sha256((root/'legacy-v3-writer.cpp.txt').read_bytes()).hexdigest()!=info['writer_source_sha256']:raise ValueError('writer provenance changed')
with tempfile.TemporaryDirectory(prefix='ot-v3-migration-') as folder:
    save=Path(folder)/'v3.otc';save.write_bytes(raw);upgraded=Path(folder)/'v4.otc'
    for mode,file in (('--legacy',save),('--continued',upgraded)):
        subprocess.run([str(a.probe.resolve()),mode,str(a.fixture.resolve()),str(file),str(upgraded)],check=True,timeout=45)
print('PASS: frozen unchanged large-11 -> v4, two independent reader processes')
