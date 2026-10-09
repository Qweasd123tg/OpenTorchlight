# CGameUI::processIngameInput recovery, 2026-10-09

Status: behaviorally accepted after full strict Stage validation and an independent root check. Remote publication is recorded in the pull request.

## Identity

- ELF SHA-256: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- Original address: `0xab6080`, symbol `_ZN7CGameUI18processIngameInputEPvfb`, 8247 bytes.
- GCC 4.4.7-3.el6, original project flags. Candidate: 8278 bytes, normalized DIFF, no unknown references. Static EH LSDA equivalence remains unverified.
- Production TU remains `decomp/src/gameui.cpp`. Private phase helpers are always-inlined into the entry; the public entry is not flattened, so other restored GameUI methods are not inadvertently inlined.
- Existing root baseline is PR #11 head `8cba8d952872a5aa550b0471d20b0cb44478a80a`. The checked delta was published transactionally into the root on branch `dot/gameui-input-20261009`, based on merged PR #11 commit `3933882592c3d41ddbc446a0f14ab3948b51b876`.

## Preserved behavior

Input capture, mouse/time injection and cursor positioning retain callback order. Early exits distinguish missing player from disabled input: a missing player does not clear consume-next, while both paths reset transient click slots.

Player lifecycle handling retains the repeated virtual enabled checks. Key gating reads cinematic dropdown `UI+0x540`, not modal `UI+0x548`; an initial candidate error at that field was corrected against original instruction `ab68f7` before differential validation.

Click precedence and ownership are preserved across inventory, enchant, combine, merchant, stash and pet menus. Pending right-click promotion does not retroactively consume the frame. Service overlap can preserve an earlier item slot while replacing the owner and menu. Player and pet quick-use/equip paths have different consumption and error-sound behavior.

Failed swaps return replaced equipment to its owner or drop it into the level, preserving first/second replacement order and player/pet sound locations. A quest item dragged into the world is returned instead of dropped. Target cancellation retains weak-pointer removal order and the original right-click versus world-left-click selected-skill distinction.

Every fishing, dropdown and submenu input callback is dispatched even after a prior rejection. Vector bounds are reread during traversal, including callback-induced growth and clearing. Dropdown results and cinematic status consume the original low byte.

Equipment hover priority and service-owner/pet fallback follow the original. The comparison tooltip path intentionally preserves the unusual case where only the second comparison exists: the third tooltip is neither refreshed nor removed. HUD inventory GUID lookup returns a `CEquipmentRef*`, then accesses its equipment at `+0x10`; the old void declaration did not describe that ABI.

Twelve independently tested function keys preserve right/left mapping, foldout reparenting, eligibility flags, the `-999` empty-left-skill sentinel, missing-manager/skill behavior and suppression of ordinary activation by hovered skills.

## Differential evidence

Focused tests use the standard headless hybrid loader, original executable and controlled collaborators. No windowed game execution is used. These tests do not require the missing resource archive; that does not replace the full resource-backed acceptance gate.

Latest passing matrix:

- 600 control scenarios, each run for two consecutive frames in separate original/candidate children. Ordered collaborator traces, return values and relevant resulting state are compared.
- 96 early-exit scenarios compare the return value and every byte of the complete 0x1a08 UI object.
- 14 expected-exception scenarios verify propagation from both by-value wstring paths and compare the surviving source string's COW reference count after unwinding. These are supplemental exception observations, explicitly not reported as normally completed calls.
- Frame-time inputs include signed zero, finite positive/negative values, infinities and a payload NaN.
- All three focused fixtures pass. Identical crashes or missing reports are not accepted.

Twelve negative controls were independently compiled and executed against the earlier 512-two-frame/96-early-exit matrix (a retained subset of the latest cases). Every control failed through a completed original/candidate difference, with zero incomplete observations:

1. Wrong null-player return.
2. Omitted transient slot reset.
3. Ignored capture consumption.
4. Modal substituted for cinematic key gating.
5. Incorrect pending-right consumption.
6. Premature dispatch short-circuit.
7. Omitted item use.
8. Omitted drop after failed pickup.
9. Incorrect third-tooltip refresh with no first comparison.
10. Wrong left/right function-key mapping.
11. Wrong empty-left-skill sentinel.
12. Mouse-coordinate read moved across the scaling callback.

The source body used by those controls is unchanged in the latest matrix; later fixture additions cover dead-player drag cleanup, drag cancellation, click-priority overlaps, unparented foldout mapping and independently invalid eligibility flags.

## Full acceptance

The original resource archive was restored and verified: 357313431 bytes, SHA-256 `8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`. Strict Stage validation passed all 177 headless tests. Transactional publication verified that the root rebuilt the same production object identities; an independent root `python3 tools/decomp/check.py` then passed all 177 tests again.

Accepted game functions: **1213 / 5247**, representing **853423 original bytes**. This is 1170 normalized MATCH plus 43 behavioral acceptances. The large-function recovery series totals 27 functions. The additional weak helper matches are not counted as extra game functions.

The restored historical per-shard timeout was 1800 seconds, with 60 shards and at most four active selftest jobs. No gates, thresholds or runtime tests were removed or relaxed. No windowed game was launched, and this is not a standalone-game execution claim. No pass6/pass7 comparator or candidate code was included.

## Integration checkpoint at 10:24 UTC

A fresh Stage based directly on the real root contains exactly the 16 intended source/header/test changes. Whole-tree static comparison preserves all 2488 previously matched original addresses, with no regressions and no unknown references. Three additional weak helper matches are TSafePointer<CCharacter>::setObject (0x591af0), CItem::isUseable (0xacbbe0), and TSafePointer<CEquipment>::setObject (0xacbc30); they are not new accepted game-function counts.

The latest three focused fixtures also pass when linked with the complete production source tree (rather than only gameui.cpp). The Stage's source/test/tool hashes were identical before and after that run. That earlier filtered integration observation was followed by the two successful full-suite gates described above.
