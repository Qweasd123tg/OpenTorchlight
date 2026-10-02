# Save & Menu: обновление menu actor из committed checkpoint

2026-10-01. Продолжение ограниченного среза
[menu-player-preview.md](menu-player-preview.md). Входы, ресурсы и неизменённая
OGRE math dependency прежние: [menu-player-inputs.json](menu-player-inputs.json).
Original function completion остаётся partial. UI-клики, кадры и оригинальный
процесс в этом проходе не выполнялись; кодовая integration и CPU contracts
не являются визуальной приёмкой.

## Original comparison

Instruction-aligned окна сняты из полного disassembly соответствующих функций
pinned ELF, SHA256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`:
[disassembly/menu-player-return.asm](disassembly/menu-player-return.asm).
Decompiler `decompiled-core/game_client.c` использован для навигации.

`original-code`: `setGameState @0x58fa90` сохраняет requested EGameState int32
в stack+0x24 и EMenu int32 в r13d. При смене state (кроме state5) вызывает
`unloadCurrentLevel(true) @0x58fb1c`. В unload `0x579b43..0x579b76` player
и pet отсоединяются от уровня. После cleanup при true выполняются virtual
несколько destructor calls и обнуления (`0x579e2c..0x579e57`); player pointer64
`+0x58` и pet `+0x60` затем обнуляются безусловно `0x579e63/0x579e6d`.
Поэтому existing-player branch нельзя объявлять сохранением живого gameplay
объекта при обычной смене состояния.

Menu state0 проверяется `0x58fb61..0x58fb6e`; загрузочная ветвь при changed/
absent level вызывает reloadMenuCharacters `0x58fb8f`, затем проверяет player
`+0x58` (`0x58fb94`). Null-player ветвь собирает save path из GameUI выбранного
имени `+0x16c0` (`0x590739..0x590751`) и вызывает loadCharacter `0x5907a7`.
Результат записывается в `+0x58`; ненулевой результат выбирает stored dungeon
name `+0x1098`, depth int32 `+0x1094`, seed int32 `+0x1090` для loadMenuLevel
`0x5907f3`. Далее addCharacter `0x59081f` использует level position `+0x140`,
setToward `0x590833` — direction `+0x164`. Cursor/quest/menu/UI writes после
ветвей видны `0x58fbe5..0x58fc1c`. Полный save, pet, state lifecycle и unwind
не переносятся этим патчем.

Есть отдельная ненулевая player ветвь `0x58fb9f..0x58fbd0`, но её наличие
не отменяет предшествующего unload при state transition. Причина исправления
порта: старый menu renderer владел отдельным actor из прежнего выбора и не
получал восстановленную экипировку после Save & Menu.

## Integration and owners

`integration`: native Options exit_game -> Frontend::activate("exit-game") ->
pending_options_exit_ / CLOSE -> Frontend::advance -> typed save_and_menu request.
Исходный COptionsMenu::update запрашивает state(0,0) после CLOSE `0xb8019d`;
существующий OTC adapter сначала записывает checkpoint. Save-menu fallback
подаёт тот же typed request. Это действующий caller нового refresh producer.

`portable adapter`: `checkpoint_now` сначала capture(session/floor), затем
SaveStore::write; только после успешной записи обновляется campaign с committed
revision. Frontend::saved(save_and_menu) переводит страницу в Main. Ошибка
записи оставляет pause/error и не ставит запрос обновления модели.

В успешной ветви request save_and_menu Application ставит owned SaveSlotInfo со slot,
class GUID, committed revision и health. Это точная identity текущей кампании,
не выбор первой/самой новой записи. Следующий draw_frontend использует тот же
SaveStore::read(identity) -> class/revision check -> restore_player ->
menu_player_visual -> build_menu_player_preview -> GLES model replacement,
что и Load. Запрос потребляется один раз. Он принудительно заменяет actor,
даже если cache key совпал; затем Back/Settings снова сохраняют его.

`player_visual_prototype` выделен из прежнего gameplay lambda в общий player
module. Единственное правило weapon producer для gameplay, Load и menu —
actual equipped InventorySlot::weapon, включая пустой slot. Mesh/hand/scale
consumers прежние. `menu_player_visual` читает const PlayerSession; dead health
даёт unsupported/null, который существующая failure ветвь потребляет удалением
старого renderer/model и фоном с diagnostic notice. Живой placeholder не
создаётся. Renderer освобождается раньше его source geometry.

Новый путь не пишет дополнительный checkpoint, не меняет gameplay inventory,
health, gold или RNG и не подставляет starting weapon вместо unequipped slot.
Контроль ошибок read/revision/resource — прежний Load consumer. В этом
историческом проходе theme оставалась portable Town; последующее
[menu-themes.md](menu-themes.md) подключает фиксированные темы через committed
OTC floor adapter, сохраняя partial для native save/depth/RNG и random themes.
Initial Main selection и восстановление scene после ошибки теперь уточнены в
[main-menu-save-selection.md](main-menu-save-selection.md). Native runtime-error
recovery, pet/dead/retired appearance,
equipped armor, initial blending и native ownership остаются открытыми.

## Verification

Расширен existing `tests/menu_scene_test.cpp` на всех3 resource classes:
read-only snapshot сохраняет combat RNG/health/gold/slots; unequip/re-equip
влияет на реальную menu geometry и hand consumer; прежний snapshot сохраняет
своё owned weapon значение. Реальный rolled inventory другого класса проходит
через checkpoint restore и отображает именно equipped resource mesh, а не
class starting weapon. Health0 не получает living preview. Existing placement,
wardrobe, IDLE/loop и source marker contracts сохранены.

Desktop и shared Application probe собраны. Узкий gate **5/5**: menu scene/core,
original menu resources, save checkpoint, original players и equipment.
Сквозной переход через UI/кадр в этом проходе не проверялся; production wiring
установлено по caller/field/consumer цепочке выше. Реестр хранит partial и
не повышает legacy compared до full-function equivalence.

Registry sync passed: 227 bounded addresses. Новых UI/GL сценариев не запускали.
