# Относительный подъём Main:1 → Town

## Найденное расхождение

Автоматический сценарий на настоящем pak прошёл городской Unit Trigger в
Main:1. Обратный trigger с относительным уровнем -1 приводил к Main:0,
который `select_dungeon_floor` затем ограничивал до Main:1. Получался повтор
первого этажа, не возврат в Town. До правки сохранены events/render/state;
это обнаружение исполняемым портом, не наблюдение оригинальной игры.

## Доказательства и статус

`resource-derived`: `MEDIA/DUNGEONS/MAIN.DAT.ADM`, разобранный текущим ADM
loader, содержит `NAME=Main`, `PARENT_DUNGEON=Town`, `VOLATILE=0`.
SHA pak: `8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`.
До исправления loader не сохранял PARENT_DUNGEON.

Декомпиляция `CGameClient::performWarp @0x0058d110`,
`research/decompiled-core/game_client.c:10970–11021`, показывает отдельную
обработку отрицательного относительного перехода с первого внутреннего
этажа: при непустом dungeon+0x80 выбирается это имя, а относительный и
абсолютный адрес становятся нулём перед последующей загрузкой. Порт
нумерует не-Town этажи с единицы, Town с нуля.

**inferred:** точная привязка dungeon+0x80 к PARENT_DUNGEON пока не доказана
отдельным loader ASM. В этом пакете нет нужного полного `CDungeon::loadDungeon`
экспорта и живого ELF. Не помечать эту ветку как побитово verified.

## Узкий перенос

`DungeonManifest` сохраняет parent_dungeon. Новый overload
`LevelTransitionState::resolve_entry(request, source_manifest)` проверяет
принадлежность metadata текущему данжу. Только не-Town depth=1, отрицательный
relative delta (кроме специального -99), без явного destination, waypoint и
ненулевого absolute, с известным parent выбирает parent:0. Остальные пути
остаются в прежнем resolver. Исходный запрос и source сохраняются в entry
context; blanket clamp не превращается в глобальный переход в Town.

В общий application вызывается этот overload. Нативный тест покрывает
все ограничения и несовпадающие metadata. Настоящий сценарий не вызывает
resolver напрямую: клики → interaction → LogicRuntime → pending Warp →
common application → resolver → load/cached floor. Возврат и fresh-process
Continue после него проверены отдельно.

Не восстановлены LASTDUNGEON fallback оригинала при отсутствии parent,
все parent у специальных карт, внутреннее original save-floor policy и
все правила entry anchors. Ни Town spawn coords, ни геометрия не подправлялись
под ожидаемый screenshot. Для следующего подтверждения нужен producer
CDungeon+0x80 и ограниченный trace `performWarp` на закреплённом ELF
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
