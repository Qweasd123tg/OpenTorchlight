#!/usr/bin/env python3
"""Authored attack fixtures: tiny OGRE mesh/skeletons, UTF16 manifests and ADMs.
No original game bytes, textures, meshes, or extracted resources are included.
"""
from __future__ import annotations
import argparse
import struct
import zipfile
from pathlib import Path
from make_ai_cooldown_fixture import adm
from make_item_cycle_fixture import triangle_mesh, group


def chunk(kind, payload):
    return struct.pack('<HI', kind, len(payload) + 6) + payload


def skeleton(name=None, duration=1.0, endpoint=10.0):
    header = struct.pack('<H', 0x1000) + b'[Serializer_v1.10]\n'
    # v1.10 serializes the bone-name bytes outside the declared 36-byte size.
    bone = struct.pack('<HI', 0x2000, 36) + b'Root\n' + struct.pack('<H7f', 0, 0,0,0, 0,0,0,1)
    if name is None:
        return header + bone
    keys = b''
    for time, x in [(0.0, 0.0), (duration, endpoint)]:
        keys += chunk(0x4110, struct.pack('<8f', time, 0,0,0,1, x,0,0))
    track = chunk(0x4100, struct.pack('<H', 0) + keys)
    return header + bone + chunk(0x4000, name.encode() + b'\n' + struct.pack('<f', duration) + track)


def mesh():
    base = triangle_mesh()
    offset = base.index(b'\n') + 1
    payload = base[offset+6:]
    payload = b'\1' + payload[1:] + chunk(0x6000, b'Creature.skeleton\n')
    for vertex in range(3):
        payload += chunk(0x7000, struct.pack('<IHf', vertex, 0, 1))
    return base[:offset] + chunk(0x3000, payload)


def manifest(clips):
    lines = ['[ANIMATIONS]']
    for name, keys in clips:
        lines += ['[ANIMATION]', f'<STRING>FILE:{name}.skeleton']
        for event, frame in keys:
            lines += ['[KEY]', f'<STRING>NAME:{event}', f'<FLOAT>FRAME:{frame}', '[/KEY]']
        lines += ['[/ANIMATION]']
    lines += ['[/ANIMATIONS]']
    return b'\xff\xfe' + ('\n'.join(lines) + '\n').encode('utf-16-le')


def effect(name, value, **extra):
    props = [('TYPE',5,name),('ACTIVATION',5,'PASSIVE'),('DURATION',5,'ALWAYS'),
             ('MIN',2,value),('MAX',2,value)]
    for key, val in extra.items():
        props.append((key, 5 if isinstance(val,str) else 2, val))
    return group('EFFECT', props)


def write_fixture(path: Path):
    entries = {}
    units, records = [], []
    def add(name, category='MONSTERS', unit_type='MONSTER', props=(), children=(), directory='media/combat/'):
        guid = 5000 + len(records)
        standard = [('NAME',5,name),('DISPLAYNAME',8,name),('UNIT_GUID',5,str(guid)),
            ('CREATEAS',5,'EQUIPMENT' if category=='ITEMS' else 'PLAYER' if category=='PLAYERS' else 'MONSTER'),
            ('UNITTYPE',5,unit_type),('LEVEL',1,1),('RARITY',1,1),
            ('RESOURCEDIRECTORY',5,directory),('MESHFILE',5,'Creature')]
        standard += list(props)
        units.append((name,group('UNIT',standard,children)))
        records.append(group(category,[('UNIT_GUID',5,str(guid)),('UNITTYPE',5,unit_type),
            ('CREATEAS',5,'EQUIPMENT' if category=='ITEMS' else 'MONSTER'),
            ('FILEITEM',5,name),('DATFILE',5,f'media/units/{name}.dat'),('NAME',5,name),
            ('DISPLAYNAME',8,name),('DONTCREATE',6,False),('RESOURCEGROUP',4,0)]))
    base = [(k,2,v) for k,v in [('MINHP',100),('MAXHP',100),('MINDAMAGE',10),('MAXDAMAGE',10),
        ('ATTACKSPEED',999),('WALKINGSPEED',1),('RUNNINGSPEED',1),('SIGHT_RADIUS',10),
        ('FOLLOW_RADIUS',20),('REACH_BONUS',0),('ATTACK_RANGE',2),('STRIKE_RANGE',1),
        ('AI_ATTACKCOOLDOWN',.5),('COLLISION_RADIUS',.25)]]
    add('INNATE',props=base)
    equip=lambda **slots: group('EQUIPMENT',[(k,5,v) for k,v in slots.items()])
    add('ARMED',props=base,children=[equip(RIGHTHAND='SWORD')])
    add('LEFT',props=base,children=[equip(LEFTHAND='SWORD')])
    add('DUAL',props=base,children=[equip(RIGHTHAND='SWORD',LEFTHAND='LEFT_SWORD')])
    add('SPAWNED_WEAPON',props=base,children=[equip(SPAWNRIGHTHAND='SWORDS')])
    add('HASTE',props=base,children=[equip(RIGHTHAND='SWORD'),effect('FIXTURE_HASTE',100)])
    add('SLOW_RESIST',props=base,children=[equip(RIGHTHAND='SWORD'),
        effect('FIXTURE_HASTE',-80),effect('FIXTURE_SLOW_RESIST',50)])
    add('NO_UNARMED',props=base+[('NO_UNARMED_ATTACKS',6,True)])
    add('NO_CLIP',props=base, directory='media/empty/')
    add('NO_HIT',props=base, directory='media/nohit/')
    add('RANGED',props=base,children=[equip(RIGHTHAND='PISTOL')])
    add('INHERITED_HASTE',props=[('BASEFILE',5,'media/units/HASTE.dat')])
    add('MISSING_RANGE',props=[p for p in base if p[0]!='ATTACK_RANGE'])
    add('DEFAULT_RANGES',props=[p for p in base if p[0] not in ('ATTACK_RANGE','STRIKE_RANGE')])
    add('BAD_RANGE',props=[p for p in base if p[0]!='ATTACK_RANGE']+[('ATTACK_RANGE',5,'invalid')])
    add('CONDITIONAL',props=base,children=[effect('FIXTURE_HASTE',100,UNITTYPE='MONSTER')])
    for name, kind, damage, speed, cooldown in [('SWORD','SWORD',20,200,1.5),
                    ('LEFT_SWORD','SWORD',40,50,2.5),('PISTOL','PISTOL',20,100,0)]:
        add(name,'ITEMS',kind,[(k,1,v) for k,v in [('MINDAMAGE',damage),('MAXDAMAGE',damage),('SPEED',speed)]]+
            [('RANGE',2,2),('STRIKERANGE',2,1),('AI_ATTACKCOOLDOWN',2,cooldown)])
    add('HASTE_CHEST','ITEMS','NORMAL CHEST ARMOR',
        [('ARMORMIN',1,10),('ARMORMAX',1,10),('ARMOR_PHYSICAL',1,100)], [effect('FIXTURE_HASTE',50)])
    add('MANA_CHEST','ITEMS','NORMAL CHEST ARMOR',
        [('ARMORMIN',1,10),('ARMORMAX',1,10),('ARMOR_PHYSICAL',1,100)],
        [effect('FIXTURE_MANA_PERCENT',12.5),effect('FIXTURE_MANA_FLAT',0.2)])
    add('INVALID_MANA_CHEST','ITEMS','NORMAL CHEST ARMOR',
        [('ARMORMIN',1,999),('ARMORMAX',1,999),('ARMOR_PHYSICAL',1,100)],
        [effect('FIXTURE_MANA_PERCENT',1e20)])
    playerbase = [(k,2,v) for k,v in [('MINHP',100),('MAXHP',100),('ATTACKSPEED',777),
        ('WALKINGSPEED',1),('RUNNINGSPEED',1),('REACH_BONUS',0),('ATTACK_RANGE',2),('STRIKE_RANGE',1),
        ('COLLISION_RADIUS',.25)]] + [(k,1,v) for k,v in [('MINDAMAGE',10),('MAXDAMAGE',10),
        ('STRENGTH',6),('DEXTERITY',8),('MAGIC',0),('DEFENSE',0),('ARMOR',0),('GOLD',109)]] + [('HEALTH_GRAPH',5,'HEALTH_PLAYER')]
    add('TEST_PLAYER','PLAYERS','PLAYER',playerbase,[effect('FIXTURE_HASTE',50)])
    add('TEST_LEFT_PLAYER','PLAYERS','PLAYER',playerbase,[equip(LEFTHAND='SWORD')])
    # First player has no starting equipment: test UNIT effects independently of inventory.
    for name, definition in units: entries[f'media/units/{name}.dat.adm']=adm(definition)
    master=adm(group('UNITS',children=records))
    entries['media/master.adm']=master
    entries['media/MASTERRESOURCEUNITS.DAT.ADM']=master
    names={4:'FIXTURE_MANA_FLAT',0x13:'FIXTURE_MANA_PERCENT',0x16:'FIXTURE_HASTE',0x8c:'FIXTURE_SLOW_RESIST',0x0f:'FIXTURE_MELEE_PERCENT',
           0x47:'FIXTURE_STR_PERCENT',0x45:'FIXTURE_STR_FLAT',0x19:'FIXTURE_DAMAGE_PERCENT'}
    entries['media/EffectsList.dat.adm']=adm(group('EFFECTS',children=[
        group('EFFECT',[('NAME',5,names.get(i,f'UNUSED_{i:03}'))]) for i in range(145)]))
    # Valid lookalike is deliberately wrong. Only the pinned EffectsList path is authoritative.
    entries['media/decoy/effects.dat.adm']=adm(group('EFFECTS',children=[
        group('EFFECT',[('NAME',5,'FIXTURE_HASTE' if i==0 else f'DECOY_{i}')]) for i in range(145)]))
    types=[group(name,[('ID',1,id)]+[('CHILD'+str(n),1,p) for n,p in enumerate(parents)])
        for name,id,parents in [('MONSTER',1,()),('SWORD',2,(8,60)),('WEAPON',8,()),
            ('MELEE',60,()),('RANGED',35,(8,)),('PISTOL',90,(35,8)),('PLAYER',3,()),
            ('CHEST ARMOR',4,()),('NORMAL CHEST ARMOR',5,(4,))]]
    entries['media/UNITTYPES.HIE.adm']=adm(group('HIERACHY',children=[group('UNITTYPES',children=types)]))
    entries['media/spawnclasses/SWORDS.dat.adm']=adm(group('SPAWNCLASS',[('NAME',5,'SWORDS')],
        [group('OBJECT',[('UNIT',5,'SWORD')])]))
    for name, value in [('HEALTH_MONSTER_BYLEVEL',100),('HEALTH_PLAYER',100),('MANA_PLAYER_DESTROYER',30.25),('DAMAGE_MONSTER',100),
            ('ARMOR_MONSTER_BYLEVEL',100),('ARMOR_PLAYER_BYLEVEL_FORSET',100),('BASE_WEAPON_DAMAGE',100),
            ('ITEM_SPAWN_RANGE_MINIMUM',1),('ITEM_SPAWN_RANGE_MAXIMUM',10)]:
        entries[f'media/graphs/stats/{name}.DAT.adm']=adm(group('LINE',children=[group('POINT',[('X',2,1),('Y',2,value)])]))
    for directory in ['media/combat/','media/empty/','media/nohit/','media/mismatch/','media/unrelated/']:
        entries[directory+'Creature.mesh']=mesh()
        entries[directory+'Creature.skeleton']=skeleton()
    clips=[('ATTACK_A', [('HIT',6),('FOOTSTEP',9),('HIT',30)]),
        ('RSLASH_A',[('HIT',6),('FOOTSTEP',9),('HIT',12),('HIT',30)]),
        ('LSLASH_A',[('HIT',15)]), ('LPISTOL_A',[('HIT',10)])]
    entries['media/combat/Creature.animation']=manifest(clips)
    for index,(name,_) in enumerate(clips):
        entries[f'media/combat/{name}.skeleton']=skeleton(name,1,10*(index+1))
    entries['media/nohit/Creature.animation']=manifest([('ATTACK_EMPTY',[('FOOTSTEP',15)])])
    entries['media/nohit/ATTACK_EMPTY.skeleton']=skeleton('ATTACK_EMPTY')
    entries['media/mismatch/Creature.animation']=manifest([('ATTACK_FAKE',[('HIT',6)])])
    entries['media/mismatch/ATTACK_FAKE.skeleton']=skeleton('RSLASH_WRONG')
    entries['media/unrelated/Other.animation']=manifest([('ATTACK_A',[('HIT',6)])])
    entries['media/unrelated/ATTACK_A.skeleton']=skeleton('ATTACK_A')
    path.parent.mkdir(parents=True,exist_ok=True)
    with zipfile.ZipFile(path,'w',zipfile.ZIP_STORED) as archive:
        for name,data in sorted(entries.items()):
            archive.writestr(zipfile.ZipInfo(name,(1980,1,1,0,0,0)),data)
    print(f'Authored combat fixture: {len(units)} units, {len(entries)} files; no original assets')

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('output',type=Path)
    write_fixture(parser.parse_args().output)
