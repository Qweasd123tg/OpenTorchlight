# InventoryMenu remaining lifetime, open and mapping methods

Restores five member entries (4962 original bytes): constructor, D1/D2 and D0
destructors, setOpen and mapEventHandlers. D0 is strict MATCH; the other four
have completed original/candidate behavioral coverage. Two compiler-generated
destructor adjustment thunks add 15 bytes and are reported separately.
All 34 measured CInventoryMenu member addresses are now accepted.

## Completed comparisons

- Constructor: 128 cases covering all five sound-record presence masks,
  full-width GUIDs, alternate collaborators and initial memory patterns.
  Captures exact lookup names/order, samples 22/66/30/24/18, width conversion,
  notification clearing before createMenus and full object/string state/canaries.
  60 matching expected exception unwinds are supplemental, not acceptance evidence.
- D1 and D0: 512 cases each over owner/inventory, camera, model/bank/tooltip
  presence, string contents and collaborator replacement. Exact owner removal,
  camera clearing and deletion order (tooltip, model, bank) are observed, followed
  by all 170 CEGUI string-destructor calls and base/deallocation behavior.
  Vendor string destructor/deallocator bodies are controlled collaborators, not
  independently revalidated here. 48 expected unwinds are separate.
- Mapping: 2304 cases over recursive window trees, child-vector replacement,
  absent/empty/nonempty onClick properties, subscriptions, member-pointer identity,
  connection lifetime and caught exceptions.
- Open/close: 1728 completed cases exercise repeated transitions, nullable owner,
  existing/new viewport, tooltip-parent combinations, model animation branches and
  collaborator replacement. Geometry covers left/right/top/bottom clipping,
  positive/negative/zero dimensions, NaN/infinity and the one-pixel minimum width.
  Exact viewport order 3, scaling constants 124/132/166/192, camera setup and tip 0
  are captured. 87 expected exception unwinds are excluded from normal coverage.
- Existing createMenus: 3136 comparisons now execute the real recursive mapper on
  both sides, using initialized empty child vectors and controlled absent
  properties. The populated-tree mapping fixture above covers nonempty recursion.
  Unknown callback identities, receiver and this-adjustment remain observable.

Thirteen compiled defects are rejected by completed differences with zero
incomplete pairs. The final clean focused suite passes all 20 tests.
Stage.validate/publish and independent root check.py pass all 265 tests.
No previous accepted address is lost; acceptance criteria are unchanged.
Totals: 1455 accepted entries, 1340 MATCH + 115 behavioral, 1012672 original bytes.
Bounded headless comparisons do not establish interactive playability.
