# CDropdownMenu: контейнер, оконный lifecycle и Options animation

## Источники и способ проверки

Проверено 2026-09-21, оригинальные входы только для чтения:

- `Torchlight.bin.x86_64`, SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- `lib64/libCEGUIBase.so.1`, SHA-256 `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.
- База пути: `/home/qweasd123tg/Games/Torchlight/game`.

`library-derived`: поставленная модифицированная CEGUI семейства 0.6.2.
Зафиксированный upstream reference — `cegui/cegui`, tag `v0-6-2`, см.
[UPSTREAM_NOTICES](ui-skin-reference/UPSTREAM_NOTICES.md). Сам tag не доказывает
совпадение ABI или поведения. Ни один приведённый ниже runtime-порядок не
обоснован только upstream: проверены инструкции именно shipped ELF.

Предписанный [headless workflow](decompiler-workflow.md) прочитан. Сохранённый
`/tmp/opentorchlight-ghidra` в этой среде отсутствует; ограниченный поиск в
Code, cache, local/share и Downloads другой базы не обнаружил. Новая полная
база не создавалась. Навигация здесь — существующие адресные исследования,
динамические символы `nm -D -C` и прямой `objdump -d -C`. Это ограничение
воспроизводимости headless, а не утверждение о новом Ghidra-экспорте.

## Создание и общая карта состояния

`original-code`: `CMainMenu` передаёт flags=1 (`0xc53b18`), поэтому
`CDropdownMenu::createMenus @0xb196f0` пропускает модель. Общая карта и ветви
модели остаются в [dropdown-mainmenu](dropdown-mainmenu.md).

| Поле CDropdownMenu | Ширина | Назначение |
|---|---:|---|
| +0x10 | 8 | внешний parent; читается setOpen |
| +0x18 | 8 | root; создаётся createMenus, читается setOpen и Main create |
| +0x20 | 8 | content; создаётся createMenus, позиция обнуляется при open |
| +0x30 | 1 | open, начально false, записывается последним в setOpen |
| +0x31 | 1 | closed, начально true, close без модели пишет true |
| +0x70 | 8 | model, null в рассматриваемой ветви |

`original-code`, точные callsites создания:

1. Root: manager.createWindow `0xb19cac`, запись +0x18 `0xb19cb1`;
   setSize(1,0;1,0) `0xb19d3d`; RiseOnClick=False через setProperty
   `0xb19eec`; setPosition(0,0) `0xb19f39`; MousePassThrough=false
   `0xb19f44`; setZOrderingEnabled(false) `0xb19f4f`.
2. Back: createWindow `0xb1a43a`; root.addChild `0xb1a4a4`; setSize
   `0xb1a4e0`; RiseOnClick=False; setPosition `0xb1a6df`; moveToBack
   `0xb1a6e7`; **после** него setZOrderingEnabled(false) `0xb1a6f1`.
3. Content: createWindow `0xb1aaba`, запись +0x20 `0xb1aac7`;
   root.addChild `0xb1ab26`; setSize `0xb1ab63`; RiseOnClick=False
   `0xb1ace9`; setPosition `0xb1ad36`; MousePassThrough=true
   `0xb1ad3f`; moveToFront `0xb1ad4a`; затем ZOrderingEnabled=false
   `0xb1ad55`.
4. `CMainMenu::createMenus @0xc52a10`, addChild callsite `0xc52bf8`,
   присоединяет layout к root +0x18, не к content. Следующий setPosition(0,0)
   `0xc52c34` меняет unified position, сохраняя размер и alignment.

`library-derived`: `Window::setPosition @0x114410` передаёт новую позицию и
прежний размер в setArea_impl. CoordConverter `getBaseXValue` читает
alignment `0xc8d1b`: Right `0xc8d31..0xc8d3f` добавляет
parent.width−width; `getBaseYValue` читает alignment `0xc8b8c`, Bottom `0xc8ba2..0xc8bb0`
аналогично добавляет parent.height−height. Поэтому сброс применяется до
выравнивания: окно 200×100 с Right/Bottom в 640×480 занимает (440,380),
а не пиксельный (0,0). Текущий ресурсный Root полноэкранный, поэтому это
различие закрепляется отдельным чистым контрактным случаем.

Итоговый ordinary sibling-порядок root: back, content, layout. Служебные
окна не требуют выдуманной картинки; их эффекты — геометрия, parent,
visibility/disabled inheritance и target traversal.

`library-derived`: DefaultWindow реализован GUISheet. Его constructor
`0x14c670..0x14c6e4` вызывает Window constructor, затем setMaxSize(1,0;1,0)
`0x14c6bb` и setSize с тем же аргументом `0x14c6c6`. Он не меняет
MousePassThrough. Window constructor `0x11ae50` задаёт parent=null
`0x11b291`, enabled=true `0x11b2d8`, visible=true `0x11b2df`,
DestroyedByParent=true `0x11b2f4`, AlwaysOnTop=false `0x11b2fb`,
ZOrderingEnabled=true `0x11b310`, RiseOnClick=true `0x11b325`,
MousePassThrough=false `0x11b45b`. Каждое перечисленное логическое поле — byte;
parent — 64-bit pointer. Поэтому back сохраняет MousePassThrough=false.

## Attachment и sibling draw-list

`library-derived`, `Window::addChildWindow(Window*) @0x111280..0x11130e`:
null или self — no-op; иначе virtual addChild_impl (slot +0x1f0),
onChildAdded (+0x118), затем child.onZChange_impl (+0x200).
`addChild_impl @0x1166f0..0x1167af` сначала вызывает removeChildWindow
прежнего parent, если он существует, **включая тот же parent**; добавляет
в draw-list с at_back=false `0x116718`, затем append в insertion child-list
(+0x78..+0x80), setParent `0x116756`, child.onParentSized (+0x110)
`0x116787`. Никакого удаления child-объекта при reparent нет.

`removeChildWindow @0x111310..0x11136d`: virtual removeChild_impl (+0x1f8),
onChildRemoved (+0x120), child.onZChange_impl (+0x200). В отличие от add,
нет null guard. `removeChild_impl @0x115bb0..0x115cc9` сначала удаляет из
draw-list, ищет child по указателю в insertion list, стирает первый найденный
элемент, затем setParent(null); если элемент не найден, parent не меняет.
`setParent @0x111750` — единственная 64-bit запись +0xb0.

`addWindowToDrawList @0x1163d0..0x11648a` поддерживает две sibling-группы:
ordinary перед AlwaysOnTop (+0x20d). at_back=true вставляет в начало своей
группы, false — в конец. Это не глобальная сортировка всего дерева.

**Существенная зависимость:** `moveToBack @0x116490..0x11654b` сначала
деактивирует active окно (virtual onDeactivated +0x108), затем, если есть
parent, проверяет ZOrderingEnabled (+0x210). Только при true переставляет
собственное окно через removeWindowFromDrawList и addWindowToDrawList(true)
`0x116513/0x116527`, вызывает onZChange_impl. Затем рекурсивно вызывает
parent.moveToBack **даже при false у самого окна**.

Следовательно, setOpen.addChild(root) помещает root в конец его ordinary
группы, а последующий root.moveToBack не переставляет root, поскольку его
ZOrderingEnabled уже false. Безусловное перемещение root в начало — неверный
перевод. Activation и движение parent теперь потребляет общий `UiWindowRuntime`;
точный порядок и capture последствия разобраны в
[ui-capture-modal-lifecycle](ui-capture-modal-lifecycle.md).

## setOpen и System fallback

`original-code`, `setOpen @0xb18e50..0xb192d1`:

- При равном open не выполняет attachment-операций; записывает open и выходит.
- Переход false→true читает width/height, model-null обнуляет content position
  `0xb191c9`; parent.addChild(root) `0xb19120`; root.moveToBack `0xb19129`;
  open записывается последним `0xb18e7a`. closed сохраняется.
- Переход true→false сначала очищает четыре GameClient safe pointers, затем
  parent.removeChild(root) `0xb19188`, closed=true `0xb1918d`, open=false.
  Удаление attachment не уничтожает окна и подписки. Safe-pointer ownership
  остаётся открытым; см. прежнюю карту адресов.

`library-derived`, полный `System::getTargetWindow @0x10ad90..0x10ae51`:

1. Нет GUI sheet (+0x68) или !sheet.isVisible(false) → null.
2. Есть capture → capture; если distributesCapturedInputs, пробует его
   getTargetChildAtPosition и сохраняет capture при null.
3. Без capture вызывает sheet.getTargetChildAtPosition `0x10ae3f`;
   null заменяет на sheet `0x10ae4c`. **Сам sheet здесь не проходит isHit,
   disabled, MousePassThrough или проверку собственного rect.**
4. При modal (+0x70), если target не modal и modal не ancestor target,
   заменяет target на modal (`0x10ade9..0x10adf2`).

Поддержка обычного sheet fallback допустима в явно указанной границе
capture=null, modal=null. Это не разрешает изображать поддержку capture/modal
фиктивными полями. Wrapper back может стать hit target без подписки; поиск
callback идёт по ancestors и не продолжает нижние siblings.

## Detach, destroy и фактический owner

`original-code`: полный `CDropdownMenu::~CDropdownMenu @0xb17140..0xb1723e`
уничтожает model +0x70 и SoundBank +0x80 при наличии, очищает массивы listeners
+0x90/+0xa8 и передаёт управление `CRunicCore::~CRunicCore @0xd79920`.
В теле **нет обращения к root/content и нет вызова CEGUI destroy/remove**.
Deleting destructor `0xb17240..0xb17251` дополнительно освобождает память
самого menu через Ogre allocator. Поэтому нельзя приписывать меню локальное
каскадное уничтожение CEGUI окон.

`library-derived`: manager.destroyWindow(Window*) `0x127160` игнорирует null,
копирует имя и обращается к overload String `0x125520..0x1257a2`. Не найденное
имя — no-op. Для найденного: стирает регистрацию из map, вызывает virtual
window.destroy (+0x30) `0x12562e`, добавляет указатель в dead-pool,
System.notifyWindowDestroyed `0x125688`, затем логирует. Фактическое удаление
памяти отложено до `cleanDeadPool @0x1253d0..0x125423`: обратный обход dead-pool,
getFactory(window.getType()), virtual factory.destroyWindow (+0x8).

`Window::destroy @0x114840..0x114956`: если ещё зарегистрирован — передаёт
manager; иначе releaseInput, очистка target tooltip если указывает на это окно,
setTooltip(null), detach/destroy window renderer, onDestructionStarted
(+0xf8), parent.removeChildWindow при наличии, virtual cleanupChildren
(+0x1e8). `cleanupChildren @0x114960..0x1149be` повторно берёт первый child
insertion list, detach, затем manager.destroyWindow(child) только при
DestroyedByParent=true (+0x20c). false оставляет живое отсоединённое окно.
Порядок определяется insertion list, не sibling draw order.

Ошибки/граница: add/remove и перечисленные virtual события могут выбросить
исключение; видимые landing pads передают его через _Unwind_Resume, без
транзакционного rollback дерева. Создание строк/векторов и manager registry
также допускает allocation failures. Scoped portable ownership может быть
более строгим/безопасным, но это должно быть обозначено как адаптер; CEGUI
exception hierarchy, callbacks, tooltip/capture/renderer teardown и dead-pool
нельзя объявить перенесёнными только по освобождению std::vector.

## Граница производственного переноса

`Frontend::windows_` — один `UiWindowRuntime` для sheet и всех присоединённых
и закрывающихся dropdown. `StaticDropdownState` хранит stable IDs root/back/content
и ресурсных окон в этом manager. Main layout присоединён к root, Settings/Options
— к content. Capture, modal, active, ButtonBase pushed/hover, previous capture,
insertion children и sibling draw-list принадлежат manager, а не копии кадра.
`bind_layout` заменяет прежние resource nodes через destroy/dead-pool; close
только отсоединяет subtree. Окна и capture переживают detach, hide и disable
согласно исходным функциям. Frontend destruction освобождает manager-owned tree;
это owner policy порта, не приписанный CDropdown destructor CEGUI вызов.

`UiWindowRuntime` исполняет проверенные attach/reparent, activation/deactivation,
Z-order guards, capture/release/restore, modal target restriction и stop-at-modal
bubbling, destruction notification и отложенное освобождение. Живые ID и имена
не переиспользуются как прежние удалённые окна. Его event listener в Frontend
инвалидирует cache; capture-lost retarget вызывает настоящий повторный target
query и обновляет button/Thumb состояние. Geometry, visibility и paint_order
берутся из единого snapshot; отделённый capture использует geometry своего
дерева, не включается для этого в видимый sheet.

`LinuxDesktopWindow` сохраняет порядок физических move/leave/down/up событий;
`Application` доставляет их в `Frontend::pointer_event`, обновляя snapshot между
событиями. ButtonBase выполняет down callback до capture/pushed. Mouse-up идёт
capture target; Checkbox меняет settings draft при подтверждённом up, RadioButton
снимает выбранность у siblings того же type/GroupID, PushButton не повторяет main down-команду.
Slider получает настоящий look-derived Thumb child: capture и drag меняют
volume draft, который читают skin и audio levels. Pushed/hover поступают в
Falagard painter. Legacy hosts без ordered events сохраняют явный click adapter.

Modal manager контракт реализован и проверяется чистыми запросами. В текущем
native Options/Settings packet не найден producer `setModalState`; frontend
его не выдумывает. Options `AlwaysOnTop` меняет sibling-группу и не означает
modal. Полноэкранное окно перехватывает ordinary hit своим деревом.

`original-code` + `resource-derived`, [анимационная цепочка](dropdown-animation-lifecycle.md):
CMainMenu flags=1 остаётся model-null; COptionsMenu использует исходные mesh,
bind skeleton, OPEN/CLOSE/IDLE и `tag_dropdowntop`. CSettingsMenu имеет собственные
setOpen/update overrides: его flags=0 не делают Settings анимированным меню.
`DropdownAnimation` хранит очередь/слои, скорость и веса; `Frontend::advance`
вызывается application clock один раз за итерацию. Tag position изменяет content,
четыре треугольника mesh идут в `GlesUiRenderer` перед CEGUI окнами с UI projection
h/768, исходными UV, alpha blend/rejection и depth policy. CLOSE оставляет дерево
прикреплённым до завершения; Options exit request выдаётся после закрытия.

Sound requests 22/66 потребляются `UiSoundPlayer`: исходные UI.DAT/GUID/WAV,
channel gain `min(1, volume + random(0, variation))`, перекрывающиеся one-shots,
актуальные master sound volume/mute. ALSA PCM mixer, локально seeded RNG и
oldest-voice eviction при max-audible=6 — явно portable backend adapters;
они не доказывают FMOD group behavior или исходную глобальную RNG sequence.

### Что ещё не закрыто по полным исходным функциям

- `CDropdownMenu::createMenus/setOpen/update`: четыре GameClient safe-pointer
  owners, полное внешнее CGameUI дерево и зависимости imageset/ResourceManager,
  исходные allocation/string/unwind paths. Подключённые Main/Options/Settings
  ветви не закрывают всё семейство dropdown.
- CEGUI за используемым frontend-срезом: exception ABI, произвольные
  reentrant SubscriberSlot callbacks/restore-chain raw lifetime, дополнительные
  selection subscribers, editable Combobox и остальные autochildren.
  Tooltip/window-renderer/factory teardown, три Settings popup, auto-repeat
  и double-click подключены и сравнены: [закрытие пакета](cegui-frontend-closure.md).
  Это не объявление переноса всех классов библиотеки.
- CGenericModel: произвольные animation families, events/KEY dependencies,
  ResourceManager/scene ownership и все ветви updateAnimation за пределами
  исходного трёхклипового dropdown. FMOD backend/group policy остаётся адаптером.
- Main controller: исходные .SVB/mod producers и state-controller ownership;
  .otc продолжает быть портовым save adapter.

`completion` исходных функций остаётся `partial`: legacy ported/wired/compared
описывают именно перечисленный производственный срез. Static/library comparison
с адресами допустим по правилам проекта; число unit tests не переводит функцию
в `full`. Карты полей и полные адресные условия приведены в связанных исследованиях.

### Проверки

Дополнение 2026-09-21: [замкнутые производственные цепочки и текущий gate](cegui-frontend-closure.md).
Следующие 13/13 относятся к предыдущему animation/capture проходу.

Ранее model-null gate: 5 core и 4 assets без пропусков,
`build-verification/dropdown-container-check.json`. Новые чистые контракты:
`tests/ui_window_runtime_test.cpp`, `tests/ui_dropdown_animation_test.cpp`,
`tests/ui_sound_test.cpp`; вместе с `tests/ui_dropdown_test.cpp` проверяют
переведённые переходы, numeric/resource inputs и порядок эффектов. Итоговые
результаты текущей интеграции: 7 core и 6 assets, 13/13 без пропусков.
Именованный gate — `build-verification/dropdown-lifecycle-check.json`; desktop
собирается отдельным `cmake --build build --target torchlight_desktop --parallel 2`.
Здесь не заявляется выполненный UI, кадровый, сквозной или звуковой playback
сценарий. Статический integration review дополнительно проверил поздний release
после CLOSE, blocking команд закрывающегося Options, owner-фильтр клавиатуры,
подписки декоративных Credits окон, namespace visibility и pending-request guard.

В предыдущем проходе один ошибочный запуск legacy CTest `frontend` остановился
до первого клика с `button absent: new`: авторская фикстура скрывала Root.
Две фикстуры исправлены и XML-проверены; повторный UI-прогон не выполнялся.
В текущем проходе UI-клики, кадры, измерения производительности и запуск
оригинальной игры не выполнялись.
