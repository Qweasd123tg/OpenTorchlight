#ifndef COMBINE_MENU_H
#define COMBINE_MENU_H
#include <map>
#include <utility>
#include "GameUI.h"
#include "SubMenu.h"
#include "iInventoryListener.h"
extern bool g_bDontTrackItemEquipAndUnEquip;
// Original TU-local ELF name; the plain declaration also exposes the type to context indexing.
extern bool g_bDontTrackItemEquipAndUnEquip __asm__("_ZL31g_bDontTrackItemEquipAndUnEquip");
class CInventory;
class CSettings;
class CSoundBank;
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
 virtual bool handle_onClick(const CEGUI::EventArgs&);
 virtual bool processInput(void*, float, bool);
 virtual void equipmentPickedUp(CEquipment*);
 virtual void equipmentDropped(CEquipment*);
 virtual void equipmentEquipped(CEquipment*);
 virtual void equipmentUnequipped(CEquipment*);
 virtual void equipmentUsed(CEquipment*);
 virtual void inventoryDestroyed();
 virtual bool onClick(ELayoutFunction);

 void setPlayer(CCharacter*);
 void returnItemsToCorrectLocation(CEquipment*);
 bool handle_CloseButton(const CEGUI::EventArgs&);
 void performInteraction();
 void itemUpdatedInMenu(CEquipment*,bool);
 void createMenus();
 void mapEventHandlers(CEGUI::Window*);
 bool handle_ItemClick(const CEGUI::EventArgs&);
 bool handle_MouseThrough(const CEGUI::EventArgs&);
 bool handle_MouseOver(const CEGUI::EventArgs&);
 bool handle_MouseOut(const CEGUI::EventArgs&);
 void setSlotIcon(CEquipment*, int);
 virtual void updateLayout();
std::map<CEquipment*, std::pair<CInventory*, EEQUIP_LOCATIONS> > m_OriginalItemLocations;
 CEGUI::Window* m_pParent;
 CEGUI::Window* m_pBackground;
 CEGUI::Window* m_pPanel;
 CEGUI::Window* m_pSocketedIconParent;
 CEGUI::Window* m_pForeground;
 CEGUI::Window* m_pTitle;
 CEGUI::Window* m_pDialog;
 CEGUI::Window* m_pAccept;
 CCharacter* m_pOwner;
 CCharacter* m_pCharacter;
 bool m_bOpen;
 bool m_bFullyClosed;
 bool m_bCloseRequested;
 char gap9B[5];
 CSettings* m_pSettings;
 CGameUI* m_pGameUI;
 Ogre::SceneManager* m_pSceneManager;
 Ogre::RenderWindow* m_pRenderWindow;
 char gapC0[8];
 CGenericModel* m_pMenuModel;
 CResourceManager* m_pResourceManager;
 float m_fPanelX;
 char gapDC[4];
 CSoundBank* m_pSoundBank;
 int m_aiSlotData[4];
 int m_aiLocalSlotData[4];
 CEGUI::Window* m_pMainGlowWindows[4];
 CEGUI::Window* m_pMainSocketGlowWindows[4];
 CEGUI::Window* m_pSocketedSizeWindows[4];
 CEGUI::Window* m_pMainStackWindows[4];
 int m_ClickedSlot;
 int m_RightClickedSlot;
 CEquipment* m_pHoverObject;
 CEGUI::Imageset* m_pImageset;
 CEGUI::Window* m_pSlotGlow;
 bool m_bHover;
 char gap1A9[3];
 float m_fScreenEdge;
};
#endif
