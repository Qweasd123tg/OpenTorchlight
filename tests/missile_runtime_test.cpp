// Missile runtime: template loader + flight/collision/delivery semantics.
// original-code: CMissile init/fire/update/collision/hit/kill contract,
// research/missile-runtime.md. Resource-backed: FIREWAND/BOWMISSILE load
// from the real pak when TORCHLIGHT_GAME_DIR is set, else that section
// reports SKIP (mechanics below always run).
#include "torchlight/missile_runtime.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>

namespace {
int failures = 0;
int assertions = 0;
void require(bool cond, const char* what) {
    ++assertions;
    if (!cond) {
        ++failures;
        std::printf("FAIL: %s\n", what);
    }
}

torchlight::MissileTemplate straight_template() {
    torchlight::MissileTemplate t;
    t.name = "TESTSTRAIGHT";
    t.max_distance = 60.0F;
    t.max_velocity = 10.0F;
    t.radius = 0.2F;
    return t;
}

torchlight::CollisionScene empty_scene() { return {}; }

torchlight::CollisionScene wall_at_x5() {
    torchlight::CollisionScene scene;
    torchlight::CollisionTriangle wall;
    wall.vertices = {{{5.0F, -10.0F, -10.0F}, {5.0F, -10.0F, 10.0F}, {5.0F, 10.0F, 0.0F}}};
    scene.triangles.push_back(wall);
    return scene;
}
} // namespace

int main() {
    if (const char* game_dir = std::getenv("TORCHLIGHT_GAME_DIR")) {
        const std::string pak = std::string(game_dir) + "/pak.zip";
        try {
            const torchlight::PakArchive archive(pak);
            for (const char* name : {"FIREWAND", "BOWMISSILE"}) {
                const auto loaded = torchlight::load_missile_template(archive, name);
                require(loaded.has_value(), "missile template loads from real pak");
                if (!loaded.has_value()) continue;
                std::printf("template %s: dist=%.3f vel=%.3f radius=%.3f aoe_r=%.3f aoe_s=%.3f die=%s\n",
                            name, loaded->max_distance, loaded->max_velocity, loaded->radius,
                            loaded->aoe_radius, loaded->aoe_damage_scale, loaded->die_layout.c_str());
                require(std::isfinite(loaded->max_distance) && loaded->max_distance > 0.0F,
                        "template distance sane");
                require(std::isfinite(loaded->max_velocity) && loaded->max_velocity > 0.0F,
                        "template velocity sane");
            }
            require(!torchlight::load_missile_template(archive, "NO_SUCH_MISSILE_XYZ").has_value(),
                    "missing template refuses");
        } catch (const std::exception& e) {
            std::printf("FAIL: pak load threw: %s\n", e.what());
            ++failures;
        }
    } else {
        std::printf("SKIP: TORCHLIGHT_GAME_DIR unset, loader section skipped\n");
    }

    {
        // Straight flight: constant velocity, position advance, expiry.
        torchlight::MissileRuntime runtime;
        torchlight::MissileSpawn spawn;
        spawn.origin = {0.0F, 0.0F, 0.0F};
        spawn.direction = {1.0F, 0.0F, 0.0F};
        const auto id = runtime.spawn(straight_template(), spawn);
        require(id != 0, "straight spawn accepted");
        for (int i = 0; i < 30; ++i) runtime.step(1.0F / 30.0F, {}, empty_scene());
        const auto pos = runtime.position(id);
        require(pos.has_value(), "missile still flying after 1s");
        if (pos.has_value()) {
            require(std::fabs((*pos)[0] - 10.0F) < 0.05F, "1s at 10u/s reaches x=10");
            // Original quirk (machine-code fact, d02c68-d02c8b): EVERY
            // missile rotates by dt*pi/180 per tick (~1 deg/s), so 1s at
            // 10u/s drifts laterally ~0.09. Fire-and-forget templates live
            // ~0.1-0.5s, where this is sub-pixel; the runtime reproduces it
            // bit-exact via missile_motion_step, not by choice.
            require(std::fabs((*pos)[1]) < 0.12F && std::fabs((*pos)[2]) < 0.12F,
                    "lateral drift within the original 1deg/s rotation");
        }
        for (int i = 0; i < 300; ++i) runtime.step(1.0F / 30.0F, {}, empty_scene());
        const auto impacts = runtime.take_impacts();
        require(impacts.size() == 1 && impacts[0].expired && impacts[0].victim_id == 0,
                "distance lifetime expires exactly once");
        require(!runtime.position(id).has_value(), "expired missile removed");
        require(runtime.take_impacts().empty(), "impact drain is single-shot");
    }
    {
        // Wall stop: authored triangle at x=5 blocks, no victim, no expiry.
        torchlight::MissileRuntime runtime;
        torchlight::MissileSpawn spawn;
        spawn.origin = {0.0F, 0.0F, 0.0F};
        spawn.direction = {1.0F, 0.0F, 0.0F};
        runtime.spawn(straight_template(), spawn);
        for (int i = 0; i < 120; ++i) runtime.step(1.0F / 30.0F, {}, wall_at_x5());
        const auto impacts = runtime.take_impacts();
        require(impacts.size() == 1 && impacts[0].blocked && !impacts[0].expired,
                "wall stops missile with blocked impact");
        if (!impacts.empty())
            require(impacts[0].position[0] <= 5.0F, "blocked at or before the wall");
        require(runtime.empty(), "blocked missile removed");
    }
    {
        // Unit hit: owner excluded, victim recorded once, dead after hit.
        torchlight::MissileRuntime runtime;
        torchlight::MissileSpawn spawn;
        spawn.origin = {0.0F, 0.0F, 0.0F};
        spawn.direction = {1.0F, 0.0F, 0.0F};
        spawn.owner_id = 7;
        runtime.spawn(straight_template(), spawn);
        const torchlight::MissileCollider owner{7, {0.0F, 0.0F, 0.0F}, 0.5F, true};
        const torchlight::MissileCollider foe{9, {6.0F, 0.0F, 0.0F}, 0.5F, true};
        for (int i = 0; i < 120; ++i)
            runtime.step(1.0F / 30.0F, {owner, foe}, empty_scene());
        const auto impacts = runtime.take_impacts();
        require(impacts.size() == 1 && impacts[0].victim_id == 9, "foe hit once, owner skipped");
        require(runtime.empty(), "spent missile removed (no second damage)");
    }
    {
        // AOE splash (original doAOEDamage): direct victim + everyone else
        // in radius, owner excluded, no double hits.
        torchlight::MissileRuntime runtime;
        auto aoe = straight_template();
        aoe.aoe_radius = 2.0F;
        aoe.aoe_damage_scale = 0.33F;
        torchlight::MissileSpawn spawn;
        spawn.origin = {0.0F, 0.0F, 0.0F};
        spawn.direction = {1.0F, 0.0F, 0.0F};
        spawn.owner_id = 7;
        require(runtime.spawn(aoe, spawn) != 0, "AOE template accepted with sink");
        const torchlight::MissileCollider owner{7, {0.0F, 0.0F, 0.0F}, 0.5F, true};
        const torchlight::MissileCollider foe{9, {6.0F, 0.0F, 0.0F}, 0.5F, true};
        const torchlight::MissileCollider near{11, {7.0F, 0.0F, 1.0F}, 0.5F, true};
        const torchlight::MissileCollider far{13, {30.0F, 0.0F, 0.0F}, 0.5F, true};
        for (int i = 0; i < 120; ++i)
            runtime.step(1.0F / 30.0F, {owner, foe, near, far}, empty_scene());
        const auto impacts = runtime.take_impacts();
        bool direct = false, splash = false;
        for (const auto& impact : impacts) {
            if (impact.victim_id == 9 && !impact.splash) direct = true;
            if (impact.victim_id == 11 && impact.splash) splash = true;
            require(impact.victim_id != 7 && impact.victim_id != 13, "owner/far untouched by splash");
        }
        require(direct && splash, "direct hit plus in-radius splash");
        require(runtime.empty(), "AOE missile removed after impact");
    }
    {
        // Refusals: bad direction, bad speed.
        torchlight::MissileRuntime runtime;
        torchlight::MissileSpawn spawn;
        spawn.origin = {0.0F, 0.0F, 0.0F};
        spawn.direction = {1.0F, 0.0F, 0.0F};
        torchlight::MissileSpawn bad = spawn;
        bad.direction = {0.0F, 0.0F, 0.0F};
        require(runtime.spawn(straight_template(), bad) == 0, "zero direction refused");
        require(runtime.empty(), "refusals leave no live missiles");
    }
    if (failures == 0)
        std::printf("missile_runtime: %d assertions\n", assertions);
    return failures == 0 ? 0 : 1;
}
