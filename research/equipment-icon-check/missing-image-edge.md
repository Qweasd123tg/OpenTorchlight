# Missing icon followed by forced refresh

## Verified scope

This is a headless characterization of original `CEquipment::createIcon`
(0x882e30, 4075 bytes) with controlled CEGUI window creation and image lookup.
It is **not** a successful differential acceptance case or an end-to-end
rendered-game reproduction. Original ELF/asset inputs remain read-only.

When a new icon is created, the original creates a parent and an image child
and stores the parent at Equipment +0x2c8. If a nonempty icon name cannot be
resolved, it returns before attaching the child. A subsequent forced refresh
uses the existing parent's first child without checking whether there is one.
The regular fixture therefore tests the safe, unforced retry separately.

`reproduce_missing_image.py` establishes these observations for case seed 33,
mode 2:

- Original after failed lookup and safe retry: parent exists, zero attached
  children, two windows created, one image lookup
- Forced second call: original exits 139 (captured SIGSEGV)
- Reconstructed forced second call: likewise exits 139

The standalone script checks that the failure exists; its successful script
status must not be mistaken for the function passing a both-crash equivalence
case. The normal acceptance fixture rejects every both-crash case.

## Supporting original evidence

- `CEquipment::createIcon`, especially the early return following image lookup
  and the existing-window path fetching child zero
- `CGameUI::getImageFromImageSet`, 0xa98630: returns null after an unsuccessful
  imageset search (also when the imageset list is empty)
- Original `media/UI/GuiLook.looknfeel` inside `pak.zip`:
  `WidgetLook name="GuiLook/StaticImage"` contains no `Child`/`WidgetComponent`
  declarations that would supply an implicit image child
- CEGUI 0.6.2 `Window::getChildAtIdx` is unchecked vector indexing

This is a reachable-looking failure path, but how often an actual game session
hits a missing icon and then requests a forced refresh has not been measured.
The fixture does not prove rendering, lifetime cleanup or WindowManager state
outside this function. No engine bug fix was applied: the reconstruction keeps
the original behavior. A robustness change should be reviewed separately from
faithful recovery.

## Reproduce

After configuring the normal original-game/toolchain environment, run from
the repository root:

```sh
python3 research/equipment-icon-check/reproduce_missing_image.py
```

The script creates isolated source/test copies under `build-decomp`, uses the
existing headless loader and exits before the game's main. It never opens a
window. It does not modify the normal tests or pipeline.
