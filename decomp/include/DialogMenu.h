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
    bool handle_ExitButton(const CEGUI::EventArgs& event);
    bool handle_CloseButton(const CEGUI::EventArgs& event);
    virtual bool onClick(ELayoutFunction function, std::wstring text);
    virtual void update(float elapsed);
    virtual void setOpen(bool open);

    virtual ~CDialogMenu();
    CDialogMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    unsigned char m_PaddingC0[0x30];
    CBaseUnit* m_dialogOwner; // +0xf0
};
typedef char check_CDialogMenu_size[sizeof(CDialogMenu)==0xf8?1:-1];
#endif
