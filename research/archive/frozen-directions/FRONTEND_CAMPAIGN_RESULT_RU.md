# OpenTorchlight large-5: меню, дисковая кампания и взаимодействия

> **Архив замороженного направления.** Указания, команды, очереди и числа ниже
> относятся к прежнему снимку; они не задают текущую работу или приёмку.
> Действующий процесс: [decomp](../../../decomp/README.md).

## Результат и граница проверки

Изменения сделаны поверх `OpenTorchlight-gpt-pro-large-5.zip`, SHA-256:
`186501e1de1e628ed69ead4f07bacb032289198d753f9faf65e0b4e512017a81`.
Исходники изменены локально; в GitHub ничего не отправлено. Предыдущие combat,
AI cooldown, предметы, recovery, материалы и logic не заменялись старыми версиями.

Реализован переносимый цикл **New/Load → выбранный герой → Town → изменение
состояния → save → новый процесс/load → переход и возврат с сохранением этажей**.
Оконный код подключён к этому циклу, добавлены GUI renderer, меню и сообщения.
Отдельно реально отрисованы четыре кадра UI через Mesa/EGL. **Полное Wayland-окно
с настоящим Town и оригинальными ресурсами здесь не собрано и не запущено.**
Это значительный законченный core-срез и подключение desktop, но не заявление,
что весь максимальный scope large-5 или вся Torchlight завершены.

Новая сборка GCC 14.2.0: **28/28 переносимых тестов**. Отдельная ASan/UBSan сборка:
**28/28**. Трёхпроцессный gameplay-тест использует собственные проверочные ресурсы,
а не извлечённый Town; адресные/ресурсные сравнения исторической интеграции
**59/59 не повторялись**. Для настоящего pak подготовлен отдельный тест ниже.

## 1. Откуда взяты решения

**resource-derived.** В предоставленном `research/ui-actions.json` есть
`mainmenuframe.layout`, `charactercreate.layout`, `characterload.layout`,
унифицированные координаты и фактические `onClick`. В load-menu встречаются
повторные свойства: поздний ScrollUp/ScrollDown заменяет ранний
`guiExitApplication`. Загрузчик применяет последнее значение, а не случайно
превращает прокрутку в выход. Это исходный аудит пакета, не новое извлечение
из отсутствующего здесь pak.

**original-code.** `CCharacterSaveState::save`, `CItemSaveState::save` и
`CLevelState::save` сохраняют разные группы данных; последний вызывает
сохранение вещей и logic nodes. `CGameClient::saveCharacter @0x0058b5d0`
собирает персонажа и состояние уровней; `performWarp @0x0058d110` удерживает
живого игрока между уровнями. Источники:
`research/decompiled-core/character_save_state.c:1319–1476`,
`item_save_state.c:1298–1372`, `level_state.c:1500–1559`,
`game_client.c:10043–10429`. В оригинальном saveCharacter есть также quest и
DungeonTracker: они не объявлены перенесёнными только из-за чтения этой функции.

**prototype / inferred.** Собственная state machine frontend, схема `.otc`,
безопасные границы snapshot, режим паузы, bitmap labels и дополнительные кнопки
сохранения — явные решения порта. Они не названы исходными enum, GUI skin или
форматом `.SVB`. Имя GameStateController само по себе не доказывает boot enum:
в его исходном классе также есть внутриигровые пороговые события.

## 2. Меню и создание персонажа

Добавлены `UiResources`, bounded XML loader, `Frontend` и `GlesUiRenderer`.
Обычный запуск с каталогом установленной игры открывает main menu, а не
безусловный тестовый этаж. New Game выбирает загруженный GUID класса, имя,
новый seed и Town. Не используется жёсткое `players.front()` для каждого героя.
Continue выбирает подходящий сохранённый слот, Load показывает список с ошибками
повреждённых/несовместимых файлов. Прокрутка, мышь, клавиатурный focus, Enter и
Escape связаны с теми же прямоугольниками, что рисуются.

Поддержанная часть UI-ресурсов: XML UTF-8/UTF-16LE, свойства и callback whitelist,
UnifiedPosition/Size/AreaRect, alignment, inherited visible/enabled, imageset
с PNG/DDS-атласом. Одинаковые рассчитанные bounds используются для draw и hit-test;
при смене страницы старые кнопки сбрасываются. В loader ограничены размер,
глубина и количество узлов; внешние entities/DTD не исполняются. Это ограниченный
CEGUI XML reader, не полная реализация XML/CEGUI.

Исходные geometry/images используются, когда соответствующие свойства и формат
поддержаны. Неподдержанный skin не выдаётся за восстановленный: на экране указаны
**prototype controls/font**. Фон fallback, дополнительная геометрия кнопок,
собственные bitmap labels и reference-canvas маленького окна тоже prototype.
Файлы шрифтов не копируются и не поставляются. Нет оснований считать результат
пиксельно идентичным оригинальному меню.

New Game предлагает только **Normal**, соответствующий текущей поддержке графов
мира. Другие сложности, полноценный hardcore workflow и выбор питомца не
показываются как работающие режимы. Ввод имени — до 32 физических US A–Z/цифр,
пробела и дефиса, Backspace; полноценные UTF-8 IME/кириллическая раскладка пока
не подключены. Codec сохраняет строковые байты, но это не заменяет text input.

В gameplay Escape открывает pause. Save остаётся в паузе; Save & Menu / Save &
Quit переходят дальше только после успешной записи. Ошибка остаётся видимой
на текущем экране. UI-кадр не продвигает симуляцию дополнительными update(0).
Инвентарь, HP/mana/gold и прежний recovery R продолжают работать в общем цикле.
На экране смерти Escape теперь ведёт в pause, а не сразу закрывает окно.

`--frames N` и `--main-stratum N --seed N` сохранены как direct-preview для
интеграционных проверок. Они обходят меню; автоматическая запись при закрытии
preview не выполняется. Обычная новая игра использует отдельную энтропию seed,
а не всегда 42. Номер слота тоже не потребляет игровой RNG.

## 3. Сохранение: что действительно переживает процесс

`CampaignCheckpoint` связывает слот/ревизию, ресурсную идентичность, class GUID,
имя, seed, текущий и последний данж, состояние игрока и до 128 снимков этажей.
`CheckpointAccess` — узкая точка доступа к закрытому состоянию контроллеров.

**Персонаж:** HP и максимум, известная/неизвестная мана и максимум, gold,
поддержанные base stats, отдельные экземпляры InventoryItem с вычисленными
WeaponItem/ArmorItem/effects, ID и next ID, слоты, combat RNG и выбор руки.
Два предмета одного GUID не сливаются. После загрузки экипировки рассчитанный
максимум маны сверяется со снимком; уже вычисленные предметы не перебрасываются.

**Этаж:** адрес и layout identity, позиция/направление игрока, отдельный recovery
anchor и floor offset, размещённые и динамические сущности с ID, источниками,
HP/alive/enabled/visible, спавнерными и loot-ссылками; поддержанные logic node
state, counter/timer/RNG; enemy alertness, signed AI cooldown/рука/RNG.
Смерть, подобранный предмет и оставленная добыча не заменяются новой генерацией.
Логический труп сохраняется, точная финальная поза его skeleton — нет.

**Не сериализуются указатели, mesh/GPU buffers, пути, callbacks, interaction
requests, текущие атаки и HIT.** На load временные исполнения отменяются.
Это не воспроизведение оригинального mid-animation save; независимый AI cooldown
и RNG при этом сохраняются. Попытка capture с необработанной смертью/loot,
очередью логики/спавна/warp отклоняется, а не молча теряет события.

Загрузка сначала декодирует и проверяет кандидат. Затем по внешним ресурсам
регенерируется исходная сцена, сверяются placed IDs/GUID, layout property/link
identity и ссылки world/logic, восстанавливаются значения. Восстановленный этаж
не получает повторный `activate_level()`. Возврат на ранее посещённый этаж
восстанавливает его сущности, но выбирает актуальную точку прибытия перехода;
загрузка текущего сохранения использует именно сохранённую допустимую позицию.
Recovery anchor хранится отдельно. Проверка позиции не телепортирует повреждённый
save в произвольный PlayerStart.

Полные quest/timeline/skills/pet/dynamic-effect states и оригинальная политика
volatile-floor reset отсутствуют в runtime и не объявлены сохранёнными.
Offscreen clocks заморожены вместе с кешем — явное prototype-правило. Это
сохранение существующих поддержанных подсистем, не совместимость всей кампании.

## 4. Формат, повреждения и атомарная запись

Отдельный `.otc` версии 1: 20-byte header (magic/version/length/CRC32), explicit
little-endian payload, строгие bool/enums, конечные числа и ограниченные
контейнеры. Максимум payload 32 MiB; совместный encoder/decoder budget — 64 MiB
учтённых DTO-выделений и 500 000 элементов, плюс ограничения каждого поля.
Это не гарантия максимального RSS всего процесса. Детальная спецификация —
`research/checkpoint-format.md`; exact field order задаёт `src/save_codec.cpp`.

До изменения live state проверяются версия/длина/CRC, duplicate IDs,
слоты/экземпляры/next ID, enum, NaN/Inf, ссылки спавнеров/loot/logic,
совместимость ресурсного набора и regenerated layout. Проверки включают и
мутированные payload с заново рассчитанным правильным CRC. **CRC/FNV — не
криптографическая подпись или защита от злонамеренного владельца файловой системы.**

POSIX: advisory lock → проверка ожидаемой ревизии → новый temp mode 0600 →
полная write/fsync → atomic rename → fsync каталога. Старая ревизия не может
затереть более новую запись второго процесса. Имя героя не используется в пути.
Оригинальные save-файлы не открываются на запись; `.SVB` import/export отсутствует.

При исключении до rename старый слот сохраняется. Проверено и настоящее
завершение процесса между fsync и rename: старые байты остаются читаемыми;
может остаться игнорируемый `.checkpoint-*` temp. Если rename уже прошёл, но
fsync каталога не удался, ошибка честно сообщает о необходимости заново
прочитать ревизию; нельзя обещать старый файл после состоявшегося rename.
Сделан и конкурентный тест: два процесса читают одну ревизию, стартуют вместе;
один commit, один явный revision conflict.

Default directory: `$XDG_DATA_HOME/opentorchlight/saves`, иначе
`$HOME/.local/share/opentorchlight/saves`. Альтернатива — `--save-dir PATH`.
Обработка более 128 слотов пока явная ошибка, не бесконечная загрузка списка.
Backup/delete UX и миграции ещё нет. Не-POSIX запись отклоняется, Android
storage/lifecycle не проверены. При принудительном закрытии окна остаётся
best-effort checkpoint; ошибка выводится в stderr, поскольку окно уже закрыто.

## 5. Общий interaction dispatcher

Добавлен отдельный dispatcher selection → approach → re-check → dispatch.
Request привязан к поколению мира, номеру выбора, виду и конкретной цели.
Поздняя доставка после нового выбора/смерти/перехода не исполняется. Нельзя
переназначить живой token на другой объект. На arrival повторно проверяются
live/enabled/visible/range, затем token расходуется до синхронного события.

Unit Trigger использует существующий LogicRuntime; сам Warper не становится
произвольно кликабельным. Так порт не добавляет новый обход Trigger-графа.
Noncombat NPC доступен для выбора и подхода, но выдаёт сообщение о пока
неподдержанном сервисе. **Merchant/stash/quest не выданы за работающие**: кошелёк
и инвентарь от такой инспекции не меняются. Исходные faction/quest gates полностью
не восстановлены.

`original-code`: `CCharacter::inInteractionRange @0x008244a0` учитывает радиусы
и разные пороги; `CTriggerUnit::interact @0x009095c0` — требования и текущего
игрока. `CInteract::interactWithUnit @0x00986ff0` найден в symbols, полного body
здесь нет. Caller radius 2.25 остаётся **prototype**, не выдуманной исходной
константой. Минимальные следующие ASM/operands перечислены в `NEXT_CHECKS.md`.

## 6. Карта остатка и её ограничения

Добавлены `research/coverage-boundaries.json` (ручные доказанные границы),
генерируемые `coverage.tsv`/`coverage-summary.json`, `tools/coverage_map.py` и
тест актуальности. Карта содержит **17 023 уникальных function addresses**
T/t/W/w и **3 port-native строки**, всего **17 026**. Включены library/thunk
символы; число не равно количеству игровых фич. Alias одного адреса не размножает
его как несколько готовых функций.

64 оригинальных адреса аннотированы вручную. Статусы всего: unseen 16 959,
researched 13, partial 29, implemented 1, verified 24, closed 0. **Unseen по
умолчанию означает отсутствие reviewed boundary, а не доказательство, что никто
не видел декомпиляцию.** 24 verified удерживают конкретные прежние differential
границы с явной пометкой, что исходный ELF здесь не запускался заново. Новые
save/menu не превращены в original verified за счёт собственных tests.

Frontier использует число уникальных resolved direct рёбер, расстояние до
игровых root-функций и заданный вес подсистем. Это воспроизводимая подсказка,
не процент готовности. Неразрешённые virtual calls в этой метрике отсутствуют.
Вверху остаются saveCharacter/loadCharacter, original UI update/create/input,
storeLevelSavedState. Инструмент не закрывает функции по имени/размеру/наличию
Ghidra-файла. Команды:

```bash
python3 tools/coverage_map.py --check
python3 tools/coverage_map.py --next 20
python3 tools/coverage_map.py --next 20 --include-researched
```

## 7. Исполняемые проверки

| Проверка | Свежий результат |
|---|---|
| Исходный portable до изменения | 21/21 |
| Portable после изменения | 28/28 |
| Отдельная GCC ASan/UBSan сборка | 28/28 |
| Frontend XML/команды/ошибки | 32 утверждения |
| Три процесса полного авторского цикла | 222 + 222 + 4 утверждения |
| Save checkpoint self | 598 утверждений |
| Дополнительный отдельный write/read | 588 + 16 утверждений |
| Crash/racing-writer | старый файл цел; ровно один commit и один conflict |
| Реальный GLES UI | 4 pixel-readback кадра |
| Чистая распаковка исходного архива → cumulative patch → новая сборка | 28/28 |
| Полный Wayland-desktop / original pak/ELF | не выполнено |

Числа утверждений включают повторные проверки во время ходьбы и проверки общих
помощников. Их нельзя складывать в количество уникальных восстановленных
механик. Логи лежат в `verification/large-5/`.

**Gameplay cycle** реально использует core mesh/unit parser, NavigationGrid,
ActorMotion, interaction, LogicRuntime, PlayerSession, World, recovery и
SaveStore. В writer выбирается не первый prototype, меняются предметы, HP/mana/
gold и логика, сохраняется позиция. Reader в новом процессе проверяет данные,
проходит через trigger в Main-shaped сцену, создаёт смерть/добычу, выполняет R-
recovery, возвращается в сохранённый Town-shaped мир и пишет второй checkpoint.
Третий процесс проверяет оба этажа, труп, вещь на земле и ревизию. Это авторская
небольшая сцена, не оригинальный Town и не управление настоящим окном.

**Отдельно обнаруженная граница навигации:** существующая grid может пропустить
тонкую вертикальную стену точно между центрами клеток при cell_size=1 и radius=.45.
Сквозная positive-сцена использует стену x=10.5, попадающую в проверяемые клетки;
вариант x=10 открыт в NEXT_CHECKS. Растеризатор здесь не изменён. Поэтому
успешная ходьба в тесте не выдана за корректность всех реальных препятствий.

**GLES test** создаёт настоящий surfaceless EGL context, вызывает renderer,
читает glReadPixels и проверяет атлас/ориентацию/resize/create/pause. Фактический
renderer: llvmpipe (LLVM 19.1.7), OpenGL ES 3.2 Mesa 25.0.7-2. Минимальные public
API declarations в tests/support — не подставные GL-функции: исполняется реальный
драйвер. Нет Wayland, original images или original font comparison.

ASan/UBSan: у нативных probes включён leak detector. У единственного Python/Mesa
host `gles_ui_headless` LSan отключён из-за процесс-глобальных выделений хозяина;
address/UB checking включены. На выполненных проверках диагностик нет. Нельзя
сказать «вся игра без утечек» или «LSan проверил Python/Mesa целиком».

Полный desktop target не появился в CMake из-за отсутствующих development
metadata/headers Wayland/EGL/GLES; попытка его сборки дала unknown target.
Игровая часть оконного файла прошла отдельную syntax-check компиляцию с
предупреждениями как ошибками, но с исключённым классом окна. Это не линковка
и не запуск всего desktop. `capabilities.log` сохраняет точную границу.

Новый `original_frontend_checkpoint` компилируется всегда, регистрируется при
`TORCHLIGHT_ORIGINAL` и готов к внешнему pak: все игроки, три UI layouts, Town,
save/load в другом процессе. На настоящем pak здесь не выполнен. Исходных ELF,
pak и GCC16 нет; исторические 59/59 интегратора не приписаны этому патчу.

## 8. Применение и проверка

Авторитетный полный ZIP содержит уже применённые изменения. Второй источник
той же версии — **один cumulative patch** к чистому исходному `large-5`:

```bash
git apply --check OpenTorchlight-frontend-campaign.patch
git apply OpenTorchlight-frontend-campaign.patch
bash tools/check.sh --portable
```

Не накладывать patch повторно на готовый ZIP. В проекте обновлён
`CHECKSUMS.sha256` (не включает собственный файл):

```bash
sha256sum -c CHECKSUMS.sha256
```

На машине с установленными ресурсами и полноценным desktop SDK:

```bash
bash tools/check.sh "/path/to/Torchlight/game"
./build/torchlight_desktop "/path/to/Torchlight/game" --save-dir "$HOME/ot-large5-test"
```

Обычный запуск не требует `--main-stratum`. Для регрессионного preview по-прежнему:

```bash
./build/torchlight_desktop "/path/to/Torchlight/game" --main-stratum 1 --seed 42 --frames 3
```

Отдельная sanitizer-сборка, использованная здесь:

```bash
cmake -S . -B build-sanitized -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON -DTORCHLIGHT_ORIGINAL= \
  -DCMAKE_CXX_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer -fno-pie' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined -no-pie' \
  -DTORCHLIGHT_PYTHON_ASAN_PRELOAD="$(c++ -print-file-name=libasan.so)"
cmake --build build-sanitized --parallel 4
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
ctest --test-dir build-sanitized --output-on-failure
```

## 9. Оставшийся объём

Ближайшее подтверждение — полный реальный New/Load/Town/window цикл и расширенный
UI resource subset, затем тонкие nav-стены и исходные interaction requirements /
NPC services. Для новых runtime-границ остаются CItemGold pickup/rank/difficulty,
точный layout no-loot, projectile/ray/missile, полный effect/skill lifecycle,
XP/quests/pet/economy, оригинальные persistent/volatile floors, sound/FX и Android.
Доступные gold/pitch/muzzle строки не подменяют неустановленные producers.
`NEXT_CHECKS.md` содержит точные следующие функции/операнды; широкое повторное
декомпилирование всего бинарника для этого не требуется.

## 10. Проверка доставки

Cumulative patch применён к чистой распаковке именно входного large-5, а не к
рабочей директории с прежними исправлениями. Полученные исходники сравнивались
побайтово; затем независимая новая portable-сборка прошла 28/28. После включения
отчётов/логов финальный patch повторно применяется к новой чистой распаковке и
сверяется с полным ZIP; исполняемые исходники совпадают с проверенной сборкой.
`verification/large-5/clean-build.log` содержит свежую сборку, а не старый лог
интегратора. Архив исходников не включает build, .git, бинарники, ELF, pak.zip
или файлы шрифтов. Полный ZIP уже содержит patch; применять его второй раз
не нужно.
