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
