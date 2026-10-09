#ifndef OTL_SETTINGSMENU_H
#define OTL_SETTINGSMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CSettingsMenu : public CDropdownMenu {
public:
    virtual ~CSettingsMenu();
    CSettingsMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecoveredc0[0x90];
};
typedef char check_CSettingsMenu_size[sizeof(CSettingsMenu)==0x150?1:-1];
#endif
