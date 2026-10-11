#include <CEGUIInputEvent.h>
#include "WaypointMenu.h"
#include "GameClient.h"
#include "Character.h"
#include "Item.h"

void CWaypointMenu::update(float)
{
    if (!m_bUnknown30 && !m_bUnknown31) {
        m_bUnknown31 = true;
        CGameClient* client = m_pGameUI->m_gameClient;
        client->m_selectedItem.setObject(NULL);
        client->m_targetItem.setObject(NULL);
        client->m_selectedCharacter.setObject(NULL);
        client->m_targetCharacter.setObject(NULL);
    }
}

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
