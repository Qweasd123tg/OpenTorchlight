# Автоматическая генерация подключённых исходных функций

> **Заморожено 2026-10-03.** Действующий процесс — [decomp](../decomp/README.md) и [AGENTS.md](../AGENTS.md). Документ остаётся справочником по поведению; его процессные указания (контракты, стадии, пакеты, очереди) не действуют.

2026-10-02. `original-code`: внешний ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`library-derived`: Ghidra 12.1.3 и его закреплённые x86:LE:64 p-code semantics;
идентичность установки и headless-проекта — [pcode-automation.md](pcode-automation.md).
Это перенос операций в компилируемый C++, который получает настоящих владельцев
состояния приложения. Decompiler C и локальные expression summaries не служат IR.

## Рабочий путь

1. `tools/ghidra_probe.py` экспортирует точные функции из read-only проекта,
   сверяет instruction bytes с внешним ELF и сохраняет tool/input SHA.
2. Reviewer принимает полный контракт, допустимые входы и memory/ABI bindings.
   Минимальные принятые operations находятся в `research/lifted-ui/`; это
   reviewed source evidence, без декомпиляции и generated analysis packets.
3. `tools/lift_pcode.py` генерирует тела по raw operations. CMake делает это
   автоматически через `cmake/LiftedCode.cmake`. Header/report находятся только
   в ignored build. Обычная сборка не требует Ghidra или оригинальной игры.
4. `src/ui_game_state.cpp`, `src/save_selection.cpp`, `src/ui_screen_scale.cpp`,
   `src/ui_int_property.cpp` и `src/ui_dropdown.cpp` связывают чтения/записи
   с owned fields. Существующие Frontend/application consumers используют
   результаты. Чужая object layout не накладывается на C++ объект порта.
5. Native comparison исполняет неизменённые полные ELF bodies и сравнивает
   generated production consumers. Реестр обновляется только после ревью;
   успех генерации не выставляет completion.

Пример повторной генерации всех одиннадцати тел:

```sh
python3 tools/lift_pcode.py \
  research/lifted-ui/00a828f0.json research/lifted-ui/00a82900.json \
  research/lifted-ui/00a84d30.json research/lifted-ui/00c2b9c0.json \
  research/lifted-ui/00c33490.json research/lifted-ui/00a84d20.json \
  research/lifted-ui/00c2b700.json research/lifted-ui/00a83e70.json \
  research/lifted-ui/00c6e410.json research/lifted-ui/00c6e440.json \
  research/lifted-ui/00b05e80.json --abi research/lifted-ui/abi.json \
  --out build-cegui/generated/lifted/torchlight/generated/ui_state_queries.hpp \
  --report build-cegui/lifted-ui-code.json
```

## Полные тела и общая карта состояния

| Owning function | ELF symbol bytes | Полный контракт |
|---|---:|---|
| `CGameUI::requestSetGameState @0xa828f0` | 13 | u32 ESI -> `this+0x1914`, затем u32 EDX -> `+0x1918`; RET |
| `CGameUI::clearGameStateRequest @0xa82900` | 21 | u32 6 -> `+0x1914`, затем u32 6 -> `+0x1918`; RET |
| `CGameUI::canContinue @0xa84d30` | 12 | pointer64 `+0x588` -> RDI, tail jump manager query |
| `CMenuManager::canContinue @0xc2b9c0` | 12 | pointer64 `+0xde8` -> RDI, tail jump Continue query |
| `CContinueGameMenu::canContinue @0xc33490` | 67 | empty/range exits; selected pointer; ordered HPf32 >0 -> AL; RET |
| `CGameUI::canLoad @0xa84d20` | 12 | pointer64 `+0x588` -> RDI, tail jump manager query |
| `CMenuManager::canLoad @0xc2b700` | 31 | Continue filename-vector bounds `+0x218/+0x220`, signed low32 count>0 -> AL |
| `CGameUI::scaledY @0xa83e70` | 36 | named ratio -> GetFloat direct CALL, original private stack, scalar SSE multiplication |
| `CDynamicPropertyFile::GetFloat @0xc6e410` | 41 | unsigned index/range, binary32 element or -1 fallback, no object writes |
| `CDynamicPropertyFile::GetInt @0xc6e440` | 32 | begin/end pointer64, zero-extended uint32 index, int32 element or -1, no writes |
| `CDropdownMenu::onDoubleClick @0xb05e80` | 6 | MOV EAX=1, actual RET; ignored object/enum/name, bool AL=1 |

`canContinue` Ghidra body занимает 65 bytes: отсутствующие `66 90 @0xc334ce..cf`
— недостижимое padding после RET, до следующего branch target. Полный symbol
hash закреплён отдельно от address/instruction hash. bool возвращается в **AL**;
верх RAX на успешной ветви содержит save pointer и не является bool result.
Все conditional targets и обе последовательные tail dependencies учтены.

| State | Тип/initial | Writers | Readers/production owner |
|---|---|---|---|
| UI `+0x1914/+0x1918` | u32/u32, 6/6 | ctor stores `0xaa6838/0xaa6847`; request/clear above | client update `0x59171e`, `0x5918be/0x5918d1`; `UiGameStateRequest::state/menu` |
| UI `+0x588` | pointer64, null then manager | ctor `0xaa66d7`; create `0xaa4023` after manager ctor | UI query; checked binding to live selection context |
| manager `+0xde8` | pointer64, null then Continue | ctor `0xc2bf0c`; create `0xc2bc8d` after Continue ctor | manager query; same context's live save-list owner |
| Continue `+0x1e8/+0x1f0` | vector begin/end pointer64, 0/0 | ctor `0xc42527/0xc42532`; reloadFiles `0xc3e420`/vector lifecycle | query; `Frontend::saves_` bounds |
| Continue `+0xc8` | signed32, 0 | ctor `0xc424c7`; selectCharacter `0xc3f8f3` | query; `Frontend::save_index_` with explicit signed32-domain adapter |
| saved record `+0xe0` | binary32 saved current HP | fillSaveState `0x826a09`; save/load `0x862130/0x862eb0` | query; selected `SaveSlotInfo::health` |

Aligned initializer/create windows:
[disassembly/lifted-ui-owners.asm](disassembly/lifted-ui-owners.asm).
Broader producer/selection contracts:
[main-menu-save-selection.md](main-menu-save-selection.md).
Object/pointer lifetime and validity are caller preconditions; these queries
do not allocate, delete or perform file I/O. Writers have two unconditional
stores, no branches, no calls/error/cleanup paths. Queries write no object
memory; two wrappers depend only on the accepted third query. There is no
external library ABI inside these five bodies.

`integration`: generated request writes **the pair actually read** by
`Frontend::main_request_state`, selecting Create/Load or producing the load
request; generated clear restores its sentinel after that consumption.
Original client update calls setGameState at `0x5918da`, then clear at
`0x5918e3`; the port retains its existing immediate frontend policy. Native
update timing, modal gates and the complete client controller stay partial.

`integration`: generated UI -> manager -> Continue query reads mapped owned
save-list/index/HP fields. `selected_continue_save` returns that exact row.
Main/Load visibility, load requests and Main-entry selection consume it.
OTC unreadable rows and indices outside signed32/count domain are rejected
before the raw query; no other row is substituted. Negative native indexing
would access outside the vector and is not a supported object precondition.
SVB parsing, source sorting and model/level lifetimes are separate producers,
not additional effects inside these five owning functions.

The two `canLoad` bodies now consume the live frontend filename count and
control Main New/Load routing. Their **separate** filename vector and signed
low32 arithmetic are documented in [generated-save-list.md](generated-save-list.md).
The scalar Y -> GetFloat direct-call closure supplies UiLayout/HUD/inventory
offset geometry and native CEGUI resize setters. Borrowed property fields,
stack slots, both getter exits and the floating-environment remainder are in
[generated-ui-scale.md](generated-ui-scale.md). GetFloat and both canLoad
queries are fully reviewed; scaledY remains partial for original MXCSR/fenv
flags, traps and control modes.

## Compiler semantics and rejection

Registers alias by byte offset, including EAX/RAX/AL. Only reviewed ABI inputs
start initialized. Unique bytes are local to each original instruction and
alias within it. Operations evaluate inputs once in raw order before writes;
truncation/extension/flags use unsigned arithmetic without signed C++ overflow.
Scalar widths1..8, bool, shifts, POPCOUNT, binary32/64 comparisons/NaN, memory
effects and static/internal branches are supported. FLOAT_MULT is restricted
to verified scalar-SSE MULSS/MULSD bytes with matching widths. Result bits
preserve destination-first NaN payload and negative indefinite for infinity*zero;
FP flags/traps/control modes remain outside this helper. Fast-math is rejected.
Identical register varnodes in INT_XOR define zero without reading unknown
incoming bytes; RAM/unique reads and all other missing-input checks stay strict.

Approved direct CALL uses the **raw preceding stack operations** and exact
original fallthrough return address. Callee RET reads/pops that slot and
merges initialized machine bytes, preserving untouched caller registers.
Tail jump shares memory/register state and consumes just the deepest RET.
Unknown targets, indirect calls/jumps, CALLOTHER, unimplemented float operations,
wide vector operations, wrong spaces/widths, recursion and closure depth>64 are
rejected. Unmapped owner reads/writes and uninitialized executed operands fail
explicitly; unsupported logic is never replaced with a dummy value.
The production cohort exercises both tail calls and the original scaledY
direct CALL to GetFloat, including its exact spill/push/return/pop operations.
Both closure forms are compared against unchanged whole original bodies.

## Проверки и масштаб

`tests/pcode_lifter_test.py`: 30 compiler/runtime checks, including strict C++17
compilation, trapping UBSan, aliasing, widths, flags, AL return with nonzero high
RAX, internal control flow, unknown dependencies, direct-call stack, preserved
caller bytes, tail closure and recursive rejection. `tests/ui_game_state_test.cpp`
exercises the real owned pair initializer and 25 request/clear combinations.
Additional checks cover scalar-SSE binary32/64 result bits, NaN payload order,
precision/underflow, fast-math rejection and register-only self-XOR initialization.

`tests/compare_ui_game_state.py`: **2112** cases against unchanged two writer
bodies, complete 0x1920-byte observation buffers after each operation, u32 bit
edges/random values. It also verifies every accepted instruction and full
symbol hash of all five generated functions against the pinned ELF.
`tests/compare_save_selection.py`: **2437** cases against unchanged three query
bodies and the production selector, including empty/range exits, nonselected
live rows, signed zero, subnormal, infinity and NaN. Constructors/game/GUI are
not executed in these native checks; nonfinite HP is raw calibration, not OTC
checkpoint acceptance. Cold scene integration is established by code and build.
`tests/compare_save_list.py`: **2634** cases against both complete canLoad
bodies, observing all 5592 fixture bytes and deliberately different filename
and save-state counts. `tests/compare_ui_scale_lift.py`: **3357** cases against
whole scaledY/GetFloat bodies, including 2777 raw-bit scale results and 580
property reads; full owner/vector/guard buffers remain unchanged.

Initial scheduling audit: 3173 residual manual routes contain 679 with no
indexed CALL, 1842 with only direct CALL and 652 with an indirect CALL. Inside
the UI contour: 211 =35/117/59. These counts come from `auto_triage.build(root,4)`
joined to the validated callsite index before this acceptance. The index omits
tail jumps, so **679 is a candidate set, not generator eligibility or closure**.
The subsequent raw-code batch screen covers **3162** residual manual bodies:
**1541** local structural candidates and **475** with all supported transitive
dependencies supplied across the four batches. These are generation candidates;
none has a reviewed ABI or production owner from screening alone. The pinned
exporter, rejection details and repeatable commands are in
[function-lift-screening.md](function-lift-screening.md). This later selection
uses sized symbols and current whole-function acceptance, and is not the same
population as the earlier callsite-only scheduling audit.
No whole-development speedup or percentage of automatically transferred game
functions is measured. Eleven generated owning bodies are connected; ten have
full acceptance and scaledY remains partial. The separate eight panel-query
closures bring the ledger's full-function total to eighteen. This count covers
accepted individual source functions, not the fraction of the game restored.

The integer reader now supplies native Settings checkboxes and shadow/resolution
selection from the live draft; Main's actual inherited default double-click
supplies the CEGUI handled result. Complete contracts and remaining controller
boundaries: [GetInt](generated-settings-int.md) and
[Dropdown default](generated-dropdown-default.md). Their native comparison
passed2470 cases (2251 integer,219 default); direct control/readback and real
CEGUI Event result accumulation passed without input/frame/GL.

Prior acceptance was re-reviewed after this additive cohort: the original
five raw bodies/ABI entries, state-pair owner and selected-row/HP consumers are
unchanged. canLoad replaces a separate frontend count predicate; new float
semantics and register self-XOR preserve the previous integer/query behavior.
The eight panel-query implementations and owned consumers are unchanged;
CMake only adds generation inputs/probes/gates. Their relevant native and CPU
checks are rerun with the final inputs before accepted hashes are refreshed.

2026-10-02 additive integer/default cohort: all nine prior generated definitions
and their ABI entries were compared and remain unchanged. Settings integer
projection and Main default-result dispatch are isolated from prior state,
Continue/canLoad, geometry and panel-query owners. Core and affected probes were
rebuilt; the four prior native gates passed10540 cases again. Only these
reviewed additive changes are used to refresh existing acceptance input hashes.
