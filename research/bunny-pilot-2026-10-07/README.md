# Merchant pet-slot pilot

Target: `CMerchantMenu::setPetSlotIcon(CEquipment*, int, int)`, original address `0xb6ab50`, 6229 machine bytes. This patch adds one method in its original TU, partial class declarations and a bounded original-process differential fixture.

## Provenance and supervision

Space Bunny Free produced the initial method and header through OpenCode file/tool turns. The first chat-like tools-disabled attempt exhausted a 32000-token generation without producing code. The useful agent pass took about 864 seconds, its compiler-feedback continuation 496 seconds, and a separate header pass 330 seconds. These are model-run durations, not total engineering time or a measured whole-project speedup.

The supervisor provided real CEGUI 0.6.2 headers, compiler errors and assembly evidence. The model corrected invented SDK APIs and reversed parent/child calls. Supervisor corrections then addressed:
- placement of `offsetof` probes after class completion;
- `Window+0x3e2` is mouse pass-through, not rise-on-click;
- total socket count at `Equipment+0x3e0` differs from inserted-item count at `+0x3f0`;
- X coordinates undergo zero-extension from 32 bits before reuse;
- window pointers must be reloaded across collaborator calls, as in the original;
- missing primary vtable slot 19 (`onClick`) and incorrect assumptions in header probes.

This is assisted reconstruction, not an unreviewed autonomous model success.

## Validation

Against original ELF SHA256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`, pinned GCC4.4.7 and original runtime/resources:

- `check.py` exits zero, 104 headless tests and no failures
- 181 tool tests run: 180 passed, one Java/Ghidra check skipped
- registered original/replacement receipt: `0xb6ab50`, 12960 completed comparisons, zero different/incomplete
- acceptance changes from 895 to 896 functions and from 53036 to 59265 machine bytes; the only new accepted address is `0xb6ab50`, none removed
- normalized machine-code status remains DIFF, not MATCH
- GCC class dumps agree with original primary/secondary vtable slot order, sizes `CMerchantMenu=0x3478`, `CSubMenu=0x10`, and used field offsets
- exporting types leaves the trusted-prototype total unchanged: new partial-header return hypotheses are explicitly quarantined with the existing promotion marker

The normal fixture covers socket and inserted-item counts 0/1/2, capacity fallback, identification, six canEquip/isMagical/ISA outcomes, stack-window absence/counts 0/1/2/37, positive and negative fractional coordinates, existing/created/missing icons, and a createIcon collaborator changing the slot window. It records helper identities, arguments, call order and selected final state. It uses equal bounded UI spies on both sides; it does not render the full UI or start gameplay.

Scratch negative controls exposed 9/12 initial semantic mismatches, 2160/3240 signed-X mismatches and 108/108 stale-window mismatches before their corrections. An additional scratch fixture exercised 324 injected-exception cases with matching observed traces/state; these are not counted as normally completed coverage receipts and do not constitute a universal exception/allocation proof.

## Limits

Partial header field names and array extents beyond this method's established accesses are still reconstruction hypotheses. Unused virtual return declarations are ABI-compatible hypotheses, not uniquely established source types; the export trust guard is intentional. Other methods/constructors are declarations only and remain original runtime code. Arbitrary callbacks, every float/NaN/Inf boundary, allocator behavior and complete GUI/resource effects are not exhaustively established. No game binary/assets are included.
