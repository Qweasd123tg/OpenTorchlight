# Eight panel query owning functions

This accepted source evidence is confined to eight complete original getter bodies.
It supplies full-completion candidates, not an automatic registry promotion or
closure of the four classes, their setters, or the game. Machine-readable body
bytes, symbol sizes, SHA-256 values and field maps are in
[ui-panel-query-functions.json](ui-panel-query-functions.json).

Main review accepts the eight owning functions in their stated initialized
domain; the explicit full-completion records and current dependency hashes are
in `research/function-transfer.json`. The broader class/query families remain
partial. Existing source/native/controller checks were rerun for integration;
the final grouped CPU report is `build-cegui/automatic-transfer-verification.json`.

## Source and complete bodies

**original-code:** read-only Linux x86_64 ELF
`/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`tools/original.py::Original` independently corroborated the audit's symbol
addresses, exact symbol-sized bodies, bytes and body hashes. No original process
or resource was modified.

| Owner | isRight address / complete instructions | openPartial address / complete instructions | LO byte |
|---|---|---|---|
| CInventoryMenu | `0xb60ed0`: `mov $1,%eax; ret` (6 bytes) | `0xb60f00`: `movzbl 0x60(%rdi),%eax; ret` (5 bytes) | `this+0x60` |
| CMerchantMenu | `0xb77580`: `xor %eax,%eax; ret` (3 bytes) | `0xb775b0`: `movzbl 0x60(%rdi),%eax; ret` (5 bytes) | `this+0x60` |
| CQuestMenu | `0xbcca70`: `mov $1,%eax; ret` (6 bytes) | `0xbccaa0`: `movzbl 0x188(%rdi),%eax; ret` (8 bytes) | `this+0x188` |
| CSkillMenu | `0xbee2b0`: `mov $1,%eax; ret` (6 bytes) | `0xbee2e0`: `movzbl 0x38(%rdi),%eax; ret` (5 bytes) | `this+0x38` |

Each owning function has one basic block and one unconditional return. All
instructions are accounted for: no conditional branch, early return alternative,
call, field write, internal error path, resource acquisition or cleanup. There
are no library/resource dependencies within these bodies. `isRight` reads no
state and does not dereference `this`; `openPartial` reads exactly one LO byte,
zero-extends it, and does not read HI. Its caller must provide a readable,
initialized object. Invalid pointers are outside that precondition, not an
unimplemented getter error branch.

The System V x86_64 ABI places `this` in RDI; these instructions set EAX, with
the bool result observed through AL. The original byte read itself does not
normalize arbitrary byte payloads. The supported initialized bool domain is
0/1, for which the port's C++ bool has the same observable query result. The
port is a semantic adapter, not an original-object-layout or arbitrary-byte ABI
emulator.

## Shared LO field map

**original-code:** each field is one byte, initialized to zero. These constructor
and setter stores establish the getter's field identity and initialized domain;
they do not assert complete transfer of the containing functions.

| Owner | Constructor / zero initializer | setOpen writers and values | Reader |
|---|---|---|---|
| Inventory | `0xb60770` / `0xb607d5` | `0xb4ec41=0`, `0xb4ec55=0`, `0xb4ee67=bpl` | `0xb60f00` |
| Merchant | `0xb772a0` / `0xb772ed` | `0xb6a265=0`, `0xb6a54d=0`, `0xb6a24a=bpl` | `0xb775b0` |
| Quest | `0xbcc6d0` / `0xbcc717` | `0xbc257a=bpl` | `0xbccaa0` |
| Skill | `0xbe39e0` / `0xbe3a17` | `0xbe1157=bpl` | `0xbee2e0` |

## Production consumers and comparison boundary

**Production-code integration:** `InventoryMenuState::open()` delegates to its
`PanelOpenState`; merchant, quest and skill use `PanelOpenState::open()` directly.
The port name `open()` here means the original **openPartial LO flag**, not the
original ordinary `open()` getter reading HI. `open_` starts false and is owned
by the real controller's setter path. The application constructs `UiPausePanel`
from those controller queries and the original role constants: inventory/right,
merchant/left, quest/right, skill/right. `src/ui_pause.cpp` consumes both fields
in the two coverage scans and feeds `ui_game_is_paused`; `src/application.cpp`
consumes that result as `menu_paused`, zero simulation elapsed and update gates.
Movement, vitals, combat and animation clocks have real consumers; rendering
continues with their resulting state. This establishes the code connection,
not a measured frame-parity or UI-click claim.

The existing `tests/compare_ui_pause.py` executes 14 unchanged original bodies,
including all eight getters, across 1536 initialized-state inputs and compares
them with `tests/ui_pause_probe.cpp`. Only CEGUI `Window::isVisible` is an
evaluated-query adapter; the private property-key index fixture is explicitly
initialized to zero. The original constructors, game process, UI events and
list mutation are not executed by that comparison. `tests/ui_pause_test.cpp`
uses actual `InventoryMenuState` and `PanelOpenState` instances and their setters
to exercise the consumer role/flag table. These are descriptions of existing
checks, **not fresh pass claims by this document's author**. Final implementation
and test fingerprints and current validation results belong to main-agent
acceptance after concurrent edits.

Ordinary `open()`, the complete `bothCoveredPartial` body, full constructors and
`setOpen`, animation behavior, HI state and object lifetime remain outside these
eight owning-function candidates. This document makes no class-wide or game-wide
completion claim and requests no automatic full promotion.
