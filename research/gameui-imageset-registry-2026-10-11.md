# CGameUI imageset registry restoration review

## Scope and current status

Restores three functions in `decomp/src/gameui.cpp`:

| Original address | Function | Original bytes | Acceptance route |
| --- | --- | ---: | --- |
| `0xa84740` | `CGameUI::addImageSet` | 289 | Behavioral comparison; DIFF |
| `0xa98460` | `CGameUI::getImageSetForIcon` | 456 | Behavioral comparison; DIFF |
| `0xa98630` | `CGameUI::getImageFromImageSet` | 626 | Behavioral comparison; DIFF |

Total: 1,371 original bytes. None of these functions is claimed as a byte-level MATCH.

**Final independent validation: PASS.** The corrected complete gate passed all **614/614 tests**, with the exact expected inventory and no duplicate or failed entries. All **2,680 previously accepted functions**, including all **2,156 prior MATCH functions**, are preserved. The exact accepted-set delta is the three addresses listed above. Total: **2,683 accepted = 2,156 MATCH + 527 behavioral**.

The first complete gate failed two existing consumer tests because the new lookup body was inlined across the original collaborator call boundary. A narrowly scoped noinline correction restored that boundary; the existing fixtures were unchanged. The corrected candidate then passed focused tests, all four negative controls, restored-positive validation, and the complete gate. Local integration and remote publication are tracked separately below.

## Original behavior checked

The original executable's SHA-256 is `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

- The imageset array uses offsets `0x458` (data), `0x460` (count), `0x464` (capacity), and `0x468` (growth). The existing layout assertion fixes the array at `0x458`.
- Insertion ignores null arguments; otherwise it appends through the original-style `TArrayList` growth/copy/release sequence, including observable allocation-failure state and reloads after allocation.
- Set lookup returns null for an empty array, the first matching imageset in array order, or the first imageset when no match exists. Indexing retains the container's capacity fallback.
- Image lookup returns null for an empty array or no successful image. It preserves the otherwise-unused outer UTF-8 String construction, per-iteration name conversion, first-hit order, null `getImage` continuation, count reload, and exception propagation.
- Image names use the pinned CEGUI case-sensitive, length-first UTF-32 map comparator. No case folding or alternate fallback was introduced.

## Focused evidence

`GameUIImagesetRegistryTest.cpp` compares original entry points with recovered functions using real CEGUI strings and image maps. Only array allocation/release and selected external `getImage` calls are detoured.

- Insertion: 45 completed normal comparisons.
- Set lookup: 291 completed normal comparisons.
- Image lookup: 317 completed normal comparisons.
- Total: **653 completed comparisons, zero differences, zero incomplete cases**.
- Separately verified expected unwinds: two allocation failures and thirteen `getImage` exceptions. These **15 unwinds are not included in normal completion counts**.

Cases include empty registries and maps, null insertion, growth and spare capacity, allocation-time state changes, missing and duplicate names, first-hit ordering, opposite-case-only keys, capacity fallback, 32/33-codepoint and longer names, equal-length long misses, two-byte/three-byte UTF-8, null image continuation, and state/guard preservation.

Four isolated deliberate source mutations were rejected: allowing null insertion, removing missing-set fallback, removing null-image continuation, and changing count during allocation-exception unwind. The first three failed by completed differences with zero incomplete reports; the fourth failed the separate unwind assertion. The restored positive build passed again with the same final source/input identity. Its blob contains the three registry tests; the corrected focused blob additionally contains the two consumer tests, so their blob hashes differ.

Focused input digest: `fe81ee630c4ce553758bd4744fa98fb32809a64198d785be699a98f39ee56c40`.
Corrected focused blob SHA-256: `8307a46af53008ba1b6e11a2498854c0e2cc9e5089220c9e6b3759d7c612296f`.

The corrected focused run additionally passed the unchanged skill-foldout fixture (3,168 comparisons) and skill-tooltip fixture (3,072 comparisons): **6,240 existing consumer comparisons, zero differences and zero incomplete cases**. All four final-revision negative controls were rejected as intended, their receipt/log hashes were independently verified, and restored-positive validation passed. Restored-positive blob SHA-256: `81e9589f4df5fcee13bdd40f3c604eeb336fac4db40f456578a2bfbe6fb3ff46`.

## Known original-library limitation

CEGUI 0.6.2 miscounts four-byte UTF-8 sequences in `String::encoded_size`: it advances three continuation bytes while subtracting only two from the remaining length. The original constructor at `0x899b18` confirms the same operation.

For `火🔥`, the constructor reports three UTF-32 codepoints while decoding only two, leaving the third word dependent on the destination's previous bytes. A separate witness invokes the original constructor on aligned storage prefilled with `0x11` and `0x22`; it confirms lengths 3/3 and retained words `0x11111111`/`0x22222222`. This witness is not counted as a GameUI comparison.

Supplementary-plane lookup equality therefore cannot be established by these deterministic fixtures. Normal multibyte lookup coverage uses BMP characters instead. Neither the pinned library nor GameUI behavior was changed to hide or repair this original defect.

## Reviewed file identities

| File | SHA-256 |
| --- | --- |
| `decomp/include/GameUI.h` | `e16ba514c613b222e28f7659738007d7945b5cc776a64f43f30761c2a5f8a5d2` |
| `decomp/src/gameui.cpp` | `12caef99abc09ac3f99ea31a1a7aad8554a7bc17fdce5d25bd293c0266590cac` |
| `decomp/hybrid/tests/GameUIImagesetRegistryTest.cpp` | `4dd5d7d25fa21fa844b68e8814025a63cf4928d22a60868ef55a797c45441ff6` |

Corrected patch SHA-256: `d33b79383231a91721d5c76c52209e02c7ea22930b0a4e9ef56f125d08f9483f`.

## Full gate and publication

The failed complete gate identified six lost out-of-line calls: original foldout calls at `0xa9ca37`, `0xa9d08e`, and `0xa9d81a`; original tooltip calls at `0xaaf137`, `0xab1a6b`, and `0xab318b`. The candidate instead contains direct imageset-array accesses in those callers. This bypasses their image collaborator spies: the tooltip trace first skips image event 32, and foldout reads beyond its boundary-only fake UI storage. Independent assembly review verified that a narrowly scoped noinline attribute restores all 14 baseline image-lookup call sites, including the six lost calls. Both existing consumer fixtures remain byte-for-byte unchanged. The file identities above describe the corrected candidate.

The complete receipt audit verified:

- Exactly 614 unique expected tests and 614 matching PASS entries, with zero FAIL entries.
- Exact accepted-set delta `{0xa84740, 0xa98460, 0xa98630}`, with no lost prior acceptances or prior MATCH functions.
- Each new function remains DIFF and carries executed-call-pair evidence bound to the verified original ELF, final object digest, fixture, and input digest.
- Full candidate tree hashes match the validated receipt. Only the three reviewed files differ from the baseline. The root tree remained unchanged at the pre-publication audit.
- Final input digest is `fe81ee630c4ce553758bd4744fa98fb32809a64198d785be699a98f39ee56c40`.

Checked local integration completed through the same validated Stage instance. Its publication receipt records exactly the three reviewed files, 2,683 accepted functions, 614 passing tests, 279 production objects, and the unchanged final input digest. The root tree was independently rechecked against every validated file hash after integration.

Remote draft PR publication is separate and is not yet established by this report.

Any remote publication must preserve these reviewed files, verify the remote commit, and review the checks for that exact commit. This report does not claim remote publication, merging, or live-game playability.
