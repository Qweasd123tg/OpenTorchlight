# Equipment enchantment generation

Original `CEquipment::enchant(bool)` at 0x8845c0, 1120 bytes. Unit category IDs
17 (Ring), 24 (Necklace) and 135 (RandomMagic) are taken from the original
pak.zip `media/unittypes.hie`, not guessed from branch behavior. Globals at
0x24..0x44 are named from CGameGlobals::reload configuration keys. Header size
and all existing later fields remain unchanged.

The fixture compares 13120 cases, two calls per side. It covers independent
unique/magic/random-magic classification, six equipment categories, existing
affix/passive counts and absent managers, all six relevant boolean/state flags,
strict probability boundaries, NaN draws, alternating singleton instances,
callback changes to classification/level/socket state, and absent resources.
The real CDataGroup reads ALWAYS_IDENTIFIED; an observing forwarding wrapper
records its key/default/call count. Random generation and affix creation are
controlled collaborators, so every requested range/count/level is compared.
Price recalculation is checked as a collaborator call, not redundantly retested
as part of the enchantment generator's acceptance.

Important original behavior: RandomMagic forces the chance decision but does
not bypass the item-generation eligibility flag. Magic bypasses the initial
chance gate. Unique fallback uses level+1 and a different existing-effect test.
Random-magic socketables can receive affixes but do not enter the new-socket
category list. Existing sockets are retained. Probability comparisons are
strict, and NaN does not pass them. ALWAYS_IDENTIFIED is queried only while the
item is unidentified. Final price recalculation always runs.

These tests do not validate the complete random-affix resource catalogue or
its statistical distribution. No render loop or whole-game run is claimed.

Final fixture: 24/24 viable sampled and 24/24 targeted mutations killed.
