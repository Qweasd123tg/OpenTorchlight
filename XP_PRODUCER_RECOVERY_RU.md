# OpenTorchlight: интеграция large-8 и восстановление XP producer

## Результат прохода

Large-8 принят на машине интегратора: патч `large-7 → large-8` применён к
репозиторию, дерево совпало с выданным ZIP, манифест `CHECKSUMS.sha256`
пересчитан. Настоящие read-only `pak.zip` и ELF доступны, поэтому выполнено то,
что авторская среда large-8 не могла: полный прогон групп и адресная сверка
обычного XP producer.

Главное изменение кода: порт переведён с `inferred` формулы
`trunc(g * XP / 100)` на машинно-подтверждённую
`trunc((g / 100) * g)`. Ghidra-вывод, который прошлый проход считал
повреждённым, оказался верным.

## Входы и хеши

```text
ZIP large-8          a8ff6bdfe6bcc124fe79c799036460bfee2449b29bfcd152c18836155ab3f3d6
patch large-7→8      ad60c30bbe454e1cd15a50793b7772e7178e1ee244bc174ea009557458917b86
pak.zip              8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8
Torchlight.bin.x86_64 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
```

## Восстановленный XP producer

`original-code`, закреплённый ELF:

* `CCharacter::unitInit` @`0x852c48` кладёт значение свойства данных `XP` в
  `+0x454`, после чего @`0x852b50` вызывает виртуальный `setLevel(level, true)`
  (слот `+0x318`).
* `CCharacter::setLevel` @`0x83ecdd..0x83ecfd`: `cvtsi2ssl level; call
  CGraph::getValue(level, 0); movaps; divss [0xfa483c = 100.0f]; mulss; cvttss2si;
  mov [this+0x454]`. Поле `XP` не участвует в арифметике — только в проверке
  `+0x454 != 0`.
* `CCharacter::makeChampion` @`0x85191b..0x85192e` повторяет тот же скаляр для
  `EXPERIENCE_CHAMPIONMONSTER[_difficulty]`.
* `CCharacter::awardExperience` @`0x822850` принимает у жертвы `+0x454` и
  добавляет `ceil(amount * effect0x44% )`.

Кривые данных подтверждают квадратичный замысел: `EXPERIENCEGATE` растёт
квадратично, а число убийств на уровень при `g²/100` держится около 54→60 за
54 уровня против 54→379 у линейной формулы.

## Изменения

* `include/torchlight/progression.hpp`, `src/progression.cpp`:
  `inferred_monster_experience(value, percent)` заменена на
  `original_monster_experience(graph_value)` с точным порядком операций
  `(g / 100.0f) * g` и прежней проверкой диапазона int32.
* `src/entity_world.cpp`: поле `XP` используется как ненулевой гейт; отсутствие
  графа по-прежнему даёт unknown, а не выдуманное число.
* Тесты: обновлены `reward_resource_probe`, `reward_cycle_test` (403 вместо 251
  на авторской фикстуре), добавлены `monster_experience_probe` и
  `compare_monster_experience.py`.
* CMake: новые CTest `monster_experience_export_comparison` (авторская выгрузка)
  и `original_monster_experience_comparison` (`--original`, закреплённый ELF).
  Таймаут `original_random_levels` поднят с 240 до 600 с: одиночный прогон
  ~216 с, при параллельной нагрузке он один раз упёрся ровно в 240 с.
* Документы: `research/progression-and-world-rewards.md`,
  `NEXT_CHECKS.md`, README.

## Проверки

| Проверка | Результат и граница |
|---|---|
| Полный набор на настоящих pak+ELF | **core 41/41, assets 30/30, reference 11/11, render 5/5** |
| desktop | NOT RUN: нет тестового композитора |
| XP scalar на выгрузке | **20 031 совпадение**, неизменённые байты `0x83ecea..0x83ecfd` |
| XP scalar на ELF | то же, SHA-закреплённый ELF и делитель `100.0f` проверены |
| `original_progression_resource_graphs` | PASS: настоящие графы трёх классов |
| `original_world_gold_comparison` | PASS, как и раньше |
| Формула `g²/100` | `original-code` скаляр; не весь `setLevel` и не award-flow |

Диапазон проверки: `g²/100` остаётся в int32 при `g ≤ ~463 409`; сравнение
ограничено этим доменом, выход за диапазон порт отвергает исключением.

## Открытые границы

`CPlayer::levelUp @0x8f9ad0`, spawner give-XP гейты и атрибуция владельцу,
реальный `CLevel+0x1a8`, volatile RNG золота, champion/fame пути, партия,
питомец. Динамическая смена уровня монстра не моделируется: portable-мир
считает награду один раз при спавне по своему `spawn_level`, оригинал
пересчитывает её на каждом `setLevel`. Полная кампания, активные умения,
regen, ranged и NPC-сервисы не заявляются.

Следующий блок — по [NEXT_CHECKS.md](NEXT_CHECKS.md): `CPlayer::levelUp`,
spawner-атрибуция и volatile RNG, затем активные skills/effects/projectiles.
