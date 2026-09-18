#pragma once

#include "torchlight/adm_document.hpp"
#include "torchlight/collision_scene.hpp"
#include "torchlight/missile_motion.hpp"
#include "torchlight/pak_archive.hpp"

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace torchlight {
// original-code: CMissile creation/frame contract (initialize @0xd00650,
// fireMissile @0xd04610, update @0xd04120, checkCollision @0xd038a0,
// handleMissileHitUnit @0xd034c0, doDamageToCharacter @0xcf9620,
// killMissile @0xd014a0, handleDeathOfMissile @0xcf9840; ELF SHA-256
// 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b;
// analysis research/missile-runtime.md).
//
// Template values come from media/Missiles/<NAME>.LAYOUT.adm; initialize()
// defaults are the fallbacks (never transferred as behavior guesses).
// Units, radii and damage ride the existing port types; model/particle/
// trail rendering has no sink (open, same category as skill visuals).
struct MissileTemplate {
    std::string name;
    float max_distance = 25.0F; // initialize +0x1b8
    float max_velocity = 1.0F; // initialize +0x158
    float radius = 0.2F; // initialize +0x178
    float aoe_radius = 0.0F; // template AOE RAIDUS (original typo kept in key)
    float aoe_damage_scale = 0.0F; // template AOE DAMAGE SCALE
    std::string die_layout;
    std::string missile_name;
};

// Loads media/Missiles/<name>.LAYOUT.adm. Missing file or unreadable
// fields -> nullopt (caller keeps the refusal, never a guessed missile).
[[nodiscard]] std::optional<MissileTemplate> load_missile_template(const PakArchive& pak,
                                                                   std::string_view name);

struct MissileSpawn {
    std::array<float, 3> origin = {0.0F, 0.0F, 0.0F};
    std::array<float, 3> direction = {0.0F, 0.0F, 1.0F};
    std::uint64_t owner_id = 0; // excluded from hits (original +0x220)
    std::uint64_t target_id = 0; // 0 none
    float speed_override = -1.0F; // <0: template max_velocity
};

struct MissileImpact {
    std::uint64_t missile_id = 0;
    std::uint64_t victim_id = 0; // 0: world/blocked/expired, no victim
    std::array<float, 3> position = {0.0F, 0.0F, 0.0F};
    bool blocked = false; // stopped by world geometry
    bool expired = false; // lifetime/distance spent, no contact
    bool splash = false; // AOE victim (original doAOEDamage list)
};

// Flat collider view so the runtime stays decoupled from the world type;
// the application maps RuntimeEntity rows to these each frame.
struct MissileCollider {
    std::uint64_t id = 0;
    std::array<float, 3> position = {0.0F, 0.0F, 0.0F};
    float radius = 0.0F;
    bool live_target = false; // alive + enabled + combat_targetable
};

// Frame runtime for live missiles: straight or template-driven flight via
// missile_motion_step, unit-sphere hits with owner exclusion + single-hit
// set, world obstruction via collision_segment_clear, distance lifetime,
// and AOE splash (original doAOEDamage: full base damage to all others in
// radius; the template scale feeds effect hooks only, which have no sink).
// Ricochet/pierce/reflect/homing/arch have no port path yet: templates
// carrying them stay refused by the caller (open, see header).
class MissileRuntime {
public:
    [[nodiscard]] bool empty() const noexcept { return missiles_.empty(); }
    [[nodiscard]] std::size_t size() const noexcept { return missiles_.size(); }

    // Returns 0 when the template refuses (arch/AOE/speed issues, see notes).
    std::uint64_t spawn(const MissileTemplate& missile_template, const MissileSpawn& spawn);
    // Steps all missiles by dt seconds; impacts are drained via take_impacts.
    void step(float dt, const std::vector<MissileCollider>& colliders,
              const CollisionScene& collision);
    [[nodiscard]] std::vector<MissileImpact> take_impacts();

    // Test seam: current position of a live missile, nullopt when gone.
    [[nodiscard]] std::optional<std::array<float, 3>> position(std::uint64_t id) const;

private:
    // AOE splash (original doAOEDamage, research/missile-runtime.md §7):
    // every other live collider within aoe_radius of the impact point takes
    // the same base damage path; owner/direct victim/hit-set excluded.
    struct Live {
        std::uint64_t id = 0;
        MissileTemplate missile_template;
        MissileSpawn spawn;
        MissileMotionState motion;
        std::array<float, 3> pos = {0.0F, 0.0F, 0.0F}; // getPosition/setPosition anchor
        float travelled = 0.0F;
        std::vector<std::uint64_t> hit_set; // single-hit (original +0x298 scan)
        bool dead = false;
    };
    std::vector<Live> missiles_;
    std::vector<MissileImpact> impacts_;
    std::uint64_t next_id_ = 1;

    void splash(Live& live, std::uint64_t direct_victim, const std::array<float, 3>& point,
                const std::vector<MissileCollider>& colliders);
};

} // namespace torchlight
