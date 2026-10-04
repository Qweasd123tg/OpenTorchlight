#include "EmptyStrings.h"
#include "Item.h"
#include "SoundBank.h"
#include "DataGroup.h"
#include "GenericModel.h"
#include "Keyframe.h"
#include "OutputEvents.h"
#include <algorithm>
#include <CEGUIWindow.h>
#include <CEGUIWindowManager.h>

CItem::CItem(CResourceManager* resourceManager)
    : CBaseUnit(resourceManager, static_cast<EBASEUNIT_TYPE>(1)), m_pSoundBank(NULL),
      m_fForcedActiveTime(0.0f), m_pItemText(NULL), m_bItemFlag1F0(true),
      m_bNonSelectable(false), m_bItemFlag1F2(true), m_pItemTextParent(NULL),
      m_bItemTextAttached(false), m_fOpacity(0.999f), m_bRequestedVisible(true),
      m_bLevelLighting(false), m_bItemFlag20A(false), m_sItemName(), m_bItemFlag218(false)
{
    m_bInActiveRange = false;
    m_bEnabled = true;
}

CItem::~CItem()
{
    if (m_pSoundBank != NULL)
    {
        delete m_pSoundBank;
        m_pSoundBank = NULL;
    }
    destroyItemText();
}

void CItem::setVisible(bool visible)
{
    m_bRequestedVisible = visible;
}

void CItem::hideItemText()
{
    if (m_pItemText != NULL && m_bItemTextAttached)
    {
        m_bItemTextAttached = false;
        m_pItemTextParent->removeChildWindow(m_pItemText);
    }
}

void CItem::showItemText()
{
    if (m_pItemText != NULL && !m_bItemTextAttached)
    {
        m_bItemTextAttached = true;
        m_pItemTextParent->addChildWindow(m_pItemText);
    }
}

void CItem::destroyItemText()
{
    hideItemText();
    if (m_pItemText != NULL)
    {
        m_bItemTextAttached = false;
        CEGUI::WindowManager::getSingleton().destroyWindow(m_pItemText);
        m_pItemText = NULL;
    }
}

void CItem::setHighlighted(bool highlighted)
{
    if (getHighlighted() != highlighted)
    {
        setItemTextHighlighted(highlighted);
        CBaseUnit::setHighlighted(highlighted);
    }
}

void CItem::setVisible(bool visible, bool immediate)
{
    if (!immediate)
    {
        setVisible(visible);
        return;
    }
    if (!visible && m_fOpacity != 0.0f)
    {
        m_fOpacity = 0.0f;
        updateOpacity(0.0f, false);
    }
    CSceneNodeObject::setVisible(visible);
}

void CItem::unitInit(CDataGroup* data, bool initialize)
{
    if (data != NULL)
    {
        m_bLevelLighting = data->GetDataValue(L"LEVELLIGHTING", m_bLevelLighting);
        CBaseUnit::unitInit(data, initialize);
        std::wstring name = data->GetDataValue(L"DISPLAYNAME", L"");
        if (name.empty())
            name = data->GetDataValue(L"NAME", L"ITEM");
        m_sItemName = std::wstring(name);
        m_bNonSelectable = data->GetDataValue(L"NONSELECTABLE", false);
    }
}

bool CItem::interact(CCharacter* character)
{
    questEventFire(static_cast<EQUEST_EVENTS>(2), character, this);
    if (character != NULL)
    {
        BroadcastEvent(OUTPUT_EVENT_ITEM_INTERACTED);
        broadcastUnitState(static_cast<EUNIT_STATES>(2));
        return true;
    }
    return false;
}

void CItem::setRimlight(std::wstring texture)
{
    if (getUnitModel() != NULL)
    {
        static_cast<CGenericModel*>(getUnitModel())->setRimLighting(texture);
        if (m_pDataGroup != NULL)
        {
            std::wstring overrideTexture = m_pDataGroup->GetDataValue(L"TEXTURE_OVERRIDE", EMPTY_WSTRING);
            if (!overrideTexture.empty())
                static_cast<CGenericModel*>(getUnitModel())->setTextureOverride(overrideTexture);
        }
    }
}

void CItem::updateOpacity(float elapsed, bool force)
{
    if (m_bItemFlag218)
        return;
    if (m_bRequestedVisible)
    {
        if (!m_bVisible)
            setVisible(true, true);
        if (!(m_fOpacity < 1.0f) && !force)
            return;
        m_fOpacity = std::min(m_fOpacity + elapsed * 1.5f, 1.0f);
    }
    else
    {
        if (!(m_fOpacity > 0.0f) && !force)
        {
            if (m_bVisible)
                setVisible(false, true);
            return;
        }
        if (!m_bInFadeRange)
            m_fOpacity = 0.0f;
        else
            m_fOpacity = std::max(m_fOpacity - elapsed, 0.0f);
    }
    if (getUnitModel() != NULL)
        static_cast<CGenericModel*>(getUnitModel())->setOpacity(m_fOpacity);
}

void CItem::updateAnimation(float elapsed)
{
    if (!m_bInActiveRange)
        setVisible(false);
    else
        updateCullingBounds();
    if ((m_bVisible || !(m_fForcedActiveTime <= 0.0f)) && getUnitModel() != NULL)
    {
        static_cast<CGenericModel*>(getUnitModel())->updateAnimation(elapsed, false);
        for (unsigned int i = 0; i < static_cast<unsigned int>(static_cast<CGenericModel*>(getUnitModel())->getAnimationEvents().size()); ++i)
        {
            if (static_cast<CGenericModel*>(getUnitModel())->getAnimationEvents()[i]->getEventCode() == 10)
            {
                m_bBlocksPath = true;
                m_bPathingFlag19C = true;
                addToAvoidanceMap(*getLevel());
            }
            if (static_cast<CGenericModel*>(getUnitModel())->getAnimationEvents()[i]->getEventCode() == 11)
            {
                m_bBlocksPath = false;
                removeFromAvoidanceMap(*getLevel());
            }
        }
    }
}
