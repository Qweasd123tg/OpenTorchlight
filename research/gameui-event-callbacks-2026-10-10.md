# GameUI event callbacks restoration, 10 October 2026

Restores five CGameUI event callbacks, 530 original bytes total: handle_onClick (0xa83690), handle_SkillMouseOver (0xa83820), handle_ToggleItemNames (0xa83b00), handle_MouseOver (0xa83c30), and handle_MouseThrough (0xa83e20).

## Original behavior

Preserves bool virtual dispatch, suppression gates, full 64-bit hover GUIDs, lookup-miss state, mutable settings/key rereads, cached event window/parent with repeated glow rereads, and tooltip callback ordering. Three nonvirtual declarations are added without changing class size or virtual slots. The complete previously accepted gameui.cpp is preserved as a byte-identical prefix. No new subscriptions, mechanics, or dependency implementations are added.

## Verification

SkillMouseOver, ToggleItemNames, and MouseThrough compile to exact MATCH. All 63 prior strong gameui.cpp MATCH symbols remain MATCH. The other two callbacks are accepted through strict differential behavior tests.

Five fixtures pass 596 completed normal original/recovered pairs: click 96, skill hover 168, item-name toggle 48, slot hover 196, and mouse-through 88. They compare return values, ordered collaborator calls, callback-sensitive rereads, repeated sequences, normalized full relevant snapshots, and canaries. Seven separate slot-hover exception-propagation witnesses match, and are excluded from normal completion receipts.

Six deliberately incorrect variants are rejected: lost dispatch return, truncated GUID, cleared lookup-miss state, incorrect negative setting toggle, front/back reversal, and post-callback hover overwrite.

Strict isolated Stage validation and independent root check both pass all 411 headless tests. All prior accepted gameplay addresses are retained. Tools, thresholds, ownership, and existing fixtures are unchanged. Headless evidence does not establish standalone build or live gameplay readiness.

Accepted gameplay addresses: 2348 / 5247 (2116 MATCH, 232 behavioral). Accepted original code bytes: 1140362. Net increase: 5.
