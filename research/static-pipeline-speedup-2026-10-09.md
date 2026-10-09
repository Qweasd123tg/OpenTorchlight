# Bounded original-disassembly reuse and streaming layout index

Source package: user-supplied OpenTorchlight-reverse-pipeline-speedup-2026-10-09(1).zip,
SHA-256 fe1067c0f1dd7df431ea9a2db4799a23d37c45c513b15ff8d635b0b139ebe0cd.
Its scripts and tests were explicitly authorized and run with inherited seccomp
socket/connect/send/receive denial and closed inherited descriptors.

## Independent reproduction on the package's exact pass8 tree

Verified all 1231 baseline and 1235 optimized input hashes. All 345 supplied
static tests passed. The pinned GCC and original ELF were unchanged.

| Static check | Baseline | Optimized | Reduction |
|---|---:|---:|---:|
| Cold project-cache wall time | 149.748 s | 100.507 s | 32.88% |
| Warm wall time, median of three | 31.869 s | 19.239 s | 39.63% |
| Cold CPU, parent plus children | 236.525 s | 172.478 s | 27.08% |
| Warm CPU, median of three | 44.189 s | 28.463 s | 35.59% |
| Cold objdump calls | 5050 | 579 | |
| Warm objdump calls | 802 | 243 | |

All eight locally produced full reports, including full object identities,
are exactly equal. The cold pair was measured once; OS page cache was not
purged. Warm runs alternated baseline/optimized order. These are static-path
measurements, not end-to-end reverse-engineering or runtime-test speedups.

The supplied reference report is NOT exactly reproduced: FileSystem.cpp has
a different full-object digest and two Ogre any_cast code fingerprints already
in the local unoptimized baseline. No other unit differs. The supplied strict
checker correctly rejected that cross-environment comparison. Do not count it
as a successful reference reproduction. All local before/after reports agree,
and these two fingerprints and all object digests remain unchanged by the
optimization. The SDK exception macro embeds __FILE__; environment-dependent
header paths are a possible explanation, not independently proven from the
supplied fingerprints alone.

## Narrow current-tree port

Ported only original instruction reuse, resolver indexing, original cleanup-EH
cache persistence, and streaming layout load/store. Existing literal-flow
acceptance behavior, original compiler flags, C++ files, SDKs and atime-v2 fix
are unchanged. PCH and the supplied atime-v1 variant are not included.

TU batching remains opt-in with OTL_ORIGINAL_DISASM=tu; default function mode
uses exact function ranges. Batching requires a bounded range, one section,
ordered decoded addresses and exact endpoints, otherwise exact decoding is
used. Both caches are bounded and return independent row copies.

Index initialization publishes its ready marker only after construction
succeeds. Added tests cover group eviction, returned batch-row mutation,
decoder failure/retry and failed initialization/retry. The new module is part
of the normalized-cache key and smallmatch verification provenance.

The final Python suite runs 624 tests: 623 pass, one pre-existing skip.
Static comparison units and all their object/row/metadata fields exactly match
the unmodified current tree: 1270 game MATCH. The current-tree port separately
reproduces 4260 original normalizations and 589 original cleanup-EH signatures
using the unchanged old implementation, including unsupported results.

Old runtime receipts correctly invalidate when tools change. A no-game run
therefore cannot by itself preserve the 77 behavioral acceptances. Fresh full
headless checks must complete and restore the exact prior 1347-address accepted
set before this change is published. No acceptance checks are weakened.

## Completed full gates

Both isolated candidate and independently checked integrated root passed all
202 headless tests. The exact prior accepted set is preserved: 1347/5247
functions and 983179 original bytes, comprising 1270 MATCH and 77 behavioral
acceptances. No gameplay function was added by this optimization. All final
unit reports remain exactly equal to the unmodified current-tree baseline.

The complete layout index is byte-identical across baseline, optimized and
current-port trees: 92845045 bytes, SHA-256
c0db9429456d2c2d4f82015eec7cd265b01c0ebf21a8c257982eea2fe0fa78d3.
Memory improvements reported by the supplier were not remeasured here.

Final independent measurements and report hashes accompany this note in
static-pipeline-speedup-measurements-2026-10-09.json. Use the usual full
check.py gate before future publication; batching does not replace it.
