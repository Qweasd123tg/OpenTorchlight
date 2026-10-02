#!/usr/bin/env python3
"""Real headless/export/emulation/native calibration, explicitly opt-in."""
import argparse
import json
from pathlib import Path
import subprocess
import sys
import tempfile

from make_pcode_probe_profile import profile

ROOT=Path(__file__).resolve().parents[1]


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original',required=True,type=Path)
    parser.add_argument('--output-dir',required=True,type=Path)
    parser.add_argument('--reference-python',default=sys.executable)
    args=parser.parse_args()
    args.output_dir.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='pcode-calibration-',dir=args.output_dir) as folder:
        root=Path(folder);inputs=profile();path=root/'profile.json'
        path.write_text(json.dumps(inputs,separators=(',',':'))+'\n')
        command=[sys.executable,str(ROOT/'tools/ghidra_probe.py'),'--original',str(args.original),
                 '--profile',str(path),'--out',str(root/'probe')]
        for entry in dict.fromkeys(case['entry'] for case in inputs['cases']):command+=['--address',entry]
        subprocess.run(command,check=True)
        subprocess.run([args.reference_python,str(ROOT/'tests/compare_pcode_probe.py'),
                        '--original',str(args.original),'--profile',str(path),
                        '--result',str(root/'probe/emulation.json')],check=True)
    return 0


if __name__=='__main__':raise SystemExit(main())
