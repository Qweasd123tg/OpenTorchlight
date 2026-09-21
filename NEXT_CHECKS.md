# Действующий пакет и история переноса

Текущий пакет — CMainMenu + CDropdownMenu и их исходная библиотечная цепочка внутри
`research/ui-contour.json`. Процесс —
[research/code-first.md](research/code-first.md), схема и инструменты —
[research/codefirst-tooling.md](research/codefirst-tooling.md).
`python3 tools/work_frontier.py --scope ui` помогает найти остаток
функций и зависимостей этого пакета.

Подключённый production-срез описан в
[menu-production-state.md](research/menu-production-state.md): список персонажей,
удаление, ползунки/применение звука, физические Hover/Pushed, кеш Falagard и
отложенная загрузка игровых каталогов. [Town scene](research/menu-scene.md)
и [inline text](research/ui-inline-text.md) подключены к desktop.
Следующие исходные цепочки: preview персонажа/питомца, pet/difficulty producer,
темы из сохранения и scene FX, resolution/FSAA, native saves и общий CEGUI runtime.

1. Продолжи исходную цепочку CDropdownMenu, используемую CMainMenu:
   библиотечное значение Window+0x3e2, ownership трёх DefaultWindow,
   handle_onClick/handle_onDoubleClick и реальную доставку подписанных событий.
   Карта полей, ветви создания/обновления и исходные вызовы записаны в
   `research/dropdown-mainmenu.md`. Диспетчер CMainMenu, down-подписки и
   model-null флаги подключены. CMainMenu передаёт flags=1 и живёт без
   dropdown-модели; анимированная ветвь нужна другим членам семейства.
   Выбор Value/body из CEGUI `text`, `elementPropertyStart`, `elementPropertyEnd`
   подключён к UiLayout и проверен на значениях XML/ресурсе CreditsB.
   Фильтр свойств, CEGUI errors/lifetime и CDATA сохраняются в остатке.
   Используй `research/mainmenu-controller-painter.md` и готовые пакеты в их границе.
2. Разбери полный контракт участников по ASM, ресурсам и закреплённым
   библиотекам: базовые блоки, поля, ветви, цели и порядок вызовов,
   ошибки, cleanup и различия семейства.
3. Сопоставь эффекты с реальным runtime: сцена, камера, библиотечные
   состояния, кадр, ввод, resize и освобождение. Переноси связанный путь
   сразу с производственным потребителем каждого эффекта.
4. Установи подключение по коду callers/полей/consumers. Сверь перевод
   с исходным ASM и закреплёнными библиотеками с адресами. Оригинальный
   стенд или трассу выбирай по конкретному нерешённому вопросу.
5. Собери затронутый код и выполни узкие проверки известного контракта.
   UI-клики, скриншоты, покадровые и сквозные сценарии выполняются отдельной
   явно запрошенной пользователем задачей. Производительность измеряй отдельно.
6. Зафиксируй reviewed-срез и остаток. Полное completion требует ревью всего
   контракта, достаточного оригинального свидетельства и реального потребителя.
   integration хранит проверенную цепочку кода/данных, original_comparison —
   reviewed-сравнение с оригинальными источниками и адресами.
   `tests/registry_sync_test.py` проверяет структуру и актуальность реестра.

Пакет функции: `python3 tools/function_package.py --address 0x...`.
Семейство: `tools/prepare_family_packet.py`, начиная с `ENTRY.md`.
Места вызовов `research/original-callsites.tsv` экспортируются через
`tools/ghidra/export_call_sites.sh`; условия и виртуальные цели разбираются
по ASM. Стадии разобрана / перенесена / подключена / сравнена в
`research/function-transfer.json` описывают reviewed-срез; целое закрытие
учитывается отдельным `completion`.

## Исторические записи

Ниже сохранены результаты и планы прежних проходов в их исходной границе.
Заголовки «Текущая точка», прежние inventory/gameplay-приоритеты и числа
проверок относятся к соответствующему историческому снимку. Действующую
очередь задаёт пакет CMainMenu + CDropdownMenu выше.

---

# Текущая точка: масштаб меню + фон (U06/U02)

Жалоба «шрифт тянется, фона нет» разобрана. Растяжение глифов по осям —
оригинал (upstream `hps/vps *= scaling` раздельно); дефектом были
немасштабированные коробки меню под масштабированным текстом. Все пять
`createMenus` вызывают `convertToScreenScale(w,false)` (YRATIO):
MainMenu @0xc52bd5, NewGame @0xc5d8f5, Continue @0xc4067d, Options @0xb881ad,
Settings @0xbd705d — проводка добавлена, `loading` без вызова оставлен как
есть. Регрессии, кодировавшие немасштабированное поведение, обновлены
(frontend 235.0, headless solid blue). Фон — цепочка `loadMenuLevel @0x584b80`
(уровень, свет, камера, музыка): многопроходная задача, не заглушена.
Доказательства: `research/ui-menu-scale.md`.
Ниже сохранена история, начиная с population-placement.

---

# Текущая точка: размещение по оригиналу (population-placement)

Закрыта проблема large-12/13: seed 42 даёт 61/61, общий сценарий seed 491 —
76 из 76 с 0 unplaced (было 51 из 76, 25 unplaced). Причина — выдуманный
BFS-фильтр связности и полное перемешивание кандидатов: оригинал так не делает.
Перенесён rejection sampling из `CLevel::populateSectionOfLevel @0x95d220`:
порядок RNG z,x, полярный pick через `randomOpenPositionRange @0x945770`
(r в [0,3], угол, sincosf-порядок `MATH::rotateY @0xc7a400`), проверка
проходимости по клеткам 0.4, no-spawn радиус 1.0, до 50 попыток.
Дифтест: 3005 пиков побитово + состояния volatile RNG
(`original_population_placement_comparison`). Высота — снэп к сетке
(у оригинала константа 27.5 и engine settle, которого в порте нет);
секции NPCS/CREEPS/PROPS, spawn nodes, formations, регионы no-spawn —
открыты. Доказательства и границы: `research/population-placement.md`.
Полный прогон: 137/137 (core 68, assets 43, reference 17, render 11
с пересечениями групп).

Следующая граница по размещению: upfront `rollSpawnClass` (порт бросает класс
на каждого монстра внутри цикла, оригинал — один раз до цикла), секции
NPCS/CREEPS/PROPS, spawn nodes (`CLevel+0xf0`, счётчики `+0x114`), настоящие
регионы no-spawn (`CLevel+0xd8`), второй слой 0.4-сетки.

# Текущая точка: UI imageset — смещения и автомасштаб (U07)

Порт игнорировал XOffset/YOffset и NativeHorzRes/VertRes/AutoScaled.
Перенесено по вендорной libCEGUIBase.so.1: парсинг атрибутов, сдвиг
destination на масштабированное смещение ДО клипа (`Image::draw`),
выравнивание round-half-away (`setHorzScaling @0xe59e0`, константы ±0.5).
Примеры: WindowLeftEdge +4 на 1080p → +8, WindowRightEdge −5 → −9,
MouseTarget (−8,−8). Тест `original_ui_imageset_offsets`: 27 проверок на
настоящем pak. Открыты: scaled-размеры для Falagard (U09), хотспот курсора
(софт-курсора нет), editor-копии imageset. Доказательства:
`research/ui-imageset-offsets.md`.
Ниже сохранена история, начиная с U06 screen scale.

---

# Текущая точка: UI screen scale возвращён (U06/P1)

`convertToScreenScale @0xa83ed0` снова в дереве: priority-ZIP merge large-16
его стёр, восстановлен с бэкап-ветки без изменений логики (только bottomhud
wired через подтверждённый call site; HUD-down large-16/P2 не тронут).
Оригинальные пробы перегенерированы свежо — байт-в-байт с JSON 2026-09-17
(400 деревьев / 9600 float, 390→548.4375 на 1080p). Тест `ui_screen_scale`:
28 проверок. Открыты: rescaleUI-жизненный цикл, остальные экраны, полная
Falagard-геометрия. Доказательства: `research/ui-scale-p1/`.
Ниже сохранена история, начиная с UI-шрифтов.

---

# Текущая точка: UI-шрифты — флаг автохинта (U14, часть)

Порт грузил глифы с `FT_LOAD_DEFAULT`; оригинал (`updateFont @0xe07b0`,
`mov edx,0x20` перед `FT_Load_Char` в shipped libCEGUIBase.so.1) — с
`FT_LOAD_FORCE_AUTOHINT`. На BRLNSDB 11/16px различаются ~213/215 растров и
~112/215 адвансов: старый вывод был неверным, не просто недоказанным.
Перенесён флаг; регрессия `original_ui_font_load_flags` сверяет порт с прямым
рендером 0x20 тем же FreeType + требует отличие от DEFAULT. Формула адванса
намеренно не тронута (×1/64 == /64 побитово). Метрики ascender/height из
юнитов — открыты (qword по `face+0xa0]+0x28` не лёг ни на одно поле
`FT_SizeRec`; см. `research/ui-font-autohint.md`).
Ниже сохранена история, начиная с UI mesh bindings.

---

# Текущая точка: UI mesh bindings (U03) + UI deep-map

Применён кандидат из внешнего `OpenTorchlight-UI-deep-map(1).zip` (SHA-256
`c951ee2b…798eb`, база large-16 — сошлась побитово): 7 UI-моделей занижают
конец submesh-чанка, парсер ронял 72 локальные привязки к костям. Проверка
байтами настоящего pak + полный прогон 3312 мешей: дельта ровно +72, остальные
тоталы не изменились (`original_ogre_meshes`: 477080). Пофайлово: character 12,
inventory 8, journal 12, merchant 8, pet 8, quest 12, skill 12; dropdown (6
shared) корректно не затронут. Импортированы 12 фрагментов и
`mesh_boundaries.json` → `research/ui-deep-map/`; тяжёлые data и ASM-выгрузки
остались во внешнем бандле и подтягиваются попатчно. U01–U02, U04–U25 открыты;
U19 подтверждает: HUD-down large-16 сохранить и не тянуть на все контролы.
Ниже сохранена история, начиная с population-placement.

---

# Текущая точка: large-16 — прямой типизированный оружейный урон

Алхимик снова атакует Moldy Staff, теперь через исходное распределение в яд,
MAGIC и защиту нужного типа. Общий цикл игрока/противника, HIT и OTC v6
подключены; исходные файлы остаются внешними. Чтение OTC v1–v5 сохранено.
Большие rollAttack/calculateCombatStats не объявлены полностью перенесёнными.

Актуальные доказательства: `research/large-16-typed-damage.md`.
Следующие пакеты: `NEXT_PATCHES_LARGE_16_RU.md`.
Текущие результаты: `verification/large-16/verification.json`.
Фикстура v5 создана неизменённой large-15, а не заменой версии нового файла.
Ниже сохранена история; блокировка посоха из large-15 уже устранена настоящей
прямой оружейной ветвью, но MISSILE/SKILLS не подменяются этим решением.

---

# Текущая точка: large-15 — оригинальное поведение вместо прототипных правил

Исправлены физическое AC/DEF, подключение поддержанных эффектов скорости,
округление графов предметов, смысл наследования и его RNG-вызов, ограничение
неподдержанных melee и MouseButtonDown HUD. Пройдено 125 уникальных основных
тестов, ASan/UBSan 11 выбранных и Release 4. Формат остаётся OTC v5.

Актуальный план: [NEXT_PATCHES_LARGE_15_RU.md](NEXT_PATCHES_LARGE_15_RU.md).
Доказательства и конкретные открытые разрывы: research/large-15-gameplay-fidelity.md.
Сначала снять подмену урона настоящим typed/missile pipeline, восстановить
требования/инвентарь и исходные состояния UI; затем расширять услуги/питомца/кампанию.
Стартовый посох Alchemist пока недоступен, а не выдаётся за физическое оружие.
Новые игровые файлы не нужны. Старые UI-патчи повторно поверх large-15 не накладывать.

---

# Исторический план UI-прохода (событие release ниже устарело)

# Прежняя точка: UI-патчи к присланному large-14

Этот UI-проход не меняет игровые формулы и формат OTC. Исправлены обрезка
изображений, потеря прозрачных HUD-кнопок, выдуманные рамки у известных
ресурсных элементов и выход настроек из модальной паузы. Постоянная техническая
панель теперь включается отдельно: `--debug-ui 1`.

Доказательства, ограничения и новые тесты: `research/ui-repair-patches.md`.
Inventory/Skills/Quests вызывают прежние PORT-панели; Journal/Pet не подменены
ими и остаются неподдержанными. Работающий click не означает готовое окно.
Следующая UI-задача — исходный inventory.mesh + inventorymenu.layout +
CInventoryMenu, затем полный Falagard FrameComponent/state/layer pipeline.
Сначала смотреть перечисленные в исследовании адреса и строки декомпиляции.

Проверять на своей оконной сборке после применения: в этом проходе доказана
работа общего цикла и software GLES, а не полнота native Wayland/FreeType.
Новые тесты зарегистрированы в существующих группах core/assets/render.
Прошлые результаты ниже не переносить автоматически на изменённые исходники.

---

## Сохранённый предыдущий план игрового наполнения

# Следующий проход после large-13

## Текущая база и запрет выдуманных замен

Донор large-12. Настоящие pak, ELF и библиотеки уже предоставлены. Не запрашивать
их повторно и не включать в исходный архив. Доказательства и адреса:
`research/large-13-subsystem-evidence.md`; результат: `GAMEPLAY_LARGE_13_RESULT_RU.md`.

Подключены Infuse (10 инвестируемых рангов), конечные self-buff эффекты на HIT,
покупка бесконечных зелий Тарна, ограниченные quest-controller команды/флаги,
OTC v5. Квестовый каталог 111/35 означает 111 прочитанных и 35 допустимых для
ограниченного контроллера определений, **не 35 готовых игровых заданий**.
Сквозной service/skill-тест имеет явную фикстуру XP/золота — не выдавать его за
прохождение кампании. Текущие результаты в `verification/large-13/verification.json`;
не переносить их автоматически на следующий изменённый исходник.

## Первый блок: настоящая цепочка Ember Bolt

Сопоставить `CSkill` events, layouts `emberfireball`, `CMissile::initialize
@0xd00650`, `updatePositionByVelocity @0xd02720`, `checkCollision @0xd038a0`.
Ember Bolt имеет 2/3/4 снаряда по рангам, poison/MAGIC damage и knockback;
не подменять одиночным огненным instant HIT. Граница полёта и столкновения —
отдельно от damage/effect evaluator. Homing выполняет нормализованное смешивание
с шагом 1/30 секунды, не поворот в градусах. Константа проверена в ELF.

Ещё не восстановлены целиком начальная скорость/разброс и все RNG-потребления,
acceleration/drift/сплайны, swept-sphere столкновения и modifier/soak pipeline.
Нужны отдельные bounded comparisons, затем реальный UI-ввод/полёт/HIT/death/XP,
сохранение и продолжение в другом процессе. Не менять compiler на частичное
исполнение неподдержанного умения только ради доступной кнопки.

## Квесты, диалоги и зависимости кампании

Уже есть каталог/requirements, forced controller commands, порядок вложенных
событий и сохраняемые flags; нет нормального NPC offer/dialog pipeline.
Продолжить reward/objective/populate/pet acceptance и исходные cleanup-правила.
Source giveQuest принудительно обходит offer requirements — обычное предложение
NPC не должно пользоваться этим обходом. QUESTCONTROLLERCOMPLETES не означает
«убить всех врагов». Проверять конкретные objective/controllers и gates.

Для IntroPT3 требуется исходное populate side effect, для Mercenary — pet side
effect; сейчас эти команды блокируются целиком. Последний босс и финал не
считаются рабочими от наличия имен квестов. Маршрут кампании должен пройти
через реальные входы/условия без ручной правки flags/здоровья/лутовых предметов.

## Торговля, услуги и питомец

Выполнено: ограниченная покупка бесконечных зелий Тарна, price graphs, atomic
transfer/debit, совместимость стеков. Открытый остаток: оригинальная частота
обновления запасов и ranges без explicit MAXLEVEL, finite stock/quality,
продажа/buyback, идентификация/зачарование/банк, NPC диалоги, pet inventory/AI,
возврат из торговли/превращения/сохранение. Цена услуги сама по себе не услуга.
Панели K/F/J и shop — PORT presentation, не исходный Falagard/UI behavior.

## Размещение, мир и выпуск

Осталась проблема large-12: seed 42 resource test 61/61, common-app seed 491 —
51 из 76, 25 unplaced. Не уменьшать requested count ради зелёного теста.
Продолжить fine grid/связность, formations/champions, динамические двери,
вражеские skills/особый AI, боссы; затем полный interface/FX/sound и desktop.

## Воспроизводимые проверки

GAME_DIR — отдельный каталог read-only оригиналов. Нужны pak.zip,
Torchlight.bin.x86_64 и родные OGRE/CEGUI/FreeImage по обычным путям установки.
Не запускать сценарии в пользовательских сохранениях.

```bash
python3 tools/check.py --core --assets "$GAME_DIR" \
  --reference "$GAME_DIR/Torchlight.bin.x86_64" --render --jobs 2
```

При конфликте адресов с non-PIE Python нельзя затирать память процесса или
считать SKIP успешной проверкой. Собрать отдельный PIE launcher из установленного
matching Python SDK (подробности в tools/testing):

```bash
python3 tools/testing/build_pie_python.py --output /tmp/torchlight-python-pie
python3 tools/check.py --core --assets "$GAME_DIR" \
  --reference "$GAME_DIR/Torchlight.bin.x86_64" \
  --reference-python /tmp/torchlight-python-pie --render --jobs 2
```

Для продукта требуется настоящий FreeType/Wayland/GLES SDK. Прототипный fallback
шрифта и тестовые ABI-декларации не являются выпускной конфигурацией.
Сохранения v5 необратимы для старых сборок; миграции проверять подлинным файлом
старого writer, а не сменой одного номера формата.

---

# Архивный план large-10 (история, не новые результаты)

# Следующий проход после large-10

## Интеграторский прогон large-10 (настоящие pak+ELF)

**Итог: core 45/45, assets 32/32, render 6/6, reference 11/11; desktop NOT RUN.**

Найден и исправлен порт-дефект, невидимый на авторских ресурсах: PORT-кнопки
паузы ставились в x=16, y=180+row*48 и перекрывали оригинальную
`Return To Game` (83,268 246x44) из `optionsmenu.layout`; `Frontend::click`
выбирает сверху вниз, поэтому `original_menu_presentation` падал
(«resource pause resume failed»). Теперь supplemental-кнопки якорятся ниже
разрешённых оригинальных прямоугольников (`src/frontend.cpp`), оригинальная
кнопка снова работает, а PORT-операции сохранены и помечены `PORT:`.
`CHECKSUMS.sha256` пересчитан на исправленном дереве.

Актуальный результат: `UI_MENU_COMPLETION_RESULT_RU.md`; исходные доказательства:
`research/ui-menu-completion.md`; проверки: `verification/large-10/verification.json`.
Ниже сохранён старый план large-9. Его `41/41 + assets/reference/render` — исторический
прогон интегратора, не повторная проверка текущего архива.

В large-10 закрыта потеря статических надписей, добавлена привязка CharacterName /
PlayerNName, ресурсная пауза, защищены скрытые/disabled кнопки и .otc save-failure.
Исправлен пустой GPU-атлас, добавлены UTF-8, переносы, ограниченное форматирование
и clipping. Core 44/44 без SDK, FT/GLES 5/5, выбранные ASan/UBSan 10/10.

**Первым делом на машине с read-only исходной игрой** повторить полный стенд:

```bash
python3 tools/check.py --core --assets "$GAME_DIR" --render --jobs 4
ctest --test-dir build-verification -R '^original_menu_presentation$' --output-on-failure
python3 tools/check.py --reference "$GAME_DIR/Torchlight.bin.x86_64" --jobs 4
```

Новая проба сравнивает наличие Text/Font в кадре с оригинальными четырьмя layouts;
она НЕ сверяет пиксели исходного CEGUI. Не перепутать авторский menu-widgets.pak.zip
с настоящим pak.zip: успешный smoke на нём не является assets-проверкой.

Дальше: реальные `WidgetLook`/`StateImagery`/Label-area, порядок слоёв, цвета,
StaticTextOutline shadows и составная рамка; `inventorymenu.layout` и createIcon /
updateSlots. Нормальный/фокусный/disabled скин частично подключён, но PushedImage
только читается: настоящая pointer capture/release и весь Falagard ещё открыты.
GUIEXITGAME оставлен disabled; не привязывать его к выходу в титульное меню без
исходного dispatcher/trace. Settings и удаление .otc требуют отдельной реализации.

Битовая сверка оригинального FreeTypeFont, закрепление DPI и точные HP/mana/XP
формулы по ASM остаются приоритетами из старого задания. Не заменять отсутствующий
оригинал картинкой текущего порта. Полный Wayland harness всё ещё NOT RUN.

---

# Следующий проход после UI-этапа (шрифты/HUD) — история

**Тогдашнее задание (файл удалён при чистке GPT workflow):** добить интерфейс (главный экран,
меню New/Load, пауза, инвентарь, бит-в-бит сверка шрифтов, Falagard,
`updateIngameUI @0xab8100`). Ниже — полный контекст и остаток.

Состояние входа: core 41/41, assets 31/31, reference 11/11, render 5/5 на
настоящих pak+ELF. `CHECKSUMS.sha256` валиден. Читать целиком этот файл,
`README.md`, `research/ui-visuals.md`, `research/progression-and-world-rewards.md`,
`research/remaining-work-inventory.md`; карта остатка —
`python3 tools/coverage_map.py --check --next 25`.

Сделано в этом проходе: оригинальные `<Font>` CEGUI 0.6.2 через FreeType,
HUD из `bottomhud.layout` с полосами HP/mana/XP, картинки кнопок из
`GuiLook.looknfeel`, подписи из layout. Проверки:
`original_ui_font_resource` (настоящий pak), HUD-кадры в `gles_ui_headless`.

## Первый приоритет: визуал (продолжить)

1. Сверить атлас глифов с оригинальным `CEGUI::FreeTypeFont` изолированным
   вызовом (бит-в-бит по возможности) и закрепить DPI-выбор (сейчас `inferred`).
2. Достроить Falagard-подмножество: состояния кнопок, Window frame составные
   части (`WindowTopLeft` и т.д.), текстовые тени; затем `inventorymenu.layout`
   (рамка, слоты, `itemicons`/`UIIcons`) и полный `updateSlots`.
3. `CGameUI::updateIngameUI @0xab8100`: декомпилировать/выгрузить участок полос
   (`0xab885b..0xab8974`) и заменить `inferred` формулы позиции/размера.
4. `--desktop` harness (тестовый композитор) остаётся NOT RUN.

## Полный список открытых моментов (выбирать по приоритету задания)

**Fidelity наград/прокачки:** `CPlayer::levelUp @0x8f9ad0`; spawner give-XP
гейты и атрибуция владельцу; fame `CCharacter::awardFame @0x83c9c0` и
`fameGate`; volatile RNG золота; ранг `CLevel+0x1a8`; champion-путь
(`makeChampion` уже снят, спавн чемпионов — нет).

**Бой:** ranged/projectile по `performAttack @0x847280`, `fireMissiles
@0x87f120`, `CWeaponMissileDescriptor @0x602dc0`, `equipment+0x400`, muzzle
`0.8`, pitch `5.0`; полный `CEffect` lifecycle/conditions/stacking/remove;
factions/AI flags/skill selection/retarget/группы; interrupt, секторы/AOE,
stun/knockback/debuff; death-события игрока/питомца/монстров.

**Умения:** loader/learn/rank/cast/cost/cooldown/animation/target/missile/AOE —
все три класса через шаблоны данных (407 файлов `media/skills/`); mana/health
regen; расходники/зелья и stack.

**Предметы/экономика:** treasure rank/RNG/rarity и вложенные spawn semantics;
affix/requirements/identification/sockets/stack; все слоты/dual-wield;
inventory grids; merchant buy/sell/stock/prices, enchant, combine, stash.

**NPC/квесты/питомец:** `CCharacter::inInteractionRange @0x8244a0` с f32
`0xfce4b8/bc/c0`; `CInteract::interactWithUnit @0x986ff0`;
`CTriggerUnit::interact @0x9095c0`; quest loader/state/requirements/dialog/
rewards/persistence; pet spawn/follow/combat/inventory/send-town/save.

**Мир/кампания:** полный layout commands/timelines/triggers и re-entrancy;
chests/doors/breakables/traps/shrines/portals; `CDungeon::loadDungeon` и
`performWarp @0x58d110` (parent-route, `CDungeon+0x80`); все 35 этажей, боссы,
финал; difficulty/rank/theme/entry modes; volatile floors.

**Save/presentation/platform:** оригинальный persistence (timeline/quest/pet/
skills), backup/delete UX; audio banks/music; particles/FX/decals/lights;
localization/settings/splash; Android lifecycle/touch/APK — только после ПК.

Правило прежнее: не поднимать допуски и не отключать проверки; каждая новая
цепочка — resource/ASM-доказательство и CTest, статусы
`original-code/library-derived/resource-derived/inferred/prototype`.

## Исторический план: награды и прокачка (после large-8)

Сначала прочитать `PROGRESSION_REWARDS_RESULT_RU.md` и
`research/progression-and-world-rewards.md`. Использовать текущий архив целиком:
формат `.otc` v2 должен сохранять обратное чтение v1.

Проверка интегратора на настоящем pak/ELF выполнена: core 40/40, assets 30/30,
render 5/5, reference 10/10, включая `original_progression_resource_graphs` и
`original_world_gold_comparison`.

Обычный XP producer проверен по машинному коду: `CCharacter::setLevel`
@0x83ecdd..0x83ecfd и `CCharacter::makeChampion` @0x85191b..0x85192e вычисляют
`trunc((g / 100) * g)`, поле данных `XP` — только ненулевой гейт. Порт переведён
на `original_monster_experience`, добавлен differential-тест
`monster_experience_export_comparison` / `original_monster_experience_comparison`
(20 031 случай). Открыто: `CPlayer::levelUp @0x8f9ad0`, spawner give-XP
gates/owner attribution, реальный CLevel+0x1a8 и volatile RNG золота. Только
после этого повышать original fidelity по этим участкам.

Следующий независимый игровой блок — активные skills/effects/projectiles,
расходники/regen или NPC services. Не превращать ranged в instant melee и не
вшивать один класс/умение ради демонстрации. Skill points сейчас накоплены,
но pipeline обучения/применения и fame остаются открытыми.

## Исторический план после large-6


Актуальная работа: `AUTOMATED_VERIFICATION_RESULT_RU.md`,
`research/automatic-verification.md`. Ниже сохранены прежние границы large-5,
но отсутствие настоящего pak/Town в их исторических формулировках больше
не описывает нынешний ресурсный стенд.

## 1. Закрыть именно оконный слой, не пересоздать тестовую игру

`src/application.cpp` уже общий для окна и сценариев. EGL/pbuffer сценарий
подтверждает настоящие menu/application/resources/render, но не Wayland
callbacks/focus/configure/close/OS input. Нужен тестовый compositor в отдельном
runtime-dir/socket и закреплённая доставка ввода. Не подключаться к рабочему
столу пользователя. Зарегистрировать настоящий CTest с меткой desktop;
тогда `--desktop` перестанет возвращать NOT RUN. Простого `--frames 3` мало.

Повторить New/Continue/resize/pause/save/новый процесс; добавить повреждённый
slot и отказ записи именно через окно. Сохранить общий loop, не дублировать
его в harness. Отсутствующий SDK/Weston/протокол тестового ввода должен быть
явным NOT RUN. Production Wayland adapter после извлечения пока не собран.

## 2. Получить ограниченные эталоны оригинала

Нужен SHA-закреплённый ELF. Имеющийся `compare_attack_speed.py --scenario-dir`
исполняет только старые immutable числовые spans на новых реальных SPEED;
нулевые haste/resistance — явные входы, а не полноценная трасса атаки.
Следующие эталоны: один обычный HIT, переход и UI → world с устойчивыми ID и
записью порядка вызовов. Не записывать текущий framebuffer порта как
доказательство исходной графики. Render dump пока не apitrace и не depth/ID pass.

## 3. Подтвердить parent-route и расширить сквозную игровую сцену

Настоящий roundtrip Town → Main:1 → Town прошёл. `PARENT_DUNGEON` взят из
MAIN.DAT.ADM; отрицательная first-floor ветвь видна в performWarp, но loader
mapping `CDungeon+0x80` всё ещё inferred. Нужен focused `CDungeon::loadDungeon`
и контрольные инструкции `performWarp @0x58d110`; source/границы в
`research/parent-dungeon-boundary.md`. Special -99/waypoint/explicit destination
не объявлены восстановленными этой правкой.

Добавить реальную controlled melee → HIT → death/loot → pickup/equip → save
сцену через тот же common host. Сейчас настоящие три класса/стартовые вещи и
цикл инвентаря проверены; полноценный ranged и боевой renderer-сценарий не
возникли автоматически. Нативные authored/pak-only combat тесты сохранены.

## 4. Пользоваться машинными артефактами

`tools/check.py --core --assets DIR --render` пишет пять групп независимо;
`coverage_map.py --verification-report FILE` показывает их рядом с reviewed
coverage, но ничего не повышает до verified/closed. Каталог missing references
(в том числе старые authoring paths) нельзя назвать 152 сломанными файлами.
Для каталога и новых сцен сохранять хеш pak/скрипта/библиотеки/Mesa и первую
ошибку, не подбирать tolerances ради зелёного результата.

Старая thin-wall проблема, исходный scheduler, interaction requirements,
эффекты, ranged, мировой gold/NPC/quests/pet остаются отдельными задачами.

---

## Исторический NEXT_CHECKS после large-5 (контекст, не свежий статус)

# Следующий проход после frontend/campaign (large-5)

Актуальный результат: `FRONTEND_CAMPAIGN_RESULT_RU.md`. Границы реализации:
`research/frontend-save-evidence.md`, формат: `research/checkpoint-format.md`.
Исходный большой scope был в удалённом при чистке `GPT_PRO_LARGE_TASK.md`; это не «вся игра».
Полный реестр: `research/remaining-work-inventory.md`. Машинная карта:
`python3 tools/coverage_map.py --check --next 20`.

## 1. Подтвердить настоящий оконный цикл на машине интегратора

Свежие проверки здесь: 28/28 portable и 28/28 ASan/UBSan GCC14.2; три отдельных
процесса авторской сцены; четыре реальных Mesa/EGL UI-кадра. Это НЕ полный
Wayland-desktop, настоящий Town или новый прогон исторических 59/59.

```bash
bash tools/check.sh "/path/to/Torchlight/game"
./build/torchlight_desktop "/path/to/Torchlight/game" --save-dir "$HOME/ot-large5-test"
```

Проверить без `--frames` и `--main-stratum`: main menu → каждый из трёх классов,
имя → Town; пройти вокруг реальных препятствий, выбрать NPC/Unit Trigger,
подобрать/надеть предмет, получить урон, сохранить через Escape. Завершить
процесс, Load/Continue, сравнить класс/имя/позицию/HP/mana/gold/экземпляры и слоты.
Затем вход в Main, смерть → R, возврат в Town, сохранение и новый процесс.
Ошибочный `.otc` должен оставаться видимым ошибочным слотом, а не New Game.

`original_frontend_checkpoint` добавлен к CTest при `TORCHLIGHT_ORIGINAL`:
он читает настоящий pak, три XML меню, всех игроков и Town, сохраняет и загружает
в отдельном процессе. Код теста скомпилирован, но без pak здесь не выполнен.
Он также не доказывает оригинальный .SVB формат или весь графический сценарий.

Особенно проверить: исходные CEGUI background/imageset свойства, unified bounds,
resize и mouse hit-test, pause → resume с восстановлением GL state, save-error
в паузе, отказ несовместимого ресурса до изменения live state. Не считать
прототипные bitmap labels/buttons восстановленным оригинальным skin/font.
Физический US-ввод имени пока без IME и кириллицы. Normal — единственный режим.

## 2. Проверка тонких препятствий в существующей NavigationGrid

При подготовке авторской сцены найдена открытая граница: вертикальная тонкая
стенка на границе клеток (x=10 при cell_size=1, radius=0.45) может оказаться между
проверяемыми центрами и не пометить клетки заблокированными. Сквозная positive
фикстура использует x=10.5, где стена действительно попадает в blocked cells.
Это не исправление исходного растеризатора и не доказательство произвольных
городских стен. Отдельно добавить сегмент/cell-edge collision или другой
доказанный способ обработки после сравнения с оригинальным pathfinder.
Не менять геометрию реального Town, чтобы скрыть проблему.

## 3. Расширить interaction по доказанным producer/requirements

Теперь есть общий generation-bound selection/approach/dispatch: Unit Trigger
идёт через LogicRuntime, не произвольный прямой Warper; noncombat NPC даёт
инспекцию/видимый unsupported-service, без фиктивной торговли или награды.
Для продолжения минимально нужны:

- `CCharacter::inInteractionRange @0x008244a0` ASM и три f32 по
  `0x00fce4b8`, `0x00fce4bc`, `0x00fce4c0`. Ghidra показывает разные ветви и
  вычитание collision radii; caller radius 2.25 в порте остаётся prototype.
- `CInteract::interactWithUnit @0x00986ff0`, producer текущего interaction target,
  выбор callback/service; не путать название класса с доказанным поведением.
- `CTriggerUnit::interact @0x009095c0`, `trigger` и producer quest/key requirements.
  Сохранять re-check на arrival, отсутствие повторного dispatch и переходов
  устаревшей команды после смерти/смены уровня.

Далее NPC merchant/quest/stash можно добавлять по одному сквозному сервису:
resource → requirement → UI → операция → checkpoint. Нельзя назначить сервис
только по имени NPC или открыть все Warper в обход logic/quest gates.

## 4. Расширить сохранение без заявления о совместимости с оригиналом

Текущий `.otc` сохраняет только поддержанные runtime-данные. Отсутствуют quest,
полные timeline/affix/skills/pet состояния, original volatile-floor reset,
миграции будущих schema versions, backup/delete UX. До их runtime-реализации
нельзя объявить эти разделы сохранёнными. Offscreen clocks в кеше заморожены —
prototype. Сохранённое действие атаки не возобновляется; actions/HIT/paths
отменяются при load, а AI cooldown/RNG сохраняются.

При ошибке после rename, но до directory fsync файл уже мог быть заменён: ошибка
прямо требует reload revision; нельзя повторно присвоить старую revision и
переписать слот. Pre-rename crash оставляет старый слот целым, возможный
`.checkpoint-*` orphan игнорируется. При принудительном закрытии compositor
ошибка последней best-effort записи видна в stderr, не в уже закрытом окне.

`CGameClient::saveCharacter @0x0058b5d0` / `loadCharacter @0x00581ce0`,
`CPlayer::storeLevelSavedState @0x008f6080`, CLevelState/CLogicNodeState и
`restoreLevelState` — ключевые границы для полного original persistence.

## 5. Следующий независимый runtime: мировой gold / no-loot / ranged

Числа/строки уже read-only извлечены в `research/original-gameplay-inputs.json`.
Не повторять извлечение вместо переноса. Но `MINVALUE/MAXVALUE`, четыре GOLDDROP
имени, одна строка `PROPERTIES`, pitch=5 и muzzle offset=.8 сами по себе не
доказывают producer/rank/difficulty/virtual dispatch.

Для `CItemGold::unitInit @0x008ca940` уже есть focused ASM. Проследить значение
client+0x1a8+1 у аргумента графа, difficulty и путь фактического getItem/pickup
до wallet. Для no-loot найти конкретный descriptor field/вход
`setUnitsGiveLoot`, а не объявить `PROPERTIES` именем искомого bool.

Ranged: `performAttack @0x00847280`, `fireMissiles @0x0087f120`, producer
`equipment+0x400` и `CWeaponMissileDescriptor @0x00602dc0`. Нужны descriptor,
hand/muzzle, resource/velocity, sweep/LOS, owner/ignore list, pierce/retire,
HIT attribution, death/warp cleanup и desktop representation. Существующий
unavailable gate не снимать ради мгновенного melee сквозь стены.

## 6. Следующий объём полного реестра

После этих границ: исходный scheduler/AI flags/factions; dynamic effects,
conditions/graphs/stacking/remove; skills/mana regeneration; XP/fame/points;
полная rarity/equipment/consumable модель; quests/merchant/stash/pet; audio/FX;
только затем проверяемый Android lifecycle/touch/packaging. Пользоваться coverage
frontier как воспроизводимой подсказкой, не принимать centrality за важность
каждого library/thunk symbol и не повышать `closed` за один smoke.
