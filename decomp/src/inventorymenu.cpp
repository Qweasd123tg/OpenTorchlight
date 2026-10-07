#include "InventoryMenu.h"

bool CInventoryMenu::handle_RotateLeft(const CEGUI::EventArgs&)
{
    m_bRotateLeft = true;
    return true;
}

bool CInventoryMenu::handle_EndRotateLeft(const CEGUI::EventArgs&)
{
    m_bRotateLeft = false;
    return true;
}

bool CInventoryMenu::handle_RotateRight(const CEGUI::EventArgs&)
{
    m_bRotateRight = true;
    return true;
}

bool CInventoryMenu::handle_EndRotateRight(const CEGUI::EventArgs&)
{
    m_bRotateRight = false;
    return true;
}
