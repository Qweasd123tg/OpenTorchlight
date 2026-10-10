# CombineMenu controls and listener methods

Restores fourteen member entries (1977 original bytes), nine strict MATCH and
five with completed original/candidate comparisons. Five compiler-generated
listener adjustment thunks contribute 30 additional bytes and are counted separately.

The source preserves the original distinction between NPC owner and player,
slot-index mapping, listener lifetime, hover and dragged-socket behavior, close
request ordering, weak mouse-click references, and recursive event mapping.
The original-item map uses the exact EEQUIP_LOCATIONS value type established by
the original map insertion symbol. The clearMouseClicks helper is transitively
inlined so the build does not introduce an unsupported game helper definition.

## Verification

- Click dispatch: left/right/nonclick buttons, nullable event window, full-width
  action values and virtual return values; 768 completed pairs.
- Close: 768 completed pairs spanning reference presence and collaborator
  replacement, close request ordering and all four weak-reference removals.
- onClick: 1536 completed pairs over open/closed state, action values and changes
  to the UI/client between collaborator calls.
- MouseOut: 2304 completed pairs over all four mapped slots, owner/window/item
  presence, hover match, dragged socket type, visibility order and UI replacement.
- Mapping: 2304 completed pairs spanning recursive children, property presence,
  member-pointer identities, connection lifetime and caught exceptions.
- Existing createMenus executes the real mapper on both sides with initialized
  empty child vectors and controlled absent properties. Exact callback identities,
  receivers and this-adjustments remain observable; populated recursion is tested
  separately. All prior layout, slot and interaction comparisons remain enabled.
- Eight compiled defects rejected with completed differences and zero incomplete
  pairs; clean focused suite passes all eleven tests.
- Stage.validate/publish and independent root check.py: 270 tests, zero failures.

Totals: 1474 accepted entries, 1354 MATCH + 120 behavioral, 1014679 original bytes.
No previously accepted address is lost; acceptance rules are unchanged.
This is bounded headless evidence, not a claim of interactive playability.
