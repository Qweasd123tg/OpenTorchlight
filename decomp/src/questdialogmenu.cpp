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
