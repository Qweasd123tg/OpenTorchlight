# GameUI click dispatcher restoration, 10 October 2026

Restores CGameUI::onClick(ELayoutFunction), original address 0xa924c0, size 1842 bytes, on the fully verified pass11 baseline.

## Original behavior

All 20 dispatch IDs and default paths are preserved, including pause/menu toggles, automap zoom, item-name settings, pet interaction and departure, pet modes, and asymmetric stat/skill point menu opening. Event 68 preserves callback-sensitive re-reads of dragged equipment, actor, follower, level, and menu pointers. Pet departure retains the exact translated warning and independent lazily initialized string caches. The bool return ABI is established through the original event adapter and CEGUI low-byte consumer.

The original full gameui.cpp definitions are preserved. Three header refinements name established pet-mode/departure fields without changing object sizes or offsets. Existing original call boundaries remain intact.

## Verification

The new normal differential fixture passes 1,111 completed original/recovered pairs, covering all event IDs, default IDs, null/false gates, ordered collaborator calls, mutable callback state, guard bytes, and repeated warm-cache calls. Another fixture compares 24 expected translation/modal exceptions with two successful retries each; these are explicitly excluded from normal completion evidence. Eight deliberately incorrect variants are rejected: consumption, pet mode, zoom sign, item-use argument roles, point threshold, departure gate, warning text, and return value.

Strict isolated Stage validation and an independent root check both pass all 406 headless tests. All prior accepted gameplay addresses are retained. Acceptance thresholds, tools, ownership, and existing fixtures are unchanged. This establishes headless behavior evidence, not standalone build or live gameplay readiness.

Accepted gameplay addresses: 2343 / 5247 (2113 MATCH, 230 behavioral). Accepted original code bytes: 1139832. Net increase: 1.
