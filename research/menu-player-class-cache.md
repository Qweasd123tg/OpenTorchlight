# Creation-class cache и сохранённый menu actor

2026-10-02. Ограниченное исправление [menu-player-preview.md](menu-player-preview.md).
Входы: [menu-player-inputs.json](menu-player-inputs.json); исходные ELF/pak
только читались. Full original functions остаются partial.

## Original comparison

Source field client+0x1a8 — cached class resource filename (wstring), а не
класс, вычисленный из player pointer+0x58. Их writers различаются.
Полные setCreationClass/applyCharacterState тела уже сохранены в
[menu-player-preview.asm](disassembly/menu-player-preview.asm).
Дополнительное окно loadCharacter:
[menu-class-cache.asm](disassembly/menu-class-cache.asm).

`original-code`: setCreationClass @0x582d0c..0x582d1e сравнивает string lengths,
при равенстве wmemcmp @0x582e28. Совпадение идёт прямо в pending int32
+0x1038=3 (`0x582e35 -> 0x582e12`), пропуская removeCharacter/destructor/
createPlayer/firstTimeSetup/addCharacter/setToward. Это сохраняет существующие
player, equipment и анимационное состояние. При изменении filename
assign+0x1a8 @0x582d2e выполняется до создания новой модели.

applyCharacterState из Load selection присваивает class resource filename
+0x1a8 @0x5844c1, **всегда** заменяя actor из выбранного save. loadCharacter
при committed menu reload вместо этого присваивает пустую строку в +0x1a8
`0x581dfe/0x581e05`: source wchar32 literal@0x1001608 начинается нулём,
wcslen на `0x581dec` даёт0. Поэтому один и тот же визуальный класс не разрешает
сохранить actor после Save & Menu при следующем Create selection.

## Production integration

Application прежде использовал один page/slot/revision key как признак
пересоздания. Load -> Main -> Create того же класса создавал starting weapon
вместо сохранённого equipment и сбрасывал IDLE clock. Введён отдельный owned
menu_creation_class (optional base-class GUID). Это portable filename adapter
только для трёх проверенных base classes; native wstring/mod ABI не переносится.

Writers: успешная Load-row read/class/revision/restore цепочка записывает GUID;
Create другого класса тоже записывает GUID; committed reload очищает его.
Consumer: только несохранённый Create selection с совпадающим cache и existing
model сохраняет MenuPlayerPreview, GLES renderer, equipment и menu_player_started.
Он обновляет page-selection key и diagnostic notice, затем обычные pose/draw
consumers продолжают работу. Load и queued refresh не попадают в эту ветвь:
новый slot/revision всегда восстанавливает actor, даже при том же class GUID.
Следующий Create после reload использует first-time prototype, потому что
creation cache пуст. Scene/camera от этого class-cache решения не меняются.

Запись source pending int32+0x1038=3 сравнена по ASM; полный native
pending-state consumer остаётся open. Прежний Frontend/page lifecycle
сохраняется; новое поле не изображает native pending object. SaveStore не пишется,
inventory/RNG не мутируют, body/weapon geometry и IDLE не пересоздаются при
same-cache branch. Null/error recovery остаётся portable diagnostic adapter;
native failures/unwind не закрываются этим исправлением.

## Verification boundary

Desktop и shared Application probe собраны. Existing menu resource/body/weapon,
checkpoint, native CEGUI Create и Load CPU/resource contracts проверены.
Новый UI/GL переход Load -> Create и покадровое сохранение IDLE не запускались:
integration установлена по реальным producer/guard/owner/consumer в Application,
comparison — по source writer/branch ASM. Это не сквозная UI или full-function
приёмка. Native string identity/mods, pet/dead/armor, initial Main, blending и
полный original lifecycle остаются open.
