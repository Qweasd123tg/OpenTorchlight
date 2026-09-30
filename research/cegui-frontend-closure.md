# Завершение библиотечной цепочки frontend CEGUI

2026-09-30: Main/credits теперь исполняются [исходной CEGUI 0.6.2](cegui-source-integration.md).
Ниже — принятый срез собственного runtime, который пока используется другими
страницами. Его результаты не являются проверкой нового library backend.

Проверено по коду 2026-09-21. Это принятый срез Main/Options/Settings/Continue,
а не утверждение о полном переносе всех классов CEGUI и игровых меню.
Исходные ELF, версии и SHA-256: [контейнер](dropdown-container-lifecycle.md),
[teardown](ui-window-teardown.md), [Combobox](ui-combobox.md).
Проприетарные входы использованы только для чтения.

## Замкнутые пути

| Контракт | Производитель и потребитель в приложении | Источник |
|---|---|---|
| Window create → renderer → detach → deferred factory release | `Frontend::ResourceWindows`/`UiWindowLifecycle` → `UiResources` bindings → `UiSkinCache` invalidation → `UiWindowRuntime::clean_dead_pool` освобождает свойства окна | shipped CEGUI create `0x128668`, destroy `0x125520/0x114840`, cleanup `0x114960/0x1253d0`; [полный порядок](ui-window-teardown.md) |
| Tooltip enter/move/down/leave → размер → fade → уничтожение владельца | `Frontend::retarget_pointer/advance` → `UiTooltips` → реальные manager windows → `UiSkin::compile`/GLES; owner reset/release hooks, явный shutdown | CGameUI `0xa9f5c3..0xa9f618`, Tooltip `0x19af70/0x19b1d0`, property pass-through `0x129c50`; [контракт](ui-window-teardown.md) |
| Double/triple/ordinary down и auto-repeat | Wayland monotonic events → Application chronological dispatch → `UiPointerTiming` → receiver property/subscription → runtime class down; repeat вызывает только исходное окно и не меняет System tracker | System `0x10c320/0x10c150`, Window `0x112e10/0x112ea0`; [таймеры](ui-pointer-timing.md) |
| Read-only Combobox → popup capture → accepted → settings | `UiSettingsComboboxes` создаёт autochildren; общий manager решает target/capture; Frontend применяет typed selection; SettingsFile сохраняет исходные ключи | Settings `0xbd5560/0xbd47e0`, Combobox `0x139390`, DropList `0x13dc00/0x13ddc0`; [данные и порядок](ui-combobox.md) |
| Combobox geometry/text/state → painter | viewport font metrics + resource NamedArea → общий snapshot → Falagard frame/editbox и `combobox_text_item` → Frontend paint order → `GlesUiRenderer::draw_skin_draw` | [Falagard и ListboxTextItem](ui-combobox-skin.md) |
| Options OPEN/CLOSE/IDLE + capture/modal/selection | прежний общий runtime и анимационная цепочка сохраняются; кликовая активация/paint читают те же ID | [capture](ui-capture-modal-lifecycle.md), [анимация](dropdown-animation-lifecycle.md) |

`library-derived`: `Window::onMouseButtonDown @0x112c60` сначала сбрасывает
tooltip, затем выполняет rise, auto-repeat и down event. Результат rise входит
в handled. `moveToFront_impl @0x116550` передаёт clicked по цепи родителей;
`isTopOfZOrder @0x112400` проверяет вершину своей AlwaysOnTop-группы и исключает
лишний Z-change. В порте эти условия сохранены. Уничтожение сразу освобождает
имя; новый ID с тем же именем разрешён до cleanDeadPool старого. Старый factory
release не удаляет renderer или cache нового окна.

`original-code`: `CDropdownMenu::onDoubleClick @0xb05e80` возвращает true без
повторного down-действия. Continue override `0xc334e0..0xc3357b` допускает
только enum 14..17 (GUISELECT1..4, **не** GUISELECT5), проверяет выбранный
save health и вызывает state(2,0), затем close. `SaveStore::list` передаёт
`checkpoint.player.health` в `SaveSlotInfo`; Frontend использует положительное
здоровье и load request существующего `.otc`-владельца. Decode допускает только
конечные числа: оригинальная unordered/NaN ветвь не входит в этот input domain.

`port-native`: доступные разрешения приходят из реальных Wayland `wl_output`
mode events, включая hotplug/remove. Если compositor не сообщил modes, host
передаёт только текущий размер; выдуманного списка разрешений нет. Настройки
записываются в файл порта, оригинальные settings не изменяются. Подтверждённые
ключи: `LIGHTING_ENABLED`, `SHADOWRESOLUTION`, `SHADOWS_DETAIL`,
`PARTICLEFPS`, `PARTICLE_EMIT_PCT`. `MAX_PARTICLES` — другой параметр.
Изменение resolution применяется при следующем запуске desktop; полный
world-shadow/ParticleUniverse renderer этим UI-срезом не восстанавливается.

`port-native`: host timestamp — время получения события. Application продвигает
frontend до каждого timestamp, доставляет событие, затем остаток интервала;
это исключает repeat после уже полученного release. После leave сохраняется
последняя позиция курсора для capture/repeat. Сводка состояния host не заменяет
состояние посреди очереди. Это clock/transport adapter, не побитовая копия
SimpleTimer или исходного игрового main loop.

## Ошибки и предел закрытия

Обычный teardown исполняет source order; исключения callback прерывают его
без выдуманного rollback. RAII cleanup при неудавшемся создании Frontend/Tooltip,
безопасные tombstone IDs, внешние font/image caches и backend ownership — явно
портовые адаптеры. CEGUI exception ABI, arbitrary SubscriberSlot/reentrant
callbacks и исходные allocator failure leaks не объявляются эквивалентными.

В текущем пакете больше нет открытых tooltip, renderer/factory teardown,
mouse timing или трёх Settings popup consumers. За ним остаются editable
Combobox, переполненные scrollbars, прочие autochildren, GameClient safe pointers,
полный внешний CGameUI/ResourceManager, native `.SVB`/preview/state owners,
общие CGenericModel families и FMOD backend. Поэтому `completion` исходных
игровых функций сохраняет `partial`; это не новый пункт в остатке выполненного
узкого CEGUI-пакета.

## Проверка

Чистые state/numeric/resource проверки: `ui_pointer_timing_test`,
`ui_window_lifecycle_test`, `ui_tooltip_test`, `ui_combobox_test`,
`ui_combobox_skin_test`, ближайшие window/dropdown/animation/sound contracts
и settings persistence. Lifecycle включает ошибки каждого hook, reentrant
creation, reverse dead pool и reuse имени. Combobox включает масштаб 2 без
повторного масштабирования font metrics. Tooltip включает custom fallback.
Итоговый именованный gate: `build-verification/cegui-closure-check.json` —
20/20 (10 core + 10 assets), без пропусков; `source_consistent=true`.
`torchlight_desktop` отдельно собран успешно. UI-клики, запуск приложения, снимки, кадровые,
сквозные и performance сценарии в эту проверку не входят и не выполнялись.
