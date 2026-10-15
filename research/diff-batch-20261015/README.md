# Small DIFF recovery, 2026-10-15

The canonical check passed: **906 headless tests, zero failures** with
comparison inputs that remained stable throughout the check. Acceptance is **3082 / 5,247 game addresses**:
2359 MATCH and 723 BEHAVIORAL. All 3062 previously accepted
addresses and every previous strong MATCH are preserved.

This batch accepts **20 additional original addresses**: 15 exact
MATCH and 5 fresh paired behavioral comparisons, covering 1571
original bytes. Compiler helpers and duplicate ABI aliases receive no game credit.

## Corrected behavior

- Ten descriptor input-event handlers now MATCH. DamageShape reads the virtual
  setEnabled slot through a normal method call instead of doing arithmetic on
  the vtable pointer. PathController dispatches enable/disable to setEnabled
  rather than changing visibility. The other handlers use the original dispatch
  and control flow.
- Timeline Pause emits event 37. StopToBeginning uses -0.01 and the playback
  direction flag for its final event. Stop and StopToEnd retain original branch
  behavior. These four methods MATCH.
- SkillParser reloadSkills calls parseSkills on the global singleton rather than
  the incoming receiver; it MATCHes.
- Timeline GetObjectIDInTimelineByIndex restores the original iterator end checks.
  It and the existing Play/Play_Backwards methods pass direct paired tests.
- The unchanged CameraController/Interactive group-name callbacks pass direct
  paired tests. Their normalized instructions already matched; the comparator
  correctly retains DIFF because the linked literal evidence is ambiguous.
  No comparator or data guard was relaxed.

## Targeted comparisons

The three new tests in two fixture files run 184 completed original/replacement call pairs over
five addresses: Play (64), Play_Backwards (32), object lookup (40), and the two
name lookups (24 each). Coverage receipts validate the exact entry pair.

Timeline controls exercise enabled/direction/forward combinations, active and
idle paths, collaborator mutations, event and call order, exact float arguments,
receiver identity, and the complete receiver state. Only the two collaborators
are redirected; the tested entry is real. Object lookup uses real original-layout
pointer-valued map nodes with empty, one-, three-, and seven-key trees; valid,
negative, high and boundary indices; signed 64-bit keys; and unchanged object/node
snapshots. Name lookups cover both index branches, unsigned boundary values,
full returned strings and sentinel state for unused pointer parameters.

## Integration evidence and remaining limits

Each worker used fresh --prepare-only --repair-address packets with the existing
opencode TU ownership. Root revalidated the immutable repair snapshot in each
Stage and compared complete candidates before integrating twelve source TUs.
Only sixteen selected bodies changed; 79 other original explicit
source definitions remain byte-for-byte unchanged. Production headers, method signatures and includes did not change. The hybrid
build tool separately omits the fixture include path for production compilation.

Alias/protection or incomplete preparation blocked several initial candidates.
Path's radius/clear methods need vector fields where the current header declares
TArrayList. Timeline's inner-map lookup needs pointer-valued storage instead of
the current by-value map. Achievement's signed stat comparisons need a reviewed
type correction. These are deferred and receive no acceptance from this batch.

functions.json lists each newly accepted game address, final object digest and
acceptance method; objects.json pins all 285 production objects.
source-preservation.json and validation.json record the preservation and current
comparison evidence. The original ELF SHA-256 remains
91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.

This validates addressed behavior and the headless hybrid. Windowed gameplay
and a standalone complete game were not evaluated.

## Destructor fixture regression

The first full check found one incomplete deleting-destructor comparison in
the existing CombineMenu fixture. Both original and replacement tail-call
Ogre::NedAllocImpl::deallocBytes, but the fixture redirected only global delete.
Its fake receiver resides on the stack; passing it to the real Ogre allocator
is invalid. A focused build reproduced the failure. The fixture now redirects
the actual Ogre deallocator as well as global delete, and verifies that the menu
is released exactly once for normal deleting-destructor calls and zero times
for ordinary destructor calls. The tested destructor entries remain real.

After the fix, both destructor modes complete 384 original/replacement pairs
each, and all 18 expected exception unwinds compare successfully. The final full
check uses the corrected fixture. This repairs an existing test and adds no new
accepted game address.

## Measured workflow cost

The focused build plus production cache-key alignment reduced this measured
preparation from 58.56 to 34.81 seconds (40.6%). It builds 288 rather than 679 TU
passes while retaining every production TU. All 285 production assembly digests
are unchanged. Production keeps fresh preprocessing and include-shadow checks.
The existing build/cache/identity test suites pass all 61 tests.

On this six-physical-core host, an ABBA run of the same twelve fixtures took
18.97 seconds on average with four selftest processes and 15.24 with six (19.7%
less wall time). All four runs passed and used identical blob/loader bytes.
The shared selftest pool is now six; the compiler pool remains two. These are
local host settings. This is a bounded throughput benchmark, not a full-suite
A/B speed claim. The canonical full selftest took 1136.18 seconds with six processes.

For focused checks, use the existing hybrid.build(tests=..., out=...) API with
only the named fixture files **and AutoTestRuntime.cpp**, retaining all production
TUs. Final validation remains the complete check.py, here run with
OTL_SELFTEST_JOBS=6 and OTL_SELFTEST_SHARDS=60. Timing-cache fallback changes were
not integrated: the simulation predicted only about 1% benefit.
