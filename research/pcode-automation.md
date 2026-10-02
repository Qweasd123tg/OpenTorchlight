# Автоматический сбор неизвестного поведения

2026-10-02. `original-code`: ELF SHA
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`library-derived`: Ghidra 12.1.3, официальный archive SHA
`93a5d11a9ad510622acaaf908c556a7b9b764d338e78a7567f3689bf5081fd54`;
это инструмент анализа x86, а не библиотека игры. Java 25.0.4.1.

Постоянные ignored tool cache и проект восстановлены. Полный импорт выполнен
один раз; дальнейшая команда выбирает 1–64 точных входа, проверяет bytes каждой
экспортированной инструкции по внешнему ELF и сохраняет SHA tool scripts,
CPU semantics, raw/evidence файлов и полного оригинального тела по symbol size.
Успех экспорта — `COLLECTED`, а не подтверждение C++ переноса.

```sh
python3 tests/make_pcode_probe_profile.py /tmp/pcode-profile.json
python3 tools/ghidra_probe.py \
  --original /home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64 \
  --address 0x7f5fd0 --address 0x7f5fe0 --address 0x805110 \
  --address 0x80e890 --address 0x80ec60 \
  --profile /tmp/pcode-profile.json --out build-ghidra/probes/primitive-fresh
python3 tests/compare_pcode_probe.py \
  --original /home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64 \
  --profile /tmp/pcode-profile.json \
  --result build-ghidra/probes/primitive-fresh/emulation.json
python3 tools/function_package.py --address 0x80e890 \
  --ghidra-dir build-ghidra/probes/primitive-fresh --out /tmp/depth-packet.md
```

Калибровка дала **561 совпадение** raw return bits и полных наблюдаемых буферов
между Ghidra и исполнением неизменённых оригинальных leaf bytes в private memory.
Состояние задаётся явно; нативный тест ограничен четырьмя проверенными no-call
телами. Он не запускает оригинальную игру или динамический загрузчик.

| Оригинальная функция | Проверенная граница |
| --- | --- |
| `CBaseUnit::setSpawnerGuid(long long) @0x7f5fd0`, 8 bytes | `mov RSI → [RDI+0x180]`: 37 значений u64, весь буфер после записи |
| `CBaseUnit::getCastsShadows() @0x7f5fe0`, 8 bytes | `movzbl [RDI+0x1a9] → EAX`: все 256 байтов, верх RAX обнуляется |
| `CBaseUnit::getHighlighted() @0x805110`, 8 bytes | `movzbl [RDI+0x1a8] → EAX`: все 256 байтов |
| `CCharacter::setMaximumTreeDepth(unsigned) @0x80e890`, 17 bytes | `[RDI+0x268]` u64 pointer; null exit или u32 запись `[pointer+0x6c]`: 12 случаев |
| `CCharacter::hasPet(CCharacter*) @0x80ec60`, 12 bytes | 1 ожидаемый `UNKNOWN`: вызов `petIndex @0x80ec10` без модели зависимости |

Включая байтовые значения вне созданного bool-object domain, это калибровка
точных операций и ветвлений. Она не доказывает constructor/ownership/valid
world state и не закрывает функцию в production. Поле `completion` не меняется.

Локальный анализ сбрасывает unique temporaries между инструкциями, обрывает
значения на границе блока/вызова, инвалидирует перекрывающиеся register widths
и сохраняет raw memory effects после неразрешённой внутренней p-code ветви.
Общий механизм проверяет `tests/pcode_analysis_test.py`; защита input hashes
пакетов проверяется `tests/function_package_test.py`.

Опциональный настоящий CTest gate:
`cmake -S . -B build-cegui -DTORCHLIGHT_ENABLE_GHIDRA_PROBES=ON`, затем
`ctest --test-dir build-cegui -R '^original_ghidra_pcode_calibration$' --output-on-failure`.
Установка и полный анализ в CTest не запускаются. Неподготовленный проект или
missing output дают ошибку, а не зелёный пропуск. В обычном прогоне gate OFF.

В этом окружении Java XML logger выдаёт diagnostic для кириллического пути
jar. Экспорт и эмуляция выполнены; наличие/схема/полнота результатов проверяются
независимо от launcher exit code, поскольку headless не всегда делает ошибку
postScript ненулевым exit. Diagnostic нельзя использовать как доказательство
успешного скрипта.

Следующая работа теперь может автоматически получать операции, размеры памяти,
ветви и точные эффекты на заданных состояниях. Внешние зависимости, виртуальные
цели, выбор допустимых входов и production consumer требуют разбора оригинала.
Процент ускорения всей разработки пока не измерен.
