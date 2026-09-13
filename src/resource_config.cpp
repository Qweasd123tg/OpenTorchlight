#include "torchlight/resource_config.hpp"

#include "torchlight/pak_archive.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>

namespace torchlight {
namespace {

std::string trim(std::string value) {
    const auto space = [](unsigned char character) { return std::isspace(character) != 0; };
    value.erase(value.begin(), std::find_if_not(value.begin(), value.end(), space));
    value.erase(std::find_if_not(value.rbegin(), value.rend(), space).base(), value.end());
    return value;
}

} // namespace

std::vector<ResourceLocation> parse_resource_config(const std::filesystem::path& path) {
    std::ifstream stream(path);
    if (!stream) {
        throw PakError("Could not open resource configuration: " + path.string());
    }
    std::vector<ResourceLocation> locations;
    std::string line;
    std::size_t line_number = 0;
    while (std::getline(stream, line)) {
        ++line_number;
        line = trim(std::move(line));
        if (line.empty() || line.front() == '#') {
            continue;
        }
        const auto separator = line.find('=');
        if (separator == std::string::npos) {
            throw PakError("Invalid resource configuration line " + std::to_string(line_number));
        }
        const auto type = trim(line.substr(0, separator));
        const auto location = trim(line.substr(separator + 1));
        if (location.empty()) {
            throw PakError("Empty resource location on line " + std::to_string(line_number));
        }
        if (type == "Zip") {
            locations.push_back({ResourceLocationType::zip, location});
        } else if (type == "FileSystem") {
            locations.push_back({ResourceLocationType::file_system, location});
        } else {
            throw PakError("Unsupported resource location type on line " +
                           std::to_string(line_number) + ": " + type);
        }
    }
    if (!stream.eof()) {
        throw PakError("Could not read resource configuration: " + path.string());
    }
    return locations;
}

} // namespace torchlight
