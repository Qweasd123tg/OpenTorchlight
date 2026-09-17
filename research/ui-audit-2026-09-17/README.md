# Исследовательский комплект интерфейса OpenTorchlight

Сначала читать `АУДИТ_СООТВЕТСТВИЯ.md`, затем `ПЛАН_ПАТЧЕЙ.md`. `ЗАДАНИЕ_АГЕНТУ.txt` — готовая передача первых двух ограниченных исправлений разработчику. **Готовых игровых diff в этом комплекте нет.** Предыдущий UI patchset не нужно повторно применять к уже изменённой ветке.

Оригинальные игровые архивы, ELF, библиотеки, изображения и шрифты сюда не включены. JSON содержит полученные из них метаданные и результаты. Инструменты читают внешние файлы; не запускают игру и не изменяют пользовательские сохранения.

## Содержание

`АУДИТ_СООТВЕТСТВИЯ.md` — находки D01–D07, подтверждения, ограничения и поправка к прежнему патчу события мыши.

`КАРТА_ИСТОЧНИКОВ.md` — файлы и строки чистого large-14 и версии с прежним patchset; адреса оригинальных функций. Полные хеши в `results/source-map.json` и `results/original-symbols.json`.

`ПЛАН_ПАТЧЕЙ.md` — P0–P8: масштаб, события, пауза, HUD, CEGUI, оригинальный инвентарь, предметные действия, остальные окна.

`tools/scan_ui_resources.py` — независимый от проекта XML-сканер, стандартная библиотека Python. Метаданные, не процент соответствия.

`tools/probe_original_ui.py` — изолированное исполнение оригинальных x86-64 функций. Область проверок и подменённые зависимости указаны в docstring и JSON. Требует Linux x86-64, 4096-байтных страниц, `nm` и конкретного ELF. Не запускать с `-O`.

`tools/probe_port_ui.cpp` — вызов настоящих UiLayout/UiHud текущего проекта. `tools/probe_inventory_assets.cpp` — чтение скелетов штатным парсером проекта. Оба — диагностика, не новые игровые модули.

`results/verification.json` — реально исполненные проверки, ошибка полной Release-сборки и явные неисполненные части. Результаты не складывать в «полный процент готовности».

## Сканирование pak

```bash
python3 tools/scan_ui_resources.py \
  --pak "/путь/к/pak.zip" \
  --output "/папка/результатов/resource-manifest.json"
```

Сканер ничего не исправляет внутри XML. Файлы с UTF-16 декодирует явно. Метаданные редакторских дубликатов не выдаются за число активных элементов игры.

## Оригинальные функции

```bash
python3 tools/probe_original_ui.py \
  --elf "/путь/к/Torchlight.bin.x86_64" \
  --output "/папка/результатов/original-ui-probes.json"
```

Скрипт проверяет SHA-256 ELF и адреса/размеры методов до исполнения. Копирует только выбранные инструкции в память отдельного процесса. `MAP_FIXED_NOREPLACE` запрещает перезапись существующих отображений; после копирования код становится RX. Полный executable loader, глобальные конструкторы и игра не запускаются. Запускать без root.

### Когда Python занимает нужные адреса

В этой среде обычные Python-executable были non-PIE и занимали страницу оригинального метода `0x56e000`. Проба корректно отказала с EEXIST. **Не заменять MAP_FIXED_NOREPLACE на MAP_FIXED и не отключать защиту.** Использовать PIE-хост с системной shared-библиотекой Python:

```bash
cc -fPIE -pie tools/python_pie.c \
  $(python3-config --includes --embed --ldflags) \
  -o /tmp/opentorchlight-python-pie

/tmp/opentorchlight-python-pie tools/probe_original_ui.py \
  --elf "/путь/к/Torchlight.bin.x86_64" \
  --output "/папка/результатов/original-ui-probes.json"
```

Нужны development headers и shared lib Python, соответствующие `python3-config`. Ничего не устанавливается автоматически. В данном проходе использован именно такой хост. Если адреса всё равно заняты, проба должна отказать, а не перезаписывать память процесса.

## Пробы текущего порта

Сначала собрать ядро текущего проекта обычным способом. Здесь для исследовательской копии применялись:

```bash
cmake -S "/путь/к/проекту" -B "/папка/build" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DTORCHLIGHT_GAME_DIR="/папка/оригинальной/игры" \
  -DTORCHLIGHT_ORIGINAL="/папка/оригинальной/игры/Torchlight.bin.x86_64" \
  -DTORCHLIGHT_ENABLE_DESKTOP=OFF

cmake --build "/папка/build" --target torchlight_core --parallel 4
```

В исходном проекте использовался статический core без FreeType/GLES SDK. Для этой конфигурации пробы связываются так:

```bash
c++ -std=c++17 -Wall -Wextra -Wpedantic -Werror \
  -I "/путь/к/проекту/include" tools/probe_port_ui.cpp \
  "/папка/build/libtorchlight_core.a" -lpng -lz \
  -o /tmp/probe-port-ui

/tmp/probe-port-ui "/путь/к/pak.zip" > "/папка/результатов/port-ui-probe.tsv"

c++ -std=c++17 -Wall -Wextra -Wpedantic -Werror \
  -I "/путь/к/проекту/include" tools/probe_inventory_assets.cpp \
  "/папка/build/libtorchlight_core.a" -lpng -lz \
  -o /tmp/probe-inventory-assets

/tmp/probe-inventory-assets "/путь/к/pak.zip" > "/папка/результатов/inventory-asset-probe.tsv"
```

Для другой конфигурации core дополнительные библиотеки брать из её link interface/CMake, не копировать эту строку как универсальную. Только целевой `torchlight_core` собран успешно; попытка полного Release-build в этой среде остановилась на двух `-Werror=maybe-uninitialized` в application.cpp. Это не скрыто под общим «сборка прошла».

Выбранные существующие тесты после прежнего patchset:

```bash
cmake --build "/папка/build" --target ui_hud_input_test ui_image_clip_test --parallel 4
ctest --test-dir "/папка/build" --output-on-failure \
  -R '^(ui_image_clip|ui_hud_input|original_ui_hud_input)$'
```

Они проходят на старом поведении. В частности, тест HUD проверяет собственную release-политику и потому **не опровергает** найденную исходную подписку MouseButtonDown. Это наглядный пример разницы между регрессией и соответствием оригиналу.

## Контроль комплектности

Из корня этого комплекта:

```bash
sha256sum -c CHECKSUMS.sha256
```

Хеши пакета не являются хешами готовой игры. Скомпилированные probe-бинарники сюда не включены: собираются локально из предоставленного кода.
