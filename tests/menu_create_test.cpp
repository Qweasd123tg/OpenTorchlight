// Tests for the generated loop-family createMenus profiles.
// original-code: createMenus of CInventoryMenu @0xb569e0, CMerchantMenu
// @0xb6ed20, CPetMenu @0xb93350, CStashMenu @0xbfbe20. Profile data is
// transcribed by tools/gen_menu_profiles.py from batch extractor output;
// values below were spot-checked against the ASM slices during review.
#include "torchlight/inventory_create.hpp"
#include "torchlight/menu_create_profiles.hpp"

#include <cstdio>
#include <string>

namespace {
int failures = 0;
int assertions = 0;
void require(bool cond, const char* what) {
    ++assertions;
    if (!cond) {
        ++failures;
        std::printf("FAIL: %s\n", what);
    }
}
const torchlight::MenuCreateProfile* find(
    const std::vector<torchlight::MenuCreateProfile>& ps, const char* cls) {
    for (const auto& p : ps)
        if (std::string(p.menu_class) == cls)
            return &p;
    return nullptr;
}
bool has_grab(const torchlight::MenuCreateProfile& p, const char* key,
              const char* field) {
    for (const auto& g : p.grabs)
        if (std::string(g.key) == key && std::string(g.menu_field) == field)
            return true;
    return false;
}
bool has_handler(const torchlight::MenuCreateProfile& p, std::uint32_t id,
                 const char* name) {
    for (const auto& h : p.handlers)
        if (h.id == id && std::string(h.name) == name)
            return true;
    return false;
}
} // namespace

int main() {
    using namespace torchlight;
    auto profiles = menu_create_profiles();
    require(profiles.size() == 4, "four loop-family profiles");

    // Loop bounds and back-pointer bases from machine code.
    struct Expect {
        const char* cls;
        unsigned table_bound, slot_bound;
        const char* base;
    };
    const Expect expects[] = {
        {"CInventoryMenu", 12, 64, "0x80"},
        {"CMerchantMenu", 127, 64, "0xb0"},
        {"CPetMenu", 12, 64, "0xa0"},
        {"CStashMenu", 43, 64, "0xb0"},
    };
    for (const auto& e : expects) {
        const auto* p = find(profiles, e.cls);
        require(p != nullptr, "profile present");
        if (!p)
            continue;
        require(p->table_loop_bound == e.table_bound, "table bound");
        require(p->slot_loop_bound == e.slot_bound, "slot bound is 64");
        require(std::string(p->table_array_base) == e.base, "table base");
        require(std::string(p->slot_array_base) == e.base, "slot base");
        require(std::string(p->index_offset) == "0x12", "index offset +0x12");
    }

    // Shared skeleton grabs present in every member.
    for (const auto& p : profiles) {
        require(has_grab(p, "Blocker", "live"), "Blocker grab");
        require(has_grab(p, "Close", "live"), "Close grab");
    }

    // Per-menu deltas (verified key lists).
    const auto* inv = find(profiles, "CInventoryMenu");
    const auto* merch = find(profiles, "CMerchantMenu");
    const auto* pet = find(profiles, "CPetMenu");
    const auto* stash = find(profiles, "CStashMenu");
    require(has_grab(*inv, "TopFrame", "0x28(%menu)"), "inv TopFrame");
    require(has_grab(*inv, "PaperdollEquip", "live"), "inv paperdoll");
    require(has_grab(*merch, "TabArmor", "0x3418(%menu)"), "merchant TabArmor");
    require(has_grab(*merch, "SlotsWeapons", "0x33f8(%menu)"),
            "merchant SlotsWeapons");
    require(has_grab(*stash, "PetSlotsEquipment", "0x33c8(%menu)"),
            "stash PetSlotsEquipment");
    require(has_grab(*pet, "XP", "0x9158(%menu)"), "pet XP label");
    require(has_grab(*pet, "Mana", "0x9148(%menu)"), "pet Mana label");
    require(has_grab(*pet, "SlotsFish", "0x91d0(%menu)"), "pet SlotsFish");

    // Slot handler ids (original code addresses, names from symbols).
    require(has_handler(*inv, 0xb45810, "ItemClick"), "inv ItemClick");
    require(has_handler(*inv, 0xb4d590, "MouseOver"), "inv MouseOver");
    require(has_handler(*merch, 0xb61040, "ItemClick"), "merch ItemClick");
    require(has_handler(*merch, 0xb688e0, "MouseOver"), "merch MouseOver");
    require(has_handler(*pet, 0xb887a0, "ItemClick"), "pet ItemClick");
    require(has_handler(*pet, 0xb914d0, "MouseOver"), "pet MouseOver");
    require(has_handler(*stash, 0xbee420, "ItemClick"), "stash ItemClick");
    require(has_handler(*stash, 0xbf5830, "MouseOver"), "stash MouseOver");

    // Shared slot-key sequence for the whole family ("Slot" prefix in all
    // four literal pools; Slot1..Slot63 in the inventory layout).
    for (unsigned i = 1; i <= 63; ++i)
        require(inventory_slot_key(i) == "Slot" + std::to_string(i),
                "shared slot key format");

    if (failures == 0)
        std::printf("menu_create: %d assertions; 4 loop-family profiles\n",
                    assertions);
    return failures == 0 ? 0 : 1;
}
