# P1 — оригинальный масштаб layout (CGameUI::convertToScreenScale)

Статус: `original-code` для арифметики преобразования; подключение — только
подтверждённые места загрузки; жизненный цикл ресайза — эквивалент
`CGameClient::rescaleUI` (пересоздание из нетронутого документа).

## Входы

- ELF `Torchlight.bin.x86_64`, SHA-256
  `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`
  (совпадает с зафиксированным в аудите; проверено `sha256sum` 2026-09-17).
- Функции: `convertToScreenScale @0xa83ed0` (0x172 байт), `scaledX @0xa83ea0`,
  `scaledY @0xa83e70`, константы `768.0f @0xfa4804`, `1/1024 @0xfa4808`,
  событие-подписка не входит в P1.
- Декомпиляция: `research/decompiled-core/game_ui.c:1256-1346`
  (рекурсия по детям, затем getPosition/scale/setPosition,
  getSize/scale/setSize; обе ветви флага).

## Воспроизведение (2026-09-17, повтор аудита)

Команда (без PIE-хоста, прямой python3 хватил; при EEXIST использовать
`research/ui-audit-2026-09-17/tools/python_pie.c` по README комплекта):

```bash
python3 probe_original_ui.py \
  --elf "/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64" \
  --output original-ui-probes.json
```

Результат: pause 682/682, click 48/48
(`EventMouseButtonDown @0x14247e0`), scale 400 деревьев / 1200 узлов /
9600 float-полей побитово, порядок «дети раньше родителя», повторное
применение 390 -> 548.4375 -> 771.240234375. Полный вывод:
`research/ui-scale-p1/original-ui-probes.rerun-2026-09-17.json`.

Дефект порта до исправления (настоящая `libtorchlight_core.a`, проба
`research/ui-audit-2026-09-17/tools/probe_port_ui.cpp` + `-lfreetype`):

```bash
c++ -std=c++17 -I include tools/probe_port_ui.cpp build-ui/libtorchlight_core.a \
  -lpng -lz -lfreetype -o /tmp/opencode/probe/probe-port-ui
/tmp/opencode/probe/probe-port-ui game/pak.zip
```

`research/ui-scale-p1/port-ui-probe.before-p1.tsv`: ширина TopFrame 390 на
всех разрешениях (1024x768, 1280x720, 1920x1080, 2560x1440); PlayButton в
обычном `UiHud::frame` (это D04, относится к P4, здесь не трогаем).

## Что изменено (коммит P1)

- `include/torchlight/ui_screen_scale.hpp`, `src/ui_screen_scale.cpp` (новое):
  `ui_screen_ratio` (YRATIO=H/768, XRATIO=W/1024), `ui_scale_area_offsets`
  (индексы 1,3,5,7), `ui_scale_vector_offsets` (индексы 1,3),
  `ui_screen_scale_for_layout` — таблица 10 подтверждённых `false`-вызовов;
  неизвестные layout возвращают `nullopt` (без выдуманного масштаба).
- `include/torchlight/ui_layout.hpp`, `src/ui_layout.cpp`: перегрузка
  `resolve(w, h, ratio)`; масштабируются свежераспарсенные pristine-значения,
  документ не мутируется, накопления нет; `resolve(w, h)` = ratio 1.
- `src/ui_hud.cpp`: `UiHud::frame` резолвит bottomhud с YRATIO
  (`CGameUI::create`, game_ui.c:9464).
- `tests/ui_screen_scale_test.cpp` + регистрация в CMake (label `core`):
  28 проверок против записанных нативных литералов (390/365.625/548.4375/
  731.25/389.4921875), негативный контроль legacy-resolve, отсутствие
  накопления, политика layout, ветви UnifiedPosition/UnifiedSize.
- `src/frontend.cpp` намеренно не тронут: политика меню не подтверждена.

## Граница

Сравнение покрывает 8 float UDim (позиция/размер) до исполнения CEGUI:
финальные прямоугольники, округление, autoscale, рендер и уведомления
`setSize` не заявляются. Шрифты вторым множителем не домножаются.
Ветка `true` (XRATIO) реализована и протестирована на уровне converter,
но ни один экран её пока не запрашивает — таких вызовов в подтверждённом
списке нет.
