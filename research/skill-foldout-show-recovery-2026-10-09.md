# CSkillFoldout::showFoldout recovery, 2026-10-09

## Scope

Original function `_ZN13CSkillFoldout11showFoldoutEP9CBaseUnitffbb`, address `0xa9c680`, 6512 original bytes. The original ELF SHA-256 is `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. Full prepared assembly and literal data were reviewed. Existing complete gameui.cpp definitions are retained. The candidate is 11090 bytes, normalized DIFF, not byte MATCH; acceptance is behavioral.

## Recovered behavior

Both option flags are stored before parent/null-owner/null-manager early exits. The window is attached and brought forward, and all 100 icon and hotkey cells are hidden and disabled in column-major order. The left-slot option adds the weapon attack cell and reserves column zero on subsequent tiers.

Skill ordering uses known-skills index order within each of 100 queried tiers. Tier derives from floor(float(unsigned level)/5), capped at ten. Effective-level, flag, left-slot eligibility and activation filters retain the original short-circuit behavior. Skill GUIDs remain 64-bit. Hotkey labels are emitted only for a found binding; the first differential pass caught an incorrect index-12/F13 label assumption and corrected both skill and default-attack paths.

Inventory item GUID deduplication precedes capacity checks. Null image exits the entire function after partial window updates. Aspect-ratio calculations preserve separate dynamic ratio reads and image reads across callbacks. Grid wrapping retains the original strict greater-than boundary. Final size, UDim rounding, sentinel coordinates and screen clamps retain floating-point ordering. The owner/UI/property receivers are reloaded where the original does so.

## Focused comparison

The standard headless original-versus-candidate fixture passes **3168 complete scenarios**, zero differences and zero incomplete observations. Six branch witnesses are covered. Cases combine 22 modes, six scales, four option combinations, callback mutation on/off and three placements.

Coverage includes early exits, skill filters and tier boundaries, unsigned maximum level, array-capacity fallback, row/column overflow, primary and secondary hotkeys, absent hotkeys, duplicate items, null images, zero ratios, real BMP UTF-8 and embedded-NUL translations, lazy translation caching, unusual UDim scales and inventory capacity fallback. Ordered collaborator traces, full foldout bytes with narrowly canonicalized pointers, all window states, userdata offsets, GUIDs and static translation contents are compared.

All **12 negative controls** are rejected by completed original/candidate differences, with no incomplete comparison counted as a kill. Mutants cover early flags, parent check, final grid column, weapon image, passive filter, GUID truncation, missing hotkeys, item deduplication, null-image return, aspect ratio, wrap boundary and position constants.

## Full validation

Full strict Stage passed 181 tests with zero failures. After transactional publication, the independent root check also passed all 181 tests. No universal exception-equivalence or standalone playable-game claim is made. Accepted total: **1301 of 5247 game functions, 880406 original bytes**, comprising 1255 normalized MATCH and 46 behavioral acceptances. This is function 30 in the large-function recovery series.
