#include "torchlight/level_scene.hpp"

#include "torchlight/master_resource_index.hpp"

#include <algorithm>
#include <charconv>
#include <cmath>
#include <deque>
#include <functional>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <system_error>

namespace torchlight {
namespace {

constexpr float kDegreesToRadians = 0.01745329251994329577F;

class LevelSceneError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

bool is_text(const AdmProperty& property) noexcept {
    return property.type == AdmValueType::string || property.type == AdmValueType::translation ||
           property.type == AdmValueType::note;
}

const AdmProperty* property(const AdmGroup& group, const char16_t* name) noexcept {
    return group.find_property(name);
}

std::u16string text_value(const AdmGroup& group, const char16_t* name,
                          std::u16string fallback = {}) {
    const auto* value = property(group, name);
    if (value == nullptr) {
        return fallback;
    }
    if (!is_text(*value)) {
        throw LevelSceneError("Level property expected to contain text");
    }
    return std::get<std::u16string>(value->value);
}

bool bool_value(const AdmGroup& group, const char16_t* name, bool fallback) {
    const auto* value = property(group, name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type != AdmValueType::boolean) {
        throw LevelSceneError("Level property expected to contain a boolean");
    }
    return std::get<bool>(value->value);
}

std::int32_t int_value(const AdmGroup& group, const char16_t* name, std::int32_t fallback) {
    const auto* value = property(group, name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type != AdmValueType::integer) {
        throw LevelSceneError("Level property expected to contain an integer");
    }
    return std::get<std::int32_t>(value->value);
}

std::uint32_t unsigned_value(const AdmGroup& group, const char16_t* name,
                             std::uint32_t fallback) {
    const auto* value = property(group, name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type != AdmValueType::unsigned_integer) {
        throw LevelSceneError("Level property expected to contain an unsigned integer");
    }
    return std::get<std::uint32_t>(value->value);
}

std::optional<float> optional_float(const AdmGroup& group, const char16_t* name) {
    const auto* value = property(group, name);
    if (value == nullptr) {
        return std::nullopt;
    }
    if (value->type != AdmValueType::floating) {
        throw LevelSceneError("Level property expected to contain a float");
    }
    return std::get<float>(value->value);
}

float float_value(const AdmGroup& group, const char16_t* name, float fallback) {
    const auto value = optional_float(group, name);
    return value.has_value() ? *value : fallback;
}

float numeric_float_value(const AdmGroup& group, const char16_t* name, float fallback) {
    const auto* value = property(group, name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type == AdmValueType::floating) {
        return std::get<float>(value->value);
    }
    if (value->type == AdmValueType::double_precision) {
        return static_cast<float>(std::get<double>(value->value));
    }
    if (value->type == AdmValueType::integer) {
        return static_cast<float>(std::get<std::int32_t>(value->value));
    }
    if (value->type == AdmValueType::unsigned_integer) {
        return static_cast<float>(std::get<std::uint32_t>(value->value));
    }
    if (value->type == AdmValueType::integer64) {
        return static_cast<float>(std::get<std::int64_t>(value->value));
    }
    if (is_text(*value)) {
        const auto& text = std::get<std::u16string>(value->value);
        std::string ascii;
        ascii.reserve(text.size());
        for (const auto character : text) {
            if (character > 0x7fU) {
                throw LevelSceneError("Level numeric text contains a non-ASCII character");
            }
            ascii.push_back(character == u',' ? '.' : static_cast<char>(character));
        }
        float parsed_value = 0.0F;
        const auto parsed =
            std::from_chars(ascii.data(), ascii.data() + ascii.size(), parsed_value);
        if (!ascii.empty() && parsed.ec == std::errc{} &&
            parsed.ptr == ascii.data() + ascii.size()) {
            return parsed_value;
        }
        throw LevelSceneError("Level numeric property contains invalid text: " + ascii);
    }
    throw LevelSceneError("Level property expected to contain a numeric value, ADM type=" +
                          std::to_string(static_cast<std::uint32_t>(value->type)));
}

std::int64_t int64_value(const AdmGroup& group, const char16_t* name,
                         std::int64_t fallback) {
    const auto* value = property(group, name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type != AdmValueType::integer64) {
        throw LevelSceneError("Level property expected to contain a 64-bit integer");
    }
    return std::get<std::int64_t>(value->value);
}

std::optional<std::int64_t> optional_decimal(const AdmGroup& group, const char16_t* name) {
    const auto value = text_value(group, name);
    if (value.empty()) {
        return std::nullopt;
    }
    std::string ascii;
    ascii.reserve(value.size());
    for (const auto character : value) {
        if (character > 0x7fU) {
            throw LevelSceneError("Level GUID contains a non-ASCII character");
        }
        ascii.push_back(static_cast<char>(character));
    }
    std::int64_t result = 0;
    const auto parsed = std::from_chars(ascii.data(), ascii.data() + ascii.size(), result);
    if (parsed.ec != std::errc{} || parsed.ptr != ascii.data() + ascii.size()) {
        throw LevelSceneError("Level GUID is not a signed 64-bit decimal number");
    }
    return result;
}

std::string normalize_path(std::string_view path) {
    std::string result;
    result.reserve(path.size());
    for (const unsigned char character : path) {
        if (character == '\\') {
            result.push_back('/');
        } else if (character >= 'A' && character <= 'Z') {
            result.push_back(static_cast<char>(character - 'A' + 'a'));
        } else {
            result.push_back(static_cast<char>(character));
        }
    }
    return result;
}

bool starts_with(std::string_view value, std::string_view prefix) noexcept {
    return value.size() >= prefix.size() && value.substr(0, prefix.size()) == prefix;
}

bool ends_with(std::string_view value, std::string_view suffix) noexcept {
    return value.size() >= suffix.size() &&
           value.substr(value.size() - suffix.size(), suffix.size()) == suffix;
}

const AdmGroup* child_group(const AdmGroup& group, const char16_t* name) noexcept {
    for (const auto& child : group.groups) {
        if (child.name == name) {
            return &child;
        }
    }
    return nullptr;
}

AdmDocument load_data_file(const PakArchive& archive, std::u16string_view path,
                           const char16_t* expected_root, std::string* actual_path = nullptr) {
    const auto compiled = compiled_adm_path(path);
    const auto* entry = archive.find_normalized(compiled);
    if (entry == nullptr) {
        throw LevelSceneError("Level data file is absent from pak.zip: " + compiled);
    }
    auto document = parse_adm(archive.read(*entry));
    if (document.root.name != expected_root) {
        throw LevelSceneError("Level data file has an unexpected root: " + entry->name);
    }
    if (actual_path != nullptr) {
        *actual_path = entry->name;
    }
    return document;
}

LayoutLogicGroup parse_logic_group(const AdmGroup& group, std::int64_t object_id) {
    LayoutLogicGroup result;
    result.object_id = object_id;
    for (const auto& child : group.groups) {
        if (child.name != u"LOGICOBJECT") {
            continue;
        }
        LayoutLogicNode node;
        node.id = unsigned_value(child, u"ID", 0);
        node.object_id = int64_value(child, u"OBJECTID", 0);
        node.editor_x = float_value(child, u"X", 0.0F);
        node.editor_y = float_value(child, u"Y", 0.0F);
        for (const auto& link_group : child.groups) {
            if (link_group.name != u"LOGICLINK") {
                continue;
            }
            const auto target = int_value(link_group, u"LINKINGTO", -1);
            if (target < 0) {
                throw LevelSceneError("Layout logic link has an invalid target node ID");
            }
            LayoutLogicLink link;
            link.target_node_id = static_cast<std::uint32_t>(target);
            link.output_name = text_value(link_group, u"OUTPUTNAME");
            link.input_name = text_value(link_group, u"INPUTNAME");
            if (link.output_name.empty() || link.input_name.empty()) {
                throw LevelSceneError("Layout logic link has an empty function name");
            }
            node.links.push_back(std::move(link));
        }
        result.nodes.push_back(std::move(node));
    }
    return result;
}

std::int64_t remapped_id(
    const std::unordered_map<std::int64_t, std::int64_t>& ids,
    std::int64_t original) {
    const auto found = ids.find(original);
    if (found == ids.end()) {
        throw LevelSceneError("Linked layout references an absent object");
    }
    return found->second;
}

void replace_int64_property(LayoutObject& object, const char16_t* name,
                            std::int64_t value) {
    for (auto& property_value : object.properties) {
        if (property_value.name == name) {
            if (property_value.type != AdmValueType::integer64) {
                throw LevelSceneError("Linked layout identity property is not 64-bit");
            }
            property_value.value = value;
            return;
        }
    }
}

std::u16string layout_link_file(const LayoutObject& object) {
    const auto* value = object.find_property(u"LAYOUT FILE");
    if (value == nullptr || !is_text(*value)) {
        throw LevelSceneError("Layout Link has no valid LAYOUT FILE");
    }
    return std::get<std::u16string>(value->value);
}

void collect_layout_objects(const AdmGroup& group, std::vector<LayoutObject>& objects,
                            std::vector<LayoutLogicGroup>& logic_groups) {
    if (group.name == u"BASEOBJECT") {
        const auto* properties = child_group(group, u"PROPERTIES");
        if (properties != nullptr) {
            LayoutObject object;
            object.descriptor = text_value(*properties, u"DESCRIPTOR");
            object.name = text_value(*properties, u"NAME");
            object.id = int64_value(*properties, u"ID", 0);
            object.parent_id = int64_value(*properties, u"PARENTID", -1);
            object.position_x = optional_float(*properties, u"POSITIONX");
            object.position_y = optional_float(*properties, u"POSITIONY");
            object.position_z = optional_float(*properties, u"POSITIONZ");
            const auto uniform_scale = float_value(*properties, u"SCALE", 1.0F);
            object.scale_x = float_value(*properties, u"SCALE X", uniform_scale);
            object.scale_y = uniform_scale;
            object.scale_z = float_value(*properties, u"SCALE Z", uniform_scale);
            object.angle = numeric_float_value(*properties, u"ANGLE", 0.0F);
            object.piece_guid = optional_decimal(*properties, u"GUID");
            object.resource_file = text_value(*properties, u"FILE");
            object.monster = text_value(*properties, u"MONSTER");
            object.unit = text_value(*properties, u"UNIT");
            object.properties = properties->properties;
            if (const auto* logic = child_group(*properties, u"LOGICGROUP")) {
                logic_groups.push_back(parse_logic_group(*logic, object.id));
            }
            objects.push_back(std::move(object));
        }
    }
    for (const auto& child : group.groups) {
        collect_layout_objects(child, objects, logic_groups);
    }
}

} // namespace

LevelsetCatalog::LevelsetCatalog(const PakArchive& archive) {
    for (const auto& entry : archive.entries()) {
        const auto normalized = normalize_path(entry.name);
        if (!starts_with(normalized, "media/levelsets/") ||
            !ends_with(normalized, ".dat.adm")) {
            continue;
        }
        const auto document = parse_adm(archive.read(entry));
        if (document.root.name != u"TILESET") {
            continue;
        }
        ++source_file_count_;
        const auto tileset = text_value(document.root, u"NAME");
        for (const auto& group : document.root.groups) {
            if (group.name != u"PIECE") {
                continue;
            }
            const auto* guid_property = property(group, u"GUID");
            if (guid_property == nullptr || guid_property->type != AdmValueType::integer64) {
                throw LevelSceneError("Level PIECE has no 64-bit GUID in " + entry.name);
            }
            LevelPiece piece;
            piece.guid = std::get<std::int64_t>(guid_property->value);
            piece.tileset = tileset;
            piece.name = text_value(group, u"NAME");
            piece.mesh_file = text_value(group, u"FILE");
            piece.collision_file = text_value(group, u"COLLISIONFILE");
            piece.tag = text_value(group, u"TAG");
            piece.prerender = bool_value(group, u"PRERENDER", false);
            piece.postrender = bool_value(group, u"POSTRENDER", false);
            piece.scalable = bool_value(group, u"SCALABLE", false);
            const auto index = pieces_.size();
            if (!by_guid_.emplace(piece.guid, index).second) {
                throw LevelSceneError("Duplicate level PIECE GUID");
            }
            pieces_.push_back(std::move(piece));
        }
    }
}

const LevelPiece* LevelsetCatalog::find(std::int64_t guid) const noexcept {
    const auto found = by_guid_.find(guid);
    return found == by_guid_.end() ? nullptr : &pieces_[found->second];
}

DungeonManifest LevelSceneLoader::load_dungeon(std::u16string_view data_file) const {
    const auto document = load_data_file(archive_, data_file, u"DUNGEON");
    DungeonManifest result;
    result.name = text_value(document.root, u"NAME");
    result.volatile_dungeon = bool_value(document.root, u"VOLATILE", false);
    for (const auto& group : document.root.groups) {
        if (group.name.size() < 6 || group.name.substr(0, 6) != u"STRATA") {
            continue;
        }
        DungeonStratum stratum;
        stratum.name = group.name;
        stratum.ruleset = text_value(group, u"RULESET");
        stratum.floors = int_value(group, u"FLOORS", 1);
        stratum.allow_portals = bool_value(group, u"ALLOW_PORTALS", true);
        stratum.allow_pet_return = bool_value(group, u"ALLOW_PET_RETURN", true);
        stratum.is_town = bool_value(group, u"IS_TOWN", false);
        if (stratum.ruleset.empty()) {
            throw LevelSceneError("Dungeon stratum has no RULESET");
        }
        result.strata.push_back(std::move(stratum));
    }
    if (result.name.empty() || result.strata.empty()) {
        throw LevelSceneError("Dungeon manifest is incomplete");
    }
    return result;
}

LevelRules LevelSceneLoader::load_rules(std::u16string_view data_file) const {
    LevelRules result;
    const auto document = load_data_file(archive_, data_file, u"LEVEL", &result.source_path);
    result.name = text_value(document.root, u"NAME");
    result.display_name = text_value(document.root, u"LEVELNAME");
    result.randomized = bool_value(document.root, u"RANDOMIZED", false);
    result.populate = bool_value(document.root, u"POPULATE", true);
    result.requires_exit = bool_value(document.root, u"REQUIRESEXIT", false);
    result.tile_basis = float_value(document.root, u"TILEBASIS", 1.0F);
    result.chunk_width_basis = float_value(document.root, u"CHUNKWIDTHBASIS", 1.0F);
    result.chunk_height_basis = float_value(document.root, u"CHUNKHEIGHTBASIS", 1.0F);
    result.minimum_chunks = int_value(document.root, u"MINCHUNKS", 0);
    result.maximum_chunks = int_value(document.root, u"MAXCHUNKS", 0);
    if (const auto* layout = child_group(document.root, u"LAYOUT")) {
        for (const auto& group : layout->groups) {
            if (group.name != u"CHUNK_RANDOM") {
                continue;
            }
            ChunkPlacement chunk;
            chunk.type = text_value(group, u"TYPE");
            chunk.x = float_value(group, u"X", 0.0F);
            chunk.y = float_value(group, u"Y", 0.0F);
            chunk.z = float_value(group, u"Z", 0.0F);
            result.chunks.push_back(std::move(chunk));
        }
    }
    for (const auto& group : document.root.groups) {
        if (group.name == u"CHUNK") {
            ChunkResource resource;
            resource.type = text_value(group, u"TYPE");
            resource.file = text_value(group, u"FILE");
            resource.weight = int_value(group, u"WEIGHT", 1);
            if (!resource.type.empty() && !resource.file.empty()) {
                result.chunk_resources.push_back(std::move(resource));
            }
            continue;
        }
        if (group.name != u"CHUNKTYPE") {
            continue;
        }
        ChunkType type;
        type.name = text_value(group, u"NAME");
        type.width = int_value(group, u"WIDTH", 1);
        type.height = int_value(group, u"HEIGHT", 1);
        type.maximum_appearance = int_value(group, u"MAX_APPEARANCE", 1);
        type.entrance = bool_value(group, u"ENTRANCE_CHUNK", false);
        type.exit = bool_value(group, u"EXIT_CHUNK", false);
        type.must_place = bool_value(group, u"MUST_PLACE", false);
        type.folder = text_value(group, u"FOLDER");
        for (const auto& child : group.groups) {
            if (child.name == u"EXIT") {
                type.exits.push_back({float_value(child, u"X", 0.0F),
                                      float_value(child, u"Y", 0.0F),
                                      float_value(child, u"Z", 0.0F)});
            } else if (child.name == u"INCLUSIVE_FILES") {
                for (const auto& value : child.properties) {
                    if (value.name == u"FILE" && is_text(value)) {
                        type.inclusive_files.push_back(std::get<std::u16string>(value.value));
                    }
                }
            }
        }
        result.chunk_types.push_back(std::move(type));
    }
    if (result.name.empty() || (result.chunks.empty() && result.chunk_types.empty() &&
                                result.chunk_resources.empty())) {
        throw LevelSceneError("Level rules are incomplete");
    }
    return result;
}

LayoutManifest LevelSceneLoader::load_layout(std::string_view compiled_path) const {
    const auto* entry = archive_.find_normalized(compiled_path);
    if (entry == nullptr) {
        throw LevelSceneError("Layout is absent from pak.zip: " + std::string(compiled_path));
    }
    const auto document = parse_adm(archive_.read(*entry));
    if (document.root.name != u"LAYOUT") {
        throw LevelSceneError("Layout file root is not LAYOUT: " + entry->name);
    }
    LayoutManifest result;
    result.source_path = entry->name;
    result.version = int_value(document.root, u"VERSION", 0);
    result.declared_count = unsigned_value(document.root, u"COUNT", 0);
    collect_layout_objects(document.root, result.objects, result.logic_groups);
    return result;
}

const AdmProperty* LayoutObject::find_property(
    const std::u16string& property_name) const noexcept {
    for (const auto& candidate : properties) {
        if (candidate.name == property_name) {
            return &candidate;
        }
    }
    return nullptr;
}

std::vector<std::string> LevelSceneLoader::layout_candidates(
    const LevelRules& rules, std::u16string_view chunk_type) const {
    const auto weighted = weighted_layout_candidates(rules, chunk_type);
    std::vector<std::string> result;
    result.reserve(weighted.size());
    for (const auto& candidate : weighted) {
        result.push_back(candidate.path);
    }
    return result;
}

std::vector<LayoutCandidate> LevelSceneLoader::weighted_layout_candidates(
    const LevelRules& rules, std::u16string_view chunk_type) const {
    const auto slash = rules.source_path.find_last_of('/');
    if (slash == std::string::npos) {
        throw LevelSceneError("Level rules path has no directory");
    }
    const auto rule_directory = normalize_path(rules.source_path.substr(0, slash + 1));
    std::vector<LayoutCandidate> result;
    for (const auto& resource : rules.chunk_resources) {
        if (resource.type != chunk_type) {
            continue;
        }
        const auto compiled = compiled_adm_path(resource.file);
        if (const auto* entry = archive_.find_normalized(compiled)) {
            result.push_back({entry->name, resource.weight});
        }
    }
    if (!result.empty()) {
        std::sort(result.begin(), result.end(), [](const auto& left, const auto& right) {
            return left.path < right.path;
        });
        std::vector<LayoutCandidate> combined;
        for (const auto& candidate : result) {
            if (!combined.empty() && combined.back().path == candidate.path) {
                combined.back().weight += candidate.weight;
            } else {
                combined.push_back(candidate);
            }
        }
        result = std::move(combined);
        return result;
    }

    const auto found_type = std::find_if(rules.chunk_types.begin(), rules.chunk_types.end(),
                                         [chunk_type](const auto& type) {
                                             return type.name == chunk_type;
                                         });
    const auto folder_name = found_type != rules.chunk_types.end() && !found_type->folder.empty()
                                 ? std::u16string_view(found_type->folder)
                                 : chunk_type;
    auto folder = compiled_adm_path(folder_name);
    folder.resize(folder.size() - 4U);
    auto prefix = rule_directory + normalize_path(folder);
    prefix += '/';

    for (const auto& entry : archive_.entries()) {
        const auto normalized = normalize_path(entry.name);
        if (starts_with(normalized, prefix) && ends_with(normalized, ".layout.adm")) {
            if (found_type != rules.chunk_types.end() && !found_type->inclusive_files.empty()) {
                const auto filename = normalized.substr(prefix.size(),
                    normalized.size() - prefix.size() - std::string_view(".layout.adm").size());
                const auto included = std::any_of(
                    found_type->inclusive_files.begin(), found_type->inclusive_files.end(),
                    [&filename](const auto& allowed) {
                        const std::string ascii(allowed.begin(), allowed.end());
                        return normalize_path(ascii) == filename;
                    });
                if (!included) {
                    continue;
                }
            }
            result.push_back({entry.name, 1});
        }
    }
    std::sort(result.begin(), result.end(), [](const auto& left, const auto& right) {
        return left.path < right.path;
    });
    return result;
}

FixedLevelScene LevelSceneLoader::load_fixed_scene(std::u16string_view dungeon_data_file,
                                                    std::size_t stratum_index) const {
    FixedLevelScene result;
    result.dungeon = load_dungeon(dungeon_data_file);
    if (stratum_index >= result.dungeon.strata.size()) {
        throw LevelSceneError("Dungeon stratum index is out of range");
    }
    result.rules = load_rules(result.dungeon.strata[stratum_index].ruleset);
    if (result.rules.randomized || result.rules.chunks.size() != 1) {
        throw LevelSceneError("Requested scene is not a single fixed layout");
    }
    const auto candidates = layout_candidates(result.rules, result.rules.chunks.front().type);
    if (candidates.size() != 1) {
        throw LevelSceneError("Fixed scene does not resolve to exactly one layout");
    }
    result.layout = load_layout(candidates.front());
    return result;
}

std::vector<LayoutWorldTransform> resolve_layout_world_transforms(const LayoutManifest& layout) {
    std::unordered_map<std::int64_t, std::size_t> by_id;
    by_id.reserve(layout.objects.size());
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        if (!by_id.emplace(layout.objects[index].id, index).second) {
            throw LevelSceneError("Layout contains duplicate object IDs");
        }
    }

    std::vector<LayoutWorldTransform> transforms(layout.objects.size());
    std::vector<std::uint8_t> states(layout.objects.size(), 0);
    std::function<void(std::size_t)> resolve = [&](std::size_t index) {
        if (states[index] == 2) {
            return;
        }
        if (states[index] == 1) {
            throw LevelSceneError("Layout object parent cycle detected");
        }
        states[index] = 1;
        const auto& object = layout.objects[index];
        LayoutWorldTransform local;
        local.position = {object.position_x.value_or(0.0F), object.position_y.value_or(0.0F),
                          object.position_z.value_or(0.0F)};
        local.scale = {object.scale_x, object.scale_y, object.scale_z};
        local.angle = object.angle;
        if (object.parent_id != -1) {
            const auto parent = by_id.find(object.parent_id);
            if (parent == by_id.end()) {
                throw LevelSceneError("Layout object references an absent parent");
            }
            resolve(parent->second);
            const auto& parent_transform = transforms[parent->second];
            const float scaled_x = parent_transform.scale[0] * local.position[0];
            const float scaled_z = parent_transform.scale[2] * local.position[2];
            const float radians = parent_transform.angle * kDegreesToRadians;
            const float cosine = std::cos(radians);
            const float sine = std::sin(radians);
            local.position[0] = parent_transform.position[0] +
                                scaled_x * cosine + scaled_z * sine;
            local.position[1] = parent_transform.position[1] +
                                parent_transform.scale[1] * local.position[1];
            local.position[2] = parent_transform.position[2] -
                                scaled_x * sine + scaled_z * cosine;
            for (std::size_t axis = 0; axis < 3; ++axis) {
                local.scale[axis] *= parent_transform.scale[axis];
            }
            local.angle += parent_transform.angle;
        }
        transforms[index] = local;
        states[index] = 2;
    };
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        resolve(index);
    }
    return transforms;
}

std::optional<LayoutWorldTransform> find_layout_world_transform(
    const LayoutManifest& layout, std::u16string_view descriptor) {
    const auto transforms = resolve_layout_world_transforms(layout);
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        if (layout.objects[index].descriptor == descriptor) {
            return transforms[index];
        }
    }
    return std::nullopt;
}

LayoutLinkExpansionStats expand_layout_links(const LevelSceneLoader& loader,
                                              LayoutManifest& layout,
                                              std::size_t maximum_depth) {
    struct PendingLink {
        std::size_t object_index = 0;
        std::size_t depth = 0;
    };

    std::unordered_map<std::int64_t, bool> existing_ids;
    existing_ids.reserve(layout.objects.size());
    std::int64_t next_id = 1;
    std::deque<PendingLink> pending;
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        const auto& object = layout.objects[index];
        if (!existing_ids.emplace(object.id, true).second) {
            throw LevelSceneError("Layout link expansion found a duplicate object ID");
        }
        if (object.id >= next_id) {
            if (object.id == std::numeric_limits<std::int64_t>::max()) {
                throw LevelSceneError("Layout object ID space is exhausted");
            }
            next_id = object.id + 1;
        }
        if (object.descriptor == u"Layout Link") {
            pending.push_back({index, 0});
        }
    }

    LayoutLinkExpansionStats stats;
    while (!pending.empty()) {
        const auto link = pending.front();
        pending.pop_front();
        if (link.depth >= maximum_depth) {
            throw LevelSceneError("Layout Link nesting exceeds the expansion limit");
        }
        const auto parent_id = layout.objects[link.object_index].id;
        const auto source_file = layout_link_file(layout.objects[link.object_index]);
        auto source = loader.load_layout(compiled_adm_path(source_file));

        std::unordered_map<std::int64_t, std::int64_t> ids;
        ids.reserve(source.objects.size());
        for (const auto& object : source.objects) {
            if (next_id == std::numeric_limits<std::int64_t>::max()) {
                throw LevelSceneError("Expanded layout has too many objects");
            }
            if (!ids.emplace(object.id, next_id++).second) {
                throw LevelSceneError("Linked layout has a duplicate object ID");
            }
        }

        const auto first_added = layout.objects.size();
        layout.objects.reserve(layout.objects.size() + source.objects.size());
        for (auto object : source.objects) {
            const auto original_id = object.id;
            object.id = remapped_id(ids, original_id);
            replace_int64_property(object, u"ID", object.id);
            if (object.parent_id == -1) {
                object.parent_id = parent_id;
            } else {
                object.parent_id = remapped_id(ids, object.parent_id);
                replace_int64_property(object, u"PARENTID", object.parent_id);
            }
            layout.objects.push_back(std::move(object));
        }

        layout.logic_groups.reserve(layout.logic_groups.size() +
                                    source.logic_groups.size());
        for (auto group : source.logic_groups) {
            group.object_id = remapped_id(ids, group.object_id);
            for (auto& node : group.nodes) {
                node.object_id = remapped_id(ids, node.object_id);
            }
            layout.logic_groups.push_back(std::move(group));
        }
        for (std::size_t index = first_added; index < layout.objects.size(); ++index) {
            if (layout.objects[index].descriptor == u"Layout Link") {
                pending.push_back({index, link.depth + 1U});
            }
        }

        const auto expanded_count = static_cast<std::uint64_t>(layout.declared_count) +
                                    source.declared_count;
        if (expanded_count > std::numeric_limits<std::uint32_t>::max()) {
            throw LevelSceneError("Expanded layout declared count is too large");
        }
        layout.declared_count = static_cast<std::uint32_t>(expanded_count);
        ++stats.links_expanded;
        stats.objects_added += source.objects.size();
        stats.logic_groups_added += source.logic_groups.size();
    }
    return stats;
}

} // namespace torchlight
