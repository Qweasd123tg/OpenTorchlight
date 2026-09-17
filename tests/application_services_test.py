#!/usr/bin/env python3
"""Common input/render/save regression; explicit level-10/gold fixture, NOT a campaign playthrough."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import subprocess
import sys
import tempfile
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from compare_scenarios import first_difference

def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe', type=Path, required=True)
    p.add_argument('--fixture', type=Path, required=True)
    p.add_argument('--game-dir', type=Path, required=True)
    p.add_argument('--output-dir', type=Path, required=True)
    p.add_argument('--timeout-scale', type=int, choices=range(1,11), default=1)
    a = p.parse_args()
    a.output_dir.mkdir(parents=True, exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix='services-', dir=a.output_dir))
    result = {'evidence':'real common loop/pak/GLES; explicit XP/gold fixture; NOT original behavior trace or campaign completion', 'assertions':0, 'runs':[]}
    def require(condition, why):
        result['assertions'] += 1
        if not condition: raise AssertionError(why)
    def run(label, script):
        out=work/label
        with (work/(label+'.log')).open('w') as log:
            rc=subprocess.run([sys.executable,str(ROOT/'tools/run_scenario.py'),'--library',str(a.probe),'--game-dir',str(a.game_dir),'--save-dir',str(work/'saves'),'--script',str(ROOT/'tests/scenarios'/script),'--output',str(out)],stdout=log,stderr=subprocess.STDOUT,timeout=300*a.timeout_scale).returncode
        result['runs'].append({'name':label,'returncode':rc})
        require(rc==0,label+': '+(work/(label+'.log')).read_text()[-8000:])
        return out
    def state(folder,name):return json.loads((folder/(name+'.state.json')).read_text())
    def quantity(s):return sum(i.get('stack',0) for i in s['inventory'])
    try:
        run('new','services-new.scenario')
        prepared=subprocess.run([str(a.fixture),str(a.game_dir/'pak.zip'),str(work/'saves')],capture_output=True,text=True,timeout=60*a.timeout_scale)
        require(prepared.returncode==0,'fixture: '+prepared.stderr)
        result['preparation']=prepared.stdout.strip()
        use=run('use','services-use.scenario')
        before,after,learned,active,journal=[state(use,n) for n in ('shop_before','shop_after','learned','active','journal')]
        require(after['gold']<before['gold'],'merchant input did not debit gold')
        require(quantity(after)==quantity(before)+1,'merchant input did not transfer one bottle')
        require(after['progression']['level']==10,'wrong prepared level')
        require(learned['progression']['skill_points']==after['progression']['skill_points']-1,'UI investment point debit')
        require(next(s['rank'] for s in learned['skills'] if s['name']=='INFUSE')==1,'UI investment rank')
        require(not learned['skill_effects'],'learning applies buff before casting')
        require(len(active['skill_effects'])==3,'cast does not apply complete Infuse effect list')
        require(active['damage'][1]>learned['damage'][1],'Infuse not connected to damage')
        require(active['mana']<learned['mana'],'cast did not consume mana')
        require(all(0<e['remaining']<=30 for e in active['skill_effects']),'invalid buff timer')
        require(active['actor_visible_pixels']>0,'actor not actually rendered')
        for field in ('skills','skill_effects','quests','completed_quests','gold','progression'):
            require(first_difference(active[field],journal[field]) is None,'journal changes '+field)
        cont=run('continue','services-continue.scenario')
        restored,expired=state(cont,'restored'),state(cont,'expired')
        for field in ('class_guid','name','seed','position','angle','hp','max_hp','mana','max_mana','gold','progression','inventory','slots','damage','armor','rng','entities','active_recovery','skills','skill_effects','quests','completed_quests'):
            require(first_difference(active[field],restored[field]) is None,'fresh process changes '+field)
        require(not expired['skill_effects'],'buff never expires in common loop')
        require(expired['damage']==learned['damage'],'expiry leaves permanent combat bonus')
        require(expired['skills']==restored['skills'],'expiry removed learned rank')
        require(expired['gold']==restored['gold'],'loaded merchant repeated purchase')
        result.update(status='PASSED',purchase_price=before['gold']-after['gold'])
        print(f"PASS {result['assertions']} service/skill assertions, 3 processes; {work}")
        return 0
    except Exception as exc:
        result.update(status='FAILED',error=str(exc))
        print(f'FAIL: {exc}; {work}',file=sys.stderr)
        return 1
    finally:
        (work/'test-result.json').write_text(json.dumps(result,indent=2)+'\n')
if __name__=='__main__':raise SystemExit(main())
