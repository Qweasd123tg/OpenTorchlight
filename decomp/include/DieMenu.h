#ifndef OTL_DIEMENU_H
#define OTL_DIEMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CDieMenu : public CDropdownMenu {
public:
    bool handle_ExitButton(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);

    virtual ~CDieMenu();
    CDieMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecoveredc0[0x48];
};
typedef char check_CDieMenu_size[sizeof(CDieMenu)==0x108?1:-1];
#endif
