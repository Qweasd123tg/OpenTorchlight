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

root = Path.cwd() / 'build-decomp/equipment-applysave-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x8863b0'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentApplySaveTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('skip_parent', 'CItem::applySaveState(state);', ';'), ('swap_prefix', 'm_sPrefix=state.m_sStateString18;', 'm_sPrefix=state.m_sStateString20;'), ('wrong_stack', 'm_iUnknown238=state.m_iStackSize;', 'm_iUnknown238=state.m_iStackSize+1;'), ('wrong_identified', 'm_bUnknown348=state.m_bIdentified;', 'm_bUnknown348=!state.m_bIdentified;'), ('damage_sentinel_zero', 'if (state.m_iBaseDamage!=-1)', 'if (state.m_iBaseDamage!=0)'), ('armor_sentinel_zero', 'if (state.m_iBaseArmor!=-1)', 'if (state.m_iBaseArmor!=0)'), ('omit_minimum_damage', 'm_iMinimumDamage=state.m_iBaseDamage;', ';'), ('omit_base_damage', 'm_iUnknown340=state.m_iBaseDamage;', ';'), ('omit_base_armor', 'm_iUnknown33C=state.m_iBaseArmor;', ';'), ('skip_guid_guard', 'if (guid!=-1)', 'if (true)'), ('wrong_spawn_level', 'createUnit(guid,1,true,false)', 'createUnit(guid,2,true,false)'), ('wrong_spawn_flag', 'createUnit(guid,1,true,false)', 'createUnit(guid,1,false,false)'), ('wrong_spawn_last_flag', 'createUnit(guid,1,true,false)', 'createUnit(guid,1,true,true)'), ('skip_child_apply', 'item->applySaveState(*state.m_SocketedItems[i]);', ';'), ('skip_add_container', 'addContainerItem(item);', ';'), ('skip_transfer_effects', 'activation<3', 'activation<2'), ('extra_activation', 'activation<3', 'activation<4'), ('skip_effect_activation', 'activateEffect(effect);', ';'), ('skip_effect_value_restore', 'effect->m_fValueC0=value;', ';'), ('read_value_after_add', 'float value=effect->m_fValueC0;', 'float value=-91.0f;'), ('retain_transferred_effects', 'effects.clear();', ';'), ('skip_effect_recalc', 'if (m_pEffectManager) m_pEffectManager->calculateEffectValues();', ';'), ('retain_damage_bonuses', 'm_ElementalDamageBonuses.clear();', ';'), ('damage_reset_nonzero', 'm_ElementalDamageBonuses.push_back(0);', 'm_ElementalDamageBonuses.push_back(1);'), ('wrong_saved_damage', 'state.m_DamageBonuses[i]);', 'state.m_DamageBonuses[i]+1);'), ('skip_elemental_refresh', 'createElementalDamages();', ';'), ('skip_price', 'recalculatePrice();', ';'), ('skip_requirements', 'setRequirements();', ';')]
mutations += [
 ('captured_socket_count','for (int i=0;i<static_cast<int>(state.m_SocketedItems.size());++i)','int count=state.m_SocketedItems.size(); for (int i=0;i<count;++i)'),
 ('captured_effect_count','for (unsigned int i=0;i<effects.size();++i)','unsigned int count=effects.size(); for (unsigned int i=0;i<count;++i)'),
 ('captured_damage_count','for (unsigned int i=0;i<state.m_DamageTypes.size();++i)','unsigned int count=state.m_DamageTypes.size(); for (unsigned int i=0;i<count;++i)'),
 ('post_callback_effect_value','effect->m_fValueC0=value;','effect->m_fValueC0=effects[i]->m_fValueC0;'),
 ('cached_child_state','CEquipment* item=dynamic_cast','CItemSaveState* child=state.m_SocketedItems[i]; CEquipment* item=dynamic_cast'),
 ('delayed_effect_clear','effects.clear();',';')]

results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    if name == 'cached_child_state': changed=changed.replace('item->applySaveState(*state.m_SocketedItems[i]);','item->applySaveState(*child);')
    if name == 'delayed_effect_clear': changed=changed.replace('if (m_pEffectManager) m_pEffectManager->calculateEffectValues();','for (int a=0;a<3;++a) state.m_Effects[a].clear(); if (m_pEffectManager) m_pEffectManager->calculateEffectValues();')
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_applysave_differential')
        passed = any('equipment_applysave_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_applysave_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
