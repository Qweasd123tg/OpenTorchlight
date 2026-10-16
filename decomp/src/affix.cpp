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
    if (m_pOwner != owner) {
        if (m_pOwner)
            m_pOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&m_pOwner), m_iOwnerSafePointerId);
        m_pOwner = NULL;
        if (owner)
            m_iOwnerSafePointerId = owner->addSafePointer(reinterpret_cast<TSafePointer<void*>*>(&m_pOwner));
        m_pOwner = owner;
    }
    for (unsigned int i = 0; i < m_Effects.size(); ++i)
        m_Effects[i]->setOwner(owner, true);
}

void CAffix::setSkillOwner(CSkill* owner)
{
    if (m_pSkillOwner != owner) {
        if (m_pSkillOwner)
            m_pSkillOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&m_pSkillOwner), m_iSkillOwnerSafePointerId);
        m_pSkillOwner = NULL;
        if (owner)
            m_iSkillOwnerSafePointerId = owner->addSafePointer(reinterpret_cast<TSafePointer<void*>*>(&m_pSkillOwner));
        m_pSkillOwner = owner;
    }
    if (owner && owner->m_pOwner)
        setOwner(owner->m_pOwner);
    for (unsigned int i = 0; i < m_Effects.size(); ++i)
        m_Effects[i]->setSkillOwner(owner);
}

void CAffix::clearEffectsFromOwner()
{
    if (m_pEffectManager) {
        for (unsigned int i = 0; i < m_Effects.size(); ++i) {
            if (m_Effects[i]->m_Owner.getObject())
                m_Effects[i]->m_Owner.getObject()->deactivateEffect(m_Effects[i]);
            m_Effects[i]->setAffixOwner(NULL);
            m_pEffectManager->removeEffect(m_Effects[i], false);
        }
        if (m_pEffectManager) {
            m_pEffectManager->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&m_pEffectManager), m_iEffectManagerSafePointerId);
            m_pEffectManager = NULL;
        }
    }
}

void CAffix::addEffectsToEffectManager(CEffectManager* manager)
{
    if (m_pEffectManager == manager)
        return;
    clearEffectsFromOwner();
    if (m_pEffectManager != manager) {
        if (m_pEffectManager)
            m_pEffectManager->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&m_pEffectManager), m_iEffectManagerSafePointerId);
        m_pEffectManager = NULL;
        if (manager)
            m_iEffectManagerSafePointerId = manager->addSafePointer(reinterpret_cast<TSafePointer<void*>*>(&m_pEffectManager));
        m_pEffectManager = manager;
    }
    CCharacter* source = dynamic_cast<CCharacter*>(m_pOwner);
    CBaseUnit* target = manager->getOwnerReference().getObject();
    if (manager) {
        for (unsigned int i = 0; i < m_Effects.size(); ++i) {
            m_Effects[i]->setAffixOwner(this);
            if (target) {
                if (target->isEffectValidForUnit(source, m_pOwner, m_Effects[i])) {
                    target->applyEffectOnUnit(source, m_pOwner, m_Effects[i]);
                    target->activateEffect(m_Effects[i]);
                }
            } else {
                manager->cloneEffect(NULL, m_Effects[i]);
            }
        }
    }
}
