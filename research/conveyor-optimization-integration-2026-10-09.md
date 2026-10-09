# Conveyor optimizer: selective integration

Source: user-supplied `OpenTorchlight-conveyor-optimization-2026-10-09.zip`,
Google Drive file `1WYRDpf_rc4R3rmjspZiG9wkEienQ9Pdq`.
Integration baseline: `138472a77dbef96b49f36c9ad848d52ab4691317`.

The package targets full historical smallmatch pass7, not this branch.
All supplied SHA-256 entries verified. Its clean reproduction succeeded in
an independent kit copy, under a syscall filter denying network sockets and
network sends; 153 smallmatch tests and 35 static comparator tests passed.
The supplied queue and packets reproduced exactly. All 67 historical C++
candidates and 31 headers remained byte-identical. This reproduction does not
re-establish the historical MATCH claims.

## Integrated scope

- Immutable ABI definition index in `llm_definitions.py`.
- Index use and per-generator source parsing cache in `smallmatch.py` and
  `smallmatch_families.py`; indexed closure in `smallmatch_verify.py`.
- Read-only queue/packet planner, archived-trace benchmark, optional trial-cache
  helper and its tests.

No original C++ bodies, headers, comparator, compiler flags, ownership or
acceptance rules changed. The planner is navigation, not acceptance, and does
not replace `llm_loop.py --prepare-only`.

The absent historical mass/pass6/pass7/variants drivers were not installed.
The divergent current recovery driver was preserved. The optional TrialMemo
helper therefore is not enabled by the current workflow. It must not be
advertised as a measured improvement to real compilation.

## Independent local measurements

Historical pass7 metadata and archived reports, three ABI repetitions:
- ABI group lookup median: 4.5924 s to 0.05746 s, 79.92x.
- Archived verdict lookup: 5.0512 s to 0.13849 s, 36.47x.
- Complete generator: 4.1499 s to 1.7395 s, 2.386x.
- All 3630 ABI groups/verdicts and all 86 hypotheses/rejection reasons agreed.
- Archived trial replay: 95 requests, 86 evaluations, 9 reused results.

These are component timings, not an end-to-end decompilation speedup.
No new recovered functions or MATCH are claimed.

## Current-branch validation

65 smallmatch tests passed in a fresh archive of the integration baseline.
The complete Python suite with configured pinned-toolchain environment ran
585 tests successfully, with one skip. An initial run without the environment
was invalid because it could not locate the toolchain; it is not counted as a
pass. Full `tools/decomp/check.py` then passed using pinned GCC 4.4.7 and the
current strict comparator: all 192 hybrid tests passed. Acceptance remained
1323/5247 functions (954432 bytes), including 68 behavioral acceptances.
No original accepted function was lost. This full run also inherited the
network-denying syscall filter.
