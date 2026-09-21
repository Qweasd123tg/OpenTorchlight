# CEGUI pointer timing and mouse auto-repeat

## Inputs and boundary

This note records the timing subset used by the frontend from the shipped
`lib64/libCEGUIBase.so.1`:

- path: `/home/qweasd123tg/Games/Torchlight/game/lib64/libCEGUIBase.so.1`;
- SHA-256: `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`;
- ABI: x86-64 CEGUI 0.6.2 library shipped with this Torchlight build.

All rules below are `library-derived` from direct disassembly. Symbol names are
used for navigation; comparisons, field widths and call order come from the
listed instruction ranges. The portable implementation is
`UiPointerTiming`/`UiAutoRepeatTiming` in `src/ui_pointer_timing.cpp`.

The helper owns numeric state only. `UiWindowRuntime` remains the owner of
Window identity and capture, while `Frontend` owns event propagation and game
callbacks. A host event timestamp is the portable clock sample for an
injection. Native CEGUI samples `SimpleTimer::currentTime()` at the end of down
dispatch and during release validation; this difference is explicitly the
host-adapter boundary, rather than an invented frame counter.

## System click tracker

`System::System @ 0x10dc4f..0x10dd7d` installs:

| System field | width | value / owner |
|---|---:|---|
| `+0x138` | 8 | single-click timeout `0.2` seconds |
| `+0x140` | 8 | multi-click timeout `0.33` seconds |
| `+0x148,+0x14c` | 4+4 | tolerance size copied from the static default |
| `+0x150` | 8 | pointer to five 40-byte per-button trackers |

The static initializer `0x10b4b6..0x10b4d2` writes `12.0f` to both members of
`System::DefaultMultiClickAreaSize`. The read-only defaults at `0x1da010` and
`0x1da018` are respectively `0.2` and `0.33`. Each tracker constructed at
`0x10dd42..0x10dd74` has:

| tracker offset | width | meaning |
|---|---:|---|
| `+0x00` | 8 | last down time |
| `+0x08` | 4 | click count |
| `+0x0c..+0x1b` | 16 | tolerance `Rect` |
| `+0x20` | 8 | target `Window*` |

There are five actual button trackers. The separate enum value `6` is the
Window auto-repeat `NoButton` sentinel; it is not a tracker index.

### Down grouping and dispatch

`System::injectMouseButtonDown @ 0x10c320..0x10c58a` updates the syskey mask,
finds the current target, then increments the selected tracker count. It resets
the sequence to count one when any of these conditions holds:

1. multi-click timeout is positive and `now - last_down > timeout`;
2. the pointer is outside the saved tolerance rectangle;
3. the current target differs by pointer identity;
4. the incremented count exceeds three.

On reset, the rectangle is anchored at the current position with the configured
width and height, and the target is replaced. It is not re-anchored on the
second or third press. `Rect::isPointInRect @ 0x0f4550..0x0f4582` proves
inclusive left/top and exclusive right/bottom bounds. Timeout equality remains
inside the sequence. A non-positive multi-click timeout disables only the time
test; area and target tests still apply.

Propagation walks `System::getNextTargetWindow`. For each receiver that wants
multi-click events, count two calls virtual `onMouseDoubleClicked` and count
three calls `onMouseTripleClicked`; count one calls `onMouseButtonDown`.
Receivers that do not want multi-clicks receive ordinary down for every count.
The handled bit stops propagation. The tracker timestamp is stored after that
dispatch. No fourth-click event exists: the fourth qualifying press has already
reset to count one.

`Window::setWantsMultiClickEvents @ 0x111840..0x111850` is a byte write at
`Window+0x211`; `Window::Window @ 0x11b317` defaults it to true.

### Up and click eligibility

`System::injectMouseButtonUp @ 0x10c150..0x10c310` first clears the syskey,
captures the tracker count in the event args, resolves the current target and
propagates virtual `onMouseButtonUp`. It subsequently attempts `onMouseClicked`
when all of the following hold:

- single-click timeout is exactly zero, or `now - last_down <= timeout`;
- release position remains in the same half-open tolerance rectangle;
- release target is the identical `Window*` saved on down.

Click propagation starts from the release target and has its own handled bit.
The function returns the logical OR of the prior up handled state and click
handled state. A failed click eligibility check does not mutate the tracker.

## Per-Window mouse auto-repeat

`Window::Window @ 0x11b33a..0x11b363` initializes:

| Window field | width | default |
|---|---:|---:|
| `+0x214` | 1 | enabled = false |
| `+0x218` | 4 | delay = `0.3f` |
| `+0x21c` | 4 | rate = `0.06f` |
| `+0x220` | 1 | repeating = false |
| `+0x224` | 4 | elapsed (zeroed when a press is armed) |
| `+0x228` | 4 | repeat button = `6` (`NoButton`) |

`setMouseAutoRepeatEnabled @ 0x111890..0x1118aa` writes the enabled byte only
when it changes and then resets only the repeat-button sentinel. It deliberately
does not clear elapsed or repeating. `setAutoRepeatDelay @ 0x1118b0` and
`setAutoRepeatRate @ 0x1118d0` are direct float replacements, including unusual
zero or negative values.

`Window::onMouseButtonDown @ 0x112c60..0x112d42` does rise-on-click for left,
then handles auto-repeat before emitting `EventMouseButtonDown`:

1. when enabled and the repeat button is `NoButton`, it tries `captureInput()`;
2. if the event button differs from the stored one and this Window owns capture,
   it stores the event button, sets elapsed to zero and repeating to false;
3. a failed capture therefore leaves repeat unarmed;
4. another down for the same active button does not reset the timer;
5. a different down while capture is still owned replaces the button and resets
   the phase.

`Window::onMouseButtonUp @ 0x112010..0x112045` checks neither event-button
identity nor a left-only rule. When auto-repeat is enabled and any repeat button
is active, any mouse-up calls `releaseInput()` and writes `NoButton`. The normal
up event is emitted afterward. `Window::onCaptureLost @ 0x113880..0x1138f6`
also writes `NoButton` before its restoration/retarget/event sequence. Disabling
auto-repeat has the same sentinel-only effect.

`Window::updateSelf @ 0x112ea0..0x112f1e` is called by
`Window::update @ 0x1118f0..0x1119a0` before the WindowUpdated event and child
updates. For an enabled, armed window it adds the frame delta once:

- initial phase fires only when `elapsed > delay`, then sets elapsed to zero and
  repeating to true;
- repeating phase fires only when `elapsed > rate`, then subtracts one rate;
- at most one repeat is generated by one update, even for a large delta;
- initial delay overshoot is discarded, while rate overshoot is retained.

`generateAutoRepeatEvent @ 0x112e10..0x112e90` builds fresh mouse args from the
current cursor/syskey state and calls this same Window's virtual
`onMouseButtonDown`. A repeat is therefore a down event. It is not a System
injection, click, double-click or triple-click, and it does not update the
System click tracker.

## Verification

`tests/ui_pointer_timing_test.cpp` checks the decisive boundaries: exact versus
expired timeouts, half-open tolerance edges, target changes, fourth-press wrap,
five independent trackers, zero-timeout behavior, release eligibility, failed
capture, strict delay/rate thresholds, one repeat per update, retained rate
surplus, replacement by a second button, arbitrary-button up, capture loss and
the sentinel-only configuration reset.

This closes click grouping and Window mouse auto-repeat for the production
frontend chain. Tooltip timers, keyboard repeat, and widget-specific behavior
after the emitted virtual down are separate contracts.
