#pragma once

#include "torchlight/entity_world.hpp"
#include "torchlight/equipment.hpp"
#include "torchlight/navigation_grid.hpp"
#include "torchlight/player.hpp"
#include "torchlight/randomizer.hpp"

#include <array>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

namespace torchlight {

// original-code CCharacter::maxMana @0x813a10, evaluated effect contributions.
// Growth is an explicit persistent numeric input; no growth-effect lifecycle is inferred.
[[nodiscard]] std::int32_t evaluated_maximum_mana(std::int32_t base, float growth,
    const AttackEffects& effects);

class PlayerCombatState {
public:
    explicit PlayerCombatState(const PlayerPrototype& prototype,
                               std::uint32_t random_seed);

    [[nodiscard]] float health() const noexcept { return health_; }
    [[nodiscard]] float maximum_health() const noexcept { return maximum_health_; }
    [[nodiscard]] bool alive() const noexcept { return health_ > 0.0F; }
    [[nodiscard]] std::optional<float> mana() const noexcept { return mana_; }
    [[nodiscard]] std::optional<float> maximum_mana() const noexcept { return maximum_mana_; }
    [[nodiscard]] bool spend_mana(float amount) noexcept;
    void set_equipment_mana_effects(const AttackEffects& effects);
    // Restores vitals only: no stat reroll, equipment reset, or level rebuild.
    void restore_after_death() noexcept;
    [[nodiscard]] float collision_radius() const noexcept { return collision_radius_; }
    [[nodiscard]] std::int32_t apply_damage(
        std::int32_t damage, std::int32_t maximum_damage, DamageType type,
        TorchlightRandom& random) noexcept;
    [[nodiscard]] std::int32_t armor_class() const noexcept {
        return damage_defense_.effective(DamageType::physical);
    }
    void equip(const ArmorItem& item) noexcept;
    void unequip(ArmorSlot slot) noexcept;
    [[nodiscard]] const std::optional<ArmorItem>& equipped(
        ArmorSlot slot) const noexcept {
        return equipped_armor_[static_cast<std::size_t>(slot)];
    }

private:
    void refresh_damage_defense() noexcept;

    std::optional<std::int32_t> base_mana_;
    std::optional<float> mana_;
    std::optional<float> maximum_mana_;
    AttackEffects base_mana_effects_;
    float collision_radius_ = 0.0F;
    float health_ = 1.0F;
    float maximum_health_ = 1.0F;
    DamageDefense base_damage_defense_;
    DamageDefense damage_defense_;
    std::array<std::optional<ArmorItem>,
               static_cast<std::size_t>(ArmorSlot::count)> equipped_armor_{};
};

enum class EnemyAiState {
    idle,
    attacking,
    missed,
    unavailable,
    chasing,
    waiting,
    attacked,
    player_killed,
};

struct EnemyAiUpdate {
    EnemyAiState state = EnemyAiState::idle;
    std::uint64_t entity_id = 0;
    bool position_changed = false;
    std::int32_t damage = 0;
    float player_health = 0.0F;
};

// original-code: the signed CMonster+0x7e8 timer, not CCharacter's clip timer.
// The caller supplies finite values and a validated simulation delta. These
// scalar operations deliberately do not clip time or implement KAIThinkTime.
// See research/monster-ai-cooldown.md for the exact instruction ranges.
struct MonsterAiCooldown {
    float remaining = 0.0F;

    void update(float seconds) noexcept;
    void attack_started(float unit_cooldown,
                        std::optional<float> equipment_cooldown) noexcept;
    [[nodiscard]] bool blocks_attack() const noexcept {
        return remaining > 0.0F;
    }
};

class EnemyController {
public:
    explicit EnemyController(std::uint32_t random_seed) : random_(random_seed) {}

    [[nodiscard]] std::vector<EnemyAiUpdate> update(
        float seconds, const std::array<float, 3>& player_position,
        PlayerCombatState& player, RuntimeEntityWorld& world,
        const NavigationGrid* navigation = nullptr);

    void set_animation_resolver(AttackClipResolver resolver) { resolver_ = std::move(resolver); }
    void advance_animations(float seconds, const RuntimeEntityWorld& world, const PlayerCombatState& player);
    [[nodiscard]] EnemyAiUpdate perform_attack(std::uint64_t entity_id, const AnimationEventOccurrence& event,
        const std::array<float, 3>& player_position, PlayerCombatState& player, RuntimeEntityWorld& world);
    void finish_animation_frame() noexcept;
    // CLevel::restartLevel -> CCharacter::levelResetting: discard targets/actions,
    // not HP, bodies, positions, spawned items, random sequence or the AI timer.
    void level_resetting() noexcept;
    void interrupt_attack(std::uint64_t entity_id) noexcept;
    [[nodiscard]] const OrdinaryAttackAction* action(std::uint64_t entity_id) const noexcept;
    [[nodiscard]] const std::string& last_attack_issue(std::uint64_t entity_id) const noexcept;
    [[nodiscard]] float ai_cooldown_remaining(std::uint64_t entity_id) const noexcept;
    [[nodiscard]] std::size_t alerted_count() const noexcept;

private:
    struct State {
        bool alerted = false;
        MonsterAiCooldown ai_cooldown;
        OrdinaryAttackAction action;
        bool prefer_left = false;
        std::string attack_issue;
        float repath_after = 0.0F;
        std::vector<std::array<float, 3>> path;
        std::size_t next_path_node = 0;
    };

    [[nodiscard]] static float distance_xz(
        const std::array<float, 3>& left,
        const std::array<float, 3>& right) noexcept;
    static bool advance_toward_player(float seconds,
                                      const std::array<float, 3>& player_position,
                                      float stopping_distance,
                                      RuntimeEntity& entity, State& state) noexcept;

    AttackClipResolver resolver_;
    std::uint64_t next_execution_id_ = 1;
    TorchlightRandom random_;
    std::unordered_map<std::uint64_t, State> states_;
};

} // namespace torchlight
