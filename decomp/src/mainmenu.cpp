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
