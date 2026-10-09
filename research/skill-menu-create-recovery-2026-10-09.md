# CSkillMenu::createMenus recovery, 2026-10-09

## Identity and scope

Original ELF SHA-256: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Original function `_ZN10CSkillMenu11createMenusEv`, address `0xbe19c0`, 8221 bytes.
The GCC 4.4.7 candidate is 11767 bytes and remains normalized **DIFF**; this is a behavioral recovery, not a MATCH claim. Static EH LSDA equivalence and ambiguous linked narrow/wide literals are not promoted to proven equivalence.

The complete existing `decomp/src/skillmenu.cpp` was preserved and the body appended. Header padding was replaced with verified typed fields at the same offsets without altering the object size or vtable. Original assembly and full terminated literals were read from the prepared function packet and original ELF; no inferred game mechanics were added.

Parent is pass6/pass7 integration commit `bd0529af91477f32e4d4f0d0ffd0f3cfd547085c` (PR #13).

## Restored behavior

- Resolution reads retain their order and re-read the property receiver. The model path is `media/ui/models/skill/skill.mesh`, with the original creation flags and `generateExtremes(5, true)`.
- Named model bounds remain alive through the end of the function. Position is `0.5 * ((width - height / 0.75) / YRATIO)` on X, with zero Y/Z; the model is hidden.
- `ui2`, `DefaultWindow`, and `SkillSheet` are preserved, including size, position, RiseOnClick, mouse pass-through, Z-order and MouseMove callback registration.
- File lookup uses `media/ui/skillmenu.layout`, the original false/true/false flags and a CFileInfo whose lifetime spans the remaining function. Layout loading preserves the complete std::string length, including embedded NUL bytes, rather than introducing c_str truncation.
- Scaling, function mapping and event mapping retain their order. Blocker, Close, skill panes, labels and radio tabs are looked up from the original layout root. Panes B/C are hidden; A/B/C radio selection is true/false/false.
- BottomFrame is detached and reparented before TopFrame. Their front/RiseOnClick/Z-order operations are preserved. There is no invented extra attachment or visibility operation for the layout root.
- The tooltip is initialized with GameUI's root at +0x488, published to the menu before loading, and loaded from `media/UI/skilltooltip.layout` with the original case.

## Differential evidence

The fixture executes original and compiled bodies in separate children of the standard headless hybrid, with controlled collaborators. It compares ordered calls, full 0x758-byte menu state after canonicalizing only known pointer identities, window parents/flags, radio selections, full callback member pointers including this-adjustment, and connection lifetimes.

The normal matrix has **784 completed comparisons, zero differences and zero incomplete observations**: seven widths, seven heights, eight ratios and two initial-state/receiver-replacement variants. Ratios include signed zero, finite values, infinities and NaN. Filename patterns cover short/long names, embedded NUL and non-ASCII bytes.

A separate **24-case exception matrix** injects failure at either event subscription or tooltip loading, across four filename patterns and two initial-state variants. It checks matching propagation, partial state and restored source-string COW reference counts. Expected exceptions remain explicitly incomplete normal calls and are excluded from normal acceptance coverage; identical crashes cannot establish acceptance.

Twelve deliberate faults were compiled independently and all rejected through completed original/candidate differences, with zero incomplete observations: wrong model path, bounds, X sign, imageset, callback, file flags, c_str truncation, omitted function mapping, pane visibility, selected radio tab, tab label, and tooltip root.

## Validation

Strict isolated Stage validation passed all **179 tests** and accepted coverage for 0xbe19c0. Transactional publication transferred only the header, source and fixture after independently verified PR #13 publication. The complete resource archive was present and hash-verified. The unchanged strict comparator and preservation guard were used; no acceptance gate was relaxed.

Independent root `python3 tools/decomp/check.py` passed all **179 tests** again. Accepted game functions are **1299 / 5247**, representing **866774 original bytes**: 1255 normalized MATCH plus 44 behavioral acceptances. The large-function recovery series totals 28 functions.

No windowed game or standalone-game execution is claimed. Differential tests with controlled collaborators are behavioral evidence for this function, not proof of a complete playable reconstruction or universal exception equivalence.
