# PR110 + PR125 integration, 2026-10-15

The fresh canonical check completed with exit 0: **902 tests, 0 failed**.
All complete input fingerprints before and after the run are identical.
Accepted **2,932 / 5,247 game functions**: 2,214 MATCH and 718 BEHAVIORAL,
covering 1,426,304 / 3,702,188 original bytes.

The batch adds **46 game functions / 38,735 original bytes**: the 44-function
mass3 package from PR110 plus `CQuestUnitData::spawnUnit` (0xd3ded0) and
`getBaseUnitDataGroup` (0xd47de0) from PR125. New acceptance is 1 MATCH and
45 BEHAVIORAL. All 2,886 previously accepted main addresses are freshly
confirmed in the combined build. Former MATCH 0x91cf50 is now BEHAVIORAL,
supported by a fresh executed comparison rather than an instruction-score claim.

## Validation and preservation

- Original ELF and pinned GCC 4.4.7/C++98; 281 production TUs.
- 60 headless shards, four selftest workers, two compiler slots. Selftest wall
  time was 1,395.35 seconds. This is a measurement of this run, not a controlled
  performance comparison with the earlier integration attempt.
- 88 tool unit tests passed; `git diff --check` passed.
- All pre-existing emitted definitions remain. Every new noncompiler definition
  has MATCH or fresh address-specific comparison evidence.
- All former MATCH addresses remain accepted. Existing DIFFs in changed objects
  have fresh executed evidence; other existing objects remain byte-identical.
- All 275 unaffected object TUs are byte-identical to a fresh main comparison.
  Only Console, Inventory, QuestUnitData, character, monster and player changed.
- 358 explicit old source definitions in those six TUs are textually unchanged.
- All 3,625 prior hooks remain; the 49 new hooks comprise 46 game bodies and
  three emitted template bodies (one MATCH, two explicitly compared).
- The original main baseline was compared statically; no separate successful
  full behavioral baseline run is claimed.

The particle fixture correction retained from the previous candidate uses
trigger offset 0x18 for the particle, rather than scene-node offset 0x38, and
requires real branch calls. Missing required callbacks invalidate the capture.

The resolver/spawn fixture executes the two real target entries: 344 resolver
and 178 spawn completed pairs. Its 29 unwind lanes are checked separately and
excluded from completed-call credit. Original dependencies and bounded world
creation are used; makeChampion covers the already-champion path, and NPC
evaluation uses a null player. No new dependency/world-lifecycle acceptance is
inferred from these two target receipts.

## Input identity

The 2026-10-14 candidate's 901 passing tests ended in an input-identity failure.
That historical cause remains unknown. None of its PASS results were rebound to
new inputs. Acceptance here comes from this new, complete execution with stable
inputs, fresh full-object bindings and preservation checks.

The check now retains its initial file/context manifest before comparison. On
an identity mismatch it saves both manifests and names changed files/context
keys, while still returning 2 without publishing acceptance. The legacy digest
encoding and acceptance guard are unchanged.

See `validation.json`, `functions.json`, `objects.json`, preservation reports and
`selftest.log` for this run. Original ELF/resources and compiled binaries are
external read-only inputs and are not published.

PR100 remains MERGE HOLD because the old Graph C2 differences are unexplained.
This headless validation does not establish windowed gameplay or a standalone
game; neither was run or claimed.
