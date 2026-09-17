# Полный рабочий реестр остатка OpenTorchlight

Этот файл задаёт область следующих больших проходов. Статус относится к
поведенческой границе, а не к наличию файла декомпиляции. `verified` означает,
что доказана только явно описанная часть; это не автоматически вся подсистема.

## Изменение large-11 (донор fresh)

Добавлены пассивная регенерация игрока из GLOBALS/эффектов, maxHP экипировки и
разделение base/effective HP, сохранение v3 с настоящими v2 migration-fixtures.
Core 49/49; выбранные ASan/UBSan 11/11; настоящий pak/ELF здесь не проверялся.
Обычная XP-формула была подтверждена интегратором ранее, до fresh; прежнее
утверждение «XP producer inferred» ниже является историей large-8.
Нет полного timed-effect/potion pipeline, восстановления HP монстров/питомца,
skills/ranged/population/quests/торговли/pet/кампании. Приоритеты и критерии
завершения: `../FULL_GAME_ROADMAP_RU.md`.

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

| Область | Текущий статус | Что уже есть | Главный остаток |
|---|---|---|---|
| Архивы/ADM/UNIT/BASEFILE | verified | полный разбор исходного pak и 3343 UNIT | редкие форматы и записи, которые появятся в новых системах |
| Mesh/skeleton/animation | verified | загрузка, skinning, клипы и события | blend graph, attachments, death/special/skill состояния |
| Material/texture/render | partial | основной GLES-проход, DDS/PNG, ambient override | все passes, blend/depth/cull, particles, decals, lights, post effects |
| Камера/input/pathfinding | partial | ранее сравненные формулы/A*, frontend focus и save-position validation | тонкая стенка между центрами grid cells, drag/controller, специальные режимы, original collision fidelity |
| Layout/random level/logic | partial | генерация, links, timer, spawn, warp | весь command set, re-entrancy, сохранение состояния, special layouts |
| Boot/game states/menu | partial | frontend New/Load/Continue/pause/save/exit, XML geometry/bindings/images, проверка реального EGL UI | полный Wayland-ввод (Town headless уже проверен), original skins/fonts, splash/loading/settings, IME |
| Town | partial | геометрия и ходьба, подключён startup/load, частичный dispatcher, checkpoint/cache этажей | оконный интеграционный сеанс, NPC services/quests/stash, исходные interaction radius/gates |
| Save/load | partial | собственный versioned .otc, atomic+revision writes, fresh-process player/items/world/floors, corrupt slots | оригинальный формат/quest/timeline/volatile reset, backup/delete UX; v1/v2→v3 поддержан; настоящий pak проверялся до этого прохода |
| Melee combat | verified | description → clip → HIT → physical damage | scheduler, factions, полный interrupt/target/damage/effects |
| Ranged/projectile | researched | основные функции и точечные ASM | descriptor → spawn → flight/sweep → HIT/pierce/retire/render |
| Enemy AI | partial | detection/chase/melee/cooldown | skill selection, flags lifecycle, factions, retarget, группы, боссы |
| Player death/restart | verified | один entry-restart с gold/10 | остальные варианты, pet, dropToGround, временные эффекты |
| HP/mana/gold | partial | base/effective HP, passive player regen, max/spend, entry fee, level growth, gold pickup/wallet/save | timed effects/potions, monster/pet regen, original volatile RNG/rank, остальные difficulty, экономика |
| Loot/inventory/equipment | partial | death → drop → pickup → equip → travel | rarity, affix, requirements, все слоты, stack, consumables, visuals |
| Effects/affixes | partial | каталог и ограниченные constant passive | полный lifecycle, graphs, conditions, stacking, FX, serialization |
| Skills | researched | центральные классы декомпилированы | data loader, controller, costs, cooldown, targeting, missiles/AOE |
| XP/level/fame | partial | portable XP/level/growth/stat+skill points, атрибуты, HUD и save | полный CPlayer levelUp (обычный XP scalar уже сравнен), factions/spawner XP gates, fame, активные skills, полные penalties |
| Quests/dialogs | researched | quest классы декомпилированы | loader, requirements, state machine, dialog, rewards, persistence |
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

## Полный функциональный остаток

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

## Правило исключения из остатка

Пункт убирается из активного остатка только когда зафиксированы источник,
граница реализации и воспроизводимая проверка. Наличие имени символа,
декомпиляции, загрузочного smoke или правдоподобной картинки не закрывает пункт.
Для `partial` нужно хранить рядом точный список уже доказанных и ещё открытых
ветвей, чтобы следующие проходы не повторяли выполненную работу.
