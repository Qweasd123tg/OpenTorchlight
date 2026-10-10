# Pipeline efficiency: compiler identity, hybrid metadata, shard scheduling

The seven tooling changes preserve the accepted PR79 game sources, headers and test fixtures. Acceptance remains 2,377 functions: 2,134 MATCH plus 243 behavioral, across 278 translation units and 446 headless tests. No game-function completion is claimed by this tooling change.

## Changes

- Compiler identity scans hash each freshly opened distinct compiler/runtime inode once per scan, preserving ordered cache-key bytes, fresh preprocessing/specs and mutation checks. This is scan-local alias deduplication, not persistent identity memoization. Measured logical reads fall from 39 paths / 25.80 MB to 29 distinct files / 19.40 MB per lookup. Existing cache schemas, flags and capacities are unchanged.
- Hybrid building retains immutable metadata from freshly assembled objects and performs independent rewrite/assembly preparation in the existing bounded worker pool. Hook/import/link reduction and diagnostics remain in source order. Aliased outputs fall back to serial processing. Assembly capture is optional and existing callers retain their behavior.
- Selftest dispatch may enqueue the longest predicted shards first. All 60 original shards, their internal test order, process isolation, exact parser, timeout and 8-worker capacity remain. Results are restored to shard-index order before parsing. Strict completeness checks reject missing/duplicate tests/results. Predictions contain durations only and cannot supply PASS or acceptance evidence.
- Timing hints are bound to the exact ordered inventory, fixture/header content, and compiled fixture/blob content. Missing, corrupt or stale hints fall back to index order. Embedded `__FILE__` paths legitimately prevent ordinary Stage/root hint reuse. Atomic diagnostic sidecars are best-effort and cannot replace a primary failure.
- Monotonic phase wall time and measured process/child CPU are reported separately. Compiler-slot wait is explicitly unmeasured; concurrent wall totals are not labeled CPU.

## Verification

123 targeted union tests and three exact AST merge checks passed. Additional independent alias/lifetime, 60-shard permutation, overflow/corrupt profile and timing-marker controls passed. The hybrid worker rejected eight deliberately broken variants; deterministic concurrency tests passed twenty repeated runs.

Changed tools are validated with the established tools-specific route: two new interpreters load the actual candidate modules, verify their paths/hashes and run full `check.main`. The source-publication `Stage.validate` tools-change guard remains intact. No Stage validation flag or old PASS report was reused.

1. An isolated candidate directory completed the full check and 446 headless tests. All 11,882 static function records, 278 production object digests, acceptance metrics, 298 fresh comparison receipts and 1,889 ordered runtime report rows were preserved. Only numeric test durations were normalized. All 842 cross-path portable artifacts matched the accepted baseline.
2. After exact seven-file adoption, an independent root check completed all 446 tests. All 1,629 same-path assembly, object, hook/import, linker, manifest, blob and loader artifacts were byte-identical to the accepted root baseline. Source/tool/generated-input hashes were stable before and after. Every shard completed exactly once. All comparison receipts bind to the new actual input digest.

The complete Stage/root check JSON reports are identical, SHA-256 `3d39bc0d0cc4d05cdc8568fbb5961f925c6389721dd02ec6bc88fcbbb0d9635c`.

## Measurements and limits

Paired bounded compiler microbenchmarks measured roughly 15–16% lower identity latency and 11–15% lower tiny warm compile latency. A 24-unit rewrite/assembly benchmark reduced ELF parses from 84 to 24 and median phase wall time from 1.235 to 0.647 seconds while preserving all 48 artifacts and metadata. A separate nine-unit complete build preserved all 36 artifacts but showed only a noisy 1.6% median wall difference; it is not evidence of a comparable whole-pipeline improvement.

Fresh full-check observations on this machine:

| Run | Full check wall | Hybrid build wall | Selftest wall | Shared cache |
| --- | ---: | ---: | ---: | --- |
| Isolated candidate, index fallback | 496.83 s | 97.38 s | 369.44 s | 735 hits, 83 misses, 0 fallbacks |
| Root, longest-predicted-first | 460.49 s | 82.69 s | 348.20 s | 818 hits, 0 misses, 0 fallbacks |

These are instrumented observations, not a controlled baseline-versus-new implementation speedup: checkout paths, cache warmth and scheduling differ. Observer hashing overhead is included. Both runs execute every existing test. No aggregate percentage speedup is claimed.

The new phase counters identify remaining serial hook reduction at approximately 56 seconds, dominated by per-function original disassembler processes. That is a separate potential optimization; this change does not alter hook-selection logic or disassembly range semantics. Old build deletion was not part of this change.
