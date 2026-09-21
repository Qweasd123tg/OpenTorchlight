# Триаж acceleration-архива (OpenTorchlight-main-accelerated(1).zip)

> История приёмки архива. Команды и критерии обновлены в
> [codefirst-tooling.md](codefirst-tooling.md). Указанное ниже «закрытие
> переклассификацией» относилось к integration-карточке ограниченного среза,
> не к полному восстановлению функции. Текущие stages/completion проверять
> в реестре; default scope теперь UI, near matching — opt-in, вход пакета ENTRY.md.

База архива старее нашего main — взят только инструментарий, проверенный
запуском на нашем дереве. Патч целиком не применялся.

## Взято (все проверено исполнением здесь)

- `tools/asm_family_cluster.py` — воспроизводит их отчёт бит-в-бит
  (проверено на `handle_CloseButton`).
- `tools/tiny_function_catalog.py` + `research/tiny-functions.json/.md` —
  выборка 5/5 сошлась с ручным objdump (геттеры/noop/константы, включая
  `getCharacterCanBeHarmedByMissile=1` — пригодится missile-потоку).
- `tools/menu_wiring_similarity.py` — работает на нашем batch-отчёте,
  подтверждает наши ручные выводы (merchant↔stash 0.73 с точными дельтами).
- `tools/work_frontier.py`, `tools/family_package.py`,
  `tools/prepare_family_packet.py`, `tools/prepare_integration_packet.py` —
  запускаются; family-пакет проверен (23→13 представителей + PROMPT).
- `tools/function_package.py` (апгрейд): суффиксный поиск evidence
  (находит `.asm`) + reuse-блок с graceful-деградацией. Проверен на `0xb4eb70`.
- `research/fast-work-prompt.md` — адаптирован (reuse-шаг заменён нашими
  `audit_sinks.py` + реестром).

## Исправлено по ходу (ошибки посылок, не инструментов)

- «Screen-scale integration packet»: в нашем дереве нечего интегрировать —
  `convertToScreenScale` факторизован в `ui_screen_ratio`/`ui_scale_*`,
  которые вызываются на реальных путях. Карточки `a83ed0/a83e70/a83ea0`
  переведены в `wired=true` (factored). Пакет закрыт переклассификацией.
- «Panel-open integration ×5»: невозможен — у merchant/pet/quest/skill/
  journal нет UI в порту (профили без CEGUI-исполнителя). Помечено, не
  замалчивается. Инструмент пакетов оставлен (пригодится настоящим группам).

## Отклонено

- `tools/reuse_inventory.py` + `research/reuse/`: дубль реестра/аудита
  (решение зафиксировано ранее, подтверждено повторно).
- Полный мерж архива и 4 «готовых задания»: stale-база, два задания
  невозможны/закрыты (см. выше).
- Массовое копирование `family-*.md`: генерируются по требованию
  (`prepare_family_packet.py`), в дерево не складываем.
