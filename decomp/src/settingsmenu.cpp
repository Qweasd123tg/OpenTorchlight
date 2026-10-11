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

#include "StringTranslate.h"
CSettingsMenu::CSettingsMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 0), m_applyChanges(false)
{
    createMenus();
    static std::wstring g_Settings;
    if (g_Settings.empty())
        g_Settings = CStringTranslate::getSinglton()->getTranslateString(L"Settings");
    setTitle(g_Settings);
}
