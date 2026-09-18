// Differential/state tests for the missile motion core.
// original-code: CMissile::updatePositionByVelocity @0xd02720 (phases,
// consts and field map: research/missile-motion.md) plus
// UTILITIES::randomBetweenVolatile @0xc92b50. Expected bits come from
// tools/emulate_missile_motion.py (binary32 op-for-op mirror of the ASM);
// libm sin/cos for rotateY is library-derived (same-system-libm), the rest
// is integer/SSE-exact. Spline/orient/trail engine sinks stay open.
#include "torchlight/missile_motion.hpp"
#include "torchlight/randomizer.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
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
std::uint32_t bits(float v) {
    std::uint32_t out = 0;
    std::memcpy(&out, &v, sizeof(out));
    return out;
}
bool be(float v, std::uint32_t b) { return bits(v) == b; }
torchlight::MissileMotionDeps base_deps() {
    torchlight::MissileMotionDeps d;
    d.show_trails = false;
    return d;
}
} // namespace

int main() {
    using namespace torchlight;

    // Volatile LCG: exact integer transcription (seed 1 then a wide seed).
    {
        VolatileRandom rng(1);
        require(be(rng.between(-2.5F, 7.25F), 0xc01e4900u), "lcg s1");
        require(be(rng.between(-2.5F, 7.25F), 0xc01db70du), "lcg s2");
        require(be(rng.between(-2.5F, 7.25F), 0xc01fff73u), "lcg s3");
        require(be(rng.between(-2.5F, 7.25F), 0xc01dcc1au), "lcg s4");
        require(rng.state() == 0x216c061c7d80da7dull, "lcg state");
    }
    {
        VolatileRandom rng(0x123456789ABCDEFULL);
        require(be(rng.between(-2.5F, 7.25F), 0xc01f60a5u), "lcg wide 1");
        require(be(rng.between(-2.5F, 7.25F), 0xc01fbde5u), "lcg wide 2");
        require(be(rng.between(-2.5F, 7.25F), 0xc01e0ae3u), "lcg wide 3");
        require(be(rng.between(-2.5F, 7.25F), 0xc01e7b36u), "lcg wide 4");
        require(rng.state() == 0x0985711c0be88810ull, "lcg wide state");
    }
    {
        VolatileRandom rng(1);
        require(be(rng.between(2.0F, 2.0F), 0x40000000u), "lcg equal");
        require(rng.state() == 1, "lcg equal keeps state");
        const float nan_out = rng.between(std::nanf(""), 1.0F);
        require(nan_out != nan_out, "lcg nan path");
    }

    // Straight flight: normalize + splash + rotate + trail check.
    {
        MissileMotionState s;
        s.vel = {0.0F, 0.0F, 1.0F};
        s.speed = 10.0F;
        s.homing_timer = -0.5F;
        s.arch_timer = 0.02F;
        s.splash_interval = 1.0F;
        s.lateral_cap = 0.5F;
        auto d = base_deps();
        d.position = {0.0F, 0.0F, 0.0F};
        const float dt = 1.0F / 60.0F;
        const auto fx = missile_motion_step(s, d, dt);
        require(be(s.vel[0], 0x3998825bu) && be(s.vel[1], 0x00000000u) &&
                    be(s.vel[2], 0x3f7fffffu),
                "straight vel bits");
        require(be(s.homing_timer, 0xbf044444u), "straight homing timer");
        require(be(s.splash_t, 0x3c888889u) && be(s.splash_lateral, 0x00000000u),
                "straight splash");
        require(fx.orient_called && !fx.spline_path && !fx.place_sphere &&
                    !fx.retargeted,
                "straight effects");
    }

    // Homing arch: steer blend with the asymmetric tail, one accumulator step.
    {
        MissileMotionState s;
        s.vel = {0.5F, -0.25F, 0.75F};
        s.speed = 8.0F;
        s.homing_timer = -0.5F;
        s.arch_timer = 0.02F;
        s.arch_object = true;
        s.arch_factor = 0.2F;
        s.aim_up = 0.5F;
        s.splash_interval = 1.0F;
        s.lateral_cap = 0.5F;
        auto d = base_deps();
        d.orient0 = {0.1F, 0.0F, 0.0F};
        d.orient1 = {0.0F, 0.2F, 0.0F};
        d.has_target = true;
        d.target_alive = true;
        d.target_pos = {10.0F, 2.0F, -4.0F};
        d.position = {1.0F, 1.0F, 1.0F};
        const auto fx = missile_motion_step(s, d, 0.02F);
        require(be(s.vel[0], 0x3f53af1bu) && be(s.vel[1], 0xbe4cbb49u) &&
                    be(s.vel[2], 0x3f3c672du),
                "arch vel bits (asymmetric tail)");
        require(be(s.arch_timer, 0x3bda7408u), "arch timer consumed once");
        require(fx.orient_called && !fx.spline_path, "arch effects");
    }

    // Position bit-test paths (z low byte): spline taken vs orient-2.
    {
        MissileMotionState s;
        s.vel = {0.0F, 0.0F, 1.0F};
        s.speed = 5.0F;
        s.homing_timer = -0.5F;
        s.arch_timer = 0.02F;
        s.splash_interval = 1.0F;
        s.lateral_cap = 0.5F;
        s.spline_threshold = 1.0F;
        auto d = base_deps();
        d.position = {0.0F, 0.0F, 1.1F}; // 0x3F8CCCCD: low byte set
        auto fx = missile_motion_step(s, d, 1.0F / 60.0F);
        require(fx.spline_path, "spline branch on bit+threshold");
        s.spline_threshold = 0.0F;
        s.orient_object = true;
        fx = missile_motion_step(s, d, 1.0F / 60.0F);
        require(!fx.spline_path && fx.orient_called, "orient-2 branch");
    }

    if (failures == 0)
        std::printf("missile_motion: %d assertions; LCG, normalize, arch tail, steps\n",
                    assertions);
    return failures == 0 ? 0 : 1;
}
