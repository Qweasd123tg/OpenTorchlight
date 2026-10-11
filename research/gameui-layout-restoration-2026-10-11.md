# GameUI layout restoration — 2026-10-11

Restores three original CGameUI functions in gameui.cpp:

- 0xa83920: mouseOverPanel(int, int), 422 original bytes
- 0xa83ed0: convertToScreenScale(CEGUI::Window*, bool), 370 bytes
- 0xa849d0: sizeComboList(CEGUI::Combobox*), 546 bytes

Original ELF SHA-256:
91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.

Panel hit testing preserves inclusive bounds, rectangle priority, signed-int to
float conversion and the original width/height and coverage calls. Recursive
layout conversion is child-first, captures child count once, reloads storage,
and changes only absolute offsets using the selected scale function. Combobox
sizing preserves dynamic item counts, virtual item heights, visibility-specific
named areas, pixel alignment rounding and floating-point operation order.

## Verification

- Complete final Stage.validate gate: 620/620 tests passed.
- 2,689 accepted functions: 2,157 MATCH and 532 behavioral. Exactly the previous
  2,686 plus these three; every prior acceptance and MATCH is preserved.
- convertToScreenScale is exact MATCH, including verified EH metadata.
- Three new fixtures: 966 completed original/candidate comparisons with zero
  differences or incomplete cases; 36 separately checked expected unwinds.
- Coverage includes boundaries, NaNs/infinities, integer-to-float precision,
  recursive order, repeated and aliased children, callback mutations, dynamic
  item counts, finite cancellation, signed rounding and real CEGUI cleanup.
- Four negative controls fail with completed differences and no incomplete
  cases: exclusive panel edge, swapped width/height calls, mixed scaling axes,
  and removed pixel alignment rounding. Restoring the source passes again.
- Existing skill-load and startup regressions pass unchanged. An initial full
  run exposed same-TU inlining across the scale boundary; a narrow noinline
  annotation restores the original calls. All 12 restored scale consumers were
  audited against original/baseline/candidate assembly, including transitive
  startup helpers. Final acceptance comes from the complete rerun after this fix.
- Final inputs digest:
  4677213039cc810ad5bd6d165f5176472f2a12bf28433be82dbe95063233cf04.
- Final full gate: 1,650.78 seconds using the unchanged two-shard headless setup
  and 1,800-second timeout per shard.

No acceptance tools or guards were changed. Original binary/resources are not
included. The headless gate does not establish live-game playability; no live
window was launched.
