#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/random_level.hpp"

#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

bool same_level(const torchlight::GeneratedLevel& left,
                const torchlight::GeneratedLevel& right) {
    if (left.requested_middle_chunks != right.requested_middle_chunks ||
        left.chunks.size() != right.chunks.size()) {
        return false;
    }
    for (std::size_t index = 0; index < left.chunks.size(); ++index) {
        const auto& a = left.chunks[index];
        const auto& b = right.chunks[index];
        if (a.type != b.type || a.layout_path != b.layout_path || a.position != b.position ||
            a.matched_exits.size() != b.matched_exits.size()) {
            return false;
        }
        for (std::size_t exit = 0; exit < a.matched_exits.size(); ++exit) {
            if (a.matched_exits[exit].has_value() != b.matched_exits[exit].has_value()) {
                return false;
            }
            if (a.matched_exits[exit] &&
                (a.matched_exits[exit]->chunk != b.matched_exits[exit]->chunk ||
                 a.matched_exits[exit]->exit != b.matched_exits[exit]->exit)) {
                return false;
            }
        }
    }
    return true;
}

void verify(const torchlight::LevelSceneLoader& loader, const torchlight::LevelRules& rules,
            const torchlight::GeneratedLevel& level,
            std::unordered_set<std::string>& checked_layouts) {
    require(!level.chunks.empty(), "generated level is empty");
    require(rules.chunk_types[level.chunks.front().type].entrance,
            "generated level does not start with an entrance");
    const auto expected = 1U + static_cast<std::size_t>(level.requested_middle_chunks) +
                          static_cast<std::size_t>(rules.requires_exit);
    require(level.chunks.size() == expected, "generated level has the wrong chunk count");
    std::map<std::size_t, std::size_t> appearances;
    std::size_t matched_ends = 0;
    std::size_t exit_chunks = 0;
    for (std::size_t chunk = 0; chunk < level.chunks.size(); ++chunk) {
        const auto& placed = level.chunks[chunk];
        require(placed.type < rules.chunk_types.size(), "generated chunk type is out of range");
        const auto& type = rules.chunk_types[placed.type];
        require(!placed.layout_path.empty(), "generated chunk has no layout");
        if (checked_layouts.insert(placed.layout_path).second) {
            require(!loader.load_layout(placed.layout_path).objects.empty(),
                    "generated chunk layout is empty");
        }
        require(placed.matched_exits.size() == type.exits.size(),
                "generated chunk exit state has the wrong size");
        ++appearances[placed.type];
        exit_chunks += static_cast<std::size_t>(type.exit);
        for (std::size_t exit = 0; exit < placed.matched_exits.size(); ++exit) {
            if (!placed.matched_exits[exit]) {
                continue;
            }
            ++matched_ends;
            const auto match = *placed.matched_exits[exit];
            require(match.chunk < level.chunks.size(), "matched chunk index is out of range");
            require(match.exit < level.chunks[match.chunk].matched_exits.size(),
                    "matched exit index is out of range");
            const auto reciprocal = level.chunks[match.chunk].matched_exits[match.exit];
            require(reciprocal && reciprocal->chunk == chunk && reciprocal->exit == exit,
                    "generated exit match is not reciprocal");
            const auto left = torchlight::generated_exit_position(rules, level, chunk, exit);
            const auto right =
                torchlight::generated_exit_position(rules, level, match.chunk, match.exit);
            const auto dx = left[0] - right[0];
            const auto dy = left[1] - right[1];
            const auto dz = left[2] - right[2];
            require(std::sqrt(dx * dx + dy * dy + dz * dz) < rules.tile_basis * 2.0F,
                    "matched generated exits exceed the original distance tolerance");
        }
    }
    require(matched_ends >= (level.chunks.size() - 1U) * 2U && matched_ends % 2U == 0,
            "generated chunks are not connected by reciprocal exits");
    require(exit_chunks == static_cast<std::size_t>(rules.requires_exit),
            "generated level has the wrong exit count");
    for (const auto& [type_index, count] : appearances) {
        const auto maximum = rules.chunk_types[type_index].maximum_appearance;
        require(maximum < 0 || count <= static_cast<std::size_t>(maximum),
                "generated chunk exceeds MAX_APPEARANCE");
    }
    for (std::size_t index = 0; index < rules.chunk_types.size(); ++index) {
        if (rules.chunk_types[index].must_place &&
            level.requested_middle_chunks > 0) {
            require(appearances[index] == 1, "required chunk type was not placed");
        }
    }
    for (std::size_t left = 0; left < level.chunks.size(); ++left) {
        const auto& left_chunk = level.chunks[left];
        const auto& left_type = rules.chunk_types[left_chunk.type];
        const auto width_unit = rules.tile_basis * rules.chunk_width_basis - 0.1F;
        const auto left_height = static_cast<float>(left_type.width) * rules.tile_basis *
                                 rules.chunk_height_basis;
        for (std::size_t right = left + 1; right < level.chunks.size(); ++right) {
            const auto& right_chunk = level.chunks[right];
            const auto& right_type = rules.chunk_types[right_chunk.type];
            const auto right_height = static_cast<float>(right_type.width) * rules.tile_basis *
                                      rules.chunk_height_basis;
            const bool x_overlap =
                left_chunk.position[0] - 0.5F * width_unit <
                    right_chunk.position[0] +
                        (static_cast<float>(right_type.width) - 0.5F) * width_unit - 0.001F &&
                left_chunk.position[0] +
                        (static_cast<float>(left_type.width) - 0.5F) * width_unit >
                    right_chunk.position[0] - 0.5F * width_unit + 0.001F;
            const bool z_overlap = left_chunk.position[2] <
                                       right_chunk.position[2] + right_height - 0.101F &&
                                   left_chunk.position[2] + left_height - 0.1F >
                                       right_chunk.position[2] + 0.001F;
            require(!(x_overlap && z_overlap), "generated chunk collision cores overlap");
        }
    }
}

void verify_composed_layout(const torchlight::LevelSceneLoader& loader,
                            const torchlight::GeneratedLevel& level) {
    const auto composed = torchlight::compose_generated_level_layout(loader, level);
    require(composed.layout.objects.size() == composed.object_origins.size(),
            "composed layout lost object origins");
    std::size_t expected_objects = 0;
    std::size_t expected_groups = 0;
    std::uint64_t expected_declared = 0;
    for (const auto& chunk : level.chunks) {
        const auto source = loader.load_layout(chunk.layout_path);
        try {
            torchlight::LogicRuntime source_runtime(source, level.seed);
            source_runtime.activate_level();
        } catch (const std::exception& error) {
            throw std::runtime_error(chunk.layout_path + ": " + error.what());
        }
        expected_objects += source.objects.size();
        expected_groups += source.logic_groups.size();
        expected_declared += source.declared_count;
    }
    require(composed.layout.objects.size() == expected_objects,
            "composed layout has the wrong object count");
    require(composed.layout.logic_groups.size() == expected_groups,
            "composed layout has the wrong graph count");
    require(composed.layout.declared_count == expected_declared,
            "composed layout has the wrong declared count");

    std::unordered_set<std::int64_t> runtime_ids;
    for (std::size_t index = 0; index < composed.layout.objects.size(); ++index) {
        require(runtime_ids.insert(composed.layout.objects[index].id).second,
                "composed layout has a duplicate runtime object ID");
        require(composed.object_origins[index].chunk < level.chunks.size(),
                "composed layout has an invalid object origin");
    }
    torchlight::LogicRuntime runtime(composed.layout, level.seed);
    runtime.activate_level();
}

void verify_repeated_chunk_layout(const torchlight::LevelSceneLoader& loader,
                                  const torchlight::GeneratedChunk& source_chunk,
                                  std::uint32_t seed) {
    torchlight::GeneratedLevel repeated;
    repeated.seed = seed;
    repeated.chunks.push_back(source_chunk);
    repeated.chunks.push_back(source_chunk);
    repeated.chunks[1].position[0] += 1000.0F;
    repeated.chunks[1].position[2] -= 500.0F;
    const auto source = loader.load_layout(source_chunk.layout_path);
    const auto composed = torchlight::compose_generated_level_layout(loader, repeated);
    require(composed.layout.objects.size() == source.objects.size() * 2U,
            "repeated chunk composition lost objects");
    require(!source.objects.empty(), "repeated chunk source is empty");
    const auto transforms = torchlight::resolve_layout_world_transforms(composed.layout);
    const auto second = source.objects.size();
    require(std::fabs(transforms[second].position[0] - transforms[0].position[0] - 1000.0F) <
                    0.001F &&
                std::fabs(transforms[second].position[2] - transforms[0].position[2] + 500.0F) <
                    0.001F,
            "repeated chunk composition applied the wrong world offset");
    torchlight::LogicRuntime runtime(composed.layout, seed);
    runtime.activate_level();
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: random_level_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const torchlight::LevelSceneLoader loader(archive);
        const torchlight::RandomLevelGenerator generator(loader);
        const auto dungeon = loader.load_dungeon(u"media/dungeons/MAIN.DAT");
        std::set<std::string> tested_rules;
        std::size_t generated_levels = 0;
        std::size_t generated_chunks = 0;
        std::size_t composed_levels = 0;
        bool repeated_chunk_checked = false;
        std::unordered_set<std::string> checked_layouts;
        for (const auto& stratum : dungeon.strata) {
            const auto rules = loader.load_rules(stratum.ruleset);
            if (!rules.randomized || !tested_rules.insert(rules.source_path).second) {
                continue;
            }
            for (std::uint32_t seed = 1; seed <= 16; ++seed) {
                torchlight::GeneratedLevel level;
                try {
                    level = generator.generate(rules, seed);
                } catch (const std::exception& error) {
                    throw std::runtime_error(rules.source_path + " seed=" +
                                             std::to_string(seed) + ": " + error.what());
                }
                verify(loader, rules, level, checked_layouts);
                require(same_level(level, generator.generate(rules, seed)),
                        "same seed did not reproduce the generated level");
                if (seed == 1) {
                    verify_composed_layout(loader, level);
                    ++composed_levels;
                    if (!repeated_chunk_checked) {
                        verify_repeated_chunk_layout(loader, level.chunks.front(), seed);
                        repeated_chunk_checked = true;
                    }
                }
                ++generated_levels;
                generated_chunks += level.chunks.size();
            }
        }
        require(tested_rules.size() == 12, "unexpected unique randomized ruleset count");
        require(composed_levels == tested_rules.size(),
                "not all randomized rulesets produced a runtime layout");
        std::cout << "PASS: generated " << generated_levels << " deterministic levels with "
                  << generated_chunks << " placed chunks across " << tested_rules.size()
                  << " campaign rulesets; composed " << composed_levels
                  << " runtime layouts\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
