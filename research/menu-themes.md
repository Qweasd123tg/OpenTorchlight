# Menu theme из committed OTC dungeon

Продолжение: [menu-caves.md](menu-caves.md) снимает исходную Caves rejection
по инварианту одного generated room; ниже сохранена граница предыдущего прохода.

2026-10-02. Продолжение [menu-player-return.md](menu-player-return.md).
Входы SHA-256 ELF/pak, пути и хеши manifest/rules/layout:
[menu-theme-inputs.json](menu-theme-inputs.json). Неизменённые pinned OGRE1.6.5
math sources и library comparison прежние: [menu-player-inputs.json](menu-player-inputs.json).
Оригинальные входы только читались. Full completion остаётся partial.

## Original comparison и карта полей

[disassembly/menu-themes.asm](disassembly/menu-themes.asm) хранит instruction-aligned
окна, выбранные из полного disassembly соответствующих функций; большие функции
не объявляются разобранными целиком. Decompiler использовался для навигации.

`original-code`: `CCharacter::fillSaveState @0x826930..0x826942` копирует
level int32 `+0x1a4` в save int32 `+0x64`. `loadCharacter @0x581ef7..0x581f0a`
восстанавливает seed int32 `save+0x60 -> client+0x1090` и depth int32
`save+0x64 -> client+0x1094`. Stored dungeon wstring присваивается client
`+0x1098` на `0x5821fa..0x58220e`. Порядок unload/reload при menu state0 и
caller `loadMenuLevel @0x5907f3` сохранены в предыдущем
[ASM](disassembly/menu-player-return.asm). Load row `selectCharacter ->
applyCharacterState @0xc3fb9c` меняет actor в существующем уровне, а не
вызывает loadMenuLevel; исходная ветвь сравнивается в
[menu-player-preview.md](menu-player-preview.md).

`loadMenuLevel @0x584b82` сохраняет **edx**, второй int argument, в r14d.
Его же передаёт resetGameSeed `0x584c53..0x584c59` и getLevelTemplateDataForDepth
`0x584c65..0x584c6b`. Поэтому ошибочное представление декомпилятора о параметрах
не используется как контракт. Template pointer64 возвращается в rax; при
nonnull `0x584c91` читает wstring `template+0x6f0`, заполненную MAINMENURULES
в `CLevelTemplateData::load @0x977272`. `0x584cbd` вызывает loadRoomLayout
с false и entryType=3. Null-template fallback `0x585355..0x585376` выбирает
Town rules; это отдельная ветвь, не разрешение подменять неподдерживаемую тему.

`CDungeon::loadDungeon @0x934c44..0x934c84` читает FLOORS (int32, default1,
неположительное ->1). В цикле до FLOORS (`0x935294..0x9352a1`) добавляет
group pointer64 в array `+0x100` (`0x934d14..0x934d24`) и slot в template
array `+0x10`, увеличивая count32 `+0x18` (`0x934d65..0x934d77`).
`getStrataTemplate @0x933818..0x933881` адресует slot `index*8`;
отложенная загрузка читает RULESET на `0x9338dc`.
`getLevelTemplateDataForDepth @0x9340a6..0x9340b0/0x934120` использует
unsigned index: при index>=count выбирает count-1. Ненулевая строка template
`+0x60` ведёт через getDungeonByName и getRandomLevelTemplateData
`0x9340ee/0x93410d`; этот random-dungeon delegate остаётся вне переноса.

## OTC adapter и resource family

OTC хранит Town depth0 и обычные depths1..N; это **не native save ABI**.
`build_saved_menu_scene` использует тот же `select_dungeon_floor`, что gameplay,
и получает MAINMENURULES именно его страты. Так фон соответствует реально
сохранённому portable этажу. Выход за число страт, random dungeon pool,
отсутствующие RULESET/MAINMENURULES и неизвестные inputs не закрываются
оригинальным clamp/fallback. No-save wrapper продолжает выбирать Town:
исходный Town depth1 при count1 соответствует slot0.

`resource-derived`: MAIN.DAT имеет35 одноэтажных страт. Сопоставление **OTC**:

| Depth | Menu rules / root layout |
| --- | --- |
| 1–4 | mainmenu_minerules.dat / MAINMENU_MINES.LAYOUT |
| 5–8 | mainmenu_cryptrules.dat / MAINMENU_CRYPT.LAYOUT |
| 9–16 | mainmenu_sunkentemplerules.dat / MAINMENU_SUNKENTEMPLE.LAYOUT |
| 17–20 | mainmenu_cavesrules.dat / MAINMENU_CAVES.LAYOUT — unsupported RANDOMIZED |
| 21–24 | mainmenu_lavarules.dat / MAINMENU_LAVA.LAYOUT |
| 25–29 | mainmenu_fortressrules.dat / MAINMENU_FORTRESS.LAYOUT |
| 30–35 | mainmenu_palacerules.dat / MAINMENU_PALACE.LAYOUT |
| Town0 | mainmenu_townrules.dat / MAINMENU_TOWN.LAYOUT |

Семейство reuse existing ADM, fixed chunk, layout-link expansion, levelsets,
OGRE mesh, static geometry, source camera/player marker и IDLE consumers.
Каждая поддержанная тема имеет один fixed chunk, offset0 и единственный layout;
Caves имеет RANDOMIZED=true и отклоняется. Palace Properties Group pivot
(-4.79,0,5.64999) не добавляется к marker vectors; это подтверждённый editor
GUID edge, прежний graphic owner контракт не меняется.

`original-code`: CRandomGroup ctor `0x9f2752` устанавливает enum32 `+0x11c=0`;
SetRandomType `0x9f1a60..0x9f1a65` принимает только0..2. Исходные имена enum
ALL/Weight/Random Chance инициализированы в `decompiled-core/layout.c`.
`rollGroup @0x74b330/0x74b361` собирает children по editor GUID;
`0x74b42b` вызывает chooseChildrenByRandomChoice. Он читает count child Groups
`0x9f9c1a`, проверяет creation predicates `0x9f9c38`, enum `0x9f9c41`, для
ALL переходит `0x9f9c4c -> 0x9f9d70`, иначе вызывает CRandomizer `0x9f9c68`.
Прямые non-Group children не являются альтернативами его Group array.

`unsupported boundary`: room-piece descendants выбранного child-Group edge
Weight/Random Chance исключаются из render view; их piece_guid очищается только
в owned копии layout. Это **не восстановленный результат RNG**. Старые данные
layout остаются целыми, object indices и настоящие Layout Link parents
сохраняются. Omitted count потребляет Application notice; Mine имеет такие
варианты. ALL/отсутствующий CHOICE не подавляется. Маркер под случайно выбранной
Group и неизвестный/нестроковый CHOICE отклоняются. Quest/class/difficulty
predicates и dynamic group events не закрываются: у проверенных базовых
room/camera/player Groups этих ограничений нет.

## Production integration

Уже подключённая цепочка save_and_menu после успешного SaveStore::write ставит
owned slot/class/committed revision/health. Следующий draw_frontend читает этот
checkpoint, проверяет class/revision, затем **только для queued return** вызывает
build_saved_menu_scene(checkpoint.current). Ordinary Load selection использует
тот же actor restore, сохраняя текущий menu level. Initial Main продолжает
Town: политика выбора стартового сохранения остаётся открытой.

Consumers: selected rules -> expanded layout -> static room geometry; camera
vectors -> GLES set_camera_pose; player spawn/toward -> model placement;
restored equipment -> mesh/hand; IDLE -> instance pose -> draw_menu_scene,
затем native UI overlay. При замене renderer освобождается **раньше** geometry;
новый actor renderer получает новую camera, а не предыдущую. Main/Settings/Back
сохраняют уровень и actor. Save request failure не ставит refresh. Unsupported
committed theme/read/actor failure очищает старую scene/model/renderer и
выдаёт diagnostic; UI остаётся доступен с прежним fallback UI background.
Старый Town/другой dungeon не выдаётся за выбранную неподдерживаемую тему.
Запрос потребляется один раз, новые disk writes и RNG calls не добавлены.

## Проверка и остаток

Desktop, Application shared probe и CPU menu test собраны. Узкий gate **5/5**:
menu scene/core, original menu resources, save checkpoint, original players
и original equipment. Registry sync прошёл: **234 bounded /161 cited** addresses;
новые source-only записи не повышают legacy transfer stages. Contracts проверяют
первый и последний OTC depth всех шести Main fixed themes (12 cases), actual
geometry, source camera/player coordinates, model/weapon hand consumer,
Town0/no-save, Palace Group offset, Caves17/20 rejection. Authored Group contract
различает прямой marker и marker внутри child-Group alternative. Resource run:
Mines505 instances/6 omitted conditional pieces; Crypt422/0, Sunken78/0,
Lava211/0, Fortress180/0, Palace210/12. Это размеры доступной статической
геометрии, не результат исходного RNG выбора. Соседние
save checkpoint, original players/equipment проходят вместе с menu gates.

UI-клики, покадровые/сквозные сценарии и оригинальный процесс в этом проходе
**не запускались**. Статическое сравнение цепочки и CPU/resource проверки
не являются frame parity. Открыты Caves/random pools, RNG-зависимый декор,
initial saved selection, pet/dead/retired appearance, armor, skybox/particles/
water/lights/projectors, оригинальный save/state/resource ownership и unwind,
full OGRE renderer и производительность. Whole original functions partial.
