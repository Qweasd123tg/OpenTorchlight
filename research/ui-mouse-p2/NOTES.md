# P2 — фаза HUD onClick: MouseButtonDown (исправление прежнего патчсета)

Статус: `original-code` для фазы события и немедленной диспетчеризации;
привязка имён callback к действиям — `resource-derived`; панели
инвентаря/умений/квестов остаются PORT-представлением.

## Источники

- `CGameUI::mapEventHandlers @0xa97e00` подписывает непустой `onClick` на
  `CEGUI::Window::EventMouseButtonDown @0x14247e0` (инструкция `0xa97f04`
  передаёт адрес события; имя подтверждено таблицей символов ELF).
- `CGameUI::handle_onClick @0xa83690` при коде кнопки 0 и наличии окна
  немедленно извлекает команду из userData и вызывает обработчик —
  ожидания release нет.
- Исполнение оригинала переподтверждено 2026-09-17 вместе с P1:
  48/48 случаев (`research/ui-scale-p1/original-ui-probes.rerun-2026-09-17.json`,
  раздел `click`).
- ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

## Ошибка прежнего комплекта

`hud_click_callback` требовал press+release на одной кнопке, а тест
закреплял «release outside — no activation». Для исследованной цепочки HUD
это неверно: уход курсора после обработанного MouseButtonDown не отменяет
прошедшую команду. Хелпер удалён, тест переписан на down-фазу.

## Что изменено (коммит P2)

- `include/torchlight/ui_hud.hpp`, `src/ui_hud.cpp`: `hud_click_callback`
  удалён; новый `hud_press_callback(frame, x, y)` — видимая включённая
  кнопка с callback в точке нажатия. Действует только для этой HUD-цепочки.
- `include/torchlight/application.hpp`: новый канал
  `take_ui_press()` (позиция физического нажатия); старые хосты отдают
  `nullopt`, release-канал тогда только дренируется.
- `src/application.cpp`: команда HUD выполняется на press через
  `hud_press_callback`; release-канал дренируется без повторной
  диспетчеризации. Убрана маршрутизация через синтетические клавиши
  I/K/J/ESC: действия панелей — общие лямбды для настоящих клавиш и HUD-команд.
  Блокировка мира нажатием по HUD (`hud_button_at`) сохранена. Дрен
  `take_ui_press` добавлен в обе menu/pause-ветви против протухших нажатий.
- `src/linux_desktop_main.cpp`: запись `ui_press_` на PRESSED, сброс на
  take/leave. Проверено компоновкой `torchlight_desktop` (Wayland/EGL/GLES,
  FreeType 2.14.3); запуск окна в этом проходе не выполнялся.
- `tests/application_scenario_probe.cpp`: стенд отдаёт `take_ui_press`;
  глагол `hud-button` ставит press на первом визите (гейт закрытого геймплея
  только там), release — на втором без повторной команды.
- `tests/ui_hud_input_test.cpp`: press диспетчеризует до release;
  press-then-drag-off не отменяет; press в мире команды не создаёт.
  Негативный контроль: старая press+release-политика не может пройти этот
  тест — без release команда у неё не существует вовсе, а drag-off у неё
  отменял бы действие.

## Сквозное подтверждение

`paused_settings_render` (реальный pak, общий цикл): Inventory открывается
нажатием, Journal/Pet репортятся как `hud_callback_unimplemented`,
Options уходит в паузу; release-маршруты присутствуют, но команд не
порождают; Apply пишет настройки без чекпоинта персонажа.

## Граница

Фаза подтверждена для in-game HUD/контроллера (`CGameUI`) и отдельно
замечена у `CInventoryMenu::mapEventHandlers @0xb4f1b0`. Остальные меню на
down не переводятся без проверки их подписок. Состояния Pushed/PushedOff,
захват мыши, Z-order и double-click не портированы. Модальность/двусторонние
панели и `getIsPaused` — предмет P3, здесь не тронуты.
