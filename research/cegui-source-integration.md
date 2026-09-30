# CEGUI 0.6.2: исходная библиотека в рабочем главном меню

Срез 2026-09-30. Main/credits теперь исполняются исходной CEGUI, а не
собственными UiWindowRuntime/UiSkin. Остальные страницы ещё используют прежний
путь. Это подключение одного меню, не полное закрытие CMainMenu или всей игры.

## Закреплённые входы

- `library-derived`: upstream `cegui/cegui`, tag `v0-6-2`, commit
  `3ed5c719c3bb27b877b192e034ef2c0b05ea722c`. Архив SHA-256
  `fe7509fce6a16fc307032254e08cff70dce2f7eb5233ee57bc24bc27b733cc84`.
  Исходники находятся в `third_party/cegui-0.6.2`, MIT notices сохранены;
  происхождение и все локальные изменения — в `PATCHES.md`.
- `original-code`: внешний `Torchlight.bin.x86_64`, SHA-256
  `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`;
  внешний `lib64/libCEGUIBase.so.1`, SHA-256
  `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.
  Повторно проверены в этом проходе; shipped ABI не приравнивается к upstream.
- `resource-derived`: `media/UI/GuiLookSkin.scheme`, `GuiLook.looknfeel`,
  `mainmenuframe.layout`, перечисленные scheme imagesets/fonts и их
  изображения/TTF из внешнего `pak.zip`. Оригинальные данные не изменяются и
  не копируются в репозиторий. Текущие хеши — `cegui-source-inputs.json`.
- CEGUI собирается статически с исходным Falagard и Expat parser.
  Settings/Options и смена parser разобраны в [актуальном пакете](cegui-settings-options.md).
  FreeType 2.14.3 и PCRE 8.45 в проверенной Linux-сборке — библиотеки хоста;
  побитовый растр оригинальной версии FreeType не подтверждён.

## Повторно использованное и необходимые адаптеры

`cmake/CEGUI062.cmake` собирает библиотеку без OGRE, старого OpenGL renderer,
Lua, samples и загрузки модулей из каталога оригинальной игры. Статические
Falagard factories регистрируются исходной `registerAllFactoriesFunction`;
сама scheme загружается без удаления или переписывания XML-элементов.

`src/cegui_menu.cpp` реализует только платформенные границы:

1. ResourceProvider читает через `PakArchive::read_normalized`: ресурсы
   ссылаются на `media/ui/...`, ZIP хранит `media/UI/...`.
2. Renderer/Texture принимают уже обрезанные библиотекой quad-команды и
   RGBA-текстуры. DDS/PNG декодируют существующие декодеры. DPI=96 подтверждён
   shipped renderer в `ui-font-dpi.md`; предел atlas=4096 — портовая граница.
3. `GlesUiRenderer` загружает текстуры и рисует эти команды через существующий
   shader. Стабильный descending Z и оба quad split соответствуют upstream
   `RendererModules/OpenGLGUIRenderer/openglrenderer.cpp` / OGRE renderer;
   четыре угловых цвета передаются без flat-tint подмены. Объекты submitted
   frames удерживают CPU textures, GLES cache освобождает истёкшие владельцы.
4. Host передаёт позицию, down/up/leave и time pulse в `CEGUI::System`.
   Его окна, hit-testing, activation, capture, класс кнопки, font layout,
   clipping, RenderCache, Falagard и deferred teardown исполняются библиотекой.

Main не создаёт второе дерево в собственном UiWindowRuntime. Сохраняется
игровой флаг open; контейнер root/back/content принадлежит CEGUI.
Урезанные авторские fixtures без scheme используют прежний portable путь;
ошибка загрузки настоящей scheme не переключает приложение на него молча.

## Контроллер и исходный порядок

`original-code`, повторно использованное ASM-ревью:

- CDropdownMenu create `0xb196f0`: root/back/content, parent edges,
  RiseOnClick, pass-through, moveBack/moveFront и последующие Z-order flags;
  Main flags=1 остаётся model-null. См. `dropdown-container-lifecycle.md`.
- CMainMenu create `0xc52a10`, callsites `0xc52bd5..0xc52c34`: layout,
  масштаб offsets по height/768, mapToFunctions, подписки, attachment к root,
  сброс позиции layout. Повторный resize начинает с сохранённых UDim offsets,
  поэтому не накапливает масштабирование.
- mapToFunctions `0xa980e0`: существующий `map_ui_functions` получает
  настоящий CEGUI tree и выполняет child-first привязку enum.
- mapEventHandlers `0xb179e0`: child-first, WantsMultiClickEvents=true,
  MouseButtonDown, затем MouseDoubleClick. Обработчик `0xb194e0` принимает
  только Left; non-left ветвь `0xb1950d -> 0xb19610` возвращает true.
- CMainMenu onClick `0xc4ae80`: библиотечное событие вызывает существующий
  `dispatch_main_menu`, его результаты потребляются Frontend/Application.
  Credits/creditsB и настройки действуют на рабочий путь.
- CMainMenu update `0xc53b70`: ContinueLast получает canContinue от `.otc`
  адаптера; `.SVB`, selected object и сравнение модов остаются открытыми.

Очередь game callbacks потребляется после возвращения inject: это явный
портовый адаптер; эквивалентность произвольных reentrant SubscriberSlot не
заявлена. Ошибки CEGUI (не наследующие std::exception) переводятся в
std::runtime_error на публичной границе; приложение получает диагностику.
Повторное создание System после обычного teardown и ошибки scheme проверено.

## Учтённые различия библиотеки

Полный XML layout/scheme/looknfeel обрабатывает исходная библиотека. В частности,
Property body и игнорирование неизвестного onClick у ItemText уже есть upstream.
Два таких свойства Credits/CreditsB дают ожидаемые сообщения CEGUI; команды
принимают родительские CreditFrame/B. Ресурсные ошибки не исправлены подменой XML.

- `original-code`: четыре Serif-шрифта получают `|cAARRGGBB` / `|u`, как в
  `ui-inline-text.md` (shipped getTextExtent `0xd1dd0`, drawTextLine `0xd23d0`).
  Неполный tag остаётся текстом; полный malformed payload потребляется;
  исходный ColourRect восстанавливается на `|u` и границе physical line.
  `getCharAtPixel @0xd1830..0xd18df` после ASM-сверки оставлен upstream:
  caret посещает буквальные glyphs, включая символы display tags.
  Прежняя inferred-адаптация hit position удалена. Justified drawing остаётся
  согласующей адаптацией upstream без отдельного full-ревью shipped функции.
- `library-derived`: upstream FreeType уже использует FORCE_AUTOHINT;
  повторное восстановление этого механизма не потребовалось.
- `library-derived`: после Main исходный Expat модуль той же версии подключён
  для настоящего UTF-16 Options layout. Host runtime Expat 2.8.3; RAII cleanup
  исключений — явно обозначенная локальная адаптация. TinyXML больше не собран.

## Проверка и остаток

`original_cegui_mainmenu_contract` проверяет настоящий library load,
controller visibility, text/whitespace, zero-width Serif tags, отсутствие
второй компиляции main через UiSkin, input command delivery, non-left/invalid
buttons, Settings overlay, detach/reattach, resize, texture lifetime и повторный
System lifecycle. `cegui_error_boundary` проверяет malformed авторскую scheme,
перевод исключения и освобождение owners без ресурсов игры.

Исторический Main gate прошёл 9/9: 5 core (ошибка CEGUI, dropdown, XML Property,
function bindings, registry) и 4 assets (настоящий CEGUI Main, dropdown,
XML Property, function bindings). `torchlight_desktop` собран успешно.

Это CPU/library/resource проверки без окна и GL-контекста. Первый Main срез проверял только сборку Desktop/GLES. Settings/Options
пакет дополнительно выполнил ограниченный Application/GL smoke; performance
и покадровая parity по-прежнему не измерены. Остаток: остальные меню и HUD ещё на прежнем runtime;
native state/SVB/mod producers, OGRE scene/model families и полное сравнение
Runic vendor delta. Settings/Options теперь также на CEGUI; актуальные runtime проверки и точный
остаток — в `cegui-settings-options.md`. Character create теперь использует
тот же native System: [имя/класс и ввод](cegui-character-creation.md).
Load и HUD остаются на прежнем runtime. Completion игровых функций остаётся partial.
