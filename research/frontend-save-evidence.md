# large-5: application flow and persistent campaign boundary

Pinned original Linux ELF in supplied research: SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
The ELF and pak.zip are not available in this execution environment. Existing
integration claims (59 tests) are historical, not re-executed here.

## Evidence before implementation

- `resource-derived` (supplied audit, not a new pak extraction):
  `research/ui-actions.json` records mainmenuframe.layout, charactercreate.layout,
  characterload.layout and their effective onClick commands and unified bounds.
  In characterload ScrollUp/ScrollDown earlier guiExitApplication bindings are
  superseded. A parser must honor the LAST property, not the first.
- `original-code` navigation evidence from Ghidra: CCharacterSaveState::save,
  CItemSaveState::save and CLevelState::save serialize separate character/item
  records and level/logic states. CLevelState::save calls the two record writers
  and CLogicNodeState::save. CGameClient::saveCharacter @0x58b5d0 collects the
  character and level states; performWarp @0x58d110 keeps the live player.
  These observations justify separate persistent records, NOT binary ABI/format
  compatibility or recovery of every original field.
- CGameStateController also broadcasts gameplay thresholds/help events. Its
  name alone does not establish the application's splash/main/pause enum.
  The new frontend is explicitly a portable state machine, not a recovered enum.

## Deliberate portable contract (prototype/inferred)

An OpenTorchlight-only versioned checkpoint, separate directory and extension;
no original .SVB import/export. Persist evaluated instances, vitals, PRNG states,
level identity/seed, entities and supported logic states. On load rebuild geometry
from unchanged external resources; never serialize pointers, mesh buffers or HITs.
Transient actions/paths are cancelled, independent AI cooldowns are preserved.
Save only at the post-loot/post-logic safe boundary. Pending requests must not be
silently discarded. Snapshot all visited floors supported by this runtime; no
claim about original timed floor-reset/quest/timeline rules.

Validate before applying: file version/size/CRC, counts, finite numeric values,
IDs, slot membership, state linkage, resource manifest and layout identity.
Write to a fresh temporary file, fsync, atomically replace, fsync directory on
POSIX. Never use a character name as a filesystem path. Corrupt/incompatible
slots remain visible with an error; never silently replace them with a new game.

UI: use runtime original XML bindings/geometry/images where the bounded loader
supports them; unsupported CEGUI widget rendering, bitmap labels and additional
save controls remain visibly prototype. No invented original font or texture.
Difficulty remains Normal because existing world graph selection supports Normal;
other settings must not be offered as implemented. Pet selection remains unavailable.

Tests must include fresh-process read, nondefault instance stats, dead entities,
spawned/picked items, timer/AI clocks, duplicate/invalid IDs, bad lengths/CRC,
failed write preserving old file, incompatible pak, and deterministic coverage.

## Interaction boundary before implementation

`original-code`: `CCharacter::inInteractionRange @0x8244a0` checks a current
interaction reference, horizontal distance minus both collision radii, and
three branch-specific thresholds. The exact thresholds at `0xfce4b8/bc/c0`
are NOT in the supplied data extract. `CTriggerUnit::interact @0x9095c0`
checks availability/player identity and optional quest/key requirements before
`trigger`. `CInteract::interactWithUnit @0x986ff0` is named in the symbol graph,
but its body is not exported. Full NPC services are therefore NOT established.

The new portable dispatcher factors the existing `Unit Trigger` click path and
adds explicit inspection of non-combat character entities. Radius 2.25 remains
an explicitly `prototype` caller policy, NOT a recovered interaction constant.
It must not make every invisible Warper clickable: that would bypass the existing
Unit Trigger/event graph and possible gates. Merchant/stash/quest actions without
handlers produce a visible unsupported-service notice, not invented rewards.
A generation/selection token prevents a queued click crossing levels/death;
state is rechecked on arrival. This is a partial dispatcher, not CInteract parity.

## New verification and unresolved boundaries

Post-integration evidence: the local original pak with
SHA-256 `8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`
contains ten `AlwaysOnTop` properties in `media/UI/characterload.layout`
(lines 218, 226, 234, 242, 250, 259, 265, 271, 277 and 283) whose XML
attributes are spelled lowercase `name` and `value`. The installed original
`lib64/libCEGUIBase.so.1`, SHA-256
`57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`,
uses case-sensitive attribute lookup. `GUILayout_xmlHandler` reads the literal
strings `Name` and `Value` and its property-end path returns without applying a
property when the pending name is empty (`original-code`, functions at
0xe32e0/0xe4e80/0xe3090 in that library). The bounded loader therefore ignores
these malformed lowercase properties instead of rejecting the whole layout or
treating XML attributes as case-insensitive.

Fresh GCC 14.2.0: 28/28 portable, 28/28 address/undefined sanitizer suite.
Native probes enable leak detection; Python-hosted Mesa GL probe disables leak
checking only for that process (Python/Mesa own process-global allocations).
`frontend_campaign_cycle`: three independent processes, 222/222/4 assertions,
authored Town-shaped/Main-shaped layout, real core mesh/unit parsing, navigation
and ActorMotion; not original Town or a complete desktop playthrough.
`gles_ui_headless`: four actual EGL/GLES pixel readbacks under Mesa llvmpipe,
authored PNG atlas plus runtime UI renderer; not fake GL stubs, but also not a
Wayland window, original skin/font or original game asset comparison.
The window gameplay section is type-checked using the existing window-omission
probe. The full desktop target is unavailable without Wayland/EGL/GLES headers.

An existing navigation limitation was observed while authoring the walking test:
a thin wall exactly between cell centers can evade cell blockage at radius .45
and cell size 1. The positive fixture places the wall on a checked center
(x=10.5), not the missed boundary (x=10). No navigation repair/parity is claimed;
the separate negative scenario is explicitly in NEXT_CHECKS.md.

Coverage is generated from all 17,023 defined T/t/W/w function addresses, not
only game methods. Aliases are deduplicated; the map includes library code.
64 addresses have manually reviewed bounded annotations. A default unseen row
means no reviewed annotation yet, not proof that its decompilation was never
looked at. 24 verified rows retain specified earlier comparison boundaries and
explicitly say that original ELF/resource runs were not repeated here. There
are zero closed rows. The three port-native rows have no invented original VA.
Callgraph score uses only resolved direct edges and cannot see all virtual calls;
it prioritizes further reading, not percentage completion or proof of semantics.
