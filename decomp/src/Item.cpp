#include "EmptyStrings.h"
#include "Item.h"
#include "ItemSaveState.h"
#include "CullingBounds.h"
#include "Editor.h"
#include <OgreCamera.h>
#include <OgreAxisAlignedBox.h>
#include "UnitSpawner.h"
#include "EditorScene.h"
#include "SoundBank.h"
#include "DataGroup.h"
#include "GenericModel.h"
#include "Keyframe.h"
#include "GameGlobals.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include <cmath>
#include "StringUtilities.h"
#include <CEGUIPropertyHelper.h>
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

void CItem::setItemTextHighlighted(bool highlighted)
{
    if (getHighlighted() == highlighted || m_pItemText == NULL)
        return;
    if (getIsQuestUnit())
    {
        m_pItemText->setProperty("TextColour", STRINGS::StringConvertToUTF8(CGameGlobals::getSingleton()->getQuestColor(highlighted)));
    }
    else if (ISA(UNITTYPES::UNIQUE))
    {
        m_pItemText->setProperty("TextColour", STRINGS::StringConvertToUTF8(CGameGlobals::getSingleton()->getUniqueColor(highlighted)));
    }
    else if (isMagical() || ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE))
    {
        if (ISA(UNITTYPES::MAGIC))
            m_pItemText->setProperty("TextColour", STRINGS::StringConvertToUTF8(CGameGlobals::getSingleton()->getRareColor(highlighted)));
        else
            m_pItemText->setProperty("TextColour", STRINGS::StringConvertToUTF8(CGameGlobals::getSingleton()->getRandomEnchantColor(highlighted)));
    }
    else
    {
        CEGUI::colour color = highlighted ? CEGUI::colour(1.0f,1.0f,1.0f,1.0f) : CEGUI::colour(0.8f,0.8f,0.8f,1.0f);
        m_pItemText->setProperty("TextColour", CEGUI::PropertyHelper::colourToString(color));
    }
    if (highlighted)
        m_pItemText->moveToFront();
}

void CItem::calculateActiveRange(const Ogre::Vector3& viewer)
{
    if (m_fForcedActiveTime > 0.0f)
    {
        m_bInActiveRange = true;
        m_bInFadeRange = true;
        return;
    }
    if (!m_bRangeEnabled)
    {
        m_bInActiveRange = false;
        return;
    }
    Ogre::Vector3 position = getPosition(true);
    float x = viewer.x - position.x;
    float z = viewer.z - position.z;
    float distance = std::sqrt(x*x + 0.0f + z*z);
    float activeRange;
    if (getLevel() == NULL || getLevel()->getLevelTemplateData() == NULL || getLevel()->getLevelTemplateData()->getUnitLightFade())
        activeRange = ISA(UNITTYPES::INTERACTABLE) ? CGameGlobals::getSingleton()->getTriggerNearRange() : CGameGlobals::getSingleton()->getIndoorUnitActiveRange();
    else
        activeRange = CGameGlobals::getSingleton()->getOutdoorUnitActiveRange();
    if (distance > activeRange)
    {
        m_bInActiveRange = false;
        float nearRange = ISA(UNITTYPES::INTERACTABLE) ? CGameGlobals::getSingleton()->getTriggerNearRange() : CGameGlobals::getSingleton()->getUnitNearRange();
        m_bInFadeRange = distance <= nearRange;
    }
    else
    {
        m_bInActiveRange = true;
        m_bInFadeRange = true;
    }
    if (getCastsShadows() && getUnitModel() != NULL)
    {
        bool shadows = !(distance > CGameGlobals::getSingleton()->getUnitShadowRange() || std::fabs(viewer.y-position.y) > 4.0f);
        static_cast<CGenericModel*>(getUnitModel())->setCastsShadows(shadows);
    }
}

void CItem::fillSaveState(CItemSaveState& state, int index, bool flag)
{
    state.m_vLocalPosition = getPosition(false);
    if (m_iRoomIndex == -1)
        m_iRoomIndex = getLevel()->getRoomIndexThatPositionIsIn(getPosition(true));
    state.m_iRoomIndex = m_iRoomIndex;
    state.m_iUnitValue60 = m_iUnitValue1A0;
    state.m_iQuestGuid = m_iQuestGuid;
    state.m_iQuestState = m_iQuestState;
    state.m_iOriginalGuid = getOriginalGuid();
    state.m_iParentHierarchyHash = getParentHierarchyHashCode();
    state.m_bSaveFlag48 = m_bSaveFlag191;
    state.m_vWorldPosition = getPosition(true);
    state.m_mOrientation = getOrientation();
    state.m_iSpawnerGuid = m_iSpawnerGuid;
    state.m_iIndex = index;
    state.m_bSaveFlag5C = flag;
    state.m_sItemName = m_sItemName;
    state.m_bEnabled = getEnabled();
    state.m_bItemFlag17C = m_bItemFlag1F2;
    state.m_bBlocksPath = m_bBlocksPath;
}

void CItem::applySaveState(CItemSaveState& state)
{
    setPosition(state.m_vLocalPosition);
    setOrientation(state.m_mOrientation, false);
    m_sItemName = state.m_sItemName;
    setEnabled(state.m_bEnabled);
    m_bItemFlag1F2 = state.m_bItemFlag17C;
    m_iQuestGuid = state.m_iQuestGuid;
    m_iQuestState = state.m_iQuestState;
    m_iRoomIndex = state.m_iRoomIndex;
    if (state.m_iSpawnerGuid != 0xffffffffLL && getLevel() != NULL)
    {
        CLevel* level = getLevel();
        int rooms = static_cast<int>(level->getRoomScenes().size());
        for (int i = 0; i < rooms; ++i)
        {
            CEditorScene* scene = level->getRoomScenes()[i];
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Unit Spawner", &objects);
            int count = static_cast<int>(objects.size());
            for (int j = 0; j < count; ++j)
            {
                CUnitSpawner* spawner = dynamic_cast<CUnitSpawner*>(objects[j]);
                if (spawner != NULL && spawner->getOriginalGuid() == state.m_iSpawnerGuid)
                    spawner->addSpawnedUnit(this);
            }
        }
    }
    m_bBlocksPath = state.m_bBlocksPath;
}

void CItem::snapToGround()
{
    if (getLevel() == NULL)
        return;
    removeFromAvoidanceMap(*getLevel());
    Ogre::Vector3 top = getPosition(true);
    Ogre::Vector3 bottom = top;
    float originalY = top.y;
    top.y = 100.0f;
    bottom.y = -100.0f;
    Ogre::Vector3 hit, normal, extra;
    unsigned int type;
    int attempts = 0;
    for (; attempts < 30; ++attempts)
    {
        if (getLevel()->rayCollision(top, bottom, hit, normal, type, extra, false) && type != 100)
        {
            top = hit;
            break;
        }
        Ogre::Vector3 next = getLevel()->randomOpenPosition(top, 4.0f, false);
        top.x = next.x;
        top.z = next.z;
        bottom.x = next.x;
        bottom.z = next.z;
        top.y = 100.0f;
        bottom.y = -100.0f;
    }
    if (attempts >= 30)
        top.y = originalY;
    setPosition(top);
    extractOrientationVectors();
    addToAvoidanceMap(*getLevel());
    setVisible(m_bVisible);
}

void CItem::update(Ogre::Camera* camera, const Ogre::Vector3& viewer, float elapsed)
{
    CBaseUnit::update(camera, viewer, elapsed);
    if (m_fForcedActiveTime >= 0.0f)
        m_fForcedActiveTime -= elapsed;
    if (m_pSoundBank != NULL)
        m_pSoundBank->update(elapsed, m_pSceneNode);
    calculateActiveRange(viewer);
    updateOpacity(elapsed, false);
    if (!m_bInActiveRange && elapsed != 1000.0f)
    {
        if (ISA(UNITTYPES::BREAKABLE) && m_bItemFlag218)
            m_bBaseUnitFlag190 = true;
        setVisible(false);
        return;
    }
    Ogre::AxisAlignedBox bounds(m_pCullingBounds->getWorldMinimum(), m_pCullingBounds->getWorldMaximum());
    if (elapsed == 1000.0f || camera->isVisible(bounds))
    {
        if (!m_bItemFlag218)
        {
            setVisible(true);
            if (getUnitModel() != NULL && (CEditor::getSingleton()->getFlags() & 2) != 0 && !m_bLevelLighting)
            {
                Ogre::Vector3 position = getPosition(true);
                float x = position.x - viewer.x;
                float z = position.z - viewer.z;
                float distance = std::sqrt(x*x + 0.0f + z*z) - 1.25f;
                float light = (10.5f - std::min(10.5f, distance)) / 10.5f;
                static_cast<CGenericModel*>(getUnitModel())->setLightOverride(light);
            }
        }
    }
    else
        setVisible(false, true);
}
