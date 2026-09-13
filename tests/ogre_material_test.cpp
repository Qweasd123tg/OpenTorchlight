#include "torchlight/level_scene.hpp"
#include "torchlight/ogre_material.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/scene_geometry.hpp"

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
            std::cerr << "usage: ogre_material_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const torchlight::OgreMaterialCatalog materials(archive);
        require(materials.source_file_count() == 1182, "unexpected material script count");

        std::size_t texture_references = 0;
        std::size_t resolved_texture_references = 0;
        for (const auto& material : materials.materials()) {
            for (const auto& texture : material.textures) {
                ++texture_references;
                resolved_texture_references += static_cast<std::size_t>(
                    torchlight::resolve_material_texture(archive, material, texture) != nullptr);
            }
        }
        const auto* bank = materials.find("Material_#238682125/town_bank_01");
        require(bank != nullptr, "town bank material was not indexed");
        require(bank->textures.size() == 1 && bank->textures.front() == "town_bank_01.png",
                "town bank material has the wrong texture");
        const auto* bank_texture =
            torchlight::resolve_material_texture(archive, *bank, bank->textures.front());
        require(bank_texture != nullptr, "town bank texture did not resolve");
        require(bank_texture->name == "media/levelSets/town1/town_bank_01.dds",
                "town bank texture resolved to the wrong resource");

        const torchlight::LevelsetCatalog levelsets(archive);
        const torchlight::LevelSceneLoader loader(archive);
        const auto town = loader.load_fixed_scene(u"media/dungeons/TOWN.DAT");
        const auto geometry = torchlight::build_room_piece_geometry(archive, levelsets, town);
        std::size_t town_submeshes = 0;
        std::size_t town_materials_found = 0;
        std::size_t town_textures_resolved = 0;
        std::size_t town_materials_without_textures = 0;
        std::size_t town_missing_textures = 0;
        for (const auto& resource : geometry.meshes) {
            for (const auto& submesh : resource.mesh.submeshes) {
                ++town_submeshes;
                const auto* material = materials.find(submesh.material);
                if (material == nullptr) {
                    continue;
                }
                ++town_materials_found;
                if (material->textures.empty()) {
                    ++town_materials_without_textures;
                } else if (torchlight::resolve_material_texture(
                               archive, *material, material->textures.front()) != nullptr) {
                    ++town_textures_resolved;
                } else {
                    ++town_missing_textures;
                }
            }
        }
        require(materials.materials().size() == 2749, "unexpected material definition count");
        require(materials.duplicate_name_count() == 1214,
                "unexpected duplicate material name count");
        require(texture_references == 2401, "unexpected texture reference count");
        require(resolved_texture_references == 2196,
                "unexpected resolved texture reference count");
        require(town_submeshes == 525, "unexpected town submesh count");
        require(town_materials_found == town_submeshes,
                "town submesh material is absent from the catalog");
        require(town_textures_resolved == town_submeshes,
                "town submesh texture did not resolve");
        require(town_materials_without_textures == 0,
                "town material has no texture declaration");
        require(town_missing_textures == 0, "town material texture is absent from pak.zip");
        std::cout << "PASS: indexed 2749 material definitions and resolved textures for all "
                     "525 town submeshes\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
