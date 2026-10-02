# Generated scalar Y scaling and float-property reader

2026-10-02. `original-code`: read-only external
`/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`library-derived`: raw x86:LE:64 p-code from pinned Ghidra 12.1.3, with tool
identity recorded in [pcode-automation.md](pcode-automation.md). Decompiler C
is navigation; the accepted inputs and original ASM establish this contract.

## Complete source bodies

| Function | Symbol / executed bytes | Accepted source and whole-symbol SHA-256 |
|---|---:|---|
| `CGameUI::scaledY(float) @0xa83e70` | 36 / 36 | [00a83e70.json](lifted-ui/00a83e70.json); `0d3b9227d789dac1773c5bb1dda4d9b550c8afb1f6bc1ae4678d4065c41fb1d5` |
| `CDynamicPropertyFile::GetFloat(unsigned) @0xc6e410` | 41 / 37 | [00c6e410.json](lifted-ui/00c6e410.json); `30db2a32eba48ef0dcbbf449cb9d95e283b90618733c713beb22e5a25882f7dc` |

`GetFloat` has an unreachable four-byte alignment NOP at `0xc6e42c..2f`
between its first RET and the fallback target. The complete 41-byte symbol
is pinned; neither executable exit is omitted.

`original-code`: GetFloat reads begin/end pointer64 from `this+0x58/+0x60`
(`0xc6e410/414`), zero-extends its uint32 ESI index (`0xc6e418`), subtracts
the pointers and arithmetic-shifts the uint64 bit result by two
(`0xc6e41a/41d`). The comparison is **unsigned64** (`0xc6e421/424`). For a
valid contiguous float vector, index<count loads exactly one binary32 value
at begin+index*4 (`0xc6e426`) and returns it in XMM0; otherwise it loads
`-1.0f`, bits `0xbf800000`, from `0xfa8760` (`0xc6e430`). It writes no object
memory, allocates nothing and has no calls, floating arithmetic or cleanup
paths. Both memory-source MOVSS exits zero XMM0's upper 96 bits; the accepted
raw operations preserve the three additional uint32 zero writes. Its RET
consumes the caller's stack return address.

`original-code`: scaledY subtracts 24 from RSP (`0xa83e70`), reads uint32
`KSETTINGS_YRATIO @0x150b470` into ESI (`0xa83e74`), spills input XMM0's
binary32 at entry-RSP-12 (`0xa83e7a`), and loads its borrowed settings pointer
from `this+0x78` (`0xa83e80`). CALL `0xa83e84` pushes the exact return address
`0xa83e89` at entry-RSP-32. GetFloat returns the property's bits in XMM0.
MULSS `0xa83e89` multiplies **ratio as destination/left operand** by the
spilled offset as right operand. ADD 24 (`0xa83e8f`) restores RSP, then RET
(`0xa83e93`) consumes the outer return address. This function has one direct
dependency, no object writes, no allocation and no source exception handlers.
The private production stack receives both the original spill and CALL slot;
the generated callee and outer RET each consume their own slot.

## Shared field and lifetime map

| Source field | Width / initialization | Writers and readers | Production owner |
|---|---|---|---|
| CGameUI `+0x78` | pointer64 to borrowed CSettings; ctor copies incoming RSI, preserved through RBP, at `0xaa641f` | scaledY reader `0xa83e80`; ctor `CGameUI @0xaa6380` | `FloatPropertyMemory` borrows the caller's evaluated table |
| property file `+0x58/+0x60/+0x68` | begin/end/capacity pointer64; ctor `0xc6e7f0` stores 0 at `0xc6e8c4/0xc6e8cc/0xc6e8d4` | GetFloat reads begin/end; native registration/growth below | borrowed `const float* values` and count in `ui_float_property` |
| vector elements | binary32; no universal element default | GetFloatPropertyIndex stores its **caller-supplied** default at `0xc70549`, advances end at `0xc70553`; SetFloat stores indexed XMM0 at `0xc6e770` | caller-provided values; scale view supplies one evaluated ratio |
| named YRATIO key | uint32 global at `0x150b470`; numeric native ID depends on registration | scaledY read `0xa83e74` | explicit single-property adapter maps evaluated YRATIO to slot 0 |

`original-code`: GetFloatPropertyIndex's capacity-exhausted branch passes the
float-vector owner at `+0x58` to `_M_insert_aux @0x8b2880` on `0xc70605`.
Its growth publishes begin/end/capacity at `0x8b29cb/0x8b29d1/0x8b29d5` relative to
that vector object. Constructor unwind frees nonnull begin at `0xc6ea12`;
the normal property-file destructor frees it at `0xc6f858`. These identify
the external allocation owner. The generated reader does not perform those
operations. No separate reset function or complete registration/lifetime
translation is accepted by this packet; constructor zeroing is the confirmed
initial empty state.

`inferred` adapter boundary: the original CSettings reference and vector stay
alive throughout each call. The port models their reads through a borrowed
view rather than overlaying the original object layout onto a C++ object.
The caller must provide a valid, stable table, representable contiguous bounds
and readable selected elements. Out-of-range indices need no element access.
`ui_scale_offset(offset,ratio)` borrows its local ratio as a singleton for the
duration of the generated call. Slot 0 is an adapter key, **not** a discovered
original numeric YRATIO registration ID. No default YRATIO value is inferred
from the empty constructor or from GetFloat's missing-index fallback.

## Production integration and comparison

[src/ui_screen_scale.cpp](../src/ui_screen_scale.cpp) executes generated
`scaledY -> GetFloat` for `ui_scale_offset`; the public generic
`ui_float_property` executes the complete generated reader. Area/vector
offset helpers use this scaler. [UiLayout::resolve](../src/ui_layout.cpp)
consumes those helpers to produce retained position/size geometry. Its
UnifiedAreaRect size terms now call `ui_scale_offset(parsed[5]-parsed[1],ratio)`
and `ui_scale_offset(parsed[7]-parsed[3],ratio)`, preserving the original
subtraction-before-multiplication order instead of subtracting separately
scaled bounds. Frontend's custom window/layout route, `UiInventory::frame`
and `UiHud::frame` consume the resolved rectangles for presentation/input.

[CeguiMenu::Impl::resize](../src/cegui_menu.cpp) also calls the same generated
scaler for all four position/size offsets on each native CEGUI layout window.
It visits children before parents, obtains pristine stored position/size,
scales the offsets and calls the real CEGUI setPosition/setSize consumers.
Relative components remain intact; rebuilding from pristine geometry avoids
accumulated scaling across resize. This connects the scalar arithmetic to the
native main-menu layout path as well as the custom UiLayout geometry path.
Integration here is established by source calls; no GUI/frame execution is
implied.

The full child-first `convertToScreenScale @0xa83ed0` visitor, CEGUI
notification/lifecycle behavior and viewport-to-property registration remain
the existing bounded adapters. Connecting the scalar to native CEGUI setters
does not close the original visitor or rescale lifecycle. `scaledX @0xa83ea0`
is not generated or newly wired by this packet. Its previous bounded arithmetic
implementation and optional native calibration are separate evidence.

`original-code` comparison: [tests/compare_ui_scale_lift.py](../tests/compare_ui_scale_lift.py)
against unchanged whole bodies and the real production probe reports **3357
cases: 2777 scaling, 580 property reads, zero raw-bit mismatches**, recorded in
ignored `build-cegui/ui-scale-lift-native.json`. Both complete symbol hashes
and every accepted instruction are checked against the pinned ELF. Full
UI/settings/vector buffers and 16-byte element guards are observed unchanged.
Property checks include empty vectors, first/last/out-of-range and high uint32
indices. Scaling checks include signed zero, subnormal boundaries, finite
rounding, infinity and signaling/quiet NaN payloads. Optional native X/Y
calibration uses equal evaluated property values and supplies no new X screen
policy.

The initial multiply implementation had 12 two-NaN payload mismatches. The
accepted scalar-SSE result-bit helper now explicitly preserves the first
operand's NaN payload, quiets signaling NaNs and returns negative indefinite
for infinity*zero; operand order is preserved. These rules are native-result
evidence for MULSS/MULSD, not a claim of universal x87 FLOAT_MULT behavior.
The compiler/runtime gate has 30 checks, including separate scalar-SSE
calibration. Fast-math is rejected.

## Completion boundary

GetFloat is **full** for its complete load/range/fallback function contract
with the stated valid borrowed-owner preconditions. Its generic reader and
generated scaledY caller consume that contract in production. Upstream
registration, mutation callbacks and settings allocation are distinct owning
functions. GetFloat itself performs no floating arithmetic.

scaledY remains **partial**: complete source instructions and result bits are
translated, but original floating environment/MXCSR rounding, DAZ/FTZ,
exception flags and traps are not modeled or compared. The helper explicitly
quieting a NaN does not prove the original instruction's invalid-operation
flag effect. The source settings registry and complete CEGUI visitor/lifecycle
also remain outside this accepted production boundary. No original game,
GUI input, screenshots, frame parity or performance measurement was run.
