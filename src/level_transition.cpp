#include "torchlight/level_transition.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

namespace torchlight {
namespace {

class LevelTransitionError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

char16_t upper_ascii(char16_t value) noexcept {
    return value >= u'a' && value <= u'z' ? static_cast<char16_t>(value - 32) : value;
}

bool same_name(std::u16string_view left, std::u16string_view right) noexcept {
    return left.size() == right.size() &&
           std::equal(left.begin(), left.end(), right.begin(),
                      [](char16_t a, char16_t b) {
                          return upper_ascii(a) == upper_ascii(b);
                      });
}

bool is_town(const DungeonManifest& dungeon) noexcept {
    return std::any_of(dungeon.strata.begin(), dungeon.strata.end(),
                       [](const auto& stratum) { return stratum.is_town; });
}

std::u16string_view text_property(const LayoutObject& object,
                                  const char16_t* name) {
    const auto* value = object.find_property(name);
    if (value == nullptr) {
        return {};
    }
    if (value->type != AdmValueType::string &&
        value->type != AdmValueType::translation &&
        value->type != AdmValueType::note) {
        throw LevelTransitionError("Layout text property has the wrong type");
    }
    return std::get<std::u16string>(value->value);
}

std::int64_t integer_property(const LayoutObject& object, const char16_t* name,
                              std::int64_t fallback) {
    const auto* value = object.find_property(name);
    if (value == nullptr) {
        return fallback;
    }
    if (value->type == AdmValueType::integer) {
        return std::get<std::int32_t>(value->value);
    }
    if (value->type == AdmValueType::integer64) {
        return std::get<std::int64_t>(value->value);
    }
    if (value->type == AdmValueType::unsigned_integer) {
        return std::get<std::uint32_t>(value->value);
    }
    throw LevelTransitionError("Warper level property has the wrong type");
}

WarpArrivalPoint arrival_point(const LayoutObject& object,
                               const LayoutWorldTransform& transform) {
    constexpr float kRadiansToDegrees = 57.295779513082320876F;
    const auto forward = rotate_vector(transform.orientation, {0.0F, 0.0F, 1.0F});
    const float angle = std::hypot(forward[0], forward[2]) > 0.000001F
                            ? std::remainder(
                                  std::atan2(forward[0], forward[2]) *
                                      kRadiansToDegrees,
                                  360.0F)
                            : 0.0F;
    return {object.id, transform.position, angle};
}

} // namespace

DungeonFloorSelection select_dungeon_floor(const DungeonManifest& dungeon,
                                            std::int32_t requested_depth) {
    if (dungeon.strata.empty()) {
        throw LevelTransitionError("Dungeon has no strata");
    }
    if (is_town(dungeon)) {
        return {0, 0, 0};
    }

    const auto depth = std::max<std::int32_t>(1, requested_depth);
    std::int64_t floor_offset = static_cast<std::int64_t>(depth) - 1;
    for (std::size_t index = 0; index < dungeon.strata.size(); ++index) {
        const auto floors = dungeon.strata[index].floors;
        if (floors <= 0) {
            throw LevelTransitionError("Dungeon stratum has no floors");
        }
        if (floor_offset < floors) {
            return {index, depth, static_cast<std::int32_t>(floor_offset)};
        }
        floor_offset -= floors;
    }
    throw LevelTransitionError("Dungeon depth is outside its strata");
}

LevelTransitionState::LevelTransitionState(DungeonAddress current)
    : current_(std::move(current)) {
    if (current_.dungeon_name.empty()) {
        throw LevelTransitionError("Current dungeon name is empty");
    }
}

DungeonAddress LevelTransitionState::resolve(const WarpRequest& request) const {
    if (same_name(request.dungeon_name, u"LASTDUNGEON")) {
        if (!last_dungeon_) {
            throw LevelTransitionError("LASTDUNGEON has no recorded destination");
        }
        return *last_dungeon_;
    }

    const auto& requested_name = request.dungeon_name.empty()
                                     ? current_.dungeon_name
                                     : request.dungeon_name;
    const bool staying = same_name(requested_name, current_.dungeon_name);
    std::int64_t depth = 0;
    if (request.absolute_level && *request.absolute_level != 0) {
        depth = *request.absolute_level;
    } else if (staying) {
        depth = static_cast<std::int64_t>(current_.depth) + request.level_delta;
    } else {
        depth = request.level_delta;
    }
    if (depth < std::numeric_limits<std::int32_t>::min() ||
        depth > std::numeric_limits<std::int32_t>::max()) {
        throw LevelTransitionError("Warp depth exceeds the 32-bit range");
    }
    return {requested_name, static_cast<std::int32_t>(depth)};
}

LevelEntryRequest LevelTransitionState::resolve_entry(
    const WarpRequest& request) const {
    return {current_, resolve(request), request};
}

void LevelTransitionState::commit(DungeonAddress destination) {
    if (destination.dungeon_name.empty()) {
        throw LevelTransitionError("Destination dungeon name is empty");
    }
    if (!same_name(destination.dungeon_name, current_.dungeon_name)) {
        last_dungeon_ = current_;
    }
    current_ = std::move(destination);
}

std::optional<WarpArrivalPoint> find_same_dungeon_warp_arrival(
    const LayoutManifest& layout, const LevelEntryRequest& entry) {
    if (entry.warp.waypoint ||
        !same_name(entry.source.dungeon_name, entry.destination.dungeon_name)) {
        return std::nullopt;
    }

    const auto transforms = resolve_layout_world_transforms(layout);
    const std::int64_t source_depth = entry.source.depth;
    const std::int64_t loaded_depth = entry.destination.depth;
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        const auto& object = layout.objects[index];
        if (object.descriptor != u"Warper") {
            continue;
        }

        // The original checks each object's NAME before its reverse route, so
        // an earlier reverse match can beat a later exact-name match.
        if (!object.name.empty() && !entry.warp.warp_name.empty() &&
            same_name(object.name, entry.warp.warp_name)) {
            return arrival_point(object, transforms[index]);
        }

        const auto reverse_dungeon = text_property(object, u"DUNGEON NAME");
        const bool reverse_dungeon_matches =
            same_name(reverse_dungeon, entry.source.dungeon_name) ||
            (reverse_dungeon.empty() &&
             same_name(entry.source.dungeon_name, u"MAIN"));
        if (!reverse_dungeon_matches) {
            continue;
        }

        const auto delta = integer_property(object, u"LEVEL DELTA", 1);
        const auto absolute = integer_property(object, u"LEVEL ABSOLUTE", 0);
        const bool matches_previous_floor =
            (delta == 0 && absolute == source_depth) ||
            (absolute == 0 && delta == source_depth - loaded_depth);
        if (matches_previous_floor) {
            return arrival_point(object, transforms[index]);
        }
    }
    return std::nullopt;
}

std::optional<LevelArrivalPoint> find_same_dungeon_level_arrival(
    const LayoutManifest& layout, const LevelEntryRequest& entry) {
    // Special paths rewrite the pending fields or use another ELevelEntryType.
    // Do not infer their behavior from this ordinary same-dungeon branch.
    if (entry.warp.waypoint || entry.warp.level_delta == -99 ||
        same_name(entry.warp.dungeon_name, u"LASTDUNGEON") ||
        !same_name(entry.source.dungeon_name, entry.destination.dungeon_name)) {
        return std::nullopt;
    }
    if (const auto warp = find_same_dungeon_warp_arrival(layout, entry)) {
        return LevelArrivalPoint{LevelArrivalKind::warper, warp->warper_id,
                                 warp->position, warp->angle_degrees};
    }

    return find_same_dungeon_entry_anchor(layout, entry);
}
std::optional<LevelArrivalPoint> find_same_dungeon_entry_anchor(
    const LayoutManifest& layout, const LevelEntryRequest& entry) {
    if (entry.warp.waypoint || entry.warp.level_delta == -99 ||
        same_name(entry.warp.dungeon_name, u"LASTDUNGEON") ||
        !same_name(entry.source.dungeon_name, entry.destination.dungeon_name)) return std::nullopt;

    // original-code: performWarp @0x58d39f compares both pending integers with
    // zero, then tests the sign of delta. An absolute jump is not classified
    // by destination.depth - source.depth. Mode 1 prefers Entrance, mode 0 Exit.
    const bool prefer_entrance =
        entry.warp.level_delta > 0 ||
        (entry.warp.level_delta == 0 && entry.warp.absolute_level.value_or(0) == 0);
    std::optional<std::size_t> selected;
    std::optional<std::size_t> player_start;
    LevelArrivalKind kind = LevelArrivalKind::default_origin;
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        const auto& object = layout.objects[index];
        if (object.descriptor != u"Property Node") {
            continue;
        }
        const auto type = text_property(object, u"TYPE");
        // original-code type mapping and predicates/order, including the
        // verified jump table at 0xfd6ad0:
        // loadRoomLayout @0x9609c0 / @0x960910 / @0x960ae3.
        if (type == u"Entrance" && (prefer_entrance || !selected)) {
            selected = index;
            kind = LevelArrivalKind::entrance;
        } else if (type == u"Exit" && !prefer_entrance) {
            selected = index;
            kind = LevelArrivalKind::exit;
        } else if (type == u"Player Start") {
            player_start = index;
        }
    }
    if (!selected) {
        selected = player_start;
        kind = player_start ? LevelArrivalKind::player_start
                            : LevelArrivalKind::default_origin;
    }
    if (!selected) {
        // original-code initialization/final copy @0x960098 and @0x960cb1:
        // no applicable marker leaves origin and +Z, not an editor start.
        return LevelArrivalPoint{};
    }
    const auto transforms = resolve_layout_world_transforms(layout);
    const auto point = arrival_point(layout.objects[*selected], transforms[*selected]);
    return LevelArrivalPoint{kind, point.warper_id, point.position, point.angle_degrees};
}

} // namespace torchlight
