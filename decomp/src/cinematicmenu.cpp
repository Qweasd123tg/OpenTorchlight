#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "CinematicMenu.h"

bool CCinematicMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (m_bUnknown30) {
        if (function == static_cast<ELayoutFunction>(10)) {
            m_pGameUI->requestSetGameState(static_cast<EGameState>(1), static_cast<EMenu>(0));
            m_bUnknown32 = true;
        }
        m_bUnknown32 = true;
    }
    return true;
}

CCinematicMenu::~CCinematicMenu()
{
}
