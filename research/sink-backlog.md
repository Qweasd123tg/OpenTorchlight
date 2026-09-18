# Бэклог подключений: код без стока (`tools/audit_sinks.py`)

Инструмент: определённые символы `torchlight::*` из статических библиотек +
inline-функции заголовков; SINKLESS = ни одного использования в `src/` вне
собственного файла определения. Тестовое покрытие отмечается отдельно
(`*` = протестировано, но не подключено). Однословные общие имена
(`effective`, `current`, `aux`) дают ложные срабатывания — список разбирать
руками, а не коммитить вслепую.

## Закрыто подключением

- `MusicPlayer::apply_gain`: был мёртв (воркер дублировал инлайн);
  воркер переведён на него, семантика сохранена (громкость уже валидирована
  в `[0,1]` на загрузке настроек).

## Зарезервировано (осознанно, не мёртвый код)

- `MusicPlayer::mix_frame`: протестирован, ждёт sample-mixer (SFX-сток для
  `playSample`-id 22/66/12/21). Удалить — только вместе с появлением микшера.
- Профили/таблицы (`menu_create_profiles`, `menu_grab_tables`,
  `inventory_*`, `panel_profile_*`): транскрипция без runtime-исполнителя
  (в порту нет CEGUI). Потребитель — будущий MenuBuilder.
- `InventoryMenuState::click_tab`: табы станут кликабельными — подключится;
  синтетические клавиши не изобретаются.

## Хост-клей (вызывается платформой, не `src/`)

- `InputState`/`KeyManager`/`MouseManager`-методы, `run_application`
  (точка входа), `render_*_probe` (dlopen), `main`.

## Открыто (следующие кандидаты на подключение)

- `CombatController::refresh_attack_values`,
  `PlayerCombatState::refresh_damage_defense`,
  `PlayerSession::refresh_effect_contributions`,
  `EnemyController::ai_cooldown_remaining` (только тесты),
  `CheckpointAccess::restore_*`, `Frontend::leave_settings`,
  `QuestControllerRuntime` (деструктор — шум),
  `UiSkin::automatic_children`, `MusicPlayer::current`.
  Каждый разбирать отдельно: часть — следующий сценарный пакет (бой/квесты),
  часть окажется шумом имён.
