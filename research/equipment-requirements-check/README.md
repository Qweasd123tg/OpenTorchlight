# Equipment requirements

Original `setRequirements()` 0x880030, 2335 bytes. All five values come from
real DataGroup getters; type queries and graph services are controlled spies.
The fixture compares 3360 cases twice per side, complete service traces and
all requirement/level/reduction fields. The base product is eight type-response
combinations x eight reductions x six requirement patterns x eight curve-value
patterns. Extra callbacks change level/reduction, requirement fields, or the
current data group while evaluation is in progress.

Preserved details:
- LEVEL_REQUIRED is synthesized only when zero for weapon, armor or trinket.
  Nonzero explicit values remain unchanged.
- Four stat requirements are scaled only when nonzero for weapon or armor.
  Trinket membership alone does not scale these fields.
- Level reduction is min(field28c,5); stat reduction is sampled later as
  min(field28c,10) and reused across all four stats. Negative values are not
  clamped away. Level and stat scales are evaluated in the original order.
- Float32 graph value times percentage divided by 100, then floorf, then
  integer reduction. Results <=1 become 0, not 1. Curves are still the original
  engine collaborators; no mechanics or graph data are invented.

24/24 sampled viable mutations and 23/23 targeted mutations killed, including
independent graph selection, rounding, scaling and clamp faults in every stat.
Extreme float-to-int overflow, null graphs and allocation exceptions are not
claimed covered. These fixture callbacks verify re-read/caching order; they
are not claims that all such changes happen in normal gameplay.
