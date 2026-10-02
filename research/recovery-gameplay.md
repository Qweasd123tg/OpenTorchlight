# Автоматическое исполнение принятых gameplay-контрактов

2026-10-02. `original-code` для перечисленных ASM и read-only ELF с SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Это перенос проверенных численных адаптеров в производственный путь, а не
автоматическое восстановление неизвестных функций по сходству.

## Исходные функции и граница

Полные symbol/address/size/body SHA находятся в `recovery-contracts.json` и
повторно проверяются `tools/generate_recovered.py`. Whole-body hash устанавливает
идентичность входа; `scalar_spans` явно ограничивает перенос ветви внутри
более широкой функции. Генерация не повышает legacy stages или completion.

| Семейство | Проверенный источник | Производственный путь | Остаток |
|---|---|---|---|
| Скорость движения | walkingSpeed 0x815a20 / runningSpeed 0x815ad0, size 0xa6 каждый; тело прочитано целиком, отличие base +0x28c/+0x290 | generated movement_speed → character_stats → PlayerCombatState / EnemyController → ActorMotion / movement | Оригинальный effect manager, обновление базовых полей и весь motion lifecycle |
| DEF / физическая AC | defense 0x814530 size 0x85; armorBonus 0x8145c0 size 0xae; AC 0x814670 size 0x61; тела прочитаны целиком | generated bonuses → character_stats → typed_damage / health state → mitigation at HIT | Жизненный цикл effects/inventory/master; элементальные защиты принадлежат отдельному переносу |
| Скорость атаки | attack owner 0x82b550; 0x82b976..0x82b9c5, 0x82bcea..0x82bd46; множитель 0x82b9e1..0x82b9e9 | generated attack_speed → ordinary_attack_speed → player/enemy attack action → clip/HIT playback | Выбор описания, AI flag ownership и все другие ветви attack не закрыты этим рецептом |
| AI cooldown | attackAI owner 0x8dfd80, scalar 0x8e00e6..0x8e013d; updateAI owner 0x8e3a40, scalar 0x8e3a5b..0x8e3a6f | generated cooldown_tick/arm → MonsterAiCooldown → EnemyController | Think scheduling, factions, flags и остальные ветви AI |
| Конечное восстановление | getEffectValue owner 0x7eb5f0; mulss 0x7eb7a0..0x7eb7a6 для конечного эффекта | generated finite_recovery_rate → consumable → PlayerSession active recovery / inventory tooltip | Cache, duration dispatch, накопление и lifetime оригинального manager |
| Численность | getNumberOfUnitsToCreate 0x971530 size 0xaf; тело прочитано целиком | generated population_count → EntityWorld::populate → существующая placement/entity chain | Оригинальная инициализация indexed template fields и генерация всех секций; placement имеет отдельную границу |
| Золото / XP | CItemGold::unitInit owner 0x8ca940, scalar 0x8cad46..0x8cad5b; CCharacter::setLevel owner 0x83ead0, scalar 0x83ecea..0x83ecfd | generated products → progression → EntityWorld resolved rewards → PlayerSession pickup/award/save | Dungeon-rank и volatile stream ownership, остальные setLevel/champion/party/fame ветви |
| Barter | buyPrice 0x86fc20 size 0xe9 / sellPrice 0x86fb40 size 0xd9; тела прочитаны целиком, перенос вычисленного вклада | generated barter_amount → economy buy/sell API → PlayerSession purchase/sale/rebuy → Application/shop/wallet/NPC stock | Nullable manager/level/player и original effect manager; normal identified potion sale/rebuy подключён в [merchant-sale-buyback.md](merchant-sale-buyback.md), прочие item/merchant branches остаются открыты |

Общий диапазон: конечные binary32 входы, целочисленные промежуточные результаты
в поддерживаемой int32 области. Portable wrappers сохраняют свои проверки и
ошибки для невалидных входов; это `prototype` safety boundary, не заявленная
семантика NaN/infinity/overflow оригинала. Исключение: RNG-рецепт отдельно
разбирает equal/unordered dispatch в `recovery-automation.md`.

## Общие поля семейства и порядок

| Исходное поле / dependency | Тип и ширина | Адаптер / владельцы |
|---|---|---|
| character +0x28c / +0x290 | float32 WALKINGSPEED / RUNNINGSPEED | base speed из UnitDefinition/PlayerPrototype/RuntimeEntity; slow effect 0x15 применяется перед mul→div→add |
| character +0x430 | int32 DEF | raw defense в combat state/checkpoint; effect 0x11 damage-type 7 затем 6, percent складываются перед делением, ceil; flat effect 2 ceil отдельно |
| character +0x424; inventory +0x10 | два int32 natural/inventory armor | caller передаёт их оценённую сумму; generated percent bonus не меняет raw сохранённые поля |
| character +0x490 / +0x640 | 64-bit inventory / nullable master pointers | Порт передаёт уже вычисленные armor inputs; original pointer alias/owner lifecycle не эмулируется |
| selected description +0x70 | float32 SPEED denominator | AttackDescription; slow resistance 0x8c действует только на отрицательный effect 0x16; minimum 0.2 применяется до AI multiplier 1.5 |
| monster +0x7e8 / +0x7ec; selected equipment +0x408 | float32 remaining / UNIT cooldown / equipment cooldown | MonsterAiCooldown владеет signed remaining; update всегда вычитает dt; после успешного attack сначала max+equipment, затем отдельный max+unit |
| template +0x634/+0x638 + 8*section; +0x5dc/+0x5e0 + 8*section | четыре float32 count/density | PopulationSettings; integer-count ветвь имеет приоритет, сортирует и trunc границы; density требует обе >0, area = uint32 nodes / 6.5, затем randomBetween и ceil |
| effect +0xc0 / +0x24 / +0x1c / +0x14 | float32 value/duration; int32 effect/damage types | ActiveRecovery передаёт value после собственного validation; oracle моделирует один concrete effect типов 6/7/123/124 |
| equipment +0x238; +0x264/+0x268/+0x26c/+0x270; +0x348 | int32 stack, четыре int32 цены, byte identified | Economy wrapper выбирает цену/stack и identified gate; contribution trunc до int32; buy clamp минимум 1, sell без такого clamp |

Новые рецепты не назначают исходным полям придуманные initial values. Их
оригинальные constructor/unitInit contracts не закрыты этим пакетом. Порт
продолжает получать базовые значения из прежних resource/checkpoint loaders;
numeric adapters не создают владельцев и не меняют порядок работы этих loaders.

`resource-derived` значения и IDs загружаются существующими каталогами effects,
UNIT, graphs и level rules. Базовые float32 константы 0/1/100/0.016/0.2/1.5/6.5
извлекаются из ELF по адресам и точным четырём bytes; generated hex-float
литералы сохраняют эти биты. Host `ceilf` служит явно указанной библиотечной
границей original probes; оригинальный libm runtime целиком не восстановлен.

Порядок операций сохраняется: movement mul→div→add; defense сначала add двух
percent; armor каждый percent div отдельно; XP (g/100)*g; gold graph*(p/100).
Перестановка, FMA/fast-math, epsilon, новые clamps или seed defaults не вводятся.
Negative intermediate movement overflow проверяется до zero clamp.

## Проверки и общий маршрут

Existing original probes исполняют неизменённые функции/участки в private
memory и сравнивают real production API: character_stats, gameplay_numeric,
attack_speed, ai_cooldown, world_gold, monster_experience, economy. Зависимости
effect getter / getPlayer / ceilf моделируются явно; original game не запускается.
Attack speed сравнивает false/true flag inputs; multiplier исполняется его
неизменёнными ASM bytes после original base/minimum результата.

`tools/check.py --recover /path/to/game` генерирует все принятые recipes и
автоматически берёт все зарегистрированные core/assets/reference tests из
CMake. Его build closure включает CPU executables/shared probes и их Ninja
dependencies, включая generated bodies и fixtures. Отчёт группирует тесты по
системам; это port-native categorization по именам, а не карта закрытия функций.
Неклассифицированные новые проверки остаются видны в other_cpu_contracts.

Resources, inventory/loot/economy, progression/quests, character/vitals,
combat/skills, world generation, input/navigation/camera, save migration и
UI/audio contract checks проходят одним запуском. UI clicks, screenshot/frame
scenarios и performance measurements сохраняются отдельными задачами.
Conditional отсутствующие CMake checks не становятся проверенными возможностями:
граница отчёта — registered-cpu-resource-reference, не вся исходная игра.

## Наблюдённое сравнение с оригиналом

В исходном расширенном прогоне reference group выполнила 23/23 проверки без
skip. Ниже результаты затронутых численных APIs; bit/state comparisons относятся
к указанным конечным областям и synthetic dependency boundaries.

| Проверка | Результаты |
|---|---:|
| Character movement/DEF/physical AC | 21 696 |
| Attack speed, оба flag-one inputs | 24 784 |
| AI cooldown rearm/tick | 42 739 |
| Finite recovery scale | 10 040 |
| Population count + post-call RNG state | 10 055 |
| World gold scalar | 10 107 |
| Monster XP scalar | 20 031 |
| Buy/sell scalar | 20 600 |

Assets group прошла 64/64. Общий прогон также обнаружил две ранее не включённые
в UI/RNG chain ошибки core harness. Syntax-only компилятор теперь получает
effective includes, SYSTEM includes и definitions самого torchlight_core из
CMake; проверка приложения сохраняет warnings-as-errors для своего кода.

Frozen v1 checkpoint использует свой companion authored pak, восстановленный
из четырёх fixture generators commit `63c0962bb160f4eed081d7cfa694846232695962`.
Исходный `checkpoint-v1.hex` не изменён. `tests/fixtures/checkpoint-v1-resources.zip`
содержит только авторские тестовые ресурсы, с фиксированными ZIP metadata;
provenance и source SHA находятся в одноимённом JSON. Хеш archive проверяется
до двух native read процессов и upgrade. Тест снова проходит с обычной
resource-identity проверкой; несовместимые игровые пакеты не разрешаются.
