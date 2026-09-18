# CInventoryMenu::setOpen + createMenus — разбор (code-first, пакет 1)

Статус: `setOpen @0xb4eb70` — **разобрана** (все ветви, поля, места вызовов —
по машинному коду; неизвестное перечислено). `createMenus @0xb569e0` —
триаж на уровне вызовов, полный разбор ветвей открыт. Не перенесено, не
подключено, не сравнено.

## Входы

- ELF `Torchlight.bin.x86_64`, SHA-256
  `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`
  (проверено `sha256sum`).
- `setOpen @0xb4eb70`, размер `0x632`: `research/disassembly/b4eb70-inventory-setopen.asm`
  (345 строк, `objdump -d`, границы по соседним символам; ключ `--stop-address`
  игнорируется — файл обрезан вручную по `mapEventHandlers @0xb4f1b0`).
- `createMenus @0xb569e0`, размер `0x9d90` (nm даёт `0x9d84`, +0xc до
  конструктора `@0xb60770`): `research/disassembly/b569e0-inventory-createmenus.asm`
  (7599 строк, обрезан по конструктору).
- Декомпиляция (навигация): `research/decompiled-core/inventory_menu.c:2403-2573`
  (`setOpen`), `:6442+` (`createMenus`).
- Ghidra-проекта и `research/original-callsites.tsv` на этой машине нет;
  упорядоченный список мест вызовов ниже снят скриптом из `objdump`-вывода
  (порядок и повторы — из машинного кода, условия — из `jcc` рядом с сайтом).

## setOpen: четыре пути (сайты — из ASM)

Вход: `cmpb $0,0x60(%rdi)` (`b4eb95`), флаг «открыто» — байт `this+0x60`.

1. **Уже открыто + `param_1 != 0`** (`b4eb99` не взят, `b4eba2` взят):
   `this[0x60] = param_1`, виртуальный вызов `updateLayout()` (`b4ee64`,
   слот vtable `+0x48` — разрешён байтами vtable, см. ниже). Больше ничего.
2. **Уже открыто + `param_1 == 0`** (закрытие, `b4eba2` не взят):
   условный `removeChildWindow` (`b4ebc4`, только если `[0x91a0] != 0` и
   `[[0x91a0]+0x30]+0xb0 != 0`); звук `playSample(0x42)`; `blendAnimation("CLOSE",
   false, 0.1, 2.0, -1.0)`; `this[0x61] = 0; this[0x60] = 0`; возврат.
   `updateLayout()` НЕ вызывается, `queueTip` НЕ вызывается.
3. **Закрыто + `param_1 == 0`** (`b4ec50`, `b4ec53` не взят): `this[0x60] = 0`,
   возврат. Пустой путь.
4. **Закрыто + `param_1 != 0`** (открытие, `b4ec90`): звук `playSample(0x16)`;
   чтение ширины/высоты через `GetInt`; виртуальный вызов объекта `this+0x9170`
   слот `+0x50` с аргументом `1` (цель неизвестна, см. ниже); если
   `animationPlaying("CLOSE")` — `blendAnimation("OPEN", false, 0.1, 2.0, -1.0)`,
   иначе `playAnimation("OPEN", false, 2.0, -1.0)`; всегда
   `queueBlendAnimation("IDLE", true, 0.1, 1.0)`; `addChildWindow([0x18],[0x20])`,
   `moveToBack([0x20])`; радиокнопки `[0x9120]=true, [0x9128]=false, [0x9130]=false`;
   видимость `[0x9108]=true, [0x9110]=false, [0x9118]=false`; ленивый viewport
   (только если `[0x9158] == 0`); `queueTip(0)`; `this[0x60] = param_1`;
   `updateLayout()`.

Порядок анимаций: `OPEN` раньше `IDLE`; `IDLE` ставится в очередь всегда
(обе подветви `animationPlaying` сходятся перед `b4ed8a`).

## setOpen: упорядоченные места вызовов (47 статических `call`)

Закрытие: `0xb4ebc4 removeChildWindow` (условный), `0xb4ebe4 playSample`,
`0xb4ebf9 string("CLOSE")`, `0xb4ec22 blendAnimation`.
Открытие: `0xb4ecae playSample`, `0xb4ecbd/b4ecd6 GetInt` (ширина, высота),
`0xb4ecf4 virtual [0x9170]+0x50 (arg 1)` — цель неизвестна,
`0xb4ed07 string("CLOSE")`, `0xb4ed16 animationPlaying`,
`0xb4ed54 string("OPEN")` + `0xb4ed7d blendAnimation` ИЛИ `0xb4ee95 string("OPEN")` +
`0xb4eeb6 playAnimation`, `0xb4ed9f string("IDLE")`, `0xb4edc3 queueBlendAnimation`,
`0xb4ede7 addChildWindow`, `0xb4edf0 moveToBack`, `0xb4ee01/0e/1d setSelected`,
`0xb4ee2e/3c/4a setVisible`, viewport-блок (ниже), `0xb4ee5f queueTip(0)`,
`0xb4ee6e updateLayout (virtual +0x48)`. Остальное — `std::string` dtor/`_M_destroy`
и landing-pad'ы (`0xb4f140-0xb4f19d`, `_Unwind_Resume`).

Viewport-блок (только при `[0x9158] == 0`, сайты `0xb4eec8-0xb4f095`):
создание через virtual объекта `this+0x9150` слот `+0x48` (`this=[0x9150]`,
`rsi=[0x9148]`, `edx=3`, `xmm=0.0, 0.0, 1.0`) → `this+0x9158`; затем
`scaledY(124.0)`, `scaledY(132.0)`, `scaledY(166.0)`, `scaledY(192.0)`;
`setDimensions(x, max(0,y), w, h)` с клампами `x+w<=1`, `y+h<=1`, `x>=0`,
`y>=0` и минимумом ширины `1/width_px` (проверено порегистрово, включая
`movaps xmm5->xmm2 @0xb4eff7`, который легко пропустить);
`setBackgroundColour(viewport, чёрный 0,0,0,1 со стека)`;
`setClearEveryFrame(viewport, esi=1, edx=3)`; `getActualWidth/Height(viewport)`;
виртуальный вызов `vtable([0x9148])+0x278` с `xmm0=w/h` (вероятно
`Camera::setAspectRatio`, помечено `inferred`); `setCamera(viewport, [0x9148])`.

## Карта полей CInventoryMenu (смещения — original-code; имена — рабочие)

- `+0x18` Window* родитель; `+0x20` Window* корень инвентаря.
- `+0x60` u8 флаг открыто; `+0x61` u8 второй флаг (сбрасывается только при закрытии).
- `+0x68` настройки (`GetInt`); `+0x70` `CGameUI*`.
- `+0x9108/0x9110/0x9118` Window* (открытие: показать/скрыть/скрыть).
- `+0x9120/0x9128/0x9130` RadioButton* (открытие: выбрать/снять/снять).
- `+0x9148` Camera* (существующая); `+0x9150` объект-фабрика viewport (тип открыт —
  нужен писатель поля из `createMenus`); `+0x9158` Viewport* (ленивый).
- `+0x9170` CGenericModel* (анимации); `+0x9184` float база x viewport;
  `+0x9188` CSoundBank*; `+0x91a0` ptr цепочки закрываемого child (`+0x30`/`+0xb0`).
- Писатели `+0x9150/+0x9148/+0x9108-30/+0x9184` — за `createMenus`/конструктором,
  в этом пакете не подтверждены.

## Константы (.rodata, прочитаны из ELF)

`0xfefd50=124.0`, `0xfefd54=132.0`, `0xfefd58=166.0`, `0xfefd5c=192.0`;
`0xfa47fc=1.0`, `0xfa480c=0.1`, `0xfa4824=2.0`, `0xfa8760=-1.0`;
строки `0xfe6008="CLOSE"`, `0xfe600e="OPEN"`, `0xfc993a="IDLE"`;
звуки open `0x16`, close `0x42`. `KSETTINGS_RES_WIDTH/HEIGHT @0x150b464/68` —
`.bss`, значения только в рантайме (открыто).

## Расхождения декомпиляции с машинным кодом (проверено)

1. `SUB81(...)` скрывает булевы аргументы: фактически `setSelected(true)` только
   `[0x9120]`, `setVisible(true)` только `[0x9108]`; остальные — `false`.
2. `setBackgroundColour`: цвет — чёрный `0,0,0,1`, собранный на стеке
   (`0x40(%rsp)`), НЕ `*(this+0x9158)`; `[0x9158]` — это сам viewport (`rdi`).
3. Вызов создания viewport: декомпилятор перепутал порядок аргументов thiscall.
   Фактически `this=[0x9150]`, `rsi=[0x9148]`, `edx=3`, `xmm=0,0,1.0`.
4. Разрешённая цель: слот vtable `+0x48` CInventoryMenu — это
   `updateLayout() @0xb53430` (vtable `0xfefb70` из конструктора `@0xb60770`,
   байты прочитаны из ELF). Значит конец `setOpen` = `updateLayout()` на путях
   1 и 4. Слот `+0x40` — сам `setOpen` (виртуальный).

## Разрешения из конструктора и vtable (машинный код, добавлено после триажа)

Конструктор `CInventoryMenu @0xb60770` (`objdump`, первые записи vtable/cTOR):

- vtable `CInventoryMenu = 0xfefb70` (слот `+0x40` = сам `setOpen`, `+0x48` =
  `updateLayout @0xb53430`, `+0x50` = `update @0xb4f9d0`).
- Сигнатура: `(CGameUI&, CSettings&, RenderWindow*, SceneManager*,
  SceneManager*, Window*, CResourceManager*)`; `r13=rcx`, `r15=r9`.
- `this+0x9140 = r15` = второй `SceneManager*` (на нём `createCamera("WardrobeCam")`
  через слот `+0x1a8`, сайт `0xb5f0ee` — согласуется: камера гардероба).
- `this+0x9150 = r13` = `RenderWindow*`. Значит фабрика viewport в `setOpen` —
  virtual `RenderWindow` слот `+0x48` с args `(Camera*, 3, 0.0, 0.0, 1.0)`.
  Кандидат `addViewport` требует сверки слота vtable OGRE — открыто, не заявлено.
- `this+0x9158 = 0`, `this+0x9170 = 0` (ноль в конструкторе; viewport ленивый,
  модель создаёт `createMenus`).
- `this+0x9184 = 0x459c4000 = 5000.0f`. В `setOpen` это даёт `x ~= 5.0`
  (парковка viewport за экраном?) — значение провизорное: сразу после идёт
  `updateLayout()`, его разбор покажет, правится ли `0x9184`/viewport там.
- vtable `CGenericModel = 0xfd1470` (ctor `@0x8a2a60`): слот `+0x50` =
  `CSceneNodeObject::setVisible(bool) @0xa01cb0`. Закрыто: `setOpen` делает
  `model->setVisible(true)` (`0xb4ecf4`), `createMenus` — `setVisible(false)`
  (`0xb56b54`). Аргументы `1`/`0` из ASM совпадают с `bool`.
- `this+0x9150` НЕ пишется в `createMenus` (только конструктор) — альтернативных
  писателей нет; `this+0x9184` тоже (только конструктор).

## Входящие вызовы: разрешены (машинный код)

Прямых рёбер в графе 0 — все вызовы виртуальные (слот `+0x40` = `setOpen`).
Разрешены охотой за `call *0x40(%rax)` и слотами vtable (байты из ELF):

Событийная цепочка (клики внутри окна):
`EventMouseButtonDown(left)` на окне с непустым свойством `onClick`
(проверка `isPropertyPresent`, значение кроме пустоты игнорируется;
рекурсия по детям ПЕРЕД собой — тот же child-first порядок, что в
`convertToScreenScale`) → `MemberFunctionSlot` (`vptr 0xfefcd0`, двойной режим:
младший бит `0x59` = virtual slot `0x58`) → `handle_onClick @0xb458d0`
(`edx=[args+0x28]` обязан быть 0/левая; `window=[args+0x10]`) →
`onClick(*(window+0x1d8))` (vtable слот `+0x98` = `onClick @0xb4f570`,
подтверждено байтами) → вкладки `14/15/16`: радио/видимость/флаг
`0x91a8/0x91a9/0x91aa`, `setProperty(UnselectedImage)`, `updateLayout()`.
`window+0x1d8` пишет `mapToFunctions @0xa980e0` (следующая зависимость пакета).

Переключение окна (клавиша/кнопка):
`CGameUI::toggleInventory @0xa8ea20` (`research/disassembly/a8ea20-toggle-inventory.asm`,
85 строк): `unPause()` → `modalDialogOpen()` gate (открыт — выход) →
`menu[+0x4d8]->setOpen(!menu->isOpen())` (слот `+0x40`, `xor $1`) → закрытие
соседей `setOpen(false)` на `[0x508]/[0x4f0]/[0x4f8]/[0x500]` по ветвям →
`moveToFront`. Кто зовёт `toggleInventory` (трейс клавиши `I`/
`guiToggleInventory`) — следующий шаг стадии «подключена».

## Перенос в порт (ported/wired-compared, граница выше)

`src/inventory_menu.cpp` (`InventoryMenuState` + `inventory_menu_viewport`):

- 4 пути `setOpen` — флагами и эффектами 1:1; вход `close_playing` подаёт
  результат запроса `animationPlaying("CLOSE")` (у порта нет модели гардероба,
  вызывающий путь передаёт `false` с явной пометкой — влияет только на
  reported-эффект, потребителя у него пока нет).
- Табы `0x0e/0x0f/0x10` (имена backpack/spells/fish — по порядку строк
  `TabBackpack/TabSpell/TabFish` перед писателями `+0x9120/+0x9128/+0x9130`);
  `0x59` табами не считается (идёт через `handle_onClick`, не в `onClick`).
- Viewport — пооперационно, NaN-поведение `ucomiss/maxss/cmpnltss` повторено
  ветвлениями (`(x<0)?0:x`, `(y<=0)?0:y`, строгие `>`/`<`); провизорный sliver
  НЕ «чинится» — оригинал считает именно его.
- Проводка: I-клавиша (`src/application.cpp`) считает запрошенный bool
  существующей логикой панелей (роль `toggleInventory`), вызывает машину,
  лениво фиксирует viewport окном/yratio, флаг едет в `inventory_view.open`.
  Кадр и так обновляет строки из сессии — это покрытие `update_layout`.
  Закрытие при смерти консистентно закрывает контроллер (семантика сброса —
  порта, не оригинала).

## Открытое (обновлено, не выдумывать)

- Точная цель virtual `RenderWindow+0x48` (создание viewport) — тип известен,
  слот открыт.
- Косвенный вызов через qword `[model+0x58]` в `createMenus` (`0xb56b46`,
  args `rdi=[this+0x68]`, `xmm0=0.5*(h_px-w_px/[0xfc6774])/yratio`, `xmm1=0`) —
  зависит от данных, цель открыта.
- `[Camera]+0x278` с `xmm0=w/h` — вероятно `Camera::setAspectRatio` (`inferred`).
- `queueTip(0)`: значение enum неизвестно. Смысл `+0x61`. Значения `KSETTINGS_*`.
- Входящие вызовы `setOpen` (в прямом графе 0).
- Полный разбор ветвей `createMenus` (620 переходов): фазы, писатели остальных
  полей, пути ошибок (`__cxa_throw x14`).

## createMenus: фазы (по машинному коду; ветви внутри фаз открыты)

Порядок опорных событий (`research/disassembly/b569e0-inventory-createmenus.asm`):

1. `GetInt(RES_WIDTH/HEIGHT)`, `createGenericModel` → `this+0x9170`,
   `generateExtremes`, `GetFloat(YRATIO)`, косвенный вызов `[model+0x58]`,
   `model->setVisible(false)` (`0xb56b54` — та же vtable-цель `+0x50`).
2. Программные окна: `this+0x1cf8` (`InventorySheet`?), `this+0x20` (корень),
   `+0x48/+0x28/+0x30/+0x38/+0x40` (фреймы), `+0x1d00`; свойства
   `RiseOnClick`/`False`, типы `DefaultWindow`, иконки `UIIcons`.
3. Загрузка layout: `getFileInfo(L"media/ui/inventorymenu.layout")`
   (`0xb575fe`, wide-строка — поэтому её нет в char-скане) →
   `loadWindowLayout` (`0xb57706`) → `convertToScreenScale(w, false/YRATIO)`
   (`0xb57723`) → `mapToFunctions` → `mapEventHandlers` (рекурсивный обход
   детей, `inventory_menu.c:2580+`). Масштабируется ЗАГРУЖЕННЫЙ layout, не
   программные окна.
4. Табы/радио/слоты (`TabBackpack/TabSpell/TabFish`, `Selected/UnselectedImage`,
   `SlotsEquipment/Spells/Fish`, `SlotGlow`, `Close`, `PaperdollEquip`,
   `RotateLeft/Right`): писатели `+0x9120/+0x91b0/+0x93c0/+0x9128/+0x9260/+0x9470/`
   `+0x9130/+0x9310/+0x9520`, тройка видимости `+0x9108/10/18`.
5. Хвост: `+0x9190/+0x9198` (`recursiveChildSearch` на `+0x28`: `Money`?,
   `WeaponSwitch`?), `+0x9148` = камера через virtual `[+0x9140]+0x1a8`
   (`SceneManager::createCamera`, имя `"WardrobeCam"`, сайт `0xb5f0ee`),
   `+0x91a0`, `CSkillTooltip::load` (`0xb5f22c`).
6. Пути ошибок: `__cxa_throw x14` (в основном `length_error` npos-ветви
   строковых сборок) + landing-pad'ы с `_Unwind_Resume` — какие именно входы
   их триггерят, открыто.

Все 25 писателей полей — ровно по одному разу (конструкционная семантика).
Байт `+0x3e2`, который пишут `createMenus:7793` и `updateLayout`, — поле
объекта `CEGUI::Window` (`*([0x20])+0x3e2 = 1`), не состояние меню
(`library-derived` граница, не переносить как поле `CInventoryMenu`).

## updateLayout @0xb53430: триаж (зависимость конца setOpen)

`research/disassembly/b53430-inventory-updatelayout.asm`, 0x35b0 байт, 269
вызовов, 175 условных переходов. Вход: `if (this[0x60]==0) goto exit`, затем
`if ([0x50]==0) goto exit` — флаг из `setOpen` стробирует обновление
(согласуется: закрытие не зовёт `updateLayout`). Содержание: иконки слотов
(`setSlotIcon`, `createIcon @0x882e30`, `getEquipmentRefInSlot`,
`getKnownSpell`, `getSkillIcon`), переводы строк, `ISA`-проверки типов.
**Ноль записей в поля `CInventoryMenu`** (`this` здесь в `r14`; записи
`0x3e2(%rbx)` — флаг окон CEGUI в цикле по слотам). Побочки — только окна
CEGUI и иконки. Viewport/`+0x9184` не трогает: парковка `x ~= 5.0` из `setOpen`
остаётся как есть. Полный разбор — отдельной записью при переносе.
