# PR110 integration candidate, 2026-10-14

**MERGE HOLD.** The full canonical check ran all 901 headless tests successfully,
but exited 2 because its input fingerprint changed during execution. No fresh
accepted count or behavioral acceptance receipts are published from that run.
The fingerprint failure must be diagnosed and the canonical gate must pass
before this candidate is merged.

Integrated only commit `f724853a91c1f475433bcc27c9b3dc1d2ba75e25` (44 game
functions) onto main `884fc68b59760bef0e63f3201a46514968990207`, preserving the
newer quest work and class layouts. Character uses main's existing display-name
field; Level retains the quest property-node arrays and adds the mass3 vectors.
All 343 pre-existing definitions in the five modified source TUs are unchanged.

Fixed the particle fixture: its particle pointer belongs at trigger offset
0x18; the old test put it at 0x38 (the scene node) and skipped particle actions.
The fixture now requires observed Start, deferred Stop with reposition, and both
looping values including Stop on the same particle after looping(false). Missing
required calls invalidate the capture. Production setVisible is unchanged.

Validation: 901 tests / 0 failed across 60 shards with four local selftest slots;
17 hybrid tool unit tests passed; git diff --check passed. See selftest.log and
validation.json for the completed run and the final failing input guard. Local
compiler capacity remains two. The full main behavioral baseline was interrupted
and is not represented as a passing baseline.

PR100 is separate and remains held: an unchanged green retry does not explain
the earlier Graph C2 differences at seeds 26, 47 and 54.

These are headless differential tests; no windowed gameplay was requested or run.
