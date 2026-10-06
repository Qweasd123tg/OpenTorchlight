# OpenTorchlight pass 5 — read-only analysis prototypes

Сначала прочитайте `REPORT_RU.md`: результаты не являются восстановленным кодом или доказательством эквивалентности.

## Файлы

- `scripts/archive_census.py` — статистика архивного псевдокода и fan-in исходного графа вызовов.
- `scripts/effect_regions.py` — экспериментальный обычный CFG, кандидаты областей и места вызова с управляющими зависимостями.
- `scripts/test_stage_tools.py` — 12 синтетических тестов инструментов.
- `results/summary.json` — небольшая сводка.
- `results/archive-census.json`, `results/effect-regions.json` — полные результаты по присланному архиву.
- `results/unit-tests.log` — результат самопроверок.
- `results/integrity-and-environment.json` — контроль исходных файлов и окружение.
- `results/pip-angr.log` — неудачная установка angr (сетевая недоступность). SAILR не запущен.

## Запуск

Нужны Python 3 и совместимая с ним версия NetworkX. Проверено здесь на NetworkX 3.6.1. Скрипты только читают проект; выходной каталог должен находиться вне исходников.

```bash
python3 -m venv .venv
. .venv/bin/activate
python3 -m pip install networkx==3.6.1

ROOT=/absolute/path/to/OpenTorchlight-main
OUT=/absolute/path/to/pass5-results
mkdir -p "$OUT"

python3 scripts/archive_census.py "$ROOT" "$OUT/archive-census.json"
python3 scripts/effect_regions.py "$ROOT" "$OUT/effect-regions.json"
python3 scripts/test_stage_tools.py
```

Оригинальный ELF для этих двух архивных анализаторов не требуется. Для настоящей интеграции новых этапов он потребуется; нельзя принимать кандидатов по одному архивному графу.

Не копируйте результаты в `decomp/src` и не используйте их как реестр завершённости. Исключения, память, вызовы без возврата, косвенные переходы и полнота листингов не доказаны. Не складывайте размеры пересекающихся областей.
