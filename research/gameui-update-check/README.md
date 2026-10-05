# CGameUI::updateIngameUI: large-function recovery, initial evidence

Status: analysis only. No replacement body, no accepted-function increment,
no claim that the whole function has been reconstructed or dynamically tested.
This continues the decomp track, not the historical remake/UI runtime.

## Input and scale

Original ELF SHA256:
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Symbol: `CGameUI::updateIngameUI(float, CGameClient*, Ogre::RenderWindow*)`.
Address interval `[0xab8100, 0xacbb35)`, 80,437 original bytes.
The local accepted-function snapshot following a1d05cc contains 1,311 entries;
this is the largest remaining game function by original symbol size.
The local owners.json has no gameui.cpp owner; a user's newer PC assignment
must take precedence before source changes.

Both the raw Ghidra draft and the older core export report a timeout for this
function. They are not usable pseudocode. Recovery currently uses actual ASM,
original symbols/vtables, neighboring constructors and pinned library source.
Run `index_assembly.py ORIGINAL_ELF OUTPUT_DIRECTORY` to reproduce the static
index. The script verifies the ELF hash and never executes it.

Static counts: 15,760 decoded instructions, 1,877 call sites, including 320
indirect sites, and 123 distinct direct target forms. These are code locations,
not invocation frequencies or test coverage. Syntactic branch indexing excludes
exception-table edges and does not prove semantic block boundaries.

## Confirmed entry behavior

- Four localized string statics are guarded before any settings/input work:
  g_HP, g_Mana, g_XP, g_Fleeing (0xab8114..0xab8169; out-of-line construction).
- 0xab8176..0xab81b8: compare RadioButton +0x200's selected flag with
  GetInt(KSETTINGS_TOGGLE_ITEM_NAME)==1. Query the setting again only on mismatch
  and call setSelected with the second result. Do not cache across callbacks.
- Mouse manager is embedded at +0x12a8. Calls test buttonPressed(1), then
  buttonPressed(0), buttonHeld(1), buttonHeld(0) in short-circuit order.
  The no-input branch also handles the visible +0x430 object's child window;
  it must not be replaced by an unconditional early exit.
- At 0xab81d9 the +0x540 pointer is CCinematicMenu, independently confirmed by
  constructor call 0xaa391f and pointer store 0xaa3924. If byte +0x30 is nonzero
  OR byte +0x31 is zero, call its virtual update(float), slot +0x18, then return
  through 0xabff98. Exact meanings of the two flag fields are not yet named.
- Character +0x330 dispatches AI state, with multiple out-of-line menu actions.
  The state is re-read at 0xab8288 after callbacks; this is not a single snapshot
  switch. Character virtual slot +0x348 resolves to setAIState(EAIState).

## Verified menu path example: state 0x13

Branch target 0xac036e. With nonnull character target at +0x340:
closeAll; re-read current character/target; if target sound bank +0x298 exists,
queue sample 0x26 with floats 0.0 and 0.1; open inventory; set merchant owner
from current character target; set merchant player; open merchant;
set current character AI state to 0x14. Rejoin at 0xab8288, which re-reads state.
Virtual dispatch and callback order must be retained. Null target skips the
open path. State names here are numeric; no invented enum names are committed.

## Main semantic areas and anchors

These are navigation anchors, not independent functions or completed slices.

- 0xab82bf: updateSlots; editor flag check and character/target gating
- 0xab8321: selected HUD window visibility, automap, stat/skill notices
- 0xab8432: HP/maxHP ratio and CEGUI position/size/tooltip
- 0xab8885: manaFloat/maxMana counterpart
- 0xab8ce9: experienceGate-based experience display
- 0xab93d4: window dimensions and screen edges; camera matrix operations
- 0xab9bde and 0xac35ce: text events
- 0xab9c53..0xab9e61: item labels and world-to-screen positioning
- 0xab9fd3..0xaba1a8: character labels and world-to-screen positioning
- 0xaba2e3 onward: settings/debug counters, missile/particle cache, audio channels,
  room query and extensive formatted-string construction
- 0xac28a9 onward: hover target/item branches; equipment and character descriptions
- 0xac1e22: queued context tips under modal/character gates
- 0xac1e53: optional visible console update, re-reading the pointer before call
- 0xac1e7d: menu manager update with original float/client/render-window arguments

## Why the machine function is much larger than its gameplay logic

There are 253 static Ogre::UTFString destructor call sites, 243 std::string
ones, 137 unsigned-short string ones and 110 CEGUI::String ones; normal paths
and exception cleanup are both present. Do not translate these as hundreds of
handwritten memory operations. Recover source-level lifetime scopes and use
pinned library types so the original compiler generates cleanup.

The sole indirect jump at 0xac2de8 is NOT the AI-state dispatcher. Its table at
0xfe4618 has seven entries: abfe54, abfe54, ac2e37, ac2e25, ac2e13, ac2e01,
ac2def. The preceding UTF surrogate handling, continuation-byte loop and
length <=6 guard correspond to Ogre 1.6.5 UTFString::_utf32_to_utf8 and
_load_buffer_UTF8 (OgreUTFString.h lines 2061..2096,2238..2258 in pinned source).
Use that library implementation; do not invent game logic for this table.

## Verification plan and current limits

1. Recover layout fields from create/constructors and confirm each virtual slot.
2. Preserve entry gating and menu transitions before reconstructing HUD math,
   label loops, tooltips, debug formatting and final update ordering.
3. Build differential cases for input short circuiting, cinematic early returns,
   numeric AI states, callback-driven pointer/state changes, null optional
   services, string lifetime/Unicode cases and exceptional exits.
4. Compare CEGUI operations headlessly. No window/main launch is authorized.
5. Only accept a complete replacement after normalized MATCH or a sufficiently
   broad original-vs-replacement fixture plus the integrated regression suite.

No production source/header edits were made for this analysis. Earlier
research/ui-hud-bars.md is a useful ASM lead, but its old remake instructions
remain frozen. Do not assume a [0,1] clamp or copy its inferred formula without
checking the complete original branch paths (including NaN and rounding).

## First executable characterizations (2026-10-05)

These probes run the original entry point with controlled collaborators and
compare its trace with a small model. They deliberately do not install a
replacement CGameUI function or contribute to acceptance totals.

- GameUIEntryProbe: 2,592 passing cases. Settings 0/1/-1, second-query changes,
  radio pointer replacement, all sixteen combinations of the four input tests,
  cinematic pointer replacement and the three early-return flag combinations.
  With no input, the child window is controlled as invisible. The visible-child
  positioning branch is still excluded. String statics are pre-initialized;
  first-call translation is excluded. Nine intentionally wrong models fail.
- GameUIHealthProbe: 810 passing cases. The original frame prefix is stopped
  immediately after the health sub-bar position call, before tooltip string
  construction. The model matches CEGUI position/size values for negative HP,
  zero, over-max HP, negative/zero/positive denominators, rounding boundaries,
  and callback changes to cached layout fields. Nine intentionally wrong
  models fail. No full-frame behavior or later cleanup is thereby accepted.

The HP result resolves an uncertainty in the historical HUD notes: the tested
original path has a lower clamp only, not an upper clamp at one. NaN survives;
replacing it with zero is observably different. Positive HP with zero max HP
also follows the original floating-point division behavior. No invented
sanitization belongs in the reconstruction.

The cached health position is a CEGUI::UVector2 at +0x16cc and cached size is
at +0x171c, corroborated by original create() reading PlayerHealthBar position
and size. Its geometry uses CEGUI::UDim::asAbsolute(1), including PixelAligned
rounding before adding the offset. Rendering operations are:

1. Health position x = cached position x; y = position y + height - height*ratio
2. Health size x = cached width; y = height*ratio
3. Health sub-bar position = (0, -(height-height*ratio))

Each expression uses the original callback-time reads. The second and third
operations re-read size fields after the preceding CEGUI call. Upper clamping,
missing lower clamping, NaN sanitization, integer division, cached height,
wrong anchor/sign, unscaled mask and omitted pixel rounding are all rejected
by the probe. Exact finite/nonfinite captures are compared byte-for-byte.

Run with the established hybrid environment:

    python3 research/gameui-update-check/check_entry.py
    GAMEUI_ENTRY_SOURCE=research/gameui-update-check/GameUIHealthProbe.cpp \
      GAMEUI_ENTRY_ROOT=build-decomp/gameui-health-characterization \
      python3 research/gameui-update-check/check_entry.py
    python3 research/gameui-update-check/check_entry_faults.py
    python3 research/gameui-update-check/check_health_faults.py

The probes use the project's original-toolchain hybrid loader, zero production
hooks and pre-main exit. The current prefix probes stop with a controlled std::runtime_error and verify
the boundary marker and exception text. This preserves C++ unwinding rather
than treating a partial frame as a completed update. Earlier checkpoints used
longjmp; the health/menu probes and all their faults were re-run after replacing
that mechanism, including paths with nontrivial temporary destructors.

### Menu prefix

GameUIMenuProbe passes 140 cases across state 0x11 (combine), 0x13 (merchant),
0x15/0x16/0x19/0x1a (enchant menu modes) and 0x24 (stash). It covers missing
versus present targets, optional sound banks and replacement of the current
character during closeAll, inventory opening, owner assignment and player
assignment. The original is stopped at updateSlots, before the HUD body.
The combined menu/retirement probes reject seventeen wrong models. Individual callback targets are spies; this does
not validate the internals of merchant/enchant/stash services themselves.

Verified resulting states: combine ->0x12, merchant ->0x14, enchant modes
->0x1c, stash ->0x26. Item-owner state 0x16 reads character +0x350 and calls
setOwnerItem; other tested states read +0x340 and call virtual setOwner. Stash
and item-owner mode skip the NPC opening sound used by the other tested modes.
The +0x578 service is CFishingMenu::setVisible(false), identified independently
from the original create() constructor/store and the CFishingMenu vtable.

Retirement state 0x1b now has 700 passing prefix cases: the global +0x48 limit is checked
against unsigned character level +0x100, with a negative limit disabling that
restriction. Its allowed path uses the enchant menu with mode 0x1b; the denied
path uses localized g_Retire/g_CannotRetire and openModalDialog. This is a separate test from the seven-state, 140-case probe. It covers
negative/zero/positive limits, equality, unsigned high-bit levels, absent targets,
optional sound and character replacement. Localization statics are initialized
with controlled nonempty strings; formatting and modal services are spies.
The denied path preserves the message composition and resets AI state to 2.

### Fresh decompiler attempt

Pinned Ghidra 12.1.3 was downloaded from its official NSA GitHub release and
verified against the repository's SHA256. A full isolated import/analysis
finished successfully (587 seconds). Increasing the function timeout from
120 to 600 seconds exposed another concrete limit: the decompiler reported
`Response buffer size exceeded` rather than producing a C draft.
The project was saved successfully; headless exit code 0 alone was NOT treated
as a successful export. A second targeted read-only export disables syntax-tree
output and raises DecompileOptions.maxPayloadMBytes to 128. Its result must be
checked separately; no draft is claimed available merely because the process
started. These changes live only in this research script, not the shared
pipeline owned by the PC worker.

The second export succeeded: 10,249 lines / 447,247 bytes of navigation C,
SHA256 `538ea393879808c9e6b981132df105c258e21b776c320d61b58f450055e5c75f`.
It is not compilable recovered source. Known decompiler issues remain visible:
misrepresented hidden return arguments, missing member-call arguments, wrong
return types and expanded standard/library string lifetime machinery. The
verified ASM/probe models, not this C draft, determine eventual source behavior.
A stale error file from the first attempt is preserved separately as evidence;
the exporter now removes an old error marker after successful output.

As of this checkpoint: four original-prefix characterizations pass 2,592 +
810 + 140 + 700 cases; 9 + 9 + 17 intentionally wrong models are rejected.
The complete updateIngameUI replacement remains unfinished. Production source,
headers and integrated tests are unchanged from a1d05cc (148 tests passing,
1,311 accepted functions). Prefix tests do not change that count.

## Second checkpoint: floating window and no-character frame

GameUITooltipProbe passes 1,512 cases for the visible floating window when no
mouse button is pressed/held, then returns normally through the cinematic path.
It compares signed/large mouse coordinates, width/height pixel rounding, the
26-pixel margin, captured window identity and later cinematic-pointer reads.
The original calls getWindowHeight but does not use its result to clamp this
position. A screen-height-clamp mutant initially survived because all test y
coordinates were small; adding y=999 and y=1000 exposes it. The initial result
is retained. All nine final tooltip faults are rejected.

GameUINoCharacterProbe passes 576 complete controlled no-character frames, not
just a prefix. It uses real pinned Ogre matrix/quaternion math and checks:

- both-window guard and three visibility operations
- orientation -> rotation matrix, translation, inverse, projection * view
- fresh camera reads after callbacks and the orientation y axis
- text events with the original elapsed value and false flag
- mandatory modal query, absent/hidden/visible console and final menu update
- console/menu-manager pointer changes during preceding callbacks

The Camera vtable +0x2d8 slot is confirmed through the original shared-library
relocation at 0x60b4e8: `_ZNK4Ogre7Frustum19getProjectionMatrixEv`.
Twelve wrong models are rejected, including reverse matrix order, missing
inverse/translation, x-axis substitution, cached pointers and swapped final
client/render-window arguments. Debug window +0xe0 is absent in this fixture;
performance-text construction and active-character branches remain excluded.

A typed navigation export also succeeded. The final scoped ABI-hinted draft is
10,241 lines / 443,318 bytes, SHA256
`0589eea4a6703cdf28856eedfb18a7e6a9462d7873aa217363c1fb86e873201c`.
Explicit hidden-result and member-call arguments repair several visibly wrong
Ghidra calls (for example RadioButton::setSelected and Window::getWidth).
The 471 supplied layouts and other inferred signatures are still hints, not
proof. The research copy of the exporter does not modify the shared pipeline;
its project changes are discarded after the read-only export.

Current six characterization tests: 6,330 cases total. Final targeted faults:
56 rejected (9 entry +9 health +17 menu/retirement +9 tooltip +12 no-character).
This still does not accept the entire updateIngameUI function. The accepted
production checkpoint remains a1d05cc, with no new production code/header edits.

## Third checkpoint: active HP/mana tooltips and experience

GameUIBarsProbe passes 5,832 cases through both player bars and their tooltips,
ending before experience evaluation. It uses the original number formatter and
real CEGUI strings. Covered inputs include fractional/negative/over-max mana,
zero maximums, callback replacement of the current character, geometry changes
between UI calls, and ASCII/Cyrillic/CJK labels. The bar uses the fractional mana
value; its tooltip truncates mana toward zero. Tooltip maximum is queried before
current value, after geometry callbacks. The original text is `label:now/max`,
without an added space. Twelve wrong models are rejected.

GameUIExperienceProbe passes 7,776 cases and stops after XP cleanup, before
pet and level-name work. The original sequence is important:

1. Snapshot current XP as float and capture current level before the first
   singleton call; query previous gate
2. Re-read level before a fresh singleton call; query current gate
3. Re-read level before another singleton call; query previous gate again
4. Use `(floatXP - float(firstPrevious)) / float(current - secondPrevious)`
5. Clamp finite fractions to [0,1], preserve NaN, scale cached width and truncate
   the final width toward zero
6. After setSize callbacks, obtain another current gate and read live absolute
   XP for the tooltip; the tooltip is not rebased to the level's starting XP

Fourteen wrong models are rejected. This includes integer-first numerator
arithmetic near 2^24, reused gate values, stale XP/level reads, missing clamps,
wrong final-width rounding and a rebased tooltip. The raw decompiler's NaN
branch is misleading: ASM at 0xac2322 uses MINSS with the fraction as its source,
and the controlled original comparison rejects replacing NaN with one.
Nonfinite float-to-int observations describe the pinned x86/GCC path, not a
portable C++ guarantee for arbitrary compilers or fast-math settings.

There are now eight characterizations / 19,938 cases and 82 rejected targeted
wrong models. These overlap intentionally and are not a branch-coverage
percentage. No complete updateIngameUI replacement has been accepted. The
production baseline and original binary/assets remain unchanged.

## Fourth checkpoint: pet HUD and stateful updates

GameUIPetProbe passes 4,320 cases with TWO successive frames per side. It extends
through the pet HUD and stops before level-name retrieval. Twenty-one wrong
models are rejected. Scope includes:

- absent pets, a covered left panel, and visible first-pet selection
- re-reading the current character/list after leftCovered, but retaining the
  selected pet across setVisible callbacks
- cached pet mode +0x710 / UI +0x16c8, radio-button mapping 0/1/2 and unknown modes
- horizontal HP/mana widths with lower-only clamping and final integer truncation
- pet HP/mana tooltips through the original number formatter and real CEGUI strings
- original narrow-name conversion (ASCII pet names here), conditional text updates
- numeric AI state 0x2a's timer, hour/minute rollover and zero padding
- near-death status with localized text plus `!`, and hidden normal status
- name-change callbacks changing the pet AI state before the subsequent status test

Actual CEGUI::String objects are placed at the observed window text offset +0xc0;
rendering/window creation remains stubbed at the service boundary. Two frames
exercise already-updated text and mode caches. Timers are finite and bounded
(-1.1 through 3661.25 seconds); arbitrary huge/nonfinite timer behavior and
non-ASCII pet-name narrowing are not claimed. Resource labels do include
ASCII/Cyrillic/CJK. Small rounding-edge and realistic larger bar widths are both
used; callback replacement of character/pet data remains explicit.

There are now nine characterizations / 24,258 cases and 103 rejected final wrong
models. This remains research toward the single large function, with no new
accepted production implementation and no change to a1d05cc's acceptance totals.

## Fifth checkpoint: level label, fading messages and menu lists

GameUILevelProbe adds two passing tests: 8,640 level/message cases and 270
menu-update cases, each with two frames per side. All 24 targeted wrong models
are rejected. The probe ends at the subsequent getWindowWidth call, before the
active-character camera/label traversal.

Level-name and message checks use real original UTF8 conversion, real CEGUI
String comparisons and real colourToString. A missing client level skips the
whole level-name/message block; it does not invent clearing or fading actions.
A modal query hides both messages and leaves their timers/alpha alone.

For each active message, text callbacks precede the timer/alpha reads. Duration
is reduced by the full frame delta; at <=0 it is stored as zero and alpha changes
by delta*(-2.0). The full delta is used, not just the part beyond expiry. Stored
alpha may become negative, while only the colour sent to TextColour and
DropTextColour uses a lower-clamped render value. Visibility remains true for
that updating frame; the next frame's initial alpha gate can hide it. NaN
changes, current-window re-reads between property callbacks and changes to the
second message from the first are included. These observations describe the
original behavior, not a suggested redesign.

Submenu and dropdown lists use different virtual slots (+0x50 and +0x18).
Their base/end pointers are re-read after each callback: tests grow, shrink and
relocate the lists. Fishing and interactive menus follow the two lists; the
interactive pointer is re-read both before its update and before the final
HUD/pet visibility decision. The fixture uses separate dropdown vtables;
sharing its +0x18 slot with fishing's setVisible stub was a fixture setup error
found and corrected before the final pass.

Current totals: eleven characterizations / 33,168 cases, 127 rejected final
wrong models. Every added case remains regional/model characterization, not
acceptance of the entire 80,437-byte function. Production remains unchanged.

## Sixth checkpoint: complete controlled active-character frames

GameUIActiveFrameProbe passes 7,128 cases, two whole controlled frames per side,
without a stop exception. Eighteen targeted incorrect models are rejected.
This adds the active camera path and hidden world-label traversal to the prior
HUD/message/menu regions. It is NOT a full implementation: world labels are
forced hidden, the performance overlay is absent, and the tip queue is empty.

Observed and checked against the original:
- screen width/height stored at +0x1684/+0x1688; span ratio at +0x1680 uses the
  current cached width after getWindowHeight callbacks
- settings YRATIO is queried, but its returned value is not used on this path
- pinned Ogre rotation/position/inverse/projection math and orientation.yAxis;
  camera pointers re-read after service calls that can replace the camera
- updateTextEvents uses the active-character flag and the resulting camera data
- item and character linked-list nodes reload next after hide callbacks
- the current client level is re-read between the item and character traversals
- a modal query occurs for each visited object and again before the final tail
- console visibility, subsequent current-console update, and current final-menu
  update retain the original callback order and frame arguments

Tests include no/one/two objects, changed level/list links, null/hidden/visible
console, current-pointer changes, zero/positive/negative width and frame delta,
and two frames. Matrix arithmetic uses the original-version Ogre library rather
than a newly approximated camera implementation.

Current validated totals: twelve characterizations / 40,296 cases and 145
rejected final wrong models. These intentionally overlap; they are not code
coverage percentages. No new production hook or acceptance entry was added.

## Seventh checkpoint: queued context tips

GameUIContextTipsProbe passes 720 two-frame cases; all 16 targeted wrong models
are rejected. It extends the controlled complete-frame model with real copied
std::wstring tip content and the queue at +0x1960/+0x1968. Tip-seen flags are
bytes at character+0xa17+signed_tip_id, confirmed in original ASM ac4152/ac418b.
Only valid nonnegative IDs 0..3 are supplied here; no bounds-safety claim is made.

The head ID is captured BEFORE getSingleton; the seen check re-reads the head
and character AFTER getContextTip. Nonempty unseen text calls setContents, then
re-reads the tip-menu pointer for its virtual +0x38 show call. After callbacks,
the current actor/head are re-read before setting the seen flag. Empty and
already-seen tips are still marked/removed. Exactly one queue entry is consumed
per frame by shifting the remaining entries; modal frames leave it alone.
Tests alter actor, queue head/storage, menu pointer and returned string storage
at these call boundaries, and include empty/ASCII/Cyrillic/CJK content.

Current validated totals: thirteen characterizations / 41,016 cases and 161
rejected wrong models. Entire-function acceptance is still absent. Next work
prioritizes assembling a coherent implementation draft and its missing-branch
list, rather than expanding the regional test-case counts for their own sake.

## Eighth checkpoint: shared executable phase implementation

`implementation/RecoveredPhases.h` is now a reusable C++98 implementation of the
recovered phases, calling actual original-symbol service bindings. It has no
fixture World/Case/input dependency. `check_recovered.py` substitutes these same
phases into the expected side of the original-vs-new comparisons. Its complete
run passes 9 tests / 15,208 cases (many reuse earlier scenarios), including 400
new closing-menu cases and 1,440 visible-label cases with existing windows.

This is an implementation draft, not a registered production replacement. A
separate GAPS.md lists the missing top-level composition, hover/overlay regions
and validations still needed. Label creation/style and quest/fishing have been
transcribed into code but are NOT covered by the passing cases just reported.
First-use translation is similarly present as source but unverified.

The shared code handles visible-label policy and existing-window placement:
items use the original toggle/key XOR rule, characters use the key-or-toggle
rule; hover exceptions and item type 0x1e are preserved. Window dimensions are
captured before show callbacks, screen limits and final window pointers are
read afterward, and both edges use the original 26-pixel margin. Hidden,
covered, hovered and callback-modified paths are included. Creation is excluded
from those tests; the new source must not be described as fully validated.

The test-only PLT switch routes imported services through their original entry
points so the fixture's dependency spies observe them. It does not replace the
recovered decision/math code. Main production and generic tooling remain at
commit a1d05cc, unchanged.

## Ninth checkpoint: complete top-level draft, validation still in progress

The shared implementation now includes Frame::run/updateIngameUIDraft, initial
localization, hover HUD, world-label creation and performance overlay. There is
no original-update fallback. It is still research source, not a production hook.

A full composed run of the nine established tests passed. Subsequently, the new
performance test (240 cases), label creation (80 cases), and first-use/retry
localization (15 cases) each passed independently. The 1,440 existing-label cases
were rerun with distinct setting IDs and passed. Do not treat these separate
runs as a full integration pass on the latest source. implementation/GAPS.md is
the current source of remaining verification work.

Two concrete issues found while consolidating: pre-main setting-key globals need
distinct fixture IDs; and CEGUI's byte-widening/UTF-8 constructor overloads differ.
The original measures byte-widened label text but displays decoded UTF-8. The
Cyrillic creation test exposed and corrected the latter call in the draft.

Latest combined verification, 2026-10-05 20:45 UTC: all 12 shared-code tests pass
(15,543 cases). See results/recovered-all-v7.log. Production acceptance unchanged.
