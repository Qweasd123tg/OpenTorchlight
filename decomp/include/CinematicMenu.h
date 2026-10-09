#ifndef OTL_CINEMATICMENU_H
#define OTL_CINEMATICMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CCinematicMenu : public CDropdownMenu {
public:
    virtual ~CCinematicMenu();
    CCinematicMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecoveredc0[0x40];
};
typedef char check_CCinematicMenu_size[sizeof(CCinematicMenu)==0x100?1:-1];
#endif
