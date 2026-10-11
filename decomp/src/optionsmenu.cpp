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

bool COptionsMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (m_bUnknown30) {
        switch (static_cast<int>(function)) {
        case 6: m_bUnknown32 = true; break;
        case 94: m_pGameUI->toggleSettings(); m_bUnknown32 = true; break;
        case 0: m_returnToMainMenu = true; m_bUnknown32 = true; break;
        }
    }
    return true;
}

#include "StringTranslate.h"
COptionsMenu::COptionsMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 0), m_returnToMainMenu(false)
{
    createMenus();
    static std::wstring g_Options;
    if (g_Options.empty())
        g_Options = CStringTranslate::getSinglton()->getTranslateString(L"Options");
    setTitle(g_Options);
}
