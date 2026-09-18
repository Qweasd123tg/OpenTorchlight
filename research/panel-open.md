# Семейство setOpen панелей: merchant/pet/quest/skill/journal

Статус: все пять — **разобраны** (представитель целиком, остальные —
проверенные дельты; что именно прочитано — ниже). Не перенесены, не
подключены, не сравнены. База inventory-пакета: `research/inventory-open.md`.

## Входы

- ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- ASM-тела извлечены из внешнего набора (см. `research/codefirst/README.md`),
  проверены по ELF: множества адресов совпадают 0/0, тела совпадают кроме
  verbosity комментариев objdump.
  `research/disassembly/b6a220-merchant-setopen.asm` (298),
  `b92aa0-pet-setopen.asm` (310), `bc2550-quest-setopen.asm` (198),
  `be1130-skill-setopen.asm` (280), `e3a680-journal-setopen.asm` (198).
- Декомпиляция (навигация): `merchant_menu.c`, `pet_menu.c`, `quest_menu.c`,
  `journal_menu.c`; у `CSkillMenu::setOpen` декомпиляции нет — только ASM.

## Общий скелет (все пять + inventory)

Флаг `cmpb` → уже-открыто+param (store; updateLayout только у
inventory/merchant/pet, см. дельты) / закрытие (`playSample(0x42)`,
`blendAnimation("CLOSE",false,0.1,2.0,-1.0)`, clear обоих флагов) /
закрыто+!param (store 0) / открытие (`playSample(0x16)`, `GetInt` w/h,
`model->setVisible(true)` слот `+0x50`, `animationPlaying("CLOSE")` →
blend-OPEN/иначе play-OPEN, всегда `queueBlendAnimation("IDLE",true,0.1,1.0)`,
`addChildWindow`, `moveToBack`, тройки, trailing `*0x48`).
Строки `CLOSE/OPEN/IDLE`, сэмплы `0x16/0x42`, константы `0.1/2.0/-1.0` — везде.

## Дельты

| | inventory | merchant | pet | quest | skill | journal |
|---|---|---|---|---|---|---|
| адрес/размер | b4eb70/0x632 | b6a220/0x563 | b92aa0/~0x5f8 | bc2550/~0x3xx | be1130/~0x4xx | e3a680/~0x3xx |
| флаг/флаг2 | 60/61 | 60/61 | 68/69 | 188/189 | 38/39 | 38/39 |
| settings/model/sound | 68/9170/9188 | 68/90/a8 | 88/9170/9180 | 198/1b0/1d8 | 48/60/e8 | 40/58/80 |
| addChildWindow | [0x18]+[0x20] | [0x18]+[0x20] | [0x18]+[0x20] | [0x10]+[0x18] | [0x10]+[0x18] | [0x10]+[0x18] |
| тройки радио/видимости | 1 | 2 + индекс | 1 | нет | 3 + индекс | нет |
| viewport (scaledY×4) | да 124/132/166/192 | НЕТ | да 97/166/135/169 | НЕТ | НЕТ | НЕТ |
| закрытие: removeChild | условное (+0x91a0) | нет | да | нет | да (+0x750) | нет |
| queueTip | (0) | 0x0c/0x05 по ISA | 0x0f (одна ветвь) | нет | нет | нет |
| playSample open/close | 22/66 | 22/12 | 22/66 | 22/66 | 22/66 | 22/66 |
| уже-открыто+open | store+updateLayout | store+updateLayout | store+updateLayout | только store | только store | только store |

Детали представителя merchant (прочитан целиком): вторая тройка
(radio `+0x3420/10/18`, visible `+0x3408/+0x33f8/+0x3400`) выбирается по
`getDefaultMerchantTab()` владельца `[0x50]` (1/2/иначе), индекс пишется в
`+0x3454` (0/1/2), `+0x3458` обнуляется. Владелец — `CCharacter*`.

Pet: префикс-гейт — при запросе open читается `[[0x58]+0x330]`, значения
`0x29/0x2a` ведут на shared-эпилог (store param, без открытия); смысл
состояния открыт. Фабрика viewport: `[0x9178]+0x48`, `edx=4` (у inventory 3).
Камера гейт: `getGameUI()` из `CResourceManager`, не поле. Пишет `+0x6c=0`,
`moveToBack([0x20])` + `moveToFront([0x48],[0x28])`.

Skill: индекс таба `+0xe0` (0/1/2), читается ПЕРЕД тройками; ветвь `!=0,1,2`
оставляет тройку и идёт на trailing update. `removeChildWindow` через цепочку
`+0x750` (как `+0x91a0` у inventory).

Quest ≡ journal: доказано полное скелетное тождество (198/198 инструкций,
различия только в смещениях/адресах переходов/nop). Закрытие идёт через
shared-эпилог `mov param→flag` (тот же нетто-эффект). Без троек, без типов,
без viewport, без removeChildWindow.

## Звуки (проверено по путям, не по порядку адресов)

`CSoundBank::playSample(id, null, 0, 0, false)`: open — всегда 22, где звук
есть; close — 66, кроме merchant (12) и stash (21, профиля пока нет).
Назначение open/close доказано разбором ветвей флага (inventory/merchant/
stash/pet/quest/skill; journal — через тождество с quest + тот же порядок).
Закрытие без открытия молча store'ит флаг (звука нет), анимация закрытия —
`blendAnimation("CLOSE")` (литерал `0xfe6008`, проверен в inventory/merchant/
quest/skill). Файлы — `resource-derived` (`media/sounds/UI.DAT.adm`:
`InventoryOpen→sheet_openright.wav`, `InventoryClose→sheet_close.wav` + …),
но id — рантайм-хэндлы банка (`addSample` зовут десятки инициализаторов
юнитов, порядок заполнения = порядок загрузки): связка id→файл требует
трейса заполнения банка — открыто. Стока семплов в порту нет (open).
В Batch-проверке ещё 6 звучащих `setOpen` без профилей
(combine/dropdown/enchant/options/stats + stash): id сняты, назначений
open/close для них НЕ делалось (их скелеты не разбирались).

## Перенос: один helper + таблица профилей

`src/panel_open.cpp` (`PanelOpenState` + 6 `PanelProfile`), тест
`tests/panel_open_test.cpp` (87 утверждений: скелет циклом по профилям +
дельты + литералы viewport пета). `src/inventory_menu.cpp` стал тонким
адаптером поверх helper с тем же API — его 53 утверждения идут через обёртку
и доказывают эквивалентность непрерывно.

- Профили несут только роли/константы/условия (смещения не переносятся).
- Таб-клики остались только у inventory (его `onClick` разобран); у остальных
  нет перенесённого `onClick` — кликов нет.
- `detach_child` репортится без потребителя (условность оригинала зависит от
  дерева CEGUI — отмечено, не смоделировано).
- Pet-gate вход — сырой `companion_mode`, проводки нет ( wired=false у всех,
  кроме inventory).
- По пути тест поймал баг переноса: trailing `updateLayout` стоит на пути
  открытия у всех (флаг профиля — только для повторного открытия). Исправлено
  до коммита стадий.

## Открытое по семейству

- Точные цели `RenderWindow+0x48` (фабрики viewport у inventory/pet; у pet
  `edx=4`), `[model+0x58]` у inventory, писатели `window+0x1d8`
  (`mapToFunctions`), смысл pet-состояния `0x29/0x2a` и `[0x58]`, смысл
  вторых флагов, `KSETTINGS_*` в рантайме.
- Входящие `toggleX` для неинвентарных меню (у inventory — `toggleInventory`).

- Точные цели `RenderWindow+0x48` (фабрики viewport у inventory/pet; у pet
  `edx=4`), `[model+0x58]` у inventory, писатели `window+0x1d8`
  (`mapToFunctions`), смысл pet-состояния `0x29/0x2a` и `[0x58]`, смысл
  вторых флагов, `KSETTINGS_*` в рантайме.
- Входящие `toggleX` для неинвентарных меню (у inventory — `toggleInventory`).
- Порт-импликация: общий helper (флаг-машина + сэмплы + OPEN/IDLE-выбор) с
  таблицей параметров на меню (смещения не переносятся — только роли);
  viewport-математика — отдельно на меню (константы разные);
  таб-переключатели — отдельно (0/1/2/3 группы + индексные поля merchant
  `+0x3454` / skill `+0xe0`); quest/journal — минимальный профиль без
  троек и типов.
