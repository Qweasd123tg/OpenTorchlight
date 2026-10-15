# Grouped decomp acceptance, 2026-10-15, follow-up

Baseline: `8d9f0ee6a2bf442295962f0d195795bec696b7af`. This tranche accepts
**84 game addresses: 26 MATCH and 58 BEHAVIORAL**, moving
**3154 to 3238/5247** (2425 MATCH,
813 BEHAVIORAL), covering 15484 additional original bytes.
The screened cohort contains 149 explicit candidates. Eighty-three pass; one
standard-library destructor clone matches as a generated consequence. The other
66 receive no acceptance credit, including two implemented methods whose passing
12/15-pair matrices fall below the unchanged 20-pair minimum. `deferred.json` records their concrete blockers.

## Changes

Seventy new definitions implement descriptor scene traversal, timeline serialization,
editor image activation/position/visibility, original string conversions and formatting,
filesystem queries, skill lookup/cooldown/control, typed DataGroup additions,
resource-list queries/cleanup, binary integer reading and room-piece prefix lookup.
Nine existing bodies are repaired and six unchanged bodies gain paired evidence.
Of the 70 new definitions, 68 are accepted here. CDataValue::GetValueTypeAsString
and FILESYSTEM::GetApplicationPath are implemented and their 15/12 normal pairs
pass, but the canonical minimum is 20; both remain unaccepted. No minimum or
counting rule is lowered. A future tranche can expand their matrices before its
full gate.

Achievement methods now preserve signed enum bounds, the integer bits used by
forceComplete, floating operand order and collaborator-sensitive rereads. The old
forceComplete body fails seed 4 with both child calls completed; the repaired set
passes 1344 exact original/replacement pairs. DescriptorManager update and postprocess
use the existing typed vector accessor while retaining live begin/end reloads.

The existing DataGroupContainers fixture no longer counts caught constructor
exceptions as normal completed entry calls. Throwing inputs are excluded from
normal coverage in this tranche; no exception acceptance is claimed. All other
ordinary branch inputs remain, including list allocation/growth and capacity fallback.
The same accounting rule applies to every new fixture.

## Preservation and validation

All 3250 preceding strong MATCH addresses retain their code and metadata;
all 3154 preceding accepted game addresses remain accepted. All unassigned
explicit bodies remain byte-identical. New definitions change temporary-register
allocation in four old DataGroup BEHAVIORAL methods; independent normalized assembly
comparison shows only register changes and they pass 128 fresh normal pairs.
Three already-unaccepted compiler DIFF helpers change because of provided includes;
independent include-only builds reproduce their exact final code/metadata. They
receive no acceptance credit. No header, comparator, runtime or fingerprint guard
is changed. Source order and include placement preserve previous strong matches.

Every integrated TU uses a fresh owner-checked prepare-only packet. Root independently
checks immutable tree/input snapshots, packet/checkpoint hashes, prior bodies and
objdiff rows. After integration, the MATCH list is refreshed without game execution,
then types are exported, followed by the combined focused and canonical full gates.

- Combined focused: all 290 production TUs, 19 fixture files plus
  AutoTestRuntime; 68 tests / 6904 normal completed pairs / no differences or incomplete
  observations. This includes 128 explicit revalidation pairs, other reused tests,
  and 27 passing pairs for the two methods below the acceptance minimum.
  Focused build: 39.04 seconds.
- Canonical `python3 tools/decomp/check.py`: **999 tests, zero failures**,
  all 60 shards validated. Full selftest: 1173.46 seconds.
- All current behavioral receipts bind current object digests and one common input
  digest; types are current. The original ELF and GCC 4.4.7 remain pinned.

These are headless pre-main comparisons; windowed gameplay has not been established.

## Confirmed deferred finding

The unchanged canonical SteamStats::statModified at 0xece450 fails a deterministic
paired probe: an empty list grows in memory filled with 0x3c, the original zeroes
both fields of every SStatChange, but the current implicit constructor zeroes only
its value union. Both calls return normally and differ. The new SteamStats slice
is entirely excluded pending a separate typed-header repair; no new acceptance
is claimed for this address.

`SteamStatsPendingProbe.cpp` is diagnostic source outside the canonical test
inventory. Copy it into an ignored prepared attempt's test directory and use a
focused build with all production TUs to reproduce the known failure. It uses
synthetic memory only and calls no Steam service. `deferred-stat-change.json` gives
source/header hashes, case and the observed result.

## Acceptance cadence

The 149-candidate tranche uses per-TU comparisons and focused tests during recovery,
then one full canonical run before commit. The focused all-production build takes
about 39 seconds; this does not imply that the full suite itself became faster.
Compiler/selftest shared capacities remain 2/6, and the full timeout remains 1800s.

Read-only inspection of this run found that the expanded 999-test inventory has no
exact matching timing profile, so scheduling falls back to index order. Reusing
individually identified fixture costs as ordering hints is a possible next
optimization; it must retain all shards and inventory validation. This is an
observed limitation and a proposal, not an implemented or measured speedup.
