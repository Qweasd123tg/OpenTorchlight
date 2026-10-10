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
    unsigned char m_PaddingC8[0x58];
    CQuestDialog* m_dialog; // +0x120
    unsigned char m_Padding128[0x8];
    std::string m_dialogName; // +0x130
    unsigned char m_Padding138[0xa8];
    CBaseUnit* m_hoveredReward; // +0x1e0
    bool m_mouseThrough; // +0x1e8
    unsigned char m_Padding1E9[0x1];
    bool m_acceptOnExit; // +0x1ea
    bool m_resultBroadcast; // +0x1eb
    unsigned char m_Padding1EC[0x4];
    TSafePointer<CRunicCore> m_safeOwner; // +0x1f0
    unsigned char m_Padding200[0x8];
};
typedef char check_CQuestDialogMenu_size[sizeof(CQuestDialogMenu)==0x208?1:-1];
#endif
