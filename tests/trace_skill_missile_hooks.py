#!/usr/bin/env python3
"""Execute original missileApplyingEffects with recording external call gates.

This proves call order and forwarded arguments, not implementations of the
intercepted weapon/effect/hit-skill functions, collision or target eligibility.
No original game process, saves or resource files are modified.
"""
import argparse
import ctypes as c
import hashlib
import json
import os
from pathlib import Path
import platform
import struct

from native_typed_reference import Memory, Original


class Trace(Memory):
    def __init__(self, path):
        super().__init__()
        try:
            self.original = Original(path)
            name = ('CSkillEvent::missileApplyingEffects(CMissile*, CCharacter*, '
                    'Ogre::Vector3 const*, float, float)')
            symbol = self.original.symbol(name, 0xcb8360)
            raw = self.original.read(symbol.address, symbol.size)
            self.put(symbol.address, raw)
            self.evidence = {'symbol': name, 'address': hex(symbol.address),
                             'size': symbol.size, 'sha256': hashlib.sha256(raw).hexdigest()}
            ptr, cf = c.c_void_p, c.CFUNCTYPE

            # SysV Vector3 return is xmm0=(x,y), xmm1=z. ctypes cannot return
            # this aggregate from a callback, so the controlled position
            # getter is a tiny constant-return ABI stub, not original code.
            position_stub = (b'\x48\xb8' + struct.pack('<ff', 1, 2) +
                             b'\x66\x48\x0f\x6e\xc0\xb8' + struct.pack('<f', 3) +
                             b'\x66\x0f\x6e\xc8\xc3')
            self.put(0x9e7080, position_stub)

            def gate(event, position, victim):
                self.calls.append('canEffectPosObject')
                self.forwarded['gate'] = {'position': list(struct.unpack('<fff', c.string_at(position, 12))),
                                          'event_matches': event == c.addressof(self.event),
                                          'victim_matches': victim == c.addressof(self.victim)}
                return self.allowed

            def orientation(obj):
                self.calls.append('getOrientation')
                return c.addressof(self.quaternion)

            def trigger(skill, kind, position, quaternion, victim, offset):
                self.calls.append('triggerEvent:' + str(kind))
                self.forwarded['trigger'] = {'skill_matches': skill == c.addressof(self.skill),
                    'victim_matches': victim == c.addressof(self.victim), 'offset_null': offset is None,
                    'position': list(struct.unpack('<fff', c.string_at(position, 12))),
                    'quaternion_matches': quaternion == c.addressof(self.quaternion)}
                return True

            def weapon(event, victim, item, scale, soak, missile, reflected):
                self.calls.append('applyWeaponDamage')
                self.forwarded['weapon'] = {'event_matches': event == c.addressof(self.event),
                    'victim_matches': victim == c.addressof(self.victim), 'item_null': item is None,
                    'scale': scale, 'soak': soak, 'missile': missile, 'reflected': reflected}
                return self.weapon_result

            def effects(event, victim, position, reflected):
                self.calls.append('applyEffects')
                self.forwarded['effects'] = {'event_matches': event == c.addressof(self.event),
                    'victim_matches': victim == c.addressof(self.victim),
                    'position_matches': position == c.addressof(self.position), 'reflected': reflected}
                return self.effects_result

            def hit(event, victim):
                self.calls.append('invokeHitSkills')
                self.forwarded['hit'] = {'event_matches': event == c.addressof(self.event),
                                         'victim_matches': victim == c.addressof(self.victim)}

            self.callback(0xcb7240, cf(c.c_bool, ptr, ptr, ptr), gate)
            self.callback(0x02001000, cf(ptr, ptr), orientation)
            self.callback(0xca5950, cf(c.c_bool, ptr, c.c_uint, ptr, ptr, ptr, ptr), trigger)
            self.callback(0xcb7b70, cf(c.c_uint, ptr, ptr, ptr, c.c_float, c.c_float, c.c_bool, c.c_bool), weapon)
            self.callback(0xcb7850, cf(c.c_uint, ptr, ptr, ptr, c.c_bool), effects)
            self.callback(0xcb7290, cf(None, ptr, ptr), hit)
            self.protect()
            self.invoke = cf(c.c_uint, ptr, ptr, ptr, ptr, c.c_float, c.c_float)(0xcb8360)
        except BaseException:
            self.close()
            raise

    def run(self, allowed=True, reflected=False, source_event=2, has_skill=True,
            weapon_result=1, effects_result=2):
        self.calls, self.forwarded = [], {}
        self.allowed, self.weapon_result, self.effects_result = allowed, weapon_result, effects_result
        self.event, self.missile, self.victim, self.skill, self.node = (
            c.create_string_buffer(size) for size in (0x228, 0x300, 0x100, 0x140, 8))
        self.quaternion = (c.c_float * 4)(1, 0, 0, 0)
        self.position = (c.c_float * 3)(4, 5, 6)
        self.vtable = (c.c_void_p * 26)()
        self.vtable[25] = 0x02001000
        struct.pack_into('<Q', self.node, 0, c.addressof(self.vtable))
        struct.pack_into('<Q', self.missile, 0x58, c.addressof(self.node))
        struct.pack_into('<?', self.missile, 0x294, reflected)
        struct.pack_into('<Q', self.event, 0x28, c.addressof(self.skill) if has_skill else 0)
        struct.pack_into('<I', self.event, 0x48, source_event)
        returned = self.invoke(c.addressof(self.event), c.addressof(self.missile),
                               c.addressof(self.victim), self.position, .4, .6)
        return {'returned': returned, 'calls': self.calls, 'forwarded': self.forwarded}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    if platform.system() != 'Linux' or platform.machine() != 'x86_64' or os.sysconf('SC_PAGE_SIZE') != 4096:
        return 77
    trace = Trace(args.original)
    cases = []
    try:
        tail = ['applyWeaponDamage', 'applyEffects', 'invokeHitSkills']
        for name, options in [('normal', {}), ('canEffect-refused', {'allowed': False}),
                              ('reflected', {'reflected': True}), ('source-event6', {'source_event': 6}),
                              ('no-parent-skill', {'has_skill': False}),
                              ('both-appliers-false', {'weapon_result': 0, 'effects_result': 0})]:
            result = trace.run(**options)
            expected = ['canEffectPosObject']
            if options.get('allowed', True):
                if not options.get('reflected') and options.get('source_event', 2) != 6 and options.get('has_skill', True):
                    expected += ['getOrientation', 'triggerEvent:6']
                expected += tail
            assert result['calls'] == expected, (name, result)
            expected_return = ((options.get('weapon_result', 1) | options.get('effects_result', 2))
                               if options.get('allowed', True) else 0)
            assert result['returned'] == expected_return, (name, result)
            forwarded = result['forwarded']
            assert forwarded['gate'] == {'position': [1, 2, 3], 'event_matches': True, 'victim_matches': True}
            if 'weapon' in forwarded:
                weapon = forwarded['weapon']
                assert all(weapon[k] for k in ('event_matches', 'victim_matches', 'item_null', 'missile'))
                assert weapon['reflected'] == options.get('reflected', False)
                assert abs(weapon['scale'] - .4) < 1e-6 and abs(weapon['soak'] - .6) < 1e-6
                assert all(forwarded['effects'][k] for k in ('event_matches', 'victim_matches', 'position_matches'))
                assert forwarded['effects']['reflected'] == options.get('reflected', False)
                assert all(forwarded['hit'].values())
            if 'trigger' in forwarded:
                assert forwarded['trigger'] == {'skill_matches': True, 'victim_matches': True,
                    'offset_null': True, 'position': [1, 2, 3], 'quaternion_matches': True}
            cases.append({'name': name, 'inputs': options, **result})
        report = {'status': 'PASS', 'elf_sha256': trace.original.sha256,
                  'function': trace.evidence, 'cases': cases,
                  'scope': 'Unchanged original missileApplyingEffects; external call gates are recording fixtures.',
                  'excluded': ['canEffect eligibility', 'weapon damage arithmetic and HP delivery',
                               'applyEffects and invokeHitSkills internals', 'collision', 'whole game execution']}
        args.output.write_text(json.dumps(report, indent=2) + '\n')
        print('PASS native missileApplyingEffects hook order: ' + str(len(cases)) + ' cases')
    finally:
        trace.close()
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
