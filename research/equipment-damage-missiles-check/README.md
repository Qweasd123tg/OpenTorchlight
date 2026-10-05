# Damage, missile callbacks and level activation

Eight method bodies and two iMissile adjustment thunks (2,588 original bytes).
The final integrated check is recorded in decomp/README.md when the batch is
accepted; standalone results alone are not the acceptance of the whole tree.

## Verified entries and independent fixtures

- addInherentDamage 0x879e10 / addDamageBonus 0x879f60: normalized MATCH.
- getDamageBonus 0x86d440: damage-array fixture, 12,288 cases across three
  entries, twice per side; all 13 targeted faults killed. Uses real vectors and
  lists, duplicate type entries, independent capacities, socket/effect fallback
  indexing, signed count gates and sequential float-to-int accumulation.
- missileApplyingEffects 0x86e540: 2,304 cases twice per side, 13 faults killed.
  Real RTTI; enemy/equipped-actor/attack services are spies. Owner and equipped
  paths, absent owners/targets/resources, callback mutations, two getter calls,
  forwarded floats and ignored rollAttack return values are checked.
- missileDieing 0x86e360: 5,832 cases twice per side, nine faults killed. Real
  safe-pointer registration and index maintenance; actual Ogre allocation and
  deallocation, observed through the shared original low-address ELF PLT entry.
  The two emitted adjustment thunks 0x86e350 and 0x86e530 are also MATCH.
- DPS 0x86f360: 3,584 cases twice per side, 13 faults killed. Checks attack
  override priority, captured attack speed/base damage, parent types 0..6,
  child types 1..6, dynamic slot/list behavior, float factor and ceiling.
  Zero speed and out-of-range float-to-long conversion are not claimed.
- createElementalDamages 0x886240: 4,608 cases twice per side, 15 faults killed.
  Checks weapon gate, passive effects 52/10, truncation, field +0x24 = -900,
  post-callback entry reads, cached-manager cleanup and late equipped check.
- setActiveInLevel 0x886100: 2,304 cases with activation and deactivation per
  side, 15 faults killed. Real Ogre nodes; other services are controlled spies.
  Checks detach/visibility/culling order, particle parenting, zero position,
  immediate flags, null gates and pointer changes during callbacks.

## A strengthened cleanup test

The initial missile-death fixture detected eight faults but missed omission of
clearing the removed slot: removeAt made that slot fall outside logical size.
The final fixture also compares initialized capacity slots as pointer identities
without dereferencing freed references. Grow-by-one means every allocated slot
was initialized. The omitted-clear fault is now killed. The initial result is
retained separately; it is not relabeled as a successful kill.

Fixture cleanup releases remaining owned allocations without dereferencing
possibly already-destroyed objects, then drops the synthetic registration lists.
The deallocation observer never substitutes another allocator. Its first draft
could not reach a high-address library function with a short detour; the final
fixture observes the verified shared ELF PLT entry instead. This was a fixture
setup issue, not an original-game defect.

## ABI and source boundaries

missileApplyingEffects returns bool, not void. CMissile::doDamageToCharacter
calls iMissile slot +0x20 at 0xcf980a and tests AL at 0xcf980d. Declarations in
iMissile, Character and Equipment are corrected together without moving slots.
Character::rollAttack also returns bool (performAttack tests AL at 0x848000),
and its original float argument order and damage discriminator 7 are retained.
The existing getCharacterCanBeHarmedByMissile bool declaration is unchanged.

Effect damage type +0x14 and float +0x24 are carved from opaque storage; size
remains 0x138. Missile cleanup pairs OGRE_NEW_T with captured-pointer
OGRE_DELETE_T. Unregister exceptions propagate without inventing a deallocation
or rollback. No foreign source TU or generic pipeline is modified.

These are original-vs-recovered protocol/state tests, not a rendered combat or
full-campaign claim. Each comparison requires two normal child exits; paired
crashes are failures. External combat, effects cleanup, physics and rendering
are outside the controlled-collaborator fixtures' implementation claims.
