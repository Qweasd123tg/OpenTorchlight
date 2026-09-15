# Следующий проход после gameplay-continuation (large-4)

Актуальная реализация и границы: `GAMEPLAY_CONTINUATION_RESULT_RU.md` и
`research/gameplay-continuation.md`. Исходное максимальное задание остаётся в
`GPT_PRO_LARGE_TASK.md`; оно выполнено частично, не закрыто как «вся игра».

## Проверенная база этого патча

Локальный интегратор собрал полный desktop GCC 16 и провёл 59/59 тестов с
настоящими ELF и `pak.zip`. `original_player_vitals_comparison` дал 6497
совпадений; original combat/AI/item cycle, GLES и рендеры также прошли.
Оконный executable загрузил Main:1 и отрисовал три кадра. Ручной полный
combat/death/R/loot/equip/warp сценарий ещё не выполнен.

## Главная цель следующего large-5

Следующий проход должен дать видимый цикл: стартовое меню → New Game/Load →
выбор героя → настоящий Town → свободная прогулка и базовые взаимодействия →
save → выход → загрузка того же состояния. Использовать оригинальные UI/layout
ресурсы и state controller; временные элементы явно помечать `prototype`.

Приоритет включает живой городской HUD, collision/navigation, NPC/порталы,
stash/merchant/quest dispatcher и сквозной save/load. Ranged переносится на
следующую позицию после работающего визуального городского цикла. Полный объём и
обязательная карта непокрытых функций описаны в `GPT_PRO_LARGE_TASK.md`.
Исчерпывающий рабочий перечень подсистем находится в
`research/remaining-work-inventory.md`; весь этот список разрешён в одном проходе.

## Сначала проверка настоящей интеграции

`bash tools/check.sh "$GAME_DIR"`, затем ручной combat/death/R/loot/equip/warp.
Проверить разные точки reverse Warper и level entry, gold/10, HP/mana, сохранение
мира и отсутствие stale HIT. Начальный boot/special entry может иметь prototype
anchor; это видно в логе `original_entry_anchor=0`. Не интерпретировать три
отрисованных кадра как доказательство этого сценария.

## Выполненный независимый ресурсный шаг

`tools/dump_original_gameplay_inputs.py` выполнен на SHA-проверенном ELF;
результат сохранён в `research/original-gameplay-inputs.json`.

Получены только строки по VA 0xfd1e98, 0xfd1ec0, 0xfd1f48, 0xfd1f80, 0xfd1f20,
0xfd1ee8, 0xfc2078 и f32-операнды 0xfa86d0/0xfc676c. Не угадывать названия
gold-percent ключей, графов, layout no-loot или значения muzzle/ray operands.
Следом — `CItemGold::unitInit/getItem` и программный drops_loot к реальному
layout-свойству. Отдельно проверить rank/difficulty источники, прежде чем считать
номинал денег или состав добычи совпадающими.

## Следующая после визуального цикла связка: ranged

`performAttack @0x847280` различает weapon skill/missile и ray fallback.
Проследить producer equipment+0x400, CWeaponMissileDescriptor `0x602dc0`, hand tag,
выбор resource/скорости/радиуса/числа пробитий. Затем flight → collision sweep →
HIT/retire с кастером и повторным попаданием, привязка к анимации и desktop.
Нельзя снять existing unavailable gate и выдать ranged за melee сквозь стены.
Точечные exports уже лежат в `research/disassembly/`; полного дампа не нужно.

## Остальные границы

AI flag1 — пока явно оценённый потребитель скорости, не менеджер флагов. Нужны
производители/сроки/interrupt/alignment, исходный глобальный scheduler и faction
semantics. Далее реальные skills/mana regen, XP/level, временные эффекты, все
режимы смерти/pets/dropToGround, дисковое сохранение и кеш покинутых этажей.
Текущая paused-death UI и безопасная deferred death-фаза обозначены prototype;
совпадение глобальной re-entrancy не заявлено. При resource failure в loot drain
нет rollback частично созданной смерти: это остаётся явной ошибкой, не повторным roll.
