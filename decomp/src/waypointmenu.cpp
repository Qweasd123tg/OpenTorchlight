#include <CEGUIInputEvent.h>
#include "WaypointMenu.h"

bool CWaypointMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    CGameUI* ui = m_pGameUI;
    ui->m_bExitButtonPressed = true;
    ui->closeAll();
    return true;
}

bool CWaypointMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button != CEGUI::LeftButton) return true;
    return CDropdownMenu::handle_CloseButton(event);
}
