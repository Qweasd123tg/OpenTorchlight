# Карта исходников и оригинальных функций — large-15

Строки относятся к финальным файлам large-15. При другой базе искать по сигнатуре и проверять diff; не вставлять код только по номеру строки. Полные патчи и changed-files находятся во внешнем patchset.

## Переносимый код

| Файл и строка | Назначение | Якорь |
|---|---|---|
| `src/character_stats.cpp:29` | Скорость и сопротивление замедлению | `float evaluated_movement_speed(float base, float percent` |
| `src/character_stats.cpp:41` | DEF, два исходных канала | `std::int32_t evaluated_defense_attribute(std::int32_t base,` |
| `src/character_stats.cpp:50` | armorBonus → AC | `std::int32_t evaluated_physical_armor` |
| `src/attack_action.cpp:134` | Приём только фиксированного SAVE-эффекта | `AttackEffects load_constant_attack_effects` |
| `src/attack_action.cpp:185` | Общее ограничение известной неподдержанной доставки | `bool ordinary_delivery_supported` |
| `src/actor_motion.cpp:24` | Смена скорости без потери маршрута | `void ActorMotion::set_speed` |
| `src/application.cpp:1023` | Команда HUD в общей ветви MouseButtonDown | `window.notice("hud_dispatch_down"` |
| `src/application.cpp:1201` | Подключение скорости к общему игровому циклу | `player_motion.set_speed` |
| `src/application.cpp:524` | Release: явно инициализированный ID | `std::uint64_t merchant_entity = 0` |
| `src/application.cpp:543` | Release: явно инициализированный ID | `std::uint64_t active_pickup = 0` |
| `src/enemy_ai.cpp:151` | Отделение классового flat-roll от сырого base | `std::int32_t PlayerCombatState::physical_armor` |
| `src/enemy_ai.cpp:163` | Итоговые эффекты скорости персонажа | `float PlayerCombatState::movement_speed` |
| `src/enemy_ai.cpp:168` | Безопасный пересчёт экипировки/AC | `void PlayerCombatState::refresh_damage_defense` |
| `src/enemy_ai.cpp:187` | Применение AC без второго DEF | `std::int32_t PlayerCombatState::apply_damage` |
| `src/enemy_ai.cpp:224` | Реальное движение врага | `bool EnemyController::advance_toward_player` |
| `src/checkpoint.cpp:304` | Восстановление класса без нового roll | `const auto armor_bonus =` |
| `src/combat.cpp:129` | Учет AC и эффектов монстра на HIT | `defense.natural_armor = evaluated_character_armor` |
| `src/equipment.cpp:164` | Binary32, ceilf, минимум только для брони | `std::int32_t item_graph_stat` |
| `src/equipment.cpp:277` | RNG перед наследованным MAX | `WeaponItem roll_weapon_item` |
| `src/ui_hud.cpp:37` | Поиск callback на нажатии | `hud_press_callback` |
| `tests/character_stats_test.cpp:46` | Один roll, прежние HP/mana/RNG, снятие | `void verify_restored` |
| `tests/character_stats_test.cpp:76` | Атомарность отказов low-level API | `Public low-level setters` |
| `tests/combat_test.cpp:109` | Отказ от подмены посоха оригинального алхимика | `unsupported_damage` |
| `tests/item_graph_test.cpp:8` | Авторские регрессии формулы предметов | `int main` |
| `tests/compare_character_stats.py:34` | Исполнение пяти оригинальных функций | `class Native` |
| `tests/compare_item_graph.py:23` | Исполнение оригинальных item graph функций | `class Native` |
| `tests/gameplay_catalog_probe.cpp:13` | Каталог через текущий наследующий loader | `int main` |
| `tests/gameplay_before_after_probe.cpp:9` | Одинаковый probe для старой и новой библиотеки | `int main` |
| `src/player_session.cpp:334` | Существующая связь эффектов экипировки/умений с derived stats | `void PlayerSession::refresh_effect_contributions` |
| `src/population.cpp:114` | Точный статус полного перемешивания prototype | `Fisher` |

## Оригинал

Pinned ELF: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. Полный хеш каждого тела — в `verification/large-15/original-symbols.json`. Декомпиляция ниже служит навигацией; численные утверждения проверяются инструкциями, не типами псевдокода.

| Символ | ELF-адрес | Навигация по сохранённому экспорту |
|---|---|---|
| `CCharacter::walkingSpeed()` | `0x815a20` | `research/decompiled-core/character.c:5341` |
| `CCharacter::runningSpeed()` | `0x815ad0` | `research/decompiled-core/character.c:5373` |
| `CCharacter::defense()` | `0x814530` | `research/decompiled-core/character.c:4758` |
| `CCharacter::armorBonus()` | `0x8145c0` | `research/decompiled-core/character.c:4781` |
| `CCharacter::AC()` | `0x814670` | `research/decompiled-core/character.c:4810` |
| `CEquipment::canEquip(CCharacter*, bool)` | `0x86f150` | `research/decompiled-core/equipment.c:1718` |
| `CEquipment::getLevelRequirement(CCharacter*)` | `0x86ddc0` | `research/decompiled-core/equipment.c:640` |
| `CEquipment::getStrengthRequirement(CCharacter*)` | `0x86dc50` | `research/decompiled-core/equipment.c:577` |
| `CEquipment::getDefenseRequirement(CCharacter*)` | `0x86d800` | `research/decompiled-core/equipment.c:388` |
| `CEquipment::setRequirements()` | `0x880030` | `research/decompiled-core/equipment.c:7009` |
| `CEquipment::calculateCombatStats(bool)` | `0x880950` | `research/decompiled-core/equipment.c:7290` |
| `CEquipment::setGraphDamage(unsigned int)` | `0x87dfa0` | `research/decompiled-core/equipment.c:5808` |
| `CEquipment::setGraphAC(unsigned int)` | `0x87e0c0` | `research/decompiled-core/equipment.c:5855` |
| `CEquipment::improveHeirloom()` | `0x882330` | `research/decompiled-core/equipment.c:7295` |
| `CEnchantMenu::onClick(ELayoutFunction)` | `0xb29650` | `research/decompiled-core/enchant_menu.c:4268` |
| `CInventory::getPaneSize(EINVENTORY_PANES)` | `0x91b0b0` | `research/decompiled-core/inventory.c:158` |
| `CInventory::canPickup(CEquipment*, bool)` | `0x91bc50` | `research/decompiled-core/inventory.c:1112` |
| `CInventory::CInventory(CCharacter*, unsigned int)` | `0x926000` | `research/decompiled-core/inventory.c:5631` |
| `CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)` | `0x847280` | `research/decompiled-core/character.c:23847` |
| `CGameUI::mapEventHandlers(CEGUI::Window*)` | `0xa97e00` | `research/decompiled-core/game_ui.c:5244` |
| `CGameUI::handle_onClick(CEGUI::EventArgs const&)` | `0xa83690` | `research/decompiled-core/game_ui.c:789` |
| `CEnchantMenu::performInteraction()` | `0xb26290` | `research/decompiled-core/enchant_menu.c:2905` |

## Отдельный SAVE-источник

`research/decompiled-core/effect.c:4178–4183`: Конструктор `CEffect::CEffect @0x7e1200`, участок `0x7e169f..0x7e16b3` читает BOOL SAVE в отдельный byte `+0x33`. Это не замена MIN/MAX или новый activation mode. В переносе снят только запрет такой метки у уже допустимого фиксированного PASSIVE/ALWAYS; целиком CEffect lifecycle не восстановлен.

## Эталонные проверки

`tests/compare_character_stats.py` и `tests/compare_item_graph.py` принимают `--original`, `--probe`, `--output`; безопасно отказывают при неподдержанном ELF/архитектуре или занятом фиксированном адресе. На неизвестном окружении не включать MAP_FIXED и не отключать fingerprint gate.
