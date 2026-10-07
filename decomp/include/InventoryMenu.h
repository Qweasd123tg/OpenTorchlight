// Partial: generated from symbols, RTTI and recovered layouts.
#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include "GameUI.h"
#include "SubMenu.h"
#include "iInventoryListener.h"

class CResourceManager;
class CSettings;

namespace Ogre
{
class RenderWindow;
class SceneManager;
}

namespace CEGUI
{
class Window;
}

// Partial: RTTI and thunks place iInventoryListener at +0x10. The vtable
// order is complete; unused virtual return types remain unverified.
class CInventoryMenu : public CSubMenu, public iInventoryListener
{
public:
    virtual ~CInventoryMenu();
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

private:
    char m_InventoryData18[0x9162 - 0x18];
    bool m_bRotateLeft;
    bool m_bRotateRight;
    char m_InventoryData9164[0x95d0 - 0x9164];
};

#endif
