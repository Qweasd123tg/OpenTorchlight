#!/usr/bin/env python3
"""Build deterministic synthetic ADM/ZIP inputs, not extracted game assets."""
from __future__ import annotations

import argparse
import struct
import zipfile
from pathlib import Path


def adm(root: tuple) -> bytes:
    dictionary: dict[str, int] = {}

    def intern(text: str) -> None:
        if text not in dictionary:
            dictionary[text] = len(dictionary) + 1

    def visit(group: tuple) -> None:
        name, properties, children = group
        intern(name)
        for key, kind, value in properties:
            intern(key)
            if kind in (5, 8, 9):
                intern(value)
        for child in children:
            visit(child)

    def u32(value: int) -> bytes:
        return struct.pack('<I', value)

    def encode(group: tuple) -> bytes:
        name, properties, children = group
        data = u32(dictionary[name]) + u32(len(properties))
        formats = {1: '<i', 2: '<f', 3: '<d', 4: '<I', 6: '<I', 7: '<q'}
        for key, kind, value in properties:
            data += u32(dictionary[key]) + u32(kind)
            data += (u32(dictionary[value]) if kind in (5, 8, 9)
                     else struct.pack(formats[kind], value))
        return data + u32(len(children)) + b''.join(encode(c) for c in children)

    visit(root)
    result = u32(1) + u32(len(dictionary))
    for text, index in dictionary.items():
        raw = text.encode('utf-16-le')
        result += u32(index) + u32(len(raw) // 2) + raw
    return result + encode(root)


def monster(cooldown: float | None = None, equipment: tuple | None = None) -> tuple:
    values = [('MINHP', 100), ('MAXHP', 100), ('MINDAMAGE', 10),
              ('MAXDAMAGE', 10), ('ATTACKSPEED', 100), ('WALKINGSPEED', 1),
              ('RUNNINGSPEED', 1), ('SIGHT_RADIUS', 10), ('FOLLOW_RADIUS', 20),
              ('REACH_BONUS', 2), ('ATTACK_RANGE', 1), ('STRIKE_RANGE', 1)]
    if cooldown is not None:
        values.append(('AI_ATTACKCOOLDOWN', cooldown))
    return ('UNIT', [(name, 2, value) for name, value in values] + [('USEWEAPONDAMAGE', 6, False)],
            [] if equipment is None else [('EQUIPMENT', [equipment], [])])


def weapon(cooldown: float | None) -> tuple:
    properties = [('CREATEAS', 5, 'EQUIPMENT'), ('RANGE', 2, 1), ('SPEED', 1, 400)]
    if cooldown is not None:
        properties.append(('AI_ATTACKCOOLDOWN', 2, cooldown))
    return ('UNIT', properties, [])


def inherited(base: str, cooldown: float | None = None) -> tuple:
    properties = [('BASEFILE', 5, f'media/units/{base}.dat')]
    if cooldown is not None:
        properties.append(('AI_ATTACKCOOLDOWN', 2, cooldown))
    return ('UNIT', properties, [])


def write_fixture(destination: Path) -> None:
    units = [
        ('DEFAULT', monster()), ('FAST', monster(0)), ('SLOW', monster(2)),
        ('INHERITED', inherited('SLOW')), ('OVERRIDE', inherited('SLOW', 0.5)),
        ('ARMED', monster(1.5, ('RIGHTHAND', 5, 'COOLDOWN_SWORD'))),
        ('LEFT_ARMED', monster(1.5, ('LEFTHAND', 5, 'COOLDOWN_SWORD'))),
        ('SPAWN_ARMED', monster(1.5, ('SPAWNRIGHTHAND', 5, 'SYNTHETIC_SWORDS'))),
        ('WEAPON_ONLY', monster(0, ('RIGHTHAND', 5, 'COOLDOWN_SWORD'))),
        ('DEFAULT_WEAPON', monster(0, ('RIGHTHAND', 5, 'DEFAULT_SWORD'))),
        ('NEGATIVE_WEAPON', monster(0.5, ('RIGHTHAND', 5, 'NEGATIVE_SWORD'))),
        ('NEGATIVE_UNIT', monster(-0.25, ('RIGHTHAND', 5, 'COOLDOWN_SWORD'))),
        ('NAN_UNIT', monster(float('nan'))), ('INF_UNIT', monster(float('inf'))),
        ('NAN_WEAPON', monster(0, ('RIGHTHAND', 5, 'NAN_SWORD'))),
        ('INF_WEAPON', monster(0, ('RIGHTHAND', 5, 'INF_SWORD'))),
    ]
    items = [('COOLDOWN_SWORD', weapon(0.5)), ('DEFAULT_SWORD', weapon(None)),
             ('NEGATIVE_SWORD', weapon(-3)), ('NAN_SWORD', weapon(float('nan'))),
             ('INF_SWORD', weapon(float('inf')))]
    records = []
    definitions = []
    for category, kind, source in [('MONSTERS', 'MONSTER', units),
                                    ('ITEMS', 'SWORD', items)]:
        for name, definition in source:
            records.append((category, [
                ('UNIT_GUID', 5, str(100 + len(records))), ('UNITTYPE', 5, kind),
                ('CREATEAS', 5, 'EQUIPMENT' if category == 'ITEMS' else 'MONSTER'),
                ('FILEITEM', 5, name), ('DATFILE', 5, f'media/units/{name}.dat'),
                ('NAME', 5, name), ('DONTCREATE', 6, False), ('RESOURCEGROUP', 4, 0)], []))
            root, properties, children = definition
            definitions.append((name, (root, properties + [
                ('UNIT_GUID', 5, str(99 + len(records)))], children)))
    graph = adm(('LINE', [], [('POINT', [('X', 2, 1), ('Y', 2, 100)], [])]))
    graph_names = ('HEALTH_MONSTER_BYLEVEL', 'DAMAGE_MONSTER', 'ARMOR_MONSTER_BYLEVEL',
                   'ARMOR_PLAYER_BYLEVEL_FORSET', 'BASE_WEAPON_DAMAGE',
                   'ITEM_SPAWN_RANGE_MINIMUM', 'ITEM_SPAWN_RANGE_MAXIMUM')
    destination.parent.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(destination, 'w', zipfile.ZIP_STORED) as archive:
        def write(path: str, data: bytes) -> None:
            entry = zipfile.ZipInfo(path, date_time=(1980, 1, 1, 0, 0, 0))
            archive.writestr(entry, data)
        for name in graph_names:
            write(f'media/graphs/stats/{name}.DAT.adm', graph)
        write('media/UNITTYPES.HIE.adm', adm(('HIERACHY', [], [
            ('UNITTYPES', [], [('MONSTER', [('ID', 1, 1)], []),
                              ('WEAPON', [('ID', 1, 8)], []),
                              ('SWORD', [('ID', 1, 2), ('CHILD0', 1, 8)], [])]) ])))
        write('media/master.adm', adm(('UNITS', [], records)))
        write('media/spawnclasses/SYNTHETIC_SWORDS.dat.adm', adm((
            'SPAWNCLASS', [('NAME', 5, 'SYNTHETIC_SWORDS')], [
                ('OBJECT', [('UNIT', 5, 'COOLDOWN_SWORD')], [])])))
        for name, definition in definitions:
            write(f'media/units/{name}.dat.adm', adm(definition))
    print(f'Synthetic AI cooldown fixture: {len(definitions)} UNIT definitions')


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('output', type=Path)
    args = parser.parse_args()
    write_fixture(args.output)


if __name__ == '__main__':
    main()
