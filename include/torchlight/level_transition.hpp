#pragma once

#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"

#include <array>
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

struct LevelEntryRequest {
    DungeonAddress source;
    DungeonAddress destination;
    WarpRequest warp;
};

struct WarpArrivalPoint {
    std::int64_t warper_id = 0;
    std::array<float, 3> position{};
    float angle_degrees = 0.0F;
};

enum class LevelArrivalKind {
    warper,
    entrance,
    exit,
    player_start,
    default_origin,
};

struct LevelArrivalPoint {
    LevelArrivalKind kind = LevelArrivalKind::default_origin;
    std::optional<std::int64_t> marker_id;
    std::array<float, 3> position{};
    float angle_degrees = 0.0F;
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
    [[nodiscard]] LevelEntryRequest resolve_entry(const WarpRequest& request) const;
    void commit(DungeonAddress destination);

private:
    friend struct CheckpointAccess;
    DungeonAddress current_;
    std::optional<DungeonAddress> last_dungeon_;
};

// original-code: the ordinary same-dungeon path of
// CLevel::placePlayerAtWarpToDungeonFloor @0x953000. Inter-dungeon portals,
// waypoint placement are separate paths; the wrapper below adds the ordinary
// property-node fallback.
[[nodiscard]] std::optional<WarpArrivalPoint> find_same_dungeon_warp_arrival(
    const LayoutManifest& layout, const LevelEntryRequest& entry);

// Ordinary same-dungeon arrival, preserving reverse-Warper priority, then the
// ordered Entrance/Exit/Player Start fallback. Unsupported special paths return
// nullopt; a supported layout without markers returns default_origin.
// original-code predicates and switch-to-node mapping, verified against the
// pinned original ELF jump table; see research/level-entry-fallback.md.
[[nodiscard]] std::optional<LevelArrivalPoint> find_same_dungeon_level_arrival(
    const LayoutManifest& layout, const LevelEntryRequest& entry);

// The level-owned Property Node anchor (CLevel+0x140/+0x164), BEFORE a reverse
// Warper overrides the player's arrival position. Death mode 1 uses this anchor.
[[nodiscard]] std::optional<LevelArrivalPoint> find_same_dungeon_entry_anchor(
    const LayoutManifest& layout, const LevelEntryRequest& entry);

} // namespace torchlight
