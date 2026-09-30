# Character Load через исходную CEGUI и реальные OTC consumers

Проверено 2026-09-30. Восстановлен подключённый UI-срез; completion больших
игровых функций остаётся `partial`. Исходные ELF/pak/CEGUI используются только
для чтения. Хеши закреплены в `cegui-source-inputs.json`; версия CEGUI 0.6.2,
commit `3ed5c719c3bb27b877b192e034ef2c0b05ea722c`, vendor adaptations прежние.
Новая UI библиотека, собственный редактор или второй production Load tree
не добавлены. Native CEGUI выполняет дерево, события, clipping, fonts и Falagard.
Принятые полные ASM тела click/double/open/scroll/delete сохранены в
`disassembly/continue-menu-native-ui.asm`; это адресный экспорт pinned ELF,
а не сгенерированный пакет или реконструированная декомпиляция.

## Проверенный контракт

`original-code`: CContinueGameMenu constructor `0xc42499` передаёт flags=1
в CDropdown — model-null. Создание `0xc404c0` загружает
`media/UI/characterload.layout`, scale(false) `0xc4067d`, mapToFunctions
`0xc40689`, mapEventHandlers `0xc40694`, attach layout к root `0xc406a0`,
нулевую позицию `0xc406dc`. Этот путь переиспользует общий native wrapper.

Общая карта полей проверенного среза:

| Поле оригинала | Тип/начало | Writers / readers и потребитель |
|---|---|---|
| `+0xc4` | signed int32, 0 в ctor `0xc424bd` | reload `0xc3e439`, scrollUp/Down; list/select; `Frontend::scroll_` в границе OTC count |
| `+0xc8` | signed int32, 0 в ctor `0xc424c7` | select `0xc3f8f3`, delete `0xc3fd81`; list/click/double; абсолютный selected index |
| `+0xd0+8*i`, `+0xf8+8*i`, `+0x120+8*i`, `+0x148+8*i` | pointers64, пять строк | create lookups; list; native Player/Name/Desc/Highlight |
| `+0x170/+0x178` | pointers64 | create; list visibility и scroll callbacks |
| `+0x180/+0x188/+0x190` | pointers64 | Continue/CharacterName/CharacterModsWarning; list/update/select |
| `+0x198/+0x1a0` | pointers64 | DeleteConfirm/Delete; create/click/list |
| `+0x1e8/+0x1f0` | begin/end pointers64, 0 в ctor | reload; count по `(end-begin)/8`; вместо SVB vector поступает `.otc` list |

Инициализация всех pointer fields до create, native object ABI, preview/mod
owners и полные unwind пути не заявляются перенесёнными. Полный lookup map
и прежнее сравнение visibility — в `menu-production-state.md`.

- `setOpen @0xc40010`: close tail-calls base. Open вызывает reload(false)
  `0xc4002a`, base(true) `0xc40037`, list `0xc4003f`, forced select(0,true)
  `0xc4004f`. Reload обнуляет scroll `0xc3e439`. Native открытие выбирает
  первую запись и scroll0, а не сохраняет прежнее положение.
- `updateCharacterList @0xc3b2f0`: пять строк от scroll. Slot/name/description
  видимы у занятых строк `0xc3b3a9..0xc3b3cd`, пустые вместе с highlight
  скрываются `0xc3b725..0xc3b752`. Highlight видим при selected==scroll+row
  `0xc3c571`, затем moveToFront `0xc3c57e` даже для невыбранной занятой строки.
  ScrollUp видим при scroll!=0 (`0xc3b78b/0xc3d5ad`), ScrollDown при scroll+5<count
  (`0xc3b7b1/0xc3d5c4`); Continue/Delete при count!=0 (`0xc3b7eb/0xc3b815`).
  Эти эффекты потребляет настоящий WindowManager, не UiLayoutState копия.
- `scrollUp @0xc3e2a0`: max(scroll-1,0), tail-call list.
  `scrollDown @0xc3e2c0`: increment, затем clamp к max(count-5,0), tail-call list.
  В UI доступен тот же шаг и граница. OTC producer имеет существующее ограничение
  count<=128; не заявляется перенос original signed overflow/invalid index.
- `onClick @0xc3fe80`: jump table `0xff27d8` подтверждает continue3, back7,
  decline8, accept9, scroll12/13, select14..18, delete90. Guard пропускает
  команды, кроме closing&&!open. Mouse wrapper дополнительно маршрутизирует
  только Left. Native callbacks принимаются для прикреплённой Load страницы;
  полная внешняя state machine остаётся адаптером.
- Play читает selected SVB health float32 `+0xe0` и требует ordered health>0
  (`0xc3feda..0xc3fee9`), запрашивает state2/menu0 `0xc3fef6`, закрывает меню.
  Native Play проверяет decoded OTC health и loadable, затем typed slot/GUID
  реально потребляется Application -> SaveStore::read -> PlayerSession.
  Original закрывает меню до state transition; порт завершает read/validation
  до entered_game и оставляет страницу при ошибке. Это существующая portable
  transaction boundary, не побитовый перенос native pending flags.
- `onDoubleClick @0xc334e0` проверяет count/health и принимает только enum14..17
  (`0xc33537..0xc3357a`). Пятый select18 намеренно не добавлен. Второй click
  не заменяется новым select: используется выбранный первым down персонаж.
  NaN comparisons у двух original обработчиков различаются; OTC decoder
  `src/save_codec.cpp` отклоняет nonfinite float, и такая parity здесь не заявлена.
- Delete показывает prompt `0xc3febc`; Decline скрывает `0xc3ff29`; Accept
  сначала проверяет видимость `0xc3ff41`, скрывает `0xc3ff57`, затем deleteCharacter
  `0xc3ff5f`. Original switch не блокирует выбор/scroll при видимом prompt.
  Прежняя portable confirmation lock убрана из native пути; смена выбора
  разрешена, Accept удаляет текущую запись. Нет выдуманного setModalState.
- `deleteCharacter @0xc3fd00`: bounds, save path, DeleteFile `0xc3fd7c`,
  selected=max(selected-1,0) `0xc3fd81..0xc3fda0`, reload `0xc3fda6`, forced
  select `0xc3fdb9`, list `0xc3fdd4`. Application уже исполняет OTC remove,
  refresh_saves и Frontend::removed. Выбор предыдущей записи применяется
  после успешного дискового consumer; ошибки — существующая OTC transaction
  boundary. Никакие исходные `.SVB` не изменяются.

## Библиотека и текст

`resource-derived` / `library-derived`: `characterload.layout` читается целиком
Expat/CEGUI. Повторное onClick у scroll получает последнее исходное значение.
Malformed lowercase `name/value` у текстовых окон не исправляется и не включает
AlwaysOnTop: upstream GUILayout handler берёт case-sensitive Name/Value, пустое
property name не применяется. Fixture проверяет это непосредственно на CEGUI.

В CEGUIString.h constructor `String(const std::string&)` считает байты
unencoded codepoints 0..255. Использовать его для готового UTF-8 нельзя.
Native row name/description/CharacterName и class display/description теперь
используют `String(const utf8*)`, библиотечный decoder и UTF-32 storage.
Найдена и исправлена именно ошибка consumer: запись/загрузка имени и раньше
сохраняла UTF-8, но GUI мог показывать байтовые символы. Creation contract
расширен не-ASCII названиями/описаниями класса.

`library-derived` / `original-code`: multi-click использует SimpleTimer с
gettimeofday, независимо от injectTimePulse. Shipped `currentTime @0x10b450`
вызывает gettimeofday `0x10b459`, переводит sec/usec и суммирует `0x10b477`.
`injectMouseButtonDown @0x10c320`, `injectTimePulse @0x10b090` — разные пути.
Test driver разделяет одиночные clicks пространственно, а double сохраняет
точку; не подменяет библиотечное правило игровой константой.

## Проверки и остаток

`original_cegui_load_contract` прошёл на настоящем pak/CEGUI: native imagery,
отсутствие duplicate painter, UTF-8 name, descriptor, case-sensitive properties,
пять строк, scroll bounds, absolute selection, reopen, health/unreadable guards,
double first-four/fifth-no-op, prompt selection/cancel/accept, hide-before-remove,
previous-record selection, empty list и Back. Это CPU/library контракт, не GL.

`character_load_render` прошёл через общий Application/GL loop: **4 процесса,
25 проверок**. Два реальных персонажа с разными классами и UTF-8 именами
записаны в изолированные OTC файлы; выбранный старый save восстановил 13 полей
и revision1. Cancel сохранил оба файла побайтно, Accept удалил только выбранный;
оставшийся персонаж загрузился с исходной identity/revision2. Load кадры
действительно отрисованы. Артефакты (ignored):
`build-cegui/ui-repair-evidence/native-load-glhrlmi7/`.
Это портовый сценарий, без original process, OS input или frame parity.

Финальный соседний gate прошёл **8/8**: Main, Settings, creation, Load,
error boundary, core/original five-row layout contracts и registry sync.
Desktop/shared Application probe собраны. Settings/Apply/resume GL regression
также прошёл: 21 поле персонажа неизменно и нет лишнего checkpoint.
Артефакты: `build-cegui/ui-repair-evidence/paused-settings-ih23cswd/`.

CharacterName и краткий PlayerNDesc имеют **OTC producer**, а не original preview
и SVB formula. Difficulty/playtime/Dead/Retired, sorting/filtering исходных files,
SVB import, enabled mods, character/pet preview, ResourceManager/GameClient
owners, localization и полный unwind/cleanup остаются открытыми.
Full-function completion и whole-library ABI parity не заявляются.
Новые исходники OGRE/FreeImage или ручные аналоги их механизмов не добавлены.
