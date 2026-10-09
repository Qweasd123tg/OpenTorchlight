#ifndef OTL_OPTIONSMENU_H
#define OTL_OPTIONSMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class COptionsMenu : public CDropdownMenu {
public:
    virtual ~COptionsMenu();
    COptionsMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecoveredc0[0x8];
};
typedef char check_COptionsMenu_size[sizeof(COptionsMenu)==0xc8?1:-1];
#endif
