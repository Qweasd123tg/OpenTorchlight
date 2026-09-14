#include "torchlight/level_scene.hpp"
#include "torchlight/pak_archive.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: level_scene_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const torchlight::LevelsetCatalog levelsets(archive);
        require(levelsets.source_file_count() == 19, "unexpected levelset file count");
        require(levelsets.pieces().size() == 1619, "unexpected level piece count");
        std::size_t missing_render_meshes = 0;
        std::size_t missing_collision_meshes = 0;
        std::size_t pieces_without_files = 0;
        for (const auto& piece : levelsets.pieces()) {
            pieces_without_files +=
                static_cast<std::size_t>(piece.mesh_file.empty() && piece.collision_file.empty());
            if (!piece.mesh_file.empty()) {
                const std::string mesh(piece.mesh_file.begin(), piece.mesh_file.end());
                missing_render_meshes +=
                    static_cast<std::size_t>(!archive.contains_normalized(mesh));
            }
            if (!piece.collision_file.empty()) {
                const std::string collision(piece.collision_file.begin(), piece.collision_file.end());
                missing_collision_meshes +=
                    static_cast<std::size_t>(!archive.contains_normalized(collision));
            }
        }
        require(missing_render_meshes == 46,
                "original levelsets have a different missing render-mesh count");
        require(missing_collision_meshes == 6,
                "original levelsets have a different missing collision-mesh count");
        require(pieces_without_files == 0, "level piece has neither render nor collision data");
        const auto* mine_cart = levelsets.find(-7368771690998263330LL);
        require(mine_cart != nullptr, "mine cart level piece lookup failed");
        require(mine_cart->name == u"mine_Cart", "mine cart has the wrong name");

        const torchlight::LevelSceneLoader loader(archive);
        const auto town = loader.load_fixed_scene(u"media/dungeons/TOWN.DAT");
        require(town.dungeon.name == u"Town", "town dungeon has the wrong name");
        require(town.dungeon.strata.size() == 1, "town has the wrong stratum count");
        require(town.dungeon.strata.front().is_town, "town stratum lacks IS_TOWN");
        require(!town.dungeon.strata.front().allow_portals, "town unexpectedly allows portals");
        require(town.rules.name == u"TOWN", "town rules have the wrong name");
        require(town.rules.display_name == u"Torchlight", "town has the wrong display name");
        require(!town.rules.randomized && !town.rules.populate,
                "town rules have the wrong generation flags");
        require(town.rules.chunks.size() == 1 &&
                    town.rules.chunks.front().type == u"1X1SINGLE_ROOM",
                "town has the wrong fixed chunk");
        require(town.layout.version == 3, "town layout has the wrong version");
        require(town.layout.declared_count == 784, "town layout has the wrong declared count");
        require(town.layout.objects.size() == 733, "town layout has the wrong object count");
        require(town.layout.logic_groups.size() == 22,
                "town layout has the wrong logic-group count");
        std::size_t town_logic_nodes = 0;
        std::size_t town_logic_links = 0;
        for (const auto& group : town.layout.logic_groups) {
            town_logic_nodes += group.nodes.size();
            for (const auto& node : group.nodes) {
                town_logic_links += node.links.size();
            }
        }
        require(town_logic_nodes == 169, "town layout has the wrong logic-node count");
        require(town_logic_links == 221, "town layout has the wrong logic-link count");

        const auto room_pieces = std::count_if(town.layout.objects.begin(),
                                               town.layout.objects.end(), [](const auto& object) {
                                                   return object.descriptor == u"Room Piece";
                                               });
        const auto monsters = std::count_if(town.layout.objects.begin(), town.layout.objects.end(),
                                            [](const auto& object) {
                                                return object.descriptor == u"Monster";
                                            });
        require(room_pieces == 352, "town has the wrong room piece count");
        require(monsters == 44, "town has the wrong placed monster count");
        std::unordered_set<std::int64_t> object_ids;
        std::size_t positioned_room_pieces = 0;
        std::size_t parented_room_pieces = 0;
        for (const auto& object : town.layout.objects) {
            object_ids.insert(object.id);
            if (object.descriptor == u"Room Piece") {
                positioned_room_pieces += static_cast<std::size_t>(
                    object.position_x.has_value() && object.position_y.has_value() &&
                    object.position_z.has_value());
                parented_room_pieces += static_cast<std::size_t>(object.parent_id != -1);
            }
        }
        require(object_ids.size() == town.layout.objects.size(), "layout object IDs are not unique");
        require(positioned_room_pieces == 352, "town room piece lacks a local position");
        require(parented_room_pieces == 352, "town room piece lacks a parent group");
        const auto transforms = torchlight::resolve_layout_world_transforms(town.layout);
        require(transforms.size() == town.layout.objects.size(),
                "world transform count does not match layout objects");
        float minimum_x = std::numeric_limits<float>::max();
        float maximum_x = std::numeric_limits<float>::lowest();
        float minimum_z = std::numeric_limits<float>::max();
        float maximum_z = std::numeric_limits<float>::lowest();
        for (const auto& object : town.layout.objects) {
            if (object.descriptor == u"Room Piece") {
                require(object.piece_guid.has_value(), "town room piece has no GUID");
                require(levelsets.find(*object.piece_guid) != nullptr,
                        "town room piece GUID is absent from levelsets");
                const auto index = static_cast<std::size_t>(&object - town.layout.objects.data());
                const auto& transform = transforms[index];
                for (const auto value : transform.position) {
                    require(std::isfinite(value), "town room piece has a non-finite position");
                }
                for (const auto value : transform.scale) {
                    require(std::isfinite(value) && value > 0.0F,
                            "town room piece has an invalid scale");
                }
                minimum_x = std::min(minimum_x, transform.position[0]);
                maximum_x = std::max(maximum_x, transform.position[0]);
                minimum_z = std::min(minimum_z, transform.position[2]);
                maximum_z = std::max(maximum_z, transform.position[2]);
            }
        }
        std::cout << "world_room_bounds x=" << minimum_x << ".." << maximum_x
                  << " z=" << minimum_z << ".." << maximum_z << '\n';

        const auto main_dungeon = loader.load_dungeon(u"media/dungeons/MAIN.DAT");
        require(main_dungeon.strata.size() == 35, "main dungeon has the wrong stratum count");
        std::set<std::string> main_rule_files;
        std::set<std::string> main_layout_files;
        std::size_t randomized_strata = 0;
        std::size_t fixed_strata = 0;
        std::size_t chunk_types = 0;
        std::size_t chunk_exits = 0;
        std::size_t candidate_references = 0;
        std::size_t inclusive_files = 0;
        std::size_t must_place_types = 0;
        for (const auto& stratum : main_dungeon.strata) {
            const auto rules = loader.load_rules(stratum.ruleset);
            main_rule_files.insert(rules.source_path);
            randomized_strata += static_cast<std::size_t>(rules.randomized);
            fixed_strata += static_cast<std::size_t>(!rules.randomized);
            if (rules.randomized) {
                require(!rules.chunk_types.empty(), "randomized floor has no chunk types");
                require(rules.minimum_chunks >= 0 &&
                            rules.maximum_chunks >= rules.minimum_chunks,
                        "randomized floor has an invalid chunk count range");
            }
            chunk_types += rules.chunk_types.size();
            for (const auto& type : rules.chunk_types) {
                chunk_exits += type.exits.size();
                inclusive_files += type.inclusive_files.size();
                must_place_types += static_cast<std::size_t>(type.must_place);
                const auto candidates = loader.layout_candidates(rules, type.name);
                require(!candidates.empty(), "main floor chunk type has no layout candidates");
                candidate_references += candidates.size();
                main_layout_files.insert(candidates.begin(), candidates.end());
            }
        }
        require(main_rule_files.size() == 25, "main dungeon has the wrong unique rule count");
        require(randomized_strata == 22 && fixed_strata == 13,
                "main dungeon generation mode count changed");
        require(chunk_types == 306, "main dungeon has the wrong chunk type count");
        require(chunk_exits == 419, "main dungeon has the wrong chunk exit count");
        require(candidate_references == 715,
                "main dungeon has the wrong layout candidate reference count");
        require(main_layout_files.size() == 257,
                "main dungeon has the wrong unique layout candidate count");
        require(inclusive_files == 31, "main dungeon inclusive-file count changed");
        require(must_place_types == 1, "main dungeon must-place type count changed");
        std::cout << "PASS: resolved Town and reusable rules for all 35 main dungeon floors\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
