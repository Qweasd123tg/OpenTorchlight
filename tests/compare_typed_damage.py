#!/usr/bin/env python3
"""Compare bounded original weapon allocation, MAGIC, defenses and attack channels.

The supplied ELF is fingerprinted. No game launcher/constructors are executed.
The attack oracle stops before critical-independent glancing/block/proc/HP stages.
See native_typed_reference.py for all fixture callbacks and interception points.
"""
from __future__ import annotations
import argparse
import ctypes as c
import hashlib
import json
import os
from pathlib import Path
import platform
import random
import struct
import subprocess
from native_typed_reference import Native


def f32(value: float) -> float:
    return struct.unpack('<f', struct.pack('<f', value))[0]


def bits(value: float) -> int:
    return struct.unpack('<I', struct.pack('<f', value))[0]


def effect_text(values: list) -> str:
    return ' '.join([str(len(values))] + [f'{kind} {channel} {bits(value)}' for kind, channel, value in values])


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original', type=Path, required=True)
    parser.add_argument('--probe', type=Path, required=True)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64') or os.sysconf('SC_PAGE_SIZE') != 4096:
        return 77
    native = Native(args.original)
    rng = random.Random(43286)
    inputs, expected, groups = [], [], {}

    def add(group: str, text: str, result: list) -> None:
        inputs.append(text + '\n')
        expected.append(result)
        groups[group] = groups.get(group, 0) + 1

    try:
        # Signed percentages, separate per-type truncation; no normalization.
        allocations = [(graph, pct) for graph in (0, 1, 7, 10, 41, 49, 100, 9999)
                       for pct in (-100, -1, 0, 1, 25, 30, 50, 99, 100, 101, 250)]
        allocations += [(rng.randrange(100000), rng.randrange(-100, 501)) for _ in range(3000)]
        for graph, pct in allocations:
            percent = [pct, 0, pct, pct, pct, pct, 0]
            bonus = native.allocate(graph, pct, False)
            add('allocation', f"A {graph} " + ' '.join(map(str, percent)),
                [native.allocate(graph, pct, True), 0, 0, bonus, bonus, bonus, bonus, 0])

        for _ in range(1500):
            magic = rng.randrange(10000)
            effect = [(0x12, 7, f32(rng.uniform(-99, 200))), (3, 7, f32(rng.uniform(-10, 10)))]
            # Duplicate contributions deliberately expose binary32 aggregation.
            effect.append((0x12, 7, f32(rng.uniform(0, 50))))
            native.effects = effect
            struct.pack_into('<i', native.actor, 0x434, magic)
            add('magic', f'G {magic} {effect_text(effect)}', [native.magic(c.addressof(native.actor))])

        for i in range(1500):
            armor, defense = rng.randrange(1000), rng.randrange(200)
            elements = [rng.randrange(1000) for _ in range(7)]
            effects = [(0x17, rng.randrange(7), f32(rng.uniform(-100, 200))),
                       (0x1a, rng.randrange(7), f32(rng.uniform(-150, 100))),
                       (0x1a, 6, f32(rng.uniform(-20, 20))),
                       (0x42, 7, f32(rng.uniform(0, 50))),
                       (rng.randrange(35, 41), 7, f32(rng.uniform(-10, 10)))]
            native.target_effects = effects
            struct.pack_into('<i', native.target, 0x424, armor)
            struct.pack_into('<i', native.target, 0x430, defense)
            for channel, value in enumerate(elements):
                struct.pack_into('<i', native.target, 0x620 + 4 * channel, value)
            maximum = [max(0, int(f32(native.defense(c.addressof(native.target), channel)))) for channel in range(7)]
            # modifyDamage uses AC()/minimumAC for physical, not damageDefense(0).
            maximum[0] = native.ac(c.addressof(native.target))
            percentages = [native.defense_percent(c.addressof(native.target), channel) for channel in range(7)]
            add('defense', f'D {armor} {defense} ' + ' '.join(map(str, elements)) + f' {effect_text(effects)}', maximum + percentages)

        for i in range(6000):
            base = rng.choice([0, 1, 2, 3, 10, 100, 999])
            bonus = [0] * 7
            for _ in range(rng.randrange(5)):
                bonus[rng.randrange(7)] = rng.randrange(1, 50)
            strength, dexterity, magic = [rng.randrange(100) for _ in range(3)]
            armor, defense = rng.randrange(50), rng.randrange(50)
            elements = [rng.randrange(50) for _ in range(7)]
            flags, seed = rng.randrange(16), rng.randrange(1, 2 ** 32)
            ae, te = [], []
            if i >= 100:
                for _ in range(rng.randrange(7)):
                    kind = rng.choice([0, 1, 3, 10, 15, 16, 18, 25, 69, 70, 71, 72, 99, 102, 103])
                    channel = rng.randrange(7) if kind in (10, 25) else 7
                    ae.append((kind, channel, f32(rng.uniform(0, 60))))
                for _ in range(rng.randrange(7)):
                    kind = rng.choice([2, 8, 17, 23, 26, 35, 36, 37, 38, 39, 40, 66])
                    channel = rng.randrange(7) if kind in (23, 26) else 7
                    te.append((kind, channel, f32(rng.uniform(-10, 40) if kind == 26 else rng.uniform(0, 40))))
            result, state = native.run(base, bonus, strength, dexterity, magic, ae, armor, defense, elements, te, seed,
                                      [value for bit, value in enumerate([0x23, 0xa2, 0xa3, 0xa4]) if flags & (1 << bit)])
            pairs, maximum, rolled, applied = result
            add('ordinary_channel_roll', f'R {base} {strength} {dexterity} {magic} {flags} {armor} {defense} {seed} '
                + ' '.join(map(str, bonus + elements)) + f' {effect_text(ae)} {effect_text(te)}',
                [len(pairs), maximum, rolled, applied, state] + [value for pair in pairs for value in pair])

        run = subprocess.run([str(args.probe.resolve())], input=''.join(inputs), text=True,
                             capture_output=True, check=True, timeout=90)
        actual = [list(map(int, line.split())) for line in run.stdout.splitlines()]
        if len(actual) != len(expected):
            raise AssertionError(f'Row count: port={len(actual)}, original={len(expected)}')
        mismatch = [i for i, pair in enumerate(zip(actual, expected)) if pair[0] != pair[1]]
        if mismatch:
            i = mismatch[0]
            raise AssertionError({'case': i, 'input': inputs[i].strip(), 'expected': expected[i],
                                  'actual': actual[i], 'mismatches': len(mismatch)})
        report = {
            'passed': True, 'original_sha256': native.original.sha256,
            'comparisons': len(expected), 'groups': groups, 'generator_seed': 43286,
            'input_sha256': hashlib.sha256(''.join(inputs).encode()).hexdigest(),
            'expected_sha256': hashlib.sha256(json.dumps(expected, separators=(',', ':')).encode()).hexdigest(),
            'functions_and_slices': native.evidence,
            'scope': 'Integer weapon graph split; MAGIC getter; resolved armor/percentage; ordinary right-hand damage through ordered channel assembly and volatile RNG. No original game launch.',
            'controlled_inputs': 'Constructed memory objects, evaluated effect contributions, one right-hand weapon/type queries; critical=false, no reflect or absorb-shield.',
            'excluded': ['Dual-hand selection/shield special case', 'Effect lifecycle/affixes/sockets', 'Critical/glancing/block/procs', 'Missiles/weapon skills', 'Actual HP, loot, UI or campaign in original executable'],
            'domain': 'Finite binary32, supported positive graph/bonus range, int32-safe evaluated sums; allocation percentages may be negative for original default/skip branches.'
        }
        if args.output:
            args.output.parent.mkdir(parents=True, exist_ok=True)
            args.output.write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n')
        print(json.dumps(report, ensure_ascii=False, indent=2))
        return 0
    finally:
        native.close()


if __name__ == '__main__':
    raise SystemExit(main())
