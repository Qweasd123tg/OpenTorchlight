#include "torchlight/adm_document.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/ogre_mesh.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/resource_config.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/unit_definition.hpp"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

struct TreeStats {
    std::size_t groups = 0;
    std::size_t properties = 0;
};

void add_stats(const torchlight::AdmGroup& group, TreeStats& stats) {
    ++stats.groups;
    stats.properties += group.properties.size();
    for (const auto& child : group.groups) {
        add_stats(child, stats);
    }
}

std::string location_type(torchlight::ResourceLocationType type) {
    return type == torchlight::ResourceLocationType::zip ? "Zip" : "FileSystem";
}

} // namespace

int main(int argc, char** argv) {
    try {
        const bool pak_only = argc == 3 && std::string(argv[1]) == "--pak";
        if (argc != 2 && !pak_only) {
            std::cerr << "usage: torchlight_bootstrap /path/to/Torchlight/game | --pak /path/to/pak.zip\n";
            return 2;
        }
        // Explicit asset-only entry point. Full installation mode remains strict
        // about resources.cfg; absent external files are never invented.
        const std::filesystem::path game_directory = argv[1];
        const auto locations = pak_only ? std::vector<torchlight::ResourceLocation>{}
            : torchlight::parse_resource_config(game_directory / "resources.cfg");
        std::filesystem::path pak_path = pak_only ? std::filesystem::path(argv[2]) : std::filesystem::path{};
        std::cout << "resource_configuration=" << (pak_only ? "NOT_RUN_explicit_pak_mode" : "checked") << '\n';
        std::cout << "resource_locations=" << locations.size() << '\n';
        for (const auto& location : locations) {
            const auto resolved = game_directory / location.path;
            std::cout << location_type(location.type) << '=' << location.path.string()
                      << " present=" << std::filesystem::exists(resolved) << '\n';
            if (pak_path.empty() && location.type == torchlight::ResourceLocationType::zip) {
                pak_path = resolved;
            }
        }
        if (pak_path.empty()) {
            throw std::runtime_error("resources.cfg does not declare a Zip location");
        }

        const torchlight::PakArchive archive(pak_path);
        const auto globals = torchlight::parse_adm(archive.read("media/GLOBALS.DAT.adm"));
        const auto units = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex master_resources(units);
        torchlight::UnitDefinitionLoader unit_loader(archive);
        std::size_t longest_inheritance_chain = 0;
        for (const auto& record : master_resources.records()) {
            const auto definition = unit_loader.load(record);
            longest_inheritance_chain = std::max(longest_inheritance_chain,
                                                  definition->inheritance_chain.size());
        }
        const torchlight::LevelsetCatalog levelsets(archive);
        const torchlight::LevelSceneLoader scene_loader(archive);
        const auto town = scene_loader.load_fixed_scene(u"media/dungeons/TOWN.DAT");
        const auto town_geometry =
            torchlight::build_room_piece_geometry(archive, levelsets, town);
        TreeStats global_stats;
        TreeStats unit_stats;
        add_stats(globals.root, global_stats);
        add_stats(units.root, unit_stats);
        const auto* normal_weight = globals.root.find_property(u"NORMAL_ITEM_WEIGHT");
        if (normal_weight == nullptr ||
            normal_weight->type != torchlight::AdmValueType::integer) {
            throw std::runtime_error("GLOBALS has no integer NORMAL_ITEM_WEIGHT");
        }

        std::cout << "archive_entries=" << archive.entries().size() << '\n';
        std::cout << "globals_groups=" << global_stats.groups
                  << " globals_properties=" << global_stats.properties << '\n';
        std::cout << "unit_groups=" << unit_stats.groups
                  << " unit_properties=" << unit_stats.properties << '\n';
        std::cout << "master_resources=" << master_resources.records().size()
                  << " items=" << master_resources.count(torchlight::MasterResourceKind::item)
                  << " monsters=" << master_resources.count(torchlight::MasterResourceKind::monster)
                  << " players=" << master_resources.count(torchlight::MasterResourceKind::player)
                  << " props=" << master_resources.count(torchlight::MasterResourceKind::prop) << '\n';
        std::cout << "unit_definitions=" << master_resources.records().size()
                  << " cached_unit_files=" << unit_loader.cached_definition_count()
                  << " longest_base_chain=" << longest_inheritance_chain << '\n';
        std::cout << "levelset_files=" << levelsets.source_file_count()
                  << " level_pieces=" << levelsets.pieces().size()
                  << " town_layout_objects=" << town.layout.objects.size()
                  << " town_layout_declared=" << town.layout.declared_count << '\n';
        std::cout << "town_meshes=" << town_geometry.meshes.size()
                  << " town_instances=" << town_geometry.instances.size()
                  << " town_vertices=" << town_geometry.unique_vertex_count
                  << " town_indices=" << town_geometry.unique_index_count << '\n';
        std::cout << "normal_item_weight="
                  << std::get<std::int32_t>(normal_weight->value) << '\n';
        std::cout << "bootstrap_state=town-meshes-ready\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "bootstrap failed: " << error.what() << '\n';
        return 1;
    }
}
