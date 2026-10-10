#ifndef JOURNALMENU_H
#define JOURNALMENU_H
#include "SubMenu.h"
#include "TArrayList.h"
namespace CEGUI {class Window;class Imageset;}
class CGenericModel;
class CSoundBank;
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
 CEGUI::Window* m_pParentWindow;
 CEGUI::Window* m_pRoot;
 CEGUI::Window* m_pTopFrame;
 CEGUI::Window* m_pBottomFrame;
 CCharacter* m_pOwner;
 bool m_bOpen;
 bool m_bClosed;
 bool m_bCloseRequested;
 char m_Padding3B[5];
 CSettings* m_pSettings;
 CGameUI* m_pGameUI;
 Ogre::SceneManager* m_pSceneManager;
 CGenericModel* m_pModel;
 CResourceManager* m_pResourceManager;
 CEGUI::Imageset* m_pImageset;
 float m_ScreenEdge;
 float m_TopEdge;
 CEGUI::Window* m_pContent;
 CSoundBank* m_pSoundBank;
 int m_LastPlayedSeconds;
 char m_Padding8C[4];
 TArrayList<CEGUI::Window*> m_Children;
};
#endif
