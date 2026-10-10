# InventoryMenu hover, spell and direct actions

Restores four member entries, 1765 original bytes. toggleWeaponSet (108 bytes) and handle_CloseButton (232 bytes) are strict
MATCH. handle_MouseOver and handle_SetSpell have
fresh completed original/candidate comparisons. All earlier accepted addresses
remain accepted.

## Coverage

- Mouse-over: 9216 cases across absent window/owner/item, socket/type decisions,
  slots 0/18/19/81, finite/NaN/infinite UDim geometry, parent membership and
  collaborator mutation. Full object/canary state and ordered UI calls are
  captured, including repeated window loads and cached parent identity.
- Weapon toggle: 192 cases independently vary owner presence, alive/attack/skill
  answers, checkbox selection, initial close state and collaborator mutation.
  Original error sound 24 and checkbox inversion are observed.
- Close: 768 cases cover four mouse buttons, all four registered weak-reference
  presence masks, initial close state and replacement during unregister calls.
  Exact clear order is fourth, third, first, second; indices are preserved.
- Spell assignment: 13824 completed cases cover drag owner restriction, item type,
  AI states around 41/42, modifier key, full-width IDs and skill GUIDs, missing
  skill, effective level, executed-by-property and enabled flags, nullable level,
  collaborator replacement, copied skill names including embedded NUL/non-ASCII,
  original item-use recipients and sounds. 42 matching expected exception unwinds
  are supplemental and excluded from normal completion evidence.
- Existing createMenus comparisons retain receiver and this-adjustment, adding
  only the three exact restored callback identity pairs.

Five direct-action and eight spell intentional compiled defects are rejected by
completed differences rather than crashes or incomplete pairs. Clean focused
comparisons and the aggregate suite pass. Acceptance criteria are unchanged.

Stage.validate/publish and independent root check.py: 257 tests, 0 failures.
Totals: 1448 accepted entries, 1337 MATCH + 111 behavioral, 1007695 original bytes.
These bounded headless comparisons do not establish interactive playability.
