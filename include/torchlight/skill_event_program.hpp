#pragma once

#include "torchlight/level_scene.hpp"
#include <string>
#include <vector>

namespace torchlight {
enum class SkillEventType : int {
    start = 0, end = 1, trigger = 2, trigger_two = 3, unit_hit = 4,
    unit_die = 5, missile_hit = 6, missile_die = 7, die_by_effect = 8,
    caster_die = 9, unit_create = 10,
};

struct SkillEventDefinition {
    SkillEventType type = SkillEventType::start;
    std::string layout_path;
    LayoutManifest scene;
    // original-code: CSkillEvent constructor @0xcc71d0 initializes these
    // before optional DAT reads; research/skill-effect-dispatch.md.
    float weapon_damage_pct = 0, soak_scale_pct = 100;
    bool use_dps = false;
    bool attaches = false;
};

struct SkillEventProgram {
    std::vector<SkillEventDefinition> events;
    bool use_weapon_animation = false;
    float range = 0;
    float find_target_angle = 0;
    bool visual_effects_pending = false;
};

// Input is SkillCatalog's evaluated rank, with LEVEL inheritance already
// resolved. Refuses unsupported gameplay fields rather than executing a
// unrelated skill. The admitted projectile subset is still partial: COUNT,
// spread/anchors/target search/homing and scene rendering remain open.
[[nodiscard]] SkillEventProgram compile_skill_event_program(
    const AdmGroup& evaluated_rank, const LevelSceneLoader& loader);
} // namespace torchlight
