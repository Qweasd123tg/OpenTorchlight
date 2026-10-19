#ifndef OTL_WAYPOINTMENU_H
#define OTL_WAYPOINTMENU_H
#include "DropdownMenu.h"
#include <vector>
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CWaypointMenu : public CDropdownMenu {
public:
    virtual bool onClick(ELayoutFunction, std::wstring);
    virtual void setOpen(bool);
    void createMenus();
    virtual void update(float elapsed);
    bool handle_ExitButton(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);

    virtual ~CWaypointMenu();
    CWaypointMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    bool m_bUnknownC0;
    bool m_bUnknownC1;
    unsigned char m_PaddingC2[6];
    CEGUI::Window* m_destinationWindows[50]; // +0xc8
    CEGUI::Window* m_floorWindows[50]; // +0x258
    std::vector<std::wstring> m_destinations; // +0x3e8
    std::vector<int> m_floors; // +0x400
};
typedef char check_CWaypointMenu_size[sizeof(CWaypointMenu)==0x418?1:-1];
#endif
