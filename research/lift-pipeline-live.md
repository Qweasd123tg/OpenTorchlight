# Живой ограниченный raw-lift pipeline

> **Заморожено 2026-10-03.** Действующий процесс — [decomp](../decomp/README.md) и [AGENTS.md](../AGENTS.md). Документ остаётся справочником по поведению; его процессные указания (контракты, стадии, пакеты, очереди) не действуют.

2026-10-02. Продолжение [плана зависимостей](lift-dependency-automation.md).
Новый `tools/run_lift_pipeline.py` связывает подготовку, read-only экспорт,
план и объединение raw-пакетов без модельных вызовов и изменения реестра.

## Подготовка и граница

`original-code`: внешний ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`prepare_lift_project.py` читает exact STT_FUNC entry/size из `readelf`, проверяет
исполняемый file-backed segment, полные symbol bytes, aliases и отсутствие
пересечения с другими source entries. Максимум 1024 функции, 1 MiB на функцию
и 8 MiB symbol bytes на пакет. Нет вывода ABI/полей или запуска игры.

`library-derived`: закреплённая Ghidra 12.1.3, архив SHA-256
`93a5d11a9ad510622acaaf908c556a7b9b764d338e78a7567f3689bf5081fd54`.
Импорт идёт с `-noanalysis`, без relocations и загрузки/линковки внешних libraries.
`PrepareLiftEntries.java` декодирует flow только внутри выбранного symbol span,
вызывает `enableCodeAnalysis(false)`, проверяет bytes до/после и транзакционно
устанавливает эти bounds. Padding и недекодированные bytes остаются явными gaps.
Source symbols ограничивают диапазон; полнота контракта от этого не принимается.

Проект сохраняется отдельно в `build-ghidra-lift`. Продолжение разрешено только
для cache с собственным provenance marker. Полный/unowned/partial проект не
исправляется автоматически. Экспортёр остаётся `-process -noanalysis -readOnly`.
`--prepare-project` явно разрешает изменение только этой анализаторной базы;
исходный ELF и ресурсы остаются read-only.

`tools/ghidra_runtime.py` задаёт локальные config/cache paths. На этом хосте Java
25.0.4.1 содержит `jdk.compiler`, но не bin/javac. Локальный launcher вызывает
настоящий модуль compiler; версия Java и установленная Ghidra не подменяются.
Путь/версия/hash Java и launcher записываются в подготовку.

## Команда и ограничения бюджета

```sh
python3 tools/setup_ghidra.py --download
python3 tools/run_lift_pipeline.py --scope ui --limit 1 \
  --address 0xa83ea0 --export --prepare-project \
  --max-rounds 1 --max-functions 2 --output /tmp/ui-scaledx-pass-1
```

`--max-rounds` и `--max-functions` обязательны (1..16 и 1..4096); root export
также расходует function budget. Все children последовательны. Перед/после
каждого проверяется tracked/nonignored source snapshot; failed/stale child
останавливает цепочку. `pipeline.json` и `SUMMARY.md` сохраняют команды,
точные targets, бюджеты, остаток и причины остановки.

Повторённый `--raw-dir` вместо `--export` переиспользует проверенные пакеты.
Уже verified bodies не экспортируются. Независимые здоровые roots могут
продолжаться при блокерах соседей; indirect/unsupported/cycle/depth остаются
явными. Failed-function retries требуют отдельного review и не крутятся.
Статус `COLLECTED` означает собранный структурный raw-граф, не production-ready
или полное восстановление оригинальной функции.

## Живые результаты

- Подготовлены 9 ранее принятых функций, 245 full-symbol bytes. Их fresh
  `ExportLiftBatch` instructions/bytes/p-code operations точно совпали со всеми
  сохранёнными `research/lifted-ui/0*.json`; источник и source-consistency проверены.
- `CGameUI::scaledX @0xa83ea0`: полный symbol36 bytes, direct CALL
  `@0xa83eb4 -> CDynamicPropertyFile::GetFloat @0xc6e410` (symbol41 bytes).
  GetFloat имеет 4 недекодированных padding bytes, которые не скрываются.
- Root-export pipeline сам подготовил/exported scaledX, нашёл GetFloat,
  подготовил/exported зависимость и объединил граф: `COLLECTED`, depth2,
  2 bodies, 1 round, 5 sequential children, 0 promotions.
- При исходном raw-пакете принятых9 exported только scaledX: 1 body, 1 round,
  4 children; GetFloat reused. Оба запуска source-consistent, residual targets0.
  ABI/production-owner scaledX остаются **missing**, production_ready=false;
  compiler acceptance и перенос этой новой функции не заявлены.

Артефакты только в ignored cache и `/tmp/otl-lift-live-inputs/`:
`prepare-accepted-1`, `export-accepted-1`, `scaledx-from-root-1`,
`scaledx-pipeline-1`. Ghidra XML logger сохраняет известный diagnostic на
кириллическом пути; JSON/byte/target проверки завершились успешно. Exit launcher
сам по себе не используется как свидетельство успешной подготовки/экспорта.

## SDK и регрессии производственного кода

`tools/setup_pcre.py` восстановил локальный PCRE1 8.45 SDK в ignored
`build-source-cache/pcre-sdk`, сохраняя прежнюю host boundary CEGUI. Архив SHA-256
`4e6ce03e0336e8b4a3d6c2b70b1c5e18590a5673a98186da90d4f33c23defc09` —
[опубликованный mirror checksum](https://sourceforge.net/projects/pcre/files/pcre/8.45/pcre-8.45.tar.gz/download),
не проверенная авторская подпись. Source/compiler/configuration/artifact pins
записаны в installation.json. Исходники PCRE/CEGUI не исправлялись; builder
использует checked ASCII alias для libtool, `.pc` — quoted physical paths.
`make check`3/3 PASS; compile/link и CMake imported-target UTF8/Unicode/JIT probe PASS.

```sh
python3 tools/setup_pcre.py --download
PKG_CONFIG_PATH="$PWD/build-source-cache/pcre-sdk/lib/pkgconfig" \
  cmake -S . -B build-verification
```

Ядро и ui_game_state/save_selection/save_list/ui_scale probes собраны успешно.
Production state25 request/clear и panel-pause consumer проверки прошли.
Свежие native comparisons на неизменённых оригинальных bodies:
2112 UI writers + 2437 Continue + 2634 canLoad + 3357 scaledY/GetFloat =
**10540 случаев**, 0 mismatches. FP environment scaledY остаётся открытым;
X native calibration этим сравнением не выполнялась.

Pipeline19 и project-preparation9 узких checks зарегистрированы в CTest core.
Существующие full-приёмки сохраняют owners/ABI/implementation; CMake меняется
только регистрацией проверок. Пины обновляются после этой сверки, новые стадии
или completion не выставляются. Исторический массовый screen3162 не повторялся;
desktop/Android, UI-сценарии, performance и готовность всей игры не проверялись.
