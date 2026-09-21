# Inventory: original event logic and opt-in resource preview

Status: `original-code` event/tab algorithm with explicit library adapters;
`resource-derived` static layout; **not** original animated inventory rendering.
ELF SHA-256:
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Original inputs remain external/read-only. No original process is launched.

## What changed

`CInventoryMenu::mapEventHandlers @0xb4f1b0` (0x3b2 bytes) now has a production
consumer in `UiInventoryPreview`. Child count is sampled at entry; children
are visited in array order before the parent. Exact `onClick` presence and one
nonempty property read cause a MouseButtonDown subscription; unknown names,
whitespace and a NUL-only value still subscribe. There is no type, visibility
or recognized-command gate here, nor deduplication on repeated mapping.
Local property/subscription errors are swallowed (`b4f523..b4f530`); recursive
traversal is outside that catch. The original subscriber is a virtual member
pointer `0x59`, vtable slot `+0x58` -> `handle_onClick @0xb458d0`.
This is **not** CGameUI's mapper: that one catches/logs Ogre::Exception.

`onClick @0xb4f570` (0x451 bytes) gates on open and commands 14/15/16. For
each recognized command the port follows the original order:

1. Set selected state Backpack/Spell/Fish (exactly one true).
2. Set visibility Equipment/Spells/Fish (exactly one true).
3. Clear this tab's flag `+0x91a8/+0x91a9/+0x91aa`.
4. Restore this tab's saved `UnselectedImage` (`+0x91b0/+0x9260/+0x9310`).
5. Request `updateLayout`; full icon/tooltip update remains open.

The production state feeds radio imagery and descendant visibility in the
preview. Default/saved images come from immutable original properties; this
preview does not yet raise item-alert flags or replace their images. Restoring
an unmodified default is not proof of the alert lifecycle. Exceptions from the
tab sink propagate; onClick has cleanup but no catch-and-continue branch.

Fresh `setOpen(true)` resets both selected and visible groups to Backpack
(`b4edf9..b4ee4a`). Previously the port's tab enum survived close/reopen, which
was a real missing state transition. Repeating true while open keeps the tab.

## Explicit Close and presentation boundaries

Installed `media/UI/inventorymenu.layout` has 98 windows and just three onClick
properties (the tabs). Close is separately subscribed in createMenus
`0xb5926a`; its handler `0xb4d920` clears four drag safe pointers and sets
`+0x62`. `processInput` consumes that request via virtual setOpen(false).
The preview has no drag runtime: a left-down on Close uses the existing
single-writer close path, without claiming safe-pointer cleanup or complete
processInput equivalence. Right-click, item actions, rotation and tooltips are
not implemented by this preview. Hidden old list keyboard actions are disabled
in this mode so Enter/U/1..4 cannot silently change the character.

The preview uses original images, XML geometry and YRATIO. It is enabled only
by `--inventory-ui-preview 1`, has an explicit on-screen warning, and leaves
the old working inventory available with the default value 0. UI targets are
clipped and ordered by paint order; only visible/enabled targets dispatch. The
existing port's modal pause policy is unchanged, not declared original.

Original `update @0xb4f9d0` overwrites XML geometry after updateAnimation and
Entity::_updateAnimation. With actual model and animated tag positions:

```text
Top.x    = W/2 + scaledY(model.x + tag_topinventory.x)
Top.y    = H/2 - scaledY(model.y + tag_topinventory.y)
Bottom.x = W/2 + scaledY(model.x + tag_bottominventory.x)
Bottom.y = Top.y
```

Writes occur at `b4ff5c` and `b5006a`. Static layout `{{1,-390},{0,0}}` is
**not** evidence of final IDLE coordinates. Wardrobe model/frame/animation,
paperdoll viewport, item icons, translations, money refresh, complete window
reparenting/z-order and CEGUI event/lifetime/exception behavior remain open.
No made-up background or model position fills these gaps. The preview is an
input/resource checkpoint, not a visual-completion claim.

## Reproducible checks

`tests/compare_inventory_events.py` first ran against native code alone before
the port was written; then compares the same bodies with the C++ probe:
81 trees / 1926 nodes and 198 tab cases (open/closed, commands -1..97).
Property read/subscription order, virtual subscriber encoding, tab calls,
flag write timing and saved-image pointer selection are checked. CEGUI calls,
allocation and updateLayout are synthetic adapters. Native exception unwind
and connection ownership are explicitly excluded; fault injection checks the
portable catch/propagation boundary separately.

`inventory_events_test` also checks fresh/repeated open, actual original
layout, three resolutions, image states, pointer hit regions, disabled Close
and hidden descendants. `inventory_ui_render` drives the shared application
with real left-down input: HUD open, tabs, off-target releases, resize, Close,
Esc and reopen. It checks 21 gameplay fields unchanged, including inventory,
equipment and attributes after attempting hidden legacy controls. Captures
are port regressions, **not** original-game golden frames.

```sh
cmake --build build --target torchlight_desktop --parallel 2
./build/torchlight_desktop /path/to/Torchlight/game \
  --inventory-ui-preview 1 \
  --save-dir ./build/inventory-preview-saves \
  --settings-dir ./build/inventory-preview-settings
```

New Game → enter Town → I (or HUD InventoryButton) → click three tabs → resize
→ Close → I → confirm Backpack selected again. Paths above isolate this manual
session from ordinary port saves/settings; original game files remain inputs.
Next visual dependency is the original animated model/tag path, not tuning
XML coordinates until they look plausible.
