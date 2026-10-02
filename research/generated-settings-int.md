# Generated integer settings reader and native control consumers

2026-10-02. `original-code`: read-only external ELF
`/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
The whole `CDynamicPropertyFile::GetInt(unsigned) @0xc6e440` symbol is
**32 bytes**, SHA-256
`026b709325aa1cd3cf3c1f896c41c587727a206c44e1466be8ce1d6e28eac12f`.
Every source instruction, field width, branch and lifecycle address below was
checked directly against this ELF. Decompiler types are not their authority.

`library-derived`: the generated raw operations use the pinned Ghidra 12.1.3
`x86:LE:64:default` language and existing scalar p-code runtime. Tool identity,
read-only export and exact-symbol checks follow
[the bounded lift pipeline](lift-pipeline-live.md) and
[raw generation](automatic-function-transfer.md). Original CEGUI ownership
and its pinned upstream/vendor boundary remain as recorded in
[Settings/Options integration](cegui-settings-options.md).

## Complete read contract

The single source body contains no calls, allocation, writes or local cleanup
handlers. It has one indexed-load branch and one shared RET:

| Address | Operation and effect |
| --- | --- |
| `0xc6e440` / `0xc6e444` | Read begin/end pointer64 from `this+0x40/+0x48` into RCX/RDX. |
| `0xc6e448` | `MOV ESI,ESI` zero-extends the supplied uint32 index into RSI. |
| `0xc6e44a` | Initialize EAX to `0xffffffff`; writing EAX also clears RAX's upper32 bits. |
| `0xc6e44f` / `0xc6e452` | Subtract pointer bit patterns, then arithmetic-shift the uint64 result by2. A valid contiguous int32 vector gives its element count. |
| `0xc6e456` / `0xc6e459` | Compare RSI with the computed count using **unsigned64** `CMP/JAE`. Index>=count skips the element read. |
| `0xc6e45b` | Load exactly four bytes from begin+index*4 into EAX. |
| `0xc6e45e` | `REPZ RET`: both paths read the actual caller return pointer64 from RSP and advance RSP by8. The prefix adds no other function effect. |

The missing-index result is int32 **-1**, not a default from property
registration. An empty vector reaches that result without touching an element.
Stored `0xffffffff` has the same result bits as the fallback. There is no
signed-index test, clamp, settings-key lookup, callback or float conversion in
this reader. All original32 bytes are executable instructions; there is no
unexported alignment gap inside the symbol.

System V x86-64 inputs are RDI pointer64, ESI uint32 and the initialized private
RSP return slot. The accepted generated entry is `fn_00c6e440`; its return
descriptor observes EAX's lower32 bits. The wrapper preserves these bits using
`memcpy` into `std::int32_t`, avoiding an implementation-defined unsigned to
signed conversion. It never overlays native offsets onto a C++ object.

## Shared fields, initial values and lifetime

| State | Width / confirmed initialization | Readers and writers |
| --- | --- | --- |
| property file `+0x40/+0x48/+0x50` | begin/end/capacity pointer64; constructor `0xc6e7f0` zeroes them at `0xc6e897/0xc6e8b4/0xc6e8bc` | GetInt reads begin/end at `0xc6e440/444`; registration/growth and destruction below own mutations/allocation. |
| vector element | int32; default is supplied by a registration caller | `GetIntPropertyIndex @0xc70620` preserves its EDX default at `0xc7063b`, stores it at the old end on `0xc70726..2a`, then advances end by4 at `0xc70730..34`. GetInt reads at `0xc6e45b`; SetInt writes at `0xc6e6a0`. |
| native named-key index | uint32 in a global settings key | `GetIntPropertyIndex` maps a name to its existing index at `0xc70777..86`, or publishes a newly appended index at `0xc7074b..53`. Settings constructor stores that returned EAX into the corresponding key global. These numeric IDs depend on registration. |
| borrowed production table | contiguous `const std::int32_t*` and count supplied by the caller | The live Settings draft supplies values; the local `std::array` in `set_settings` owns the evaluated snapshot for the whole generated call. The query performs no writes or acquisition and retains no pointer after return. |

Capacity exhaustion calls the original int-vector `_M_insert_aux @0x85b790`
from `0xc707e4`, with RDI pointing to the vector at property-file `+0x40`.
Its growth publishes begin/end/capacity pointer64 at `0x85b8db/0x85b8e1/0x85b8e5`
relative to that vector. The property constructor's unwind loads begin at
`0xc6ea17`; normal destruction loads it at `0xc6f85d`, checks nonnull and frees
it through `operator delete @0xc6f866`. These are evidence of the external
allocation owner, not operations executed by GetInt or its borrowed wrapper.

`SetInt(unsigned,int) @0xc6e650` checks the same begin/end range at
`0xc6e66b..683`, stores EDX at `0xc6e6a0` only when in range, then invokes the
per-index listeners from `0xc6e6f6` in their stored order. Registration, SetInt,
listeners and allocation/string/unwind contracts are separate owning
functions; this reader does not implement them.

`original-code`: representative defaults are supplied by the full Settings
constructor `0xd80cf0`, rather than inferred from empty vectors or GetInt's
fallback. The following calls pass their listed EDX defaults to
`GetIntPropertyIndex`, then store the returned index into the named global:

| Named setting | Registration call / global-index writer | Supplied default |
| --- | --- | ---: |
| FULLSCREEN | `0xd80f19` / `0xd80f26` | 1 |
| VSYNCH | `0xd8111f` / `0xd8112c` | 0 |
| RES_WIDTH | `0xd811fd` / `0xd8120a` | 800 |
| RES_HEIGHT | `0xd81247` / `0xd81254` | 600 |
| SHADOW_DETAIL | `0xd81498` / `0xd814a5` | 4 |
| FSAA | `0xd82019` / `0xd82026` | 0 |

This documents native registration provenance. It does not change the port's
existing `DisplaySettings` defaults, persisted overrides or runtime choices.

## Borrowed adapter and production integration

[ui_int_property.cpp](../src/ui_int_property.cpp) maps the source's pointer64
reads to a caller-owned evaluated table through checked synthetic addresses.
The synthetic end pointer is calculated only after verifying that
`count*4+begin` fits uint64. A nonempty null table is rejected before generated
execution; an empty null table remains valid. Exact-width, aligned element
reads stay inside the mapped vector. Every memory write is rejected. The
actual RET reads an initialized private eight-byte `ByteState` slot.

`inferred` adapter precondition: the supplied C++ table is valid and stable for
the duration of the synchronous query. Address representability checks do not
prove a raw external pointer's allocation size. The implementation borrows,
never allocates or copies an owning settings object, and never guesses native
numeric key IDs. Named port slots in the native Settings projection are
evaluated bindings, not discovered registration numbers.

`original-code`: `CSettingsMenu::setOpen @0xbd5560` shows the real consumers:

| Field | GetInt call / downstream consumer |
| --- | --- |
| FULLSCREEN | `0xbd5660`; TEST EAX/SETNE at `0xbd566e..70`; Checkbox::setSelected `0xbd5674`. |
| FSAA | `0xbd568d`; TEST/SETNE `0xbd569b..9d`; Checkbox::setSelected `0xbd56a1`. |
| VSYNCH | `0xbd5741`; TEST/SETNE `0xbd574f..51`; Checkbox::setSelected `0xbd5755`. |
| RES_WIDTH / RES_HEIGHT | `0xbd5c90` / `0xbd5d8e`; compare each actual mode component before selecting its matching resolution row at `0xbd5da6`. |
| SHADOW_DETAIL | `0xbd61f7`; compare EAX with the current row index at `0xbd61fc`, branch to the matching row at `0xbd61fe`. |

The portable production chain is `Frontend`'s existing `settings_draft_` →
`CeguiMenu::settings_state` → `Impl::set_settings` → the named evaluated int
table and `ui_int_property` → native CEGUI checkbox/combobox setters. This
links the recovered reader's effects to real controls. The unchanged typed
Apply payload and Application persistence transaction consume later edits.
The complete original Settings setOpen/update, MasterResourceManager/global
property ownership and arbitrary registered callbacks remain outside this
reader's acceptance boundary.

## Verification boundary

`compare_settings_queries.py` passed **2470 cases**, including 2251 GetInt
(1084 in-range and1167 fallback) and219 default double-click. The probe executes
the generated production wrappers. Both full-symbol hashes and every accepted
instruction were rechecked against the pinned ELF. All initialized
settings/object/vector/guard bytes remained unchanged.

`settings_queries_controls_test` passed on the external pak and pinned CEGUI:
fullscreen/FSAA/VSync, shadow/resolution selection, native readback, repeated
opening with new values, negative nonzero FSAA, unmatched/default rows and
null/empty owner boundary. It calls state APIs directly without input injection,
frame collection or GL. Existing resource unknown-property diagnostics remain.

All eleven bodies, core/probes/controls were built. The previous nine generated
definitions and ABI entries are unchanged by this additive cohort; their four
native gates passed10540 cases again. This closes the whole32-byte GetInt
contract under valid stable borrowed-table preconditions. Registration/full
controllers/callback ownership and scaledY FP environment remain outside it.
No original game, UI clicks, screenshots or performance measurement is implied.
