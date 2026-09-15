#pragma once
#include "torchlight/equipment.hpp"
#include <array>
#include <cstdint>
#include <optional>
#include <vector>

namespace torchlight {
using InventoryId = std::uint64_t;
// Portable slot numbering, NOT EEQUIP_LOCATIONS from the original executable.
enum class InventorySlot : std::size_t {
    weapon, chest, boots, gloves, helmet, shoulders, belt, shield, count
};
struct InventoryItem {
    InventoryId id = 0;
    std::int64_t resource_guid = 0;
    std::u16string name;
    std::u16string display_name;
    std::u16string unit_type;
    std::string mesh_path;
    std::optional<WeaponItem> weapon;
    std::optional<ArmorItem> armor;
    // Hand-classification is filled from original UNITTYPES ID 10 by callers.
    bool two_handed = false;
};
enum class InventoryChange { changed, unchanged, not_found, unsupported, busy, dead };

class PlayerInventory {
public:
    // Owns the already rolled instance, never re-rolls from a resource GUID.
    // Bag capacity, stacks and original pane numbering are not yet recovered.
    [[nodiscard]] InventoryId store(InventoryItem item);
    [[nodiscard]] bool erase(InventoryId id) noexcept;
    [[nodiscard]] InventoryChange equip(InventoryId id) noexcept;
    [[nodiscard]] InventoryChange unequip(InventoryId id) noexcept;
    [[nodiscard]] const InventoryItem* find(InventoryId id) const noexcept;
    [[nodiscard]] const InventoryItem* equipped(InventorySlot slot) const noexcept;
    [[nodiscard]] std::optional<InventorySlot> equipped_slot(InventoryId id) const noexcept;
    [[nodiscard]] static std::optional<InventorySlot> slot_for(const InventoryItem& item) noexcept;
    [[nodiscard]] const std::vector<InventoryItem>& items() const noexcept { return items_; }
private:
    InventoryId next_id_ = 1;
    std::vector<InventoryItem> items_;
    std::array<InventoryId, static_cast<std::size_t>(InventorySlot::count)> equipped_{};
};
[[nodiscard]] const char* inventory_slot_name(InventorySlot slot) noexcept;
} // namespace torchlight
