# Главный экран: действующая граница

Текущий пакет — [CMainMenu и painter](mainmenu-controller-painter.md).
Процесс — [code-first](code-first.md). Единица полного закрытия — исходная
функция; рабочий пакет связывает её эффекты с кадром и вводом приложения.

## Входное меню

Источники: pinned ELF `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`,
внешние `media/UI/mainmenuframe.layout`, `GuiLook.looknfeel`, `GuiLookSkin.scheme`.

- `CMainMenu::createMenus @0xc52a10` задаёт свойства поверх XML: скрывает
  DemoVersion, предупреждение о модах и панели credits, заполняет Credits
  и CopyrightInfo. Продакшен-перенос и остаток описаны в текущем пакете.
- `CMainMenu::update @0xc53b70` обновляет Continue и предупреждение о модах.
  Continue подключён к адаптеру `.otc`; исходный `.SVB` producer открыт.
- `CMainMenu::onClick @0xc4ae80` содержит диспетчер по ELayoutFunction.
  Общий [mapToFunctions](ui-function-bindings.md) связывает layout с enum;
  [диспетчер](dropdown-mainmenu.md) переносит все ветви и порядок вызовов.
  Frontend потребляет запросы состояния и credits через явные адаптеры.
- `CDropdownMenu::mapEventHandlers @0xb179e0` подписывает непустой onClick
  после обхода детей: multi-click, MouseButtonDown, MouseDoubleClick.
  Down-подписки подключены; double-click delivery и CEGUI ownership открыты.
  CMainMenu flags=1 выбирает model-null: его флаги/attachment подключены,
  полный контейнерный и анимированный runtime остаётся в остатке.
- `CreditFrame/Credits` содержит Runic credits из rodata @0xff2e30.
  `CreditFrameB/CreditsB` содержит Linux credits из layout. Обе панели
  открываются и закрываются через собственные ресурсные окна.
- Общий paint list сохраняет порядок между изображениями, кнопками и текстом.
  Falagard компилируется для каждого окна; проверяются свойство enabled,
  форматирование, clip и последовательность команд. Inline colour spans,
  полный lifetime/events и динамический sibling order остаются открытыми.

## Связанные страницы

`CNewGameMenu::onClick @0xc5c040`, `setOpen @0xc5c5a0`,
`update @0xc5cc30`, `createMenus @0xc5d730` определяют выбор героя/питомца.
Порт заполняет CharacterClass/CharacterClassDescription по UNIT NAME и
DESCRIPTION, EditBox по имени `.otc`. Полные исходные выбор питомца,
сложность, getEmptySave и переходы контроллера требуют переноса.

`CContinueGameMenu::updateCharacterList @0xc3b2f0` формирует описания
оригинальных сохранений. Порт использует свои `.otc` name/level/class/hardcore.
Описание времени, сложности, Dead/Retired и `.SVB` читается отдельным контрактом.
`deleteCharacter @0xc3fd00` задаёт последовательность удаления и обновления
списка; текущий SaveStore удаляет только собственные `.otc` через подтверждение.

Исходная сцена меню и персонажи прослеживаются через CMenuManager/CGameUI;
ресурс PortraitBox сам по себе описывает лишь окно. Состояние сцены:
[menu-background.md](menu-background.md).

## Проверки

`ui_dropdown_contract` проверяет исходные ветви, флаги, порядок вызовов,
подписки и границы исключений на значениях функций.
`original_ui_dropdown_contract` добавляет свойства настоящего layout.
`ui_layout_property` и `original_ui_layout_property` закрепляют выбор
Value/body. Подключение устанавливается по callers/полям/consumers;
полное закрытие записывается в function-transfer.json.

Сохранённые `mainmenu_presentation_test`, `frontend_menu_test` и
`gles_skin_button_render` относятся к отдельно запрашиваемой группе
UI-интеграции. Для текущего переноса выбираются проверки контрактов выше.
