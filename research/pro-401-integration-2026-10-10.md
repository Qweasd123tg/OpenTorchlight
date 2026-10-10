# ChatGPT Pro pass 10: integration of all 401 definitions

The incoming package is now represented in the normal `decomp/src` translation units and shared `decomp/include` layouts. Its historical MATCH labels were not reused as acceptance. All 401 primary definitions were compiled and compared again with the pinned GCC 4.4.7 toolchain and original ELF.

The final primary-function split is 396 normalized object MATCH and five independently executed behavioral comparisons:

- Inventory::itemsInPane: pane bounds, slot zero fallback, count/capacity, callback mutation.
- GameClient::processMenuInput: UI availability, held buttons, callback changes, elapsed-time edge values.
- Graph::clear: line limits, missing curves, list count/capacity and callback identity.
- STRINGS::GetValueAsWString(bool): both original wide literals.
- MATH::worldToLocal: matrix components, aliasing, signed zero and non-finite inputs.

Four definitions were already present in the working baseline and were reconciled rather than duplicated. Constructor/destructor aliases are checked separately from the primary-definition count. The 401 count is not an assertion of 401 newly accepted unique gameplay addresses.

## Integration repairs

The package did not carry all the class declarations/layouts required by its snippets. Fields and signatures were reconstructed from the original and checked by fresh full-TU comparison. Existing Inventory users and two equipment fixtures were adapted to the typed owner/equipment-list fields; their assertions remain intact.

Integration also exposed three pre-existing EffectManager defects: an extra pointer dereference in the activation overload, wrong value offset/conversion constants in the named overload, and a missing null write before removing a deleted effect. Six regression tests cover 17,280 completed original/replacement pairs. Thirteen deliberately wrong isolated effect/utility variants are rejected by completed differences, not matching crashes.

The SoundManager constructor and its channel/sound-instance layout now match the original. A TU-local copy of the pinned OGRE 1.6.5 UTFString header preserves its license and implementation, changing only three inlining attributes required to preserve the original emitted SDK family in GameUI. Four SDK regression tests cover 640 completed comparisons; deliberate assign/copy/destructor regressions are rejected. The original SDK header used by other translation units is unchanged.

The previously flattened UI implementations retain original out-of-line call boundaries for window dimensions, scaling, cursor state and closing menus. Otherwise GCC could inline newly imported collaborators into those large bodies. The two entry-frame fixtures now split their unchanged redirects across bounded patch sets because both original and recovered collaborators exist; their coverage and checks are retained.

Graph.cpp and UtilitiesMath.cpp retain the baseline implementations. Their relevant incoming definitions have behavioral proofs; unrelated old unaccepted DIFFs are not reclassified by this import.

## Verification limits

Only the documented headless hybrid has been run. The fixtures compare the actual original and replacement entry points, outputs, relevant state and collaborator traces. They do not prove all possible inputs, gameplay with a window, rendering equivalence or a standalone rebuilt game. Invalid wide integer parsing remains the original uninitialized-result behavior and is not claimed as defined-input coverage. No supplied compiler/archive binary, original ELF or game asset is added to Git.

## Final acceptance

Strict isolated Stage and independent root check each passed all 383 tests. Root acceptance: 2072 / 5247 gameplay addresses, including 1847 MATCH and 225 behavioral acceptances; 1101859 original machine-code bytes. Net increase: 415 accepted addresses, no previously accepted address lost. The primary incoming set remains 396 MATCH plus five behavioral definitions; every emitted ABI address also has fresh evidence. The net increase includes collateral legacy definitions newly proved during integration, not only newly written snippets.
