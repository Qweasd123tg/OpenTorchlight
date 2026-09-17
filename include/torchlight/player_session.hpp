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
struct RewardCollection {
    std::uint32_t kills = 0, levels = 0, unavailable = 0;
    std::int64_t experience = 0;
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
    [[nodiscard]] ConsumableUse use_consumable(InventoryId id);
    [[nodiscard]] ConsumableUse use_recovery(bool health);
    [[nodiscard]] bool update_vitals(float seconds);
    [[nodiscard]] const std::vector<ActiveRecovery>& active_recovery() const noexcept { return active_recovery_; }
    // Enrich v1-v3 owned potions after loading with this exact resource catalog.
    // Does not grant items, reroll values, or replace v4 serialized descriptors.
    void hydrate_consumables(UnitDefinitionLoader&, const MasterResourceIndex&);
    [[nodiscard]] InventoryChange equip(InventoryId id);
    [[nodiscard]] InventoryChange unequip(InventoryId id);
    [[nodiscard]] std::int32_t gold() const noexcept { return gold_; }
    [[nodiscard]] std::optional<std::int32_t> pick_up_gold(RuntimeEntityWorld&, std::uint64_t, LogicRuntime&);
    [[nodiscard]] const ProgressionState& progression() const noexcept { return progression_; }
    [[nodiscard]] const ProgressionRules* progression_rules() const noexcept { return progression_rules_.get(); }
    [[nodiscard]] std::array<std::int32_t, 4> attributes() const;
    [[nodiscard]] bool allocate_attribute(std::size_t index);
    [[nodiscard]] std::uint32_t award_experience(std::int32_t amount);
    [[nodiscard]] RewardCollection collect_kill_rewards(RuntimeEntityWorld&);
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
    friend struct CheckpointAccess;
    [[nodiscard]] InventoryChange change_equipment(InventoryId id, bool remove);
    void refresh_equipment();
    void refresh_attributes();
    std::shared_ptr<const ProgressionRules> progression_rules_;
    ProgressionState progression_;
    std::array<std::int32_t, 4> base_attributes_{};
    std::int32_t gold_ = 0;
    bool hardcore_ = false;
    PlayerInventory inventory_;
    CombatController combat_;
    PlayerCombatState health_;
    std::vector<ActiveRecovery> active_recovery_;
};
} // namespace torchlight
