#pragma once

#include "torchlight/animation_events.hpp"
#include "torchlight/unit_definition.hpp"
#include "torchlight/unit_type.hpp"

#include <array>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace torchlight {

struct ModelAnimationClip;

// All original addresses and excluded branches are recorded in
// research/ordinary-attack-action.md. These are values, not a binary ABI layout.
enum class AttackHand { innate, right, left };
// The original branches on weapon skills and MISSILE, not simply ranged ISA.
// Unknown metadata must not silently turn a spell/projectile into a physical HIT.
enum class WeaponDelivery { unverified, direct_physical, missile, weapon_skill, unsupported_damage };
[[nodiscard]] WeaponDelivery load_weapon_delivery(const UnitDefinition& definition);
[[nodiscard]] const char* weapon_delivery_issue(WeaponDelivery delivery) noexcept;
enum class WeaponAttackFamily { slash, bow, crossbow, rifle, pistol, wand, polearm };
struct WeaponAttackTraits {
    WeaponAttackFamily family = WeaponAttackFamily::slash;
    bool ranged = false;
    bool melee_specialization = false; // ISA 0xa2
    bool ranged_specialization = false; // ISA 0xa3
    bool shared_specialization = false; // ISA 0xa4
};
[[nodiscard]] WeaponAttackTraits weapon_attack_traits(
    std::u16string_view type, const UnitTypeHierarchy& hierarchy);
[[nodiscard]] WeaponAttackTraits weapon_attack_traits(
    std::u16string_view type, const UnitTypeResourceIndex& hierarchy);
[[nodiscard]] std::string weapon_attack_prefix(WeaponAttackFamily family, AttackHand hand);

// Values are already evaluated contributions, not unresolved resource MIN/MAX.
// type==0x16 is the original speed effect; it is NOT UNIT.ATTACKSPEED.
struct AttackEffectValue {
    std::uint16_t type = 0;
    std::uint8_t damage_type = 7;
    float value = 0.0F;
};
struct AttackEffects {
    std::vector<AttackEffectValue> values;
    std::vector<std::string> unresolved;
    [[nodiscard]] float get(std::uint16_t type, std::uint8_t damage_type = 7) const noexcept;
    void add(std::uint16_t type, float value, std::uint8_t damage_type = 7);
    void append(const AttackEffects& other);
};

// parseEffects @0xd608f0 uses child order, not a guessed English-name enum.
// The original exact catalog path is pinned by original-combat-inputs.json.
// No structural guessing or fallback to similarly named effect files.
class AttackEffectCatalog {
public:
    explicit AttackEffectCatalog(const AdmDocument& document);
    [[nodiscard]] std::optional<std::uint16_t> find(std::u16string_view name) const;
    [[nodiscard]] static std::optional<AttackEffectCatalog> discover(const PakArchive& archive);
    [[nodiscard]] const std::string& source_path() const noexcept { return source_path_; }
private:
    std::vector<std::u16string> names_;
    std::string source_path_;
};
// Supported resource boundary: constant, unconditional PASSIVE / ALWAYS effects.
// No random rerolls, guessed scaling, proc execution or timer emulation here.
[[nodiscard]] AttackEffects load_constant_attack_effects(
    const UnitDefinition& definition, const AttackEffectCatalog* catalog);

struct AttackDescription {
    std::string animation_prefix = "ATTACK";
    AttackHand hand = AttackHand::innate;
    std::int64_t source_guid = 0;
    std::int32_t minimum_damage = 0;
    std::int32_t maximum_damage = 0;
    float range = 0.0F;
    float strike_range = 0.0F;
    float speed_denominator = 1.0F;
    std::optional<float> equipment_ai_cooldown;
    WeaponAttackTraits traits;
    AttackEffects effects;
    std::string unavailable_reason;
    WeaponDelivery delivery = WeaponDelivery::unverified;
};
struct AttackLoadout {
    std::vector<AttackDescription> innate;
    std::optional<AttackDescription> right;
    std::optional<AttackDescription> left;
    bool no_unarmed_attacks = false;
    bool use_weapon_damage = true;
};
[[nodiscard]] const AttackDescription* select_ordinary_attack(
    const AttackLoadout& loadout, bool prefer_left, TorchlightRandom& random);

struct AttackCharacterValues {
    std::int32_t strength = 0;
    std::int32_t dexterity = 0;
    float reach_bonus = 0.0F;
    float scale = 1.0F;
    float range_multiplier = 1.0F;
    float collision_radius = 0.0F;
    float damage_multiplier = 1.0F;
    // Evaluated CAIManager::hasAIFlag(1), not a UNIT property or a monster default.
    // Producers/expiry of original AI flags remain separate from attack execution.
    bool ai_flag_one = false;
    AttackEffects effects; // Character manager + non-hand equipped contributions.
};
[[nodiscard]] AttackDescription load_innate_attack(const UnitDefinition& definition,
    std::int32_t minimum_damage, std::int32_t maximum_damage);
[[nodiscard]] AttackCharacterValues load_attack_character_values(const UnitDefinition& definition,
    const AttackEffectCatalog* catalog);
[[nodiscard]] bool attack_unit_bool(const UnitDefinition& definition, const char16_t* key, bool fallback);
[[nodiscard]] AttackEffects total_attack_effects(
    const AttackLoadout& loadout, const AttackCharacterValues& character);
[[nodiscard]] float ordinary_attack_speed(float description_speed, const AttackEffects& effects,
                                          bool ai_flag_one = false);
[[nodiscard]] float ordinary_attack_range(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character);
[[nodiscard]] float ordinary_strike_range(const AttackDescription& selected,
    const AttackCharacterValues& character, const AttackEffects& effects);
[[nodiscard]] std::array<std::int32_t, 2> ordinary_physical_damage(
    const AttackDescription& selected, const AttackLoadout& loadout,
    const AttackCharacterValues& character);
[[nodiscard]] bool within_horizontal_reach(const std::array<float, 3>& attacker,
    const std::array<float, 3>& target, float attacker_radius, float target_radius,
    float reach) noexcept;

// inAttackRange examines both equipped hands; inStrikeRange only the selected hand.
[[nodiscard]] bool has_ranged_weapon(const AttackLoadout& loadout) noexcept;
[[nodiscard]] bool within_character_attack_reach(const std::array<float, 3>& attacker,
    const std::array<float, 3>& target, float attacker_radius, float target_radius,
    float reach, bool ranged) noexcept;

// Caller supplies collision context from the current floor. No callback means
// ranged delivery is unavailable; returning false consumes HIT without damage.
using AttackLineOfSight = std::function<bool(const std::array<float, 3>&,
                                            const std::array<float, 3>&)>;
using AttackClip = std::shared_ptr<const ModelAnimationClip>;
using AttackClips = std::vector<AttackClip>;
using AttackClipResolver = std::function<AttackClips(std::string_view mesh, std::string_view prefix)>;
class AttackAnimationCatalog {
public:
    explicit AttackAnimationCatalog(const PakArchive& archive) : archive_(&archive) {}
    [[nodiscard]] AttackClips resolve(std::string_view mesh, std::string_view prefix);
private:
    const PakArchive* archive_;
    std::unordered_map<std::string, AttackClips> cache_;
};

// The same immutable clip and clock are read by rendering and HIT delivery.
// IDs and the consumption ledger are inferred portable ownership guards, not
// claims about the memory layout of CCharacter in the original executable.
class OrdinaryAttackAction {
public:
    void start(std::uint64_t execution_id, std::uint64_t target_id,
               AttackDescription description, AttackClip clip, float playback_speed);
    void advance(float seconds);
    [[nodiscard]] bool consume_hit(const AnimationEventOccurrence& occurrence);
    void finish_frame() noexcept;
    void cancel() noexcept;
    [[nodiscard]] bool active() const noexcept { return active_; }
    [[nodiscard]] std::uint64_t id() const noexcept { return playback_.execution_id(); }
    [[nodiscard]] std::uint64_t target_id() const noexcept { return target_id_; }
    [[nodiscard]] const AttackDescription& description() const noexcept { return description_; }
    [[nodiscard]] const AttackClip& clip() const noexcept { return clip_; }
    [[nodiscard]] const AnimationEventPlayback& playback() const noexcept { return playback_; }
private:
    AttackDescription description_;
    AttackClip clip_;
    AnimationEventPlayback playback_;
    std::vector<bool> consumed_hits_;
    std::uint64_t target_id_ = 0;
    bool active_ = false;
};

} // namespace torchlight
