#include "torchlight/logic_runtime.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

namespace torchlight {
namespace {

constexpr std::size_t kMaximumEventsPerDispatch = 16384;

class LogicRuntimeError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

const AdmProperty* property(const LayoutObject& object, const char16_t* name) noexcept {
    return object.find_property(name);
}

bool bool_value(const LayoutObject& object, const char16_t* name, bool fallback) {
    const auto* value = property(object, name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type != AdmValueType::boolean) {
        throw LogicRuntimeError("Layout logic property expected a boolean");
    }
    return std::get<bool>(value->value);
}

std::int32_t integer_value(const LayoutObject& object, const char16_t* name,
                           std::int32_t fallback) {
    const auto* value = property(object, name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type == AdmValueType::integer) {
        return std::get<std::int32_t>(value->value);
    }
    if (value->type == AdmValueType::unsigned_integer) {
        const auto number = std::get<std::uint32_t>(value->value);
        if (number > static_cast<std::uint32_t>(std::numeric_limits<std::int32_t>::max())) {
            throw LogicRuntimeError("Layout logic integer is out of range");
        }
        return static_cast<std::int32_t>(number);
    }
    throw LogicRuntimeError("Layout logic property expected an integer");
}

std::optional<std::int32_t> optional_integer(const LayoutObject& object,
                                             const char16_t* name) {
    if (property(object, name) == nullptr) {
        return std::nullopt;
    }
    return integer_value(object, name, 0);
}

float float_value(const LayoutObject& object, const char16_t* name, float fallback) {
    const auto* value = property(object, name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type == AdmValueType::floating) {
        return std::get<float>(value->value);
    }
    if (value->type == AdmValueType::double_precision) {
        return static_cast<float>(std::get<double>(value->value));
    }
    throw LogicRuntimeError("Layout logic property expected a float");
}

std::u16string text_value(const LayoutObject& object, const char16_t* name,
                          std::u16string fallback = {}) {
    const auto* value = property(object, name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type != AdmValueType::string && value->type != AdmValueType::translation &&
        value->type != AdmValueType::note) {
        throw LogicRuntimeError("Layout logic property expected text");
    }
    return std::get<std::u16string>(value->value);
}

bool is_player_trigger(const LayoutObject& object) noexcept {
    return object.descriptor == u"Player Sphere Trigger" ||
           object.descriptor == u"Player Box Trigger";
}

} // namespace

LogicRuntime::LogicRuntime(const LayoutManifest& layout, std::uint32_t random_seed)
    : layout_(&layout), transforms_(resolve_layout_world_transforms(layout)), random_(random_seed) {
    object_indices_.reserve(layout.objects.size());
    states_.reserve(layout.objects.size());
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        const auto& object = layout.objects[index];
        if (!object_indices_.emplace(object.id, index).second) {
            throw LogicRuntimeError("Layout logic runtime found a duplicate object ID");
        }
        LogicObjectState state;
        state.enabled = bool_value(object, u"ENABLED", true);
        state.visible = bool_value(object, u"VISIBLE", true);
        if (object.descriptor == u"Counter") {
            state.counter = integer_value(object, u"STARTING VALUE", 0);
        } else if (object.descriptor == u"Timer") {
            state.timer_loops_remaining = integer_value(object, u"LOOP COUNT", 1);
            if (state.timer_loops_remaining <= 0) {
                state.timer_loops_remaining = 1;
            }
            state.timer_running = state.enabled;
            reset_timer(object, state);
        }
        states_.emplace(object.id, state);
    }

    for (const auto& group : layout.logic_groups) {
        std::unordered_map<std::uint32_t, const LayoutLogicNode*> nodes;
        nodes.reserve(group.nodes.size());
        for (const auto& node : group.nodes) {
            if (!nodes.emplace(node.id, &node).second) {
                throw LogicRuntimeError("Logic Group contains a duplicate node ID");
            }
            static_cast<void>(require_object(node.object_id));
        }
        for (const auto& node : group.nodes) {
            for (const auto& link : node.links) {
                const auto target = nodes.find(link.target_node_id);
                if (target == nodes.end()) {
                    // Shipped layouts can retain editor links to deleted nodes.
                    // The original game loads those rooms, so keep the graph usable
                    // and expose the count for diagnostics.
                    ++dangling_link_count_;
                    continue;
                }
                routes_[node.object_id].push_back(
                    {link.output_name, target->second->object_id, link.input_name});
            }
        }
    }
}

const LogicObjectState* LogicRuntime::state(std::int64_t object_id) const noexcept {
    const auto found = states_.find(object_id);
    return found == states_.end() ? nullptr : &found->second;
}

const LayoutObject& LogicRuntime::require_object(std::int64_t object_id) const {
    const auto found = object_indices_.find(object_id);
    if (found == object_indices_.end()) {
        throw LogicRuntimeError("Logic event references an absent layout object");
    }
    return layout_->objects[found->second];
}

void LogicRuntime::activate_level() {
    for (const auto& group : layout_->logic_groups) {
        emit(group.object_id, u"Level Activated");
    }
    for (const auto& object : layout_->objects) {
        if (object.descriptor == u"Unit Spawner" &&
            bool_value(object, u"SPAWN ON CREATE", false)) {
            invoke(object.id, u"Spawn Units");
        } else if (object.descriptor == u"Timeline" &&
                   bool_value(object, u"START ON LOAD", false)) {
            invoke(object.id, u"Play");
        }
    }
}

void LogicRuntime::emit(std::int64_t object_id, std::u16string_view output_name) {
    static_cast<void>(require_object(object_id));
    pending_events_.push_back({object_id, std::u16string(output_name)});
    if (!processing_events_) {
        process_events();
    }
}

void LogicRuntime::process_events() {
    processing_events_ = true;
    std::size_t processed = 0;
    try {
        while (next_pending_event_ < pending_events_.size()) {
            if (++processed > kMaximumEventsPerDispatch) {
                throw LogicRuntimeError("Logic graph exceeded the event dispatch limit");
            }
            auto event = std::move(pending_events_[next_pending_event_++]);
            events_.push_back({event.object_id, event.output_name});
            const auto found = routes_.find(event.object_id);
            if (found == routes_.end()) {
                continue;
            }
            for (const auto& route : found->second) {
                if (route.output_name == event.output_name) {
                    invoke_from(event.object_id, route.target_object_id, route.input_name);
                }
            }
        }
        pending_events_.clear();
        next_pending_event_ = 0;
        processing_events_ = false;
    } catch (...) {
        pending_events_.clear();
        next_pending_event_ = 0;
        processing_events_ = false;
        throw;
    }
}

void LogicRuntime::invoke(std::int64_t object_id, std::u16string_view input_name) {
    invoke_from(0, object_id, input_name);
    if (!processing_events_) {
        process_events();
    }
}

void LogicRuntime::invoke_from(std::int64_t source_object_id, std::int64_t target_object_id,
                               std::u16string_view input_name) {
    const auto& object = require_object(target_object_id);
    auto& object_state = states_.at(target_object_id);
    invocations_.push_back(
        {source_object_id, target_object_id, std::u16string(input_name)});

    if (input_name == u"Enable") {
        object_state.enabled = true;
        if (object.descriptor == u"Timer") {
            object_state.timer_running = true;
            if (object_state.timer_loops_remaining <= 0) {
                object_state.timer_loops_remaining =
                    std::max(1, integer_value(object, u"LOOP COUNT", 1));
            }
            reset_timer(object, object_state);
        }
        emit(target_object_id, u"Enabled");
        return;
    }
    if (input_name == u"Disable") {
        object_state.enabled = false;
        object_state.timer_running = false;
        emit(target_object_id, u"Disabled");
        return;
    }
    if (input_name == u"Show") {
        object_state.visible = true;
        return;
    }
    if (input_name == u"Hide") {
        object_state.visible = false;
        return;
    }
    if (input_name == u"Trigger") {
        trigger(target_object_id);
        return;
    }
    if (input_name == u"Reset") {
        object_state.trigger_active = false;
        object_state.triggered_once = false;
        object_state.deactivated_once = false;
        if (object.descriptor == u"Counter") {
            object_state.counter = integer_value(object, u"STARTING VALUE", 0);
            object_state.enabled = true;
        } else if (object.descriptor == u"Timer") {
            object_state.timer_running = true;
            object_state.enabled = true;
            object_state.timer_loops_remaining =
                std::max(1, integer_value(object, u"LOOP COUNT", 1));
            reset_timer(object, object_state);
        } else if (object.descriptor == u"Unit Spawner") {
            object_state.active_spawned_units = 0;
        }
        return;
    }

    if (object.descriptor == u"Logic Group" && input_name == u"Start") {
        emit(target_object_id, u"Start");
        return;
    }
    if (object.descriptor == u"Counter" &&
        (input_name == u"Add" || input_name == u"Increment" ||
         input_name == u"Subtract" || input_name == u"Decrement")) {
        if (!object_state.enabled) {
            return;
        }
        const bool subtract = input_name == u"Subtract" || input_name == u"Decrement";
        object_state.counter += subtract ? -1 : 1;
        if (object_state.counter == integer_value(object, u"EQUALS VALUE", 10)) {
            emit(target_object_id, u"Activated");
            const auto behavior = text_value(object, u"LOGIC", u"Activate only once");
            if (behavior == u"Activate and reset") {
                object_state.counter = integer_value(object, u"STARTING VALUE", 0);
            } else {
                object_state.enabled = false;
            }
        }
        return;
    }
    if (object.descriptor == u"Unit Spawner" && input_name == u"Spawn Units") {
        if (!object_state.enabled) {
            return;
        }
        const auto count = static_cast<std::uint32_t>(
            std::max(0, integer_value(object, u"COUNT", 1)));
        spawn_requests_.push_back({target_object_id, text_value(object, u"RESOURCE"),
                                   text_value(object, u"GROUP"), count});
        return;
    }
    if (object.descriptor == u"Unit Spawner" && input_name == u"Destroy Spawned Units") {
        spawn_requests_.push_back(
            {target_object_id, {}, {}, 0, SpawnAction::destroy});
        return;
    }
    if (object.descriptor == u"Unit Spawner" &&
        input_name == u"Hide And Disable Spawned Units") {
        spawn_requests_.push_back(
            {target_object_id, {}, {}, 0, SpawnAction::hide_and_disable});
        object_state.enabled = false;
        return;
    }
    if (object.descriptor == u"Warper" && input_name == u"Activate Warper") {
        if (!object_state.enabled) {
            return;
        }
        warp_requests_.push_back(
            {target_object_id, text_value(object, u"DUNGEON NAME"),
             text_value(object, u"WARP NAME"), integer_value(object, u"LEVEL DELTA", 1),
             optional_integer(object, u"LEVEL ABSOLUTE"),
             bool_value(object, u"WAYPOINT", false)});
    }
}

void LogicRuntime::trigger(std::int64_t object_id) {
    const auto& object = require_object(object_id);
    auto& object_state = states_.at(object_id);
    if (!object_state.enabled) {
        return;
    }
    if (is_player_trigger(object)) {
        activate_trigger(object, object_state);
    } else {
        emit(object_id, u"Triggered");
    }
}

void LogicRuntime::activate_trigger(const LayoutObject& object, LogicObjectState& object_state) {
    if (object_state.trigger_active || !object_state.enabled) {
        return;
    }
    object_state.trigger_active = true;
    // CLogicTrigger::TriggerActivated invokes output 1 before output 0 on the
    // first activation. The descriptor names are Triggered First Time and Triggered.
    if (!object_state.triggered_once) {
        object_state.triggered_once = true;
        emit(object.id, u"Triggered First Time");
    }
    emit(object.id, u"Triggered");
}

void LogicRuntime::deactivate_trigger(std::int64_t object_id) {
    const auto& object = require_object(object_id);
    auto& object_state = states_.at(object_id);
    if (!is_player_trigger(object) || !object_state.trigger_active || !object_state.enabled) {
        return;
    }
    object_state.trigger_active = false;
    if (!object_state.deactivated_once) {
        object_state.deactivated_once = true;
        emit(object_id, u"Deactivated First Time");
    }
    emit(object_id, u"Deactivated");
}

void LogicRuntime::reset_timer(const LayoutObject& object, LogicObjectState& object_state) {
    const auto minimum = float_value(object, u"TIME", 1.0F);
    const auto maximum = float_value(object, u"MAXTIME", -1.0F);
    object_state.timer_remaining = maximum > minimum ? random_.between(minimum, maximum) : minimum;
}

void LogicRuntime::update(float elapsed_seconds) {
    if (!(elapsed_seconds >= 0.0F) || !std::isfinite(elapsed_seconds)) {
        throw LogicRuntimeError("Logic update requires a finite non-negative time step");
    }
    for (const auto& object : layout_->objects) {
        if (object.descriptor != u"Timer") {
            continue;
        }
        auto& object_state = states_.at(object.id);
        if (!object_state.enabled || !object_state.timer_running) {
            continue;
        }
        object_state.timer_remaining -= elapsed_seconds;
        while (object_state.timer_remaining <= 0.0F && object_state.enabled &&
               object_state.timer_running) {
            emit(object.id, u"Activated");
            const bool forever = bool_value(object, u"LOOPS FOREVER", false);
            if (!forever && --object_state.timer_loops_remaining <= 0) {
                object_state.timer_running = false;
                break;
            }
            const auto overshoot = object_state.timer_remaining;
            reset_timer(object, object_state);
            object_state.timer_remaining += overshoot;
        }
    }
}

void LogicRuntime::update_player_position(const std::array<float, 3>& position) {
    for (std::size_t index = 0; index < layout_->objects.size(); ++index) {
        const auto& object = layout_->objects[index];
        if (!is_player_trigger(object)) {
            continue;
        }
        auto& object_state = states_.at(object.id);
        bool inside = false;
        if (object_state.enabled) {
            const auto& transform = transforms_[index];
            const float dx = position[0] - transform.position[0];
            const float dy = position[1] - transform.position[1];
            const float dz = position[2] - transform.position[2];
            if (object.descriptor == u"Player Sphere Trigger") {
                const float scale = std::max({std::abs(transform.scale[0]),
                                              std::abs(transform.scale[1]),
                                              std::abs(transform.scale[2])});
                const float radius = float_value(object, u"RADIUS", 1.0F) * scale;
                inside = dx * dx + dy * dy + dz * dz <= radius * radius;
            } else {
                const auto local = inverse_rotate_vector(transform.orientation, {dx, dy, dz});
                const float half_x = float_value(object, u"DIMENSIONSX", 1.0F) *
                                     std::abs(transform.scale[0]) * 0.5F;
                const float half_y = float_value(object, u"DIMENSIONSY", 1.0F) *
                                     std::abs(transform.scale[1]) * 0.5F;
                const float half_z = float_value(object, u"DIMENSIONSZ", 1.0F) *
                                     std::abs(transform.scale[2]) * 0.5F;
                inside = std::abs(local[0]) <= half_x && std::abs(local[1]) <= half_y &&
                         std::abs(local[2]) <= half_z;
            }
        }
        if (inside && !object_state.trigger_active) {
            activate_trigger(object, object_state);
        } else if (!inside && object_state.trigger_active) {
            deactivate_trigger(object.id);
        }
    }
}

void LogicRuntime::mark_spawn_complete(std::int64_t spawner_id,
                                       std::uint32_t active_monster_count) {
    const auto& object = require_object(spawner_id);
    if (object.descriptor != u"Unit Spawner") {
        throw LogicRuntimeError("Spawn completion references a non-spawner object");
    }
    states_.at(spawner_id).active_spawned_units = active_monster_count;
    emit(spawner_id, u"All Units Spawned");
}

void LogicRuntime::synchronize_spawned_units(
    std::int64_t spawner_id, std::uint32_t active_monster_count) {
    const auto& object = require_object(spawner_id);
    if (object.descriptor != u"Unit Spawner") {
        throw LogicRuntimeError("Spawn synchronization references a non-spawner object");
    }
    states_.at(spawner_id).active_spawned_units = active_monster_count;
}

void LogicRuntime::notify_monster_killed(std::int64_t spawner_id) {
    const auto& object = require_object(spawner_id);
    if (object.descriptor != u"Unit Spawner") {
        throw LogicRuntimeError("Monster death references a non-spawner object");
    }
    auto& object_state = states_.at(spawner_id);
    if (object_state.active_spawned_units == 0) {
        return;
    }
    --object_state.active_spawned_units;
    emit(spawner_id, u"Monster Killed");
    if (object_state.active_spawned_units == 0) {
        emit(spawner_id, u"All Monsters Dead");
    }
}

void LogicRuntime::notify_item_picked_up(std::int64_t spawner_id) {
    const auto& object = require_object(spawner_id);
    if (object.descriptor != u"Unit Spawner") {
        throw LogicRuntimeError("Item pickup references a non-spawner object");
    }
    emit(spawner_id, u"Item Picked Up");
}

std::vector<LogicEvent> LogicRuntime::take_events() {
    return std::exchange(events_, {});
}

std::vector<LogicInvocation> LogicRuntime::take_invocations() {
    return std::exchange(invocations_, {});
}

std::vector<SpawnRequest> LogicRuntime::take_spawn_requests() {
    return std::exchange(spawn_requests_, {});
}

std::vector<WarpRequest> LogicRuntime::take_warp_requests() {
    return std::exchange(warp_requests_, {});
}

} // namespace torchlight
