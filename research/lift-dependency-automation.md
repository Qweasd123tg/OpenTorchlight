# Автоматический следующий пакет raw-зависимостей

2026-10-02. Продолжение [массового screen](function-lift-screening.md), без
модельных вызовов. `tools/lift_dependency_plan.py` строит следующий пакет;
`screen_function_lifts.py` выбирает и экспортирует его.

## Контракт и происхождение

`original-code`: ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Direct CALL и unconditional tail targets поступают из raw operations с адресом
инструкции и p-code index. Проверенные тела повторно не экспортируются. Общая
зависимость получает один target, сохраняя все roots и повторные sites.

`inferred`: очередь экспорта не является приёмкой семантики. Неизвестные и
interior адреса, unsized/конфликтующие aliases, indirect/userop, unsupported
operations и циклы остаются блокерами. ABI, поля и owners не выводятся.
Failed exports помечаются `retry`; повтор сам не исправляет границы Ghidra.
После исправления исходного missing-function вопроса объединение с
`--retry-failed` явно принимает verified re-export вместо прежнего
`missing_function`, сохраняя оба входа и audit record. Конфликтующие verified
тела по-прежнему отклоняются, включая этот режим.

`library-derived`: прежний Ghidra 12.1.3 / raw schema 2, `ExportLiftBatch.java`,
`-noanalysis -readOnly`, максимум 1024 entry на пакет. Новый decompiler,
полный анализ проекта и запуск игры не добавлены.

`--targets-file` допускает dependency-only symbols, включая библиотечные,
уже принятые и отсутствующие в coverage. Роль — `dependency_export`,
`selected_residual=false`. Перед Ghidra внешний ELF подтверждает exact entry
и единственный ненулевой размер T/t/W/w symbol; после экспорта сохраняются
прежние byte/hash gates и точное равенство manifest выбранным entry. Targets
защищены от записи и входят в SHA до/после. Пустые, повторные, некорректные
и превышающие limit списки отклоняются без усечения.

## Повторение

Переиспользуй raw-пакет текущей цепочки и начни чтение с `SUMMARY.md`:

```sh
python3 tools/screen_function_lifts.py --scope ui --limit 1024 \
  --raw-dir /tmp/ui-roots/raw --output /tmp/ui-plan-1
python3 tools/screen_function_lifts.py --limit 1024 \
  --targets-file /tmp/ui-plan-1/dependency-targets-000.txt \
  --export --output /tmp/ui-dependencies-1
python3 tools/screen_function_lifts.py --scope ui --limit 1024 \
  --raw-dir /tmp/ui-roots/raw --raw-dir /tmp/ui-dependencies-1/raw \
  --output /tmp/ui-plan-2
```

`dependency-plan.json` сохраняет roots/sites/блокеры; `dependency-targets-000.txt`,
`001.txt`, ... — дедуплицированные пакеты. Экспортируй их последовательно на
сохранённом проекте. При выборочных `--address` повтори исходные адреса при
объединении: dependency-export сам не создаёт residual roots. Следующий слой
обнаруживается после объединения, без повторного экспорта неизменённых тел.
Сводка показывает факт проверки внешнего ELF. Без raw/экспорта доступна только
очередь точных символов, без проверки исходных bytes.

## Проверено в этом изменении

Planner: 10 проверок; explicit selection/CLI: 15; screening: 25;
lifter: 32, включая компиляцию/исполнение C++ и UBSan fixtures. Проверены общие
roots/sites, 1025-target batching, helpers вне manual/coverage, retries,
indirect/cycle/unsupported, ошибочные symbols, actual ELF symbol fixtures,
объединение графа, SHA/согласованность входов и сохранение прежнего evidence.

Исправлен reject mismatch: внутренние RAM BRANCH/CBRANCH требуют восьмибайтовую
цель, как screen; ширины 1/2/4 отклоняются обоими путями. Const micro-branches
не изменены. Все девять принятых `research/lifted-ui` тел с прежним ABI
сгенерированы прежним и новым compiler; headers побайтно одинаковы, SHA-256
`8b8ec6db80f1b1309b3381d0f83956d1b2171eb2e66e7b6ec3b50dcb352d17ef`.
Новый header прошёл строгую C++17-компиляцию. `src/ui_game_state.cpp` с production
test собран и исполнен: 25 request/clear пар.
`compare_ui_game_state.py` прошёл 2112 случаев против двух неизменённых полных
оригинальных writer bodies, с наблюдением всего буфера. Он также заново сверил
все девять принятых instruction/symbol inputs с ELF. Exact targets нового
dependency-файла отдельно проверены по symbols и SHA настоящего ELF.

Восемь generated full-приёмок сохраняют исходные bytes, ABI, owners и consumers;
узкое изменение rejection не меняет их output. Пины compiler/test обновлены
после сверки. Ещё восемь panel-query приёмок затронуты только регистрацией
Python tests в CMake; production rules и тесты неизменны. Новые completion
или стадии не выставлены.

В первом проходе отсутствовали прошлые raw batches и Ghidra cache; конфигурация
сборки остановилась на отсутствующем `libpcre`. Следующий проход восстановил
инструмент и локальный PCRE SDK, собрал ядро и проверил живой ограниченный цикл:
[актуальное подключение pipeline](lift-pipeline-live.md). Исторические
3162/1541/475 заново не утверждаются. GUI, кадры, performance и готовность
всей игры этим изменением не проверяются.
