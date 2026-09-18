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

## createMenus: карта (машинный код; поправлено по полному проходу)

Опорный срез: `research/disassembly/b569e0-inventory-createmenus.asm`
(7599 строк). Вызовы-функции внутри (прямые, не PLT): `GetInt x2`
(`RES_WIDTH/HEIGHT`), `createGenericModel`, `generateExtremes`,
`loadWindowLayout`, `convertToScreenScale`, `mapToFunctions`,
`mapEventHandlers`, `CSkillTooltip::load`, `GetFloat` (`YRATIO`),
`GetValueAsString`, `uniqueName x7`, `getFileInfo`. Остальное — CEGUI/Ogre
PLT и строковые сборки (`__cxa_throw x14`, в основном `length_error`
npos-ветви — это НЕ логические ветви меню).

Порядок фаз:

1. Пролог: `GetInt(RES_WIDTH/HEIGHT)` → `createGenericModel` → `this+0x9170`
   → `generateExtremes` → `GetFloat(YRATIO)` → косвенный `[model+0x58]`
   → AABB ±100000 (`0xc7c35000/0x47c35000`, `0xb56a80`) → `model->setVisible`
   (vtable `+0x50`, `0xb56b54`) → `getImageset("UIIcons")` → `this+0x1cf8`
   (исправлено: раньше было записано `InventorySheet` — неверно).
2. Корневые окна (тип `DefaultWindow`, `createWindow(type, name)` —
   порядок аргументов подтверждён сайтом 1: `rsi="DefaultWindow"`,
   `rdx="InventorySheet"`): `+0x20` (`"InventorySheet"`), `+0x30`
   (`"ISockets"`, под `+0x28`, размер = размер родителя,
   `RiseOnClick=False`, позиция 0, байт окна `+0x3e2=1`, front),
   `+0x38`, `+0x40` (имена — открыто, рядом только литерал типа).
3. Layout: `getFileInfo` (wide-имя, `.bss` — статически не читается) →
   `loadWindowLayout` (`0xb57706`) → корень layout → на нём
   `convertToScreenScale(w,false)` → `mapToFunctions` → `mapEventHandlers`.
   Масштабируется ЗАГРУЖЕННЫЙ layout, не программные окна.
4. Захваты из layout (`recursiveChildSearch`, 19/19 ключей извлечены):
   `Blocker` (сразу в дело), `BottomFrame→+0x48`, `TopFrame→+0x28`,
   `SlotGlow→+0x1d00`, `Close/PaperdollEquip/RotateLeft/RotateRight`
   (в дело), `TabBackpack→+0x9120`, `TabSpell→+0x9128`, `TabFish→+0x9130`,
   `SlotsEquipment→+0x9108`, `SlotsSpells→+0x9110`, `SlotsFish→+0x9118`,
   `Money→+0x9190`, `WeaponSwitch→+0x9198`, + динамический ключ из таблицы
   `.bss 0x14c6b20` (цикл A) + `"Slot"+N` (цикл B). Перешло: `TopFrame` и
   `BottomFrame` отцепляются от старого родителя (`window+0xb0`) и
   переподвешиваются (`BottomFrame` под `+0x20`), `RiseOnClick=False`,
   `setZOrderingEnabled(false)`; `SlotsSpells/SlotsFish→setVisible(false)`.
   Проверено по `media/UI/inventorymenu.layout` из `pak.zip` (98 окон):
   все ключи в нём есть.
5. Цикл A (`0xb59b00–0xb5b600`, счётчик 0..11): имя из таблицы 12
   `std::string` (`.bss`), поиск под `TopFrame`, проводка слота (см. 6),
   обнуление 4 массивов меню `+0x1028/+0x12b8/+0x17d8/+0x1548`
   (по 8 байт x12) + 3 `createWindow` с `uniqueName`-именами
   (`'gui_'`-префикс) за итерацию = 36 окон.
6. Проводка слота (одинакова в цикле A и B): `Window+0x213=0`,
   `setWantsMultiClickEvents(false)`, `window+0x1d8 = &menu+0x80[k]`
   (k = счётчик в A; k = счётчик+0x12 в B), две подписки через
   `MemberFunctionSlot` (vtable `0xfefcd0`): `handle_ItemClick @0xb45810`
   (событие — глобала `.bss`, имя открыто) +
   `handle_MouseOver @0xb4d590` (вторая `.bss`-глобала).
7. Цикл B (`0xb5c4b9–0xb5e20f`, счётчик 1..63): ключ `"Slot"+N`
   (`GetValueAsString`), поиск под `BottomFrame` (= `Slot1..63` из layout),
   проводка (6) с `k=i+0x12`, окно слота → `menu+0x10c0[i-1]`,
   4 `createWindow` с `uniqueName`-именами за итерацию = 252 окна;
   оверлеи копируют позицию/размер найденного слота, `setMutedState(true)`,
   `setAlwaysOnTop(true)`; последний → `menu+0x1b00[i-1]`.
   Итого динамика: 4 + 36 + 252 = 292 окна.
8. Хвост: `+0x9148` = результат виртуального вызова на `+0x9140`
   (`[vtable]+0x1a8`, `0xb5f0ee`; исправлено: `"WardrobeCam"` в этом срезе
   НЕ упоминается — старый claim отозван, цель открыта); `CSkillTooltip`
   (`new`, поля `+0x10/+0x20=-1/+0x28`) → `+0x91a0`,
   `CSkillTooltip::load(gameui=+0x70, L"media/UI/skilltooltip.layout")`
   — имя файла прочитано из ELF как UTF-32 (`0xfe5528`), layout есть в
   `pak.zip` (`resource-derived`).

Байт окна `+0x3e2` (=1 у созданных/оверлеев) — поле `CEGUI::Window`, не меню
(`library-derived` граница). `window+0xb0` — родитель (наблюдено в
`removeChildWindow(0xb0(child))`, `inferred`). `window+0x213` — байт-флаг
(0 у слотов), смысл открыт.

Открыто по createMenus: имена `+0x38/+0x40`; содержимое таблицы `0x14c6b20`
и wide-имя layout (`.bss` — нужен рантайм-трейс); имена двух событий подписок
(`.bss`-глобалы `0x14247e0/0x1423b80`); свойства/позиции 7 групп созданных
окон (сайты 5–11 детально); цель `[+0x9140]+0x1a8`; какие входы триггерят
14 `throw`-путей.

## Мелкие помощники: разобраны целиком и перенесены

- `STRINGS::GetValueAsString(uint) @0xc91f60` (168 строк ASM): тело — только
  libstdc++ (`ostringstream` + `operator<<(unsigned long)` + `str()`),
  локаль по умолчанию (C). Порт: `original_uint_to_string` (явный decimal),
  дифференциально сверён с `snprintf %u` (0, 1..63, 100, 2^32-1).
- `STRINGS::uniqueName @0xc8ea50` (97 строк): `prefix + '_' + decimal(++n)`,
  разделитель `_` — байт `.rodata 0xfd3a73`, число —
  `Ogre::StringConverter::toString(n, width=0)` (plain decimal),
  счётчик — статик `.bss 0x14e6914` (в порту явное состояние
  `UniqueNameState`). Refcount/EH-шаблон не переносится (нет модели
  аллокатора). Обе — `analyzed/ported/wired/compared` (scoped).
- Разбор проводки частично автоматизирован:
  `tools/extract_menu_wiring.py` (пул литералов, copy-loop→строки, сайты
  `createWindow`, ключи поисков, подписки→символы, счётчики циклов,
  внутренние вызовы). Выход на `b569e0` сошёлся с ручной картой 1-в-1
  (11 сайтов, 19 ключей, циклы 12/64, 21 подписка) + нашёл пропущенные
  вручную подписки кнопок/спеллов. Механика — да, семантика CEGUI и
  `.bss`-имена — по-прежнему руками.

## Крупный проход: все createMenus/setOpen/update меню (автоматически)

`tools/batch_menu_pass.py` + `research/batch-menu-pass.json` (76 функций;
срезы — рабочий материал в `research/disassembly/batch/`, не коммитятся).
Итог по `createMenus` (26 меню):

- **Семья циклов** (`creates=11`, второй счётчик =64 — Slot-петля общая):
  inventory (таблица 12, база `+0x80`), merchant (таблица 127, `+0xb0`,
  табы Armor/Misc/Weapon + Pet-варианты), pet (таблица 12, проводка иной
  формы — открыто, стат-лейблы), stash (таблица 43, `+0xb0`). Везде
  `idxoff +0x12`, захваты `Blocker/BottomFrame/TopFrame/SlotGlow/Close`,
  подписки `{CloseButton, ItemClick, MouseOut, MouseOver, MouseThrough}` +
  классовые (у inventory≡pet — 12 одинаковых; у merchant≡stash — 8 с
  Pet*-вариантами). Один обобщённый helper + 4 таблицы профилей.
- **Близнецы** `creates=8/searches=4/subs=5`: combine ≡ enchant.
- **Только захваты** (`creates=0`): dialog, die, fishing, interactive, modal,
  options, difficulty, mainmenu, newgame, tip, cinematic, waypoint +
  settings (18 поисков), continue (27 поисков) — портабельны как таблицы
  ключей без fresh-окон.
- **Средние**: questdialog (5), quest (6), skill/journal/stats (1).
- `setOpen`/`update`: проводки CEGUI нет (флаг-машины), кроме петель
  settings-`setOpen` (6, 3) и waypoint-`setOpen` — им нужен свой разбор.

## Обобщение: один профиль на семью циклов (сгенерировано + проверено)
`tools/gen_menu_profiles.py` транскрибирует batch-отчёт в
`include/torchlight/menu_create_profiles.hpp` (4 профиля:
границы петель, базы back-pointer, все ключи захватов, id подписок),
`tests/menu_create_test.cpp` пинит 112 утверждений. Ручная проверка
генерата: базы обеих петель совпадают внутри класса
(inventory `+0x80`, merchant/stash `+0xb0`, pet `+0xa0`), `idxoff +0x12`
везде, ключи и id — по срезам. Открыто и НЕ в профилях: свойства окон,
имена `createWindow`, `.bss`-имена, доставка событий — поэтому стадии
трёх `createMenus` остаются `false`, данные — только transcription.

## Средние createMenus: ключи петель проверены, профилей стало 10

- Combine ≠ enchant («близнецы» только по счётчикам 8/4/5): combine —
  петля `ItemSlot1..4` (тело 0..3, ключи +1, база `+0xf8`, plain-индекс);
  enchant — одиночный статический `ItemSlot` (база `+0xc4`, без страйда).
- Quest: `Quest1..6` + `QuestText1..6` в одной петле (r15, без back-pointer),
  `ItemRewardBkg1..3` + `ItemRewardSlot1..3` в одной петле (база `+0xd8`).
- QuestDialog: `ItemBkg1..3` + `ItemSlot1..3` в одной петле ×3 (база `+0x148`).
- Skill/journal: только статика (фреймы A/B/C, табы, `Skill Points` с
  пробелом — inline-паттерн это взял).
- Петля заклинаний инвентаря (`Spell1..4`, счётчик `0x18`) и пета
  (`Spell1..2`, bound-2 петля) — back-pointer у заклинаний нет нигде.
- Границы петель всех классов сверены с layout (`Slot1..126` торговца =
  bound 127 и т.д.). Sidecar `research/menu-key-loops.json` — единственный
  ручной источник петель; скаляры профилей берутся из него, не из
  авто-детекта (тот ловил шаги счётчиков вроде `+0x1`).
- Стадии шести новых `createMenus` — `false` (transcription); стадии поднимутся
  только с полным разбором свойств окон и доставки событий.

## Grab-only меню: таблицы ключей (сгенерировано + проверено)

`gen_menu_profiles.py --grab-only` → `menu_grab_tables.hpp` (14 таблиц),
тест 17 утверждений. Extractor к этому проходу выучил: this-регистр
(`rbx`/`r12`), inline-ключи (`movl`, `XP/HP/Mana` пета), String-ctor ключи
(`JournalFrame` журнала), префиксы динамик (`Slot/Spell/PetSlot/ItemSlot/
ItemReward*/Quest*/Button/Choice`). Проверено вручную: settings (18
виджетов с полями), continue (27), waypoint (`Button/Choice+N`),
fishing/interactive (пусто — только pipeline). Статус: transcription,
не перенос; в ledger не вносятся, граница семейства — в реестре.

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
