# Ghidra BSim/FID и статические ссылки: пилот 2026-09-20

Статус: `original-code` для конкретных инструкций/ссылок;
`port-native tooling` для измерения поиска кандидатов.
[Машинный отчёт](library-match-pilot.json),
[заранее выбранные 20 адресов](library-match-targets.tsv).

## Результат

Штатный BSim сравнил 20 исходных функций с 149 пригодными сигнатурами из
кандидатной библиотеки. Имена использовались только для оценки результата:

| Результат поиска по similarity | Функций |
|---|---:|
| Ожидаемое имя — единственный первый кандидат | 7 |
| Ожидаемое имя в группе равных первых кандидатов | 3 |
| Первым оказался кандидат с другим именем | 10 |

FID full+specific hash с размером дал один совпадающий кандидат:
`lodepng_is_palette_type`. Хеши исходных 20 функций были доступны;
часть коротких кандидатных функций не проходит минимальный размер FID.

Это retrieval по символам известного исходного кандидата, **не** оценка
семантической точности, готовности игры или exact historical source version.
Порог принятия совпадений не подбирался. Даже unique top у CRC32 имеет
similarity только 0.288488. FID здесь использован как hash API, а не полный
контекстный FID analyzer с сопоставлением окружения. BSim использован через
штатный weighted-vector API, без собственного cosine и без BSim server/index.

| Ожидаемый символ, префикс `lodepng_` опущен | Ранг с учётом ties | Similarity ожидаемого |
|---|---:|---:|
| read32bitInt | 70 | 0.042928 |
| compress_settings_init | 7 | 0.338288 |
| decompress_settings_init | 1 | 0.588136 |
| crc32 | 1 | 0.288488 |
| chunk_length | 107 | 0 |
| chunk_type | 1 | 0.414044 |
| chunk_ancillary | 1, tie из 3 | 1 |
| chunk_private | 1, tie из 3 | 1 |
| chunk_safetocopy | 1, tie из 3 | 1 |
| chunk_check_crc | 94 | 0.019717 |
| chunk_generate_crc | 77 | 0.036023 |
| chunk_next | 107 | 0 |
| chunk_next_const | 107 | 0 |
| color_mode_init | 10 | 0.207947 |
| get_bpp | 1 | 1 |
| get_channels | 1 | 1 |
| is_greyscale_type | 2 | 0.274397 |
| is_alpha_type | 13 | 0.125586 |
| is_palette_type | 1 | 1 |
| has_palette_alpha | 1 | 0.369792 |

Три chunk-флага имеют **одинаковые BSim feature arrays**, хотя читают разные
байты. У них также одинаковый full FID hash в кандидатной сборке, а specific
hash отличается. Это конкретная граница утверждения `exact fingerprint`:
совпали выбранные признаки, для переноса требуется контракт операции.

Предыдущий [native source pilot](lodepng-source-pilot.md) сравнивал read32 и
CRC32 по значениям. Низкий retrieval-score read32 не отменяет ту проверку;
первое место CRC32 не расширяет её на остальные условия и функции.

## Идентичность входов и ограничения анализа

- Оригинальный ELF SHA-256:
  `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- Ghidra **12.1.3**, архив `ghidra_12.1.3_PUBLIC_20260817.zip`, SHA-256
  `93a5d11a9ad510622acaaf908c556a7b9b764d338e78a7567f3689bf5081fd54`.
- LodePNG [bf09e0a5f173ba07821b782b8297dbfc139d5fed](https://github.com/lvandeve/lodepng/tree/bf09e0a5f173ba07821b782b8297dbfc139d5fed):
  `.cpp` SHA `8f6810a4b848e1e45ec8559df121f90342078b1af3a1c4d0ccbd86d91bc1391d`,
  `.h` SHA `c44978696b0e2eb40b573d65e3dd16f7fa7f1202cf0cf862802493aeaf861ee0`.
- g++ **16.1.1 20260515**, `-std=c++11 -O2 -fPIC -shared`, без debug info.
  SHA полученной `.so`:
  `8a27d70835a47d0d98822db0b92de1f41df6c249daad5030da3a17b36846c7cc`.
- Java **25.0.4**; язык `x86:LE:64:default`, compiler spec `gcc`.
- Стандартные `lshweights_64.xml`, signature settings **73**, SHA weights
  `1b0795effc4f696082faca3a2145e714c1b120aed7461a0f32d3ba29a0056912`.

Полный старый Ghidra-проект в `/tmp` отсутствовал. Создан отдельный пилотный
проект. **Первичный анализ оригинала достиг лимита 600 секунд**; Ghidra
сохранила частичный результат. Поэтому глобальная полнота анализа остаётся
открытой. У всех 20 выбранных функций генерация BSim завершилась без bad-data
или unimplemented-флагов; это локальный диагностический результат.

В кандидатной `.so` выбраны все 150 non-external/non-thunk функций, включая
ELF/C++ boilerplate, а не только 20 ожидаемых. Одна `_M_default_append`
`@0x00110a50` отмечена `incomplete_instructions` и исключена из BSim-сравнения.
Анализаторы сообщали предупреждения EH/LSDA и внешних vtables; сохранены логи.
Символы присутствовали при анализе и могли повлиять на выведенные прототипы:
это эксперимент без names в scoring, а не полностью blind stripped benchmark.
Исходный компилятор/настройки Torchlight здесь не воспроизводились.

## Проверка исторически пропущенного хвостового перехода

`ExportCodeFirstPacket.java` скомпилирован и исполнен против текущей Ghidra.
Экспортированы `0xd04610`, `0xa0adc0`, `0xc4ae80`, `0xb179e0`.
Входящие ссылки `CMissile::fireMissile @0xd04610` содержат:

| Место | Записанный тип / значение |
|---|---|
| `0x87f56f`, owner `0x87f120` | `UNCONDITIONAL_CALL` |
| `0xa0ae8c`, owner `0xa0adc0` | `UNCONDITIONAL_CALL`, instruction `JMP`, flow `CALL_TERMINATOR` |
| `0x1054714` | `INDIRECTION` |
| `0x10d4cc8` | `DATA` |
| synthetic Entry Point | `EXTERNAL` |

Байты `e9 7f 97 2f 00` на `0xa0ae8c` независимо сверены `objdump`: это
`jmp 0xd04610` после восстановления стека. Проверка требует как входящую
ссылку, так и исходящую JMP-инструкцию. Ghidra классифицирует её как
хвостовой вызов, поэтому проверка только `reference_type == JUMP` тоже
потеряла бы этот случай. Instruction bytes, mnemonic и analysis ref type
сохраняются отдельно.

Пять записей не означают пять callers: здесь есть две ссылки из функций,
две неатрибутированные записи данных/indirection и synthetic external entry.
Назначение таблиц и динамические косвенные пути в этом пилоте не разобраны.
`function_package.py` пока не подключает этот JSON и остаётся на CALL-index;
экспорт Ghidra — отдельное дополнение к нему.

## Стоимость и воспроизводимость

Локальные единичные wall-clock замеры:

- загрузка отсутствовавшего Ghidra-архива: около 95 s, 543 MiB;
- fresh original import + ограниченный анализ + четыре экспорта: **640.32 s**,
  пик RSS около **2.83 GiB**, анализ завершился timeout;
- candidate import + анализ + export: **22.93 s**, из них feature script **2.945 s**;
- query из сохранённой базы: **5.81 s**, из них 20 сигнатур и 2980 BSim
  сравнений **0.476 s**;
- повторный query дал идентичный JSON после исключения только elapsed time.

База, toolchain, логи и полные feature/score JSON оставлены в
`/tmp/opentorchlight-match-pilot-RB9wPs`. `/tmp` — временное хранилище, его
наличие проверяется перед повторным запуском. В репозитории только малый
список целей, сводка и скрипты; оригинальный ELF/ресурсы внешние read-only.

После проверки хешей Ghidra/исходников и сборки кандидата:

```sh
# Ghidra уже распакована; pilot_dir — отдельный существующий рабочий каталог.
# Переменные указывают на локальные пути; sha256sum проверяет внешние входы.
export XDG_CONFIG_HOME="$pilot_dir/config"
export XDG_CACHE_HOME="$pilot_dir/cache"
export GHIDRA_HEADLESS_MAXMEM=2G
mkdir -p "$pilot_dir/project"
g++ -std=c++11 -O2 -fPIC -shared -o "$pilot_dir/lodepng-O2.so" "$source_dir/lodepng.cpp"
candidate_sha=$(sha256sum "$pilot_dir/lodepng-O2.so" | cut -d ' ' -f 1)
original_sha=91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b

"$ghidra_home/support/analyzeHeadless" "$pilot_dir/project" Candidate \
  -import "$pilot_dir/lodepng-O2.so" -max-cpu 2 -analysisTimeoutPerFile 120 \
  -scriptPath tools/ghidra -postScript LibraryMatchPilot.java \
  "$candidate_sha" - "$pilot_dir/candidate.json"

# Original — заранее импортированная программа с проверенным SHA.
# Состояние её auto-analysis устанавливается по сохранённому логу.
"$ghidra_home/support/analyzeHeadless" "$pilot_dir/project" Original \
  -process Torchlight.bin.x86_64 -readOnly -noanalysis -max-cpu 2 \
  -scriptPath tools/ghidra -postScript LibraryMatchPilot.java \
  "$original_sha" research/library-match-targets.tsv "$pilot_dir/query.json" \
  "$pilot_dir/candidate.json" "$candidate_sha"

python3 tools/library_match_report.py \
  --query "$pilot_dir/query.json" --candidate "$pilot_dir/candidate.json" \
  --xref-dir "$pilot_dir/xref-export" --out "$pilot_dir/report.json"
```

Выходные JSON должны быть новыми; повторный query получает другое имя.
Для xref-export используется команда из [decompiler-workflow.md](decompiler-workflow.md)
и файл четырёх точных адресов выше. CLI headless может вернуть exit 0 даже при
ошибке анализа/скрипта: проверяются лог и наличие завершённых выходов.
`library_match_report.py` отклоняет иной ELF, изменённые цели, другой candidate
export/settings, пропущенные сравнения и отсутствие известного tail edge.

Проверка tooling: **7 unit cases**, CTest `library_match_report` через
`tools/check.py --core --test library_match_report`; отчёт
`build-verification/library-match-check.json`. Игра, кадры и UI-клики не запускались.

## Решение по результатам

Готовые BSim/FID используются как опциональное сужение поиска. Для уже
символизированного LodePNG поиск по имени и pinned source остаётся полезным
первым шагом; широкий hash/similarity match не закрывает библиотеку.
Сбор recorded static refs доказан на конкретном пропущенном tail path и
подходит для следующей интеграции в function package.

Перед собственным IR/emitter следующий кандидат на отдельный эксперимент —
[rev.ng; для сравнения контрактов — cozy/angr](deterministic-reconstruction-tools.md).
Миграция инструментария и массовая генерация C++ этим пилотом не утверждались.
