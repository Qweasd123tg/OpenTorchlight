#!/usr/bin/env python3
"""Authored hostile spawn tables and resources; no original game content."""
from pathlib import Path
import sys
import zipfile
from make_attack_fixture import write_fixture
from make_ai_cooldown_fixture import adm

def write(destination: Path):
    write_fixture(destination, with_rewards=True, with_consumables=True)
    with zipfile.ZipFile(destination) as source:
        entries = {n: source.read(n) for n in source.namelist()}
    def table(name, objects):
        entries[f'media/spawnclasses/{name}.dat.adm'] = adm(('SPAWNCLASS', [('NAME', 5, name)], objects))
    def entry(unit, key='UNIT', weight=1):
        return ('OBJECT', [(key,5,unit),('WEIGHT',1,weight),('MINCOUNT',1,1),('MAXCOUNT',1,1)], [])
    table('POPULATION', [entry('REWARD_DUMMY'), entry('INNATE')])
    table('ZERO_REQUIRED', [entry('INNATE',weight=0)])
    table('DEFAULT_REQUIRED', [('OBJECT',[('UNIT',5,'INNATE'),('MINCOUNT',1,0),('MAXCOUNT',1,0)],[])])
    table('INVALID_POPULATION', [entry('MISSING')])
    table('UNSAFE_POPULATION', [entry('HP_POTION')])
    table('RANDOM_POPULATION', [entry('POPULATION','SPAWNCLASS')])
    table('FAIL_POPULATION', [entry('NAN_UNIT')])
    with zipfile.ZipFile(destination,'w',zipfile.ZIP_DEFLATED) as target:
        for name,data in entries.items(): target.writestr(name,data)
if __name__ == '__main__': write(Path(sys.argv[1]))
