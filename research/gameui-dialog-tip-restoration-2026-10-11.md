# GameUI dialog and tip restoration: 2026-10-11

Restores three original functions in gameui.cpp (731 original bytes):

- 0xa8ec90: openModalDialog, 193 bytes, exact MATCH.
- 0xa8e140: forceInteractiveDialog, 398 bytes, behaviorally compared.
- 0xa8f450: queueTip, 140 bytes, exact MATCH.

Original ELF SHA256:
91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
Baseline: f457d23f953048ddf7cc23470a8e985b35ccab88.

Modal delivery preserves by-value entry string lifetime, mutable contents
reference, null callbacks, helper order and menu-pointer reloads. Interactive
handling preserves real RTTI target selection, the deliberately discarded quest
lookup result, the dialog sound branch, and player-state/pathing order. Tip
queueing preserves signed flag indexing, exact settings == 1, duplicates and
real vector growth. Quest.h remains unchanged.

## Verification

- One unchanged full Stage.validate gate passed all 624 tests.
- 2,692 accepted = 2,159 MATCH + 533 behavioral: exactly the previous 2,689 plus
  these three addresses. Every previous acceptance and MATCH is preserved.
- 1,025 completed new-target original/candidate comparisons, no differences or
  incomplete cases; 299 separately witnessed expected unwinds.
- Four new registrations include a supplemental flattened-retirement caller
  modal-unwind/retry regression. Existing consumer fixtures remain unchanged.
- The focused 25-test run and restored-positive run passed with identical input
  digest and binary hash. They include existing click, retirement, menu, skill
  and equipment consumer normal/exception regressions.
- Five separately staged semantic mutations were rejected through completed
  mismatches, zero incomplete observations: stale modal pointer, title/open
  reordering, adopting the discarded quest result, falling through the sound
  branch, and accepting any nonzero settings value.
- Actual public-body assembly confirms modal calls survive in both onClick and
  flattened updateIngameUI. A narrowly justified noinline preserves this original
  boundary; new modal/unPause and interactive/closeAll calls are also verified.
- Final input digest:
  b36966e3f1532b85a9b4bbdd2b3956bbed105081e3d4557a1c78ce225417ab36.

## Observed validation resources

Final full gate: 1,051.49 seconds. Headless phase: 767.03 seconds using eight
shards, four workers and four shared selftest slots; compiler slots remain two.
All eight shards exited successfully and timing intervals confirm at most four
concurrent shard processes. Per-shard timeout remained 1,800 seconds.

The preceding 620-test layout gate used two shards/two workers and its headless
phase took 1,463.63 seconds. This is an observed comparison across different
624/620-test inventories and source revisions, not a controlled benchmark.

One-second same-invocation samples observed peak aggregate descendant RSS of
1,127,148 KiB, including the driver and double-counting shared mappings. Samples
can miss short peaks. Largest sampled game-process RSS was 88,084 KiB; maximum
child high-water RSS was 476,876 KiB and included compiler processes. Exposed CPU
affinity included nine CPUs; external CPU/memory quotas were not verifiable.
These measurements do not establish a safe eight-worker maximum.

No acceptance tools, guards or compiler configuration were changed. Vector
allocation failure was not injected; real growth and GetInt exception behavior
were checked. Original binary/resources are excluded. Headless validation does
not establish live-game playability; no live window was launched.
