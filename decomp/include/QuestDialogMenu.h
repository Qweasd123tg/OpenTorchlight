#ifndef OTL_QUESTDIALOGMENU_H
#define OTL_QUESTDIALOGMENU_H
#include "DropdownMenu.h"
#include "SafePointer.h"
#include "TArrayList.h"
#include <utility>
class CBaseUnit;
class CQuestDialog;
class CQuest;
class CGameUI; class CSettings; class CResourceManager; class CEquipment;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; class Imageset; }
void getTags(std::string&, TArrayList<std::pair<std::string, std::string> >&);
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CQuestDialogMenu : public CDropdownMenu {
public:
    void updateTextDisplay(float);
    void updateDialogTags();
    void setSlotIcon(int, CEquipment*);
    void createMenus();
    void setNPC(CBaseUnit*, bool, CQuest*);
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
    CEGUI::Window* m_windowF8; // +0xf8
    CEGUI::Window* m_detailWindow;
    CEGUI::Window* m_iconWindow;
    CEGUI::Window* m_iconParent;
    CEGUI::Window* m_window118; // +0x118
    CQuestDialog* m_dialog; // +0x120
    float m_textIndex; // +0x128 elapsed
    float m_textLength; // +0x12c duration
    std::string m_dialogName; // +0x130
    int m_displayedCharacters;
    unsigned char m_Padding13C[4];
    CEGUI::Imageset* m_uiImages; // +0x140
    int m_rewardIDs[4]; // +0x148
    CEGUI::Window* m_rewardRarity[3]; // +0x158
    CEGUI::Window* m_rewardIcons[3]; // +0x170
    CEGUI::Window* m_rewardSlots[3]; // +0x188
    CEGUI::Window* m_rewardBackgrounds[3]; // +0x1a0
    CEGUI::Window* m_rewardCounts[3]; // +0x1b8
    CEGUI::Window* m_rewardContainer; // +0x1d0
    CEGUI::Window* m_overlayWindow; // +0x1d8
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
