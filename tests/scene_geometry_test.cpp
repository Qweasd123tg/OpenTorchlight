#include "torchlight/adm_document.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/random_level.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/unit_definition.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

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
            std::cerr << "usage: scene_geometry_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const torchlight::LevelsetCatalog levelsets(archive);
        const torchlight::LevelSceneLoader loader(archive);
        const auto town = loader.load_fixed_scene(u"media/dungeons/TOWN.DAT");
        auto geometry = torchlight::build_room_piece_geometry(archive, levelsets, town);
        require(geometry.meshes.size() == 303, "unexpected town mesh resource count");
        require(geometry.instances.size() == 352, "unexpected town mesh instance count");
        require(geometry.unique_vertex_count == 421431, "unexpected town vertex count");
        require(geometry.unique_index_count == 421431, "unexpected town index count");
        for (const auto& instance : geometry.instances) {
            require(instance.object_index < town.layout.objects.size(),
                    "town instance has an invalid object index");
            require(instance.mesh_index < geometry.meshes.size(),
                    "town instance has an invalid mesh index");
            for (const auto value : instance.transform.position) {
                require(std::isfinite(value), "town instance has a non-finite position");
            }
            for (const auto value : instance.transform.scale) {
                require(std::isfinite(value) && value > 0.0F,
                        "town instance has an invalid scale");
            }
        }
        const auto master = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex resources(master);
        torchlight::UnitDefinitionLoader definitions(archive);
        const auto monsters = torchlight::append_layout_monster_geometry(
            archive, resources, definitions, town.layout, geometry);
        require(monsters == 44, "unexpected placed town monster count");
        require(geometry.instances.size() == 396,
                "placed monsters were not appended to town geometry");
        require(geometry.meshes.size() > 303,
                "placed monsters added no unique mesh resources");
        const auto main = loader.load_dungeon(u"media/dungeons/MAIN.DAT");
        const auto mine_rules = loader.load_rules(main.strata.front().ruleset);
        const torchlight::RandomLevelGenerator generator(loader);
        const auto generated = generator.generate(mine_rules, 42U);
        const auto mine_geometry = torchlight::build_generated_level_geometry(
            archive, levelsets, loader, mine_rules, generated);
        require(generated.chunks.size() >= 3, "generated mine has too few chunks");
        require(!mine_geometry.meshes.empty(), "generated mine has no mesh resources");
        require(!mine_geometry.instances.empty(), "generated mine has no mesh instances");
        for (const auto& instance : mine_geometry.instances) {
            require(instance.layout_index < generated.chunks.size(),
                    "generated mine instance has an invalid layout index");
            require(instance.mesh_index < mine_geometry.meshes.size(),
                    "generated mine instance has an invalid mesh index");
        }
        std::cout << "PASS: built 352 town pieces and 44 placed monsters from "
                  << geometry.meshes.size() << " cached OGRE meshes\n";
        std::cout << "generated_mine chunks=" << generated.chunks.size()
                  << " meshes=" << mine_geometry.meshes.size()
                  << " instances=" << mine_geometry.instances.size() << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
