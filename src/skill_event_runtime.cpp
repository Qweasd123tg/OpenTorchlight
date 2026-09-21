#include "torchlight/skill_event_runtime.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/resource_fields.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace torchlight {
std::u16string_view skill_event_type_name(SkillEventType type) noexcept {
    static constexpr const char16_t* names[] = {
        u"EVENT_START", u"EVENT_END", u"EVENT_TRIGGER", u"EVENT_TRIGGER_TWO",
        u"EVENT_UNITHIT", u"EVENT_UNITDIE", u"EVENT_MISSILEHIT",
        u"EVENT_MISSILEDIE", u"EVENT_DIEBYEFFECT", u"EVENT_CASTERDIE", u"EVENT_UNIT_CREATE"};
    const auto index = static_cast<int>(type);
    return index >= 0 && index < 11 ? std::u16string_view(names[index]) : std::u16string_view{};
}
SkillEventRuntime::SkillEventRuntime(std::string name, std::shared_ptr<const SkillEventProgram> program)
    : skill_name_(std::move(name)), program_(std::move(program)) {}
bool SkillEventRuntime::has_event(SkillEventType type) const noexcept {
    return program_ && std::any_of(program_->events.begin(), program_->events.end(),
        [type](const auto& event) { return event.type == type; });
}
SkillStartResult SkillEventRuntime::start_skill(const SkillCastContext& context) {
    // Original startSkill @0xca9150: caster and property guards, then chance.
    // Alive/cooldown validation is explicitly caller-side admission policy.
    if (!context.caster_id) return {false, "no_caster"};
    if (!program_) return {false, "no_skill_program"};
    if (!context.caster_alive) return {false, "caster_down"};
    if (!context.chance_passed) return {false, "chance"};
    if (!std::isfinite(context.cooldown_remaining) || !std::isfinite(context.cooldown_seconds) ||
        context.cooldown_seconds < 0 || context.cooldown_remaining < 0)
        return {false, "invalid_cooldown"};
    if (context.cooldown_remaining > 0) return {false, "cooldown"};
    if (context.skill_level < 1) return {false, "level"};
    for (const auto v : context.origin) if (!std::isfinite(v)) return {false, "position"};
    float norm = 0;
    for (const auto v : context.direction) {
        if (!std::isfinite(v)) return {false, "direction"};
        norm += v * v;
    }
    if (!(norm > 0) || !std::isfinite(norm)) return {false, "direction"};
    if (active_ || has_pending_missiles()) return {false, "busy"};
    context_ = context;
    active_ = true; // native: state/timers BEFORE START, no-handler success
    cooldown_at_start_ = context.cooldown_seconds;
    static_cast<void>(trigger(SkillEventType::start));
    return {true, {}};
}
bool SkillEventRuntime::trigger(SkillEventType type) {
    if (!program_ || (!active_ && type != SkillEventType::die_by_effect)) return false;
    if (skill_event_type_name(type).empty()) return false;
    bool dispatched = false;
    // Original triggerEvent @0xca5950 recursively posts UNITDIE for event 8.
    if (type == SkillEventType::die_by_effect) dispatched = trigger(SkillEventType::unit_die);
    for (std::size_t i = 0; i < program_->events.size(); ++i) {
        if (program_->events[i].type != type) continue;
        start_event(i);
        dispatched = true;
    }
    return dispatched;
}
void SkillEventRuntime::start_event(std::size_t index) {
    const auto& event = program_->events.at(index);
    skill_events_.push_back({event.type, 0, 0, false, false, false, event.layout_path});
    LogicRuntime scene(event.scene, 1);
    // Bounded scene start: SPAWN ON CREATE + t=0 timeline routing only.
    // Nonzero timeline points remain observable, never fired prematurely.
    scene.activate_level();
    for (const auto& point : event.scene.timeline_points) {
        if (point.input_name.empty()) continue;
        if (point.time_percent != 0 || !scene.state(point.target_object_id)) {
            deferred_timeline_points_.push_back({point.timeline_id, point.target_object_id,
                resource_fields::ascii(point.input_name), point.time_percent});
        } else scene.invoke(point.target_object_id, point.input_name);
    }
    for (const auto& request : scene.take_spawn_requests()) {
        if (request.action != SpawnAction::spawn || request.count == 0) continue;
        const auto group = resource_fields::ascii(request.group);
        const auto resource = resource_fields::ascii(request.resource);
        if (group != "Missiles" || resource.empty()) {
            unsupported_spawns_.push_back({group, resource, request.count});
            continue;
        }
        if (next_launch_id_ == std::numeric_limits<std::uint64_t>::max())
            throw std::overflow_error("skill launch IDs exhausted");
        // Anchor/spread/COUNT repetition are still explicit partial boundaries,
        // not evidence of full original skill-projectile placement.
        missile_launches_.push_back({next_launch_id_++, resource, context_.origin,
            context_.direction, context_.caster_id, context_.skill_level,
            request.count, request.count != 1, index});
    }
}
void SkillEventRuntime::drain_launches(const SkillMissileFireSink& sink) {
    if (!sink) return;
    auto pending = take_missile_launches();
    for (const auto& launch : pending) {
        const auto outcome = sink(launch);
        if (!outcome.missile_id) {
            refused_launches_.push_back({launch.launch_id, launch.missile_resource,
                outcome.issue.empty() ? "spawn_refused" : outcome.issue});
        } else if (!live_skill_missiles_.emplace(outcome.missile_id, LiveSkillMissile{launch, {}}).second) {
            refused_launches_.push_back({launch.launch_id, launch.missile_resource, "duplicate_missile_id"});
        }
    }
}
bool SkillEventRuntime::notify_missile_impact(std::uint64_t id, std::uint64_t victim,
    bool blocked, bool expired, const SkillWeaponDamageSink& sink) {
    const auto found = live_skill_missiles_.find(id);
    if (found == live_skill_missiles_.end()) return false;
    if (!victim) {
        if (!found->second.victims.insert(0).second) return false;
        skill_events_.push_back({SkillEventType::missile_die, id, 0, blocked, expired, false, {}});
        static_cast<void>(trigger(SkillEventType::missile_die));
        // A world/expiry terminal can precede splash victims in the same
        // MissileRuntime batch. Ownership ends at retire_missile, not here.
        return true;
    }
    if (!found->second.victims.insert(victim).second) return false;
    const auto launch = found->second.launch;
    const auto& event = program_->events.at(launch.event_index);
    // Original cb8360 posts event 6 BEFORE calling the weapon/effects legs.
    // The compiler refuses reflected/source-MISSILEHIT event programs here.
    skill_events_.push_back({SkillEventType::missile_hit, id, victim, blocked, expired, false, {}});
    static_cast<void>(trigger(SkillEventType::missile_hit));
    const SkillWeaponDamageRequest request{id, victim, launch.caster_id, launch.skill_level,
        event.weapon_damage_pct, event.soak_scale_pct, event.use_dps, blocked, expired};
    // No post can manufacture the death fact: it is obtained from this sink.
    const auto outcome = sink ? sink(request) : SkillWeaponDamageOutcome{};
    skill_events_.push_back({SkillEventType::unit_hit, id, victim, blocked, expired, !outcome.applied, {}});
    static_cast<void>(trigger(SkillEventType::unit_hit));
    if (outcome.killed && outcome.applied) {
        skill_events_.push_back({SkillEventType::unit_die, id, victim, blocked, expired, false, {}});
        static_cast<void>(trigger(SkillEventType::unit_die));
    }
    return true;
}
std::vector<SkillMissileLaunch> SkillEventRuntime::take_missile_launches() {
    std::vector<SkillMissileLaunch> out; out.swap(missile_launches_); return out;
}
std::vector<SkillRefusedLaunch> SkillEventRuntime::take_refused_launches() {
    std::vector<SkillRefusedLaunch> out; out.swap(refused_launches_); return out;
}
std::vector<SkillEventRecord> SkillEventRuntime::take_skill_events() {
    std::vector<SkillEventRecord> out; out.swap(skill_events_); return out;
}
std::vector<UnsupportedSkillSpawn> SkillEventRuntime::take_unsupported_spawns() {
    std::vector<UnsupportedSkillSpawn> out; out.swap(unsupported_spawns_); return out;
}
std::vector<DeferredTimelinePoint> SkillEventRuntime::take_deferred_timeline_points() {
    std::vector<DeferredTimelinePoint> out; out.swap(deferred_timeline_points_); return out;
}
} // namespace torchlight
