# Косвенные вызовы в общем машинном состоянии

> **Заморожено 2026-10-03.** Действующий процесс — [decomp](../decomp/README.md) и [AGENTS.md](../AGENTS.md). Документ остаётся справочником по поведению; его процессные указания (контракты, стадии, пакеты, очереди) не действуют.

2026-10-03. Проверка общего механизма массового перевода, не новый production
binding игровых классов. Единственный compiler/runtime остаётся общим для игры.

## Источники и граница

`original-code`: read-only
`/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`library-derived`: raw schema2 p-code Ghidra12.1.3, x86:LE:64:default;
точные entry подготовлены в owned bounded проекте по
[decompiler-workflow](decompiler-workflow.md), последующий экспорт read-only.
Accepted raw тела и исходные таблицы: [lifted-machine-fixtures](lifted-machine-fixtures/).
Каждый прогон повторно сверяет ELF, полный symbol body, все exported instruction
bytes, SHA и используемые virtual slots.

| Исходное тело | Entry | Размер | Проверяемая исходная цепочка |
| --- | --- | ---: | --- |
| CGameUI::bothCoveredPartial | 0xa82ae0 |277| vector +1930/+1938, два последовательных прохода, четыре CALLIND |
| Combine isRight / openPartial | 0xae15f0 / 0xae1620 |3 /8| EAX=0 / byte +98 |
| Quest isRight / openPartial | 0xbcca70 / 0xbccaa0 |6 /8| EAX=1 / byte +188 |
| CCollisionShapeDescriptor::Get_getEnabled | 0x5bb4a0 |39| null exit, count32=1 до CALLIND, AL в global +142c4a0, pointer result |
| CSceneNodeObject::getEnabled | 0x5a6cd0 |8| byte +82 в EAX |

349 исходных symbol bytes,336 exported instruction bytes. Разница13 —
недостижимые NOP после unconditional jump/RET в первом теле:
0xa82b1f (1),0xa82b68 (8),0xa82b85 (3),0xa82bef (1).
Их bytes проверены по ELF/objdump; остальные шесть тел экспортированы полностью.
Каждая ветвь, включая пустой vector и оба exits, представлена в raw CFG.

`original-code`: CALLIND находятся в 0xa82b48,0xa82b5d,0xa82bb0,0xa82bc5
и0x5bb4b4. Используются настоящие RO table bytes:
Combine address point0xfe6270 (+18->ae15f0,+28->ae1620),
Quest0xff0e30 (+18->bcca70,+28->bccaa0),
CollisionShape0xfd8e50 (+48->5a6cd0).
Ни target replacement, ни callback, ни переписывание алгоритмов не используются.

## Контракт адаптера

В shared_machine `CALLIND` читает register/unique pointer64 один раз и
диспетчеризует exact compiled entry. Callee сохраняет общие регистры/RAM;
исходные push/RET управляют гостевым стеком и проверенным continuation.
Zero/interior/noncompiled/import targets завершают исполнение через
`UntranslatedCallTarget`, сохраняющий числовую цель. Ранее выполненные исходные
effects не откатываются. Автоматическое расширение пакета/возобновление ещё
не подключено; неинициализированная цель и неверный RET также вызывают отказ.

`CallDepth` — явный host stack budget, default64 и диапазон1..64. RAII guard
общий для direct/tail/indirect entries и снимается при ошибке; бюджет считает
generated host entries, включая tail lowering, а не исходную глубину guest stack.
Он не подменяет original exception/unwind. Статическая direct/tail recursion,
BRANCHIND и CALLOTHER остаются неподдержанными. Scalar режим и legacy structural
screen продолжат отклонять CALLIND.

## Проверки и результат

`tests/shared_machine_indirect_test.py`:10 PASS. Проверены nested targets,
continuation, shared registers/RAM, actual stack/RET, неизвестные и частично
инициализированные цели, import exclusion, bounded dynamic recursion и
guard unwind, direct/tail budget, malformed metadata. Scalar11 header/report
побайтно идентичны закреплённому прошлому результату.

`tests/compare_shared_machine_indirect.py`:3157 PASS,0 mismatches.
1365 vector cases (341 все короткие normal lists,1024 mixed random lists),
1792 descriptor cases (768 edge,1024 random). Неизменённые полные native bodies
исполняются в отдельном Linux x86_64 process с настоящими table bytes; original
file не изменяется. Сравниваются result bits и все initialized owner/vector/
object/output/guard bytes. Guest probe дополнительно проверяет RO snapshots,
saved registers, реальный RET/RSP. Flags2/127/128/255 проверяют только машинные
инструкции, не корректность конструирования исходных C++ bool объектов.

```sh
cmake --build build-verification --target torchlight_core shared_machine_indirect_probe shared_machine_queries_probe settings_queries_probe -j3
python3 tests/compare_shared_machine_indirect.py \
  --original /home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64 \
  --probe build-verification/shared_machine_indirect_probe \
  --output /tmp/shared-machine-indirect-native.json
ctest --test-dir build-verification --output-on-failure \
  -R '^(shared_machine_indirect|shared_machine_lifter|function_lift_screening|lifted_address_space|ui_game_state_request|ui_game_pause)$'
```

Core и затронутые probes rebuilt; выбранные CTest gates6/6 PASS. Rebuilt прежние
scalar/shared GetInt/default probes прошли по2470 native regressions. Прежние
ByteState/import/owner реализации не изменены, новое CALLIND действует только
в shared backend. Review hashes прежних completion обновляются только для
этих общих изменений. Семь calibration bodies не получают новые stages/full:
оригинальные constructors/lifetime, приложение, library/image bootstrap,
игровые ресурсы и UI/frame здесь не исполнены и не сравнены.
