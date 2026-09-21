# CDropdownMenu и диспетчер CMainMenu

`original-code`, ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Полные тела ниже прочитаны через `tools/original.py`/objdump; игра не запускалась.

## Общая карта полей и создание

CDropdownMenu constructor `0xb1b6f0`, размер `0x2b5`:
`+0x10` внешний CEGUI parent, `+0x18` корневой контейнер, `+0x20` content;
`+0x30` open=false, `+0x31` closed=true, `+0x32` pending-close=false;
`+0x38` settings, `+0x40` GameUI, `+0x48` SceneManager,
`+0x70` model=null, `+0x78` ResourceManager, `+0x80` SoundBank,
`+0x88` flags. Списки listeners/pending removals: `+0x90/+0xa8`.
SoundBank создаётся и получает samples 22/66 при наличии записей ресурсов;
затем вызывается базовый createMenus. Ошибки проходят cleanup/unwind.

CMainMenu constructor `0xc53b10` передаёт flags=1 @`0xc53b18`.
CNewGameMenu также передаёт 1; COptionsMenu/CSettingsMenu передают 0.
`createMenus 0xb196f0`, размер `0x2000`, проверяет бит 1 @`0xb19722`:
при сброшенном бите создаёт модель @`0xb1af7f` и bounds ±100000;
при установленном бите пропускает создание. Модель при наличии получает
нулевую позицию и visibility=false. Далее обе ветки:

1. Проверяют imageset `GuiLook` (строка `0xfe493c`).
2. Создают три `DefaultWindow` (`0xfe499d`), имена через uniqueName(`gui_`).
3. Root `+0x18`: size=(1,0;1,0), position=0, RiseOnClick=False,
   MousePassThroughEnabled=false (window+0x3e2=0), ZOrderingEnabled=false.
4. Back-child: attach к root, size=(1,0;1,0), position=0,
   RiseOnClick=False, moveToBack, ZOrderingEnabled=false.
5. Content `+0x20`: attach к root, size=(1,0;1,0), position=0,
   RiseOnClick=False, MousePassThroughEnabled=true (window+0x3e2=1), moveToFront,
   ZOrderingEnabled=false.

Строки, UTF-8→UTF-32, grow/npos/length_error, refcount/destruction и unwind
прочитаны. `WindowProperties::MousePassThroughEnabled::set @0x129c50` из
закреплённой CEGUI связывает window+0x3e2 с одноимённым свойством;
источник и хеш — [маршрутизация указателя](mainmenu-pointer-routing.md).
CMainMenu::createMenus добавляет ресурсный layout к `+0x18`, а не к `+0x20`.

## setOpen / update / processInput

`setOpen 0xb18e50`, размер `0x482`: равное состояние только записывает open.
Закрытие сначала очищает четыре safe pointers GameUI→GameClient:
`+0x1f8`, `+0x1e8`, `+0x1c8`, `+0x1d8` (removeSafePointer, затем null).
С моделью: sound66, blend CLOSE(false,0.1,2,-1), closed=false.
Без модели: removeChild(root), closed=true. open записывается последним.
Открытие читает width/height; без модели обнуляет позицию content.
С моделью: sound22, visible=true, CLOSE playing → blend OPEN(false,0.1,2,-1),
иначе play OPEN(false,2,-1); queue IDLE(true,0.1,1).
Обе ветки делают addChild(root), moveToBack(root), затем open=true.
Открытие сохраняет прежнее значение closed.

`update 0xb176b0`, размер `0x32b`: читает width/height; closed && !open → return.
При model выполняет updateAnimation(dt,false), Entity::_updateAnimation,
читает tag_dropdowntop и позицию модели. Content position:
`x = width*0.5 + scaledY(model.x + tag.x)`,
`y = -(scaledY(model.y + tag.y) + height*(-0.5))`.
Порядок SSE сохранён в формуле; это не линейное UI-интерполирование.
Для !open && !closed модель скрывается и root удаляется после завершения
и playing, и queued CLOSE; затем closed=true. При model=null действий нет.

`processInput 0xb102a0`, размер `0x28`: разрешённый проход и pending-close
вызывают виртуальный setOpen(false), затем очищают pending-close и возвращают
false; иначе true. `handle_CloseButton 0xb17380` принимает только mouse button=0,
ставит pending-close и очищает те же safe pointers; возвращает true.

## mapEventHandlers: полный обход и подписки

`0xb179e0`, размер `0x483`: один снимок child count, child-first recursion,
затем локальный try/catch-all. Существующий непустой `onClick`:
setWantsMultiClickEvents(true), subscribe MouseButtonDown→`0xb194e0`,
subscribe MouseDoubleClick→`0xb192e0` — именно в этом порядке.
Неизвестное имя команды также подписывается. Ошибка подписки оставляет уже
сделанные действия. Повторное отображение добавляет подписки.
Child traversal находится вне локального catch; библиотечные временные
строки, слоты и connections очищаются в исходных cleanup-блоках.

## CMainMenu::onClick: все ветви

`0xc4ae80`, размер `0x172`; guard `!open && closed` → true без действий.
Остальные пути также возвращают true. Параметр строки не читается.

| ELayoutFunction | Последовательность |
|---|---|
| 1 | GameUI+0x12f9=true; closeAll |
| 3 | requestSetGameState(2,0); virtual setOpen(false) |
| 4 | requestSetGameState(0,1); virtual setOpen(false) |
| 5 | canLoad; requestSetGameState(0, canLoad ? 3 : 1); virtual setOpen(false) |
| 64 / 65 | CreditFrame.setVisible(true / false), обязательное окно |
| 66 / 67 | CreditFrameB при наличии: setVisible(true / false) |
| 94 | toggleSettings |
| остальные | return true |

`requestSetGameState 0xa828f0` записывает GameUI+0x1914/+0x1918.
`canLoad 0xa84d20` → `CMenuManager::canLoad 0xc2b700`: count списка сохранений >0,
а не успешность загрузки конкретного сохранения.

## Производственное подключение и граница

`UiResources::layout` → mapper подписок → разрешённое дерево окон →
верхняя цель указателя → подписка её самой/предка → bound enum →
диспетчер CMainMenu → реальные изменения frontend page/request/credits/settings.
Точный scope выбора цели и сохраняющиеся библиотечные зависимости описаны
в [mainmenu-pointer-routing.md](mainmenu-pointer-routing.md).
Проверки вызывают функции перевода с известными входами и фиксируют порядок
вызовов, значения и ошибки. Они не создают окно и не исполняют UI-сценарий.

Порт поддерживает статическую ветвь CMainMenu (flags=1, model=null).
[Контейнер и библиотечный lifecycle](dropdown-container-lifecycle.md) уточняют
производственный перенос: постоянные root/back/content и ресурсное дерево,
реальная parent-связь при open/close, достижимый snapshot для painter и ввода,
обычный System sheet fallback. Close сохраняет отсоединённые окна и подписки.
Владение ими до teardown frontend — адаптер порта: оригинальный деструктор
CDropdownMenu не уничтожает окна CEGUI. Ветви модели, общий manager/dead-pool,
события activation/lifecycle и safe-pointer ownership сохраняются открытыми
для всего класса CDropdownMenu. `.otc` остаётся явным
адаптером canLoad/Continue и запросов состояния; native `.SVB`, CGameStateController,
полный event dispatch/prefix decoding и settings overlay остаются отдельными
зависимостями. Полное закрытие класса или меню этим срезом не заявляется.
