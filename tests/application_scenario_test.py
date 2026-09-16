#!/usr/bin/env python3
"""Real-pak, separate-process application regression. Same application/UI/renderer as desktop.
No direct session creation, no world injection, no original-process equivalence claim.
"""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from compare_scenarios import compare, first_difference


def main() -> int:
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe',type=Path,required=True);p.add_argument('--game-dir',type=Path,required=True)
    p.add_argument('--output-dir',type=Path,required=True)
    p.add_argument('--roundtrip',action='store_true')
    p.add_argument('--speed-probe',type=Path)
    p.add_argument('--timeout-scale',type=int,choices=range(1,11),default=1)
    a=p.parse_args();a.output_dir.mkdir(parents=True,exist_ok=True)
    work=Path(tempfile.mkdtemp(prefix='application-',dir=a.output_dir))
    outcomes=[];checks=0
    def require(condition,message):
        nonlocal checks
        checks+=1
        if not condition:raise AssertionError(message)
    def state(folder,name):return json.loads((folder/(name+'.state.json')).read_text())
    def run(label,script,saves):
        output=work/label
        command=[sys.executable,str(ROOT/'tools/run_scenario.py'),'--library',str(a.probe),
                 '--game-dir',str(a.game_dir),'--save-dir',str(saves),'--script',str(script),'--output',str(output)]
        with (work/(label+'.log')).open('w') as log:
            result=subprocess.run(command,stdout=log,stderr=subprocess.STDOUT,timeout=240*a.timeout_scale)
        outcomes.append({'scenario':label,'returncode':result.returncode})
        if result.returncode==77:raise RuntimeError('NOT RUN: real EGL runtime unavailable')
        if result.returncode:
            raise AssertionError(f'{label} failed; '+(work/(label+'.log')).read_text()[-8000:])
        return output
    result={'evidence':'resource-backed port regression; not original or Wayland execution','output':str(work),
            'timeout_scale':a.timeout_scale,'scenario_inputs_unchanged':True}
    try:
        new=ROOT/'tests/scenarios/town-new.scenario';saved=work/'saves-a'
        first=run('new',new,saved)
        initial=state(first,'town_initial');walked=state(first,'town_walked')
        unarmed=state(first,'unarmed');rearmed=state(first,'rearmed')
        require(initial['name']=='automated','real name input was not applied')
        require(initial['dungeon']=='Town' and initial['depth']==0,'not the real Town start')
        require(initial['actor_visible_pixels']>0,'player/weapon contributes no visible pixels')
        render = json.loads((first/'town_initial.render.json').read_text())
        passes = [draw for instance in render['instances'] for draw in instance['passes']]
        require(bool(passes), 'real Town produced no draw-pass diagnostics')
        require(all(len(draw[field]) == 3 for draw in passes for field in ('ambient','diffuse','emissive')),
                'material diagnostic does not match the actual RGB uniform arity')
        require(walked['position']!=initial['position'] and walked['walkable'],'pointer walk did not change valid position')
        require(unarmed['slots'][0]==0 and rearmed['slots'][0]!=0,'real inventory key commands did not change equipment')
        require(unarmed['damage']!=rearmed['damage'],'equipment did not affect computed combat state')
        require(initial['inventory']==rearmed['inventory'],'unequip/equip rerolled or lost a concrete item')
        require(state(first,'town_resized')['viewport']==[800,450],'viewport resize missed common app')
        require(state(first,'town_resized')['actor_visible_pixels']>0,'actor disappeared after resize')
        resumed=run('continue',ROOT/'tests/scenarios/town-continue.scenario',saved)
        before=state(first,'before_exit');after=state(resumed,'restored')
        for key in ('class_guid','name','seed','position','angle','recovery_anchor','hp','max_hp','mana','max_mana',
                    'gold','progression','inventory','slots','damage','armor'):
            require(first_difference(before[key],after[key]) is None,'fresh process changed '+key)
        require(after['revision']==2,'actual save-and-exit did not write the second revision')
        require(after['walkable'],'loaded position not on navigation grid')
        for suffix in ('.rgba','.render.json','.actor-mask.bin'):
            require((resumed/('frozen_before_pause'+suffix)).read_bytes()==
                    (resumed/('frozen_after_pause'+suffix)).read_bytes(),
                    'UI -> world changed frozen renderer state or pixels: '+suffix)

        # Execute again in a fresh process and empty save store. Exact output
        # comparison (including RNG call order), not a screenshot similarity score.
        replay=run('replay',new,work/'saves-b')
        difference=compare(first,replay)
        (work/'repeatability.json').write_text(json.dumps(difference,indent=2)+'\n')
        require(difference['status']=='PASSED','first exact replay difference: '+json.dumps(difference))
        guids={initial['class_guid']}
        for index in (0,2):
            script=work/f'class-{index}.scenario'
            script.write_text(f'''menu main
button new
menu create
button class-{index}
name class{index}
button create
level Town 0
frames 3
capture selected
key ESC
menu pause
button save-exit
''')
            sample=run('class-'+str(index),script,work/('saves-class-'+str(index)))
            selected=state(sample,'selected');guids.add(selected['class_guid'])
            require(selected['walkable'] and selected['actor_visible_pixels']>0,'class not visibly placed in real Town')
            require(bool(selected['bones']),'selected class did not reach real skeleton sampler')
        require(len(guids)==3,'class buttons did not select three distinct resources')
        if a.roundtrip:
            route=run('dungeon',ROOT/'tests/scenarios/dungeon-roundtrip.scenario',saved)
            entered=state(route,'dungeon_entry');returned=state(route,'returned_town')
            require(entered['dungeon']=='Main' and returned['dungeon']=='Town','real trigger roundtrip did not change floors')
            require(entered['walkable'] and returned['walkable'],'roundtrip placed player off navigation grid')
            # One more fresh process verifies campaign save after the roundtrip.
            restored=run('return-continue',ROOT/'tests/scenarios/town-continue.scenario',saved)
            require(state(restored,'restored')['inventory']==returned['inventory'],'roundtrip save changed items')
        if a.speed_probe:
            with (work/'resource-speed-comparison.log').open('w') as log:
                numeric=subprocess.run([sys.executable,str(ROOT/'tests/compare_attack_speed.py'),
                                        '--probe',str(a.speed_probe),'--scenario-dir',str(work)],
                                       stdout=log,stderr=subprocess.STDOUT,timeout=90*a.timeout_scale)
            require(numeric.returncode==0,'bounded exported speed comparison failed; see resource-speed-comparison.log')
        result.update(status='PASSED',assertions=checks,runs=outcomes)
        print(f'PASS: {len(outcomes)} real-resource application processes, {checks} assertions; evidence {work}')
        return 0
    except Exception as exc:
        result.update(status='FAILED',error=str(exc),assertions=checks,runs=outcomes)
        print('FAIL:',exc,file=sys.stderr);print('Evidence retained:',work,file=sys.stderr)
        return 1
    finally:
        (work/'test-result.json').write_text(json.dumps(result,indent=2)+'\n')

if __name__=='__main__':raise SystemExit(main())
