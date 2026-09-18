#pragma once

// Portable motion core of CMissile::updatePositionByVelocity @0xd02720.
//
// original-code: Torchlight.bin.x86_64
//   (SHA-256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b)
//   Analysis: research/missile-motion.md (phases, float consts, field map).
//
// BOUNDARY: only the engine-free motion math is modelled here — velocity
// steer/normalize, homing retarget decision, arch accumulator + blend,
// splash/jitter/clamp, spline advance. Virtual orientation getters, the
// spline evaluator, RNG and settings are injected inputs (their meanings
// are open). Engine sinks (placeSphere, trail spawn, setTarget,...) — hmm,
// setTarget IS modelled as a reported effect; placeSphere/trails are
// reported effects, not executed. All arithmetic is binary32 in original
// op order (see tools/emulate_missile_motion.py).

#include <array>
#include <cstdint>
#include <functional>
#include <optional>
#include <vector>

namespace torchlight {

using MissileVec = std::array<float, 3>; // x, y, z

struct MissileMotionState {
    MissileVec vel = {0.0F, 0.0F, 0.0F}; // +0x148/14c/150 (x/y/z)
    float speed = 0.0F;                  // +0x154
    float homing_timer = 0.0F;           // +0x258 (arch delay, ticks down)
    float arch_timer = 0.0F;             // +0x25c
    float arch_factor = 0.0F;            // +0x250
    bool arch_object = false;            // +0x230 != 0
    float splash_t = 0.0F;               // +0x278
    float splash_lateral = 0.0F;         // +0x274
    float splash_interval = 0.0F;        // +0x270
    float splash_rate = 0.0F;            // +0x268
    float lateral_cap = 0.0F;            // +0x264
    float jitter = 0.0F;                 // +0x26c
    float spline_dist = 0.0F;            // +0x1c4
    MissileVec lock = {0.0F, 0.0F, 0.0F}; // +0x1e0/1e4/1e8
    float aim_up = 0.0F;                 // +0x178
    float steer_rate = 0.0F;             // +0x15c
    float spline_threshold = 0.0F;       // +0x19c (> 0 selects spline path)
    bool has_path = false;               // +0x210 != 0
    float path_length = 0.0F;            // +0x210 + 0x18
    bool orient_object = false;          // +0x108 != 0
};

struct MissileMotionDeps {
    MissileVec orient0 = {0.0F, 0.0F, 0.0F}; // virtual *0x130 (open)
    MissileVec orient1 = {0.0F, 0.0F, 0.0F}; // virtual *0x138 (open)
    MissileVec position = {0.0F, 0.0F, 0.0F}; // getPosition (injected)
    bool has_target = false;
    bool target_alive = true;
    MissileVec target_pos = {0.0F, 0.0F, 0.0F}; // live target position
    std::vector<std::uint64_t> tracked_ids; // +0x298 contents (opaque)
    std::uint64_t old_target_id = 0;        // +0x240 identity
    unsigned track_bound_a = 0;             // +0x2a4 role (open)
    unsigned track_bound_b = 0;             // +0x2a0 role (open)
    // getClosestTarget replacement: new target identity + position.
    std::optional<std::pair<std::uint64_t, MissileVec>> reacquire;
    // CPath::GetSplinePositionAtDistance replacement.
    std::function<MissileVec(float)> spline_at;
    float seg_a0 = 0.0F, seg_a1 = 0.0F; // +0x1b8/+0x1c0
    float seg_b0 = 0.0F, seg_b1 = 0.0F; // +0x198/+0x1bc
    bool show_trails = false;           // KSETTINGS_SHOW_MISSILE_TRAILS
    std::function<float(float, float)> random_between; // volatile RNG
};

struct MissileMotionEffects {
    bool retargeted = false;
    std::uint64_t new_target_id = 0;
    bool place_sphere = false;
    bool orient_called = false; // virtual *0x128 taken (open target)
    bool spline_path = false;   // spline branch taken: next package
};

// One updatePositionByVelocity(dt) step. Bit-exact binary32 op order;
// compare against tools/emulate_missile_motion.py, not this comment.
MissileMotionEffects missile_motion_step(MissileMotionState &state,
                                         const MissileMotionDeps &deps, float dt);

} // namespace torchlight
