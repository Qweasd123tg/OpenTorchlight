# Descriptor family batch, 2026-10-15

Baseline `6bb574a04b25d2b6f31047640db73c67b0bd01be`: 3269/5247 accepted.
The tranche covers 124 previously unaccepted game addresses: 71 new source
definitions and behavioral acceptance of 53 existing descriptor constructors.
The mandatory final `check.py` passes: 1143 tests, no failures, 60 shards,
1298.40s headless time and 75.08s hybrid build time. Accepted coverage is now
3393/5247: 2435 MATCH + 958 BEHAVIORAL. All 3269 prior accepted addresses remain;
all 958 behavioral receipts bind to current final object/input identities.
See `validation.json`, `functions.json` and `selftest-summary.txt`.

`DescriptorController.cpp` now contains 60 naturally emitted static factories,
the ordered factory registration and controller construction. Eight other
controller methods remain absent. Factory allocation/constructor arguments,
metadata assignments, return identity, untouched bytes and exception cleanup
are compared with the original. All 60 registration entries retain their order.
Ambiguous linked wide literals still produce DIFF; comparison policy is unchanged.

Nine missing descriptor constructors restore the original property and logic
registrations. Positionable and Shape include every conditional branch after
the first ASM return; the old descriptor generator's first-return truncation
was not used for these bodies. UnitTrigger's helper is static, as the original
RDI argument and callers show; its existing strong MATCH remains unchanged.

Six descriptor headers had unused opaque derived tails copied from unrelated
object access. Removing 107 tail declarations restores each complete size to
368 bytes, as the original factory allocations require. Inherited fields and
virtual order remain unchanged. All 57 factory class sizes, seven affected
vtable layouts, the 96-byte controller and 376-byte LayoutDescriptor are checked
with GCC 4.4.7. The two descriptor string assignments use existing typed fields.

The complete constructor fixture compares 62 original/replacement targets with
2400 normal completed pairs. It covers all 32/8 Positionable/Shape option
combinations, flags at every registration call, ordered full strings and callback
identity, legal growing ParentFilters and final object state. Only known exact
original/linked callback symbol pairs are normalized; unknown pointers remain
unchanged. A separate negative control checks all 810 identity pairs.

Focused results on every production TU:

- Factory/registry plus initial constructor group: 115 tests, no failures;
  build 45.81s, headless 2.51s. The 120 expected exception unwinds are separate
  tests and do not count as normal comparison coverage.
- Final constructor group: 63 tests, 62 addresses, 2400 normal pairs, no
  differences or incomplete calls; build 92.72s, headless 3.44s.
- Deliberately wrong factory constructor text and an equipmentUsed early return
  are both rejected by their respective fixtures.
- All 3283 prior strong MATCH addresses retain their code and status; static
  comparison now has 3292 strong MATCH, including 857 compiler helpers.

The suppressed CombineMenu matrix now uses 24 cases instead of 44,544, asserting
one layout update, no inventory/drop callbacks and unchanged inventory-map state.
All six locations remain represented. The two unsuppressed matrices retain
44,544 cases each. The reduced fixture takes 0.056s in the focused sample;
`test-cost.json` separates that result from full-suite timing.

`bulk_autotest.py` adds one diagnostic command for all written unaccepted game
DIFF, separate from admission. The initial 207-address sweep generated 191
probes and compiled 135 in one hybrid: 39 passed probes, 93 incomplete, three
different, 56 compile errors and 16 unsupported. None of those generic passes
is automatically accepted: zeroed maps and invalid object lifetimes can miss
real branches. Per-target results and frozen generated inputs remain available.

Preparation now resolves unique global callback typedefs and equivalent inner
const spelling. Scoped/conflicting aliases stay blocked. Review reproduced a
false match when a class typedef shadowed a global callback; conservative scoped
typedef exclusion and two regressions close it. Context, alias, diagnostic, header and pipeline
tool tests total 250 PASS (158 + 10 + 4 + 13 + 65).

The requested universal-modder review found reusable reverse-engineering and
oracle practices, including batch Ghidra scripting and deliberate broken-build
checks. Its CLI has no native C++ reconstruction engine or Torchlight-specific
files. No plugin, MCP service or cloud asset workflow was installed. Sources and
the inspected repository tree are in `universal-modder-review.json`.
Its Kenshi case study also describes a headless host constructing real OGRE
managers and scene objects. That is a concrete candidate for richer legal test
objects here; the reported OGRE 2/MSVC layouts cannot be reused for OGRE 1.6.5/GCC.
This idea has not been implemented or validated in Torchlight.

The next generator screen yields 81 unverified proposals, representing 51 source
definitions with a 101-address game ABI closure plus 22 thunks. These are analysis
only; some closure bodies remain unsupported. See `next-capacity.json`.

A separate symbolic screen proposes reducing each remaining unsuppressed
CombineMenu matrix from 44,544 to 1364 cases by removing unread callback-reply
bits. All six locations and eight mutation values remain. This is only a
proposal: neither implementation, fresh differential evidence nor timing exists
yet. Required defect controls and limits are in `next-test-cost.json`.

The user also found `YaPeL/torchlight-recomp`. Its actual build and hooks confirm
a substantial Xbox 360 static recompilation with a modern host OGRE backend,
published beta packages and author gameplay reports. It preserves PPC registers,
guest memory and address-based calls rather than original PC C++98 TU/classes.
The practical portable-game goal overlaps substantially, so this alternative
should inform the next tranche decision. No executable was run; beta completeness
and Android readiness were not independently established. See
`torchlight-recomp-review.json` for pinned source evidence and limitations.

Windowed gameplay and standalone reconstructed-game linking remain unverified.
