# Panel open queries: `open()` / `openPartial()` family (20 functions)

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Historical packet: analyzed (machine code) + ported; wired per member (only panels with
a port instance); compared=false (equivalence is by construction, no
independent differential). No code change in this packet: parity holds, proven
below.

Current acceptance: [ui-panel-query-functions.md](ui-panel-query-functions.md)
records four complete `isRight` and four `openPartial` bodies, initialized LO
fields and the production pause consumers. The 1536-case whole-body comparison
supersedes the old `compared=false` claim for those eight getters only.
Ordinary `open()` still needs HI and is not fully implemented by the port's
LO-only `open()` accessor; the historical instant-settle argument below does
not close that original function.

## 1. Machine semantics (all 20 verified by objdump, pattern-identical)

`open()`: `cmpb $0x0,LO; mov $1,%eax; jne ret; movzbl HI,%eax; xor $0x1,%eax`
i.e. `return LO ? 1 : (HI ^ 1)`.
`openPartial()`: `movzbl LO,%eax` i.e. `return LO`.

## 2. Byte roles (inventory proven across three dumps)

- `LO (+0x60 inventory)` = requested-open flag: `setOpen` stores `requested`
  there on the open path (`b4ee67 mov %bpl,0x60`) and clears it on close
  (`b4ec41/b4ec55`). Port equivalent: `PanelOpenState::open_` (stored on
  every path incl. the pet gate). Exact.
- `HI (+0x61 inventory)` = close-settled bit: cleared by `setOpen` close
  (`b4ec3d`), SET by `update()` after the close animation/hide completes
  (`b51396 movb $0x1,0x61` after hide virtual `*+0x50`, `removeChildWindow`,
  `+0x9158 = 0`). Hence `open()` = "visible, including a running close
  animation"; `update()` skips work while `LO == 0 && HI == 0` (`b5020c-216`).
- Port `aux_` is the `HI` slot but is never set: without a close-animation
  sink the close settles instantly, so no observable port state can
  distinguish "closing" from "closed". `open() == open_` holds at every point
  a port caller can observe. If a close-animation sink ever lands, `aux_` must
  be driven by it and `open()` becomes `open_ || !aux_` with `aux_` init true
  (settled-closed). Until then this is recorded, not implemented.

## 3. Per-class offsets (offsets never transfer; roles do)

| Menu | open | openPartial | LO/HI |
|---|---|---|---|
| CCombineMenu | 0xae1600 | 0xae1620 | 0x98/0x99 |
| CEnchantMenu | 0xb34250 | 0xb34270 | 0x70/0x71 |
| CInventoryMenu | 0xb60ee0 | 0xb60f00 | 0x60/0x61 |
| CMerchantMenu | 0xb77590 | 0xb775b0 | 0x60/0x61 |
| CPetMenu | 0xba5190 | 0xba51b0 | 0x68/0x69 |
| CQuestMenu | 0xbcca80 | 0xbccaa0 | 0x188/0x189 |
| CSkillMenu | 0xbee2c0 | 0xbee2e0 | 0x38/0x39 |
| CStashMenu | 0xc04210 | 0xc04230 | 0x60/0x61 |
| CStatsMenu | 0xc187f0 | 0xc18810 | 0x68/0x69 |
| (10th `open` member per frontier not located in symbols; see §4) | | | |

## 4. Open

- Frontier lists 10 `open` / 10 `openPartial` members; 9 classes × 2 = 18
  located. The 10th pair is unidentified — likely a menu class outside the
  nine (find via vtable scan before claiming the family complete).
- `open()` has no direct (non-virtual) callers anywhere in `.text`
  (full-section objdump grep for `b60ee0/b60f00`: zero hits outside the
  definitions) — queries go through virtual slots, matching the toggle
  bodies that read menu state via `+0x20/+0x28` virtuals instead.
- LO=0 is now confirmed for Inventory/Merchant/Quest/Skill at constructor
  stores `0xb607d5`, `0xb772ed`, `0xbcc717`, `0xbe3a17`; see the accepted
  shared field map above. HI lifecycle and other family owners remain open.
