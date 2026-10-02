# Generated Dropdown default double-click result

`original-code`: external read-only `Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
The accepted boundary is the whole default callee
`CDropdownMenu::onDoubleClick(ELayoutFunction, std::wstring) @0xb05e80`.
It does not include its event wrapper, string conversion or the Continue override.

## Whole source body and ABI

The exact sized ELF symbol is six bytes, `b8 01 00 00 00 c3`, SHA-256
`2db31f4e09597946e56e859813bfdad7046d457c32332c3a882654d1e3ffdf67`:

```asm
b05e80: mov $0x1,%eax
b05e85: ret
```

`original-code`: MOV writes EAX32=1 and zeroes the upper RAX32. The C++ bool
return is AL8=1. RET reads the eight-byte return address at entry RSP, publishes
it to RIP and advances RSP by eight. Both complete instructions are included;
there is no padding, alternative exit, branch or direct/indirect dependency.
There are no object/global reads or writes, allocations, cleanup operations,
floating arithmetic or source error paths. Integer flags are unchanged.

The body does not read the incoming `this`, layout enum or by-value string
argument. Its generated ABI therefore initializes only RSP64, Ghidra register
offset `0x20`, and reads AL8, offset `0x0`, as the return. Other registers are
not silently initialized. Valid caller-owned argument objects remain the
external caller's language-level precondition; the callee needs no emulated
object, string representation or invented state owner. It has no field map.

`src/ui_dropdown.cpp::dropdown_default_double_click` executes generated
`fn_00b05e80` over an initialized private RET slot. The memory view supplies
only that eight-byte sentinel; unexpected reads and all writes fail. The
returned AL becomes a C++ bool. This private stack and address identity are
explicit port adapters, not original game-object addresses or state fields.

## Actual virtual target and caller cleanup boundary

`original-code`, pinned ELF data and ASM:

| Owner | Published vtable address point | `+0x48` target |
| --- | --- | --- |
| CDropdownMenu | `0xfee490`, table symbol `0xfee480` | `0xb05e80` |
| CMainMenu | `0xff30f0`, table symbol `0xff30e0` | `0xb05e80` |
| CContinueGameMenu | `0xff2ab0`, table symbol `0xff2aa0` | override `0xc334e0` |

CMainMenu constructor publishes `0xff30f0` to its vptr at `0xc53b24`, after
the base constructor call `0xc53b1f`. Thus Main actually inherits the default
double-click function; this is not inferred from the absence of a source method.

`CDropdownMenu::handle_onDoubleClick @0xb192e0`, complete symbol size503,
is a separate caller. It obtains the event window at `0xb1930a`, reads its
layout enum via window+`0x1d8` at `0xb19317/2c`, converts the window's name
at window+`0x520` through CEGUI UTF-8 and `StringConvertToWide`, applies the signed prefix field
window+`0x680` at `0xb19349`, checks substring bounds and constructs a by-value
wstring argument. The virtual target is loaded from vptr+`0x48` at `0xb193a2`;
`0xb193b4` calls it with RDI=this, ESI=enum32 and RDX=argument object address.
The wrapper's null-window path returns true without calling the callee.
The name-field identity is corroborated by shipped `Window::rename`, which
addresses window+`0x520` at `0x117e63`.

After this call, the argument temporary and converted name are released by
the caller. `0xb1941f/28` and `0xb19452/5b` explicitly save/restore AL around
wstring `_Rep::_M_destroy` calls. Reference-count paths, the substring
out-of-range throw `0xb193f6/3fb` and cleanup/unwind `0xb1948e..a4` belong to
that wrapper. They are not cleanup performed by the six-byte callee.
General string/allocator ABI, event-prefix decoding and complete wrapper
exceptions remain outside this callee's acceptance. This transfer does not
close `handle_onDoubleClick`, `mapEventHandlers`, CMainMenu or CDropdownMenu.

The Continue target remains its original distinct override. Its enum14..17
selection/health behavior is documented in [cegui-character-load.md](cegui-character-load.md).
Main's default does not request a page change or activate a save.

## Real library return-value consumer

`library-derived`: upstream CEGUI 0.6.2, tag `v0-6-2`, commit
`3ed5c719c3bb27b877b192e034ef2c0b05ea722c`; local source provenance and
vendor differences are in [cegui-source-integration.md](cegui-source-integration.md)
and `third_party/cegui-0.6.2/PATCHES.md`.
The external shipped `lib64/libCEGUIBase.so.1` was also rechecked read-only,
SHA-256 `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.

`original-code`/`library-derived` comparison for the consumed result:

- Shipped `Window::onMouseDoubleClicked @0x1120b0..0x1120d1` forwards
  `EventMouseDoubleClick` to EventSet. Upstream
  `src/CEGUIWindow.cpp::onMouseDoubleClicked` fires the same event.
- Shipped `Event::operator() @0xce500..0xce55c` invokes each SubscriberSlot,
  zero-extends returned AL at `0xce539`, ORs the previous handled byte at
  `0xce53f` and writes EventArgs+`0x8` at `0xce542`. The loop visits all
  subscribers, including after handled=true. Upstream `src/CEGUIEvent.cpp`
  performs the same `args.handled |= subscriber(args)` accumulation;
  `include/CEGUIMemberFunctionSlot.h` returns the bound member function's bool.
- Shipped `System::injectMouseButtonDown @0x10c320..0x10c592` dispatches the
  second click to the double-click virtual slot at `0x10c559`. Its parent
  routing loop tests the handled byte at `0x10c508`; the injection returns
  that byte at `0x10c51e`. Upstream `src/CEGUISystem.cpp` uses the same
  multi-click/handled routing contract.

Consequently the default result has a concrete state consumer: CEGUI sets
EventArgs.handled and stops routing this double click to further parent
targets. It does not stop the remaining subscribers of the same Event.
`src/cegui_menu.cpp::Impl::double_click` now returns
`dropdown_default_double_click()` for Main-bound event windows. The existing
real CEGUI subscriber invokes that callback and consumes its bool through this
library machinery. Its Load route retains the Continue override.
`src/frontend.cpp` also invokes the helper for a subscribed Main double click
and terminates dispatch according to its returned bool; its separate Continue
route still owns save activation. Neither Main consumer creates a game-state
effect for this default function.

## Verification boundary

The complete source bytes, virtual target data, wrapper return preservation
and pinned upstream/shipped library bool consumption were statically reviewed.
`compare_settings_queries.py` passed2470 cases, including219 default cases
against the unchanged whole6-byte body and generated production helper. All
initialized opaque object/name/guard bytes remained unchanged; ignored operands
do not establish a wstring ABI or constructor contract.

`settings_queries_controls_test` directly feeds the result into a real CEGUI
Event subscriber: handled becomes true and the following subscriber still
runs. No input, frame or GL is injected. Core and probes were built. The callee
is accepted whole; its caller/string wrapper and Continue override remain separate.
No original game, GUI clicks, screenshots or frame/performance measurement was
run for this function. The small callee has no FP environment dependency.
