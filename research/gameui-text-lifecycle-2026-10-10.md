# GameUI pooled text-event lifecycle, 10 October 2026

Restores four CGameUI functions, 1,601 original bytes total: hideTextEvents (0xa8ee40), returnTextEventObject (0xa8efa0), updateTextEvents (0xa8f100), and addTextEvent (0xa9c2a0).

## Original behavior

Preserves active/free list topology and ordering, first-only removal and pool guard, cached successor traversal, exact NedAlloc allocation boundaries, callback-sensitive list-shell/head rereads, ordered expiry comparisons including NaN, projection arguments and half-width centering, camera sphere visibility, settings gating, and producer arguments. Existing getTextEventObject, projection, and weak CTextEvent::update dependencies remain at their verified call boundaries. No extra subscriptions, renderer, invented mechanics, or replacement dependency implementations are added.

The full accepted gameui.cpp prefix is byte-identical. Header additions declare original methods and settings without changing layouts. addTextEvent compiles to exact MATCH; all 66 prior strong gameui.cpp MATCH symbols remain MATCH.

## Verification

Four strict fixtures pass 183 completed normal original/recovered pairs: hide 29, return 34, update 63, add 57. They cover guarded snapshots, ordered calls, linked topology, callback mutations, allocation timing, zero/NaN filtering, and original producer/update integration subsets. Twelve expected unwind comparisons are separate and excluded from normal receipts.

Seven deliberately incorrect variants are rejected: omitted detachment, wrong free-list guard, incorrect zero expiry, inverted retention flag, half-width sign, sphere radius, and producer flag.

Strict isolated Stage validation and independent root check both pass all 415 headless tests. All prior accepted addresses are retained. Tools, thresholds, ownership, and all prior cases and assertions are unchanged. The existing visible-label fixture required 65 hook sites after updateTextEvents gained a recovered address, exceeding its single 64-entry detour set. Only that collaborator now uses a second bounded set, retaining the exact 63+2 disjoint hook union and all 1,440 paired cases. A deliberately wrong elapsed value is still rejected by the repaired fixture. This is headless comparison evidence, not a claim that standalone or live gameplay is complete.

Accepted gameplay addresses: 2352 / 5247 (2117 MATCH, 235 behavioral). Accepted original code bytes: 1141963. Net increase: 4.
