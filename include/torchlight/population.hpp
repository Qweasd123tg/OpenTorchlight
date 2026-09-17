#pragma once
#include "torchlight/navigation_grid.hpp"
#include "torchlight/randomizer.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
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
// Portable, deterministic component traversal. Excludes disconnected islands and
// cells across excessive height discontinuities; not original location selection.
[[nodiscard]] std::vector<std::array<float, 3>> population_candidates(
    const NavigationGrid&, const std::array<float, 3>& entry,
    const std::vector<std::array<float, 3>>& exclusions = {});
}
