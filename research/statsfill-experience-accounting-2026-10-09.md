# StatsMenuFill experience accounting and opening

Six original functions, 728 original bytes, restored on merged main.

| Address | Function | Evidence |
|---|---|---|
| 0xc188e0 | getStatInvestment | MATCH, 91 bytes |
| 0xc18940 | getStatBarCurrentAmount | MATCH, 91 bytes |
| 0xc189a0 | getExperienceToSpend | MATCH, 24 bytes |
| 0xc189c0 | addExperienceToStat | MATCH, 308 bytes |
| 0xc18b00 | addExperienceSpent | Behavioral, 65 bytes |
| 0xc224e0 | setOpen | MATCH, 149 bytes |

Five missing nonvirtual declarations were recovered before requesting fresh
strict packets; all six packets completed with no unresolved dependencies.
Return/register behavior and player-field offsets were checked against the
original machine code. Existing player-layout views are reused. Invalid stat
indices return zero; the experience getter retains the original non-null player
precondition. Arithmetic preserves original 32-bit wrap using unsigned operations
and target-GCC conversions, without signed overflow or negating INT_MIN as int.

Opening updates visuals first, plays sample 22/66 only on an actual transition,
then calls the base implementation and updates interactive-menu visibility.
The separate sound-bank field at +0x180 is named in a view and offset-asserted;
it is not confused with the base class sound bank at +0x80.

The spent updater deliberately retains a code-generation DIFF: two compare
operands and the corresponding unsigned branch are reversed. The instruction
count and size match, but the comparison rule has not been broadened to accept
this as MATCH. Its readable unsigned clamp/add implementation is instead checked
with 324 original/candidate complete-state comparisons: null/present player,
two canary patterns, nine initial spent values and nine signed increments.
Values include zero, UINT_MAX, the signed boundary, INT_MIN and INT_MAX.
Temporary allocation identity is canonicalized only for the known player buffer;
unknown pointer values remain part of the observation. All menu/player bytes are
compared, including canaries surrounding the changed field.

Three independently compiled defects were caught by completed differences:
clamp-to-one, positive off-by-one and signed comparison. All report incomplete=0.
The unmodified final candidate then passed all 324 comparisons again.

## Aggregate acceptance

Strict isolated Stage validation and the independent integrated-root check each
passed all 203 tests. Every previous accepted address is retained and exactly
six are added. Total: 1353/5247 functions, 983907 original bytes; 1275 machine
MATCH and 78 behavioral. No tool, comparator, compiler-flag or gameplay-input
changes were made in this slice. Constructor/destructor and remaining callbacks
are not claimed complete.
