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
        BroadcastEvent(0x65);
    else
        BroadcastEvent(0x64);
}

void CQuestController::setQuestAccepted(bool bIsAccepted)
{
    if (m_pQuest)
    {
        unsigned char* pAcceptDialogInteracted =
            reinterpret_cast<unsigned char*>(m_pQuest) + 0x26;

        if (bIsAccepted)
        {
            if (!*pAcceptDialogInteracted)
            {
                CQuestManager::getSingleton()->giveQuest(m_pQuest, NULL, true);
                *pAcceptDialogInteracted = 1;
            }
        }
        else if (*pAcceptDialogInteracted)
        {
            CQuestManager::getSingleton()->removeQuest(m_pQuest, false);
        }
    }
}

void CQuestController::menuEventOccured(void* pData,
                                         EMENU_TYPE menuType,
                                         EMENU_EVENT menuEvent)
{
    CQuestController* pThis = reinterpret_cast<CQuestController*>(
        reinterpret_cast<char*>(this) - 0x58);
    pThis->CQuestController::menuEventOccured(pData, menuType, menuEvent);
}

long long CQuestController::updateLevelObject(float fTimeDelta,
                                                Ogre::Camera* pCamera,
                                                const Ogre::Vector3& vPosition)
{
    CQuestController* pThis =
        reinterpret_cast<CQuestController*>(reinterpret_cast<char*>(this) - 0x60);
    return pThis->CQuestController::updateLevelObject(fTimeDelta, pCamera, vPosition);
}

CQuestController::CQuestController(CResourceManager* resourceManager)
    : CEditorBaseObject(),
      m_pResourceManager(resourceManager),
      m_pDataGroup(NULL),
      m_pUnit(NULL),
      m_iUnitSafePointer(-1),
      m_sCategory(*reinterpret_cast<const std::wstring*>(gRESOURCE_GROUP_NAMES + 8)),
      m_sUnitInteractWith(),
      m_pQuest(NULL),
      m_iQuestSafePointer(-1),
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
}
