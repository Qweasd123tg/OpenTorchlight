# StatsMenuFill bar controls and tick

Restored eight original entries, 2051 original bytes. Five are strict machine
MATCH: exit handler (0xc18b50), close handler (0xc18c40), experience-bar total
(0xc18d40), XP add amount (0xc18d80), and XP remove amount (0xc18e50).
Three remain DIFF and are accepted by executed original comparisons:
fillIntoBar (0xc21f30), removeFromBar (0xc22200), update (0xc22380).

Fresh prepare-only packets were generated after the phase-tooling change and
checked complete for all eight targets before transferring the candidate to a
new current-root Stage. Existing definitions were retained. The base close
callback's placeholder return type is corrected to bool, as required by its
original event-callback use and return value; no base body was invented.

## Behavior and evidence

The natural std::max/std::min clamp preserves the original NaN ordering and
produces exact XP amount code. Fill/remove preserve first-sample behavior,
held-state resets, threshold decisions, stat selection, allocated-point clearing,
wrapping integer updates, callback order, cooldown, and visual updates. Tick
preserves base-call-first behavior, timer arithmetic, first active held button
priority, accumulator updates, sound replay interval and stop window.

The three fixtures compare complete menu state with canaries, two player states,
sound-bank state, collaborator argument/order traces, and floating-point exception
flags. They cover invalid stat indices, zero/negative/current amounts, boundary
fractions, infinity/NaN, signed wrapping, both fill states, alternate player/bank
identities, multiple held-button combinations, cooldown/countdown branches and
nonfinite frame times. Collaborators are controlled spies; actual restored target
bodies execute on both sides. This is bounded runtime evidence, not a proof of
all possible engine or allocator states.

Completed equal comparisons: fill 4320, remove 1440, tick 4608 (10368 total),
zero differences and zero incomplete calls. Original CVTTSS2SI invalid inputs
produce INT_MIN and raise FE_INVALID. The helper preserves both rather than
using undefined out-of-range C++ floating conversion or silently losing the flag.
Six separately compiled intentional defects are rejected by completed differences:
fill amount, stat increment, missing invalid flag, removal sign, cooldown boundary,
and replay interval. The final clean candidate passes all three fixtures again.

## Aggregate validation

Normal Stage.validate ran the complete 208-test suite, enforced preservation and
fresh behavioral evidence, and Stage.publish verified the integrated object
identities atomically. An independent root check.py also passed all 208 tests.
All previous accepted addresses remain; exactly these eight are added.
Total: 1364/5247 accepted, 987827 original bytes, 1282 MATCH and 82 behavioral.
All measured CStatsMenuFill member addresses in this TU are now accepted; ctor
and destructor aliases are not double counted. This does not claim a standalone
rebuilt game, interactive UI verification, or completion of other menu classes.
