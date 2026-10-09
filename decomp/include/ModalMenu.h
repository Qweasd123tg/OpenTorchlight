#ifndef OTL_MODALMENU_H
#define OTL_MODALMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CModalMenu : public CDropdownMenu {
public:
    virtual ~CModalMenu();
    CModalMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecoveredc0[0x38];
};
typedef char check_CModalMenu_size[sizeof(CModalMenu)==0xf8?1:-1];
#endif
