#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "QuestController.h"
#include "EditorBaseObject.h"
#include "QuestManager.h"
#include "ResourceManager.h"
#include "BaseUnit.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"
#include "Quest.h"
#include "GameClient.h"
#include "GameUI.h"
#include "Level.h"
#include "Player.h"

typedef char QuestControllerLayout[(sizeof(CQuestController) == 0xb8 &&
    __builtin_offsetof(CQuestController, m_pResourceManager) == 0x68 &&
    __builtin_offsetof(CQuestController, m_pDataGroup) == 0x70 &&
    sizeof(TSafePointer<CBaseUnit>) == 0x10 &&
    sizeof(TSafePointer<CQuest>) == 0x10 &&
    __builtin_offsetof(CQuestController, m_unit) == 0x78 &&
    __builtin_offsetof(CQuestController, m_sCategory) == 0x88 &&
    __builtin_offsetof(CQuestController, m_sUnitInteractWith) == 0x90 &&
    __builtin_offsetof(CQuestController, m_quest) == 0x98 &&
    __builtin_offsetof(CQuestController, m_sQuestName) == 0xa8 &&
    __builtin_offsetof(CQuestController, m_bFirstUpdate) == 0xb0 &&
    __builtin_offsetof(CQuestController, m_bBroadcastEventsOnLoad) == 0xb1 &&
    __builtin_offsetof(CQuestController, m_bPlayerEnabled) == 0xb2 &&
    __builtin_offsetof(CQuestController, m_bPlayerGetsDisabled) == 0xb3 &&
    __builtin_offsetof(CQuestController, m_eMenuEvent) == 0xb4) ? 1 : -1];

void CQuestController::questHasBeenAccepted(bool bIsAccepted)
{
    if (bIsAccepted)
        BroadcastEvent(0x62);
    else
        BroadcastEvent(0x63);
}

void CQuestController::questHasBeenAbandoned()
{
    BroadcastEvent(0x66);
}

void CQuestController::questHasBeenCompleted(bool bIsComplete)
{
    if (bIsComplete)
        BroadcastEvent(0x64);
    else
        BroadcastEvent(0x65);
}

void CQuestController::setQuestAccepted(bool bIsAccepted)
{
    CQuest* quest = m_quest.getObject();
    if (!quest)
        return;
    if (bIsAccepted)
    {
        if (!quest->m_questAccepted)
        {
            CQuestManager::getSingleton()->giveQuest(quest, NULL, true);
            m_quest.getObject()->setQuestAcceptDialogInteracted(true);
        }
    }
    else if (quest->m_questAccepted)
        CQuestManager::getSingleton()->removeQuest(quest, false);
}

void CQuestController::menuEventOccured(void*, EMENU_TYPE menuType,
                                       EMENU_EVENT menuEvent)
{
    if (menuType == 0 && m_pResourceManager->getGameClient()->getPlayer())
    {
        m_eMenuEvent = menuEvent;
        m_pResourceManager->getLevel()->addUpdateObject(this);
        if (m_bPlayerGetsDisabled)
            m_pResourceManager->getGameClient()->getPlayer()->setEnabled(m_bPlayerEnabled);
    }
}

long long CQuestController::updateLevelObject(float, Ogre::Camera*,
                                             const Ogre::Vector3&)
{
    if (m_bFirstUpdate && m_bBroadcastEventsOnLoad)
    {
        m_bFirstUpdate = false;
        questHasBeenAccepted(static_cast<unsigned char>(CQuestManager::getSingleton()->getQuestIsActive(m_sQuestName)) != 0);
        questHasBeenCompleted(static_cast<unsigned char>(CQuestManager::getSingleton()->getQuestComplete(m_sQuestName)) != 0);
    }
    else
    {
        BroadcastEvent(0x5c);
        if (m_eMenuEvent == 3)
            BroadcastEvent(0x5d);
        else if (m_eMenuEvent == 4)
            BroadcastEvent(0x5e);
        CGameUI::getSingleton()->removeMenuListener(static_cast<EMENU_TYPE>(0), this);
    }
    return 0;
}

CQuestController::CQuestController(CResourceManager* resourceManager)
    : CEditorBaseObject(),
      m_pResourceManager(resourceManager),
      m_pDataGroup(NULL),
      m_unit(),
      m_sCategory(*reinterpret_cast<const std::wstring*>(gRESOURCE_GROUP_NAMES + 8)),
      m_sUnitInteractWith(),
      m_quest(),
      m_sQuestName(EMPTY_WSTRING),
      m_bFirstUpdate(true),
      m_bBroadcastEventsOnLoad(false),
      m_bPlayerEnabled(true),
      m_bPlayerGetsDisabled(false),
      m_eMenuEvent(static_cast<EMENU_EVENT>(5))
{
}

CQuestController::~CQuestController()
{
    if (m_quest.getObject())
        m_quest.getObject()->removeQuestControllerListerner(this);
    if (CGameUI::getSingleton())
        CGameUI::getSingleton()->removeMenuListener(static_cast<EMENU_TYPE>(0), this);
    m_quest.setObject(NULL);
}
