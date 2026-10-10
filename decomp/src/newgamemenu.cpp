#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "NewGameMenu.h"

bool CNewGameMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    CGameUI* ui = m_pGameUI;
    ui->m_bExitButtonPressed = true;
    ui->closeAll();
    return true;
}

bool CNewGameMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    return CDropdownMenu::handle_CloseButton(event);
}

bool CNewGameMenu::handle_Submit(const CEGUI::EventArgs&)
{
    if (m_pUnknownD0->getText().length() != 0) m_pUnknownD8->activate();
    return true;
}

CNewGameMenu::CNewGameMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 1), m_bUnknownC0(false), m_bUnknownC1(false), m_bUnknownF8(false)
{
    createMenus();
}
