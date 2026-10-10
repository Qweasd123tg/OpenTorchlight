# EnchantMenu controls, input, hover and listener methods

Restores 18 CEnchantMenu members (3101 original bytes): twelve strict MATCH and
six verified by completed original/candidate comparisons. Six compiler-generated
listener-adjustment thunks add 36 original bytes and are counted separately.

## Verification

- Click dispatch: 768 completed pairs, preserving mouse button and virtual slot.
- Actions: 1536 pairs across open state, close/interaction/other actions and
  mutable collaborators. Close: 768 pairs checking flag, target clearing,
  the four safe pointers and closeRight ordering.
- Recursive event mapping: 2304 completed pairs with populated child trees,
  missing/empty/nonempty properties, property failures, specific callback identity,
  receiver and this-adjustment. Unknown callback identities remain observable.
- MouseOut: 576 pairs across mapped inventory slots, nullable event/owner,
  hovered and dragged items and socket item types.
- Input: 4096 completed pairs. Inactive handling preserves clicked slots;
  active handling resets both. A close request affects the return value.
  Enchant's hovered-item flag branch hides foreground before socket overlay;
  its null-hover branch hides them in the opposite order, matching the original.
- Hover: 2304 pairs cover local-to-inventory slot mapping, item/socket state,
  mutable collaborators, glow parenting and unusual floating-point geometry.
- Existing createMenus runs real event mapping on both sides and checks exact
  original/candidate callback pairs without masking unknown identities.
- Twelve compiled defects are rejected with completed differences and no
  incomplete comparisons. The final clean focused suite passes all 16 tests.
- Stage.validate/publish and independent root check.py pass all 292 tests.

The fully-closed byte is named without changing layout. Owner setters preserve
mutual exclusion between character and item owner; all five item notifications
only call updateLayout. The existing two-argument setOpen behavior is unchanged.
GameUI's nonvirtual requestSetGameState declaration follows original 0xa828f0;
no foreign translation-unit body is changed.

No previous accepted address is lost and acceptance criteria are unchanged.
Totals: 1511 accepted entries, 1379 MATCH + 132 behavioral, 1023660 original bytes.
Constructor, destructor and update remain for the next focused batch.
Bounded headless comparisons do not establish interactive playability.
