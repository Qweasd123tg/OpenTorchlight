#include "torchlight/entity_world.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

namespace torchlight {
namespace {

class EntityWorldError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::u16string normalized(std::u16string_view value) {
    std::u16string result;
    result.reserve(value.size());
    for (const auto character : value) {
        result.push_back(character >= u'a' && character <= u'z'
                             ? static_cast<char16_t>(character - u'a' + u'A')
                             : character);
    }
    return result;
}

} // namespace

RuntimeEntityWorld::RuntimeEntityWorld(const LayoutManifest& layout,
                                       const MasterResourceIndex& resources,
                                       const SpawnClassCatalog& spawn_classes,
                                       const UnitTypeResourceIndex& unit_types,
                                       std::uint32_t random_seed,
                                       std::int32_t spawn_level)
    : resources_(&resources), spawn_classes_(&spawn_classes),
      unit_types_(&unit_types), random_(random_seed),
      spawn_level_(std::max<std::int32_t>(1, spawn_level)) {
    const auto transforms = resolve_layout_world_transforms(layout);
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        if (layout.objects[index].descriptor == u"Unit Spawner") {
            spawner_positions_.emplace(layout.objects[index].id,
                                       transforms[index].position);
        }
    }
}

const MasterResourceRecord* RuntimeEntityWorld::resolve_direct(
    std::u16string_view group, std::u16string_view resource) const noexcept {
    const auto key = normalized(group);
    if (key == u"MONSTERS") {
        return resources_->find_case_insensitive(MasterResourceKind::monster, resource);
    }
    if (key == u"ITEMS") {
        return resources_->find_case_insensitive(MasterResourceKind::item, resource);
    }
    if (key == u"PROPS") {
        return resources_->find_case_insensitive(MasterResourceKind::prop, resource);
    }
    return resources_->find_any(resource);
}

void RuntimeEntityWorld::create_leaf(std::int64_t spawner_id,
                                     const std::array<float, 3>& position,
                                     const SpawnLeaf& leaf,
                                     SpawnResolutionStats& stats) {
    if (leaf.kind == SpawnLeafKind::unit_type) {
        const auto* resource = unit_types_->roll(leaf.value, spawn_level_, random_);
        if (resource == nullptr) {
            ++stats.unresolved_unit_types;
            return;
        }
        ++stats.resolved_unit_types;
        create_resource(spawner_id, position, *resource, stats);
        return;
    }
    const auto* resource = resources_->find_any(leaf.value);
    if (resource == nullptr || resource->do_not_create) {
        ++stats.missing_resources;
        return;
    }
    create_resource(spawner_id, position, *resource, stats);
}

void RuntimeEntityWorld::create_resource(std::int64_t spawner_id,
                                         const std::array<float, 3>& position,
                                         const MasterResourceRecord& resource,
                                         SpawnResolutionStats& stats) {
    RuntimeEntity entity;
    entity.id = next_entity_id_++;
    entity.spawner_id = spawner_id;
    entity.resource_guid = resource.guid;
    entity.kind = resource.kind;
    entity.name = resource.name;
    entity.position = position;
    entities_.push_back(std::move(entity));
    ++stats.entities_created;
}

std::uint32_t RuntimeEntityWorld::alive_monster_count(
    std::int64_t spawner_id) const noexcept {
    return static_cast<std::uint32_t>(std::count_if(
        entities_.begin(), entities_.end(), [spawner_id](const auto& entity) {
            return entity.spawner_id == spawner_id && entity.alive &&
                   entity.kind == MasterResourceKind::monster;
        }));
}

SpawnResolutionStats RuntimeEntityWorld::consume_spawn_requests(
    const std::vector<SpawnRequest>& requests, LogicRuntime& logic) {
    SpawnResolutionStats stats;
    stats.requests = requests.size();
    for (const auto& request : requests) {
        const auto position = spawner_positions_.find(request.spawner_id);
        if (position == spawner_positions_.end()) {
            throw EntityWorldError("Spawn request references an absent Unit Spawner");
        }
        for (std::uint32_t instance = 0; instance < request.count; ++instance) {
            if (normalized(request.group) == u"SPAWN CLASS") {
                for (const auto& leaf : spawn_classes_->roll(request.resource, random_)) {
                    create_leaf(request.spawner_id, position->second, leaf, stats);
                }
            } else {
                const auto* resource = resolve_direct(request.group, request.resource);
                if (resource == nullptr || resource->do_not_create) {
                    ++stats.missing_resources;
                    continue;
                }
                create_resource(request.spawner_id, position->second, *resource, stats);
            }
        }
        logic.mark_spawn_complete(request.spawner_id,
                                  alive_monster_count(request.spawner_id));
    }
    return stats;
}

bool RuntimeEntityWorld::kill(std::uint64_t entity_id, LogicRuntime& logic) {
    const auto found = std::find_if(entities_.begin(), entities_.end(),
                                    [entity_id](const auto& entity) {
                                        return entity.id == entity_id;
                                    });
    if (found == entities_.end() || !found->alive ||
        found->kind != MasterResourceKind::monster) {
        return false;
    }
    found->alive = false;
    logic.notify_monster_killed(found->spawner_id);
    return true;
}

bool RuntimeEntityWorld::pick_up(std::uint64_t entity_id, LogicRuntime& logic) {
    const auto found = std::find_if(entities_.begin(), entities_.end(),
                                    [entity_id](const auto& entity) {
                                        return entity.id == entity_id;
                                    });
    if (found == entities_.end() || !found->alive ||
        found->kind != MasterResourceKind::item) {
        return false;
    }
    found->alive = false;
    logic.notify_item_picked_up(found->spawner_id);
    return true;
}

} // namespace torchlight
