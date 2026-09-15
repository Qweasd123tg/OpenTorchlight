#!/usr/bin/env python3
"""Deterministic synthetic item-cycle PAK; contains NO extracted game assets."""
from __future__ import annotations
import argparse
import struct
import zipfile
from pathlib import Path
from make_ai_cooldown_fixture import adm, monster


def group(name, props=(), children=()):
    return name, list(props), list(children)


def triangle_mesh():
    def chunk(tag, payload):
        return struct.pack('<HI', tag, len(payload) + 6) + payload
    element = chunk(0x5110, struct.pack('<5H', 0, 2, 1, 0, 0))
    data = struct.pack('<9f', 0, 0, 0, 1, 0, 0, 0, 0, 1)
    geometry = chunk(0x5000, struct.pack('<I', 3) + chunk(0x5100, element)
                     + chunk(0x5200, struct.pack('<HH', 0, 12) + chunk(0x5210, data)))
    submesh = chunk(0x4000, b'FixtureMaterial\n' + struct.pack('<?I?3H', True, 3, False, 0, 1, 2))
    return struct.pack('<H', 0x1000) + b'[MeshSerializer_v1.40]\n' + chunk(0x3000, b'\0' + geometry + submesh)


def write_fixture(destination: Path):
    records, units = [], []
    def add(name, kind, unit_type, properties=(), children=(), create_as=None):
        guid = 1000 + len(records)
        create_as = create_as or ('EQUIPMENT' if kind == 'ITEMS' else 'MONSTER')
        values = [('NAME', 5, name), ('DISPLAYNAME', 8, name), ('UNIT_GUID', 5, str(guid)),
                  ('CREATEAS', 5, create_as), ('LEVEL', 1, 1), ('RARITY', 1, 1),
                  ('RESOURCEDIRECTORY', 5, 'media/synthetic/'), ('MESHFILE', 5, name)]
        values.extend(properties)
        records.append(group(kind, [('UNIT_GUID', 5, str(guid)), ('UNITTYPE', 5, unit_type),
            ('FILEITEM', 5, name), ('DATFILE', 5, f'media/units/{name}.dat'),
            ('NAME', 5, name), ('DISPLAYNAME', 8, name), ('DONTCREATE', 6, False), ('RESOURCEGROUP', 4, 0)]))
        units.append((name, group('UNIT', values, children)))
    def treasure(name, low=None, high=None):
        values = [('SPAWNCLASS', 5, name)]
        if low is not None: values.append(('MIN', 1, low))
        if high is not None: values.append(('MAX', 1, high))
        return group('TREASURE', values)
    monster_values = monster()[1]
    add('EXPLICIT', 'MONSTERS', 'MONSTER', monster_values, [treasure('CYCLE_LOOT')])
    add('DEFAULT', 'MONSTERS', 'MONSTER', monster_values)
    add('EMPTY', 'MONSTERS', 'MONSTER', monster_values, [treasure('EMPTY_LOOT')])
    add('ZERO', 'MONSTERS', 'MONSTER', monster_values, [treasure('CYCLE_LOOT', 0, 0)])
    add('REVERSED', 'MONSTERS', 'MONSTER', monster_values, [treasure('ONE_SWORD', 2, 1)])
    add('INHERITED', 'MONSTERS', 'MONSTER', [('BASEFILE', 5, 'media/units/EXPLICIT.dat')])
    # Original GetDataGroupByName returns the FIRST child group after BASEFILE appends groups.
    add('DUPLICATE_GROUP', 'MONSTERS', 'MONSTER', [('BASEFILE', 5, 'media/units/EXPLICIT.dat')],
        [treasure('EMPTY_LOOT')])
    add('MISSING_CLASS', 'MONSTERS', 'MONSTER', monster_values, [treasure('MISSING')])
    for name, damage, speed, reach in [('SWORD_A', 20, 50, 2), ('SWORD_B', 40, 200, 4)]:
        add(name, 'ITEMS', 'SWORD', [('MINDAMAGE', 1, damage), ('MAXDAMAGE', 1, damage),
            ('SPEED', 1, speed), ('RANGE', 2, reach), ('STRIKERANGE', 2, reach)])
    for name, unit_type, armor in [('CHEST_A', 'NORMAL CHEST ARMOR', 10),
                                    ('CHEST_B', 'NORMAL CHEST ARMOR', 30), ('BELT', 'NORMAL BELT', 5)]:
        add(name, 'ITEMS', unit_type, [('ARMORMIN', 1, armor), ('ARMORMAX', 1, armor),
            ('ARMOR_PHYSICAL', 1, 100), ('ARMOR_FIRE', 1, 50)])
    add('TOKEN', 'ITEMS', 'TRINKET')
    add('INHERITED_ITEM', 'ITEMS', 'SWORD', [('BASEFILE', 5, 'media/units/SWORD_A.dat')])
    # Master metadata deliberately omits CREATEAS, and this UNIT inherits it.
    name, child = units[-1]
    units[-1] = (name, group(child[0], [p for p in child[1] if p[0] != 'CREATEAS'], child[2]))
    add('GOLD', 'ITEMS', 'GOLD', create_as='GOLD')
    def leaf(key, name, weight=-1):
        return group('OBJECT', [(key, 5, name), ('WEIGHT', 1, weight)])
    tables = {
        'CYCLE_LOOT': [leaf('SPAWNCLASS', 'SWORDS'), leaf('UNIT', 'CHEST_A'),
                       leaf('UNIT', 'CHEST_B'), leaf('UNITTYPE', 'BELT'), leaf('UNIT', 'TOKEN')],
        'SWORDS': [leaf('UNIT', 'SWORD_A'), leaf('UNIT', 'SWORD_B')],
        'ONE_SWORD': [leaf('UNIT', 'SWORD_A')],
        'BARREL_TREASURE': [leaf('UNIT', 'TOKEN')], 'EMPTY_LOOT': [leaf('UNITTYPE', 'NONE')],
    }
    def graph(value): return adm(group('LINE', children=[group('POINT', [('X', 2, 1), ('Y', 2, value)])]))
    destination.parent.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(destination, 'w', zipfile.ZIP_STORED) as z:
        def write(path, data): z.writestr(zipfile.ZipInfo(path, (1980,1,1,0,0,0)), data)
        write('media/master.adm', adm(group('UNITS', children=records)))
        write('media/MASTERRESOURCEUNITS.DAT.ADM', adm(group('UNITS', children=records)))
        for name, unit in units:
            write(f'media/units/{name}.dat.adm', adm(unit))
            write(f'media/synthetic/{name}.mesh', triangle_mesh())
        types = [group('MONSTER', [('ID',1,1)]), group('WEAPON', [('ID',1,8)]), group('SWORD', [('ID',1,2),('CHILD0',1,8)]),
                 group('CHEST ARMOR', [('ID',1,3)]), group('NORMAL CHEST ARMOR',[('ID',1,4),('CHILD0',1,3)]),
                 group('BELT', [('ID',1,5)]), group('NORMAL BELT',[('ID',1,6),('CHILD0',1,5)]),
                 group('TRINKET',[('ID',1,7)]), group('GOLD',[('ID',1,9)])]
        write('media/UNITTYPES.HIE.adm',adm(group('HIERACHY',children=[group('UNITTYPES',children=types)])))
        for name, objects in tables.items():
            write(f'media/spawnclasses/{name}.dat.adm',adm(group('SPAWNCLASS',[('NAME',5,name)],objects)))
        for name in ('HEALTH_MONSTER_BYLEVEL','DAMAGE_MONSTER','ARMOR_MONSTER_BYLEVEL',
                     'ARMOR_PLAYER_BYLEVEL_FORSET','BASE_WEAPON_DAMAGE'):
            write(f'media/graphs/stats/{name}.DAT.adm',graph(100))
        write('media/graphs/stats/ITEM_SPAWN_RANGE_MINIMUM.DAT.adm',graph(1))
        write('media/graphs/stats/ITEM_SPAWN_RANGE_MAXIMUM.DAT.adm',graph(10))
    print(f'Synthetic item fixture: {len(units)} units, {len(tables)} tables; no game assets')

if __name__ == '__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('output',type=Path)
    write_fixture(parser.parse_args().output)
