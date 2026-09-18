#pragma once

#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/pak_archive.hpp"

#include <array>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace torchlight {
// original-code: skill execution entry + event dispatch + hit appliers
// (CSkill::startSkill @0xca9150, CSkill::triggerEvent @0xca5950,
// CSkillEvent::startEvent @0xcc4300, CUnitSpawner missile branch in
// spawnUnitByIndex @0xa167a0, createAndFireMissile @0xa0adc0,
// missileApplyingEffects @0xcb8360, canEffectPosObject @0xcb7240,
// applyWeaponDamage @0xcb7b70, applyEffects @0xcb7850,
// applyAffixesAndEffects @0xcac040, invokeHitSkills @0xcb7290,
// missileDieing @0xcb7670; ELF SHA-256
// 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b;
// analysis research/skill-effect-dispatch.md).
//
// EventRuntime: common dispatch + the supported missile-spawn path +
// MISSILEHIT/MISSILEDIE callbacks. Unsupported event types, non-missile
// spawn groups, skill damage application (applyWeaponDamage/applyEffects
// inside the hit hook), chance evaluation, cooldown values and animation
// assignment are explicit boundaries, never invented behavior. Skills never
// touch the missile runtime: launches leave through the fire sink (the
// application-owned createAndFireMissile equivalent) and impacts re-enter
// through notify_missile_impact (the missile-hook equivalent).
enum class SkillEventType : int {
    start = 0,
    end = 1,
    trigger = 2,
    trigger_two = 3,
    unit_hit = 4,
    unit_die = 5,
    missile_hit = 6,
    missile_die = 7,
    die_by_effect = 8,
    caster_die = 9,
    unit_create = 10,
};

// gSKILL_EVENT_TYPE_NAMES order (11 names); unknown values yield empty view.
[[nodiscard]] std::u16string_view skill_event_type_name(SkillEventType type) noexcept;

// One LEVEL ladder rung from a skill .DAT (EVENT_TRIGGER scalars).
// effect_entries counts LEVEL subgroups outside EVENT_START/EVENT_TRIGGER:
// the applyEffects leg input. present=false when the rung has no readable
// EVENT_TRIGGER (never defaulted scalars).
struct SkillTriggerLevel {
    float weapon_damage_pct = 0.0F;
    float soak_scale_pct = 0.0F;
    std::uint32_t effect_entries = 0;
    bool present = false;
};

// Loads LEVEL1..N rungs from <path> (a skill .DAT.adm). Missing file or an
// unreadable document -> nullopt (caller keeps the refusal, never defaults).
[[nodiscard]] std::optional<std::vector<SkillTriggerLevel>> load_skill_trigger_levels(
    const PakArchive& pak, std::string_view dat_path);

// Caller-owned cast inputs. Chance evaluation and cooldown values live in
// the caller until skill chance/cooldown data is ported: the runtime gates
// on the supplied outcome, it never rolls or reads skill data itself.
struct SkillCastContext {
    std::uint64_t caster_id = 0; // 0: no caster (startSkill null guard)
    std::array<float, 3> origin = {0.0F, 0.0F, 0.0F};
    std::array<float, 3> direction = {0.0F, 0.0F, 1.0F};
    bool caster_alive = true; // caller-side castSkill gate, not startSkill body
    bool chance_passed = true; // caller-side rollSkillChance outcome (open)
    float cooldown_remaining = 0.0F; // >0 refuses (getCoolDown analog)
    float cooldown_seconds = 0.0F; // armed on a started cast
    int skill_level = 1; // 1-based LEVEL ladder rung; gated when rungs loaded
};

struct SkillStartResult {
    bool started = false;
    // Empty on success, otherwise one of: no_skill_scene, no_caster,
    // caster_down, chance, cooldown, level.
    std::string issue;
};

// One spawner object with GROUP=Missiles (spawnUnitByIndex Missiles branch).
// COUNT rides along for the record; repeated multi-launch semantics stay
// open (repeated_count_open) and exactly one launch is produced.
struct SkillMissileLaunch {
    std::uint64_t launch_id = 0;
    std::string missile_resource; // ASCII form of the spawner RESOURCE
    std::array<float, 3> origin = {0.0F, 0.0F, 0.0F};
    std::array<float, 3> direction = {0.0F, 0.0F, 1.0F};
    std::uint64_t caster_id = 0;
    int skill_level = 1; // ladder rung bound at cast (setSkillOwner role)
    std::uint32_t spawner_count = 1;
    bool repeated_count_open = false;
};

// Application-owned createAndFireMissile equivalent. Returns the live
// missile id, or missile_id 0 with an issue (template_missing when the
// template cannot load, spawn_refused when the runtime refuses it).
struct SkillMissileFireOutcome {
    std::uint64_t missile_id = 0;
    std::string issue;
};
using SkillMissileFireSink = std::function<SkillMissileFireOutcome(const SkillMissileLaunch&)>;

struct SkillRefusedLaunch {
    std::uint64_t launch_id = 0;
    std::string missile_resource;
    std::string issue; // template_missing | spawn_refused
};

// Weapon leg output (applyWeaponDamage role): the resource scalars for the
// future damage backend. The NUMBER is still open (performAttack/rollAttack
// chain unported): this request is its exact input contract, never a roll.
struct SkillWeaponDamageRequest {
    std::uint64_t missile_id = 0;
    std::uint64_t victim_id = 0;
    std::uint64_t caster_id = 0;
    int skill_level = 1;
    float weapon_damage_pct = 0.0F;
    float soak_scale_pct = 0.0F;
    bool scalars_present = false;
};

// Effects leg with entries to apply (applyEffects role): no leaf backend is
// ported yet, so the leg is retained open with its input count.
struct OpenEffectLeg {
    std::uint64_t missile_id = 0;
    std::uint32_t entry_count = 0;
};

// Missile-hook equivalent posters (missileApplyingEffects/missileDieing):
// victim hits post MISSILEHIT, victimless ends post MISSILEDIE.
// damage_application_open marks the unported applyWeaponDamage/applyEffects
// work inside the hit hook: the event is real, the damage has no sink yet.
struct SkillEventRecord {
    SkillEventType type = SkillEventType::start;
    std::uint64_t missile_id = 0;
    std::uint64_t victim_id = 0;
    bool blocked = false;
    bool expired = false;
    bool damage_application_open = false;
};

// Spawner requests outside the Missiles branch (spawnUnitByIndex sibling
// branches): retained, never acted on.
struct UnsupportedSkillSpawn {
    std::string group;
    std::string resource;
    std::uint32_t count = 0;
};

// Timeline points that need a timeline clock (time_percent != 0) or address
// an absent object: parsed, never fired. Firing them without playhead
// playback would invent timing.
struct DeferredTimelinePoint {
    std::int64_t timeline_id = 0;
    std::int64_t target_object_id = 0;
    std::string input_name;
    float time_percent = 0.0F;
};

class SkillEventRuntime {
public:
    SkillEventRuntime(std::string skill_name, LayoutManifest skill_scene,
                      std::vector<SkillTriggerLevel> trigger_levels = {},
                      std::uint32_t random_seed = 1);

    [[nodiscard]] const std::string& skill_name() const noexcept { return skill_name_; }
    // Supported dispatch set for the ported slice: start always (scene
    // present), missile_hit/missile_die once a skill missile was fired.
    // Every other type returns false: explicit boundary, not a silent pass.
    [[nodiscard]] bool has_event(SkillEventType type) const noexcept;
    // Common dispatcher (triggerEvent role). Returns false for unsupported
    // types. start runs the scene spawner setup (startEvent/CLayout::start
    // role for the missile path): SPAWN ON CREATE spawners plus timeline
    // points exactly at 0.0 (the playhead rests there at layout start, so
    // they fire without inventing playback timing); missile_* types only
    // enter through notify_missile_impact, any other direct trigger returns
    // false.
    bool trigger(SkillEventType type);
    // Execution entry (executeSkill -> startSkill role): guards in original
    // order, then trigger(start). On success arms the cooldown clock.
    SkillStartResult start_skill(const SkillCastContext& context);
    void advance(float seconds) noexcept;
    // Fires pending launches through the application sink (createAndFireMissile
    // role); refusals ride take_refused_launches, never guessed missiles.
    void drain_launches(const SkillMissileFireSink& sink);
    // Returns false for unknown missile ids (not one of ours): nothing posted.
    // victim_died is an application-observed fact (the runtime owns no HP):
    // it selects the UNITDIE poster from invokeHitSkills, it never evaluates.
    bool notify_missile_impact(std::uint64_t missile_id, std::uint64_t victim_id,
                               bool blocked, bool expired, bool victim_died = false);

    [[nodiscard]] std::vector<SkillMissileLaunch> take_missile_launches();
    [[nodiscard]] std::vector<SkillRefusedLaunch> take_refused_launches();
    [[nodiscard]] std::vector<SkillEventRecord> take_skill_events();
    [[nodiscard]] std::vector<UnsupportedSkillSpawn> take_unsupported_spawns();
    [[nodiscard]] std::vector<SkillWeaponDamageRequest> take_weapon_damage_requests();
    [[nodiscard]] std::vector<OpenEffectLeg> take_open_effect_legs();
    [[nodiscard]] std::vector<DeferredTimelinePoint> take_deferred_timeline_points();

private:
    void collect_spawner_scene();

    std::string skill_name_;
    LayoutManifest skill_scene_;
    std::vector<SkillTriggerLevel> trigger_levels_;
    LogicRuntime scene_;
    std::uint64_t next_launch_id_ = 1;
    float cooldown_remaining_ = 0.0F;
    std::uint64_t caster_id_ = 0;
    int pending_level_ = 1;
    struct LiveSkillMissile {
        std::uint64_t launch_id = 0;
        int skill_level = 1;
        std::uint64_t caster_id = 0;
    };
    std::array<float, 3> pending_origin_ = {0.0F, 0.0F, 0.0F};
    std::array<float, 3> pending_direction_ = {0.0F, 0.0F, 1.0F};
    bool missile_path_seen_ = false;
    std::unordered_map<std::uint64_t, LiveSkillMissile> live_skill_missiles_; // by missile id
    std::vector<SkillMissileLaunch> missile_launches_;
    std::vector<SkillRefusedLaunch> refused_launches_;
    std::vector<SkillEventRecord> skill_events_;
    std::vector<SkillWeaponDamageRequest> weapon_damage_requests_;
    std::vector<OpenEffectLeg> open_effect_legs_;
    std::vector<UnsupportedSkillSpawn> unsupported_spawns_;
    std::vector<DeferredTimelinePoint> deferred_timeline_points_;
};

} // namespace torchlight
