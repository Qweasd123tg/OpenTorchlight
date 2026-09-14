#pragma once

#include "torchlight/level_scene.hpp"
#include "torchlight/randomizer.hpp"

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace torchlight {

struct LogicEvent {
    std::int64_t object_id = 0;
    std::u16string output_name;
};

struct LogicInvocation {
    std::int64_t source_object_id = 0;
    std::int64_t target_object_id = 0;
    std::u16string input_name;
};

struct SpawnRequest {
    std::int64_t spawner_id = 0;
    std::u16string resource;
    std::u16string group;
    std::uint32_t count = 0;
};

struct WarpRequest {
    std::int64_t warper_id = 0;
    std::u16string dungeon_name;
    std::u16string warp_name;
    std::int32_t level_delta = 0;
    std::optional<std::int32_t> absolute_level;
    bool waypoint = false;
};

struct LogicObjectState {
    bool enabled = true;
    bool visible = true;
    bool trigger_active = false;
    bool triggered_once = false;
    bool deactivated_once = false;
    std::int32_t counter = 0;
    bool timer_running = false;
    float timer_remaining = 0.0F;
    std::int32_t timer_loops_remaining = 0;
    std::uint32_t active_spawned_units = 0;
};

// Executes the event graph embedded in a LAYOUT. The runtime handles the
// generic graph machinery and the small stateful objects needed by ordinary
// level scripts. Inputs belonging to other game systems are retained as
// LogicInvocation records for their future subsystem implementations.
class LogicRuntime {
public:
    explicit LogicRuntime(const LayoutManifest& layout, std::uint32_t random_seed = 1);

    [[nodiscard]] const LogicObjectState* state(std::int64_t object_id) const noexcept;

    void activate_level();
    void emit(std::int64_t object_id, std::u16string_view output_name);
    void invoke(std::int64_t object_id, std::u16string_view input_name);
    void trigger(std::int64_t object_id);
    void deactivate_trigger(std::int64_t object_id);
    void update(float elapsed_seconds);
    void update_player_position(const std::array<float, 3>& position);

    void mark_spawn_complete(std::int64_t spawner_id);
    void notify_monster_killed(std::int64_t spawner_id);
    void notify_item_picked_up(std::int64_t spawner_id);

    [[nodiscard]] std::vector<LogicEvent> take_events();
    [[nodiscard]] std::vector<LogicInvocation> take_invocations();
    [[nodiscard]] std::vector<SpawnRequest> take_spawn_requests();
    [[nodiscard]] std::vector<WarpRequest> take_warp_requests();

private:
    struct Route {
        std::u16string output_name;
        std::int64_t target_object_id = 0;
        std::u16string input_name;
    };

    struct PendingEvent {
        std::int64_t object_id = 0;
        std::u16string output_name;
    };

    void process_events();
    void invoke_from(std::int64_t source_object_id, std::int64_t target_object_id,
                     std::u16string_view input_name);
    void reset_timer(const LayoutObject& object, LogicObjectState& state);
    void activate_trigger(const LayoutObject& object, LogicObjectState& state);
    [[nodiscard]] const LayoutObject& require_object(std::int64_t object_id) const;

    const LayoutManifest* layout_ = nullptr;
    std::vector<LayoutWorldTransform> transforms_;
    std::unordered_map<std::int64_t, std::size_t> object_indices_;
    std::unordered_map<std::int64_t, LogicObjectState> states_;
    std::unordered_map<std::int64_t, std::vector<Route>> routes_;
    std::vector<PendingEvent> pending_events_;
    std::size_t next_pending_event_ = 0;
    bool processing_events_ = false;
    TorchlightRandom random_;
    std::vector<LogicEvent> events_;
    std::vector<LogicInvocation> invocations_;
    std::vector<SpawnRequest> spawn_requests_;
    std::vector<WarpRequest> warp_requests_;
};

} // namespace torchlight
