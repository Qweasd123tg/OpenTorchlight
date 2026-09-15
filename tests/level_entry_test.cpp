#include "torchlight/level_transition.hpp"
#include "torchlight/player.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {

std::size_t checks = 0;

void require(bool condition, const char* message) {
    ++checks;
    if (!condition) {
        throw std::runtime_error(message);
    }
}

torchlight::AdmProperty text(const char16_t* name, std::u16string value) {
    return {0, name, torchlight::AdmValueType::string, std::move(value)};
}

torchlight::LayoutObject node(std::int64_t id, const char16_t* type) {
    torchlight::LayoutObject result;
    result.id = id;
    result.descriptor = u"Property Node";
    result.name = u"Name is not the node type";
    result.position_x = static_cast<float>(id * 10);
    result.position_z = static_cast<float>(id * 20);
    result.properties.push_back(text(u"TYPE", type));
    return result;
}

torchlight::LevelEntryRequest request(std::int32_t delta) {
    torchlight::LevelEntryRequest result;
    result.source = {u"Main", 2};
    result.destination = {u"MAIN", delta > 0 ? 3 : 1};
    result.warp.level_delta = delta;
    return result;
}

void expect(const torchlight::LayoutManifest& layout,
            const torchlight::LevelEntryRequest& entry,
            torchlight::LevelArrivalKind kind,
            std::optional<std::int64_t> id) {
    const auto actual = torchlight::find_same_dungeon_level_arrival(layout, entry);
    require(actual && actual->kind == kind && actual->marker_id == id,
            "incorrect level arrival kind or marker ID");
}

void check_sequences() {
    // Independent whole-sequence oracle: find last preferred / first secondary
    // node rather than repeating the implementation's forward state machine.
    const char16_t* types[] = {u"Editor Player Start", u"Entrance", u"Exit",
                              u"Player Start"};
    std::size_t sequence_count = 0;
    std::size_t count = 1;
    for (std::size_t length = 0; length <= 5; ++length) {
        for (std::size_t code = 0; code < count; ++code) {
            torchlight::LayoutManifest layout;
            auto remaining = code;
            std::optional<std::int64_t> first_entrance, last_entrance, last_exit, last_start;
            for (std::size_t i = 0; i < length; ++i) {
                const auto type = remaining % 4;
                remaining /= 4;
                const auto id = static_cast<std::int64_t>(i + 1);
                layout.objects.push_back(node(id, types[type]));
                if (type == 1) {
                    if (!first_entrance) {
                        first_entrance = id;
                    }
                    last_entrance = id;
                } else if (type == 2) {
                    last_exit = id;
                } else if (type == 3) {
                    last_start = id;
                }
            }
            for (const auto delta : {-1, 1}) {
                auto expected = delta > 0 ? last_entrance
                                         : (last_exit ? last_exit : first_entrance);
                auto kind = delta > 0 || !last_exit ? torchlight::LevelArrivalKind::entrance
                                                    : torchlight::LevelArrivalKind::exit;
                if (!expected) {
                    expected = last_start;
                    kind = last_start ? torchlight::LevelArrivalKind::player_start
                                      : torchlight::LevelArrivalKind::default_origin;
                }
                const auto actual = torchlight::find_same_dungeon_level_arrival(
                    layout, request(delta));
                require(actual && actual->kind == kind && actual->marker_id == expected,
                        "ordered fallback differs from whole-sequence reference");
                const float x = expected ? static_cast<float>(*expected * 10) : 0.0F;
                require(actual->position[0] == x && actual->position[1] == 0.0F &&
                            actual->position[2] == x * 2.0F && actual->angle_degrees == 0.0F,
                        "ordered fallback returned wrong coordinates");
                ++sequence_count;
            }
        }
        count *= 4;
    }
    std::cout << "Checked " << sequence_count << " synthetic ordered-node sequences\n";
}

} // namespace

int main() {
    using Kind = torchlight::LevelArrivalKind;
    try {
        torchlight::LayoutManifest layout;
        auto editor = node(90, u"Editor Player Start");
        editor.descriptor = u"Editor Player Start";
        editor.position_x = -100.0F;
        layout.objects = {editor, node(1, u"Entrance"), node(2, u"Exit")};
        require(torchlight::layout_player_start(layout)[0] == -100.0F,
                "fixture does not exercise the old editor-start fallback");
        expect(layout, request(-1), Kind::exit, 2);
        expect(layout, request(1), Kind::entrance, 1);
        expect(layout, request(0), Kind::entrance, 1);

        // The raw warp fields, not the normalized destination depth, set mode.
        auto absolute = request(0);
        absolute.destination.depth = 9;
        absolute.warp.absolute_level = 9;
        expect(layout, absolute, Kind::exit, 2);
        absolute.warp.absolute_level = 0;
        expect(layout, absolute, Kind::entrance, 1);
        absolute.warp.level_delta = 1;
        absolute.warp.absolute_level = 1;
        absolute.destination.depth = 1;
        expect(layout, absolute, Kind::entrance, 1);
        absolute.warp.level_delta = std::numeric_limits<std::int32_t>::min();
        expect(layout, absolute, Kind::exit, 2);
        absolute.warp.level_delta = std::numeric_limits<std::int32_t>::max();
        expect(layout, absolute, Kind::entrance, 1);

        // An existing Warper always keeps priority over fallback nodes.
        auto warp = node(10, u"Ignored");
        warp.descriptor = u"Warper";
        warp.name = u"Return";
        warp.properties.clear();
        layout.objects.push_back(warp);
        auto named = request(-1);
        named.warp.warp_name = u"return";
        expect(layout, named, Kind::warper, 10);
        layout.objects.pop_back();

        auto special = request(-1);
        special.warp.waypoint = true;
        require(!torchlight::find_same_dungeon_level_arrival(layout, special),
                "waypoint incorrectly entered the ordinary fallback");
        special.warp.waypoint = false;
        special.destination.dungeon_name = u"Town";
        require(!torchlight::find_same_dungeon_level_arrival(layout, special),
                "inter-dungeon transition incorrectly entered the ordinary fallback");
        special.destination.dungeon_name = u"Main";
        special.warp.dungeon_name = u"lastdungeon";
        require(!torchlight::find_same_dungeon_level_arrival(layout, special),
                "LASTDUNGEON rewrite was guessed from raw warp fields");
        special.warp.dungeon_name.clear();
        special.warp.level_delta = -99;
        require(!torchlight::find_same_dungeon_level_arrival(layout, special),
                "town-portal sentinel incorrectly entered the ordinary fallback");

        // A valid Exit-only scene must not depend on a legacy start helper.
        layout.objects = {node(4, u"Exit")};
        expect(layout, request(-1), Kind::exit, 4);
        expect(layout, request(1), Kind::default_origin, std::nullopt);
        layout.objects = {node(5, u"Player Start"), node(6, u"Player Start")};
        expect(layout, request(-1), Kind::player_start, 6);
        layout.objects.front().properties.clear();
        layout.objects.back().descriptor = u"Group";
        expect(layout, request(-1), Kind::default_origin, std::nullopt);

        // Match TYPE, not NAME; do not invent an enabled filter for these cases.
        layout.objects = {node(7, u"Entrance")};
        layout.objects[0].name = u"Exit";
        layout.objects[0].properties.push_back(
            {0, u"ENABLED", torchlight::AdmValueType::boolean, false});
        expect(layout, request(-1), Kind::entrance, 7);

        torchlight::LayoutObject parent;
        parent.id = 20;
        parent.descriptor = u"Group";
        parent.position_x = 100.0F;
        parent.position_y = 7.0F;
        parent.position_z = 200.0F;
        parent.scale_x = 2.0F;
        parent.scale_y = 3.0F;
        parent.scale_z = 4.0F;
        parent.angle = 90.0F;
        auto child = node(21, u"Exit");
        child.parent_id = parent.id;
        child.position_x = 3.0F;
        child.position_y = 2.0F;
        child.position_z = 4.0F;
        child.angle = 90.0F;
        layout.objects = {parent, child};
        const auto nested = torchlight::find_same_dungeon_level_arrival(layout, request(-1));
        require(nested && nested->marker_id == 21 &&
                    std::abs(nested->position[0] - 116.0F) < 0.0001F &&
                    std::abs(nested->position[1] - 13.0F) < 0.0001F &&
                    std::abs(nested->position[2] - 194.0F) < 0.0001F &&
                    std::abs(std::remainder(nested->angle_degrees - 180.0F, 360.0F)) < 0.0001F,
                "property fallback lost the complete parent world transform");

        check_sequences();
        std::cout << "PASS: " << checks << " level-entry assertions\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
