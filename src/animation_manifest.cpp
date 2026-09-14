#include "torchlight/animation_manifest.hpp"

#include <cerrno>
#include <charconv>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <string_view>

namespace torchlight {
namespace {

std::string decode_utf16le(const std::vector<std::uint8_t>& bytes) {
    if (bytes.size() < 2U || bytes[0] != 0xffU || bytes[1] != 0xfeU ||
        (bytes.size() & 1U) != 0U) {
        throw AnimationManifestError("Animation manifest is not BOM-marked UTF-16LE");
    }
    std::string result;
    result.reserve(bytes.size() / 2U);
    for (std::size_t offset = 2U; offset < bytes.size(); offset += 2U) {
        std::uint32_t codepoint = static_cast<std::uint32_t>(bytes[offset]) |
                                  (static_cast<std::uint32_t>(bytes[offset + 1U]) << 8U);
        if (codepoint >= 0xd800U && codepoint <= 0xdbffU) {
            if (offset + 3U >= bytes.size()) {
                throw AnimationManifestError("Animation manifest has a truncated UTF-16 surrogate");
            }
            const auto low = static_cast<std::uint32_t>(bytes[offset + 2U]) |
                             (static_cast<std::uint32_t>(bytes[offset + 3U]) << 8U);
            if (low < 0xdc00U || low > 0xdfffU) {
                throw AnimationManifestError("Animation manifest has an invalid UTF-16 surrogate");
            }
            codepoint = 0x10000U + ((codepoint - 0xd800U) << 10U) + (low - 0xdc00U);
            offset += 2U;
        } else if (codepoint >= 0xdc00U && codepoint <= 0xdfffU) {
            throw AnimationManifestError("Animation manifest has an unmatched UTF-16 surrogate");
        }
        if (codepoint <= 0x7fU) {
            result.push_back(static_cast<char>(codepoint));
        } else if (codepoint <= 0x7ffU) {
            result.push_back(static_cast<char>(0xc0U | (codepoint >> 6U)));
            result.push_back(static_cast<char>(0x80U | (codepoint & 0x3fU)));
        } else if (codepoint <= 0xffffU) {
            result.push_back(static_cast<char>(0xe0U | (codepoint >> 12U)));
            result.push_back(static_cast<char>(0x80U | ((codepoint >> 6U) & 0x3fU)));
            result.push_back(static_cast<char>(0x80U | (codepoint & 0x3fU)));
        } else {
            result.push_back(static_cast<char>(0xf0U | (codepoint >> 18U)));
            result.push_back(static_cast<char>(0x80U | ((codepoint >> 12U) & 0x3fU)));
            result.push_back(static_cast<char>(0x80U | ((codepoint >> 6U) & 0x3fU)));
            result.push_back(static_cast<char>(0x80U | (codepoint & 0x3fU)));
        }
    }
    return result;
}

std::string_view trim(std::string_view value) noexcept {
    while (!value.empty() && (value.front() == ' ' || value.front() == '\t' ||
                              value.front() == '\r')) {
        value.remove_prefix(1U);
    }
    while (!value.empty() && (value.back() == ' ' || value.back() == '\t' ||
                              value.back() == '\r')) {
        value.remove_suffix(1U);
    }
    return value;
}

struct Property {
    std::string_view type;
    std::string_view name;
    std::string_view value;
};

Property parse_property(std::string_view line) {
    if (line.empty() || line.front() != '<') {
        throw AnimationManifestError("Animation manifest has an invalid property line");
    }
    const auto type_end = line.find('>');
    const auto name_end = line.find(':', type_end == std::string_view::npos ? 0U : type_end + 1U);
    if (type_end == std::string_view::npos || name_end == std::string_view::npos ||
        type_end == 1U || name_end == type_end + 1U) {
        throw AnimationManifestError("Animation manifest has a malformed property");
    }
    return {line.substr(1U, type_end - 1U),
            line.substr(type_end + 1U, name_end - type_end - 1U),
            trim(line.substr(name_end + 1U))};
}

float parse_float(std::string_view value, std::string_view name) {
    std::string text(value);
    char* end = nullptr;
    errno = 0;
    const float result = std::strtof(text.c_str(), &end);
    if (errno == ERANGE || end != text.c_str() + text.size() || !std::isfinite(result)) {
        throw AnimationManifestError("Animation manifest has an invalid float for " +
                                     std::string(name));
    }
    return result;
}

std::int32_t parse_integer(std::string_view value, std::string_view name) {
    std::int32_t result = 0;
    const auto parsed = std::from_chars(value.data(), value.data() + value.size(), result);
    if (parsed.ec != std::errc{} || parsed.ptr != value.data() + value.size()) {
        throw AnimationManifestError("Animation manifest has an invalid integer for " +
                                     std::string(name));
    }
    return result;
}

bool parse_boolean(std::string_view value, std::string_view name) {
    if (value == "True" || value == "true" || value == "1") {
        return true;
    }
    if (value == "False" || value == "false" || value == "0") {
        return false;
    }
    throw AnimationManifestError("Animation manifest has an invalid boolean for " +
                                 std::string(name));
}

void require_type(const Property& property, std::string_view expected) {
    if (property.type != expected) {
        throw AnimationManifestError("Animation manifest property " +
                                     std::string(property.name) + " has the wrong type");
    }
}

} // namespace

AnimationManifest parse_animation_manifest(const std::vector<std::uint8_t>& bytes) {
    const auto text = decode_utf16le(bytes);
    enum class Section { outside, animations, animation, key, bone_offset };
    Section section = Section::outside;
    AnimationManifest result;
    AnimationManifestClip* clip = nullptr;
    AnimationEventKey* key = nullptr;
    std::array<float, 3> offset{};
    std::array<bool, 3> has_offset{};
    bool saw_root = false;

    std::size_t begin = 0U;
    while (begin <= text.size()) {
        const auto newline = text.find('\n', begin);
        const auto line = trim(std::string_view(text).substr(
            begin, newline == std::string::npos ? text.size() - begin : newline - begin));
        begin = newline == std::string::npos ? text.size() + 1U : newline + 1U;
        if (line.empty()) {
            continue;
        }
        if (line.front() == '[') {
            if (line == "[ANIMATIONS]" && section == Section::outside && !saw_root) {
                section = Section::animations;
                saw_root = true;
            } else if (line == "[/ANIMATIONS]" && section == Section::animations) {
                section = Section::outside;
            } else if (line == "[ANIMATION]" && section == Section::animations) {
                result.clips.emplace_back();
                clip = &result.clips.back();
                section = Section::animation;
            } else if (line == "[/ANIMATION]" && section == Section::animation) {
                if (clip == nullptr || clip->file.empty()) {
                    throw AnimationManifestError("Animation manifest clip has no FILE");
                }
                clip = nullptr;
                section = Section::animations;
            } else if (line == "[KEY]" && section == Section::animation && clip != nullptr) {
                clip->keys.emplace_back();
                key = &clip->keys.back();
                section = Section::key;
            } else if (line == "[/KEY]" && section == Section::key) {
                key = nullptr;
                section = Section::animation;
            } else if (line == "[BONEOFFSET]" && section == Section::key && key != nullptr) {
                offset = {};
                has_offset = {};
                section = Section::bone_offset;
            } else if (line == "[/BONEOFFSET]" && section == Section::bone_offset && key != nullptr) {
                if (!has_offset[0] || !has_offset[1] || !has_offset[2]) {
                    throw AnimationManifestError("Animation BONEOFFSET is incomplete");
                }
                key->bone_offset = offset;
                section = Section::key;
            } else {
                throw AnimationManifestError("Animation manifest has an unexpected section: " +
                                             std::string(line));
            }
            continue;
        }

        const auto property = parse_property(line);
        if (section == Section::animation && clip != nullptr && property.name == "FILE") {
            require_type(property, "STRING");
            clip->file = std::string(property.value);
        } else if (section == Section::key && key != nullptr) {
            if (property.name == "NAME") {
                require_type(property, "STRING");
                key->name = std::string(property.value);
            } else if (property.name == "FRAME") {
                require_type(property, "FLOAT");
                key->frame = parse_float(property.value, property.name);
            } else if (property.name == "PARTICLECOUNT") {
                require_type(property, "INTEGER");
                key->particle_count = parse_integer(property.value, property.name);
            } else if (property.name == "PARTICLEATTACHES") {
                require_type(property, "BOOL");
                key->particle_attaches = parse_boolean(property.value, property.name);
            } else if (property.name == "SOUND") {
                require_type(property, "STRING");
                key->sound = std::string(property.value);
            } else if (property.name == "LAYOUT") {
                require_type(property, "STRING");
                key->layout = std::string(property.value);
            } else if (property.name == "UNITTHEME") {
                require_type(property, "STRING");
                key->unit_theme = std::string(property.value);
            } else if (property.name == "BONE") {
                require_type(property, "STRING");
                key->bone = std::string(property.value);
            } else if (property.name == "CAMERASHAKE") {
                require_type(property, "STRING");
                key->camera_shake = std::string(property.value);
            } else if (property.name == "CAMERASHAKEDURATION") {
                require_type(property, "FLOAT");
                key->camera_shake_duration = parse_float(property.value, property.name);
            } else {
                throw AnimationManifestError("Unknown animation KEY property: " +
                                             std::string(property.name));
            }
        } else if (section == Section::bone_offset && key != nullptr) {
            require_type(property, "FLOAT");
            const auto axis = property.name == "X" ? 0U : property.name == "Y" ? 1U :
                              property.name == "Z" ? 2U : 3U;
            if (axis == 3U) {
                throw AnimationManifestError("Unknown animation BONEOFFSET property");
            }
            offset[axis] = parse_float(property.value, property.name);
            has_offset[axis] = true;
        } else {
            throw AnimationManifestError("Animation manifest property is outside its section");
        }
    }
    if (!saw_root || section != Section::outside) {
        throw AnimationManifestError("Animation manifest has unbalanced sections");
    }
    return result;
}

} // namespace torchlight
