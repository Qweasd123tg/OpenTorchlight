#ifndef JOURNALMENU_H
#define JOURNALMENU_H
#include "SubMenu.h"
#include "TArrayList.h"
namespace CEGUI {class Window;class Imageset;}
class CGenericModel;
class CGameUI;class CResourceManager;
class CSettings;
namespace Ogre { class RenderWindow; class SceneManager; }
class CJournalMenu : public CSubMenu {
public:
    CJournalMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

 void createMenus();
 bool handle_MouseThrough(const CEGUI::EventArgs&);
 bool handle_CloseButton(const CEGUI::EventArgs&);
 virtual ~CJournalMenu();
 virtual CBaseUnit* getOwner();
 virtual bool isRight();
 virtual bool open();
 virtual bool openPartial();
 virtual float screenEdge();
 virtual void setOwner(CCharacter*);
 virtual void setOpen(bool);
 virtual void updateLayout();
 virtual void update(float);
 virtual bool handle_onClick(const CEGUI::EventArgs&);
 virtual bool processInput(void*,float,bool);
 char m_Data10[8];
 CEGUI::Window* m_pRoot;
 CEGUI::Window* m_pTopFrame;
 CEGUI::Window* m_pBottomFrame;
 CCharacter* m_pOwner;
 char m_Data38[8];
 CSettings* m_pSettings;
 CGameUI* m_pGameUI;
 Ogre::SceneManager* m_pSceneManager;
 CGenericModel* m_pModel;
 CResourceManager* m_pResourceManager;
 CEGUI::Imageset* m_pImageset;
 char m_Data70[8];
 CEGUI::Window* m_pContent;
 char m_Data80[16];
 TArrayList<CEGUI::Window*> m_Children;
};
#endif
