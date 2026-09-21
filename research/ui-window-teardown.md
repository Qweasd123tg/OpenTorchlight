# CEGUI window teardown and tooltip source contract

Source review 2026-09-21. This document records `original-code` and
`library-derived` contracts, not a claim that every CEGUI function is fully
implemented. Addresses below are virtual addresses in the shipped ELF.

Inputs, read-only under `/home/qweasd123tg/Games/Torchlight/game/`:

| Input | SHA-256 |
| --- | --- |
| `Torchlight.bin.x86_64` | `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b` |
| `lib64/libCEGUIBase.so.1` | `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa` |
| `lib64/libCEGUIFalagardWRBase.so` | `f336dbc15357be833d19c62ad597046cc028c8de5411b554dda6d0aa7f9bcdfe` |

Existing `research/decompiled-core/game_ui.c` was used for navigation;
ordering, branches and fields below were checked with `objdump -d -C` on
these exact libraries. Missing saved headless project remains the previously
documented tooling limitation. No UI execution was performed for this review.

## Destruction and deferred ownership

`WindowManager::destroyWindow(String) @0x125520` returns on missing name;
otherwise removes the name entry first (`0x125605`), calls virtual window
destroy (`0x12562e`), appends its pointer to the dead pool, then calls
`System::notifyWindowDestroyed` (`0x125688`). This ordering allows callbacks
to observe the name absent while the object is still usable. It does not
release the object's C++ storage at logical destruction.

`Window::destroy @0x114840` delegates to the manager if its name remains
registered. Once unregistered, its ordered effects are:

1. `releaseInput` (`0x11486d`).
2. Resolve effective tooltip; when its target is this window, call
   `setTargetWindow(nullptr)` (`0x114945`).
3. `setTooltip(nullptr)` (`0x114898`), destroying an owned custom tooltip.
4. If renderer exists: its virtual `onDetach` (`0x1148ac`), renderer manager
   destruction (`0x1148c1`), then clear renderer pointer `+0x3d8`.
5. Destruction-started event via virtual slot `0xf8` (`0x1148f8`).
6. Remove self from parent (`0x11490d`).
7. Virtual `cleanupChildren` (`0x114918`).

`cleanupChildren @0x114960` repeatedly takes the first insertion-order child,
removes it, then destroys it through the manager iff `DestroyedByParent`
byte `+0x20c` is set. Nonowned children survive detached.

`cleanDeadPool @0x1253d0` traverses the pool in reverse, resolves each
window's actual type through `WindowFactoryManager::getFactory`, and calls
the factory destroy slot. Only after this loop is the pool end reset. A
throwing factory propagates; this function is not a transactional recovery
algorithm. `Window::~Window @0x1152e0` finally releases strings, render cache
(`+0x2f0`, call `0x115357`), user-string map, vectors, event connections and
property map. Shared Imageset textures/fonts are not owned here.

`WindowRenderer::onDetach @0x12b300` removes renderer-added properties from
the window in reverse renderer-property order. It does not delete global
fonts/textures. The portable equivalent must release per-window skin
bindings/cache entries and connections while keeping shared resource caches
alive; merely incrementing a teardown counter does not implement an effect.

## Construction and failures

`WindowManager::createWindow @0x127c70` checks manager lock, combines prefix
and name (or generates a unique name), rejects duplicate names, resolves a
factory, and invokes factory create (`0x128263`). It sets naming metadata;
for a Falagard-mapped type it resolves mapping, calls `setWindowRenderer`
(`0x128569`) and virtual `setLookNFeel` (`0x12857b`). Only afterward is the
manager name map populated (`0x128668`).

`Window::setLookNFeel @0x117610` requires a renderer. Replacing an existing
look first calls the renderer's look-unassigned hook and old
`WidgetLookFeel::cleanUpWidget` (`0x11781a..0x117830`). New look initialization
calls `initialiseWidget` (`0x11779f`), window `initialiseComponents`
(`0x1177aa`), renderer look-assigned hook (`0x1177b7`), then redraw.

`setWindowRenderer @0x112680` returns if the existing renderer has the same
name; otherwise detaches/destroys the previous renderer before constructing
the replacement. Empty renderer name takes an exception path. Construction
and look initialization failures unwind local strings; inspection of
`createWindow` landing pads does not establish rollback of the allocated
window or autochildren. Portable transaction cleanup can prevent leaks but
must be described as a deliberate safety difference, not original parity.
Arbitrary third-party renderer/factory exception behavior is not closed by
support for the shipped menu type mappings.

## Tooltip producer and property contract

`CGameUI` creates default type `GuiLook/Tooltip` at `0xa9f5c3..0xa9f5d2`;
System owns it at `+0x238`. It sets AlwaysOnTop true (`0xa9f5f5`), hover time
zero (`0xa9f600`), display time zero (`0xa9f60b`), activates it, and writes
byte `+0x3e2=true` (`0xa9f618`). Do not substitute the generic library hover
and display defaults. CGameUI sets default font `Serif` in the same creation
chain; tooltip's own font is absent and resolves through `getFont(true)`.

`WindowProperties::Tooltip::set @0x12a390` directly calls `setTooltipText`:
the XML key is `Tooltip`, not a custom game alias. `CustomTooltipType` maps
to `setTooltipType @0x1149c0`. `getTooltipText @0x111ae0` returns own string
unless it is empty, inherits-tooltip byte `+0x2e9` is true, and a parent
exists; then repeats on the parent. Default tooltip use depends on absence
of a custom tooltip pointer.
`Window` constructor writes inherits-tooltip false at `0x11b37b`; inheritance
is opt-in, not the default.

`setTooltip(pointer) @0x1147e0` destroys the old tooltip only if owned,
assigns the pointer, clears ownership. `setTooltipType @0x1149c0` destroys
old owned tooltip, creates `windowName + TooltipNameSuffix` for nonempty
type, and sets ownership true. Its caught CEGUI exception path
`0x114b03..0x114b1d` clears pointer/ownership and returns. Other exceptions
unwind. `System::setDefaultTooltip(String) @0x10cc20` likewise manages a
separate ownership flag at `+0x240`; do not transfer that ownership to each
window using the default.

## Tooltip state machine

Fields: enum `+0x730` (inactive=0, active=1, fade-in=2, fade-out=3), timer
`+0x734`, target pointer `+0x738`, hover `+0x740`, display `+0x744`, fade
`+0x748`. Constructor `0x19b6d0` gives float32 defaults 0.4, 7.5 and 0.33
(`0x3ea8f5c3`), disables parent clipping and parent destruction, enables
AlwaysOnTop and enters inactive. Game overrides hover/display as above.

`updateSelf @0x19b410` first calls base Window update, then exactly one state
handler. It does not carry excess dt into subsequent states.

| State / function | Effect |
| --- | --- |
| Inactive `0x19b3b0` | With nonnull target and nonempty inherited tooltip text, timer += dt; timer >= hover enters fade-in. |
| Enter fade-in `0x19b340` | Position; state=2; timer=0; visible=true; TooltipActive event. |
| Fade-in `0x19ae40` | Missing target/text enters inactive immediately; otherwise timer += dt, alpha=timer/fade; at >= fade alpha=1 and enter active (state=1,timer=0). |
| Active `0x19aee0` | Missing target/text enters inactive immediately. Only display>0 advances timer; >=display enters fade-out (state=3,timer=0). |
| Fade-out `0x19adb0` | Missing target/text enters inactive immediately. Otherwise timer += dt, alpha=1-timer/fade; at >=fade alpha=0 then inactive. |
| Enter inactive `0x19ad20` | alpha=0; state=0; timer=0; detach from parent; TooltipInactive event; target=null; visible=false. |

`resetTimer @0x19aa50` only resets inactive/active states, not either fade.
`setTargetWindow @0x19b600` for a changed nonnull target attaches tooltip to
System sheet, then copies target tooltip text, resizes and positions. It
resets timer and assigns target last. It never changes the state enum.
Null target only resets timer and assigns null; actual hide/detach happens
on update. Rapid target switches therefore preserve fade progress.

Window mouse-enter `0x112f60` sets cursor and tooltip target before its
event. Mouse-move `0x112d50` only resets tooltip timer. Mouse-leave
`0x112db0` and mouse-down `0x112c60` set tooltip target null before events.

## Tooltip geometry and render consumers

`positionSelf @0x19b1d0` sets absolute position to cursor position plus the
cursor image's rendered width/height (zero when no image). It queries the
render rectangle but does **not** clamp or flip at screen edges in this
shipped build. `onTextChanged @0x19b2e0` calls base then size then position;
tooltip's own mouse-enter positions before base event processing.

`Tooltip::getTextSize_impl @0x19af70` uses default-resolved font, formatted
line count and extent with LeftAligned formatting against renderer rect,
font line spacing, and signed nearest-pixel rounding. No font returns zero
size. `FalagardTooltip::getTextSize @0x3d560` adds current window pixel size
minus look's `TextArea` size to this text size. `sizeSelf @0x19b170` sets
absolute pixel dimensions.

Resource-derived mapping in `media/UI/GuiLookSkin.scheme`:
`GuiLook/Tooltip -> CEGUI/Tooltip`, renderer `Falagard/Tooltip`, look
`GuiLook/Tooltip`. The `media/UI/GuiLook.looknfeel` TextArea uses Tooltip
edge-image margins. Actual imagery deliberately uses frame left offset 20,
top offset minus its height; enabled/disabled imagery is unclipped. These
must be consumed by the existing look compiler, not replaced with an
invented rectangle next to the cursor. Settings uses `Tooltip` properties;
the selected main/options layouts do not manufacture tooltip text.

## Acceptance boundary

For current menu consumers the required additions are: manager-owned
default tooltip, genuine target/timer/visibility tree effects, resource
look/font/cursor sizing, lifecycle callbacks that invalidate per-window
skin bindings, and actual deferred release of widget/property allocations.
Validate with scalar/tree/property contract tests and resource compilation;
no click/frame scenario is implied by this source review.

This research alone does not close full original Window constructor,
arbitrary dynamic factory/plugin loading, allocator exception ABI, all
look replacement behaviors, or whole-library CEGUI coverage. Each original
function retains its own full-contract assessment in the registry.
