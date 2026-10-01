# Caves: RANDOMIZED и единственный выход сцены

2026-10-02. Продолжение [menu-themes.md](menu-themes.md). ELF/pak и Caves
rules/root-layout уже закреплены в [menu-theme-inputs.json](menu-theme-inputs.json).
Внешние ресурсы и бинарник не изменены. Whole functions остаются partial;
нет заявления о переносе native catalog/RNG состояния.

## Исходная цепочка и исправленная граница

В предыдущем проходе порт отклонял любую RANDOMIZED menu theme. Это была
граница реализации, не доказательство, что Caves требует нескольких комнат.
Исходные [ASM окна](disassembly/menu-caves.asm) показывают конкретную ветвь.

`resource-derived`: mainmenu_cavesrules.dat содержит RANDOMIZED=true,
один CHUNKTYPE `1X1SINGLE_ROOM_CAVE`: ENTRANCE_CHUNK=true, EXIT_CHUNK=false,
MUST_PLACE=false, MAX_APPEARANCE=1, размер1x1, без EXIT точек. MINCHUNKS=0,
MAXCHUNKS=0, REQUIRESEXIT=false. Authored LAYOUT содержит один chunk того
же типа с offset0. Единственный concrete layout — MAINMENU_CAVES.LAYOUT.

`original-code`: CLevelTemplateData::load читает ENTRANCE_CHUNK bool с default
false (`0x977fee..0x977ff8`) в type byte+0x10. Ненулевой entrance flag
вызывает addChoice у entrance chooser (`0x978bac -> 0x979578..0x97958e`).
Authored LAYOUT каталог создаётся независимо: chooser pointer64+0xe8 и
addChoice каждого LAYOUT `0x978c94/0x978d26`.

CLevel::loadRoomLayout проверяет byte+0x762 (generated) и byte+0x58
(RANDOMIZED) `0x95fe0e..0x95fe1f`, затем делает10 вызовов createRandomLayout(0)
`0x960fd5..0x960fe4`. После них повторно setSeed и getRandomLayout
`0x96101e/0x96102a`. Поэтому нельзя объявлять Caves no-entrance early-exit:
её entrance chooser **не пуст**. Эта предварительная гипотеза была отклонена
ресурсным тестом до принятия изменений.

createRandomLayout: entrance chooser вызван `0x97348e`, его единственный
возможный type index0 записывается в chunk uint32+0x10. Chunk position float32
+0x20/+0x24/+0x28 =0 на `0x9734cb..0x9734d9`. RandomIntegerBetween читает
min/max int32+0x74/+0x78 `0x9735bf..0x9735c5`; при0..0 возвращает0. Условие
middle-loop (`0x9735de..0x9735fa`) не добавляет chunks. REQUIRESEXIT byte+0x59
на `0x973b90` false пропускает exit-placement. MUST_PLACE count32+0x48
`0x9745d9` равен0. Для единственного instance проверяется concrete chooser
hasValidChoices `0x974b41`, затем выбирается один concrete index через getRandom
и сохраняется CChunk pointer; resetOdds и добавление CLevelLayout выполняются
в общей source цепочке. getRandomLayout `0x9713c0` выбирает любой каталоговый
entry. Authored entry и все10 generated entries имеют один и тот же type,
layout path и position0. Выход геометрии и markers не зависит от выбранного
catalog index или seed. Их **RNG-state effects остаются неперенесёнными**.

## Перенос и consumers

`build_saved_menu_scene` разрешает RANDOMIZED только при полном проверенном
предикате: один type и authored chunk, type совпадает, entrance true, exit/
must false, exits.empty, MAX_APPEARANCE=1, middle min/max0, REQUIRESEXIT=false.
Прежние проверки offset0, единственного concrete layout и camera/player markers
сохранены. Другие RANDOMIZED rules по-прежнему отклоняются. Условие не
проверяет имя Caves: оно следует контракту источника и данным, а не имени файла.

Перенос использует доказанное постоянство scene output, **не вызывает** новый
заменяющий RNG и не записывает native generation/catalog fields. Static room,
expanded links, source camera/player placement и IDLE/weapon идут через уже
подключённую committed Save & Menu цепочку. Ни очередность исходных RNG draws,
ни random Group decorations этим расширением не объявляются восстановленными.

## Проверка

Desktop, shared Application probe и menu CPU test собраны. Узкий gate5/5:
menu scene/core, original menu resources, save checkpoint, original players
и original equipment. Main OTC depths17/20 проходят тот же camera/player/body/
hand contract, что остальные темы. Source coordinates: camera
(4.91000986,3.5150001,-7.15001011), target
(0.500001013,0.829999983,-0.00999784004), player
(1.11000001,1.83000004,-1.00999999). Geometry193 instances, conditional omitted0.
Всего14 first/last Main theme cases. Существующий portable generator отдельно
проверен на seeds1/77/0x7fffffff/0xffffffff: один chunk с этим layout, position0.
Это проверка инварианта результата, не RNG differential parity.

Новые UI-клики, кадры, сквозные сценарии и original process не запускались.
Registry sync прошёл: **237 bounded /161 cited** addresses. Legacy stages
отражают только connected scene-output invariant, whole completion partial.

Основная случайная генерация, catalog/state/allocator/native lifecycle,
random-dungeon delegates и зависимый декор остаются open. Следующий RNG пакет
должен учитывать compiled-layout Group creation order и реальный stream prefix;
передача произвольного seed не закрывает этот контракт.
