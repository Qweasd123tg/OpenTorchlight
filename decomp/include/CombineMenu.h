#ifndef COMBINE_MENU_H
#define COMBINE_MENU_H
#include "GameUI.h"
#include "SubMenu.h"
#include "iInventoryListener.h"
class CSettings;
class CGenericModel;
class CResourceManager;
namespace Ogre { class SceneManager; class RenderWindow; }
namespace CEGUI { class Window; class Imageset; }
// Partial named layout; original allocation size is 0x1b0.
class CCombineMenu : public CSubMenu, public iInventoryListener {
public:
    CCombineMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

 virtual ~CCombineMenu();
 // Original override symbols; return declarations follow the existing base ABI.
 // create does not invoke these methods. Bodies remain external and untouched.
 virtual CBaseUnit* getOwner();
 virtual bool isRight();
 virtual bool open();
 virtual bool openPartial();
 virtual float screenEdge();
 virtual void setOwner(CCharacter*);
 virtual void setOpen(bool);
 virtual void update(float);
 virtual void equipmentPickedUp(CEquipment*);
 virtual void equipmentDropped(CEquipment*);
 virtual void equipmentEquipped(CEquipment*);
 virtual void equipmentUnequipped(CEquipment*);
 virtual void equipmentUsed(CEquipment*);
 virtual void inventoryDestroyed();

 void createMenus();
 void mapEventHandlers(CEGUI::Window*);
 bool handle_ItemClick(const CEGUI::EventArgs&);
 bool handle_MouseThrough(const CEGUI::EventArgs&);
 bool handle_MouseOver(const CEGUI::EventArgs&);
 bool handle_MouseOut(const CEGUI::EventArgs&);
 void setSlotIcon(CEquipment*, int);
 virtual void updateLayout();
char gap18[0x48-0x18];
 CEGUI::Window* m_pParent;
 CEGUI::Window* m_pBackground;
 CEGUI::Window* m_pPanel;
 CEGUI::Window* m_pSocketedIconParent;
 CEGUI::Window* m_pForeground;
 CEGUI::Window* m_pTitle;
 CEGUI::Window* m_pDialog;
 CEGUI::Window* m_pAccept;
 char gap88[8];
 CCharacter* m_pCharacter;
 bool m_bOpen;
 char gap99[0xa0-0x99];
 CSettings* m_pSettings;
 CGameUI* m_pGameUI;
 Ogre::SceneManager* m_pSceneManager;
 Ogre::RenderWindow* m_pRenderWindow;
 char gapC0[8];
 CGenericModel* m_pMenuModel;
 CResourceManager* m_pResourceManager;
 char gapD8[0xe8-0xd8];
 int m_aiSlotData[4];
 int m_aiLocalSlotData[4];
 CEGUI::Window* m_pMainGlowWindows[4];
 CEGUI::Window* m_pMainSocketGlowWindows[4];
 CEGUI::Window* m_pSocketedSizeWindows[4];
 CEGUI::Window* m_pMainStackWindows[4];
 char gap188[0x198-0x188];
 CEGUI::Imageset* m_pImageset;
 CEGUI::Window* m_pSlotGlow;
 char gap1A8[8];
};
#endif
