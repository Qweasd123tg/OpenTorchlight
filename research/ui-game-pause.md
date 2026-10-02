# Пауза мира и частично открытые панели

2026-10-02, `original-code`: pinned ELF SHA
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Основные функции целиком: `CGameClient::getIsPaused @0x56e570` (139 bytes),
`CGameUI::bothCoveredPartial @0xa82ae0` (277),
`modalDialogOpenPartial @0xa82a80` (86), `getConsoleIsOpen @0xa84140` (27).
Caller: `CGameClient::updateIngame @0x58e5f0`.

## От полей до решения

getIsPaused сначала читает u8 client+0x10bb (forced pause), затем UI u64
pointer+0x78. Null UI даёт false. При наличии UI порядок:
bothCoveredPartial -> console open и GetInt(CONSOLE_NOPAUSE)==0 -> modal partial
-> u8 UI+0x1999 explicit pause. Pointer+0x78 перечитывается после каждого
query; динамическая замена владельца остаётся вне immutable port query.
Forced/both/console/modal дают canonical 1, final explicit читается как byte;
перенос использует корректно initialized bool domain 0/1.

bothCoveredPartial читает vector begin/end u64 UI+0x1930/+0x1938, дважды
обходит array указателей. Vtable+0x18 isRight; +0x28 openPartial. Первый scan
собирает открытые левые, второй открытые правые; нет early exit из scans.
Пауза требует обоих. Getter family подтверждён неизменёнными телами:

| Меню | isRight | openPartial |
| --- | --- | --- |
| Inventory | `0xb60ed0`: 1 | `0xb60f00`: u8+0x60 |
| Merchant | `0xb77580`: 0 | `0xb775b0`: u8+0x60 |
| Quest | `0xbcca70`: 1 | `0xbccaa0`: u8+0x188 |
| Skill | `0xbee2b0`: 1 | `0xbee2e0`: u8+0x38 |

Поэтому одна Inventory, Skill или Quest панель **не останавливает мир**.
Inventory+Merchant останавливают. Несколько открытых правых панелей сами по
себе не заменяют левую. Это правило getter roles, не вывод из XML ширины.

modalDialogOpenPartial обходит vector UI+0x1948/+0x1950 и проверяет u8
dialog+0x30. Console pointer UI+0x1690 -> CConsole::getVisible @0xae1df0 ->
Window pointer console+0x18 -> CEGUI isVisible(false). Null guards дают 0.
GetInt @0xc6e440 читает vector i32 properties+0x40/+0x48, индекс вне массива
даёт -1, который также означает console no-pause. Setting index находится в
KSETTINGS_CONSOLE_NOPAUSE @0x150b4cc; fixture задаёт его как explicit index 0.
Нет записей state/ресурсов в query family. Virtual query reentrancy, resizing,
исключения и полный UI lifetime не имитируются.

## Производственный потребитель времени

Оригинальный updateIngame вызывает getIsPaused `0x58e626`; результат хранит
EBP. Gate `0x58e8a5..0x58e8a8` пропускает CLevel::update `0x58e8ec` при pause.
В non-editor normal branch cast/attack не являются отдельными pause inputs.
Первоначальный port вместо этого обнулял timestep при любом inventory_view.open
и дополнительно блокировал AI/logic при skill cast.

`ui_pause.cpp` переносит evaluated query contract. Application передаёт живые
Inventory/merchant/quest/skill controller flags, исходные right roles и explicit
frontend pause. Console/forced/modal runtime здесь отсутствует, нулевые inputs
обозначают отсутствие соответствующих port объектов. Single writer controllers
остаются владельцами flags; отдельный snapshot-only pause bool не хранится.

Решение используется **до** update_vitals/ActorMotion и всеми активными
simulation gates: waypoint continuation, arrival/pickup, combat/AI, LogicRuntime,
animation clocks, enemy/player HIT и skill event delivery. Так ранее начатый
удар не теряет HIT из-за открытой одной панели. Внешние world-click commands
по-прежнему блокируются overlay input adapter; это другой контракт.
AI/logic больше не замораживаются только из-за активного cast; запуск нового
player ordinary attack по-прежнему не совмещается с owned skill cast.

`prototype`: dt clamp 0.1, dead overlay pause/death pose, pending warp и modal
input routing сохраняют прежние отдельно описанные границы. Original substeps,
paused character-only animations/particles, console/modals, wardrobe animation,
full getIsPaused owner reentrancy и весь updateIngame не объявляются закрытыми.

## Сравнение

`original_ui_pause_comparison` сравнивает **1536** комбинаций flags, 16 panel
masks и console no-pause -1/0/1 с production query. Исполняются 14 неизменённых
whole bodies, включая реальные isRight/openPartial getters, modal/console
guards и GetInt. Единственный named adapter — уже оценённая CEGUI visibility.
Raw object buffers/property index являются явно заданными synthetic inputs;
constructors/game process/GUI events не запускаются.

`ui_game_pause` использует настоящие production panel controllers, проверяет
single/right/both sides и приоритет forced/UI/console/modal. Application собран
и прошёл syntax gate; source integration проверена по перечисленным consumers.
UI/frame scenarios в этом проходе отдельно не запускались. `completion: partial`
отражает именно эти remaining ownership/lifecycle/time boundaries.
