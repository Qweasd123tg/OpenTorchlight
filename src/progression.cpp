#include "torchlight/progression.hpp"
#include "torchlight/recovered/gameplay_numeric.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <string>

namespace torchlight {
namespace {
std::string lower(std::string_view name) {
    std::string result(name);
    for (auto& c : result) {
        if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
        if (c == '\\') c = '/';
    }
    return result;
}
std::string graph_name(const UnitDefinition& d, const char16_t* key, const char* fallback) {
    const auto* property = d.find_property(key);
    if (!property) return fallback;
    if (property->type != AdmValueType::string && property->type != AdmValueType::translation &&
        property->type != AdmValueType::note) throw std::invalid_argument("progression graph name is not text");
    std::string result;
    for (auto c : std::get<std::u16string>(property->value)) {
        if (c > 127) throw std::invalid_argument("non-ASCII progression graph name");
        result.push_back(static_cast<char>(c));
    }
    return result;
}
std::int32_t sum_points(std::int32_t a, std::int32_t b) {
    const auto result = static_cast<std::int64_t>(a) + b;
    if (result < 0 || result > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("progression point total outside int32");
    return static_cast<std::int32_t>(result);
}
}
std::optional<StatGraph> find_named_stat_graph(const PakArchive& archive, std::string_view name) {
    if (name.empty()) return std::nullopt;
    const auto wanted = lower(name) + ".dat.adm";
    const PakArchive::Entry* found = nullptr;
    for (const auto& entry : archive.entries()) {
        const auto path = lower(entry.name);
        if (path.compare(0, 13, "media/graphs/") != 0) continue;
        const auto slash = path.find_last_of('/');
        if (path.substr(slash + 1) != wanted) continue;
        if (found) throw std::invalid_argument("ambiguous named stat graph: " + std::string(name));
        found = &entry;
    }
    if (!found) return std::nullopt;
    return StatGraph(archive, found->name);
}
std::int32_t checked_reward_integer(float value, bool round_up) {
    value = round_up ? std::ceil(value) : std::trunc(value);
    if (!std::isfinite(value) || value < 0 ||
        static_cast<double>(value) > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("reward graph value outside nonnegative int32");
    return static_cast<std::int32_t>(value);
}
std::int32_t evaluated_world_gold(float value, float percent) {
    if (!std::isfinite(value) || !std::isfinite(percent) || value < 0 || percent < 0)
        throw std::invalid_argument("invalid gold inputs");
    return checked_reward_integer(recovered::world_gold_amount(value, percent), true);
}
std::int32_t original_monster_experience(float graph_value) {
    if (!std::isfinite(graph_value) || graph_value < 0)
        throw std::invalid_argument("invalid monster experience graph value");
    return checked_reward_integer(recovered::monster_experience_amount(graph_value), false);
}
std::int32_t experience_with_bonus(std::int32_t amount, float percent) {
    if (!std::isfinite(percent)) throw std::invalid_argument("non-finite XP bonus");
    const auto bonus = std::ceil(static_cast<float>(amount) * (percent / 100.0F));
    if (!std::isfinite(bonus) || static_cast<double>(bonus) < std::numeric_limits<std::int32_t>::min() ||
        static_cast<double>(bonus) > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("XP bonus outside int32");
    const auto total = static_cast<std::int64_t>(amount) + static_cast<std::int32_t>(bonus);
    return static_cast<std::int32_t>(std::clamp<std::int64_t>(total,
        std::numeric_limits<std::int32_t>::min(), std::numeric_limits<std::int32_t>::max()));
}
ProgressionRules::ProgressionRules(std::vector<LevelProgressionRule> levels) : levels_(std::move(levels)) {
    if (levels_.empty() || levels_.size() > 100000)
        throw std::invalid_argument("invalid progression level count");
    std::int32_t previous = -1;
    for (const auto& rule : levels_) {
        if (rule.gate <= previous || rule.stat_points < 0 || rule.skill_points < 0 ||
            rule.maximum_health < 1 || (rule.base_mana && *rule.base_mana < 0))
            throw std::invalid_argument("invalid progression rule or non-increasing XP gates");
        previous = rule.gate;
    }
}
std::int32_t ProgressionRules::maximum_level() const noexcept {
    return static_cast<std::int32_t>(levels_.size());
}
const LevelProgressionRule& ProgressionRules::at(std::int32_t level) const {
    if (level < 1 || level > maximum_level()) throw std::invalid_argument("progression level outside rules");
    return levels_[static_cast<std::size_t>(level - 1)];
}
std::int32_t ProgressionRules::gate(std::int32_t level) const {
    if (level == 0) return 0;
    return at(std::min(level, maximum_level())).gate;
}
std::shared_ptr<const ProgressionRules> load_progression_rules(const PakArchive& archive,
                                                              const UnitDefinition& definition) {
    auto gates = find_named_stat_graph(archive, "EXPERIENCEGATE");
    if (!gates) return {};
    if (gates->size() > 100000) throw std::invalid_argument("too many XP gates");
    auto hp = find_named_stat_graph(archive, graph_name(definition, u"HEALTH_GRAPH", "HEALTH_PLAYER_DESTROYER"));
    if (!hp) return {}; // no fabricated level-up HP
    auto mana = find_named_stat_graph(archive, graph_name(definition, u"MANA_GRAPH", "MANA_PLAYER_DESTROYER"));
    auto stats = find_named_stat_graph(archive, graph_name(definition, u"STAT_POINTS_PER_LEVEL", "STAT_POINTS_PER_LEVEL"));
    auto skills = find_named_stat_graph(archive, graph_name(definition, u"SKILL_POINTS_PER_LEVEL", "SKILL_POINTS_PER_LEVEL"));
    std::vector<LevelProgressionRule> levels;
    levels.reserve(gates->size());
    for (std::size_t i = 1; i <= gates->size(); ++i) {
        const auto x = static_cast<float>(i);
        LevelProgressionRule rule;
        rule.gate = checked_reward_integer(gates->value(x), false);
        rule.maximum_health = checked_reward_integer(hp->value(x), true);
        if (mana) rule.base_mana = checked_reward_integer(mana->value(x), true);
        if (stats) rule.stat_points = checked_reward_integer(stats->value(x), true);
        if (skills) rule.skill_points = checked_reward_integer(skills->value(x), true);
        levels.push_back(rule);
    }
    return std::make_shared<const ProgressionRules>(std::move(levels));
}
void validate_progression(const ProgressionState& s) {
    if (s.level < 1 || s.level > 100000 || s.experience < 0 || s.stat_points < 0 || s.skill_points < 0)
        throw std::invalid_argument("invalid progression state");
    for (auto v : s.allocated) if (v < 0 || v > 1000000)
        throw std::invalid_argument("allocated attribute outside supported range");
}
void validate_progression(const ProgressionState& s, const ProgressionRules& rules, std::int32_t spent_skill_points) {
    if (spent_skill_points < 0) throw std::invalid_argument("negative invested skill points");
    validate_progression(s);
    if (s.level > rules.maximum_level() || s.experience > rules.gate(rules.maximum_level()) ||
        (s.level < rules.maximum_level() && s.experience >= rules.gate(s.level)))
        throw std::invalid_argument("saved level/XP disagrees with progression rules");
    std::int64_t stats = 0, skills = 0, allocated = 0;
    for (std::int32_t i = 2; i <= s.level; ++i) {
        stats += rules.at(i).stat_points; skills += rules.at(i).skill_points;
    }
    for (auto v : s.allocated) allocated += v;
    if (stats != static_cast<std::int64_t>(s.stat_points) + allocated || skills != static_cast<std::int64_t>(s.skill_points) + spent_skill_points)
        throw std::invalid_argument("saved progression points disagree with level history");
}
std::uint32_t advance_progression(ProgressionState& state, const ProgressionRules& rules,
                                  std::int32_t reward, float bonus_percent, std::int32_t spent_skill_points) {
    validate_progression(state, rules, spent_skill_points);
    auto next = state;
    const auto total = static_cast<std::int64_t>(next.experience) + experience_with_bonus(reward, bonus_percent);
    next.experience = static_cast<std::int32_t>(std::clamp<std::int64_t>(total, 0,
        std::numeric_limits<std::int32_t>::max()));
    while (next.level < rules.maximum_level() && next.experience >= rules.gate(next.level)) {
        ++next.level;
        next.stat_points = sum_points(next.stat_points, rules.at(next.level).stat_points);
        next.skill_points = sum_points(next.skill_points, rules.at(next.level).skill_points);
    }
    if (next.level == rules.maximum_level()) next.experience = std::min(next.experience, rules.gate(next.level));
    const auto count = static_cast<std::uint32_t>(next.level - state.level);
    validate_progression(next, rules, spent_skill_points);
    state = next;
    return count;
}
} // namespace torchlight
