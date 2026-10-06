# OpenTorchlight pass 7

Читать `REPORT_RU.md`. Краткая сводка: `results/summary.json`.

Новые прототипы: библиотечные рецепты CEGUI, схемы чтения ресурсов, инвентаризация эффектных таблиц и восстановление типизированных логических данных как C++98.

## Запуск всех проверок

```sh
python3 tools/run_checks.py /путь/к/распакованному/OpenTorchlight-main
```

Python 3.10+, GNU g++, Linux x86-64. Используется исходный архив, содержащий `research/original-symbols.txt`, `research/decompiled-core/` и `third_party/cegui-0.6.2/`. Вывод нельзя направлять внутрь исходного проекта. Игра и оригинальный ELF не запускаются; входные файлы не изменяются. Сборки здесь проверены GCC14.2, не исходным GCC4.4.7.

## Отдельные этапы

```sh
python3 tools/binding_recipes.py /путь/OpenTorchlight-main results/binding-recipes.json
python3 tools/resource_recipes.py /путь/OpenTorchlight-main results/resource-recipes.json
python3 tools/effect_table_inventory.py /путь/OpenTorchlight-main results/effect-table-inventory.json
python3 tools/check_cegui_recipes.py /путь/OpenTorchlight-main results results/binding-recipes.json
python3 tools/check_snapshot_roundtrip.py results
python3 -m unittest discover -s tests -v
```

`snapshot_to_cpp.py` работает только с уже подготовленным типизированным JSON; не читает чужую память. Пример схемы: `results/synthetic-original-tables.json`.

В комплекте нет оригинальной игры, сторонних библиотек, шрифтов или готовых бинарников. Все результаты — кандидаты/ограниченные проверки, не принятые игровые реализации. Перед размещением в decomp/src нужны штатные проверки проекта и исходный компилятор.
