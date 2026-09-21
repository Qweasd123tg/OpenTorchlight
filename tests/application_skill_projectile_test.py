#!/usr/bin/env python3
"""Physical-input/common-loop projectile skill regression, not full original SEEKING parity."""
import argparse
import json
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', type=Path, required=True)
    parser.add_argument('--fixture', type=Path, required=True)
    parser.add_argument('--game-dir', type=Path, required=True)
    parser.add_argument('--output-dir', type=Path, required=True)
    args = parser.parse_args()
    args.output_dir.mkdir(parents=True, exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix='skill-projectile-', dir=args.output_dir))
    report = {'evidence': 'real common loop/pak/GLES with explicit level-10 fixture; not native lifecycle parity', 'assertions': 0}

    def require(value, message):
        report['assertions'] += 1
        if not value:
            raise AssertionError(message)

    def run(label):
        with (work / (label + '.log')).open('w') as log:
            proc = subprocess.run([sys.executable, str(ROOT / 'tools/run_scenario.py'),
                '--library', str(args.probe), '--game-dir', str(args.game_dir),
                '--save-dir', str(work / 'saves'), '--script', str(ROOT / 'tests/scenarios' / f'skill-projectile-{label}.scenario'),
                '--output', str(work / label)], stdout=log, stderr=subprocess.STDOUT, timeout=300)
        text = (work / (label + '.log')).read_text()
        require(proc.returncode == 0, text[-8000:])
        return text

    try:
        run('new')
        prepared = subprocess.run([str(args.fixture), str(args.game_dir / 'pak.zip'), str(work / 'saves'), 'SEEKING SHOT'], capture_output=True, text=True, timeout=60)
        require(prepared.returncode == 0, prepared.stderr)
        text = run('use')
        learned, after = [json.loads((work / 'use' / f'{name}.state.json').read_text()) for name in ('learned', 'after')]
        require(next(s['rank'] for s in learned['skills'] if s['name'] == 'SEEKING SHOT') == 1, 'input investment failed')
        require(after['mana'] < learned['mana'], 'input cast did not spend mana')
        require(not after['skill_effects'], 'weapon skill invented self-buff effects')
        require(after['actor_visible_pixels'] > 0, 'real actor rendering missing')
        markers = ['skill_started=SEEKING SHOT', 'skill_event=EVENT_START', 'skill_hit=SEEKING SHOT', 'skill_missile_fired=SEEKINGSHOT']
        positions = [text.find(marker) for marker in markers]
        require(all(p >= 0 for p in positions) and positions == sorted(positions), 'START/HIT/launch sequence absent or reversed')
        require(text.count('skill_missile_fired=SEEKINGSHOT') == 1, 'launch duplicated or missing')
        require('skill_event=EVENT_MISSILEDIE' in text, 'projectile never retired')
        require('skill_missile_refused' not in text and 'missile_impact_without_shot' not in text, 'ownership/template refusal')
        require(after['skills'] == learned['skills'], 'cast changed learned ranks')
        report['status'] = 'PASSED'
        print(f"PASS application skill projectile: {report['assertions']} assertions; {work}")
        return 0
    except Exception as error:
        report.update(status='FAILED', error=str(error))
        print(f'FAIL {error}; {work}', file=sys.stderr)
        return 1
    finally:
        (work / 'test-result.json').write_text(json.dumps(report, indent=2) + '\n')


if __name__ == '__main__':
    raise SystemExit(main())
