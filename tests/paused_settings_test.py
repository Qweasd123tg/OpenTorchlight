#!/usr/bin/env python3
"""Actual common loop + original pak: pause/settings must stay modal and not save a character."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import subprocess
import sys
import tempfile
ROOT = Path(__file__).resolve().parents[1]

def main() -> int:
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe',type=Path,required=True)
    p.add_argument('--game-dir',type=Path,required=True)
    p.add_argument('--output-dir',type=Path,required=True)
    a=p.parse_args(); a.output_dir.mkdir(parents=True,exist_ok=True)
    work=Path(tempfile.mkdtemp(prefix='paused-settings-',dir=a.output_dir))
    output=work/'capture'; saves=work/'saves'
    with (work/'run.log').open('w') as log:
        run=subprocess.run([sys.executable,str(ROOT/'tools/run_scenario.py'),
            '--library',str(a.probe),'--game-dir',str(a.game_dir),'--save-dir',str(saves),
            '--script',str(ROOT/'tests/scenarios/paused-settings.scenario'),'--output',str(output)],
            stdout=log,stderr=subprocess.STDOUT,timeout=240)
    if run.returncode:
        print((work/'run.log').read_text()[-8000:],file=sys.stderr); return run.returncode
    try:
        for name in ('opened_settings','applied_settings'):
            assert (output/(name+'.rgba')).stat().st_size>0, 'settings page was not drawn: '+name
        settings=(output/'settings/local_settings.txt').read_text(encoding='utf-16')
        assert 'SHOW BLOOD :0' in settings, 'Apply did not store the toggled value'
        events=[json.loads(line) for line in (output/'events.jsonl').read_text().splitlines()]
        releases=[e['value'] for e in events if e['kind']=='hud_release']
        assert releases==['PauseButton','InventoryButton','JournalButton','PetButton','OptionsButton'], 'HUD route was bypassed'
        dispatches=[(i,e) for i,e in enumerate(events) if e['kind']=='hud_dispatch_down']
        release_events=[(i,e) for i,e in enumerate(events) if e['kind']=='hud_release']
        assert [e['value'] for _,e in dispatches]==['guiPause','guiToggleInventory','guiToggleJournal','guiTogglePet','guiToggleOptions'], 'down command missing or release replayed it'
        for (di,_),(ri,_) in zip(dispatches,release_events):
            assert di<ri, 'HUD command waited for release'
        unsupported=[e['value'] for e in events if e['kind']=='hud_callback_unimplemented']
        assert unsupported==['guiToggleJournal','guiTogglePet'], 'unsupported callback was silently remapped'
        writes=[i for i,e in enumerate(events) if e['kind']=='checkpoint_saved']
        quit_index=next(i for i,e in enumerate(events) if e['kind']=='command' and e['value'].endswith(':quit'))
        assert len(writes)==1 and writes[0]>quit_index, 'Apply performed an accidental checkpoint write'
        assert len(list(saves.glob('*.otc')))==1, 'normal exit checkpoint policy was changed'
        before=json.loads((output/'before.state.json').read_text())
        after=json.loads((output/'after.state.json').read_text())
        fields=('class_guid','name','seed','position','angle','hp','max_hp','mana','max_mana',
                'gold','progression','inventory','slots','damage','armor','active_recovery',
                'skills','skill_effects','quests','completed_quests','revision')
        for field in fields:
            assert before[field]==after[field], 'paused settings changed '+field
        print('PASS: rendered settings, Apply, return through pause; '+str(len(fields))+
              ' state fields unchanged; five original HUD down routes, off-target releases do not replay; no accidental OTC save; '+str(work))
        return 0
    except Exception as exc:
        print('FAIL:',exc,'evidence:',work,file=sys.stderr); return 1

if __name__=='__main__': raise SystemExit(main())
