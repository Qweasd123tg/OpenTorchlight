# HUD onClick dispatch: `CGameUI::onClick(ELayoutFunction) @0x00a924c0`

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Status: analyzed (machine code) + subset ported/wired; compared=false (no
original-execution proof). Decompilation (`research/decompiled-core/game_ui.c`)
was navigation only; every claim below was checked against the ASM dumps
(`research/disassembly/a924c0.asm`, `a980e0.asm`,
`layout-command-initializers.asm`) or the jump-table/rodata bytes.

## 1. String -> enum (`CGameUI::mapToFunctions @0xa980e0`)

- Recurses into child windows, reads the `onClick` CEGUI property
  (`String("onClick")` at rodata `0xfe4840`), uppercases it
  (`STRINGS::StringUpper`), linear-searches `KLayoutFunctionNames`
  (base `0x14b7dc0`, bound `0x61` = 97) with length-first `cmpsb`.
- Hit at index `i`: stores `this + i*4 + 0x1790` at window+`0x1d8` (the
  back-pointer the batch extractor records). No `onClick`: default
  `this + 0x1910`.
- `KLayoutFunctionNames` is BSS filled by `__static_initialization`:
  97 `(slot, string)` pairs read from `layout-command-initializers.asm`
  (slots `0x14b7dc0 + i*8`, strings in `.rodata`). Full table, index = enum:

```
0x00 GUIEXITGAME            0x20 GUISELECT19           0x40 GUISELECTA
0x01 GUIEXITAPPLICATION     0x21 GUISELECT20           0x41 GUISELECTB
0x02 GUINEWGAME             0x22 GUISELECT21           0x42 GUISELECTC
0x03 GUICONTINUEGAME        0x23 GUISELECT22           0x43 GUISELECTD
0x04 GUINEWGAMEMENU         0x24 GUISELECT23           0x44 GUIFEEDPET
0x05 GUICONTINUEGAMEMENU    0x25 GUISELECT24           0x45 GUIPETPASSIVE
0x06 GUICLOSEMENU           0x26 GUISELECT25           0x46 GUIPETAGGRESSIVE
0x07 GUIBACK                0x27 GUISELECT26           0x47 GUIPETDEFENSIVE
0x08 GUIDECLINE             0x28 GUISELECT27           0x48 GUITOGGLEINVENTORY
0x09 GUIACCEPT              0x29 GUISELECT28           0x49 GUITOGGLEQUESTS
0x0A GUIOK                  0x2A GUISELECT29           0x4A GUITOGGLESTATS
0x0B GUIPAUSE               0x2B GUISELECT30           0x4B GUITOGGLESKILLS
0x0C GUISCROLLUP            0x2C GUISELECT31           0x4C GUITOGGLEPERKS
0x0D GUISCROLLDOWN          0x2D GUISELECT32           0x4D GUITOGGLEJOURNAL
0x0E GUISELECT1             0x2E GUISELECT33           0x4E GUITOGGLEPET
0x0F GUISELECT2             0x2F GUISELECT34           0x4F GUITOGGLEAUTOMAP
0x10 GUISELECT3             0x30 GUISELECT35           0x50 GUITOGGLEOPTIONS
0x11 GUISELECT4             0x31 GUISELECT36           0x51 GUITOGGLEITEMNAMES
0x12 GUISELECT5             0x32 GUISELECT37           0x52 GUIAUTOMAPZOOMIN
0x13 GUISELECT6             0x33 GUISELECT38           0x53 GUIAUTOMAPZOOMOUT
0x14 GUISELECT7             0x34 GUISELECT39           0x54 GUILEVELUP
0x15 GUISELECT8             0x35 GUISELECT40           0x55 GUISTATSUP
0x16 GUISELECT9             0x36 GUISELECT41           0x56 GUISKILLUP
0x17 GUISELECT10            0x37 GUISELECT42           0x57 GUIPET1
0x18 GUISELECT11            0x38 GUISELECT43           0x58 GUIPET2
0x19 GUISELECT12            0x39 GUISELECT44           0x59 GUIPET3
0x1A GUISELECT13            0x3A GUISELECT45           0x5A GUIDELETE1
0x1B GUISELECT14            0x3B GUISELECT46           0x5B GUIDELETE2
0x1C GUISELECT15            0x3C GUISELECT47           0x5C GUIDELETE3
0x1D GUISELECT16            0x3D GUISELECT48           0x5D GUIDELETE4
0x1E GUISELECT17            0x3E GUISELECT49           0x5E GUISETTINGSMENU
0x1F GUISELECT18            0x3F GUISELECT50           0x5F GUIPETSELL
                                                      0x60 NONE
```

## 2. Enum -> action (`CGameUI::onClick @0xa924c0`, 0x732 bytes)

Dispatch head (ASM-verified): `sub $0xb,%esi; cmp $0x54,%esi; ja default;
jmp *0xfe4370(,%rsi,8)`. Range `0x0b..0x5f`; everything else returns 1.
Jump-table targets dumped from `.rodata @0xfe4370` (85 entries):

| Enum | Name | Target | Action (decomp-guided, ASM spot-checked) |
|---|---|---|---|
| 0x0b | GUIPAUSE | a92a18 | `togglePause` (closeAll, flip `+0x1999`, automap/UI visibility) |
| 0x44 | GUIFEEDPET | a92960 | dragged-item use (`performItemUse`) else `togglePet`; `isUseable` + `playSample 0x18` / `queueGlobalSample 0x31` paths |
| 0x45–0x47 | PETPASSIVE/AGGRESSIVE/DEFENSIVE | a92928/a928f0/a928b8 | pet stance marker 0/1/2 (`+0x16c8`, `+0x710`, `setTarget(null)`) |
| 0x48 | GUITOGGLEINVENTORY | a928a8 | `toggleInventory` (unPause; closes other menus when open; closeRight + toggle + moveToFront) |
| 0x49 | GUITOGGLEQUESTS | a92898 | `toggleQuest` |
| 0x4a | GUITOGGLESTATS | a92888 | `toggleStats` |
| 0x4b | GUITOGGLESKILLS | a92878 | `toggleSkill` |
| 0x4d | GUITOGGLEJOURNAL | a92868 | `toggleJournal` |
| 0x4e | GUITOGGLEPET | a92858 | `togglePet` |
| 0x4f | GUITOGGLEAUTOMAP | a92830 | `toggleAutomap` if level != null and `+0x1999 == 0` |
| 0x50 | GUITOGGLEOPTIONS | a92820 | `toggleOptions` |
| 0x51 | GUITOGGLEITEMNAMES | a927f0 | flip `KSETTINGS_TOGGLE_ITEM_NAME` int |
| 0x52/0x53 | ZOOMIN/ZOOMOUT | a927b8/a92780 | `zoomAutomap` with `0xfe5fdc` / `0xfa86d0` consts |
| 0x54/0x55 | GUILEVELUP/GUISTATSUP | a926a8/a92620 | modal-dialog closeLeft/closeRight paths |
| 0x56 | GUISKILLUP | a926f0 | modal-dialog closeRight (+ closeLeft if `+0x45c > 0`) |
| 0x5f | GUIPETSELL | a92518 | pet modal (`g_Pet`/`g_PetCannotDepart` strings) or `sendToTown` + sample `0x2b` |
| else | SELECT*/PERKS/PET1-3/DELETE*/SETTINGSMENU | a925f0 | no-op return (incl. `GUITOGGLEPERKS` — perks dispatch lives elsewhere) |

`toggleInventory` (decomp `game_ui.c:2485`, structure ASM-plausible, NOT
op-by-op verified): `unPause`; if inventory open, `setOpen(0)` the menus at
`+0x4f0/+0x4f8/+0x500` (slot `+0x40`) and stash `+0x508` (slot `+0x20`); if
closed, `closeRight`; then `setOpen(!open)` + `moveToFront`. This matches the
port's I-key interplay shape (opening inventory drops the other panels).

## 3. Port parity (`src/application.cpp` HUD dispatch)

Resource vocabulary (`media/UI/bottomhud.layout`, UTF-16, 14 `onClick`
values): guiAutomapZoomIn/Out, guiPause, guiSkillUp, guiStatsUp,
guiToggleAutoMap/Inventory/ItemNames/Journal/Options/Pet/Quests/Skills/Stats.

| Callback | Original | Port | Verdict |
|---|---|---|---|
| guiToggleInventory | toggleInventory | synthetic I | match (shape verified above) |
| guiToggleSkills | toggleSkill | synthetic K | match (by name; toggle body not yet read) |
| guiToggleQuests | toggleQuest | synthetic J | match (by name; toggle body not yet read) |
| guiToggleOptions | toggleOptions | synthetic ESC | match (by name; toggle body not yet read) |
| guiPause | togglePause (closeAll+flip) | synthetic ESC | match: dispatch runs only with inventory closed, so closeAll is vacuous; ESC with nothing open pauses |
| guiToggleJournal/Pet/Stats | toggle* | `hud_callback_unimplemented` | open: panels absent in port |
| guiToggleAutoMap/Zoom | automap calls | unimplemented | open: no automap in port |
| guiToggleItemNames | setting flip | unimplemented | open: no item-name setting sink |
| guiSkillUp/guiStatsUp | modal paths | unimplemented | open: stat/skill invest lives in the skill panel keys instead |
| (not in bottomhud) | FEEDPET/stance/PETSELL/DELETE/etc. | n/a | other menus' onClick vocabularies; out of scope |

## 4. Open (do not guess)

- `toggleSkill/Quest/Options/Journal/Pet/Stats` bodies: name-level match only;
  read before claiming interplay parity for K/J/ESC beyond clicks.
- Dead-player HUD clicks are dropped in the port (`player_combat.alive()`
  gate); original gating per case unknown.
- `+0x1999` pause flag vs port `FrontendPage::pause`: same role, inferred.
- String bytes of `g_Pet`/`g_PetCannotDepart` (translate IDs `0xfe4fd0`+):
  not decoded; PETSELL stays unported.
