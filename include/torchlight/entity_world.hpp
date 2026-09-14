#pragma once

#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/spawn_class.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace torchlight {

struct RuntimeEntity {
    std::uint64_t id = 0;
    std::int64_t spawner_id = 0;
    std::int64_t resource_guid = 0;
    MasterResourceKind kind = MasterResourceKind::prop;
    std::u16string name;
    std::array<float, 3> position{};
    bool alive = true;
};

struct SpawnResolutionStats {
    std::size_t requests = 0;
    std::size_t entities_created = 0;
    std::size_t deferred_unit_types = 0;
    std::size_t missing_resources = 0;
};

class RuntimeEntityWorld {
public:
    RuntimeEntityWorld(const LayoutManifest& layout,
                       const MasterResourceIndex& resources,
                       const SpawnClassCatalog& spawn_classes,
                       std::uint32_t random_seed = 1);

    SpawnResolutionStats consume_spawn_requests(
        const std::vector<SpawnRequest>& requests, LogicRuntime& logic);
    bool kill(std::uint64_t entity_id, LogicRuntime& logic);
    bool pick_up(std::uint64_t entity_id, LogicRuntime& logic);

    [[nodiscard]] const std::vector<RuntimeEntity>& entities() const noexcept {
        return entities_;
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
    const SpawnClassCatalog* spawn_classes_ = nullptr;
    std::unordered_map<std::int64_t, std::array<float, 3>> spawner_positions_;
    TorchlightRandom random_;
    std::uint64_t next_entity_id_ = 1;
    std::vector<RuntimeEntity> entities_;
};

} // namespace torchlight
