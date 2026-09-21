#pragma once

#include "torchlight/skill_event_program.hpp"

#include <array>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace torchlight {
// Bounded original-code dispatch; research/skill-production-dispatch.md.
// Rank inheritance, mana, cooldown ticking and animation ownership belong to
// SkillCatalog/PlayerSession. The runtime never substitutes TRIGGER for START.
[[nodiscard]] std::u16string_view skill_event_type_name(SkillEventType type) noexcept;

struct SkillCastContext {
    std::uint64_t caster_id = 0;
    std::array<float, 3> origin{};
    std::array<float, 3> direction{0.0F, 0.0F, 1.0F};
    bool caster_alive = true;
    bool chance_passed = true; // caller-evaluated; chance formula remains open
    float cooldown_remaining = 0.0F; // admission input, no second ticking clock
    float cooldown_seconds = 0.0F;
    int skill_level = 1;
};
struct SkillStartResult {
    bool started = false;
    std::string issue;
};
struct SkillMissileLaunch {
    std::uint64_t launch_id = 0;
    std::string missile_resource;
    std::array<float, 3> origin{};
    std::array<float, 3> direction{0.0F, 0.0F, 1.0F};
    std::uint64_t caster_id = 0;
    int skill_level = 1;
    std::uint32_t spawner_count = 1;
    bool repeated_count_open = false;
    std::size_t event_index = 0;
};
struct SkillMissileFireOutcome {
    std::uint64_t missile_id = 0;
    std::string issue;
};
using SkillMissileFireSink = std::function<SkillMissileFireOutcome(const SkillMissileLaunch&)>;
struct SkillRefusedLaunch {
    std::uint64_t launch_id = 0;
    std::string missile_resource, issue;
};
struct SkillWeaponDamageRequest {
    std::uint64_t missile_id = 0, victim_id = 0, caster_id = 0;
    int skill_level = 1;
    float weapon_damage_pct = 0.0F, soak_scale_pct = 100.0F;
    bool use_dps = false;
    bool blocked = false, expired = false;
};
struct SkillWeaponDamageOutcome {
    bool applied = false;
    bool killed = false;
};
using SkillWeaponDamageSink =
    std::function<SkillWeaponDamageOutcome(const SkillWeaponDamageRequest&)>;
struct SkillEventRecord {
    SkillEventType type = SkillEventType::start;
    std::uint64_t missile_id = 0, victim_id = 0;
    bool blocked = false, expired = false, damage_application_open = false;
    std::string layout_path; // empty for hook posts with no layout handler
};
struct UnsupportedSkillSpawn {
    std::string group, resource;
    std::uint32_t count = 0;
};
struct DeferredTimelinePoint {
    std::int64_t timeline_id = 0, target_object_id = 0;
    std::string input_name;
    float time_percent = 0.0F;
};

class SkillEventRuntime {
public:
    SkillEventRuntime(std::string skill_name, std::shared_ptr<const SkillEventProgram> program);
    [[nodiscard]] const std::string& skill_name() const noexcept { return skill_name_; }
    [[nodiscard]] bool has_event(SkillEventType type) const noexcept;
    [[nodiscard]] bool active() const noexcept { return active_; }
    [[nodiscard]] float cooldown_at_start() const noexcept { return cooldown_at_start_; }
    [[nodiscard]] bool has_pending_missiles() const noexcept {
        return !missile_launches_.empty() || !live_skill_missiles_.empty();
    }
    bool trigger(SkillEventType type);
    SkillStartResult start_skill(const SkillCastContext& context);
    // Finishing the animation must not discard its last frame's HIT launches.
    void stop() noexcept { active_ = false; }
    void drain_launches(const SkillMissileFireSink& sink);
    // MISSILEHIT precedes weapon application; outcome drives UNITHIT/UNITDIE.
    // Native applyWeaponDamage's additional internal UNITDIE stays open.
    // No caller-supplied death fact before constructing the damage request.
    bool notify_missile_impact(std::uint64_t missile_id, std::uint64_t victim_id,
                               bool blocked, bool expired, const SkillWeaponDamageSink& sink);
    // One collision batch may contain multiple victims for one missile.
    // Retire only after the batch; each victim is delivered at most once.
    void retire_missile(std::uint64_t id) { live_skill_missiles_.erase(id); }
    [[nodiscard]] std::vector<SkillMissileLaunch> take_missile_launches();
    [[nodiscard]] std::vector<SkillRefusedLaunch> take_refused_launches();
    [[nodiscard]] std::vector<SkillEventRecord> take_skill_events();
    [[nodiscard]] std::vector<UnsupportedSkillSpawn> take_unsupported_spawns();
    [[nodiscard]] std::vector<DeferredTimelinePoint> take_deferred_timeline_points();
private:
    void start_event(std::size_t index);
    std::string skill_name_;
    std::shared_ptr<const SkillEventProgram> program_;
    SkillCastContext context_;
    bool active_ = false;
    float cooldown_at_start_ = 0.0F;
    std::uint64_t next_launch_id_ = 1;
    struct LiveSkillMissile {
        SkillMissileLaunch launch;
        std::unordered_set<std::uint64_t> victims;
    };
    std::unordered_map<std::uint64_t, LiveSkillMissile> live_skill_missiles_;
    std::vector<SkillMissileLaunch> missile_launches_;
    std::vector<SkillRefusedLaunch> refused_launches_;
    std::vector<SkillEventRecord> skill_events_;
    std::vector<UnsupportedSkillSpawn> unsupported_spawns_;
    std::vector<DeferredTimelinePoint> deferred_timeline_points_;
};
} // namespace torchlight
