#!/usr/bin/env python3
"""Render and click the opt-in inventory preview through the common application.

Port integration regression, not original-game visual parity. Isolated saves.
"""
import argparse
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import zlib

ROOT = Path(__file__).resolve().parents[1]


def require(condition, reason):
    if not condition: raise AssertionError(reason)


def export_png(output, name):
    meta = json.loads((output / (name + '.image.json')).read_text())
    w,h = meta['viewport']
    rgba = (output / (name + '.rgba')).read_bytes()
    require(len(rgba) == w*h*4, 'invalid framebuffer capture')
    # Pure format conversion, bottom-left GL origin to standard top-left PNG.
    rows = b''.join(b'\0' + rgba[y*w*4:(y+1)*w*4] for y in reversed(range(h)))
    def chunk(kind, data):
        return struct.pack('>I',len(data)) + kind + data + struct.pack('>I',zlib.crc32(kind+data))
    png = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR',struct.pack('>IIBBBBB',w,h,8,6,0,0,0))
    png += chunk(b'IDAT',zlib.compress(rows)) + chunk(b'IEND',b'')
    (output / (name + '.png')).write_bytes(png)


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe',type=Path,required=True)
    p.add_argument('--game-dir',type=Path,required=True)
    p.add_argument('--output-dir',type=Path,required=True)
    a=p.parse_args();a.output_dir.mkdir(parents=True,exist_ok=True)
    work=Path(tempfile.mkdtemp(prefix='inventory-ui-',dir=a.output_dir))
    output=work/'capture'
    with (work/'run.log').open('w') as log:
        result=subprocess.run([sys.executable,str(ROOT/'tools/run_scenario.py'),
            '--library',str(a.probe),'--game-dir',str(a.game_dir),'--save-dir',str(work/'saves'),
            '--script',str(ROOT/'tests/scenarios/inventory-ui.scenario'),'--output',str(output)],
            stdout=log,stderr=subprocess.STDOUT,timeout=240)
    if result.returncode:
        print((work/'run.log').read_text()[-6000:],file=sys.stderr);return result.returncode
    try:
        events=[json.loads(line) for line in (output/'events.jsonl').read_text().splitlines()]
        down=[e['value'] for e in events if e['kind']=='inventory_tab_down']
        require(down==['15','16','14','16'],'tab delivery missing or duplicated on release')
        require(sum(e['kind']=='inventory_close_down' for e in events)==2,'close delivery differs')
        presses=[i for i,e in enumerate(events) if e['kind']=='inventory_press']
        releases=[i for i,e in enumerate(events) if e['kind']=='inventory_release']
        actions=[i for i,e in enumerate(events) if e['kind'] in ('inventory_tab_down','inventory_close_down')]
        require(len(presses)==len(releases)==len(actions)==6,'input route bypassed')
        require(all(p<d<r for p,d,r in zip(presses,actions,releases)),'action not delivered on down')
        before=json.loads((output/'before.state.json').read_text())
        after=json.loads((output/'after.state.json').read_text())
        fields=('class_guid','name','seed','position','angle','hp','max_hp','mana','max_mana',
                'gold','progression','inventory','slots','damage','armor','active_recovery',
                'skills','skill_effects','quests','completed_quests','revision')
        for field in fields: require(before[field]==after[field],'UI changed gameplay '+field)
        for name,tab in [('backpack',14),('spells',15),('fish_resized',16)]:
            state=json.loads((output/(name+'.state.json')).read_text())
            require(state['inventory_tab']==tab,'capture did not observe tab state')
            export_png(output,name)
        require((output/'backpack.rgba').read_bytes()!=(output/'spells.rgba').read_bytes(),
                'tab state did not affect rendering')
        report={'status':'PASSED','evidence':'port-regression-not-original',
                'unchanged_gameplay_fields':len(fields),'pointer_actions':6,
                'resize_preserves_tab':True,'fresh_open_resets_tab':True}
        (work/'summary.json').write_text(json.dumps(report,indent=2)+'\n')
        print('PASS inventory preview: 6 pointer actions, resize/reopen, 21 unchanged fields; '+str(work))
        return 0
    except Exception as exc:
        print('FAIL:',exc,'evidence:',work,file=sys.stderr);return 1


if __name__=='__main__':raise SystemExit(main())
