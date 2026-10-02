# Целая стопка при автоматическом подборе

2026-10-02, `original-code`: `CInventory::findFreeSlot(CEquipment*) @0x91ba50`,
506 bytes, pinned ELF SHA
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Перенос — выбор существующей стопки внутри stack-enabled плотной portable bag.
Разметка pane/capacity/type routing остаётся вне перенесённой границы.

## Контракт оригинальной функции

Функция читает capacity u32 `inventory+0x28`, получает pane через
`getRequiredPane @0x91b9c0` и `getPaneIndex @0x91b050`, затем читает begin/end
из vector u32 `+0x78/+0x80`. `+0x14` — u8 stack-enabled; references:
pointer array `+0x30`, count/capacity u32 `+0x38/+0x3c`. Если индекс reference
за capacity, оригинал читает первый элемент. Slot ref содержит equipment
pointer u64 `+0x10`, slot number i32 `+0x18`. Equipment: resource GUID i64
`+0x1a0`, count i32 `+0x238`, maximum i32 `+0x23c`.

Блоки `0x91ba50..0x91ba99` выбирают границу; `0x91ba99..0x91bab8`
проверяют stack flag, positive maximum и непустой диапазон. Scan
`0x91bad0..0x91bbdd` ищет существующий equipment в каждом слоте, пропускает
null ref/null equipment, maximum==1, другой GUID и **сумму count, превышающую
maximum существующего предмета**. Не переносит часть incoming stack.

Необычное правило сохраняется буквально: `0x91bbc3` записывает `RBP` (incoming
pointer) в `R14`. После первого кандидата `0x91bbba` сравнивает count следующего
кандидата с `[R14+0x238]`, то есть с incoming count. Это не best-fit сравнение
с предыдущей найденной стопкой. Для incoming=5 и старых `[6,9,7]` выбирается
последняя 7, хотя 9 больше. При отсутствии кандидата scan
`0x91bb26..0x91bc48` ищет первый свободный slot, снова допускает только полный
fit, возвращает -1 при исчерпанном диапазоне. Нет записей полей или владения
ресурсами в этой функции.

## Подключение

`inventory_pickup_stack` потребляется непосредственно `PlayerInventory::store`.
Вход — оценённые owned potion descriptors и их resource GUID/count/maximum;
выход — индекс единственной принимающей стопки либо новая целая стопка.
`PlayerSession::pick_up` и `buy_potion` передают найденные/купленные instances,
проверяют ownership и получают реальный inventory ID. Bag consumers, potion use
и `CheckpointAccess::capture/restore_player` используют те же изменённые counts.
Стопки больше не распределяются частями между несколькими предметами.

Безопасная portable граница: входы count/maximum положительные, <=100000,
count<=maximum; evaluated descriptors должны совпадать. Оригинал сравнивает
только GUID. Portable IDs/порядок плотной bag, неограниченная ёмкость и отсутствие
native panes не объявляются исходными CInventory slots. Explicit drag-to-slot
имеет отдельную ветвь частичного переноса в `pickupEquipment @0x924bd0` и не
подменяется этим автоматическим подбором.

## Сравнение

`original_inventory_stack_comparison` исполняет **неизменённое целое тело**
`findFreeSlot` в private memory. Две внешние функции выбора pane заменены явно
названными constant-zero ABI adapters. Synthetic raw objects представляют
плотную occupied pane с одним следующим свободным slot. **6005** случаев
сравнивают возвращённый slot с production selector: count/maximum, чужие GUID,
нет whole-fit, maximum==1 и incoming-pointer replacement order. Это
ограниченное сравнение тела, а не оригинальный constructor или UI.

`inventory_instances` проверяет через настоящий `store/consume_one` два 18/20
плюс incoming 4 (результат `[18,18,4]`) и выбор `[6,9,7]+5 → [6,9,12]` с
сохранением ownership IDs. `consumable_cycle` исправлен по этому контракту:
два 2/3 остаются `[2,2]`; прежнее ожидание `[3,1]` закрепляло придуманное
распределение. Resource potion/purchase проверки используют тот же live store.

Отдельно для следующего торгового пакета: `generateMerchantInventory @0x836cb0`
пишет u8 **0 в inventory+0x14** на `0x836d16`; merchant inventory не объединяет
проданные стопки. `unitInit @0x889110` читает `MERCHANTINFINITE` UTF-32 key
`0xfd0568` и сохраняет u8 `equipment+0x25f @0x88967d`. В `menuItemClick` reuse
этого флага для count==1 и whole finite transfer для count>1 требует отдельного
переноса. Эти адреса — свидетельства для навигации, не завершённая торговля.

`completion: partial`: full native panes, sparse refs, original capacity/failure
handling, pickup/remove callbacks, item safe pointers и остальные CInventory
methods остаются открыты. Автоматические gates не повышают `completion`.
