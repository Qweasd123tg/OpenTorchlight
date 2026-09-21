# Recovery-method pilots, 2026-09-19

Three bounded experiments following the review of recent code-first work.
These are checks of the recovery method, not a new claim of game completion.
All use ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`;
original binary/resources remain external read-only inputs.

| Work type | Experiment | Useful result / boundary |
|---|---|---|
| Numeric game code | [rollAttack skill profile](skill-weapon-oracle.md) | Existing native oracle exposed 1216/1478 failures; corrected four arithmetic mistakes. Expanded suite: 2078 cases, including RNG. Not caller/HP parity. |
| Stateful event code | [startSkill / triggerEvent](skill-event-native-trace.md) | 15 bounded native traces plus a resource audit. START and TRIGGER must be separate. startEvent is an explicit sink, not a scene implementation. |
| Recognized library code | [lodepng source candidate](lodepng-source-pilot.md) | Two leaf functions compared with pinned upstream: 260 read32 and 83 cold+warm CRC cases. Not whole-library identification or port replacement. |

## What changes in the work process

1. Keep the original function/family as the accounting unit, with its full
   branch/call/field map. An executable slice is a **partial boundary**, not a
   shortcut to declaring the whole function recovered.
2. Before implementation, select the smallest external oracle: resources for
   data, pinned upstream for recognized library code, original instructions
   for arithmetic, short original traces for order/state. Reuse existing
   harnesses before creating new infrastructure.
3. For numerical work, preserve a failing original-versus-port input before
   fixing it. Compare exact values and RNG/state, not only broad invariants.
   The old skill unit test actually asserted the wrong zero-percent behavior.
4. For lifecycle work, annotate every stub and manually supplied value. A
   synthetic callback chain does not prove resource dispatch or application
   wiring. Count a runtime as wired only when a production caller consumes it.
5. Source matching is candidate discovery followed by a proof boundary.
   Symbol/API overlap alone cannot establish a library version. BSim is
   optional for uncertain candidates; local H2 needs no PostgreSQL server
   ([official documentation](https://ghidra.re/ghidra_docs/GhidraClass/BSim/BSimTutorial_Intro.html)).
6. Use helpers for bounded search/source-package preparation; keep ABI,
   arithmetic interpretation, proof boundaries and integration under primary
   review. This tranche used one Luna helper for the library pilot.

## Acceptance and costs

The skill arithmetic suite takes roughly 0.3 seconds locally, the event trace
roughly 0.2 seconds, excluding build and tool startup variability. The existing
12088 allocation/MAGIC/defense/ordinary comparisons remain a regression gate.
The library pilot compiles pinned source in a temporary directory and records
its own elapsed time. These are test timings, **not** measured total engineer
time or token savings; no percentage speedup is claimed.

All three tests use the CTest `reference` group, so the existing
`tools/check.sh` runs them; the library test requires an explicit external
source-directory cache setting. No new service or toolchain installation is
needed for these pilots.

Validation: `tools/check.sh --core --reference <ELF> --game-dir <game>
--build-dir build-verification --reference-python /usr/bin/python3.14` passed
**80 core + 20 reference** CTest cases, zero failures/skips (with the optional
lodepng cache setting enabled). Report:
`build-verification/recovery-pilots-check.json`. The synthetic skill
composition also passed **96 assertions** with the real pak; it now has an
explicit assets test, `original_skill_event_resource_composition`, instead of
depending on an ambient environment variable to exercise that branch.

`research/function-transfer.json` now separates the ordinary rollAttack
production caller from the unwired skill helper. The skill event group is
`partial`, not `implemented`; native traces do not set port `compared=true`.

## Follow-up production tranche

The user authorized continuing implementation and removal of obsolete helpers.
[Production dispatch](skill-production-dispatch.md) now connects the distinct
resource scenes to authenticated HIT, application missiles and request-driven
HP delivery. Six native missile-hook probes corrected the initial post order;
48 additional left-hand arithmetic cases bring the numeric suite to 2126.
The above 80+20 report and 96-assertion synthetic composition describe the
earlier pilot, not current integration. The parallel rung parser and synthetic
START=TRIGGER fixture were removed. Full SEEKING parity remains open.
