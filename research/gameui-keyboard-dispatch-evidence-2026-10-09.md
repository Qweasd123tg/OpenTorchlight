# GameUI keyboard dispatch restoration

Restored CGameUI::handleKeyPresses at 0xab4f80 (4341 original bytes), in the
existing gameui.cpp TU. The pinned GCC candidate is DIFF, not byte-MATCH.
Acceptance uses executed original/candidate differential observations.

## Recovered paths

Resource-manager early exit; repeated master/settings queries for console keys;
console capture and visibility gate; inventory, weapon-set, skill, journal, quest,
stats and pet toggles; skill swap and actual-parent foldout detach; automap pause
restriction and the original +5/-5 zoom; seed/depth/room clipboard diagnostics;
modifier-gated timestamped screenshot; down-before-up skill cycling and sound.
Pointers are reread across calls where the original does so, including the player
after the sound callback. The room label retains the original UTFString roundtrip.
The screenshot window is captured before path callbacks, and the configured
folder reference is fetched before GetAppDataPath.

Declarations and return types were grounded in original callers/callees before
strict llm_loop --prepare-only completed with no blocked or preexisting target.
Six local non-owning view offsets are compile-time checked. These views do not
construct engine objects or claim a complete class layout.

## Executed evidence

256 completed original/candidate comparisons, zero differences or incomplete
observations. Inputs exercise individual keys and combined masks, console hold
settings (negative/zero/positive), visible/toggled console, null resource/level/
inventory/render-window cases, weapon presence and menu visibility, all three
queued toggle flags, pause, parent presence, missing/present room, ordinary and
Unicode/non-BMP room names, signed seed/depth extremes, screenshot modifiers,
changed singleton instances and a sound callback replacing the player.

The fixture records collaborator identity, order and arguments, clipboard text,
screenshot prefix/suffix, full GameUI bytes and resulting flags. Clipboard,
screenshot, filesystem and engine services are controlled collaborators: no real
clipboard update, screenshot, directory creation, UI or audio occurs. Existing
key-helper bodies are stubbed consistently on both sides; this does not claim
those helpers or a running interactive game have been validated here.

Twelve separately compiled intentional defects were all rejected by completed
comparisons: wrong inventory-flag reset, omitted journal, wrong zoom sign/amount,
wrong down/up cycle direction, wrong sound index, wrong screenshot suffix,
wrong diagnostic label, wrong captured slot, missing pause guard, missing foldout
detach. After these negative controls the unmodified candidate passed again.

These are bounded valid-input observations, not exhaustive exception/allocator or
world-state equivalence. In particular callback replacement is sampled, not
proved for arbitrary hostile callbacks.

## Aggregate gate

Final current-tree check.py: 200 tests, zero failures. All 1341 prior accepted
addresses preserved; exactly 0xab4f80 added. Total 1342/5247 accepted functions,
980897 original bytes, comprising 1268 byte-MATCH and 74 behavioral acceptances.
No comparator, acceptance threshold, optimization flags or pinned toolchain changes.
The separately supplied pass-8 overlay is not included in this commit or count.
