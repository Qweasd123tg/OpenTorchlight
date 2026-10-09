# StatsMenu constructor, destruction and strict signature recognition

Follow-up to the creation/actions slice. Restored constructor 0xc18470 (864
original bytes), complete/base destructor 0xc0c2f0 (458 bytes), and the generated
deleting destructor 0xc0c4c0 (18 bytes). C1/C2 and D1/D2 aliases are not double
counted. The deleting destructor is byte-MATCH; constructor and complete destructor
remain DIFF and are accepted only by executed original comparisons.

## Behavior and observations

Constructor: exact partial initialization, four empty wide strings, separate
master-resource lookups, SoundBank allocation/construction, STATSOPEN/POINTASSIGN/
STATSCLOSE lookup and optional sample registration, second screen-edge reset, and
createMenus call. Thirty-two completed cases cover all eight missing/present sample
combinations, independent initial-state patterns, ordinary/zero/extreme GUIDs,
and callback-replacement configurations.
The fixture observes the complete initialized menu and bank buffers, identities,
order, arguments, signed 64-bit GUIDs, flags, and initialized strings. Resource
singletons and the bank pointer can change between callbacks. Twenty-four supplemental
expected exceptions cover allocation, bank construction, each lookup, and menu
creation; they are not counted as completed constructor coverage.

Destruction: model then bank virtual deletion with original conditional pointer
clearing, reverse wide-string member destruction, and base destruction. Each of
D1 and D0 passed 32 completed cases: null/present owned pointers, four string/COW
patterns, and deletion callbacks replacing the bank and model pointers. The
fixture observes complete initialized menu bytes, deletion order/identities,
base/free calls and restored alias refcounts. Sixteen supplemental exceptions
match unwind effects. The actual base destructor runs into a controlled core
destructor in both executions, preserving rather than ignoring the base-vptr step.

Eight constructor and six destructor independently compiled intentional defects
were all detected by completed differences. Combined create/constructor/destructor
focused run: all seven tests passed. The prior create fixture contributes 784
completed comparisons and 72 expected exceptions; all four measured entries
jointly have 880 completed comparisons and 112 supplemental expected exceptions.
These are bounded collaborator-based observations, not universal allocator,
engine-state, or exception proofs.

The initial sixteen successful constructor cases were below the existing twenty-case
acceptance minimum and were not accepted. Independent state/GUID cases expanded
the fixture to thirty-two without changing the threshold.

The first constructor-fixture attempt accidentally copied reference arguments
through the by-value invocation helper and failed before invocation. Explicit
reference carriers fixed the fixture; no failed/incomplete case was accepted.

## Reusable context fix

Strict preparation originally refused the explicitly declared destructor because
its word-boundary regex could not recognize a leading tilde. The same rule could
mistake a destructor declaration for a default constructor. Replace that boundary
with an identifier/tilde-aware boundary; no missing declaration is inferred.
Tests cover destructor recognition, constructor/destructor separation, wrong
parameters, nested declarations and identifier suffixes. The strict destructor
packet then completed without a bypass. Full Python suite: 590 tests OK, one skip.

## Final validation

Final current-tree check.py: all 199 hybrid tests pass. Accepted 1341/5247 functions,
976556 original bytes; 1268 MATCH plus 73 behavioral. All 1338 prior acceptances
are preserved; precisely three addresses are added. All 17 measured CStatsMenu
addresses in statsmenu.cpp are now accepted. This statement excludes the separate
static-initialization clone and is not a standalone-game or full-class ABI claim.
Original source input remains the pinned ELF; no interactive game was launched.
