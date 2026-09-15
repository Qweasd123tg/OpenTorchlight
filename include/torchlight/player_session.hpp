#pragma once
#include "torchlight/combat.hpp"
#include "torchlight/actor_motion.hpp"
#include "torchlight/enemy_ai.hpp"
#include "torchlight/inventory.hpp"

namespace torchlight {
// Session lifetime, not floor lifetime. No file saves or hidden references to a
// RuntimeEntityWorld. Item IDs are session-scoped, entity IDs remain floor-local.
enum class RecoveryStatus { recovered, alive, hardcore, invalid_anchor };
struct RecoveryResult {
    RecoveryStatus status = RecoveryStatus::alive;
    std::int32_t gold_lost = 0;
};
class PlayerSession {
public:
    PlayerSession(const PlayerPrototype& prototype, std::uint32_t seed,
                  const UnitTypeHierarchy* hierarchy = nullptr);
    [[nodiscard]] const PlayerInventory& inventory() const noexcept { return inventory_; }
    [[nodiscard]] CombatController& combat() noexcept { return combat_; }
    [[nodiscard]] const CombatController& combat() const noexcept { return combat_; }
    [[nodiscard]] PlayerCombatState& health() noexcept { return health_; }
    [[nodiscard]] const PlayerCombatState& health() const noexcept { return health_; }
    [[nodiscard]] InventoryId pick_up(RuntimeEntityWorld& world, std::uint64_t entity_id,
                                      LogicRuntime& logic);
    [[nodiscard]] InventoryChange equip(InventoryId id);
    [[nodiscard]] InventoryChange unequip(InventoryId id);
    [[nodiscard]] std::int32_t gold() const noexcept { return gold_; }
    [[nodiscard]] bool hardcore() const noexcept { return hardcore_; }
    // original-code giveGold: positive saturation, negative clamp, no wrapping.
    void give_gold(std::int32_t amount) noexcept;
    // Death menu mode 1 (entry): floor(gold/10), no experience/fame deduction.
    // Repositions atomically with validation; never loads or regenerates a floor.
    [[nodiscard]] RecoveryResult recover_at_entry(EnemyController& enemies, ActorMotion& motion,
        const std::array<float, 3>& anchor) noexcept;
    void enter_level() noexcept { combat_.reset_level_context(); }
    [[nodiscard]] const InventoryItem* weapon() const noexcept {
        return inventory_.equipped(InventorySlot::weapon);
    }
private:
    [[nodiscard]] InventoryChange change_equipment(InventoryId id, bool remove);
    void refresh_equipment();
    std::int32_t gold_ = 0;
    bool hardcore_ = false;
    PlayerInventory inventory_;
    CombatController combat_;
    PlayerCombatState health_;
};
} // namespace torchlight
