#ifndef OTL_QUESTMENU_H
#define OTL_QUESTMENU_H
#include "SubMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CQuestMenu : public CSubMenu {
public:
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
    char m_Unrecovered10[0x378];
};
typedef char check_CQuestMenu_size[sizeof(CQuestMenu)==0x388?1:-1];
#endif
