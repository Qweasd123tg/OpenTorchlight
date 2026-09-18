#include "torchlight/missile_runtime.hpp"

#include "torchlight/resource_fields.hpp"

#include <cmath>
#include <limits>

namespace torchlight {
namespace {

// Missile .adm files nest the value block under descriptor/property groups
// whose depth varies; search the whole document for the owning group.
const AdmProperty* find_property_deep(const AdmGroup& group, std::u16string_view key) {
    const auto want = resource_fields::upper(std::u16string(key));
    for (const auto& property : group.properties) {
        if (resource_fields::upper(property.name) == want) return &property;
    }
    for (const auto& child : group.groups) {
        if (const auto* hit = find_property_deep(child, key)) return hit;
    }
    return nullptr;
}

float number_field_deep(const AdmDocument& document, std::u16string_view key, float fallback) {
    const auto* property = find_property_deep(document.root, key);
    if (property == nullptr) return fallback;
    try {
        const auto value = std::visit(
            [](const auto& v) -> double {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T, std::u16string>) return std::stod(resource_fields::ascii(v));
                else if constexpr (std::is_same_v<T, bool>) return std::numeric_limits<double>::quiet_NaN();
                else return static_cast<double>(v);
            },
            property->value);
        if (!std::isfinite(value)) return fallback;
        return static_cast<float>(value);
    } catch (const std::exception&) {
        return fallback;
    }
}

std::u16string text_field_deep(const AdmDocument& document, std::u16string_view key) {
    const auto* property = find_property_deep(document.root, key);
    if (property == nullptr) return {};
    if (const auto* s = std::get_if<std::u16string>(&property->value)) return *s;
    return {};
}

} // namespace

std::optional<MissileTemplate> load_missile_template(const PakArchive& pak, std::string_view name) {
    if (name.empty()) return std::nullopt;
    std::vector<std::uint8_t> bytes;
    try {
        bytes = pak.read(std::string("media/Missiles/") + std::string(name) + ".LAYOUT.adm");
    } catch (const std::exception&) {
        return std::nullopt;
    }
    AdmDocument document;
    try {
        document = parse_adm(bytes);
    } catch (const std::exception&) {
        return std::nullopt;
    }
    // Field block lives under descriptor/property groups whose depth varies;
    // search the whole document. Core fields must be present in the resource:
    // silent defaults for them would be invented data, so refuse instead.
    if (find_property_deep(document.root, u"MAX DISTANCE") == nullptr ||
        find_property_deep(document.root, u"MAX VELOCITY") == nullptr)
        return std::nullopt;
    MissileTemplate out;
    out.name = std::string(name);
    try {
        out.max_distance = number_field_deep(document, u"MAX DISTANCE", -1.0F);
        out.max_velocity = number_field_deep(document, u"MAX VELOCITY", -1.0F);
        out.radius = number_field_deep(document, u"RADIUS", out.radius);
        out.aoe_radius = number_field_deep(document, u"AOE RAIDUS", out.aoe_radius);
        out.aoe_damage_scale = number_field_deep(document, u"AOE DAMAGE SCALE", out.aoe_damage_scale);
        out.die_layout = resource_fields::ascii(text_field_deep(document, u"DIE"));
        out.missile_name = resource_fields::ascii(text_field_deep(document, u"MISSILE NAME"));
    } catch (const std::exception&) {
        return std::nullopt;
    }
    if (!(out.max_distance > 0.0F) || !(out.max_velocity > 0.0F) || !(out.radius >= 0.0F) ||
        !(out.aoe_radius >= 0.0F) || !(out.aoe_damage_scale >= 0.0F))
        return std::nullopt;
    return out;
}

std::uint64_t MissileRuntime::spawn(const MissileTemplate& missile_template,
                                    const MissileSpawn& spawn) {
    if (missile_template.max_distance <= 0.0F || missile_template.max_velocity <= 0.0F)
        return 0;
    const float dir_len =
        std::sqrt(spawn.direction[0] * spawn.direction[0] + spawn.direction[1] * spawn.direction[1] +
                  spawn.direction[2] * spawn.direction[2]);
    if (!(dir_len > 0.0F) || !std::isfinite(dir_len)) return 0;
    Live live;
    live.id = next_id_++;
    live.missile_template = missile_template;
    live.spawn = spawn;
    live.spawn.direction[0] /= dir_len;
    live.spawn.direction[1] /= dir_len;
    live.spawn.direction[2] /= dir_len;
    const float speed = spawn.speed_override >= 0.0F ? spawn.speed_override
                                                     : missile_template.max_velocity;
    if (!(speed > 0.0F) || !std::isfinite(speed)) return 0;
    // original-code: fireMissile velocity = dir * template speed (no rodata
    // constant; research/missile-runtime.md §2). Straight flight: velocity
    // seed only, no homing (arch factor stays 0).
    live.motion.vel = {live.spawn.direction[0] * speed, live.spawn.direction[1] * speed,
                       live.spawn.direction[2] * speed};
    live.motion.speed = speed;
    live.pos = live.spawn.origin;
    missiles_.push_back(live);
    return live.id;
}

void MissileRuntime::step(float dt, const std::vector<MissileCollider>& colliders,
                          const CollisionScene& collision) {
    if (!(dt > 0.0F) || !std::isfinite(dt)) return;
    for (auto& live : missiles_) {
        if (live.dead) continue;
        const auto from = live.pos;
        // Linear advance first; the motion core only steers when a homing
        // target is configured (arch object + factor), which spawn refuses.
        MissileMotionDeps deps;
        deps.position = live.pos;
        const auto effects = missile_motion_step(live.motion, deps, dt);
        static_cast<void>(effects);
        // Position advance with the same op order as the motion core's
        // predicted point (one rounding per mul, one per add).
        std::array<float, 3> to = {live.pos[0] + live.motion.vel[0] * dt,
                                   live.pos[1] + live.motion.vel[1] * dt,
                                   live.pos[2] + live.motion.vel[2] * dt};
        live.pos = to;
        const float dx = to[0] - from[0];
        const float dy = to[1] - from[1];
        const float dz = to[2] - from[2];
        const float step_len = std::sqrt(dx * dx + dy * dy + dz * dz);
        // World obstruction (original preSortedSphereCollision role; port
        // primitive collision_segment_clear, same as ranged-direct).
        if (!collision_segment_clear(collision, from, to)) {
            live.dead = true;
            impacts_.push_back({live.id, 0, from, true, false, false});
            splash(live, 0, from, colliders);
            continue;
        }
        live.travelled += step_len;
        // Unit hits: owner excluded, single-hit set (original +0x298 scan).
        const MissileCollider* victim = nullptr;
        for (const auto& entity : colliders) {
            if (!entity.live_target) continue;
            if (entity.id == live.spawn.owner_id) continue;
            bool seen = false;
            for (const auto hit : live.hit_set)
                if (hit == entity.id) {
                    seen = true;
                    break;
                }
            if (seen) continue;
            const float ex = entity.position[0] - to[0];
            const float ey = entity.position[1] - to[1];
            const float ez = entity.position[2] - to[2];
            const float radius = live.missile_template.radius + entity.radius;
            if (ex * ex + ey * ey + ez * ez <= radius * radius) {
                victim = &entity;
                break;
            }
        }
        if (victim != nullptr) {
            live.hit_set.push_back(victim->id);
            live.dead = true; // no pierce path in scope (original +0x142)
            impacts_.push_back({live.id, victim->id, to, false, false, false});
            splash(live, victim->id, to, colliders);
            continue;
        }
        if (live.travelled >= live.missile_template.max_distance) {
            live.dead = true;
            impacts_.push_back({live.id, 0, to, false, true, false});
            splash(live, 0, to, colliders);
        }
    }
    // List removal is caller-side in the original; same here on drain.
}

void MissileRuntime::splash(Live& live, std::uint64_t direct_victim,
                              const std::array<float, 3>& point,
                              const std::vector<MissileCollider>& colliders) {
    const float radius = live.missile_template.aoe_radius;
    if (!(radius > 0.0F) || !std::isfinite(radius)) return;
    for (const auto& entity : colliders) {
        if (!entity.live_target) continue;
        if (entity.id == live.spawn.owner_id || entity.id == direct_victim) continue;
        bool seen = false;
        for (const auto hit : live.hit_set)
            if (hit == entity.id) {
                seen = true;
                break;
            }
        if (seen) continue;
        const float ex = entity.position[0] - point[0];
        const float ey = entity.position[1] - point[1];
        const float ez = entity.position[2] - point[2];
        const float reach = radius + entity.radius;
        if (ex * ex + ey * ey + ez * ez > reach * reach) continue;
        live.hit_set.push_back(entity.id);
        impacts_.push_back({live.id, entity.id, point, false, false, true});
    }
}

std::vector<MissileImpact> MissileRuntime::take_impacts() {
    std::vector<MissileImpact> out;
    out.swap(impacts_);
    std::vector<Live> kept;
    kept.reserve(missiles_.size());
    for (auto& live : missiles_)
        if (!live.dead) kept.push_back(live);
    missiles_.swap(kept);
    return out;
}

std::optional<std::array<float, 3>> MissileRuntime::position(std::uint64_t id) const {
    for (const auto& live : missiles_)
        if (live.id == id && !live.dead) return live.pos;
    return std::nullopt;
}

} // namespace torchlight
