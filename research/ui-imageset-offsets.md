# UI imageset offsets and autoscale (U07)

Pinned inputs (read-only, never copied into the repo):

- `libCEGUIBase.so.1` from the installed game
  SHA-256 `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`
- `CEGUI::Image::setHorzScaling @0xe59e0` (vert twin +`0x80`), alignment
  constants `+0.5 @0x1d6c6c` / `-0.5 @0x1d6c68` (f32 reads from the shipped
  rodata), native-resolution constructor immediates `640.0 @0x44200000` /
  `480.0 @0x43f00000`.
- Upstream CEGUI tag `v0-6-2`: `src/CEGUIImageset.cpp`
  (`defineImage` scaling factors, `notifyScreenResolution`,
  `updateImageScalingFactors`, offset-free stretch in `Imageset::draw`) and
  `src/CEGUIImage.cpp` (`Image::draw` offsets dest by the scaled offset
  before delegating to the imageset draw).
- pak: 36 imagesets (all declare NativeHorzRes/VertRes; 2 WindowsLook sets
  are not autoscaled), 34 images with XOffset/YOffset.

## Applied

- Parse: per-image XOffset/YOffset (signed; routinely negative) plus
  per-imageset NativeHorzRes/NativeVertRes/AutoScaled into `UiImage`.
  Missing native res falls back to the ASM-pinned 640x480 (unreachable on
  shipped data — all 36 sets declare it).
- Render: the destination rect is shifted by the scaled offset BEFORE
  clipping (`GlesUiRenderer::draw_image`), mirroring `Image::draw`.
  Factors are screen/native per axis when auto-scaled, else 1.
- Alignment is the vendored round-half-away-from-zero
  `(float)(int)(v + (v > 0 ? +0.5 : -0.5))`, including its NaN/inf edge
  (INT_MIN via explicit code — `cvttss2si` is UB in C++). It is NOT
  `floor(x + 0.5)`: negative offsets (-5, -8, -10) prove the difference
  ((-8.5) truncates to -8, floors to -9).

## Worked examples (also locked in `original_ui_imageset_offsets`)

- `GuiLook/WindowLeftEdge` XOffset=4 at 1920x1080: 4×1.875=7.5 → 8.
- `GuiLook/WindowRightEdge` XOffset=-5 at 1920x1080: -9.375 → -9.
- `GuiLook/MouseTarget` (-8,-8) at native: (-8,-8).
- `WindowsLook/MouseMoveCursor` (-10,-10), non-autoscaled: raw at any res.

## Open

- Scaled image DIMENSIONS (`scaledWidth/Height`) are parsed nowhere yet:
  our dest rects come from layouts, but Falagard image-dim sizing will need
  them (U09).
- Cursor hotspot application: the port draws no software cursor (U25), so
  the Mouse* offsets currently shift nothing visible; they are stored and
  covered for the day a cursor path exists.
- Editor-copy imagesets (`editimages/`) load like the rest (pre-existing
  port behavior, unchanged); whether the original SchemeManager touched
  each one is still open per the deep-map audit.
