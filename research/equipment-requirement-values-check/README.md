# Reading an item's level and stat requirements

Five original entries: strength 0x86dc50, dexterity 0x86dae0, magic 0x86d970,
defense 0x86d800 (354 bytes each), level 0x86ddc0 (283 bytes).

The five-entry fixture passes 15,360 cases, twice per side. All 28 targeted
mutations are killed, covering both the shared inlined reduction and individual
getters. getLevelRequirement also achieves normalized MATCH (100%).

The general reduction (effect 93) is converted to int FIRST. A category-specific
float reduction is then added to that integer and converted to int again.
Postponing the initial truncation changes results for fractional inputs and is
caught by the test. Category precedence is martial, ranged, magic, armor, spell;
overlapping category flags do not accumulate several category reductions.

Requirements are read after callbacks, then clamped at zero. A null Character
is a deliberate exception in the LEVEL getter: it immediately returns the
stored value without clamping or checking categories. The four stat getters
still inspect categories and clamp their result. Negative stored values,
fractional reductions, all category masks, null/non-null actors, repeated calls
and callback changes to requirement fields are included. Out-of-range float to
int conversion and signed-overflow inputs are outside this fixture's claim.

The category IDs 162/163/164 were verified against the original
media/unittypes.hie: ItemCategoryMartial, ItemCategoryRanged, ItemCategoryMagic.
Character::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES) is a nonvirtual float
service, as verified by the original symbol and SSE caller sequence. Its full
external effect aggregation is not implemented or claimed by this test.
