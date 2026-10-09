# CSkillTooltip::load recovery, 2026-10-09

## Scope and behavior

Original `_ZN13CSkillTooltip4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE`, address `0xa96270`, 5163 original bytes, pinned ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. The complete assembly and all NUL-terminated names were reviewed. The full existing gameui.cpp, including the recovered Foldout display, is preserved.

The loader resolves the supplied wide path with the original FileSystem flags. It uses the five-argument WindowManager overload with full-length std::string-to-CEGUI byte widening, a unique gui_ prefix, empty resource group and null callbacks. Window assignment and string-temporary lifetimes retain the original order.

Always-on-top, muted state, mouse passthrough and screen-scale conversion precede 32 ordered child lookups. All named tooltip fields are populated at verified offsets. The two groups of icon/label offsets use original signed UDim rounding and a freshly queried base icon for each child; no screen-dimension multiplier or cached base value is introduced. The caller's UI argument is used for scaling; the object's UI field is not overwritten.

## Focused evidence

**192 completed original/candidate comparisons**, zero differences and zero incomplete observations. Cases rotate twelve scale profiles through windows, four string patterns, callback mutation on/off and aliased/distinct child windows.

Ordered calls, complete input/output strings, full tooltip bytes after narrow pointer canonicalization, all window flags and offsets, returned UDim state, unchanged prefix fields and restored COW reference counts are compared. Inputs include short/long strings, embedded NUL, non-ASCII bytes and wide paths, signed zero, finite rounding boundaries, infinities and NaN. Callbacks replace root windows and base icons and modify returned positions. Out-of-range float conversions test this pinned compiler/machine behavior, not portable C++ guarantees.

**134 supplemental expected-exception comparisons** throw at each of 67 collaborator calls with mutation off/on. Matching propagation, partial object state and restored COW references are checked. These are excluded from normal successful-call coverage and do not establish universal allocation-failure or static EH LSDA equivalence.

All **12 negative controls** were rejected by completed differences. They cover FileSystem flags, unique prefix, embedded-NUL truncation of both filename and prefix, mouse passthrough, recursive scaling, child names, loop bounds, offset sign, negative rounding, next-group base and final label. Each mutation was verified to lie within the target function or its inlined helper.

## Full validation

The combined candidate is 8292 bytes and remains normalized DIFF, not MATCH. Fresh combined Stage validation passed all 183 tests with zero failures. After transactional publication, the independent root check also passed all 183 tests with zero failures. No standalone-playability claim is made. Accepted total: **1302 of 5247 game functions, 885569 original bytes**, comprising 1255 normalized MATCH and 47 behavioral acceptances. This is function 31 in the large-function recovery series.
