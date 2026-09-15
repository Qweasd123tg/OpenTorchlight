# Полный рабочий реестр остатка OpenTorchlight

Этот файл задаёт область следующих больших проходов. Статус относится к
поведенческой границе, а не к наличию файла декомпиляции. `verified` означает,
что доказана только явно описанная часть; это не автоматически вся подсистема.

## Сводная карта

| Область | Текущий статус | Что уже есть | Главный остаток |
|---|---|---|---|
| Архивы/ADM/UNIT/BASEFILE | verified | полный разбор исходного pak и 3343 UNIT | редкие форматы и записи, которые появятся в новых системах |
| Mesh/skeleton/animation | verified | загрузка, skinning, клипы и события | blend graph, attachments, death/special/skill состояния |
| Material/texture/render | partial | основной GLES-проход, DDS/PNG, ambient override | все passes, blend/depth/cull, particles, decals, lights, post effects |
| Камера/input/pathfinding | verified | основные формулы и A* | UI focus, drag, hotkeys, controller, специальные режимы камеры |
| Layout/random level/logic | partial | генерация, links, timer, spawn, warp | весь command set, re-entrancy, сохранение состояния, special layouts |
| Boot/game states/menu | researched | классы и UI-индексы доступны | настоящий splash/main/new/load/pause/exit flow |
| Town | partial | геометрия, сущности, collision, прогулка | городской state flow, NPC dispatcher, порталы, сервисы и сохранение |
| Save/load | researched | save-state классы декомпилированы | формат, атомарная запись, персонаж, предметы, мир, этажи, слоты |
| Melee combat | verified | description → clip → HIT → physical damage | scheduler, factions, полный interrupt/target/damage/effects |
| Ranged/projectile | researched | основные функции и точечные ASM | descriptor → spawn → flight/sweep → HIT/pierce/retire/render |
| Enemy AI | partial | detection/chase/melee/cooldown | skill selection, flags lifecycle, factions, retarget, группы, боссы |
| Player death/restart | verified | один entry-restart с gold/10 | остальные варианты, pet, dropToGround, временные эффекты |
| HP/mana/gold | partial | base/max/spend и entry fee | regen, мировой gold, difficulty/rank graphs, UI/economика |
| Loot/inventory/equipment | partial | death → drop → pickup → equip → travel | rarity, affix, requirements, все слоты, stack, consumables, visuals |
| Effects/affixes | partial | каталог и ограниченные constant passive | полный lifecycle, graphs, conditions, stacking, FX, serialization |
| Skills | researched | центральные классы декомпилированы | data loader, controller, costs, cooldown, targeting, missiles/AOE |
| XP/level/fame | unseen | отдельные поля/символы известны | начисление, growth, points, UI, penalties, serialization |
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
- save → завершение процесса → load с тем же доказанным состоянием.

### Мир и уровни

- полный набор layout commands/logic objects/timelines/triggers;
- точный глобальный scheduler и безопасная re-entrancy;
- persistent level state для покинутых этажей;
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
- mana/health regeneration, buffs, debuffs, potions и consumables;
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
