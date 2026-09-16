# Следующий проход после large-8: награды и прокачка

Сначала прочитать `PROGRESSION_REWARDS_RESULT_RU.md` и
`research/progression-and-world-rewards.md`. Использовать текущий архив целиком:
формат `.otc` v2 должен сохранять обратное чтение v1.

Первая проверка интегратора — новые графы трёх классов и награды на настоящем
pak (`original_progression_resource_graphs`), затем прежние assets/render
сценарии общего `run_application` и новый численный reference
`original_world_gold_comparison`. В этом проходе настоящих pak/ELF нет.

Далее — проверить ASM обычного XP producer внутри CCharacter при выборе
EXPERIENCE_MONSTER (экспорт `character.c`, область около 0x83ecd6..0x83f928),
отдельно `CPlayer::levelUp @0x8f9ad0`; не принимать повреждённую декомпиляцию
за формулу. Уточнить spawner give-XP gates/owner attribution, реальный
CLevel+0x1a8 и volatile RNG золота. Только после этого повышать original fidelity.

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
Исходный большой scope остаётся в `GPT_PRO_LARGE_TASK.md`; это не «вся игра».
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
