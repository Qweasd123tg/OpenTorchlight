#ifndef OTL_WAYPOINTMENU_H
#define OTL_WAYPOINTMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CWaypointMenu : public CDropdownMenu {
public:
    virtual ~CWaypointMenu();
    CWaypointMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecoveredc0[0x358];
};
typedef char check_CWaypointMenu_size[sizeof(CWaypointMenu)==0x418?1:-1];
#endif
