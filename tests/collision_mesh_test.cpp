#include "torchlight/collision_scene.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/navigation_grid.hpp"
#include "torchlight/ogre_mesh.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/player.hpp"

#include <algorithm>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace {
void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

std::string ascii(const std::u16string& value) {
    return std::string(value.begin(), value.end());
}
}

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: collision_mesh_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const torchlight::LevelsetCatalog levelsets(archive);
        std::unordered_set<std::string> unique_paths;
        std::size_t references = 0;
        std::size_t missing = 0;
        for (const auto& piece : levelsets.pieces()) {
            if (piece.collision_file.empty()) {
                continue;
            }
            ++references;
            const auto path = ascii(piece.collision_file);
            const auto* entry = archive.find_normalized(path);
            if (entry == nullptr) {
                ++missing;
                continue;
            }
            unique_paths.insert(entry->name);
        }

        std::uint64_t vertices = 0;
        std::uint64_t indices = 0;
        std::size_t triangle_submeshes = 0;
        std::size_t skeletal = 0;
        for (const auto& path : unique_paths) {
            const auto* entry = archive.find_normalized(path);
            require(entry != nullptr, "indexed collision mesh disappeared");
            const auto mesh = torchlight::parse_ogre_mesh(archive.read(*entry));
            require(mesh.serializer_version == "[MeshSerializer_v1.40]",
                    "collision mesh has an unexpected serializer");
            skeletal += static_cast<std::size_t>(mesh.skeletally_animated);
            if (mesh.shared_geometry) {
                vertices += mesh.shared_geometry->vertex_count;
            }
            for (const auto& submesh : mesh.submeshes) {
                if (submesh.geometry) {
                    vertices += submesh.geometry->vertex_count;
                }
                indices += submesh.indices.size();
                triangle_submeshes += static_cast<std::size_t>(submesh.operation_type == 4);
            }
        }
        require(references > 0 && !unique_paths.empty(), "no collision meshes were indexed");
        require(missing == 6, "original collision missing-file count changed");
        require(skeletal == 0, "collision mesh unexpectedly uses a skeleton");
        require(triangle_submeshes > 0 && indices > 0, "collision meshes have no triangles");
        std::cout << "PASS: parsed " << unique_paths.size() << " unique collision meshes from "
                  << references << " level-piece references, missing=" << missing
                  << " vertices=" << vertices << " indices=" << indices
                  << " triangle_submeshes=" << triangle_submeshes << '\n';

        const torchlight::LevelSceneLoader loader(archive);
        const auto main = loader.load_dungeon(u"media/dungeons/MAIN.DAT");
        const auto rules = loader.load_rules(main.strata.front().ruleset);
        const torchlight::RandomLevelGenerator generator(loader);
        const auto generated = generator.generate(rules, 42U);
        std::size_t angled_objects = 0;
        float maximum_angle = 0.0F;
        for (const auto& chunk : generated.chunks) {
            const auto layout = loader.load_layout(chunk.layout_path);
            for (const auto& object : layout.objects) {
                angled_objects += static_cast<std::size_t>(object.angle != 0.0F);
                maximum_angle = std::max(maximum_angle, std::abs(object.angle));
            }
        }
        const auto scene = torchlight::build_generated_level_collision(
            archive, levelsets, loader, generated);
        require(scene.source_meshes > 0 && scene.instances > 0 && !scene.triangles.empty(),
                "generated floor has no collision geometry");
        std::size_t horizontal = 0;
        std::size_t vertical = 0;
        for (const auto& triangle : scene.triangles) {
            const auto& a = triangle.vertices[0];
            const auto& b = triangle.vertices[1];
            const auto& c = triangle.vertices[2];
            const float ab_x = b[0] - a[0];
            const float ab_y = b[1] - a[1];
            const float ab_z = b[2] - a[2];
            const float ac_x = c[0] - a[0];
            const float ac_y = c[1] - a[1];
            const float ac_z = c[2] - a[2];
            const float nx = ab_y * ac_z - ab_z * ac_y;
            const float ny = ab_z * ac_x - ab_x * ac_z;
            const float nz = ab_x * ac_y - ab_y * ac_x;
            const float length = std::sqrt(nx * nx + ny * ny + nz * nz);
            if (length <= 0.0F) {
                continue;
            }
            horizontal += static_cast<std::size_t>(std::abs(ny) / length >= 0.7F);
            vertical += static_cast<std::size_t>(std::abs(ny) / length <= 0.3F);
        }
        require(horizontal > 0 && vertical > 0,
                "generated collision scene lacks floor or wall triangles");
        std::cout << "generated_collision meshes=" << scene.source_meshes
                  << " instances=" << scene.instances
                  << " missing_instances=" << scene.missing_instances
                  << " triangles=" << scene.triangles.size()
                  << " degenerate=" << scene.degenerate_triangles
                  << " horizontal=" << horizontal << " vertical=" << vertical << '\n';
        std::cout << "layout_angles nonzero=" << angled_objects
                  << " maximum_absolute=" << maximum_angle << '\n';
        const auto navigation = torchlight::NavigationGrid::build(scene);
        const auto player_start = torchlight::generated_player_start(loader, generated);
        require(navigation.walkable_cell_count() > 0,
                "generated navigation grid has no walkable cells");
        require(navigation.nearest_walkable(player_start).has_value(),
                "PlayerStart has no nearby walkable cell");
        std::vector<std::array<float, 3>> path;
        for (const auto offset : std::array<std::array<float, 2>, 8>{{
                 {{12.0F, 0.0F}}, {{-12.0F, 0.0F}}, {{0.0F, 12.0F}}, {{0.0F, -12.0F}},
                 {{8.0F, 8.0F}}, {{-8.0F, 8.0F}}, {{8.0F, -8.0F}}, {{-8.0F, -8.0F}},
             }}) {
            path = navigation.find_path(
                player_start,
                {player_start[0] + offset[0], player_start[1], player_start[2] + offset[1]});
            if (path.size() > 1U) {
                break;
            }
        }
        require(path.size() > 1U, "A* found no local path from PlayerStart");
        std::cout << "navigation_grid=" << navigation.width() << 'x' << navigation.height()
                  << " walkable=" << navigation.walkable_cell_count()
                  << " test_path_nodes=" << path.size() << '\n';

        const auto town = loader.load_fixed_scene(u"media/dungeons/TOWN.DAT");
        const auto town_collision =
            torchlight::build_fixed_level_collision(archive, levelsets, town);
        require(town_collision.instances > 0 && !town_collision.triangles.empty(),
                "town has no collision geometry");
        const auto town_navigation = torchlight::NavigationGrid::build(town_collision);
        const auto town_start = torchlight::layout_player_start(town.layout);
        const auto town_start_cell = town_navigation.nearest_walkable(town_start);
        require(town_start_cell.has_value(), "town PlayerStart has no nearby walkable cell");
        const auto town_floor =
            town_navigation.cell_center((*town_start_cell)[0], (*town_start_cell)[1]);
        require(std::hypot(town_floor[0] - town_start[0], town_floor[2] - town_start[2]) < 1.0F,
                "town PlayerStart does not align with its collision floor");
        require(std::abs(town_floor[1] - town_start[1]) < 0.25F,
                "town PlayerStart has the wrong floor height");
        std::vector<std::array<float, 3>> town_path;
        for (const auto offset : std::array<std::array<float, 2>, 8>{{
                 {{8.0F, 0.0F}}, {{-8.0F, 0.0F}}, {{0.0F, 8.0F}}, {{0.0F, -8.0F}},
                 {{6.0F, 6.0F}}, {{-6.0F, 6.0F}}, {{6.0F, -6.0F}}, {{-6.0F, -6.0F}},
             }}) {
            town_path = town_navigation.find_path(
                town_start,
                {town_start[0] + offset[0], town_start[1], town_start[2] + offset[1]});
            if (town_path.size() > 1U) {
                break;
            }
        }
        require(town_path.size() > 1U, "A* found no local path in town");
        std::cout << "town_navigation_grid=" << town_navigation.width() << 'x'
                  << town_navigation.height()
                  << " walkable=" << town_navigation.walkable_cell_count()
                  << " test_path_nodes=" << town_path.size() << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
