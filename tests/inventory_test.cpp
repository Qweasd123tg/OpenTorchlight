#include "torchlight/inventory.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace torchlight;
namespace {
std::size_t checks=0;
void require(bool value, const char* message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}
InventoryItem sword(int damage, bool two_handed=false) {
    InventoryItem item;
    item.resource_guid=50;
    item.name=u"Same resource";
    item.two_handed=two_handed;
    WeaponItem weapon;
    weapon.prototype.guid=50;
    weapon.minimum_damage=damage/2;
    weapon.maximum_damage=damage;
    item.weapon=weapon;
    return item;
}
InventoryItem armor(ArmorSlot slot, int value) {
    InventoryItem item;
    item.resource_guid=60;
    ArmorItem armor;
    armor.slot=slot;
    armor.armor=value;
    armor.damage_defense.natural_armor=value;
    item.armor=armor;
    return item;
}
}
int main() {
try {
    PlayerInventory inventory;
    const auto first=inventory.store(sword(21));
    const auto second=inventory.store(sword(37));
    require(first != second && first && second, "duplicate GUID needs distinct IDs");
    require(inventory.find(first)->weapon->maximum_damage==21, "first roll retained");
    require(inventory.find(second)->weapon->maximum_damage==37, "second roll retained");
    require(!inventory.equipped(InventorySlot::weapon), "store must not auto-equip");
    require(inventory.equip(first)==InventoryChange::changed, "equip first");
    require(inventory.equip(second)==InventoryChange::changed, "replace weapon");
    require(!inventory.equipped_slot(first) && inventory.find(first), "old weapon stays in bag");
    require(inventory.items().size()==2, "replace conserves item count");
    require(inventory.equip(second)==InventoryChange::unchanged, "equip is idempotent");
    require(!inventory.erase(second), "cannot erase equipped instance");
    const auto chest1=inventory.store(armor(ArmorSlot::chest,10));
    const auto chest2=inventory.store(armor(ArmorSlot::chest,40));
    const auto boots=inventory.store(armor(ArmorSlot::boots,7));
    require(inventory.equip(chest1)==InventoryChange::changed,"equip chest");
    require(inventory.equip(boots)==InventoryChange::changed,"equip other armor slot");
    require(inventory.equip(chest2)==InventoryChange::changed,"replace chest only");
    require(inventory.equipped(InventorySlot::boots)->id==boots,"boots not displaced");
    require(!inventory.equipped_slot(chest1),"replaced chest in bag");
    require(inventory.unequip(chest2)==InventoryChange::changed,"unequip chest");
    require(inventory.find(chest2) && !inventory.equipped(InventorySlot::chest),"unequip retains object");
    const auto twohand=inventory.store(sword(45,true));
    const auto shield=inventory.store(armor(ArmorSlot::shield,11));
    require(inventory.equip(shield)==InventoryChange::changed,"equip shield");
    require(inventory.equipped(InventorySlot::weapon)->id==second,"one-hand survives shield");
    require(inventory.equip(twohand)==InventoryChange::changed,"equip two-handed weapon");
    require(!inventory.equipped(InventorySlot::shield),"two-hander displaces shield");
    require(inventory.find(shield),"displaced shield not lost");
    require(inventory.equip(shield)==InventoryChange::changed,"equip shield after two-hander");
    require(!inventory.equipped(InventorySlot::weapon),"shield displaces two-hander");
    InventoryItem token; token.resource_guid=90;
    const auto unsupported=inventory.store(token);
    require(inventory.equip(unsupported)==InventoryChange::unsupported,"unknown item stays view-only");
    auto malformed=armor(ArmorSlot::count,20);
    const auto malformed_id=inventory.store(malformed);
    require(inventory.equip(malformed_id)==InventoryChange::unsupported,"reject invalid armor slot");
    require(!inventory.equipped(InventorySlot::count),"invalid slot safe");
    require(inventory.equip(0)==InventoryChange::not_found,"zero id rejected");
    require(inventory.unequip(123456)==InventoryChange::not_found,"foreign id rejected");
    require(!inventory.equipped_slot(0),"zero id never equipped");
    auto copied=inventory;
    require(copied.find(first)->weapon->maximum_damage==21,"copy retains roll");
    const auto potion = [](std::uint32_t count) {
        InventoryItem item; item.resource_guid=99;
        ConsumableItem consumable; consumable.count=count; consumable.maximum_stack=20;
        consumable.unavailable_reason="stack ownership fixture"; item.consumable=consumable;
        return item;
    };
    PlayerInventory stacks;
    const auto a=stacks.store(potion(18)), b=stacks.store(potion(18));
    const auto c=stacks.store(potion(4));
    require(stacks.items().size()==3 && stacks.find(a)->consumable->count==18 &&
            stacks.find(b)->consumable->count==18 && stacks.find(c)->consumable->count==4,
            "whole pickup must not spread across two partially full stacks");
    PlayerInventory ordered;
    const auto x=ordered.store(potion(20)), y=ordered.store(potion(20)), z=ordered.store(potion(20));
    for(unsigned n=0;n<14;++n) require(ordered.consume_one(x),"decrease first stack");
    for(unsigned n=0;n<11;++n) require(ordered.consume_one(y),"decrease second stack");
    for(unsigned n=0;n<13;++n) require(ordered.consume_one(z),"decrease third stack");
    require(ordered.store(potion(5))==z && ordered.find(x)->consumable->count==6 &&
            ordered.find(y)->consumable->count==9 && ordered.find(z)->consumable->count==12,
            "original selection compares later candidates against incoming count");
    const auto newer=copied.store(sword(100));
    require(newer>malformed_id,"copy retains identity allocator");
    require(!inventory.find(newer),"copy independent");
    for (int iteration=0;iteration<1000;++iteration) {
        const auto id=iteration%2 ? first : second;
        require(inventory.equip(id)==InventoryChange::changed,"alternating replacement");
        require(inventory.find(first)->weapon->maximum_damage==21,"no reroll first");
        require(inventory.find(second)->weapon->maximum_damage==37,"no reroll second");
        require(inventory.items().size()==9,"no loss or duplication on swaps");
    }
    std::cout<<"inventory_checks="<<checks<<'\n';
    return 0;
} catch(const std::exception& e) { std::cerr<<e.what()<<'\n'; return 1; }
}
