#ifndef OTL_DIALOGMENU_H
#define OTL_DIALOGMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager; class CQuestDialog;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CDialogMenu : public CDropdownMenu {
public:
    void createMenus();
    bool handle_ExitButton(const CEGUI::EventArgs& event);
    bool handle_CloseButton(const CEGUI::EventArgs& event);
    virtual bool onClick(ELayoutFunction function, std::wstring text);
    virtual void update(float elapsed);
    virtual void setOpen(bool open);

    virtual ~CDialogMenu();
    CDialogMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    CBaseUnit* m_speaker; // +0xc0
    CEGUI::Window* m_promptWindow;
    CEGUI::Window* m_acceptWindow;
    CEGUI::Window* m_declineWindow;
    CEGUI::Window* m_extraWindow;
    unsigned char m_PaddingE8[8];
    CQuestDialog* m_dialogOwner; // +0xf0
};
typedef char check_CDialogMenu_size[sizeof(CDialogMenu)==0xf8?1:-1];
#endif
