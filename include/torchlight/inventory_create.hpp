#pragma once

// Portable model of the pure logic inside CInventoryMenu::createMenus.
//
// original-code: Torchlight.bin.x86_64
//   (SHA-256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b)
//   CInventoryMenu::createMenus @0xb569e0 plus the two tiny helpers it uses:
//   STRINGS::GetValueAsString(unsigned) @0xc91f60 and
//   STRINGS::uniqueName @0xc8ea50.
//
// BOUNDARY (see research/inventory-open.md "createMenus: карта"):
// only the engine-free facts are modelled here — search-key sequences, loop
// bounds, slot-key format, back-pointer indices, the subscription table and
// the unique-name format. NOT modelled: CEGUI windows, Ogre objects, layout
// loading, property writes, actual event delivery. Offsets below are the
// original CInventoryMenu field ids (roles, not port struct layout).

#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace torchlight {

// ---- tiny helpers (original-code, fully decoded) ---------------------------

// STRINGS::GetValueAsString(unsigned) @0xc91f60 is
//   std::ostringstream() << value; return str();
// with a default-constructed (C-locale) stream: plain decimal, no padding,
// no separators. Implemented as an explicit decimal conversion.
std::string original_uint_to_string(unsigned value);

// STRINGS::uniqueName(prefix) @0xc8ea50 is
//   prefix + "_" + decimal(++gUniqueNameValue)
// (separator byte '_' read from ELF rodata @0xfd3a73; the number comes from
// Ogre::StringConverter::toString(n, width=0, fill=' ', flags=0), i.e. plain
// decimal). The counter is a process-global in the original; here it is
// explicit state so tests pin the sequence.
class UniqueNameState {
public:
    explicit UniqueNameState(unsigned first = 0) : counter_(first) {}
    std::string make(const std::string& prefix);
    unsigned counter() const { return counter_; }

private:
    unsigned counter_;
};

// ---- createMenus wiring ----------------------------------------------------

// Static layout grabs: (search key, CInventoryMenu field id).
// Keys extracted from machine code; presence cross-checked against
// media/UI/inventorymenu.layout from pak.zip (resource-derived).
struct ChildGrab {
    const char* key;
    std::uint32_t menu_field;
};

inline const std::array<ChildGrab, 13>& inventory_static_grabs() {
    static const std::array<ChildGrab, 13> grabs = {{
        {"Blocker", 0},          // used immediately, not stored
        {"BottomFrame", 0x48},
        {"TopFrame", 0x28},
        {"SlotGlow", 0x1d00},
        {"Close", 0},            // used immediately (CloseButton wiring)
        {"PaperdollEquip", 0},   // used immediately
        {"RotateLeft", 0},       // used immediately (RotateLeft wiring)
        {"RotateRight", 0},      // used immediately (RotateRight wiring)
        {"TabBackpack", 0x9120},
        {"TabSpell", 0x9128},
        {"TabFish", 0x9130},
        {"Money", 0x9190},
        {"WeaponSwitch", 0x9198},
    }};
    return grabs;
}

// SlotsEquipment/Spells/Fish containers (grabbed, then hidden).
inline const std::array<ChildGrab, 3>& inventory_slot_containers() {
    static const std::array<ChildGrab, 3> grabs = {{
        {"SlotsEquipment", 0x9108},
        {"SlotsSpells", 0x9110},
        {"SlotsFish", 0x9118},
    }};
    return grabs;
}

// Slot loop (0xb5c4b9-0xb5e20f): counter i runs 1..63, key is
// "Slot" + GetValueAsString(i), back-pointer index is i + 0x12
// (window+0x1d8 = &menu->field_0x80[i + 0x12]).
inline constexpr unsigned kInventorySlotFirst = 1;
inline constexpr unsigned kInventorySlotCount = 63;
inline constexpr unsigned kInventorySlotBackOffset = 0x12;

inline std::string inventory_slot_key(unsigned i) {
    return "Slot" + original_uint_to_string(i);
}
inline unsigned inventory_slot_back_index(unsigned i) {
    return i + kInventorySlotBackOffset;
}

// Table loop (0xb59b00-0xb5b600): 12 iterations over the runtime name table
// 0x14c6b20 (contents live in .bss: an input here), back-pointer index is
// the plain counter, four menu arrays (+0x1028/+0x12b8/+0x17d8/+0x1548)
// are zeroed per iteration.
inline constexpr unsigned kInventoryTableLoopCount = 12;

// Subscription functors every wired slot gets (MemberFunctionSlot,
// vtable 0xfefcd0): handler ids are the original code addresses.
enum class InventorySlotHandler : std::uint32_t {
    item_click = 0xb45810,  // CInventoryMenu::handle_ItemClick
    mouse_over = 0xb4d590,  // CInventoryMenu::handle_MouseOver
};

inline const std::array<InventorySlotHandler, 2>& inventory_slot_handlers() {
    static const std::array<InventorySlotHandler, 2> handlers = {{
        InventorySlotHandler::item_click,
        InventorySlotHandler::mouse_over,
    }};
    return handlers;
}

// One recorded slot wiring: what createMenus decides for slot i.
struct InventorySlotWiring {
    unsigned counter;          // loop counter i (1..63)
    std::string key;           // "Slot<i>"
    unsigned back_index;       // menu+0x80[] index (i + 0x12)
    unsigned slot_array_index; // menu+0x10c0[] index (i - 1)
};

inline InventorySlotWiring inventory_slot_wiring(unsigned i) {
    return InventorySlotWiring{i, inventory_slot_key(i),
                               inventory_slot_back_index(i), i - 1};
}

// Full slot-wiring sequence of loop B (63 entries, "Slot1".."Slot63").
inline std::vector<InventorySlotWiring> inventory_all_slot_wirings() {
    std::vector<InventorySlotWiring> out;
    out.reserve(kInventorySlotCount);
    for (unsigned i = kInventorySlotFirst;
         i < kInventorySlotFirst + kInventorySlotCount; ++i)
        out.push_back(inventory_slot_wiring(i));
    return out;
}

} // namespace torchlight
