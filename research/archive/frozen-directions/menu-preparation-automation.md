# Автоматизация подготовки и проверки Main/Dropdown

> **Архив замороженного направления.** Указания, команды, очереди и числа ниже
> относятся к прежнему снимку; они не задают текущую работу или приёмку.
> Действующий процесс: [decomp](../../../decomp/README.md).

2026-10-02. Статус: `port-native tooling`. Расширены существующие
`function_package.py`, `prepare_family_packet.py`, `auto_triage.py` и
`work_frontier.py`; отдельный оркестратор или реестр не вводился.

## Повторяемый путь

Один запуск `prepare_family_packet.py ... --build-dir build-cegui --check`:

1. Декодирует целые выбранные функции и группирует structural shapes;
   сохраняет конкретные member deltas, границы, callers и callsites.
2. По собственным библиотечным символам и прямым callees ищет локальные
   CEGUI/OGRE/ParticleUniverse spelling candidates. Читает vendor corpus один
   раз на batch, разделяет namespaces библиотек, сохраняет file/line и hashes.
   Учитывает external имена без аргументов старого графа и полные PLT symbols.
   Доступные source/version manifests входят в fingerprint. Отсутствие hit
   явно видно; совпадение имени не закрывает ABI, overload или vendor delta.
3. Сопоставляет **уже записанные** test files с CTest/Ninja dependencies;
   использует общий `check_selection` для fixture closure и build targets.
   В `test-plan.json` видны unmapped files и исключённые UI/render/desktop tests.
4. С `--check` собирает цели и исполняет CPU/resource/reference проверки.
   Записывает JSON/log/JUnit. Skip, пустой набор, неизвестные результаты,
   build failure или изменение исходников не превращаются в PASS.
   Существующий CMake cache не перенастраивается. Без `--check` остаётся план.

Команда и правила output: [codefirst-tooling.md](codefirst-tooling.md).
Генерируемые пакеты и CALL index остаются в ignored build или `/tmp`.

Дополнение того же дня: с `--build-dir` индекс автоматически экспортируется
или переиспользуется после проверки input/generator/tool/content hashes.
При cache hit full objdump/nm не выполняются, index/sidecar не переписываются.
`summary.json` содержит краткие source-hit/missing и open-code counts, а также
выбор проверок: не нужно загружать весь пакет в модель для выбора карточки.
Эти механические шаги работают без LLM/API/сети; новое содержательное ревью
по-прежнему не выводится из cache hit или счётчика.

## Исполненный пример

Внешний read-only ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`createMenus`, class regex `^(CMainMenu|CDropdownMenu)$`:
`CDropdownMenu::createMenus @0xb196f0` и `CMainMenu::createMenus @0xc52a10`.
Оба тела сохранены; 2 structural representatives, одного только сходства
имён для общего перевода недостаточно.

Индекс binutils: 239452 direct sites, 6061 indirect, 8 unattributed.
Это статические адреса/повторы, не порядок исполнения или resolved virtual ABI.
В карточках Dropdown 14 библиотечных member queries / 11 с локальными hits;
Main 8 / 8. Итого 19 из 22 **записей**, с повторяющимися между карточками
зависимостями; это не 19 полностью восстановленных библиотечных функций.
Примеры: CEGUI WindowManager::createWindow, Window::recursiveChildSearch,
PropertySet::setProperty и String::grow ведут к реальным vendored source files.

Все 7 записанных test files сопоставлены. Выбрано 8 проверок; 2 integration
проверки вынесены отдельно. Сборка и 8/8 прошли, skipped=0,
source_consistent=true в автоматическом `--check` запуске. Проверены bounded
Mainmenu/dropdown/window/sound contracts и error boundary; нового GUI или
полного original game process не было. Отчёт во временном пакете
`/tmp/opentorchlight-menu-automation-20261002-pass3/checks.json`.
Tooling gate: function_auto_triage, function_package_automation, codefirst_tools.

## Исправление очереди вместо ложного процента

Свежая сортировка 17023 адресов после исправления:

| Маршрут | Адресов |
|---|---:|
| Без отдельного глубокого разбора сейчас, включая FLTK deferral candidates | 6533 |
| Сначала сопоставление библиотечных исходников | 3623 |
| Семейство/target/initializer batch review | 2094 |
| Проверить игровые consumers shared scene/descriptor candidates | 1600 |
| Остаток без найденного механизма сокращения | 3173 |

Категории не пересекаются. Это маршруты работы, а не готовность или сроки.
Наличие библиотеки в маршруте source-first не доказывает наличие подходящих
исходников локально. Динамические библиотеки находятся вне этих main-ELF адресов;
на практике уже подключён полный vendored CEGUI source и OGRE math subset.

Убрано ошибочное deferral по одному имени CEditor*/параметру CEditorBaseObject*.
Эти имена употребляются загрузчиками сцен и игровыми descriptors.
`original-code`: loadObjectByCompressedFile @0x74c660 разобран в
[menu-player-preview.md](../../menu-player-preview.md). CEditorScene::loadScene
@0x7502c0 вызывает loadCompressedLayout @0x74ce10 на 0x750978.
Name heuristic теперь возвращает `check_runtime_dependencies`, а не editor-only.
FLTK UI остаётся отдельным **кандидатом** на отложенную границу.

Global ctor/dtor/static initializer routing сохраняет review effects.
`original-code`: global constructor @0xc92eb0 пишет g_Rand @0x14ecaf0
на 0xc9302f и g_RandVolatile @0x14ecaf8 на 0xc9303d. Поэтому его наличие
среди compiler glue не разрешает выбросить seed producers.

## Остаток

Произвольный ASM -> производственный C++ автоперенос не реализован.
Для уже принятых контрактов подключена генерация рабочего UI binding/RNG кода
и весь build/comparison/registry путь: [recovery-automation.md](../../recovery-automation.md).
Повторные поиски исходников, сбор тел/дельт и выбор/исполнение известных проверок
теперь автоматизированы существующим маршрутом. Общая реализация семейства
принимается после проверки member deltas и реальных consumers.
Автоматизация не меняет stages/completion и не подменяет неизвестное приближением.
