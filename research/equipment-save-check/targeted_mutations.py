"""Targeted branch mutations for original-vs-recovered Equipment particle selection.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-save-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x8867c0'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentSaveTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('skip_base', 'CItem::fillSaveState(state,index,flag);', ';'), ('wrong_index', 'state,index,flag', 'state,index+1,flag'), ('wrong_flag', 'state,index,flag', 'state,index,!flag'), ('drop_disabled', 'if (m_bUnknown25C && !getEnabled())', 'if (m_bUnknown25C && getEnabled())'), ('ignore_drop', 'if (m_bUnknown25C && !getEnabled())', 'if (!getEnabled())'), ('wrong_name_flag', 'getFullItemName(true);', 'getFullItemName(false);'), ('skip_name', 'getFullItemName(true);', ';'), ('swap_prefix', 'state.m_sStateString18=m_sPrefix;', 'state.m_sStateString18=m_sSuffix;'), ('skip_elements', 'createElementalDamages();', ';'), ('child_index', '*child,-1,false', '*child,0,false'), ('child_flag', '*child,-1,false', '*child,-1,true'), ('dynamic_socket_count', 'i<sockets', 'i<static_cast<int>(m_SocketedEquipment.size())'), ('skip_transfer', 'activation<3', 'activation<2'), ('wrong_owner_recalc', 'copy->setOwner(NULL,true);', 'copy->setOwner(NULL,false);'), ('skip_owner', 'copy->setOwner(NULL,true);', ';'), ('skip_skill', 'copy->setSkillOwner(NULL);', ';'), ('skip_value_restore', 'copy->m_fValueC0=effects[i]->m_fValueC0;', ';'), ('wrong_effect_bucket', 'state.m_Effects[activation].push_back(copy);', 'state.m_Effects[0].push_back(copy);'), ('wrong_bonus', 'state.m_DamageBonuses.push_back(m_ElementalDamageBonuses[i]);', 'state.m_DamageBonuses.push_back(m_ElementalDamageBonuses[i]+1);'), ('skip_affix_clear', 'm_pEffectManager->clearOutAffixEffects();', ';'), ('skip_affix_restore', 'm_pEffectManager->addAffixEffectsBackIn();', ';')]
mutations += [
 ('cached_effect_count','for (unsigned int i=0;i<effects.size();++i)','unsigned int count=effects.size(); for (unsigned int i=0;i<count;++i)'),
 ('cached_effect_source','CEffect* copy=new CEffect(effects[i]);','CEffect* source=effects[i]; CEffect* copy=new CEffect(source);'),
]
# The cached-source mutant must also alter the post-callback reread.

results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    if name == 'cached_effect_source': changed=changed.replace('copy->m_fValueC0=effects[i]->m_fValueC0;', 'copy->m_fValueC0=source->m_fValueC0;')
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_save_differential')
        passed = any('equipment_save_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_save_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
