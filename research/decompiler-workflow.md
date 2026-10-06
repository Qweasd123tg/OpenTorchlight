# Черновики Ghidra для decomp

Декомпиляция — навигационный вход для восстановления TU. Поведение, типы и
ABI проверяются по ASM, символам, RTTI/vtable, ресурсам и исполнению оригинала.
Рабочий процесс и приёмка — [decomp](../decomp/README.md).

## Вход и проект

Внешний ELF: `/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64`,
SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Он используется только для чтения и не попадает в git.

`tools/decomp/ghidra_draft.py` использует восстановленные типы и заголовки
в постоянном проекте. Нужна установленная закреплённая Ghidra 12.1.3:
`python3 tools/setup_ghidra.py --download` подготавливает её в tool cache;
распакованный каталог передаётся через `GHIDRA_HOME`. Также нужен JDK 21
в `OTL_DECOMP_CACHE/jdk/jdk-21*/`; `analyze` эти инструменты не устанавливает.
Проект и временные артефакты — вне git;
`OTL_GHIDRA_WORK` по умолчанию `/var/tmp/opentorchlight-ghidra`.
Первичный импорт/анализ нужен при подготовке проекта, не для каждого TU:

```sh
python3 tools/decomp/ghidra_draft.py analyze
```

## Целевой экспорт

```sh
python3 tools/decomp/ghidra_draft.py stale
python3 tools/decomp/ghidra_draft.py drafts AIFlag.cpp
python3 tools/decomp/ghidra_draft.py drafts merchantmenu.cpp --address 0xb6ab50
```

На каждую цель сохраняются raw-тело, SHA и статус COMPLETE, TIMEOUT,
TYPE_ERROR или NO_BODY. Отпечаток учитывает ELF, инструменты, типы,
прототипы и vtable. Экспорты имеют отдельные IO/логи; доступ к проекту
сериализован. Повторные попытки ограничены и предназначены для timeout.

Fresh означает пригодный полный экспорт ожидаемых целей с текущими входами.
Изменение отпечатка без успешного обновления тела не делает его fresh.
Частичный `--address` экспорт полезен для выбранного метода, но не делает
весь TU свежим. Черновики и пробные сборки находятся в `build-decomp/`.

Полный COMPLETE не доказывает семантическую правильность черновика.
Generated layouts и SDK declarations не доказывают неподдерживаемый ABI;
secondary this-adjustments и aggregate/variadic signatures нельзя угадывать.

## Дополнительные индексы

Существующие `research/original-callgraph.tsv`, `original-callsites.tsv`,
`original-strings.txt` помогают найти callers, данные и зависимости.
Граф и сортировка callsites не сохраняют условия, повторы и runtime-порядок;
виртуальные цели восстанавливаются по оригиналу.

Прежние команды целевого экспорта, library-match пилоты, code-first пакеты
и p-code workflow сохранены в
[исторической справке](archive/decomp-2026-10-03-06/decompiler-workflow.md).
Code-first и лифтинг заморожены; их пакеты не являются текущей единицей
работы или доказательством переноса.
