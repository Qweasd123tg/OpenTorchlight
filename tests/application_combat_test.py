#!/usr/bin/env python3
"""Real pak, real common application and GLES, two independent processes.

New Vanquisher -> real portal -> density population -> pointer-targeted HIT kill
-> reward -> save -> fresh process. No injection of entities, gear or damage.
This is a port regression, not a capture of the original game or desktop window.
"""
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
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', type=Path, required=True)
    parser.add_argument('--game-dir', type=Path, required=True)
    parser.add_argument('--output-dir', type=Path, required=True)
    parser.add_argument('--timeout-scale', type=int, choices=range(1, 11), default=1)
    args = parser.parse_args()
    args.output_dir.mkdir(parents=True, exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix='combat-', dir=args.output_dir))
    result = {'evidence': 'resource-backed common application regression, not original/Wayland',
              'output': str(work), 'runs': [], 'assertions': 0}
    def require(condition, message):
        result['assertions'] += 1
        if not condition:
            raise AssertionError(message)
    def run(label, script):
        output = work / label
        with (work / (label + '.log')).open('w') as log:
            code = subprocess.run([sys.executable, str(ROOT / 'tools/run_scenario.py'),
                '--library', str(args.probe), '--game-dir', str(args.game_dir),
                '--save-dir', str(work / 'saves'), '--script', str(ROOT / 'tests/scenarios' / script),
                '--output', str(output)], stdout=log, stderr=subprocess.STDOUT,
                timeout=240 * args.timeout_scale).returncode
        result['runs'].append({'name': label, 'returncode': code})
        require(code == 0, label + ' failed: ' + (work / (label + '.log')).read_text()[-8000:])
        return output
    def state(folder, name):
        return json.loads((folder / (name + '.state.json')).read_text())
    try:
        first = run('kill', 'ranged-kill.scenario')
        populated, killed, frozen = [state(first, name) for name in ('populated', 'killed', 'frozen')]
        require(populated['dungeon'] == 'Main' and populated['depth'] == 1, 'wrong resource floor')
        require(populated['population_generated'], 'population flag not committed')
        require(len(populated['entities']) > 1, 'only placed boss, no ordinary population')
        require(populated['actor_visible_pixels'] > 0, 'player is not rendered')
        require(populated['inventory'][0]['delivery'] == 1, 'starting bow not direct physical')
        deaths = [e for e in killed['entities'] if e['player_kill']]
        require(bool(deaths), 'no actual player HIT kill')
        require(all(not e['alive'] and e['reward_claimed'] for e in deaths), 'unfinished death/reward transaction')
        require(killed['progression']['experience'] > populated['progression']['experience'], 'kill gave no XP')
        require(len(killed['entities']) >= len(populated['entities']), 'unrelated entities lost during attack')
        for name in ('hp','gold','progression','rng','entities','inventory','active_recovery'):
            require(first_difference(killed[name], frozen[name]) is None, 'dt=0 changed ' + name)
        second = run('continue', 'ranged-continue.scenario')
        restored = state(second, 'restored')
        for name in ('class_guid','name','seed','position','angle','recovery_anchor',
                     'hp','max_hp','mana','max_mana','gold','progression','inventory','slots',
                     'damage','armor','rng','entities','active_recovery','population_generated'):
            difference = first_difference(frozen[name], restored[name])
            require(difference is None, 'fresh process changed ' + name + ': ' + str(difference))
        require(restored['revision'] == 1, 'wrong checkpoint revision')
        require(restored['walkable'], 'loaded player is outside navigation')
        result.update(status='PASSED', entities=len(populated['entities']), player_kills=len(deaths),
                      experience=killed['progression']['experience'])
        print(f"PASS: {result['assertions']} common-app combat assertions, two processes; evidence {work}")
        return 0
    except Exception as exc:
        result.update(status='FAILED', error=str(exc))
        print(f'FAIL: {exc}; evidence {work}', file=sys.stderr)
        return 1
    finally:
        (work / 'test-result.json').write_text(json.dumps(result, indent=2) + '\n')


if __name__ == '__main__':
    raise SystemExit(main())
