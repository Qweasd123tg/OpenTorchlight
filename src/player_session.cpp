#include "torchlight/player_session.hpp"
#include <utility>
#include <algorithm>
#include <limits>
#include <cmath>
#include <type_traits>
#include <stdexcept>
#include "torchlight/resource_fields.hpp"

namespace torchlight {
namespace {
PlayerPrototype unarmed(PlayerPrototype prototype) {
    prototype.starting_weapon.reset();
    return prototype;
}
}
PlayerSession::PlayerSession(const PlayerPrototype& prototype, std::uint32_t seed,
                             const UnitTypeHierarchy* hierarchy)
    : progression_rules_(prototype.progression_rules),
      base_attributes_{prototype.strength, prototype.dexterity, prototype.magic, prototype.defense},
      gold_(std::max(0, prototype.starting_gold)), hardcore_(prototype.hardcore),
      combat_(unarmed(prototype), seed), health_(prototype, seed),
      class_skills_(prototype.class_skills), skill_mesh_(prototype.mesh_path) {
    for (const auto& grant : class_skills_) skills_.skills.push_back({grant.name,grant.rank,0});
    if (prototype.starting_weapon) {
        TorchlightRandom random(seed);
        InventoryItem item;
        item.resource_guid = prototype.starting_weapon->guid;
        item.name = prototype.starting_weapon->name;
        item.display_name = prototype.starting_weapon->display_name;
        item.unit_type = prototype.starting_weapon->unit_type;
        item.mesh_path = prototype.starting_weapon->mesh_path;
        item.two_handed = hierarchy && hierarchy->is_a_id(item.unit_type, 10);
        item.weapon = roll_weapon_item(*prototype.starting_weapon, random);
        const auto id = inventory_.store(std::move(item));
        static_cast<void>(inventory_.equip(id));
        refresh_equipment();
        health_.restore_after_death(); // New character starts full AFTER starting equipment.
    }
}
std::array<std::int32_t, 4> PlayerSession::attributes() const {
    auto values = base_attributes_;
    for (std::size_t i = 0; i < values.size(); ++i) {
        const auto n = static_cast<std::int64_t>(values[i]) + progression_.allocated[i];
        if (n < -1000000 || n > 1000000) throw std::invalid_argument("attribute outside supported range");
        values[i] = static_cast<std::int32_t>(n);
    }
    return values;
}
void PlayerSession::refresh_attributes() {
    const auto values = attributes();
    combat_.set_attributes(values[0], values[1], values[2]);
    health_.set_defense_attribute(values[3]);
}
bool PlayerSession::allocate_attribute(std::size_t index) {
    if (!progression_rules_ || !health_.alive() || combat_.attack_in_progress() || skill_cast_.active() ||
        index >= progression_.allocated.size() || progression_.stat_points == 0) return false;
    PlayerSession staged(*this);
    --staged.progression_.stat_points;
    ++staged.progression_.allocated[index];
    validate_progression(staged.progression_, *progression_rules_, spent_skill_points());
    staged.refresh_attributes();
    using std::swap;
    swap(progression_, staged.progression_);
    swap(combat_, staged.combat_);
    swap(health_, staged.health_);
    return true;
}
std::uint32_t PlayerSession::award_experience(std::int32_t amount) {
    if (!health_.alive() || !progression_rules_) return 0;
    auto next = progression_;
    const auto bonus = total_attack_effects(combat_.attack_loadout(), combat_.attack_character()).get(0x44);
    const auto levels = advance_progression(next, *progression_rules_, amount, bonus, spent_skill_points());
    // Preserve the action object and sampled clip: a multi-HIT kill must not
    // cancel/restart the current attack or invalidate its event cursor.
    auto vitals = health_;
    if (levels) {
        const auto& rule = progression_rules_->at(next.level);
        vitals.set_progression_vitals(rule.maximum_health, rule.base_mana);
    }
    using std::swap;
    swap(health_, vitals);
    progression_ = next;
    return levels;
}
RewardCollection PlayerSession::collect_kill_rewards(RuntimeEntityWorld& world) {
    RewardCollection result;
    for (auto& entity : world.entities()) {
        if (entity.kind != MasterResourceKind::monster || entity.alive ||
            !entity.player_kill || entity.reward_claimed) continue;
        if (!health_.alive() || !progression_rules_ || !entity.experience_reward) {
            ++result.unavailable;
        } else {
            const auto before = progression_.experience;
            result.levels += award_experience(*entity.experience_reward);
            result.experience += static_cast<std::int64_t>(progression_.experience) - before;
            ++result.kills;
        }
        entity.reward_claimed = true; // commit only after a successful award/explicit exclusion
    }
    return result;
}
std::optional<std::int32_t> PlayerSession::pick_up_gold(RuntimeEntityWorld& world,
    std::uint64_t id, LogicRuntime& logic) {
    const auto* entity = world.find(id);
    if (!health_.alive() || !entity || !entity->gold_amount || entity->inventory_eligible ||
        entity->kind != MasterResourceKind::item || !entity->alive || !entity->enabled || !entity->visible)
        return std::nullopt;
    const auto amount = *entity->gold_amount;
    if (amount < 0) throw std::invalid_argument("negative world gold");
    if (!world.pick_up(id, logic)) return std::nullopt;
    give_gold(amount);
    return amount;
}
void PlayerSession::give_gold(std::int32_t amount) noexcept {
    const auto total = static_cast<std::int64_t>(gold_) + amount;
    gold_ = static_cast<std::int32_t>(std::clamp<std::int64_t>(
        total, 0, std::numeric_limits<std::int32_t>::max()));
}
RecoveryResult PlayerSession::recover_at_entry(EnemyController& enemies, ActorMotion& motion,
    const std::array<float, 3>& anchor) {
    if (health_.alive()) return {RecoveryStatus::alive, 0};
    if (hardcore_) return {RecoveryStatus::hardcore, 0};
    for (const auto value : anchor)
        if (!std::isfinite(value)) return {RecoveryStatus::invalid_anchor, 0};
    const auto loss = gold_ / 10; // original signed /10 for nonnegative gold.
    PlayerSession staged(*this);
    staged.give_gold(-loss);
    staged.combat_.clear_target();
    staged.combat_.interrupt_attack();
    staged.active_recovery_.clear();
    staged.skills_.effects.clear();
    staged.skill_cast_.cancel();
    staged.refresh_effect_contributions();
    staged.health_.restore_after_death();
    // Finish potentially allocating derived-state work before the transaction commits.
    static_assert(std::is_nothrow_move_assignable_v<PlayerSession>);
    *this = std::move(staged);
    enemies.level_resetting();
    motion = ActorMotion(anchor, motion.speed());
    return {RecoveryStatus::recovered, loss};
}
InventoryId PlayerSession::pick_up(RuntimeEntityWorld& world, std::uint64_t entity_id,
                                   LogicRuntime& logic) {
    if (!health_.alive()) return 0;
    const auto* entity = world.find(entity_id);
    if (!entity || !entity->alive || !entity->enabled || !entity->visible ||
        entity->kind != MasterResourceKind::item || !entity->inventory_eligible) return 0;
    InventoryItem item;
    item.resource_guid = entity->resource_guid;
    item.name = entity->name;
    item.display_name = entity->display_name;
    item.unit_type = entity->unit_type;
    item.mesh_path = entity->mesh_path;
    item.weapon = entity->weapon_item;
    item.armor = entity->armor_item;
    item.two_handed = entity->two_handed;
    item.consumable = entity->consumable;
    // Allocate/store first. Failure to allocate leaves the world item untouched.
    // This is a single-threaded transfer; no persistent world pointer is kept.
    auto staged = inventory_;
    const auto id = staged.store(std::move(item));
    if (!world.pick_up(entity_id, logic)) return 0;
    using std::swap;
    swap(inventory_, staged);
    return id;
}
void PlayerSession::hydrate_consumables(UnitDefinitionLoader& loader, const MasterResourceIndex& index) {
    const auto catalog = AttackEffectCatalog::discover(loader.archive());
    auto bag = inventory_;
    for (auto& item : bag.items_) {
        const auto* record = index.find(item.resource_guid);
        if (item.weapon && !item.weapon->prototype.damage_percent && record)
            hydrate_weapon_damage(*item.weapon, *loader.load(*record));
        if (item.consumable || item.weapon || item.armor) continue;
        if (record && record->kind == MasterResourceKind::item)
            item.consumable = load_consumable(loader.archive(), *loader.load(*record), catalog ? &*catalog : nullptr);
    }
    using std::swap;
    // This entry-only hydration never rolls weapon damage or restores vitals.
    // Keep current clip ownership intact if the caller invokes it during a fight.
    auto next_combat = combat_;
    if (!next_combat.attack_in_progress()) {
        const auto* equipped = bag.equipped(InventorySlot::weapon);
        if (equipped && equipped->weapon) next_combat.equip(*equipped->weapon);
    }
    swap(inventory_, bag);
    swap(combat_, next_combat);
}
float PlayerSession::barter_percent() const {
    return total_attack_effects(combat_.attack_loadout(), combat_.attack_character()).get(0x53, 7);
}
PurchaseResult PlayerSession::buy_potion(const PotionMerchantCatalog& catalog,std::int64_t merchant,std::int64_t guid) {
    if(!health_.alive())return {PurchaseStatus::dead,0,0};
    if(combat_.attack_in_progress()||skill_cast_.active())return {PurchaseStatus::busy,0,0};
    if(!catalog.find(merchant))return {PurchaseStatus::unsupported,0,0};
    const auto* offer=catalog.offer(merchant,guid,progression_.level);
    if(!offer)return {PurchaseStatus::unavailable,0,0};
    const auto price=equipment_buy_price(offer->prices,1,true,barter_percent());
    if(gold_<price)return {PurchaseStatus::insufficient_gold,0,0};
    auto staged=inventory_;
    const auto id=staged.store(offer->item);
    using std::swap;
    static_assert(std::is_nothrow_swappable_v<PlayerInventory>);
    swap(inventory_,staged);
    gold_-=price;
    return {PurchaseStatus::purchased,id,price};
}
ConsumableUse PlayerSession::use_consumable(InventoryId id) {
    if (!health_.alive()) return ConsumableUse::dead;
    const auto* item = inventory_.find(id);
    if (!item) return ConsumableUse::not_found;
    if (!item->consumable || !item->consumable->unavailable_reason.empty()) return ConsumableUse::unsupported;
    const auto& c = *item->consumable;
    validate_consumable(c);
    if (progression_.level < c.level_required) return ConsumableUse::level_required;
    auto effects = active_recovery_;
    std::size_t accepted = 0;
    for (const auto& e : c.effects) {
        const bool hp = is_health_recovery(e.type);
        if (!hp && (!health_.mana() || !health_.maximum_mana())) continue;
        const auto current = hp ? health_.health() : *health_.mana();
        const auto maximum = hp ? health_.maximum_health() : *health_.maximum_mana();
        // Original potion gate uses integer HP()/mana() and any effect NAME.
        // Check the staged list too: duplicate effects in one item cannot bypass it.
        if (c.dont_use_on_full && (std::trunc(current) >= maximum ||
            std::any_of(effects.begin(), effects.end(), [&](const auto& a) { return a.effect.name == e.name; }))) continue;
        if (effects.size() >= 256) return ConsumableUse::unsupported;
        effects.push_back({e, e.duration, item->resource_guid});
        ++accepted;
    }
    if (!accepted) return ConsumableUse::full_or_active;
    auto bag = inventory_;
    // All allocations and effect checks finish BEFORE either side commits.
    if (!bag.consume_one(id)) return ConsumableUse::exhausted;
    using std::swap;
    swap(inventory_, bag);
    active_recovery_.swap(effects);
    return ConsumableUse::used;
}
ConsumableUse PlayerSession::use_recovery(bool hp) {
    ConsumableUse result = health_.alive() ? ConsumableUse::not_found : ConsumableUse::dead;
    for (const auto& item : inventory_.items()) {
        if (!item.consumable || !item.consumable->unavailable_reason.empty()) continue;
        if (!std::any_of(item.consumable->effects.begin(), item.consumable->effects.end(),
            [hp](const auto& e) { return hp ? is_health_recovery(e.type) : is_mana_recovery(e.type); })) continue;
        result = use_consumable(item.id);
        if (result == ConsumableUse::used) return result; // bag may now have erased this item
    }
    return result;
}
bool PlayerSession::update_vitals(float seconds) {
    if (!std::isfinite(seconds) || seconds < 0) return false;
    if (!health_.alive()) {
        active_recovery_.clear(); skill_cast_.cancel();
        if (!skills_.effects.empty()) { skills_.effects.clear(); refresh_effect_contributions(); }
        return true;
    }
    if (seconds == 0) return true;
    // Stage all advancing state. Invalid recovery arithmetic must not consume
    // cooldowns or expire a buff when HP/mana advancement is rejected.
    auto next_skills = skills_;
    auto vitals = health_;
    auto active = active_recovery_;
    auto next_combat = combat_;
    for (auto& skill : next_skills.skills) skill.cooldown = std::max(0.0F, skill.cooldown - seconds);
    if (advance_timed_skill_effects(next_skills.effects, seconds)) {
        auto effects = skill_attack_effects(next_skills.effects);
        for (std::size_t i = 0; i < static_cast<std::size_t>(ArmorSlot::count); ++i) {
            const auto* item = inventory_.equipped(static_cast<InventorySlot>(i + 1));
            if (item && item->armor) effects.append(item->armor->attack_effects);
        }
        next_combat.set_external_attack_effects(effects);
        if (const auto* item = weapon(); item && item->weapon)
            effects.append(item->weapon->prototype.attack_effects);
        vitals.set_equipment_vital_effects(effects);
    }
    // Portable scheduler: split at recovery expiry, so long frames cannot
    // over-heal. Infuse has no timed HP/mana-rate contribution.
    float remaining = seconds;
    while (remaining > 0 && !active.empty()) {
        float step = remaining, hp = 0, mana = 0;
        for (const auto& a : active) {
            step = std::min(step, a.remaining);
            (is_health_recovery(a.effect.type) ? hp : mana) += finite_recovery_rate(a.effect.value);
        }
        if (!(step > 0) || !vitals.update_vitals(step, hp, mana)) return false;
        for (auto& a : active) a.remaining = std::max(0.0F, a.remaining - step);
        active.erase(std::remove_if(active.begin(), active.end(), [](const auto& a) { return a.remaining == 0; }), active.end());
        remaining = std::max(0.0F, remaining - step);
    }
    if (remaining > 0 && !vitals.update_vitals(remaining)) return false;
    static_assert(std::is_nothrow_swappable_v<SkillCheckpoint> &&
                  std::is_nothrow_swappable_v<CombatController> &&
                  std::is_nothrow_swappable_v<PlayerCombatState>);
    using std::swap;
    swap(health_, vitals);
    swap(combat_, next_combat);
    swap(skills_, next_skills);
    active_recovery_.swap(active);
    return true;
}
InventoryChange PlayerSession::equip(InventoryId id) { return change_equipment(id, false); }
InventoryChange PlayerSession::unequip(InventoryId id) { return change_equipment(id, true); }
InventoryChange PlayerSession::change_equipment(InventoryId id, bool remove) {
    if (!health_.alive()) return InventoryChange::dead;
    if (combat_.attack_in_progress() || skill_cast_.active()) return InventoryChange::busy;
    // Portable transaction: resource-derived overflow/invalid effects must not
    // replace a slot while leaving combat, armor and mana from different items.
    // Copying inactive action state neither issues events nor advances RNG.
    PlayerSession staged(*this);
    const auto result = remove ? staged.inventory_.unequip(id) : staged.inventory_.equip(id);
    if (result != InventoryChange::changed) return result;
    staged.refresh_equipment();
    static_assert(std::is_nothrow_swappable_v<PlayerInventory> &&
                  std::is_nothrow_swappable_v<CombatController> &&
                  std::is_nothrow_swappable_v<PlayerCombatState>);
    using std::swap;
    swap(inventory_, staged.inventory_);
    swap(combat_, staged.combat_);
    swap(health_, staged.health_);
    return result;
}
void PlayerSession::refresh_equipment() {
    if (const auto* item = weapon(); item && item->weapon) combat_.equip(*item->weapon);
    else combat_.unequip();
    for (std::size_t i = 0; i < static_cast<std::size_t>(ArmorSlot::count); ++i) {
        const auto* item = inventory_.equipped(static_cast<InventorySlot>(i + 1));
        if (item && item->armor) health_.equip(*item->armor);
        else health_.unequip(static_cast<ArmorSlot>(i));
    }
    refresh_effect_contributions();
}
void PlayerSession::refresh_effect_contributions() {
    auto effects = skill_attack_effects(skills_.effects);
    for (std::size_t i = 0; i < static_cast<std::size_t>(ArmorSlot::count); ++i) {
        const auto* item = inventory_.equipped(static_cast<InventorySlot>(i + 1));
        if (item && item->armor) effects.append(item->armor->attack_effects);
    }
    combat_.set_external_attack_effects(effects);
    if (const auto* item = weapon(); item && item->weapon)
        effects.append(item->weapon->prototype.attack_effects);
    health_.set_equipment_vital_effects(effects);
}
std::int32_t PlayerSession::spent_skill_points() const {
    if (skills_.skills.size()!=class_skills_.size()) throw std::invalid_argument("skill state/class size mismatch");
    std::int64_t spent=0;
    for (const auto& grant:class_skills_) {
        const auto found=std::find_if(skills_.skills.begin(),skills_.skills.end(),[&](const auto& s){return s.name==grant.name;});
        if(found==skills_.skills.end()||found->invested<grant.rank) throw std::invalid_argument("saved class skill rank missing");
        spent+=found->invested-grant.rank;
    }
    if(spent>std::numeric_limits<std::int32_t>::max()) throw std::invalid_argument("invested skills overflow");
    return static_cast<std::int32_t>(spent);
}
void PlayerSession::attach_skill_catalog(std::shared_ptr<const SkillCatalog> catalog) {
    if (!catalog) { skill_catalog_.reset(); return; }
    validate_skill_checkpoint(skills_);
    if (skills_.skills.size() != class_skills_.size()) throw std::invalid_argument("saved class skill set differs from resources");
    for (const auto& state : skills_.skills) {
        const auto grant=std::find_if(class_skills_.begin(),class_skills_.end(),[&](const auto& g){return g.name==state.name;});
        const auto* def=catalog->find(state.name);
        if (grant==class_skills_.end() || !def || state.invested<grant->rank || state.invested>std::max(def->maximum_investment,grant->rank))
            throw std::invalid_argument("saved skill rank disagrees with class resources");
        const auto* rank = def->rank(state.invested);
        if ((state.invested > 0 && !rank) ||
            state.cooldown > (rank ? std::max(0.0F, rank->cooldown) : 0.0F))
            throw std::invalid_argument("saved skill cooldown disagrees with resources");
        if (state.invested > grant->rank &&
            (!rank->self_buff || progression_.level < std::max(grant->level_required, rank->level_required)))
            throw std::invalid_argument("saved purchased skill is unavailable at the player level");
    }
    for (const auto& active : skills_.effects) {
        bool match=false;
        for (const auto& state : skills_.skills) {
            const auto* def=catalog->find(state.name);
            if (!def || def->guid!=active.source_skill) continue;
            for (int n=1;n<=state.invested;++n) if (const auto* r=def->rank(n); r && r->self_buff)
                for (const auto& e:r->self_buff->effects)
                    match |= e.name==active.name&&e.type==active.type&&e.damage_type==active.damage_type&&e.value==active.value&&
                             e.duration==active.duration&&e.exclusive==active.exclusive&&e.unit_theme==active.unit_theme;
        }
        if (!match) throw std::invalid_argument("saved skill effect has no matching resource program");
    }
    skill_catalog_=std::move(catalog);
}
SkillUse PlayerSession::invest_skill(std::u16string_view name) {
    if (!health_.alive()) return SkillUse::dead;
    if (skill_cast_.active()||combat_.attack_in_progress()) return SkillUse::busy;
    const auto key=resource_fields::upper(std::u16string(name));
    const auto state=std::find_if(skills_.skills.begin(),skills_.skills.end(),[&](const auto& s){return s.name==key;});
    const auto grant=std::find_if(class_skills_.begin(),class_skills_.end(),[&](const auto& s){return s.name==key;});
    const auto* def=skill_catalog_?skill_catalog_->find(key):nullptr;
    if (state==skills_.skills.end()||grant==class_skills_.end()||!def) return SkillUse::unknown;
    if (state->invested>=def->maximum_investment) return SkillUse::maximum_rank;
    const auto* rank=def->rank(state->invested+1);
    if (!rank||!rank->self_buff) return SkillUse::unsupported;
    if (progression_.level<std::max(rank->level_required,grant->level_required)) return SkillUse::level_required;
    if (progression_.skill_points<=0) return SkillUse::no_points;
    ++state->invested; --progression_.skill_points;
    return SkillUse::learned;
}
SkillUse PlayerSession::begin_skill(std::u16string_view name,const AttackClipResolver& resolver) {
    if (!health_.alive()) return SkillUse::dead;
    if (skill_cast_.active()||combat_.attack_in_progress()) return SkillUse::busy;
    const auto key=resource_fields::upper(std::u16string(name));
    const auto state=std::find_if(skills_.skills.begin(),skills_.skills.end(),[&](const auto& s){return s.name==key;});
    const auto* def=skill_catalog_?skill_catalog_->find(key):nullptr;
    if (state==skills_.skills.end()||!def) return SkillUse::unknown;
    if (state->invested<=0) return SkillUse::unlearned;
    const auto* rank=def->rank(state->invested);
    if (!rank||!rank->self_buff) return SkillUse::unsupported;
    if (state->cooldown>0) return SkillUse::cooldown;
    if (!health_.mana()||std::trunc(*health_.mana())<rank->mana_cost) return SkillUse::no_mana;
    AttackClips clips;
    try { if (resolver) clips=resolver(skill_mesh_,def->animation); } catch(const std::exception&) {return SkillUse::missing_animation;}
    // Single-clip branch: do not invent original random selection for casts.
    if (clips.size()!=1) return SkillUse::missing_animation;
    const auto effects=total_attack_effects(combat_.attack_loadout(),combat_.attack_character());
    const auto speed=original_cast_speed(effects.get(0x1d),effects.get(0x8c),rank->speed);
    auto next=skill_cast_;
    if (!next_skill_execution_) throw std::overflow_error("skill execution IDs exhausted");
    try { next.start(next_skill_execution_,key,*rank->self_buff,clips.front(),speed); }
    catch(const std::invalid_argument&) {return SkillUse::missing_animation;}
    auto vitals=health_;
    if (!vitals.spend_mana(static_cast<float>(rank->mana_cost))) return SkillUse::no_mana;
    // CCharacter::castSkill debits mana after successful start, before animation HIT.
    skill_cast_=std::move(next); health_=std::move(vitals);state->cooldown=rank->cooldown;
    ++next_skill_execution_; combat_.clear_target();
    return SkillUse::started;
}
void PlayerSession::advance_skill_animation(float seconds) {
    if (!health_.alive()) skill_cast_.cancel(); else skill_cast_.advance(seconds);
}
bool PlayerSession::perform_skill_event(const AnimationEventOccurrence& event) {
    if (!health_.alive()) return false;
    auto next_cast=skill_cast_; if (!next_cast.consume(event)) return false;
    auto next_effects=skills_.effects;
    add_timed_skill_effects(next_effects,next_cast.program().effects);
    // Stage derived combat values too: allocation/validation failure cannot eat HIT.
    auto next=*this;next.skills_.effects=std::move(next_effects);next.refresh_effect_contributions();
    skill_cast_=std::move(next_cast);skills_.effects.swap(next.skills_.effects);
    std::swap(combat_,next.combat_);std::swap(health_,next.health_);
    return true;
}
} // namespace torchlight
