// Partial: generated from symbols, RTTI and recovered layouts; assisted reconstruction.
// Sizes, used offsets and vtable slot order are checked. Unused return declarations
// remain ABI hypotheses and must not be exported as trusted prototypes.
#ifndef MERCHANTMENU_H
#define MERCHANTMENU_H

// Reconstructed declaration of CMerchantMenu (recovered size 0x3478).
//
// Bases are original RTTI: CSubMenu at 0, iInventoryListener at 0x10. The 0x10
// base offset is independently re-confirmed by CMerchantMenu::setPlayer, which
// passes `this + 0x10` to CInventory::addListener/removeListener as an
// iInventoryListener*.
//
// Evidence classes used below:
//   [A] established  — read straight out of instruction bytes.
//   [B] structural   — forced by surrounding [A] facts; name/params unproven.
//   [C] hypothesis   — ABI-compatible but not uniquely recoverable.
//
// Data members are declared in strict offset order so that every proven offset
// survives. Array extents are lower bounds at best; each one is flagged inline
// and collected in UNRESOLVED.md. No method bodies are defined here.

#include "SubMenu.h"
#include "iInventoryListener.h"
#include "GameUI.h"

class CBaseUnit;
class CCharacter;
class CEquipment;
class CGameUI;
class CResourceManager;
class CDynamicPropertyFile;
class CSoundBank;
class CPositionableObject;
class CSettings;

namespace Ogre
{
class SceneManager;
class RenderWindow;
}

namespace CEGUI
{
class Window;
class Imageset;
}

class CMerchantMenu : public CSubMenu, public iInventoryListener
{
public:
    // Primary vtable slots 0/1. The original emits _ZN13CMerchantMenuD1Ev,
    // D0Ev and the -16 thunks for both. [A]
    virtual ~CMerchantMenu();

    // ----------------------------------------------------------------------
    // CSubMenu overrides — primary vtable slots 2..12, in this order.
    // The generated draft declares all of these `virtual void`; register categories guide these ABI hypotheses; exact bool versus integer/pointer subtype is not uniquely proved.
    // ----------------------------------------------------------------------
    virtual CBaseUnit* getOwner();                     // slot 2  [A] mov 0x50(%rdi),%rax
    virtual bool isRight();                            // slot 3  [A] xor %eax,%eax
    virtual bool open();                               // slot 4  [A] returns 0/1
    virtual bool openPartial();                        // slot 5  [A] movzbl 0x60(%rdi),%eax
    virtual float screenEdge();                        // slot 6  [A] movss 0xa0(%rdi),%xmm0
    virtual void setOwner(CCharacter*);                // slot 7  [B]
    virtual void setOpen(bool);                        // slot 8  [B]
    virtual void updateLayout();                       // slot 9  [B]
    virtual void update(float);                        // slot 10 [B]
    virtual bool handle_onClick(const CEGUI::EventArgs&); // slot 11 [A]
    virtual bool processInput(void*, float, bool);       // slot 12 [A]

    // ----------------------------------------------------------------------
    // iInventoryListener overrides — secondary vtable slots 2..7 (plus the
    // -16 thunks, all present in the original). Under the Itanium ABI these
    // also append primary slots 13..18, while secondary entries use this-adjusting thunks. The
    // void return matches input/iInventoryListener.h and is confirmed: every
    // body tail-calls primary slot 9 without producing a value.
    // ----------------------------------------------------------------------
    virtual void equipmentPickedUp(CEquipment*);
    virtual void equipmentDropped(CEquipment*);
    virtual void equipmentEquipped(CEquipment*);
    virtual void equipmentUnequipped(CEquipment*);
    virtual void equipmentUsed(CEquipment*);
    virtual void inventoryDestroyed();                  // [A] body is `repz ret`
    virtual bool onClick(ELayoutFunction); // original primary slot19; bool is an ABI-compatible hypothesis from 0/1 EAX returns

    // ----------------------------------------------------------------------
    // Non-virtual members of the original TU. Signatures come from the mangled
    // symbols where one exists; return types are marked. Integer 0/1 returns do not uniquely prove bool versus int; unused callback return declarations remain ABI hypotheses.
    // ----------------------------------------------------------------------
    // The method this header exists for. Element size 4 is proven by the
    // addressing form `lea 0xb0(%rbp,%r12,4)`; the extent is NOT.
    void setPetSlotIcon(CEquipment*, int, int);         // [A] params
    void setSlotIcon(CEquipment*, int, int);            // [C] no symbol in the evidence
    void setPlayer(CCharacter*);                        // [A] params, [A] void
    void setTab(int);                                   // [A] params, [C] return
    void setPetTab(int);                                // [A] params, [C] return
    bool handle_ItemClick(const CEGUI::EventArgs&);     // [A] params, [A] bool
    bool handle_MouseThrough(const CEGUI::EventArgs&);  // [A] params, [A] bool
    bool handle_PetItemClick(const CEGUI::EventArgs&);  // [A] params, [A] bool
    bool handle_PetMouseOut(const CEGUI::EventArgs&);   // [A] params, [A] bool
    bool handle_MouseOut(const CEGUI::EventArgs&);      // [A] params, [A] bool

    CMerchantMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
                  CEGUI::Window*, CResourceManager*);  // [A] full signature

    // ----------------------------------------------------------------------
    // Fields. Offsets marked [A] are proven by the listing; the rest follow the
    // original base sizes plus the [B]/[C] offsets reported by
    // input/layout-draft.json, whose names and types are guesses. Anything not
    // named above it is explicit padding, never an invented fill array.
    // ----------------------------------------------------------------------
    void* m_pUnknown18;                                // +0x18  [B]
    void* m_pUnknown20;                                // +0x20  [B]
    void* m_pUnknown28;                                // +0x28  [B]
    CEGUI::Window* m_pSocketedIconParent;              // +0x30  [A] addChildWindow/setVisible receiver
    CEGUI::Window* m_pUnknown38;                       // +0x38  [A] CEGUI::Window::setVisible receiver
    void* m_pUnknown40;                                // +0x40  [B]
    unsigned char m_Gap48[0x08];                       // +0x48  [B]
    CBaseUnit* m_pOwner;                               // +0x50  [A] getOwner() returns it
    CCharacter* m_pCanEquipCharacter;                  // +0x58  [A] setPlayer stores it; canEquip arg
    bool m_bOpenPartial;                               // +0x60  [A] openPartial() returns it
    bool m_bUnknown61;                                 // +0x61  [A] open() tests this byte
    bool m_bUnknown62;                                 // +0x62  [B]
    unsigned char m_Gap63[0x05];                       // +0x63  [B]
    CDynamicPropertyFile* m_pDynamicPropertyFile;      // +0x68  [B]
    CGameUI* m_pGameUI;                                // +0x70  [A] createIcon(*m_pGameUI)
    Ogre::SceneManager* m_pUnknown78;                  // +0x78  [B]
    Ogre::RenderWindow* m_pUnknown80;                  // +0x80  [B]
    unsigned char m_Gap88[0x08];                       // +0x88  [B]
    CPositionableObject* m_pPositionableObject;        // +0x90  [B]
    CResourceManager* m_pResourceManager;              // +0x98  [B]
    float m_fScreenEdge;                               // +0xa0  [A] screenEdge() movss
    unsigned char m_GapA4[0x04];                       // +0xa4  [B]
    CSoundBank* m_pSoundBank;                          // +0xa8  [B]

    // Slot-data array. Base 0xb0 and element size 4 are proven; the extent is
    // NOT. 1000 elements is a LOWER BOUND: it stops where the layout draft
    // first reports an independent 8-byte object (0x1050) instead of running
    // on to 0x1de8 and overlaying the 8-byte members at 0x1050/0x10e8/0x14d8/
    // 0x1570/0x1960/0x19f8. The scratch header's 1878-element overlay is
    // exactly the "giant array hiding known fields" case.
    int m_aiSlotData[1000];                            // +0xb0  [A] base+stride, extent uncertain

    // Window pointer blocks. Bases and the 0x98/0x3F0/0x290/0x60 extents come
    // from the arithmetic of input/layout-draft.json's reported offsets, which
    // form a strict [0x98][0x3f0] period of 0x488 repeated five times from
    // 0x1050 to 0x26f8, then 0x290 blocks. Element type CEGUI::Window* is [C]
    // for the unnamed blocks (proven only for the six arrays setPetSlotIcon
    // reads); all extents are lower bounds.
    unsigned char m_pUnknown1050[0x98];                          // +0x1050
    unsigned char m_pUnknown10E8[0x3f0];                         // +0x10e8
    unsigned char m_pUnknown14D8[0x98];                          // +0x14d8
    unsigned char m_pUnknown1570[0x3f0];                         // +0x1570
    unsigned char m_pUnknown1960[0x98];                          // +0x1960
    unsigned char m_pUnknown19F8[0x3f0];                         // +0x19f8
    CEGUI::Window* m_pSocketedSizeWindows[19];         // +0x1de8 [A] base+stride 8, extent lower bound
    unsigned char m_pUnknown1E80[0x3f0];                         // +0x1e80
    unsigned char m_pUnknown2270[0x98];                          // +0x2270
    unsigned char m_pUnknown2308[0x3f0];                         // +0x2308
    CEGUI::Window* m_pSlotWindows[82];                 // +0x26f8 [A] base+stride 8
    CEGUI::Window* m_pUnidentifiedWindows[82];         // +0x2988 [A] base+stride 8
    CEGUI::Window* m_pSlotGlowWindows[82];             // +0x2c18 [A] base+stride 8
    CEGUI::Window* m_pSocketGlowWindows[82];           // +0x2ea8 [A] base+stride 8
    CEGUI::Window* m_pStackWindows[82];                // +0x3138 [A] base+stride 8
    unsigned char m_pUnknown33C8[0x60];                          // +0x33c8

    // Four consecutive ints; all four offsets are proven. handle_PetItemClick
    // stores to 0x3428/0x342c and handle_ItemClick to 0x3430/0x3434.
    int m_iPetSlotIndexA;                              // +0x3428 [A]
    int m_iPetSlotIndexB;                              // +0x342c [A]
    int m_iItemSlotIndexA;                             // +0x3430 [A]
    int m_iItemSlotIndexB;                             // +0x3434 [A]
    CEquipment* m_pHoveredEquipment;                   // +0x3438 [A] compared to getEquipmentInSlot()
    CEGUI::Imageset* m_pImageset;                      // +0x3440 [A] receiver of every getImage()
    void* m_pUnknown3448;                              // +0x3448 [B]
    bool m_bUnknown3450;                               // +0x3450 [A] handle_MouseThrough stores 0
    unsigned char m_Gap3451[0x03];                     // +0x3451 [B]
    int m_iUnknown3454;                                // +0x3454 [B]
    int m_iUnknown3458;                                // +0x3458 [B]
    unsigned char m_Gap345C[0x04];                     // +0x345c [B]
    unsigned char m_Gap3460[0x18];                     // +0x3460 .. end 0x3478 [B]

    friend struct MerchantMenuLayoutProbe;
};

#endif
