#ifndef ENCHANT_MENU_H
#define ENCHANT_MENU_H
#include "GameUI.h"
#include "Character.h"
#include "SubMenu.h"
#include "iInventoryListener.h"
class CItem; class CSoundBank;
class CSettings; class CGenericModel; class CResourceManager;
namespace Ogre { class SceneManager; class RenderWindow; }
namespace CEGUI { class Window; class Imageset; }
// Partial named layout; original allocation is 0x110 bytes.
class CEnchantMenu : public CSubMenu, public iInventoryListener {
public:
    CEnchantMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

 virtual ~CEnchantMenu();
 // Original override symbols; return declarations follow the existing base ABI.
 // create does not invoke these methods. Bodies remain external and untouched.
 virtual CBaseUnit* getOwner();
 virtual bool isRight();
 virtual bool open();
 virtual bool openPartial();
 virtual float screenEdge();
 virtual void setOwner(CCharacter*);
 virtual void setOpen(bool);
 void setOpen(bool, EAIState);
 virtual void update(float);
 virtual bool handle_onClick(const CEGUI::EventArgs&);
 virtual bool processInput(void*,float,bool);
 virtual void equipmentPickedUp(CEquipment*);
 virtual void equipmentDropped(CEquipment*);
 virtual void equipmentEquipped(CEquipment*);
 virtual void equipmentUnequipped(CEquipment*);
 virtual void equipmentUsed(CEquipment*);
 virtual void inventoryDestroyed();
 virtual bool onClick(ELayoutFunction);
 void setPlayer(CCharacter*);
 void setOwnerItem(CItem*);
 bool handle_CloseButton(const CEGUI::EventArgs&);

 void createMenus();
 void mapEventHandlers(CEGUI::Window*);
 bool handle_ItemClick(const CEGUI::EventArgs&);
 bool handle_MouseThrough(const CEGUI::EventArgs&);
 bool handle_MouseOver(const CEGUI::EventArgs&);
 bool handle_MouseOut(const CEGUI::EventArgs&);
 virtual void updateLayout();
 void performInteraction();
 void setSlotIcon(CEquipment*, int);
 CEGUI::Window* m_pParent;
 CEGUI::Window* m_pBackground;
 CEGUI::Window* m_pPanel;
 CEGUI::Window* m_pSocketedIconParent;
 CEGUI::Window* m_pForeground;
 CEGUI::Window* m_pTitle;
 CEGUI::Window* m_pDescription;
 CEGUI::Window* m_pAccept;
 CCharacter* m_pOwner;
 CCharacter* m_pCharacter;
 CItem* m_pOwnerItem;
 bool m_bOpen;
 bool m_bFullyClosed;
 bool m_bInteractionComplete;
 bool m_bRetirementComplete;
 char gap74[4];
 CSettings* m_pSettings;
 CGameUI* m_pGameUI;
 Ogre::SceneManager* m_pSceneManager;
 Ogre::RenderWindow* m_pRenderWindow;
 char gap98[8];
 CGenericModel* m_pMenuModel;
 CResourceManager* m_pResourceManager;
 char gapB0[8];
 CSoundBank* m_pSoundBank;
 int m_aiSlotData[1];
 int m_aiLocalSlotData[1];
 CEGUI::Window* m_pMainGlowWindows[1];
 CEGUI::Window* m_pMainSocketGlowWindows[1];
 CEGUI::Window* m_pSocketedSizeWindows[1];
 CEGUI::Window* m_pMainStackWindows[1];
 int m_ClickedSlot;
 int m_RightClickedSlot;
 CEquipment* m_pHoverObject;
 CEGUI::Imageset* m_pImageset;
 CEGUI::Window* m_pSlotGlow;
 bool m_bHover;
 char gap109[3];
 int m_iMode;
};
#endif
