#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "DifficultyMenu.h"

bool CDifficultyMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    CGameUI* ui = m_pGameUI;
    ui->m_bExitButtonPressed = true;
    ui->closeAll();
    return true;
}

bool CDifficultyMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    return CDropdownMenu::handle_CloseButton(event);
}

void CDifficultyMenu::update(float elapsed)
{
    CDropdownMenu::update(elapsed);
}

void CDifficultyMenu::setOpen(bool open)
{
    CDropdownMenu::setOpen(open);
    if (open) m_hardcoreCheckbox->setSelected(false);
}

CDifficultyMenu::CDifficultyMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 1), m_bUnknownC0(false), m_bUnknownC1(false), m_bUnknownD0(false)
{
    createMenus();
}
