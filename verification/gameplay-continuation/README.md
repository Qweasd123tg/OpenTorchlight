# Логи проверки large-4 continuation

`baseline.log` и `input-checksums.log` относятся к нетронутому входному ZIP.
`final-portable-and-sanitizers.log` — два полных прогона 21/21: обычный build,
затем отдельный build с ASan/UBSan; параметры кеша в `sanitizer-flags.txt`.
`new-check-details.log` — 390 gameplay, 62 death finalization, 6497 numeric matches.
`read-only-tools.log` — 21 проверка защитного чтения, без настоящего ELF.
`environment.log` и `apt-update.log` фиксируют компилятор и причину отсутствия
полного графического build. `before_inputs.cpp/.log` — исходная минимальная
диагностика только для pristine large-4; горизонтальный helper сам по себе и
после патча не проверяет высоту, её добавляет `within_character_attack_reach`.

`clean-applied-build.log` добавляется после проверки cumulative patch на чистой
копии исходного архива. Все тестовые pak генерируются авторскими scripts в build,
не входят в доставку. Исторические 52/52 на оригинале не выполнялись в этой среде.

Логи могут содержать абсолютные пути среды проверки. Команды для повторения
на своей машине приведены в `../../GAMEPLAY_CONTINUATION_RESULT_RU.md`.
