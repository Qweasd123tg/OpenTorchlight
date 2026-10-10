#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "OptionsMenu.h"

bool COptionsMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
    CGameUI* ui = m_pGameUI;
    ui->m_bExitButtonPressed = true;
    ui->closeAll();
    }
    return true;
}

bool COptionsMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    return CDropdownMenu::handle_CloseButton(event);
}

void COptionsMenu::update(float elapsed)
{
    bool closing = m_bUnknown31;
    CDropdownMenu::update(elapsed);
    if (closing != m_bUnknown31 && m_returnToMainMenu) {
        m_returnToMainMenu = false;
        m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(0));
    }
}
