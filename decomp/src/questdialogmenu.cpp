#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "GameUI.h"
#include "Player.h"
#include "Quest.h"
#include "QuestDialog.h"
#include "QuestDialogMenu.h"
#include "QuestManager.h"
#include "QuestRewards.h"

bool CQuestDialogMenu::handle_MouseThrough(const CEGUI::EventArgs&)
{
    m_mouseThrough = false;
    return true;
}

const Ogre::Vector3& CQuestDialogMenu::getCameraOffset()
{
    return m_dialog ? m_dialog->m_cameraOffset : Ogre::Vector3::ZERO;
}

bool CQuestDialogMenu::acceptQuest(CBaseUnit* unit)
{
    if (!m_dialog || m_dialog->m_pQuest->m_questAccepted)
        return false;
    static_cast<CPlayer*>(m_pGameUI->getCharacter())->getQuestManager()->giveQuest(
        m_dialog->m_pQuest, unit ? unit : m_unit, true);
    broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(3));
    broadcastAcceptedOrDeclined(true, unit);
    return true;
}

bool CQuestDialogMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    if (m_unit)
        m_unit->BroadcastEvent(95);
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(static_cast<EAIState>(2));
    if (m_acceptOnExit)
        acceptQuest(NULL);
    m_acceptOnExit = false;
    broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(1));
    broadcastAcceptedOrDeclined(false, NULL);
    return true;
}

bool CQuestDialogMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button != CEGUI::LeftButton)
        return true;
    if (m_unit)
        m_unit->BroadcastEvent(95);
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(static_cast<EAIState>(2));
    if (m_acceptOnExit)
        acceptQuest(NULL);
    m_acceptOnExit = false;
    broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(1));
    broadcastAcceptedOrDeclined(false, NULL);
    return CDropdownMenu::handle_CloseButton(event);
}

CQuestDialogMenu::~CQuestDialogMenu()
{
    m_unit = NULL;
}

bool CQuestDialogMenu::handle_MouseOver(const CEGUI::EventArgs& event)
{
    if (m_dialog)
    {
        int index = *static_cast<int*>(static_cast<const CEGUI::WindowEventArgs&>(event).window->getUserData());
        CQuest* quest = m_dialog->m_pQuest;
        if (quest)
        {
            TArrayList<CBaseUnit*>* items = quest->m_pQuestRewards->getRewardItems();
            if (index < static_cast<int>(items->size()))
                m_hoveredReward = (*items)[index];
        }
        m_mouseThrough = true;
    }
    return true;
}

bool CQuestDialogMenu::handle_MouseOut(const CEGUI::EventArgs& event)
{
    if (m_dialog)
    {
        int index = *static_cast<int*>(static_cast<const CEGUI::WindowEventArgs&>(event).window->getUserData());
        CQuest* quest = m_dialog->m_pQuest;
        if (quest)
        {
            TArrayList<CBaseUnit*>* items = quest->m_pQuestRewards->getRewardItems();
            if (index < static_cast<int>(items->size()))
            {
                if (m_hoveredReward == (*items)[index])
                    m_hoveredReward = NULL;
            }
        }
    }
    return true;
}

#include "StringTranslate.h"
CQuestDialogMenu::CQuestDialogMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 1), m_unit(NULL), m_dialogWindow(NULL), m_promptWindow(NULL), m_acceptWindow(NULL), m_declineWindow(NULL), m_rewardWindow(NULL), m_rewardTextWindow(NULL), m_detailWindow(NULL), m_iconWindow(NULL), m_iconParent(NULL), m_dialog(NULL), m_textIndex(0), m_textLength(0), m_dialogName(), m_displayedCharacters(0), m_hoveredReward(NULL), m_mouseThrough(false), m_dialogActive(true), m_acceptOnExit(false), m_resultBroadcast(false), m_safeOwner(), m_textSpeed(1.0f)
{
    static std::wstring g_Dialog;
    if (g_Dialog.empty())
        g_Dialog = CStringTranslate::getSinglton()->getTranslateString(L"Dialog");
    setTitle(g_Dialog);
    createMenus();
}
#include "BaseUnit.h"

void CQuestDialogMenu::broadcastAcceptedOrDeclined(bool accepted, CBaseUnit* unit)
{
    if (!unit) unit = m_unit;
    if (!unit) return;
    if (m_dialog && !m_resultBroadcast) {
        m_resultBroadcast = true;
        unit->BroadcastEvent(accepted ? 93 : 94);
    }
    unit->BroadcastEvent(92);
}

#include "GameClient.h"
#include "Item.h"
void CQuestDialogMenu::setOpen(bool open)
{
    if (m_bUnknown30 != open) m_pGameUI->setInteractiveMenuVisible(open);
    if (m_bUnknown30) {
        if (!open) {
            if (m_dialog) m_dialog->stopDialogSound();
            CGameClient* client = m_pGameUI->getGameClient();
            client->m_selectedItem.setObject(NULL); client->m_targetItem.setObject(NULL);
            client->m_selectedCharacter.setObject(NULL); client->m_targetCharacter.setObject(NULL);
            static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
            m_bUnknown31 = true; m_hoveredReward = NULL;
            if (m_unit) m_unit->setEnabled(m_dialogActive);
            m_unit = NULL;
        }
    } else if (open) {
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
        static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
        static_cast<CEGUI::Window*>(m_pUnknown10)->addChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        static_cast<CEGUI::Window*>(m_pUnknown18)->moveToBack();
    }
    m_bUnknown30 = open; m_resultBroadcast = false;
}
