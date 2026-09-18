#include "torchlight/skill_event_runtime.hpp"

#include <string>

namespace torchlight {
namespace {

std::string to_ascii(std::u16string_view text) {
    std::string out;
    out.reserve(text.size());
    for (const char16_t c : text) out.push_back(c <= 0x7F ? static_cast<char>(c) : '?');
    return out;
}

} // namespace

std::u16string_view skill_event_type_name(SkillEventType type) noexcept {
    // gSKILL_EVENT_TYPE_NAMES order, research/skill-effect-dispatch.md §3.
    static constexpr const char16_t* kNames[11] = {
        u"EVENT_START", u"EVENT_END", u"EVENT_TRIGGER", u"EVENT_TRIGGER_TWO",
        u"EVENT_UNITHIT", u"EVENT_UNITDIE", u"EVENT_MISSILEHIT",
        u"EVENT_MISSILEDIE", u"EVENT_DIEBYEFFECT", u"EVENT_CASTERDIE",
        u"EVENT_UNIT_CREATE"};
    const auto index = static_cast<int>(type);
    if (index < 0 || index > 10) return {};
    return kNames[index];
}

SkillEventRuntime::SkillEventRuntime(std::string skill_name, LayoutManifest skill_scene,
                                     std::uint32_t random_seed)
    : skill_name_(std::move(skill_name)),
      skill_scene_(std::move(skill_scene)),
      scene_(skill_scene_, random_seed) {}

bool SkillEventRuntime::has_event(SkillEventType type) const noexcept {
    if (skill_scene_.objects.empty()) return false;
    switch (type) {
        case SkillEventType::start:
            return true;
        case SkillEventType::missile_hit:
        case SkillEventType::missile_die:
            return missile_path_seen_;
        default:
            return false;
    }
}

bool SkillEventRuntime::trigger(SkillEventType type) {
    if (!has_event(type)) return false;
    if (type != SkillEventType::start) return false;
    // startEvent/CLayout::start role for the ported slice: the scene spawner
    // setup. LogicRuntime::activate_level invokes Spawn Units on SPAWN ON
    // CREATE spawners; timeline points exactly at 0.0 fire through the same
    // scene (the playhead rests at 0 at layout start). Later points need a
    // timeline clock (open) and are retained; timeline-object routing beyond
    // spawners stays observable through the scene (no invented handlers).
    skill_events_.push_back(SkillEventRecord{type, 0, 0, false, false, false});
    scene_.activate_level();
    for (const auto& point : skill_scene_.timeline_points) {
        if (point.time_percent != 0.0F || point.input_name.empty()) {
            if (!point.input_name.empty())
                deferred_timeline_points_.push_back({point.timeline_id, point.target_object_id,
                                                     to_ascii(point.input_name),
                                                     point.time_percent});
            continue;
        }
        if (scene_.state(point.target_object_id) == nullptr) {
            deferred_timeline_points_.push_back({point.timeline_id, point.target_object_id,
                                                 to_ascii(point.input_name), point.time_percent});
            continue;
        }
        scene_.invoke(point.target_object_id, point.input_name);
    }
    collect_spawner_scene();
    return true;
}

SkillStartResult SkillEventRuntime::start_skill(const SkillCastContext& context) {
    // Guard order mirrors startSkill @0xca9150: scene usability (the +0x90
    // analog: no scene, no execution), caster presence, caller-side gates
    // (alive/chance/cooldown), then triggerEvent(START).
    if (skill_scene_.objects.empty()) return {false, "no_skill_scene"};
    if (context.caster_id == 0) return {false, "no_caster"};
    if (!context.caster_alive) return {false, "caster_down"};
    if (!context.chance_passed) return {false, "chance"};
    if (cooldown_remaining_ > 0.0F || context.cooldown_remaining > 0.0F)
        return {false, "cooldown"};
    caster_id_ = context.caster_id;
    pending_origin_ = context.origin;
    pending_direction_ = context.direction;
    if (!trigger(SkillEventType::start)) return {false, "no_skill_scene"};
    cooldown_remaining_ = context.cooldown_seconds > 0.0F ? context.cooldown_seconds : 0.0F;
    return {true, {}};
}

void SkillEventRuntime::advance(float seconds) noexcept {
    if (seconds <= 0.0F || cooldown_remaining_ <= 0.0F) return;
    cooldown_remaining_ -= seconds;
    if (cooldown_remaining_ < 0.0F) cooldown_remaining_ = 0.0F;
}

void SkillEventRuntime::collect_spawner_scene() {
    // spawnUnitByIndex dispatch role: only the Missiles branch is ported
    // (createAndFireMissile path); sibling spawn-type branches are retained
    // as unsupported records. COUNT>1 multi-launch semantics stay open.
    for (const auto& request : scene_.take_spawn_requests()) {
        if (request.action != SpawnAction::spawn) continue;
        const std::string group = to_ascii(request.group);
        const std::string resource = to_ascii(request.resource);
        if (group != "Missiles" || resource.empty()) {
            unsupported_spawns_.push_back({group, resource, request.count});
            continue;
        }
        SkillMissileLaunch launch;
        launch.launch_id = next_launch_id_++;
        launch.missile_resource = resource;
        // Launch anchor: the caster position/direction carried by the cast.
        // The original anchor math (WEAPON_SCALE/0.8/probe offsets) belongs
        // to the equipment path and stays open for the skill path.
        launch.origin = pending_origin_;
        launch.direction = pending_direction_;
        launch.caster_id = caster_id_;
        launch.spawner_count = request.count;
        launch.repeated_count_open = request.count != 1;
        missile_launches_.push_back(launch);
        missile_path_seen_ = true;
    }
}

void SkillEventRuntime::drain_launches(const SkillMissileFireSink& sink) {
    if (!sink) return;
    for (auto& launch : missile_launches_) {
        auto outcome = sink(launch);
        if (outcome.missile_id != 0) {
            live_skill_missiles_.emplace(outcome.missile_id, launch.launch_id);
        } else {
            refused_launches_.push_back(
                {launch.launch_id, launch.missile_resource,
                 outcome.issue.empty() ? std::string("spawn_refused") : outcome.issue});
        }
    }
    missile_launches_.clear();
}

bool SkillEventRuntime::notify_missile_impact(std::uint64_t missile_id, std::uint64_t victim_id,
                                              bool blocked, bool expired) {
    // missileApplyingEffects/missileDieing poster role: only our own
    // missiles dispatch; unknown ids are ignored, never forged into events.
    if (live_skill_missiles_.erase(missile_id) == 0) return false;
    SkillEventRecord record;
    if (victim_id != 0) {
        record = {SkillEventType::missile_hit, missile_id, victim_id, blocked, expired, true};
    } else {
        record = {SkillEventType::missile_die, missile_id, 0, blocked, expired, false};
    }
    skill_events_.push_back(record);
    return true;
}

std::vector<SkillMissileLaunch> SkillEventRuntime::take_missile_launches() {
    std::vector<SkillMissileLaunch> out;
    out.swap(missile_launches_);
    return out;
}

std::vector<SkillRefusedLaunch> SkillEventRuntime::take_refused_launches() {
    std::vector<SkillRefusedLaunch> out;
    out.swap(refused_launches_);
    return out;
}

std::vector<SkillEventRecord> SkillEventRuntime::take_skill_events() {
    std::vector<SkillEventRecord> out;
    out.swap(skill_events_);
    return out;
}

std::vector<UnsupportedSkillSpawn> SkillEventRuntime::take_unsupported_spawns() {
    std::vector<UnsupportedSkillSpawn> out;
    out.swap(unsupported_spawns_);
    return out;
}

std::vector<DeferredTimelinePoint> SkillEventRuntime::take_deferred_timeline_points() {
    std::vector<DeferredTimelinePoint> out;
    out.swap(deferred_timeline_points_);
    return out;
}

} // namespace torchlight
