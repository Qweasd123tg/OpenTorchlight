#!/usr/bin/env python3
"""Missile runtime proof: fixture-granted rolled wand -> real equip keys ->
portal -> Main 1 -> missile flight -> impact kill. Real pak/GLES, no damage
or entity injection; the wand grant itself is the only fixture step (same
honesty category as the services XP/gold fixture)."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]

def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe', type=Path, required=True)
    p.add_argument('--fixture', type=Path, required=True)
    p.add_argument('--game-dir', type=Path, required=True)
    p.add_argument('--output-dir', type=Path, required=True)
    p.add_argument('--timeout-scale', type=int, choices=range(1, 11), default=1)
    a = p.parse_args()
    a.output_dir.mkdir(parents=True, exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix='missile-', dir=a.output_dir))
    result = {'evidence': 'real wand equip + missile flight/impact; fixture grant only',
              'assertions': 0, 'runs': []}
    def require(condition, why):
        result['assertions'] += 1
        if not condition:
            raise AssertionError(why)
    def run(label, script):
        out = work / label
        with (work / (label + '.log')).open('w') as log:
            rc = subprocess.run(
                [sys.executable, str(ROOT / 'tools/run_scenario.py'), '--library', str(a.probe),
                 '--game-dir', str(a.game_dir), '--save-dir', str(work / 'saves'),
                 '--script', str(ROOT / 'tests/scenarios' / script), '--output', str(out)],
                stdout=log, stderr=subprocess.STDOUT, timeout=300 * a.timeout_scale).returncode
        result['runs'].append({'name': label, 'returncode': rc})
        require(rc == 0, label + ': ' + (work / (label + '.log')).read_text()[-8000:])
        return out
    def state(folder, name):
        return json.loads((folder / (name + '.state.json')).read_text())
    try:
        run('new', 'wand-missile-new.scenario')
        prepared = subprocess.run(
            [str(a.fixture), str(a.game_dir / 'pak.zip'), str(work / 'saves'), 'WAND_MAGIC_5A'],
            capture_output=True, text=True, timeout=60 * a.timeout_scale)
        require(prepared.returncode == 0, 'fixture: ' + prepared.stderr)
        result['preparation'] = prepared.stdout.strip()
        use = run('use', 'wand-missile-use.scenario')
        log = (work / 'use.log').read_text()
        equipped, populated, killed = (state(use, n) for n in ('wand_equipped', 'populated', 'missile_kill'))
        slots = equipped.get('slots', [])
        require(slots and slots[0] != 0, 'wand not wielded in weapon slot')
        wielded = [i for i in equipped['inventory'] if i.get('id') == slots[0]] if slots else []
        require(bool(wielded) and wielded[0].get('delivery') == 2, 'wielded weapon is not missile delivery')
        require('missile_fired=FIREWAND' in log, 'no missile creation notice in run log')
        require('source=missile:direct' in log, 'no missile impact notice in run log')
        deaths = [e for e in killed['entities'] if e.get('player_kill')]
        require(bool(deaths), 'no player missile kill')
        require(all(not e['alive'] for e in deaths), 'missile victim left alive')
        require(killed['progression']['experience'] > equipped['progression']['experience'],
                'missile kill gave no XP')
        result.update(status='PASSED')
        print(f"PASS {result['assertions']} missile assertions; {work}")
        return 0
    except Exception as exc:
        result.update(status='FAILED', error=str(exc))
        print(f'FAIL: {exc}; {work}', file=sys.stderr)
        return 1
    finally:
        (work / 'test-result.json').write_text(json.dumps(result, indent=2) + '\n')

if __name__ == '__main__':
    raise SystemExit(main())
