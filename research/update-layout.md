# Panel `updateLayout` family (11 members)

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Status: inventory fully analyzed; merchant skeleton-compared; rest registered.
Compared=false everywhere (no original-execution proof). No code change in
this packet: the data-refresh path already runs per frame and is now
scenario-proven; the presentation refresh has no renderer sink.

## 1. Inventory `@0xb53430` (full analysis, dump `b53430-*.asm` 2338 lines)

Shape: detach-all + rebuild icons/glows/tooltips/z-order. No menu-field
writes (only a CEGUI flag `+0x3e2`); virtual slot `+0x48` (called from
`setOpen` tail).

- Guards: `+0x60 == 0`, `+0x50 == null`, `[+0x490] == null` → return.
- Equipment loop k=0..11 (`getEquipmentRefInSlot`): reparent/reposition icon,
  glow overlays (`goldslotglow` ISA 0x36 / `blueslotglow` / `greenslotglow`),
  socket icons + `onesocketglow`/`twosocketglow`, tooltips; empty slot resets
  to defaults (`+0x1d08`, `+0x5568`).
- Backpack loop **63** iters (`0x13..0x52` — note: `createMenus` builds 64
  slot windows): clear 3 `Image` overlays + label + detach, then `setSlotIcon`
  gated by `inv+0x38/0x3c` counts and a `+0x12` filter.
- Spell loop 4 iters: `getKnownSpell` icons/tooltips, `setText` only clears.
- Tail: `moveToBack(+0x20)`, `moveToFront(+0x48,+0x28,+0x30,+0x38)`.
- NOT refreshed here: tabs/radio/visibility, money/gold value (`Money@+0x9190`
  untouched), paperdoll/model/viewport, stats. No sound/model calls.

## 2. Merchant `@0xb6dc70` (skeleton via call census, 0x10a5 bytes)

Same family shape: `setProperty ×6`, `moveToFront ×4`, `removeChildWindow`,
`setText ×2` (vs inventory ×1 — merchant writes a value text, presumably
gold), `getItemPane ×2`, `setSlotIcon` + `setPetSlotIcon` (pet-slot variant,
matches the 127+64 slot structure from `createMenus`). Full phase map open.

## 3. Port coverage audit (per refreshed element, inventory)

| Original element | Port sink | Verdict |
|---|---|---|
| which item in which slot (equip/backpack/spell lists) | per-frame session render; equip/unequip/buy/learn scenarios | wired (data) |
| money/gold value | session gold render in panel | wired (data; original doesn't refresh it here either) |
| tab states | `InventoryMenuTab` + radio selects in `setOpen` path | wired |
| icons/glows/tooltips/z-order | none (no icon/glow/tooltip renderer) | open, no sink |
| paperdoll/model/viewport | viewport math ported; model absent | partial, see panel-open boundary |

Merchant data path (offers from catalog, gold debit, bottle transfer) is
proven by `application_services_test.py` (47 assertions, 3 processes, PASSED
on real pak/EGL 2026-09-18). Skill invest/cast/journal covered by the same run.

## 4. Open

- Remaining 9 members (Combine/Dropdown/Enchant/Pet/Quest/Skill/Stash/Stats/
  Journal) registered, undumped. Skill/Quest data paths are scenario-proven
  but their `updateLayout` bodies are unread — wired flags stay false there.
- Backpack 63-vs-64 iter/window mismatch: needs a targeted read (off-by-one
  or last-slot-special); recorded, not blocking.
- Field meanings (`+0x348/+0x3e0/+0x3f0/+0x3f4`, ISA 0x36/0x37, `+0x2b0`
  predicate) stay inferred.
