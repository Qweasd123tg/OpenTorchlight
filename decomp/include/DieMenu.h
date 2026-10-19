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
    virtual void setOpen(bool);
    void createMenus();
    virtual void update(float elapsed);
    virtual bool onClick(ELayoutFunction function, std::wstring text);
    bool handle_ExitButton(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);

    virtual ~CDieMenu();
    CDieMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    bool m_returnToMainMenu;
    bool m_returnToTown;
    unsigned char m_PaddingC2[2];
    int m_returnToTownOption; // +0xc4
    CEGUI::Window* m_windowC8; // +0xc8
    CEGUI::Window* m_windowD0; // +0xd0
    CEGUI::Window* m_windowD8; // +0xd8
    CEGUI::Window* m_windowE0; // +0xe0
    CEGUI::Window* m_windowE8; // +0xe8
    CEGUI::Window* m_windowF0; // +0xf0
    int m_famePenalty; // +0xf8
    int m_experiencePenalty; // +0xfc
    int m_goldPenalty; // +0x100
    unsigned char m_Padding104[4];
};
typedef char check_CDieMenu_size[sizeof(CDieMenu)==0x108?1:-1];
#endif
