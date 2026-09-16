#!/usr/bin/env python3
"""Reproducible evidence-bounded coverage and callgraph frontier. No code execution.
A decompiled file alone never promotes a function. Statuses come ONLY from the
reviewed boundary annotations; callgraph degree is a priority hint, not coverage.
"""
from __future__ import annotations
import argparse,csv,hashlib,io,json,math,re
from collections import defaultdict,deque
from pathlib import Path

STATUSES={'unseen','researched','partial','implemented','verified','closed'}
VERIFICATION_GROUPS=('core','assets','reference','render','desktop')
SYMBOL=re.compile(r'^([0-9a-fA-F]+) (?:([0-9a-fA-F]+) )?([TtWw]) (.+)$')
ROOTS=('CGame::update(', 'CGameClient::updateIngame(', 'CGameClient::loadMenuLevel(',
       'CGameClient::saveCharacter(', 'CGameClient::loadCharacter(', 'CGameClient::performWarp(',
       'CCharacter::performAttack(', 'CCharacter::getItem(', 'CInteract::interactWithUnit(')
SUBSYSTEMS=[('frontend',r'CGameUI|CGameState|CMainMenu|CCharacterCreate|CCharacterLoad|CUI|CGame::'),
 ('save',r'CCharacterSaveState|CItemSaveState|CLevelState|CPlayerSaveState|Save|saveCharacter|loadCharacter'),
 ('interaction',r'CInteract|CMerchant|CStash|CQuest|CDialog|CTriggerUnit|CNPC'),
 ('ranged',r'CMissile|CProjectile|fireMissiles|doWeaponSkill'),
 ('effects_skills',r'CEffect|CSkill|CAffix|CEnchant|CFlags'),
 ('world',r'CLevel|CUnitSpawner|CLogic|CTimeline|CDungeon|CWarper|CLayout'),
 ('items',r'CItem|CEquipment|CInventory|CTreasure|CSpawnClass'),
 ('combat',r'CCharacter|CMonster|CPlayer|CAttack'),
 ('render_animation',r'CGenericModel|CCamera|CRender|CParticle|Ogre::'),
 ('audio',r'CSound|CAudio'),('resources',r'CResource|CDataGroup|CGraph|CUnitResource')]

def subsystem(name):
    return next((area for area,pattern in SUBSYSTEMS if re.search(pattern,name)), 'other')
def generate(root):
    inputs=[root/'research/original-symbols.txt',root/'research/original-callgraph.tsv',root/'research/coverage-boundaries.json']
    annotations=json.loads(inputs[2].read_text())
    functions={}
    for line in inputs[0].read_text().splitlines():
        m=SYMBOL.match(line)
        if not m:continue
        address=int(m[1],16);name=m[4]
        row=functions.setdefault(address,{'address':f'0x{address:08x}','aliases':set()})
        row['aliases'].add(name)
    incoming=defaultdict(set);outgoing=defaultdict(set)
    with inputs[1].open(newline='') as stream:
        for row in csv.DictReader(stream,delimiter='\t'):
            source,target=int(row['caller_address'],16),int(row['callee_address'],16)
            if source!=target:outgoing[source].add(target);incoming[target].add(source)
    distance={};queue=deque()
    for address,row in functions.items():
        if any(any(name.startswith(prefix) for prefix in ROOTS) for name in row['aliases']):distance[address]=0;queue.append(address)
    while queue:
        a=queue.popleft()
        if distance[a]>=4:continue
        for b in incoming[a]|outgoing[a]:
            if b not in distance:distance[b]=distance[a]+1;queue.append(b)
    boundaries={}
    for a in annotations['boundaries']:
        status=a['status']
        if status not in STATUSES:raise ValueError('bad status: '+status)
        for field in ['evidence','implementation','tests']:
            for value in a.get(field,[]):
                file=value.split('#',1)[0]
                if not (root/file).is_file():raise ValueError('missing coverage input: '+file)
        if status in {'verified','closed'} and not a.get('comparison'):raise ValueError('verified requires explicit comparison boundary')
        if status=='closed' and not a.get('tests'):raise ValueError('closed requires regression tests')
        for address in a.get('addresses',[]):
            address=int(address,16)
            if address not in functions:raise ValueError('unknown annotated address: '+hex(address))
            if address in boundaries:raise ValueError('duplicate annotated address: '+hex(address))
            boundaries[address]=a
    fields=['address','symbol','subsystem','status','incoming','outgoing','root_distance','priority','boundary','evidence','implementation','tests','comparison','aliases']
    rows=[]
    for address,row in sorted(functions.items()):
        names=sorted(row['aliases']);name=next((n for n in names if not n.startswith(('non-virtual thunk','virtual thunk'))),names[0])
        area=subsystem(name);a=boundaries.get(address,{})
        degree=len(incoming[address])+len(outgoing[address]);d=distance.get(address)
        influence={'frontend':5,'save':5,'interaction':4,'ranged':4,'world':3,'combat':3,'items':3,'effects_skills':2}.get(area,1)
        priority=round(math.log2(1+degree)*10+influence*12+(5-d)*8 if d is not None else math.log2(1+degree)*10+influence*12,3)
        rows.append(dict(address=row['address'],symbol=name,subsystem=area,status=a.get('status','unseen'),incoming=len(incoming[address]),
            outgoing=len(outgoing[address]),root_distance=d if d is not None else '',priority=priority,boundary=a.get('boundary','No reviewed boundary annotation'),
            evidence=';'.join(a.get('evidence',[])),implementation=';'.join(a.get('implementation',[])),tests=';'.join(a.get('tests',[])),
            comparison=a.get('comparison',''),aliases=' | '.join(names)))
    # Port-native orchestration has no false original function address.
    for a in annotations.get('port_systems',[]):
        if a['status'] not in STATUSES:raise ValueError('bad port status')
        for field in ['evidence','implementation','tests']:
            for p in a.get(field,[]):
                if not(root/p.split('#',1)[0]).is_file():raise ValueError('missing port coverage path '+p)
        rows.append(dict(address='port:'+a['id'],symbol=a['id'],subsystem=a['subsystem'],status=a['status'],incoming=0,outgoing=0,root_distance='',priority=0,
           boundary=a['boundary'],evidence=';'.join(a.get('evidence',[])),implementation=';'.join(a.get('implementation',[])),tests=';'.join(a.get('tests',[])),comparison='',aliases='port-native (no original symbol alias)'))
    output=io.StringIO(newline='');writer=csv.DictWriter(output,fieldnames=fields,delimiter='\t',lineterminator='\n');writer.writeheader();writer.writerows(rows)
    metadata={'schema':1,'original_elf_sha256':annotations['original_elf_sha256'],
      'inputs':{str(p.relative_to(root)):hashlib.sha256(p.read_bytes()).hexdigest() for p in inputs},
      'rows':len(rows),'defined_function_addresses':len(functions),'annotated_function_addresses':len(boundaries),
      'status_counts':{s:sum(r['status']==s for r in rows) for s in sorted(STATUSES)},
      'verification_groups':list(VERIFICATION_GROUPS),'verification_join':'tools/coverage_map.py --check --verification-report FILE; never changes reviewed statuses',
      'meaning':'Callgraph has only resolved direct edges. Status is a reviewed bounded claim, not percent game completion. No runtime verification is inferred from symbol/decompilation presence.',
      'priority_formula':'10*log2(1+unique_in+unique_out) + 12*subsystem_weight + 8*(5-root_distance) for distances <=4; otherwise omit distance term'}
    return output.getvalue(),json.dumps(metadata,ensure_ascii=False,indent=2,sort_keys=True)+'\n',rows

def verification_summary(path):
    """Join an explicit run without promoting any reviewed original boundary."""
    report=json.loads(path.read_text())
    if report.get('schema') != 1 or report.get('kind') != 'verification-run':
        raise ValueError('not an OpenTorchlight verification-run report')
    groups={}
    for name in VERIFICATION_GROUPS:
        group=report.get('groups',{}).get(name)
        if not isinstance(group,dict) or group.get('status') not in {'PASSED','FAILED','NOT RUN'}:
            raise ValueError('missing or invalid verification group: '+name)
        groups[name]={key:group.get(key) for key in ('requested','status','passed','failed','skipped','reason')}
    return {'schema':1,'kind':'coverage-verification-join','source_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),
            'groups':groups,'original_status_promotions':0,
            'meaning':'Execution groups are separate evidence. PASSED resource/regression tests do not promote original fidelity.'}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[1]);p.add_argument('--check',action='store_true');p.add_argument('--next',type=int,default=0);p.add_argument('--include-researched',action='store_true');p.add_argument('--verification-report',type=Path)
    a=p.parse_args();root=a.root.resolve();tsv,meta,rows=generate(root)
    for path,text in [(root/'research/coverage.tsv',tsv),(root/'research/coverage-summary.json',meta)]:
        if a.check:
            if not path.is_file() or path.read_text()!=text:raise SystemExit('coverage stale: '+str(path))
        else:path.write_text(text)
    print(f'Coverage: {len(rows)} explicit rows; no automatic promotions from decompilation.')
    if a.next:
        allowed={'unseen','partial'}|({'researched'} if a.include_researched else set())
        frontier=[r for r in rows if r['status'] in allowed and re.search(r'\bC[A-Z]\w*::',r['symbol']) and not r['symbol'].startswith(('non-virtual thunk','virtual thunk'))]
        for r in sorted(frontier,key=lambda r:(-r['priority'],r['address']))[:max(0,a.next)]:
            print(f"{r['priority']:8.3f} {r['status']:10} {r['address']} [{r['subsystem']}] {r['symbol']}")
    if a.verification_report:
        print(json.dumps(verification_summary(a.verification_report),ensure_ascii=False,sort_keys=True))
    return 0
if __name__=='__main__':raise SystemExit(main())
