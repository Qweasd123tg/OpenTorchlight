# Главное меню: от дерева окон к цели MouseButtonDown

Источники проверены 2026-09-20, только чтение:

- Torchlight ELF SHA-256
  `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- `lib64/libCEGUIBase.so.1` SHA-256
  `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.
- `media/UI/mainmenuframe.layout` из установленного `pak.zip`.

## Контракт цепочки

`original-code`: CEGUI `Window::getTargetChildAtPosition @0x1110a0..0x111103`:

1. Обходит sibling draw list `+0x90..+0x98` с конца.
2. Пропускает невидимого ребёнка (`isVisible(false) @0x110d00`).
3. Сначала рекурсивно исследует его детей и возвращает найденную цель.
4. Затем проверяет собственный `+0x3e2`; при ненулевом значении продолжает
   поиск, при нуле вызывает виртуальный `isHit` (slot `+0x20`).
5. Возвращает попавшее окно, либо null после исчерпания списка.

`WindowProperties::MousePassThroughEnabled::set @0x129c50` связывает `+0x3e2`
с одноимённым свойством. Оно исключает само окно, сохраняя его детей в поиске.
Это также устанавливает назначение прежнего неизвестного поля при создании
root/content в CDropdownMenu.

`Window::isHit @0x114cd0..0x114d64` проверяет наследуемый disabled через
`isDisabled(false) @0x110cc0`, затем getPixelRect и isPointInRect. Для
прямоугольных main-menu widgets перенос потребляет разрешённые rect/clip,
visibility/enabled из UiLayout; полнота исходных rounding/getPixelRect остаётся
отдельной границей resolver.

`Window::addWindowToDrawList @0x1163d0..0x11648a` вставляет обычные окна перед
AlwaysOnTop-группой, а AlwaysOnTop — в её начало/конец согласно front/back.
`addChild_impl @0x1166f0` передаёт at_back=false в вызов @0x116718, то есть
добавляет окно в конец его группы. Для исходного порядка это подтверждает stable partition siblings,
который уже использует UiLayout. Уровень AlwaysOnTop относится к siblings:
верхний ребёнок нижнего sibling не обгоняет весь следующий sibling-subtree.

`System::getTargetWindow @0x10ad90..0x10ae50` выбирает одну цель, затем
`injectMouseButtonDown @0x10c4d0..0x10c577` направляет событие в неё и при
необработанном событии переходит к следующему ancestor.
`getNextTargetWindow @0x109e40..0x109e4f` возвращает parent (`+0xb0`), либо null
на modal target. Окна-соседи под целью повторно не рассматриваются.

Дополнение [контейнера](dropdown-container-lifecycle.md): рабочее дерево main
включает внешний sheet и root/back/content. `DropdownWindowFrame` выполняет
обычный System fallback (capture=null, modal=null): при видимом sheet отсутствие
дочерней цели возвращает сам sheet без проверки его hit/pass-through/disabled.
Back сохраняет MousePassThrough=false и может блокировать свободную область
без подписки. Существующий `ui_target_at_position` остаётся запросом по
ресурсному дереву; System fallback добавляется только в контейнере main.

Игровая цепочка: `CMainMenu::createMenus @0xc52a10`, callsite `0xc52bec`, вызывает
`CDropdownMenu::mapEventHandlers @0xb179e0`, который подписывает все непустые
onClick, включая неизвестные команды. `handle_onClick @0xb194e0` проверяет
left button (`args+0x28 == 0`), извлекает bound enum и вызывает virtual onClick
(slot `+0x40`). `CMainMenu::onClick @0xc4ae80` обрабатывает свои enum и всегда
возвращает true, в том числе для посторонней команды.

## Производственная граница

Прежний Frontend выбирал последний подходящий **элемент buttons_**, а не
верхнее окно. В этот список не попадали неинтерактивные перекрывающие окна;
его порядок также зависел от назначения действия. Новый main-menu путь
сначала использует все разрешённые окна и paint_order, затем ближайшую
MouseButtonDown-подписку по parent-цепочке. Окно без подписки блокирует нижних
siblings. Подписанный неизвестный enum потребляется без запуска другой кнопки.

Resource node и enum доходят до `dispatch_main_menu`; отдельное портовое
перекрытие CreditFrame для hit-testing больше не требуется. Credits и
CreditsB имеют MousePassThroughEnabled=True; их backing windows имеют False
и собственные guiSelectB/guiSelectD — это прямо задано layout.
Все видимые main-menu окна с callback сохраняются в paint tree независимо от
списка действий. Paint list объединяет записи одного окна по имени; разные
окна с одной enum-командой сохраняют самостоятельные image/text components.

Маршрут к подписке предполагает, что предшествующий обработчик widget class
не завершил событие. Это явная граница простого menu adapter; общий
`Window::onMouseButtonDown @0x112c60` также обслуживает tooltip, активацию,
RiseOnClick и autorepeat/capture. Портовое игнорирование unbound userData
является защитой входа, а не воспроизведением исходного разыменования указателя.

Это перенос выбора цели и маршрута к подписке для статического main-menu
дерева. В отдельном остатке: capture/modal state, автоматические события
widget classes, activation/RiseOnClick, double/triple-click timing,
handle_onClick wide-string/prefix/exception lifetime, runtime reparent/Z-order.
Обычный System root fallback и wrapper root/back/content подключены через
описанный выше контейнер; внешнее дерево CGameUI и native lifecycle остаются открытыми.
Другие frontend pages продолжают пользоваться прежним явным port adapter.

Проверка перевода — чистые запросы дерева: обратный sibling order,
AlwaysOnTop и вложенность, pass-through, disabled/hidden ancestors,
clipping/out-of-parent children, блокирующее окно без callback, родительская
подписка и равные команды на разных окнах. Игровые/UI сценарии не запускаются.

## Воспроизведение

Чистые проверки: `tests/ui_pointer_target_test.cpp`, CTest `ui_pointer_targets`
и `original_mainmenu_pointer_targets`. Второй читает внешний pak и проверяет
дерево mainmenuframe в 1024×768 и 1920×1080, включая обе backing-панели credits.
Подтверждение здесь — статическое сопоставление алгоритма и проверки его
входов/выходов, а не дифференциальное исполнение всей библиотеки.
2026-09-20: прошли 4 core и 3 assets проверки (targeting, dropdown subscriptions,
Property parsing, registry), без пропусков. Отчёт:
`build-verification/mainmenu-pointer-check.json`.

```sh
objdump -d -C --start-address=0x1110a0 --stop-address=0x111104 /path/to/game/lib64/libCEGUIBase.so.1
objdump -d -C --start-address=0x129c50 --stop-address=0x129c64 /path/to/game/lib64/libCEGUIBase.so.1
tools/check.sh --core --assets /path/to/game --test ui_pointer_targets --test original_mainmenu_pointer_targets
```
