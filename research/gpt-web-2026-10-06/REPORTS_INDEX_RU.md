# Комплектность присланных исследований

Проверено 6 октября 2026. Идентифицированы девять последовательных проходов Pro. Номер прохода не равен версии этого общего архива. Ранние сообщения присланы текстом, поздние — ZIP.

| Проход | Полученный материал | Где лежит в этом пакете | Собственная сверка |
|---|---|---|---|
| 1 | Полный переданный текст | user-supplied-opinions/opinion-1.txt | research/night-audit-2026-10-06 |
| 2 | Полный переданный текст | user-supplied-opinions/opinion-2.txt | research/night-audit-2026-10-06 и decomp-acceleration-2026-10-05 |
| 3 | Полный переданный текст | user-supplied-opinions/opinion-3.txt | research/pass3-check, capture-research |
| 4 | Полное сообщение с отчётом | user-supplied-opinions/opinion-4.txt | research/pass4-check |
| 5 | Полный распакованный ZIP | user-supplied-opinions/OpenTorchlight_pass5 | research/pass5-review |
| 6 | Полный распакованный ZIP | user-supplied-opinions/OpenTorchlight_pass6 | research/pass6-review |
| 7 | Полный распакованный ZIP | user-supplied-opinions/OpenTorchlight_pass7 | research/pass7-review |
| 8 | Полный распакованный ZIP и пересланный текст | user-supplied-opinions/OpenTorchlight_pass8; research/pass8-9-review/pass8-forwarded-text.txt | research/pass8-9-review |
| 9 | Полный распакованный ZIP | user-supplied-opinions/OpenTorchlight_pass9 | research/pass8-9-review |

На момент первой сверки отдельные ZIP и прототипы первых четырёх проходов не были получены. Позднее предоставлен OpenTorchlight_unified_audit: теперь в нём есть наборы воспроизведений types-and-comparison, fast-comparison и syntax-and-signatures, соответствующие ранним проходам. Они лежат внутри user-supplied-opinions/OpenTorchlight_unified_audit/reproductions. Отдельные первоначальные ZIP этим не подменяются. Ссылки sandbox внутри пересланных текстов не являются включёнными файлами. Наши воспроизведения по первым четырём проходам включены отдельно и не заменяют исходники автора.

В предыдущем общем архиве версии 10 отсутствовали полные тексты 3–4: там были только наши проверки. Эта неполнота устранена в данном обновлении. Отдельный десятый проход Pro по доступной истории не идентифицирован; это не утверждение о полном содержимом иных чатов.

## Собственные дополнительные исследования

- decomp-acceleration-2026-10-05: SDK/prototype A/B, LP64, String layout, clone-delta
- night-audit-2026-10-06: objdiff/отпечатки, EH/vtables и предыдущие ограничения
- pass3-check: индекс objdiff и сравнение результатов
- capture-research: границы наблюдения/ошибки Capture
- pass4-check: сохранение семантики convert, сигнатуры, перегрузки и охват очереди
- mutation-audit: привязка доказательств к версии, зависимые пакетные мутанты
- cache-audit: приоритеты include и неактуальный объект компиляции
- queue-audit: двойная выдача TU и зависшая резервация
- table-audit: исчезновение позиции и ошибки декодирования таблиц
- pass5-review ... pass8-9-review: независимая сверка, разграничение результатов автора и наших проверок

Это комплект исследований для внедрения. Он не содержит исходный ELF/PAK, тулчейн, Ghidra database или полную актуальную ветку проекта с ПК. Ранее созданные игровые реализации находятся в отдельном полном архиве dot-all-work-2026-10-05; данный пакет не заменяет его.

## Единый аудит Pro, получен дополнительно

user-supplied-opinions/OpenTorchlight_unified_audit: полный предоставленный комплект из 250 файлов, каталог 56 замечаний, четыре патча и ранние воспроизведения. Собственная сверка: research/unified-pro-review. Это сводный аудит, а не десятый независимый номерной проход с 56 новыми находками.
