#pragma once

#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/unit_definition.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace torchlight {

struct PlayerPrototype {
    std::int64_t guid = 0;
    std::u16string name;
    std::u16string display_name;
    std::string mesh_path;
    float walking_speed = 0.0F;
    float running_speed = 0.0F;
    float attack_speed = 0.0F;
    float reach_bonus = 0.0F;
    std::int32_t minimum_damage = 0;
    std::int32_t maximum_damage = 0;
    std::int32_t strength = 0;
    std::int32_t dexterity = 0;
    std::int32_t magic = 0;
    std::int32_t defense = 0;
};

[[nodiscard]] std::vector<PlayerPrototype> load_playable_players(
    const PakArchive& archive, const MasterResourceIndex& resources,
    UnitDefinitionLoader& definitions);

void append_player_geometry(const PakArchive& archive, const PlayerPrototype& player,
                            const std::array<float, 3>& position,
                            FixedSceneGeometry& geometry);

[[nodiscard]] std::array<float, 3> layout_player_start(const LayoutManifest& layout);

[[nodiscard]] std::array<float, 3> generated_player_start(
    const LevelSceneLoader& loader, const GeneratedLevel& level);

} // namespace torchlight
