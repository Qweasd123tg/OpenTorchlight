#!/usr/bin/env python3
"""Independent float32 emulation of the CInventoryMenu::setOpen viewport block.

Original: setOpen @0xb4eb70, sites 0xb4eef2-0xb4f004 (see
research/disassembly/b4eb70-inventory-setopen.asm and
research/inventory-open.md). Every SSE scalar op (movss/divss/addss/subss/
ucomiss/maxss/cmpnltss+andps) is one numpy binary32 op in the same order,
including the easily missed `movaps xmm5->xmm2 @0xb4eff7` reload of W on the
non-taken path. NaN inputs are out of scope (original inputs are finite:
integer pixels, finite ratio, finite .rodata consts).

Prints C++ float literals (hexfloat) for tests/inventory_menu_test.cpp.
"""
import numpy as np

F = np.float32
ONE = F(1.0)
ZERO = F(0.0)


def scaled(constant: float, yratio: float) -> float:
    return F(F(constant) * F(yratio))


def viewport(width_px: int, height_px: int):
    yratio = F(F(height_px) / F(768.0))
    a = scaled(124.0, yratio)  # 0xfefd50
    b = scaled(132.0, yratio)  # 0xfefd54
    c = scaled(166.0, yratio)  # 0xfefd58
    d = scaled(192.0, yratio)  # 0xfefd5c
    w = F(width_px)
    h = F(height_px)
    x = F(F(F(5000.0) + a) / w)  # this+0x9184 = 5000.0 (ctor @0xb60938)
    y = F(b / h)
    wd = F(c / w)
    hh = F(d / h)
    if F(x + wd) > ONE:  # ucomiss+jbe @0xb4efa8
        wd = F(ONE - x)
    if F(y + hh) > ONE:  # ucomiss+jbe @0xb4efbb
        hh = F(ONE - y)
    x = x if x >= ZERO else ZERO  # cmpnltss+andps @0xb4efcd
    y = np.maximum(ZERO, y)  # maxss @0xb4efd8
    e = F(ONE / w)  # @0xb4efe8
    if wd < e:  # ucomiss+ja @0xb4efee (strictly less)
        x, wd = F(ONE - e), e  # @0xb4f09f; W reload @0xb4eff7 on fallthrough
    return x, y, wd, hh


def hx(v: float) -> str:
    return float(v).hex()


if __name__ == "__main__":
    cases = [(1024, 768), (1280, 720), (1920, 1080), (2560, 1440),
             (800, 600), (1023, 767), (1366, 768), (3840, 2160)]
    for w, h in cases:
        x, y, wd, hh = viewport(w, h)
        print(f"{w:5d}x{h:<5d} x={hx(x)} y={hx(y)} w={hx(wd)} h={hx(hh)}")
