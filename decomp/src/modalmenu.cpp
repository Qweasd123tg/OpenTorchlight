#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "ModalMenu.h"

void CModalMenu::update(float elapsed)
{
    CDropdownMenu::update(elapsed);
}

void CModalMenu::setOpen(bool open)
{
    CDropdownMenu::setOpen(open);
}

bool CModalMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
    }
    return true;
}

bool CModalMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
        return CDropdownMenu::handle_CloseButton(event);
    }
    return true;
}
