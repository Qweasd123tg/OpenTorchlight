#ifndef OTL_OPTIONSMENU_H
#define OTL_OPTIONSMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class COptionsMenu : public CDropdownMenu {
public:
    virtual bool onClick(ELayoutFunction function, std::wstring text);
    virtual void update(float elapsed);

    bool handle_ExitButton(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);

    virtual ~COptionsMenu();
    COptionsMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    bool m_returnToMainMenu; // +0xc0
    unsigned char m_PaddingC1[0x7];
};
typedef char check_COptionsMenu_size[sizeof(COptionsMenu)==0xc8?1:-1];
#endif
