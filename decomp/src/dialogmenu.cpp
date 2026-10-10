#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "DialogMenu.h"

bool CDialogMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
    return true;
}

bool CDialogMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
        return CDropdownMenu::handle_CloseButton(event);
    }
    return true;
}

void CDialogMenu::update(float elapsed)
{
    bool closing = m_bUnknown31;
    CDropdownMenu::update(elapsed);
    if (!closing && m_bUnknown31) m_dialogOwner = NULL;
}

void CDialogMenu::setOpen(bool open)
{
    if (m_bUnknown30 != open) m_pGameUI->setInteractiveMenuVisible(open);
    CDropdownMenu::setOpen(open);
}
