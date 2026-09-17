#include "torchlight/inventory.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <utility>

namespace torchlight {
static_assert(static_cast<std::size_t>(InventorySlot::count) ==
              static_cast<std::size_t>(ArmorSlot::count) + 1U,
              "Portable inventory/armor slot mapping must stay aligned");
InventoryId PlayerInventory::store(InventoryItem item) {
    if (item.consumable) {
        validate_consumable(*item.consumable);
        if (item.weapon || item.armor) throw std::invalid_argument("consumable equipment conflict");
        // Stage all stack changes: allocation failure cannot lose part of a pickup.
        auto staged = items_;
        auto remaining = item.consumable->count;
        InventoryId first = 0;
        for (auto& other : staged) {
            if (!other.consumable || other.weapon || other.armor ||
                other.resource_guid != item.resource_guid || other.name != item.name ||
                other.display_name != item.display_name || other.unit_type != item.unit_type ||
                other.mesh_path != item.mesh_path || !same_consumable(*other.consumable, *item.consumable)) continue;
            const auto take = std::min(remaining, other.consumable->maximum_stack - other.consumable->count);
            if (take == 0) continue;
            other.consumable->count += take;
            remaining -= take;
            if (!first) first = other.id;
            if (!remaining) break;
        }
        if (remaining) {
            if (next_id_ == 0 || next_id_ == std::numeric_limits<InventoryId>::max())
                throw std::overflow_error("Inventory instance ID exhausted");
            item.id = next_id_;
            item.consumable->count = remaining;
            staged.push_back(std::move(item));
            if (!first) first = next_id_;
        }
        items_.swap(staged);
        if (remaining) ++next_id_;
        return first;
    }
    if (next_id_ == 0) throw std::overflow_error("Inventory instance ID exhausted");
    const auto id = next_id_;
    item.id = id;
    items_.push_back(std::move(item));
    ++next_id_;
    return id;
}
const InventoryItem* PlayerInventory::find(InventoryId id) const noexcept {
    if (id == 0) return nullptr;
    const auto it = std::find_if(items_.begin(), items_.end(),
                                 [id](const auto& item) { return item.id == id; });
    return it == items_.end() ? nullptr : &*it;
}
bool PlayerInventory::erase(InventoryId id) noexcept {
    if (equipped_slot(id)) return false;
    const auto it = std::find_if(items_.begin(), items_.end(),
                                 [id](const auto& item) { return item.id == id; });
    if (it == items_.end()) return false;
    items_.erase(it);
    return true;
}
bool PlayerInventory::consume_one(InventoryId id) noexcept {
    const auto it = std::find_if(items_.begin(), items_.end(), [id](const auto& i) { return i.id == id; });
    if (it == items_.end() || !it->consumable || equipped_slot(id)) return false;
    auto& c = *it->consumable;
    if (c.count == 0 || (c.uses < 1 && c.uses != -9999)) return false;
    if (c.count > 1) --c.count;
    else if (c.uses == -9999) return true;
    else if (c.uses > 1) --c.uses;
    else items_.erase(it);
    return true;
}
std::optional<InventorySlot> PlayerInventory::slot_for(const InventoryItem& item) noexcept {
    if (item.armor) {
        const auto slot = static_cast<std::size_t>(item.armor->slot);
        if (slot < static_cast<std::size_t>(ArmorSlot::count))
            return static_cast<InventorySlot>(slot + 1U);
        return std::nullopt;
    }
    if (item.weapon) return InventorySlot::weapon;
    return std::nullopt;
}
const InventoryItem* PlayerInventory::equipped(InventorySlot slot) const noexcept {
    const auto index = static_cast<std::size_t>(slot);
    return index < equipped_.size() ? find(equipped_[index]) : nullptr;
}
std::optional<InventorySlot> PlayerInventory::equipped_slot(InventoryId id) const noexcept {
    if (id == 0) return std::nullopt;
    for (std::size_t i = 0; i < equipped_.size(); ++i)
        if (equipped_[i] == id) return static_cast<InventorySlot>(i);
    return std::nullopt;
}
InventoryChange PlayerInventory::equip(InventoryId id) noexcept {
    const auto* item = find(id);
    if (!item) return InventoryChange::not_found;
    const auto slot = slot_for(*item);
    if (!slot) return InventoryChange::unsupported;
    auto& destination = equipped_[static_cast<std::size_t>(*slot)];
    if (destination == id) return InventoryChange::unchanged;
    // CInventory hand-conflict branch uses ISA(10). Only one weapon set/hand
    // is modelled here; displaced instances stay in the same owned collection.
    if (*slot == InventorySlot::weapon && item->two_handed)
        equipped_[static_cast<std::size_t>(InventorySlot::shield)] = 0;
    if (*slot == InventorySlot::shield) {
        const auto* weapon = equipped(InventorySlot::weapon);
        if (weapon && weapon->two_handed) equipped_[0] = 0;
    }
    destination = id;
    return InventoryChange::changed;
}
InventoryChange PlayerInventory::unequip(InventoryId id) noexcept {
    if (!find(id)) return InventoryChange::not_found;
    const auto slot = equipped_slot(id);
    if (!slot) return InventoryChange::unchanged;
    equipped_[static_cast<std::size_t>(*slot)] = 0;
    return InventoryChange::changed;
}
const char* inventory_slot_name(InventorySlot slot) noexcept {
    constexpr const char* names[]{"WEAPON", "CHEST", "BOOTS", "GLOVES", "HELMET",
                                   "SHOULDERS", "BELT", "SHIELD"};
    const auto index = static_cast<std::size_t>(slot);
    return index < static_cast<std::size_t>(InventorySlot::count) ? names[index] : "NONE";
}
} // namespace torchlight
