#pragma once

#include "torchlight/entity_world.hpp"
#include "torchlight/navigation_grid.hpp"
#include "torchlight/player.hpp"
#include "torchlight/randomizer.hpp"

#include <array>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace torchlight {

class PlayerCombatState {
public:
    explicit PlayerCombatState(const PlayerPrototype& prototype,
                               std::uint32_t random_seed);

    [[nodiscard]] float health() const noexcept { return health_; }
    [[nodiscard]] float maximum_health() const noexcept { return maximum_health_; }
    [[nodiscard]] bool alive() const noexcept { return health_ > 0.0F; }
    [[nodiscard]] float apply_damage(std::int32_t damage) noexcept;

private:
    float health_ = 1.0F;
    float maximum_health_ = 1.0F;
};

enum class EnemyAiState {
    idle,
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

class EnemyController {
public:
    explicit EnemyController(std::uint32_t random_seed) : random_(random_seed) {}

    [[nodiscard]] std::vector<EnemyAiUpdate> update(
        float seconds, const std::array<float, 3>& player_position,
        PlayerCombatState& player, RuntimeEntityWorld& world,
        const NavigationGrid* navigation = nullptr);

    [[nodiscard]] std::size_t alerted_count() const noexcept;

private:
    struct State {
        bool alerted = false;
        float cooldown = 0.0F;
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

    TorchlightRandom random_;
    std::unordered_map<std::uint64_t, State> states_;
};

} // namespace torchlight
