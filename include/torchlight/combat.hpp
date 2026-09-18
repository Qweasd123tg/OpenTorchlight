#pragma once

#include "torchlight/entity_world.hpp"
#include "torchlight/player.hpp"
#include "torchlight/randomizer.hpp"

#include <array>
#include <cstdint>
#include <optional>

namespace torchlight {

enum class CombatState { idle, approaching, waiting, attacking, attacked, killed, missed, unavailable };
struct CombatUpdate {
    CombatState state = CombatState::idle;
    std::uint64_t target_id = 0;
    std::int32_t damage = 0;
    float remaining_health = 0.0F;
    std::uint64_t execution_id = 0;
};

class CombatController {
public:
    CombatController(const PlayerPrototype& player, std::uint32_t random_seed);
    [[nodiscard]] bool select_target(RuntimeEntityWorld& world,
        const std::array<float, 3>& position, float maximum_distance) noexcept;
    void clear_target() noexcept;
    void equip(const WeaponItem& item);
    void unequip();
    void reset_level_context() noexcept;
    void interrupt_attack() noexcept;
    void set_animation_resolver(AttackClipResolver resolver);
    void set_line_of_sight(AttackLineOfSight resolver) { line_of_sight_ = std::move(resolver); }
    // Replaces evaluated non-hand equipment/active contributions, not base
    // UNIT passives. Live damage sees new effects; a running clip keeps its speed.
    void set_external_attack_effects(const AttackEffects& effects);
    [[nodiscard]] bool attack_in_progress() const noexcept { return action_.active(); }
    [[nodiscard]] const RuntimeEntity* target(const RuntimeEntityWorld& world) const noexcept;
    [[nodiscard]] std::uint64_t target_id() const noexcept { return target_id_; }
    [[nodiscard]] float attack_range() const noexcept { return attack_range_; }
    [[nodiscard]] float attack_playback_speed() const noexcept { return attack_playback_speed_; }
    [[nodiscard]] std::int32_t minimum_damage() const noexcept { return minimum_damage_; }
    [[nodiscard]] std::int32_t maximum_damage() const noexcept { return maximum_damage_; }
    [[nodiscard]] const OrdinaryAttackAction& action() const noexcept { return action_; }
    [[nodiscard]] const std::string& last_attack_issue() const noexcept { return last_attack_issue_; }
    [[nodiscard]] const AttackLoadout& attack_loadout() const noexcept { return loadout_; }
    [[nodiscard]] const AttackCharacterValues& attack_character() const noexcept { return character_; }

    // Four phases: decide/start -> advance -> sample pose -> deliver events.
    // Neither update() nor advance_animation() applies damage.
    [[nodiscard]] CombatUpdate update(float seconds, const std::array<float, 3>& position,
                                     RuntimeEntityWorld& world);
    void advance_animation(float seconds);
    [[nodiscard]] CombatUpdate perform_attack(const AnimationEventOccurrence& event,
        const std::array<float, 3>& position, RuntimeEntityWorld& world, LogicRuntime& logic);
    void finish_animation_frame() noexcept;
    // Missile delivery (original fireMissiles path): HIT consumes the event
    // and snapshots the damage context, but damage lands later through
    // apply_missile_impact when the application-owned runtime reports a hit.
    // Gates mirror perform_attack (target/reach/line-of-sight).
    struct MissileShot {
        AttackDescription description;
        AttackLoadout loadout;
        AttackCharacterValues character;
        std::uint64_t target_id = 0;
    };
    [[nodiscard]] std::optional<MissileShot> begin_missile_attack(
        const AnimationEventOccurrence& event, const std::array<float, 3>& position,
        RuntimeEntityWorld& world);
    [[nodiscard]] CombatUpdate apply_missile_impact(const MissileShot& shot, std::uint64_t victim_id,
        RuntimeEntityWorld& world, LogicRuntime& logic);
    // Recompute existing physical consumers without replacing the current action.
    void set_attributes(std::int32_t strength, std::int32_t dexterity, std::int32_t magic = 0);

private:
    friend struct CheckpointAccess;
    void refresh_attack_values();
    TorchlightRandom random_;
    std::string mesh_path_;
    AttackClipResolver resolver_;
    AttackLineOfSight line_of_sight_;
    AttackLoadout loadout_;
    AttackCharacterValues character_;
    AttackEffects base_effects_;
    OrdinaryAttackAction action_;
    std::string last_attack_issue_;
    std::uint64_t target_id_ = 0;
    std::uint64_t next_execution_id_ = 1;
    bool prefer_left_ = false;
    std::int32_t minimum_damage_ = 0;
    std::int32_t maximum_damage_ = 0;
    float attack_range_ = 0.0F;
    float attack_playback_speed_ = 1.0F;
};
} // namespace torchlight
