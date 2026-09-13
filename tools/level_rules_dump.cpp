#include "torchlight/level_scene.hpp"
#include "torchlight/pak_archive.hpp"

#include <iostream>
#include <string>

namespace {
std::string narrow(const std::u16string& value) {
    return std::string(value.begin(), value.end());
}
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: torchlight_level_rules_dump pak.zip dungeon.dat\n";
        return 2;
    }
    try {
        const torchlight::PakArchive archive(argv[1]);
        const torchlight::LevelSceneLoader loader(archive);
        const std::u16string dungeon_path(argv[2], argv[2] + std::char_traits<char>::length(argv[2]));
        const auto dungeon = loader.load_dungeon(dungeon_path);
        for (std::size_t stratum = 0; stratum < dungeon.strata.size(); ++stratum) {
            const auto rules = loader.load_rules(dungeon.strata[stratum].ruleset);
            std::cout << "stratum=" << stratum << " rules=" << rules.source_path
                      << " random=" << rules.randomized << " chunks=" << rules.minimum_chunks
                      << ".." << rules.maximum_chunks << " tile=" << rules.tile_basis
                      << " basis=" << rules.chunk_width_basis << 'x' << rules.chunk_height_basis
                      << " types=" << rules.chunk_types.size() << '\n';
            for (std::size_t index = 0; index < rules.chunk_types.size(); ++index) {
                const auto& type = rules.chunk_types[index];
                std::cout << "  [" << index << "] " << narrow(type.name) << " size=" << type.width
                          << 'x' << type.height << " max=" << type.maximum_appearance
                          << " entrance=" << type.entrance << " exit=" << type.exit
                          << " must=" << type.must_place << " exits=" << type.exits.size()
                          << " candidates=" << loader.layout_candidates(rules, type.name).size()
                          << '\n';
                for (std::size_t exit = 0; exit < type.exits.size(); ++exit) {
                    const auto& point = type.exits[exit];
                    std::cout << "      exit[" << exit << "]=" << point.x << ',' << point.y << ','
                              << point.z << '\n';
                }
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
