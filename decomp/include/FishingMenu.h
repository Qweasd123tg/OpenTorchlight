#ifndef OTL_FISHINGMENU_H
#define OTL_FISHINGMENU_H
#include "RunicCore.h"
#include "GameUI.h"
#include <CEGUIEventArgs.h>
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CFishingMenu : public CRunicCore {
public:
    virtual ~CFishingMenu();
    virtual void update(float);
    virtual void setVisible(bool);
    virtual bool processInput(void*,float,bool);
    virtual void createMenus();
    virtual bool onClick(ELayoutFunction function);
    bool handle_onClick(const CEGUI::EventArgs& event);
    CFishingMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    CEGUI::Window* m_parent; // +0x10
    CEGUI::Window* m_window; // +0x18
    unsigned char m_Padding20[0x8];
    CResourceManager* m_resources; // +0x28
    bool m_visible; // +0x30
    unsigned char m_Padding31[0x7];
    CGameUI* m_gameUI; // +0x38
};
typedef char check_CFishingMenu_size[sizeof(CFishingMenu)==0x40?1:-1];
#endif
