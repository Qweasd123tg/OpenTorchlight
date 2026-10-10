# OpenTorchlight mass-pass-100 integration report — 2026-10-10

Local integration completed. The final gate returned success at 21:48 UTC: one full Stage suite passed all 460 tests, followed by unchanged Stage publication and verified root production-object/input identity. Remote PR creation, CI and main merge are not claimed in this report.

Final acceptance: **2,480 functions**, comprising **2,138 primary MATCH** and **342 behaviorally accepted functions**, covering **1,174,686 original bytes**. The previous 2,380 accepted functions are preserved; the exact new accepted-address difference is the package's 100 targets, adding 20,449 bytes.

## Provenance and intended scope

User-supplied archive: OpenTorchlight-mass-pass-100-20261010.zip, retained at attachments/36218be4-e31f-4e4a-8d2a-5892ad0a32fe/OpenTorchlight-mass-pass-100-20261010.zip.

- SHA256: 8ca4361688afefe124391301b9740fe60e26e7293f456e93ce2faac2eec61cf5
- Archive size: 909,446 bytes; 30 entries; total expanded bytes recorded in inventory: 10,360,838; inventory bad-entry list is empty.
- Original ELF identity: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
- Package scope: 100 distinct target addresses, covering 20,449 original bytes. Address-to-function, translation-unit and fixture mapping is in functions.csv; this report does not duplicate that list.
- Final authored overlay has 15 files: five source files, three headers and seven fixtures. Production sources and headers remain byte-for-byte identical to the reviewed supplied versions. Five fixtures contain separately authored quality repairs.

The integration baseline is the clean PR81 tree represented by recovery-runner/window-player-root.json: 2,380 accepted functions and 1,154,237 accepted bytes, with 453 tests. The package target addresses do not overlap already accepted addresses in this baseline. The verified final acceptance above is derived from the actual Stage evidence and publication-identity receipt, with the baseline accepted set preserved.

## Compatibility and stale supplied-report warning

All existing touched-file prehashes match the current baseline. Five source edits append function definitions without modifying old function bodies. The header changes add a matching CCinematic declaration, expose CHierarchy::getTypeNames, and correct CSkillParser::getSkillNames to static. Original ELF argument use independently confirms the latter: the list is passed in RDI and the parser is loaded from g_SkillParser. No old baseline source caller or definition of getSkillNames exists; no class field or virtual slot is added or reordered.

The supplied aggregate recovery report is stale relative to the current authoritative baseline: it omits 21 already accepted GameUI addresses. Examples include CGameUI::processInput at 0xab80c0 and CGameUI::update at 0xacbb40. Their full list is retained in evidence-comparison.json under package_missing_current. This is a warning against replacing the current root with the supplied aggregate report, not a finding that those 21 functions were deleted by this source patch. Integration must preserve the current accepted-address set and apply only the reviewed compatible changes.

Source/static clearance is recorded in source-review.json, bound to all 15 final file hashes. No confirmed source mismatch or malicious behavior remains unresolved in that stated scope. Independent negative-control test review has now passed separately in test-review.json. The completed baseline-preservation and publication-identity receipts provide the separate integrated clearance.

## Authored fixture repairs

1. EditorCoreMassTest.cpp: expected allocation and constructor exceptions are separately checked, with callCompleted left at zero for throwing calls. They are excluded from normal completed-pair coverage. Positive checks include expected fault, allocation/free calls and singleton cleanup; ordinary getCamera no longer catches unrelated exceptions as completed calls.
2. EditorMassLogicTimelineTest.cpp: timeline mock returns are independent of input amounts and use asymmetric 64-bit identifiers. Live-path counters prove those return paths actually ran and exact fixture coverage is checked.
3. EditorMassListsTest.cpp: GraphNames and SpawnClasses gain an exact 999-character result plus the four-byte terminator, filling the actual 4000-byte buffer without overflow. Each child checks returned-buffer identity, all key characters, comma and terminator; the full buffer remains captured.
4. InventoryMassTest.cpp: socket callbacks mutate count, capacity and backing pointers; inventory listeners shrink/grow their list, change capacity/backing pointers and change item stack state before the deletion decision. Independent positive witnesses check mutation count and receiver sequence. Additional finite-only fractional cases distinguish per-element ceilf accumulation from rounding the combined sum. Existing 504 baseline cases per operation remain.
5. EditorMassAnimationResourcesTest.cpp: a valid object with a descriptor returns a zero-length property, independent of the old null-object case. The test requires one property callback and empty shared-memory/string output.

EditorMassControlsTest.cpp and EditorMassValuesTest.cpp are unchanged from the supplied package. No production feature or safety hardening was added by these fixture repairs.

## Positive preflight actually observed

The saved Stage is build-decomp/attempts/tu-j8mekzsz. Its positive preflight receipt binds the authored manifest to the Stage's expected file state. The source reviewer separately rehashed all final overlay files and confirmed every hash against that receipt.

- Focused selftest process returned code 0.
- All seven new fixture groups passed, covering all 100 requested addresses.
- Coverage contains 41,293 normal completed original/replacement call pairs, zero differences and zero incomplete comparisons.
- Another 84 expected exception witnesses passed separately: 42 allocation failures and 42 constructor failures. They are not counted as normal completed calls.
- The package originally reported 41,352 pairs. The revised accounting is 41,352 minus 84 throwing calls plus 25 new normal witnesses = 41,293. The 25 additions are two map boundaries, 16 mutation cases, six finite rounding cases and one valid-object zero-property case.
- New per-address minima remain at least 28 normal comparisons. Graph/spawn have 29; revised singleton has 336; inventory operations 9/10/12 have 510 and operation 18 has 508; valid-object property wrapper has 505.

These are focused positive results only. The independent negative controls below establish rejection of the selected mutations. The final integrated Stage gate subsequently passed all 460 tests, and the preservation receipt verifies the previous accepted set.

## Completed negative controls and exact restoration

Independent test-review.json now records PASS for all seven final fixture files and the exact 15-file authored overlay. Ten replacement-only mutation controls were run and rejected:

- core-singleton-cleanup: expected_invariant_rejection
- core-undo-redo-nodes: completed_difference
- controls-rotation-argument: completed_difference
- lists-quest-delimiter: completed_difference
- timeline-return-elapsed: completed_difference
- timeline-swap-halves: completed_difference
- values-all-duplicates: completed_difference
- animation-post-reload-rtti: completed_difference
- inventory-round-total: completed_difference
- inventory-append-count: completed_difference

Nine controls produced completed original/replacement capture differences. The singleton-cleanup control produced an explicit expected-exception invariant rejection; it is not represented as a completed capture difference. An earlier runner-selector failure occurred before compilation/execution, was repaired, and is excluded from negative evidence. Fresh r2 receipts are the evidence used here.

After all mutations, the overlay hashes were restored exactly and a fresh seven-fixture positive run passed: 100 covered addresses, 41,293 normal completed pairs, zero differences, zero incomplete comparisons and 84 separately validated exception witnesses. Restored input/result/log hashes and individual negative-control hashes are bound in test-review.json and negative-results-mass100-r2/complete.json. This confirms the final source/fixture overlay, rather than any mutant, is the input for the final gate.

## Completed integration method: one full Stage suite plus publication identity

The user requested fewer redundant full test runs. One actual, unmodified Stage.validate full suite was executed on Stage tu-j8mekzsz. All 460 tests passed (453 baseline plus seven new fixtures), with zero failures. The final full-suite report also retains all 100 package target rows, 41,293 normal completed pairs, zero differences/incomplete comparisons, and 84 separately checked exception witnesses.

The same unchanged, validated Stage was passed to unmodified Stage.publish, which completed local publication. Its normal verifier confirmed exact identity of all 278 canonical production translation-unit objects. The validated Stage tree and published root tree mappings are equal; all 15 authored file hashes match the manifest. Source/test inputs, generated Stage fixtures and tools were preserved. A fresh root evidence.input_digest equals the tested Stage digest:

bda7c97da161a1d99ac9141978ba87c11684526fb86346c6d62ed2b694e51c87

Acceptance was derived from genuine Stage unit rows and fresh Stage comparison bindings. The accepted-address set equals the previous accepted set union exactly the 100 package targets. Result: 2,480 accepted, 2,138 MATCH, 342 behavioral, 1,174,686 bytes. Raw Stage units/report remain the execution evidence; canonical source-path mapping in derived acceptance is not a separate root execution.

single-full-gate-review.json independently cleared the driver design. stage-validation.json, local-publication.json, integration-acceptance.json and preservation.json now record actual successful execution, unchanged publication and linked evidence hashes. During final report preparation, their hash links, exact accepted-address union, totals, 460 individual PASS lines, 100 target coverage rows, all 1,064 published input-file hashes and all 15 authored hashes were independently checked. The 278-object identity is the result recorded by the unmodified publication verifier; the equality of its object mappings was independently checked without recompilation.

No second root headless/full-suite execution occurred, and no separately built root test blob was executed. The root validation claim is production source/object/input identity with the tested Stage, not independent root runtime testing. Environment, runtime, fixture, build or source changes invalidate reuse. A later change must not inherit this receipt without revalidation.

## Compiler and emitted helper observations

The target set has four primary MATCH rows and 96 DIFF rows. The 96 DIFF targets require executed comparison evidence; matching C++ source shape or a test registration alone is insufficient. All 100 targets, including the four MATCH targets, received positive differential coverage.

The four primary MATCH targets are:
- 0x731ec0: EditorGetCountOfLogicObjectsInLogicGroup(long long)
- 0x91b5b0: CInventory::getEquipmentCountOfGuid(long long)
- 0x91b680: CInventory::getEquipmentOfGuid(long long)
- 0x91ccd0: CInventory::getEffectValueMinusEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)

The emitted-definition proof records 117 new emitted rows: the 100 target rows plus 17 compiler/template/helper rows. These are not 117 newly recovered game functions. Of the extra rows, the matching TArrayList<wstring> destructor aliases share address 0x5f8e90, and wstring operator+ at 0x7017d0 is another helper MATCH; these addresses were already matched elsewhere in the baseline. Eleven __tcf compiler cleanup rows are DIFF. Three red-black-tree map insertion helpers newly appear as MATCH addresses 0x9263b0, 0x926460 and 0x926500; they are compiler/template observations, outside the requested 100-function count. Do not add them to the task's recovered-game count by inference.

CEditor::getSingleton retains compiler metadata reporting unverified EH LSDA equivalence and a size difference (original 151 bytes, candidate 129). Its executed normal comparisons and separately checked throwing/cleanup cases provide bounded behavioral evidence, not exact exception-table equivalence or a primary MATCH claim. GCC compatibility warnings in the build log do not themselves establish a failure; the recorded focused run succeeded.

The integration driver's emitted-map caching optimization has a separate receipt recording identical new-emitted evidence for all 117 rows. It is execution bookkeeping, not a source-recovery result.

## Preserved original unsafe semantics

This is 1:1 recovery. All 21 resource-list original guards were checked in disassembly. Some allow up to 1,999,999 characters with a two-byte copy; others allow up to 999,999 with a four-byte copy, then write a four-byte zero terminator. The actual shared destination is only 4000 bytes.

The reconstructed source intentionally retains that original contract. Memory-bounded output lengths are at most 1,998 characters for the two-byte-copy paths or 999 characters for the four-byte-copy paths. Intermediate overflowing lengths are deliberately excluded from executed fixtures. The oversized no-copy branch is tested. No memory-safety claim is made for these functions, and no silent change to their original guard behavior is proposed.

Other original quirks remain, including zero-extended 0xffffffff timeline sentinels, null-timeline forwarding in RemoveProperty under the original second-lookup condition, retained null redo nodes and TArrayList capacity-fallback behavior. Original callback sequencing, cached owners versus reread globals, and signed inventory slot bounds were checked in the static review.

## Proven limits and remote-publication status

Static review covered all source/header changes and fixture structure, with high-risk original-ASM checks. It is not a formal instruction-by-instruction proof of every path of all 100 functions. Mock collaborators establish selected argument, ordering and mutation behavior, not full real-game integration. Corrupt huge container counts and original unsafe overflow ranges remain outside the observed domain. Ten selected negative controls establish sensitivity to those mutations, not exhaustive equivalence.

The complete 460-test Stage run, unchanged local publication, exact accepted-address preservation, all 278 production-object identities and root input-digest equality have completed successfully. Root headless execution was intentionally not repeated; see the method above.

Remote draft PR creation, CI/review outcomes and main merge remain outside this report's verified scope. No PR number, remote publication or merged state is assumed. Record those separately from actual remote receipts.

## Exact final file hashes

Hashes below were re-read from both the authored overlay and published root, checked against authored-overlay-manifest.json and the final validated/published tree mappings. They describe the final validated inputs, not temporary negative-control mutations.

### Sources

- decomp/src/Editor.cpp: 335e545cbea4e7eeb442cbb68b051c06827e2ebe903986e8b3a41b4ee920646f
- decomp/src/EditorDLL.cpp: 645280b49019e1eba676b13c092485d243c76f3d1b1f5b0cc7d652825629bfca
- decomp/src/EditorScene.cpp: f72648f2e3140db2c004b338c289b0abb834dbe76c3f3a87f3418e5d1eb05438
- decomp/src/Inventory.cpp: 127acf4dbf13beee45c86a27ec8250c10e96f94e55f938eea399427b0f0af245
- decomp/src/ObjectControl3D.cpp: 1e165a4ce517bdeaed132e1f352714c65d8746b8b17d6537b12dd86210b0dc4e

### Headers

- decomp/include/Cinematic.h: 26a7136573a4e104588fcc10784f7a08f87f597ebbb93219e3ae024b5ac25aee
- decomp/include/Hierarchy.h: 8dd467d5a01daeebdddb7973145c616a5b5343254fdabfd9ccadf6444fe1354a
- decomp/include/SkillParser.h: 483cc53ace950fe63b9a36a570fcc34535cb7926b591c6fbf13f660796d298ee

### Fixtures

- decomp/hybrid/tests/EditorCoreMassTest.cpp: fa67e6359396ba0dae2684c7cdc46c498d3b287ff23363f347b9ede08d2753c7
- decomp/hybrid/tests/EditorMassAnimationResourcesTest.cpp: d2e6c0c627bcaf51905cb7ac0adc37a35463061ee67454479995eee0953f9a92
- decomp/hybrid/tests/EditorMassControlsTest.cpp: 2aad1a99152d0ab4578ea7eff87285b4a0a468d02451d7d22d11c525419c0734
- decomp/hybrid/tests/EditorMassListsTest.cpp: 19aadad9e172d1acb5945c52db632c62bfbfe787132a1bd2451b5effdfd9d94a
- decomp/hybrid/tests/EditorMassLogicTimelineTest.cpp: 51a1aa419b21392071a2cd3f1fe0d22c652a1e22ff91373044f856fc90713989
- decomp/hybrid/tests/EditorMassValuesTest.cpp: 79fd6abe3b8950f8f4eceeaddfd1f7926cd931534bb4c364c9ebfde7e5bf64e6
- decomp/hybrid/tests/InventoryMassTest.cpp: 6978de76a38d1e7ee64df00c8dd26e3396ab3b8c93e0d52d24aad3f874b867b8

## Evidence paths and receipt hashes

Evidence paths are workspace-relative audit locations; most are not tracked repository files. Raw logs and the complete function list are not duplicated here. The report is a bounded summary; full local receipts remain the detailed evidence.

- recovery-runner/mass-pass-100-review/inventory.json (SHA256 3d33f95076036df8f897a65ef431748518d390d51b16e980f76f265cec02fc14)
- recovery-runner/mass-pass-100-review/functions.csv (SHA256 3ffe2839ba8c0c20072b7ebd7fb8053a5e43615681dd77addcd162eeea9de03d)
- recovery-runner/mass-pass-100-review/file-comparison.json (SHA256 ca3d3c0267a37c2ece829d4a466d88d97fdafdb0d732a3e10b448a5aa0f2527b)
- recovery-runner/mass-pass-100-review/evidence-comparison.json (SHA256 b3e401009f5f4cf739bc1b71c4373afc7144d5667d93f0a3dada53321225d5bb)
- recovery-runner/mass-pass-100-review/authored-overlay-manifest.json (SHA256 26d000a3d9ce847a785e5511134b1d202d0c2a61311cfd9a9400d3b20081f75e)
- recovery-runner/mass-pass-100-review/source-review.json (SHA256 933f9d8e8c1f9f949ba8b60efd82c350415babb589191e13b60ba348c727c874)
- recovery-runner/mass-pass-100-review/integration-plan.json (SHA256 f54183d61ccb162ddef41f94e0b5b05f1cf7a6744d53d409c2e6872d28c24633)
- recovery-runner/mass-pass-100-review/integration-run/preflight-complete.json (SHA256 6b49fce119585294d4d8376dd46490fdd7a6142a5d8aed0a516cf6ed77e7f538)
- recovery-runner/mass-pass-100-review/integration-run/focused-selftest.json (SHA256 c29cd23bf732af94cfeac91cb8a788388e321b5a659f34c819470611ea79aca5)
- recovery-runner/mass-pass-100-review/integration-run/preflight-units.json (SHA256 611cd837760c9fddc1a16157adf207d876106f7bc73562fd4c81f5a036bef80a)
- recovery-runner/mass-pass-100-review/integration-run/required-definition-proof.json (SHA256 b13348741ac7dbc26a905fea0af0a512d3c47020961d12daf7dc9d872c9946e3)
- recovery-runner/mass-pass-100-review/integration-run/stage.json (SHA256 8e6a72470bdf013a8b296c4944adf2e3dff491e2b19f6e32ece6694148c85544)
- recovery-runner/mass-pass-100-review/emitted-map-optimization-receipt.json (SHA256 088e2df539484ee324428fc53406e96ed64c50fd0d4e132051708923be9b872a)
- recovery-runner/window-player-root.json (SHA256 c0455898a120583152f075905ad8d9a79f40e098816eaef388ed6aadcbb81fe6)
- recovery-runner/mass-pass-100-semantic-review/REVIEW.md (SHA256 8ff9320bd81db9f7acc85661729942279f8fef56f6be8a8ea81d2d10827b04d1)
- recovery-runner/mass-pass-100-semantic-review/list-guards.json (SHA256 a4f0e55a64aa7b88e6475983d820165642faea2102fbef8fb327575b2d0aaa53)
- recovery-runner/mass-pass-100-semantic-review/proposed/EXPECTATIONS.md (SHA256 a3498f8203286a6ec93c509396c7de29967f6562c6638b9f665a8a12117f3635)
- recovery-runner/mass-pass-100-semantic-review/proposed/MERGED-REVIEW.md (SHA256 9f3019984360e7357667cd98023ad521fc1a4f15cb0c46d82751ac152a00771d)
- recovery-runner/mass-pass-100-test-review/REVIEW.txt (SHA256 f51feddc55a8081b4bb3bebd6668aca8bcb2ab0b6d7ecf54fb48b0a00b6a933b)

Final Stage/publication/acceptance/preservation receipts are listed below. Remote PR/CI/merge receipts remain outside this report. No root headless-run receipt exists under the single-full-suite method.

### Completed control and method receipts added at this update

- recovery-runner/mass-pass-100-review/test-review.json (SHA256 420b3c9a984d9b43fe97bbb2ffbac550860bc90e0e794ea1adf48d38d11310a1)
- recovery-runner/mass-pass-100-review/single-full-gate-review.json (SHA256 b248126beb6de3857838ca937dbe07bc8b5e246e0e2efec30a8e84c8671b39e9)
- recovery-runner/mass-pass-100-test-review/negative-results-mass100-r2/complete.json (SHA256 d0441fff2315c92f6670f79e3472ba6defdc6ed0a8a6ded7c076fecad71d0699)
- recovery-runner/mass-pass-100-review/negative-controls/mass100-r2-restored-positive/inputs.json (SHA256 5acbe2367851252537d253feafda07beb41ebeb106de9dd9916d45893bcd476f)
- recovery-runner/mass-pass-100-review/negative-controls/mass100-r2-restored-positive/result.json (SHA256 b101d6a758083f12c644579faf6c34f77caa808c7457a46208b9bd4a141c3d70)
- recovery-runner/mass-pass-100-review/negative-controls/mass100-r2-restored-positive/selftest.log (SHA256 01a9a58842f805cc579ae73a135f9d62e2bd5ed6edaeb788f098d44e3abee6a9)

### Final successful integration receipts

- recovery-runner/mass-pass-100-review/integration-run/stage-validation.json (SHA256 5010393292c8133e7bb20f526594031b870e1a2a01acaaae6b9d75e54feb724a)
- recovery-runner/mass-pass-100-review/integration-run/local-publication.json (SHA256 cf6b551cc0ef76fd6c0f73c37adeb55df4ac491cf0d51fbd929aead395fd839a)
- recovery-runner/mass-pass-100-review/integration-run/integration-acceptance.json (SHA256 e15e4fb0d480306578d6e885abcabb4e53ef204edbe6112f570ebb8a09f6a3fc)
- recovery-runner/mass-pass-100-review/integration-run/preservation.json (SHA256 fad3ecac0b549ecf849149ea305e2a0e17f17874f44914dcf6f1f9acd04a99cd)
