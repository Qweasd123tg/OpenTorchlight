# CPetMenu::setSlotIcon recovery, 2026-10-09

## Scope

Original `_ZN8CPetMenu11setSlotIconEP10CEquipmentii`, address `0xba16b0`, 4085 original bytes, pinned ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. Complete original assembly and unwind paths were reviewed; literals were independently decoded from the ELF. The existing full petmenu.cpp is preserved.

The inventory-slot homologue is useful but not interchangeable: Pet reads the Y coordinate before X, and passes the pet character's master to canEquip. The restored method preserves icon creation, muting, mouse passthrough, parent changes, both successive position writes, current slot size, front order and slot-data pointer. Identification/socket overlays, socket-icon capacity fallback, vertical offsets and spacing, eligibility/magical/type-specific glow, and optional stack-count text follow the original.

## Differential evidence

1728 completed original/candidate comparisons, zero differences and zero incomplete observations. Cases cover all six glow modes, socket counts and capacity fallback, missing/preexisting/failed icons, identified/unidentified items, stack label absence and threshold, four slot indices (0, 11, 12, 81), data indices 0/999, and negative, fractional and large coordinates.

Coordinate callbacks change values between reads and can replace the slot window, exposing X/Y evaluation order. Icon-creation callbacks can replace the current character with a different character sharing the master or having a null master. Calls, receivers, arguments, text and full initialized menu, equipment, child, UI, character, window and image buffers are compared.

Thirteen independent negative controls were killed by completed differences, with zero incomplete observations: master receiver, main-icon mouse passthrough, user-data index, identification overlay, socket image, initial socket offset, socket spacing, magical glow, gold item type, stack threshold, stack prefix, socket parent and coordinate-call order.

The 7173-byte candidate remains normalized DIFF, with no unknown original references. Full strict Stage and the independent root check each passed all 188 tests with zero failures. Accepted total: **1305 of 5247 functions, 897372 original bytes**, comprising 1255 normalized MATCH and 50 behavioral acceptances. Large-function recovery series: 34. No universal exception-equivalence or standalone-playability claim is made.
