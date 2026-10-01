#!/usr/bin/env python3
"""Op-for-op binary32 emulation of CMissile motion fragments.

Mirrors the machine code, not the port: every mulss/addss/sqrtss/divss is one
numpy float32 op in original order (see research/missile-motion.md). Used to
generate the literals pinned in tests/missile_motion_test.cpp; rerun to
re-derive them after any transcription change.

Covers: volatile LCG (integer-exact), velocity normalize, arch blend + the
asymmetric tail, splash advance/clamp, rotateY rescale.
"""
import struct
import sys

import numpy as np

F32 = lambda v: np.float32(v)


def bits(v):
    return "0x%08x" % struct.unpack("<I", struct.pack("<f", float(v)))[0]


def lcg_between(state, lo, hi):
    lo, hi = F32(lo), F32(hi)
    if lo == hi:
        return state, lo
    K = 0x29777B41
    M = (1 << 64) - 1
    lo32 = state & 0xFFFFFFFF
    hi32 = (state >> 32) & 0xFFFFFFFF
    t2 = (lo32 * K + hi32) & M
    t3 = ((t2 & 0xFFFFFFFF) * K + (t2 >> 32)) & M
    state = t3
    raw = (((t3 & 0xFFFFFFFF) + ((t2 & 0xFFFFFFFF) << 32)) & 0xFFFFFFFFFFFFF) | 0x3FF0000000000000
    frac = struct.unpack("<d", struct.pack("<Q", raw))[0] - 1.0
    span = np.float64(np.float32(hi - lo)) * frac
    return state, F32(lo + np.float32(span))


def vec_len(v):
    yy = F32(v[1] * v[1])
    zz = F32(v[2] * v[2])
    xx = F32(v[0] * v[0])
    return np.sqrt(F32(F32(yy + zz) + xx))


def normalize(v):
    ln = vec_len(v)
    if not float(ln) > 1e-8:
        return v
    f = F32(F32(1.0) / ln)
    return [F32(c * f) for c in v]


def arch_blend(vel, target_dir, f):
    g = F32(F32(1.0) - f)
    new_y = F32(F32(target_dir[1] * f) + F32(vel[1] * g))
    new_x = F32(F32(target_dir[0] * f) + F32(vel[0] * g))
    new_z = F32(F32(target_dir[2] * f) + F32(vel[2] * g))
    vel_gy = F32(vel[1] * g)
    t = F32(F32(new_x * vel_gy) + F32(new_z * new_z))
    t = F32(t + F32(new_z * new_z))
    ln = np.sqrt(t)
    if float(ln) > 1e-8:
        inv = F32(F32(1.0) / ln)
        return [F32(new_x * inv), F32(new_y * inv), F32(new_z * inv)]
    return [new_x, new_y, new_z]


def main():
    out = []
    # LCG from two seeds (seed 0 exercises the low-bit path).
    for seed in (1, 0x123456789ABCDEF):
        st = seed
        vals = []
        for _ in range(4):
            st, v = lcg_between(st, -2.5, 7.25)
            vals.append(v)
        out.append(("lcg_%016x" % seed, vals, st))
    # Equal bounds short-circuit; NaN falls into the random path.
    st, v = lcg_between(1, 2.0, 2.0)
    out.append(("lcg_equal", [v], st))
    st, v = lcg_between(1, float("nan"), 1.0)
    out.append(("lcg_nan", [v], st))
    # Normalize incl. previously-normalized rescale shape.
    out.append(("norm", normalize([F32(3.0), F32(-4.0), F32(12.0)]), None))
    out.append(("norm_zero", normalize([F32(0.0), F32(0.0), F32(0.0)]), None))
    # Arch blend incl. the asymmetric tail (deliberately not |v|).
    out.append(("arch", arch_blend([F32(0.5), F32(-0.25), F32(0.75)],
                                   [F32(0.1), F32(0.9), F32(-0.3)], F32(0.2)), None))
    for name, vals, st in out:
        if isinstance(vals, list):
            print("%s:" % name, " ".join(bits(v) for v in vals),
                  ("state=0x%016x" % st) if st is not None else "")
        else:
            print("%s: %s" % (name, bits(vals)))
    # Full step() mirror for the C++ test literals (scripted deps).
    print("--- step scenarios ---")
    for tag, vel, speed, dirs, tgt, tgt_pos, pos, arch, splash, dt in SCENARIOS:
        print(tag, " ".join("%s=%s" % kv for kv in step(vel, speed, dirs, tgt,
                                                        tgt_pos, pos, arch, splash, dt)))


def step(vel, speed, dirs, tgt, tgt_pos, pos, arch, splash, dt):
    # vel/speed updated in place like the port; returns (vel_bits, flags...).
    import math
    vel = [F32(v) for v in vel]
    dt = F32(dt)
    for d in dirs:
        for c in range(3):
            vel[c] = F32(vel[c] + F32(F32(d[c] * F32(speed)) * dt))
    pre_len = vec_len(vel)
    vel = normalize(vel)
    homing_timer = F32(F32(-0.5) - dt)  # scripted: starts -0.5 (subss)
    flags = [("homing_timer", bits(homing_timer))]
    arch_iters = 0
    timer = F32(0.02)  # scripted arch_timer state; advanced only in-gate
    if not (homing_timer > 0.0):
        if arch["object"] and arch["factor"] > 0.0:
            timer = F32(timer + dt)
            while timer >= F32(1.0 / 30.0):
                timer = F32(timer - F32(1.0 / 30.0))
                to = [F32(tgt_pos[0] - pos[0]),
                      F32(F32(tgt_pos[1] - pos[1]) + F32(2.0 * arch["aim"])),
                      F32(tgt_pos[2] - pos[2])]
                to = normalize(to)
                vel = arch_blend(vel, to, F32(arch["factor"]))
                arch_iters += 1
    flags.append(("arch_iters", "%d" % arch_iters))
    flags.append(("arch_timer", bits(timer)))
    # splash advance
    st_t = F32(F32(splash["t"]) + dt)
    st_l = F32(splash["l"] + F32(dt * F32(splash["rate"])))
    if not (st_t > F32(splash["interval"])):
        if abs(float(st_l)) > abs(float(splash["cap"])):
            st_l = F32(-splash["cap"]) if st_l < 0.0 else F32(splash["cap"])
    else:
        st_l = F32(st_l + F32(0.0))  # scripted RNG returns 0
        st_t = F32(0.0)
        if abs(float(st_l)) > abs(float(splash["cap"])):
            st_l = F32(-splash["cap"]) if st_l < 0.0 else F32(splash["cap"])
    flags.append(("splash_t", bits(st_t)))
    flags.append(("splash_l", bits(st_l)))
    # rotate + rescale + orient flags
    angle = float(dt) * 0.01745329252
    sa, ca = F32(math.sin(angle)), F32(math.cos(angle))
    x, z = vel[0], vel[2]
    vel[0] = F32(F32(x * ca) + F32(z * sa))
    vel[2] = F32(F32(z * ca) - F32(x * sa))
    vel = [F32(v * pre_len) for v in vel]
    flags.append(("orient", "1"))
    pred = [F32(p + F32(v * dt)) for p, v in zip(pos, vel)]
    zbits = struct.unpack("<I", struct.pack("<f", float(pos[2])))[0]
    flags.append(("al", "1" if (zbits & 0xFF) != 0 else "0"))
    if (zbits & 0xFF) != 0 and splash.get("spline_thr", 0.0) > 0.0:
        flags.append(("spline", "1"))
        return [("vel", " ".join(bits(v) for v in vel))] + flags
    return [("vel", " ".join(bits(v) for v in vel))] + flags


SCENARIOS = [
    ("bitpath_spline", [F32(0.0), F32(0.0), F32(1.0)], F32(5.0),
     [[F32(0.0), F32(0.0), F32(0.0)], [F32(0.0), F32(0.0), F32(0.0)]],
     False, [0.0, 0.0, 0.0], [F32(0.0), F32(0.0), F32(1.1)],
     {"object": False, "factor": F32(0.0), "aim": F32(0.0)},
     {"t": F32(0.0), "l": F32(0.0), "rate": F32(0.0), "interval": F32(1.0),
      "cap": F32(0.5), "spline_thr": F32(1.0)}, F32(1.0 / 60.0)),
    ("bitpath_orient2", [F32(0.0), F32(0.0), F32(1.0)], F32(5.0),
     [[F32(0.0), F32(0.0), F32(0.0)], [F32(0.0), F32(0.0), F32(0.0)]],
     False, [0.0, 0.0, 0.0], [F32(0.0), F32(0.0), F32(1.1)],
     {"object": False, "factor": F32(0.0), "aim": F32(0.0)},
     {"t": F32(0.0), "l": F32(0.0), "rate": F32(0.0), "interval": F32(1.0),
      "cap": F32(0.5), "spline_thr": F32(0.0)}, F32(1.0 / 60.0)),
    ("straight", [F32(0.0), F32(0.0), F32(1.0)], F32(10.0),
     [[F32(0.0), F32(0.0), F32(0.0)], [F32(0.0), F32(0.0), F32(0.0)]],
     False, [0.0, 0.0, 0.0], [F32(0.0), F32(0.0), F32(0.0)],
     {"object": False, "factor": F32(0.0), "aim": F32(0.0)},
     {"t": F32(0.0), "l": F32(0.0), "rate": F32(0.0), "interval": F32(1.0),
      "cap": F32(0.5), "spline_thr": F32(0.0)}, F32(1.0 / 60.0)),
    ("homing_arch", [F32(0.5), F32(-0.25), F32(0.75)], F32(8.0),
     [[F32(0.1), F32(0.0), F32(0.0)], [F32(0.0), F32(0.2), F32(0.0)]],
     True, [F32(10.0), F32(2.0), F32(-4.0)], [F32(1.0), F32(1.0), F32(1.0)],
     {"object": True, "factor": F32(0.2), "aim": F32(0.5)},
     {"t": F32(0.0), "l": F32(0.0), "rate": F32(0.0), "interval": F32(1.0),
      "cap": F32(0.5), "spline_thr": F32(0.0)}, F32(0.02)),
]


if __name__ == "__main__":
    main()
