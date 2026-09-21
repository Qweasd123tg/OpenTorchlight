# Автоматизация без модели

Статус: `port-native tooling`, не новое доказательство поведения игры.
Все команды работают локально: Python standard library, Git, CMake/CTest,
Ninja, GNU binutils. API моделей, ключи, сервисы и сеть не требуются.

Основной маршрут восстановления функций/семейств и отдельная приёмка полного
закрытия — [codefirst-tooling.md](codefirst-tooling.md). Этот файл описывает
вспомогательные проверки и экспорты, а не задаёт feature-first очередь.

## Готовые инструменты вместо отдельного движка автоматизации

- [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html): JSON discovery,
  точный выбор тестов, fixtures, JUnit (для driver нужен CTest >=3.21).
  Используется экранированный anchored `-R`, а не более новый `--tests-from-file`.
- [Ninja](https://ninja-build.org/manual.html): `-t targets all` и `-t inputs`
  (последний с Ninja 1.11) дают уже существующий граф сборки. Если инструмент
  или граф недоступен, выбор расширяется до полной запрошенной группы.
- GNU `nm`/`objdump`: индекс прямых CALL из ELF. Ghidra headless остаётся
  отдельным источником более глубокого анализа; установка Ghidra для нового
  экспортёра не нужна. BSim может находить кандидатов сходства, но не доказывает
  равенство и не является обязательной зависимостью этих команд.

## Проверка изменённой части

Обычный цикл — сборка затронутого кода и узкая проверка установленного контракта:

```sh
python3 tools/check.py --core --test ui_layout_property
python3 tools/check.py --assets /path/to/game --test original_ui_layout_property
```

`--test NAME` повторяется для нескольких проверок. Выбор включает необходимые
fixtures и записывается как частичный: такой отчёт описывает только выбранные
контракты. Опечатка или имя вне выбранных групп завершают команду ошибкой.
`--core` конфигурирует render/desktop OFF. Позиционный каталог игры выбирает
core/assets/reference. UI-клики, кадры и сквозные сценарии вынесены в группы
render/desktop; они выполняются отдельной явно запрошенной задачей через
`--render`, `--desktop` или `--all`. Fixture-зависимость требует того же явного
выбора интеграционной группы.

Для отдельной задачи общей регрессии доступен baseline и выбор по изменениям:

```sh
python3 tools/check.py --core --report build-verification/baseline.json
python3 tools/check.py --core --since-report build-verification/baseline.json \
  --plan --report build-verification/selection.json
python3 tools/check.py --core --since-report build-verification/baseline.json \
  --report build-verification/changed.json
```

Либо изменения относительно коммита, включая index/worktree/untracked:

```sh
python3 tools/check.py --core --changed HEAD --plan \
  --report build-verification/selection.json
```

Выбор делается только внутри явно запрошенных групп. Для настоящих ресурсов
и оригинальных сравнений добавляются прежние `--assets /path/to/game` и
`--reference /path/to/game/Torchlight.bin.x86_64` во все команды этой серии.
Непереданная группа не считается проверенной. `--plan` конфигурирует CMake
и читает discovery/граф, но ничего не собирает и не запускает тесты.

Граница первой версии намеренно консервативна:

- сужать выбор можно по известным графу C/C++ translation units;
- headers, Python/shared helpers, ресурсы, правила сборки, неизвестные или
  удалённые неизвестные файлы возвращают полный набор запрошенных тестов;
- script-тесты с непрозрачными runtime-зависимостями остаются в наборе;
- если build-зависимости выбранных скриптов не доказаны, собирается `all`;
- общая статическая библиотека может затронуть много тестов: точечность не
  выдумывается. Для дальнейшего ускорения сначала нужны явные контракты
  тестов/более мелкие библиотечные цели, а не угадывание по имени файла;
- fixture setup/cleanup и DEPENDS включаются; пропущенный CTest не становится PASS.

`--since-report` принимает только полноценный успешный baseline для всех
запрошенных групп с теми же входами и CMake-конфигурацией. Старый отчёт без
идентичности исходников, частичная проверка или изменившаяся конфигурация
возвращают полный прогон. Baseline нельзя перезаписать тем же вызовом.
`NOT AFFECTED` означает отсутствие выбранной работы, **не свежий полный PASS**.
Для code-first транша выбираются проверки изменённого контракта через `--test`.
Полный прогон выбранных групп используется при задаче общей регрессии.

## Идентичность и актуальность

Отчёт содержит SHA-256 содержимого всех tracked и nonignored untracked файлов,
включая executable mode и удаления. Для symlink хешируется сама ссылка, не
внешний объект. Проверка до и после прогона запрещает выдавать изменившийся
во время тестов код за проверенный. HEAD записывается, но не заменяет content
fingerprint. Оригинальные pak/ELF по-прежнему хешируются отдельно.

Отчёты, пакеты и generated indices писать в ignored build-каталог либо `/tmp`,
не поверх исходников/реестров/оригинальных входов. Отпечаток намеренно включает
документацию и evidence: изменение границы тоже делает прежний отчёт историей.

## Пакет исследования из ELF без Ghidra

Оригинал: SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Экспортёр проверяет его до запуска декодирования. Оригинальная игра не запускается.

```sh
python3 tools/export_callsites.py \
  --original /path/to/game/Torchlight.bin.x86_64 \
  --out build-verification/research/original-callsites.tsv
python3 tools/function_package.py --address 0xb4eb70 --address 0xb569e0 \
  --callsites build-verification/research/original-callsites.tsv \
  --out build-verification/inventory-packet.md \
  --json-out build-verification/inventory-packet.json
```

TSV совместим с полями прежнего Ghidra-экспорта. Sidecar `.meta.json` хранит
хеши ELF/TSV, версию binutils, косвенные и неатрибутированные вызовы, ограничения.
Caller определяется границей sized ELF symbol, не восстановленным CFG. Сортировка
по адресам не является порядком исполнения; branch predicates, tail calls и
виртуальные цели не восстанавливаются. Полный индекс — локальный generated cache,
не полный дамп функций и не файл для коммита. Пакеты ограничены 1–64 явно заданными
входами; подробности: [scripted-packets.md](scripted-packets.md).

## Вторичный отчёт smoke/compatibility

```sh
python3 tools/readiness.py \
  --report build-verification/baseline.json \
  --json build-verification/readiness.json \
  --markdown build-verification/readiness.md
```

Можно повторить `--report` для нескольких прогонов. Исторические отчёты без
fingerprint помечаются UNKNOWN; несовпадающий исходный код — STALE; план —
PLAN ONLY. Ничто из этого не подтверждает текущий код. Для одной проверки
актуальные результаты выбираются по времени завершения; свежий FAIL не
перекрывается более старым PASS. Выход 0 означает успешно построенный отчёт,
а не готовую игру. `release_readiness` явно NOT ASSESSED, `release_ready=false`:
этот отчёт не аттестует fidelity целых функций даже при зелёных capabilities.
`capability_scope_ready` относится только к перечисленному функциональному срезу.

`research/capabilities.json` — вторичный реестр текущих поведенческих срезов,
связанных исходников, evidence, именованных тестов и блокеров. Он не полный
список всех требований (`scope_complete=false`), поэтому процент и готовность
к выпуску не выдумываются. Тесты не повышают declared stage и не удаляют blockers.
Старые large-N документы остаются историей, а не конкурирующими текущими отчётами.

## Приёмка

`deterministic_automation`, `function_package_automation` и `codefirst_tools`
входят в группу core.
Помимо негативных проверок, первый тест создаёт маленький Git/CMake/Ninja проект
с двумя независимыми executable: полный baseline → plan/no changes → изменение
одного `.cpp` → одна цель/один тест → неизвестный файл → полный fallback.
Это доказывает механизм выбора, не обещает такое же ускорение монолитного
`torchlight_core`. Число функций/пакетов/зелёных тестов не процент готовности игры.
