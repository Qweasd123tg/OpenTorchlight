# BaseUnit initialization evidence upgrade, 2026-10-09

CBaseUnit::unitInit(CDataGroup*, bool), original 0x803100, 7229 bytes. The existing production body is unchanged. The strict original context packet and assembly control flow, calls and state stores were reviewed against that body.

Null input returns unchanged. Initialization records data/GUID/type, computes scale with the volatile random stream, updates shadow/collision/pathing flags, conditionally reapplies effects, loads skill settings and animation overrides, reapplies affixes under the original flag/type condition, recalculates effect values and propagates the shared-stash cheat flag.

The original uses unsigned data getters for skill column/row while the existing source uses signed getters. This is not byte identity: both original getter paths perform the same lookup/default-bit handling, and the underlying signed/unsigned getters at 0xc62e60/0xc62e70 are each the identical 32-bit load from +0x18. The body is retained under behavioral acceptance rather than claiming identical callees.

768 completed original/candidate comparisons, zero differences or incomplete observations. The former 192-seed, two-call fixture is expanded to 384 seeds and independent cold/warm cases, including both managers already present. It retains real data, skill, effect, affix and random services and now invokes the exact original/replacement pointers with strict complete-report checks.

Observations include the entire initialized base-unit buffer with narrow named-pointer canonicalization, scene scale, model callback counts, written skill fields/strings, selected effect/affix state, logs and subsequent random-stream value. This is bounded collaborator evidence: it does not claim exhaustive internal manager/scene state, arbitrary callback mutation or universal exception equivalence.

Unchanged candidate: 6325 bytes, normalized DIFF, no unknown original references. All eighteen independently compiled deliberate faults were rejected by completed differences, with zero incomplete observations. Strict full Stage and independent root validation each passed all 192 tests. Root acceptance: 1311/5247 functions, 921777 original bytes, including 1255 MATCH and 56 behavioral acceptances.
