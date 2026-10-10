# PetMenu remaining lifetime, hover and spell methods

Restores five original member entries (3518 original bytes): constructor, D1/D2
and D0 destructors, handle_MouseOver and handle_SetSpell. D0 is strict MATCH;
the other four are backed by fresh completed original/candidate comparisons.
Two automatically generated destructor this-adjustment thunks add 15 bytes and
are strict MATCH. They are reported separately, not as two extra restored methods.
All 33 measured CPetMenu member addresses are now accepted.

## Completed comparisons

- Constructor: 32 cases over all three sound-record presence masks, collaborator
  replacement and two initial memory patterns. Full object/string-array state,
  sound names and full-width GUIDs, settings reads, creation ordering and canaries.
  44 expected exception unwinds are supplemental and excluded from acceptance.
- D1 and D0: 512 cases each cover owner/inventory, camera and three owned-object
  presence combinations, POD buffer shapes, empty/short/long string contents and
  collaborator replacement. Observe owner detachment, camera removal, deletion
  order, all 170 string-destructor requests, buffer/base cleanup and deallocation.
  CEGUI destructor/deallocator collaborators are controlled; this does not claim
  a separate revalidation of the vendor's string implementation. 48 expected
  exception unwinds are checked separately.
- Mouse-over: 9216 cases cover null window/owner, item absence, socket flag/count,
  unit type, slot boundaries 0/18/19/81, existing glow parent, finite/NaN/infinite
  UDim scales and collaborator replacement. Full state and ordered geometry/UI
  calls are compared, including reloaded window pointers and cached parent identity.
- Spell assignment: 7680 cases cover null window, drag owner/type restriction,
  item/type, owner states around 41/42, modifier-key state, full-width window IDs,
  null/present level and master pointers, and collaborator replacement. Exact
  item-use recipients, unlearning ID, layout timing, sounds and achievement are
  captured. 36 expected unwinds are supplemental, not normal completion evidence.
- All 4704 existing createMenus cases remain checked. Callback capture adds only
  the two exact restored handler identities and retains unknown pointers, receiver
  and member-pointer this-adjustment. A wrong-handler negative control fails.

Fifteen intentional compiled defects are rejected by completed differences, not
crashes/incomplete pairs. The final clean focused run passes all 18 tests.

## Declaration and layout evidence

Added only nonvirtual declarations for Character::unLearnSpell(int) and
GameUI::performItemUse(CLevel&, CEquipment*, CCharacter*, CCharacter*, CCharacter*).
The original bodies and callers were checked before choosing void returns; fresh
prepare-only context then resolved both blockers. No virtual slots changed.
Existing Character declarations from earlier PRs are preserved.

The 24-byte POD list at PetMenu+0x70 initializes with grow-by 10 and its buffer
is deleted without element destructors. Its original element type remains
unresolved; TArrayList<unsigned char> preserves these observed storage/lifetime
operations without inventing element behavior. No recovered method indexes it.

Adding the remaining members changed the emitted UTF-16 append helper from
MATCH to DIFF. A separate 1920-case comparison of the actual linked helper
covers external and self-aliased buffers, empty/nonempty data, growth, sharing,
return identity, embedded NULs and COW detachment. Acceptance rules are unchanged.

Stage.validate/publish and independent root check.py pass all 246 tests.
All previous accepted addresses remain. Totals: 1427 accepted entries,
1003547 original bytes, 1323 MATCH and 104 behavioral.
These bounded headless comparisons do not establish interactive playability.
