# CEGUI capture/modal, ButtonBase и lifecycle

## Источники

Проверено 2026-09-20 по shipped `lib64/libCEGUIBase.so.1`, SHA-256
`57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`;
Torchlight ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Входы read-only из `/home/qweasd123tg/Games/Torchlight/game`.
Версия/отличия от upstream `v0-6-2`, недоступность прежней headless-базы и
проверенный attach/destroy контракт — [dropdown-container-lifecycle](dropdown-container-lifecycle.md).
Ниже `library-derived` означает прямой ASM именно закреплённой библиотеки;
новых Ghidra-экспортов или запусков игры в этом проходе нет.

`resource-derived`, SHA-256 извлечённых байтов внешнего pak:

| Ресурс | SHA-256 |
|---|---|
| media/UI/mainmenuframe.layout | 60bccb2941daebd326205413905f9e8e34210df4c33e775a128a7bd20adb1ba0 |
| media/UI/settingsmenu.layout | dd4b17748afaeb5e9e21525847757f2d6aa4ef6f6cf53756f7f9bde0305c6751 |
| media/UI/GuiLookSkin.scheme | 006c21ae3754dea3638ff9233701d4e815b656cc415fd60823ec5c53ff1cddc0 |

## Состояние и владельцы

System: +0x60 mouse-target, +0x68 GUI sheet, +0x70 modal, все 64-bit pointers.
Capture — отдельный static Window::d_captureWindow. Window: +0xa8 previous
capture (pointer), +0xb0 parent (pointer), +0x20a locally-active (byte),
+0x20f restore-capture (byte), +0x210 ZOrderingEnabled (byte),
+0x212 distribute-captured-inputs (byte), +0x213 RiseOnClick (byte),
+0x214 auto-repeat enabled (byte), +0x228 repeat button (32-bit enum).
Window ctor: active=false, restore=false, distribute=false, repeat=false,
repeat button=6. ButtonBase ctor `0x1370f0..0x137120` дополнительно задаёт
+0x730 pushed=false и +0x731 hovering=false, оба byte.

`isActive @0x110d40..0x110d6a` — own active AND parent.isActive при parent;
без parent возвращает own active. Это не проверка attachment к GUI sheet,
visible или enabled. `distributesCapturedInputs @0x1119b0` читает +0x212.

## Capture: порядок событий

`captureInput @0x111470..0x111531`:

1. !isActive → false, без записей. Уже владелец capture → true без событий.
2. Сохраняет old локально, **сначала** global capture=this `0x1114ae`.
3. При restore=true сохраняет old в +0xa8 (включая null), не уведомляя old.
   При restore=false и old!=null вызывает old.onCaptureLost, args.window=this.
4. Вызывает this.onCaptureGained (vslot +0xd0), возвращает true.

`releaseInput @0x111540..0x1115d1`: если capture!=this, no-op. При restore=true
сначала capture=previous; если previous!=null, previous field=null и
previous.moveToFront `0x111583`. При restore=false capture=null. Затем
this.onCaptureLost (+0xd8), args.window=this. Не испускает CaptureGained
восстановленному окну. `setRestoreCapture @0x1115e0..0x11163c` записывает флаг
и рекурсивно задаёт его имеющимся детям по insertion list.

`Window::onCaptureLost @0x113880..0x1138f6` сначала repeat button=6. Если
restore=true и previous!=null, вызывает previous.onCaptureLost с теми же args,
потом previous=null. Далее System.injectMouseMove(0,0) `0x1138cd`, затем
EventInputCaptureLost. Нулевое движение — реальная повторная маршрутизация,
не бездействие. Значит callbacks могут видеть уже изменённый capture/hover.

## Modal, activation и target

`setModalState @0x112bc0..0x112c27` сравнивает requested с modal==this.
Равенство → no-op. true: activate(), затем modal=this. false: modal=null
только для текущего modal. Нет стека и автоматического восстановления
предыдущей модальности. Даже если activate отказался из-за visibility,
последующая запись modal происходит.

`activate @0x1113e0..0x111460`: !isVisible(false) → no-op; если capture чужой,
сначала capture=null, затем old.onCaptureLost с args.window=null; затем
moveToFront. Отдельной проверки enabled нет. `deactivate @0x1111a0..0x1111e3`
всегда вызывает onDeactivated с otherWindow=null.

`onActivated @0x1132b0..0x1132ff`: own active=true, requestRedraw, EventActivated.
`onDeactivated @0x1131c0..0x1132a8`: посещает детей в insertion order,
вызывает onDeactivated только для isActive детей (передаёт otherWindow),
потом own active=false, redraw, EventDeactivated. Capture/modal здесь не
очищаются. `moveToFront_impl @0x116550..0x1166e8` выполняет parent-first
activation, активирует this, деактивирует прежнего active sibling, лишь затем
переставляет draw-list при разрешённом ZOrderingEnabled (и RiseOnClick для
кликового вызова). `doRiseOnClick @0x111b70` вызывает этот virtual slot
с wasClicked=true. RiseOnClick=false не отменяет activation само по себе;
оно запрещает соответствующую перестановку. Полный порядок moveToBack
разобран в предыдущем документе.

`System::getTargetWindow @0x10ad90..0x10ae51`:

- Нет sheet или sheet невидим → null, даже при capture/modal.
- Capture существует → он является target; при distribute=true descendant
  hit заменяет его, иначе он сохраняется, в том числе вне его rect.
- Без capture → sheet.getTargetChildAtPosition, null заменяется на sheet
  без проверки isHit/disabled/pass-through самого sheet.
- Modal существует и target не modal/его descendant → target=modal.

`getNextTargetWindow @0x109e40..0x109e4f`: target==modal → null;
иначе parent. Таким образом unhandled событие никогда не выходит выше modal.
Выбор target и его widget handler нужно выполнить до поиска следующего
ancestor, а не сразу выбрать первого предка с игровой подпиской.

## Window down и ButtonBase: порядок относительно игровой подписки

`Window::onMouseButtonDown @0x112c60..0x112d42`: сбрасывает tooltip target;
для left OR-ит результат doRiseOnClick в handled; при auto-repeat управляет
capture и repeat button/timer; затем испускает EventMouseButtonDown.
Повторный enum/timer контракт: при repeat button=6 пробует captureInput;
если новый button отличается и capture=this, пишет button, elapsed=0,
repeating=false. Полный временной update/auto-repeat теперь разобран и подключён в [ui-pointer-timing.md](ui-pointer-timing.md).

`ButtonBase::onMouseButtonDown @0x136fe0..0x13704c` **сначала вызывает этот
Window handler, включая игровые подписки**, затем для left вызывает
captureInput. При успехе pushed=true, updateInternalState(args.position),
redraw. Для left всегда handled=true, даже при неудачном capture.
Нет guard по ранее установленному handled. Игровой callback может изменить
дерево/закрыть меню до продолжения ButtonBase; объект должен пережить этот
вызов. Переставить capture/pushed перед callback — неверный перевод.

`onMouseButtonUp @0x136e70..0x136eaa`: Window base up, затем для left
releaseInput и handled=true. Очистка pushed происходит через capture-lost.
`ButtonBase::onCaptureLost @0x136f80..0x136fdb`: Window base capture-lost
(включая injectMouseMove), pushed=false, updateInternalState текущей позиции
MouseCursor, redraw, handled=true.

`updateInternalState @0x136eb0..0x136f7a`: сохраняет old hover, очищает hover;
если capture=this, hover=isHit(position); если capture чужой, hover=false;
без capture hover=(System.mouseTarget==this && isHit(position)). При изменении
hover requestRedraw. `Window::isHit @0x114cd0..0x114d5a` сначала отклоняет
`isDisabled(false)` (`0x114ce6..0x114ced`); отдельной проверки visibility в
этом методе нет. Нельзя вычислять hover ближайшего clickable ancestor
вместо истинного System.mouseTarget. `onMouseMove @0x137050..0x137087`:
Window base, updateInternalState, handled=true. `onMouseLeaves
@0x136e30..0x136e6a`: Window base, hover=false, redraw, handled=true.

Derived up handlers сначала проверяют left && pushed && sheet существует &&
sheet.getTargetChildAtPosition(position)==this (именно обычный child-hit,
не capture/modal getTargetWindow), затем выполняют собственный эффект:

| Класс и адрес | Эффект до ButtonBase::onMouseButtonUp |
|---|---|
| PushButton 0x17ac30..0x17acd6 | onClicked (+0x228) |
| Checkbox 0x137200..0x137276 | setSelected(!selected) |
| RadioButton 0x17aff0..0x17b05e | setSelected(true) |

Во всех трёх left&&pushed путях handled=true, включая промах; затем base up.
`RadioButton::setSelected @0x17af70..0x17afc8` при изменении сначала пишет
selected и запрашивает redraw. При true затем вызывает
`deselectOtherButtonsInGroup @0x17b060..0x17b117`: проходит insertion children
непосредственного parent, оставляет только окна с **точно равным type**, уже
selected, не self и с равным 64-bit GroupID, и вызывает каждому
`setSelected(false)` в порядке списка. После возврата исходный setSelected
испускает собственный SelectStateChanged; события снятых siblings поэтому
предшествуют событию выбранного окна. Без parent снятий нет. Constructor
`@0x17b1a0..0x17b1df` задаёт selected=false и GroupID=0; `setGroupID
@0x17b120..0x17b13c` при уже selected также сразу снимает конкурентов.
Runtime переносит default/явный GroupID и этот sibling-order для
`set_button_selected` и accepted RadioButton up. Произвольные внешние
Checkbox/Radio SelectStateChanged subscribers остаются отдельными consumers,
а не только локальной boolean записью.
Main CDropdown подписан на MouseButtonDown, поэтому PushButton Clicked нельзя
повторно привязать к той же игровой команде без оригинального основания.

## Detach/hide/disable/destroy

removeChildWindow/removeChild_impl меняют дерево и Z события; **не release
capture и не clear modal**. `onHidden @0x113550` деактивирует при isActive,
затем redraw/Hidden; `onDisabled @0x1133b0` распространяет Disabled на locally
enabled детей, redraw/Disabled; ни один не release capture. Поэтому политика
порта clear_capture(subtree) при detach/hide должна обозначаться адаптером,
если она требуется host lifecycle, а не приписываться CEGUI.

Window.destroy `0x114840` вызывает releaseInput до tooltip/renderer/event/
parent/child cleanup. Manager затем вызывает
`System::notifyWindowDestroyed @0x10a1c0..0x10a201`, который очищает только
равные этому pointer mouse-target, sheet, modal, в указанном порядке.
Каскад DestroyedByParent и deferred dead-pool см. предыдущий документ.
Restore-chain raw-pointer и произвольные callbacks требуют настоящего
lifetime владельца; безопасная portable invalidation не доказывает исходный
полный manager/exception контракт.

## Какие widgets реально участвуют

По layout и scheme (не по наличию onClick):

| Layout/type | Количество | Runtime type |
|---|---:|---|
| main StandardButton | 5 | CEGUI/PushButton |
| main RadioTab (TabA, TabB) | 2 | CEGUI/RadioButton |
| main StaticImage / StaticText / ItemText / DefaultWindow | 10 / 5 / 2 / 1 | DefaultWindow |
| settings StandardButton (Cancel, Apply) | 2 | CEGUI/PushButton |
| settings Checkbox | 12 | CEGUI/Checkbox |
| settings Slider (MusicVolume, SoundVolume) | 2 | CEGUI/Slider |
| settings Combobox (Resolution, Shadow, Particle Dropdown) | 3 | CEGUI/Combobox |
| settings StaticText / StaticImage | 6 / 1 | DefaultWindow |

SliderThumb scheme target — CEGUI/Thumb. Combobox и Slider имеют библиотечные
look-generated children, которых нет в этих XML counts. Их event handlers,
capture restoration и скрытые popup/autochildren нельзя заменить ButtonBase
на всём внешнем widget. Credits backing StaticImage также не ButtonBase,
хотя имеет игровую onClick подписку.

В двух XML нет явных ModalState, RestoreOldCapture, DistributeCapturedInputs
или MouseAutoRepeatEnabled properties. Это не доказывает отсутствие runtime
записей или widget constructor defaults. Производитель modal для settings
должен устанавливаться по CGameUI/settings ASM отдельно; визуальный overlay
сам по себе не основание вызвать setModalState(true).

## Производственное подключение и граница

`library-derived` контракт подключён через постоянный `UiWindowRuntime`
(`include/torchlight/ui_window_runtime.hpp`, `src/ui_window_runtime.cpp`). Он
владеет stable ID registry без повторного использования ID, parent/insertion
children/draw-list, deferred dead-pool, active/capture/previous-capture/modal/
sheet/mouse-target и ButtonBase pushed/hover. `StaticDropdownState` использует
этот же owner: close отсоединяет root без уничтожения ресурсов и подписок.
Snapshot хранит source IDs, а отдельный resolve detached capture ремапит
геометрию и zero-position по ID, не по устаревшему индексу кадра.

`Frontend::pointer_event` — реальный consumer targeting, ancestor dispatch,
ButtonBase down/up/move/leave и горизонтального `GuiLook/SliderThumb` drag.
Window/game callback на down выполняется до capture/pushed. Capture-lost
сначала просит frontend повторно маршрутизировать сохранённую позицию мыши,
затем испускает lost, очищает ButtonBase state и повторно вычисляет hover как
последующий `updateInternalState`. Detach/hide/disable/deactivate не снимают
capture; disabled capture остаётся owner, но `isHit` возвращает false. Destroy
вызывает release до destruction и очищает равные System owners перед
`clean_dead_pool`. Checkbox toggle и RadioButton setSelected(true) хранятся в
runtime до release; radio siblings того же type/GroupID снимаются в insertion
order, после чего `selection_changed` инвалидирует consumer frame.
Произвольные дополнительные native selection subscribers не объявляются
выполненными.

`tests/ui_window_runtime_test.cpp` проверяет чистым state-контрактом порядок
capture/restore/release, reentrant retarget/lost, modal clamp, detached capture,
disabled hit, destroy/dead-pool, Z-группы, ButtonBase и Thumb drag. Shared
dropdown и реальный pak layout проверяются `tests/ui_dropdown_test.cpp`.
Это не UI-клик, кадр или сквозной сценарий и не запуск оригинала.

Tooltip/renderer/factory teardown, auto-repeat и три Settings Combobox
подключены отдельно: [закрытие frontend](cegui-frontend-closure.md).
Открытая библиотечная граница за этим пакетом: exception ABI и arbitrary
SubscriberSlot callbacks, остальные autochildren, editable/overflow Combobox,
vertical/reversed/nonstandard Slider track и дополнительные selection events.
Modal state имеет настоящий single-owner runtime и targeting. Проверенные
CSettingsMenu/COptionsMenu/CModalMenu не вызывают setModalState: исследование
переопределений и AlwaysOnTop находится в dropdown-animation-lifecycle.md.
Поэтому этим меню не добавляется искусственный modal producer. Restore-chain raw pointers
заменены безопасной tombstone invalidation; это portable ownership policy, а
не утверждение побайтовой lifetime parity. Поэтому этот перенос закрывает
используемую frontend цепочку, но не весь lifecycle CEGUI.
