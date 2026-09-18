# Menu hover/click/exit handlers (56 fns, 5 families)

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Status: call-census over all 56 (objdump to next symbol) + 6 fully read;
wired=false everywhere (no hover/click slot system in port); compared=false.
Full census: `/tmp/opencode/handler-census.txt` (regenerate with the packet
command; not committed).

## 1. Clusters (census-verified shapes)

- **MouseThrough ~5-insn clear** ×10: two byte-clears at per-menu offsets +
  `return 1` (e.g. inventory `+0x9160/+0x9161 = 0`). Records "no hover".
  Exception: `CGameUI::handle_MouseThrough @0xa83e20` also calls
  `CSkillMenu::clearSkillTooltip`.
- **MouseOut ~38-insn hide** ×6: `getEquipmentInSlot` + `ISA` + one
  `setVisible` + per-menu store (e.g. `+0x1020` inventory). Reward variant ×2
  (`getRewardItems`, stores `+0x1e0/+0x170`). Trivial `return 1` ×2
  (`CGameUI @0xa83680`, skill `@0xbd8870` — 4 bytes each).
- **MouseOver item-hover ~150-210 insns** ×6: `getEquipmentInSlot` + `ISA` +
  CEGUI tooltip/glow/move/reparent writes (feeds what `updateLayout`
  rebuilds). Reward variant ×2. Skill `@0xbd8840` (12 insns): window+`0x1d8`
  → `menu+0x40`, `+0x3b = 1` ("record hovered skill").
- **onClick trivial forward** ×12 (12–15 insns): guard `args+0x28/args+0x10`,
  read window+`0x1d8` back-pointer enum, virtual dispatch into the menu's
  `onClick(ELayoutFunction)`. Exception: dropdown `@0xb194e0` (131 insns,
  `StringConvertToWide` — converts a label, body unread).
- **ExitButton closeAll** ×7 (frontend menus): guard, `gameui+0x40 → +0x12f9
  = 1`, `CGameUI::closeAll()`, return 1 (read: Die `@0xb060c0`). Simple
  `+0x32`-store variant ×4 (dialog-internal close, bodies unread).
  `CQuestDialogMenu @0xba5490` is NOT an exit: `acceptQuest` + `broadcastEvent`
  + `broadcastAcceptedOrDeclined` (34 insns) — campaign-relevant, queued.

## 2. Port verdict

No callers: the port has no hover tracking, no clickable slots, no panel
Close/Exit buttons; frontend-menu buttons travel through `Frontend`, not
these handlers. Nothing to wire; nothing changes. When clickable slots land,
the hover trio + `onClick` forward become the dispatch contract (shapes above).

## 3. Open

- 50/56 bodies unread beyond census (calls/stores/insn counts only).
- Dropdown `onClick @0xb194e0` body; quest-accept `@0xba5490` (campaign).
- `+0x12f9` flag and `closeAll` body unrecovered.
