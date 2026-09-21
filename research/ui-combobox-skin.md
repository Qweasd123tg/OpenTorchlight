# Settings Combobox: Falagard render contract

Reviewed 2026-09-21. This is the render half of the bounded production chain
in [ui-combobox.md](ui-combobox.md); it does not extend that document's input,
keyboard, sorting or overflowing-list boundary.

## Read-only inputs

| input | SHA-256 |
|---|---|
| `lib64/libCEGUIBase.so.1` | `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa` |
| `lib64/libCEGUIFalagardWRBase.so` | `f336dbc15357be833d19c62ad597046cc028c8de5411b554dda6d0aa7f9bcdfe` |
| `pak.zip` | `8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8` |
| `media/UI/GuiLook.looknfeel` | `2cc118a13f7421c8f1e9d5b25f29f4b7962042898110a5e71b333b2b8766ef43` |
| `media/UI/GuiLookSkin.scheme` | `006c21ae3754dea3638ff9233701d4e815b656cc415fd60823ec5c53ff1cddc0` |

The ELF files and archive were only read. Addresses below are virtual
addresses in these exact shipped libraries.

## Window renderers and states

`resource-derived`: `GuiLookSkin.scheme` maps the three participants as:

| type | renderer | look |
|---|---|---|
| `GuiLook/Combobox` | `Falagard/Default` | `GuiLook/Combobox` |
| `GuiLook/ComboEditbox` | `Falagard/Editbox` | `GuiLook/ComboEditbox` |
| `GuiLook/ComboDropList` | `Falagard/Listbox` | `GuiLook/ComboDropList` |

The parent Combobox `Enabled` and `Disabled` states contain no sections. It
therefore contributes no imagery; its three real autochildren are the render
consumers. The portable compiler admits this known instantiated family without
emitting the generic `automatic-children-not-instantiated` diagnostic.

`library-derived`: `FalagardEditbox::render @0x1fa90` chooses `Disabled` after
`Window::isDisabled` (`0x1fac0..0x1fac7`), otherwise reads the Editbox read-only
byte at `+0x730` and chooses `ReadOnly` or `Enabled`
(`0x1fac9..0x1fae2`). It renders that StateImagery first
(`0x1fbb9..0x1fbdb`), resolves named area `TextArea`
(`0x1fcaf..0x1fcc2`), resolves the inherited font (`0x1fd0a..0x1fd18`) and
caches unselected text with `TextFormatting=0` / LeftAligned
(`0x20191`, `0x202fd..0x20319`). The portable read-only path consequently
emits images before one text draw, uses runtime `Text`, inherited/default
`Serif`, `NormalTextColour`, effective alpha and a clip intersected with the
resource TextArea.

`resource-derived`: ComboEditbox `TextArea` is left `10`, top `5`, right
`width-15`, bottom `height-5`. Both `Enabled` and `ReadOnly` render
`ComboboxEditLeft` in `container_left` followed by `ComboboxEditMiddle` in
`container_normal`; `Disabled` uses the same sections modulated by
`FF7F7F7F`. `NormalTextColour` is `FFFFFFFF`. Selection and caret sections are
not rendered for the production read-only state.

`library-derived`: `FalagardListbox::cacheListboxBaseImagery @0x24520` chooses
`Enabled` or `Disabled` and renders it at `0x24602..0x24623` before list items.
`FalagardListbox::getListRenderArea @0x248e0` selects one of
`ItemRenderingArea`, `ItemRenderingAreaHScroll`, `ItemRenderingAreaVScroll`,
or `ItemRenderingAreaHVScroll` from actual scrollbar visibility. Current
Settings lists keep both scrollbars hidden, so the portable row geometry uses
the resource `ItemRenderingArea` NamedArea.

`resource-derived`: ComboDropList `Enabled` draws the nine ItemTooltip frame
pieces: four corners, four edges, and `ItemTooltipMiddle`; `Disabled` applies
`FF7F7F7F`. `ItemRenderingArea` subtracts the actual left/right/top/bottom edge
image dimensions rather than a hard-coded inset.

## ListboxTextItem rows

`library-derived`: `FalagardListbox::render @0x24650` renders the base imagery,
iterates the item vector (`0x247bd`), intersects each item rectangle with the
list area (`0x24842`) and invokes the item's draw slot at `0x248c0`.
`ListboxTextItem::draw(RenderCache,...) @0x1596a0` in `libCEGUIBase.so.1`
draws selection imagery only when both the selected byte `+0x178` and selection
brush pointer `+0x1e8` are nonzero (`0x1596c6..0x159729`). It then resolves the
font and caches left-aligned text (`0x159729..0x159800`) using the item's colour
rectangle and effective alpha.

`original-code`: as recorded with exact Settings call sites in
[ui-combobox.md](ui-combobox.md), the three item loops set pink selection
colours but never set a selection brush image. The brush condition therefore
prevents highlight imagery in this production chain. The portable row draw is
white Serif text, vertically centred within the item rectangle, clipped to the
same immutable list area, and alpha-modulated. Selected and hovered state do
not manufacture a rectangle or image.

## Portable verification boundary

`tests/ui_combobox_skin_test.cpp` checks the original archive mapping and
resources: empty parent imagery, read-only editbox state and image-before-text
ordering, exact TextArea dimensions, nine-piece DropList frame, resource
ItemRenderingArea and a white alpha-modulated row with no selection brush.
The focused contract has 12 assertions. This is a scalar/resource test; no UI
click, frame comparison or end-to-end scenario was run for this review.

The implementation does not claim editable selection/caret rendering,
password masking, scrollbar-visible NamedAreas, arbitrary ListboxItem
subclasses, selection brushes, sorting, multiselect or the whole Falagard
plugin.
