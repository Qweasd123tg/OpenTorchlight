#pragma once

#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/spawn_class.hpp"
#include "torchlight/unit_type.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

namespace torchlight {

struct RuntimeEntity {
    std::uint64_t id = 0;
    std::int64_t spawner_id = 0;
    std::int64_t layout_object_id = 0;
    std::int64_t resource_guid = 0;
    MasterResourceKind kind = MasterResourceKind::prop;
    std::u16string name;
    std::array<float, 3> position{};
    float health = 0.0F;
    float maximum_health = 0.0F;
    bool alive = true;
    bool combat_targetable = false;
};

struct DamageResult {
    bool accepted = false;
    bool killed = false;
    float remaining_health = 0.0F;
};

struct SpawnResolutionStats {
    std::size_t requests = 0;
    std::size_t entities_created = 0;
    std::size_t resolved_unit_types = 0;
    std::size_t unresolved_unit_types = 0;
    std::size_t missing_resources = 0;
};

class RuntimeEntityWorld {
public:
    RuntimeEntityWorld(const LayoutManifest& layout,
                       const MasterResourceIndex& resources,
                       UnitDefinitionLoader& definitions,
                       const SpawnClassCatalog& spawn_classes,
                       const UnitTypeResourceIndex& unit_types,
                       std::uint32_t random_seed = 1,
                       std::int32_t spawn_level = 1);

    SpawnResolutionStats consume_spawn_requests(
        const std::vector<SpawnRequest>& requests, LogicRuntime& logic);
    bool kill(std::uint64_t entity_id, LogicRuntime& logic);
    [[nodiscard]] DamageResult apply_damage(std::uint64_t entity_id, float damage,
                                            LogicRuntime& logic);
    bool pick_up(std::uint64_t entity_id, LogicRuntime& logic);
    [[nodiscard]] RuntimeEntity* find(std::uint64_t entity_id) noexcept;
    [[nodiscard]] const RuntimeEntity* find(std::uint64_t entity_id) const noexcept;
    [[nodiscard]] const RuntimeEntity* find_layout_entity(
        std::int64_t layout_object_id) const noexcept;
    [[nodiscard]] const RuntimeEntity* nearest_alive_monster(
        const std::array<float, 3>& position, float maximum_distance) const noexcept;

    [[nodiscard]] const std::vector<RuntimeEntity>& entities() const noexcept {
        return entities_;
    }
    [[nodiscard]] std::size_t placed_entity_count() const noexcept {
        return placed_entity_count_;
    }

private:
    [[nodiscard]] const MasterResourceRecord* resolve_direct(
        std::u16string_view group, std::u16string_view resource) const noexcept;
    void create_leaf(std::int64_t spawner_id, const std::array<float, 3>& position,
                     const SpawnLeaf& leaf, SpawnResolutionStats& stats);
    void create_resource(std::int64_t spawner_id,
                         const std::array<float, 3>& position,
                         const MasterResourceRecord& resource,
                         SpawnResolutionStats& stats);
    [[nodiscard]] std::uint32_t alive_monster_count(
        std::int64_t spawner_id) const noexcept;

    const MasterResourceIndex* resources_ = nullptr;
    UnitDefinitionLoader* definitions_ = nullptr;
    const SpawnClassCatalog* spawn_classes_ = nullptr;
    const UnitTypeResourceIndex* unit_types_ = nullptr;
    std::unordered_map<std::int64_t, std::array<float, 3>> spawner_positions_;
    TorchlightRandom random_;
    std::int32_t spawn_level_ = 1;
    std::uint64_t next_entity_id_ = 1;
    std::size_t placed_entity_count_ = 0;
    std::vector<RuntimeEntity> entities_;
};

} // namespace torchlight
