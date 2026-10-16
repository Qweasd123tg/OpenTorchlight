# Measured throughput pilot, 2026-10-15

Baseline: `1007609d7cdeea56f01016babb5ffa6f28a596f9` (3393/5247
accepted: 2435 MATCH and 958 BEHAVIORAL). This is a bounded test of the
previous repository-review ideas. It does not establish an overall source
recovery speedup of 1.5–2x or a sustained functions-per-hour rate.

The useful result is a smaller branch-derived CombineMenu test matrix, a
conservative declaration lookup repair, and eight additional game MATCH
addresses. Final canonical acceptance is recorded in `validation.json`.

The completed canonical check on 2026-10-16 passes **1143 tests, zero failures**.
Accepted coverage is **3401/5247: 2443 MATCH + 958 BEHAVIORAL**. All 3393 prior
accepted addresses remain; all 958 behavioral receipts bind to current objects
and inputs. All 3292 prior strong MATCH addresses preserve their normalized code.
See `functions.json` and `selftest-summary.txt` for the new addresses and affected
fixture coverage.

The complete command takes 1190.71s, including 67.26s hybrid build and 1086.12s
headless execution. The previous headless run took 1298.40s: the descriptive
ratio is 1.195x, with 212.28s less elapsed time. These are separate runs with
different production inputs and ambient conditions; the difference cannot all
be attributed to matrix pruning. The controlled focused sample remains the
evidence for that change, and overall source-recovery acceleration is unproven.

## Test cost

The two unsuppressed CombineMenu fixtures used 44,544 normal pairs each.
`usedMaskBits` selects 1364 per fixture by the original control flow and
callback mutations, keeping bits that affect reached callbacks, valid inputs,
or final captured state. This selector never deduplicates observed outputs.
All six locations, eight mutation values, seven reached callback sites,
normal-completion requirements, target identity, capture fields and child
isolation remain. The suppressed fixture retains its 24 cases.

An exhaustive host-side mapping checked all 49,152 combinations (44,544 valid)
per mode, with no missing representative. Both frozen binaries used identical
291 production TUs, headers and tool imports. In one uncontended focused sample
per variant, with six self-test workers/shards, three fixtures took
**102.4616s before and 3.3383s after (30.69x)**. Both passed against the original;
total normal pairs fell from 89,112 to 2752. This is the speed of these selected
fixtures, not the complete gate. They account for 6.65% of the previous full
run's summed fixture time; an idealized Amdahl estimate is only 1.069x overall
from this change alone. This is an estimate, not a measured full-run speedup.
Build timings are descriptive only.

A five-second live snapshot during the canonical rerun found six available CPU
cores, six active shard parents and 98.77% host CPU utilization, with no I/O
wait. This supports reducing redundant fixture work as the next measured
opportunity. It is not a concurrency experiment or proof of an optimal worker
count; see `resource-snapshot.json` for the sample and limitations.

Seventeen deliberately faulty implementations were rejected by a normal
completed behavioral difference; none relied on a crash or incomplete call.
Two equivalent implementation controls passed all 1364 pairs each. An earlier
direct-wrapper harness failed the target-identity guard and was discarded.
The corrected harness redirects the actual linked candidate entry only in its
replacement child, leaving the original child and target unchanged. This is
evidence for the listed defects, not proof against every possible wrong program.
See `test-cost.json`, `selector-proof.json` and `negative-controls.json`.

## Declaration lookup

On the same frozen eleven real counterexamples, exact declaration lookup
improves from 0/11 to 11/11. All 35 real negative examples remain blocked.
Across all 1854 baseline remaining game addresses on those same frozen inputs,
resolved declarations increase from 612 to 628: sixteen newly resolved and
zero previously resolved declarations lost. This broader lookup screen performs
no source generation, compilation or game acceptance.
The fixes cover verified global callback aliases, nested types, fixed array
references, the pinned stdio FILE alias, exact map defaults and leading comments.
Global versus nested identity, pointer-key constness, shadowed aliases and
pointer-object cv callbacks remain conservative. Return/static/variadic/sret
admission checks and comparison acceptance are unchanged.

The existing generator still emits **zero hypotheses** for those eleven
functions: all now reach `no supported semantic idiom`. Parsing is slightly
slower (single initialization sample 0.757s to 0.979s). Thus the measured gain
in accepted addresses from this lookup fix is **zero**. Header DWARF comes
from our compiled declarations, not original debug information.
Validation: 116 smallmatch tests (including 42 new declaration regressions),
158 context tests, ten alias tests and thirteen callback declaration tests:
297 unique tests pass. See `signature.json`.

## Source pilot

The previous screen's structurally closed proposals were not ready transfers.
Only the 27 groups/54 game addresses owned by `opencode` were tested; four
groups assigned to other owners were excluded. Against frozen baseline
headers/tools, the compiler-trial phase tested 27 source definitions in
10.6195s: one MATCH definition (LayoutDescriptor, two ABI addresses), 26 DIFF.
This time excludes setup/context preparation and overlaps unrelated compilation;
it is not an uncontended end-to-end throughput benchmark. See `generator.json`.

The original weak `iDataFileSaveAndLoad` destructor at `0xc67fb0` is an empty
inline body storing its base vptr (`0xff3810`). Our header only declared it,
forcing derived destructors to call it out of line. Restoring the inline body
gives strict MATCH for existing BinaryStyle and PairStyle destructors and the
new OgreResourceFile destructor. The new LayoutDescriptor destructor also
matches with ordinary automatic base destruction. No data layout changes or
instruction lifting are involved. Fresh `llm_loop.py --prepare-only` packets
were inspected before writing the two full-TU candidates; all earlier TU
definitions were preserved.

The result is eight new game MATCH addresses across four TUs, from two new
C++ definitions and one shared header repair, totaling 90 bytes of original
game machine code. Six additionally emitted static
cleanup helpers are outside the game count. All 3292 prior strong MATCH
addresses retain their normalized code and status in the static comparison.
The other destructor proposals still need their actual ownership/cleanup logic;
they were not published or accepted as empty bodies.

## Reproduction and limits

Tool regressions:

```sh
python3 -m unittest discover -s tools/decomp -p 'test_smallmatch*.py'
python3 -m unittest discover -s tools/decomp -p 'test_llm_context.py'
python3 -m unittest discover -s tools/decomp -p 'test_callback_aliases.py'
python3 -m unittest discover -s tools/decomp -p 'test_callback_declarations.py'
```

Canonical final gate (sources, tools, headers and generated types remain frozen
through completion):

```sh
env LANG=C.UTF-8 LC_ALL= TZ= OTL_JOBS=2 OTL_COMPARE_JOBS=2 OTL_BUILD_JOBS=2 \
  OTL_SELFTEST_JOBS=6 OTL_SELFTEST_SHARDS=60 OTL_SELFTEST_TIMEOUT=1800 \
  python3 tools/decomp/check.py
```

Full-gate before/after timings are separate runs and include the new source and
header repair; they are not a controlled isolated A/B experiment. Only the
focused test-cost comparison pins all production inputs. No executable or
external repository tool was installed, and no game window was opened.
Headless acceptance does not establish playable windowed gameplay or a linked
standalone reconstructed game.

Next useful tranche: bounded cleanup families with verified member ownership,
and the remaining highest-cost fixtures after measuring their redundant inputs.
The present data does not support promising hundreds of automatic transfers
from the closed destructor proposals.

Read-only follow-up identifies three related destructor definitions using the
existing `TArrayList::deleteAll()` pattern: LogicGroup (`0x795fe0/0x7960b0`),
SoundBankDataInformation (`0xa64820/0xa649f0`) and Achievements
(`0xec65a0/0xec66c0`, also clearing its singleton). These are six possible game
addresses requiring fresh preparation and acceptance. Selected-definition ABI
closures and field types are known, but some element destructors still reside
in the original hybrid; this does not close the standalone source dependency
graph. Their deleting destructors match in rejected isolated trials, while the
full destructor definitions fail, so none is counted or published here.

The next test-cost candidate is `merchant_main_slot_differential` (25,992
pairs, 165.684s, 2.162% of the historical summed fixture time). Original guards
make capacity unread at count=0 and item-mode replies unread for the merchant
owner path. A static domain proposal retains 11,814 cases. This proposal has
not been implemented, timed or checked with deliberate defects, and contributes
no measured speedup to this pilot.
