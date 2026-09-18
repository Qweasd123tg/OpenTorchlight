#include "torchlight/population.hpp"
#include "torchlight/entity_world.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <optional>
#include <queue>
#include <stdexcept>

namespace torchlight {
namespace {
// The spawn-facing setup uses double-precision pi/180 (cvtps2pd/mulsd/cvtpd2ps
// at 0x95d723-0x95d736, f64 0xfc4588 = 0.01745329252); the polar pick below
// uses the f32 path (mulss at 0x9457d2, f32 0xfce49c). Facings are not stored
// by the port (no facing state). Full pin-down: research/population-placement.md.
constexpr float kSpawnHeightGuess = 27.5F;   // code immediate at 0x95d59b (0x41dc0000)
constexpr float kOpenPickRadius = 3.0F;      // DAT_00fa86d4
constexpr float kNoSpawnTestRadius = 1.0F;   // DAT_00fa47fc
constexpr int kSpawnAttempts = 50;           // ebp <= 0x31 retry loop
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
PolarPick random_open_offset(float minimum_radius, float maximum_radius,
                             TorchlightRandom& rng) {
    const float radius = rng.between(minimum_radius, maximum_radius);
    const float degrees = rng.between(0.0F, 360.0F);
    // original-code: single-precision degrees * f32 pi/180 here (mulss at
    // 0x9457d2 with DAT_00fce49c). The facing setup uses the double path
    // instead (see random_spawn_facing); do not unify them.
    const float angle = degrees * 0.017453292F;
    float sine = 0.0F, cosine = 0.0F;
    ::sincosf(angle, &sine, &cosine);
    // SSE order of the original: dx = 0*cos + radius*sin, dz = radius*cos - 0*sin.
    return PolarPick{radius * sine, radius * cosine};
}
std::optional<std::array<float, 3>> section_spawn_point(const NavigationGrid& grid,
    float minimum_x, float maximum_x, float minimum_z, float maximum_z, float height,
    const std::vector<std::array<float, 3>>& exclusions, TorchlightRandom& rng) {
    for (int attempt = 0; attempt < kSpawnAttempts; ++attempt) {
        // Register-verified RNG order: z first, then x (0x95d550/0x95d568).
        const float z = rng.between(minimum_z, maximum_z);
        const float x = rng.between(minimum_x, maximum_x);
        const auto pick = scan_open_point(grid, x, height, z, rng);
        if (!pick) continue;
        const float px = (*pick)[0], pz = (*pick)[2];
        // ucomiss jne/jp chains: accept unless the whole triple is unchanged
        // (NaN/unordered accepts, identical to chained !=).
        if (px != x || kSpawnHeightGuess != height || pz != z) {
            bool inside = false;
            for (const auto& exclusion : exclusions)
                if ((px - exclusion[0]) * (px - exclusion[0]) +
                        (pz - exclusion[2]) * (pz - exclusion[2]) <
                    kNoSpawnTestRadius * kNoSpawnTestRadius) {
                    inside = true;
                    break;
                }
            if (!inside) return std::array<float, 3>{px, height, pz};
        }
    }
    return std::nullopt;
}
bool grid_point_walkable(const NavigationGrid& grid, float x, float z) {
    // original-code: floor((v-o)/0.4) indices, out-of-bounds rejection
    // (mapPassable @0x938390 / positionPassable @0x938480).
    const float cs = grid.cell_size();
    if (!(cs > 0.0F) || grid.width() == 0 || grid.height() == 0) return false;
    const auto corner = grid.cell_center(0, 0);
    const long ix = static_cast<long>(std::floor((x - (corner[0] - cs / 2.0F)) / cs));
    const long iz = static_cast<long>(std::floor((z - (corner[2] - cs / 2.0F)) / cs));
    if (ix < 0 || iz < 0 || static_cast<std::size_t>(ix) >= grid.width() ||
        static_cast<std::size_t>(iz) >= grid.height())
        return false;
    return grid.cell(static_cast<std::size_t>(ix), static_cast<std::size_t>(iz)).walkable;
}
std::optional<std::array<float, 3>> scan_open_point(const NavigationGrid& grid, float cx,
    float cy, float cz, TorchlightRandom& rng) {
    // original-code: live scan of randomOpenPositionRange @0x945770. One map
    // test per attempt; the elaborate x/z loop bounds collapse to a single
    // evaluation of the polar candidate (GDB-verified control flow; the
    // redundant evaluations are idempotent).
    float radius = kOpenPickRadius;
    for (int attempt = 0; attempt < 100; ++attempt) {
        const PolarPick pick = random_open_offset(0.0F, radius, rng);
        if (grid_point_walkable(grid, cx + pick.dx, cz + pick.dz))
            return std::array<float, 3>{cx + pick.dx, cy, cz + pick.dz};
        if (attempt >= 5) radius = std::max(5.0F, radius + 0.1F);
    }
    return std::nullopt;
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
    // original-code: rejection sampling per entry, no connectivity filtering
    // (research/population-placement.md). The grid bounds stand in for the
    // template section rect, which the port does not plumb yet (documented
    // deviation, not a claim of section parity).
    for (const auto v : entry) if (!std::isfinite(v)) throw std::invalid_argument("invalid population entry");
    const auto cell = grid.cell_size();
    const auto corner = grid.cell_center(0, 0);
    const float minimum_x = corner[0] - cell / 2.0F, minimum_z = corner[2] - cell / 2.0F;
    const float maximum_x = minimum_x + static_cast<float>(grid.width()) * cell;
    const float maximum_z = minimum_z + static_cast<float>(grid.height()) * cell;
    // The original spawns at the constant height guess 27.5 and lets the engine
    // settle units; the port has no settle step, so Y is snapped to the nearest
    // walkable cell height (documented deviation; X/Z selection is unaffected).
    const auto ground_height = [&](float x, float z) {
        if (const auto near = grid.nearest_walkable({x, entry[1], z}, 16))
            return grid.cell_center((*near)[0], (*near)[1])[1];
        return entry[1];
    };
    report.reachable_nodes = report.pathable_nodes;
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
        std::size_t accounted = 0;
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
                std::optional<std::array<float, 3>> position =
                    section_spawn_point(grid, minimum_x, maximum_x, minimum_z, maximum_z,
                        kSpawnHeightGuess, exclusions, random_);
                if (!position) { ++report.unplaced; continue; }
                (*position)[1] = ground_height((*position)[0], (*position)[2]);
                SpawnResolutionStats created;
                create_resource(0, *position, *resource, created);
                report.created += created.entities_created;
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
