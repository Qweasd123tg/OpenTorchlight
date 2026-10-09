# CSkillFoldout::load recovery, 2026-10-09

## Scope and behavior

Original `_ZN13CSkillFoldout4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE`, address `0xa95530`, 3384 original bytes, pinned ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. Complete assembly, unwind paths and literals were reviewed. Three callback declarations are added from the original symbols and CEGUI member-slot ABI; no class layout change is required.

The loader resolves the wide path and loads a uniquely prefixed CEGUI layout with the original five-argument overload. Full std::string lengths, including embedded NUL, are retained. Always-on-top, disabled mouse passthrough and caller-UI screen scaling precede a column-major 10-by-10 loop.

Each cell looks up SkillIcon plus one-based column and row numbers, subscribes mouse-move, mouse-leave and mouse-button-down handlers, then looks up SkillHotkey with fresh number conversions. The original right-operand-first conversion order is retained by the pinned compiler. Every subscription uses the current object's UI field, reloads the icon receiver, and releases the temporary Connection before the SubscriberSlot. No invented visibility or parent-attachment behavior is added.

## Focused evidence

**48 completed original/candidate comparisons**, zero differences and zero incomplete observations. Every case checks 200 child lookups and 300 subscriptions, across four string patterns, callback mutation on/off, aliasing on/off and three Connection modes.

The fixture compares full ordered calls, callback identities and member-pointer adjustment, dynamic receivers, complete final Foldout bytes with narrow pointer canonicalization, window flags, COW lifetimes and Connection refcounts. The caller UI differs from the object's UI so substitutions are observable. Callback mutation replaces the root, current icon and UI between operations. Long, embedded-NUL and non-ASCII byte strings exercise the original widening behavior.

**68 supplemental expected-exception comparisons** sample 34 early, middle and final collaborator-call positions with mutation on/off, spanning every call kind and loop boundaries. They compare propagation, partial state and string/connection lifetimes, and are excluded from normal successful-call coverage.

All twelve independently compiled negative controls were rejected by completed differences, with zero incomplete observations. The combined strict Stage passed all 185 tests with zero failures. After transactional publication, the independent root check also passed all 185 tests. The 5213-byte candidate is normalized DIFF, not MATCH; no universal exception-equivalence or standalone-playability claim is made. Accepted total: **1303 of 5247 game functions, 888953 original bytes**, comprising 1255 normalized MATCH and 48 behavioral acceptances. This is function 32 in the large-function recovery series.
