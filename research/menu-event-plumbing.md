# Menu event plumbing: `handle_CloseButton` (23) + `mapEventHandlers` (11)

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Status: representatives analyzed; family NOT uniform (deltas below);
wired=false everywhere (no clickable panel buttons in port, no subscription
phase — the port resolves callbacks at click time). Compared=false.

## 1. `handle_CloseButton`: shared skeleton + real deltas

Skeleton (all three read): `if (args+0x28 != 0) return 1; ...; return 1`.
Never returns 0; never touches CEGUI visibility directly.

| Member | Address | Body after guard |
|---|---|---|
| CInventoryMenu | 0xb4d920 (0xe8 B) | 4× `CRunicCore::removeSafePointer` on the `+0x70 → +0x1920` object (slots `+0x1f8/+0x1e8/+0x1c8/+0x1d8`, each nulled); `menu+0x62 = 1`. NO `setOpen` call. |
| CMerchantMenu | 0xb68ca0 | `menu+0x62 = 1`; `CCharacter::setTarget(null)` on `+0x70 → +0x38`. NO `setOpen` call. |
| CSkillMenu | 0xbd87d0 | flag bytes `+0x3a/+0x3b` machine + **virtual `*+0x40` call** (the `setOpen` slot) — i.e. skill Close DOES drive `setOpen(false)`; no `+0x62` write seen. |

Consequences: inventory/merchant Close = cleanup + `+0x62` marker (close
animation presumably consumed in per-frame code outside the dumps we hold);
skill Close = real close. The family cannot share one executor body — delta
is structural, not parametric.

`+0x62` (inventory/merchant) has NO reader in any dump we hold (`setOpen`,
`update`, `onClick`, `mapEventHandlers`, `updateLayout`, `toggleInventory`
all grepped): writer without a recovered consumer. Recorded, not modeled.
Port impact: none — no Close-button caller exists in the port, and the
`setOpen(false)` path it would feed is already wired via ESC/I/K/J.

## 2. `mapEventHandlers`: recurse + subscribe `handle_onClick`

`CInventoryMenu::mapEventHandlers @0xb4f1b0` (full 196-line dump read):
recurse into child windows (`+0x78/+0x80` range); build `String("onClick")`
(rodata `0xfe4840`, 7 chars); if the property is present AND non-empty,
allocate a `MemberFunctionSlot` (`this+0x18`, vptr `0xfefcd0`, id `0x59`)
and subscribe it through the window EventSet (`call *+0x10`, table
`0x14247e0`) — this is the menu's `handle_onClick`, which routes into the
`onClick(ELayoutFunction)` chain from boundary 34. Windows without `onClick`
get nothing. CEGUI `String::grow`/SSO/exception paths are mechanical.

Port comparison: the port has no subscription phase — `ui_layout` keeps the
verbatim `onClick` string per widget and `hud_press_callback` matches it at
click time. Same vocabulary, different mechanism (pull vs subscribe); parity
of the VALUE set is covered by the HUD-dispatch boundary. No port change.

## 3. Open

- Remaining 20 `handle_CloseButton` + 10 `mapEventHandlers` members:
  registered, unread. Expect per-menu cleanup deltas (do not assume the
  inventory shape).
- `+0x62` consumer unrecovered; skill `+0x3a/+0x3b` machine unread in full.
- Subscription id `0x59` / table `0x14247e0` semantics: recorded raw.
