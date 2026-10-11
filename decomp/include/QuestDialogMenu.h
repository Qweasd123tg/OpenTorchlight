#ifndef OTL_QUESTDIALOGMENU_H
#define OTL_QUESTDIALOGMENU_H
#include "DropdownMenu.h"
#include "SafePointer.h"
class CBaseUnit;
class CQuestDialog;
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CQuestDialogMenu : public CDropdownMenu {
public:
    void createMenus();
    bool handle_MouseOver(const CEGUI::EventArgs& event);
    bool handle_MouseOut(const CEGUI::EventArgs& event);

    void broadcastAcceptedOrDeclined(bool accepted, CBaseUnit* unit);
    const Ogre::Vector3& getCameraOffset();
    bool acceptQuest(CBaseUnit* unit);
    bool handle_ExitButton(const CEGUI::EventArgs& event);
    bool handle_CloseButton(const CEGUI::EventArgs& event);
    virtual void update(float elapsed);
    virtual void setOpen(bool open);
    virtual bool onClick(ELayoutFunction function, std::wstring text);

    bool handle_MouseThrough(const CEGUI::EventArgs&);

    virtual ~CQuestDialogMenu();
    CQuestDialogMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    CBaseUnit* m_unit; // +0xc0
    CEGUI::Window* m_dialogWindow;
    CEGUI::Window* m_promptWindow;
    CEGUI::Window* m_acceptWindow;
    CEGUI::Window* m_declineWindow;
    CEGUI::Window* m_rewardWindow;
    CEGUI::Window* m_rewardTextWindow;
    unsigned char m_PaddingF8[8];
    CEGUI::Window* m_detailWindow;
    CEGUI::Window* m_iconWindow;
    CEGUI::Window* m_iconParent;
    unsigned char m_Padding118[8];
    CQuestDialog* m_dialog; // +0x120
    int m_textIndex;
    int m_textLength;
    std::string m_dialogName; // +0x130
    int m_displayedCharacters;
    unsigned char m_Padding13C[0xa4];
    CBaseUnit* m_hoveredReward; // +0x1e0
    bool m_mouseThrough; // +0x1e8
    bool m_dialogActive;
    bool m_acceptOnExit; // +0x1ea
    bool m_resultBroadcast; // +0x1eb
    unsigned char m_Padding1EC[0x4];
    TSafePointer<CRunicCore> m_safeOwner; // +0x1f0
    float m_textSpeed;
    unsigned char m_Padding204[4];
};
typedef char check_CQuestDialogMenu_size[sizeof(CQuestDialogMenu)==0x208?1:-1];
#endif
