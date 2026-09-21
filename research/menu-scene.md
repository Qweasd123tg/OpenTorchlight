# Main-menu scene: no-save Town boundary

ELF SHA-256: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
OGRE 1.6.5 SHA-256: `bef109bfdc1210ede92731ead4a2b3fae76a8905f10bac14d5fdb54ae5474c31`.

## Original-code selection

`CGameClient::setGameState`: failed/absent saved-player load reaches
`0x590c2a` (UTF-32 `TOWN` at `0xfa83a8`), `0x590c40` (depth 1),
`0x590c48` (`loadMenuLevel(seed, 1, TOWN)` at `0x584b80`). Existing-player
paths instead use the saved dungeon and depth; this builder implements only
the no-save Town branch.

`CLevelTemplateData::load` reads `MAINMENURULES` (`0xfd7278`) at `0x977265`
and assigns field `+0x6f0` at `0x977272`. `loadMenuLevel` reads that field at
`0x584c91` and calls `loadRoomLayout(..., false, entryType=3, ...)` at
`0x584cbd`. Its null-template fallback also names
`media/layouts/mainmenus/mainmenu_townrules.dat` (`0x585330..0x58537a`).

Resource-derived chain in the external pak:

- `media/dungeons/TOWN.DAT.adm`: STRATA0, one floor,
  RULESET `media/layouts/town/rules.dat`.
- That LEVEL's MAINMENURULES selects
  `media/layouts/MainMenus/MAINMENU_TOWNRULES.DAT.adm`.
- Fixed chunk `1X1SINGLE_ROOM_TOWN`, position zero, resolves to
  `media/layouts/MainMenus/1X1SINGLE_ROOM_TOWN/MAINMENU_TOWN.LAYOUT.adm`.

## Original-code camera contract

`CLevel::loadRoomLayout @0x95f150` calls `getPosition(true)` at `0x9601e6`.
Property Node type 10 (Camera Position) dispatches to `0x960868`, storing
level `+0x188`; type 11 (Camera Target) dispatches to `0x960838`, storing
`+0x194`. Jump table: `0xfd6ad0`. `loadMenuLevel @0x584d9f/0x584db7` passes
those vectors to `Camera::setPosition/lookAt`.

`getPosition(true) @0x9e70ce` calls node virtual slot `+0x200`:
OGRE SceneNode vtable relocation `0x619110` resolves to
`Ogre::Node::_getDerivedPosition`. The port therefore resolves parent
transforms before using marker coordinates. Node IDs in the Town menu are
`8012869437876343262` and `8012869442171310558`, both beneath Group Properties
`8012869433581375966` at `(69,0,14)`. Marker-local positions are respectively
`(73.345703125,2.5,10.848299980163574)` and
`(65.12799835205078,1.0199999809265137,9.146269798278809)`.

`CCameraControl` ctor `0xceb591` stores PlayerCam at `+0x10`, the menu's camera.
`CGame::createCamera @0x5613f0` establishes FOV 35 degrees (`0x56149d`,
rodata `0xfa4814`), near 1 (`0x5614f8`, `0xfa47fc`), far 90 (`0x561535`,
`0xfa481c`), or far 45 for NETBOOK_MODE==1 (`0x56178f`, `0xfa4818`).
OGRE Camera relocations `0x60b458/0x60b468/0x60b478` identify the virtual
setFOVy/setNearClipDistance/setFarClipDistance calls. Auto aspect is enabled
at `0x561506`. These are creation values, unchanged by loadMenuLevel; a full
audit of subsequent projection mutations remains open.

## Port and verification boundary

`build_main_menu_scene` uses existing ADM/layout/mesh loaders and hierarchy
math. `menu_scene_camera` exposes the world-marker selection independently
of GL. The explicit renderer camera pose uses the existing projection math;
the gameplay camera path keeps its previous parameters.

`tests/menu_scene_test.cpp` checks transformed markers, invalid/missing
markers, and projection parameters without graphics. Its optional
`--original /path/to/pak.zip` mode loads the external Town menu, checks the
resource route and exact marker coordinates, and builds room-piece geometry.
These checks prove data flow and the bounded contract, not rendered parity
or execution of the original loadMenuLevel function.

Verified locally with the external pak: both authored contracts and the
resource route passed; the existing geometry builder produced 10 instances
using 10 meshes. New builder, test, and renderer compiled with
`-Wall -Wextra -Wpedantic -Werror`; no graphics calls were executed.

Open: save-dependent themes, menu player/pet, skybox, particles, water,
projector/light passes, and complete original menu lifecycle. The existing
mesh renderer still has its documented shading approximations. Game assets
remain external read-only inputs. No game, GUI, or frame capture is required.

The desktop currently uses this Town scene as its portable default even when
`.otc` saves exist; it does not claim the original save-dependent theme branch.
`run_application` creates the scene once and `DesktopWindow::draw_menu_scene`
draws it before `GlesUiRenderer::draw(..., false)`, preserving the background.
