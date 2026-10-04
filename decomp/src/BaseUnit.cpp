#include "EmptyStrings.h"
#include "BaseUnit.h"
#include "CullingBounds.h"
#include "GenericModel.h"
#include "Level.h"
#include "OutputEvents.h"
#include "EffectManager.h"
#include "UnitThemes.h"

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

bool CBaseUnit::hasUnitTheme(CUnitTheme* theme)
{
    return m_AffixThemes.find(theme) != -1 || m_UnitThemes.find(theme) != -1;
}

bool CBaseUnit::hasUnitTheme(long long guid)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    return themes != NULL ? hasUnitTheme(themes->getTheme(guid)) : false;
}

bool CBaseUnit::hasUnitTheme(const std::wstring& name)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    return themes != NULL ? hasUnitTheme(themes->getTheme(name)) : false;
}

bool CBaseUnit::removeEffect(const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->removeEffect(name, true) : false;
}

bool CBaseUnit::removeAffix(const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->deleteAffix(name) : false;
}

bool CBaseUnit::hasEffect(EEFFECT_TYPE type)
{
    return m_pEffectManager != NULL ? m_pEffectManager->hasEffect(type) : false;
}

bool CBaseUnit::hasEffect(EEFFECT_TYPE type, const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->hasEffect(type, name) : false;
}

bool CBaseUnit::hasEffect(const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->hasEffect(name) : false;
}

float CBaseUnit::getEffectValue(EEFFECT_TYPE type, float fallback, EDAMAGE_TYPES damage)
{
    return m_pEffectManager != NULL ? m_pEffectManager->getEffectValue(type, damage) : fallback;
}

float CBaseUnit::getEffectValue(EEFFECT_TYPE type, float fallback, const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->getEffectValue(type, name) : fallback;
}

float CBaseUnit::getEffectValue(EEFFECT_ACTIVATION activation, EEFFECT_TYPE type, float fallback, EDAMAGE_TYPES damage)
{
    return m_pEffectManager != NULL ? m_pEffectManager->getEffectValue(activation, type, damage) : fallback;
}

void CBaseUnit::addUnitTheme(CUnitTheme* theme)
{
    if (m_UnitThemes.find(theme) != -1)
        return;
    m_ThemesToRemove.remove(theme);
    m_ThemesToAdd.add(theme);
    m_UnitThemes.add(theme);
}

void CBaseUnit::removeUnitTheme(CUnitTheme* theme)
{
    if (m_UnitThemes.find(theme) == -1)
        return;
    m_ThemesToRemove.add(theme);
    m_ThemesToAdd.remove(theme);
    m_UnitThemes.remove(theme);
}

void CBaseUnit::addUnitTheme(const std::wstring& name)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    if (themes != NULL)
        addUnitTheme(themes->getTheme(name));
}

void CBaseUnit::removeUnitTheme(const std::wstring& name)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    if (themes != NULL)
        removeUnitTheme(themes->getTheme(name));
}

void CBaseUnit::removeUnitTheme(long long guid)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    if (themes != NULL)
        removeUnitTheme(themes->getTheme(guid));
}

void CBaseUnit::setEditorThemeID(unsigned int id)
{
    if (m_pResourceManager->getEditorIsRunning())
    {
        m_iEditorThemeID = id;
        CUnitThemes* themes = CUnitThemes::getSingleton();
        for (unsigned int i = 1; i <= themes->getThemes().size(); ++i)
        {
            if (i == id)
                addUnitTheme(themes->getThemes()[i-1]);
            else
                removeUnitTheme(themes->getThemes()[i-1]);
        }
    }
}
