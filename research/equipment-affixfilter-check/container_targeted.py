"""Run standalone branch mutations of one Equipment entry, from the repository root."""
import json, shutil, sys
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid, mutate
root=Path('build-decomp/container_targeted-targeted').resolve()
(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
source=Path('decomp/src/Equipment.cpp').read_text()
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x86e1d0'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentAffixFilterTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/name,root/'tests'/name)
mutations=[('inclusive_capacity', 'm_SocketedEquipment.size() < m_iSocketCount', 'm_SocketedEquipment.size() <= m_iSocketCount'), ('signed_capacity', 'm_SocketedEquipment.size() < m_iSocketCount', 'static_cast<int>(m_SocketedEquipment.size()) < static_cast<int>(m_iSocketCount)'), ('omit_append', 'm_SocketedEquipment.add(item);', ';'), ('append_parent', 'm_SocketedEquipment.add(item);', 'm_SocketedEquipment.add(this);'), ('ignore_socketable', 'item->ISA(UNITTYPES::SOCKETABLE)', 'true'), ('allow_randommagic', '!item->ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE)', 'true'), ('omit_filter', 'item->removeAffixesThatDontSupportUnitType(m_eUnitType);', ';'), ('wrong_parent_type', 'removeAffixesThatDontSupportUnitType(m_eUnitType)', 'removeAffixesThatDontSupportUnitType(UNITTYPES::ARMOR)'), ('omit_calculate', 'item->m_pEffectManager->calculateEffectValues();', ';')]
import subprocess
lib=root/'heap_counter.so'
subprocess.run(['cc','-shared','-fPIC','-O2','-Wall','-Wextra','research/equipment-affixfilter-check/heap_counter.c','-o',str(lib)],check=True)
old_env=hybrid.game_env
def counted_env(*a,**kw):
 game,e=old_env(*a,**kw);e['LD_PRELOAD']+=':'+str(lib);e['OTL_FILTER_HEAP_REQUIRED']='1';return game,e
hybrid.game_env=counted_env

results=[]
for name,before,after in [('baseline','','')]+mutations:
 if name!='baseline' and body.count(before)!=1:raise SystemExit('ambiguous replacement: '+name)
 changed=body if name=='baseline' else body.replace(before,after,1)
 (root/'src/Equipment.cpp').write_text(head+changed+tail)
 try:
  blob,loader=hybrid.build(out=root/name,src=root/'src',tests=sorted((root/'tests').glob('*.cpp')),verbose=False)
  code,report=hybrid.selftest(blob,loader,only='equipment_container_differential')
  passed=any('equipment_container_differential' in line and 'PASS (0)' in line for line in report)
  if name=='baseline' and (code or not passed):raise SystemExit('baseline failed: '+'\n'.join(report))
  outcome='pass' if name=='baseline' else 'survived' if passed else 'killed' if any('equipment_container_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
  row={'name':name,'outcome':outcome,'exit':code}
 except Exception as e:row={'name':name,'outcome':'inconclusive','error':str(e)}
 results.append(row);print(json.dumps(row),flush=True)
 (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
