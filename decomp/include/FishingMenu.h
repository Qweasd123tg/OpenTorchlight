#ifndef OTL_FISHINGMENU_H
#define OTL_FISHINGMENU_H
#include "RunicCore.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CFishingMenu : public CRunicCore {
public:
    virtual ~CFishingMenu();
    CFishingMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecovered10[0x30];
};
typedef char check_CFishingMenu_size[sizeof(CFishingMenu)==0x40?1:-1];
#endif
