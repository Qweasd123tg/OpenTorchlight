# Автоподбор золота: от on-screen списка до кошелька

2026-10-02. `original-code`: ELF SHA
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Основная owning function целиком: `CGameClient::autoPickupGold @0x56e3a0`,
302 bytes. `CCharacter::alive @0x80e850`, 21 bytes; caller
`CGameClient::updateIngame @0x58e5f0`. Точка вызова `0x58e8fa` находится после
unpaused level update и перед character-animation/on-screen refresh branch.

## Полный контракт owning function

Null player u64 client+0x58 даёт ранний выход. alive читает character i32
state+0x330: 5/6 false, остальные true. Нулевой u8 character+0x264 также даёт
ранний выход. Это pathing flag, не guessed running/auto-loot option:
`stopPathing @0x80e8b0` его очищает; `setDestination(CLevel&,float,float)
@0x82ac30` устанавливает его в `0x82b3cf` (`movb $1,0x264(%rbx)`).
Тот же path builder очищает флаг в `0x82acd0` и `0x82b10b`.

Client+0x70 — level u64; level+0xc0 — pointer to список on-screen items.
List head — первый u64 container; node+0 — item u64, node+8 — next u64.
`0x56e408` читает next **до** вызовов для текущего предмета, чтобы getItem
мог удалить current node. Каждый item проходит ISA(0x22) `0x56e40c`.
Для GOLD позиции player/item получаются через getPosition(true) `0x9e7080`;
caller `0x56e424..0x56e45f` подтверждает SysV aggregate X/Y в XMM0 и Z в XMM1.

`0x56e47c..0x56e49e`: target.x-player.x и target.z-player.z, две отдельные
f32 square, сначала `xx+0`, затем `+zz`. Y полностью исключён. SQRTSS
`0x56e4aa` и UCOMISS/JBE `0x56e4ae..0x56e4b1` допускают **строго <3.0**;
literal `0xfa86d4` — bytes `00004040`. Exact 3, larger и unordered не проходят.
Каждый принятый target передаётся в getItem(player,item,level) `0x56e4c4`;
порядок supplied linked list сохраняется. Собственных полевых записей и
allocations в этой owning function нет; getItem и object lifetime — зависимости.

## Важный producer: это не список всех предметов

`CLevel::findItemsOnscreen @0x94f730` очищает/rebuilds level+0xc0 из списка
units+0x90. Item eligibility, virtual +0x48, camera/view/projection и XY/depth
проверяются перед добавлением. XY gate по ASM `0x95013a..0x950190`:
X>-1 и X<=1, Y>=-1 и Y<=1; literal -1 `0xfa8760`, +1 `0xfa47fc`.
On-screen список обновляется после autoPickupGold, следовательно следующая
simulation phase использует previous-frame membership и актуальные позиции.
`addItem @0x95c970` вставляет новые units в head (+0x90, `0x95ca23`),
findItemsOnscreen также prepends accepted nodes; в normal creation projection
две инверсии дают исходный creation order.

Production API требует **явный on-screen ID список**. Пустой список не
подменяется всей world. Application rebuilds cache после реального draw по
существующим renderer instances и его actual last-rendered camera; при menu
pause cache остаётся прежним. `world_point_on_screen` использует исходные XY
границы с имеющимся `CameraProjection::project_ndc`, допускает только normal
front-facing point projection. **Prototype adapter boundary**: full original
camera/inverse-matrix math, CItem eligibility fields/virtual callbacks, dynamic
original list ownership и paused rendering не закрыты. Здесь нет guessed
camera position или fabricated gold positions: читаются реальные port state.
Нативное сравнение ниже не включает этот render provider и не доказывает его
полную эквивалентность findItemsOnscreen.

## Consumers и владение

`auto_gold_targets` переносит alive/pathing/type/XZ/strict-radius selection.
`PlayerSession::auto_pick_up_gold` получает живой ActorMotion::moving, HP state,
known on-screen IDs, current entity positions и evaluated ISA(0x22) из
resource UnitTypeHierarchy. Он пропускает unavailable/non-gold entities и
передаёт выбранные IDs в существующий pick_up_gold. Тот использует **сохранённый
оценённый amount**, помечает entity consumed через World/Logic и кредитует
wallet с saturation. Graph/RNG rank-generation сохраняет прежнюю prototype
границу [recovery-gameplay.md](recovery-gameplay.md).

Перед ownership effects заканчиваются allocations candidate collection.
World scripts остаются queued до завершения scan; collection не удерживает
pointer/iterator в world vector через growth. Application скрывает реальные
mesh instances, снимает уже consumed active_pickup и drains queued logic.
Wallet/HUD и world checkpoint читают те же обновлённые состояния. Zero-amount
gold тоже consumes один объект; повторный scan не выдаёт награду заново.

## Проверки и остаток

`original_auto_gold_comparison`: **6006** сценариев unchanged whole
autoPickupGold + alive bodies. Три названных adapters: evaluated ISA,
getPosition ABI/raw position и getItem recording. Выбраны life states0/5/6,
pathing0/1, другой type, XZ/height independence, exact/adjacent-f32 boundary,
multiple items и cached next при invalidation current node. Results сравниваются
с используемым production selector. No original constructors/game/process,
full getItem effects или native visibility-list construction исполняются.

`auto_gold_pickup` проверяет pure consumer; `original_auto_gold_collection`
использует реальные pak/Gold type/player/graphs и actual spawned world items
с явно заданной membership fixture. Проверены stationary/dead guards, empty
on-screen input, available/hidden/exact-radius items, zero amount, no duplicate
credit, wallet saturation и saved consumed entity flags. Height fixture здесь
тестирует selection only, не camera visibility. Application/GLES собраны;
UI/frame runs не запрашивались и отдельно не выполнялись.

`completion: partial`: original on-screen provider, full getItem effects
(sounds, item quest events, callbacks/resources), linked-list ownership,
character state/path lifecycle и original save format остаются открытыми.
Каждая существенная новая арифметическая константа и branch выше имеет ASM
источник; underlying portable adapters остаются явно отмеченными.
