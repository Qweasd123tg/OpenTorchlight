#include "torchlight/save_store.hpp"
#include <cmath>
#include <algorithm>
#include <cstring>
#include <limits>
#include <type_traits>
#include <zlib.h>

namespace torchlight {
namespace {
// Explicit little-endian fields. Never memcpy a C++ object, ABI enum or pointer.
template <class A, class S> void versioned_fields(A&, S&) {}
#define V2_FIELDS(T, ...) \
    template <class A> void versioned_fields(A& a, T& s) { if (a.version >= 2) a(__VA_ARGS__); } \
    template <class A> void versioned_fields(A& a, const T& s) { if (a.version >= 2) a(__VA_ARGS__); }
V2_FIELDS(PlayerCheckpoint, s.progression)
V2_FIELDS(RuntimeEntity, s.gold_amount, s.experience_reward, s.player_kill, s.reward_claimed)
#undef V2_FIELDS
#define FIELDS(T, ...)                                                                             \
    template <class A> void fields(A &a, T &s) {                                                   \
        a(__VA_ARGS__); versioned_fields(a, s);                                                                            \
    }                                                                                              \
    template <class A> void fields(A &a, const T &s) {                                             \
        a(__VA_ARGS__); versioned_fields(a, s);                                                                            \
    }
FIELDS(ProgressionState, s.level, s.experience, s.stat_points, s.skill_points, s.allocated)
FIELDS(DamageDefense, s.natural_armor, s.defense_attribute, s.elemental_armor)
FIELDS(AttackEffectValue, s.type, s.damage_type, s.value)
FIELDS(AttackEffects, s.values, s.unresolved)
FIELDS(WeaponAttackTraits, s.family, s.ranged, s.melee_specialization, s.ranged_specialization,
       s.shared_specialization)
FIELDS(AttackDescription, s.animation_prefix, s.hand, s.source_guid, s.minimum_damage,
       s.maximum_damage, s.range, s.strike_range, s.speed_denominator, s.equipment_ai_cooldown,
       s.traits, s.effects, s.unavailable_reason)
FIELDS(AttackLoadout, s.innate, s.right, s.left, s.no_unarmed_attacks, s.use_weapon_damage)
FIELDS(AttackCharacterValues, s.strength, s.dexterity, s.reach_bonus, s.scale, s.range_multiplier,
       s.collision_radius, s.damage_multiplier, s.ai_flag_one, s.effects)
FIELDS(WeaponPrototype, s.guid, s.name, s.display_name, s.unit_type, s.mesh_path, s.level,
       s.minimum_damage_percent, s.maximum_damage_percent, s.rarity_damage_modifier,
       s.speed_damage_modifier, s.speed, s.range, s.strike_range, s.base_weapon_damage,
       s.attack_traits, s.attack_hand, s.attack_effects, s.ai_attack_cooldown)
FIELDS(WeaponItem, s.prototype, s.minimum_damage, s.maximum_damage)
FIELDS(ArmorItem, s.guid, s.name, s.display_name, s.slot, s.level, s.armor, s.damage_defense,
       s.attack_effects)
FIELDS(InventoryItem, s.id, s.resource_guid, s.name, s.display_name, s.unit_type, s.mesh_path,
       s.weapon, s.armor, s.two_handed)
FIELDS(InventoryCheckpoint, s.next_id, s.items, s.slots)
FIELDS(PlayerCheckpoint, s.inventory, s.gold, s.hardcore, s.health, s.maximum_health, s.mana,
       s.maximum_mana, s.base_defense, s.combat_random, s.prefer_left)
FIELDS(TreasureProfile, s.spawn_class, s.minimum_rolls, s.maximum_rolls)
FIELDS(RuntimeEntity, s.id, s.spawner_id, s.layout_object_id, s.resource_guid, s.kind, s.name,
       s.display_name, s.unit_type, s.mesh_path, s.inventory_eligible, s.two_handed, s.treasure,
       s.drops_loot, s.loot_source_id, s.position, s.level, s.health, s.maximum_health,
       s.minimum_damage, s.maximum_damage, s.walking_speed, s.running_speed, s.attack_speed,
       s.ai_attack_cooldown, s.equipped_ai_attack_cooldown, s.sight_radius, s.reach_bonus,
       s.weapon_range, s.attack_range, s.motion_radius, s.follow_radius, s.equipped_attack_name,
       s.armor_item, s.weapon_item, s.damage_defense, s.attacks, s.attack_character, s.alive,
       s.enabled, s.visible, s.combat_targetable)
FIELDS(WorldCheckpoint, s.next_id, s.random_state, s.placed_count, s.spawn_level, s.entities)
FIELDS(LogicObjectState, s.enabled, s.visible, s.trigger_active, s.triggered_once,
       s.deactivated_once, s.counter, s.timer_running, s.timer_remaining, s.timer_loops_remaining,
       s.active_spawned_units)
FIELDS(LogicCheckpointEntry, s.id, s.state)
FIELDS(LogicCheckpoint, s.random_state, s.entries)
FIELDS(EnemyCheckpointEntry, s.id, s.alerted, s.prefer_left, s.ai_cooldown)
FIELDS(EnemyCheckpoint, s.random_state, s.entries)
FIELDS(DungeonAddress, s.dungeon_name, s.depth)
FIELDS(FloorCheckpoint, s.address, s.layout_identity, s.player_position, s.recovery_anchor,
       s.player_angle, s.recovery_angle, s.floor_offset, s.original_recovery_anchor, s.world,
       s.logic, s.enemies)
FIELDS(CampaignCheckpoint, s.slot, s.revision, s.resource_identity, s.seed, s.class_guid,
       s.character_name, s.difficulty, s.current, s.last_dungeon, s.player, s.floors)
#undef FIELDS
class AllocationBudget {
  public:
    std::size_t elements = 0, allocated = 0;
    void reserve(std::size_t n, std::size_t element_size, bool container) {
        if ((container && (n > 100000 || n > 500000 - elements)) ||
            n > (64U * 1024U * 1024U - allocated) / element_size)
            throw CheckpointError("checkpoint decoded allocation budget exceeded");
        if (container)
            elements += n;
        allocated += n * element_size;
    }
};
class Writer {
  public:
    const std::uint32_t version = kCheckpointFormatVersion;
    std::vector<std::uint8_t> bytes;
    AllocationBudget budget;
    template <class... T> void operator()(const T &...v) {
        (write(v), ...);
    }
    void write(bool n) {
        write(static_cast<std::uint8_t>(n));
    }
    void write(float n) {
        if (!std::isfinite(n))
            throw CheckpointError("non-finite value in checkpoint");
        std::uint32_t bits;
        static_assert(sizeof n == sizeof bits);
        std::memcpy(&bits, &n, sizeof bits);
        write(bits);
    }
    template <class T> void write(const T &n) {
        if constexpr (std::is_enum_v<T>)
            write(static_cast<std::uint32_t>(n));
        else if constexpr (std::is_integral_v<T>) {
            using U = std::make_unsigned_t<T>;
            U v = static_cast<U>(n);
            for (std::size_t i = 0; i < sizeof v; ++i) {
                bytes.push_back(static_cast<std::uint8_t>(v));
                v >>= 8U;
            }
        } else
            fields(*this, n);
        if (bytes.size() > kMaximumCheckpointBytes)
            throw CheckpointError("checkpoint size limit exceeded");
    }
    template <class T, std::size_t N> void write(const std::array<T, N> &a) {
        for (const auto &v : a)
            write(v);
    }
    template <class T> void write(const std::optional<T> &v) {
        write(bool(v));
        if (v)
            write(*v);
    }
    template <class T> void write(const std::vector<T> &a) {
        budget.reserve(a.size(), sizeof(T), true);
        write(static_cast<std::uint32_t>(a.size()));
        for (const auto &v : a)
            write(v);
    }
    template <class C> void write(const std::basic_string<C> &s) {
        if (s.size() > 4096)
            throw CheckpointError("checkpoint string limit exceeded");
        budget.reserve(s.size(), sizeof(C), false);
        write(static_cast<std::uint32_t>(s.size()));
        for (const auto c : s) {
            if (c == 0)
                throw CheckpointError("NUL in checkpoint string");
            write(c);
        }
    }
};
class Reader {
  public:
    explicit Reader(const std::vector<std::uint8_t> &b) : bytes(b) {
    }
    std::uint32_t version = kCheckpointFormatVersion;
    const std::vector<std::uint8_t> &bytes;
    std::size_t pos = 0;
    // Aggregate element budget prevents many small nested containers from expanding
    // a tiny hostile payload into gigabytes before validation.
    AllocationBudget budget;
    template <class... T> void operator()(T &...v) {
        (read(v), ...);
    }
    void read(bool &n) {
        std::uint8_t v;
        read(v);
        if (v > 1)
            throw CheckpointError("invalid encoded boolean");
        n = v != 0;
    }
    void read(float &n) {
        std::uint32_t b;
        read(b);
        std::memcpy(&n, &b, sizeof n);
        if (!std::isfinite(n))
            throw CheckpointError("non-finite encoded number");
    }
    template <class T> void read(T &n) {
        if constexpr (std::is_enum_v<T>) {
            std::uint32_t v;
            read(v);
            n = static_cast<T>(v);
        } else if constexpr (std::is_integral_v<T>) {
            using U = std::make_unsigned_t<T>;
            if (bytes.size() - pos < sizeof(T))
                throw CheckpointError("truncated checkpoint");
            U v = 0;
            for (std::size_t i = 0; i < sizeof(T); ++i)
                v |= static_cast<U>(bytes[pos++]) << (8U * i);
            // Preserve signed bit patterns without out-of-range casts.
            std::memcpy(&n, &v, sizeof n);
        } else
            fields(*this, n);
    }
    template <class T, std::size_t N> void read(std::array<T, N> &a) {
        for (auto &v : a)
            read(v);
    }
    template <class T> void read(std::optional<T> &v) {
        bool present;
        read(present);
        if (present) {
            v.emplace();
            read(*v);
        } else
            v.reset();
    }
    template <class T> void read(std::vector<T> &a) {
        std::uint32_t n;
        read(n);
        if (n > bytes.size() - pos)
            throw CheckpointError("encoded container limit exceeded");
        budget.reserve(n, sizeof(T), true);
        // Each element needs at least one byte. Never allocate on an unchecked size.
        a.resize(n);
        for (auto &v : a)
            read(v);
    }
    template <class C> void read(std::basic_string<C> &s) {
        std::uint32_t n;
        read(n);
        if (n > 4096 || n > (bytes.size() - pos) / sizeof(C))
            throw CheckpointError("encoded string limit exceeded");
        budget.reserve(n, sizeof(C), false);
        s.resize(n);
        for (auto &c : s)
            read(c);
        for (const auto c : s)
            if (c == 0)
                throw CheckpointError("NUL in checkpoint string");
    }
};
constexpr std::array<std::uint8_t, 8> magic{'O', 'T', 'C', 'H', 'K', 'P', 'T', 0};
} // namespace
std::vector<std::uint8_t> encode_checkpoint(const CampaignCheckpoint &c) {
    CheckpointAccess::validate(c);
    Writer payload;
    payload(c);
    const auto crc = static_cast<std::uint32_t>(
        crc32(0, payload.bytes.data(), static_cast<uInt>(payload.bytes.size())));
    Writer file;
    file.bytes.assign(magic.begin(), magic.end());
    file(kCheckpointFormatVersion, static_cast<std::uint32_t>(payload.bytes.size()), crc);
    file.bytes.insert(file.bytes.end(), payload.bytes.begin(), payload.bytes.end());
    return file.bytes;
}
CampaignCheckpoint decode_checkpoint(const std::vector<std::uint8_t> &file) {
    if (file.size() < 20 || file.size() > kMaximumCheckpointBytes + 20 ||
        !std::equal(magic.begin(), magic.end(), file.begin()))
        throw CheckpointError("not an OpenTorchlight checkpoint");
    Reader header(file);
    header.pos = 8;
    std::uint32_t version, length, crc;
    header(version, length, crc);
    if (version != 1 && version != kCheckpointFormatVersion)
        throw CheckpointError("unsupported checkpoint version");
    if (length != file.size() - 20)
        throw CheckpointError("checkpoint length mismatch");
    if (static_cast<std::uint32_t>(crc32(0, file.data() + 20, length)) != crc)
        throw CheckpointError("checkpoint checksum mismatch");
    Reader reader(file);
    reader.version = version;
    reader.pos = 20;
    CampaignCheckpoint result;
    reader(result);
    if (reader.pos != file.size())
        throw CheckpointError("unexpected trailing checkpoint data");
    CheckpointAccess::validate(result);
    return result;
}
} // namespace torchlight
