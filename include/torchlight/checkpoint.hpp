#pragma once

#include "torchlight/player_session.hpp"
#include "torchlight/level_transition.hpp"
#include <stdexcept>

namespace torchlight {
// Portable checkpoint DTOs, not the original C*SaveState binary layouts.
// See research/frontend-save-evidence.md. No pointers, actions or resource bytes.
class CheckpointError : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
};
struct InventoryCheckpoint {
    InventoryId next_id = 1;
    std::vector<InventoryItem> items;
    std::array<InventoryId, static_cast<std::size_t>(InventorySlot::count)> slots{};
};
struct PlayerCheckpoint {
    InventoryCheckpoint inventory;
    std::int32_t gold = 0;
    bool hardcore = false;
    float health = 1, maximum_health = 1;
    std::optional<float> mana, maximum_mana;
    DamageDefense base_defense;
    std::uint64_t combat_random = 0;
    bool prefer_left = false;
    std::optional<ProgressionState> progression;
    // v3: absent only for migration from v1/v2, where max-HP effects were ignored.
    std::optional<std::int32_t> base_health;
};
struct WorldCheckpoint {
    std::uint64_t next_id = 1, random_state = 0;
    std::uint32_t placed_count = 0;
    std::int32_t spawn_level = 1;
    std::vector<RuntimeEntity> entities;
};
struct LogicCheckpointEntry {
    std::int64_t id = 0;
    LogicObjectState state;
};
struct LogicCheckpoint {
    std::uint64_t random_state = 0;
    std::vector<LogicCheckpointEntry> entries;
};
struct EnemyCheckpointEntry {
    std::uint64_t id = 0;
    bool alerted = false, prefer_left = false;
    float ai_cooldown = 0;
};
struct EnemyCheckpoint {
    std::uint64_t random_state = 0;
    std::vector<EnemyCheckpointEntry> entries;
};
struct FloorCheckpoint {
    DungeonAddress address;
    std::uint64_t layout_identity = 0;
    std::array<float, 3> player_position{}, recovery_anchor{};
    float player_angle = 0, recovery_angle = 0, floor_offset = 0;
    bool original_recovery_anchor = false;
    WorldCheckpoint world;
    LogicCheckpoint logic;
    EnemyCheckpoint enemies;
};
struct CampaignCheckpoint {
    std::string slot;
    std::uint64_t revision = 0;
    std::uint64_t resource_identity = 0;
    std::uint32_t seed = 1;
    std::int64_t class_guid = 0;
    std::string character_name;
    // Normal only. Never silently advertise unimplemented difficulty graphs.
    std::uint8_t difficulty = 1;
    DungeonAddress current{u"Town", 0};
    std::optional<DungeonAddress> last_dungeon;
    PlayerCheckpoint player;
    std::vector<FloorCheckpoint> floors;
};
// One narrow friend controls checkpoint access. restore_* build candidates and
// validate before committing; active HITs and paths never cross a load boundary.
struct CheckpointAccess {
    [[nodiscard]] static PlayerCheckpoint capture(const PlayerSession &);
    [[nodiscard]] static WorldCheckpoint capture(const RuntimeEntityWorld &);
    [[nodiscard]] static LogicCheckpoint capture(const LogicRuntime &);
    [[nodiscard]] static EnemyCheckpoint capture(const EnemyController &);
    [[nodiscard]] static PlayerSession restore_player(const PlayerPrototype &,
                                                      const PlayerCheckpoint &, std::uint32_t seed,
                                                      const UnitTypeHierarchy *hierarchy = nullptr);
    static void restore_floor(const FloorCheckpoint &, RuntimeEntityWorld &, LogicRuntime &,
                              EnemyController &);
    [[nodiscard]] static LevelTransitionState restore_transitions(const CampaignCheckpoint &);
    static void validate(const CampaignCheckpoint &);
    static void validate(const PlayerCheckpoint &);
    static void validate(const FloorCheckpoint &);
};
[[nodiscard]] std::uint64_t checkpoint_resource_identity(const PakArchive &);
[[nodiscard]] std::uint64_t checkpoint_layout_identity(const LayoutManifest &);
[[nodiscard]] bool same_dungeon_address(const DungeonAddress &, const DungeonAddress &) noexcept;
[[nodiscard]] const FloorCheckpoint *find_floor(const CampaignCheckpoint &,
                                                const DungeonAddress &) noexcept;
void remember_floor(CampaignCheckpoint &, FloorCheckpoint);
// Only resumes on an existing walkable cell. No silent teleport out of a bad save.
[[nodiscard]] bool checkpoint_position_walkable(const NavigationGrid &,
                                                const std::array<float, 3> &position,
                                                float floor_offset) noexcept;
} // namespace torchlight
