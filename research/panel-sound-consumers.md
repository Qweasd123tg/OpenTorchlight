# Звуковые эффекты живых панелей

2026-10-02. `original-code`: Linux ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
`resource-derived`: `media/sounds/UI.DAT.adm`, SHA-256
`568873fd9e04ae0fe91a061cd34543336200ad1a813b2e8ed970a179ae51790c`.

## Локальные банки и исправление ошибки

Sample IDs принадлежат отдельному CSoundBank меню. ID22 не является GUID
и не даёт глобальную привязку к CenterOpen. Constructors создают свой
bank(manager,false), ищут named data и передают GUID64 из +0x20 в addSample.
Срезы сверены по ASM и UTF-32 literals:

| Владелец | Constructor | NAME22 / NAME66 | addSample callsites |
| --- | --- | --- | --- |
| Inventory | 0xb60770 | INVENTORYOPEN / INVENTORYCLOSE | 0xb60aad / 0xb60b00 |
| Merchant | 0xb772a0 | STATSOPEN / STATSCLOSE | 0xb77436 / 0xb77485 |
| Quest | 0xbcc6d0 | INVENTORYOPEN / INVENTORYCLOSE | 0xbcc860 / 0xbcc8ae |
| Skill | 0xbe39e0 | INVENTORYOPEN / INVENTORYCLOSE | 0xbe3b61 / 0xbe3baf |

Literal addresses: INVENTORYOPEN 0xfefaa8, INVENTORYCLOSE 0xfefae0,
STATSOPEN 0xfe6200, STATSCLOSE 0xfe6228. Other bank entries и полные
constructors/allocators/load failures остаются вне этого sound slice.

Все четыре setOpen открывают sample22 и закрывают sample66:
Inventory 0xb4ecae / 0xb4ebe4; Merchant 0xb6a2b9 / 0xb6a4f3;
Quest 0xbc263b / 0xbc25b8; Skill 0xbe122b / 0xbe11b1.
`0xb6a4e4: mov $0x42,%esi` исправляет прежний ошибочный merchant close=12.
`0xb6a4c6: mov $0xc,%esi` относится к queueTip `0xb6a4cb`, а не playSample.
Это ошибка прежнего исследования. CLOSED->CLOSED не выдаёт звук.

## Ресурсный путь

| NAME | GUID64 | Реальный FILE | PCM |
| --- | ---: | --- | --- |
| InventoryOpen | 4315958940208140766 | media/sounds/UI/sheet_openright.wav | stereo16, 44100Hz, 27636 frames |
| InventoryClose | 4315958944503108062 | media/sounds/UI/sheet_close.wav | stereo16, 48000Hz, 21760 frames |
| StatsOpen | 1579749139973280222 | media/sounds/UI/sheet_openleft.wav | stereo16, 44100Hz, 27636 frames |
| StatsClose | 1579749148563214814 | media/sounds/UI/sheet_closeleft.wav | stereo16, 44100Hz, 23904 frames |

WAV SHA-256 соответственно:
`864598d803537bec01ff52627175e27f8e81374348b3d7598a952ea2fced6fdf`,
`c82c39d9471816a6cf98cb6cffd604976015a2a63633c66d471b75b2a9629a91`,
`12b09f18217a71302598840e6e1db62028d00bd6233ebbd94ec530b326d15d84`,
`f7456e8c3b518f5155ec4ad677adb20a44ce9d766c274d94ba64686ea511caef`.
CATEGORY=UI, LOOPS=0, VOLUME=.2, VOLUMEVARIATION=.2,
FREQUENCYVARIATION=0, RADIUS=10 и один FILE у каждой записи.
Channel gain переиспользует проверенный volatile RNG helper и исходную
формулу; см. [dropdown-animation-lifecycle.md](dropdown-animation-lifecycle.md).

## Consumers и границы

Application принимает sound_sample от single-writer setters Inventory,
merchant, quest и skill. `ui_panel_sound_request` разрешает (банк,local ID)
в resource cue; неизвестный слот не подменяется другим. `UiSoundPlayer`
читает ADM/GUID/WAV, создаёт voice и использует persistent ALSA worker.
Volume/mute берутся из актуального frontend.audio_settings. Death close
также идёт через inventory setter. Повторное открытие не повторяет звук.

`prototype` output adapter: local RNG seed, oldest voice eviction,
ALSA lifecycle и линейная интерполяция вместо полного FMOD mixer.
Source PCM сохраняет родные channels/rate. Целочисленный rate remainder
продвигает voice с исходной частотой через общий output stream: 48000Hz
InventoryClose не замедляется при 44100Hz output. 21760 source frames
заканчиваются через 19992 output frames. Output rate фиксирован на lifetime
voice. Original FMOD interpolation/filtering/ownership и enable lifecycle
не объявляются закрытыми. Порт не создаёт новый thread при каждом play.

## Проверки и остаток

`original_panel_sound_comparison`: восемь unchanged whole-body executions
четырёх setOpen — OPEN->CLOSED и CLOSED->CLOSED. Сравниваются sample ID,
open/aux и факт CLOSE blend с production PanelOpenState. Записан порядок
sound66 -> string(CLOSE) -> blend(false,.1,2,-1). Три named adapters:
sound recording, opaque old-ABI string sentinel и blend recording.
Optional child pointers null; native tree/allocation/cleanup alternate
branches не моделируются. Original constructors/game/audio не запускаются.

`ui_sound_contract`: настоящие controllers -> bank cues, no replay/unknown
slot guessing, mixer mute/gain и stereo sample-rate conversion.
`original_ui_sound_contract` загружает шесть реальных sounds без создания
audio thread/device, проверяет PCM metadata и mixed-rate duration.
Application/desktop собраны; GUI-клики/кадры/прослушивание не выполнялись.

`completion: partial`: звук четырёх панелей имеет реального consumer.
Pet/journal callers, native animated models/viewports/camera/tips,
createMenus/tree lifetime и полный контракт setOpen остаются открытыми.
