#include "torchlight/ogre_material.hpp"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <stdexcept>
#include <string>
#include <utility>

namespace torchlight {
namespace {

class OgreMaterialError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::string lowercase(std::string_view value) {
    std::string result;
    result.reserve(value.size());
    for (const unsigned char character : value) {
        if (character >= 'A' && character <= 'Z') {
            result.push_back(static_cast<char>(character - 'A' + 'a'));
        } else if (character == '\\') {
            result.push_back('/');
        } else {
            result.push_back(static_cast<char>(character));
        }
    }
    return result;
}

bool ends_with(std::string_view value, std::string_view suffix) noexcept {
    return value.size() >= suffix.size() &&
           value.substr(value.size() - suffix.size(), suffix.size()) == suffix;
}

std::vector<std::string> tokenize(std::string_view script) {
    std::vector<std::string> tokens;
    std::size_t index = 0;
    while (index < script.size()) {
        const auto character = static_cast<unsigned char>(script[index]);
        if (std::isspace(character) != 0) {
            ++index;
            continue;
        }
        if (script[index] == '/' && index + 1 < script.size() && script[index + 1] == '/') {
            index += 2;
            while (index < script.size() && script[index] != '\n') {
                ++index;
            }
            continue;
        }
        if (script[index] == '/' && index + 1 < script.size() && script[index + 1] == '*') {
            const auto end = script.find("*/", index + 2);
            if (end == std::string_view::npos) {
                throw OgreMaterialError("Unterminated block comment in OGRE material script");
            }
            index = end + 2;
            continue;
        }
        if (script[index] == '{' || script[index] == '}' || script[index] == ':') {
            tokens.emplace_back(1, script[index++]);
            continue;
        }
        if (script[index] == '"') {
            const auto begin = ++index;
            while (index < script.size() && script[index] != '"') {
                ++index;
            }
            if (index == script.size()) {
                throw OgreMaterialError("Unterminated quote in OGRE material script");
            }
            tokens.emplace_back(script.substr(begin, index - begin));
            ++index;
            continue;
        }
        const auto begin = index;
        while (index < script.size()) {
            const auto current = static_cast<unsigned char>(script[index]);
            if (std::isspace(current) != 0 || script[index] == '{' || script[index] == '}' ||
                script[index] == ':' ||
                (script[index] == '/' && index + 1 < script.size() &&
                 (script[index + 1] == '/' || script[index + 1] == '*'))) {
                break;
            }
            ++index;
        }
        if (begin != index) {
            tokens.emplace_back(script.substr(begin, index - begin));
        }
    }
    return tokens;
}

std::size_t matching_brace(const std::vector<std::string>& tokens, std::size_t open) {
    std::size_t depth = 0;
    for (std::size_t index = open; index < tokens.size(); ++index) {
        if (tokens[index] == "{") {
            ++depth;
        } else if (tokens[index] == "}") {
            if (depth == 0) {
                throw OgreMaterialError("Unexpected closing brace in OGRE material script");
            }
            --depth;
            if (depth == 0) {
                return index;
            }
        }
    }
    throw OgreMaterialError("Unterminated material block in OGRE material script");
}

std::string replace_extension_with_dds(std::string path) {
    const auto slash = path.find_last_of('/');
    const auto dot = path.find_last_of('.');
    if (dot == std::string::npos || (slash != std::string::npos && dot < slash)) {
        path += ".dds";
    } else {
        path.resize(dot);
        path += ".dds";
    }
    return path;
}

std::string collapse_path(std::string_view path) {
    std::vector<std::string> components;
    std::size_t begin = 0;
    while (begin <= path.size()) {
        const auto end = path.find('/', begin);
        const auto component = path.substr(
            begin, end == std::string_view::npos ? path.size() - begin : end - begin);
        if (!component.empty() && component != ".") {
            if (component == "..") {
                if (!components.empty()) {
                    components.pop_back();
                }
            } else {
                components.emplace_back(component);
            }
        }
        if (end == std::string_view::npos) {
            break;
        }
        begin = end + 1;
    }
    std::string result;
    for (const auto& component : components) {
        if (!result.empty()) {
            result.push_back('/');
        }
        result += component;
    }
    return result;
}

std::array<float, 3> parse_rgb(const std::vector<std::string>& tokens,
                               std::size_t first, std::size_t end) {
    if (first > end || 3U > end - first) {
        throw OgreMaterialError("OGRE material color has fewer than three channels");
    }
    std::array<float, 3> result{};
    for (std::size_t channel = 0; channel < result.size(); ++channel) {
        std::size_t parsed = 0;
        result[channel] = std::stof(tokens[first + channel], &parsed);
        if (parsed != tokens[first + channel].size()) {
            throw OgreMaterialError("OGRE material color channel is not numeric");
        }
    }
    return result;
}

std::uint8_t parse_byte(std::string_view value, std::string_view directive) {
    unsigned parsed = 0;
    const auto result = std::from_chars(value.data(), value.data() + value.size(), parsed);
    if (result.ec != std::errc{} || result.ptr != value.data() + value.size() ||
        parsed > 255U) {
        throw OgreMaterialError(std::string(directive) + " value is not a byte");
    }
    return static_cast<std::uint8_t>(parsed);
}

void parse_first_texture_unit(const std::vector<std::string>& tokens,
                              std::size_t open, std::size_t close,
                              OgreMaterial& material) {
    for (auto index = open + 1U; index < close; ++index) {
        const auto directive = lowercase(tokens[index]);
        if (directive == "texture" && index + 1U < close) {
            material.primary_texture = tokens[index + 1U];
        } else if (directive == "tex_address_mode" && index + 1U < close) {
            material.texture_clamp = lowercase(tokens[index + 1U]) == "clamp";
        } else if (directive == "filtering" && index + 1U < close) {
            material.texture_filter_linear = lowercase(tokens[index + 1U]) != "none";
        } else if (directive == "colour_op" && index + 1U < close) {
            material.texture_color_operation =
                lowercase(tokens[index + 1U]) == "add"
                    ? OgreTextureColorOperation::add
                    : OgreTextureColorOperation::modulate;
        }
    }
}

void parse_first_pass(const std::vector<std::string>& tokens,
                      std::size_t open, std::size_t close,
                      OgreMaterial& material) {
    bool parsed_texture_unit = false;
    for (auto index = open + 1U; index < close; ++index) {
        const auto directive = lowercase(tokens[index]);
        if (directive == "texture_unit") {
            auto child_open = index + 1U;
            while (child_open < close && tokens[child_open] != "{") {
                ++child_open;
            }
            if (child_open < close) {
                const auto child_close = matching_brace(tokens, child_open);
                if (!parsed_texture_unit) {
                    parse_first_texture_unit(tokens, child_open, child_close, material);
                    parsed_texture_unit = true;
                }
                index = child_close;
            }
        } else if (tokens[index] == "{") {
            index = matching_brace(tokens, index);
        } else if (directive == "ambient" && index + 3U < close) {
            material.ambient = parse_rgb(tokens, index + 1U, close);
            index += 3U;
        } else if (directive == "diffuse" && index + 1U < close &&
                   lowercase(tokens[index + 1U]) == "vertexcolour") {
            material.diffuse_vertex_color = true;
            ++index;
        } else if (directive == "diffuse" && index + 3U < close) {
            material.diffuse = parse_rgb(tokens, index + 1U, close);
            index += 3U;
        } else if (directive == "emissive" && index + 3U < close) {
            material.emissive = parse_rgb(tokens, index + 1U, close);
            index += 3U;
        } else if (directive == "scene_blend" && index + 1U < close) {
            const auto source = lowercase(tokens[index + 1U]);
            if (source == "alpha_blend") {
                material.scene_blend = OgreSceneBlend::alpha;
            } else if (source == "add" ||
                       (source == "one" && index + 2U < close &&
                        lowercase(tokens[index + 2U]) == "one")) {
                material.scene_blend = OgreSceneBlend::add;
            } else if (source == "modulate") {
                material.scene_blend = OgreSceneBlend::modulate;
            }
        } else if (directive == "alpha_rejection" && index + 2U < close) {
            const auto comparison = lowercase(tokens[index + 1U]);
            if (comparison == "greater") {
                material.alpha_compare = OgreAlphaCompare::greater;
            } else if (comparison == "greater_equal") {
                material.alpha_compare = OgreAlphaCompare::greater_equal;
            }
            material.alpha_rejection_value =
                parse_byte(tokens[index + 2U], "alpha_rejection");
        } else if (directive == "depth_write" && index + 1U < close) {
            material.depth_write = lowercase(tokens[index + 1U]) != "off";
        } else if (directive == "lighting" && index + 1U < close) {
            material.lighting = lowercase(tokens[index + 1U]) != "off";
        }
    }
}

} // namespace

std::vector<OgreMaterial> parse_ogre_material_script(std::string_view script,
                                                      std::string source_path) {
    const auto tokens = tokenize(script);
    std::vector<OgreMaterial> result;
    std::size_t index = 0;
    std::size_t depth = 0;
    while (index < tokens.size()) {
        if (tokens[index] == "{") {
            ++depth;
            ++index;
            continue;
        }
        if (tokens[index] == "}") {
            if (depth == 0) {
                ++index;
                continue;
            }
            --depth;
            ++index;
            continue;
        }
        if (depth != 0 || lowercase(tokens[index]) != "material") {
            ++index;
            continue;
        }
        if (++index >= tokens.size()) {
            throw OgreMaterialError("Material declaration has no name");
        }
        OgreMaterial material;
        material.name = tokens[index++];
        if (index < tokens.size() && tokens[index] == ":") {
            ++index;
            if (index >= tokens.size()) {
                throw OgreMaterialError("Material inheritance has no base name");
            }
            material.base_material = tokens[index++];
        }
        while (index < tokens.size() && tokens[index] != "{") {
            ++index;
        }
        if (index == tokens.size()) {
            throw OgreMaterialError("Material declaration has no body");
        }
        const auto close = matching_brace(tokens, index);
        for (auto body = index + 1; body < close; ++body) {
            const auto directive = lowercase(tokens[body]);
            if (directive == "texture" && body + 1 < close && tokens[body + 1] != "{") {
                material.textures.push_back(tokens[++body]);
            }
        }
        for (auto body = index + 1U; body < close; ++body) {
            if (lowercase(tokens[body]) != "pass") {
                continue;
            }
            auto pass_open = body + 1U;
            while (pass_open < close && tokens[pass_open] != "{") {
                ++pass_open;
            }
            if (pass_open < close) {
                parse_first_pass(tokens, pass_open,
                                 matching_brace(tokens, pass_open), material);
            }
            break;
        }
        material.source_path = source_path;
        result.push_back(std::move(material));
        index = close + 1;
    }
    if (depth != 0) {
        throw OgreMaterialError("Unterminated top-level block in OGRE material script");
    }
    return result;
}

OgreMaterialCatalog::OgreMaterialCatalog(const PakArchive& archive) {
    for (const auto& entry : archive.entries()) {
        const auto normalized = lowercase(entry.name);
        if (!ends_with(normalized, ".material")) {
            continue;
        }
        ++source_file_count_;
        const auto bytes = archive.read(entry);
        const std::string script(bytes.begin(), bytes.end());
        std::vector<OgreMaterial> parsed;
        try {
            parsed = parse_ogre_material_script(script, entry.name);
        } catch (const std::exception& error) {
            throw OgreMaterialError(entry.name + ": " + error.what());
        }
        for (auto& material : parsed) {
            const auto material_index = materials_.size();
            const auto inserted = by_name_.emplace(material.name, material_index).second;
            duplicate_name_count_ += static_cast<std::size_t>(!inserted);
            materials_.push_back(std::move(material));
        }
    }
}

const OgreMaterial* OgreMaterialCatalog::find(std::string_view name) const noexcept {
    const auto found = by_name_.find(std::string(name));
    return found == by_name_.end() ? nullptr : &materials_[found->second];
}

const PakArchive::Entry* resolve_material_texture(const PakArchive& archive,
                                                  const OgreMaterial& material,
                                                  std::string_view texture_name) noexcept {
    const auto normalized_texture = lowercase(texture_name);
    std::vector<std::string> candidates;
    if (normalized_texture.rfind("media/", 0) == 0) {
        candidates.push_back(collapse_path(normalized_texture));
    } else {
        const auto slash = material.source_path.find_last_of("/\\");
        const auto directory = slash == std::string::npos
                                   ? std::string{}
                                   : material.source_path.substr(0, slash + 1);
        candidates.push_back(collapse_path(lowercase(directory + std::string(texture_name))));
    }
    candidates.push_back(replace_extension_with_dds(candidates.front()));
    for (const auto& candidate : candidates) {
        if (const auto* entry = archive.find_normalized(candidate)) {
            return entry;
        }
    }
    return nullptr;
}

} // namespace torchlight
