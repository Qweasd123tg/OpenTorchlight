#!/usr/bin/env python3
"""Compare skill percentage/DPS/soak branches against original instructions.

The oracle reuses the bounded ordinary-attack fixture, with explicit skill
scalars. It does not run the game, skill activation or original HP delivery.
"""
import argparse
import hashlib
import itertools
import json
import os
from pathlib import Path
import platform
import random
import subprocess
import time

from compare_typed_damage import bits, effect_text, f32
from native_typed_reference import Native


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original', type=Path, required=True)
    parser.add_argument('--probe', type=Path, required=True)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64') or os.sysconf('SC_PAGE_SIZE') != 4096:
        return 77
    began = time.monotonic()
    native = Native(args.original)
    inputs, expected, groups = [], [], {}
    rng = random.Random(20260919)

    def add(group, base, pct, soak, dps, speed, seed=1, bonus=None,
            strength=0, dexterity=0, magic=0, armor=0, defense=0,
            elemental=None, actor_effects=(), target_effects=(), left_hand=False):
        bonus = bonus or [0] * 7
        elemental = elemental or [0] * 7
        pct, soak, speed = map(f32, (pct, soak, speed))
        result, state = native.run(base, bonus, strength, dexterity, magic,
            actor_effects, armor, defense, elemental, target_effects, seed, [0x23],
            damage_fraction=f32(pct / 100.0), soak_multiplier=f32(soak / 100.0),
            use_dps=dps, dps_speed=speed, left_hand=left_hand)
        pairs, maximum, rolled, applied = result
        mode = 'L' if left_hand else 'S'
        inputs.append(f'{mode} {bits(pct)} {bits(soak)} {int(dps)} {bits(speed)} '
            f'{base} {strength} {dexterity} {magic} 1 {armor} {defense} {seed} '
            + ' '.join(map(str, bonus + elemental))
            + f' {effect_text(actor_effects)} {effect_text(target_effects)}\n')
        expected.append([len(pairs), maximum, rolled, applied, state]
                        + [value for pair in pairs for value in pair])
        groups[group] = groups.get(group, 0) + 1

    try:
        # Small explicit repros come first in failure reports.
        add('regressions', 100, 40, 100, False, 1)
        add('regressions', 100, 0, 100, False, 1)
        for base, pct, profile, seed in itertools.product(
                (0, 1, 2, 3, 7, 99, 100, 1001), (0, 0.1, 40, 99.9, 100, 150),
                ((False, 1.0), (True, 0.3), (True, 1.0), (True, 2.0)),
                (1, 7, 0xFFFFFFFF)):
            add('boundary_rolls', base, pct, 100, *profile, seed=seed)
        for _ in range(900):
            bonus = [0] * 7
            for channel in (2, 3, 4, 5):
                if rng.randrange(2):
                    bonus[channel] = rng.randrange(1, 80)
            actor = [(0x19, 6, f32(rng.uniform(0, 50))),
                     (0x10, 7, f32(rng.uniform(0, 50)))]
            target = [(0x1a, 6, f32(rng.uniform(-80, 100)))]
            add('channels_and_defense', rng.randrange(1000),
                rng.choice((0, 0.1, 40, 100, 150)), rng.choice((0, 60, 100, 150)),
                bool(rng.randrange(2)), rng.choice((0.3, 0.8, 1, 2.5)),
                seed=rng.randrange(1, 2**32), bonus=bonus,
                strength=rng.randrange(100), dexterity=rng.randrange(100),
                magic=rng.randrange(100), armor=rng.randrange(80),
                defense=rng.randrange(80), elemental=[rng.randrange(50) for _ in range(7)],
                actor_effects=actor, target_effects=target)
        # DPS applies before flat bonuses in the maximum pass but after them
        # in the roll pass. Exercise the distinction, including flat-only.
        for _ in range(600):
            channel = rng.randrange(7)
            bonus = [0] * 7
            bonus[channel] = rng.randrange(50)
            add('flat_bonus_dps', rng.randrange(100), rng.choice((0, 40, 100, 150)),
                rng.choice((0, 60, 100)), True, rng.choice((0.3, 1, 2)),
                seed=rng.randrange(1, 2**32), bonus=bonus,
                actor_effects=[(10, channel, f32(rng.uniform(0.1, 30)))],
                elemental=[rng.randrange(40) for _ in range(7)])
        for base, pct, speed, seed in itertools.product((1, 7, 99, 100), (0, 40, 100), (0.8, 2), (1, 91)):
            add('left_hand', base, pct, 60, True, speed, seed=seed,
                bonus=[0, 0, 9, 0, 0, 0, 0], dexterity=23, magic=17,
                actor_effects=[(10, 2, 3), (0x10, 7, 11)], armor=9,
                elemental=[0, 0, 12, 0, 0, 0, 0], left_hand=True)
        result = subprocess.run([str(args.probe.resolve())], input=''.join(inputs),
                                text=True, capture_output=True, check=True, timeout=90)
        actual = [list(map(int, line.split())) for line in result.stdout.splitlines()]
        if len(actual) != len(expected):
            raise AssertionError(f'row count: original={len(expected)}, port={len(actual)}')
        mismatches = [i for i, pair in enumerate(zip(expected, actual)) if pair[0] != pair[1]]
        report = {
            'passed': not mismatches, 'original_sha256': native.original.sha256,
            'comparisons': len(expected), 'groups': groups, 'mismatches': len(mismatches),
            'generator_seed': 20260919,
            'input_sha256': hashlib.sha256(''.join(inputs).encode()).hexdigest(),
            'expected_sha256': hashlib.sha256(json.dumps(expected, separators=(',', ':')).encode()).hexdigest(),
            'elapsed_seconds': round(time.monotonic() - began, 3),
            'functions_and_slices': native.evidence,
            'scope': 'Original rollAttack percentage/DPS/soak through channel assembly and volatile RNG; explicit fraction/speed inputs.',
            'excluded': ['Full skill/caller wiring', 'Equipment-to-DPS-speed mapping',
                         'Dual hands', 'Crit/block/glance/procs', 'HP and resource event execution'],
        }
        if mismatches:
            i = mismatches[0]
            report['first_mismatch'] = {'case': i, 'input': inputs[i].strip(),
                                        'original': expected[i], 'port': actual[i]}
        if args.output:
            args.output.parent.mkdir(parents=True, exist_ok=True)
            args.output.write_text(json.dumps(report, indent=2) + '\n')
        print(json.dumps({key: value for key, value in report.items()
                          if key != 'functions_and_slices'}, indent=2))
        return 1 if mismatches else 0
    finally:
        native.close()


if __name__ == '__main__':
    raise SystemExit(main())
