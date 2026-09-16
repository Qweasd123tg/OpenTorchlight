#include "torchlight/entity_world.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
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

float optional_number(const UnitDefinition& definition, const char16_t* name,
                      float fallback) {
    const auto* property = definition.find_property(name);
    if (property == nullptr) {
        return fallback;
    }
    switch (property->type) {
    case AdmValueType::integer:
        return static_cast<float>(std::get<std::int32_t>(property->value));
    case AdmValueType::floating:
        return std::get<float>(property->value);
    case AdmValueType::double_precision:
        return static_cast<float>(std::get<double>(property->value));
    default:
        throw EntityWorldError("Runtime combat property is not numeric");
    }
}

bool optional_layout_bool(const LayoutObject& object, const char16_t* name,
                          bool fallback) {
    const auto* property = object.find_property(name);
    if (property == nullptr) {
        return fallback;
    }
    if (property->type != AdmValueType::boolean) {
        throw EntityWorldError("Placed-unit property is not boolean");
    }
    return std::get<bool>(property->value);
}

const std::u16string* optional_text(const AdmGroup& group,
                                    const char16_t* name) {
    const auto* property = group.find_property(name);
    if (property == nullptr) {
        return nullptr;
    }
    if (property->type != AdmValueType::string &&
        property->type != AdmValueType::translation &&
        property->type != AdmValueType::note) {
        throw EntityWorldError("Runtime equipment slot is not text");
    }
    return &std::get<std::u16string>(property->value);
}

} // namespace

RuntimeEntityWorld::RuntimeEntityWorld(const LayoutManifest& layout,
                                       const MasterResourceIndex& resources,
                                       UnitDefinitionLoader& definitions,
                                       const SpawnClassCatalog& spawn_classes,
                                       const UnitTypeResourceIndex& unit_types,
                                       std::uint32_t random_seed,
                                       std::int32_t spawn_level)
    : resources_(&resources), definitions_(&definitions),
      spawn_classes_(&spawn_classes),
      unit_types_(&unit_types),
      monster_health_graph_(
          definitions.archive(),
          "media/graphs/stats/HEALTH_MONSTER_BYLEVEL.DAT.adm"),
      monster_damage_graph_(definitions.archive(),
                            "media/graphs/stats/DAMAGE_MONSTER.DAT.adm"),
      monster_armor_graph_(
          definitions.archive(),
          "media/graphs/stats/ARMOR_MONSTER_BYLEVEL.DAT.adm"),
      player_armor_graph_(
          definitions.archive(),
          "media/graphs/stats/ARMOR_PLAYER_BYLEVEL_FORSET.DAT.adm"),
      player_weapon_damage_graph_(
          definitions.archive(),
          "media/graphs/stats/BASE_WEAPON_DAMAGE.DAT.adm"),
      random_(random_seed),
      spawn_level_(std::max<std::int32_t>(1, spawn_level)) {
    attack_effect_catalog_ = AttackEffectCatalog::discover(definitions.archive());
    gold_graph_ = find_named_stat_graph(definitions.archive(), "GOLDDROP");
    experience_graph_ = find_named_stat_graph(definitions.archive(), "EXPERIENCE_MONSTER");
    const auto transforms = resolve_layout_world_transforms(layout);
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        if (layout.objects[index].descriptor == u"Unit Spawner") {
            spawner_positions_.emplace(layout.objects[index].id,
                                       transforms[index].position);
        }
    }
    SpawnResolutionStats ignored_stats;
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        const auto& object = layout.objects[index];
        if (object.descriptor != u"Monster" || object.monster.empty()) {
            continue;
        }
        const auto* resource = resources_->find(
            MasterResourceKind::monster, object.monster);
        if (resource == nullptr || resource->do_not_create) {
            throw EntityWorldError("Placed unit is absent from master resources");
        }
        create_resource(0, transforms[index].position, *resource, ignored_stats);
        auto& entity = entities_.back();
        entity.layout_object_id = object.id;
        const auto unit_type = normalized(resource->unit_type);
        const bool enabled = optional_layout_bool(object, u"ENABLED", true);
        entity.alive = enabled;
        entity.enabled = enabled;
        entity.visible = optional_layout_bool(object, u"VISIBLE", true);
        entity.combat_targetable =
            enabled && unit_type == u"MONSTER" &&
            optional_layout_bool(object, u"TARGETABLE", true) &&
            !optional_layout_bool(object, u"INVINCIBLE", false);
        ++placed_entity_count_;
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
    entity.display_name = resource.display_name;
    entity.unit_type = resource.unit_type;
    entity.position = position;
    entity.level = spawn_level_;
    if (resource.kind == MasterResourceKind::item) {
        const auto definition = definitions_->load(resource);
        entity.mesh_path = unit_model_path(*definition);
        if (const auto* entry = definitions_->archive().find_normalized(entity.mesh_path))
            entity.mesh_path = entry->name;
        // Match the loaded UNIT/BASEFILE value, not optional master-table metadata.
        const auto* create_as = optional_text(definition->root, u"CREATEAS");
        entity.inventory_eligible = create_as && normalized(*create_as) == u"EQUIPMENT";
        if (create_as && normalized(*create_as) == u"GOLD" && gold_graph_) {
            const auto low = optional_number(*definition, u"MINVALUE", 100);
            const auto high = optional_number(*definition, u"MAXVALUE", 100);
            if (!std::isfinite(low) || !std::isfinite(high) || low < 0 || high < low)
                throw EntityWorldError("invalid gold MINVALUE/MAXVALUE");
            // prototype context: portable rank = spawn_level - 1. Normal only.
            // The original uses a separate volatile RNG; this portable world stream
            // is reproducible, but NOT a claim of identical original random ordering.
            const auto percent = random_.between(low, high);
            entity.gold_amount = evaluated_world_gold(gold_graph_->value(
                static_cast<float>(spawn_level_)), percent);
        }
        entity.two_handed = unit_types_->is_a_id(resource.unit_type, 10);
        const auto effects = load_constant_attack_effects(
            *definition, attack_effect_catalog_ ? &*attack_effect_catalog_ : nullptr);
        entity.armor_item = roll_armor_item(
            resource, *definition, player_armor_graph_, random_);
        if (entity.armor_item) entity.armor_item->attack_effects = effects;
        if (auto weapon = load_weapon_prototype(
                resource, *definition, player_weapon_damage_graph_)) {
            weapon->attack_traits = weapon_attack_traits(resource.unit_type, *unit_types_);
            weapon->attack_hand = weapon->attack_traits.family == WeaponAttackFamily::bow ?
                AttackHand::left : AttackHand::right;
            weapon->attack_effects = effects;
            weapon->ai_attack_cooldown = optional_number(*definition, u"AI_ATTACKCOOLDOWN", 0);
            entity.weapon_item = roll_weapon_item(*weapon, random_);
            entity.weapon_item->prototype.mesh_path = entity.mesh_path;
        }
    } else if (resource.kind == MasterResourceKind::monster) {
        const auto definition = definitions_->load(resource);
        entity.mesh_path = unit_model_path(*definition);
        if (const auto* entry = definitions_->archive().find_normalized(entity.mesh_path))
            entity.mesh_path = entry->name;
        entity.treasure = load_treasure_profile(*definition);
        // CCharacter::unitInit @0x852c4d reads unit data XP only as a nonzero
        // gate; CCharacter::setLevel @0x83ecea then overwrites the reward with
        // trunc((EXPERIENCE_MONSTER(level)/100) * graph). Zero stays unknown.
        if (experience_graph_ && optional_number(*definition, u"XP", 0) != 0) {
            entity.experience_reward = original_monster_experience(
                experience_graph_->value(static_cast<float>(spawn_level_)));
        }
        const auto minimum_health_percent =
            optional_number(*definition, u"MINHP", 1.0F);
        const auto maximum_health_percent =
            optional_number(*definition, u"MAXHP", minimum_health_percent);
        const auto health_scale = monster_health_graph_.value(
            static_cast<float>(spawn_level_));
        const auto health_low = health_scale *
            std::min(minimum_health_percent, maximum_health_percent) / 100.0F;
        const auto health_high = health_scale *
            std::max(minimum_health_percent, maximum_health_percent) / 100.0F;
        const auto rolled_health = health_high > health_low
            ? random_.between(health_low, health_high)
            : health_low;
        entity.maximum_health = std::max(1.0F, std::trunc(rolled_health));
        entity.health = entity.maximum_health;
        const auto minimum_damage_percent =
            optional_number(*definition, u"MINDAMAGE", 0.0F);
        const auto maximum_damage_percent =
            optional_number(*definition, u"MAXDAMAGE", minimum_damage_percent);
        const auto damage_scale = monster_damage_graph_.value(
            static_cast<float>(spawn_level_));
        entity.minimum_damage = std::max(
            0, static_cast<std::int32_t>(std::ceil(
                   damage_scale * std::min(minimum_damage_percent,
                                           maximum_damage_percent) / 100.0F)));
        entity.maximum_damage = std::max(
            entity.minimum_damage,
            static_cast<std::int32_t>(std::ceil(
                damage_scale * std::max(minimum_damage_percent,
                                        maximum_damage_percent) / 100.0F)));
        const auto armor_percent = optional_number(*definition, u"ARMOR", 0.0F);
        entity.damage_defense.natural_armor = std::max(
            0, static_cast<std::int32_t>(std::ceil(
                   monster_armor_graph_.value(static_cast<float>(spawn_level_)) *
                   armor_percent / 100.0F)));
        entity.damage_defense.defense_attribute = std::max(
            0, static_cast<std::int32_t>(
                   optional_number(*definition, u"DEFENSE", 0.0F)));
        constexpr std::array<const char16_t*, 7> armor_properties{
            u"ARMOR_PHYSICAL", u"ARMOR_MAGICAL", u"ARMOR_FIRE", u"ARMOR_ICE",
            u"ARMOR_ELECTRIC", u"ARMOR_POISON", u"ARMOR_ALL"};
        const auto scaled_natural_armor = entity.damage_defense.natural_armor;
        for (std::size_t index = 0; index < armor_properties.size(); ++index) {
            const auto percent = optional_number(
                *definition, armor_properties[index], -1.0F);
            if (percent == -1.0F) {
                continue;
            }
            const auto armor = static_cast<std::int32_t>(std::ceil(
                static_cast<float>(scaled_natural_armor) * percent / 100.0F));
            if (index == static_cast<std::size_t>(DamageType::physical)) {
                if (armor > 0) {
                    entity.damage_defense.natural_armor = armor;
                }
            } else {
                entity.damage_defense.elemental_armor[index] = armor;
            }
        }
        entity.walking_speed = optional_number(*definition, u"WALKINGSPEED", 1.0F);
        entity.running_speed = optional_number(
            *definition, u"RUNNINGSPEED", entity.walking_speed);
        entity.attack_speed = optional_number(*definition, u"ATTACKSPEED", 100.0F);
        entity.ai_attack_cooldown = optional_number(
            *definition, u"AI_ATTACKCOOLDOWN", 0.0F);
        entity.sight_radius = optional_number(*definition, u"SIGHT_RADIUS", 0.0F);
        entity.reach_bonus = optional_number(*definition, u"REACH_BONUS", 0.0F);
        entity.attacks.innate.push_back(load_innate_attack(
            *definition, entity.minimum_damage, entity.maximum_damage));
        entity.attacks.no_unarmed_attacks = attack_unit_bool(*definition, u"NO_UNARMED_ATTACKS", false);
        entity.attacks.use_weapon_damage = attack_unit_bool(*definition, u"USEWEAPONDAMAGE", true);
        entity.attack_character = load_attack_character_values(
            *definition, attack_effect_catalog_ ? &*attack_effect_catalog_ : nullptr);
        equip_monster_attack(entity, *definition);
        entity.attack_range = std::max(
            0.5F, entity.weapon_range + entity.reach_bonus + 0.2F);
        entity.motion_radius = optional_number(*definition, u"MOTION_RADIUS", 0.0F);
        entity.follow_radius = optional_number(
            *definition, u"FOLLOW_RADIUS", entity.sight_radius);
        if (!std::isfinite(entity.maximum_health)) {
            throw EntityWorldError("Runtime monster health is invalid");
        }
        if (!std::isfinite(entity.walking_speed) || entity.walking_speed < 0.0F ||
            !std::isfinite(entity.running_speed) || entity.running_speed < 0.0F) {
            throw EntityWorldError("Runtime monster movement speed is invalid");
        }
        // Keep finite negative cooldowns: the original clamps before adding
        // the UNIT value, not after it. Non-finite resource values are invalid
        // portable inputs, not a claimed recovery of original error handling.
        if (!std::isfinite(entity.ai_attack_cooldown)) {
            throw EntityWorldError("Runtime monster AI attack cooldown is invalid");
        }
        if (!std::isfinite(entity.attack_speed) || entity.attack_speed < 0.0F) {
            throw EntityWorldError("Runtime monster attack speed is invalid");
        }
        if (!std::isfinite(entity.sight_radius) || entity.sight_radius < 0.0F ||
            !std::isfinite(entity.reach_bonus) || entity.reach_bonus < 0.0F ||
            !std::isfinite(entity.weapon_range) || entity.weapon_range < 0.0F ||
            !std::isfinite(entity.attack_range) || entity.attack_range < 0.0F ||
            !std::isfinite(entity.motion_radius) || entity.motion_radius < 0.0F ||
            !std::isfinite(entity.follow_radius) || entity.follow_radius < 0.0F) {
            throw EntityWorldError("Runtime monster perception or reach is invalid");
        }
        entity.combat_targetable = true;
    }
    entities_.push_back(std::move(entity));
    ++stats.entities_created;
}

void RuntimeEntityWorld::equip_monster_attack(
    RuntimeEntity& entity, const UnitDefinition& definition) {
    const auto equip = [&](const MasterResourceRecord* record, AttackHand hand) {
        if (!record || record->kind != MasterResourceKind::item || record->do_not_create) return false;
        const auto unit = definitions_->load(*record);
        const auto* create_as = optional_text(unit->root, u"CREATEAS");
        if (!create_as || normalized(*create_as) != u"EQUIPMENT" || !unit->find_property(u"RANGE")) return false;
        // Only weapon types may occupy this attack path; shields stay outside it.
        if (!unit_types_->is_a_id(record->unit_type, 8)) return false;
        const auto cooldown = optional_number(*unit, u"AI_ATTACKCOOLDOWN", 0);
        if (!std::isfinite(cooldown)) throw EntityWorldError("Runtime weapon AI attack cooldown is invalid");
        WeaponPrototype prototype;
        if (auto loaded = load_weapon_prototype(*record, *unit, player_weapon_damage_graph_))
            prototype = std::move(*loaded);
        else {
            // No fabricated damage: original zero-base metadata still selects a
            // weapon animation when USEWEAPONDAMAGE=false uses innate damage.
            prototype.guid = record->guid; prototype.unit_type = record->unit_type;
            prototype.range = optional_number(*unit, u"RANGE", 0);
            prototype.strike_range = optional_number(*unit, u"STRIKERANGE", prototype.range);
            const auto raw_speed = optional_number(*unit, u"SPEED", 100);
            if (!std::isfinite(raw_speed) || raw_speed <= 0 ||
                static_cast<double>(raw_speed) > std::numeric_limits<std::int32_t>::max() ||
                !std::isfinite(prototype.range) || prototype.range < 0 ||
                !std::isfinite(prototype.strike_range) || prototype.strike_range < 0)
                throw EntityWorldError("Runtime weapon attack metadata is invalid");
            prototype.speed = static_cast<std::int32_t>(raw_speed);
        }
        prototype.attack_traits = weapon_attack_traits(record->unit_type, *unit_types_);
        prototype.attack_effects = load_constant_attack_effects(
            *unit, attack_effect_catalog_ ? &*attack_effect_catalog_ : nullptr);
        prototype.ai_attack_cooldown = cooldown;
        auto item = roll_weapon_item(prototype, random_);
        if (!unit->find_property(u"MINDAMAGE") || !unit->find_property(u"MAXDAMAGE"))
            item.minimum_damage = item.maximum_damage = 0;
        auto description = describe_weapon_attack(item, hand);
        if (hand == AttackHand::right) entity.attacks.right = std::move(description);
        else entity.attacks.left = std::move(description);
        if (entity.equipped_attack_name.empty() || hand == AttackHand::right) {
            entity.equipped_attack_name = record->name;
            entity.equipped_ai_attack_cooldown = cooldown;
            entity.weapon_range = prototype.range;
        }
        return true;
    };
    for (auto group = definition.root.groups.rbegin(); group != definition.root.groups.rend(); ++group) {
        if (group->name != u"EQUIPMENT") continue;
        for (const auto hand : {AttackHand::right, AttackHand::left}) {
            const auto* direct = optional_text(*group, hand == AttackHand::right ? u"RIGHTHAND" : u"LEFTHAND");
            if (direct && equip(resources_->find_case_insensitive(MasterResourceKind::item, *direct), hand)) continue;
            const auto* spawn = optional_text(*group, hand == AttackHand::right ? u"SPAWNRIGHTHAND" : u"SPAWNLEFTHAND");
            if (!spawn) continue;
            for (const auto& leaf : spawn_classes_->roll(*spawn, random_)) {
                const MasterResourceRecord* record = nullptr;
                if (leaf.kind == SpawnLeafKind::unit_type) record = unit_types_->roll(leaf.value, spawn_level_, random_);
                else record = resources_->find_any(leaf.value);
                if (equip(record, hand)) break;
            }
        }
        return;
    }
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
        if (request.action != SpawnAction::spawn) {
            ++stats.control_requests;
            for (auto& entity : entities_) {
                if (entity.spawner_id != request.spawner_id) {
                    continue;
                }
                if (request.action == SpawnAction::hide_and_disable) {
                    if (entity.enabled || entity.visible) {
                        ++stats.entities_hidden;
                    }
                    entity.enabled = false;
                    entity.visible = false;
                    continue;
                }
                if (entity.alive || entity.enabled || entity.visible) {
                    ++stats.entities_destroyed;
                }
                entity.health = 0.0F;
                entity.alive = false;
                entity.enabled = false;
                entity.visible = false;
                entity.combat_targetable = false;
            }
            logic.synchronize_spawned_units(
                request.spawner_id, alive_monster_count(request.spawner_id));
            continue;
        }
        ++stats.spawn_requests;
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

void RuntimeEntityWorld::record_death(RuntimeEntity& entity) {
    // Snapshot even a no-loot death: it still owes its spawner a notification.
    // Allocate before committing death; entity pointers remain valid until flush.
    pending_deaths_.push_back({entity.id, entity.position, entity.treasure,
                              entity.spawner_id, entity.drops_loot});
    entity.health = 0.0F;
    entity.alive = false;
}

LootResolutionStats RuntimeEntityWorld::resolve_death_loot(LogicRuntime& logic) {
    LootResolutionStats stats;
    while (!pending_deaths_.empty()) {
        auto death = std::move(pending_deaths_.front());
        pending_deaths_.pop_front();
        // Consume once before generation. Malformed resource exceptions remain
        // fatal to this drain; no partly spawned death may be rerolled on retry.
        // Other deaths remain queued instead of being lost with a moved batch.
        const auto generate = [&] {
            ++stats.deaths;
            auto name = death.treasure.spawn_class;
            auto rolls = 1;
            if (!name.empty() && spawn_classes_->find(name)) {
                rolls = random_.integer_between(death.treasure.minimum_rolls,
                                                 death.treasure.maximum_rolls);
            } else {
                // CCharacter::die null table -> CLevel::rollTreasure @0x95d0b0.
                if (!name.empty()) ++stats.missing_classes;
                name = u"BARREL_TREASURE";
            }
            if (!spawn_classes_->find(name)) { ++stats.missing_classes; return; }
            std::size_t leaves_created = 0;
            for (int roll = 0; roll < rolls; ++roll) {
                const auto leaves = spawn_classes_->roll(name, random_);
                leaves_created += leaves.size();
                if (leaves_created > 4096U)
                    throw EntityWorldError("Death loot exceeds the portable spawn safety budget");
                ++stats.class_rolls;
                for (const auto& leaf : leaves) {
                    const auto before = entities_.size();
                    // Drops are independent world items, NOT children of the dead
                    // unit's spawner. Hide/Destroy on that spawner must not eat loot.
                    create_leaf(0, death.position, leaf, stats.spawns);
                    for (auto i = before; i < entities_.size(); ++i)
                        entities_[i].loot_source_id = death.source_id;
                }
            }
        };
        if (death.drops_loot) generate();
        // original-code CCharacter::die @0x838ed0: treasure precedes
        // broadcastKilled. The portable phase is deferred for vector safety;
        // it is not a claim of original synchronous/global character ordering.
        if (death.spawner_id != 0) logic.notify_monster_killed(death.spawner_id);
    }
    return stats;
}

bool RuntimeEntityWorld::kill(std::uint64_t entity_id, LogicRuntime& /*logic*/) {
    auto* found = find(entity_id);
    if (found == nullptr || !found->alive || !found->enabled ||
        !found->combat_targetable ||
        found->kind != MasterResourceKind::monster) {
        return false;
    }
    record_death(*found);
    return true;
}

DamageResult RuntimeEntityWorld::apply_damage(std::uint64_t entity_id, float damage,
                                               LogicRuntime& /*logic*/, bool player_credit) {
    auto* entity = find(entity_id);
    if (entity == nullptr || !entity->alive || !entity->enabled ||
        !entity->combat_targetable ||
        entity->kind != MasterResourceKind::monster ||
        !std::isfinite(damage) || !(damage > 0.0F)) {
        return {};
    }
    const auto remaining_health = std::max(0.0F, entity->health - damage);
    const bool killed = remaining_health <= 0.0F;
    if (killed) {
        record_death(*entity);
        entity->player_kill = player_credit;
    } else entity->health = remaining_health;
    return {true, killed, entity->health};
}

bool RuntimeEntityWorld::pick_up(std::uint64_t entity_id, LogicRuntime& logic) {
    auto* found = find(entity_id);
    if (found == nullptr || !found->alive || !found->enabled || !found->visible ||
        found->kind != MasterResourceKind::item) {
        return false;
    }
    found->alive = false;
    found->visible = false;
    found->enabled = false;
    if (found->spawner_id != 0) logic.notify_item_picked_up(found->spawner_id);
    return true;
}

RuntimeEntity* RuntimeEntityWorld::find(std::uint64_t entity_id) noexcept {
    const auto found = std::find_if(entities_.begin(), entities_.end(),
                                    [entity_id](const auto& entity) {
                                        return entity.id == entity_id;
                                    });
    return found == entities_.end() ? nullptr : &*found;
}

const RuntimeEntity* RuntimeEntityWorld::find(std::uint64_t entity_id) const noexcept {
    const auto found = std::find_if(entities_.begin(), entities_.end(),
                                    [entity_id](const auto& entity) {
                                        return entity.id == entity_id;
                                    });
    return found == entities_.end() ? nullptr : &*found;
}

const RuntimeEntity* RuntimeEntityWorld::find_layout_entity(
    std::int64_t layout_object_id) const noexcept {
    const auto found = std::find_if(entities_.begin(), entities_.end(),
                                    [layout_object_id](const auto& entity) {
                                        return entity.layout_object_id == layout_object_id;
                                    });
    return found == entities_.end() ? nullptr : &*found;
}

const RuntimeEntity* RuntimeEntityWorld::nearest_alive_monster(
    const std::array<float, 3>& position, float maximum_distance) const noexcept {
    if (!std::isfinite(maximum_distance) || maximum_distance < 0.0F) {
        return nullptr;
    }
    const RuntimeEntity* result = nullptr;
    float nearest_squared = maximum_distance * maximum_distance;
    for (const auto& entity : entities_) {
        if (!entity.alive || !entity.enabled || !entity.combat_targetable ||
            entity.kind != MasterResourceKind::monster) {
            continue;
        }
        const auto delta_x = entity.position[0] - position[0];
        const auto delta_z = entity.position[2] - position[2];
        const auto distance_squared = delta_x * delta_x + delta_z * delta_z;
        if (distance_squared <= nearest_squared) {
            nearest_squared = distance_squared;
            result = &entity;
        }
    }
    return result;
}

const RuntimeEntity* RuntimeEntityWorld::nearest_alive_item(
    const std::array<float, 3>& position, float maximum_distance, bool inventory_only) const noexcept {
    if (!std::isfinite(maximum_distance) || maximum_distance < 0.0F) {
        return nullptr;
    }
    const RuntimeEntity* nearest = nullptr;
    auto nearest_distance = maximum_distance;
    for (const auto& entity : entities_) {
        if (!entity.alive || !entity.enabled || !entity.visible ||
            entity.kind != MasterResourceKind::item || (inventory_only && !entity.inventory_eligible && !entity.gold_amount)) {
            continue;
        }
        const auto distance = std::hypot(entity.position[0] - position[0],
                                         entity.position[2] - position[2]);
        if (distance <= nearest_distance) {
            nearest = &entity;
            nearest_distance = distance;
        }
    }
    return nearest;
}

} // namespace torchlight
