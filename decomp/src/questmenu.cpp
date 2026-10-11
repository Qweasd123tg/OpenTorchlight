#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "QuestMenu.h"

void CQuestMenu::setOwner(CCharacter* owner)
{
    m_owner = owner;
}

bool CQuestMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton)
        m_requestClose = true;
    return true;
}

bool CQuestMenu::handle_MouseThrough(const CEGUI::EventArgs&)
{
    m_mouseThrough = false;
    return true;
}

bool CQuestMenu::handle_QuestClick(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = static_cast<const CEGUI::WindowEventArgs&>(event).window;
    if (window && window->getID() != m_selectedQuestID) {
        m_selectedQuestID = window->getID();
        m_selectedQuestChanged = true;
    }
    return true;
}

bool CQuestMenu::onClick(ELayoutFunction function)
{
    if (m_allowAbandon && function == static_cast<ELayoutFunction>(8)) abandonQuest();
    return true;
}

bool CQuestMenu::processInput(void*,float,bool capture)
{
    if (capture) {
        if (m_requestClose) {
            setOpen(false);
            m_requestClose = false;
            return false;
        }
    } else m_hoveredReward = NULL;
    return true;
}

#include "Player.h"
#include "Quest.h"
#include "QuestManager.h"
#include "QuestRewards.h"

bool CQuestMenu::handle_onClick(const CEGUI::EventArgs& event)
{
    const CEGUI::MouseEventArgs& mouse = static_cast<const CEGUI::MouseEventArgs&>(event);
    CEGUI::Window* window = mouse.window;
    if (mouse.button == CEGUI::LeftButton && window)
        return onClick(*static_cast<ELayoutFunction*>(window->getUserData()));
    return true;
}

bool CQuestMenu::handle_MouseOver(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = static_cast<const CEGUI::WindowEventArgs&>(event).window;
    if (window && m_owner) {
        int reward = *static_cast<int*>(window->getUserData());
        CQuestManager* manager = static_cast<CPlayer*>(m_owner)->getQuestManager();
        if (manager && m_selectedQuestIndex < static_cast<int>(reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18).size())) {
            CQuest* quest = reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[m_selectedQuestIndex];
            TArrayList<CBaseUnit*>* items = quest->m_pQuestRewards->getRewardItems();
            if (reward < static_cast<int>(items->size())) m_hoveredReward = (*items)[reward];
        }
        m_mouseThrough = true;
    }
    return true;
}

bool CQuestMenu::handle_MouseOut(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = static_cast<const CEGUI::WindowEventArgs&>(event).window;
    if (window && m_owner) {
        int reward = *static_cast<int*>(window->getUserData());
        CQuestManager* manager = static_cast<CPlayer*>(m_owner)->getQuestManager();
        if (manager && m_selectedQuestIndex < static_cast<int>(reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18).size())) {
            CQuest* quest = reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[m_selectedQuestIndex];
            TArrayList<CBaseUnit*>* items = quest->m_pQuestRewards->getRewardItems();
            if (reward < static_cast<int>(items->size()) && m_hoveredReward == (*items)[reward])
                m_hoveredReward = NULL;
        }
    }
    return true;
}

#include "GenericModel.h"
#include "SoundBank.h"
CQuestMenu::~CQuestMenu()
{
    if (m_model) { delete m_model; m_model = NULL; }
    if (m_soundBank) { delete m_soundBank; m_soundBank = NULL; }
}

void CQuestMenu::abandonQuest()
{
    CQuestManager* manager = static_cast<CPlayer*>(m_owner)->getQuestManager();
    if (!manager) return;
    unsigned int visible = 0;
    for (int i = 0; i < static_cast<int>(reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18).size()); ++i) {
        if (!reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[i]->getQuestDetails().empty()) {
            if (visible == m_selectedQuestID && reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[i]->m_bUnknown208) {
                m_soundBank->playSample(35, NULL, 0.0f, 0.0f, false);
                manager->removeQuest(reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[i], true);
                updateLayout(); return;
            }
            ++visible;
        }
    }
}
