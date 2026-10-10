# Remaining EnchantMenu lifetime and retirement animation methods

Restores four measured member entries (2457 original bytes): constructor,
D1/D2, D0 and update. D0 is strict MATCH; the other three have completed
original/candidate comparisons. Two compiler-generated destructor thunks
contribute 15 additional bytes, separately counted.
All 27 measured CEnchantMenu member addresses are now accepted.

## Verification

- Constructor: 256 completed pairs over six sound-presence bits, full-width
  GUIDs, alternate sound-manager and bank collaborators and initial memory
  patterns. Exact sample names/IDs, owner pointers, open/close/retirement flags,
  panel offset and object/canary state are compared. Sixty expected exception
  unwinds are supplemental and are not normal-completion evidence.
- Destructors: 64 completed pairs each for D1 and D0 across nullable player,
  model and sound bank, two memory patterns and four collaborator mutations.
  Listener removal precedes model and bank deletion. Callbacks may replace
  player or clear model/bank pointers. Sixteen reachable expected unwinds are
  compared separately. The fault at model deletion is not expected to throw
  when the preceding listener callback clears the model; that path completes
  normally and is included in the normal matrix.
- Update: 3720 completed pairs cover open/closed/closing state, original-valid
  nullable-model branches, animation-playing/queued combinations, retirement
  pending/not-pending, mutable collaborators, unusual resolutions and float
  geometry. Bone tag_dropdowntop, half-screen offsets and Y inversion are
  checked. Closing removes the background and marks fully closed before
  consuming retirement and requesting game state 0 / menu 2. Callback changes
  to retirement and UI pointers are observed. 124 general and eight retirement
  expected exception unwinds are supplemental only.
- Ten compiled defects are rejected with completed differences and zero
  incomplete comparisons. Clean focused suite: 24 tests pass.
- Stage.validate/publish and independent root check.py: 300 tests pass.

No prior accepted address is lost. Acceptance criteria and foreign TU bodies
are unchanged. Totals: 1517 accepted entries, 1382 MATCH + 135 behavioral,
1026132 original bytes. Headless comparisons do not establish playability.
