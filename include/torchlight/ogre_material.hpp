#pragma once

#include "torchlight/pak_archive.hpp"

#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace torchlight {

struct OgreMaterial {
    std::string name;
    std::string source_path;
    std::string base_material;
    std::vector<std::string> textures;
    std::array<float, 3> ambient{1.0F, 1.0F, 1.0F};
    std::array<float, 3> diffuse{1.0F, 1.0F, 1.0F};
    std::array<float, 3> emissive{0.0F, 0.0F, 0.0F};
    bool diffuse_vertex_color = false;
    bool alpha_blend = false;
    bool alpha_rejection = false;
};

[[nodiscard]] std::vector<OgreMaterial> parse_ogre_material_script(
    std::string_view script, std::string source_path);

class OgreMaterialCatalog {
public:
    explicit OgreMaterialCatalog(const PakArchive& archive);

    [[nodiscard]] const std::vector<OgreMaterial>& materials() const noexcept {
        return materials_;
    }
    [[nodiscard]] const OgreMaterial* find(std::string_view name) const noexcept;
    [[nodiscard]] std::size_t source_file_count() const noexcept { return source_file_count_; }
    [[nodiscard]] std::size_t duplicate_name_count() const noexcept {
        return duplicate_name_count_;
    }

private:
    std::vector<OgreMaterial> materials_;
    std::unordered_map<std::string, std::size_t> by_name_;
    std::size_t source_file_count_ = 0;
    std::size_t duplicate_name_count_ = 0;
};

[[nodiscard]] const PakArchive::Entry* resolve_material_texture(
    const PakArchive& archive, const OgreMaterial& material, std::string_view texture_name) noexcept;

} // namespace torchlight
