# PetMenu opening and recursive event mapping

Two original entries restored, 2206 original bytes. setOpen (0xb92aa0,
1474 bytes) is strict MATCH, independently backed by runtime comparisons.
mapEventHandlers (0xb93070, 732 bytes) is accepted through fresh completed
original/candidate comparisons; its generated code remains DIFF.

- Opening: 1152 completed cases cover four transitions, owner absence and states
  around 41/42, existing/missing viewport, positive and clipped coordinates,
  zero/negative dimensions, NaN position, model animation state, tooltip attachment,
  repeated calls and collaborator replacement. Full menu state, call order,
  animation/sound arguments, tab state, camera/viewport geometry, context tip and
  return-path layout timing are compared.
- 99 expected exception unwinds are compared separately, excluded from normal
  completion coverage.
- Mapping: 2304 completed cases cover flat, chain and branching six-window trees,
  every property presence mask, empty/nonempty values and exceptions caught inside
  the original mapper. Member-pointer representation, receiver, event name,
  postorder traversal and connection reference counts remain checked.
- Existing createMenus keeps all 4704 comparisons and now executes the actual
  mapper on both sides, including when the candidate caller flattens it. Its fake
  windows have correctly initialized child vectors and absent controlled properties.

A zero-width, negatively clipped geometry case exposed NaN-sensitive max operand
ordering. Reusing the existing maxSecond helper reproduces original SSE behavior
and produces a strict full-body MATCH. Eight compiled intentional defects are
rejected by completed differences, including this NaN regression, wrong owner
state, viewport layer, context tip, layout timing and mapping order/handler/value.
The final clean focused run passes ten tests.

Stage.validate/publish and independent root check.py pass all 237 tests.
All earlier accepted addresses remain. Totals: 1420 accepted entries,
1000014 original bytes, 1320 MATCH and 100 behavioral.
These headless checks do not establish interactive game playability.
