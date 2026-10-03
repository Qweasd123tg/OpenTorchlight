# Массовая проверка возможности генерации исходных функций

> **Заморожено 2026-10-03.** Действующий процесс — [decomp](../decomp/README.md) и [AGENTS.md](../AGENTS.md). Документ остаётся справочником по поведению; его процессные указания (контракты, стадии, пакеты, очереди) не действуют.

2026-10-02. `original-code`: внешний read-only ELF
`Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`library-derived`: Ghidra 12.1.3, закреплённые установка и проект из
[decompiler-workflow.md](decompiler-workflow.md) и
[pcode-automation.md](pcode-automation.md). Архив инструмента SHA-256
`93a5d11a9ad510622acaaf908c556a7b9b764d338e78a7567f3689bf5081fd54`.

## Принятая граница

`tools/screen_function_lifts.py` выбирает residual `manual_reverse` из
`auto_triage.build(root,4)`, ограничивает экспорт точными sized symbols и
исключает только актуальные full/closed приёмки. Stale/invalid full снова
попадают в очередь. UI scope задаётся `research/ui-contour.json`, а не
неявной группой имен из старого отчёта.

`tools/ghidra/ExportLiftBatch.java` выгружает raw schema-2 operations без
decompiler, повторного analysis и записи проекта: `-noanalysis -readOnly`.
Каждый пакет ограничен 1024 функциями. Проверяются исходный ELF SHA,
точный entry/symbol range, все instruction bytes, отсутствие пересечений,
instruction/address hash и SHA полного ELF symbol, включая padding.
Неэкспортированные bytes сохраняются как явная граница; удача preflight
сама по себе не доказывает, что padding недостижим или весь контракт разобран.

Четыре последовательных экспорта 1024/1024/1024/90 покрыли **3162** тела
тогдашней остаточной ручной очереди. Отдельный UI экспорт содержит **226**.
В объединении всех четырёх пакетов:

| Проверенное свойство | Функций |
|---|---:|
| Raw packets с проверенными оригинальными bytes | 3162 |
| Локальные operations проходят структурный preflight | 1541 |
| Также доступна поддерживаемая transitive call/tail closure | 475 |

Это `inferred` возможность генерации, не перенос или completion. Screen
не придумывает ABI, значения регистров, memory owners или targets виртуальных
вызовов. Без отдельного reviewed ABI/owner mapping он не даёт production-ready
функций. Блокеры включают неподдержанные opcode/width/space, отсутствующий
fallthrough, indirect/userop dependencies, recursion/depth и недоступные тела
прямых или tail зависимостей. `reason:*` считает появления блокеров в цепочках,
а не уникальные функции.

## Повторение и объединение

Выбор без экспорта сохраняет selection report; `--export` использует
закреплённый сохранённый проект. Запускай следующие пакеты последовательно
с отдельным output, чтобы один проект не анализировался конкурирующими jobs:

```sh
python3 tools/screen_function_lifts.py --scope all --limit 1024 --offset 0 \
  --export --output build-verification/lift-screen/batch-0
python3 tools/screen_function_lifts.py --scope all --limit 1024 --offset 1024 \
  --export --output build-verification/lift-screen/batch-1
python3 tools/screen_function_lifts.py --scope all --limit 1024 --offset 2048 \
  --export --output build-verification/lift-screen/batch-2
python3 tools/screen_function_lifts.py --scope all --limit 1024 --offset 3072 \
  --export --output build-verification/lift-screen/batch-3
python3 tools/screen_function_lifts.py --scope all --limit 1024 \
  --raw-dir build-verification/lift-screen/batch-0/raw \
  --raw-dir build-verification/lift-screen/batch-1/raw \
  --raw-dir build-verification/lift-screen/batch-2/raw \
  --raw-dir build-verification/lift-screen/batch-3/raw \
  --output build-verification/lift-screen/joined
```

Повторённый `--raw-dir` соединяет graph по точным entry. Одинаковые packets
переиспользуются; конфликтующие дубликаты отклоняются. Selected counts относятся
к выбранному ограниченному пакету; `raw_packet_counts` описывает все supplied
packets, включая dependency-only rows. Поэтому selected1024 и supplied3162
не означают потерю функций. Поздняя приёмка сокращает residual selection,
но не удаляет ранее проверенные raw packets из объединения.

Accepted snapshot выгружен в `/tmp/otl-all-lift-screen-20261002-{0,1,2,3}/raw`;
повторная проверка объединения —
`/tmp/otl-all-lift-screen-20261002-joined/report.json`. Generated raw data,
targets, graph reports и логи остаются в ignored build или `/tmp`. JSON хранит
SHA всех прочитанных входов/packets, exact symbol/instruction verification,
closure reasons и source-consistency. После правок повторяется raw-only анализ,
а не Ghidra экспорт неизменённых исходных функций.

Отдельная команда `--scope ui --limit 1024 --export` готовит текущий UI contour.
Callsite index может отсутствовать; screen явно сообщает это и извлекает CALL,
tail, indirect и userop зависимости из raw operations. Старый список функций
без индексированных CALL не используется как доказательство leaf/closure.

## От генерации к рабочему переносу

Автоматический [план следующего dependency-пакета](lift-dependency-automation.md)
пишется в `dependency-plan.json` и `dependency-targets-*.txt`; короткий вход —
`SUMMARY.md`. `--targets-file` экспортирует также библиотечные/принятые helpers
вне residual manual selection. Затем объедини новые raw с исходными roots
повторным `--raw-dir`, чтобы обнаружить следующий слой без повторного анализа.

Следующий пакет выбирается по текущей производственной цепочке из closure
candidates, после разбора всех полей/ветвей/вызовов и reviewed bindings.
`--abi` принимает только настоящий явный descriptor и дополнительно проверяет
lowering компилятором; не подставляет шаблонные входы. Source-consistency,
byte verification и opcode support не заменяют это ревью.

Через этот путь уже приняты новые Main canLoad и scaledY -> GetFloat:
[generated-save-list.md](generated-save-list.md),
[generated-ui-scale.md](generated-ui-scale.md). Их consumers подключены,
сравнение исполняет неизменённые полные тела, а реестр меняется вручную по
контракту. Screen всегда сохраняет `original_status_promotions: 0`.
Измерение ускорения разработки и производительности игры этим проходом
не выполнялось; запуск GUI, клики и кадры не входят в проверку.
