#ifndef OTL_MODALMENU_H
#define OTL_MODALMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CModalMenu : public CDropdownMenu {
public:
    bool handle_ExitButton(const CEGUI::EventArgs& event);
    bool handle_CloseButton(const CEGUI::EventArgs& event);
    virtual bool onClick(ELayoutFunction function, std::wstring text);

    virtual void setOpen(bool open);

    virtual void update(float elapsed);

    virtual ~CModalMenu();
    CModalMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    void* m_callbackData; // +0xc0
    unsigned char m_PaddingC8[0x20];
    void (*m_acceptCallback)(CCharacter*, void*); // +0xe8
    void (*m_declineCallback)(CCharacter*, void*); // +0xf0
};
typedef char check_CModalMenu_size[sizeof(CModalMenu)==0xf8?1:-1];
#endif
