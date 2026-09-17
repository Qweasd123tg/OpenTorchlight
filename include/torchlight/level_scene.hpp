#pragma once

#include "torchlight/adm_document.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/scene_math.hpp"

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace torchlight {

struct LevelPiece {
    std::int64_t guid = 0;
    std::u16string tileset;
    std::u16string name;
    std::u16string mesh_file;
    std::u16string collision_file;
    std::u16string tag;
    bool prerender = false;
    bool postrender = false;
    bool scalable = false;
};

class LevelsetCatalog {
public:
    explicit LevelsetCatalog(const PakArchive& archive);

    [[nodiscard]] const std::vector<LevelPiece>& pieces() const noexcept { return pieces_; }
    [[nodiscard]] const LevelPiece* find(std::int64_t guid) const noexcept;
    [[nodiscard]] std::size_t source_file_count() const noexcept { return source_file_count_; }

private:
    std::vector<LevelPiece> pieces_;
    std::unordered_map<std::int64_t, std::size_t> by_guid_;
    std::size_t source_file_count_ = 0;
};

// Constructor defaults recovered from CLevelTemplateData. Placement remains a
// portable collision-grid policy, not a reproduction of original formations.
struct PopulationSettings {
    std::u16string monster_class = u"MONSTERSET";
    bool randomized_class = false;
    float minimum_count = 0, maximum_count = 0;
    float minimum_density = .01F, maximum_density = .0125F;
    std::int32_t minimum_level = -1, maximum_level = -1;
};
void apply_population_overrides(PopulationSettings&, const AdmGroup&);

struct DungeonStratum {
    std::u16string name;
    std::u16string ruleset;
    std::int32_t floors = 1;
    bool allow_portals = true;
    bool allow_pet_return = true;
    bool is_town = false;
    AdmGroup population_overrides{};
};

struct DungeonManifest {
    std::u16string name;
    bool volatile_dungeon = false;
    std::vector<DungeonStratum> strata;
    // Resource-derived route when leaving the first ordinary dungeon floor.
    std::u16string parent_dungeon{};
};

struct ChunkPlacement {
    std::u16string type;
    float x = 0.0F;
    float y = 0.0F;
    float z = 0.0F;
};

struct ChunkExit {
    float x = 0.0F;
    float y = 0.0F;
    float z = 0.0F;
};

struct ChunkResource {
    std::u16string type;
    std::u16string file;
    std::int32_t weight = 1;
};

struct LayoutCandidate {
    std::string path;
    std::int32_t weight = 1;
};

struct ChunkType {
    std::u16string name;
    std::int32_t width = 1;
    std::int32_t height = 1;
    std::int32_t maximum_appearance = 1;
    bool entrance = false;
    bool exit = false;
    bool must_place = false;
    std::u16string folder;
    std::vector<ChunkExit> exits;
    std::vector<std::u16string> inclusive_files;
};

struct LevelRules {
    std::string source_path;
    std::u16string name;
    std::u16string display_name;
    bool randomized = false;
    bool populate = false;
    bool requires_exit = false;
    float tile_basis = 1.0F;
    float chunk_width_basis = 1.0F;
    float chunk_height_basis = 1.0F;
    std::array<float, 4> material_ambient{
        92.0F / 255.0F, 92.0F / 255.0F, 92.0F / 255.0F, 1.0F};
    std::int32_t minimum_chunks = 0;
    std::int32_t maximum_chunks = 0;
    std::vector<ChunkPlacement> chunks;
    std::vector<ChunkResource> chunk_resources;
    std::vector<ChunkType> chunk_types;
    PopulationSettings population{};
};

struct LayoutObject {
    std::u16string descriptor;
    std::u16string name;
    std::int64_t id = 0;
    std::int64_t parent_id = -1;
    std::optional<float> position_x;
    std::optional<float> position_y;
    std::optional<float> position_z;
    float scale_x = 1.0F;
    float scale_y = 1.0F;
    float scale_z = 1.0F;
    float angle = 0.0F;
    std::optional<Matrix3> orientation;
    std::optional<std::int64_t> piece_guid;
    std::u16string resource_file;
    std::u16string monster;
    std::u16string unit;
    std::vector<AdmProperty> properties;

    [[nodiscard]] const AdmProperty* find_property(
        const std::u16string& property_name) const noexcept;
};

struct LayoutLogicLink {
    std::uint32_t target_node_id = 0;
    std::u16string output_name;
    std::u16string input_name;
};

struct LayoutLogicNode {
    std::uint32_t id = 0;
    std::int64_t object_id = 0;
    float editor_x = 0.0F;
    float editor_y = 0.0F;
    std::vector<LayoutLogicLink> links;
};

struct LayoutLogicGroup {
    std::int64_t object_id = 0;
    std::vector<LayoutLogicNode> nodes;
};

struct LayoutWorldTransform {
    std::array<float, 3> position{};
    std::array<float, 3> scale{1.0F, 1.0F, 1.0F};
    Matrix3 orientation = kIdentityRotation;
};

struct LayoutManifest {
    std::string source_path;
    std::int32_t version = 0;
    std::uint32_t declared_count = 0;
    std::vector<LayoutObject> objects;
    std::vector<LayoutLogicGroup> logic_groups;
};

struct LayoutLinkExpansionStats {
    std::size_t links_expanded = 0;
    std::size_t objects_added = 0;
    std::size_t logic_groups_added = 0;
};

struct FixedLevelScene {
    DungeonManifest dungeon;
    LevelRules rules;
    LayoutManifest layout;
};

class LevelSceneLoader {
public:
    explicit LevelSceneLoader(const PakArchive& archive) : archive_(archive) {}

    [[nodiscard]] DungeonManifest load_dungeon(std::u16string_view data_file) const;
    [[nodiscard]] LevelRules load_rules(std::u16string_view data_file) const;
    [[nodiscard]] LayoutManifest load_layout(std::string_view compiled_path) const;
    [[nodiscard]] std::vector<std::string> layout_candidates(
        const LevelRules& rules, std::u16string_view chunk_type) const;
    [[nodiscard]] std::vector<LayoutCandidate> weighted_layout_candidates(
        const LevelRules& rules, std::u16string_view chunk_type) const;
    [[nodiscard]] FixedLevelScene load_fixed_scene(std::u16string_view dungeon_data_file,
                                                   std::size_t stratum_index = 0) const;

private:
    const PakArchive& archive_;
};

[[nodiscard]] std::vector<LayoutWorldTransform> resolve_layout_world_transforms(
    const LayoutManifest& layout);

[[nodiscard]] std::optional<LayoutWorldTransform> find_layout_world_transform(
    const LayoutManifest& layout, std::u16string_view descriptor);

// Replaces Layout Link placeholders with remapped copies of their referenced
// layouts. Linked roots inherit the placeholder transform, and nested links
// are expanded recursively.
[[nodiscard]] LayoutLinkExpansionStats expand_layout_links(
    const LevelSceneLoader& loader, LayoutManifest& layout,
    std::size_t maximum_depth = 16);

} // namespace torchlight
