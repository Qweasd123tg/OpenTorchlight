# Main / Continue: выбранное сохранение и начальная menu scene

2026-10-02. Принятый ASM-разбор и производственная integration текущего среза.
Внешний read-only `Torchlight.bin.x86_64`:
`/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Decompiler используется для навигации; приведённые ширины, условия и адреса
установлены по ASM. Документ уточняет прежний открытый initial-Main остаток в
[menu-player-return.md](menu-player-return.md) и [menu-themes.md](menu-themes.md).
Большие исходные контроллеры, `setGameState` и сцена остаются **partial**.

## Полный predicate и цепочка query

`original-code`: `CContinueGameMenu::canContinue @0xc33490`, полное тело 67 bytes.
Сначала читает vector begin/end pointer64 `this+0x1e8/+0x1f0`, вычитает указатели
и выполняет signed shift на 3. Пустой vector возвращает false. Затем читает
selected index int32 `+0xc8` и сравнивает его с count по signed int32;
`selected >= count` возвращает false. Дополнительного `selected < 0` guard в
теле нет: отрицательные индексы не входят в поддержанный initialized domain.
Внутри диапазона индекс sign-extend используется для чтения pointer64 из
vector, затем saved HP binary32 `record+0xe0`. `ucomiss` с `+0.0f @0xfa47f8`
и `seta AL` дают **ordered HP > 0**: zero, negative и NaN не проходят.
Положительный subnormal и `+inf` проходят raw query; допустимость checkpoint
input является отдельным контрактом. Другие записи списка не ищутся.

| Полная owning function | Размер | Цель и поле |
|---|---:|---|
| `CContinueGameMenu::canContinue @0xc33490` | 67 bytes | выбранный record, HP `+0xe0` |
| `CMenuManager::canContinue @0xc2b9c0` | 12 bytes | pointer64 manager `+0xde8`, tail-call `0xc33490` |
| `CGameUI::canContinue @0xa84d30` | 12 bytes | pointer64 UI `+0x588`, tail-call `0xc2b9c0` |

Wrapper bodies не добавляют null guard. Их caller обязан предоставить
инициализированную pointer chain. Query не пишет state, не приобретает
ресурсы и не имеет cleanup/library-call зависимости внутри перечисленных тел.
System V x86_64: `this` в RDI, bool наблюдается через AL.

`original-code`: `CMainMenu::update @0xc53b70` вызывает query на `0xc53b8b`;
результат управляет visibility ContinueLast. Это не выбор «первого живого»
персонажа. В production `Frontend::continue_save()` вызывает
`selected_continue_save(saves_, save_index_)`; native CEGUI `state()` и
portable layout visibility получают тот же результат. Main Continue и Load
Selected формируют `FrontendRequest::load` с **тем же выбранным slot**.

## Писатели выбора и Main entry

`original-code`: `CContinueGameMenu` constructor `0xc42490` задаёт
selected index0 на `0xc424c7`. `reloadFiles(bool) @0xc3e420` сбрасывает
scroll на `0xc3e439`, но не пишет selected. Последующий forced select0
в reload/open producer устанавливает выбранную запись.
`sourceFileTimeSorter` сравнивает **signed64 modification times** по убыванию
на `0xc42917..0xc4291f`. Это provenance порядка native save records;
равные timestamps и вся исходная reload/sort/файловая цепочка этим срезом
не восстанавливаются.

`CMenuManager::setActiveMenu @0xc2b9d0` проверяет прежний enum на
`0xc2b9db..0xc2b9e1`: повтор того же manager menu выходит рано.
При настоящем переходе в Main ветвь `0xc2bb68..0xc2bb76` проверяет прежний
canContinue и только при true вызывает `selectCharacter(0, true)` без reload.
`selectCharacter @0xc3f8c0` прибавляет текущий scroll int32 `+0xc4` на
`0xc3f8d1`, записывает абсолютный selected int32 `+0xc8` на `0xc3f8f3`
**до** range guard `0xc3f900..0xc3f902`. Поэтому row0 здесь — первая текущая
видимая строка, а не безусловный абсолютный индекс0. Она может оказаться dead;
предыдущее canContinue не доказывает продолжимость нового выбора.

`integration`: `main_entry_save_selection` применяет это правило только к
переходу из Create/Load в Main. `Frontend::show_main()` вычисляет его до записи
новой page. Повтор Main, Settings overlay и gameplay-return producer сохраняют
свой выбор. Закрытие Settings не меняет исходный manager enum. Portable
На changed-index пути Main открывает saved preview consumer, сохраняющий тему.
Same-index forced select копирует только filename (`0xc3fb38..0xc3fb5c`),
поэтому уже созданный actor сохраняется. `main_preview_selection_changed_`
передаёт это различие в `preview_save()`; новый actor выбирается только при
фактической смене индекса, как `applyCharacterState @0xc3fb9c` в оригинале.
Portable
`size_t`/range guard оставляет недоступный scroll невыбранным, без подстановки
другого сохранения; исходная операция записи до guard сохраняется в роли.

`portable adapter`: `SaveStore::list` декодирует только принадлежащие порту OTC,
передаёт checkpoint health/current/class/revision и сортирует по filesystem
mtime descending, при равенстве — по slot ascending. Это не SVB ABI или
доказательство идентичного original sort при равных временах. Unreadable rows
остаются видимыми с `error`; дополнительный `loadable()` guard не приписывается
оригинальному HP predicate. `Frontend::set_saves` сохраняет переданную identity
slot после сортировки; отсутствующий slot даёт индекс за концом и null query.

## Один filename у Main actor и Continue load

`original-code`: native state2 Continue ветвь `CGameClient::setGameState
@0x58fa90` собирает путь из UI filename `+0x16c0` на `0x590276..0x5902b0`,
затем вызывает `loadCharacter @0x59037c`. Initial/menu state0 читает **то же**
UI filename на `0x59072e`, вызывает `loadCharacter @0x5907a7` и записывает
player pointer64 в client `+0x58`. Stored seed int32 `+0x1090`, depth int32
`+0x1094` и dungeon wstring `+0x1098` поступают в `loadMenuLevel @0x5907f3`.
После этого `addCharacter @0x59081f` использует level position `+0x140`,
`setToward @0x590833` — direction `+0x164`. Адресные окна state0:
[disassembly/menu-player-return.asm](disassembly/menu-player-return.asm);
seed/depth/dungeon mapping: [menu-themes.md](menu-themes.md).

Обычный gameplay return предварительно unloads player, вызывает
`reloadMenuCharacters @0x58fb8f`, а его manager chain выполняет
`reloadFiles(true)` и forced select0. Это reload-ветвь, отличная от настоящего
Main manager entry без reload. OTC producer намеренно передаёт **точный
успешно committed slot** после mtime resort: реальный save обычно оказывается
row0, но отсутствие identity не заменяется другим героем. Это собственный
адаптер идентичности, а не утверждение native SVB выбора при любом filesystem.

`integration`: обычный cold boot после `refresh_saves()` копирует текущий
loadable `selected_save()` в owned `menu_player_refresh`. Direct preview
(`main_stratum`/frame-limit) сохраняет отдельную прежнюю границу. Начальная
scene не создаёт transient Town перед обработкой saved selection. Cold boot
и успешный Save & Menu используют одну цепочку:

`SaveStore::read(slot, resource_identity)` -> class/revision check ->
`build_saved_menu_scene(checkpoint.current)` -> `CheckpointAccess::restore_player`
-> `menu_player_visual` -> `build_menu_player_preview` -> scene/model renderer
-> `draw_menu_scene` и UI overlay.

Saved theme строится до проверки живого visual. Load row selection меняет
actor в уже существующей menu scene; тему не перезагружает. Это соответствует
`selectCharacter -> applyCharacterState @0xc3fb9c`, а не state-transition
`loadMenuLevel`. Back/Settings сохраняют actor и IDLE clock. Gameplay-return
ставит refresh только после successful checkpoint commit; frontend list
refresh получает campaign slot и сохраняет его identity. Renderer уничтожается
раньше model/scene geometry, указатели на которую он использует.

## Ошибки и остаток

`portable adapter`: `draw_frontend` записывает selection key до I/O и кеширует
ошибки. Тот же failed slot/revision не перечитывается каждый кадр. Refresh
потребляется один раз. Новая selection может снова построить scene; Create
выбирает Town, если после ошибки saved theme scene отсутствует.

Если saved theme успешно построена, а restore/model/renderer actor не удался,
actor очищается и сохраняется корректный background этой темы. Если refresh
не построил selected theme, очищается прежняя scene: Town/другой dungeon не
выдаётся за выбранный. Background renderer при наличии scene пересоздаётся
отдельно; его ошибка оставляет UI fallback и diagnostic notice. Dead actor
appearance/recovery остаётся portable partial, living placeholder не создаётся.

Native SVB decoding, exact file-list/order lifetime, source sorting ties,
original selected-filename writer/string ABI, mod/retired/pet state, full
CEGUI SubscriberSlot/exception ownership, native model/scene/RNG/depth lifecycle,
input/state-transition timing и весь `setGameState` остаются открытыми.
Pinned CEGUI 0.6.2 и OGRE 1.6.5 math/resource reuse имеют прежние границы в
[cegui-source-integration.md](cegui-source-integration.md),
[menu-player-preview.md](menu-player-preview.md) и
[menu-themes.md](menu-themes.md). Ни full original controller, ни frame parity
не выводятся из этого подключения. Query и оба wrapper теперь компилируются
из принятого raw p-code через [automatic-function-transfer.md](automatic-function-transfer.md).
Проверенное отображение памяти связывает их чтения с тем же владельцем списка
и текущим индексом; исходная цепочка tail jumps сохранена.

## Проверки и статус свидетельств

`tests/compare_save_selection.py` исполняет три перечисленных неизменённых
whole bodies над явно заданными buffers/pointers и сравнивает с production
selector через `tests/save_selection_probe.cpp`. Сохранённые prior-worker
отчёты `/tmp/opentorchlight-save-selection-comparison.json` и
`/tmp/save-selection-integration-original.json` содержат PASS **2437 cases**,
body SHA-256 и zero literal. Это свидетельство уже выполненной проверки,
**не свежий запуск после финальных concurrent правок**. Нет constructors,
callbacks, original game process или negative selected-index fixtures;
nonfinite HP calibrates raw query, не OTC input acceptance.

`tests/save_selection_test.cpp` проверяет выбранную identity, dead/corrupt/NaN
guards, реальные Main-entry source pages/current scroll, same-page/Settings
retention, сортировку переданного slot и missing identity. В CMake записаны
`save_selection`, `original_save_selection_frontend` и
`original_save_selection_comparison`. Автор документа не выполнял tests,
builds, GUI-клики или кадровые сценарии. Актуальная итоговая приёмка и
fingerprints принадлежат main-agent после завершения integration.
