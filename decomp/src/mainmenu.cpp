#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "MainMenu.h"

bool CMainMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    CGameUI* ui = m_pGameUI;
    ui->m_bExitButtonPressed = true;
    ui->closeAll();
    return true;
}

bool CMainMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    return CDropdownMenu::handle_CloseButton(event);
}

CMainMenu::CMainMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 1), m_bUnknownC0(false), m_bUnknownC1(false)
{
    createMenus();
}

bool CMainMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (!m_bUnknown30 && m_bUnknown31) return true;
    switch (static_cast<int>(function)) {
    case 1: {
        CGameUI* ui = m_pGameUI;
        ui->m_bExitButtonPressed = true;
        ui->closeAll();
        break;
    }
    case 3: m_pGameUI->requestSetGameState(static_cast<EGameState>(2), static_cast<EMenu>(0)); setOpen(false); break;
    case 4: m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(1)); setOpen(false); break;
    case 5: {
        bool canLoad = m_pGameUI->canLoad();
        m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(canLoad ? 3 : 1));
        setOpen(false); break;
    }
    case 64: m_creditsWindow->setVisible(true); break;
    case 65: m_creditsWindow->setVisible(false); break;
    case 66: if (m_extraWindow) m_extraWindow->setVisible(true); break;
    case 67: if (m_extraWindow) m_extraWindow->setVisible(false); break;
    case 94: m_pGameUI->toggleSettings(); break;
    }
    return true;
}
