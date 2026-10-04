#include "EmptyStrings.h"
#include "BaseUnit.h"
#include "CullingBounds.h"
#include "GenericModel.h"
#include "Level.h"
#include "OutputEvents.h"

void CBaseUnit::setSpawnerGuid(long long guid)
{
    m_iSpawnerGuid = guid;
}

bool CBaseUnit::getCastsShadows()
{
    return m_bCastsShadows;
}

const Ogre::Vector3& CBaseUnit::getMinBounds()
{
    return m_pCullingBounds != NULL ? m_pCullingBounds->getWorldMinimum() : Ogre::Vector3::ZERO;
}

const Ogre::Vector3& CBaseUnit::getMaxBounds()
{
    return m_pCullingBounds != NULL ? m_pCullingBounds->getWorldMaximum() : Ogre::Vector3::ZERO;
}

const Ogre::Vector3& CBaseUnit::getLocalMinBounds()
{
    return m_pCullingBounds != NULL ? m_pCullingBounds->getLocalMinimum() : Ogre::Vector3::ZERO;
}

const Ogre::Vector3& CBaseUnit::getLocalMaxBounds()
{
    return m_pCullingBounds != NULL ? m_pCullingBounds->getLocalMaximum() : Ogre::Vector3::ZERO;
}

void CBaseUnit::deactivateUnitInLevel()
{
    m_bRangeEnabled = false;
    setActiveInLevel(false);
}

void CBaseUnit::setHighlighted(bool highlighted)
{
    m_bHighlighted = highlighted;
    if (getUnitModel() != NULL)
        static_cast<CGenericModel*>(getUnitModel())->setHighlighted(m_bHighlighted);
}

bool CBaseUnit::ISA(UNITTYPES::EUNITTYPES type)
{
    return m_pResourceManager != NULL ? m_pResourceManager->ISA(m_eUnitType, type) : false;
}

bool CBaseUnit::getIsQuestUnit()
{
    return ISA(UNITTYPES::QUESTITEM) || m_iQuestGuid != -1;
}

void CBaseUnit::broadcastAlerted()
{
    if (m_bBaseUnitFlag0 && !ISA(UNITTYPES::PLAYER))
        BroadcastEvent(OUTPUT_EVENT_MONSTER_ALERTED);
}

void CBaseUnit::broadcastKilled()
{
    if (!ISA(UNITTYPES::PLAYER))
        BroadcastEvent(OUTPUT_EVENT_MONSTER_KILLED);
}

void CBaseUnit::setCastsShadows(bool shadows)
{
    m_bCastsShadows = shadows;
    if (getUnitModel() != NULL)
        static_cast<CGenericModel*>(getUnitModel())->setCastsShadows(m_bCastsShadows);
}

void CBaseUnit::activateUnitInLevel()
{
    m_bInActiveRange = true;
    m_bInFadeRange = true;
    m_bRangeEnabled = true;
    setActiveInLevel(true);
    setCastsShadows(m_bCastsShadows);
}

void CBaseUnit::broadcastUnitState(EUNIT_STATES state)
{
    if (getLevel() != NULL)
        getLevel()->unitBroadcastMessage(this, state);
}

void CBaseUnit::questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target)
{
    if (getLevel() != NULL)
        getLevel()->questEventFire(event, character, target);
}
