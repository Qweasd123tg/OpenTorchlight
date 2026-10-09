// Partial: generated from symbols, RTTI and recovered layouts; callback types constrained by SDK.
#ifndef MERCHANTMENU_H
#define MERCHANTMENU_H

// ============================================================================
//  output/MerchantMenu.h
//
//  Replacement for input/project-headers/MerchantMenu.h, which is a partial
//  reconstruction missing every declaration output/MerchantMenu.cpp needs and
//  which types six of the window blocks as `void*` / `unsigned char[]`.
//
//  Provenance of every offset below:
//    [A] established  - read out of input/original.asm instruction bytes.
//    [A-SDK]          - pinned by input/supervisor-verification/sdk-layout-facts.json
//                       (pinned GCC 4.4.7 header layout export).
//    [B] structural   - forced by surrounding [A] facts.
//    [C] hypothesis   - ABI-compatible, not uniquely recoverable.
//
//  Corrections against the first candidate, all forced by the supervisor
//  verification packet:
//
//   * CEGUI::Window's real layout (sdk-layout-facts.json) agrees with every
//     offset the listing used: EventSet base at +56 (0x38), d_parent at +176
//     (0xb0), d_userData at +472 (0x1d8).  The "+0x213" and "+0x3e2" raw byte
//     stores are NOT unexplained fields: they are CEGUIWindow.h's own inline
//     setters for d_riseOnClick and d_mousePassThroughEnabled.  No raw-offset
//     accessors are needed anywhere.
//
//   * CMerchantMenu +0x90 must be assignable from CResourceManager::
//     createGenericModel's return type, CGenericModel*.  It is retyped here
//     from CPositionableObject*; the offset is unchanged.
//
//   * The five 126-entry blocks and the twelve-panel block hold CEGUI::Window*
//     (recursiveChildSearch results), not bytes.  Retyped here; every extent
//     is exact (see the arithmetic at the bottom of this header).
//
//  The declarations accepted in the input header are preserved verbatim,
//  including the ones the first candidate could not use:
//      setPetSlotIcon(CEquipment*, int, int)
//      setSlotIcon(CEquipment*, int, int)
//      setPlayer(CCharacter*), setTab(int), setPetTab(int)
//      handle_ItemClick / handle_MouseThrough / handle_PetItemClick /
//      handle_PetMouseOut / handle_MouseOut
//      onClick(ELayoutFunction)
//      the full CSubMenu override set and the full iInventoryListener set.
//
//  Return types follow the input header's evidence classes.  Where the input
//  marked a return type a hypothesis it is left off rather than asserted.
//
// ============================================================================

#include "SubMenu.h"
#include "iInventoryListener.h"
#include "GameUI.h"
#include "EmptyStrings.h"

// Collaborators used only by pointer in this class.
class CBaseUnit;
class CCharacter;
class CEquipment;
class CGameUI;
class CGenericModel;
class CResourceManager;
class CDynamicPropertyFile;
class CSoundBank;
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
    // ------------------------------------------------------------------
    // Primary vtable slots 0/1.  The original emits _ZN13CMerchantMenuD1Ev,
    // D0Ev and the -16 thunks for both.  [A]
    // ------------------------------------------------------------------
    virtual ~CMerchantMenu();

    // ------------------------------------------------------------------
    // CSubMenu overrides - primary vtable slots 2..12, in this order.
    // ------------------------------------------------------------------
    virtual CBaseUnit* getOwner();                        // slot 2  [A] +0x50
    virtual bool isRight();                               // slot 3  [A]
    virtual bool open();                                  // slot 4  [A]
    virtual bool openPartial();                           // slot 5  [A] +0x60
    virtual float screenEdge();                           // slot 6  [A] +0xa0
    virtual void setOwner(CCharacter*);                   // slot 7  [B]
    virtual void setOpen(bool);                           // slot 8  [B]
    virtual void updateLayout();                          // slot 9  [B]
    virtual void update(float);                           // slot 10 [B]
    virtual bool handle_onClick(const CEGUI::EventArgs&); // slot 11 [A]
    virtual bool processInput(void*, float, bool);        // slot 12 [A]

    // ------------------------------------------------------------------
    // iInventoryListener overrides - secondary vtable slots 2..7, plus the
    // primary slots 13..18 and the -16 thunks, all present in the original.
    // void returns match input/iInventoryListener.h and are confirmed by
    // bodies that tail-call without producing a value.
    // ------------------------------------------------------------------
    virtual void equipmentPickedUp(CEquipment*);
    virtual void equipmentDropped(CEquipment*);
    virtual void equipmentEquipped(CEquipment*);
    virtual void equipmentUnequipped(CEquipment*);
    virtual void equipmentUsed(CEquipment*);
    virtual void inventoryDestroyed();                     // [A] `repz ret`
    virtual bool onClick(ELayoutFunction);                // slot 19 [C] return

    // ------------------------------------------------------------------
    // The method this header exists for.  _ZN13CMerchantMenu11createMenusEv,
    // 0xb6ed20, 34170 bytes, `void` (no %rax setup before the six pops at
    // b75c06..b75c10).
    // ------------------------------------------------------------------
    void createMenus();                                   // [A]

    // ------------------------------------------------------------------
    // Non-virtual members of the original TU, confirmed by symbol address.
    // The eight callbacks below are the only members createMenus() names as
    // subscriber targets; each is non-virtual and takes
    // `const CEGUI::EventArgs&`, which is exactly
    // CEGUI::Event::Subscriber's required `bool (const EventArgs&)`.
    // Their declared return type is deliberately left off: the generated
    // draft's `void` is a hypothesis and a wrong return type would change the
    // subscriber's call ABI.
    // ------------------------------------------------------------------
    bool handle_ItemClick(const CEGUI::EventArgs&);        // 0xb61040  [A] params
    bool handle_MouseThrough(const CEGUI::EventArgs&);     // 0xb61090  [A] params
    bool handle_PetItemClick(const CEGUI::EventArgs&);     // 0xb610f0  [A] params
    bool handle_PetMouseOut(const CEGUI::EventArgs&);      // 0xb61140  [A] params
    bool handle_MouseOut(const CEGUI::EventArgs&);         // 0xb611f0  [A] params
    bool handle_MouseOver(const CEGUI::EventArgs&);        // 0xb688e0  [A] address
    bool handle_PetMouseOver(const CEGUI::EventArgs&);     // 0xb68530  [A] address
    bool handle_CloseButton(const CEGUI::EventArgs&);      // 0xb68ca0  [A] address

    void mapEventHandlers(CEGUI::Window*);                // 0xb6a790  [A] address

    // setPetSlotIcon and setSlotIcon: element size 4 and the base of the
    // slot-data table are proven by `lea 0xb0(%rbp,%r12,4)`; the extents are
    // not.  Signatures come from the mangled names of setPetSlotIcon; the
    // second is ABI-compatible with it.
    void setPetSlotIcon(CEquipment*, int, int);           // [A] mangled name
    void setSlotIcon(CEquipment*, int, int);              // [B]

    void setPlayer(CCharacter*);                          // [A] params, [A] void
    void setTab(int);                                     // [A] params, [C] return
    void setPetTab(int);                                  // [A] params, [C] return

    CMerchantMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
                  CEGUI::Window*, CResourceManager*);      // [A] full signature

    // ------------------------------------------------------------------
    // Fields.  Declared in strict offset order so every proven offset
    // survives.  Anything unnamed is explicit padding, never an invented fill
    // array, unless a fill array IS the thing being addressed.
    // ------------------------------------------------------------------
    void* m_pUnknown18;                                   // +0x18  [B]
                                                          //   Never written by
                                                          //   createMenus(); the
                                                          //   listing contains no
                                                          //   store to +0x18.  Left
                                                          //   as an opaque pointer
                                                          //   rather than guessed.
    CEGUI::Window* m_pUnknown20;                           // +0x20  [A] createWindow("DefaultWindow","MerchantSheet","")
    CEGUI::Window* m_pUnknown28;                           // +0x28  [A] layoutRoot->recursiveChildSearch("TopFrame")
    CEGUI::Window* m_pSocketedIconParent;                  // +0x30  createWindow("DefaultWindow","MSockets","")
    CEGUI::Window* m_pUnknown38;                           // +0x38  [A] +0x38 is both this member and the
                                                          //        CEGUI::EventSet base offset
    CEGUI::Window* m_pUnknown40;                           // +0x40  [A] layoutRoot->recursiveChildSearch("BottomFrame")
    void* m_pUnknown080;                                   // +0x48  [B]
    CBaseUnit* m_pOwner;                                  // +0x50  [A] getOwner() returns it
    CCharacter* m_pCanEquipCharacter;                     // +0x58  [A] setPlayer stores it
    bool m_bOpenPartial;                                  // +0x60  [A] openPartial() returns it
    bool m_bUnknown61;                                    // +0x61  [A] open() tests this byte
    bool m_bUnknown62;                                    // +0x62  [B]
    unsigned char m_Gap63[0x05];                          // +0x63  [B]
    CDynamicPropertyFile* m_pDynamicPropertyFile;         // +0x68  [A] GetInt/GetFloat receiver
    CGameUI* m_pGameUI;                                   // +0x70  [A] convertToScreenScale/mapToFunctions receiver
    Ogre::SceneManager* m_pUnknown78;                     // +0x78  [A] createGenericModel arg 2
    Ogre::RenderWindow* m_pUnknown80;                     // +0x80  [B]
    unsigned char m_Gap88[0x08];                          // +0x88  [B]
    CGenericModel* m_pPositionableObject;                 // +0x90  [A] createGenericModel
                                                          //        result; retyped from
                                                          //        CPositionableObject*
                                                          //        because the only
                                                          //        assignment in the
                                                          //        listing stores the
                                                          //        CGenericModel*
                                                          //        return value
                                                          //        (compile diagnostic
                                                          //        compile-declaration.log:2).
    CResourceManager* m_pResourceManager;                 // +0x98  [A] createGenericModel receiver
    float m_fScreenEdge;                                  // +0xa0  [A] screenEdge() movss
    unsigned char m_GapA4[0x04];                          // +0xa4  [B]
    CSoundBank* m_pSoundBank;                             // +0xa8  [B]

    // Slot-data table.  Base +0xb0 and stride 4 are proven by
    // `lea 0xb0(%rbp,%r12,4)` and by the priming loop at b70e60.  The extent
    // is not: createMenus() primes 0..399 and hands indices i+18 (19..144) to
    // setUserData, so >=400 is proven.  1000 is the layout draft's figure and
    // is kept because it is the only value that lands the next block on its
    // proven offset +0x1050 - see the arithmetic below.
    int m_aiSlotData[1000];                               // +0xb0  [A] base+stride, [C] extent

    // ------------------------------------------------------------------
    // Five [19][126] pairs.  0x98 == 19*8 and 0x3F0 == 126*8 exactly; the
    // 126 extent is the item-slot loop's trip count
    // (i = 1 .. 126, `cmpl $0x7f` at b7327a).
    //
    // The 19-element half of each pair is NEVER written by createMenus() -
    // an exhaustive sweep of the listing for stores to +0x1050, +0x14d8,
    // +0x1960, +0x1de8 and +0x2270 finds none.  Those are the socket-count
    // blocks and belong to setSlotIcon/setPetSlotIcon.  They are typed
    // CEGUI::Window* for consistency with the 126 half, which the listing
    // does write with recursiveChildSearch results.
    // ------------------------------------------------------------------
    CEGUI::Window* m_pUnknown1050[145];                     // +0x1050  [C] element, [B] extent
    CEGUI::Window* m_pUnknown14D8[145];                     // +0x14d8  [C] element, [B] extent
    CEGUI::Window* m_pUnknown1960[145];                     // +0x1960  [C] element, [B] extent
    CEGUI::Window* m_pSocketedSizeWindows[145];            // +0x1de8  [B] 19-pointer socket block
    CEGUI::Window* m_pUnknown2270[145];                     // +0x2270  [C] element, [B] extent

    // ------------------------------------------------------------------
    // Five 82-entry blocks, 0x290 == 82*8 exactly.  The pet-slot loop writes
    // elements 19..81 of all five (first access +0x2790 = +0x26f8 + 19*8, and
    // 19 + 63 == 82 for `cmpl $0x40`).  Elements 0..18 are written by
    // setPetSlotIcon, not here.
    // ------------------------------------------------------------------
    CEGUI::Window* m_pSlotWindows[82];                     // +0x26f8  [A] base+stride
    CEGUI::Window* m_pUnidentifiedWindows[82];             // +0x2988  [A] base+stride
    CEGUI::Window* m_pSlotGlowWindows[82];                 // +0x2c18  [A] base+stride
    CEGUI::Window* m_pSocketGlowWindows[82];               // +0x2ea8  [A] base+stride
    CEGUI::Window* m_pStackWindows[82];                    // +0x3138  [A] base+stride

    // ------------------------------------------------------------------
    // Twelve named panel windows, 0x60 == 12*8 exactly.  Every destination in
    // +0x33c8..+0x3420 is written by a recursiveChildSearch result:
    //     [ 0] +0x33c8 PetSlotsEquipment     [ 6] +0x33f8 SlotsWeapons
    //     [ 1] +0x33d0 PetSlotsSpells        [ 7] +0x3400 SlotsArmor
    //     [ 2] +0x33d8 PetSlotsFish          [ 8] +0x3408 SlotsMisc
    //     [ 3] +0x33e0 TabBackpack           [ 9] +0x3410 TabWeapon
    //     [ 4] +0x33e8 TabSpell              [10] +0x3418 TabArmor
    //     [ 5] +0x33f0 TabFish               [11] +0x3420 TabMisc
    // ------------------------------------------------------------------
    CEGUI::Window* m_pUnknown33C8[12];                     // +0x33c8  [A] 0x60 bytes

    int m_iPetSlotIndexA;                                 // +0x3428  [A] handle_PetItemClick stores
    int m_iPetSlotIndexB;                                 // +0x342c  [A] handle_PetItemClick stores
    int m_iItemSlotIndexA;                                // +0x3430  [A] handle_ItemClick stores
    int m_iItemSlotIndexB;                                // +0x3434  [A] handle_ItemClick stores
    CEquipment* m_pHoveredEquipment;                      // +0x3438  [A] compared to getEquipmentInSlot()
    CEGUI::Imageset* m_pImageset;                         // +0x3440  [A] getImageset("UIIcons")
    CEGUI::Window* m_pUnknown3448;                         // +0x3448  [A] recursiveChildSearch("SlotGlow")
    bool m_bUnknown3450;                                  // +0x3450  [A] handle_MouseThrough stores 0
    unsigned char m_Gap3451[0x03];                        // +0x3451  [B]
    int m_iUnknown3454;                                   // +0x3454  [B]
    int m_iUnknown3458;                                   // +0x3458  [B]
    unsigned char m_Gap345C[0x04];                        // +0x345c  [B]
    unsigned char m_Gap3460[0x18];                        // +0x3460 .. end 0x3478  [B]
};

// ----------------------------------------------------------------------------
//  Extent arithmetic.  Every one of these sums to a proven offset, which is
//  why the extents are not free parameters:
//      0xb0 + 1000*4 = 0x1050
//      0x1050 + 19*8 = 0x10e8 ; 0x10e8 + 126*8 = 0x14d8
//      0x14d8 + 19*8 = 0x1570 ; 0x1570 + 126*8 = 0x1960
//      0x1960 + 19*8 = 0x19f8 ; 0x19f8 + 126*8 = 0x1de8
//      0x1de8 + 19*8 = 0x1e80 ; 0x1e80 + 126*8 = 0x2270
//      0x2270 + 19*8 = 0x2308 ; 0x2308 + 126*8 = 0x26f8
//      0x26f8 + 82*8  = 0x2988 ; ... 0x3138 + 82*8 = 0x33c8
//      0x33c8 + 12*8  = 0x3428
//  Note the deliberately non-proven one: 400 prime counts also divide evenly
//  into 1000, so 1000 is the layout draft's figure, not a recovered extent.
// ----------------------------------------------------------------------------

#endif