# Small-function batch, 2026-10-15

The combined canonical check passed: **903 headless tests, zero failures**.
Acceptance is now **2979 / 5,247 game addresses**, comprising
2261 MATCH and 718 BEHAVIORAL. All 2,932 previously accepted
addresses remain accepted. The batch adds **47 MATCH game addresses**
covering 2248 original bytes; 2268 addresses remain unaccepted.

The source changes restore 14 ParticleEmitterWrapper property/position methods,
25 descriptor name lookups, the two originally empty editor update callbacks,
and CDynamicLine's destructor. The latter also emits its nondeleting/deleting
variants and four adjustment thunks, accounting for six original addresses.
Original empty methods are confirmed by their original return-only machine code.

The emitter's generated position-end fields had incorrectly forced 8-byte
alignment at +0x140. The original Vector3 begins at +0x13c; restoring it places
the dynamic-attribute pointers at +0x148, +0x150, +0x158 and +0x160. Four dynamic
getters return float pointers. The final full TU obtains exact MATCH for all
14 additions without replacing previous bodies.

The descriptor family uses the original bounded unsigned-index lookup and
wide-string copy. The game-state fallback returns entry 1; other restored
lookups return entry 0. Two generated signatures are corrected to static
std::wstring returns, as confirmed by hidden-result ABI and callback consumers.

Existing name_tables.py recovers 141 actual strings in 21 tables from original
static-initializer calls and ELF literals. Fourteen owner-only Names.h files
supply real static const std::wstring objects and are included solely by their
owning TU, after its previous includes. Six conflicting uninitialized byte-array
declarations are removed from GameVariables.h. Existing game bodies and compiler
destructor identities are preserved. Fourteen already-DIFF compiler initialization
helpers change to initialize the recovered data; these helpers receive no new
function-acceptance credit.

## Validation

The final check uses the pinned GCC 4.4.7/C++98 toolchain and original ELF.
Every new game address has MATCH in the final combined build. Previously accepted
functions have fresh final-object comparison bindings where required.
98 previous explicit source definitions in changed TUs are unchanged.
See validation.json, functions.json, objects.json, source-preservation.json,
tables.json and targeted-selftest-summary.txt.
The types export was refreshed after the final static MATCH inventory, before
the full headless check, so its MATCH-dependent input stamp remains current.
The first combined 902-test check found one fixture failure in missile descriptor
registration: the captured callback pointer was compared as a raw address after
GetDamageTypeStringByID became a MATCH replacement. The fixture now normalizes
only the original/linked aliases of this exact symbol. A regression test keeps
other callbacks, unknown addresses and null distinct. The five targeted identity
and registration tests passed before the final full rerun.

An earlier 26-address run was stopped before completion when the batch expanded;
no acceptance is claimed from that interrupted run.

This is headless, address-level acceptance. Windowed gameplay and a standalone
complete game were not evaluated.

## What a 500-function batch would contain

The base snapshot at 3ad959f has 2,315 unaccepted game addresses: 2,048 without
strong definitions and 267 implemented DIFFs. Its cumulative short-function
inventory is:

| Original size | Addresses | Original bytes |
| --- | ---: | ---: |
| <=96 bytes | 533 | 19,406 |
| <=128 bytes | 656 | 33,331 |
| <=256 bytes | 1,001 | 97,856 |

Ninety-six of the shortest entries are compiler thunks, tied to ordinary method
restoration. The <=96-byte group represents 0.85% of remaining original bytes.

A fresh read-only scan of 1,791 remaining addresses below 1,000 bytes produced
56 existing-generator hypotheses. Fifty belonged to opencode. The first combined
static trial accepted three C++ definitions, yielding eight game addresses;
44 hypotheses differed and three failed compilation (including two duplicate
ABI representatives). No rejected body was integrated.

The next useful scale is a queue of 500 candidates grouped by original TU,
shared header/data prerequisite and semantic family. Deduplicate source/ABI
representatives and exclude current accepted BEHAVIORAL as well as MATCH work.
Run compiler comparisons for the whole groups, retain actual MATCH closures,
and use one final canonical check for the assembled batch. A 500-entry queue
is measurable work to triage; it does not promise 500 newly accepted functions.
The existing deterministic generators and table recovery are reused here.

After this batch, opencode owns 1518 remaining candidate addresses:
358 at <=96 bytes, 468 at <=128 bytes and 758 at <=256 bytes.
A 500-candidate queue therefore fits within existing ownership when the size
range extends to 256 bytes. Other owners' TUs stay out of this queue; ownership
and current acceptance must be rechecked before preparing each new slice.

The same descriptor TUs still have 27 unimplemented string-to-ID callbacks;
13 directly reference the tables restored in this batch. They are navigation
candidates, requiring their own fresh preparation and ABI/ASM review.

The run also exposed a scheduling limitation: it
fell back to shard-index order because the profile key includes the complete
fixture/header digest and aggregate test-object identity. Per-object timing
hints could retain costs for unchanged fixtures across a source batch. This
is a scheduling idea only; it is not implemented or benchmarked, and it would
not change comparison evidence or acceptance inputs.
