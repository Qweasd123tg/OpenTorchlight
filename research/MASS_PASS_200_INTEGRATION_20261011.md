# OpenTorchlight incremental 200 function integration review

## Status

**Full validation and local integration publication passed.** The final accepted set is exactly the fresh 2,480-function baseline plus the 200 requested functions, with no lost addresses. All 611 registered tests passed. Independent receipt review confirmed the accepted sets, MATCH preservation, test inventory, and published tree identity. Updated 2026-10-11 UTC.

The integration uses pinned main `9c3ef9811330ee7f78865e87672bc27df1793db5`, the incremental patch only, and fixture-only evidence repairs. It preserves the previously repaired fixtures. The original repository and remote repository are outside this report's publication scope. Publication was performed in a separate local integration tree.

## Provenance and scope

- Archive: `OpenTorchlight-mass-pass-200-plus-100-20261010(1).zip`, 1,432,446 bytes; SHA-256 `8379b35d624f3596c9b9c3ace62104bc3c3420badb21107e471449191aeba981`.
- Incremental patch: `new-200.patch`; SHA-256 `39d47e5f04d5fd64b3c8d563827e5f673baf42d13c70c809cc8bb5cf6a14736d`.
- The original incremental overlay has 88 files: 24 production C++ sources, 28 headers, and 36 fixture sources. The reviewed overlay has 89 files after adding `ObservedWitness.h` and repairing five of the new fixtures. Production sources and headers were not changed by the evidence repairs.
- The full archive overlay was rejected as an integration route because it would overwrite five earlier repaired fixtures: EditorCoreMassTest, EditorMassAnimationResourcesTest, EditorMassListsTest, EditorMassLogicTimelineTest, and InventoryMassTest.
- There are 200 unique requested function addresses and 100 distinct carried addresses. Only the incremental 200 are new integration targets. They represent 93,343 original bytes across 44 translation units. The final build independently confirms 16 new primary MATCH and 184 new behavioral acceptances.
- Original ELF SHA-256 independently reread: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- Fresh baseline: 2,480 accepted functions, comprising 2,138 primary MATCH and 342 behavioral functions. The driver verifies that all 342 behavioral addresses are present in the ordinary `acceptance.prior_compared` guard set before constructing the executable Stage.

The initial package assessment preceded asset recovery and the fresh baseline run. This report supersedes its earlier pending statuses.

## Exception accounting repairs

Caught dependency exceptions are no longer labeled as normally completed primary calls. Normal completion is set only after the selected primary function returns. Expected exceptions require an actual caught type/value-derived terminal tag, a valid clean report, the exact original/replacement identity pair, `callStarted=1`, `callCompleted=0`, and equal captured effects. They are counted separately from normal coverage.

| Fixture scope | Normal pairs | Expected exception witnesses |
| --- | ---: | ---: |
| Collision avoider constructor | 192 | 128 |
| Eight menu constructors, each | 64 | 128 |
| Editor camera shake | 792 | 72 |
| Menu double click | 1,324 | 116 |
| Menu click | 1,400 | 40 |
| FileSystem reload | 420 | 1 |

The supplied fixtures mislabeled 1,380 exceptional pairs as normal returns. The original FileSystem constructor exception was unreachable because its seed predicates were correlated. The repair adds an explicit seed-1 exception case, preserving all 420 prior normal cases. Total observed exception witnesses are therefore 1,381.

The helper also rejects eight distinct replacement-report corruptions per exception-bearing primary function: false completion, missing invocation, wrong target, invalid report, invalid capture issue, wrong fault tag, changed captured effect, and empty capture. These are bookkeeping negative controls, separate from behavioral source mutants.

## Independently verified preflight

The focused build ran all 151 newly registered tests plus 12 registrations from nine affected old smoke-fixture files: **163 of 163 passed**. Direct recomputation from `focused.log` establishes:

- 191 requested addresses with normal original/replacement comparisons
- 115,721 normally completed pairs
- Zero differences and zero incomplete observations
- 1,381 separately checked expected-exception witnesses
- 104 rejected report-corruption controls

The nine requested addresses without behavioral comparisons are covered by final MATCH evidence. Focused behavioral coverage was not substituted for that final check.

The independent reviewer checked the complete selected/observed registration inventory, the log and compiled blob/loader hashes, the 89-file approved overlay against the active Stage, and manifest links in the focused, negative-control, and restoration receipts.

## Behavioral negative controls and restoration

Three isolated replacement-only source mutants were built and run. Each failed through a captured behavioral difference, with both child statuses clean and zero incomplete observations:

1. Collision radius changed from 1.0 to 2.0: rejected at case 0, normal-pair difference; first differing capture byte 60.
2. Collision constructor changed its flag during radius-setter exception unwinding: rejected at case 2, exception-pair difference; first differing capture byte 356.
3. FileSystem constructor-failure path incorrectly set the initialized flag: rejected at case 420, exception-pair difference.

All mutant source hashes were restored exactly. The final Stage was never mutated by these controls. Its two targeted restoration tests passed. Each mutant's result/log/blob/loader hash and isolation from the final Stage were independently checked.

## Original unsafe behavior and limits of equivalence

These are restoration-fidelity limitations, not evidence that the new source invented the unsafe behavior. Read-only disassembly of the pinned original ELF independently confirms the following operations on the 4,000-byte `sEditorTmpMemory` buffer:

- `EditorPollObjects`, original start `0x730c60`: the comparison at `0x730c9d` permits exactly 500 entries (`cmp 0x1f4`, followed by `ja` at `0x730ca8`). The sentinel write at `0x730ce9` then writes eight bytes at offset 4,000. The fixture covers 499 and 501, but intentionally does not execute the overflowing 500-entry case.
- `EditorGetDebugOutput`, original start `0x731cc0`: comparison at `0x731d33` permits up to 999,999 wide characters. The code multiplies the count by four and calls `memcpy` at `0x731d48`, then writes a four-byte terminator at `0x731d54`. A count of 1,000 already places the terminator outside the declared buffer.
- `EditorGetObjectSnap`, original start `0x722fc0`: comparison at `0x72305e` likewise permits up to 999,999 floats. The copy at `0x72307b` and terminator at `0x723080` have the same bound problem.

The fixtures use bounded safe domains and some no-copy guard cases. They do not establish memory safety for arbitrary input sizes. Silently changing these production mechanics would alter the original behavior and is outside this faithful-restoration integration. The original disassembly is preserved at `independent-review/original-editor-thresholds.txt`.

## Final acceptance and preservation

Independent recomputation from the final receipts establishes:

- Accepted addresses: **2,680**, exactly the fresh baseline set of 2,480 union the 200 requested addresses; the sets are disjoint and there are no missing or extra acceptances.
- Accepted original bytes: **1,268,029**.
- Primary MATCH: **2,156**, up from 2,138. Every prior primary MATCH remains MATCH.
- Behavioral acceptances: **524**. All 592 stored comparison bindings, including supplementary comparisons for MATCH functions, agree with positive final-log coverage, the final object digest, the validated input digest, and the original ELF hash.
- Requested 200: **16 MATCH plus 184 behavioral**.
- Actual primary MATCH gain is **18**: the 16 new matches plus two already accepted behavioral functions promoted to MATCH: `0x91b7a0`, `CInventory::forceRecalculationOfEquipmentStats()`, and `0x923730`, `CInventory::getEquipmentsOfUnitType(...)`.
- The full log contains exactly the expected **611 PASS registrations**, zero failures, and no missing or duplicate registrations.

Raw comparison rows must not be confused with distinct accepted game functions. Total MATCH rows increased from 7,221 to 7,303. The final rows include 4,879 compiler/helper rows: 820 compiler rows and 4,059 inline/template rows (568 distinct inline/template addresses). The prior helper/compiler total was 4,819, including 3,999 inline/template rows (564 distinct addresses). Primary aliases also produce repeated rows. None of those helper or alias row gains is an additional accepted game function.

## Publication identity

The reviewed coordinator invokes the ordinary `Stage.validate()` and then `Stage.publish()` on the same in-memory instance, without replacement coverage providers, baseline overrides, or altered preservation checks. The successful publication receipt identifies the same tested Stage and the separate local integration tree.

The independently checked current published integration tree and Stage tree are identical to the validated tree. The published delta is exactly the approved **89 files**. The **279-production-object** identity map agrees with the final comparison units, and the generated-fixture hashes agree with the files used for the complete test inventory. `Stage.publish()` includes its standard locked root-path object verification before committing publication, rejecting unknown or path-sensitive object mismatches.

The validated and published input digest is `df6bea6b8d32c572333ad3661f7ae84942c23677deae2ff6d3b90144741c3eab`. It agrees across acceptance, preservation, validated identity, and publication receipts. The separate root-input reread in `root-input-identity.json` also matches this digest. Root production-object equality is established by the unmodified publication API verification; no second root runtime execution or independently repeated root compilation is claimed.

This is local integration publication, not a claim that a remote pull request has been created or merged.

## Durable evidence locations

Artifact names below identify files in the retained evidence bundle. Raw receipts remain in that bundle and are not part of the source change.

- `candidate-receipt.json`: original incremental compatibility and file hashes
- `repaired-overlay-hashes.json` and `manifest.json`: reviewed 89-file overlay
- `baseline-provenance.json`: fresh baseline and actual behavioral guard addresses
- `focused.json`, `focused.log`, `focused-metrics.json`, `focused-coverage.json`
- `negative-controls.json` and `negative/`: mutant definitions and results
- `restoration.json`, `restored-positive.json`, `restored-positive.log`
- `stage.json`: active Stage and integration root identity
- `driver.py`: reviewed coordinator using unmodified repository APIs
- `independent-review/original-editor-thresholds.txt`: original ELF disassembly

The baseline source receipt is `baseline-completed-progress.json`. Final receipts are `publication.json`, `preservation.json`, `acceptance.json`, `final-stage-identity.json`, `final-stage-report.log`, `final-stage-units.json`, and `baseline-units.json`. The independent recomputation is recorded in `independent-review/final-receipt-audit.json`.

## Receipt integrity hashes

The following SHA-256 values pin the evidence reviewed for this report.

- `manifest.json`: `6ca8f2d7fd6f9dc5a147afe0e491c3ce3fa6da356543a60911556b9e05eccacf`
- `baseline-provenance.json`: `7f145c7b5c6e511650cc6e5656a43251675e3fc9b2d27f03126a97a7f0e14c77`
- `focused.json`: `974e0c2e500e8632489368168b6c0e60ff54eb637b481a75f5be68e48ce44e35`
- `negative-controls.json`: `f19967ef611f326bfa9a2e533ca3cd08d72f4bb36f0dd085e8e605709f855e69`
- `restoration.json`: `caed7d5a733e712bca5e383e94a8e7e3c3396bdffbea8687ff61db050560a9d6`
- `acceptance.json`: `c9fb6aa6dc508a238566ed30c164df35b8911341e2c03d4463531d10f61dc9f7`
- `publication.json`: `8fe90a9275c7a01308bb75e2c8ed9677e37e81166c977909cf01b7bbe68ee2ee`
- `preservation.json`: `d9b2ff4559b6b7d9b94cef95d006e60d798cb4e16ad3804e23e930f3c376b569`
- `final-stage-identity.json`: `dd77bb4e74a3a5dc743082f4a15f0ac41591f6d12198fae3a389a06a19b786fc`
- `final-stage-report.log`: `53d3a6dbd7ba8f9b9ae4264c5f746a9b7491d5013a59038ef45b199d9d2d31bd`
- `root-input-identity.json`: `a020884e65b98895dfe33e2c3d27c4d1bbd01c6231a698d2d9a3251bb5efe3be`
- `independent-review/final-receipt-audit.json`: `7631b65b1b78dbeae706c967dee2098aab6593b81973b6f849d2ce230b4c799b`
- `independent-review/original-editor-thresholds.txt`: `8df69d93fffd4d8be99576ab65b0ff18e72599428ecc862efd28d3d2ac24648e`
- `driver.py`: `6e93f65fe414e6b1fb4f3b6f188c1d3f1bd2ec9d69f5aa05e081baf37c9cba4b`
