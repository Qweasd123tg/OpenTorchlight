# Settings Combobox: autochildren, popup capture и потребители

Дата проверки: 2026-09-21.

## Входы

| вход | SHA-256 |
|---|---|
| `Torchlight.bin.x86_64` | `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b` |
| `lib64/libCEGUIBase.so.1` | `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa` |
| `media/UI/settingsmenu.layout` | `dd4b17748afaeb5e9e21525847757f2d6aa4ef6f6cf53756f7f9bde0305c6751` |
| `media/UI/GuiLook.looknfeel` | `2cc118a13f7421c8f1e9d5b25f29f4b7962042898110a5e71b333b2b8766ef43` |
| `media/UI/GuiLookSkin.scheme` | `006c21ae3754dea3638ff9233701d4e815b656cc415fd60823ec5c53ff1cddc0` |
| `media/UI/Serif.font` | `f8239ab96f42d8906022e5066ab790da788d4de023155ed1caa00b290c045375` |

ELF и pak использованы только для чтения. Сопоставленная библиотека — именно
поставляемая игрой CEGUI 0.6-линия; существенные условия ниже проверены по её
инструкциям, а не перенесены только по современному upstream API.

## Ресурсное дерево

`resource-derived`: `settingsmenu.layout` содержит три `GuiLook/Combobox`:
`ResolutionDropdown`, `ShadowDropdown`, `ParticleDropdown`. У всех `ReadOnly=True`,
авторский размер `200x130` и нет XML-детей.

`library-derived` + `resource-derived`: scheme сопоставляет `GuiLook/Combobox`
с `CEGUI/Combobox`, а look создаёт, в таком порядке:

1. `GuiLook/ComboEditbox`, suffix `__auto_editbox__`;
2. `GuiLook/ComboDropList`, suffix `__auto_droplist__`;
3. `GuiLook/ImageButton`, suffix `__auto_button__`.

Строки suffix дополнительно находятся в поставляемой библиотеке по file offsets
`0x1dd7a4`, `0x1dd7b5`, `0x1dd7c7`. Editbox занимает ширину минус
`1.5 * Font::LineSpacing` и высоту `1.5 * LineSpacing`; кнопка — правый квадрат
той же стороны; DropList начинается под editbox и занимает остаток Combobox.
ComboDropList через Listbox look получает `__auto_hscrollbar__` и
`__auto_vscrollbar__` (строки `0x1dfd53/0x1dfd3f`), оба толщиной 12. В текущих
трёх списках `CGameUI::sizeComboList` подгоняет высоту под все строки, поэтому
scrollbars остаются скрыты, но являются настоящими runtime children.

`original-code`: `CSettingsMenu::createMenus @0xbd7fbd..0xbd80e9` для каждого
из трёх DropList пишет `AlwaysOnTop=true`, включает single-click operation и
ставит `ClippedByParent=false` и на DropList, и на Combobox. Реализация создаёт
те же stable-ID children в общем `UiWindowRuntime`; DropList не обрезается
родителем и раздаёт captured input детям. Scrollbars имеют RestoreOldCapture,
как `ComboDropList::initialiseComponents @0x13df10..0x13df3f`.

## Открытие, capture и принятие строки

Полная цепочка поставляемой библиотеки:

- `Combobox::initialiseComponents @0x139390`: получает три обязательных child;
  `@0x1393f2..0x139450` подписывает DropButton `EventMouseButtonDown` на
  `button_PressHandler`, затем подписывает DropList accepted/hidden и Editbox
  mouse-down/text события.
- `button_PressHandler @0x139240`: находит строку с текущим текстом, выделяет и
  обеспечивает её видимость, либо очищает selection; затем вызывает show.
- `showDropList @0x139120`: порядок строго `visible=true`, `activate`,
  `captureInput`, затем `DropListDisplayed`.
- Вызов происходит внутри базового Window mouse-down. Активация DropList
  деактивирует DropButton, поэтому последующая попытка ButtonBase захватить ввод
  не отнимает capture у списка. Это сохранено callback-порядком
  `UiWindowRuntime::button_mouse_down`.
- `ComboDropList` constructor `@0x13dfb0` начинает hidden, с
  `distributesCapturedInputs=true`, `singleClick=false`, `armed=false` и пустым
  last-accepted. Settings меняет single-click на true.
- `onMouseButtonDown @0x13dc00`: внутри списка ставит armed; вне списка очищает
  selection и освобождает capture. `onMouseMove @0x13dc80` при single-click
  включает armed и выбирает строку под курсором; вне item area очищает выбор.
- `onMouseButtonUp @0x13ddc0`: первый unarmed release только ставит armed. При
  armed release над строкой сначала вызывает `ListSelectionAccepted`, затем
  освобождает capture. Release вне строк тоже освобождает capture.
- `droplist_SelectionAcceptedHandler @0x138b90`: пишет текст выбранной строки в
  ComboEditbox, для ReadOnly ставит caret=0, испускает Combobox accepted и
  активирует editbox.
- `ComboDropList::onCaptureLost @0x13db80`: сначала базовый Window lost,
  затем `armed=false`, `visible=false`; если текущий временный selection не был
  принят, восстанавливает last-accepted строку. Hidden handler после этого
  испускает `DropListRemoved` (`Combobox @0x1381c0`).

Порт возвращает typed `UiComboSelection` именно в точке accepted. Контроллер
применяет её к draft settings; закрытие без accepted восстанавливает selection.
Чужая активация теряет глобальный capture, после чего `reconcile_capture`
выполняет тот же hide/restore путь.

## Строки и эффекты Settings

`original-code`: `CSettingsMenu::setOpen @0xbd5845..0xbd5ddb` один раз добавляет
каждое разрешение из `CSettings` (ширина + `" x "` + высота), выбирает точное
совпадение `RES_WIDTH/RES_HEIGHT`, вызывает `sizeComboList`, поднимает Combobox
и его DropList. В порт список разрешений является typed host input, сохраняет
порядок, удаляет точные дубликаты и не придумывает режимы.

Shadow создаёт 6 переведённых строк (`@0xbd5df5..0xbd61b1`), item ID 0..5, и
выбирает `SHADOW_DETAIL`. `CSettingsMenu::update` dispatch table
`0xff10c8`, `@0xbd4e93` задаёт:

| ID | LIGHTING | SHADOWS | resolution |
|---:|---:|---:|---:|
| 0 | 0 | 0 | 128 |
| 1 | 1 | 0 | 128 |
| 2 | 1 | 1 | 128 |
| 3 | 1 | 1 | 256 |
| 4 | 1 | 1 | 512 |
| 5 | 1 | 1 | 1024 |

Повторная ASM-сверка 2026-09-30 исправила прежний ошибочный `unchanged`
для ID0/1. Jump table даёт targets `bd5300`, `bd52b8`, `bd4ea0`,
`bd5150`, `bd51c8`, `bd5240`. ID0/1 идут через `bd52f4 -> bd4edf`,
после SHADOWS write проходят `bd4ee8..bd4f07`, где `edx=128` @bd4f02.
Следовательно выключение теней тоже сбрасывает размер карты в 128.

`DisplaySettings` хранит `shadows_detail`, `shadows_enabled`,
`lighting_enabled` и `shadow_resolution`; accepted ID применяет всю таблицу
к draft settings без промежуточного приближения.

Particle создаёт 3 переведённых строки (`@0xbd6251..0xbd6605`). Таблицы ELF
`0xff10f8` и `0xff1104`, потребление `CSettingsMenu::update
@0xbd4c4b..0xbd4d13` дают пары:

| ID | PARTICLE_FPS | PARTICLE_PCT | нормализованный emitter release |
|---:|---:|---:|---:|
| 0 | 20 | 10 | 0.1 |
| 1 | 30 | 50 | 0.5 |
| 2 | 40 | 100 | 1.0 |

Они возвращаются в `UiComboSelection.option.particle_fps/particle_percent`
и применяются к одноимённым полям `DisplaySettings`. Portable `MAX_PARTICLES`
остаётся другим параметром.

`CGameUI::sizeComboList @0xa849d0..0xa84bc2` суммирует pixel height всех item,
берёт высоту editbox, named item area DropList и округлённую Y-position, затем
пишет итоговую высоту Combobox. Порт применяет эквивалент текущего resource
случая: `1.5 * Serif line height + N * line height +` вертикальные края
resource `ItemRenderingArea`. Serif
пересчитывает AutoScaled FreeType metric для viewport; при отсутствующем
внешнем font resource явный deterministic fallback равен 16px, а для
недоступной frame imagery — 10 native pixels. Полученные viewport-pixel
метрики делятся на `UiLayoutState::offset_ratio` перед записью Unified
offset, поэтому resolver масштабирует их ровно один раз. Row painter
берёт `ItemRenderingArea` из GuiLook NamedArea, а строки — из того же
`UiWindowSnapshot`, clip и paint order, что autochildren.

`resource-derived`: ComboDropList frame состоит из
`GuiLook/ItemTooltip{TopLeft,TopRight,BottomLeft,BottomRight,LeftEdge,RightEdge,TopEdge,
BottomEdge,Middle}`. ComboEditbox использует `ComboboxEditLeft/Middle`,
white `NormalTextColour=FFFFFFFF` и TextArea `L=10,T=5,R=-15,B=-5`.
`original-code`: все три item loop вызывают `setSelectionColours`
(`@0xbd5bfb`, `@0xbd6191`, `@0xbd65e5`) с четырьмя одинаковыми
RGBA `(1, 0.5, 0.5, 1)`, то есть ARGB `FFFF8080`. Вызова
`setSelectionBrushImage` в этой цепочке нет, поэтому порт не приписывает
selection несуществующему image resource.

Точные ключи settings/runtime в ELF: `KSETTINGS_F_PARTICLEFPS`
(`0x150b520`), `KSETTINGS_F_PARTICLE_PCT` (`0x150b524`),
`KSETTINGS_SHADOW_DETAIL` (`0x150b4ac`), `KSETTINGS_LIGHTING_ENABLED`
(`0x150b4b4`) и `KSETTINGS_SHADOW_RESOLUTION` (`0x150b534`).
`KSETTINGS_MAX_PARTICLES` (`0x150b4a4`) остаётся отдельным параметром.

## Принятая граница

Закрыта production-цепочка трёх read-only Settings Combobox: обязательные
autochildren, child ownership, popup show/capture/restore/hide, single-click
highlight/accept, immutable geometry/clip/paint descriptors и потребители
Resolution/Shadow плюс точные Particle FPS/PCT значения.

Не утверждается общий CEGUI Combobox: editable validation/caret/keyboard,
sorting/multiselect, реально переполненный список и scrollbar drag/repeat не
возникают в `settingsmenu.layout` и остаются вне этого пакета.
