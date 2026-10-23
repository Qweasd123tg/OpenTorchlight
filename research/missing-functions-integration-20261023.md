# Объединение decomp перед остановкой — 23 октября 2026

По просьбе пользователя восстановление новых функций остановлено после
текущих rollRandomGroups и CAutomap::setFullMap. Оба тела завершены и прошли
совместную проверку. Все назначения помощникам завершены.

## Состав дерева

- Пачка PR #164, commit 5f61a0c: 39 ранее отсутствовавших определений.
- Продолжение 717ef75: 20 определений.
- Текущая работа поверх 717ef75: 84 определения; инвентарь 138 → 54 MISSING.
- Подтверждённый repair прежнего CUnitThemes C1, устраняющий double-free.
- Опубликованная общая интеграция PR #185, commit 232e97b: 42 компонентных PR
  с исходниками и проверяющими инструментами. Отдельный screening-driver #181
  остаётся за пределами этого среза, как в опубликованной интеграции #185.

185 объединён обычным merge без переписывания истории. Проверено, что 42
его файла точно совпадают с опубликованными blob; llm_context.py и его тест
совмещены трёхсторонним merge с тремя добавленными в #164 точными weak destructor
декларациями. Все 2919 остальных входов нашей работы сохранены по SHA256.
Исходники, SDK cache и незакоммиченные данные корневого main не переносились
из произвольных соседних checkout. Точная база — ветки/commits выше и наши
проверенные полные TU в рабочем дереве codex/finish-missing-20261023.

## Адресные проверки

Подробности и ветви перечислены в отчётах:

- [Первый срез](missing-functions-continuation-20261023.md).
- [Runtime и PathController](missing-functions-runtime-20261023.md).
- [Serialization и spawn](missing-functions-serialization-spawn-20261023.md).
- [Mods и dungeon](missing-functions-mods-dungeon-20261023.md).
- [Resource manager, mesh и UnitThemes repair](missing-functions-resource-mesh-20261023.md).
- [Automap addTile и compressed loader](missing-functions-automap-compressed-20261023.md).
- [Последняя пара](missing-functions-final-pair-20261023.md).

Три последних совместных прогона: 42 tests / 11568 completed пар,
15 tests / 3000 completed пар и 20 tests / 4600 completed пар; все PASS,
different/incomplete равны 0, unbound []. Каждому перенесённому DIFF
соответствуют завершённые сравнения с оригиналом; семантические отрицательные
контроли также завершены. Последний полный static inventory перед присоединением
tooling #185: 308 TU, 54 MISSING, unknown [] и compile errors [], все 10691
прежних MATCH сохранены. Этот инвентарь не подменяет новую canonical приёмку.

## Общий gate

- `python3 -m unittest discover -s tools/decomp -p 'test_*.py'`: 1333 tests,
  OK (50.112 s; полный процесс 51.043 s).
- Полный `python3 tools/decomp/check.py` на коде `ced9bb7`: **FAIL**, returncode 1,
  2424 tests / 4 failed, 11047.805 s. Статическая часть и сборка гибрида завершены
  без compile errors и unknown references; инвентарь — 54 MISSING.
  Статически MATCH 3225 из 5247 игровых функций и 993 compiler-generated
  initializers/destructors вне этого счёта. Из-за общего FAIL checker не принял
  новые DIFF по этому полному прогону; новый общий accepted-процент не заявляется.
- Сбои: `complete_ui_dropdown_map`, `complete_ui_dropdown_title`,
  `complete_trigger_action`, `compressed_object_native`. Все четыре повторно
  проходят отдельно на том же неизменённом бинарнике. Это не отменяет полный FAIL.

Обе последние игровые функции прошли и в этом полном прогоне:
automap_full_native (0x92b4b0) — 256 completed пар;
random_groups_native и random_groups_observed (0x74c900) — 480 + 480.
Различий и incomplete нет.

У loader-фикстуры найден неинициализированный optional output-list pointer:
родной CDescriptorLoadConfiguration C1 по 0x701e20 имеет MATCH и оставляет +0x38
неопределённым; тест теперь явно задаёт m_createdObjects = NULL до вариаций
created-list. У dropdown-фикстуры родной C1 оставляет +0x18/+0x20 для createMenus,
который fixture намеренно пропускает; эти два указателя теперь явно NULL.
Диагностическое заполнение только этих двух raw slots значениями 1/2 перед
настоящим C1 воспроизвело падение прежней фикстуры в CEGUI destroyWindow.
Исправленная фикстура при таком же заполнении прошла map 32 и title 24 пары.
Это диагностика причины, а не замена обычных завершённых native-сравнений.
Игровые функции, заголовки и инструменты после `ced9bb7` не менялись.
Сверка двух hybrid manifests также подтвердила одинаковые SHA256 всех 312
production source files и всех 312 production objects до и после fixture repair.

После этих двух исправлений полный текущий гибрид адресно проверен:
compressed native/observed — 2 tests / 480 completed пар и 2 completed negative
controls; dropdown ctor/map/title/open/update/create — 6 tests / 272 пары;
trigger modes/skills с настоящим teardown — 1 test / 1152 пары. Итого 9 tests /
1904 completed пары, 0 different, 0 incomplete, PASS. Причина единственного
падения trigger worker в полном порядке не установлена. Ограниченный повтор
45 предшествующих тестов соответствующего shard на старом canonical blob также
прошёл: 25999 completed сравнений в 49 coverage rows, 0 different, 0 incomplete;
trigger worker и настоящий teardown завершились штатно. Диагностическое
заполнение трёх native CGameClient allocations перед их настоящими C1 также
не воспроизвело сбой. Необоснованных изменений trigger fixture не внесено.
Адресные повторы не заменяют завершённый полный gate; после fixture repair
нового полного PASS нет. **MERGE HOLD сохраняется.**

SHA256 лога ограниченного повтора порядка:
`43a68276d4c23076381f3062f63423939a8a1d348b6acc10313601c4f668dc26`.

Во время полного прогона исходники, заголовки, инструменты и third_party не
менялись; его артефакты сохранены до адресных повторов. SHA256 полного лога:
`82556e6041f40263b790f9b4075731622fe6465c9a2f24f1f4c342d4a843e2cf`;
progress snapshot:
`290f3423a6129ac7956a7380faa912a908a332168e932b4ed0a94923405a09d6`.

В #185 сохранено ограничение: RunicCore D1/D2 по 0xd79920 остаётся DIFF с
неподтверждённой EH LSDA equivalence в исходном frozen comparator. Отдельный
ручной EH/CFI audit не превращает его в MATCH. Новый gate фиксируется отдельно.
Живой сеанс игры с окном в эту приёмку не входит.

Проверка `git diff --cached --check` чиста для изменений проекта, кроме
унаследованного оформления двух добавленных SDK-заголовков: OgreMesh.h
(99 предупреждений) и OgreResourceGroupManager.h (121). Их байты совпадают
с закреплённым OGRE SDK после удаления только двух документированных добавлений
Runic (поле mMaxBoneAssignments и объявление filesystem-access метода).
Новые объявления предупреждений не содержат; форматирование SDK сохранено.
Проверка с исключением ровно этих двух путей проходит. Сверка и SHA256 сохранены
в sdk-formatting.json среди ignored-диагностик.

Ignored-диагностика общей интеграции:
build-decomp/pr-final-integration-20261023/ (composition.json, snapshots,
tools-suite.log, canonical-check.log и отчёты результатов).
