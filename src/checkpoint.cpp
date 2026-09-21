#include "torchlight/checkpoint.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
#include <set>
#include <type_traits>
#include <unordered_set>

namespace torchlight {
namespace {
void require(bool ok, const char *message) {
    if (!ok)
        throw CheckpointError(message);
}
void scalar(float value, const char *message) {
    require(std::isfinite(value) && std::abs(value) <= 1.0e9F, message);
}
void position(const std::array<float, 3> &v) {
    for (const auto n : v)
        scalar(n, "invalid checkpoint position");
}
void defense(const DamageDefense &d) {
    const auto valid = [](std::int32_t v) { return v >= -1000000 && v <= 1000000; };
    require(valid(d.natural_armor) && valid(d.defense_attribute),
            "checkpoint defense outside supported range");
    for (const auto v : d.elemental_armor)
        require(valid(v), "invalid checkpoint elemental defense");
}
void effects(const AttackEffects &e) {
    require(e.values.size() <= 1024 && e.unresolved.size() <= 1024, "too many saved effects");
    for (const auto &v : e.values) {
        require(v.type < 145 && v.damage_type <= 7, "invalid saved effect type");
        scalar(v.value, "invalid saved effect value");
    }
    for (const auto &s : e.unresolved)
        require(s.size() <= 4096, "oversized unresolved effect");
}
void traits(const WeaponAttackTraits &t) {
    require(static_cast<unsigned>(t.family) <= static_cast<unsigned>(WeaponAttackFamily::polearm),
            "invalid saved weapon family");
}
void delivery(WeaponDelivery value) {
    require(static_cast<unsigned>(value) <= static_cast<unsigned>(WeaponDelivery::direct_typed), "invalid saved weapon delivery");
}
void attack(const AttackDescription &a) {
    delivery(a.delivery);
    for (const auto value : a.damage_bonus) require(value >= 0 && value <= 100000000, "invalid saved damage bonus");
    require(a.delivery != WeaponDelivery::direct_typed || a.damage_allocation_known, "unresolved saved typed attack");
    require(a.minimum_damage >= 0 && a.maximum_damage >= a.minimum_damage &&
                a.maximum_damage <= 100000000,
            "invalid saved attack damage");
    require(static_cast<unsigned>(a.hand) <= static_cast<unsigned>(AttackHand::left),
            "invalid saved attack hand");
    scalar(a.range, "invalid saved attack range");
    scalar(a.strike_range, "invalid saved strike range");
    scalar(a.speed_denominator, "invalid saved speed denominator");
    if (a.equipment_ai_cooldown)
        scalar(*a.equipment_ai_cooldown, "invalid saved weapon AI clock");
    traits(a.traits);
    effects(a.effects);
    require(a.animation_prefix.size() <= 4096 && a.unavailable_reason.size() <= 4096,
            "oversized saved attack name");
}
void weapon(const WeaponItem &w) {
    require(w.minimum_damage >= 0 && w.maximum_damage >= w.minimum_damage &&
                w.maximum_damage <= 100000000,
            "invalid saved item damage");
    const auto &p = w.prototype;
    delivery(p.delivery);
    for (const auto value : w.damage_bonus) require(value >= 0 && value <= 100000000, "invalid saved item damage bonus");
    require(p.delivery != WeaponDelivery::direct_typed || p.damage_percent.has_value(), "unresolved saved typed item");
    if (p.damage_percent) {
        for (const auto value : *p.damage_percent) require(value >= -1000000 && value <= 1000000, "invalid saved allocation percentage");
        require((*p.damage_percent)[1] == 0 && (*p.damage_percent)[6] == 0, "unsupported saved allocation channel");
    }
    require(p.speed > 0 && p.level >= 0 && p.level <= 100000, "invalid saved item speed/level");
    scalar(p.range, "invalid saved weapon range");
    scalar(p.strike_range, "invalid saved strike range");
    scalar(p.base_weapon_damage, "invalid saved base weapon damage");
    scalar(p.ai_attack_cooldown, "invalid weapon cooldown");
    require(static_cast<unsigned>(p.attack_hand) <= static_cast<unsigned>(AttackHand::left),
            "invalid weapon hand");
    traits(p.attack_traits);
    effects(p.attack_effects);
}
void armor(const ArmorItem &a) {
    require(static_cast<std::size_t>(a.slot) < static_cast<std::size_t>(ArmorSlot::count),
            "invalid saved armor slot");
    require(a.armor >= 0 && a.armor <= 1000000, "invalid saved armor");
    defense(a.damage_defense);
    effects(a.attack_effects);
}
void item(const InventoryItem &i) {
    if (i.consumable) {
        try { validate_consumable(*i.consumable); } catch (const std::exception& e) { throw CheckpointError(e.what()); }
        require(!i.weapon && !i.armor, "consumable equipment conflict");
    }
    require(!(i.weapon && i.armor), "saved item cannot be both weapon and armor");
    require(i.mesh_path.size() <= 4096 && i.name.size() <= 4096 && i.display_name.size() <= 4096 &&
                i.unit_type.size() <= 4096,
            "oversized saved item metadata");
    if (i.weapon) {
        weapon(*i.weapon);
        require(i.weapon->prototype.guid == i.resource_guid, "weapon GUID mismatch");
    }
    if (i.armor) {
        armor(*i.armor);
        require(i.armor->guid == i.resource_guid, "armor GUID mismatch");
    }
}
void entity(const RuntimeEntity &e) {
    require(static_cast<unsigned>(e.kind) <= static_cast<unsigned>(MasterResourceKind::prop),
            "invalid entity kind");
    if (e.consumable) {
        try { validate_consumable(*e.consumable); } catch (const std::exception& ex) { throw CheckpointError(ex.what()); }
        require(e.kind == MasterResourceKind::item && e.inventory_eligible && !e.weapon_item && !e.armor_item && !e.gold_amount,
            "invalid world consumable ownership");
    }
    require(e.level > 0 && e.level <= 100000, "invalid entity level");
    require(!e.gold_amount || (*e.gold_amount >= 0 && e.kind == MasterResourceKind::item &&
        !e.inventory_eligible && !e.armor_item && !e.weapon_item), "invalid saved world gold");
    require(!e.experience_reward || (*e.experience_reward >= 0 && e.kind == MasterResourceKind::monster),
        "invalid saved monster experience");
    require(!e.player_kill || (e.kind == MasterResourceKind::monster && !e.alive && e.health == 0),
        "invalid saved player kill credit");
    require(!e.reward_claimed || e.player_kill, "reward claimed without player kill");
    position(e.position);
    scalar(e.health, "invalid saved HP");
    scalar(e.maximum_health, "invalid saved max HP");
    require(e.health >= 0 && e.maximum_health >= e.health, "saved entity HP outside maximum");
    require(e.minimum_damage >= 0 && e.maximum_damage >= e.minimum_damage &&
                e.maximum_damage <= 100000000,
            "invalid saved entity damage");
    for (const auto v :
         {e.walking_speed, e.running_speed, e.attack_speed, e.ai_attack_cooldown, e.sight_radius,
          e.reach_bonus, e.weapon_range, e.attack_range, e.motion_radius, e.follow_radius})
        scalar(v, "invalid entity scalar");
    if (e.equipped_ai_attack_cooldown)
        scalar(*e.equipped_ai_attack_cooldown, "invalid equipped AI cooldown");
    require(e.treasure.minimum_rolls >= 0 && e.treasure.maximum_rolls >= e.treasure.minimum_rolls &&
                e.treasure.maximum_rolls <= 10000,
            "invalid saved treasure rolls");
    if (e.weapon_item)
        weapon(*e.weapon_item);
    if (e.armor_item)
        armor(*e.armor_item);
    defense(e.damage_defense);
    require(e.attacks.innate.size() <= 256, "too many innate attacks");
    for (const auto &a : e.attacks.innate)
        attack(a);
    if (e.attacks.right)
        attack(*e.attacks.right);
    if (e.attacks.left)
        attack(*e.attacks.left);
    const auto &c = e.attack_character;
    for (const auto v :
         {c.reach_bonus, c.scale, c.range_multiplier, c.collision_radius, c.damage_multiplier})
        scalar(v, "invalid attack character value");
    require(c.strength >= -1000000 && c.strength <= 1000000 && c.dexterity >= -1000000 &&
                c.dexterity <= 1000000 && c.magic >= -1000000 && c.magic <= 1000000,
            "saved character attributes outside supported range");
    effects(c.effects);
}
void address(const DungeonAddress &a) {
    require(!a.dungeon_name.empty() && a.dungeon_name.size() <= 128 && a.depth >= 0 &&
                a.depth <= 100000,
            "invalid saved dungeon address");
    for (const auto c : a.dungeon_name)
        require((c >= u'a' && c <= u'z') || (c >= u'A' && c <= u'Z') || (c >= u'0' && c <= u'9') ||
                    c == u'_' || c == u'-' || c == u' ',
                "unsafe saved dungeon name");
}
char16_t upper(char16_t c) {
    return c >= u'a' && c <= u'z' ? static_cast<char16_t>(c - 32) : c;
}
// Non-cryptographic identity of immutable external inputs, NOT authentication.
struct Identity {
    std::uint64_t value = UINT64_C(14695981039346656037);
    void byte(std::uint8_t n) {
        value = (value ^ n) * UINT64_C(1099511628211);
    }
    template <class T> void integer(T n) {
        using U = std::make_unsigned_t<T>;
        auto u = static_cast<U>(n);
        for (std::size_t i = 0; i < sizeof(U); ++i) {
            byte(static_cast<std::uint8_t>(u));
            u >>= 8U;
        }
    }
    void number(float f) {
        std::uint32_t b;
        std::memcpy(&b, &f, sizeof b);
        integer(b);
    }
    template <class C> void text(const std::basic_string<C> &s) {
        integer(static_cast<std::uint64_t>(s.size()));
        for (const auto c : s)
            integer(c);
    }
};
} // namespace
PlayerCheckpoint CheckpointAccess::capture(const PlayerSession &p) {
    PlayerCheckpoint s;
    s.inventory = {p.inventory_.next_id_, p.inventory_.items_, p.inventory_.equipped_};
    s.gold = p.gold_;
    s.hardcore = p.hardcore_;
    s.health = p.health_.health_;
    s.maximum_health = p.health_.maximum_health_;
    s.base_health = p.health_.base_health_;
    require(!p.skill_cast_.active(), "save requires a completed or cancelled cast");
    require(!p.has_pending_skill_missiles(), "save requires completed skill projectiles");
    s.active_recovery = p.active_recovery_;
    s.skills = p.skills_;
    s.mana = p.health_.mana_;
    s.maximum_mana = p.health_.maximum_mana_;
    s.base_defense = p.health_.base_damage_defense_;
    s.combat_random = p.combat_.random_.state_;
    s.prefer_left = p.combat_.prefer_left_;
    if (p.progression_rules_) s.progression = p.progression_;
    validate(s);
    return s;
}
WorldCheckpoint CheckpointAccess::capture(const RuntimeEntityWorld &w) {
    require(w.pending_deaths_.empty(), "save requires finalizing pending deaths first");
    require(w.placed_entity_count_ <= std::numeric_limits<std::uint32_t>::max(),
            "too many placed entities");
    return {w.next_entity_id_, w.random_.state_, static_cast<std::uint32_t>(w.placed_entity_count_),
            w.spawn_level_, w.entities_, w.population_generated_};
}
LogicCheckpoint CheckpointAccess::capture(const LogicRuntime &l) {
    require(!l.processing_events_ && l.pending_actions_.empty() && l.spawn_requests_.empty() &&
                l.warp_requests_.empty(),
            "save requires a settled logic/warp boundary");
    LogicCheckpoint s;
    s.random_state = l.random_.state_;
    for (const auto &pair : l.states_)
        s.entries.push_back({pair.first, pair.second});
    std::sort(s.entries.begin(), s.entries.end(),
              [](const auto &a, const auto &b) { return a.id < b.id; });
    return s;
}
EnemyCheckpoint CheckpointAccess::capture(const EnemyController &e) {
    EnemyCheckpoint s;
    s.random_state = e.random_.state_;
    for (const auto &pair : e.states_)
        s.entries.push_back({pair.first, pair.second.alerted, pair.second.prefer_left,
                             pair.second.ai_cooldown.remaining});
    std::sort(s.entries.begin(), s.entries.end(),
              [](const auto &a, const auto &b) { return a.id < b.id; });
    return s;
}
void CheckpointAccess::validate(const PlayerCheckpoint &s) {
    try { validate_active_recovery(s.active_recovery); } catch (const std::exception& e) { throw CheckpointError(e.what()); }
    if (s.skills) { try { validate_skill_checkpoint(*s.skills); } catch(const std::exception& e) {throw CheckpointError(e.what());} }
    require(s.gold >= 0, "negative saved gold");
    if (s.progression) {
        try { validate_progression(*s.progression); }
        catch (const std::invalid_argument& e) { throw CheckpointError(e.what()); }
    }
    if (s.base_health) require(*s.base_health >= 1, "invalid saved base HP");
    scalar(s.health, "invalid player HP");
    scalar(s.maximum_health, "invalid player max HP");
    require(s.maximum_health >= 1 && s.health >= 0 && s.health <= s.maximum_health,
            "player HP out of range");
    require(s.mana.has_value() == s.maximum_mana.has_value(), "inconsistent known mana");
    if (s.mana) {
        scalar(*s.mana, "invalid mana");
        scalar(*s.maximum_mana, "invalid max mana");
        require(*s.mana >= 0 && *s.mana <= *s.maximum_mana, "mana out of range");
    }
    defense(s.base_defense);
    require(s.inventory.items.size() <= 8192, "inventory checkpoint too large");
    require(s.inventory.next_id != 0, "inventory ID exhausted");
    std::unordered_set<std::uint64_t> ids;
    for (const auto &i : s.inventory.items) {
        require(i.id != 0 && i.id < s.inventory.next_id && ids.insert(i.id).second,
                "invalid or duplicate inventory ID");
        item(i);
    }
    std::unordered_set<std::uint64_t> equipped;
    bool two_handed = false;
    for (std::size_t n = 0; n < s.inventory.slots.size(); ++n) {
        const auto id = s.inventory.slots[n];
        if (!id)
            continue;
        const auto it = std::find_if(s.inventory.items.begin(), s.inventory.items.end(),
                                     [&](const auto &i) { return i.id == id; });
        require(it != s.inventory.items.end() && equipped.insert(id).second, "invalid equipped ID");
        const auto slot = PlayerInventory::slot_for(*it);
        require(slot && static_cast<std::size_t>(*slot) == n, "item in wrong saved slot");
        if (n == 0)
            two_handed = it->two_handed;
    }
    require(!two_handed || !s.inventory.slots[static_cast<std::size_t>(InventorySlot::shield)],
            "two-handed/shield conflict in save");
}
PlayerSession CheckpointAccess::restore_player(const PlayerPrototype &proto,
                                               const PlayerCheckpoint &s, std::uint32_t seed,
                                               const UnitTypeHierarchy *hierarchy) {
    validate(s);
    auto prototype = proto;
    prototype.starting_weapon.reset();
    prototype.hardcore = s.hardcore;
    PlayerSession p(prototype, seed, hierarchy);
    p.inventory_.next_id_ = s.inventory.next_id;
    p.inventory_.items_ = s.inventory.items;
    p.inventory_.equipped_ = s.inventory.slots;
    p.gold_ = s.gold;
    p.health_.base_damage_defense_ = s.base_defense;
    // Legacy v1-v5 stored the class flat-armor roll in raw base armor. Recover
    // that same roll rather than rerolling it or applying a percent to it.
    const auto armor_bonus = static_cast<std::int64_t>(s.base_defense.natural_armor) -
        proto.damage_defense.natural_armor;
    require(armor_bonus >= std::min(proto.minimum_armor_bonus, proto.maximum_armor_bonus) &&
            armor_bonus <= std::max(proto.minimum_armor_bonus, proto.maximum_armor_bonus),
            "saved class armor roll disagrees with resource range");
    p.health_.base_armor_bonus_ = static_cast<std::int32_t>(armor_bonus);
    // V1/v2 stored only the then-unmodified maximum. It is the migration base,
    // never the already-buffed maximum in a v3 save.
    require(s.base_health || (std::trunc(s.maximum_health) == s.maximum_health &&
                static_cast<double>(s.maximum_health) <= std::numeric_limits<std::int32_t>::max()),
            "legacy saved base HP is not an integer");
    // Do not evaluate a float-to-int fallback for a v3 value: rounding the
    // valid INT32_MAX base to float can put the derived maximum above int32.
    const auto saved_base = s.base_health ? *s.base_health : static_cast<std::int32_t>(s.maximum_health);
    p.health_.base_health_ = saved_base;
    p.active_recovery_ = s.active_recovery;
    if (s.skills) p.skills_ = *s.skills;
    if (s.progression) {
        require(bool(p.progression_rules_), "saved progression requires class graphs");
        try {
            validate_progression(*s.progression, *p.progression_rules_, p.spent_skill_points());
            p.progression_ = *s.progression;
            require(p.attributes()[3] == s.base_defense.defense_attribute,
                    "saved defense disagrees with allocated attributes");
            p.refresh_attributes();
            if (p.progression_.level > 1) {
                const auto& rule = p.progression_rules_->at(p.progression_.level);
                p.health_.set_progression_vitals(rule.maximum_health, rule.base_mana);
                require(rule.maximum_health == saved_base,
                        "saved base health disagrees with level graph");
            }
        } catch (const std::invalid_argument& e) { throw CheckpointError(e.what()); }
    }
    p.refresh_equipment(); // validates/recomputes current resource-dependent derived values
    require(!s.base_health || p.health_.maximum_health_ == s.maximum_health,
            "saved health maximum disagrees with base/equipment resources");
    require(p.health_.maximum_mana_ == s.maximum_mana,
            "saved mana maximum disagrees with class/equipment resources");
    p.health_.health_ = std::min(s.health, p.health_.maximum_health_);
    p.health_.mana_ = s.mana;
    p.combat_.random_.state_ = s.combat_random;
    p.combat_.prefer_left_ = s.prefer_left;
    p.enter_level();
    return p;
}
void CheckpointAccess::validate(const FloorCheckpoint &s) {
    address(s.address);
    position(s.player_position);
    position(s.recovery_anchor);
    scalar(s.player_angle, "bad saved facing");
    scalar(s.recovery_angle, "bad saved recovery facing");
    scalar(s.floor_offset, "bad floor offset");
    require(s.world.entities.size() <= 50000 && s.world.placed_count <= s.world.entities.size() &&
                s.world.next_id != 0,
            "invalid saved world size/IDs");
    require(s.world.spawn_level > 0 && s.world.spawn_level <= 100000, "invalid spawn rank");
    std::unordered_set<std::uint64_t> ids;
    std::unordered_set<std::int64_t> placed_ids, logic_ids;
    for (std::size_t i = 0; i < s.world.entities.size(); ++i) {
        const auto &e = s.world.entities[i];
        entity(e);
        require(e.id != 0 && e.id < s.world.next_id && ids.insert(e.id).second,
                "invalid or duplicate entity ID");
        if (i < s.world.placed_count)
            require(e.layout_object_id != 0 && placed_ids.insert(e.layout_object_id).second,
                    "invalid placed entity identity");
        else
            require(e.layout_object_id == 0, "dynamic entity with placed identity");
    }
    require(s.logic.entries.size() <= 100000 && s.enemies.entries.size() <= s.world.entities.size(),
            "oversized level state");
    for (const auto &l : s.logic.entries) {
        require(logic_ids.insert(l.id).second, "duplicate logic identity");
        scalar(l.state.timer_remaining, "invalid saved logic clock");
        require(l.state.active_spawned_units <= s.world.entities.size(),
                "invalid spawner population");
    }
    std::unordered_set<std::uint64_t> clocks;
    for (const auto &e : s.enemies.entries) {
        require(ids.count(e.id) && clocks.insert(e.id).second, "invalid enemy clock identity");
        scalar(e.ai_cooldown, "invalid saved AI clock");
    }
    for (const auto &e : s.world.entities) {
        require(!e.spawner_id || logic_ids.count(e.spawner_id),
                "saved entity refers to missing spawner");
        require(!e.loot_source_id || ids.count(e.loot_source_id),
                "saved loot refers to missing source");
    }
}
void CheckpointAccess::restore_floor(const FloorCheckpoint &s, RuntimeEntityWorld &world,
                                     LogicRuntime &logic, EnemyController &enemies) {
    validate(s);
    require(checkpoint_layout_identity(*logic.layout_) == s.layout_identity,
            "saved level layout changed");
    require(world.placed_entity_count_ == s.world.placed_count &&
                world.spawn_level_ == s.world.spawn_level,
            "saved world does not match generated level");
    for (std::size_t i = 0; i < world.placed_entity_count_; ++i) {
        const auto &a = world.entities_[i];
        const auto &b = s.world.entities[i];
        require(a.id == b.id && a.layout_object_id == b.layout_object_id &&
                    a.resource_guid == b.resource_guid,
                "saved placed unit differs from level resources");
    }
    for (const auto &e : s.world.entities) {
        const auto *r = world.resources_->find(e.resource_guid);
        require(r && r->kind == e.kind, "saved entity resource absent or changed kind");
    }
    require(logic.states_.size() == s.logic.entries.size(),
            "saved logic object set differs from layout");
    auto staged_world = s.world.entities;
    // v1-v3 retained potion items without use descriptors. Resolve ONLY missing
    // descriptors from the exact current catalog; never re-roll a v4 value.
    for (auto& e : staged_world) {
        // v1-v5 stored the pre-allocation graph roll. Recover the missing
        // metadata from the exact GUID and split it once, without an RNG draw.
        const auto resolve_attack = [&](std::optional<AttackDescription>& attack) {
            if (!attack || attack->damage_allocation_known) return;
            const auto* record = world.resources_->find(attack->source_guid);
            if (record && record->kind == MasterResourceKind::item)
                hydrate_attack_damage(*attack, *world.definitions_->load(*record));
        };
        if (e.weapon_item && !e.weapon_item->prototype.damage_percent) {
            const auto* record = world.resources_->find(e.weapon_item->prototype.guid);
            if (record && record->kind == MasterResourceKind::item)
                hydrate_weapon_damage(*e.weapon_item, *world.definitions_->load(*record));
        }
        resolve_attack(e.attacks.right); resolve_attack(e.attacks.left);
        if (!e.attack_character.magic_known && e.kind == MasterResourceKind::monster) {
            const auto* record = world.resources_->find(e.resource_guid);
            if (record) {
                const auto values = load_attack_character_values(*world.definitions_->load(*record), nullptr);
                e.attack_character.magic = values.magic;
                e.attack_character.magic_known = true;
            }
        }
        if (e.kind != MasterResourceKind::item || e.consumable || e.weapon_item || e.armor_item || !e.inventory_eligible) continue;
        const auto* record = world.resources_->find(e.resource_guid);
        if (record) e.consumable = load_consumable(world.definitions_->archive(), *world.definitions_->load(*record),
            world.attack_effect_catalog_ ? &*world.attack_effect_catalog_ : nullptr);
    }
    auto staged_logic = logic.states_;
    for (const auto &l : s.logic.entries) {
        const auto it = staged_logic.find(l.id);
        require(it != staged_logic.end(), "saved logic object is absent");
        it->second = l.state;
    }
    decltype(enemies.states_) staged_enemies;
    for (const auto &e : s.enemies.entries) {
        auto &state = staged_enemies[e.id];
        state.alerted = e.alerted;
        state.prefer_left = e.prefer_left;
        state.ai_cooldown.remaining = e.ai_cooldown;
    }
    // All allocations/validation done. Existing active actions are discarded.
    world.entities_.swap(staged_world);
    world.next_entity_id_ = s.world.next_id;
    world.population_generated_ = s.world.population_generated;
    world.random_.state_ = s.world.random_state;
    world.pending_deaths_.clear();
    logic.states_.swap(staged_logic);
    logic.random_.state_ = s.logic.random_state;
    logic.events_.clear();
    logic.invocations_.clear();
    logic.spawn_requests_.clear();
    logic.warp_requests_.clear();
    logic.pending_actions_.clear();
    logic.processing_events_ = false;
    logic.dispatched_events_ = 0;
    enemies.states_.swap(staged_enemies);
    enemies.random_.state_ = s.enemies.random_state;
}
LevelTransitionState CheckpointAccess::restore_transitions(const CampaignCheckpoint &c) {
    address(c.current);
    if (c.last_dungeon)
        address(*c.last_dungeon);
    LevelTransitionState result(c.current);
    result.last_dungeon_ = c.last_dungeon;
    return result;
}
void CheckpointAccess::validate(const CampaignCheckpoint &c) {
    try { validate_quest_checkpoint(c.quests); } catch (const std::exception& e) { throw CheckpointError(e.what()); }
    require(!c.slot.empty() && c.slot.size() <= 64, "invalid save slot");
    for (const auto ch : c.slot)
        require((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '-',
                "unsafe save slot");
    require(c.seed != 0 && c.class_guid != 0 && c.difficulty == 1,
            "unsupported saved seed/class/difficulty");
    require(!c.character_name.empty() && c.character_name.size() <= 128, "invalid character name");
    for (const unsigned char ch : c.character_name)
        require(ch >= 32 && ch != 127, "control character in saved name");
    address(c.current);
    if (c.last_dungeon)
        address(*c.last_dungeon);
    validate(c.player);
    require(!c.floors.empty() && c.floors.size() <= 128, "unsupported floor cache size");
    std::set<std::pair<std::u16string, std::int32_t>> keys;
    for (const auto &f : c.floors) {
        validate(f);
        auto name = f.address.dungeon_name;
        for (auto &ch : name)
            ch = upper(ch);
        require(keys.emplace(name, f.address.depth).second, "duplicate cached floor");
    }
    require(find_floor(c, c.current) != nullptr, "current floor missing from save");
}
bool same_dungeon_address(const DungeonAddress &a, const DungeonAddress &b) noexcept {
    return a.depth == b.depth && a.dungeon_name.size() == b.dungeon_name.size() &&
           std::equal(a.dungeon_name.begin(), a.dungeon_name.end(), b.dungeon_name.begin(),
                      [](auto x, auto y) { return upper(x) == upper(y); });
}
const FloorCheckpoint *find_floor(const CampaignCheckpoint &c, const DungeonAddress &a) noexcept {
    const auto it = std::find_if(c.floors.begin(), c.floors.end(),
                                 [&](const auto &f) { return same_dungeon_address(f.address, a); });
    return it == c.floors.end() ? nullptr : &*it;
}
void remember_floor(CampaignCheckpoint &c, FloorCheckpoint f) {
    CheckpointAccess::validate(f);
    const auto it = std::find_if(c.floors.begin(), c.floors.end(), [&](const auto &v) {
        return same_dungeon_address(f.address, v.address);
    });
    if (it == c.floors.end()) {
        require(c.floors.size() < 128, "floor cache capacity exceeded");
        c.floors.push_back(std::move(f));
    } else
        *it = std::move(f);
}
std::uint64_t checkpoint_resource_identity(const PakArchive &archive) {
    Identity h;
    std::vector<const PakArchive::Entry *> entries;
    for (const auto &e : archive.entries())
        if (!e.is_directory())
            entries.push_back(&e);
    std::sort(entries.begin(), entries.end(),
              [](const auto *a, const auto *b) { return a->name < b->name; });
    for (const auto *e : entries) {
        h.text(e->name);
        h.integer(e->crc32);
        h.integer(e->uncompressed_size);
    }
    return h.value;
}
std::uint64_t checkpoint_layout_identity(const LayoutManifest &layout) {
    Identity h;
    h.text(layout.source_path);
    h.integer(layout.version);
    const auto transforms = resolve_layout_world_transforms(layout);
    for (std::size_t i = 0; i < layout.objects.size(); ++i) {
        const auto &o = layout.objects[i];
        h.integer(o.id);
        h.text(o.descriptor);
        h.text(o.monster);
        h.text(o.unit);
        h.text(o.name);
        h.integer(o.parent_id);
        for (const auto &property : o.properties) {
            h.text(property.name);
            h.integer(static_cast<std::uint32_t>(property.type));
            std::visit(
                [&](const auto &value) {
                    using T = std::decay_t<decltype(value)>;
                    if constexpr (std::is_same_v<T, std::u16string>)
                        h.text(value);
                    else if constexpr (std::is_same_v<T, float>)
                        h.number(value);
                    else if constexpr (std::is_same_v<T, double>) {
                        std::uint64_t bits;
                        std::memcpy(&bits, &value, sizeof bits);
                        h.integer(bits);
                    } else if constexpr (std::is_same_v<T, bool>)
                        h.byte(value ? 1 : 0);
                    else
                        h.integer(value);
                },
                property.value);
        }
        for (const auto v : transforms[i].position)
            h.number(v);
        for (const auto v : transforms[i].orientation)
            h.number(v);
        for (const auto v : transforms[i].scale)
            h.number(v);
    }
    for (const auto &group : layout.logic_groups) {
        h.integer(group.object_id);
        for (const auto &node : group.nodes) {
            h.integer(node.id);
            h.integer(node.object_id);
            for (const auto &link : node.links) {
                h.integer(link.target_node_id);
                h.text(link.input_name);
                h.text(link.output_name);
            }
        }
    }
    return h.value;
}
bool checkpoint_position_walkable(const NavigationGrid &grid, const std::array<float, 3> &p,
                                  float offset) noexcept {
    for (const auto v : p)
        if (!std::isfinite(v))
            return false;
    if (!std::isfinite(offset))
        return false;
    try {
        const auto cell = grid.nearest_walkable(p, 0);
        if (!cell)
            return false;
        return std::abs(p[1] - grid.cell((*cell)[0], (*cell)[1]).height - offset) <= 1.5F;
    } catch (...) {
        return false;
    }
}
} // namespace torchlight
