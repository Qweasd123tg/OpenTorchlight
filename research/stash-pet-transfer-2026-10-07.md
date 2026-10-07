# Stash pet-slot transfer from the accepted Merchant implementation

Snapshot: PR7 head b5c450c425fca65b4521f21eb093d1555c6af702, original ELF SHA-256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b. No new model-generated implementation was used for this transfer.

## Transfer evidence

The originals CMerchantMenu::setPetSlotIcon (0xb6ab50) and CStashMenu::setPetSlotIcon (0xbf7cc0) each contain 6229 machine bytes. Existing objdiff normalization produces 1057 instructions for each. They agree after changing eight Imageset member loads from +0x3440 to +0x3410. This is supporting evidence for reuse, not a proof of full equivalence: normalization and unwind/LSDA interpretation remain limitations.

The accepted Merchant implementation was specialized by changing its owner class and the member names corresponding to the same original offsets. The sole changed member displacement is the Imageset pointer. No copied data/assets or modifications to the original executable are included.

## Array declaration refinement

Cross-method accesses require the common main-slot Window-pointer block to begin at +0x1de8 with 145 entries. Its earlier partial declaration split it into 19 and 126 entries. Five pet-window blocks begin at +0x26f8, +0x2988, +0x2c18, +0x2ea8, and +0x3138 and each span 82 pointers. Stash createMenus initializes their indices19..81, so its previous sliced declarations were replaced with the full domains and adjusted source indices.

This changes the partial C++ model, not the physical layout. Pinned-compiler assertions verify these bases and the unchanged class sizes (Merchant0x3478, Stash0x3428). These assertions and access patterns do not establish every original member's source-level type.

## Validation

- Initial combined run: Stash pet-slot 12960 completed pairs with zero differences; accepted Merchant pet-slot 12960 pairs; both resource-backed createMenus 392 pairs each; all four tests passed.
- Six-index run: slots 0,1,18,19,60,81 with data indices 0,3,399,25,144,399 respectively; 12960 pairs per slot, 77760 total, zero differences or incomplete outcomes. An earlier 180-second whole-shard limit expired before completion; the complete rerun used 600 seconds and all six tests passed.
- Full check.py run with the exact candidate: 109 tests, zero failures. Isolated staged acceptance is 899/5247 and 132714 original bytes, up from PR7's 898/5247 and126485 bytes. The only newly accepted address is0xbf7cc0; none were removed. These are NOT main's totals.
- The self-contained research/check_stash_pet_transfer.py reproducer was exercised with --negative-control: five of six completed cases differ as intended. Run without that flag for the six-index positive matrix. Prerequisites are the regular pinned toolchain, generated types.json, and authorized original-game files.

The negative control changes all eight Stash Imageset receivers to a different member. It compiles; five of six bounded comparison cases detect the mismatch, with no incomplete comparisons. The unmodified candidate is used for all positive checks.

## Limits and integration

The tests execute both functions inside the original headless process before main, substituting bounded UI/equipment collaborators. They compare ordered calls and relevant observed state. They do not execute gameplay, render UI, establish universal equivalence, or establish exception-path/LSDA equivalence for setPetSlotIcon.

Indices below19 in the boundary test are synthetic array-domain checks, not a claim that createMenus populates those pet slots. The implementation is still machine DIFF unless a separate objdiff MATCH is reported.

This change is layered on draft PR7. Shared-header reconciliation with the user's PC work must finish before merging the stack. Main acceptance totals must not be inferred from this staged run.
