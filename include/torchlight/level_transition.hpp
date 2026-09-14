#pragma once

#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>

namespace torchlight {

struct DungeonAddress {
    std::u16string dungeon_name;
    std::int32_t depth = 0;
};

struct DungeonFloorSelection {
    std::size_t stratum_index = 0;
    std::int32_t depth = 0;
    std::int32_t floor_in_stratum = 0;
};

[[nodiscard]] DungeonFloorSelection select_dungeon_floor(
    const DungeonManifest& dungeon, std::int32_t requested_depth);

class LevelTransitionState {
public:
    explicit LevelTransitionState(DungeonAddress current);

    [[nodiscard]] const DungeonAddress& current() const noexcept { return current_; }
    [[nodiscard]] const std::optional<DungeonAddress>& last_dungeon() const noexcept {
        return last_dungeon_;
    }
    [[nodiscard]] DungeonAddress resolve(const WarpRequest& request) const;
    void commit(DungeonAddress destination);

private:
    DungeonAddress current_;
    std::optional<DungeonAddress> last_dungeon_;
};

} // namespace torchlight
