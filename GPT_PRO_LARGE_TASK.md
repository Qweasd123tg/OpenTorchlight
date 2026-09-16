> Состояние после продолжения large-8: см. `PROGRESSION_REWARDS_RESULT_RU.md`
> и `NEXT_CHECKS.md`. Ниже сохранена исходная широкая постановка large-7.
> Утверждение о наличии pak описывало предыдущую среду: в текущей передаче
> был только ZIP проекта. Новые assets/reference/full-scene проверки не запускались.

# Максимальный этап large-7: играбельная кампания поверх готового стенда

Работай поверх `OpenTorchlight-gpt-pro-large-7.zip`. Это снова большой единый
проход: разрешено менять весь проект и реализовывать много связанных подсистем.
Не останавливайся после одной константы, функции или узкого патча. Если одна
граница заблокирована, зафиксируй минимально недостающие адреса и продолжай
следующую независимую часть.

Главная цель — довести игру до **играбельной кампании**, а не до новой
инфраструктуры. Автоматический стенд large-6 уже принят интегратором и должен
оставаться зелёным; его нужно использовать и точечно расширять под новые
цепочки, а не строить заново.

Сначала прочитай `AGENTS.md`, `README.md`, `NEXT_CHECKS.md`,
`AUTOMATED_VERIFICATION_RESULT_RU.md`, `research/automatic-verification.md`,
`research/remaining-work-inventory.md`, `research/parent-dungeon-boundary.md`,
`research/frontend-save-evidence.md`, `research/checkpoint-format.md`,
`research/gameplay-continuation.md`, `research/ordinary-attack-action.md`,
`research/item-cycle.md`, `tools/check.py`, `tests/scenarios/`,
`src/application.cpp`, `include/torchlight/application.hpp` и профильные
`research/decompiled-core/`. Исторические задания и отчёты сохранены в
`research/reviews/`.

## Подтверждённая исходная точка (large-6 принят)

- Патч large-6 применён интегратором; дерево побайтово совпало с выданным ZIP,
  559/559 записей `CHECKSUMS.sha256` валидны, промоушенов статусов coverage нет.
- Независимый прогон интегратора на настоящем pak и закреплённом ELF:
  **core 33/33, assets 29/29, render 5/5, reference 9/9**. Сценарный прогон:
  7 процессов, 41 утверждение, точный повтор 33 файлов, Town → Main:1 → Town.
- В среде внешнего исполнителя есть настоящий pak
  SHA-256 `8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`,
  но нет ELF. Группы `--core --assets --render` обязаны остаться зелёными;
  `--reference` запускает интегратор, не заявляй его выполнение.
- `src/application.cpp` — единственный общий игровой цикл для окна и сценариев.
  Не создавай второй рантайм и не «исправляй» мир в тестовом host.

## Главная цель этапа

Сквозная играбельная кампания: New Game любым из трёх классов → Town с
работающими сервисами → подземелья с развитием персонажа и предметами → все
этажи кампании, боссы, финал → save/load переносит всё достигнутое состояние.
Промежуточный ориентир: обычный игрок может пройти значительный участок без
ручных правок и заглушек.

## Приоритет 1: бой и эффекты — фундамент для всего остального

1. Полный lifecycle `CEffect`: create/clone/owner/lifetime/update/remove,
   passive и dynamic, conditions/graphs/stacking/removal, все damage channels,
   armor/resistance, crit/block/dodge/reflection. Сначала интерпретатор данных,
   затем подключение к игроку, монстрам и предметам.
2. AI flags manager, factions, target filtering, skill selection, retarget,
   группы; не подменяй это глобальным ускорением монстров.
3. Ranged/projectile по доказанным адресам: `performAttack @0x00847280`,
   `fireMissiles @0x0087f120`, `CWeaponMissileDescriptor @0x00602dc0`,
   producer `equipment+0x400`, hand/muzzle offset `0.8`, pitch `5.0`,
   resource/velocity, sweep/LOS, owner/ignore list, pierce/retire, HIT
   attribution, очистка при смерти/смене уровня и представление в renderer.
   Не превращай ranged в мгновенный melee и не стреляй сквозь стены.
4. Interrupt, AOE/секторы, stun/knockback/debuff, полные death-события игрока,
   монстров и питомца.

## Приоритет 2: развитие персонажа и умения

1. XP/level/fame/attributes/stat и skill points, level-up, доказанные death
   penalties; сохранение и отображение этих чисел.
2. Универсальный skill pipeline: loader/learn/rank/cast/cost/cooldown/animation
   events/target/missile/AOE. Все три класса — через шаблоны данных, без
   прошивки отдельных умений по именам.
3. Mana/health regeneration, buffs/debuffs, potions и расходники.
4. Классовые механики (например, заряды/специальные ресурсы), если они есть в
   данных; иначе — явная граница, а не выдуманная механика.

## Приоритет 3: предметы и экономика

1. `CItemGold::unitInit @0x008ca940` и мировой gold: difficulty/rank/floor
   graphs, no-loot вход, pickup → кошелёк.
2. Полный treasure rank/RNG/rarity и вложенные spawn semantics; affix roll,
   требования, identification, sockets/gems, stack, consumables.
3. Все equipment slots, dual/two-handed правила, wardrobe/armor appearance.
4. Inventory grids/limits, ground placement и метки предметов.
5. Merchant buy/sell/stock/prices, enchant, combine, stash/shared stash — каждый
   сервис по цепочке resource → requirement → UI → операция → checkpoint.

## Приоритет 4: NPC, квесты, питомец

1. Interaction по доказанным границам: `CCharacter::inInteractionRange
   @0x008244a0` с тремя f32 по `0x00fce4b8/bc/c0`, `CInteract::interactWithUnit
   @0x00986ff0`, `CTriggerUnit::interact @0x009095c0` и producer quest/key
   requirements. Сохрани re-check на arrival и отсутствие повторного dispatch.
2. Quest loader/state/requirements/rewards/dialog/markers/persistence.
3. NPC services добавляй по одному сквозному сервису, не назначай сервис по
   имени NPC.
4. Питомец: spawn/follow/path/combat/skills/inventory/equipment/send-town/
   transform/death/recovery/save.

## Приоритет 5: мир, этажи и кампания

1. Полный набор layout commands/logic objects/timelines/triggers, безопасная
   re-entrancy, persistent level state посещённых этажей.
2. Chests, doors, breakables, traps, shrines, portals, scripted encounters.
3. Difficulty/rank/theme/rarity sources и специальные entry modes.
4. Focused ASM parent-route: `CDungeon::loadDungeon` и
   `performWarp @0x0058d110` — преврати `resource-derived/inferred` привязку
   `CDungeon+0x80` к `PARENT_DUNGEON` в проверенную границу.
5. Все 35 этажей кампании, боссы, gates, возвраты в Town, финал и map content;
   переходы `LASTDUNGEON`/absolute/relative, volatile floors.

## Приоритет 6: представление и платформа

1. HUD: HP/mana/XP, action bar, target frame, loot labels, уведомления,
   tooltips, окна персонажа/умений/заданий. Оригинальные layout и fonts — где
   поддержаны; прототипное явно помечай.
2. Audio: banks/categories, позиционный звук, music states, настройки.
3. Particles/FX, trails, decals, lights/shadows, остальные material passes.
4. Localization/тексты, настройки, splash/loading.
5. Android lifecycle/touch/APK — только после подтверждённой ПК-границы.

## Стенд: как пользоваться и что расширять

- Держи `--core --assets --render` зелёными на настоящем pak. Не поднимай
  допуски и не отключай проверки ради нового контента.
- Для каждой новой цепочки добавляй pak-only или сценарную проверку:
  бой → HIT → loot → pickup/equip, ranged, cast скилла, quest reward,
  транзакция торговца, питомец, переходы этажей, level-up.
- Расширяй `tests/scenarios/*.scenario` и `application_scenario_probe`; новые
  команды должны идти через реальные обработчики, без телепортов и обходов.
- `.otc` дополни новыми состояниями (skills/quests/pet/timeline) с версией и
  строгой валидацией; не заявляй совместимость с оригинальным .SVB.
- `--desktop` harness и живые original traces — по остатку времени; лучше
  закрытая игровая вертикаль, чем незавершённый compositor.
- Не выдавай собственные регрессионные дампы за эталон оригинала.

## Приоритеты и правило незавершённых ветвей

Порядок выше задаёт последовательность, а не предел: если предыдущая группа
достигла воспроизводимой границы, продолжай следующую. Лучше большая
законченная вертикаль (например, полный цикл боя → эффекты → прокачка),
чем множество полусырых заглушек. Для каждой подсистемы указывай, что именно
доказано, а что осталось.

## Правила исследования и реализации

1. Сначала ресурсы, символы, RTTI, функции и адреса оригинала, затем код.
2. Каждое существенное утверждение помечай `original-code`,
   `resource-derived`, `library-derived`, `inferred` или `prototype`.
3. Сначала минимальный дамп/чистая функция/differential test, затем runtime.
4. Сравнивай числа, состояния и последовательности событий. Внешнее сходство и
   загрузочный smoke не доказывают поведение.
5. Не создавай огромную ABI-имитацию ради тесно связанной функции: выделяй
   чистые части, остаток проверяй короткой трассировкой.
6. Оригинальные ELF и ресурсы только read-only. Не включай их в результат и не
   создавай полный дамп программы; добавляй только точечные экспорты.
7. Сохраняй `-Wall -Wextra -Wpedantic -Werror`; не отключай предупреждения и не
   ослабляй прежние проверки. Не удаляй и не переименовывай существующие тесты
   без сохранения их покрытия.
8. Универсальные интерпретаторы данных вместо правил по именам предметов,
   монстров или умений. Не оставляй необъяснённых констант, влияющих на
   поведение: рядом путь ресурса, функция и адрес оригинала либо явный
   `prototype` с задачей на проверку.

## Проверки и результат

- Сохрани принятые группы: `--core --assets --render` зелёные на настоящем pak.
- Добавь проверки для каждой новой цепочки, включая отказ, повтор, смерть,
  смену уровня и восстановление состояния после save/load.
- Обнови `research/coverage.tsv` только по доказанным границам и обнови
  `remaining-work-inventory.md` с точным списком закрытого и открытого.

Верни **один авторитетный полный ZIP** проекта, cumulative patch к
`large-7` и подробный русский отчёт: что стало играбельно end-to-end, что
осталось, какие проверки это подтверждают. Не возвращай несколько
конкурирующих `patched/fix` архивов. В ZIP не должно быть ELF, `pak.zip`,
`build/`, собранных бинарников или полного дампа. Если всё не помещается в
один проход, сделай максимально большой законченный участок и продолжи по
приоритетам, а не растягивай один scalar-fix.
