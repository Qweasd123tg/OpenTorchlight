#ifndef OTL_QUESTMENU_H
#define OTL_QUESTMENU_H
#include "SubMenu.h"
#include "GameUI.h"
#include "TArrayList.h"
class CGenericModel; class CSoundBank;
#include <CEGUIWindow.h>
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CQuestMenu : public CSubMenu {
public:
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
    unsigned char m_Padding10[0x160];
    CBaseUnit* m_hoveredReward; // +0x170
    bool m_mouseThrough; // +0x178
    unsigned char m_Padding179[0x7];
    CCharacter* m_owner; // +0x180
    bool m_allowAbandon; // +0x188
    unsigned char m_Padding189[0x1];
    bool m_requestClose; // +0x18a
    bool m_selectedQuestChanged; // +0x18b
    unsigned int m_selectedQuestID; // +0x18c
    int m_selectedQuestIndex; // +0x190
    unsigned char m_Padding194[0x1c];
    CGenericModel* m_model; // +0x1b0
    unsigned char m_Padding1B8[0x20];
    CSoundBank* m_soundBank; // +0x1d8
    unsigned char m_Padding1E0[0x190];
    TArrayList<CEGUI::Window*> m_questWindows; // +0x370
};
typedef char check_CQuestMenu_size[sizeof(CQuestMenu)==0x388?1:-1];
#endif
