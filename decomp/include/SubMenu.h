// Partial: generated from symbols, RTTI and recovered layouts; assisted reconstruction.
// Sizes, used offsets and vtable slot order are checked. Unused return declarations
// remain ABI hypotheses and must not be exported as trusted prototypes.
#ifndef SUBMENU_H
#define SUBMENU_H

// Reconstructed declaration of CSubMenu (recovered size 0x10).
//
// Evidence classes used below:
//   [A] established  — pinned by original RTTI, a symbol, or instruction bytes.
//   [B] structural   — the slot index is forced by [A] slots around it, but no
//                      symbol proves the name/params.
//   [C] hypothesis   — ABI-compatible, not uniquely recoverable. See UNRESOLVED.md.
//
// CSubMenu derives CRunicCore (input/RunicCore.h, a project input that is reused
// unmodified). CRunicCore is vptr + m_pSafePointers == 0x10 bytes, which is the
// whole of CSubMenu: the recovered CSubMenu size of 0x10 leaves room for no data
// member of its own, and the destructor listing writes only the vptr before
// tail-calling CRunicCore::~CRunicCore. Hence CSubMenu declares no fields.

#include "RunicCore.h"

// Forward declarations instead of #include <CEGUIEventArgs.h>: only a reference
// parameter needs the type, and a forward declaration cannot fail on an include
// path. CEGUI::EventArgs is a class in the SDK, so this matches the real header.
namespace CEGUI
{
class EventArgs;
}

class CBaseUnit;
class CCharacter;

class CSubMenu : public CRunicCore
{
public:
    // Slots 0/1 are the D1/D0 pair of CSubMenu's own destructor: the original
    // emits both (0xae19a0, 0xae19b0, the latter tail-calling
    // Ogre::NedAllocImpl::deallocBytes).
    virtual ~CSubMenu();

    // Slots 2..6 — index established, return category established from the
    // CMerchantMenu overrides' register usage.
    virtual CBaseUnit* getOwner() = 0;                       // slot 2  [B] name, [A] pointer return
    virtual bool isRight() = 0;                              // slot 3  [A]
    virtual bool open() = 0;                                 // slot 4  [A]
    virtual bool openPartial() = 0;                          // slot 5  [A]
    virtual float screenEdge() = 0;                          // slot 6  [A]

    // Slots 7..10 — [B]. These fill the only unaccounted run between the
    // evidenced slot 6 and the evidenced slot 11, and the ordering agrees with
    // input/CSubMenu-generated.h. Nothing in the supplied evidence names them.
    virtual void setOwner(CCharacter*) = 0;                  // slot 7  [B]
    virtual void setOpen(bool) = 0;                          // slot 8  [B]
    virtual void updateLayout() = 0;                         // slot 9  [B]
    virtual void update(float) = 0;                          // slot 10 [B]

    // Slots 11/12 — [A]. Both original bodies are `mov $0x1,%eax; ret`, so both
    // return an integer 1; bool is a working ABI hypothesis, unlike the `void` in input/CSubMenu-generated.h.
    // Virtual slot 11 is also reported for CStatsMenu, so it is declared on this
    // base rather than introduced by CMerchantMenu.
    virtual bool handle_onClick(const CEGUI::EventArgs&);    // slot 11 [A]
    virtual bool processInput(void*, float, bool);            // slot 12 [A]
};

#endif
