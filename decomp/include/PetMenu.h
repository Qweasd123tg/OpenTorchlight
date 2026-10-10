// Partial: generated from symbols, RTTI and recovered layouts.
#ifndef PETMENU_H
#define PETMENU_H

#include "GameUI.h"
#include <CEGUIString.h>
#include "SubMenu.h"
#include "iInventoryListener.h"

class CSoundBank;
class CResourceManager;
class CDynamicPropertyFile;
class CGenericModel;
class CSkillTooltip;
class CSettings;

namespace Ogre
{
class Viewport;
class Camera;
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
class CPetMenu : public CSubMenu, public iInventoryListener
{
public:
    virtual ~CPetMenu();
    void setTab(int);
    void checkForUpdate(CEquipment*);
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

    CPetMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
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
    CEGUI::Window* m_pIconLayer;
    CEGUI::Window* m_pSocketOverlay;
    CEGUI::Window* m_pForeground48;
    char m_Data50[8];
    CCharacter* m_pCharacter;
    char m_Data60[8];
    bool m_bOpenPartial;
    bool m_bFullyClosed;
    char m_Data6a[2];
    int m_iCurrentTab;
    char m_Data70[0x88-0x70];
    CDynamicPropertyFile* m_pDynamicPropertyFile;
    CGameUI* m_pGameUI;
    int m_ClickedSlot;
    int m_RightClickedSlot;
    int m_aiSlotData[1000];
    CEGUI::Window* m_pSpellWindows[2];
    long long m_SpellGuids[99];
    long long m_NoSpell;
    void* m_pHoverObject;
    CEGUI::Window* m_pSocketedSizeWindows[82];
    CEGUI::Window* m_pMainUnidentifiedWindows[82];
    CEGUI::Window* m_pMainGlowWindows[82];
    CEGUI::Window* m_pMainSocketGlowWindows[82];
    CEGUI::Window* m_pMainStackWindows[82];
    CEGUI::String m_DefaultSlotImages[82];
    CEGUI::String m_DefaultSlotTooltips[82];
    CEGUI::Imageset* m_pImageset;
    CEGUI::Window* m_pSlotGlow;
    CEGUI::Window* m_pCharacterName;
    CEGUI::Window* m_pLevel;
    CEGUI::Window* m_pMeleeDamage;
    CEGUI::Window* m_pRangedDamage;
    CEGUI::Window* m_pMagicDamage;
    CEGUI::Window* m_pDefense;
    CEGUI::Window* m_pMana;
    CEGUI::Window* m_pHP;
    CEGUI::Window* m_pXP;
    Ogre::SceneManager* m_pPetSceneManager;
    Ogre::SceneManager* m_pWardrobeSceneManager;
    Ogre::Camera* m_pWardrobeCamera;
    Ogre::RenderWindow* m_pRenderWindow;
    Ogre::Viewport* m_pViewport;
    char m_Data9188;
    bool m_bSpellHovered;
    char m_Data918a[6];
    long long m_HoveredSkillGuid;
    bool m_bRotateLeft;
    bool m_bRotateRight;
    char m_Data919a[6];
    CGenericModel* m_pPetModel;
    CResourceManager* m_pResourceManager;
    float m_fScreenEdge;
    float m_fPanelX;
    CSoundBank* m_pSoundBank;
    CEGUI::Window* m_pBackpackSlots;
    CEGUI::Window* m_pSpellsSlots;
    CEGUI::Window* m_pFishSlots;
    CEGUI::Window* m_pBackpackTab;
    CEGUI::Window* m_pSpellsTab;
    CEGUI::Window* m_pFishTab;
    CSkillTooltip* m_pSkillTooltip;
    bool m_TabNotifications[3];
    char m_Data91fb;
    float m_fTabPhase;
    CEGUI::String m_TabUnselectedImages[3];
    CEGUI::String m_TabSelectedImages[3];
};
#endif
