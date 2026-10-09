# CCombineMenu::performInteraction recovery, 2026-10-09

## Scope

Original `_ZN12CCombineMenu18performInteractionEv`, address `0xad6470`, 4334 original bytes, pinned ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. The entire original assembly, unwind paths and referenced wide literals were reviewed. No current Ghidra draft was available. The existing complete combinemenu.cpp is preserved.

Missing declarations were verified from the selected method's caller, existing typed parser API and createEquipment's dynamic-cast wrapper. Only declarations are added to ResourceManager; those method bodies remain external. The menu's soundbank pointer is named at its existing offset without changing layout. Small verified views describe only the recipe and owner fields read by this function.

## Behavior retained

- Two independent recipe-singleton reads; signed initial recipe-count handling; capacity-based TArrayList fallback; eligibility scanning across four menu slots.
- Exact named-item GUID matching, ordinary type matching and the special magical-item category with both exclusions. Quantities, stack changes and callback-visible receiver reloads preserve machine behavior.
- The original selection quirk is retained: a recipe's total required quantity is compared with a threshold, but the threshold is then set to the number of ingredient entries. It is not silently corrected to the summed quantity.
- Consumption preserves partial-stack adjustment, removal, menu notification and virtual destruction order. Success/failure sounds, optional character voice and journal-statistic timing are unchanged.
- Existing items are moved back into inventory before outputs are created; a failed pickup falls back to dropping into the current level at the character's current position.
- Only the first recipe output is used. Direct-item creation and spawn-class generation retain different null checks and early exits, the maximum of four spawned outputs, optional enchantment and destination slots.

## Focused evidence

**256 completed original/candidate comparisons**, zero differences and zero incomplete observations, cover 32 scenarios, four string/voice profiles and callback mutation off/on. All thirteen branch witnesses are reached (0x1fff).

Cases include zero and negative signed recipe counts, empty/unmatched recipes, ordinary and magical eligibility, named GUIDs and missing groups, quantity/stack boundaries, twelve eligible recipes requiring list growth, the selection-threshold quirk, capacity fallback, direct/spawn outputs, missing spawn class, empty/more-than-four spawn results, enchant flags, partial consumption, owner/resource replacement and failed inventory pickup with a drop fallback.

The fixture compares ordered collaborator calls, strings, receivers and arguments; full menu bytes with narrowly canonicalized local pointers; complete fake equipment, owner, inventory, resource, recipe and data-group buffers; recipe strings/counts; resulting inventory slots, stack changes and destruction/enchantment counts. Full buffers are initialized identically before each original/candidate call.

**120 supplemental expected-exception comparisons** inject faults into the first 30 collaborator positions of spawn-output and drop-fallback scenarios, with mutation off/on. Matching propagation and partial state are compared. These are excluded from successful-call coverage; no universal allocation-failure or static EH LSDA equivalence is claimed.

## Full validation

The focused candidate is 4457 bytes, normalized DIFF, with no unknown original references. All twelve independent negative controls were rejected by completed differences, with zero incomplete observations. They cover failure sound, exact-zero eligibility, magical override, named GUID matching, recipe-selection threshold, stack delta, removal notification, journal statistic, spawn count limit, enchant flag, direct-output slot and drop-position flag. The full strict Stage passed all 187 tests. After transactional publication, the independent root check passed all 187 tests again. Accepted total: **1304 of 5247 game functions, 893287 original bytes**, comprising 1255 normalized MATCH and 49 behavioral acceptances. This is function 33 in the large-function recovery series. No standalone-playability claim is made.
