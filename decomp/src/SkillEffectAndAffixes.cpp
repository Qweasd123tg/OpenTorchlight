#include "SkillEffectAndAffixes.h"
#include "BaseUnit.h"
#include "Effect.h"
#include "EmptyStrings.h"

void CSkillEffectAndAffixes::setDurationOverride(float duration)
{
    for (unsigned int i = 0; i < m_affixData.size(); ++i)
        m_affixData[i]->m_durationOverride = duration;
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
            // The original uses the outer index for this inner access.
            if (!m_effectData[i]->m_effects[i]->m_bFlag28)
                m_effectData[i]->m_effects[i]->m_fValue24 = duration;
}

bool CSkillEffectAndAffixes::effectsTargetEnemy(CBaseUnit* unit)
{
    if (unit != NULL)
        for (unsigned int i = 0; i < m_affixData.size(); ++i)
            if (unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_affixData[i]->m_unitType)) &&
                m_affixData[i]->m_targetType == 0)
                return true;
    return false;
}

std::wstring CSkillEffectAndAffixes::getPortalSkillName()
{
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
            if (m_effectData[i]->m_effects[j]->m_eType == static_cast<EEFFECT_TYPE>(0x71))
                return m_effectData[i]->m_effects[j]->m_sName;
    return EMPTY_WSTRING;
}

void CSkillEffectAndAffixes::appendName(const std::wstring& name)
{
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        if (m_effectData[i] != NULL)
            for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
                m_effectData[i]->m_effects[j]->m_sName =
                    m_effectData[i]->m_effects[j]->m_sName + name;
}

#include "Affix.h"
#include "ResourceManager.h"
#include <algorithm>

void CSkillEffectAndAffixes::addMinAndMaxValuesOfAnEffect(CResourceManager* resources, unsigned int type, float& minimum, float& maximum)
{
    for (unsigned int i = 0; i < m_displayAffixes.size(); ++i)
        for (unsigned int j = 0; j < m_displayAffixes[i]->m_Effects.size(); ++j)
        {
            CEffect* effect = m_displayAffixes[i]->m_Effects[j];
            if (effect && effect->m_eType == static_cast<EEFFECT_TYPE>(type))
            {
                minimum = effect->getMinCaculatedValue() + minimum;
                maximum = effect->getMaxCaculatedValue() + maximum;
            }
        }
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
        {
            CEffect* effect = m_effectData[i]->m_effects[j];
            if (effect && effect->m_eType == static_cast<EEFFECT_TYPE>(type))
            {
                minimum = effect->getMinCaculatedValue() + minimum;
                maximum = effect->getMaxCaculatedValue() + maximum;
            }
        }
}

void CSkillEffectAndAffixes::createAffixesForDisplay(CResourceManager* resources)
{
    if (m_displayAffixes.size() || !m_affixData.size()) return;
    for (unsigned int i = 0; i < m_affixData.size(); ++i)
    {
        CAffix* affix = resources->getNewAffixByName(m_affixData[i]->m_name, m_affixData[i]->m_value18);
        if (affix)
        {
            affix->setSkillOwner(m_pSkill);
            if (!affix->m_bHasDuration && m_affixData[i]->m_durationOverride > 0.0f)
                affix->m_fDuration = m_affixData[i]->m_durationOverride;
            m_displayAffixes.add(affix);
        }
    }
}

bool CSkillEffectAndAffixes::isDamaging()
{
    for (unsigned int i = 0; i < m_displayAffixes.size(); ++i)
        if (m_displayAffixes[i]->effectExists(static_cast<EEFFECT_TYPE>(52)) ||
            m_displayAffixes[i]->effectExists(static_cast<EEFFECT_TYPE>(7)) ||
            m_displayAffixes[i]->effectExists(static_cast<EEFFECT_TYPE>(124))) return true;
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
            if (m_effectData[i]->m_effects[j]->m_eType == static_cast<EEFFECT_TYPE>(52) ||
                m_effectData[i]->m_effects[j]->m_eType == static_cast<EEFFECT_TYPE>(7) ||
                m_effectData[i]->m_effects[j]->m_eType == static_cast<EEFFECT_TYPE>(124)) return true;
    return false;
}

void CSkillEffectAndAffixes::fillOutStatBonuses(float (&values)[6], bool takeHighest)
{
    if (!m_displayAffixes.size()) getDisplayStats();
    for (unsigned int i = 0; i < m_displayAffixes.size(); ++i) m_displayAffixes[i]->fillOutStatBonuses(values, takeHighest);
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
            for (unsigned int stat = 0; stat < 6; ++stat)
            {
                CEffect* effect = m_effectData[i]->m_effects[j];
                int index = effect->m_statModifiers.find(static_cast<EEFFECT_STAT_MODIFIERS>(stat));
                float value = index == -1 ? 0.0f : effect->m_statModifierValues[index];
                if (takeHighest) values[stat] = std::max(values[stat], value);
                else values[stat] = value;
            }
}

CSkillEffectAndAffixes::~CSkillEffectAndAffixes()
{
    m_displayAffixes.deleteAll();
    m_affixNames.clear();
    m_effectNames.clear();
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        if (m_effectData[i]->m_flag10) m_effectData[i]->m_effects.deleteAll();
    m_effectData.deleteAll();
    m_affixData.deleteAll();
}
