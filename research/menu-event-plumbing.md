# Menu event plumbing: `handle_CloseButton` (23) + `mapEventHandlers` (11)

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Status: representatives analyzed; family NOT uniform (deltas below).
2026-09-20: inventory mapper is now ported/wired/compared in the opt-in
[resource preview](inventory-ui-preview.md); native normal-path comparison,
not complete CEGUI/runtime parity. The current
[CDropdownMenu packet](dropdown-mainmenu.md) adds a reviewed close handler
and its own event mapper; the down subscription is consumed by CMainMenu.

## 1. `handle_CloseButton`: shared skeleton + real deltas

Skeleton (all three read): `if (args+0x28 != 0) return 1; ...; return 1`.
Never returns 0; never touches CEGUI visibility directly.

| Member | Address | Body after guard |
|---|---|---|
| CInventoryMenu | 0xb4d920 (0xe8 B) | 4× `CRunicCore::removeSafePointer` on the `+0x70 → +0x1920` object (slots `+0x1f8/+0x1e8/+0x1c8/+0x1d8`, each nulled); `menu+0x62 = 1`. NO `setOpen` call. |
| CMerchantMenu | 0xb68ca0 | `menu+0x62 = 1`; `CCharacter::setTarget(null)` on `+0x70 → +0x38`. NO `setOpen` call. |
| CSkillMenu | 0xbd87d0 | flag bytes `+0x3a/+0x3b` machine + **virtual `*+0x40` call** (the `setOpen` slot) — i.e. skill Close DOES drive `setOpen(false)`; no `+0x62` write seen. |
| CDropdownMenu | 0xb17380 | pending-close `+0x32`; four GameClient safe-pointer removals/null writes. `processInput @0xb102a0` calls virtual setOpen(false), then clears the marker. |

Consequences: inventory/merchant Close = cleanup + `+0x62` marker (close
animation presumably consumed in per-frame code outside the dumps we hold);
skill Close = real close. The family cannot share one executor body — delta
is structural, not parametric.

Inventory `+0x62` reader is now identified in `processInput`
(`research/decompiled-core/inventory_menu.c:365`): setOpen(false), then clear.
The preview adapts that close request to the existing owner; its absent drag
safe-pointer cleanup is not declared recovered. Merchant is not covered.

## 2. `mapEventHandlers`: recurse + subscribe `handle_onClick`

`CInventoryMenu::mapEventHandlers @0xb4f1b0` (full 196-line dump read):
recurse into child windows (`+0x78/+0x80` range); build `String("onClick")`
(rodata `0xfe4840`, 7 chars); if the property is present AND non-empty,
allocate a `MemberFunctionSlot` (`this+0x18`, vptr `0xfefcd0`, id `0x59`)
and subscribe it through the window EventSet (`call *+0x10`, table
`0x14247e0`) — this is the menu's `handle_onClick`, which routes into the
`onClick(ELayoutFunction)` chain from boundary 34. Windows without `onClick`
get nothing. CEGUI `String::grow`/SSO/exception paths are mechanical.

Inventory now maps subscriptions once at preview creation; the three actual
tab commands retain the prior mapToFunctions binding. Comparison details and
local catch-all versus CGameUI's Ogre-only catch are in the linked report.

## 3. Open

- Remaining 19 `handle_CloseButton` + 9 `mapEventHandlers` members:
  registered, unread. Expect per-menu cleanup deltas (do not assume the
  inventory shape).
- Merchant `+0x62` consumer; skill `+0x3a/+0x3b` machine unread in full.
- Inventory subscription id `0x59` = virtual +0x58; `0x14247e0` =
  EventMouseButtonDown. Full connection lifetime/error behavior remains open.
