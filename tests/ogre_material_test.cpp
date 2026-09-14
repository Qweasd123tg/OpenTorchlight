#include "torchlight/level_scene.hpp"
#include "torchlight/ogre_material.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/scene_geometry.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>
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

        const auto parse_script = [&](std::string_view path) {
            const auto bytes = archive.read_normalized(path);
            return torchlight::parse_ogre_material_script(
                std::string(bytes.begin(), bytes.end()), std::string(path));
        };
        const auto skeleton_materials =
            parse_script("media/models/skeleton/skeleton_warrior.material");
        const auto skeleton_skin = std::find_if(
            skeleton_materials.begin(), skeleton_materials.end(), [](const auto& material) {
                return material.name == "Material_#38/15_-_Defaultaaa";
            });
        require(skeleton_skin != skeleton_materials.end() &&
                    skeleton_skin->scene_blend == torchlight::OgreSceneBlend::alpha &&
                    skeleton_skin->alpha_compare == torchlight::OgreAlphaCompare::greater &&
                    skeleton_skin->alpha_rejection_value == 5,
                "skeleton alpha pass state was not parsed exactly");
        const auto spectral_materials =
            parse_script("media/models/shadowarcher/shadowarmor.material");
        require(spectral_materials.size() == 1 &&
                    spectral_materials.front().scene_blend ==
                        torchlight::OgreSceneBlend::add &&
                    !spectral_materials.front().depth_write &&
                    !spectral_materials.front().texture_clamp &&
                    spectral_materials.front().primary_texture ==
                        spectral_materials.front().textures.front(),
                "spectral first pass inherited state from another texture unit");
        const auto gold_materials = parse_script("media/models/gold/gold.material");
        require(gold_materials.size() == 1 && gold_materials.front().lighting &&
                    gold_materials.front().textures.size() == 3 &&
                    gold_materials.front().primary_texture ==
                        gold_materials.front().textures.front(),
                "gold first pass inherited state from a later pass");

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
        require(bank->diffuse_vertex_color &&
                    std::abs(bank->ambient[0] - 0.588F) < 0.0001F,
                "town bank material has the wrong vertex-color lighting");
        const auto* alchemist = materials.find("Starter_Set/boots");
        require(alchemist != nullptr &&
                    std::abs(alchemist->diffuse[0] - 0.745098F) < 0.0001F &&
                    std::abs(alchemist->emissive[0] - 0.5F) < 0.0001F,
                "Alchemist material colors were not parsed");
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
                if (material->primary_texture.empty()) {
                    ++town_materials_without_textures;
                } else if (torchlight::resolve_material_texture(
                               archive, *material, material->primary_texture) != nullptr) {
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
