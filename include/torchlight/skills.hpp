#pragma once
#include "torchlight/attack_action.hpp"
#include "torchlight/unit_definition.hpp"
#include <memory>
#include <unordered_map>
namespace torchlight {
struct SkillEventProgram;
struct SkillGrant {
    std::u16string name;
    std::int32_t rank = 0, level_required = 0;
};
[[nodiscard]] std::vector<SkillGrant> load_class_skills(const UnitDefinition&);
struct TimedSkillEffect {
    std::u16string name, unit_theme;
    std::uint16_t type = 0;
    std::uint8_t damage_type = 7;
    float value = 0, duration = 0, remaining = 0;
    bool exclusive = false;
    std::int64_t source_skill = 0;
};
struct SkillProgress {
    std::u16string name;
    std::int32_t invested = 0;
    float cooldown = 0; // simulation seconds, canonicalized at zero when ready
};
struct SkillCheckpoint {
    std::vector<SkillProgress> skills;
    std::vector<TimedSkillEffect> effects;
};
struct SelfBuffProgram {
    std::vector<TimedSkillEffect> effects;
    // UNIT THEME and original animation particle/sound keys are preserved, but
    // the port's particle/audio renderer is not declared complete.
    bool visual_effects_pending = false;
};
struct SkillRank {
    std::int32_t level_required = 0, mana_cost = 0;
    float cooldown = 0, monster_cooldown = 0, speed = 1;
    AdmGroup resource;
    std::optional<SelfBuffProgram> self_buff;
    std::shared_ptr<const SkillEventProgram> event_program;
    std::string unavailable_reason;
};
struct SkillDefinition {
    std::u16string name, display_name;
    std::string source_path, animation;
    std::int64_t guid = 0;
    std::int32_t maximum_investment = 0;
    std::vector<SkillRank> ranks;
    [[nodiscard]] const SkillRank* rank(std::int32_t n) const noexcept;
};
class SkillCatalog {
public:
    explicit SkillCatalog(const PakArchive&);
    [[nodiscard]] const SkillDefinition* find(std::u16string_view) const;
    [[nodiscard]] const std::vector<SkillDefinition>& definitions() const noexcept { return definitions_; }
private:
    std::vector<SkillDefinition> definitions_;
    std::unordered_map<std::u16string,std::size_t> by_name_;
};
[[nodiscard]] float original_cast_speed(float cast_percent, float slow_resistance, float skill_speed);
void validate_skill_checkpoint(const SkillCheckpoint&);
void add_timed_skill_effects(std::vector<TimedSkillEffect>&, const std::vector<TimedSkillEffect>&);
[[nodiscard]] AttackEffects skill_attack_effects(const std::vector<TimedSkillEffect>&);
// Returns true when the evaluated contributions changed. Pure simulation time.
[[nodiscard]] bool advance_timed_skill_effects(std::vector<TimedSkillEffect>&, float seconds);
// A finite, non-looping cast with the same immutable clip for pose and HIT.
// Portable event ownership guards prevent forged/replayed HIT consumption.
class SkillCast {
public:
    void start(std::uint64_t execution, std::u16string name, SelfBuffProgram, AttackClip, float speed);
    void advance(float seconds);
    [[nodiscard]] bool consume(const AnimationEventOccurrence&);
    void finish_frame() noexcept;
    void cancel() noexcept;
    [[nodiscard]] bool active() const noexcept { return active_; }
    [[nodiscard]] const AttackClip& clip() const noexcept { return clip_; }
    [[nodiscard]] const AnimationEventPlayback& playback() const noexcept { return playback_; }
    [[nodiscard]] const SelfBuffProgram& program() const noexcept { return program_; }
    [[nodiscard]] const std::u16string& name() const noexcept { return name_; }
private:
    AttackClip clip_;
    AnimationEventPlayback playback_;
    SelfBuffProgram program_;
    std::u16string name_;
    std::vector<bool> consumed_;
    bool active_ = false;
};
enum class SkillUse { started, learned, unknown, unsupported, unlearned, maximum_rank,
                      level_required, no_points, no_mana, dead, busy, cooldown, missing_animation };
[[nodiscard]] const char* skill_use_message(SkillUse) noexcept;
} // namespace torchlight
