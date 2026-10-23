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
- Полный `python3 tools/decomp/check.py` на окончательном объединённом дереве:
  PENDING, идёт нативный самотест. Статическая часть и сборка гибрида завершены
  без compile errors и unknown references; инвентарь — 54 MISSING.

Прежние адресные PASS и исправленные worker timeout не выдаются за новый
полный PASS. Во время общего прогона исходники, заголовки, инструменты и
third_party не меняются.

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
