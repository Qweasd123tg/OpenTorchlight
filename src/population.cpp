#include "torchlight/population.hpp"
#include "torchlight/entity_world.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <stdexcept>

namespace torchlight {
namespace {
float distance_squared(const std::array<float, 3>& a, const std::array<float, 3>& b) {
    const float x = a[0] - b[0], z = a[2] - b[2];
    return x * x + z * z;
}
bool none(std::u16string_view name) {
    return name.empty() || (name.size() == 4 && (name[0] == u'N' || name[0] == u'n') &&
        (name[1] == u'O' || name[1] == u'o') && (name[2] == u'N' || name[2] == u'n') &&
        (name[3] == u'E' || name[3] == u'e'));
}
}
std::uint32_t population_count(float cmin, float cmax, float dmin, float dmax,
                               std::uint32_t nodes, TorchlightRandom& rng) {
    for (const float v : {cmin, cmax, dmin, dmax})
        if (!std::isfinite(v) || v < 0 || v > 50000)
            throw std::invalid_argument("population count outside portable resource bounds");
    if (cmin > 0 || cmax > 0)
        return static_cast<std::uint32_t>(rng.integer_between(
            static_cast<std::int32_t>(std::min(cmin, cmax)),
            static_cast<std::int32_t>(std::max(cmin, cmax))));
    if (dmin <= 0 || dmax <= 0) return 0;
    const float area = static_cast<float>(nodes) / 6.5F;
    const float n = std::ceil(rng.between(area * std::min(dmin, dmax),
                                        area * std::max(dmin, dmax)));
    if (!std::isfinite(n) || n > 50000) throw std::length_error("population exceeds entity budget");
    return static_cast<std::uint32_t>(n);
}
std::vector<std::array<float, 3>> population_candidates(const NavigationGrid& grid,
    const std::array<float, 3>& entry, const std::vector<std::array<float, 3>>& exclusions) {
    for (const auto v : entry) if (!std::isfinite(v)) throw std::invalid_argument("invalid population entry");
    std::vector<std::array<float, 3>> result;
    const auto start = grid.nearest_walkable(entry, 64);
    if (!start) return result;
    const auto width = grid.width(), height = grid.height();
    std::vector<bool> visited(width * height, false);
    std::queue<std::array<std::size_t, 2>> pending;
    pending.push(*start); visited[(*start)[1] * width + (*start)[0]] = true;
    while (!pending.empty()) {
        const auto p = pending.front(); pending.pop();
        const auto position = grid.cell_center(p[0], p[1]);
        bool safe = distance_squared(position, entry) >= 25.0F;
        for (const auto& exclusion : exclusions)
            if (distance_squared(position, exclusion) < 9.0F) { safe = false; break; }
        if (safe) result.push_back(position);
        constexpr std::array<std::array<int, 2>, 4> offsets{{{1,0},{-1,0},{0,1},{0,-1}}};
        for (const auto& offset : offsets) {
            const auto x = static_cast<std::int64_t>(p[0]) + offset[0];
            const auto z = static_cast<std::int64_t>(p[1]) + offset[1];
            if (x < 0 || z < 0 || x >= static_cast<std::int64_t>(width) || z >= static_cast<std::int64_t>(height)) continue;
            const auto ux = static_cast<std::size_t>(x), uz = static_cast<std::size_t>(z);
            const auto id = uz * width + ux;
            if (!visited[id] && grid.cell(ux, uz).walkable &&
                std::abs(grid.cell(ux, uz).height - position[1]) <= 1.5F) {
                visited[id] = true; pending.push({ux, uz});
            }
        }
    }
    return result;
}
PopulationReport RuntimeEntityWorld::populate(const PopulationSettings& settings,
    const NavigationGrid& grid, const std::array<float, 3>& entry,
    const std::vector<std::array<float, 3>>& exclusions) {
    PopulationReport report;
    if (population_generated_) { report.already_generated = true; return report; }
    if (std::abs(grid.cell_size() - .4F) > .00001F)
        throw std::invalid_argument("population density requires the 0.4-node grid");
    report.pathable_nodes = grid.walkable_cell_count();
    if (report.pathable_nodes > std::numeric_limits<std::uint32_t>::max())
        throw std::length_error("too many population nodes");
    auto candidates = population_candidates(grid, entry, exclusions);
    report.reachable_nodes = candidates.size();
    // World changes and RNG must commit together. Definition caches may warm on
    // failure, but no entities, ids, current level or random state are changed.
    auto previous_entities = entities_;
    const auto previous_random = random_;
    const auto previous_id = next_entity_id_;
    const auto previous_level = spawn_level_;
    try {
        auto classname = settings.monster_class;
        if (none(classname)) { population_generated_ = true; return report; }
        if (!spawn_classes_->find(classname)) {
            report.missing_resources = 1; population_generated_ = true; return report;
        }
        if (settings.randomized_class) {
            // chooseUnitSpawners chooses ONE nested class, not one per monster.
            const auto& choices = spawn_classes_->find(classname)->entries;
            std::vector<float> weights;
            for (const auto& choice : choices) {
                if (choice.spawn_class.empty()) throw std::runtime_error("randomized population class contains a non-class choice");
                weights.push_back(static_cast<float>(choice.weight < 1 ? 100 : choice.weight));
            }
            if (weights.empty()) throw std::runtime_error("empty randomized population class");
            classname = choices[weighted_index(weights, random_)].spawn_class;
            if (!spawn_classes_->find(classname)) throw std::runtime_error("missing randomized population class");
        }
        report.requested = population_count(settings.minimum_count, settings.maximum_count,
            settings.minimum_density, settings.maximum_density,
            static_cast<std::uint32_t>(report.pathable_nodes), random_);
        if (report.requested + entities_.size() > 50000) throw std::length_error("world population budget exceeded");
        const auto low = settings.minimum_level < 1 ? previous_level : settings.minimum_level;
        const auto high = settings.maximum_level < 1 ? low : settings.maximum_level;
        if (low > 1000 || high > 1000) throw std::invalid_argument("population level outside supported graph bounds");
        // Partial Fisher-Yates: stable, finite, no retries stuck on blocked cells.
        for (std::size_t i = candidates.size(); i > 1; --i) {
            const auto j = static_cast<std::size_t>(random_.integer_between(0, static_cast<std::int32_t>(i - 1)));
            std::swap(candidates[i - 1], candidates[j]);
        }
        std::vector<std::array<float, 3>> occupied;
        for (const auto& entity : entities_) if (entity.alive && entity.combat_targetable) occupied.push_back(entity.position);
        std::size_t candidate_index = 0, accounted = 0;
        while (accounted < report.requested) {
            const auto leaves = spawn_classes_->roll(classname, random_);
            if (leaves.empty()) { ++report.missing_resources; ++accounted; continue; }
            for (const auto& leaf : leaves) {
                if (accounted >= report.requested) break;
                ++accounted;
                spawn_level_ = random_.integer_between(std::min(low, high), std::max(low, high));
                const MasterResourceRecord* resource = nullptr;
                if (leaf.kind == SpawnLeafKind::unit) resource = resources_->find_any(leaf.value);
                else resource = unit_types_->roll(leaf.value, spawn_level_, random_);
                if (!resource || resource->do_not_create) { ++report.missing_resources; continue; }
                // Population category zero is hostile monsters, never turn an
                // NPC, a pet or an item into an attackable enemy by inference.
                if (resource->kind != MasterResourceKind::monster || resource->unit_type != u"MONSTER") {
                    ++report.unsupported_resources; continue;
                }
                std::optional<std::array<float, 3>> position;
                while (candidate_index < candidates.size()) {
                    const auto point = candidates[candidate_index++];
                    bool free = true;
                    for (const auto& prior : occupied)
                        if (distance_squared(point, prior) < 2.25F) { free = false; break; }
                    if (free) { position = point; break; }
                }
                if (!position) { ++report.unplaced; continue; }
                SpawnResolutionStats created;
                create_resource(0, *position, *resource, created);
                report.created += created.entities_created;
                if (created.entities_created) occupied.push_back(*position);
            }
        }
        spawn_level_ = previous_level;
        population_generated_ = true;
        return report;
    } catch (...) {
        entities_.swap(previous_entities); random_ = previous_random;
        next_entity_id_ = previous_id; spawn_level_ = previous_level;
        throw;
    }
}
}
