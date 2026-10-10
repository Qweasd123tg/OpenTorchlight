#ifndef OTL_TIPMENU_H
#define OTL_TIPMENU_H
#include "DropdownMenu.h"
#include <elements/CEGUICheckbox.h>
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CTipMenu : public CDropdownMenu {
public:
    virtual bool onClick(ELayoutFunction function,std::wstring text);
    virtual void update(float elapsed);
    virtual void setOpen(bool open);

    bool handle_ExitButton(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);

    virtual ~CTipMenu();
    CTipMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    unsigned char m_PaddingC0[0x10];
    CEGUI::Checkbox* m_showTipsCheckbox; // +0xd0
    unsigned char m_PaddingD8[0x10];
};
typedef char check_CTipMenu_size[sizeof(CTipMenu)==0xe8?1:-1];
#endif
