# Историческая функциональная инвентаризация OpenTorchlight

> Исторический накопительный перечень. Часть таблицы ниже отстаёт от новых
> missiles/skills/UI проходов. Текущие ограниченные возможности и блокеры:
> [capabilities.json](capabilities.json); актуальность их тестовых свидетельств —
> `tools/readiness.py`. Это не code-first readiness. Старые результаты не
> переносятся на новый код.

Этот файл не задаёт область следующих проходов. Действующий процесс — [decomp](../decomp/README.md); прежний процесс —
[code-first.md](code-first.md), текущий scope — [ui-contour.json](ui-contour.json).
Сохраняем список как вторичный источник reuse-контекста и smoke/compatibility
сценариев. Статус относится к исторической поведенческой границе; `verified`
не означает закрытие подсистемы или целой исходной функции. Четыре legacy-стадии
среза и feature-checklist 30/38 не заменяют отдельную reviewed-приёмку всех
ветвей, полей, порядка, ошибок, эффектов и библиотечных зависимостей функции.

## Изменение large-13 (донор large-12)

Infuse (10 инвестируемых рангов), исходные cost/level/cast/HIT и конечные
усиления; покупка бесконечных зелий Тарна; ограниченные quest requirements /
controller flags / nested events; OTC v5 и подлинный v4 migration writer.
Сквозной common-loop тест: 47 assertions/3 processes, с явно подготовленными
XP и золотом. Экономика: 20 600 native результатов. Точные свежие прогоны:
`../verification/large-13/verification.json`.

Каталоги 407 skills и 111 quests не означают их исполнение. 35 definitions
пригодны только для flag-only quest slice без rewards/objectives/populate/pet.
Остальные навыки, missiles/magic, услуги NPC, pet, dialogue/reward/campaign и
полный UI/FX/desktop остаются. Границы: `../GAMEPLAY_LARGE_13_RESULT_RU.md`.

## Изменение large-12 (донор large-11)

Теперь есть настоящие pak/ELF. Подключены конечное HP/mana-восстановление от
12 поддержанных зелий, стеки/расход, OTC v4, обычная STRATA-популяция и прямой
физический ranged HIT со статической линией видимости. Проверены миграция
настоящего старого v3 и общий сценарий новой игры/выстрела/XP/save/Continue.
Численные recovery/population-функции сравнены исполнением оригинальных
инструкций. Исходные материалы, точные результаты и ограничения:
`../GAMEPLAY_LARGE_12_RESULT_RU.md`, `../verification/large-12/verification.json`.
Это не полные effects, skills, missiles, исходное размещение или кампания.

## Изменение large-11 (донор fresh)

Добавлены пассивная регенерация игрока из GLOBALS/эффектов, maxHP экипировки и
разделение base/effective HP, сохранение v3 с настоящими v2 migration-fixtures.
Core 49/49; выбранные ASan/UBSan 11/11; настоящий pak/ELF здесь не проверялся.
Обычная XP-формула была подтверждена интегратором ранее, до fresh; прежнее
утверждение «XP producer inferred» ниже является историей large-8.
Нет полного timed-effect/potion pipeline, восстановления HP монстров/питомца,
skills/ranged/population/quests/торговли/pet/кампании. Исторические функциональные
требования: `../FULL_GAME_ROADMAP_RU.md`.

## Изменение large-8

Подключены обычные награды за смертельный HIT игрока, graph-driven XP/level,
очки/распределение атрибутов, рост HP/mana, gold pickup в кошелёк и checkpoint v2
с миграцией v1. Это рабочий portable срез, не завершённая исходная прокачка:
XP producer ещё inferred, gold rank/RNG context prototype. Настоящие pak/ELF
в этом проходе отсутствуют; исторический large-6 acceptance не переносится
автоматически на новый код. Детали — `../PROGRESSION_REWARDS_RESULT_RU.md`.

## Изменение large-6

Настоящий pak теперь проверен и отрисован в общем application-loop без окна:
Town/Main, три класса, разные стартовые вещи, движение/инвентарь/resize,
межпроцессный save/Continue и обратный маршрут через parent. Отдельные группы
и отчёты различают resource compatibility, собственный regression и original
reference. Renderer выполняется в Mesa EGL; compositor/OS input harness и
новые original-process traces остаются открытыми. Каталог перечисляет
поддержанные и неподдержанные границы, а не процент готовности игры.
Подробно: `automatic-verification.md`, `../AUTOMATED_VERIFICATION_RESULT_RU.md`.

## Историческое изменение large-5

Новый переносимый checkpoint и frontend реализованы и проверены на авторских
ресурсах; оконный код подключён, но настоящий Wayland/Town/pak здесь не запускался.
Это не закрывает весь New/Load оригинала. Текущий результат и пределы:
`../FRONTEND_CAMPAIGN_RESULT_RU.md`, `frontend-save-evidence.md`.
`coverage.tsv` — машинная карта по адресам; наличие декомпиляции автоматически
не повышает статус. Исторические `verified` ниже относятся только к ранее
описанным проверенным границам, а не ко всей подсистеме и не к fresh full-game run.

## Сводная карта

| Область | Исторический статус | Что было зафиксировано | Остаток на момент записи |
|---|---|---|---|
| Архивы/ADM/UNIT/BASEFILE | verified | полный разбор исходного pak и 3343 UNIT | редкие форматы и записи, которые появятся в новых системах |
| Mesh/skeleton/animation | verified | загрузка, skinning, клипы и события | blend graph, attachments, death/special/skill состояния |
| Material/texture/render | partial | основной GLES-проход, DDS/PNG, ambient override | все passes, blend/depth/cull, particles, decals, lights, post effects |
| Камера/input/pathfinding | partial | ранее сравненные формулы/A*, frontend focus и save-position validation | тонкая стенка между центрами grid cells, drag/controller, специальные режимы, original collision fidelity |
| Layout/random level/logic | partial | генерация, links, timer, spawn, warp, обычная STRATA-популяция | точное размещение/связность (не все выбранные монстры размещаются), весь command set, re-entrancy, сохранение состояния, special layouts |
| Boot/game states/menu | partial | frontend New/Load/Continue/pause/save/exit, XML geometry/bindings/images, проверка реального EGL UI | полный Wayland-ввод (Town headless уже проверен), original skins/fonts, splash/loading/settings, IME |
| Town | partial | геометрия и ходьба, подключён startup/load, частичный dispatcher, checkpoint/cache этажей | оконный интеграционный сеанс, NPC services/quests/stash, исходные interaction radius/gates |
| Save/load | partial | собственный versioned .otc, atomic+revision writes, fresh-process player/items/world/floors, corrupt slots | оригинальный формат/quest/timeline/volatile reset, backup/delete UX; v1–v4 читаются в v5, skill/quest срез large-13 сохраняется, не исходный SVB |
| Melee combat | verified | description → clip → HIT → physical damage | scheduler, factions, полный interrupt/target/damage/effects |
| Ranged/projectile | partial | direct physical HIT для обычных bows/pistols/rifles/crossbows, статическая LOS | настоящие missiles/skills, динамические препятствия, trail, полная физика |
| Enemy AI | partial | detection/chase/melee/cooldown | skill selection, flags lifecycle, factions, retarget, группы, боссы |
| Player death/restart | verified | один entry-restart с gold/10 | остальные варианты, pet, dropToGround, временные эффекты |
| HP/mana/gold | partial | base/effective HP, passive player regen, max/spend, entry fee, level growth, gold pickup/wallet/save | все остальные временные эффекты, monster/pet regen, original volatile RNG/rank, остальные difficulty, экономика |
| Loot/inventory/equipment | partial | death → drop → pickup → equip → travel | rarity, affix, все требования/слоты, прочие consumables, visuals |
| Effects/affixes | partial | passive + ограниченные finite DYNAMIC recovery, OTC таймеры | остальные lifecycle/graphs/conditions/stacking/FX |
| Skills | partial | catalog/ranks/costs и исполняемый Infuse, обучение, HIT, finite buffs, save | остальные умения, targeting/missiles/AOE, полный lifecycle/FX |
| XP/level/fame | partial | portable XP/level/growth/stat+skill points, атрибуты, HUD и save | полный CPlayer levelUp (обычный XP scalar уже сравнен), factions/spawner XP gates, fame, активные skills, полные penalties |
| Quests/dialogs | partial | catalog/requirements, ограниченные forced controller flags/events, persistence | NPC offering/dialogue, objectives/rewards/populate/pet, automatic completion, реальный campaign route |
| NPC/merchant | researched | merchant/dialog classes доступны | interaction, buy/sell, prices, stock, окна и сохранение |
| Stash/shared stash | researched | классы доступны | UI, перенос экземпляров, disk persistence |
| Enchant/combine | researched | menu/core классы доступны | рецепты, стоимость, RNG, эффекты и UI |
| Pet | researched | pet menu и player/character связи | spawn/follow/combat/inventory/send-town/transform/death/save |
| Props/chests/traps | partial | runtime entities/spawn/logic | interaction, destructible, containers, traps и специальные события |
| Audio/music | researched | sound classes декомпилированы | banks, categories, spatial playback, music states, settings |
| Particles/FX | unseen | resource names и renderer hooks | particle templates, emitters, lifetime, attachment и blending |
| UI/HUD/localization | partial | inventory/death prototype, UI audit | исходные layout, fonts, text, HUD, tooltips, action bar, settings |
| Campaign/boss progression | unseen | 35 этажей читаются | quests, bosses, gates, town returns, финал и карты после кампании |
| Android/OnePlus 7 | unseen | GLES-friendly desktop foundation | touch UI, lifecycle, packaging, assets, performance и APK |

## Исторический функциональный остаток

### Запуск и интерфейс приложения

- splash/logo/loading и переходы `GameStateController`;
- главное меню, New Game, выбор класса/имени/сложности, Continue/Load/Delete;
- пауза, настройки, возврат в меню, выход и обработка ошибок;
- оригинальные UI layout, изображения, fonts, localization и sound feedback;
- разрешение/resize/fullscreen, UI focus, keyboard/mouse/controller navigation.

### Город и основной цикл

- запуск новой игры в Town без обязательных тестовых CLI-флагов;
- прогулка, idle/run/turn, collision, navigation и камера;
- selection/highlight/approach/interaction для NPC и интерактивных props;
- вход в данж, обратный портал, stash, merchant, quest giver и сервисы;
- HUD, target frame, loot labels, уведомления и окна персонажа/предметов;
- save → завершение процесса → load реализовано для переносимого состояния; настоящий Town прошёл общим headless-loop; осталось подтвердить именно оконный слой.

### Мир и уровни

- полный набор layout commands/logic objects/timelines/triggers;
- точный глобальный scheduler и безопасная re-entrancy;
- полный original persistent level state: собственный кеш runtime-сущностей/логики уже есть, quest/timeline/volatile reset ещё нет;
- chests, doors, breakables, traps, shrines, portals и scripted encounters;
- difficulty/rank/theme/rarity sources и все special entry modes;
- кампания по всем этажам, боссы, переходы, финал и map content.

### Бой и персонажи

- ranged weapon skill, ray и missile ветви;
- projectile descriptor, muzzle/hand, sweep/LOS, collision, pierce и FX;
- все damage channels, armor/resistance, crit, block, dodge и reflection;
- factions, target filtering, sectors/AOE, interrupts, stun/knockback/debuff;
- AI flags manager, skill AI, group behavior, special monsters и bosses;
- полный player/pet death flow и все варианты восстановления.

### Эффекты, умения и развитие

- создание/clone/owner/lifetime/update/remove/serialize `CEffect`;
- affix roll, graphs, requirements, activation/conditions и visual FX;
- skill load/learn/rank/cast/cost/cooldown/event/target/missile/AOE;
- полные buffs/debuffs/timed effects, potions/consumables; passive player HP/mana regen добавлен, monster/pet lifecycle ещё нет;
- XP, level, fame, attributes, skill/stat points и death penalties;
- поддержка шаблонов всех трёх классов без ручной прошивки каждого skill.

### Предметы и экономика

- полный treasure rank/RNG/rarity и nested spawn semantics;
- `CItemGold` с difficulty graphs, world pickup и кошельком;
- требования, identification, affixes, sockets/gems, stack и consumables;
- все equipment slots, dual/two-handed rules, wardrobe/armor appearance;
- inventory grids/limits, ground placement/physics и item labels;
- buy/sell/stock/prices, enchant, combine и stash/shared stash.

### NPC, задания и питомец

- quest loader/state/requirements/rewards/dialog/markers и persistence;
- NPC interaction dispatcher и все используемые service menus;
- pet spawn/follow/path/combat/skills/inventory/equipment;
- отправка питомца в город, трансформации, death/recovery и save.

### Представление и платформа

- остальные OGRE material techniques/passes и renderer states;
- lights, shadows, particles, trails, decals, weather и screen effects;
- sound banks, positional sound, music transitions и volume categories;
- visual differential fixtures для сцен, персонажей, UI и эффектов;
- profiling, streaming/cache, стабильность долгой игры;
- после ПК-границы: Android lifecycle, touch controls, packaging и APK.

## Как уточнять остаток

Подтверждённый срез можно уточнить, когда зафиксированы источник, граница
реализации и воспроизводимая проверка; его открытые части остаются в учёте.
Полное закрытие функции принимается отдельно по `code-first.md`, включая
все различия семейства и потребителей эффектов. Наличие имени символа,
декомпиляции, загрузочного smoke или правдоподобной картинки не закрывает пункт.
Для `partial` нужно хранить рядом точный список уже доказанных и ещё открытых
ветвей, чтобы следующие проходы не повторяли выполненную работу.
