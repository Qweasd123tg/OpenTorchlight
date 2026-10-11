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

#include "GameClient.h"
bool CDifficultyMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (!m_bUnknown30 && m_bUnknown31) return true;
    if (function == 7) {
        setOpen(false);
        m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(m_bUnknownD0 ? 2 : 1));
    } else if (function >= 14 && function <= 17) {
        m_pGameUI->m_gameClient->m_startDifficulty = static_cast<int>(function) - 14;
        setOpen(false);
        m_pGameUI->m_gameClient->m_startHardcore = m_hardcoreCheckbox->isSelected();
        m_pGameUI->requestSetGameState(static_cast<EGameState>(m_bUnknownD0 ? 4 : 3), static_cast<EMenu>(0));
    }
    return true;
}
