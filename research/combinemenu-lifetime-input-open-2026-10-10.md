# Remaining CombineMenu lifetime, input, hover, open and update methods

Restores seven member entries (4849 original bytes). processInput, setOpen and
D0 are strict MATCH; hover, constructor, D1/D2 and update have completed
original/candidate comparisons. Two compiler-generated destructor adjustment
thunks contribute 15 additional bytes, reported separately.
All 28 measured CCombineMenu member addresses are now accepted.

## Verification

- Input: 4096 completed pairs across active/inactive state, close requests,
  dragged socket items, hovered-item flag, glow-parent membership and collaborator
  replacement. Inactive handling preserves clicked slots; active handling resets
  both. Close request consumption preserves the original return value.
- Hover: 9216 completed pairs across four local-to-inventory slot mappings,
  nullable event/owner/item, socket/type combinations, child ownership, mutable
  window pointers, positive/negative/zero/infinite/NaN geometry and exact glow size.
- Constructor: 256 completed pairs over all six sound-presence masks, full-width
  GUIDs, alternative collaborators and initial memory patterns. Exact names and
  sample IDs are observed: STATSOPEN/22, STATSCLOSE/66, ERROR/24, LOWMANA/35,
  REVEAL/36 and GOLDBUY/23. Empty-map initialization and object/canary state are
  compared. Sixty expected exception unwinds are supplemental only.
- Destructors: 384 completed pairs each for D1 and D0. Populated maps, player
  listener removal, model/bank presence, callback insertions into the map and
  deletion ordering are observed. Deallocation is a controlled collaborator with
  node identities/order recorded; it is not a retest of the vendor allocator.
  Eighteen expected unwinds are separate from normal completion evidence.
- Open: 3072 completed pairs over repeated transitions, all four item-presence
  combinations, nullable player, animation branches, preexisting maps, tracking
  flag state and mutable collaborators. Closing restores item locations while
  suppression is active, then clears tracking; opening queues tip 14. Seventy-two
  expected exception unwinds observe the original partial state, including the
  tracking flag remaining set when the original throws before resetting it.
- Update: 1488 completed pairs cover open/closed/closing, nullable model where the
  original permits it, animation-playing/queued combinations, mutable model,
  skeleton, UI and window collaborators, unusual resolutions and float geometry.
  The exact tag_dropdowntop bone, half-screen offsets and Y inversion are checked.
  124 expected exception unwinds remain separate from successful completion.
- Existing createMenus now recognizes the exact original/candidate MouseOver
  callback pair while retaining unknown identities, receiver and this-adjustment.
  A wrong-hover-callback mutation is explicitly rejected.
- Fifteen compiled defects are rejected by completed differences with zero
  incomplete pairs. The final clean focused suite passes all 26 tests.
- Stage.validate/publish and independent root check.py pass all 285 tests.

No prior accepted address is lost. Acceptance criteria are unchanged.
Totals: 1487 accepted entries, 1361 MATCH + 126 behavioral, 1020523 original bytes.
Bounded headless comparisons do not establish interactive playability.
