#include "torchlight/player_session.hpp"
#include <utility>
#include <algorithm>
#include <limits>
#include <cmath>
#include <type_traits>
#include <stdexcept>

namespace torchlight {
namespace {
PlayerPrototype unarmed(PlayerPrototype prototype) {
    prototype.starting_weapon.reset();
    return prototype;
}
}
PlayerSession::PlayerSession(const PlayerPrototype& prototype, std::uint32_t seed,
                             const UnitTypeHierarchy* hierarchy)
    : progression_rules_(prototype.progression_rules),
      base_attributes_{prototype.strength, prototype.dexterity, prototype.magic, prototype.defense},
      gold_(std::max(0, prototype.starting_gold)), hardcore_(prototype.hardcore),
      combat_(unarmed(prototype), seed), health_(prototype, seed) {
    if (prototype.starting_weapon) {
        TorchlightRandom random(seed);
        InventoryItem item;
        item.resource_guid = prototype.starting_weapon->guid;
        item.name = prototype.starting_weapon->name;
        item.display_name = prototype.starting_weapon->display_name;
        item.unit_type = prototype.starting_weapon->unit_type;
        item.mesh_path = prototype.starting_weapon->mesh_path;
        item.two_handed = hierarchy && hierarchy->is_a_id(item.unit_type, 10);
        item.weapon = roll_weapon_item(*prototype.starting_weapon, random);
        const auto id = inventory_.store(std::move(item));
        static_cast<void>(inventory_.equip(id));
        refresh_equipment();
    }
}
std::array<std::int32_t, 4> PlayerSession::attributes() const {
    auto values = base_attributes_;
    for (std::size_t i = 0; i < values.size(); ++i) {
        const auto n = static_cast<std::int64_t>(values[i]) + progression_.allocated[i];
        if (n < -1000000 || n > 1000000) throw std::invalid_argument("attribute outside supported range");
        values[i] = static_cast<std::int32_t>(n);
    }
    return values;
}
void PlayerSession::refresh_attributes() {
    const auto values = attributes();
    combat_.set_attributes(values[0], values[1]);
    health_.set_defense_attribute(values[3]);
}
bool PlayerSession::allocate_attribute(std::size_t index) {
    if (!progression_rules_ || !health_.alive() || combat_.attack_in_progress() ||
        index >= progression_.allocated.size() || progression_.stat_points == 0) return false;
    PlayerSession staged(*this);
    --staged.progression_.stat_points;
    ++staged.progression_.allocated[index];
    validate_progression(staged.progression_, *progression_rules_);
    staged.refresh_attributes();
    using std::swap;
    swap(progression_, staged.progression_);
    swap(combat_, staged.combat_);
    swap(health_, staged.health_);
    return true;
}
std::uint32_t PlayerSession::award_experience(std::int32_t amount) {
    if (!health_.alive() || !progression_rules_) return 0;
    auto next = progression_;
    const auto bonus = total_attack_effects(combat_.attack_loadout(), combat_.attack_character()).get(0x44);
    const auto levels = advance_progression(next, *progression_rules_, amount, bonus);
    // Preserve the action object and sampled clip: a multi-HIT kill must not
    // cancel/restart the current attack or invalidate its event cursor.
    auto vitals = health_;
    if (levels) {
        const auto& rule = progression_rules_->at(next.level);
        vitals.set_progression_vitals(rule.maximum_health, rule.base_mana);
    }
    using std::swap;
    swap(health_, vitals);
    progression_ = next;
    return levels;
}
RewardCollection PlayerSession::collect_kill_rewards(RuntimeEntityWorld& world) {
    RewardCollection result;
    for (auto& entity : world.entities()) {
        if (entity.kind != MasterResourceKind::monster || entity.alive ||
            !entity.player_kill || entity.reward_claimed) continue;
        if (!health_.alive() || !progression_rules_ || !entity.experience_reward) {
            ++result.unavailable;
        } else {
            const auto before = progression_.experience;
            result.levels += award_experience(*entity.experience_reward);
            result.experience += static_cast<std::int64_t>(progression_.experience) - before;
            ++result.kills;
        }
        entity.reward_claimed = true; // commit only after a successful award/explicit exclusion
    }
    return result;
}
std::optional<std::int32_t> PlayerSession::pick_up_gold(RuntimeEntityWorld& world,
    std::uint64_t id, LogicRuntime& logic) {
    const auto* entity = world.find(id);
    if (!health_.alive() || !entity || !entity->gold_amount || entity->inventory_eligible ||
        entity->kind != MasterResourceKind::item || !entity->alive || !entity->enabled || !entity->visible)
        return std::nullopt;
    const auto amount = *entity->gold_amount;
    if (amount < 0) throw std::invalid_argument("negative world gold");
    if (!world.pick_up(id, logic)) return std::nullopt;
    give_gold(amount);
    return amount;
}
void PlayerSession::give_gold(std::int32_t amount) noexcept {
    const auto total = static_cast<std::int64_t>(gold_) + amount;
    gold_ = static_cast<std::int32_t>(std::clamp<std::int64_t>(
        total, 0, std::numeric_limits<std::int32_t>::max()));
}
RecoveryResult PlayerSession::recover_at_entry(EnemyController& enemies, ActorMotion& motion,
    const std::array<float, 3>& anchor) noexcept {
    if (health_.alive()) return {RecoveryStatus::alive, 0};
    if (hardcore_) return {RecoveryStatus::hardcore, 0};
    for (const auto value : anchor)
        if (!std::isfinite(value)) return {RecoveryStatus::invalid_anchor, 0};
    const auto loss = gold_ / 10; // original signed /10, gold invariant is nonnegative.
    give_gold(-loss);
    // Do not use enter_level(): the level and its clip resolver remain loaded.
    combat_.clear_target();
    combat_.interrupt_attack();
    enemies.level_resetting();
    health_.restore_after_death();
    motion = ActorMotion(anchor, motion.speed());
    return {RecoveryStatus::recovered, loss};
}
InventoryId PlayerSession::pick_up(RuntimeEntityWorld& world, std::uint64_t entity_id,
                                   LogicRuntime& logic) {
    if (!health_.alive()) return 0;
    const auto* entity = world.find(entity_id);
    if (!entity || !entity->alive || !entity->enabled || !entity->visible ||
        entity->kind != MasterResourceKind::item || !entity->inventory_eligible) return 0;
    InventoryItem item;
    item.resource_guid = entity->resource_guid;
    item.name = entity->name;
    item.display_name = entity->display_name;
    item.unit_type = entity->unit_type;
    item.mesh_path = entity->mesh_path;
    item.weapon = entity->weapon_item;
    item.armor = entity->armor_item;
    item.two_handed = entity->two_handed;
    // Allocate/store first. Failure to allocate leaves the world item untouched.
    // This is a single-threaded transfer; no persistent world pointer is kept.
    const auto id = inventory_.store(std::move(item));
    if (!world.pick_up(entity_id, logic)) {
        static_cast<void>(inventory_.erase(id));
        return 0;
    }
    return id;
}
InventoryChange PlayerSession::equip(InventoryId id) { return change_equipment(id, false); }
InventoryChange PlayerSession::unequip(InventoryId id) { return change_equipment(id, true); }
InventoryChange PlayerSession::change_equipment(InventoryId id, bool remove) {
    if (!health_.alive()) return InventoryChange::dead;
    if (combat_.attack_in_progress()) return InventoryChange::busy;
    // Portable transaction: resource-derived overflow/invalid effects must not
    // replace a slot while leaving combat, armor and mana from different items.
    // Copying inactive action state neither issues events nor advances RNG.
    PlayerSession staged(*this);
    const auto result = remove ? staged.inventory_.unequip(id) : staged.inventory_.equip(id);
    if (result != InventoryChange::changed) return result;
    staged.refresh_equipment();
    static_assert(std::is_nothrow_swappable_v<PlayerInventory> &&
                  std::is_nothrow_swappable_v<CombatController> &&
                  std::is_nothrow_swappable_v<PlayerCombatState>);
    using std::swap;
    swap(inventory_, staged.inventory_);
    swap(combat_, staged.combat_);
    swap(health_, staged.health_);
    return result;
}
void PlayerSession::refresh_equipment() {
    if (const auto* item = weapon(); item && item->weapon) combat_.equip(*item->weapon);
    else combat_.unequip();
    AttackEffects effects;
    for (std::size_t i = 0; i < static_cast<std::size_t>(ArmorSlot::count); ++i) {
        const auto* item = inventory_.equipped(static_cast<InventorySlot>(i + 1));
        if (item && item->armor) { health_.equip(*item->armor); effects.append(item->armor->attack_effects); }
        else health_.unequip(static_cast<ArmorSlot>(i));
    }
    combat_.set_external_attack_effects(effects);
    // Original equipped hand effects belong to the same effect manager for mana.
    if (const auto* item = weapon(); item && item->weapon)
        effects.append(item->weapon->prototype.attack_effects);
    health_.set_equipment_mana_effects(effects);
}
} // namespace torchlight
