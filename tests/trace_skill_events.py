#!/usr/bin/env python3
"""Trace bounded original startSkill/triggerEvent; do not launch the game.

External startEvent is a recording sink, not a simulated implementation.
See research/skill-event-native-trace.md for the explicit object/branch scope.
"""
import argparse
import ctypes as c
import hashlib
import json
import os
from pathlib import Path
import platform
import struct
import time
import zipfile

from native_typed_reference import Memory, Original
from audit_gameplay_resources import adm


def put(obj, offset, fmt, *values):
    struct.pack_into('<' + fmt, obj, offset, *values)


def get(obj, offset, fmt):
    return struct.unpack_from('<' + fmt, obj, offset)[0]


class Trace(Memory):
    def __init__(self, original):
        super().__init__()
        self.original = Original(original)
        self.evidence = []
        try:
            for name, address in (
                ('CSkill::startSkill(CBaseUnit*, ESKILL_ACTIVATION_TYPE, Ogre::Vector3 const&, Ogre::Quaternion const&, Ogre::Vector3 const&, CBaseUnit*)', 0xca9150),
                ('CSkill::triggerEvent(ESKILL_EVENT_TYPE, Ogre::Vector3 const&, Ogre::Quaternion const&, CBaseUnit*, Ogre::Vector3 const*)', 0xca5950),
            ):
                symbol = self.original.symbol(name, address)
                raw = self.original.read(address, symbol.size)
                self.put(address, raw)
                self.evidence.append({'symbol': name, 'address': hex(address),
                                      'size': len(raw), 'sha256': hashlib.sha256(raw).hexdigest()})
            ptr = c.c_void_p
            for address, name in ((0xca4a00, 'assignSkillAnimations'),
                                  (0xca7740, 'calculateEffectiveSkillLevel')):
                self.callback(address, c.CFUNCTYPE(None, ptr),
                              lambda obj, name=name: self.calls.append(name))

            def chance(obj):
                self.calls.append('rollSkillChance')
                return self.chance

            def cooldown(obj):
                self.calls.append('getCoolDown')
                return 1.25

            def event(obj, caster, prop):
                self.calls.append('startEvent:' + self.names[obj])
                self.sinks.append({'event': self.names[obj],
                                   'active': bool(get(self.skill, 0x64, 'B')),
                                   'cooldown': get(self.skill, 0xfc, 'f'),
                                   'active_count_before_append': get(self.skill, 0xc0, 'I'),
                                   'caster_matches': caster == c.addressof(self.caster),
                                   'property_matches': prop == c.addressof(self.prop)})

            self.callback(0xc9db70, c.CFUNCTYPE(c.c_bool, ptr), chance)
            self.callback(0xcdd1f0, c.CFUNCTYPE(c.c_float, ptr), cooldown)
            # SysV integer registers are first three pointers; vector SSE and
            # trailing pointer arguments are intentionally not inspected.
            self.callback(0xcc4300, c.CFUNCTYPE(None, ptr, ptr, ptr), event)
            self.protect()
            self.start = c.CFUNCTYPE(c.c_bool, ptr, ptr, c.c_uint, ptr, ptr, ptr, ptr)(0xca9150)
            self.trigger = c.CFUNCTYPE(c.c_bool, ptr, c.c_uint, ptr, ptr, ptr, ptr)(0xca5950)
        except BaseException:
            self.close()
            raise

    def reset(self, groups, active=False):
        self.calls, self.sinks, self.names, self.keep = [], [], {}, []
        self.chance = True
        self.skill, self.caster, self.prop = (c.create_string_buffer(n) for n in (0x140, 0x200, 0x100))
        self.position = (c.c_float * 3)(1, 2, 3)
        self.quaternion = (c.c_float * 4)(1, 0, 0, 0)
        self.offset = (c.c_float * 3)(4, 5, 6)
        self.table, self.active_events = (c.c_void_p * 11)(), (c.c_void_p * 64)()
        for index, records in groups.items():
            entries = (c.c_void_p * len(records))()
            for i, (name, blocked, clone) in enumerate(records):
                record = c.create_string_buffer(0x228)
                put(record, 0x220, 'Q', int(blocked))
                put(record, 0x140, 'B', int(clone))
                self.names[c.addressof(record)] = name
                entries[i] = c.addressof(record)
                self.keep.append(record)
            vector = c.create_string_buffer(0x10)
            put(vector, 0, 'QII', c.addressof(entries), len(records), len(records))
            self.table[index] = c.addressof(vector)
            self.keep.extend((entries, vector))
        put(self.prop, 0x58, 'Q', c.addressof(self.table))
        put(self.prop, 0x64, 'I', 11)
        put(self.skill, 0x30, 'Q', c.addressof(self.caster))
        put(self.skill, 0x64, 'BB', int(active), 1)
        put(self.skill, 0x90, 'Q', c.addressof(self.prop))
        put(self.skill, 0xb8, 'QIII', c.addressof(self.active_events), 0, 64, 64)
        put(self.skill, 0x100, 'f', 2.5)
        put(self.skill, 0x108, 'f', 99)
        put(self.skill, 0x120, 'I', 3)

    def start_skill(self, caster=True):
        return bool(self.start(c.addressof(self.skill), c.addressof(self.caster) if caster else None,
                               0, self.position, self.quaternion, self.offset, None))

    def trigger_event(self, event):
        return bool(self.trigger(c.addressof(self.skill), event, self.position,
                                 self.quaternion, None, self.offset))

    def state(self):
        count = get(self.skill, 0xc0, 'I')
        return {'active': bool(get(self.skill, 0x64, 'B')),
                'cooldown': get(self.skill, 0xfc, 'f'),
                'events': [self.names[self.active_events[i]] for i in range(count)]}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original', type=Path, required=True)
    parser.add_argument('--pak', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    if platform.system() != 'Linux' or platform.machine() != 'x86_64' or os.sysconf('SC_PAGE_SIZE') != 4096:
        return 77
    began = time.monotonic()
    path = 'media/skills/vanquisher/seeking/SEEKING.DAT.adm'
    with zipfile.ZipFile(args.pak) as pak:
        raw = pak.read(path)
    rung = next(x for x in adm(raw)['children'] if x['group'] == 'LEVEL1')
    resources = {x['group']: x['properties']['FILE'] for x in rung['children']}
    assert resources['EVENT_START'].lower().endswith('/warmup.layout'), resources
    assert resources['EVENT_TRIGGER'].lower().endswith('/seeking.layout'), resources
    trace = Trace(args.original)
    cases = []

    def record(name, result):
        cases.append({'name': name, 'returned': result, 'calls': list(trace.calls),
                      'event_sinks': list(trace.sinks), 'state': trace.state()})

    try:
        records = {0: [('start', False, False)], 2: [('trigger', False, False)]}
        trace.reset(records)
        result = trace.start_skill(False)
        assert not result and not trace.calls and not trace.state()['active']
        record('null_caster', result)
        trace.reset(records)
        put(trace.skill, 0x90, 'Q', 0)
        result = trace.start_skill()
        assert not result and not trace.calls
        record('null_property', result)
        trace.reset(records)
        trace.chance = False
        result = trace.start_skill()
        setup = ['assignSkillAnimations', 'calculateEffectiveSkillLevel', 'rollSkillChance']
        assert not result and trace.calls == setup and not trace.state()['active']
        record('chance_failed', result)
        trace.reset(records)
        result = trace.start_skill()
        assert result and trace.calls == setup + ['getCoolDown', 'startEvent:start']
        assert trace.state() == {'active': True, 'cooldown': 1.25, 'events': ['start']}
        assert struct.unpack_from('<fff', trace.skill, 0x50) == (4, 5, 6)
        assert get(trace.prop, 0x50, 'I') == 3 and get(trace.skill, 0x65, 'B') == 0
        assert get(trace.skill, 0xf8, 'f') == 1 and get(trace.skill, 0x104, 'f') == 2.5
        assert get(trace.skill, 0x108, 'f') == 0
        assert trace.sinks[0] == {'event': 'start', 'active': True, 'cooldown': 1.25,
                                 'active_count_before_append': 0,
                                 'caster_matches': True, 'property_matches': True}
        record('start_only', result)
        result = trace.trigger_event(2)
        assert result and trace.state()['events'] == ['start', 'trigger']
        assert trace.sinks[-1]['active_count_before_append'] == 1
        record('separate_trigger', result)
        trace.reset({})
        result = trace.start_skill()
        assert result and trace.state()['active'] and not trace.sinks
        record('start_without_events_still_succeeds', result)
        for event in (0, 2, 6, 7, 11):
            trace.reset(records)
            result = trace.trigger_event(event)
            assert not result and not trace.calls
            record(f'inactive_{event}', result)
        trace.reset(records, active=True)
        result = trace.trigger_event(11)
        assert not result and not trace.calls
        record('invalid_event', result)
        trace.reset({6: [('blocked', True, False), ('first', False, False),
                         ('clone_ineligible', False, True), ('second', False, False)]}, active=True)
        result = trace.trigger_event(6)
        assert result and trace.state()['events'] == ['first', 'second']
        assert trace.calls == ['startEvent:first', 'startEvent:second']
        record('ordered_dispatch_and_skips', result)
        for active in (False, True):
            trace.reset({5: [('unit_die', False, False)],
                         8: [('die_by_effect', False, False)]}, active=active)
            result = trace.trigger_event(8)
            assert result and trace.state()['events'] == (['unit_die'] if active else []) + ['die_by_effect']
            record(f'die_by_effect_active_{active}', result)
        report = {'passed': True, 'original_sha256': trace.original.sha256,
                  'function_bodies': trace.evidence, 'cases': cases, 'case_count': len(cases),
                  'resource': {'path': path, 'sha256': hashlib.sha256(raw).hexdigest(),
                               'first_rung_event_files': resources},
                  'elapsed_seconds': round(time.monotonic() - began, 3),
                  'scope': 'Bounded original dispatch with controlled getters and startEvent sink; NOT port parity or full game execution.'}
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + '\n')
        print(f'PASS: {len(cases)} original dispatch cases; START warmup != TRIGGER seeking; {args.output}')
    finally:
        trace.close()
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
