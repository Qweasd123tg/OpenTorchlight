#ifndef OTL_DIALOGMENU_H
#define OTL_DIALOGMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CDialogMenu : public CDropdownMenu {
public:
    virtual ~CDialogMenu();
    CDialogMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecoveredc0[0x38];
};
typedef char check_CDialogMenu_size[sizeof(CDialogMenu)==0xf8?1:-1];
#endif
