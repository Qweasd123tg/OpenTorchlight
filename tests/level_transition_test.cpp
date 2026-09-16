#include "torchlight/level_scene.hpp"
#include "torchlight/level_transition.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/random_level.hpp"

#include <cmath>
#include <iostream>
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
            std::cerr << "usage: level_transition_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const torchlight::LevelSceneLoader loader(archive);
        const auto town = loader.load_dungeon(u"media/dungeons/TOWN.DAT");
        const auto main = loader.load_dungeon(u"media/dungeons/MAIN.DAT");
        require(main.parent_dungeon == u"Town", "MAIN PARENT_DUNGEON resource was not retained");
        require(torchlight::select_dungeon_floor(town, 99).depth == 0,
                "town did not normalize to depth zero");
        require(torchlight::select_dungeon_floor(main, 0).stratum_index == 0 &&
                    torchlight::select_dungeon_floor(main, 1).depth == 1,
                "main entrance did not normalize to floor one");
        require(torchlight::select_dungeon_floor(main, 4).stratum_index == 3 &&
                    torchlight::select_dungeon_floor(main, 8).stratum_index == 7 &&
                    torchlight::select_dungeon_floor(main, 9).stratum_index == 8,
                "main absolute depths selected the wrong strata");

        torchlight::LevelTransitionState state({u"Town", 0});
        torchlight::WarpRequest enter_main;
        enter_main.dungeon_name = u"Main";
        enter_main.level_delta = 0;
        auto destination = state.resolve(enter_main);
        auto floor = torchlight::select_dungeon_floor(main, destination.depth);
        destination.depth = floor.depth;
        require(destination.dungeon_name == u"Main" && destination.depth == 1,
                "town-to-main warp did not select the first floor");
        state.commit(destination);

        torchlight::WarpRequest descend;
        descend.level_delta = 1;
        destination = state.resolve(descend);
        floor = torchlight::select_dungeon_floor(main, destination.depth);
        destination.depth = floor.depth;
        require(destination.depth == 2 && floor.stratum_index == 1,
                "relative exit did not select the next main floor");
        state.commit(destination);

        torchlight::WarpRequest absolute;
        absolute.absolute_level = 8;
        destination = state.resolve(absolute);
        floor = torchlight::select_dungeon_floor(main, destination.depth);
        require(destination.depth == 8 && floor.stratum_index == 7,
                "absolute warp did not override the relative depth");

        torchlight::WarpRequest return_to_town;
        return_to_town.dungeon_name = u"TOWN";
        return_to_town.level_delta = 0;
        destination = state.resolve(return_to_town);
        destination.depth = torchlight::select_dungeon_floor(town, destination.depth).depth;
        state.commit(destination);
        require(state.current().depth == 0 && state.last_dungeon() &&
                    state.last_dungeon()->depth == 2,
                "changing dungeon did not preserve the previous address");

        torchlight::WarpRequest return_last;
        return_last.dungeon_name = u"LASTDUNGEON";
        return_last.level_delta = 1;
        destination = state.resolve(return_last);
        require(destination.dungeon_name == u"Main" && destination.depth == 2,
                "LASTDUNGEON did not ignore delta and restore the recorded floor");

        bool rejected = false;
        try {
            static_cast<void>(torchlight::select_dungeon_floor(main, 36));
        } catch (const std::exception&) {
            rejected = true;
        }
        require(rejected, "out-of-range main depth was accepted");

        const auto build_main_layout = [&](std::int32_t depth, std::uint32_t seed) {
            const auto selected = torchlight::select_dungeon_floor(main, depth);
            const auto rules = loader.load_rules(main.strata[selected.stratum_index].ruleset);
            const torchlight::RandomLevelGenerator generator(loader);
            const auto generated = generator.generate(rules, seed);
            auto composed = torchlight::compose_generated_level_layout(loader, generated);
            static_cast<void>(torchlight::expand_layout_links(loader, composed.layout));
            return composed.layout;
        };
        const auto floor_two_layout = build_main_layout(2, 0x9e377993U);
        torchlight::WarpRequest down;
        down.level_delta = 1;
        const auto floor_two_arrival = torchlight::find_same_dungeon_warp_arrival(
            floor_two_layout, {{main.name, 1}, {main.name, 2}, down});
        require(floor_two_arrival.has_value() &&
                    std::isfinite(floor_two_arrival->position[0]) &&
                    std::isfinite(floor_two_arrival->position[2]),
                "real second floor has no reverse Warper for floor one");

        const auto floor_one_layout = build_main_layout(1, 42U);
        torchlight::WarpRequest up;
        up.level_delta = -1;
        const auto floor_one_arrival = torchlight::find_same_dungeon_warp_arrival(
            floor_one_layout, {{main.name, 2}, {main.name, 1}, up});
        require(floor_one_arrival.has_value() &&
                    std::isfinite(floor_one_arrival->angle_degrees),
                "real first floor has no reverse Warper for floor two");

        std::cout << "PASS: resolved town, relative, absolute and LASTDUNGEON warps\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
