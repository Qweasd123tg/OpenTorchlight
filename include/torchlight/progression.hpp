#pragma once
#include "torchlight/stat_graph.hpp"
#include "torchlight/unit_definition.hpp"
#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

namespace torchlight {
// Resource lookup is deliberately bounded; absent graphs stay unknown.
[[nodiscard]] std::optional<StatGraph> find_named_stat_graph(const PakArchive&, std::string_view name);
[[nodiscard]] std::int32_t checked_reward_integer(float value, bool round_up);
// Exact float operation order from CItemGold::unitInit @0x8cad46.
[[nodiscard]] std::int32_t evaluated_world_gold(float graph_value, float percent);
// Exact float operation order from CCharacter::setLevel @0x83ecea and
// CCharacter::makeChampion @0x85191b: trunc((EXPERIENCE_MONSTER(level)/100) * g).
// The unit data XP field is only a nonzero gate in the original.
[[nodiscard]] std::int32_t original_monster_experience(float graph_value);
[[nodiscard]] std::int32_t experience_with_bonus(std::int32_t amount, float percent);

struct LevelProgressionRule {
    std::int32_t gate = 0, stat_points = 0, skill_points = 0, maximum_health = 1;
    std::optional<std::int32_t> base_mana;
};
class ProgressionRules {
public:
    explicit ProgressionRules(std::vector<LevelProgressionRule> levels);
    [[nodiscard]] std::int32_t maximum_level() const noexcept;
    [[nodiscard]] const LevelProgressionRule& at(std::int32_t level) const;
    [[nodiscard]] std::int32_t gate(std::int32_t level) const;
private:
    std::vector<LevelProgressionRule> levels_;
};
[[nodiscard]] std::shared_ptr<const ProgressionRules> load_progression_rules(
    const PakArchive&, const UnitDefinition&);
struct ProgressionState {
    std::int32_t level = 1, experience = 0, stat_points = 0, skill_points = 0;
    std::array<std::int32_t, 4> allocated{}; // STR, DEX, MAGIC, DEF
};
void validate_progression(const ProgressionState&);
void validate_progression(const ProgressionState&, const ProgressionRules&);
// Stages all changes, including overflow checks, before replacing state.
[[nodiscard]] std::uint32_t advance_progression(ProgressionState&, const ProgressionRules&,
                                               std::int32_t reward, float bonus_percent = 0);
} // namespace torchlight
