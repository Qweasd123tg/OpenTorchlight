# Small typed recovery batch, 2026-10-15

Baseline `fddb27aee8703178c4375a33048b588801b0282e`: **3241 → 3269/5247** accepted,
with **2432 MATCH + 837 BEHAVIORAL**.
This batch adds **28 original addresses: 6 MATCH + 22 behavioral** across ten TUs.
Every prior accepted address remains accepted; all 3277 prior strong matches
retain their code and metadata. Unchanged definitions remain byte-identical prefixes.

The tranche restores linked timeline point lookup, values and removal; dynamic
integer/float setters and their callbacks; property-list lookup; sound release and
SDK channel control; room parent identity; Steam local updates; achievement type,
completion and construction; editor registration and selection; game speed and
wide-string prefix comparison. See `functions.json` for the final object-bound evidence.

The timeline head is now `TLinkedListNode<CTimelinePoint*>*`, matching the original
point/next/previous node fields. Its pointer stays eight bytes at offset 0x40.
`DynamicPropertyFile::SetInt/SetFloat` and `DescriptorProp::cloneValue` return bool,
as their explicit 0/1 ASM paths show; cloneValue itself remains deferred because
it needs a protected descriptor-owned name. Five imported FMOD Channel methods
are declared using the existing SDK result convention and original parameter types.
All five affected class sizes, bases and member offsets/sizes remain unchanged.

Both preparation scanners now recognize the existing `class __attribute__((packed))`
syntax. The owner scanner previously replaced TimelineProperty's hand-written header
with a generated opaque draft; the one-hop scanner also lost its member declarations.
The regressions verify retained source bytes and exact overload rejection.
**236 tooling tests pass** (13 header, 65 pipeline, 158 context).

Independent review found signed overflow in the new stopSound counter decrement.
Unsigned subtraction now preserves the original 32-bit wrap, with twelve additional
INT_MIN cases. The later review found no further P1/P2 issues in the new bodies/fixtures.
The only redirected calls in comparisons are collaborators; actual original and
replacement targets execute normally.

- Focused: all 290 production TUs, **18 tests**, **26 addresses**,
  **1914 normal completed pairs**, no differences or incomplete calls.
  Build 42.32s; self-test 1.61s.
- Mandatory full `python3 tools/decomp/check.py`: **1018 tests / 0 failures**,
  60 shards, **1227.67s**. The previous 1000-test run took 1195.50s.
  These different inventories and single samples do not establish a controlled speedup.
  Compiler/self-test capacities remain 2/6.
- Every accepted behavioral address has a current object digest and the same current
  input digest; exported types are current. The minimum remains 20 normal pairs.

The screening considered 113 game addresses across 15 TUs, plus nine BinaryStyle
addresses. Final packets admitted 48 of the 113 for inspection; 28 were implemented.
The other twenty still need typed fields/dependencies or would disturb a prior MATCH.
The 65 packet blockers and nine BinaryStyle declaration blockers receive no credit.
In particular Steam getters/listener dispatch remain deferred because even natural
additional definitions changed the accepted statModified register allocation.

ENOSPC interrupted preparation. Only generated `.o`/`.so` outputs from old temporary
builds and reproducible `types.json` copies in 336 old isolated attempts were removed,
freeing about 14 GiB. Authored candidates, headers, prompts, checkpoints, receipts,
logs and current attempts were retained. Interrupted packages were prepared again.

This is headless pre-main evidence. Windowed gameplay remains unverified.

The next throughput opportunity is recorded in `test-cost-followup.json`: the
suppressed CombineMenu fixture currently repeats 44,544 normal pairs. ASM still
requires updateLayout; a proposed 24-pair subset keeps that callback and state
observations. This is read-only analysis, not a measured or implemented speedup.
A separate ignored next-frontier screen found 129 other addresses, of which only
34 have an existing typed path for their first preflight; these are not accepted.
