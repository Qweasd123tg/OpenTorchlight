OpenTorchlight — 200 новых принятых функций + сохранённая предыдущая сотня
10 октября 2026

РЕЗУЛЬТАТ

Закрыто 200 новых самостоятельных адресов первичного игрового кода.
Предыдущие 100 функций перенесены в обновлённый handoff и прошли свежую проверку.
Они вынесены в carried-100.csv и не входят в число 200 новых функций.
Общая прибавка к присланному обновлённому handoff: 300 адресов.

Приёмка: 2380 -> 2680 из 5247 первичных игровых функций.
Новые: 16 MATCH и 184 EXECUTED_COMPARISON.
191 новых адресов имеют выполненные адресные сравнения;
суммарно 117101 завершённых пар оригинал/замена, без различий и незавершённых вызовов.
Часть функций с MATCH также дополнительно проверена сравнением поведения.
Полный headless-набор: 611 тестов, 0 ошибок.
Точные первичные MATCH всей базы: 2134 -> 2156.
Потерянных ранее принятых адресов, ранее точных первичных MATCH и функций предыдущей сотни нет.
Добавлено покрытие 93343 байт исходного машинного кода только новыми 200 адресами.

Закрытие включает восстановление недостающих реализаций и доведение существовавших
DIFF-реализаций до адресной приёмки. Исходные статусы новых адресов: {'DIFF': 73, 'MISSING': 122, 'UNLISTED': 5}.
Алиасы C1/C2 и D1/D2 считаются один раз по адресу; шаблоны STL, библиотечные функции
и служебные инициализаторы компилятора в число 200 не включены.

Новые функции по TU:
  EditorDLL.cpp                     36
  Descriptor.cpp                    22
  EditorScene.cpp                   15
  astarpathfinder.cpp               10
  Shape.cpp                         9
  ObjectControl3D.cpp               8
  FileSystem.cpp                    7
  Inventory.cpp                     7
  continuegamemenu.cpp              7
  dropdownmenu.cpp                  6
  questmenu.cpp                     6
  FileReader.cpp                    5
  diemenu.cpp                       5
  AIStatWatcher.cpp                 4
  GameStateController.cpp           3
  RunicCore.cpp                     3
  cinematicmenu.cpp                 3
  leveltemplatedata.cpp             3
  questdialogmenu.cpp               3
  randomizer.cpp                    3
  tipmenu.cpp                       3
  EditorBaseObject.cpp              2
  GraphManager.cpp                  2
  ModelViewerScene.cpp              2
  SceneNodeObject.cpp               2
  Settings.cpp                      2
  dialogmenu.cpp                    2
  fishingmenu.cpp                   2
  modalmenu.cpp                     2
  optionsmenu.cpp                   2
  AIManager.cpp                     1
  CollisionAvoiderWrapper.cpp       1
  Editor.cpp                        1
  LogicTimer.cpp                    1
  OutputIncrementor.cpp             1
  ResourceSettings.cpp              1
  StringTranslate.cpp               1
  TriggerBox.cpp                    1
  TriggerSphere.cpp                 1
  difficultymenu.cpp                1
  mainmenu.cpp                      1
  settingsmenu.cpp                  1
  utilities.cpp                     1
  waypointmenu.cpp                  1

КАКОЙ ПАТЧ ПРИМЕНЯТЬ

changes.patch — к обновлённому handoff, присланному в этом сообщении.
Он включает предыдущую сотню и новые 200 адресов; полный результат — 300 дополнительных функций.

new-200.patch — к этому же обновлённому handoff, если предыдущий пакет 100 уже перенесён.
Он содержит только разницу от состояния «обновлённый handoff + предыдущие 100».
Точные исходные хэши для обоих вариантов сохранены в verification/.
Применяется один из этих двух патчей. Хэши позволяют проверить выбранный вариант
без предположений о состоянии рабочей копии.

База: commit 7bc6ca009ec5c3872cd8f3719014690a24119385
Tree: bae3d5676fd1523ad96e471df571d827a389f313
ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
Компилятор: GCC 4.4.7 20120313 (Red Hat 4.4.7-3), настройки обновлённого handoff.

ПРИМЕНЕНИЕ К ОБНОВЛЁННОМУ HANDOFF

  python3 /path/to/package/verify_files.py /path/to/OpenTorchlight --patch all
  cd /path/to/OpenTorchlight
  git apply --check /path/to/package/changes.patch
  git apply /path/to/package/changes.patch
  python3 /path/to/package/verify_files.py . --patch all --after

ЕСЛИ ПРЕДЫДУЩАЯ СОТНЯ УЖЕ ПЕРЕНЕСЕНА

  python3 /path/to/package/verify_files.py /path/to/OpenTorchlight --patch new
  cd /path/to/OpenTorchlight
  git apply --check /path/to/package/new-200.patch
  git apply /path/to/package/new-200.patch
  python3 /path/to/package/verify_files.py . --patch new --after

Для дерева без git в files/decomp/ лежат полные версии всех изменённых файлов.
Если проверка исходных хэшей не проходит, рабочая копия содержит дополнительные
изменения: перенесите нужный diff с учётом этих изменений, затем выполните приёмку.

ПОВТОРНАЯ ПРОВЕРКА НА ВАШЕЙ МАШИНЕ

  source handoff/env.sh
  python3 tools/decomp/check.py --json build-decomp/progress.json

Нужны закреплённый toolchain, исходный Torchlight.bin.x86_64, его runtime-библиотеки
и pak.zip согласно handoff/env.sh. В этот архив включены изменения проекта и
свидетельства проверки; исходные игровые ресурсы и toolchain берутся из handoff.
Переносимый протокол описывает именно проверенные здесь входы. Новая сборка создаёт
свежие привязки свидетельств к своим исходникам, объектам и внешним ресурсам.

ПРИЁМКА И ГРАНИЦЫ РЕЗУЛЬТАТА

Выполнены неизменённые publication.Stage.validate и Stage.publish. Общая проверка
собрала все TU и весь headless-набор; затем локальная публикация заново проверила
идентичность опубликованных исходников и скомпилированных объектов.
Исходные файлы TU, занятых другими владельцами в owners.json, не изменены.
Инструменты приёмки, конфигурация, frozen/remake/pcode/process-файлы не изменены.
Графический игровой процесс не запускался; сравнения выполняются до main.

MATCH означает приёмку objdiff по критериям проекта. EXECUTED_COMPARISON означает
совпадение наблюдаемого поведения оригинала и замены на выполненных сценариях.
Это не утверждение о доказанной эквивалентности для всех возможных входов.
Все новые DIFF приняты по фактически завершённым вызовам конкретного адреса;
порог приёмки и проверки полноты наблюдений сохранены.

Оригинальные особенности ABI, порядка вызовов, float и контейнеров сохранены.
Некоторые исходные команды редактора имеют защитный порог больше физического
буфера 4000 байт: тесты используют безопасные входы и не исполняют переполнение.

СОСТАВ

README.txt                        результат и применение
PATTERNS.txt                      найденные закономерности и важные исключения
changes.patch                     полный перенос к обновлённому handoff
new-200.patch                     добавка к handoff с уже перенесённой сотней
files/decomp/...                  98 полных изменённых/новых файлов
functions.csv                     новые 200 адресов, статусы, тесты и хэши объектов
carried-100.csv                   предыдущие 100 адресов и свежая проверка
verify_files.py                   проверка совместимости и результата применения
verification/summary.json         итоговые числа
verification/functions.json       полный реестр новых функций
verification/carried-100.json     сохранённая сотня и её свежие свидетельства
verification/selftest.log         полный итоговый протокол
verification/progress.json        objdiff и привязки сравнений итогового состояния
verification/baseline.json        objdiff и приёмка исходного обновлённого handoff
verification/baseline-selftest.log исходный headless-протокол
verification/files.json           SHA-256 файлов для полного патча
verification/incremental-files.json SHA-256 файлов для добавочного патча
verification/publication.log      журнал полного Stage gate
verification/patch-application.json проверка применения обоих патчей по SHA-256
verification/origin.json          происхождение базы и предыдущего пакета

Оба патча проверены через git apply --check, реально применены к отдельным копиям
соответствующих исходных файлов и сверены побайтово по SHA-256 с принятым результатом.
