# UI font load flags + metrics (U14)

Pinned inputs (read-only, never copied into the repo):

- `libCEGUIBase.so.1` from the installed game
  SHA-256 `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`
- `CEGUI::FreeTypeFont::updateFont @0xe07b0`, `rasterize @0xe1500`
  (symbol addresses verified against the shipped library; the UI-deep-map
  ASM bundle matches it instruction-for-instruction on sampled blocks).
- pak fonts: `media/UI/Serif*.font` + `media/UI/BRLNSDB.TTF` (AutoScaled,
  AntiAlias, sizes 11/16/… at native 1024x768, DPI 96).

## Applied: load flags 0x20 (original-code)

`updateFont` loads every preloaded glyph via `FT_Load_Char(face, index,
0x20)` — `mov edx,0x20` at `0xe0997` before the call at `0xe099f`, inside a
`FT_Get_First_Char`/`FT_Get_Next_Char` loop that also records advances and
the max codepoint. `0x20` is `FT_LOAD_FORCE_AUTOHINT`. The port used
`FT_LOAD_DEFAULT` (0) and now passes `FT_LOAD_FORCE_AUTOHINT`.

Relevance on real UI data (system FreeType 2.14.3, BRLNSDB at 11px/16px,
DPI 96): 213/215 sampled glyphs differ in bitmap, ~112/215 in advance
between the two flags. The old port output was wrong, not merely unproven.

Regression: `original_ui_font_load_flags` renders sampled UI glyphs through
the port and through direct system-FreeType with 0x20 and requires equal
advance/bearing/bitmap, plus at least one DEFAULT-vs-0x20 difference
(non-vacuity). Negative control verified: with the old flag the test fails
on the first advance comparison. Same-library comparison only — this does
NOT claim raster parity with the bundled FreeType build.

## Deliberate non-change: advance formula (proven identical)

The original stores per-glyph `advance.x(int32) * x_scale` where `x_scale`
is the f32 constant at lib offset `0x1d839c` = `0.015625` (1/64, read from
the shipped library rodata). The port computes `advance.x / 64.0F. For an
exact power-of-two scale both are the correctly-rounded quotient, hence
bitwise identical (barring over/underflow/NaN, which the port rejects
upstream). Verified numerically; left untouched on purpose.

## Open: scalable face metrics (needs a live CEGUI object or font-test)

`updateFont` also derives three stored metrics (offsets `+0x278/+0x27c/
+0x280`) as `(float)units * factor`, where the per-metric words are the
`FT_Face` `units_per_EM+2/4/6` shorts (`ascender @+0x8a`, `descender @+0x8c`,
`height @+0x8e` — layout verified against LP64 `FT_FaceRec`) and
`factor = (float)(qword at face+0xa0]+0x28) * (1/64) * (1/65536)`
(`mulss` chain at `0xe08f9/0xe090a`; constants `0x1d839c = 1/64`,
`0x1d83a0 = 1/65536`, both read from the shipped rodata).
`face+0xa0` is `face->size`, but `+0x28` into `FT_SizeRec` does not land on
a documented field for any FreeType 2.x LP64 layout tried
(`y_scale` sits at `size+0x20`), so the qword's meaning is UNRESOLVED —
no formula is ported from this block. The port keeps FreeType-computed
`size->metrics` ascender/height. Resolving this needs either a live
`FreeTypeFont` object under the shipped library or a targeted font
differential; recorded here so nobody re-derives it from scratch.
`FT_Set_Char_Size` truncation (`cvttss2si` both axes) and DPI 96 already
match the port (`research/ui-font-dpi.md`).

## Not in this pass

Eager glyph preload loop (port stays lazy), atlas growth (U15), word-wrap
(U16), vendor `|c`/`|u` markup (U13), per-glyph render-mode branches.
