// Partial: generated from symbols, RTTI and recovered layouts; unused return types remain hypotheses.
// -----------------------------------------------------------------------------
// CStashMenu.h -- recovered declaration of CStashMenu (compiled size 0x3428).
//
// TARGET OF RECONSTRUCTION
//   _ZN10CStashMenu11createMenusEv @ 0xbfbe20, 33050 bytes, TU 202 (stashmenu.cpp)
//
// EVIDENCE CLASSES (same convention as the supplied headers)
//   [A] established - read straight out of input/original.asm, or named by an
//                     original symbol in input/metadata.json /
//                     input/evidence-supplement/references.json.
//   [B] structural  - forced by the [A] facts around it; name is a reconstruction.
//   [C] hypothesis  - ABI-compatible, not uniquely recoverable.
//
// OFFSET ENFORCEMENT
//   Every proven offset below is produced by *real* declared members and
//   `unsigned char` padding arrays, not by comments.  The comments give the
//   offset for the reader; the padding is what makes the compiler reproduce it.
//   The whole chain is anchored at both ends:
//       +0x0000  CSubMenu (== CRunicCore, vptr + m_pSafePointers) 0x10 bytes
//       +0x0010  iInventoryListener sub-object, 0x08 bytes  (_ZThn16_ thunks)
//       ...      ...
//       +0x3420  bool m_bUnknown3420
//       +0x3421  bool m_bUnknown3421   -> last named byte ends at0x3422; compiler rounds sizeof to0x3428 (13352)
//   The draft end marker is not sizeof: alignment rounds it up.
//   Original allocation size is not independently established in this pass.
//
// CORRECTIONS APPLIED IN THIS REVISION (see output/parts/10-repair-log.md)
//   1. +0x90 is CGenericModel*, not CPositionableObject*.
//      input/project-headers/ResourceManager.h:36 declares the return type of
//      createGenericModel() as CGenericModel*, and
//      input/supervisor-verification/sdk-layout-facts.json gives
//      CGenericModel size 592 with CPositionableObject (size 256) at offset 0.
//   2. +0x3410 is CEGUI::Imageset*, not void*: it receives the result of
//      CEGUI::ImagesetManager::getImageset() which returns Imageset*.
//   3. +0x33c8 .. +0x33f0 are six DISTINCT CEGUI::Window* members.  Each one
//      receives its own recursiveChildSearch() result and is reloaded for its
//      own call.  They are deliberately NOT merged into an array.
//   4. The eleven array extents are now derived, not guessed: each runs up to
//      the next proven address.
// -----------------------------------------------------------------------------

#ifndef STASHMENU_H
#define STASHMENU_H

#include "SubMenu.h"
#include "iInventoryListener.h"

#include "DynamicPropertyFile.h"
#include "FileSystem.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "StringUtilities.h"

#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>

class CBaseUnit;
class CCharacter;
class CEquipment;
class CGenericModel;
class CSoundBank;

namespace Ogre
{
    class RenderWindow;
    class SceneManager;
}

namespace CEGUI
{
    class Imageset;
}

class CStashMenu : public CSubMenu, public iInventoryListener
{
public:
    // ---- CSubMenu overrides, primary vtable slots 0..12 ---------------------
    // Declared with exactly the return types input/project-headers/SubMenu.h
    // uses; nothing here is a new return-type hypothesis of mine.
    virtual ~CStashMenu();                                        // slots 0,1

    virtual CBaseUnit* getOwner();                                // slot 2  [A]
    virtual bool isRight();                                       // slot 3  [A]
    virtual bool open();                                          // slot 4  [A]
    virtual bool openPartial();                                   // slot 5  [A]
    virtual float screenEdge();                                   // slot 6  [A]
    virtual void setOwner(CCharacter*);                           // slot 7  [A]
    virtual void setOpen(bool);                                   // slot 8  [A]
    virtual void updateLayout();                                  // slot 9  [A]
    virtual void update(float);                                   // slot 10 [A]
    virtual bool handle_onClick(const CEGUI::EventArgs&);         // slot 11 [A]
    virtual bool processInput(void*, float, bool);                // slot 12 [A]

    // ---- iInventoryListener overrides, primary slots 13..18 ---------------
    // Return types are void because input/project-headers/iInventoryListener.h
    // declares them void; metadata.json confirms no return_hint.
    virtual void equipmentPickedUp(CEquipment*);                  // slot 13 [A]
    virtual void equipmentDropped(CEquipment*);                   // slot 14 [A]
    virtual void equipmentEquipped(CEquipment*);                  // slot 15 [A]
    virtual void equipmentUnequipped(CEquipment*);                // slot 16 [A]
    virtual void equipmentUsed(CEquipment*);                      // slot 17 [A]
    virtual void inventoryDestroyed();
    // Primary slot19; onClick returns1 on all observed paths (0xbee5c0).
    // bool is ABI-consistent; exact source spelling is not uniquely recovered.
    virtual bool onClick(ELayoutFunction);                             // slot 19

    // ---- non-virtual members ----------------------------------------------
    // Signatures are from the mangled symbols in input/metadata.json.  The four
    // handlers that are handed to CEGUI::SubscriberSlot are forced to return
    // bool by CEGUIMemberFunctionSlot.h:46, not by choice.
    void createMenus();                                           // [A] symbol
    void mapEventHandlers(CEGUI::Window*);                        // [A] symbol
    void setSlotIcon(CEquipment*, int, int);                       // [A] symbol
    void setPetSlotIcon(CEquipment*, int, int);                    // [A] symbol
    void setPlayer(CCharacter*);                                   // [A] symbol
    void setPetTab(int);                                           // [A] symbol

    bool handle_ItemClick(const CEGUI::EventArgs&);                // [A] symbol
    bool handle_PetItemClick(const CEGUI::EventArgs&);             // [A] symbol
    bool handle_MouseOut(const CEGUI::EventArgs&);                 // [A] symbol
    bool handle_PetMouseOut(const CEGUI::EventArgs&);              // [A] symbol
    bool handle_MouseThrough(const CEGUI::EventArgs&);             // [A] symbol
    bool handle_MouseOver(const CEGUI::EventArgs&);                // [A] symbol
    bool handle_PetMouseOver(const CEGUI::EventArgs&);             // [A] symbol
    bool handle_CloseButton(const CEGUI::EventArgs&);              // [A] symbol

    CStashMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
               CEGUI::Window*, CResourceManager*);                 // [A] full

    // ======================= data, in strict offset order ====================
    // (the draft name is kept where the listing does not prove a better one)

    // [A] receives a createWindow()/recursiveChildSearch() result.  Not touched
    // by createMenus; typed Window* because it shares the run with +0x20.
    CEGUI::Window* m_pUnknown18;                          // +0x0018

    // [A] createWindow("DefaultWindow", "StashSheet", "") at bf c68c.
    CEGUI::Window* m_pUnknown20;                          // +0x0020
    // [A] recursiveChildSearch("TopFrame") in the loaded layout.
    CEGUI::Window* m_pUnknown28;                          // +0x0028
    // [A] createWindow("DefaultWindow", "SSockets", "").
    CEGUI::Window* m_pUnknown30;                          // +0x0030
    // [A] createWindow("DefaultWindow", "SSocketsO", "").
    CEGUI::Window* m_pUnknown38;                          // +0x0038
    // [A] recursiveChildSearch("BottomFrame") in the loaded layout.
    CEGUI::Window* m_pUnknown40;                          // +0x0040

    unsigned char  m_Unrecovered48[0x08];                 // +0x0048

    CBaseUnit*     m_pOwner;                              // +0x0050  [A] getOwner
    CCharacter*    m_pCharacter;                          // +0x0058  [A] setPlayer
    bool           m_bOpenPartial;                        // +0x0060  [A] openPartial
    bool           m_bUnknown61;                          // +0x0061
    bool           m_bUnknown62;                          // +0x0062
    unsigned char  m_Unrecovered63[0x05];                 // +0x0063

    // [A] receiver of GetInt() and GetFloat() at the head of createMenus.
    CDynamicPropertyFile* m_pDynamicPropertyFile;         // +0x0068
    // [A] receiver of convertToScreenScale() and mapToFunctions().
    CGameUI*       m_pGameUI;                             // +0x0070
    // [A] 2nd argument of CResourceManager::createGenericModel().
    Ogre::SceneManager* m_pUnknown78;                     // +0x0078
    Ogre::RenderWindow* m_pUnknown80;                     // +0x0080
    unsigned char  m_Unrecovered88[0x08];                 // +0x0088

    // [A] receives CResourceManager::createGenericModel()'s return value, whose
    // declared type is CGenericModel*.  See correction 1.
    CGenericModel* m_pUnknown90;                          // +0x0090
    CResourceManager* m_pResourceManager;                 // +0x0098
    float          m_fScreenEdge;                         // +0x00a0
    unsigned char  m_UnrecoveredA4[0x04];                 // +0x00a4
    CSoundBank*    m_pSoundBank;                          // +0x00a8

    // [A] base +0xb0 and stride 4 are proven by the clearing loop at bfdf60:
    //     `mov %eax,0xb0(%rdx) ; add $4,%rdx ; cmp $0x190,%eax` -- 400 four-byte
    //     stores, not a memset and not eight-byte stores.  400 is the proven
    //     extent; the array subsumes the draft's single `m_iUnknownB0` int.
    //     Both socket loops index it as `&m_aiSlotData[i + 18]`.
    int            m_aiSlotData[400];                     // +0x00b0 .. +0x06ef

    unsigned char  m_Unrecovered6F0[0x960];               // +0x06f0
    long long      m_Unknown1050;                          // +0x1050
    unsigned char  m_Unrecovered1058[0x90];               // +0x1058

    // ===== the five item-socket arrays =====================================
    // Loop: for (i = 1; i < 43; ++i), element i-1.  42 of the 126 slots are
    // written; 126 is forced because the array runs up to the next proven
    // address, +0x14d8.

    // image, added to slot->getParent(), muted, copies the slot's rect
    CEGUI::Window* m_apItemSocketGlowWindows[126];         // +0x10e8
    long long      m_Unknown14D8;                          // +0x14d8
    unsigned char  m_Unrecovered14E0[0x90];               // +0x14e0

    // image, added to slot->getParent(), then setAlwaysOnTop(true)
    CEGUI::Window* m_apItemStackWindows[126];              // +0x1570
    long long      m_Unknown1960;                          // +0x1960
    unsigned char  m_Unrecovered1968[0x90];               // +0x1968

    // image, added to m_pUnknown38 ("SSocketsO"), muted
    CEGUI::Window* m_apItemSocketOverlayWindows[126];     // +0x19f8
    // One 145-entry main-slot block; indexed from +0x1de8 by setPetSlotIcon.
    CEGUI::Window* m_pSocketedSizeWindows[145]; // +0x1de8
    long long      m_Unknown2270;                          // +0x2270
    unsigned char  m_Unrecovered2278[0x90];               // +0x2278

    // GuiLook/StaticText item-count label
    CEGUI::Window* m_apItemCountWindows[126];              // +0x2308
    // Five complete 82-entry pet blocks. createMenus fills indices19..81;
    // setPetSlotIcon uses the original full-index domain from each true base.
    CEGUI::Window* m_pSlotWindows[82];         // +0x26f8
    CEGUI::Window* m_pUnidentifiedWindows[82]; // +0x2988
    CEGUI::Window* m_pSlotGlowWindows[82];     // +0x2c18
    CEGUI::Window* m_pSocketGlowWindows[82];   // +0x2ea8
    CEGUI::Window* m_pStackWindows[82];        // +0x3138

    // ---- six DISTINCT pet-tab windows, all found in BottomFrame -----------
    // [A] Each is stored by its own `mov %rax,off(%rbx)` and reloaded for its
    //     own call; merging them into one array would contradict the listing.
    // [A] PetSlotsSpells and PetSlotsFish are additionally setVisible(false);
    //     PetSlotsEquipment is not.
    CEGUI::Window* m_pUnknown33c8;                         // +0x33c8 "PetSlotsEquipment"
    CEGUI::Window* m_pUnknown33d0;                         // +0x33d0 "PetSlotsSpells"
    CEGUI::Window* m_pUnknown33d8;                         // +0x33d8 "PetSlotsFish"
    // [A] The three tab frames each get their own setZOrderingEnabled(false).
    CEGUI::Window* m_pUnknown33e0;                         // +0x33e0 "TabBackpack"
    CEGUI::Window* m_pUnknown33e8;                         // +0x33e8 "TabSpell"
    CEGUI::Window* m_pUnknown33f0;                         // +0x33f0 "TabFish"

    // Not touched by createMenus; carried for a complete shape.  No socket-count
    // or inserted-item-list size is written anywhere in this function.
    int            m_iUnknown33F8;                         // +0x33f8
    int            m_iUnknown33FC;                         // +0x33fc
    int            m_iUnknown3400;                         // +0x3400
    int            m_iUnknown3404;                         // +0x3404
    long long      m_iUnknown3408;                         // +0x3408

    // [A] the "UIIcons" imageset.  See correction 2.
    CEGUI::Imageset* m_pUnknown3410;                       // +0x3410
    // [A] recursiveChildSearch("SlotGlow") inside TopFrame; muted, then removed
    // from its parent and deliberately NOT re-attached.
    CEGUI::Window* m_pUnknown3418;                         // +0x3418

    bool           m_bUnknown3420;                         // +0x3420
    bool           m_bUnknown3421;                         // +0x3421
};

#endif // STASHMENU_H