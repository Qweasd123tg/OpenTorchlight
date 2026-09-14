#include "torchlight/random_level.hpp"

#include "torchlight/randomizer.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace torchlight {
namespace {

class RandomLevelError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::string choose_layout(const LevelSceneLoader& loader, const LevelRules& rules,
                          const ChunkType& type, TorchlightRandom& random) {
    const auto layouts = loader.weighted_layout_candidates(rules, type.name);
    if (layouts.empty()) {
        throw RandomLevelError("Random chunk type has no layout resource");
    }
    std::vector<float> weights;
    weights.reserve(layouts.size());
    for (const auto& layout : layouts) {
        weights.push_back(static_cast<float>(std::max(0, layout.weight)));
    }
    return layouts[weighted_index(weights, random)].path;
}

struct Bounds {
    float minimum_x;
    float maximum_x;
    float minimum_y;
    float maximum_y;
    float minimum_z;
    float maximum_z;
};

Bounds core_bounds(const LevelRules& rules, const ChunkType& type,
                   const std::array<float, 3>& position) {
    const auto width_unit = rules.tile_basis * rules.chunk_width_basis - 0.1F;
    // The original intersectsChunks routine uses the +0x14 dimension for both
    // horizontal axes. Preserve that behavior, including its apparent neglect
    // of the separately loaded HEIGHT field.
    const auto height = rules.chunk_height_basis * static_cast<float>(type.width) *
                        rules.tile_basis;
    return {position[0] - 0.5F * width_unit,
            position[0] + (static_cast<float>(type.width) - 0.5F) * width_unit,
            position[1] - 1000.0F,
            position[1] + 1000.0F,
            position[2],
            position[2] + height - 0.1F};
}

bool overlaps(const Bounds& left, const Bounds& right) {
    return left.minimum_x <= right.maximum_x && left.maximum_x >= right.minimum_x &&
           left.minimum_y <= right.maximum_y && left.maximum_y >= right.minimum_y &&
           left.minimum_z <= right.maximum_z && left.maximum_z >= right.minimum_z;
}

bool intersects_existing(const LevelRules& rules, const GeneratedLevel& level,
                         std::size_t type_index, const std::array<float, 3>& position) {
    for (const auto& placed : level.chunks) {
        if (generated_chunks_intersect(rules, rules.chunk_types[type_index], position,
                                       rules.chunk_types[placed.type], placed.position)) {
            return true;
        }
    }
    return false;
}

float snap_to_chunk_grid(float value, float spacing) {
    return spacing > 0.0F ? std::round(value / spacing) * spacing : value;
}

std::array<float, 3> aligned_chunk_position(const LevelRules& rules,
                                            const std::array<float, 3>& source_exit,
                                            const ChunkExit& candidate_exit) {
    return {
        snap_to_chunk_grid(source_exit[0] - candidate_exit.x,
                           rules.tile_basis * rules.chunk_width_basis),
        source_exit[1] - candidate_exit.y,
        snap_to_chunk_grid(source_exit[2] - candidate_exit.z,
                           rules.tile_basis * rules.chunk_height_basis),
    };
}

bool types_can_connect(const LevelRules& rules, std::size_t source_type,
                       std::size_t candidate_type) {
    GeneratedLevel probe;
    GeneratedChunk source;
    source.type = source_type;
    source.matched_exits.resize(rules.chunk_types[source_type].exits.size());
    probe.chunks.push_back(std::move(source));
    for (std::size_t source_exit = 0;
         source_exit < rules.chunk_types[source_type].exits.size(); ++source_exit) {
        const auto source_position =
            generated_exit_position(rules, probe, 0, source_exit);
        for (const auto& candidate_exit : rules.chunk_types[candidate_type].exits) {
            const auto position = aligned_chunk_position(rules, source_position, candidate_exit);
            if (!intersects_existing(rules, probe, candidate_type, position)) {
                return true;
            }
        }
    }
    return false;
}

struct OpenExit {
    std::size_t chunk;
    std::size_t exit;
};

std::vector<OpenExit> open_exits(const GeneratedLevel& level) {
    std::vector<OpenExit> result;
    for (std::size_t chunk = 0; chunk < level.chunks.size(); ++chunk) {
        for (std::size_t exit = 0; exit < level.chunks[chunk].matched_exits.size(); ++exit) {
            if (!level.chunks[chunk].matched_exits[exit]) {
                result.push_back({chunk, exit});
            }
        }
    }
    return result;
}

struct PlacementOption {
    std::size_t source_chunk;
    std::size_t source_exit;
    std::size_t type;
    std::size_t candidate_exit;
    std::array<float, 3> position;
    std::vector<std::pair<OpenExit, std::size_t>> matches;
};

std::array<float, 3> exit_probe(const LevelRules& rules, const ChunkType& type,
                                const ChunkExit& exit, const std::array<float, 3>& position) {
    const auto width = rules.tile_basis * rules.chunk_width_basis;
    const auto height = rules.tile_basis * rules.chunk_height_basis;
    const std::array<float, 4> distances{
        std::fabs(exit.x + 0.5F * width),
        std::fabs(exit.x - (static_cast<float>(type.width) - 0.5F) * width),
        std::fabs(exit.z),
        std::fabs(exit.z - static_cast<float>(type.height) * height),
    };
    const auto edge = static_cast<std::size_t>(
        std::min_element(distances.begin(), distances.end()) - distances.begin());
    auto probe = std::array<float, 3>{position[0] + exit.x, position[1] + exit.y,
                                      position[2] + exit.z};
    const auto step = rules.tile_basis * 1.5F;
    if (edge == 0) {
        probe[0] -= step;
    } else if (edge == 1) {
        probe[0] += step;
    } else if (edge == 2) {
        probe[2] -= step;
    } else {
        probe[2] += step;
    }
    return probe;
}

bool contains(const Bounds& bounds, const std::array<float, 3>& point) {
    return point[0] >= bounds.minimum_x && point[0] <= bounds.maximum_x &&
           point[1] >= bounds.minimum_y && point[1] <= bounds.maximum_y &&
           point[2] >= bounds.minimum_z && point[2] <= bounds.maximum_z;
}

bool collect_exit_matches(const LevelRules& rules, const GeneratedLevel& level,
                          std::size_t type_index, const std::array<float, 3>& position,
                          std::vector<std::pair<OpenExit, std::size_t>>& matches) {
    const auto& type = rules.chunk_types[type_index];
    const auto tolerance = rules.tile_basis * 2.0F;
    for (std::size_t candidate_exit = 0; candidate_exit < type.exits.size(); ++candidate_exit) {
        const auto probe = exit_probe(rules, type, type.exits[candidate_exit], position);
        const std::array<float, 3> world{
            position[0] + type.exits[candidate_exit].x,
            position[1] + type.exits[candidate_exit].y,
            position[2] + type.exits[candidate_exit].z,
        };
        bool points_into_chunk = false;
        bool matched = false;
        for (std::size_t chunk = 0; chunk < level.chunks.size(); ++chunk) {
            const auto& placed = level.chunks[chunk];
            if (!contains(core_bounds(rules, rules.chunk_types[placed.type], placed.position),
                          probe)) {
                continue;
            }
            points_into_chunk = true;
            bool chunk_matched = false;
            const auto& existing_type = rules.chunk_types[placed.type];
            for (std::size_t existing_exit = 0; existing_exit < existing_type.exits.size();
                 ++existing_exit) {
                if (placed.matched_exits[existing_exit]) {
                    continue;
                }
                const auto existing = generated_exit_position(rules, level, chunk, existing_exit);
                const auto dx = world[0] - existing[0];
                const auto dy = world[1] - existing[1];
                const auto dz = world[2] - existing[2];
                if (std::sqrt(dx * dx + dy * dy + dz * dz) < tolerance) {
                    matches.push_back({OpenExit{chunk, existing_exit}, candidate_exit});
                    matched = true;
                    chunk_matched = true;
                    break;
                }
            }
            if (!chunk_matched) {
                return false;
            }
        }
        if (points_into_chunk && !matched) {
            return false;
        }
    }
    std::vector<bool> used_candidate_exits(type.exits.size(), false);
    for (const auto& match : matches) {
        if (used_candidate_exits[match.second]) {
            return false;
        }
        used_candidate_exits[match.second] = true;
    }
    return true;
}

std::vector<PlacementOption> placement_options(
    const LevelRules& rules, const GeneratedLevel& level,
    const std::vector<std::size_t>& eligible_types,
    const std::vector<std::size_t>& appearances) {
    std::vector<PlacementOption> result;
    for (const auto source : open_exits(level)) {
        const auto source_position =
            generated_exit_position(rules, level, source.chunk, source.exit);
        for (const auto type_index : eligible_types) {
            const auto& type = rules.chunk_types[type_index];
            if (type.maximum_appearance >= 0 &&
                appearances[type_index] >= static_cast<std::size_t>(type.maximum_appearance)) {
                continue;
            }
            for (std::size_t candidate_exit = 0; candidate_exit < type.exits.size();
                 ++candidate_exit) {
                const auto& exit = type.exits[candidate_exit];
                const auto position = aligned_chunk_position(rules, source_position, exit);
                if (!intersects_existing(rules, level, type_index, position)) {
                    std::vector<std::pair<OpenExit, std::size_t>> matches;
                    if (!collect_exit_matches(rules, level, type_index, position, matches)) {
                        continue;
                    }
                    const auto selected_source = std::find_if(
                        matches.begin(), matches.end(), [&](const auto& match) {
                            return match.first.chunk == source.chunk &&
                                   match.first.exit == source.exit &&
                                   match.second == candidate_exit;
                        });
                    if (selected_source == matches.end()) {
                        continue;
                    }
                    result.push_back({source.chunk, source.exit, type_index, candidate_exit,
                                      position, std::move(matches)});
                }
            }
        }
    }
    return result;
}

void apply_placement(const LevelRules& rules, GeneratedLevel& level,
                     std::vector<std::size_t>& appearances, const PlacementOption& option) {
    GeneratedChunk placed;
    placed.type = option.type;
    placed.position = option.position;
    placed.matched_exits.resize(rules.chunk_types[option.type].exits.size());
    const auto placed_index = level.chunks.size();
    for (const auto& match : option.matches) {
        placed.matched_exits[match.second] =
            GeneratedExitMatch{match.first.chunk, match.first.exit};
        level.chunks[match.first.chunk].matched_exits[match.first.exit] =
            GeneratedExitMatch{placed_index, match.second};
    }
    level.chunks.push_back(std::move(placed));
    ++appearances[option.type];
}

void undo_placement(GeneratedLevel& level, std::vector<std::size_t>& appearances) {
    const auto removed_index = level.chunks.size() - 1U;
    const auto removed_type = level.chunks.back().type;
    for (const auto& match : level.chunks.back().matched_exits) {
        if (match && match->chunk < removed_index) {
            level.chunks[match->chunk].matched_exits[match->exit].reset();
        }
    }
    level.chunks.pop_back();
    --appearances[removed_type];
}

void replace_int64_property(LayoutObject& object, const char16_t* name,
                            std::int64_t value) {
    for (auto& property : object.properties) {
        if (property.name != name) {
            continue;
        }
        if (property.type != AdmValueType::integer64) {
            throw RandomLevelError("Generated layout identity property has the wrong type");
        }
        property.value = value;
        return;
    }
}

void replace_position_property(LayoutObject& object, const char16_t* name, float value) {
    for (auto& property : object.properties) {
        if (property.name != name) {
            continue;
        }
        if (property.type != AdmValueType::floating) {
            throw RandomLevelError("Generated layout position property has the wrong type");
        }
        property.value = value;
        return;
    }
}

std::int64_t mapped_object_id(
    const std::unordered_map<std::int64_t, std::int64_t>& object_ids,
    std::int64_t original_id) {
    const auto found = object_ids.find(original_id);
    if (found == object_ids.end()) {
        throw RandomLevelError("Generated layout graph references an absent object");
    }
    return found->second;
}

} // namespace

bool generated_chunks_intersect(const LevelRules& rules, const ChunkType& left_type,
                                const std::array<float, 3>& left_position,
                                const ChunkType& right_type,
                                const std::array<float, 3>& right_position) noexcept {
    return overlaps(core_bounds(rules, left_type, left_position),
                    core_bounds(rules, right_type, right_position));
}

std::array<float, 3> generated_exit_position(const LevelRules& rules,
                                              const GeneratedLevel& level,
                                              std::size_t chunk, std::size_t exit) {
    if (chunk >= level.chunks.size() || level.chunks[chunk].type >= rules.chunk_types.size() ||
        exit >= rules.chunk_types[level.chunks[chunk].type].exits.size()) {
        throw RandomLevelError("Generated exit index is out of range");
    }
    const auto& placed = level.chunks[chunk];
    const auto& local = rules.chunk_types[placed.type].exits[exit];
    return {placed.position[0] + local.x, placed.position[1] + local.y,
            placed.position[2] + local.z};
}

GeneratedLevelLayout compose_generated_level_layout(const LevelSceneLoader& loader,
                                                     const GeneratedLevel& level) {
    GeneratedLevelLayout result;
    result.layout.source_path = "generated-level:" + std::to_string(level.seed);
    std::int64_t next_object_id = 1;
    std::uint64_t declared_count = 0;

    for (std::size_t chunk_index = 0; chunk_index < level.chunks.size(); ++chunk_index) {
        const auto& chunk = level.chunks[chunk_index];
        if (chunk.layout_path.empty()) {
            throw RandomLevelError("Generated chunk has no layout path");
        }
        auto source = loader.load_layout(chunk.layout_path);
        result.layout.version = std::max(result.layout.version, source.version);
        declared_count += source.declared_count;
        if (declared_count > std::numeric_limits<std::uint32_t>::max()) {
            throw RandomLevelError("Generated layout declared count exceeds 32-bit range");
        }

        std::unordered_map<std::int64_t, std::int64_t> object_ids;
        object_ids.reserve(source.objects.size());
        for (const auto& object : source.objects) {
            if (next_object_id == std::numeric_limits<std::int64_t>::max()) {
                throw RandomLevelError("Generated layout has too many objects");
            }
            if (!object_ids.emplace(object.id, next_object_id++).second) {
                throw RandomLevelError("Generated chunk layout has a duplicate object ID");
            }
        }

        result.layout.objects.reserve(result.layout.objects.size() + source.objects.size());
        result.object_origins.reserve(result.object_origins.size() + source.objects.size());
        for (auto object : source.objects) {
            const auto original_id = object.id;
            object.id = mapped_object_id(object_ids, original_id);
            replace_int64_property(object, u"ID", object.id);
            if (object.parent_id == -1) {
                object.position_x = object.position_x.value_or(0.0F) + chunk.position[0];
                object.position_y = object.position_y.value_or(0.0F) + chunk.position[1];
                object.position_z = object.position_z.value_or(0.0F) + chunk.position[2];
                replace_position_property(object, u"POSITIONX", *object.position_x);
                replace_position_property(object, u"POSITIONY", *object.position_y);
                replace_position_property(object, u"POSITIONZ", *object.position_z);
            } else {
                object.parent_id = mapped_object_id(object_ids, object.parent_id);
                replace_int64_property(object, u"PARENTID", object.parent_id);
            }
            result.layout.objects.push_back(std::move(object));
            result.object_origins.push_back({chunk_index, original_id});
        }

        result.layout.logic_groups.reserve(result.layout.logic_groups.size() +
                                           source.logic_groups.size());
        for (auto group : source.logic_groups) {
            group.object_id = mapped_object_id(object_ids, group.object_id);
            for (auto& node : group.nodes) {
                node.object_id = mapped_object_id(object_ids, node.object_id);
            }
            result.layout.logic_groups.push_back(std::move(group));
        }
    }
    result.layout.declared_count = static_cast<std::uint32_t>(declared_count);
    return result;
}

GeneratedLevel RandomLevelGenerator::generate(const LevelRules& rules, std::uint32_t seed) const {
    if (!rules.randomized) {
        throw RandomLevelError("Random generator requires a randomized ruleset");
    }
    if (rules.chunk_types.empty()) {
        throw RandomLevelError("Randomized ruleset has no chunk types");
    }
    if (rules.maximum_chunks < rules.minimum_chunks || rules.minimum_chunks < 0) {
        throw RandomLevelError("Randomized ruleset has an invalid chunk range");
    }
    TorchlightRandom random(seed);
    GeneratedLevel result;
    result.seed = seed;
    result.requested_middle_chunks =
        random.integer_between(rules.minimum_chunks, rules.maximum_chunks);

    std::vector<std::size_t> entrance_types;
    std::vector<std::size_t> middle_types;
    std::vector<std::size_t> exit_types;
    std::vector<std::size_t> must_place_types;
    for (std::size_t index = 0; index < rules.chunk_types.size(); ++index) {
        const auto& type = rules.chunk_types[index];
        if (type.entrance) {
            entrance_types.push_back(index);
        } else if (type.exit) {
            exit_types.push_back(index);
        } else {
            middle_types.push_back(index);
            if (type.must_place) {
                must_place_types.push_back(index);
            }
        }
    }
    if (!must_place_types.empty() && result.requested_middle_chunks > 0) {
        entrance_types.erase(
            std::remove_if(entrance_types.begin(), entrance_types.end(),
                           [&rules, &must_place_types](const auto entrance) {
                               return std::none_of(
                                   must_place_types.begin(), must_place_types.end(),
                                   [&rules, entrance](const auto required) {
                                       return types_can_connect(rules, entrance, required);
                                   });
                           }),
            entrance_types.end());
    }
    std::vector<std::size_t> appearances(rules.chunk_types.size(), 0U);
    std::function<bool(std::int32_t)> build = [&](std::int32_t placed_middle) {
        const bool placing_exit = placed_middle == result.requested_middle_chunks;
        if (placing_exit && !rules.requires_exit) {
            return true;
        }
        const std::vector<std::size_t>* eligible = nullptr;
        std::vector<std::size_t> required;
        if (placing_exit) {
            eligible = &exit_types;
        } else if (placed_middle < static_cast<std::int32_t>(must_place_types.size())) {
            required.push_back(must_place_types[static_cast<std::size_t>(placed_middle)]);
            eligible = &required;
        } else {
            eligible = &middle_types;
        }
        auto options = placement_options(rules, result, *eligible, appearances);
        while (!options.empty() && result.placement_attempts < 1000U) {
            const auto selected = static_cast<std::size_t>(random.integer_between(
                0, static_cast<std::int32_t>(options.size() - 1U)));
            const auto option = options[selected];
            options.erase(options.begin() + static_cast<std::ptrdiff_t>(selected));
            ++result.placement_attempts;
            apply_placement(rules, result, appearances, option);
            if ((placing_exit && rules.requires_exit) || build(placed_middle + 1)) {
                return true;
            }
            undo_placement(result, appearances);
        }
        return false;
    };

    auto remaining_entrances = entrance_types;
    bool built = false;
    while (!remaining_entrances.empty() && result.placement_attempts < 1000U) {
        const auto selected = static_cast<std::size_t>(random.integer_between(
            0, static_cast<std::int32_t>(remaining_entrances.size() - 1U)));
        const auto entrance = remaining_entrances[selected];
        remaining_entrances.erase(remaining_entrances.begin() +
                                  static_cast<std::ptrdiff_t>(selected));
        result.chunks.clear();
        std::fill(appearances.begin(), appearances.end(), 0U);
        GeneratedChunk first;
        first.type = entrance;
        first.matched_exits.resize(rules.chunk_types[entrance].exits.size());
        result.chunks.push_back(std::move(first));
        ++appearances[entrance];
        built = build(0);
        if (built) {
            break;
        }
    }
    if (!built) {
        throw RandomLevelError("Could not build a connected random layout within 1000 attempts");
    }
    for (auto& chunk : result.chunks) {
        chunk.layout_path = choose_layout(loader_, rules, rules.chunk_types[chunk.type], random);
    }
    return result;
}

} // namespace torchlight
