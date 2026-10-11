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
    unsigned char m_PaddingC8[0x30];
    int m_famePenalty; // +0xf8
    int m_experiencePenalty; // +0xfc
    int m_goldPenalty; // +0x100
    unsigned char m_Padding104[4];
};
typedef char check_CDieMenu_size[sizeof(CDieMenu)==0x108?1:-1];
#endif
