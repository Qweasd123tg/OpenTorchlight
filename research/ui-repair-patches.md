# UI repair patchset for the exact user-provided large-14

This is a bounded UI repair, not large-15/full-game or CEGUI fidelity certification.
The existing large-14 font, text shadow/outline, checkbox-label, music, settings,
and HUD low-clamp work is retained. Gameplay algorithms and OTC format are unchanged.

## Pinned inputs

- Source archive `OpenTorchlight-gpt-pro-large-14.zip`, SHA-256
  `52311366f94364d94f049df167db5cc4038f61878ef9dc816dd14332677439b9`.
- Original Linux ELF `Torchlight.bin.x86_64`, SHA-256
  `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- Bundled `lib64/libCEGUIBase.so.1`, SHA-256
  `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.
- Bundled `lib64/libCEGUIFalagardWRBase.so`, SHA-256
  `f336dbc15357be833d19c62ad597046cc028c8de5411b554dda6d0aa7f9bcdfe`.

Library identity is pinned by its actual shipped bytes, not a guessed modern CEGUI
release. Original archives, fonts, DLL/SO/ELF files are external read-only inputs;
none is redistributed in this patchset.

## 1. Clipping images rather than stretching visible fragments

`library-derived`, bounded: bundled `CEGUI::Imageset::draw @0xe6f20` calls
`CEGUI::Rect::getIntersection @0xe6f5b` and adjusts the source rectangle for the
clipped destination (`0xe703f..0xe70b8`). large-14 calculated widget clips but
`GlesUiRenderer::Impl::draw_image` ignored them. The new `clip_ui_image` clips the
quad and proportionally adjusts UV coordinates. `has_clip` distinguishes an
explicit empty clip (draw nothing) from an authored PORT element with no clip.
A fully clipped valid texture is handled, not replaced by diagnostic chrome.

This does not port every subsequent operation: original pixel snapping, colour
interpolation, quad splitting, tiled formatting and the entire Falagard engine
remain outside the patch. Numeric tests validate the transferred intersection/UV
geometry, not bitwise execution of the complete original library function.

## 2. Empty original skins and the diagnostic overlay

`resource-derived`: `media/UI/GuiLook.looknfeel`, `GuiLook/ImageButton`, defines
NormalImage, HoverImage, PushedImage, DisabledImage with empty initial values.
An explicit empty image is meaningful and cannot inherit a fabricated gray
rectangle or a different state. Image selection preserves explicit empty values.
Original selected controls no longer acquire the PORT gold selection border.

`prototype`, explicit: supplemental controls and a genuinely missing widget look
retain the existing diagnostic fallback. Known looks and explicit image properties,
even empty ones, do not. This is not a generalized fallback skin for original UI.
The existing technical overlay is now opt-in (`--debug-ui 1`). An empty overlay
draws nothing. Existing inventory/service/skill/quest modal panels and death UI
remain reachable; they are still PORT presentation. Suppressing the technical
header also hides its textual status notices when no panel is open: original
notifications/tooltips are a separate unfinished subsystem.

## 3. Transparent HUD targets and pointer states

`resource-derived`: `media/UI/bottomhud.layout` contains InventoryButton,
SkillsButton, JournalButton, PetButton, QuestButton and OptionsButton whose normal
image may be empty although callback and hit rectangle exist. They must survive
frame extraction. `JournalButton`/`guiToggleJournal` and
`QuestButton`/`guiToggleQuests` are distinct; they are not aliases.

`library-derived` + `resource-derived`: bundled
`CEGUI::FalagardButton::render @0x1eb30` chooses imagery by disabled/pushed/hover
state. The shipped `GuiLook/ImageButton` maps `PushedOff` to its **hover** section,
not its normal section. This patch follows that look for this exact widget type.
Do not generalize its state map to RadioButton, Checkbox, or every custom look.

`prototype`, explicit input bridge: the portable host carries pointer position,
press origin, and release coordinates; a bounded visible/clipped callback hit test
requires press and release on the same enabled target. Presses over HUD targets
are consumed before world-click navigation. This is NOT a port of the complete
CEGUI capture, hierarchy, Z-order, pass-through or double-click pipeline. The
native adapter is Wayland; the scenario adapter supplies deterministic events.

Four callbacks route into existing functionality: Inventory, Skills, Quests and
Options. Inventory/skills/quest panels remain PORT. Journal, Pet, Perks, automap
and other unsupported callbacks are reported, not silently rebound or implemented
with invented gameplay. No pet AI, journal text, skill or NPC service is added.

## 4. Paused settings stay in the frontend

`prototype` / port orchestration repair, not original-code: the old application
branch handled only `FrontendPage::pause`. Switching to `settings` stopped drawing
that page and then fell through to simulation. Both pages are now modal. Their
`apply_settings` request shares the settings persistence handler with the main
menu; it must not trigger an OTC checkpoint. Save commands still explicitly invoke
the existing checkpoint policy. The clock anchor updates while paused, preventing
paused time from becoming one catch-up simulation step.

The scenario writes settings into its temporary output directory, never HOME.
It tests separate HUD press/release events, Inventory opening, unsupported
Journal/Pet reporting, Options -> pause -> Settings -> Apply -> back -> resume.
Time advances inside paused settings; character state is compared before/after.
The normal automatic checkpoint at final quit is expected and is distinguished
from an accidental character save on Apply.

## Reproducible verification

Tests are registered in CMake and picked up by the existing `tools/check.py`
labels; no bypass or softened warning flags is required.

- `ui_image_clip`: authored geometry, empty/invalid clips, proportional UV,
  overfilled bars and ClippedByParent=False.
- `ui_hud_input`: authored hover-only, pressed/off, disabled, clipped hit testing.
- `original_ui_hud_input`: actual supplied HUD resource names, properties and
  distinct Journal/Quests callbacks; resource compatibility, not full event parity.
- `ui_repairs_render`: 12 actual Mesa/EGL frame readbacks. These are authored
  regressions, not original-game screenshots.
- `paused_settings_render`: common application, actual pak, pointer bridge and
  modal settings persistence; no native window is needed by this test.

Example after building with a real external game directory:

```bash
ctest --test-dir build-ui -R '^(ui_image_clip|ui_hud_input|original_ui_hud_input|ui_repairs_render|paused_settings_render)$' --output-on-failure
```

All skips must remain NOT RUN. A successful software GL test is not native
Wayland link/execution, release font quality, or original visual equivalence.

## Recorded run for this patchset (2026-09-17)

Baseline: 60/60 core tests. Patched: 62/62 core and 7/7 render tests, with two
shared labels (67 unique tests); three selected original-resource tests passed
separately (70 unique tests total), no skips. The paused-settings/HUD scenario
executed 32 commands, 38 ticks, 16 scene frames and 19 menu frames; 21 character
state fields remained identical before/after. The existing original-resource
combat and service scenarios also passed. Software renderer: Mesa llvmpipe,
OpenGL ES 3.2, surfaceless EGL. No original game process was started.

The unchanged large-14 renderer, compiled against the new probe/current headers,
fails the new regression with `empty overlay still paints over the game`.
This is a countercheck of the defect in our port, not differential execution of
CEGUI. Native Wayland build/execution, a FreeType-SDK build, sanitizers, and the
complete assets/reference groups were NOT run for this patchset. Do not reuse
old release reports as if those checks ran on these changed files.

## Unfinished original UI: exact next sources

Inventory is not just a list with a textured rectangle. Existing decompilation
`research/decompiled-core/inventory_menu.c` is the next source:

- `CInventoryMenu::createMenus @0xb569e0`: decompilation starts near line 6442;
  inventory mesh load at line 7290 (`media/ui/models/inventory/inventory.mesh`),
  layout load at line 7826 (`media/ui/inventorymenu.layout`).
- `mapEventHandlers @0xb4f1b0`, near line 2580; some event handlers are subscribed
  in code, not encoded by `onClick` in layout.
- `setOwner @0xb45dc0`, line 438; `setOpen @0xb4eb70`, line 2403;
  `handle_CloseButton @0xb4d920`, line 2359.
- `update @0xb4f9d0`, near line 2894; `setSlotIcon @0xb51bf0`, line 3694;
  `updateLayout @0xb53430`, line 4569.
- RotateLeft/Right and their end handlers: `0xb45860..0xb45890`.

These are navigation anchors in the unchanged large-14 decompilation, not proof
that Ghidra's inferred C types are correct. Confirm uncertain fields in the pinned
ELF before implementing. First transfer the data/3D/UI binding and event map;
then check item placement, icon state, rotate/release/close, viewport resizing,
and persistence. Do not invent a new inventory window or claim paperdoll parity
from a layout-only render. Merchant, skills and quest/journal windows require
similar independent resource + controller analysis.
