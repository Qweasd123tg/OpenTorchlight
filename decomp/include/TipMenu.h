#ifndef OTL_TIPMENU_H
#define OTL_TIPMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CTipMenu : public CDropdownMenu {
public:
    virtual ~CTipMenu();
    CTipMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecoveredc0[0x28];
};
typedef char check_CTipMenu_size[sizeof(CTipMenu)==0xe8?1:-1];
#endif
