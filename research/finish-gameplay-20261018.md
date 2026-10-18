# Gameplay recovery and handoff integration, 18 October 2026

Validated from main `a40beae3dceee956258f97a63e20279a9277360b` (PR135),
using original ELF SHA256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

## Accepted result

The integrated tree adds 147 game functions in nine original TUs. All 4,210
previously accepted addresses remain accepted; there are no unexpected additions.

| Source family | New functions | MATCH | Behavioral comparison |
| --- | ---: | ---: | ---: |
| Level | 69 | 18 | 51 |
| GenericModel / GameClient | 44 | 14 | 30 |
| Skill / SkillManager / SkillController | 31 | 11 | 20 |
| Quest / SoundBank / UnitResourceList | 3 | 0 | 3 |
| Total | 147 | 43 | 104 |

Global acceptance is **4,357 / 5,247** game functions: **2,821 MATCH + 1,536
behavioral**, covering 2,071,892 of 3,702,188 original game-code bytes. There are
890 functions remaining. Another 815 compiler-generated matches are outside
these totals.

Three previously matching Skill addresses (`0xc9d160`, `0xcd0d90`, `0xcd3440`)
now have behavioral acceptance; two previously behavioral addresses (`0xcd5260`,
`0xcd5460`) now MATCH. Eleven other accepted Skill bodies changed code generation
and retain completed comparison coverage. Thus the net MATCH increase is 42.

## Canonical acceptance

`python3 tools/decomp/check.py` passed **1,803 tests, 0 failed** in
1,623.253 seconds. Source/tool tree and comparison inputs were identical before
and after the run. Input digest:
`04ae79ea6687e2b7754f566e6ed94084bc7af8f21ac5d629a2986a5b7ee43902`.

The runner used `LANG=C.UTF-8`, empty `LC_ALL` and `TZ`, TU disassembly,
four comparison/build workers, six self-test workers, 60 shards and an
1,800-second per-shard timeout. The full run had no fixture filter.

Local evidence is retained under `build-decomp/finish-20261018/`:
`full-result.json`, `full-check.log`, `final-tree-before.json`,
`final-inputs-before.json`, `final-progress.json`, `validation.json` and
`integration.json`. The audit checks exact old/new accepted address sets,
candidate integration hashes and the final input manifest.

The initial full attempt stopped at compilation because a Level fixture header
still used its ignored-candidate relative Detour include. Canonical
`tests/Detour.h` fixes the relocation; the failed evidence remains under
`failed-include-*`. The successful full run above used the corrected header.
Two source integration adjustments only remove extra blank lines at EOF.

## Behavioral fixes and controls

- Level uses native `setEnabled` slot `0x40` when loading/activating room layouts.
  Separate virtual-slot observers and actual-body mutations reject the wrong
  `setVisible` operation. Its focused group has 64 tests / 5,632 completed pairs;
  all eight semantic negative controls detect differences without incomplete calls.
- Model/client has 34 normal fixtures / 6,264 completed pairs, plus two separate
  counterfactual controls. Existing menu-input regression contributes another
  1,536 completed pairs. Counterfactuals are not acceptance evidence.
- Skills has 46 focused tests, including 25 new fixtures / 9,600 pairs, and 24
  detected body mutations. The full run also includes the two unrelated fixtures
  omitted from the focused Skill filter. Orientation follows the original Node
  virtual operation rather than substituting derived orientation.
- Quest save compares 34 original-child cases, 27 explicitly synthetic collection
  cases and four selected-child composition cases. Its fixture gives the native
  root DataGroup ownership of an Ogre-allocated repository; a stack repository
  previously caused invalid teardown. The default-GUID mutant is detected.
- SoundBank playback compares 512 cases, including probability, attenuation,
  looping and channel policy; the untracked-channel mutant is detected.
- UnitResourceList loading compares 256 cases with real DataGroup operations;
  the overwrite-argument mutant is detected. Both controls complete normally.
- Graph loading keeps the filename wstring alive through point processing,
  matching native cleanup order. `graph-negative.log` records 56 differences in
  64 completed old-body comparisons and zero incomplete calls; the fixed body
  passes all 11 Graph tests. PR100's historical three Graph mismatches remain
  unexplained; this lifetime defect is not claimed as their cause.

## ABI boundaries and reserves

Typed Level, GenericModel, GameClient, Player and Skill fields, RenderableStates
and ActiveAnimation were checked with an actual pinned-compiler layout probe.
Thirty-eight retired TU ownership assignments were transferred to `opencode`.
Recovery used fresh prepare-only packets on a frozen common-header context.

Uninitialized SDK branches do not establish acceptance. Native Level destructor
bootstrap and full renderer/client initialization remain outside these fixtures.
No complete SkillEvent layout or SDK padding overlay was invented. Loot methods
`0x95ce70` / `0x95d0b0` await repair of the existing ResourceManager string-value
versus const-reference signature discrepancy. SpawnClassData `0xa7cf40` /
`0xa7e170` await verified private access. Headless PASS does not prove playable
windowed gameplay.

## Handoff and cleanup

The supplied handoff is a technical specification, without the unpublished
Wardrobe source/receipts. Its PR127/128 work is already in main. Merchant/Inventory
parent-owned detours are already in PR134 and JSON preparation handoff in PR135;
none is counted again. Its Runic Ogre layout warnings inform the reserved paths.

Cleanup removed 140 old remote and 18 old local branches. Unique tips are kept in
`refs/archive/branch-cleanup-20261018/` and the verified incremental
`stale-branches.bundle`; its prerequisites remain in repository history.
Auxiliary worktrees were detached at their original commits with files and
staged/untracked changes preserved. The old PR100 tree remains unmerged: its
useful Quest save change is transferred and freshly accepted here. Its head
`fdbd5a0cc714dee47e2a7087b0355945ea61fc7f` is additionally preserved in an archive
ref and verified `pr100-held.bundle` before retiring the held branch.

An ENOSPC interruption during preparation was resolved by hardlinking identical
ignored snapshot data. Paths and contents were preserved; no recovered source,
candidate, archive or worktree files were removed. Failed preparations were
rerun before recovery continued.
