# Horizontal settings slider boundary

Status: `resource-derived` geometry and `library-derived` arithmetic/state
selection; static disassembly reviewed, not isolated-original differential or
whole-game input parity. The portable invalid-input guards are port safety.

## Pinned inputs

External read-only `/home/qweasd123tg/Games/Torchlight/game/`:

- `Torchlight.bin.x86_64`: SHA-256
  `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- `lib64/libCEGUIFalagardWRBase.so`: SHA-256
  `f336dbc15357be833d19c62ad597046cc028c8de5411b554dda6d0aa7f9bcdfe`.
- `lib64/libCEGUIBase.so.1`: SHA-256
  `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.

`pak.zip:media/UI/GuiLook.looknfeel`, WidgetLook `GuiLook/Slider`:
`VerticalSlider=False`; `ThumbTrackArea` is the complete parent rectangle.
Child `GuiLook/SliderThumb`, suffix `__auto_thumb__`, has zero left/top,
right `UnifiedDim(.095, RightEdge)` and bottom `UnifiedDim(.95, BottomEdge)`.
These dimensions are evaluated from XML by the same Compiler Area evaluator;
they are not hardcoded geometry in the implementation. Child pixel size is
rounded using the bundled CEGUI round-half-away-from-zero operation.

`media/UI/GuiLookSkin.scheme` maps the parent to `Falagard/Slider`, child to
`Falagard/Button`. Parent Enabled/Disabled render `main` SliderBar (3-pixel
left inset, width minus 6). The thumb uses `UIIcons/sliderthumb` in Normal and
Hover; Pushed references hover; Disabled references normal with FF7F7F7F tint.
Child draws follow parent draws, retaining per-window image/text ordering.

## Formula and addresses

Addresses below are ELF virtual addresses within the named shared library.
FalagardSlider::updateThumb `libCEGUIFalagardWRBase.so @0x32dd0`, horizontal
branch `0x33010..0x330bc`: let W be parent pixel width, T rounded child width,
M maximum, V current value, L/R local track edges. Travel = R-L-T.
Horizontal movement range is `[L/W, (L+travel)/W]`. Thumb X UDim is
`{((travel/M)*V)/W, L}`; Y is `{0, track.top}`.

FalagardSlider::getValueFromThumb `@0x32ae0`, horizontal branch
`0x32cf8..0x32d90`: resolve local thumb X as
`roundAway(W * thumb.x.scale) + thumb.x.offset`, then divide
`(resolvedX-L)/(travel/M)`. Reversed direction would subtract from M.
The implemented public inverse takes the **screen-space left edge of the
thumb**, not the cursor centre: `roundAway(pixel_x-parent.x)/((W-T)/M)`.
It clamps to `[0,M]`; nonfinite/degenerate inputs safely return zero.

Only full-parent-track, horizontal, non-reversed `GuiLook/Slider` with its
single known child is admitted. Other shapes retain the compiler's automatic
children diagnostic. Slider::setCurrentValue `libCEGUIBase.so.1 @0x18a4b0`
clamps ordinary values to `[0,M]`. Slider constructor `@0x18a870` initializes
current 0, max 1, click step .01 (`0x18a884`, `0x18a891`, `0x18a89b`).
Compiler runtime properties are `CurrentValue` and `MaximumValue`, default 0/1.

Input integration is separate: Slider::onMouseButtonDown `@0x18a790`
adds direction times clickStep (`0x18a7f0..0x18a803`), not a cursor jump.
FalagardSlider::getAdjustDirectionFromPoint `@0x32890` compares cursor with
the two thumb edges. Thumb::onMouseButtonDown `@0x197300` captures the local
drag point, and onMouseMove `@0x1973a0` preserves that offset while changing
X scale by local delta / parent width and clamping to the horizontal range.
Capture, repeat scheduling, callbacks and the full CEGUI widget lifecycle
are not implemented by this geometry/compiler module.

The game sets settings sliders' max to 1 and uses direct values:
CSettingsMenu::setOpen `@0xbd5560` music max/current `0xbd5827/0xbd5839`,
sound `0xbd5801/0xbd5813`; update `@0xbd47e0` persists music directly at
`0xbd4e30`, sound at `0xbd4dfa`. No nonlinear audio mapping is inferred here.

## Reproduction boundary

`ui_slider_test` with no arguments checks pure rounding, clamp, maximum and
invalid-input handling. Optional argument `/path/to/game/pak.zip` adds actual
resource geometry at two dimensions, child state/paint order, and rejection
of vertical/reversed shapes. It uses no GL, game startup, saves or UI events.
These are portable regression/resource tests, not a claim of differential
verification against executed original functions.
