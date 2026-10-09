# Fresh evidence for five existing Equipment definitions, 2026-10-08

No implementation body was written or changed by this batch. The existing
CEquipment source already had comparison fixtures, but those fixtures predated
the standard direct-invocation marker and per-address Coverage record. They
therefore did not meet the current acceptance protocol despite prior passing
comparisons. This batch strengthens the fixtures instead of weakening a gate.

- 0x893660 getEquipmentStats: 24219 original bytes, 294 cases.
- 0x88f420 getEquipmentDescription: 16955 bytes, 1224 cases.
- 0x88d040 getEquipmentType: 9173 bytes, 1536 cases.
- 0x880950 calculateCombatStats: 6615 bytes, 1122 cases.
- 0x889110 unitInit: 8303 bytes, 1140 cases.

Total: 65265 original bytes; 5316 completed original/compiled comparison cases,
zero different and zero incomplete. Each case retains two calls and all prior
inputs, spies, status/equality checks, and post-state assertions. The first
call now goes through autotest::invoke with the exact original or compiled
entry function pointer; returned strings are captured by the existing standard
serializer. The second call stays direct. Coverage::observe==0 is an additional
mandatory check. AutoTest, acceptance.py and publication gates are unchanged.

Twelve deliberately wrong implementation variants produced completed
original/replacement differences: physical half-damage, active-set boundary,
socket numerator, snapshotting a mutable affix count, suffix rank selection,
buy-price flag, quality flag, sword label, range default, fixed-damage boundary,
socket cap and unlimited-use sentinel. Mutants remain private and were never
published. They demonstrate sensitivity of each upgraded fixture.

A read-only audit found 140 existing compiled definitions (184666 original
bytes) with original declarations in old fixtures but no Coverage/invoke markers
and no current acceptance. These were candidates only. This batch verifies five
of them; the other 135 remain unaccepted until individually checked. It is not
140 newly written or automatically accepted functions.

The controlled headless harness intercepts external game/rendering services.
No rendered game was launched, no acceptance threshold was reduced, and no
original asset or executable was modified. The full Stage and independent repository check passed, as recorded below.

## Final validation

Stage publication and the independent root tools/decomp/check.py both pass:
166 tests, zero failures, exit 0. Acceptance is 1185/5247 functions, 733100
original bytes: 1149 normalized MATCH and 36 behavioral acceptances. This adds
five existing addresses and 65265 bytes to the previous 1180-function result. Twelve negative
controls were rejected with completed differences. No remote push was performed.
