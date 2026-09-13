#pragma once

#include <filesystem>
#include <vector>

namespace torchlight {

enum class ResourceLocationType { zip, file_system };

struct ResourceLocation {
    ResourceLocationType type = ResourceLocationType::file_system;
    std::filesystem::path path;
};

[[nodiscard]] std::vector<ResourceLocation> parse_resource_config(
    const std::filesystem::path& path);

} // namespace torchlight
