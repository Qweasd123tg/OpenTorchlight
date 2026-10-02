# Generated Main canLoad query and filename-count owner

2026-10-02. `original-code`: read-only
`/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`library-derived`: raw p-code exported with pinned Ghidra 12.1.3; identity
and workflow are recorded in [pcode-automation.md](pcode-automation.md).
These two whole bodies have no external-library calls.

| Owning function | Complete symbol bytes | Contract / whole-symbol SHA-256 |
|---|---:|---|
| `CGameUI::canLoad @0xa84d20` | 12 | pointer64 `this+0x588` -> RDI; tail jump `0xc2b700`; `fe88d0aee7c5a3b1ed4e926cf98ff629a30b7e23e42c942c88cce7d1fbba4c23` |
| `CMenuManager::canLoad @0xc2b700` | 31 | Continue pointer, filename-vector bounds, signed-low32 count>0 -> AL; RET; `c616c081d6c241233f2369bb15e030f92bef141855eeb2aaf5a25acb3d7fb9c4` |

Accepted machine inputs:
[00a84d20.json](lifted-ui/00a84d20.json),
[00c2b700.json](lifted-ui/00c2b700.json). Every instruction, both complete
symbol hashes and the ELF identity are checked by the native comparison.

## Complete contract and fields

`original-code`: wrapper loads manager pointer64 at `0xa84d20`, then JMP
`0xa84d27` shares the machine/stack with its dependency. Manager reads its
Continue pointer64 from `+0xde8` (`0xc2b700`), reads filename end pointer64
`+0x220` (`0xc2b707`), subtracts begin pointer64 `+0x218` (`0xc2b70e`),
arithmetic-shifts the uint64 difference by 3 (`0xc2b715`), and tests only
signed EAX32 (`0xc2b719`). SETG writes **AL8** at `0xc2b71b`; upper RAX is
not a boolean return value. RET `0xc2b71e` consumes the shared outer return
address. There are no branches beyond the tail dependency, object stores,
allocations, errors or cleanup paths. The source does not guard null owners;
valid live pointers are caller preconditions.

| State | Width / initial state | Source writers | Readers / port owner |
|---|---|---|---|
| UI `+0x588` | pointer64,0 | ctor `0xaa66d7`; publication after manager ctor `0xaa4023` | UI query; live FilenameCountMemory UI route |
| manager `+0xde8` | pointer64,0 | ctor `0xc2bf0c`; publication after Continue ctor `0xc2bc8d` | manager query; same live count context |
| Continue `+0x218/+0x220/+0x228` | filename-vector begin/end/capacity pointer64,0/0/0 | ctor `0xc42569/0xc42574/0xc4257f`; reload/growth below | query reads begin/end only; `Frontend::saves_` row count through explicit OTC producer adapter |
| Continue `+0x1e8/+0x1f0` | separate save-state-vector begin/end pointer64,0/0 | ctor `0xc42527/0xc42532`; reload pointer append `0xc3ec6f` | canContinue; **not read by canLoad** |

`original-code`: the filename container is `vector<wstring>`, with 8-byte
elements in this original libstdc++ ABI. Constructor unwind passes `+0x218`
to `vector<wstring>::~vector` at `0xc425cd`. `reloadFiles @0xc3e420` clears
filename end to begin on `0xc3e5bb`. Its append invokes the wstring copy
constructor on `0xc3ec9b`, advances end by 8 on `0xc3eca7`, and publishes end
at `0xc3ecab`. The save-state pointer append immediately preceding it is a
different container and store (`0xc3ec6f`). Filename content, allocation and
SVB decoding are not effects of the two query functions.

For a valid nonnegative contiguous pointer difference, the result is
`signed32(count & 0xffffffff)>0`, not an unconditional size_t nonempty test.
Counts at INT32_MAX+1 or UINT32_MAX are false, 2^32 is false, and 2^32+1 is
true. These raw arithmetic boundaries are calibrated without huge real
vectors; ordinary frontend filename counts lie within the usual signed32
range. Integer operations use exact truncation and arithmetic shift without
signed C++ overflow.

## Real owner and consumer

[src/save_selection.cpp](../src/save_selection.cpp) supplies a read-only
`FilenameCountMemory` view and calls generated UI -> manager bodies through
`save_list_can_load(filename_count)`. Pointer identities are private adapter
addresses; no original object layout is imposed on an application object.
The view exposes only UI/manager pointers, filename begin/end and the
explicit outer RET sentinel. Any other read or object write fails.

[Frontend::main_can_load](../src/frontend.cpp) passes `saves_.size()` from the
actual frontend-owned list. `dispatch_main_menu` consumes the returned AL
boolean in Main New/Load routing and sends Create or Load state requests;
Frontend's own Load/Open action also reads this query. Thus the generated
arithmetic has a real state-transition consumer. `set_saves` replaces the
owned OTC list and resets related frontend selection/scroll state.

`inferred` adapter boundary: current OTC list rows provide the filename count.
This does not equate the two distinct original vectors or reproduce the
original SVB reader, file filtering/sorting, filename strings or resource
lifetimes. Invalid/unreadable OTC rows and source producer policy remain
their existing separate boundary; the query itself does not inspect a row,
filename, selected index or saved HP. The earlier generated canContinue
chain is documented in [automatic-function-transfer.md](automatic-function-transfer.md).

## Verification and remaining scope

`original-code` comparison:
[tests/compare_save_list.py](../tests/compare_save_list.py) executes unchanged
whole original bodies from private PIE-compatible mappings, with explicit
UI -> manager -> Continue pointer chains. It compares the actual
[production probe](../tests/save_list_probe.cpp) over **2634 cases / 1317
distinct filename counts**. Every fixture deliberately supplies a different
save-state count; both original routes must agree and all **5592 fixture
bytes remain unchanged after each call**. The grid, integer boundaries,
large signed64-representable pointer deltas and deterministic random counts
produce zero mismatches. Results are recorded in ignored
`build-cegui/save-list-native.json`. The count-only query never dereferences
the fake vector bounds, so huge allocations are unnecessary.

The two complete query contracts, exact tail dependency and owned production
consumer are covered. Full CGameUI/CMenuManager/Continue constructors,
settings/game lifetimes, source file parsing/sorting/string ABI and full
Main/Dropdown presentation remain separate owning functions. This packet
does not close those producer or controller families. No original game,
GUI input, screenshots, frame parity or performance measurement was run.
