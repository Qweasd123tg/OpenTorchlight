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
