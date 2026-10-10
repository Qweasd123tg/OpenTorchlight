#include "SettingsMenu.h"

bool CSettingsMenu::onClick(ELayoutFunction function,std::wstring)
{
    if (m_bUnknown30) {
        if (function == static_cast<ELayoutFunction>(8)) m_bUnknown32 = true;
        else if (function == static_cast<ELayoutFunction>(9)) { m_applyChanges = true; m_bUnknown32 = true; }
        setOpen(false);
    }
    return true;
}
