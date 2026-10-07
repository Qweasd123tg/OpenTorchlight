# Integration of PC and dot work, 2026-10-07

## Inputs

- Main baseline: ae84cf63855833c0551d2c220278bb3db92f09c7
- PC branch bunny/character-inventory-pilot: 4c86f0be2a213ca163af207e11cb01d9779a85d8 (four commits)
- dot draft PR7 and stacked PR8: a8354105221686ab25a01b163162688b0ad28783
- Historical collision candidate: c436f77eaf3e390fe966137c0165a5f998856e47 (selective source reuse, not a wholesale merge)

The PC branch and dot stack merge without text conflicts. Shared Character declarations and the existing Merchant/Stash functions are nevertheless covered by the aggregate run.

## Collision scope

The historical branch was explicitly WIP. Its full file currently gives eight DIFF rows, including constructor aliases whose instructions match but EH/LSDA equivalence is unverified. Four functions were absent in that branch.

Only the currently machine-MATCH source definitions were copied into the integration. Recompiling this reduced TU produced 27 MATCH rows (including inline/library symbols), zero DIFF, and 11 MISSING. Row count is not the number of uniquely accepted game functions.

The following implemented bodies were left in the historical branch pending stronger validation: getMemoryUsage, optimize, the long scalar sphereCollision overload, the long scalar rayCollision overload, calculateFaceBounds, calculateNormals, and the constructor. No stubs replace them; unresolved original methods remain provided by the original ELF in the hybrid. The four already absent methods also remain unresolved. The old branch is retained.

## Integration fix

The new publication-definition unit tests hardcoded an existing /tmp/opencode parent directory. On a clean host all 19 tests in that class failed before exercising their assertions. They now use TemporaryDirectory's normal parent selection. Full tool suite: 362 tests run, 361 passed, one Java/Ghidra-dependent test skipped.

## Verification status

Final exact-tree check.py completed with exit 0: 110 headless tests, zero failures. Accepted: 941/5247 game functions, 134888 original bytes; 935 machine MATCH and six functions with executed comparison evidence. The previous main snapshot was 896 accepted functions. The selected collision source contributes 22 unique original game addresses (including distinct destructor entry points). A preliminary run also passed its 110 fixtures but was correctly rejected because source/test inputs changed while it ran; only the subsequent stable-tree run is acceptance evidence.

Original inputs were restored read-only and verified: ELF SHA-256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b, PAK SHA-256 8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8. Pinned GCC4.4.7 package hashes and OGRE archive hash were verified against toolchain.py. No model calls or GUI/gameplay execution were used for integration.
