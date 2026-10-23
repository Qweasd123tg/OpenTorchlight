# Спавн, сериализация и числовые строки — 23 октября 2026

Ещё 15 отсутствовавших игровых адресов перенесены поверх предыдущего пакета
из 50. Все новые тела DIFF; совместный адресный headless-прогон завершился:
31 тест PASS, 9108 completed сравнительных пар, different/incomplete/UNBOUND — 0.
Из них 8652 пары относятся к новым функциям и 456 — к шести прежним адресам
SpawnClassParser. Общий полный PASS на интегрированном снимке ещё не получен.

| TU | Новые адреса | Completed пары |
| --- | --- | --- |
| SpawnClass.cpp | `0xa751e0`, `0xa76100` | 1536 |
| SpawnClassParser.cpp | `0xa7f410`, `0xa816c0` | 508 |
| StringUtilities.cpp | `0xc8f600`, `0xc90060` | 3872 |
| PairStyle.cpp | `0xc6ae40`, `0xc6b4c0`, `0xc6c950` | 896 |
| BinaryStyle.cpp / OgreResourceFile.cpp | `0xc669f0`, `0xc695e0` | 768 |
| Itemsavestate.cpp | `0x8d1670`, `0x8d2390` | 324 |
| UnitThemes.cpp | `0xa67a00` | 180 |
| UnitSpawnerDescriptor.cpp | `0x65e3e0` | 568 |

Для каждого TU до восстановления проверен владелец opencode и получен ready
prepare-only пакет без existing/staged адресов и blockers; проверены хеши
пакетов, исходника, checkpoint и stage. После объединения заголовков подготовка
повторена для всех 15 адресов. После исправления возврата узкого GetArrayValueFloat
его пакет дополнительно подготовлен заново. Прежние определения полных TU
сохранены. В девяти изменённых TU сохранены 164 прежних emitted MATCH. Пять SDK
weak-функций компилятор больше не выпускает: два copy constructor Ogre::UTFString,
два ushort-string helper и char-string `_S_construct`. Изменённых emitted MATCH
и unknown references нет; отсутствующие weak replacement не подменяют native код.

## Сохранённые особенности оригинала

Узкий GetArrayValueFloat сравнивает индекс с уменьшающимся размером очереди,
но возвращает первоначальное число токенов. Широкий вариант использует
первоначальный размер и в условии цикла. Обе функции проверены с настоящим
TokenizeString, четырьмя rounding modes, FENV, errno, NaN/inf, Unicode,
embedded NUL, охранными словами массива и длинными deque. Для непустой строки
и пустого разделителя native TokenizeString не продвигается и зависает.
96 narrow и 64 wide таких входа не засчитываются как completed native пары;
отдельный typed tokenizer observer проверяет протокол вызова без выдуманного
early return. NULL-output с пустым разделителем проверяется нативно.

SpawnClass сохраняет различие между повторным чтением unweighted entry и
кешированием weighted entry до calculateChoices, порядок RNG/removeChoice,
повторные roll callbacks и добавление к непустому выходу. Fixtures используют
настоящие Character, SpawnClass, SpawnClassData и DataGroup с native C1/D1;
мутации pointer identity не подменяют владельцев.

Parser сохраняет map identity кешированного владельца и двухпроходное
разрешение forward references. Полный native каталог превышал 256 KiB capture;
теперь все прежние сериализованные поля без усечения проходят через streaming
SHA-256 и полный byte count. Known answers empty/abc/56-byte multi-block
проверяются при запуске. Counts, return, metadata и weak lifetimes остаются
явными. Отдельный completed negative меняет последнюю запись каталога и
подтверждает чувствительность к хвосту.

Три файловых serializer LoadDataGroupToFile возвращают int; согласованные
объявления исправлены в базовом интерфейсе и наследниках. Раскладка и порядок
vtable не меняются. Проверены native disk files, настоящий FileStreamDataStream
и MemoryDataStream, EOF, версии, repository IDs и владение. ItemSaveState
дополнительно проверяет legacy версии, owning sockets/effects, повторный load
с добавлением к непустому владельцу, float/int damage bonuses и большие
16-битные счётчики с точным сравнением файлов.

UnitThemes использует настоящие synthetic files и native LoadFile/SaveToFile;
перечисление файлов наблюдается на typed границе. Проверены пустые имена,
генерация и запись GUID, defaults ANY/ATTACHES, рост списка частиц за 10,
порядок и инвалидирование прежних владельцев. Это не полная проверка native FS.
Descriptor проверяет девять категорий, guard-ветви, повторные вызовы и native
кеши списков. RTTI, владельцы и weak invalidation настоящие.

## Ошибки fixtures и пределы проверки

Первый общий прогон имел пять FAIL и сохранён отдельно. Native root DataGroup
при parent==NULL удаляет non-global repository: переданный stack repository
приводил к повторному уничтожению. Fixture теперь передаёт heap repository
единственному native владельцу. Обе production load-функции не менялись.

В Descriptor fixture неверно предполагалось, что g_iTotalCountOfObjects —
число живых объектов. Native CRunicCore C1 увеличивает его, D1 не уменьшает;
это накопительный счётчик конструкторов. Теперь отдельно сравнивается setup
delta и требуется нулевой прирост во время actual calls и cleanup. Все
деструкторы и weak assertions сохранены. Равные аварии и InvalidReport не
принимались как PASS.

В предыдущем полном прогоне из 2367 тестов три isolated workers достигли
60-секундного лимита. Их адресный повтор с индивидуальным лимитом 180 секунд
завершился: LevelCharacterView 3072 пары, MissileFire 2048, LevelScreen
1024 + 1024 + 1024, всего 8192; incomplete/different — 0. Изменён только
параметр внешнего worker; тела, входы и лимиты runChild сохранены. Этот повтор
не заменяет свежий полный check.py перед коммитом.

Счётчик отсутствующих определений после интеграции подтверждён: 73. Объявленные
для корректных native calls inline helpers createSpawnClass и CPairStyle::Save
не входят в эту метрику ELF DB; их восстановление этим отчётом не заявляется.
Игровое окно не запускалось, играбельность гибрида не подтверждена.

Отдельное полное сравнение всех исходников после интеграции (`objdiff.py --all`,
`build-decomp/next-recovery/post-objdiff65.json`) подтвердило ровно 73 MISSING.
Это счётчик отсутствующих тел; он не заменяет общий headless gate. Команда
`check.py --no-game` с подключёнными source libraries пока не поддерживается и
завершилась до сборки, без записи результатов.
