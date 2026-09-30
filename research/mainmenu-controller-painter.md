# Входное меню: свойства контроллера и единый painter

2026-09-30: Main/credits перенесены на [исходную CEGUI](cegui-source-integration.md).
Ниже сохранён контракт оригинала и прежнего собственного painter.
Текущая проверка `tests/mainmenu_presentation_test.cpp` проверяет библиотечный
путь; CTest name — `original_cegui_mainmenu_contract`. Полный completion по-прежнему partial.

## Источники и граница

ELF `Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Ресурсы: `media/UI/mainmenuframe.layout`, `GuiLook.looknfeel`,
`GuiLookSkin.scheme` из внешнего `pak.zip`.
CEGUI: `libCEGUIBase.so.1`, SHA-256
`57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`;
пофункционный порядок image/text — `RenderCache::render @0xf48a0`,
экспорт `ui-skin-reference/render-cache.asm`.

`original-code`: `CMainMenu::createMenus @0xc52a10` загружает layout,
вызывает scale(false) @0xc52bd5, mapToFunctions @0xc52be1,
CDropdownMenu::mapEventHandlers @0xc52bec, addChildWindow @0xc52bf8,
затем setPosition(0,0) @0xc52c34. Далее сохраняет ContinueLast (+0xc8),
DemoVersion (+0xd0), CharacterModsWarning (+0xd8), Credits (+0xe0),
CreditFrame (+0xe8), CreditFrameB (+0xf0). DemoVersion и оба CreditFrame
скрываются, CharacterModsWarning скрывается при наличии окна. Credits и
CopyrightInfo получают runtime-текст. XML описывает начальное состояние;
рабочее окно получает последующие записи контроллера.

`original-code`: `CMainMenu::update @0xc53b70` сначала вызывает
CDropdownMenu::update, затем canContinue. ContinueLast показывается/скрывается
через isVisible(false) и setVisible @0xc53ca9 / @0xc53d9d. При наличии
выбранного персонажа сравниваются количество и упорядоченные имена модов
(StringUpper + wmemcmp); результат записывается в CharacterModsWarning.

Текущий перенос покрывает презентацию обычного входного меню: начальное
скрытие demo/warning, доступность Continue, иерархическое открытие credits,
порядок окон и компиляцию Falagard каждого окна перед GLES. Producer
canContinue остаётся адаптером `.otc`; оригинальные `.SVB` и моды остаются открытыми.
[CDropdownMenu и CMainMenu::onClick](dropdown-mainmenu.md) разобраны отдельно:
подключены enum-dispatch и down-подписки.
[Model-null контейнер](dropdown-container-lifecycle.md) добавляет root/back/content,
parent-связи и сохранение отсоединённого дерева; painter и input получают один
достижимый snapshot. Native manager/dead-pool, lifecycle events, полная
доставка событий и state controller сохраняются в остатке. CopyrightInfo
получает `(v1.15) Torchlight (C) 2009 Runic Games Inc.` из глобального
инициализатора @0xc4f708 / UTF-32LE @0xff2d00, как setText @0xc53560.
Completion create/update остаётся partial.

Карта полей CMainMenu: `+0x18` — родительское окно, `+0x40` — CGameUI,
`+0xc8` — ContinueLast (create пишет, update читает), `+0xd0` — DemoVersion,
`+0xd8` — CharacterModsWarning (create пишет/скрывает, update меняет видимость),
`+0xe0` — Credits, `+0xe8/+0xf0` — CreditFrame/CreditFrameB (create пишет,
onClick использует). Все перечисленные поля — 64-битные указатели.
DemoVersion hide @0xc52e05; warning optional hide @0xc52efa;
credits text @0xc53291; frame hides @0xc532a7 / @0xc5339a.
Credits берётся из UTF-8 literal @0xff2e30 с пустыми строками между разделами.
CreditsB уже содержит Linux Platform / OutOfOrder Games в XML. Текст и
цветовые теги сохраняются до рендера; [inline Serif](ui-inline-text.md)
потребляет их при измерении, переносе строк и создании glyph-команд.

### Загрузка значения Property

Проверенный контракт shipped CEGUI (SHA выше):
`GUILayout_xmlHandler::elementPropertyStart @0xe4e80` читает Name и Value.
Непустой Value устанавливается сразу через setProperty @0xe5309. При пустом
или отсутствующем Value имя сохраняется в +0xf0, буфер +0x1a0 очищается.
`text @0xe3560` дописывает очередной текстовый фрагмент в этот буфер.
`elementPropertyEnd @0xe3090` проверяет имя и наличие окна, применяет callback
фильтрации при наличии и вызывает setProperty @0xe3109. Исключение CEGUI
обрабатывается локально; остальные исключения передаются через unwind.

`UiLayout::parse` переносит выбор значения в существующую загрузку ресурсов:
непустой Value имеет приоритет, иначе берётся тело Property, с сохранением
фрагментов текста, XML line-end normalization и entities. Последующая
Property заменяет предыдущее значение. Ресурс CreditsB использует именно
тело Property. Callback-фильтр, CEGUI exception hierarchy и CDATA остаются
отдельными частями библиотечного контракта.

Подключение по коду: `UiResources::layout` → `UiLayout::parse` →
`UiLayout::resolve` → `Frontend::frame` (CreditsB) → `frontend_paint_list` →
`UiSkin::compile` (TextComponent). Узкая проверка сравнивает входные XML
значения и выходные свойства/текст; графическое исполнение задаётся отдельно.

Разбор ошибок: create проверяет наличие warning, CreditFrameB и CopyrightInfo;
DemoVersion, Credits и CreditFrame обязательны. Оставшиеся блоки выполняют
CEGUI/std string allocation/encoding, length-error @0xc536f0, cleanup/unwind.
Portable layout допускает урезанные авторские fixtures; это явно более мягкий
адаптер, чем исходный lifetime/error контракт.

update сохраняет warning при отсутствии selected saved object; при его
наличии сравнивает count, затем пары StringUpper по индексам, затем длину и
wmemcmp. Массив saved: pointer +0xa58, count +0xa60, capacity +0xa64.
Ветвь index >= capacity возвращает базовый адрес массива. Проверка модов
выполняется и при canContinue=false. Эти ветви разобраны, перенос producer
состояния остаётся открытым.

## Проверяемая цепочка

Контроллер применяет visibility до resolve, чтобы дети наследовали состояние.
Frontend формирует общий paint list по paint_order; каждое окно компилируется
в свой RenderCache (images, затем text), после чего начинается следующее окно.
Кнопка передаёт compiler актуальные enabled/text/font. Порядок начального
дерева подтверждён `Window::addWindowToDrawList @0x1163d0` и
`addChild_impl @0x1166f0` закреплённой CEGUI: обычные siblings, затем
AlwaysOnTop siblings, каждый со своим subtree. Программный draw-list эффект
moveToFront подключён к highlights списка персонажей; activation и reparent
остаются открытыми. [Выбор цели указателя](mainmenu-pointer-routing.md)
потребляет то же полное дерево; windows с callback сохраняются в painter
даже при общей enum-команде.

Проверки перевода фиксируют значения свойств, ветви и параметры Falagard
по установленному исходному контракту. Подключение подтверждает цепочка
вызовов и потребления полей. Сохранённые кадровые и кликовые стенды относятся
к отдельно запрашиваемым интеграционным задачам.

Кеш Frontend — `port-native` оптимизация: неизменившиеся запросы возвращают
копию уже собранного кадра. Изменения модели инвалидируют кеш; движение
указателя меняет состояния поверх копии. Размер viewport входит в ключ.
`frame_build_count` проверяет фактическое
число сборок отдельно от времени копирования. FPS требует отдельного замера.
