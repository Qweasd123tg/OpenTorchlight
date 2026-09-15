#include "torchlight/scene_animation.hpp"
#include "torchlight/attack_action.hpp"
#include "torchlight/ogre_mesh.hpp"
#include "torchlight/original_combat_inputs.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

namespace torchlight {
namespace {
std::string upper(std::string_view text) {
    std::string result(text);
    for (auto& c : result) if (c >= 'a' && c <= 'z') c -= 'a' - 'A';
    return result;
}
std::u16string upper16(std::u16string_view text) {
    std::u16string result(text);
    for (auto& c : result) if (c >= u'a' && c <= u'z') c -= u'a' - u'A';
    return result;
}
std::string narrow(std::u16string_view text) {
    std::string result;
    for (auto c : text) result += c <= 127 ? static_cast<char>(c) : '?';
    return result;
}
std::u16string text(const AdmGroup& group, const char16_t* name) {
    const auto* p = group.find_property(name);
    if (!p) return {};
    const auto* v = std::get_if<std::u16string>(&p->value);
    return v ? upper16(*v) : std::u16string{};
}
std::optional<float> number(const AdmProperty* p) {
    if (!p) return std::nullopt;
    return std::visit([](const auto& value) -> std::optional<float> {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_arithmetic_v<T>) return static_cast<float>(value);
        else return std::nullopt;
    }, p->value);
}
template<class Hierarchy>
WeaponAttackTraits traits(std::u16string_view type, const Hierarchy& hierarchy) {
    WeaponAttackTraits r;
    const auto isa = [&](int id) { return hierarchy.is_a_id(type, id); };
    if (isa(0x24)) r.family = WeaponAttackFamily::bow;
    else if (isa(0x6e)) r.family = WeaponAttackFamily::crossbow;
    else if (isa(0x74)) r.family = WeaponAttackFamily::rifle;
    else if (isa(0x5a)) r.family = WeaponAttackFamily::pistol;
    else if (isa(0x62)) r.family = WeaponAttackFamily::wand;
    else if (isa(0x69) || isa(0x3d)) r.family = WeaponAttackFamily::polearm;
    r.ranged = isa(0x23);
    r.melee_specialization = isa(0xa2);
    r.ranged_specialization = isa(0xa3);
    r.shared_specialization = isa(0xa4);
    return r;
}
std::int32_t checked_sum(std::initializer_list<std::int32_t> terms) {
    std::int64_t result = 0;
    for (auto term : terms) result += term;
    if (result < std::numeric_limits<std::int32_t>::min() ||
        result > std::numeric_limits<std::int32_t>::max())
        throw std::overflow_error("ordinary attack integer sum exceeds int32");
    return static_cast<std::int32_t>(result);
}
std::int32_t checked_int(float value) {
    if (!std::isfinite(value) || static_cast<double>(value) < std::numeric_limits<std::int32_t>::min() ||
        static_cast<double>(value) > std::numeric_limits<std::int32_t>::max())
        throw std::overflow_error("ordinary attack arithmetic exceeds int32");
    return static_cast<std::int32_t>(value);
}
}
WeaponAttackTraits weapon_attack_traits(std::u16string_view type, const UnitTypeHierarchy& h) {
    return traits(type, h);
}
WeaponAttackTraits weapon_attack_traits(std::u16string_view type, const UnitTypeResourceIndex& h) {
    return traits(type, h);
}
std::string weapon_attack_prefix(WeaponAttackFamily family, AttackHand hand) {
    if (hand == AttackHand::innate) return {};
    const bool left = hand == AttackHand::left;
    switch (family) {
    case WeaponAttackFamily::bow: return left ? "BOW" : "";
    case WeaponAttackFamily::crossbow: return left ? "" : "CROSSBOW";
    case WeaponAttackFamily::rifle: return left ? "" : "RIFLE";
    case WeaponAttackFamily::pistol: return left ? "LPISTOL" : "RPISTOL";
    case WeaponAttackFamily::wand: return left ? "LWAND" : "RWAND";
    case WeaponAttackFamily::polearm: return left ? "" : "POLEARM";
    case WeaponAttackFamily::slash: return left ? "LSLASH" : "RSLASH";
    }
    return {};
}
float AttackEffects::get(std::uint16_t type, std::uint8_t damage_type) const noexcept {
    float result = 0;
    for (const auto& effect : values)
        if (effect.type == type && (damage_type == 7 || effect.damage_type == damage_type))
            result += effect.value;
    return result;
}
void AttackEffects::add(std::uint16_t type, float value, std::uint8_t damage_type) {
    if (type >= 0x91 || damage_type > 7 || !std::isfinite(value))
        throw std::invalid_argument("invalid evaluated attack effect");
    values.push_back({type, damage_type, value});
}
void AttackEffects::append(const AttackEffects& other) {
    values.insert(values.end(), other.values.begin(), other.values.end());
    unresolved.insert(unresolved.end(), other.unresolved.begin(), other.unresolved.end());
}
AttackEffectCatalog::AttackEffectCatalog(const AdmDocument& document) {
    if (document.root.groups.size() != 0x91)
        throw std::invalid_argument("original effect catalog must contain 145 ordered children");
    for (const auto& child : document.root.groups) {
        auto name = text(child, u"NAME");
        if (name.empty() || std::find(names_.begin(), names_.end(), name) != names_.end())
            throw std::invalid_argument("effect catalog contains absent or duplicate NAME");
        names_.push_back(std::move(name));
    }
}
std::optional<std::uint16_t> AttackEffectCatalog::find(std::u16string_view name) const {
    const auto key = upper16(name);
    const auto it = std::find(names_.begin(), names_.end(), key);
    if (it == names_.end()) return std::nullopt;
    return static_cast<std::uint16_t>(it - names_.begin());
}
std::optional<AttackEffectCatalog> AttackEffectCatalog::discover(const PakArchive& archive) {
    const auto* entry = archive.find_normalized(original_combat_inputs::effect_catalog_compiled_path);
    if (!entry) return std::nullopt;
    // A corrupt authoritative table must not be silently replaced by another file.
    AttackEffectCatalog catalog(parse_adm(archive.read(*entry)));
    catalog.source_path_ = entry->name;
    return catalog;
}
AttackEffects load_constant_attack_effects(const UnitDefinition& definition,
                                         const AttackEffectCatalog* catalog) {
    AttackEffects result;
    for (const auto& group : definition.root.groups) {
        if (upper16(group.name) != u"EFFECT") continue;
        const auto name = text(group, u"TYPE");
        const auto activation = text(group, u"ACTIVATION");
        const auto duration = text(group, u"DURATION");
        const auto type = catalog ? catalog->find(name) : std::nullopt;
        // ARMOR BONUS is already handled by the existing armor path and cannot
        // change attack timing. All other unclassified records stay visible.
        if (!type && name == u"ARMOR BONUS") continue;
        const auto unsupported = [&](const char* why) {
            result.unresolved.push_back(narrow(name) + ": " + why);
        };
        if (!type) { unsupported("effect ordinal catalog unavailable"); continue; }
        if (activation != u"PASSIVE" || (!duration.empty() && duration != u"ALWAYS")) {
            unsupported("activation/lifetime is not a constant passive"); continue;
        }
        bool conditional = false;
        for (const auto& property : group.properties) {
            const auto key = upper16(property.name);
            if (key == u"TYPE" || key == u"ACTIVATION" || key == u"DURATION" ||
                key == u"MIN" || key == u"MAX" || key == u"DAMAGE_TYPE") continue;
            // No silent acceptance of graph/rank/theme/target/unit restrictions.
            conditional = true;
        }
        if (conditional || !group.groups.empty()) {
            unsupported("additional effect fields need evaluation"); continue;
        }
        const auto minimum = number(group.find_property(u"MIN"));
        const auto maximum = number(group.find_property(u"MAX"));
        if (!minimum || !maximum || !std::isfinite(*minimum) || *minimum != *maximum) {
            unsupported("MIN/MAX is not one finite constant"); continue;
        }
        std::uint8_t damage_type = 0; // CEffect constructor defaults DAMAGE_TYPE to PHYSICAL.
        const auto damage_name = text(group, u"DAMAGE_TYPE");
        constexpr std::array<std::u16string_view, 7> names{
            u"PHYSICAL", u"MAGICAL", u"FIRE", u"ICE", u"ELECTRIC", u"POISON", u"ALL"};
        if (!damage_name.empty()) {
            const auto it = std::find(names.begin(), names.end(), damage_name);
            if (it == names.end()) { unsupported("unknown DAMAGE_TYPE"); continue; }
            damage_type = static_cast<std::uint8_t>(it - names.begin());
        }
        result.add(*type, *minimum, damage_type);
    }
    return result;
}
const AttackDescription* select_ordinary_attack(const AttackLoadout& loadout,
                                                bool prefer_left, TorchlightRandom& random) {
    if (loadout.right) {
        if (loadout.left && prefer_left) return &*loadout.left;
        return &*loadout.right;
    }
    if (loadout.left) return &*loadout.left;
    if (loadout.no_unarmed_attacks || loadout.innate.empty()) return nullptr;
    if (loadout.innate.size() > static_cast<std::size_t>(std::numeric_limits<std::int32_t>::max()))
        throw std::length_error("too many innate attacks");
    const auto index = random.integer_between(0, static_cast<std::int32_t>(loadout.innate.size() - 1));
    return &loadout.innate[static_cast<std::size_t>(index)];
}
bool attack_unit_bool(const UnitDefinition& definition, const char16_t* key, bool fallback) {
    const auto* p = definition.find_property(key);
    if (!p) return fallback;
    const auto* value = std::get_if<bool>(&p->value);
    if (!value) throw std::invalid_argument("attack UNIT boolean has wrong type");
    return *value;
}
AttackDescription load_innate_attack(const UnitDefinition& definition,
                                    std::int32_t minimum, std::int32_t maximum) {
    AttackDescription result;
    result.minimum_damage = minimum; result.maximum_damage = maximum;
    const auto range = [&](const char16_t* key, float fallback) {
        const auto* p = definition.find_property(key);
        if (!p) return fallback;
        const auto value = number(p);
        if (!value || !std::isfinite(*value))
            throw std::invalid_argument("invalid innate attack range");
        return *value;
    };
    result.range = range(u"ATTACK_RANGE", original_combat_inputs::innate_attack_range);
    result.strike_range = range(u"STRIKE_RANGE", original_combat_inputs::innate_strike_range);
    return result;
}
AttackCharacterValues load_attack_character_values(const UnitDefinition& definition,
                                                   const AttackEffectCatalog* catalog) {
    const auto read = [&](const char16_t* key, float fallback) {
        const auto* p = definition.find_property(key);
        if (!p) return fallback;
        const auto value = number(p);
        if (!value || !std::isfinite(*value)) throw std::invalid_argument("invalid character attack value");
        return *value;
    };
    AttackCharacterValues result;
    result.strength = checked_int(read(u"STRENGTH", 0));
    result.dexterity = checked_int(read(u"DEXTERITY", 0));
    result.reach_bonus = read(u"REACH_BONUS", 0);
    result.range_multiplier = read(u"RANGE_MULTIPLIER", 1);
    result.collision_radius = read(u"COLLISION_RADIUS", 0);
    result.effects = load_constant_attack_effects(definition, catalog);
    return result;
}
AttackEffects total_attack_effects(const AttackLoadout& loadout,
                                  const AttackCharacterValues& character) {
    auto effects = character.effects;
    if (loadout.right) effects.append(loadout.right->effects);
    if (loadout.left) effects.append(loadout.left->effects);
    return effects;
}
float ordinary_attack_speed(float denominator, const AttackEffects& effects, bool ai_flag_one) {
    using namespace original_combat_inputs;
    if (!std::isfinite(denominator) || denominator <= 0)
        throw std::invalid_argument("attack description SPEED must be positive and finite");
    auto speed = effects.get(0x16);
    const auto resistance = effects.get(0x8c);
    if (!std::isfinite(speed) || !std::isfinite(resistance))
        throw std::invalid_argument("non-finite attack speed contribution");
    if (speed < 0) speed *= speed_one - std::clamp(resistance / percentage_divisor, 0.0F, speed_one);
    auto result = std::max(minimum_attack_speed, (speed_one + speed / percentage_divisor) / denominator);
    // Original 0x82b9e1: multiplier follows the minimum clamp, not precedes it.
    if (ai_flag_one) result *= ai_flag_one_speed_multiplier;
    if (!std::isfinite(result)) throw std::invalid_argument("attack speed effect overflow");
    return result;
}
float ordinary_attack_range(const AttackDescription& selected, const AttackLoadout& loadout,
                            const AttackCharacterValues& character) {
    auto range = selected.range;
    if (selected.hand != AttackHand::innate && loadout.right && loadout.left) {
        if (loadout.right->traits.ranged || loadout.left->traits.ranged)
            range = std::max({range, loadout.right->range, loadout.left->range});
        else range = std::min({range, loadout.right->range, loadout.left->range});
    }
    const auto effects = total_attack_effects(loadout, character);
    const bool ranged = (loadout.right && loadout.right->traits.ranged) ||
                        (loadout.left && loadout.left->traits.ranged);
    return (character.reach_bonus * character.scale + 0.2F + range) * character.range_multiplier +
           (ranged ? effects.get(0x4e) : 0.0F);
}
float ordinary_strike_range(const AttackDescription& selected,
                            const AttackCharacterValues& character, const AttackEffects& effects) {
    return (character.reach_bonus * character.scale + 0.2F + selected.strike_range) *
           character.range_multiplier + (selected.traits.ranged ? effects.get(0x4e) : 0.0F);
}
std::array<std::int32_t, 2> ordinary_physical_damage(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character) {
    const auto global = total_attack_effects(loadout, character);
    const bool ranged = selected.traits.ranged;
    const auto base = loadout.use_weapon_damage ? selected.maximum_damage :
        (loadout.innate.empty() ? 0 : loadout.innate.front().maximum_damage);
    const auto stat = ranged ? character.dexterity : character.strength;
    // original-code 0x813982..0x813993: ceil -> integer addition -> float.
    // Out-of-domain overflow is rejected, not emulated as machine wraparound.
    const auto attribute = checked_sum({stat,
        checked_int(std::ceil(static_cast<float>(stat) * global.get(ranged ? 0x48 : 0x47) / 100.0F)),
        checked_int(std::ceil(global.get(ranged ? 0x46 : 0x45)))});
    auto percent = global.get(ranged ? 0x10 : 0x0f) / 100.0F + static_cast<float>(attribute) / 100.0F;
    if (loadout.left && loadout.right) percent += global.get(0x58) / 100.0F;
    if (!ranged && selected.traits.melee_specialization) percent += global.get(0x63) / 100.0F;
    if (ranged && selected.traits.ranged_specialization) percent += global.get(0x66) / 100.0F;
    if (selected.traits.shared_specialization) percent += global.get(0x67) / 100.0F;
    // Original overload excludes the opposite hand for the current damage type.
    auto channel = character.effects;
    channel.append(selected.effects);
    percent = global.get(0x19, 6) / 100.0F + (channel.get(0x19, 0) / 100.0F + percent);
    // original-code 0x815f69..0x815f9e: bonuses accumulate as integers before
    // converting once for the final multiplier. Preserve that rounding order.
    const auto sum = checked_sum({base, checked_int(std::ceil(static_cast<float>(base) * percent)),
        checked_int(std::ceil(global.get(ranged ? 1 : 0))), checked_int(channel.get(10, 0))});
    const auto result = static_cast<float>(sum) * character.damage_multiplier;
    const auto maximum = std::max(0, checked_int(result));
    return {checked_int(std::ceil(static_cast<float>(maximum) * 0.5F)), maximum};
}
bool within_horizontal_reach(const std::array<float, 3>& a, const std::array<float, 3>& b,
                             float ar, float br, float reach) noexcept {
    return std::hypot(a[0] - b[0], a[2] - b[2]) - std::max(0.0F, ar) - std::max(0.0F, br) <= reach;
}
bool has_ranged_weapon(const AttackLoadout& loadout) noexcept {
    return (loadout.right && loadout.right->traits.ranged) ||
           (loadout.left && loadout.left->traits.ranged);
}
bool within_character_attack_reach(const std::array<float, 3>& attacker,
    const std::array<float, 3>& target, float attacker_radius, float target_radius,
    float reach, bool ranged) noexcept {
    for (std::size_t i = 0; i < 3; ++i)
        if (!std::isfinite(attacker[i]) || !std::isfinite(target[i])) return false;
    if (!ranged && std::fabs(target[1] - attacker[1]) > original_combat_inputs::melee_vertical_cutoff)
        return false;
    return within_horizontal_reach(attacker, target, attacker_radius, target_radius, reach);
}

AttackClips AttackAnimationCatalog::resolve(std::string_view mesh, std::string_view prefix) {
    const auto key = upper(mesh) + '\n' + upper(prefix);
    const auto cached = cache_.find(key);
    if (cached != cache_.end()) return cached->second;
    AttackClips result;
    const auto* entry = archive_->find_normalized(mesh);
    if (entry && !prefix.empty()) {
        const auto model = parse_ogre_mesh(archive_->read(*entry));
        if (!model.skeleton_file.empty()) {
            const auto slash = entry->name.find_last_of("/\\");
            const auto directory = slash == std::string::npos ? std::string{} : entry->name.substr(0, slash+1);
            const auto* bind_entry = archive_->find_normalized(directory + model.skeleton_file);
            if (!bind_entry) { cache_.emplace(key, result); return result; }
            auto bind = std::make_shared<const OgreSkeleton>(parse_ogre_skeleton(archive_->read(*bind_entry)));
            for (auto& clip : load_model_animations_by_prefix(
                    *archive_, entry->name, model.skeleton_file, prefix)) {
                if (upper(clip.animation_name).rfind(upper(prefix), 0) != 0) continue;
                clip.bind_skeleton = bind;
                result.push_back(std::make_shared<const ModelAnimationClip>(std::move(clip)));
            }
        }
    }
    cache_.emplace(key, result);
    return result;
}
void OrdinaryAttackAction::start(std::uint64_t execution_id, std::uint64_t target_id,
    AttackDescription description, AttackClip clip, float speed) {
    if (!clip || !std::isfinite(clip->duration) || clip->duration <= 0 ||
        description.animation_prefix.empty() ||
        upper(clip->animation_name).rfind(upper(description.animation_prefix), 0) != 0)
        throw std::invalid_argument("clip does not match selected attack description");
    // Build the new playback before replacing a live action (strong exception safety).
    AnimationEventPlayback next;
    next.start(execution_id, clip->skeleton_path, clip->duration, speed, clip->event_keys);
    std::vector<bool> hits(clip->event_keys.size(), false);
    playback_ = std::move(next);
    description_ = std::move(description);
    clip_ = std::move(clip);
    consumed_hits_ = std::move(hits);
    target_id_ = target_id;
    active_ = true;
}
void OrdinaryAttackAction::advance(float seconds) {
    if (active_) playback_.advance(seconds);
}
bool OrdinaryAttackAction::consume_hit(const AnimationEventOccurrence& event) {
    if (!active_ || !clip_ || event.execution_id != id() ||
        event.source_clip != clip_->skeleton_path || event.key.name != "HIT" ||
        event.key_index >= consumed_hits_.size() || consumed_hits_[event.key_index]) return false;
    const auto& issued = playback_.frame_events();
    const auto it = std::find_if(issued.begin(), issued.end(), [&](const auto& original) {
        return original.playback_generation == event.playback_generation &&
            original.execution_id == event.execution_id && original.source_clip == event.source_clip &&
            original.key_index == event.key_index && original.key.name == event.key.name &&
            original.key.frame == event.key.frame && original.clip_time_seconds == event.clip_time_seconds;
    });
    if (it == issued.end()) return false;
    consumed_hits_[event.key_index] = true;
    return true;
}
void OrdinaryAttackAction::finish_frame() noexcept {
    if (playback_.finished()) active_ = false;
}
void OrdinaryAttackAction::cancel() noexcept {
    active_ = false;
    target_id_ = 0;
    playback_.stop();
    consumed_hits_.clear();
    // Retain the last immutable clip for a renderer fading the interrupted pose.
}
} // namespace torchlight
