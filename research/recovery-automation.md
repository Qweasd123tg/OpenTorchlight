# Автоматическое исполнение проверенного переноса

2026-10-02. Port-native tooling: генерация принятых контрактов в рабочий C++,
сборка потребителей, original comparison и проверка реестра без LLM/API/сети.

## Один запуск

```sh
python3 tools/check.py --recover /path/to/game \
  --build-dir build-recovery --report build-recovery/recovery.json
```

Внешний read-only каталог содержит pak.zip и Torchlight.bin.x86_64.
Для раздельных входов: `--assets DIR --reference ELF`.
Для fixed-address probes доступен `--reference-python /path/to/PIE-python`.

Driver проверяет входы, конфигурирует CMake, повторно извлекает принятые данные
из оригинала, генерирует C++, собирает `torchlight_recovery_gates` и выполняет
все зарегистрированные CPU/resource/reference/registry проверки: план расширенного
среза содержит 181 проверку. RecoveryChecks.cmake берёт существующую регистрацию
CMake и excludes render/desktop/ui-integration. Новые CPU проверки подхватываются
без второй ручной таблицы; именованные domain summaries показывают PASSED,
FAILED и NOT RUN отдельно. Generated recovery-plan.json
не является вторым реестром функций. UI/game process не запускается.

Отсутствие входа не вызывает частичную сборку. Unknown recipe/body/width,
ошибка, skip или потерянная проверка не дают полного PASS. `--plan` ничего не
собирает/исполняет. JSON/JUnit/log сохраняются в ignored build.
Перед сборкой driver материализует известные outputs, исправляя их дрейф;
одинаковые файлы сохраняют mtime. Handwritten source и оригинал не переписываются.
Failed generated-file check также заменяет старый generation PASS в отчёте.

## Реальные производственные рецепты

research/recovery-contracts.json — принятый source-data snapshot с content SHA,
не статус готовности. Полные body SHA закреплены в генераторе. С ELF source
data повторно извлекаются и сравниваются целиком; обычная portable сборка без
ELF использует явно обозначенный accepted-snapshot режим, не новое сравнение.

| Рецепт | Источник | Потребитель |
|---|---|---|
| UI binding adapter / 97 команд | mapToFunctions 0xa980e0, size 0x374; KLayoutFunctionNames 0x14b7dc0 / initializer 0xa850bd..0xa85a5b | generated map_functions → ui_function_bindings → UiLayout/native CEGUI → frontend/HUD/application |
| MWC float adapter | randomBetween 0xc92a70 и randomBetweenVolatile 0xc92b50, оба size 0x97 | generated mwc_between → обе RNG обёртки → weighted/generation и UI gain/mix |
| Gameplay numeric adapters | 14 дополнительно закреплённых owning bodies; 8 scalar-only ASM boundaries; семь raw float32 констант | character_stats, attack_action, enemy_ai, consumable, population, progression, economy → прежние production callers; [поля и остаток](recovery-gameplay.md) |

`torchlight_core` прямо зависит от generated headers через RecoveredCode.cmake;
Desktop/application/probes используют тот же код. Старые ручные копии float
алгоритма удалены. Observer нормального RNG остаётся в owning wrapper.
Schema 2 snapshot фиксирует 17 полных body identities и отдельные scalar
boundaries; это не означает 17 полностью закрытых исходных функций.

Original-code: полные normal/volatile 151-byte тела одинаковы по операциям,
константам и relative branch targets; различаются RIP references к uint64
storage g_Rand 0x14ecaf0 / g_RandVolatile 0x14ecaf8. Общие два unsigned64
low32*0x29777b41+high32 шага, 52-bit fraction, double bit construction и
binary32→double→binary32 rounding order. AND eax на +0x1d кодирован **83 e0 ff**:
sign-extended imm8, не imm32. Literal locations охраняются whole-body hash;
различие operand maps блокирует shared recipe. Equal bounds сохраняют low/state,
NaN идёт в random ветвь. Clamp/swap/epsilon/fallback seed не добавлены.

UI template переносит весь ранее проверенный adapter algorithm: child-first
вне property catch, repeated get, first-NUL, ASCII/C-locale lookup, last-match
и preservation unknown binding. Все 97 извлечённых имён совпали с прежней
таблицей. Предшествующие ASM/LSDA/field/library reviews:
[ui-function-bindings.md](ui-function-bindings.md),
[volatile-random-fraction.md](volatile-random-fraction.md).

## Граница

Теперь автоматизированы preparation/cache/source lookup, материализация
проверенного перевода, dependency build, original comparison, regression и
структурная приёмка актуальности. Новый разобранный контракт получает recipe
и consumers/checks в этом же механизме, без нового scheduler.

Неизвестная функция не получает перевод по сходству и не закрывается тестом
соседа. Для неё остаётся конкретный field/call/member-delta разбор. Произвольная
автореконструкция C++/ownership/virtual dispatch не заявляется. Current UI/RNG
completion остаётся **partial**: CEGUI userData/exception ABI и process-global
RNG/seed/clock/общий порядок ещё не перенесены. Генератор не повышает стадии.
UI-клики, кадры и performance остаются отдельными задачами.

## Предыдущий проверенный UI/RNG результат

Один `--recover` запуск: core 7/7, assets 3/3, reference 3/3; skip=0,
source_consistent=true. Generated-код прошёл 28000 volatile float-bit/state,
4000 production UI gain/state и 64004 прежних RNG/weighted/geometry сравнений;
UI mapping — 469 original trees / 2312 nodes с точным порядком property calls.
Оригинальный ELF/pak хешируются как внешние входы. Registry: 238 bounded /165 cited.

Затем в ignored generated mwc_float.hpp специально возвращена старая 44-bit
mask. Повторный `--recover` обнаружил/перезаписал этот output по live original
recipe, пересобрал consumer и снова прошёл 13/13 без skip и изменения source.
Report changed_outputs содержит только mwc_float.hpp. Это проверка работы
автоматического пути после генерации; handwritten source и snapshot не менялись.
Desktop также собирается с теми же generated bodies; UI/frame/device проверки
этим траншем не выполнялись. Whole-function completion не повышен до full.
