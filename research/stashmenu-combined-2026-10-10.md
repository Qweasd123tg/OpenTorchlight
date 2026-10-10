# StashMenu controls and pet-tab actions

Restores 16 CStashMenu members (2287 original bytes): ten strict MATCH and
six with completed original/candidate comparisons. Six compiler-generated
listener-adjustment thunks add 36 original bytes and are counted separately.

## Verification

- Owner switching: 8192 completed pairs cover nullable/same/different owners,
  nullable normal/shared inventories, owner ISA results, unavailable and available
  shared stash, player/follower presence, and callback changes to owners, followers
  and singleton identity. Repeated singleton calls and listener ordering remain
  observable. Player switching: 512 pairs across empty/null/one/two followers,
  nullable/same/different player and callback changes. Fifty-two reachable expected
  exception unwinds are separate from normal completion coverage.

- Pet-tab actions: 1920 completed pairs across open state, three recognized
  actions and signed boundary/other values. Radio selection, panel visibility
  and virtual updateLayout order are observed, including callback replacement
  of windows and changes to open state while an action is underway.
- Close: 768 completed pairs across mouse buttons, initial flag, four safe
  pointers and mutable collaborators. Target clearing, safe-pointer removal
  and closeRight occur in original order.
- Virtual click dispatch: 960 pairs preserve action values, nullable window,
  mouse button, receiver and the virtual result.
- Recursive event mapping: 2304 pairs cover populated trees, property states,
  failures, callback identity, receiver and this-adjustment.
- Existing createMenus tests use real recursive mapping on both sides with
  controlled absent onClick properties and exact original/candidate callback
  pairs. Unknown identities remain visible. Resource-hierarchy acceptance:
  392 completed pairs. Main/pet slot comparisons remain green.
- Twelve compiled defects are rejected with completed differences and zero
  incomplete pairs. Wrong pet callback yields 392 completed differences.
- Clean focused suite: eleven tests pass. Stage.validate/publish and independent
  root check.py: 307 tests pass.

Preparation used canonical ELF TU spelling stashmenu.cpp in an isolated copy
while preserving all existing bodies. Integration retains the repository's
existing StashMenu.cpp filename. Character.h adds only CStashMenu friendship to access its existing private inventory field; no layouts or foreign TU bodies change.
No previous accepted address is lost and acceptance criteria are unchanged.
Totals: 1539 accepted entries, 1398 MATCH + 141 behavioral, 1028455 original bytes.
Headless comparisons do not establish interactive playability.
