# Массовый перенос: общее состояние машины

> **Заморожено 2026-10-03.** Действующий процесс — [decomp](../decomp/README.md) и [AGENTS.md](../AGENTS.md). Документ остаётся справочником по поведению; его процессные указания (контракты, стадии, пакеты, очереди) не действуют.

2026-10-02. Приоритет пользователя: массовый перевод всей игры с сохранением
поведения; читаемость добавляется там, где не требует догадок или отдельного
ручного переноса. Новые мелкие UI-функции не назначаются следующей единицей работы.
Принятые реализации и их точные остатки сохраняются в прежнем реестре.

## Источник семантики

`original-code`: внешний read-only ELF
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`library-derived`: raw p-code закреплённой Ghidra12.1.3, `x86:LE:64:default`.
Экспорт сверяет инструкции с ELF; перевод сохраняет исходные операции, ширины,
ветви и порядок. Decompiler C, сходство имён и предложенные LLM алгоритмы не
заменяют операции. Неизвестный opcode, target или boundary вызывает отказ.

Сам генератор и runtime также требуют проверки: SHA удостоверяет исходные
байты, но не доказывает правильность исполнения p-code. Поэтому результаты,
память, вызовы и стек сравниваются с исходными телами; генерация не выставляет
`full`, `wired` или готовность игры.

## Одно ядро, повторно используемые границы

Общее ядро состоит из сохранённого headless-проекта, bounded экспорта,
dependency planner, raw validator/emitter и runtime. Уже имеющиеся recipes в
`generate_recovered.py` сохраняются в своих подтверждённых границах. Отдельные
компиляторы для боёвки, интерфейса или инвентаря не нужны.

- **Машинное состояние:** общие регистры и адресное пространство для целого
  пакета. Внутренним функциям не назначаются придуманные C++ типы или отдельные
  карты входных регистров. Read/write widths поступают из исходных операций.
- **Библиотечные границы:** один проверенный import может обслуживать повторные
  точные callsites. Его аргументы, результаты, clobbers и реализация закреплены;
  состояние приложения не подменяется пустыми callbacks.
- **Образы, ресурсы и lifetime:** будущий сборщик должен загружать подтверждённые
  ELF/library segments, relocations, globals/TLS и создавать/освобождать память
  согласно исходным вызовам. Общий владелец RAM уже есть; полной загрузки игры
  и автоматического восстановления allocator/resource ABI пока нет.

`inferred`, организация инструментария: эти границы можно собирать отдельными
plugins поверх одного emitter. Это не утверждение, что исходные функции имеют
только три вида поведения, или что существующие recipes покрывают всю игру.

## Режим shared_machine

Профиль задаёт только ELF, архитектуру и режим:

```json
{
  "schema": 1,
  "original_elf_sha256": "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b",
  "memory_space_id": 433,
  "execution_mode": "shared_machine"
}
```

Вместо per-function ABI используется один `RegisterFile&` и `Memory&`.
Сгенерированные entry имеют void-return, а исходные RETURN и прямые CALL/tail
переходы изменяют общую машину. Внешний entry caller явно предоставляет
исходное состояние и return sentinel. Неинициализированные регистры не
дополняются нулями. Имена символов в комментариях служат только навигацией.
Отдельный namespace `pcode_machine` позволяет безопасно сосуществовать с
прежними reviewed scalar wrappers.

```sh
python3 tools/lift_pcode.py research/lifted-ui/0*.json \
  --abi research/lifted-ui/shared-machine.json \
  --out /tmp/guest-program.hpp --report /tmp/guest-program.json
```

Пакет может включать любые exact exported bodies в поддерживаемой closure;
список одиннадцати сохранённых тел здесь является калибровочным входом.
Этот backend не объявлен production replacement всего приложения.

С 2026-10-03 поддержан `CALLIND`: pointer64 берётся из исходного register/unique
varnode и выбирает только exact entry включённого raw-тела. Общие регистры,
память, исходный push/RET и continuation сохраняются. Реальные vtable bytes
могут использоваться прямо; специального переписывания виртуальных методов нет.
Неизвестная цель вызывает `UntranslatedCallTarget` с числовым адресом для
последующего точного экспорта. [Автосборщик](shared-machine-package.md) добирает
static dependencies и exact entries из observed-target protocol;
автоматическое возобновление не подключено. Interior/zero/import targets этим
dispatcher не принимаются.

Caller-owned `CallDepth` ограничивает host C++ stack: профиль принимает
`max_call_depth` от1 до64, default64. Считаются все generated entries, включая
direct и tail lowering. Это бюджет адаптера, а не исходная глубина гостевого
стека: превышение останавливает исполнение явно, без придуманного guest result.
Динамическая рекурсия ограничена этим бюджетом; статические direct/tail циклы
пока отклоняются. Прежний scalar backend продолжает отклонять CALLIND, как и
его отдельная structural screening очередь.

## Общая память и imports

`pcode::AddressSpace` владеет снимками и явно выделенными областями гостевой
памяти. Числовые адреса не накладываются на host C++ объекты. Области могут быть
read-only или writable; неизвестные байты доступны после записи. Проверяются
лимиты, пересечения, uint64 overflow, unmapped/неинициализированные чтения.
Запись проверяет весь диапазон до мутации. `release` снимает exact mapping;
повторное явное отображение того же адреса создаёт новую область.

Optional `imports` в профиле перечисляет target и exact
`caller/instruction/pcode_index/kind=direct_call`, input/output/clobber register
ranges и `implementation_inputs` SHA. Runtime проверяет исходный pushed return
slot до и после callback, выдаёт отдельные входные/выходные banks, принимает
только все объявленные результаты и распространяет invalidation clobbers.
RSP/RIP и callee-saved register mutation через callback запрещены. Callback
исключения прекращают вызов; оригинальная C++ unwinding модель этим не создана.
Отсутствующий callback, stale SHA и лишний/несовпадающий callsite отвергаются.

## Остаток общего перевода

Пока отклоняются BRANCHIND, CALLOTHER, статически рекурсивные direct/tail closures, неподдержанные
floating/SIMD/x87 operations и varnodes шире8 байт. Не восстановлены общая
exception/unwinding модель, загрузка/relocation всех библиотек, host ABI мосты,
heap/TLS, исходный FP environment и общий boot/run path оригинала. Эти препятствия
обрабатываются как общие механизмы, а не заменяются догадками в игровых функциях.
Массовый код ещё не означает исполнимую или подтверждённую целую игру.
Режим переводит экспортированный raw CFG. Он не доказывает полноту symbol gaps
и exception landing pads: эти входы также должны пройти отдельную механическую
проверку. Отсутствие известного structural blocker не доказывает, что неизвестных
нет. Для функций со сложным unwind это остаётся конкретным препятствием.

## Проверено 2026-10-02

Один профиль без `functions` сгенерировал все11 сохранённых bodies, включая
двухуровневые direct/tail зависимости (maximum depth3). Header и общий RAM owner
скомпилированы в `shared_machine_queries_probe`; это отдельный engine calibration
probe, не новый Application binding. Он прошёл2470 сравнений с неизменёнными
GetInt/default bodies: результаты бит-в-бит, плюс собственные проверки RIP/RSP.
Оригинальные guarded fixture bytes неизменны. Остальные9 bodies компилируются
этим backend, но не получают новую native whole-function приёмку из двух probes.

Shared-mode tests7/7, полный compiler/runtime набор41/41 и screening25/25 PASS.
Общий AddressSpace прошёл строгую C++17 сборку и contract test. Семь выбранных
CTest gates (shared, память, screen, planner/export/pipeline/preparation) PASS.
Прежние scalar11 header и generation report побайтно неизменны. После runtime
изменения core и затронутые probes перестроены: старые native gates10540 и
scalar GetInt/default2470 прошли повторно. Прямые native controls/readback и
CEGUI handled-result consumer также PASS без input/frame/GL.

## Проверено 2026-10-03

[CALLIND calibration](shared-machine-indirect.md): семь неизменённых исходных
тел, пять косвенных callsites, три настоящие таблицы методов.3157 сравнений
результатов и initialized RAM/guards прошли без расхождений; guest probe также
проверяет исходный RET/RSP и callee-saved registers. Новые10 engine checks,
прежние shared7 и screening25 прошли; выбранные CTest gates6/6 PASS. Core и
probes перестроены. Scalar11 header/report побайтно совпадают с прошлым
результатом; rebuilt scalar и shared GetInt/default probes прошли по2470
native regressions. Новые source bodies не объявлены production переносом
и не увеличивают число full функций.

Сборка пакета теперь тоже использует shared emitter без per-function ABI:
missing direct/tail тела добираются через bounded exporter, наблюдаемые
CALLIND targets проверяются по exact ELF entries. Живой цикл сам экспортировал
scaledX/GetFloat, затем последовательно добавил пять наблюдаемых виртуальных
целей из verified cache.9-body C++ program скомпилирован; семь исходных тел
CALLIND chains снова прошли3157 native comparisons. Сборщик11 checks PASS;
игра и automatic replay не исполнялись. Подробная граница:
[shared-machine-package](shared-machine-package.md).

Это подтверждает новый механизм в указанной области, а не ускорение разработки
в несколько раз, процент восстановленной игры или полный запуск Torchlight.
Whole-game скорость ещё не измерена; для неё нужен широкий пакет с явными
числами exported/generated/executed/compared и количеством общих блокеров.
