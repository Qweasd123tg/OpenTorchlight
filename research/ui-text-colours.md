# Текст UI: цвета из ресурсов + граница тени (library-derived)

## Что сделано (resource-derived + library-derived)

- `TextColour` парсится как AARRGGBB hex (`FFFFFFFF`, `c2FFFFFF`=alpha 0xC2,
  `FFFF0000`, тултипные `FF64bcff`/`FF9df2ab`/`FFffeb9a`): 27 значений во всех
  layout. Дефолт — белый `Font::DefaultColour = 0xFFFFFFFF` из исходников
  CEGUI 0.6.2 (`src/CEGUIFont.cpp`, тег `v0-6-2`), вместо прототипного тёплого
  тинта. Disabled — тот же цвет ×0.55 (policy порта, не оригинал).
- Тень/обводка полностью из `GuiLook.looknfeel` (никакого подбора):
  `StaticText` и `StandardButton` — `DropTextColour` (+2,+2) + main;
  `StaticTextOutline` — кольцо 8×(±2) + main; `ItemText`/`Button` — один main.
  Парсер `UiResources::widget_text_passes` + `look_default`, рендер
  `draw_widget_text` идёт проходами по порядку. Проверка
  `frontend_resource_test` на настоящем pak: 2/9/1 проходов и дефолт
  `FF000000`.
- Неизвестные луки и неподдержанные `DimOperator` — честный фолбэк в один
  проход + диагностика, не выдуманная геометрия.

## Шрифт по умолчанию: Serif (original-code)

- `CGameUI::create` вызывает `CEGUI::System::setDefaultFont("Serif")`
  (вызов @`0xa9f016`, строка `Serif` в rodata @`0xfe4944`). Окна без `Font`
  (все кнопки главного меню) наследуют его.
- Порт раньше подставлял `FrizQuadrata`/`SerifSmall` — исправлено на `Serif`
  в `draw_widget_text` и подписях кнопок.
- Подписи `StandardButton`: тень (+2,+2) + main, оба `CentreAligned`
  (форматы тоже из looknfeel); цвет main — state-colours, у этого лука все
  `FFFFFFFF`, т.е. совпадает с белым дефолтом. Состояния текста других луков —
  открыто.

## Граница: тень текста (закрыта данными looknfeel)

Старый вопрос про пиксельный сдвиг снят: Falagard не гадает — оффсеты лежат в
`GuiLook.looknfeel` (`StaticText`/`StandardButton`: тень (+2,+2);
`StaticTextOutline`: кольцо 8×±2). ASM-ветка (`drawText+0x10 → d71d0`,
патченный CEGUI) этому не противоречит. Открыты: `|c..|u` инлайн-цвета,
ImageDim-луки (Tooltip и др. — честный фолбэк).

## Области текста лука (resource-derived, сделано)

- Парсер понимает `AbsoluteDim` и `UnifiedDim(scale, Width|Height)` с
  `Add/Subtract` (в т.ч. вложенными): Checkbox — 2 прохода `(W+5,+2/+0)` +
  degenerate wrap; StaticText — тень (+2,+2); Outline — кольцо; Button —
  тень; ItemText — один. Проверено пробой на настоящем looknfeel (Slider без
  TextComponent — немой; Tooltip/RadioButton/Titlebar/ListHeaderSegment/
  MenuItem с ImageDim — честный фолбэк + диагностика).
- Рендер кладёт текст в область лука: подпись чекбокса начинается за боксом
  (`x+w+5`) и бежит к краю вьюпорта; клип — область ∩ вьюпорт (контейнерный
  клип предков — открыто). До этого был фолбэк в 50px-бокс — рваные куски.
- Выдуманные подписи значений слайдеров убраны (в оригинале их нет —
  слайдер немой); бокс-контур остался плейсхолдером контрола.
- Antialiasing (FSAA, без чистого bool-мэппинга) — disabled footprint
  display-only, как слайдеры; покрыт PORT-примечанием.

## Выравнивание и клип (resource-derived, сделано)

- Layout выравнивают StaticText через `HorzTextFormatting`
  (Left/Centre/RightAligned + WordWrap*, 56 употреблений) и `VertFormatting`
  (Top/Centre/BottomAligned, 32). Голого `HorzFormatting` в shipped layouts
  нет вовсе — старый `text_style()` читал его и всегда падал в left/centre
  случайно. Теперь читаются настоящие имена (+ сабстринги под `*Aligned`).
- Парсер берёт per-TextComponent `VertFormat`/`HorzFormat type`:
  Checkbox Left/CentreAligned оба прохода, StandardButton Centre/CentreAligned,
  StaticText/ItemText — `*Property`, т.е. deferred к виджету. Формат лука бьёт
  свойство виджета; неуказанное остаётся виджету (дефолт CEGUI left/top).
- Убрана blanket-инъекция CentreAligned всем кнопкам (`draw`, бывшая 509):
  она уносила подписи чекбоксов на сотни пикселей вправо. Центрирование
  осталось только фолбэком для контролов без TextComponent в луке.
- Баг клипа: область считалась от `y` после цикла строк (низ текста) —
  подписи резались до волосков тени. Теперь от `top` до цикла.
- Фикстура `make_menu_fixture.py`: авторский Checkbox-лук с двумя проходами
  (тень +2, degenerate wrap, Left/Centre) + узкие боксы 50px; тест
  `gles_menu_text_test.py` стр.4 проверяет видимость подписей и отсутствие
  уползания вправо. Негативный контроль: возврат клип-бага роняет тест.
