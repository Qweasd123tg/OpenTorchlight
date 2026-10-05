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

root = Path.cwd() / 'build-decomp/equipment-use-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x86e910'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentUseTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('skip_null_target', 'if (!target) return;', ';'), ('charge_zero_allowed', 'm_iUnknown248<1', 'm_iUnknown248<0'), ('wrong_unlimited_guard', 'm_iUnknown248!=-9999) return', 'm_iUnknown248!=-9998) return'), ('ignore_stack_guard', 'm_iUnknown238<2 &&', 'true &&'), ('skip_effects', 'if (m_pEffectManager)', 'if (false)'), ('wrong_activation_list', 'm_EffectData10+0x30', 'm_EffectData10+0x18'), ('skip_validity', 'target->isEffectValidForUnit(character,effects[i]->m_Owner.getObject(),effects[i])', 'true'), ('ignore_application_result', 'target->applyEffectOnUnit(character,effects[i]->m_Owner.getObject(),effects[i])', '(target->applyEffectOnUnit(character,effects[i]->m_Owner.getObject(),effects[i]),true)'), ('wrong_effect_owner', 'target->applyEffectOnUnit(character,effects[i]->m_Owner.getObject(),effects[i])', 'target->applyEffectOnUnit(character,NULL,effects[i])'), ('skip_potion_guard', 'if (ISA(UNITTYPES::POTION))', 'if (true)'), ('skip_journal', 'character->incrementJournalStatistic(static_cast<EJournalStatistic>(12),1);', ';'), ('wrong_journal_amount', 'static_cast<EJournalStatistic>(12),1', 'static_cast<EJournalStatistic>(12),2'), ('ignore_master_guard', 'if (dynamic_cast<CCharacter*>(target)->m_pMaster)', 'if (true)'), ('skip_pet_stat', 'CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(20),1);', ';'), ('wrong_pet_stat', 'static_cast<ESTATS>(20),1', 'static_cast<ESTATS>(19),1'), ('never_applied', 'applied=true;', 'applied=false;'), ('skip_skill', 'character->performUnknownSkill(m_pSkillManager->m_OtherSkills[0]);', ';'), ('wrong_skill', 'm_OtherSkills[0]', 'm_OtherSkills[1]'), ('consume_on_failure', 'else if (!applied) return;', ';'), ('always_return_without_skill', 'else if (!applied) return;', 'else return;'), ('skip_sound', 'm_pSoundBank->playSample(20,character->m_pSceneNode,0.0f,0.0f,false);', ';'), ('wrong_sound_id', 'playSample(20,', 'playSample(19,'), ('wrong_sound_flag', '0.0f,0.0f,false', '0.0f,0.0f,true'), ('wrong_stack_delta', 'incrementStackBy(-1);', 'incrementStackBy(1);'), ('decrement_unlimited', 'else if (m_iUnknown248!=-9999)', 'else'), ('increment_charges', '--m_iUnknown248;', '++m_iUnknown248;'), ('captured_count', 'for (unsigned int i=0;i<effects.size();++i)', 'unsigned int count=effects.size(); for (unsigned int i=0;i<count;++i)')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_use_differential')
        passed = any('equipment_use_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_use_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
