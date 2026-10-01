# Menu player: Create/Load -> original markers -> animated model

Проверено 2026-09-30. Это подключённый срез, не полное закрытие GameClient,
CLevel или оригинального save/runtime ABI. Входы и хеши:
[menu-player-inputs.json](menu-player-inputs.json). ELF, pak и shipped библиотеки
использованы только для чтения. Полные тела малых функций и явно помеченные
окна больших тел сохранены в `disassembly/menu-player-preview.asm`;
библиотечное сравнение — `disassembly/ogre165-menu-math.asm`.

## Original contract and fields

`original-code`: `CGameClient::setCreationClass @0x582d00` сравнивает класс
`+0x1a8`, при изменении отсоединяет GameUI player (`0x582d39`), удаляет прежнего
из уровня (`0x582d4b`) и освобождает (`0x582d5c`), создаёт нового
(`0x582d7b`), пишет player pointer64 `+0x58`, alignment int32=1,
вызывает firstTimeSetup, присваивает имя, добавляет к level position
`+0x140` (`0x582de9`), применяет toward `+0x164` (`0x582dfd`) и возвращает
GameUI player (`0x582e0d`). Pending int32 `+0x1038=3` пишется и при том же
классе (`0x582e12`). Portable GUID selection не заменяет оригинальную строку
класса/ResourceManager ABI; тот же класс сохраняет текущую preview модель.

`applyCharacterState @0x584460` требует save и существующего player, сохраняет
filename в `+0x1a8`, заменяет player с createPlayer(filename,true), virtual
restoreState, именем и теми же placement/toward consumers (`0x584572/0x584586`).
Затем отдельно восстанавливает pet. `CContinueGameMenu::selectCharacter`
вызывает этот путь `0xc3fb9c`. Наш read-only OTC adapter читает выбранный
slot/revision, проверяет identity и использует существующий restore_player;
из его inventory берётся реально equipped weapon. Сохранения не записываются
при просмотре. Dead/unreadable preview скрывается с diagnostic notice:
death/retired pose и SVB producer не восстановлены, живой герой не подставляется.

`CPropertyNode` constructor `0x9e862c` инициализирует uint32 TYPE `+0x10c=1`
(Player Start). Отсутствующий TYPE у Town Player Start нельзя считать типом0.
В menu entryType3 Player Start (`0x960ad8 -> 0x960e98`) и Entrance
(`0x9609c0`) записывают position float32[3] `+0x140` и toward float32[3]
`+0x164`; последнее подходящее присваивание побеждает. Exit для menu не выбран.
`getPosition(true)` — `0x9601e6`, derived orientation — `0x960225`,
OGRE zAxis — `0x960235`. Y сбрасывается в0, X/Z нормализуются при float32
length > double `1e-8 @0xfa87a0` (`0x960251..0x9602c2`).
`CCharacter::setToward @0x8126e0` использует atan2f(x,z), VerifyFloat и
`MATH::matrixRotationY @0xc7a2a0`: radians передаются непосредственно в sincosf.
Конечные resource vectors используются без degrees round trip; invalid source
отклоняется. Общая VerifyFloat recovery semantics остаётся вне этого среза.

## Corrected Group boundary

Ранее menu camera ошибочно считала редакторский Group графическим parent.
`getPosition(true)` действительно читает derived position, но одного этого
недостаточно, чтобы превратить PARENTID в OGRE edge.

`original-code`: `setParentGuid @0x59f070` пишет GUID64 в editor `+0x18`.
`CRandomGroupDescriptor` ctor `0x6373b7` передаёт имя `Group @0xfa8310`;
`rollGroup @0x74b330/0x74b361` сравнивает child editor parent GUID `+0x18`
с group GUID `+0x20`. Графический owner имеет отдельное pointer64 поле `+0x50`.
`CLayout::editorObjectCreated @0x9df820`, ветвь `0x9df843..0x9df854`,
при null/external scene-owner parent вызывает virtual slot+0x10 с owning
CLayout (`0x9df9d8..0x9df9e2`). Base vtable `0xfc45a0+0x20` задаёт
setParentPositionableObject; scene-node override `0xa01f30` передаёт parent
node `+0x58` в `sceneNodeSetParent @0xa01e10`. Binary object loader
`0x74c660` не добавляет графический parent по аргументу editor grouping.

В подтверждённой Town/ALL-group границе Group pivots поэтому исключаются
из transform view, а реальные expanded Layout Link transforms сохраняются.
Исходный manifest и его editor GUID/properties остаются доступными отдельно.
Это исправляет **камеру, player и menu geometry одним правилом**, без ручного
вычитания Town константы. Полный random/dynamic group loader не перенесён.

`resource-derived`: Town Player Start `(66.2762985,1.21500003,9.37747002)`;
forward approximately `(0.891007,0,0.453989)`. Camera
`(73.3457031,2.5,10.8483)`, target `(65.128,1.02,9.14627)`.
Pivot Group Properties `(69,0,14)` повторно не прибавляется.

## Library reuse and real consumers

`library-derived`: включён **неизменённый OgreQuaternion.cpp из OGRE 1.6.5**
и его Linux header closure (17 stock source/header/license файлов),
`third_party/ogre-1.6.5-math/source-inputs.json` фиксирует каждый SHA-256.
Archive `7fc0e948679c1c1f10751756d267a41d0e3395a6520a23f7853a0ae39a1281f5`;
version macros1/6/5 совпадают с shipped library. LGPL2.1 + OGRE exceptions
сохранены целиком в COPYING. Нового алгоритма Matrix3->Quaternion нет.

Build differences: float Real, STD allocator вместо NED, thread support0,
static/PIC, hidden symbols и section GC; core C++17, stock unit C++11.
Unused quaternion APIs с зависимостями Ogre::Math отсекаются. В final shared
Application probe нет unresolved Ogre symbols. Это math subset Linux
GNU/Clang, не второй движок или замена OGRE renderer/resource manager.
Штатные FromRotationMatrix/normalise/composition/vector rotation/zAxis реально
потребляются placement resolver. Shipped FromRotationMatrix `0x23ca30`,
normalise `0x23c710`, zAxis `0x23be90`, Node::setOrientation `0x1f9410`
и updateFromParentImpl `0x1f9ad0` сопоставлены с pinned source.

`resource-derived` / `original-code`: три поддержанных класса имеют один
IDLE prefix match в исходных alchemist/warrior/player/vanquisher manifests.
CCharacter IDLE branch `0x84a6c3/0x84b13c` выбирает этот state; отдельный menu
RNG не придуман. Другой manifest с несколькими IDLE отклоняется, пока не
подключён его original random chain. Используется existing skeleton-link bind
loader и gameplay sampler, loop/speed1; initial blend0.2 и прочие animation
states остаются вне подтверждённого steady IDLE среза.

`integration`: native CEGUI class/save callback -> Frontend read-only selection
-> Application model replacement -> existing append_player_geometry / wardrobe
layers / equipped weapon -> resource placement -> GlesSceneRenderer instance
pose и hand-tag transform -> DesktopWindow scene draw -> native UI overlay.
Back/Settings не выбирают другого actor: текущая модель продолжает idle.
Renderer уничтожается **до** владельца source geometry; ресурсная загрузка и
renderer replacement выполняются только при изменении selection key.
Menu clock и OTC revision — portable adapters. Игровые stats/RNG не обновляются
ради preview. ScenarioHost теперь также вызывает реальный menu scene renderer,
а не только UI fallback; menu capture сохраняет его штатные diagnostics.

## Verification and residue

CPU/library/resource: authored placement/Group-vs-Layout-Link, missing markers,
Town default TYPE и координаты; все3 модели, wardrobe layers, настоящий bind,
движение vertices в IDLE, loop, hand tag, отсутствие оружия у unarmed prototype.
Native creation contract проверяет default/class/Back actor selection consumer.

Common Application/GL scenario `tests/scenarios/menu-player.scenario` прошёл
**34 проверки**: 10 background instances -> ровно body+weapon без накопления,
все3 класса и соответствующие textured equipment, координаты camera/player,
idle hand movement в renderer, Back retention, source default Destroyer при
reopen, отсутствие fallback notices и OTC writes. Артефакты ignored:
`build-cegui/ui-repair-evidence/menu-player-qptd8xjx/`.
Это port regression; original process/OS delivery/frame equivalence не проверены.

Финальный соседний gate: **8/8** (menu scene/core/resources, native
Main/Settings/Create/Load и пятистрочный menu state); registry sync passed,
225 bounded addresses. Повторный общий OTC/GL Load regression после исправления
Group: **4 процесса, 25 проверок**, артефакты
`build-cegui/ui-repair-evidence/native-load-r2pr9fc4/`. Vendored stock math
checksums повторно проверены: **17/17**, source edits отсутствуют.

Остаток: SVB/pet/mod/dead/retired, equipped armor appearance (сейчас те же base
wardrobe layers, что в gameplay), saved themes и initial actor на Main до выбора,
полный native state lifecycle и initial
animation blending/events/global RNG, shader/light/particles/skybox и полные
original ownership/pending flags/unwind. Все большие функции остаются partial.

Продолжение 2026-10-01: [Save & Menu refresh](menu-player-return.md) подключает
committed OTC slot/revision к тому же restored-player model consumer, что Load.
Оружие после возврата обновляется; новые UI/frame checks в этом проходе не выполнялись.
