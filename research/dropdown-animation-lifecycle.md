# CDropdownMenu: модель, анимация и UI projection

## Проверенные входы и граница

`original-code`: read-only ELF `/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64`,
SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`,
проверенный `tools.original.Original`. ASM ниже прочитан objdump; декомпиляция
`research/decompiled-core/generic_model.c`, `game.c`, `game_ui.c` использована
для навигации. Запуск игры, кадры и UI-сценарии не выполнялись.

`library-derived`: оригинальная `lib64/libOgreMain-1.6.5.so`, SHA-256
`bef109bfdc1210ede92731ead4a2b3fae76a8905f10bac14d5fdb54ae5474c31`.
Существующий sampler сверялся с этой библиотекой в границе
[animation-runtime.md](animation-runtime.md); OGRE v1-6-0 source не равен
бинарной версии 1.6.5, поэтому virtual targets ниже установлены непосредственно
по ELF relocation, а не по порядку методов нового заголовка.

Записка устанавливает исходный контракт и минимальную связку. Она сама по себе
не является свидетельством полной реализации CGenericModel/updateAnimation
или всего семейства dropdown.

## Создание и реальные consumers

`original-code`: CDropdownMenu::createMenus @0xb196f0, ветвь
@0xb1af60..0xb1b016 вызывает ResourceManager::createGenericModel @0xd77e40:
SceneManager из +0x48, UTF-32 имя @0xfe60f0
`media/ui/models/dropdown/dropdown.mesh`, второе имя @0x1001608 пустое,
три bool=false. Model записан в +0x70, mesh bounds выставлены ±100000.
Созданная модель получает position=0 и visibility=false.

CMainMenu flags=1 остаётся без этой модели. COptionsMenu constructor
@0xb885c6 и CSettingsMenu @0xbd8666 передают flags=0.
COptionsMenu::createMenus @0xb8828e..0xb88295 и CSettingsMenu::createMenus
@0xbd7079..0xbd7080 присоединяют layout под content (+0x20), не root.

В порте `FrontendPage::pause` читает `media/UI/optionsmenu.layout`,
`FrontendPage::settings` — `media/UI/settingsmenu.layout` (`src/frontend.cpp`).
Options — реальный consumer model-enabled animation ветви. Settings имеет
собственные setOpen/update overrides без анимации (уточнение ниже); flags=0
само по себе не доказывает анимированный consumer. Inventory сейчас имеет
отдельный диагностический overlay (`GlesUiRenderer::draw_overlay`), поэтому
само наличие inventory модели/ресурса не означает подключённую dropdown-цепочку.

## Ресурсы модели

`resource-derived`: внешний `pak.zip`, каталог `media/UI/models/dropdown/`.
Mesh `dropdown.MESH` (534 bytes), SHA-256
`b68dac4a0033315e7151bf1b2b74fe643033e01d3a90bf5d1f748fd5870c974d`.
Serializer v1.40: shared geometry, 6 vertices, 12 uint16 indices, triangle list;
position/normal float3 в buffer0 stride24, UV float2 buffer1 stride8.
Вершины0..3 имеют bone0 weight1, вершины4..5 bone2 weight1.
Это четыре треугольника, не один прямоугольник. Bind skeleton —
`dropdown.skeleton`; tag — `tag_dropdowntop`.

`dropdown.animation` SHA-256
`68a32c080f6e082f51ac27149e612515b76b15f2d26e3ea32cdac1ba5ac635a4`
перечисляет ровно idle.skeleton, open.skeleton, close.skeleton, без KEY events.

| Файл | Имя клипа | Длина float32, секунд | SHA-256 |
|---|---|---:|---|
| dropdown.SKELETON | bind | 0 | 5862e90cd4a50052e153f24c82bfad8518e29e135c73e7de25fc8cff070d0fca |
| idle.SKELETON | idle | 0.03333330154418945 | 3db5acf4aa2598c318ec2eae1a67147d3d4c31438d320b6e775427d4f11f18a4 |
| open.SKELETON | open | 0.9666669964790344 | fcf6be49c714b55a556b070c8c158d6fc1d366af06386b385dde65ee22c93667 |
| close.SKELETON | close | 0.33333298563957214 | dbf6342778fa067d6c44fb0a6907bb8b773699d7ba059799e88a50f059f5b9fd |

`dropdown.material` SHA-256
`d14c035b117d35c481327202428464bbb82ac77c2127029d92b820fa3b337128`:
material Dropdown_, lighting off, depth_write/check off, scene_blend alpha_blend,
alpha_rejection greater 5, texture dropdown.png, filtering linear linear none.
В архиве фактическая текстура `dropdown.dds`, SHA-256
`b486b209fd4cb0cd8c8ca95a7f2316248d0d37a3488ebbbea0ff409264b659d7`.
Переиспользовать существующее разрешение material texture PNG→DDS.

## Открытие, закрытие, очередь

`original-code`: setOpen @0xb18e50..0xb192d2:

- equal state: только записывает open (+0x30).
- close: очищает четыре GameClient safe pointers, sound66 @0xb18f8e,
  blend CLOSE(false, .1, 2, -1) @0xb18fc6, closed=false; root пока attached.
- open: sound22 @0xb19034, visible=true @0xb19045,
  animationPlaying(CLOSE) @0xb19061; если true, blend OPEN(false,.1,2,-1)
  @0xb190bc; иначе play OPEN(false,2,-1) @0xb19168.
  Затем queueBlendAnimation(IDLE,true,.1,1) @0xb190fc,
  parent.addChild(root) @0xb19120, root.moveToBack @0xb19129.
- open записывается последним @0xb18e7a. Открытие не переписывает closed.

Обычная длина OPEN/speed ≈.4833335s, CLOSE/speed ≈.1666665s — это не
полное описание смены состояний. `CGenericModel::queueBlendAnimation(uint)`
@0x8a1320 проверяет индекс и таблицу, включает loop flag, получает clip length;
@0x8a13e9 ограничивает requested blend min(requested,length).
Для IDLE фактическая длительность blend равна .0333333015, а не .1.
Активный объект 64 bytes: index+0x10, length+0x18, position+0x20,
loop+0x24, active+0x25, queued+0x26, remaining blend+0x2c,
initial blend+0x30, weight+0x34, speed+0x38.

`updateAnimation` @0x8aa4b0 использует очередь и веса, а не последовательный
таймер «OPEN закончился, затем IDLE». Для queued слоя исходный predecessor
должен быть активен. Ветвь @0x8abfa5..0x8abfc5 сравнивает
`(predecessor.length-predecessor.position)/predecessor.speed - dt`
с queued.initial_blend и активирует queued слой при <=.
Полный перевод общего алгоритма требует также обработки interrupted blend,
удаления предыдущих слоёв и animationPlaying/animationQueued; двух
произвольных UI easing-кривых здесь недостаточно.

## Update и позиция content

`original-code`: CDropdownMenu::update @0xb176b0..0xb179db читает width/height,
выходит при !open && closed; иначе с model:
updateAnimation(dt,false) @0xb17731 → Entity::_updateAnimation @0xb1773e →
Skeleton lookup tag_dropdowntop @0xb17774 → model.getPosition(false)
@0xb17799 → bone derived position @0xb177c8 → content.setPosition @0xb1785e.

`scaledY` @0xa83e70..0xa83e93 умножает на KSETTINGS_YRATIO.
Исходный CGame устанавливает YRATIO=height/768 (float @0xfa4804=768).
Порядок формулы:

```
x = float(width)*0.5f + (model.x + tag.x)*(height/768.f)
y = -((model.y + tag.y)*(height/768.f) + float(height)*(-0.5f))
```

При !open && !closed последовательно проверяются playing(CLOSE)
@0xb178a5, затем queued(CLOSE) @0xb17947. Только когда оба false:
visibility=false @0xb178cc → parent.removeChild(root) @0xb178d7 → closed=true.

## UI camera и GLES projection

`original-code`: CGame::createCamera @0x5613f0, UICam участок
@0x561582..0x561643: setProjectionType(0), position(0,0,10), lookAt(0,0,0),
near=.1, far=90, autoAspectRatio=true. Тип0 — orthographic.
`library-derived`: Ogre::Camera vtable @0x60b200; address-point +0x10,
slot+0x368 relocation @0x60b578 → Frustum::setProjectionType @0x1650e0;
slot+0x2b0 relocation @0x60b4c0 → setFrustumExtents @0x165380.
Это подтверждает имена виртуальных вызовов без догадки декомпилятора.

CCameraControl::setAspectRatio @0xce9ef0..0xce9fcc обновляет aspect/window;
для UI enum1 @0xce9f68..0xce9fca задаёт frustum extents:
left=-width*(768/height)*.5, right=+width*(768/height)*.5,
top=+384, bottom=-384. Поэтому project model-space vertex при нулевой
позиции модели: x=width/2+vx*height/768, y=height/2-vy*height/768.
Это та же ортографическая проекция, что используется для tag/content;
world scene camera не нужна.

CGame::createViewports @0x561cd6 создаёт UI viewport zorder5, full normalized
area. @0x561d10..0x561d1a clearEveryFrame(true,2): только depth.
CGameUI initialization @0xa9ead7 передаёт OgreCEGUIRenderer queue100,
post_queue=false, capacity3000, UI SceneManager. Порядок mesh перед CEGUI
нужно сохранять в consumer; запись конструктора сама по себе не заменяет
полную проверку library queue callback для всех сцен.

## Минимальное производственное подключение

1. Загрузить исходные mesh/bind/три manifest clips существующими
   `parse_ogre_mesh`, `load_model_animations_by_prefix`.
2. Владеть слоями, queued state и временем в живом model-enabled dropdown;
   продвигать их frame dt независимо от видимости текущей portable страницы,
   пока root attached и CLOSE не закончен.
3. Переиспользовать `sample_ogre_mesh_animation[_blend]`:
   `OgreMeshPose::bones` уже содержит derived/global позиции, а geometries —
   skin positions. Брать tag из той же позы, которую потребляет renderer.
4. Присоединить layout options под постоянный content и менять его
   offset; settings использует собственный статический offset=0; painter и pointer hit-test должны видеть одно смещённое дерево.
5. Перед рисованием CEGUI tree отрисовать четыре исходных textured triangles
   UI projection с alpha/material rules. `GlesSceneRenderer::set_mesh_pose`
   уже принимает такую позу, но его world camera не подходит; разумнее
   расширить существующий UI renderer mesh-пакетом с тем же sampler.
6. Скрыть модель и отсоединить root только после playing/queued CLOSE=false.

Открытые зависимости для полного общего класса: полная карта активной очереди
CGenericModel (особенно повторный OPEN во время CLOSE), ownership и разрушение
resource model/SoundBank, safe-pointer recipients, все производные dropdown
и их собственные virtual overrides. Данная записка не объявляет их закрытыми.

## Уточнение: interrupted blend и общая очередь трёх dropdown clips

Этот срез разобран дополнительно по ASM всех арифметических/условных участков
`updateAnimation`, `playAnimation`, `blendAnimation`, `clearQueuedAnimations`
и оригинальной OGRE. Ниже область: существующие три ненулевых клипа, обычный
конечный dt>=0, model visible, без pause-animation flag, без KEY событий и
без force-update flag. Служебный dt=1000 обходит visibility guard; это отдельный
общий путь CGenericModel, не timestep frontend.

**Исправление обозначения +0x34:** это inverse blend weight, а не вес слоя.

| Поле CActiveAnimation | Тип | Начальное play / blend / queue | Смысл |
|---|---|---|---|
| +0x10 | uint32 | clip index | shared OGRE AnimationState index |
| +0x18 | float32 | clip length | effective playback length, -1 override означает исходную |
| +0x1c | float32 | clip length | исходная длина |
| +0x20 | float32 | 0 | время данного queue entry |
| +0x24 | byte bool | loop argument | повторение |
| +0x25 | byte bool | true / true / false | active |
| +0x26 | byte bool | false / false / true | queued |
| +0x27 | byte bool | false | crossed loop end, сбрасывается перед advance |
| +0x28 | byte bool | false | removal/completed marker |
| +0x29 | byte bool | false | blend/clip completed, сохраняется между update |
| +0x2a | byte bool | false | older processed-entry marker, сохраняется |
| +0x2c | float32 | 0 / min(blend,length) / min(blend,length) | remaining blend |
| +0x30 | float32 | то же | initial blend |
| +0x34 | float32 | 0 / 1 / 1 | inverse weight |
| +0x38 | float32 | speed | playback multiplier |

Для queue с нулевым/неположительным blend применяется fallback float
@0xfd1a30=0.0001; обычный IDLE имеет положительный blend и сюда не попадает.

### Mutations перед update

- `play(uint) @0x8a5a40`: clearAnimations отключает shared states имеющихся
  записей и удаляет все entries; устанавливает loop в shared state; создаёт
  entry(active=true, inverse=0), enable shared state, push_front.
  Немедленного reset shared time/weight здесь нет.
- `blend(uint) @0x8a6d70`: zero clip length или zero blend вызывает play.
  Иначе setLoop; min(blend,length); clearQueuedAnimations; создать entry;
  enable shared state; push_front. Если среди старых entries есть тот же
  clip index (@0x8a7007..0x8a700e), сохранить старый shared weight.
  Если такого clip нет, shared.setWeight(0) @0x8a709e.
- `clearQueuedAnimations @0x8a68e0`: удаляет только queued=true, со стабильным
  сдвигом оставшихся элементов; active entries и их shared states сохраняются.
- `queue(uint) @0x8a1320`: push_front queued entry, а не append к хвосту;
  shared loop устанавливается сразу, shared enable не выполняется до activation.

Поэтому последовательность OPEN/update/CLOSE/update/OPEN может иметь deque
`[IDLE queued, OPEN new, CLOSE old, OPEN older]`. Entries с одинаковым clip
не объединяются: shared Ogre state получает их записи последовательно.

### Update: порядок для обычных входов

Псевдокод обозначает observed branch order; names являются локальными
смысловыми именами полей таблицы, не восстановленными C++ именами оригинала.

```
cumulative = 0
weight_latch = false
remove_older = false
deferred = []
for i from 0 to entries.size-1:             # newest first
    a = entries[i]
    if a.queued && dt != 0:
        if i+1 < size && entries[i+1].queued:
            pass                           # process inactive entry below
        else:
            if i+1 < size && entries[i+1].active:
                p = entries[i+1]
                remaining = 0 if p.wrapped else p.length-p.time
                if remaining/p.speed-dt > a.initial_blend:
                    continue               # no time/weight/culling for this i
            a.active=true; a.queued=false; a.inverse=0
            shared[a.clip].setEnabled(true)
            shared[a.clip].setTimePosition(a.time)
    if i != 0 && dt != 0:
        a.older_processed=true
    old_time=a.time; was_active=a.active
    a.wrapped=false
    if a.active:
        if a.remaining_blend > 0:
            a.remaining_blend -= dt
            a.inverse=1
            if a.initial_blend != 0 && a.remaining_blend > 0:
                a.inverse=min(a.remaining_blend/a.initial_blend,1)
            if a.remaining_blend <= 0:
                a.completed_blend=true
                a.inverse=0; a.remaining_blend=0
        a.time += dt*a.speed
        if a.time > a.length:              # strict >, not >=
            a.time -= a.length
            if a.loop:
                while a.time > a.length: a.time-=a.length
                a.wrapped=true
            else:
                a.time=a.length
                a.remove=true; a.completed_blend=true; a.active=false
    raw=1-a.inverse
    if raw != 0 && (a.active || was_active || old_time != a.time):
        shared[a.clip].setTimePosition(a.time)
    delta=raw-cumulative
    cumulative+=delta                       # not a multiplicative blend
    if delta != 0:
        if !weight_latch && old_time != a.time:
            deferred.push(a.clip,delta)
        elif a.active && old_time != a.time:
            shared[a.clip].setWeight(delta)
    if delta == 1 && a.older_processed:
        weight_latch=true
    # dropdown manifest has no KEY events; original event block is empty here
    if remove_older && dt != 0: a.remove=true
    if a.completed_blend && dt != 0: remove_older=true
factor = 2 if cumulative>=1 || cumulative==0 else 1-cumulative
for (clip,delta) in deferred:
    shared[clip].setWeight(delta*factor)
if dt != 0:
    i=1                                   # front entry is retained!
    while i<size:
        if !entries[i].remove: i++; continue
        if no entries[0..i-1] has same clip:
            shared[entries[i].clip].setEnabled(false)
        delete entries[i]
        entries[i]=entries.back(); pop_back() # swap removal, NOT stable erase
        # repeat same i
```

Ключевые ASM блоки: activation @0x8aa738..0x8aa7f1;
threshold @0x8abfa5..0x8abfc5; older marker @0x8ab41e;
blend arithmetic @0x8ab208..0x8ab27d; time @0x8aafe7..0x8ab051;
non-loop completion @0x8ab484; shared time and raw/delta @0x8aa924..0x8aa968;
weight deferral @0x8aa96e..0x8aaa20; direct weight @0x8aaeb4..0x8aaeed;
post-loop factor @0x8aac98..0x8aacd5 and @0x8ac010..0x8ac049;
remove marker propagation @0x8aaba0..0x8aac44;
removal starts index1 @0x8ab542 and checks duplicate prefix before disabling;
swap-last/pop @0x8aba8d and following blocks.

`force=true` adds force to old_time!=time checks and permits some terminal
single-entry refreshes. Clip length=0 has separate termination/loop branch.
Neither is silently replaced with ordinary logic in a claim of full generic
function transfer. dt0 does not activate queued entries or perform removal.

### Shared OGRE state: критично для rapid reopen

`animationQueued(uint) @0x8a53f0`: any queued&&index matches.
`animationPlaying(uint) @0x8a76c0`: any !queued&&active&&index matches.
Завершённый retained front не считается playing, хотя shared state остаётся
enabled до последующего play/clear либо уничтожения модели.

`library-derived`: `AnimationState::setWeight @0x112670` записывает float
без clamp. `setEnabled @0x1127f0` всегда вызывает notification; notification
@0x112770 сначала удаляет state из enabled-list, затем при true append к концу.
Повторное включение уже enabled clip изменяет порядок применения слоёв.

`Skeleton` constructor @0x2f7cd5 пишет blendMode0 (average).
`Skeleton::setAnimationState @0x2f38b0` суммирует веса enabled unique states;
@0x2f3ac0..0x2f3ae6 применяет factor=1/sum при sum>1, иначе1.
Следовательно observed factor2 в CGenericModel нельзя исправлять как опечатку;
его потребляет библиотечная нормализация. Shared duplicate writes выполняются
в порядке вызовов, последнее присваивание weight/time побеждает, веса entries
с одинаковым index не суммируются.

Runtime должен хранить отдельно entries и shared per-clip state, включая
порядок enabled states. `sample_ogre_mesh_animation_blend` принимает только два
слоя, а interrupted chain допускает три unique clips. Нужно расширение
существующего sampler для массива слоёв, с нормализацией enabled states
перед sampling; отдельная выдуманная UI интерполяция не нужна. Existing
`apply_animation_layer` clamps [0,1]; если reachable interrupted вход даёт
отрицательный delta, этот clamp нельзя выдавать за original library behavior.

## Проверка производных: Settings не запускает dropdown animation

`original-code`: полный `COptionsMenu::setOpen @0xb86f50` повторяет base
animation/safe-pointer/sound ветви. Отличие: addChild @0xb87220 →
**moveToFront** @0xb87229, тогда как base делает moveToBack.
`createMenus @0xb8829a..0xb882b1`: root.setAlwaysOnTop(true),
root.MousePassThroughEnabled=false. Fullscreen root/back/content размеры
унаследованы; layout под content, additional setSize/position в create нет.
`update @0xb80140`: сохранить closed → base update → если closed изменился
и +0xc0=true, очистить +0xc0 и requestSetGameState(0,0) @0xb8019d.
Это дополнительный реальный delayed consumer окончания закрытия.

`CSettingsMenu::setOpen @0xbd5560` имеет собственное поведение:
changed-state сначала вызывает setInteractiveMenuVisible(newOpen) @0xbd5585.
Close: removeChild(root) @0xbd55bd, **closed=false** @0xbd55c2.
Open: **closed=false** @0xbd55d0; читает resolution; content.position=0
@0xbd562a; addChild(root) @0xbd5637; moveToBack @0xbd5640; заполняет
checkbox/slider/combobox значениями settings. open записывается в финале
@0xbd5598. Полный symbol просмотрен: model+0x70 не читается, sound/animation
не вызываются. Конструктор действительно создал model, но она остаётся hidden.
Полный `CSettingsMenu::update @0xbd47e0` (0xd76 bytes) также не вызывает
base/model animation; обновляет настройки из widget state. Значит запуск
OPEN/CLOSE по одному только flags=0 для settings был бы ошибкой перевода.

Три AlwaysOnTop в settings create @0xbd7fd1, @0xbd8040, @0xbd80a1 относятся
к getDropList() combobox +0xf8/+0x100/+0x108, **не root**.

## Native modal producer: отсутствует в проверенной цепочке

`CModalMenu::setOpen @0xb77770` — movzx bool и tailcall base setOpen.
`createMenus @0xb7f580` присоединяет layout под content @0xb7fbaf,
затем root.setAlwaysOnTop(true) @0xb7fbbd. `setContents @0xb7e520`
обновляет text/visibility/callbacks. В просмотренных create/setOpen/setContents
нет setModalState. В динамических imports исходного ELF нет CEGUI setModalState.
Ресурсы settingsmenu.layout/optionsmenu.layout/modalmenu.layout не содержат
Modal property. Это свидетельство **отсутствия native modal producer в данном
срезе**, а не доказательство отсутствия всех modal механизмов игры.

AlwaysOnTop/root hit interception нельзя переименовывать в System modal.
Перенос библиотечной поддержки modal сам по себе не разрешает принудительно
делать settings/options/modalmenu активным modal window. App-level ограничение
ввода через GameUI и именование CModalMenu — отдельные механизмы.

## Dropdown sounds 22/66: ресурсная привязка

`original-code`: constructor @0xb1b7fa создаёт CSoundBank(manager,false).
@0xb1b810 строка UTF-32 @0xfee408="CENTEROPEN" →
getSoundDataObject @0xb1b823 → если объект существует, GUID64 из +0x20 →
addSample(22,guid) @0xb1b853. Аналогично @0xfee438="CENTERCLOSE",
lookup @0xb1b875 → addSample(66,guid) @0xb1b8a2.
22/66 — локальные sample IDs, не GUID.

`resource-derived`: `media/sounds/UI.DAT.adm`, SHA-256
`568873fd9e04ae0fe91a061cd34543336200ad1a813b2e8ed970a179ae51790c`.
Прочитан существующим `parse_adm`, без добавления отдельного формата.

| Local ID | NAME | GUID64 | FILE |
|---|---|---:|---|
| 22 | CenterOpen | 2190439802373280222 | media/sounds/ui/sheet_opencenter.wav |
| 66 | CenterClose | 2190439810963214814 | media/sounds/ui/sheet_closecenter.wav |

Обе записи CATEGORY=UI, LOOPS=0, VOLUME=.2, VOLUMEVARIATION=.2,
FREQUENCYVARIATION=0, RADIUS=10; один FILE.

Фактический архивный case: `media/sounds/UI/sheet_opencenter.wav`,
SHA-256 `3847c10681e787e7c6a4f7a2829760de565100d0309f6536feda80e4fa9dba39`;
mono PCM16 44100Hz, 30622 samples. Close
`media/sounds/UI/sheet_closecenter.wav`, SHA-256
`d139a9a5ff18738d795bf5dbcf4b7b4b7706d92f380d6270ab35c669e00b931d`;
mono PCM16 44100Hz, 27986 samples.

Вызов `playSample(id,nullptr,0.f,0.f,false)` происходит при реальном переходе
open-state и наличии model: close до blend CLOSE, open до visibility=true.
Options адреса @0xb8708e/@0xb87134; base @0xb18f8e/@0xb19034.
Равное состояние не создаёт sample request. Settings override этого не делает.

**Consumer gap:** `MusicPlayer` — один disk OGG stream (vorbisfile→ALSA),
request переключает/останавливает музыку, WAV decoding и mix one-shot voices
нет. Нельзя передать WAV в MusicPlayer::request и считать эффект подключённым.
Допустимое переиспользование — существующий audio output/mixing backend,
дополнив PCM one-shot voices из PakArchive. Формула volume variation и
ограничения одновременных voices требуют CSoundBank::playSample/CSoundManager
разбора; значения ADM не означают разрешение выдумать random gain.

## Уточнение audio: точная channel gain и overlap

`original-code`: createSoundData @0xa640f0 читает VOLUME (строка @0xfb63b0)
в float+0x28 @0xa642c7, FREQUENCYVARIATION (@0xfe1390) в +0x30
@0xa64301, VOLUMEVARIATION (@0xfe13e0) в +0x34 @0xa6433b,
PLAYCHANCE (@0xfe1420) в int+0x3c с default=-1 @0xa64446..0xa64456.

addSample(guid) @0xa69642..0xa69661 передаёт volume, volumevariation,
frequencyvariation, radius в float registers0..3.
addSample(path) @0xa69202..0xa6920d вызывает createSound с первым float
volumevariation; createSound @0xa6d623 записывает его в CSoundInstance+0x4c.
Bank volume[id] хранится в массиве +0x78 @0xa693ce..0xa693df.

Для dropdown playSample(id,nullptr,0,0,false):

1. Backend enable flags +0x6a9/+0x6a8 должны быть true; ID допустим.
2. PLAYCHANCE=-1 обходит вероятность @0xa6993e.
3. Нулевой первый float выбирает bank volume=.2 @0xa6999e.
4. Null SceneNode выбирает spatial scale=1 @0xa69b44.
5. File choice вызывает randomIntegerBetweenVolatile(0,0) @0xa69a4c;
   equal bounds возвращает0 без изменения RNG @0xc92bf0..0xc92c2a.
6. manager.playSound(instance,nullptr,-1,.2) создаёт paused channel
   @0xa6caef; получает index; затем @0xa6cd15..0xa6cd56:

```
variation = randomBetweenVolatile(0.f, instance.volumeVariation)
channelGain = min(1.f, variation + bankVolume)
channel.setVolume(channelGain)
channel.setPaused(false)
```

Для исходных ресурсов gain лежит в [.2,.4), а не в симметричном диапазоне
и не является `.2 * random(...)`. Верхнее ограничение1 подтверждено
`minss` @0xa6cd4f; нижнего clamp в этом участке нет. RNG использует исходный
volatile stream @0xc92b50; готовый `VolatileRandom::between` в
`randomizer.hpp/.cpp` транскрибирует его. Исправление52-bit mask и прямое
ASM comparison зафиксированы в [volatile-random-fraction.md](volatile-random-fraction.md):
прежняя44-bit маска сжимала variation. Выбор явно отдельного локального
seed — адаптер порта, не доказательство совпадения глобальной RNG sequence.

FREQUENCYVARIATION=0 в обоих ресурсах; playSound не вызывает setFrequency.
One-shot playback использует исходную WAV sample rate. Master SOUNDVOLUME и
mute применяет отдельный `CSoundManager::updateAudioLevels @0xa6b750`
через FMOD master SoundGroup/ChannelGroup; это уровень mixer/backend, а не
часть channel gain variation.

`addSample(guid)` создаёт SoundGroup по GUID @0xa696ad,
setMaxAudible(6) @0xa696cf и setMaxAudibleBehavior(1) @0xa696dd.
Точное FMOD virtual/mute поведение группы — отдельная library граница;
не подменять удалением старого голоса без подтверждения. Для bank LOOPS=false
+c8=false, playSample не вызывает stop() перед новым голосом; он лишь очищает
массивы tracked channel IDs @0xa69ae3..0xa69b37, затем запускает новый голос.
Поэтому предыдущие open/close one-shots могут продолжать звучать одновременно.

## Options: producer отложенного выхода

`original-code`: COptionsMenu::onClick @0xb800a0..0xb800f3:
!open → returntrue без эффектов. При open:

| enum | Ресурс optionsmenu.layout | Последовательность |
|---|---|---|
| 0 | ExitGame / guiExitGame | +0xc0=true @0xb800b8; pending-close+0x32=true @0xb800bf |
| 6 | ReturnToGame / guiCloseMenu | pending-close=true @0xb800d0 |
| 94 | Settings / guiSettingsMenu | toggleSettings @0xb800e4; pending-close=true @0xb800e9 |
| прочие | — | returntrue |

`resource-derived`: исходные три onClick прочитаны из UTF-16
media/UI/optionsmenu.layout. Имена→enum соответствуют исходной таблице
bindings (`src/ui_function_bindings.cpp`).

Pending close потребляет base processInput @0xb102a0 через virtual setOpen(false).
COptionsMenu::update @0xb80140 сохраняет closed до base.update;
если closed изменился и +0xc0 установлен, очищает +0xc0
@0xb80184 и вызывает requestSetGameState(0,0) @0xb8019d.
Таким образом выход из игры запускается **после** фактического завершения CLOSE,
а не одновременно с onClick. ReturnToGame и переход к Settings не устанавливают
+c0, поэтому не создают этот отложенный request. Fullscreen root/pointer
interception при этом остаются до подтверждённого detach.

### Root layout position Settings/Options

`resource-derived`: settingsmenu.layout — UTF-8; Frame задаёт
UnifiedAreaRect={{0,0},{0,0},{1,0},{1,0}} и UnifiedMaxSize={{1,0},{1,0}}.
optionsmenu.layout — UTF-16; Frame задаёт UnifiedPosition={{0,0},{0,0}}
и UnifiedSize={{1,0},{1,0}}. Оба root уже zero/fullscreen из ресурса.
`original-code`: settings create @0xbd705d вызывает
convertToScreenScale(layout,false); @0xa83ed0 этот механизм child-first
масштабирует абсолютные offsets через scaledY, сохраняя relative scales.
Отдельного принудительного zero-position для settings layout root нет;
setOpen сбрасывает только service content. Маскировать ресурсные значения
zero_position_nodes для Frame не требуется.
