# Menu-layout screen scale (U06 extension)

## Finding

The port left every menu layout except bottomhud unscaled ("unknown
policy"), while fonts scale per-axis. On the main screen this mismatches
boxes and text as soon as the aspect leaves 1024x768.

All five controller-menu `createMenus` in the shipped ELF call
`CGameUI::convertToScreenScale(window, false)` (`xor edx,edx` + call):

| Menu | Call site | Layout (resource-derived 1:1) |
|---|---|---|
| `CMainMenu::createMenus` | `0xc52bd5` | `mainmenuframe.layout` |
| `CNewGameMenu::createMenus` | `0xc5d8f5` | `charactercreate.layout` |
| `CContinueGameMenu::createMenus` | `0xc4067d` | `characterload.layout` |
| `COptionsMenu::createMenus` | `0xb881ad` | `optionsmenu.layout` |
| `CSettingsMenu::createMenus` | `0xbd705d` | `settingsmenu.layout` |

`false` selects the YRATIO branch (height/768) for both axes — uniform,
aspect-preserving scaling. The menu→layout pairing is resource-derived
(class/layout names and contents plus the port's page mapping); the
per-menu call itself is original-code ASM.

## Port

`ui_screen_scale_for_layout` covers the five layouts (all YRATIO);
`Frontend::frame` resolves through the policy. `loading.layout` stays
unscaled (no call site found — open, not invented).

Font aspect behaviour is NOT changed here: upstream v0-6-2
`FreeTypeFont::updateFont` scales axes separately
(`hps *= d_horzScaling`, `vps *= d_vertScaling`), verified in
`src/CEGUIFreeTypeFont.cpp` and matching the vendored scale-factor
multiply at `0xe0de0`. Non-uniform glyph aspect at non-native aspects
is original behaviour; the visible defect was unscaled boxes under
scaled text, fixed by the layout side.

## Regression updates (both encoded the unscaled bug)

- `frontend_menu_resources`: the 512x384 CopyrightInfo expectation is now
  exactly half (235.0 = 470 × 0.5; YRATIO is exact at this size).
- `gles_ui_headless`: the YRATIO-scaled background covers the viewport at
  any size, so the 512x384 corner is solid blue like native — the old
  "blend zone" expectation described unscaled sampling.

## Open: menu background (U02)

`CGameClient::loadMenuLevel @0x584b80` chains setCurrentDungeon → new
`CLevel` → resetGameSeed → getLevelTemplateDataForDepth → loadRoomLayout →
activate → setProjectorPass → refreshLighting → camera setPosition/lookAt →
cursor/music/setInited. A background needs menu-state level loading plus
scene-behind-menu composition (U01) plus cameras — a multi-pass feature
on its own, not stubbed here.
