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
    virtual void update(float elapsed);
    virtual void setOpen(bool open);
    virtual bool onClick(ELayoutFunction function, std::wstring text);

    virtual ~CCinematicMenu();
    CCinematicMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    unsigned char m_PaddingC0[0x20];
    std::string m_cinematicName; // +0xe0
    unsigned char m_PaddingE8[0x18];
};
typedef char check_CCinematicMenu_size[sizeof(CCinematicMenu)==0x100?1:-1];
#endif
