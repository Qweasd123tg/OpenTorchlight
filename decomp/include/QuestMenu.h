#ifndef OTL_QUESTMENU_H
#define OTL_QUESTMENU_H
#include "SubMenu.h"
#include "GameUI.h"
#include "TArrayList.h"
class CGenericModel; class CSoundBank;
#include <CEGUIWindow.h>
class CGameUI; class CSettings; class CResourceManager; class CEquipment;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; class Imageset; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CQuestMenu : public CSubMenu {
public:
    void mapEventHandlers(CEGUI::Window*);
    void setSlotIcon(int, CEquipment*);
    void createMenus();
    bool handle_MouseOver(const CEGUI::EventArgs& event);
    bool handle_MouseOut(const CEGUI::EventArgs& event);

    virtual bool handle_onClick(const CEGUI::EventArgs& event);
    virtual bool processInput(void* window,float elapsed,bool capture);

    bool handle_CloseButton(const CEGUI::EventArgs&);
    bool handle_MouseThrough(const CEGUI::EventArgs&);
    bool handle_QuestClick(const CEGUI::EventArgs&);
    virtual bool onClick(ELayoutFunction);
    void abandonQuest();

    virtual ~CQuestMenu();
    CQuestMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    virtual CBaseUnit* getOwner();
    virtual bool isRight();
    virtual bool open();
    virtual bool openPartial();
    virtual float screenEdge();
    virtual void setOwner(CCharacter*);
    virtual void setOpen(bool);
    virtual void updateLayout();
    virtual void update(float);
    CEGUI::Window* m_parentWindow; // +0x10
    CEGUI::Window* m_rootWindow; // +0x18
    CEGUI::Window* m_topWindow; // +0x20
    CEGUI::Window* m_bottomWindow; // +0x28
    CEGUI::Window* m_detailsWindow; // +0x30
    CEGUI::Window* m_listWindow; // +0x38
    CEGUI::Window* m_xpWindow; // +0x40
    CEGUI::Window* m_goldWindow; // +0x48
    CEGUI::Window* m_fameWindow; // +0x50
    CEGUI::Window* m_rewardLabel; // +0x58
    CEGUI::Window* m_xpIcon; // +0x60
    CEGUI::Window* m_goldIcon; // +0x68
    CEGUI::Window* m_fameIcon; // +0x70
    CEGUI::Window* m_questButtons[6]; // +0x78
    CEGUI::Window* m_questMarkers[6]; // +0xa8
    int m_rewardIDs[4]; // +0xd8
    CEGUI::Window* m_rewardRarity[3]; // +0xe8
    CEGUI::Window* m_rewardIcons[3]; // +0x100
    CEGUI::Window* m_rewardSlots[3]; // +0x118
    CEGUI::Window* m_rewardBackgrounds[3]; // +0x130
    CEGUI::Window* m_rewardCounts[3]; // +0x148
    CEGUI::Window* m_listContent; // +0x160
    CEGUI::Window* m_detailContent; // +0x168
    CBaseUnit* m_hoveredReward; // +0x170
    bool m_mouseThrough; // +0x178
    unsigned char m_Padding179[0x7];
    CCharacter* m_owner; // +0x180
    bool m_allowAbandon; // +0x188
    bool m_closed; // +0x189
    bool m_requestClose; // +0x18a
    bool m_selectedQuestChanged; // +0x18b
    unsigned int m_selectedQuestID; // +0x18c
    int m_selectedQuestIndex; // +0x190
    unsigned char m_Padding194[4];
    CSettings* m_settings; // +0x198
    CGameUI* m_gameUI; // +0x1a0
    Ogre::SceneManager* m_scene; // +0x1a8
    CGenericModel* m_model; // +0x1b0
    CResourceManager* m_resources; // +0x1b8
    CEGUI::Imageset* m_uiImages; // +0x1c0
    CEGUI::Imageset* m_itemImages; // +0x1c8
    float m_screenEdge; // +0x1d0
    float m_modelAnchor; // +0x1d4
    CSoundBank* m_soundBank; // +0x1d8
    int m_questIDs[100]; // +0x1e0
    TArrayList<CEGUI::Window*> m_questWindows; // +0x370
};
typedef char check_CQuestMenu_size[sizeof(CQuestMenu)==0x388?1:-1];
#endif
