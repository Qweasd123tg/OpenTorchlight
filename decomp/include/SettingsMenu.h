#ifndef OTL_SETTINGSMENU_H
#define OTL_SETTINGSMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CSettingsMenu : public CDropdownMenu {
public:
    void createMenus();
    virtual ~CSettingsMenu();
    virtual bool onClick(ELayoutFunction function,std::wstring text);
    virtual void update(float elapsed);
    virtual void setOpen(bool open);
    CSettingsMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    unsigned char m_PaddingC0[0x1];
    bool m_applyChanges; // +0xc1
    unsigned char m_PaddingC2[6];
    CEGUI::Window* m_windowC8; // +0xc8
    CEGUI::Window* m_windowD0; // +0xd0
    CEGUI::Window* m_windowD8; // +0xd8
    CEGUI::Window* m_windowE0; // +0xe0
    CEGUI::Window* m_windowE8; // +0xe8
    CEGUI::Window* m_windowF0; // +0xf0
    CEGUI::Window* m_windowF8; // +0xf8
    CEGUI::Window* m_window100; // +0x100
    CEGUI::Window* m_window108; // +0x108
    CEGUI::Window* m_window110; // +0x110
    CEGUI::Window* m_window118; // +0x118
    CEGUI::Window* m_window120; // +0x120
    CEGUI::Window* m_window128; // +0x128
    CEGUI::Window* m_window130; // +0x130
    CEGUI::Window* m_window138; // +0x138
    CEGUI::Window* m_window140; // +0x140
    CEGUI::Window* m_window148; // +0x148
};
typedef char check_CSettingsMenu_size[sizeof(CSettingsMenu)==0x150?1:-1];
#endif
