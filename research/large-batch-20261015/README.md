# Grouped decomp acceptance, 2026-10-15

Baseline: `342e732823d272800760f014e6d80736ec45d438`. The original ELF and pinned GCC 4.4.7
remain unchanged. This tranche accepts **72 game addresses: 40 MATCH and
32 BEHAVIORAL**, bringing the total from **3082 to 3154/5247**
(2399 MATCH, 755 BEHAVIORAL).
The new addresses cover 8483 original bytes.

The screened cohort contained 131 candidates: the previous 39 repair candidates
and 92 bounded new-definition candidates grouped by original TU. Seventy explicit
targets passed; two original virtual-adjustment thunks matched as generated
consequences. The remaining 61 screened candidates receive no acceptance credit.
Eight reserve frontier entries were not part of this tranche. ABI/signature
conflicts, opaque layouts, unavailable typed dependencies and unresolved behavior
remain deferred; examples include UnitSpawner dependencies, DynamicPropertyFile
return types, room metadata and ResourceManager::ISA(string,string).

## Changes

The 47 new source definitions restore descriptor lookups and scene operations,
logic-link removal, collision/light forwarding, PuzzleRandomizer state handling,
particle-emitter parent lookup, room highlight/animation queries, DataGroup
container operations and ResourceManager forwarding. Nine existing bodies were
repaired; fourteen unchanged bodies gained paired behavioral evidence.

`CPOV::UpdateFlyingTo` now preserves the original unordered-comparison behavior:
when one component is NaN, finite neighboring components still interpolate.
The old implementation fails seed 22 while both child invocations complete;
the repaired implementation passes exact captures. The full UNIT_GUID literal
used by ResourceManager::createUnit was verified from the original ELF including
its UTF-32 terminator. No comparison normalization or acceptance guard changed.

New includes are placed after the prior include blocks in MonsterDescriptor and
UnitTriggerDescriptor to preserve the numbering and code of existing compiler
destructors. All 3194 prior strong MATCH addresses still match, and all 3082 prior
accepted game addresses remain accepted. The three unaccepted DIFF compiler
initializers affected by added includes remain outside game-function totals;
their changes were isolated against a baseline with the same includes.

## Validation

Every integrated full-TU candidate came from a current owner-checked prepare-only
packet. Root integration independently verified checkpoint/input identity, packet
hashes, complete prior definitions and narrow objdiff results. No header or
tool implementation was changed.

- Combined focused build: all 289 production TUs, ten new fixture
  files plus AutoTestRuntime, 31 tests, 2016 completed original/replacement pairs,
  zero differences and zero incomplete observations across all 32 BEHAVIORAL targets.
- Canonical `python3 tools/decomp/check.py`: **937 tests, zero failures**;
  the 60-shard run executed every fixture. Full selftest: 1075.78 seconds.
- All behavioral receipts bind current object and common input digests, and the
  type snapshot is current. The MATCH list was refreshed without game execution
  before the final type export and full gate. An earlier preflight was interrupted
  before selftests to establish this ordering; it supplied no acceptance evidence.

These are headless pre-main comparisons, not a claim of playable windowed gameplay.

## Acceptance cadence

`decomp/README.md` now groups roughly 100–200 candidates into one integration.
During recovery, compare changed TUs and run address-specific fixtures; run the
full suite after integration before commit/PR. Reuse the preceding successful
baseline when HEAD and its inputs are unchanged. Shared ABI/header/runtime changes
can justify an earlier broad gate. Candidate count never replaces evidence.

The read-only CombineMenu case audit found a conservative projection that could
reduce its three return fixtures from 133632 to 66048 pairs. This projection was
**not implemented or runtime-validated** and is not a measured full-suite speedup.
The current tranche reduces repeated full runs through batching; it does not
change canonical fixture coverage, timeouts, comparator rules or fingerprint guards.
