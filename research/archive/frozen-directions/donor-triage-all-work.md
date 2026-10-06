# Триаж архива OpenTorchlight-all-work-reconciled.zip

> **Архив замороженного направления.** Указания, команды, очереди и числа ниже
> относятся к прежнему снимку; они не задают текущую работу или приёмку.
> Действующий процесс: [decomp](../../../decomp/README.md).

> Историческая приёмка конкретного архива, не действующая очередь задач.
> Текущие границы и инструменты: [code-first.md](code-first.md),
> [codefirst-tooling.md](codefirst-tooling.md).

Вход: `/home/qweasd123tg/Загрузки/OpenTorchlight-all-work-reconciled.zip`
(1012 файлов). База архива — снимок эпохи `15a00bd` (его ledger: 11 записей
против наших 22; нет batch-проходов, профилей, звуков, single-writer фикса).
Архив целиком НЕ применялся (откатил бы main). Взято по частям, каждая —
с проверкой.

## Взято (phase A, этот коммит)

- `src/ui_skin.cpp`, `include/torchlight/ui_skin.hpp` — дословно: компилятор
  Falagard-команд (states/sections/frame/text), честно ограниченный
  («NOT the full CEGUI runtime»).
- Дельта `ui_layout.{hpp,cpp}` донора, влитая вручную с сохранением нашего:
  `UiLayoutState` (visibility/offset_ratio/screen_scale), `effective_alpha`
  (+`InheritsAlpha`), `paint_order`-обход, `scaled_metrics`, `skin()`,
  проверка нативных разрешений, `ui_skin_xml`. Наши `resolve(w,h)`,
  original-code комментарии и `(max-min)*ratio`-тонкость сохранены.
- Тесты: `ui_skin_test.cpp` (46/46 на синтетической фикстуре) +
  `make_ui_skin_fixture.py`, метка core. Нативные probe/render-харнесы НЕ
  взяты (нет инфраструктуры пробников).
- Research: `ui-skin-continuation.md`, `ui-skin-findings.json`,
  `ui-skin-reference/` (срезы + manifest + UPSTREAM_NOTICES).
- Поправка честности: цитируемые донором адреса `Window::render @0x1130c0`
  / `addWindowToDrawList @0x1163d0` отсутствуют в нашем
  `original-symbols.txt` — в комментарии это помечено как unconfirmed/open,
  а не как original-code.

## Отложено (нужна адъюдикация с доказательствами, не мерж)

- Порядок хит-теста: наш обратный обход vs донорский `paint_order`.
  Оба правдоподобны; решает поведение CEGUI 0.6.2 (library-derived) или
  машинный код, а не голосование. `paint_order` уже считается и хранится —
  переключение тривиально, когда будет доказательство.
- Оверлей Credits: наша синтетическая fullscreen-кнопка vs донорская
  parent-image кнопка. Конфликт утверждений — сравнить с ресурсами/layout.
- Сигнатура `Frontend::frame(w, h, pointer)`: API-churn ради hover —
  отложить до сценарного пакета, которому нужен hover.
- `population.*`, `ogre_mesh_test`: версии архива СТАРЕЕ наших
  (у нас новее комментарии/доказательства) — оставлены наши.

## Отклонено

- Применение патча/архива целиком: stale-база, регресс main.
- `research/reviews/`: удалены у нас осознанно (`a9915be`), не восстанавливать.
- `tools/reuse_inventory.py` + `research/reuse/`: дублирует реестр/аудит
  (fingerprints принятого контекста уже держит `tools/check.sh`-линейка и
  `audit_registry_sync.py`); второй учёт вводится не будет. Идея «сначала
  смотри существующее» уже зафиксирована правилом baseline в `code-first.md`.
- `ui_contract_test`, `ui-audit` label-инфраструктура, `compare_ui_scale.py`:
  вне текущего скоупа.
