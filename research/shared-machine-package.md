# Автоматическая сборка пакета общего машинного состояния

> **Заморожено 2026-10-03.** Действующий процесс — [decomp](../decomp/README.md) и [AGENTS.md](../AGENTS.md). Документ остаётся справочником по поведению; его процессные указания (контракты, стадии, пакеты, очереди) не действуют.

2026-10-03. Продолжение [общего переводчика](mass-transfer-engine.md) и
[CALLIND](shared-machine-indirect.md). `tools/assemble_machine_package.py`
соединяет source validation, bounded preparation/export и настоящий shared
emitter. Отдельные компиляторы игровых подсистем не вводятся.

## Контракт сборщика

`original-code`: внешний read-only ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Exact sized STT_FUNC entries берутся из оригинала, не из предполагаемых C++ типов.
`library-derived`: экспорт raw schema2 закреплённой Ghidra12.1.3 и проверка
manifest/tool/ELF/instruction bytes существующим `load_raw`. Подготовка owned
bounded проекта и read-only экспорт переиспользуют
[сохранённый workflow](decompiler-workflow.md).

Явные `--entry` задают roots. Уже экспортированные пакеты из `--raw-dir`
образуют reusable pool; неподключённые тела не становятся частью программы.
Настоящий `compile_function(..., shared_machine=True)` проверяет все операции
и извлекает direct/tail dependencies. Отдельного приблизительного screen или
придуманных per-function ABI здесь нет. Missing bodies становятся точным
`missing-targets.txt`; с `--export` добираются автоматически. Опция
`--prepare-project` разрешает только подготовку принадлежащей инструменту
анализаторной базы, не исправление оригинальных файлов.

`--observed-targets FILE` принимает protocol:

```json
{
  "schema": 1,
  "kind": "observed-machine-call-targets",
  "original_elf_sha256": "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b",
  "targets": ["0xae15f0"]
}
```

`shared_machine_indirect_probe` выдаёт такой JSON только при
`UntranslatedCallTarget`. Перед добавлением числа в dispatcher проверяются
точный ELF entry, отсутствие неоднозначных размеров, source body и весь raw
контракт; zero/interior/неизвестные/stale-ELF записи отвергаются. Уже проверенное
тело переиспользуется, отсутствующее может экспортироваться. Это observation
программы на предоставленном guest state, не доказательство полноты всех
виртуальных целей или lifetime создаваемых исходной игрой объектов.

Никакого автоматического исполнения/возобновления guest программа сборщик не
делает. Effectful вызов может успеть изменить RAM до missing target; повторный
запуск приложения требует отдельного решения о состоянии. В проверке ниже
переисполняются только явные изолированные fixtures в новых процессах.

Бюджет выбранных тел1..4096 включает reused и exported entries, dependency
rounds1..16, экспортный batch максимум1024. Failed packets не повторяются
автоматически, conflicting duplicates отвергаются. Stale source/profile/raw/
observation/ELF, malformed metadata, неподдержанные операции, recursion и
generation failures сохраняют отчёт и не дают успешный статус. Output должен
быть свежим ignored build или `/tmp`; original/resources остаются read-only.
`GENERATED` удостоверяет только сборку raw closure и C++ generation. Stages,
completion и game-ready не повышаются.

## Проверенный живой цикл

Roots: `CGameUI::bothCoveredPartial @0xa82ae0`,
`CCollisionShapeDescriptor::Get_getEnabled @0x5bb4a0` и
`CGameUI::scaledX @0xa83ea0`. Первые два тела reused из проверенного raw batch.
Третье отсутствовало: инструмент сам подготовил/exported36-byte scaledX,
обнаружил direct CALL `0xa83eb4 -> GetFloat @0xc6e410` и подготовил/exported
41-byte dependency. Два rounds, два новых тела, source_consistent=true.
Полные SHA и instruction coverage записаны в child reports. Полнота symbolic
padding или исходного FP environment этим результатом не принимается.

```sh
python3 tools/assemble_machine_package.py \
  --entry 0xa82ae0 --entry 0x5bb4a0 --entry 0xa83ea0 \
  --raw-dir /tmp/otl-indirect-20261003/export/raw \
  --export --prepare-project --max-functions 32 --max-rounds 3 \
  --output /tmp/otl-machine-direct-20261003
```

Затем изолированный probe стартовал с четырьмя сгенерированными телами.
Реальные source vtables последовательно дали missing targets
`ae15f0, ae1620, bcca70, bccaa0, 5a6cd0`. Пять наблюдений переданы сборщику;
проверенные raw bodies reused без повторного Ghidra запуска. Шесть сборок
программ с4/5/6/7/8/9 bodies скомпилированы strict C++17. Последняя прошла
3157 unchanged-original comparisons (1365 panel,1792 descriptor),0 mismatches;
результаты/initialized RAM/guards и guest stack проверяются тем же native gate.
Это сравнение семи тел CALLIND chains; присутствие scaledX/GetFloat в общей
сборке не создаёт нового native сравнения scaledX.

Артефакты: `/tmp/otl-machine-direct-20261003/package.json`,
`/tmp/otl-machine-expansion-20261003/expansion.json`,
`/tmp/otl-machine-expansion-20261003/native-final.json`.
`tests/machine_package_test.py`:11 PASS — static dependency collection,
exact observed targets, cache reuse, source/byte/selection drift, failures,
duplicate conflicts, malformed profiles и budgets. Ядро/probes rebuilt;
сборщик зарегистрирован как отдельный CTest core gate.

Остаток: library/image/bootstrap ABI, неподдержанные операции, guest exceptions,
unwinding/FP state и производство оригинальных allocator/resource effects.
Automatic replay и exhaustive dynamic-target discovery не реализованы;
отдельные наблюдения не закрывают весь исходный контракт функции.
