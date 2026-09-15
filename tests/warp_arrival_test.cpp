#include "torchlight/level_transition.hpp"
#include "torchlight/scene_math.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

torchlight::AdmProperty text_property(const char16_t* name,
                                      std::u16string value) {
    return {0, name, torchlight::AdmValueType::string, std::move(value)};
}

torchlight::AdmProperty int_property(const char16_t* name, std::int32_t value) {
    return {0, name, torchlight::AdmValueType::integer, value};
}

torchlight::LayoutObject warper(std::int64_t id, std::u16string name,
                               float x, float z, float angle,
                               std::u16string dungeon, std::int32_t delta,
                               std::int32_t absolute = 0) {
    torchlight::LayoutObject result;
    result.id = id;
    result.descriptor = u"Warper";
    result.name = std::move(name);
    result.position_x = x;
    result.position_y = 0.0F;
    result.position_z = z;
    result.angle = angle;
    result.properties = {
        text_property(u"DUNGEON NAME", std::move(dungeon)),
        int_property(u"LEVEL DELTA", delta),
        int_property(u"LEVEL ABSOLUTE", absolute)};
    return result;
}

} // namespace

int main() {
    try {
        torchlight::LevelTransitionState transitions({u"Main", 2});
        torchlight::WarpRequest ascend;
        ascend.warp_name = u"ReturnFrom2";
        ascend.level_delta = -1;
        auto entry = transitions.resolve_entry(ascend);
        require(entry.source.depth == 2 && entry.destination.depth == 1 &&
                    entry.warp.warp_name == u"ReturnFrom2",
                "level entry did not preserve the source and outgoing request");

        torchlight::LayoutManifest layout;
        layout.objects.push_back(
            warper(10, u"Other", 30.0F, 40.0F, 90.0F, u"", 1));
        layout.objects.push_back(
            warper(11, u"ReturnFrom2", -100.0F, 0.0F, 0.0F, u"Wrong", 99));
        const auto early_reverse =
            torchlight::find_same_dungeon_warp_arrival(layout, entry);
        require(early_reverse && early_reverse->warper_id == 10,
                "a later exact name incorrectly beat an earlier reverse route");
        require(std::abs(early_reverse->position[0] - 30.0F) < 0.0001F &&
                    std::abs(early_reverse->position[2] - 40.0F) < 0.0001F &&
                    std::abs(early_reverse->angle_degrees - 90.0F) < 0.0001F,
                "arrival did not retain the warper world transform");

        std::swap(layout.objects[0], layout.objects[1]);
        const auto exact_name =
            torchlight::find_same_dungeon_warp_arrival(layout, entry);
        require(exact_name && exact_name->warper_id == 11,
                "the current warper NAME was not checked first");

        layout.objects.clear();
        layout.objects.push_back(
            warper(12, u"Absolute", 1.0F, 2.0F, 0.0F, u"Main", 0, 2));
        const auto absolute =
            torchlight::find_same_dungeon_warp_arrival(layout, entry);
        require(absolute && absolute->warper_id == 12,
                "absolute reverse-floor predicate did not match");
        layout.objects.front().properties.back() =
            int_property(u"LEVEL ABSOLUTE", 2);
        layout.objects.front().properties[1] = int_property(u"LEVEL DELTA", 1);
        require(!torchlight::find_same_dungeon_warp_arrival(layout, entry),
                "two non-zero level fields used an invented priority rule");

        torchlight::LevelEntryRequest non_main{{u"Crypt", 2}, {u"Crypt", 1}, ascend};
        layout.objects.front() =
            warper(13, u"Other", 0.0F, 0.0F, 0.0F, u"", 1);
        require(!torchlight::find_same_dungeon_warp_arrival(layout, non_main),
                "empty reverse dungeon became a universal wildcard");

        entry.warp.waypoint = true;
        require(!torchlight::find_same_dungeon_warp_arrival(layout, entry),
                "waypoint entered the ordinary floor-warp path");
        entry.warp.waypoint = false;
        entry.destination.dungeon_name = u"Town";
        require(!torchlight::find_same_dungeon_warp_arrival(layout, entry),
                "inter-dungeon warp entered the same-dungeon path");

        torchlight::LayoutManifest nested;
        torchlight::LayoutObject parent;
        parent.id = 20;
        parent.descriptor = u"Group";
        parent.position_x = 100.0F;
        parent.position_z = 200.0F;
        parent.angle = 90.0F;
        nested.objects.push_back(parent);
        auto child = warper(21, u"ReturnFrom2", 3.0F, 4.0F, 0.0F,
                            u"Wrong", 99);
        child.parent_id = parent.id;
        nested.objects.push_back(std::move(child));
        entry.destination.dungeon_name = u"Main";
        const auto nested_arrival =
            torchlight::find_same_dungeon_warp_arrival(nested, entry);
        require(nested_arrival &&
                    std::abs(nested_arrival->position[0] - 104.0F) < 0.0001F &&
                    std::abs(nested_arrival->position[2] - 197.0F) < 0.0001F &&
                    std::abs(nested_arrival->angle_degrees - 90.0F) < 0.0001F,
                "arrival ignored the parent world transform");

        std::cout << "PASS: selected same-dungeon reverse Warpers in original order\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
