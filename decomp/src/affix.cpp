#include "BaseUnit.h"
#include "Character.h"
#include "Skill.h"
#include "EffectManager.h"
#include "MasterResourceManager.h"
#include "Hierarchy.h"
#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Affix.h"
#include "Effect.h"

void CAffix::effectDeleted(CEffect *pEffect)
{
    m_Effects.remove(pEffect);
}

void CAffix::setLevel(unsigned int uiLevel)
{
    m_uiLevel = std::max((float)uiLevel, (float)m_iMinSpawnRange);
    m_uiLevel = std::min((float)m_uiLevel, (float)m_iMaxSpawnRange);

    float fLevelPercent =
        ((float)(m_uiLevel - m_iMinSpawnRange) /
         (float)(m_iMaxSpawnRange - m_iMinSpawnRange)) * 100.0f;

    char percent = 100;
    if (fLevelPercent < 100.0f)
        percent = (char)(fLevelPercent + 0.5f);
    m_cLevelPercent = percent;
    setPercent(percent);
}

bool CAffix::effectHasDuration(EEFFECT_TYPE type)
{
    for (unsigned int i = 0; i < m_Effects.size(); ++i) {
        if (m_Effects[i]->m_fValue24 > 0.0f) {
            if (type != m_Effects[i]->m_eType)
                continue;
            return true;
        }
    }
    return false;
}

bool CAffix::effectExists(EEFFECT_TYPE type)
{
    for (unsigned int i = 0; i < m_Effects.size(); ++i) {
        if (type != m_Effects[i]->m_eType)
            continue;
        return true;
    }
    return false;
}

std::wstring CAffix::getDisplayStats(unsigned int level)
{
    std::wstring result(L"");
    for (unsigned int i = 0; i < m_Effects.size(); ++i) {
        std::wstring text = m_Effects[i]->getDisplayStats(level, false);
        if (result != EMPTY_WSTRING && text != EMPTY_WSTRING)
            result += L"\n";
        result += text;
    }
    return result;
}

void CAffix::setSaves(bool saves)
{
    for (unsigned int i = 0; i < m_Effects.size(); ++i)
        m_Effects[i]->m_flag33 = saves;
}

bool CAffix::updateAffixDuration(float elapsed)
{
    if (m_fDuration < 0.0f)
        return true;
    m_fDuration -= elapsed;
    if (m_fDuration <= 0.0f) {
        m_fDuration = 0.0f;
        return false;
    }
    return true;
}

bool CAffix::canBeAppliedToUnitType(unsigned int type)
{
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    for (unsigned int i = 0; i < m_ApplicableUnitTypes.size(); ++i)
        if (hierarchy->ISA(type, m_ApplicableUnitTypes[i]))
            return true;
    return false;
}

void CAffix::setOwner(CBaseUnit* owner)
{
    m_Owner.setObject(owner);
    for (unsigned int i = 0; i < m_Effects.size(); ++i)
        m_Effects[i]->setOwner(owner, true);
}

void CAffix::setSkillOwner(CSkill* owner)
{
    m_SkillOwner.setObject(owner);
    if (owner && owner->m_pOwner)
        setOwner(owner->m_pOwner);
    for (unsigned int i = 0; i < m_Effects.size(); ++i)
        m_Effects[i]->setSkillOwner(owner);
}

void CAffix::clearEffectsFromOwner()
{
    if (m_EffectManager.getObject()) {
        for (unsigned int i = 0; i < m_Effects.size(); ++i) {
            if (m_Effects[i]->m_Owner.getObject())
                m_Effects[i]->m_Owner.getObject()->deactivateEffect(m_Effects[i]);
            m_Effects[i]->setAffixOwner(NULL);
            m_EffectManager.getObject()->removeEffect(m_Effects[i], false);
        }
        if (m_EffectManager.getObject())
            m_EffectManager.setObject(NULL);
    }
}

void CAffix::addEffectsToEffectManager(CEffectManager* manager)
{
    if (m_EffectManager.getObject() == manager)
        return;
    clearEffectsFromOwner();
    m_EffectManager.setObject(manager);
    CCharacter* source = dynamic_cast<CCharacter*>(m_Owner.getObject());
    CBaseUnit* target = manager->getOwnerReference().getObject();
    if (manager) {
        for (unsigned int i = 0; i < m_Effects.size(); ++i) {
            m_Effects[i]->setAffixOwner(this);
            if (target) {
                if (target->isEffectValidForUnit(source, m_Owner.getObject(), m_Effects[i])) {
                    target->applyEffectOnUnit(source, m_Owner.getObject(), m_Effects[i]);
                    target->activateEffect(m_Effects[i]);
                }
            } else {
                manager->cloneEffect(NULL, m_Effects[i]);
            }
        }
    }
}

void CAffix::setDirection(const Ogre::Vector3* direction)
{
    for (unsigned int i = 0; i < m_Effects.size(); ++i)
        if (direction)
            m_Effects[i]->m_direction = *direction;
        else
            m_Effects[i]->m_direction = Ogre::Vector3::UNIT_Z;
}

void CAffix::fillOutStatBonuses(float (&values)[6], bool takeHighest)
{
    for (unsigned int i = 0; i < m_Effects.size(); ++i)
        for (unsigned int stat = 0; stat < 6; ++stat)
        {
            CEffect* effect = m_Effects[i];
            int index = effect->m_statModifiers.find(static_cast<EEFFECT_STAT_MODIFIERS>(stat));
            float value = index == -1 ? 0.0f : effect->m_statModifierValues[index];
            if (takeHighest) values[stat] = std::max(values[stat], value);
            else values[stat] = value;
        }
}

void CAffix::setPercent(char percent)
{
    m_cLevelPercent = percent;
    if (m_cLevelPercent < 0) m_cLevelPercent = 0;
    if (m_cLevelPercent > 100) m_cLevelPercent = 100;
    float fraction = static_cast<float>(m_cLevelPercent) / 100.0f;
    if (m_pOriginalAffix)
        for (unsigned int i = 0; i < m_pOriginalAffix->m_Effects.size(); ++i)
            if (i < m_Effects.size())
            {
                CEffect* original = m_pOriginalAffix->m_Effects[i];
                if (original->m_fValueC8 != 0.0f && original->m_fValueC8 != original->m_fValueC4 &&
                    !original->m_graphs[0] && !original->m_graphs[1] &&
                    !original->m_graphs[2] && !original->m_graphs[3])
                {
                    float value = original->m_fValueC4 + (original->m_fValueC8 - original->m_fValueC4) * fraction;
                    m_Effects[i]->m_fValueC4 = value;
                    m_Effects[i]->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
                    m_Effects[i]->m_fValueC8 = value;
                    m_Effects[i]->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
                }
                m_Effects[i]->m_iLevel = m_uiLevel == static_cast<unsigned int>(-1) || m_uiLevel > 1000 ? 0 : m_uiLevel;
                m_Effects[i]->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
            }
}

void CAffix::clone(const CAffix* source)
{
    if (!source || !source->m_bDataFileInitialized) return;
    m_pOriginalAffix = const_cast<CAffix*>(source);
    clearEffectsFromOwner();
    m_Effects.deleteAll();
    m_bDataFileInitialized = false;
    m_Owner.setObject(source->m_Owner.getObject());
    m_sAffixFileName = source->m_sAffixFileName;
    m_sDisplayName = source->m_sDisplayName;
    m_iMinSpawnRange = source->m_iMinSpawnRange;
    m_iMaxSpawnRange = source->m_iMaxSpawnRange;
    m_fDuration = source->m_fDuration;
    m_bHasDuration = source->m_bHasDuration;
    m_sPrefix = source->m_sPrefix;
    m_sSuffix = source->m_sSuffix;
    m_iRank = source->m_iRank;
    m_iWeight = source->m_iWeight;
    m_iSlotsOccupy = source->m_iSlotsOccupy;
    m_ApplicableUnitTypes.setGrowBy(source->m_ApplicableUnitTypes.size() + 1);
    for (unsigned int i = 0; i < source->m_ApplicableUnitTypes.size(); ++i)
        m_ApplicableUnitTypes.add(source->m_ApplicableUnitTypes[i]);
    setSkillOwner(source->m_SkillOwner.getObject());
    m_Effects.setGrowBy(source->m_Effects.size() + 1);
    for (unsigned int i = 0; i < source->m_Effects.size(); ++i)
        m_Effects.add(new CEffect(source->m_Effects[i]));
    setLevel(m_uiLevel);
}

CAffix::CAffix(const std::wstring& name)
    : m_pOriginalAffix(NULL), m_sAffixFileName(name), m_sPrefix(EMPTY_WSTRING),
      m_sSuffix(EMPTY_WSTRING), m_iMinSpawnRange(0), m_iMaxSpawnRange(9999999),
      m_cLevelPercent(100), m_iRank(1), m_iSlotsOccupy(1), m_uiLevel(1),
      m_bTemporary(false), m_Effects(1), m_bDataFileInitialized(true),
      m_fDuration(-1.0f), m_bHasDuration(false), m_iWeight(1), m_ApplicableUnitTypes(10)
{
    parseAffixGroup();
}

CAffix::CAffix(CAffix* source, unsigned int level)
    : m_uiLevel(level), m_bTemporary(false), m_Effects(1),
      m_bDataFileInitialized(true), m_bHasDuration(false), m_ApplicableUnitTypes(10)
{
    clone(source);
    if (level != static_cast<unsigned int>(-1)) setLevel(level);
}

CAffix::~CAffix()
{
    clearEffectsFromOwner();
    m_Effects.deleteAll();
}
