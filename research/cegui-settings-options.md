# Settings/Options через исходную CEGUI

Проверено 2026-09-30. Это подключённая UI-цепочка, completion игровых
функций остаётся `partial`.

## Входы и повторное использование

ELF `Torchlight.bin.x86_64` SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`;
`libCEGUIBase.so.1` —
`57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.
Новый проверенный вход `libCEGUIExpatParser.so` —
`7fcde2e0baf1a8d3d483ee54df1dd73d4e3de22c9a5a81043c6513bcfff9ff1f`.
Хеши layout и локального vendor tree — в `cegui-source-inputs.json`.
Оригинал и pak остаются только для чтения.

`library-derived`: используется тот же upstream CEGUI 0.6.2 commit
`3ed5c719c3bb27b877b192e034ef2c0b05ea722c`, включая ExpatParser из
`XMLParserModules/expatParser`. Поставляемый игрой модуль действительно
зависит от `libexpat.so.1`. `parseXMLFile @0x3120` создаёт Expat parser
@0x313c, устанавливает element/character handlers @0x3171/0x3180,
передаёт ResourceProvider buffer напрямую в XML_Parse @0x31e4, final=true.
Поэтому UTF-16 `optionsmenu.layout` читает исходная библиотека без
переписывания ресурсов. Host runtime — Expat 2.8.3. При отсутствии SDK
используются неизменённые MIT public headers из официального
[R_2_8_3](https://github.com/libexpat/libexpat/tree/R_2_8_3/expat/lib);
сам Expat не копируется в репозиторий. Старый TinyXML больше не собирается.
Локальная адаптация Expat-модуля освобождает parser и raw resource также
при исключении из ResourceProvider/XMLHandler; обычные callbacks и XML
разбирает библиотека. Различия полного vendor ABI не закрыты.

## Контракт и производственное подключение

- `original-code`: `CSettingsMenu::createMenus @0xbd6ea0` загружает layout,
  вызывает scale(false) @0xbd705d, mapToFunctions @0xbd7069 и child-first
  mapEventHandlers @0xbd7074. Layout прикрепляется к content @0xbd7079..
  0xbd7080. Native wrapper в `CeguiMenu::Impl` сохраняет root/back/content,
  свойства контейнеров и неизменные исходные UDim position/size для resize.
  Scale выполняется child-first, setPosition перед setSize, четыре offsets
  умножаются на height/768, как a83ed0. Pristine geometry — адаптация
  resize вместо исходного уничтожения/recreate UI; все rescale side effects
  целиком не заявляются.
- `original-code`: create @0xbd7fbd..0xbd80e9 задаёт AlwaysOnTop,
  auto-arm=true, single-click=true и ClippedByParent=false трём реальным
  ComboDropList; не root. `HardwareSkinning` скрывается @0xbd8027.
  Checkbox/Slider/Combobox/Thumb/scrollbar state, clipping, capture,
  activation и события принадлежат CEGUI, без второго UiWindowRuntime tree.
- `original-code`: constructor @0xbd86a9 читает UTF-32LE `Settings`
  @0xff10a0, вызывает `setTitle @0xbd86e0`; setTitle @0xb17e70 делает
  Window::setText @0xb17f87. Native Title получает эту английскую строку.
  Полная CStringTranslate/localization цепочка остаётся открытой.
- `original-code`: Settings setOpen @0xbd5560 открывает без OPEN/CLOSE
  анимации: content.position=0 @0xbd562a, addChild @0xbd5637, moveToBack
  @0xbd5640, затем значения 12 checkbox, 2 slider и 3 combobox. Повторный
  open не переписывает текущие значения. Close отсоединяет сохранённый root.
- `original-code`: FSAA — setSelected(value!=0) @0xbd5692..0xbd56a1;
  Apply пишет checkbox bool `0/1` @0xbd53c6..0xbd53d4. Значения 2/4/8
  не придуманы. Music/Sound slider maximum=1 @0xbd5801/0xbd5827.
- `original-code`: shadow text из constructors @0xbd0795..0xbd082d:
  UTF-32LE @0xfe4dc4/0xfe4f20/0xfe4dd4/0xfe4de4/0xfe4e00/0xfe4f58
  дают `Off`, `Lighting Only`, `Low`, `Medium`, `High`, `Very High`.
  Эти строки заменяют прежние описательные приближения. Particle Low/
  Medium/High читает те же три literals @0xbd084b..0xbd088f.
- `original-code`: Resolution ID — индекс предоставленного settings modes
  массива; текст `width + " x " + height`, default row0 @0xbd692e,
  затем точное совпадение. Host mode enumeration остаётся платформенным
  входом с положительными, дедуплицированными режимами. Hotplug заменяет
  этот вход, не добавляет выдуманные режимы.
- `original-code`: shadow ID0..5 и particle ID0..2 применяют подтверждённые
  таблицы из `ui-combobox.md`. Повторная ASM-сверка targets ff10c8 исправила
  прежнее приближение: shadow0/1 тоже пишут resolution128 через bd52f4 ->
  bd4edf -> bd4f02, даже при выключенных тенях. Particle при открытии выбирает первую строку
  с table FPS >= stored FPS @0xbd6656..0xbd665f, иначе сохраняет row0.
  При Apply Netbook @0xbd4a11..0xbd4a42 принудительно выключает FSAA,
  RenderBehind, Rimlights, выбирает shadow0; @0xbd4c58..0xbd4c62 выбирает
  particle0 (20 FPS, 10 percent). HardwareSkinning сохраняется отдельно.
- `original-code`: `CGameUI::sizeComboList @0xa849d0..0xa84bc2` переносится
  через реальные `Listbox::getTotalItemsHeight`, editbox height и NamedArea
  `ItemRenderingArea[HScroll]`. Формула: totalItems + editHeight +
  (listHeight-areaHeight) + rounded(listY.scale*comboHeight)+listY.offset-
  editHeight. Знак округления ±0.5 и float32 порядок сохранены. `Rect` в
  этом ABI хранит top/bottom перед left/right; @0xa84af3..0xa84b17 вычитает
  именно высоту. Не используются прежние fallback font/frame числа.
- `original-code`: Settings onClick @0xbccb20, 0x3d bytes: open=false
  ничего не делает; accept9 устанавливает +0xc1, accept9/decline8 — +0x32,
  затем virtual setOpen(false); остальные команды тоже закрывают. Update
  @0xbd47e0 читает сохранённые controls после close, live audio preview
  @0xbd487d..0xbd489d, Cancel restore @0xbd5090..0xbd512f.
  `Frontend::native_action` получает sender page, собирает настоящий widget
  state и закрывает Settings; Apply передаёт typed payload существующему
  Application -> UTF-16 settings writer -> `applied()` consumer. Cancel
  возвращает saved fields. Mouse callbacks доставляются после inject;
  отделение persistence transaction и возврат к opening page — portable
  policy, не перенос +0x30..0x32 native pending flags побитово.
- `original-code`: CGameUI constructors @0xaa3666 передают Options родителя
  Ingame UI Sheet (+0x488); @0xaa36e0 и @0xaa4016 передают Settings/Main
  Sheet (+0x470). Native Options имеет отдельный ingame parent; Settings
  находится выше его subtree. Options AlwaysOnTop @0xb8829a действует
  внутри своего родителя. `setModalState` не добавлен.
- `original-code`: Options onClick @0xb800a0 обрабатывает exit0, close6,
  settings94; settings вызывает toggleSettings @0xb800e4 и pending close.
  Existing DropdownAnimation сохраняет OPEN/IDLE/CLOSE, tag projection,
  sound22/66 и delayed exit после CLOSE @0xb8019d. Frame отдаёт mesh до
  native quads; окно хранится до завершения CLOSE. Математика/границы модели
  остаются из `dropdown-animation-lifecycle.md`.

`port-native`: прежняя keyboard navigation передаёт активацию через native
pointer path; focus активирует настоящее окно. Это доступность portable
контроллера, не утверждение полного исходного keyboard/IME/shortcut пути.
Input release над другим местом всё равно доставляется CEGUI capture owner.

## Проверки

`tests/cegui_settings_test.cpp` / `original_cegui_settings_contract` использует
настоящий pak и библиотеку: controls/autochildren, checkbox release, native
slider drag/capture/release outside, audio draft preview/Cancel, popup capture,
selection/dismissal, точные shadow/particle/FSAA/Netbook значения, constructor
Title, Apply request/close и Options retained animation/delayed exit.
`original_cegui_mainmenu_contract` и `cegui_error_boundary` сохраняют проверки
Main, font tags, texture lifetime и error cleanup. CPU tests не являются GL.

`paused_settings_render` прошёл в общем Application loop с GL: HUD -> Options
-> Settings -> Show Blood -> Apply -> pause -> resume. Перечисленные поля
session state неизменны; settings writer сохранил `SHOW BLOOD :0`; один .otc
checkpoint относится только к обычному выходу. У сценария появились реальные
паузы для OPEN/CLOSE; click по ещё невъехавшему контенту не считается успешным.
Артефакты этой проверки (ignored):
`build-cegui/ui-repair-evidence/paused-settings-j6y1c6ll/`.
Просмотрены фактические кадры Settings и возвращения в Options; это проверка конкретного пути,
не сравнение кадров с оригинальным приложением и не измерение performance.

Итоговый затронутый gate прошёл 9/9: 3 core, 5 assets, 1 render.
Desktop и shared Application probe собраны успешно.

## Точный остаток

Графические поля теперь имеют UI, typed Apply и persistence consumer, но
полное выполнение исходных `resetShadows`, OGRE render-window/viewport,
UI recreate и scene-effects не подключено. Fullscreen/VSync/resolution
использует уже существующий backend при следующем запуске; live graphics
recreation original update остаётся открытым. Подключены MusicPlayer и
UiSoundPlayer levels; полный FMOD mixer/game-effect groups не восстановлен.
Original .SVB/game-state/global menu-owner/localization остаются адаптерами.
Не утверждается полное закрытие create/setOpen/update/onClick или общий UI.
Character create теперь использует native Editbox и producer имени/класса;
контракт и остаток — в [cegui-character-creation.md](cegui-character-creation.md).
Load теперь также использует CEGUI: [граница](cegui-character-load.md).
HUD пока на прежнем runtime.
