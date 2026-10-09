# CSkillMenu::update recovery, 2026-10-09

## Scope and source

Function `_ZN10CSkillMenu6updateEf`, original address `0xbe3e10`, 7120 original bytes. Original ELF SHA-256 is `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. The complete prepared assembly was reviewed; no current Ghidra draft was available. Prior accepted source definitions are preserved in their original TU.

The candidate is 20552 bytes and remains normalized DIFF, with no unknown original references. This work uses behavioral comparison rather than claiming normalized or byte MATCH. Static EH LSDA equivalence is not asserted.

## Behavior preserved

- Resolution reads precede skill-point comparison. A changed count is stored before virtual updateLayout; subsequent reads use the possibly changed owner.
- The function-local Points Remaining translation is lazily initialized, retried while empty, and cached while nonempty. The original Ogre UTF-16 intermediate, wide-string conversion and CEGUI UTF-8 roundtrips are retained.
- A non-ASCII differential case caught an initial overload error: CEGUI setText(text.c_str()) selected byte widening. The original calls the unsigned-char UTF-8 constructor, and the source was corrected with the explicit cast before acceptance. The Unicode cases were retained.
- Unchanged text avoids setText. Fully closed menus only detach an existing tooltip and return; otherwise model animation and entity animation precede bone-relative layout.
- TopFrame and BottomFrame retain distinct X calculations and share the top frame's Y. Screen-edge clamping preserves the original floating-point operand behavior, including NaN cases.
- Closing uses short-circuit checks of both playing and queued CLOSE animation. Only then is the model hidden, the closed flag written and the background detached.
- A hovered skill with no manager or no lookup result returns without removing a previous tooltip. A found skill uses the owner's current identity and 64-bit mouse coordinates converted to float. Other paths detach the tooltip from its current parent.

## Focused evidence

The standard headless hybrid compares original and candidate calls in separate children. The fixture runs **1728 scenarios, each for two frames**, spanning four open/closed combinations, three layout/cache-count conditions, four hover/manager/lookup outcomes, six translation/animation profiles, two callback-mutation variants and three static-cache states.

Checks include ordered collaborator traces, complete menu bytes after narrow pointer canonicalization, resulting window text/parents/positions, cached translation, owner skill points and branch witnesses. Cases include empty, non-ASCII/non-BMP and embedded-NUL translations, integer extremes, signed zero, infinities and NaN scaling. Callback mutations exercise property/UI receiver replacement, owner changes during layout and owner loss during animation.

The final integration fixture has 1728 completed comparisons, zero differences and zero incomplete observations. All eleven instrumented branch witnesses are reached (0x7ff). The fixture's point adjustment uses explicit unsigned arithmetic, avoiding a signed-overflow test assumption.

Twelve negative controls cover count caching, translation key, UTF-8 overload, unconditional text replacement, the closed-menu condition, animation flags, bone lookup, bottom Y, edge clamping, close short-circuiting, GUID truncation and mouse-coordinate swapping. All twelve final-source controls were rejected by completed differences, with zero incomplete observations.

## Packet preparation improvement

The preparation gate previously rejected two std::basic_string empty-storage template objects emitted as GNU-unique symbols, because it recognized only imported GLIBCXX COPY objects. The narrow addition recognizes exactly the two reviewed unsigned-int and unsigned-short instantiations in this original image.

It requires matching original ELF/DB identity, exact names and addresses, both symbol tables, GNU-unique STT_OBJECT binding, 32-byte writable non-executable BSS storage, no COPY relocation and SHA-256-verified pinned basic_string.h/basic_string.tcc declarations and definitions. It synthesizes no game declaration and changes neither objdiff nor acceptance gates. Missing, altered or unlisted evidence remains a preparation error.

All **122 offline packet-context tests** pass, including 28 individual evidence-corruption variants, missing/changed header checks, both valid template identities and interior references. A fresh original-function packet was then generated without gaps.

## Non-BMP dependency limitation

The four-byte UTF-8 probe exposed a pre-existing bug in pinned CEGUI 0.6.2: encoded_size(utf8*, len) advances four bytes while reducing the remaining count by only three, causing an overread and nondeterministic trailing code points. Such comparisons are not used as acceptance evidence. The final fixture tests real BMP UTF-8 and separately records non-BMP wide arguments at the converter boundary while returning a controlled ASCII token. This explicitly does not establish real non-BMP CEGUI rendering. Library source is unchanged.

## Full validation

An initial full Stage rejected a newly emitted weak Ogre::UTFString::assign definition without its own evidence. Keeping the template implementation inline avoids adding that unproved replacement; gates are unchanged. The revised complete tree passed fresh full Stage validation: 180 tests, zero failures. After transactional publication, an independent root check also passed all 180 tests with zero failures. The accepted total is **1300 of 5247 game functions, 873894 original bytes**: 1255 normalized MATCH and 45 behavioral acceptances. This is function 29 in the large-function recovery series. No standalone playable-game or universal exception-equivalence claim is made.
