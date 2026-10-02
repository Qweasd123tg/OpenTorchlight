# Продажа и выкуп проверенных зелий

2026-10-02. `original-code`: ELF SHA
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`resource-derived`: внешний `pak.zip` SHA
`8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`.
Участники: `CGameUI::menuItemClick @0xa8f780` (10484 bytes),
`CEquipment::sellPrice @0x86fb40`, `buyPrice @0x86fc20`,
`CCharacter::giveGold @0x811a70`, `generateMerchantInventory @0x836cb0`,
`CEquipment::unitInit @0x889110`, `CPlayer::soldItem @0x8e41a0`.
Полное закрытие `menuItemClick` не заявляется: это normal identified potion
transfer, free destination capacity и корректное существующее владение.

## Контракт участников

| Поле оригинала | Тип / начальное состояние / readers / writers |
| --- | --- |
| Equipment `+0x238` | i32 count; ctor 1; price и transfer ветви читают; stack/uses ветви изменяют |
| Equipment `+0x25f` | u8 MERCHANTINFINITE; ctor 0; unitInit читает UTF-32 key `0xfd0568`, пишет `0x88967d`; menuItemClick читает |
| Equipment `+0x264/+0x268` | i32 identified buy/sell; recalculatePrice writer; price methods readers |
| Equipment `+0x26c/+0x270` | i32 unidentified buy/sell; эта transfer граница не допускает unidentified objects |
| Equipment `+0x348` | u8 identified; price выбирает identified branch; все принятые potion resources генерируются identified |
| Equipment `+0x1b0` | u64 original data pointer; infinite clone передаёт его в createUnit |
| Character `+0x444` | i32 wallet; giveGold обновляет с clamp 0..INT_MAX; buy gate читает |
| Character `+0x640` | u64 parent-character pointer; giveGold следует до null, затем изменяет wallet; у player projection parent отсутствует |
| Character `+0x490` | u64 inventory owner; sale/rebuy передают в remove/pickup |
| Inventory `+0x14` | u8 stack-enabled; ctor 1, generateMerchantInventory `0x836d16` пишет **0**; merchant не объединяет проданные стопки |
| GameUI `+0x38/+0x4f0` | u64 player / merchant menu; menu virtual `+0x20` open и `+0x10` owner |
| GameUI `+0xb8/+0xc8` | u64 held equipment / source character; drag safe pointers остаются вне нового пути |

Оригинальная normal Shift-sale ветвь: `0xa906c0..0xa9070d` проверяет найденный
предмет, открытый merchant menu, source не merchant и !ISA(0x67) quest item.
`0xa9072f` sound id 0x17; `0xa90737` sellPrice; `0xa90742` giveGold;
`0xa9074e` soldItem; затем очищает tooltip/cursor safe fields;
`0xa907f4` removeEquipment(source); `0xa9080d` pickupEquipment(merchant,true).
При null pickup оригинал уничтожает предмет `0xa919ae` после уже выданных денег.
Native capacity/deletion branch не воспроизводится неограниченной portable bag.

Оригинальная normal Shift-buy ветвь: `0xa900ee` buyPrice, `0xa900f7..0xa900fd`
проверяет wallet, `0xa90106` повторно получает цену. `0xa901b8` count==1,
`0xa9122b` flag+0x25f !=0 выбирают createUnit(original data) `0xa91254`.
Остальные предметы удаляются из merchant inventory `0xa901d1`. Pickup player
`0xa901e9` выполняется перед giveGold(-price) `0xa90215`. Неуспех finite pickup
возвращает instance в исходный slot; неуспех clone освобождает новый object.
Таким образом, **проданное одиночное MERCHANTINFINITE зелье тоже остаётся
infinite при выкупе**, а count>1 покупается целиком и исчезает из merchant stock.
Это сохранённая ветка оригинала, не новое правило для удобства игрока.

Linux soldItem имеет только getSingleton и tail incrementStat(type0x11,1).
`CSteamStats::getSingleton @0xece430` читает `m_gStatsObject @0x153a840`,
`incrementStat @0xece340` — **REP RET**, без reads/writes/calls. В закреплённом
Linux ELF отсутствует ожидаемый статистический side effect; port не придумывает
локальные Steam counters. Это не утверждение о других сборках игры.

## Производственное подключение

`PotionMerchantCatalog::trade_offer` допускает только resource GUID и полный
оценённый descriptor известного identified/infinite зелья, независимо от
generation level range. Оружие, неизвестные rolled effects, fish/scrolls,
unidentified предметы и другие merchant services не исполняются частично.

`PlayerSession::sell_potion` вычисляет whole-count sell price с живым BARTEReffect,
сохраняет exact owned descriptor в `RuntimeEntity::merchant_buyback`, удаляет
его из player bag и кредитует wallet через существующий give_gold clamp.
`buy_back_potion` проверяет wallet, передаёт whole finite instance или создаёт
известный count-one resource descriptor, затем дебитует деньги. Counts/uses,
effect durations/values, GUID и canonical mesh сохраняются; portable bag IDs
выдаются при store, исходный merchant selection ID не переиспользуется игроком.
Все allocating операции staged до commit: это portable failure policy,
не утверждение об оригинальном exception/allocator поведении.

Application передаёт **реальный NPC entity**, а не один global bucket на GUID.
В существующем keyboard shop TAB переключает buy/sell/buyback, arrows выбирают,
Enter выполняет команду. Список, количество, цены, статус и wallet читает
существующий overlay renderer. Keyboard presentation, inventory modal policy,
interaction radius 2.25, portable unlimited capacity/8192 DTO limit не являются
оригинальным CEGUI merchant layout/capacity. UI clicks/frames отдельно не проверялись.

OTC **v7** хранит merchant-owned items на каждой entity/floor. Campaign capture,
возврат на этаж, Save/Load и continue используют те же live descriptors. Decode
v1–v6 оставляет stock пустым; v7 restore проверяет тип owner и potion resources,
descriptor/effects/mesh, uniqueness IDs и отклоняет corrupt data до commit.
Это собственный checkpoint format, а не оригинальный SVB.

## Проверки и остаток

- `original_merchant_transfer_trace`: **21** execution paths неизменённого
  целого menuItemClick и связанных whole price/gold/stat bodies. Явные adapters
  задают type/input/menus, evaluated effects, allocation/pickup/remove и sound.
  Проверены caller order, whole finite transfer, count-one clone, failed funds,
  finite pickup rollback, quest-item block и wallet saturation. Constructors,
  inventory capacity, CEGUI/FMOD internals и whole game не исполняются.
- `original_merchant_purchases`: реальные pak/UNITTYPES/Tarn stock, world NPC
  creation, player sale/rebuy, no money/ownership change on denied buyback,
  count-one infinite branch, no sharing between same-GUID NPC instances,
  v7 encode/decode/floor restore, changed effects/duplicate IDs rejection.
- `original_typed_save_migration` и `original_v6_save_migration`: frozen v5/v6
  actual writer inputs -> v7 -> второй независимый native reader, canonical bytes.
  Новый v6 fixture создан **до** изменения codec из commit `1b8878c`, без
  подмены version byte; SHA и producer в `tests/fixtures/typed-v6-player.json`.
- Desktop и affected CPU consumers собраны; синтаксис application проверен.

Полный `menuItemClick` остаётся `partial`: drag/drop/splitting, pet/stash/equip,
gambling/enchant, full pane/capacity/deletion, tooltip safe pointers, sounds,
item quest events и original resource-manager/allocator ownership не закрыты.
Merchant generation/refresh/random stock и full original saves — отдельный
остаток. Ни тесты, ни codegen не повышают `completion` автоматически.
