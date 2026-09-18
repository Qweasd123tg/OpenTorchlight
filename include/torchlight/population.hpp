#pragma once
#include "torchlight/navigation_grid.hpp"
#include "torchlight/randomizer.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>
namespace torchlight {
struct PopulationReport {
    std::size_t pathable_nodes = 0, reachable_nodes = 0, requested = 0;
    std::size_t created = 0, missing_resources = 0, unsupported_resources = 0, unplaced = 0;
    bool already_generated = false;
};
// Original arithmetic at CLevelTemplateData::getNumberOfUnitsToCreate 0x971530.
// Input is pathable 0.4-grid nodes, NOT square meters or the 1.0 movement grid.
[[nodiscard]] std::uint32_t population_count(float count_min, float count_max,
    float density_min, float density_max, std::uint32_t pathable_nodes, TorchlightRandom&);
// original-code: CLevel::randomOpenPositionRange @0x945770 live scan and the
// per-entry sampling of CLevel::populateSectionOfLevel @0x95d220. Each scan
// attempt tests one polar candidate for map/position passability (the loop
// bounds collapse to a single test; the redundant evaluations are idempotent).
// Proof and exact boundaries: research/population-placement.md.
struct PolarPick { float dx = 0.0F, dz = 0.0F; };
// Single polar offset: r in [minimum_radius, maximum_radius], angle in
// [0, 360) degrees through single-precision pi/180 and sincosf, matching the
// original MATH::rotateY @0xc7a400 SSE order (dx = r*sinA, dz = r*cosA).
// (The spawn-facing setup uses the double path instead; see the .cpp.)
[[nodiscard]] PolarPick random_open_offset(float minimum_radius, float maximum_radius,
    TorchlightRandom&);
// Grid-cell walkability for a world point: floor((v-o)/0.4) indices with the
// original out-of-bounds rejection. Stands in for BOTH original 0.4 layers
// (map grid 0x40 and position grid 0x48); the second layer's distinct
// semantics are open, so this is a documented approximation.
[[nodiscard]] bool grid_point_walkable(const NavigationGrid&, float x, float z);
// Live-scan sampling: at most 100 attempts of {r in [0, R], angle, polar
// candidate, walkability test}; R grows as max(5, R + 0.1) after 5 failures.
// nullopt on exhaustion (mirrors the original give-up, which returns the input
// position for the caller to detect). The in-scan no-spawn-region test is
// covered at section level with points (see below), not omitted silently.
[[nodiscard]] std::optional<std::array<float, 3>> scan_open_point(
    const NavigationGrid&, float center_x, float center_y, float center_z,
    TorchlightRandom&);
// Single rejection-sampled section point. RNG order per outer attempt is z,
// x, then the scan above (register-verified). At most 50 outer attempts;
// nullopt on exhaustion. exclusions are tested in XZ against the original 1.0
// radius (DAT_00fa47fc); the original tests true no-spawn region boxes
// (CLevel+0xd8, box fields +0x120/+0x12c/+0x124/+0x130/+0x128/+0x134, kind
// +0x138) while the port only carries points: documented deviation.
[[nodiscard]] std::optional<std::array<float, 3>> section_spawn_point(
    const NavigationGrid&, float minimum_x, float maximum_x, float minimum_z,
    float maximum_z, float height, const std::vector<std::array<float, 3>>& exclusions,
    TorchlightRandom&);
}
