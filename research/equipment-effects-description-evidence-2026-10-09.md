# Equipment effects-description evidence upgrade, 2026-10-09

CEquipment::effectsDescription(EEFFECT_ACTIVATION, bool, bool), original 0x88b180, 4048 bytes. The complete original assembly and cleanup paths were reviewed against the existing implementation. This work upgrades its legacy regression to strict executed-function comparison evidence; it does not rewrite the production body.

The lazy Damage translation is retried while empty. Passive positive elemental bonuses reload values after translation callbacks, then append type and damage text. Nonembedded descriptions filter socketable and random-magic-socketable units. The effect-manager receiver is reloaded after type callbacks. Socket-only descriptions retain the initial count, capacity-based first-element fallback, recursive embedded calls, per-entry newline trimming, socket color markup and final newline.

6720 completed original/candidate comparisons, zero differences or incomplete observations. Cases cover cold/warm calls, activation and both flags, positive/zero/negative bonuses, missing/replaced effect managers, empty/multiline/Unicode descriptions, empty translations, socket-list/elemental-vector mutations, self-reference with nonrecursive child flags, color changes and reduced logical capacity.

The fixture invokes the exact original/replacement pointers and observes the returned wide string. It also compares ordered calls, full initialized equipment/global/service buffers, every initialized elemental element, socket identities/count/capacity/growth, and collaborator-produced descriptions. Pointer canonicalization is restricted to named fields and container storage. Internal allocator state and universal exception behavior are not claimed.

The unchanged candidate is 3979 bytes, normalized DIFF, with no unknown original references. All fifteen independently compiled deliberate faults were rejected by completed differences, with zero incomplete observations. Strict full Stage and independent root validation each passed all 192 tests. Acceptance is 1310/5247 functions, 914548 original bytes: 1255 MATCH and 55 accepted by differential self-test.
