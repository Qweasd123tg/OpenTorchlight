# CGameUI startup recovery — 2026-10-09

## Scope and evidence

`CGameUI::create()` at `0xa9e4a0`, 32473 original bytes, is reconstructed in
its original `gameui.cpp` TU. The previous definitions are preserved. The entry
is divided into eight always-inlined implementation phases under
`decomp/include/GameUIStartup/`; no alternative runtime or guessed game mechanics
are introduced. Original ELF SHA-256:
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

The entry creates the cursors, audio bank, renderer/System, schemes and fonts,
interface sheets and item imagesets, HUD, skill/hotkey widgets, menus, tooltips,
console and pool of 100 linked text events. It retains construction order,
resource names, callback/member-pointer identities, settings conditions,
geometry, window flags, initial IDs and cached values.

Original exception handlers recover from `CEGUI::GenericException` by value
around the first scheme's resolution/load and each existing item's imageset
creation/resolution/add sequence. They log the message at critical level and
continue. The WindowsLook load and item-file resolution are outside those
catches, as in the original ASM.

## Details deliberately retained

- The fifth cursor is a distinct allocation from the fourth cursor's surface.
- Native font width uses the first aspect-ratio call and integer truncation.
- SerifHuge gets markup configuration but is absent from the later resolution list.
- The item imageset name uses byte widening after UTF8 conversion, matching the
  original overload rather than silently changing its encoding behavior.
- Pet mana initialization repeats the health-hover tooltip assignment.
- The attack button receives ID100 before subscriptions; the other primary
  buttons receive IDs afterwards. Hotkeys receive ID0 before subscription.
- Item/skill/pet menus keep their distinct scene and root-window arguments.
- Active/free text lists are allocated in the original order; free entries are
  prepended with matching previous/next links and initial text/color/float state.

## Declarations and pinned SDK

The CEGUI renderer declaration comes from pinned OGRE 1.6.5, with only include
paths adapted to the existing vendored CEGUI layout. Its license and source
hashes accompany the header. Renderer/System allocation sizes are checked.
The game's added font markup fields use an offset-checked partial overlay;
the stock SDK font is not falsely claimed to contain them.

Constructor prototypes and previously incomplete menu override declarations
were checked against symbols, existing base declarations and relevant getters.
Convenience constructors for the inlined tooltip/foldout/text-event setup are
always-inlined initializers, not claims of recovered external constructor ABIs.
No opencode-owned UTF8 implementation was changed.

## Controlled full-entry comparison

256 original-versus-candidate pairs completed, with zero differences and zero
incomplete reports. Sixteen scenarios each use sixteen variants, including:

- null bitmap/cursor, absent item file, absent pet button, empty file list,
  null imageset, nonempty event connection cleanup;
- pre-existing cursor/storage vectors, existing imagesets, reserved menu vectors,
  and an already created information window;
- exceptions in first-scheme file resolution, first-scheme load, item imageset
  creation and item native-resolution setup;
- all sixteen sound-availability masks, setting values -1/0/1/2, Unicode paths
  and key labels, fractional aspect ratios and differing widget geometry.

Both sides use controlled SDL, file/resource, logging, rendering, audio,
constructor and UI collaborators. Only audited value/memory helpers run normally.
Indirect calls are restricted to initialized font-resolution and event-subscription
vtables; no real event callback is invoked. Captures include ordered calls,
arguments, all relevant UI fields, vectors, text/flags, member callback pointers,
font markup and the complete text-event lists. Unsupported pointers fail capture.

The initial 192-pair baseline completed without differences but the fixture used
an inverted success return, so its overall failure was not counted as a pass.
That error was corrected before the completed 256-pair run. The two recovery
handlers were found by auditing original exception ASM, then added and tested.

New GenericException copy/destructor and event-functor helpers normalize MATCH.
The implicitly emitted FileInfo destructor differs in its wide-string inlining;
512 separate direct comparisons passed rather than treating startup's use of
that shared helper as independent proof. They cover all four-field combinations
of empty, unique, shared and leaked-refcount representations, short/long text
and wide Unicode. A pinned wide-destructor adapter bridges the original external
call and candidate inlining; intercepted representation releases expose exact
release order/refcounts without inspecting freed memory. This weak helper is
not counted as another game function.

## Final validation

All twelve intentional semantic faults were rejected by completed comparisons,
with zero incomplete captures: duplicate cursor, renderer batch size, native font
width, scheme/imageset error severity, sheet mouse pass-through, original pet
hover assignment, magnify setting, attack button ID, pet scene, text-pool size
and console root. All 34 changed headers compile separately, and 31 allocation
size assertions pass.

Strict Stage and independent root checks both passed all 173 headless tests.
Acceptance is 1211 game functions / 836445 original bytes: 1170 normalized
MATCH and 41 behavioral acceptances. This adds one large function and 32473 bytes,
bringing the large-function recovery series to 25 functions. The candidate is
behaviorally accepted, not reported as a machine-code MATCH.

No original game window was launched. The tests finish before game main; this
is not a standalone rebuild or rendered-game validation claim.

## Tool regression

The unchanged tool implementation was also retested against the updated root:
532 tests, 531 passed and one existing Ghidra/JDK-dependent skip. No comparison,
exception, capture, timeout or publication gate was relaxed for this recovery.
