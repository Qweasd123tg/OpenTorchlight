# CGameUI lifetime restoration

Base: PR89, commit `2df4ed173e9fffda1e26ff17bfa190c17bc6b131`.

## Restored behavior

Three unique original entries, 4,760 bytes total:

- CGameUI C1/C2, `0xaa6380`, 2,158 bytes: declaration-ordered real member construction, original singleton/key-map timing, ignored false create result, and member-only exception unwinding.
- CGameUI D1/D2, `0xa94240`, 2,584 bytes: five cursor releases, both event-list passes, reentrant vector reloads, owned dragged-item deletion, allocator-correct shell/node lifetimes, exact explicit cleanup order, and reverse automatic-member cleanup.
- CGameUI D0, `0xa94c60`, 18 bytes: exact MATCH; D1 followed by Ogre owner deallocation. Constructor/destructor aliases are counted once.

The typed layout preserves CGameUI size `0x1a08` and its untouched bytes. CKeyManager size/alignment `0xd18/8` is asserted before embedding; the GameUI layout and checked GameClient/ObjectControl3D/MenuManager boundaries, sizes, and alignments pass the pinned GCC 4.4.7 assertions. Existing call boundaries, original global redirections, vtable entries, and exception cleanup were reviewed. The unrelated potential keyEvent issue is outside this change.

## Strict preparation support

Two reviewed context-tool files add narrow, original-ELF/source-bound support for existing TArrayList<wstring> and TSafePointer<Character/Equipment> destructor templates. All 144 context unit tests pass. Fresh exact preparation succeeds; altered template bodies and incompatible type metadata fail closed. These tools were installed in an isolated baseline before Stage creation. No publication or evidence guard changed.

## Behavioral evidence

- Constructor: 32 completed pairs, nine independent poisoned-byte boundary snapshots, 72 separate expected-exception pairs, and 12 synthetic oracle negatives.
- D1 and D0: 208 completed pairs each, plus 58 separate expected-exception pairs, including interrupted second-pass shell deletion. Genuine constructed owners, reentrant changes, safe registrations, string lifetimes, and allocator categories are observed.
- Direct weak helper closures: TArrayList<wstring> `0x5f8e90`, 252 completed pairs; TSafePointer<CCharacter> `0x591b50` and TSafePointer<CEquipment> `0xacbc90`, 44 pairs each; 48 separate unregister-exception witnesses. These are supporting weak-template coverage, not additional strong accepted functions.
- Nine isolated source controls are rejected by completed differences with zero incomplete observations: three constructor ordering controls, four destructor ownership/order/allocator controls, and two direct-helper controls. Restored positives reproduce the exact focused input digest and blob hash.

The first full attempt passed its headless tests but was correctly rejected by the unchanged preservation guard for missing direct weak-helper evidence. The complete emitted-body audit identified exactly those three closures; dedicated fixtures were added, with all original candidate source/tool/fixture hashes unchanged, then the final tree was fully validated.

## Final validation

Unmodified Stage.validate passes all 637 tests and preserves all 2,694 prior accepted functions and all 2,159 prior exact matches. Exactly the three primary entries are added:

- 2,697 accepted functions
- 2,160 exact MATCH functions
- 537 behavioral functions
- 637 passing tests, including the original 627

Validated input digest: `a4c6454a0dce7a56a59ecbda2d5323a9cced9b97456b54a0059841b9b0091cb8`.

Final validation: 870.34 seconds. Build: 89.62 seconds. Headless shard execution: 722.64 seconds. Established resource limits were retained: eight shards, four workers/shared slots, two compiler slots, 1,800-second timeout. Sampled aggregate descendant RSS peaked at 892,212 KiB; largest child high-water RSS was 474,388 KiB. Aggregate RSS double-counts shared mappings and is sampled, not peak physical memory.

Full proof, rejected attempts, exact-source manifests, focused/control logs, and independent review are retained privately. The export consists of twelve source/header/fixture files and the two reviewed context-tool files; this report adds no runtime code.
