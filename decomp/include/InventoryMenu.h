// Partial: generated from symbols, RTTI and recovered layouts.
#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include "GameUI.h"
#include <CEGUIString.h>
#include "SubMenu.h"
#include "iInventoryListener.h"

class CResourceManager;
class CDynamicPropertyFile;
class CGenericModel;
class CSkillTooltip;
class CSettings;
class CSoundBank;

namespace Ogre
{
class Camera;
class Viewport;
class RenderWindow;
class SceneManager;
}

namespace CEGUI
{
class Window;
class Imageset;
}

// Partial: RTTI and thunks place iInventoryListener at +0x10. The vtable
// order is complete; unused virtual return types remain unverified.
class CInventoryMenu : public CSubMenu, public iInventoryListener
{
public:
    void toggleWeaponSet();
    virtual ~CInventoryMenu();
    void setTab(int);
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
    virtual bool processInput(void*, float, bool);
    virtual void equipmentPickedUp(CEquipment*);
    virtual void equipmentDropped(CEquipment*);
    virtual void equipmentEquipped(CEquipment*);
    virtual void equipmentUnequipped(CEquipment*);
    virtual void equipmentUsed(CEquipment*);
    virtual void inventoryDestroyed();
    virtual bool onClick(ELayoutFunction);

    bool handle_RotateLeft(const CEGUI::EventArgs&);
    bool handle_EndRotateLeft(const CEGUI::EventArgs&);
    bool handle_RotateRight(const CEGUI::EventArgs&);
    bool handle_EndRotateRight(const CEGUI::EventArgs&);

    CInventoryMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
                   Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

    void createMenus();
    void mapEventHandlers(CEGUI::Window*);
    bool handle_ItemClick(const CEGUI::EventArgs&);
    bool handle_MouseThrough(const CEGUI::EventArgs&);
    bool handle_MouseOver(const CEGUI::EventArgs&);
    bool handle_MouseOut(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);
    bool handle_SpellMouseOver(const CEGUI::EventArgs&);
    bool handle_SpellMouseOut(const CEGUI::EventArgs&);
    bool handle_SetSpell(const CEGUI::EventArgs&);
    void setSlotIcon(CEquipment*, int, int);
private:
    CEGUI::Window* m_pParent;
    CEGUI::Window* m_pBackground;
    CEGUI::Window* m_pPanel;
    CEGUI::Window* m_pSocketedIconParent;
    CEGUI::Window* m_pForeground38;
    CEGUI::Window* m_pIconParent;
    CEGUI::Window* m_pForeground48;
    CCharacter* m_pCharacter;
    char m_InventoryData58[8];
    bool m_bOpen;
    bool m_bFullyClosed;
    char m_InventoryData62[0x68 - 0x62];
    CDynamicPropertyFile* m_pDynamicPropertyFile;
    CGameUI* m_pGameUI;
    char m_InventoryData78[8];
    int m_aiSlotData[1000];
    CEquipment* m_pHoverObject;
    CEGUI::Window* m_pSocketedSizeWindows[82];
    CEGUI::Window* m_pMainGlowWindows[82];
    CEGUI::Window* m_pMainSocketGlowWindows[82];
    CEGUI::Window* m_pMainStackWindows[82];
    CEGUI::Window* m_pMainUnidentifiedWindows[82];
    CEGUI::Imageset* m_pImageset;
    CEGUI::Window* m_pSlotGlow;
    CEGUI::String m_DefaultSlotImages[82];
    CEGUI::String m_DefaultSlotTooltips[82];
    CEGUI::Window* m_pSpellWindows[4];
    long long m_SpellGuids[99];
    long long m_NoSpell;
    CEGUI::Window* m_pBackpackSlots;
    CEGUI::Window* m_pSpellsSlots;
    CEGUI::Window* m_pFishSlots;
    CEGUI::Window* m_pBackpackTab;
    CEGUI::Window* m_pSpellsTab;
    CEGUI::Window* m_pFishTab;
    Ogre::SceneManager* m_pInventorySceneManager;
    Ogre::SceneManager* m_pWardrobeSceneManager;
    Ogre::Camera* m_pWardrobeCamera;
    Ogre::RenderWindow* m_pRenderWindow;
    Ogre::Viewport* m_pViewport;
    char m_InventoryData9160;
    bool m_bSpellHovered;
    bool m_bRotateLeft;
    bool m_bRotateRight;
    char m_InventoryData9164[4];
    long long m_HoveredSkillGuid;
    CGenericModel* m_pInventoryModel;
    CResourceManager* m_pResourceManager;
    float m_fScreenEdge;
    float m_fPanelX;
    CSoundBank* m_pSoundBank;
    CEGUI::Window* m_pMoneyWindow;
    CEGUI::Window* m_pWeaponSwitchWindow;
    CSkillTooltip* m_pSkillTooltip;
    bool m_TabNotifications[3];
    char m_InventoryData91ab;
    float m_fTabPhase;
    CEGUI::String m_TabUnselectedImages[3];
    CEGUI::String m_TabSelectedImages[3];
};

#endif
