# GameUI text-event pool recovery

Recovered CGameUI::getTextEventObject (0xa9ba60) against the original ELF, on top of the verified 401-definition integration. The original controls all behavior; this is not a new UI implementation.

The implementation preserves new and recycled event allocation, free-list unlinking and node release, active-list insertion, text encoding and repeated assignment, font-based sizing, colors, editor parent selection, initial update and the ordering of animation flags. Existing definitions and SDK acceptance are retained.

## Verification

- 1,920 production-path comparisons and 4,224 callback-mutation comparisons against the original, all completed with no differences.
- 160 matching injected exception unwinds, separately checked and not counted as normal coverage.
- Eight completed negative controls detect deliberate errors in pool release, active-list insertion, width, text encoding, height, alpha, removal and color. The unmodified candidate passes again after restoration.
- Strict isolated Stage validation and independent root check both pass all 386 headless tests.
- The implementation is behaviorally accepted; no byte-for-byte MATCH claim. This headless result does not establish live gameplay readiness.

Root acceptance: 2073 / 5247 gameplay addresses (1847 MATCH, 226 behavioral), 1103960 original machine-code bytes. Net increase: 1 addresses; no prior accepted address lost.
