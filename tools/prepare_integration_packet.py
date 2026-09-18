#!/usr/bin/env python3
"""Package already-ported-but-unwired functions that share one implementation.

No reverse engineering is performed. The point is to stop re-researching code
that already exists and hand an integrator the exact functions/evidence/gaps.
"""
from __future__ import annotations
import argparse,json,subprocess,sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]

def main()->int:
 ap=argparse.ArgumentParser(description=__doc__)
 ap.add_argument('--group',required=True,help='implementation group from work_frontier, e.g. src/panel_open.cpp')
 ap.add_argument('--out',type=Path,required=True)
 args=ap.parse_args(); out=args.out.resolve();out.mkdir(parents=True,exist_ok=True)
 # Generate a fresh frontier rather than trusting a stale artifact.
 frontier=out/'frontier.json'
 subprocess.run([sys.executable,str(ROOT/'tools/work_frontier.py'),'--json',str(frontier),'--out',str(out/'frontier.md')],check=True)
 data=json.loads(frontier.read_text(encoding='utf-8'))
 group=next((g for g in data['near_term']['integration_groups'] if g['implementation_group']==args.group),None)
 if group is None: raise SystemExit(f'integration group not found: {args.group}')
 pdir=out/'functions';pdir.mkdir(exist_ok=True)
 for m in group['members']:
  subprocess.run([sys.executable,str(ROOT/'tools/function_package.py'),'--address',m['address'],'--out',str(pdir/(m['address']+'.md'))],check=True)
 summary={"schema":1,"implementation_group":args.group,"members":[m['address'] for m in group['members']],
          "meaning":"Integration packet for existing port code; not new fidelity evidence."}
 (out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
 (out/'PROMPT.txt').write_text(
  f"Integrate the already-ported original-function family that shares {args.group}. Do NOT restart reverse engineering unless a concrete sink/caller ambiguity requires it.\n\n"
  "Read every functions/*.md package first. Reuse the existing implementation and its bounded original evidence.\n"
  "Goal: consume every already-reported effect through the real application/window/game caller, or leave the exact effect explicitly unwired.\n"
  "Do not mark wired merely because a helper returns the right value. Exercise the real caller/scenario.\n"
  "Do not duplicate the helper per menu/function. Preserve proven member deltas as profile/data.\n"
  "If integration exposes a mismatch, identify the smallest original caller/callee slice needed; do not reopen the whole subsystem.\n"
  "Update function-transfer per member only after the sink exists. Report: reused code, caller changes, sinks connected, remaining effects, scenario/comparison actually run.\n",
  encoding='utf-8')
 print(f"packet {out}: {len(group['members'])} existing functions share {args.group}")
 return 0
if __name__=='__main__': raise SystemExit(main())
