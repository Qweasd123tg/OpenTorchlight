# Продолжение decomp: Automap addTile и compressed object loader (2026-10-23)

База — рабочая ветка codex/finish-missing-20261023, HEAD 717ef75 и 80 ранее
восстановленных функций; перед срезом 58 MISSING. Работал один помощник.
Все кандидаты сначала готовились через llm_loop --prepare-only. Для совместной
проверки создана новая frozen-база с обоими header overlays и новые ready-пакеты
для обоих адресов; проверены checkpoint, stage, source и prompt hashes,
blockers/existing/staged lists пусты.

## CAutomap::addTile — 0x928910

Источник сохраняет создание billboard, исходный порядок обновления min/max,
точные пять таблиц атласа float[34], UV inset, atan2 и перевод градусов,
размер, поведение animated/npc и списков reveal. Добавлены только декларации
существующих таблиц в Automap.h: каждое исходное STT_OBJECT занимает 136 байт;
раскладки владельцев не менялись. За пределами верхней границы исходный код
использует fallback index 5. Искусственный нижний clamp не добавлен: неположительные
номера оригинал использует как индекс до начала таблиц, они не выдаются за
валидную предметную область теста.

Локальная проверка: 1216 completed пар, 0 different/incomplete; шесть отдельных
завершённых semantic negatives меняют UV, rotation, dimensions, bounds,
NPC reveal и map reveal. Проверены все 34 atlas types, fallback 35/36/1000/INT_MAX,
все четыре animated/npc сочетания, рост/резерв vector, signed zero, NaN/Inf,
alias-параметры из настоящих billboard. Фикстура использует настоящие native
Automap C1/D1, ResourceManager и OGRE SceneManager/BillboardSet/Billboard;
GPU seams ограничены подготовкой и очисткой. Проверяется и удаление владельцев.
Все 18 прежних MATCH этого TU сохранены; новая функция DIFF, 1030/1026 байт.

## loadObjectByCompressedFile — 0x74c660

ASM подтверждает bool return, проверку равенства reader position/size по
0x14/0x10, native virtual CreateObjectByDescriptor в scene slot 0x1d8,
добавление в configuration.m_createdObjects перед native binary load и
игнорирование переданного parent: родитель читается из бинарной записи.
EOF и sentinel -1 возвращают true; отсутствие descriptor, неудача создания
и binary load возвращают false. В обычном режиме дети загружаются рекурсивно;
в режиме random group читаются три metadata-слова и записываются в поля
0x118, 0x10c и 0x110 без рекурсии. Для доступа к полям reader добавлен friend
существующей функции, новых полей или изменений ABI нет.

Кандидат — DIFF, 670/662 байт; все 87 прежних MATCH сохранены. Первый native
прогон: 480 completed пар без различий, два завершённых отрицательных контроля.
Фикстура создаёт настоящие native Scene/ResourceManager/RandomGroup/LogicGroup,
использует настоящие Descriptor и COgreReader, а поток получает штатной
saveObjectInBinaryFile. Проверяются EOF, sentinel, неизвестный descriptor,
рекурсия/сбой ребёнка, UTF16 имена, remaps, поля групп, исходные/растущие списки,
неполные записи ровно на границе read. Отдельная наблюдаемая граница логирует
и вызывает настоящие зависимости, а также задаёт NULL/false и меняет ссылку
выходного списка. В финальной фикстуре наличие списка независимо от group flag;
первый вариант и его PASS сохранены отдельно.

## Совместная приёмка

Свежая совместная сборка всех текущих исходников прошла **15/15 labels,
3000 completed пар, 0 different, 0 incomplete, unbound []**. Проверены три
новых теста и прежние тесты автомапы, настоящих scene objects, Descriptor
binary и COgreResourceFile. Полный статический инвентарь: 308 TU,
**56 MISSING** вместо 58, unknown [] и compile errors []; все прежние
**10 689 MATCH** сохранены. Оба кандидата, overlays и fixtures перенесены
в рабочее дерево. Коммита нет.

Ignored-артефакты: build-decomp/remaining58-next/joint2-continuation/
{prepared.json,assembly.json,result.json,run.log,raw.log,global-objdiff.json,
global-audit.json,integration.json}. SHA256 run.log:
23a9d6a48a2a55d49e2f6782ca8c617ce07aaa5c23d827a80d1fc3ccdf8e137f.

Полный tools/decomp/check.py перед коммитом остаётся обязательным. Предыдущий
canonical запуск среза 50 имел 3 worker timeout; адресные повторы прошли,
но новым полным PASS это не считается. Срезы остаются без коммита; окно игры
не запускалось и играбельность живого сеанса не подтверждалась.
