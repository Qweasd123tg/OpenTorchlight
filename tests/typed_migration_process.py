#!/usr/bin/env python3
"""Genuine frozen large-15 v5 -> v6 -> independent second v6 reader."""
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
    work=Path(tempfile.mkdtemp(prefix='typed-v5-',dir=args.output_dir))
    original_hash=hashlib.sha256(args.legacy.read_bytes()).hexdigest()
    manifest=json.loads(args.legacy.with_suffix('.json').read_text())
    if original_hash!=manifest['checkpoint_sha256']:
        raise AssertionError('Frozen v5 fixture hash differs from unchanged-writer provenance')
    reports=[]
    for source,destination,version in ((args.legacy,work/'v6.otc',5),(work/'v6.otc',work/'v6-again.otc',6)):
        run=subprocess.run([str(args.probe),str(args.pak),str(source),str(destination),str(version)],capture_output=True,text=True,timeout=120)
        reports.append({'input_version':version,'returncode':run.returncode,'stdout':run.stdout,'stderr':run.stderr})
        if run.returncode:
            (work/'result.json').write_text(json.dumps(reports,indent=2))
            raise AssertionError(run.stdout+run.stderr)
    if (work/'v6.otc').read_bytes()!=(work/'v6-again.otc').read_bytes():
        raise AssertionError('Independent v6 load produced a second allocation/migration')
    if hashlib.sha256(args.legacy.read_bytes()).hexdigest()!=original_hash:
        raise AssertionError('Legacy fixture modified')
    result={'passed':True,'processes':2,'source_sha256':original_hash,'runs':reports,
            'v6_sha256':hashlib.sha256((work/'v6.otc').read_bytes()).hexdigest(),
            'scope':'Original-resource-backed port checkpoint migration, not original SVB or campaign.'}
    (work/'result.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result,indent=2))
    return 0


if __name__=='__main__':
    raise SystemExit(main())
