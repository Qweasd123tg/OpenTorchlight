# Продолжение: моды, подземелья, аффиксы и логические события

После предыдущего среза `objdiff.py --all` подтвердил 73 MISSING в 308 исходных
TU; unknown references и ошибок сборки не было. Это число отсутствующих тел,
а не число функций до полной поведенческой приёмки всей игры.

Следующие шесть тел восстановлены по адресным ASM-пакетам. Владельцы TU —
`opencode`; после уточнения общих заголовков для всех четырёх TU заново выполнены
`types_export` и `llm_loop.py --prepare-only`. Все handoff — ready, blockers[],
назначенные адреса отсутствовали в подготовленном исходнике.

| TU | Адреса | Завершённые пары в отдельных проверках |
|---|---|---:|
| Mod.cpp | 0xc81ad0, 0xc82880 | 320 |
| dungeon.cpp | 0x9337f0, 0x934720 | 832 |
| affix.cpp | 0x7d4e20 | 768 |
| LogicObject.cpp | 0x7b2c70 | 700 |

Всего 2620 completed original/replacement pairs, без different/incomplete;
12 отрицательных контролей меняют наблюдаемое состояние после настоящего
вызова кандидата и обнаруживаются завершённым сравнением. Прежние определения
полных TU сохранены. Самостоятельные адресные сборки используют полный выбранный
TU, остальные игровые функции в них исполняются из оригинального ELF.

Общий срез подготовлен в `build-decomp/remaining73-next/joint6-continuation`.
43 теста включают 12 новых и 31 адресную регрессию предыдущих 15 функций;
выполнены 11728 completed pairs, все 43 PASS, UNBOUND[]. 48 прежних
MATCH четырёх TU сохранены без исключений; unknown[]. Шесть тел, четыре
заголовка и четыре fixture перенесены в основной рабочий снимок. После
интеграции полное сравнение всех 308 TU подтвердило ровно 67 MISSING.
Все 10626 прежних записей MATCH сохранены, без исключений; unknown[] и ошибок
сборки нет. CLI objdiff возвращает 1 при наличии любых DIFF: здесь это
не ошибка сборки и не результат canonical gate. Подробный JSON —
`build-decomp/remaining73-next/post-global-audit71.json`.

## Наблюдаемое поведение и уточнения заголовков

**Mod.** Настоящие CMod/CFileSystem/Master/OGRE owners, UTF-16 metadata,
рекурсивный обход реального временного дерева и настоящий Ogre archive проходят
C1/reload. Отдельный observer проверяет последовательность unload/list/add/access,
повторы, Unicode и изменения из callback. Файлы создаются только в /tmp.
Runic runtime экспортирует nonvirtual
`ResourceGroupManager::setResourceGroupAllowedToAccessFileSystemOnSearch`, которого
нет в upstream SDK header. Локальная копия закреплённого OgreResourceGroupManager.h
добавляет только это объявление, без полей или virtual-слотов; общий SDK cache не
изменён. Patch и ASM экспорта сохранены в ignored артефактах.

**Dungeon.** Четыре таблицы ключей извлечены из native initializer 0x92c240:
66 wstring с точными литералами, включая PPROPS_MAX и пустые ключи. Две пары
ключей представлены плоскими массивами по 22 элемента, индексация 2*i/2*i+1
совпадает с доказанным байтовым расположением. Заголовок DungeonCreationNames.h
объявляет эти данные; Dungeon.h включает его. getStrataTemplate проверяется
с настоящими native DataGroup/Template/Dungeon owners, FENV, identity кэша,
повторным чтением 44 float-полей и callback-изменениями. Загрузка ruleset у
конструктора Template — явная граница оснастки; native ruleset IO этой проверкой
не заявляется. Отдельные 192 пары loadDungeon используют настоящий SaveToFile/
LoadFile временных данных. Все native D1 и weak witnesses проверены.

**Affix.** Настоящие native Affix/Equipment/Effect/Hierarchy owners, /tmp FILE,
повторное добавление списков, расширение, изменение hierarchy из callback и FENV.
Duration -999 и <=0 имеют разные hasDuration; NaN и положительные значения
сохраняют native ветвление. Заголовки для этого TU не менялись.

**Logic Invoke.** Возвращает единицу; заголовок void уточнён до bool, единственный
вызывающий результат игнорирует. GetObject выполняется один раз. Ошибочные
object/descriptor/event не прекращают обработку связей, количество и элементы
списка перечитываются после callback. Для ошибочного event оригинал строит
диагностическую строку без присваивания переменной сообщения и пишет пустую
строку; это поведение сохранено. Native Editor/Scene/LogicObject/LogicLink/
LogicGroup/Descriptor/Settings owners и настоящий Ogre LogListener используются
без окна и файлового журнала. На ошибочных входах listener выключает debug до
второй потенциально некорректной диагностики. Same-crash не является PASS.

Первый native fixture выявил отсутствующий настоящий gEditor: SIGSEGV 7a6837,
чтение gEditor+0x66 в оригинальном InitiateInputEvent. Исправлен owner оснастки;
старая ошибка и два неуспешных среза Logic сохранены в v1-failed/v2-failed.

Полный canonical check предыдущего среза из 50 функций остаётся FAIL:
2364/2367 тестов, три worker timeout. Их неизменные тела после увеличения worker
лимита прошли отдельные 8192 пары. Общий check на новом снимке ещё требуется
перед коммитом; адресный PASS не заменяет этот gate и не доказывает играбельность.
