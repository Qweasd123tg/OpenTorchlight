#!/usr/bin/env python3
"""Genuine frozen checkpoint -> current codec -> independent current reader."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import tempfile


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe',type=Path,required=True)
    parser.add_argument('--pak',type=Path,required=True)
    parser.add_argument('--legacy',type=Path,required=True)
    parser.add_argument('--output-dir',type=Path,required=True)
    args=parser.parse_args()
    args.output_dir.mkdir(parents=True,exist_ok=True)
    work=Path(tempfile.mkdtemp(prefix='typed-migration-',dir=args.output_dir))
    original_hash=hashlib.sha256(args.legacy.read_bytes()).hexdigest()
    manifest=json.loads(args.legacy.with_suffix('.json').read_text())
    if original_hash!=manifest['checkpoint_sha256']:
        raise AssertionError('Frozen fixture hash differs from unchanged-writer provenance')
    reports=[]
    current=work/'current.otc';again=work/'current-again.otc'
    for source,destination in ((args.legacy,current),(current,again)):
        version=int.from_bytes(source.read_bytes()[8:12],'little')
        run=subprocess.run([str(args.probe),str(args.pak),str(source),str(destination),str(version)],capture_output=True,text=True,timeout=120)
        reports.append({'input_version':version,'returncode':run.returncode,'stdout':run.stdout,'stderr':run.stderr})
        if run.returncode:
            (work/'result.json').write_text(json.dumps(reports,indent=2))
            raise AssertionError(run.stdout+run.stderr)
    if current.read_bytes()!=again.read_bytes():
        raise AssertionError('Independent current load produced a second allocation/migration')
    if hashlib.sha256(args.legacy.read_bytes()).hexdigest()!=original_hash:
        raise AssertionError('Legacy fixture modified')
    result={'passed':True,'processes':2,'source_sha256':original_hash,'runs':reports,
            'current_version':int.from_bytes(current.read_bytes()[8:12],'little'),
            'current_sha256':hashlib.sha256(current.read_bytes()).hexdigest(),
            'scope':'Original-resource-backed port checkpoint migration, not original SVB or campaign.'}
    (work/'result.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result,indent=2))
    return 0


if __name__=='__main__':
    raise SystemExit(main())
