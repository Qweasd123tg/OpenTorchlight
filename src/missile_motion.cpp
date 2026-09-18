#include "torchlight/missile_motion.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>

// Portable motion core of CMissile::updatePositionByVelocity @0xd02720.
// Provenance per phase: research/missile-motion.md. All float ops are
// binary32 in original order; bit patterns verified against
// tools/emulate_missile_motion.py. Conventions: Vector3 is [x, y, z];
// missile fields +0x148/14c/150 hold (x, y, z) velocity.

namespace torchlight {
namespace {

constexpr float kEpsDouble = 1e-8; // double compare, ucomisd+jbe (NaN skips)
constexpr float kUnit = 1.0F;
constexpr float kArchStep = 0.03333333507180214F; // 1/30
constexpr float kPiOver180 = 0.01745329252F;

inline float mul(float a, float b) { return a * b; }

float vec_len(const MissileVec &v) {
    // Order per ASM: ((y*y) + (z*z)) + (x*x).
    const float yy = mul(v[1], v[1]);
    const float zz = mul(v[2], v[2]);
    const float xx = mul(v[0], v[0]);
    return std::sqrt((yy + zz) + xx);
}

void normalize(MissileVec &v, float len) {
    const float f = kUnit / len;
    v[0] = mul(v[0], f);
    v[1] = mul(v[1], f);
    v[2] = mul(v[2], f);
}

bool orient_nonzero(float len) {
    // ucomisd against double 1e-8 + jbe: normalize iff strictly greater.
    return static_cast<double>(len) > static_cast<double>(kEpsDouble);
}

std::uint32_t bits(float v) {
    std::uint32_t out = 0;
    std::memcpy(&out, &v, sizeof(out));
    return out;
}

} // namespace

MissileMotionEffects missile_motion_step(MissileMotionState &s,
                                         const MissileMotionDeps &d, float dt) {
    MissileMotionEffects fx;
    // Phase 1: two steer-accel passes (virtuals *0x130/*0x138, injected).
    // Per component: t = dir.speed; t *= dt; vel += t.
    for (const MissileVec *dir : {&d.orient0, &d.orient1}) {
        for (int c = 0; c < 3; ++c) {
            float t = mul((*dir)[c], s.speed);
            t = mul(t, dt);
            s.vel[c] = s.vel[c] + t;
        }
    }
    // Phase 2: normalize (skip on <= 1e-8 or NaN). The length is also
    // latched for the rotate-path rescale (0x28 rsp slot).
    float pre_len = 0.0F;
    {
        const float len = vec_len(s.vel);
        pre_len = len;
        if (orient_nonzero(len))
            normalize(s.vel, len);
    }
    // Phase 3: homing retarget. Timer always decrements.
    s.homing_timer = s.homing_timer - dt;
    if (d.has_target && !d.target_alive) {
        // Bounded scan of tracked_ids for old_target_id. Mirrors the exact
        // control flow including the +0x2a4-gated recheck (dead under the
        // recorded invariant, kept literally).
        bool found = false;
        unsigned eax = 0;
        const unsigned total = static_cast<unsigned>(d.tracked_ids.size());
        const unsigned bound_a = d.track_bound_a ? d.track_bound_a : total;
        const unsigned bound_b = d.track_bound_b ? d.track_bound_b : total;
        while (true) {
            if (eax >= bound_a) {
                // L0 recheck path: examine slot 0 once more, then continue.
                if (!d.tracked_ids.empty() && d.tracked_ids[0] == d.old_target_id) {
                    found = true;
                    break;
                }
                eax += 1;
                if (eax >= bound_b || eax >= total)
                    break;
                continue;
            }
            if (eax < total && d.tracked_ids[eax] == d.old_target_id) {
                found = true;
                break;
            }
            eax += 1;
            if (eax >= bound_b || eax >= total)
                break;
        }
        if (found && d.reacquire) {
            fx.retargeted = true;
            fx.new_target_id = d.reacquire->first;
        }
    }
    // Phase 4: arch gate. Ordered compares (ucomiss+jcc): NaN never enters.
    // Gate passes iff homing_timer <= 0 AND arch object AND factor > 0.
    const bool gate_shut = (s.homing_timer > 0.0F) || !s.arch_object ||
                           !(s.arch_factor > 0.0F);
    if (!gate_shut) {
        s.arch_timer = s.arch_timer + dt;
        // Fixed-step accumulator: consume 1/30 steps, steering once each.
        while (s.arch_timer >= kArchStep) {
            s.arch_timer = s.arch_timer - kArchStep;
            // Steer blend: vel = dirN*f + vel*(1-f), exact op order.
            // dirN = normalize(target + aim_up - pos).
            MissileVec to = {d.target_pos[0] - d.position[0],
                             d.target_pos[1] - d.position[1] + 2.0F * s.aim_up,
                             d.target_pos[2] - d.position[2]};
            {
                const float len = vec_len(to);
                if (orient_nonzero(len))
                    normalize(to, len);
            }
            const float f = s.arch_factor;
            const float g = kUnit - f;
            // Component order per ASM: y, x, then z.
            const float vel_gy = mul(s.vel[1], g);
            const float new_y = mul(to[1], f) + vel_gy;
            const float new_x = mul(to[0], f) + mul(s.vel[0], g);
            const float new_z = mul(to[2], f) + mul(s.vel[2], g);
            s.vel[1] = new_y;
            s.vel[0] = new_x;
            s.vel[2] = new_z;
            // Tail: asymmetric partial-norm recompute, transcribed literally
            // (d02b92-d02bbd). t = new_x*vel.y*(1-f) + new_z^2 + new_z^2:
            // NOT |v|^2 — likely an original code quirk (CSE artifact or
            // bug). Do NOT "fix" into a real norm; bit-exactness needs the
            // exact sequence. The blended velocity is then scaled by
            // 1/sqrt(t) (skipped on <= 1e-8 or NaN).
            float t = mul(new_x, vel_gy) + mul(new_z, new_z);
            t = t + mul(new_z, new_z);
            const float t_len = std::sqrt(t);
            if (orient_nonzero(t_len)) {
                const float inv = kUnit / t_len;
                s.vel[0] = mul(new_x, inv);
                s.vel[1] = mul(new_y, inv);
                s.vel[2] = mul(new_z, inv);
            }
        }
        // Falls through to splash (d02bec -> d02bed check): no return here.
    }
    // Phase 5: splash advance.
    {
        const float rate_dt = mul(dt, s.splash_rate);
        s.splash_t = s.splash_t + dt;
        s.splash_lateral = s.splash_lateral + rate_dt;
    }
    if (!(s.splash_t > s.splash_interval)) {
        // Phase 6: lateral clamp |lateral| <= |cap| (abs-mask compares).
        const float a_lat = std::fabs(s.splash_lateral);
        const float a_cap = std::fabs(s.lateral_cap);
        if (a_lat > a_cap) {
            s.splash_lateral =
                (s.splash_lateral < 0.0F) ? -s.lateral_cap : s.lateral_cap;
        }
    } else {
        // Phase 7: jitter. RNG injected (volatile LCG in production).
        const float r = d.random_between ? d.random_between(-s.jitter, s.jitter) : 0.0F;
        s.splash_lateral = s.splash_lateral + r;
        s.splash_t = 0.0F;
        const float a_lat = std::fabs(s.splash_lateral);
        const float a_cap = std::fabs(s.lateral_cap);
        if (a_lat > a_cap) {
            s.splash_lateral =
                (s.splash_lateral < 0.0F) ? -s.lateral_cap : s.lateral_cap;
        }
    }
    // Phase 8: rotate velocity by dt*pi/180 (MATH::rotateY, library-derived
    // glibc sincosf semantics: x' = x*cos+z*sin, z' = z*cos-x*sin),
    // then rescale by the stale phase-2 length.
    {
        const double angle = static_cast<double>(dt) * static_cast<double>(kPiOver180);
        const float s_a = static_cast<float>(std::sin(angle));
        const float c_a = static_cast<float>(std::cos(angle));
        const float x = s.vel[0], z = s.vel[2];
        s.vel[0] = mul(x, c_a) + mul(z, s_a);
        s.vel[2] = mul(z, c_a) - mul(x, s_a);
        s.vel[0] = mul(s.vel[0], pre_len);
        s.vel[1] = mul(s.vel[1], pre_len);
        s.vel[2] = mul(s.vel[2], pre_len);
    }
    // Orient call #1 (virtual *0x128, open target): the call itself is
    // unconditional on this path (only the temp normalize is eps-gated).
    // Reported, not executed.
    fx.orient_called = true;
    // Predicted position + validity bit-test. The tested byte is the low
    // byte of the third getPosition float (z by register-flow inference —
    // marked inferred; behavior pinned by tests with crafted patterns).
    const MissileVec predicted = {d.position[0] + mul(s.vel[0], dt),
                                  d.position[1] + mul(s.vel[1], dt),
                                  d.position[2] + mul(s.vel[2], dt)};
    const bool pos_bit_set = (bits(d.position[2]) & 0xFFu) != 0u;
    if (pos_bit_set && s.spline_threshold > 0.0F) {
        // Spline path (d02fc0): next package (needs CPath evaluator).
        fx.spline_path = true;
        return fx;
    }
    if (pos_bit_set) {
        // Second normalize into temps + orient call #2 on the orient object
        // (virtual *0x128, open target). Reported, not executed.
        const float len = vec_len(s.vel);
        if (orient_nonzero(len) && s.orient_object)
            fx.orient_called = true;
    }
    // Phase 9: trail check. GetInt(SHOW_MISSILE_TRAILS) is injected.
    if (d.show_trails) {
        // dist(predicted, lock) > eps → lock = predicted, placeSphere.
        const float dx = predicted[0] - s.lock[0];
        const float dy = predicted[1] - s.lock[1];
        const float dz = predicted[2] - s.lock[2];
        const float dist =
            std::sqrt(mul(dx, dx) + mul(dy, dy) + mul(dz, dz));
        if (dist > kUnit) {
            s.lock = predicted;
            fx.place_sphere = true;
        }
    }
    return fx;
}

} // namespace torchlight
