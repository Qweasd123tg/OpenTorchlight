# Complete updateIngameUI draft: validation status

RecoveredPhases.h now contains the complete top-level draft:
updateIngameUIDraft -> localizedLabels -> Frame::run. There is no fallback to
original updateIngameUI and no registered production hook. It uses the original
ABI/layout and native service symbols. This is NOT an accepted replacement.

## Compared against the original

- first-use localization, retry after an exception at each of four translations,
  ASCII/Cyrillic/CJK output and subsequent cached frame
- input/radio state, floating-window placement and cinematic early return
- no-character and controlled active-character frames
- service-menu opening/retirement with already-localized strings and closing
- player HP/mana/XP, pet HUD, level/messages, per-frame menu updates
- camera/text events, console/final tail and queued tips
- existing item/actor label visibility and positioning
- label creation, sizing, text and color priority across 80 two-frame cases
- performance overlay gates, counter reset/division and text across 240 cases

The latest combined run on this complete draft passed 12 tests / 15,543
original-compared cases. This is the research comparison suite, NOT the main
production integration/acceptance suite. No production hook was added.

## Remaining validation/integration work

1. Dedicated visible hover-target text/health and cache/safe-pointer cases
2. Quest/fishing branches and merchant-close dragged-item return
3. Retirement lazy empty-string retranslation and exception behavior
4. Performance room-name path with a character and nontrivial resource lifetimes;
   current tests use no-character frames, empty/null-resource mesh entries
5. Additional label-creation callback/window replacement and exceptional paths
6. Reuse fine-grained HUD/menu callback fixtures against the shared implementation
7. Full combined regression on the final source, then allocation checks
8. Review source structure and integrate through existing ownership/acceptance

Known fixture correction: named setting IDs begin uninitialized in the pre-main
harness. Visible-label and performance fixtures now assign distinct IDs before
comparison. Without this, a test can accidentally exercise the wrong setting.
Both corrected fixtures pass. This was a test-fixture issue, not a production fix.

Assembly review found distinct CEGUI string-constructor overloads: label extent
uses byte-widening, displayed text uses UTF-8 decoding. Cyrillic creation tests
caught the wrong displayed-text overload; it is fixed. Hover description's call
site uses the same UTF-8 overload and was corrected, but visible hover remains
unverified as listed above.

Main accepted baseline: a1d05cc, 148 integrated tests, 1311 accepted functions.
This draft changes none of those totals. Original binary/assets remain external.
