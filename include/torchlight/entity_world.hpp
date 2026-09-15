#pragma once

#include "torchlight/damage.hpp"
#include "torchlight/equipment.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/spawn_class.hpp"
#include "torchlight/stat_graph.hpp"
#include "torchlight/treasure.hpp"
#include "torchlight/unit_type.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
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
    std::u16string display_name;
    std::u16string unit_type;
    std::string mesh_path;
    bool inventory_eligible = false;
    bool two_handed = false;
    TreasureProfile treasure;
    bool drops_loot = true;
    std::uint64_t loot_source_id = 0;
    std::array<float, 3> position{};
    std::int32_t level = 1;
    float health = 0.0F;
    float maximum_health = 0.0F;
    std::int32_t minimum_damage = 0;
    std::int32_t maximum_damage = 0;
    float walking_speed = 0.0F;
    float running_speed = 0.0F;
    float attack_speed = 0.0F;
    // original-code: CMonster+0x7ec; independent of attack animation speed.
    float ai_attack_cooldown = 0.0F;
    // CEquipment+0x408 of the currently selected weapon (nullopt: unarmed).
    std::optional<float> equipped_ai_attack_cooldown;
    float sight_radius = 0.0F;
    float reach_bonus = 0.0F;
    float weapon_range = 0.0F;
    float attack_range = 0.5F;
    float motion_radius = 0.0F;
    float follow_radius = 0.0F;
    std::u16string equipped_attack_name;
    std::optional<ArmorItem> armor_item;
    std::optional<WeaponItem> weapon_item;
    DamageDefense damage_defense;
    AttackLoadout attacks;
    AttackCharacterValues attack_character;
    bool alive = true;
    bool enabled = true;
    bool visible = true;
    bool combat_targetable = false;
};

struct DamageResult {
    bool accepted = false;
    bool killed = false;
    float remaining_health = 0.0F;
};

struct SpawnResolutionStats {
    std::size_t requests = 0;
    std::size_t spawn_requests = 0;
    std::size_t control_requests = 0;
    std::size_t entities_created = 0;
    std::size_t entities_hidden = 0;
    std::size_t entities_destroyed = 0;
    std::size_t resolved_unit_types = 0;
    std::size_t unresolved_unit_types = 0;
    std::size_t missing_resources = 0;
};

struct LootResolutionStats {
    std::size_t deaths = 0;
    std::size_t class_rolls = 0;
    std::size_t missing_classes = 0;
    SpawnResolutionStats spawns;
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
    // Safe phase after damage callbacks. Never grows entities_ while callers
    // hold pointers into that vector. Repeated drains cannot duplicate loot.
    // Death finalization phase: create a death's items, THEN notify its spawner.
    // Call after releasing pointers into entities_, before draining script commands.
    // No world/LogicRuntime pointers are captured in pending death snapshots.
    [[nodiscard]] LootResolutionStats resolve_death_loot(LogicRuntime& logic);
    [[nodiscard]] std::size_t pending_loot_count() const noexcept {
        std::size_t count = 0;
        for (const auto& death : pending_deaths_) if (death.drops_loot) ++count;
        return count;
    }
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
    [[nodiscard]] const RuntimeEntity* nearest_alive_item(
        const std::array<float, 3>& position, float maximum_distance,
        bool inventory_only = false) const noexcept;

    [[nodiscard]] const std::vector<RuntimeEntity>& entities() const noexcept {
        return entities_;
    }
    [[nodiscard]] std::vector<RuntimeEntity>& entities() noexcept { return entities_; }
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
    void equip_monster_attack(RuntimeEntity& entity,
                              const UnitDefinition& definition);
    [[nodiscard]] std::uint32_t alive_monster_count(
        std::int64_t spawner_id) const noexcept;

    struct PendingDeath {
        std::uint64_t source_id;
        std::array<float, 3> position;
        TreasureProfile treasure;
        std::int64_t spawner_id;
        bool drops_loot;
    };
    void record_death(RuntimeEntity& entity);
    std::deque<PendingDeath> pending_deaths_;
    const MasterResourceIndex* resources_ = nullptr;
    UnitDefinitionLoader* definitions_ = nullptr;
    const SpawnClassCatalog* spawn_classes_ = nullptr;
    const UnitTypeResourceIndex* unit_types_ = nullptr;
    std::optional<AttackEffectCatalog> attack_effect_catalog_;
    StatGraph monster_health_graph_;
    StatGraph monster_damage_graph_;
    StatGraph monster_armor_graph_;
    StatGraph player_armor_graph_;
    StatGraph player_weapon_damage_graph_;
    std::unordered_map<std::int64_t, std::array<float, 3>> spawner_positions_;
    TorchlightRandom random_;
    std::int32_t spawn_level_ = 1;
    std::uint64_t next_entity_id_ = 1;
    std::size_t placed_entity_count_ = 0;
    std::vector<RuntimeEntity> entities_;
};

} // namespace torchlight
