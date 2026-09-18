// Tests for the generated createMenus profiles (loop family + middle group).
// original-code: createMenus of CInventoryMenu @0xb569e0, CMerchantMenu
// @0xb6ed20, CPetMenu @0xb93350, CStashMenu @0xbfbe20, CCombineMenu @0xad7a50,
// CEnchantMenu @0xb2e0a0, CQuestMenu @0xbc6b90, CQuestDialogMenu @0xbb08f0,
// CSkillMenu @0xbe19c0, CJournalMenu @0xe3b5e0. Profile data is transcribed
// by tools/gen_menu_profiles.py from batch extractor output plus the
// hand-verified research/menu-key-loops.json; values below were spot-checked
// against the ASM slices during review.
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
bool has_loop(const torchlight::MenuCreateProfile& p, const char* keys,
              unsigned first, unsigned last, const char* base,
              const char* off) {
    for (const auto& l : p.loops)
        if (std::string(l.keys) == keys && l.first == first &&
            l.last == last && std::string(l.back_base) == base &&
            std::string(l.back_offset) == off)
            return true;
    return false;
}
} // namespace

int main() {
    using namespace torchlight;
    auto profiles = menu_create_profiles();
    require(profiles.size() == 10, "ten createMenus profiles");

    // Loop bounds and back-pointer bases from machine code.
    struct Expect {
        const char* cls;
        unsigned table_bound, slot_bound;
        const char* base;
        const char* index_offset;
    };
    const Expect expects[] = {
        {"CInventoryMenu", 12, 64, "0x80", "0x12"},
        {"CMerchantMenu", 127, 64, "0xb0", "0x12"},
        {"CPetMenu", 12, 64, "0xa0", "0x12"},
        {"CStashMenu", 43, 64, "0xb0", "0x12"},
        {"CCombineMenu", 4, 0, "0xf8", "0x0"},
        {"CEnchantMenu", 0, 0, "none", "none"},
        {"CQuestMenu", 0, 0, "0xd8", "none"},
        {"CQuestDialogMenu", 3, 0, "0x148", "0x0"},
        {"CSkillMenu", 0, 0, "none", "none"},
        {"CJournalMenu", 0, 0, "none", "none"},
    };
    for (const auto& e : expects) {
        const auto* p = find(profiles, e.cls);
        require(p != nullptr, "profile present");
        if (!p)
            continue;
        require(p->table_loop_bound == e.table_bound, "table bound");
        require(p->slot_loop_bound == e.slot_bound, "slot bound");
        require(std::string(p->table_array_base) == e.base, "table base");
        require(std::string(p->slot_array_base) == e.base, "slot base");
        require(std::string(p->index_offset) == e.index_offset, "index offset");
    }

    // Blocker/Close live grabs where the menu has them.
    for (const char* cls :
         {"CInventoryMenu", "CMerchantMenu", "CPetMenu", "CStashMenu", "CQuestMenu",
          "CSkillMenu", "CJournalMenu"}) {
        const auto* p = find(profiles, cls);
        require(has_grab(*p, "Blocker", "live"), "Blocker grab");
        require(has_grab(*p, "Close", "live"), "Close grab");
    }

    // Per-menu deltas (verified key lists).
    const auto* inv = find(profiles, "CInventoryMenu");
    const auto* merch = find(profiles, "CMerchantMenu");
    const auto* pet = find(profiles, "CPetMenu");
    const auto* stash = find(profiles, "CStashMenu");
    require(has_grab(*inv, "TopFrame", "0x28"), "inv TopFrame");
    require(has_grab(*inv, "PaperdollEquip", "live"), "inv paperdoll");
    require(has_grab(*merch, "TabArmor", "0x3418"), "merchant TabArmor");
    require(has_grab(*merch, "SlotsWeapons", "0x33f8"),
            "merchant SlotsWeapons");
    require(has_grab(*stash, "PetSlotsEquipment", "0x33c8"),
            "stash PetSlotsEquipment");
    require(has_grab(*pet, "XP", "0x9158"), "pet XP label");
    require(has_grab(*pet, "Mana", "0x9148"), "pet Mana label");
    require(has_grab(*pet, "SlotsFish", "0x91d0"), "pet SlotsFish");

    // Slot handler ids (original code addresses, names from symbols).
    require(has_handler(*inv, 0xb45810, "ItemClick"), "inv ItemClick");
    require(has_handler(*inv, 0xb4d590, "MouseOver"), "inv MouseOver");
    require(has_handler(*merch, 0xb61040, "ItemClick"), "merch ItemClick");
    require(has_handler(*merch, 0xb688e0, "MouseOver"), "merch MouseOver");
    require(has_handler(*pet, 0xb887a0, "ItemClick"), "pet ItemClick");
    require(has_handler(*pet, 0xb914d0, "MouseOver"), "pet MouseOver");
    require(has_handler(*stash, 0xbee420, "ItemClick"), "stash ItemClick");
    require(has_handler(*stash, 0xbf5830, "MouseOver"), "stash MouseOver");

    // Middle group deltas.
    const auto* combine = find(profiles, "CCombineMenu");
    const auto* enchant = find(profiles, "CEnchantMenu");
    const auto* quest = find(profiles, "CQuestMenu");
    const auto* qdialog = find(profiles, "CQuestDialogMenu");
    const auto* skill = find(profiles, "CSkillMenu");
    const auto* journal = find(profiles, "CJournalMenu");
    require(has_grab(*combine, "Accept", "0x80"), "combine Accept");
    require(has_handler(*combine, 0xacd330, "ItemClick"), "combine ItemClick");
    require(has_handler(*combine, 0xacd460, "MouseOver"), "combine MouseOver");
    require(has_loop(*combine, "ItemSlot", 1, 4, "0xf8", "0x0"),
            "combine ItemSlot 1..4");
    require(has_grab(*enchant, "ItemSlot", "live"), "enchant single ItemSlot");
    require(has_handler(*enchant, 0xb1bb10, "ItemClick"), "enchant ItemClick");
    require(has_loop(*enchant, "ItemSlot", 0, 0, "0xc4", "0x0"),
            "enchant singleton back-pointer");
    require(has_grab(*quest, "Abandon", "0x40"), "quest Abandon");
    require(has_grab(*quest, "FameReward", "0x58"), "quest FameReward");
    require(has_handler(*quest, 0xbba070, "QuestClick"), "quest QuestClick");
    require(has_loop(*quest, "Quest,QuestText", 1, 6, "none", "none"),
            "quest Quest/Text 1..6");
    require(has_loop(*quest, "ItemRewardBkg,ItemRewardSlot", 1, 3, "0xd8", "0x0"),
            "quest rewards 1..3");
    require(has_grab(*qdialog, "Portrait", "0x100"), "qdialog Portrait");
    require(has_handler(*qdialog, 0xba5370, "MouseOver"), "qdialog MouseOver");
    require(has_loop(*qdialog, "ItemBkg,ItemSlot", 1, 3, "0x148", "0x0"),
            "qdialog rewards 1..3");
    require(has_grab(*skill, "TabB", "0xb8"), "skill TabB");
    require(has_grab(*skill, "Skill Points", "0x88"), "skill points");
    require(has_handler(*skill, 0xbd87d0, "CloseButton"), "skill CloseButton");
    require(skill->loops.empty(), "skill has no key loops");
    require(has_grab(*journal, "JournalFrame", "0x78"),
            "journal frame");
    require(has_handler(*journal, 0xe332b0, "CloseButton"),
            "journal CloseButton");
    require(journal->loops.empty(), "journal has no key loops");

    // Key loops of the loop family (verified first/last/backs).
    require(has_loop(*inv, "Slot", 1, 63, "0x80", "0x12"), "inv slots");
    require(has_loop(*inv, "Spell", 1, 4, "none", "none"), "inv spells");
    require(has_loop(*merch, "Slot", 1, 126, "0xb0", "0x12"), "merch slots");
    require(has_loop(*merch, "PetSlot", 1, 63, "0xb0", "0x12"), "merch petslots");
    require(has_loop(*pet, "Slot", 1, 63, "0xa0", "0x12"), "pet slots");
    require(has_loop(*pet, "Spell", 1, 2, "none", "none"), "pet spells");
    require(has_loop(*stash, "Slot", 1, 42, "0xb0", "0x12"), "stash slots");
    require(has_loop(*stash, "PetSlot", 1, 63, "0xb0", "0x12"), "stash petslots");

    // Shared slot-key sequence for the whole family ("Slot" prefix in all
    // four literal pools; Slot1..Slot63 in the inventory layout).
    for (unsigned i = 1; i <= 63; ++i)
        require(inventory_slot_key(i) == "Slot" + std::to_string(i),
                "shared slot key format");

    if (failures == 0)
        std::printf("menu_create: %d assertions; 10 createMenus profiles\n",
                    assertions);
    return failures == 0 ? 0 : 1;
}
