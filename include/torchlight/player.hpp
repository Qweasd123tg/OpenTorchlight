#pragma once

#include "torchlight/damage.hpp"
#include "torchlight/progression.hpp"
#include "torchlight/equipment.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/unit_definition.hpp"

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace torchlight {

struct PlayerPrototype {
    std::shared_ptr<const ProgressionRules> progression_rules;
    std::int64_t guid = 0;
    std::u16string name;
    std::u16string display_name;
    std::string mesh_path;
    std::vector<std::string> wardrobe_texture_layers;
    float walking_speed = 0.0F;
    float running_speed = 0.0F;
    float attack_speed = 0.0F;
    float weapon_scale = 1.0F;
    float reach_bonus = 0.0F;
    float minimum_health = 1.0F;
    float maximum_health = 1.0F;
    // original-code: CPlayer::calculateMaxMana evaluates MANA_GRAPH at level 1.
    // Absent graph => unknown capacity, not a fabricated default.
    std::optional<std::int32_t> base_mana;
    std::int32_t starting_gold = 0;
    // Session creation policy. Hardcore character creation is not yet imported.
    bool hardcore = false;
    std::int32_t minimum_damage = 0;
    std::int32_t maximum_damage = 0;
    std::int32_t strength = 0;
    std::int32_t dexterity = 0;
    std::int32_t magic = 0;
    std::int32_t defense = 0;
    std::int32_t minimum_armor_bonus = 0;
    std::int32_t maximum_armor_bonus = 0;
    DamageDefense damage_defense;
    AttackLoadout attacks;
    AttackCharacterValues attack_character;
    std::optional<WeaponPrototype> starting_weapon;
};

[[nodiscard]] std::vector<PlayerPrototype> load_playable_players(
    const PakArchive& archive, const MasterResourceIndex& resources,
    UnitDefinitionLoader& definitions);

void append_player_geometry(const PakArchive& archive, const PlayerPrototype& player,
                            const std::array<float, 3>& position,
                            FixedSceneGeometry& geometry);

[[nodiscard]] std::optional<std::size_t> append_player_weapon_geometry(
    const PakArchive& archive, const PlayerPrototype& player,
    const std::array<float, 3>& position, FixedSceneGeometry& geometry);

[[nodiscard]] std::array<float, 3> layout_player_start(const LayoutManifest& layout);

[[nodiscard]] std::array<float, 3> generated_player_start(
    const LevelSceneLoader& loader, const GeneratedLevel& level);

} // namespace torchlight
