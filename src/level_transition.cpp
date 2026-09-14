#include "torchlight/level_transition.hpp"

#include <algorithm>
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

void LevelTransitionState::commit(DungeonAddress destination) {
    if (destination.dungeon_name.empty()) {
        throw LevelTransitionError("Destination dungeon name is empty");
    }
    if (!same_name(destination.dungeon_name, current_.dungeon_name)) {
        last_dungeon_ = current_;
    }
    current_ = std::move(destination);
}

} // namespace torchlight
