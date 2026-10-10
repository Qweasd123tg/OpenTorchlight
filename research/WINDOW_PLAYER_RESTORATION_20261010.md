# Window mapping and player rebinding restoration

Date: 2026-10-10. Status: final isolated Stage validation, local publication, and independent full root check passed. This report records local validation; it does not claim a remote merge or assign a PR number.

## Accepted scope

| Original address | Function | Original bytes | Acceptance |
| --- | --- | ---: | --- |
| 0xa97e00 | CGameUI::mapEventHandlers(CEGUI::Window*) | 732 | Behavioral; object DIFF |
| 0xa980e0 | CGameUI::mapToFunctions(CEGUI::Window*) | 884 | Behavioral; object DIFF |
| 0xa9b420 | CGameUI::setPlayer(CCharacter*) | 1593 | Behavioral; object DIFF |

Net gain: three game functions and 3,209 original bytes. No target is claimed as MATCH. Baseline accepted functions 2,377 → 2,380; MATCH remains 2,134; behavioral acceptance 243 → 246. Accepted original bytes 1,151,028 → 1,154,237 of 3,702,188; game-function denominator remains 5,247.

Verified upstream baseline: `d5c1071dada56c15d9ae1f98d71a5bfa8cf79169`, tree `8fd2692d34cceda4a6b4a4673a2a6dcde7d3118a`. Clean local starting HEAD: `473f6cdb4b8befb3c5e80c888eab3826544d0f7d`. Combined Stage: `tu-3lhkyye6`. Original ELF SHA256: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

The validated delta contains one production source, two headers, and three fixtures, listed below. Tools were not changed. The source prefix is preserved; combined object review retains all 190 previously emitted gameui rows and the individual target code digests. The only changed production translation-unit object is `decomp/src/gameui.cpp`; all other production-unit object digests are preserved. Stage and root final object/function evidence agrees, all 2,377 previously accepted game addresses remain accepted, and validation inputs stayed unchanged.

## Behavioral review and focused evidence

The fixtures call original ELF entries and candidate symbols compiled from the complete frozen production translation unit, rather than substitute target implementations. Successful positive coverage requires completed original/candidate invocation pairs, zero observed differences, and zero incomplete observations.

| Fixture entry | Completed positive pairs | Separate exception witnesses |
| --- | ---: | ---: |
| mapEventHandlers | 309 | 17 |
| mapToFunctions | 321 | 4 |
| setPlayer | 290 | 88 |

Exception witnesses are independently checked and excluded from completed normal-call coverage. Normal player cases make two calls per side. Final full Stage and root logs reproduce these positive counts and exception checks.

Mapping coverage exercises all 97 table names in multiple cases, duplicate-last-match semantics, absent/empty/unmatched values, default owner-relative data, embedded NUL behavior, child-first recursion, signed cached child counts, and per-iteration child-array reloads. Subscriber identity, EventSet receiver adjustment, strings, connection cleanup, by-value Ogre exception copying/destruction, logger arguments, and catch-scope/propagation boundaries are observed. Six unreachable second-property-read event configurations were removed; a formerly unreachable logger-throw scenario was repaired to actually propagate. No claimed exception witness is substituted for completed-call coverage.

Player coverage includes null/non-player/player RTTI, repeated rebinding and unchanged owners, zero to three followers, button masks, slot iteration, callback order, repeated quest binding, exact receiver/owner reloads, UI strings/IDs, and callback-induced pointer/array mutations. Real dynamic_cast/RTTI is used; dependency observations and guarded fixture bytes are compared, and planned mutations must actually execute.

Nine mapping negative controls and eight player negative controls each fail through a completed difference, not a crash or incomplete observation. Mapping controls alter catch-by-value, logging level, callback identity, first/last match, default index, repeated property read, child-array reload, cached count, or unmatched-value preservation. Player controls alter unchanged-owner behavior, tenth slot, pet selection, second quest binding, updateSlots, callback receiver reload, ID, or tooltip. Focused fixture hashes match the final validated inputs. An independent source/assembly and fixture review cleared these behaviors while explicitly retaining object-DIFF and exception-table limitations.

## Initial gate rejection and direct helper repair

The initial 450-test runtime suite passed, but Stage preservation correctly rejected newly emitted weak Ogre Exception destructor definitions without direct comparison evidence (`new definition lacks MATCH or fresh behavioral evidence: 0x56d1f0`). That attempt did not publish to root. A runtime PASS was not treated as acceptance, and no preservation guard was bypassed or weakened.

The unchanged pinned Ogre inline definitions emit D0 at `0x56d1f0` and aliased D1/D2 at `0x56bd50`. These SDK/library helper addresses are not additional accepted game functions. A supplemental opaque-owner fixture directly compares each destructor entry without including OgreException.h; its object leaves all six original/candidate destructor references undefined, so the fixture cannot supply its own candidate destructors.

Each of D0, D1, and D2 has 98 completed positive comparisons, zero differences, and zero incomplete observations. Coverage includes five-string empty/nonempty masks, unique/shared/retained/leaked COW representations, short/long/embedded-NUL data, reverse release order, guarded bytes, base vptr transition, and deleting-only owner disposal. Three production-assembly negative controls (skip outer delete, skip string release, skip base destructor) produce completed differences.

An initial helper-observer attempt was incomplete on both sides and was not accepted. The observer was corrected to the real `_Rep::_M_destroy` dependency boundary, because allocator internals bypassed the executable operator-delete PLT. The production source and headers stayed frozen. The final observer records disposal requests and retains storage for snapshots; it does not establish physical freeing or allocator-internal equivalence. The base-destructor spy was reviewed against pinned libstdc++ assembly.

## Final full gates

After adding the three direct helper tests, fresh complete Stage validation and the independent complete root check both passed **453 tests, 0 failed**. Root process exit is 0 and reports `hybrid self-test: PASS`. Both full runs include fresh coverage for all three game targets and both unique weak-helper addresses. Local Stage publication occurred only after the repaired Stage acceptance gate passed. Final preservation records 2,380 accepted / 2,134 MATCH / 246 behavioral, +3,209 bytes, all prior accepted addresses retained, Stage/root object equality, unchanged validated inputs, and only the gameui production object changed.

This is headless behavioral acceptance within the exercised observations. It is not byte-identical object matching, proof of LSDA/exception-table equivalence, exhaustive equivalence for untested inputs/dependency behavior, GUI/playthrough validation, or whole-game readiness. Helper disposal-request observations do not prove allocator internals or physical deallocation. No GUI/game process was used for this validation.

## Final input identities

SHA256:

- `decomp/src/gameui.cpp`: `88bdd3879a14d8ba1da1015483afa286d72ae5713686aec7ce3687b77b0d36a3`
- `decomp/include/GameUI.h`: `a2a9a62efae7ad235999353ca716e7fa40bda847314c9c2615cd3a2742b7f38d`
- `decomp/include/GameUIWindowBindings.h`: `2c81ae2c58eeadce3335c93a5b076cbd216a7f265267bd9cd27b588fc2582f96`
- `decomp/hybrid/tests/GameUIWindowBindingsTest.cpp`: `ecd902b4aa0929745e519945cf61d16dcc6e2f479c7769bad452cc7adc676b7d`
- `decomp/hybrid/tests/GameUIPlayerRebindingTest.cpp`: `f969fdd4d458a95f9bf3b35b1989384ed09cbb870173c7fa979c8955b192ef69`
- `decomp/hybrid/tests/OgreExceptionCleanupTest.cpp`: `64ff2baee14775cac5fb2ca4d1ed4ba41f4e78c67779c62e8f566ab90418de9c`

## Evidence provenance

The following retained validation artifacts were read to prepare this report. Names identify local audit artifacts, not repository-relative published links. SHA256 binds the exact reviewed receipts/logs; focused receipts describe their own isolated source snapshots, while final Stage/root receipts bind the integrated source above.

- `window-player-stage-validation.json`: `b89813f9cca563b0feccf82de5020e3dd4ed6f4724eb957c2e38f31355725470`
- `window-player-root.json`: `c0455898a120583152f075905ad8d9a79f40e098816eaef388ed6aadcbb81fe6`
- `window-player-root.log`: `5bf8fc6dd01f1765aee38eb0f1ab704ba3bee522bb0000b5cf447d7450174979`
- `window-player-root.exit`: `5feceb66ffc86f38d952786c6d696c79c2dbc239dd4e91b46729d73a27fb57e9`
- `window-player-preservation.json`: `17149b684b72c51c7e626103606e05706530be094749710b7144027190e80ed5`
- `window-player-integrated.json`: `480b65cd1ee9ecf066ffc6f9075f6a93261ef5b1e5c964f267a15b3f76e7ec7e`
- `window-player-final-inputs.json`: `ccdc7aa40fb63259f90e6982eba2ae22d0036816dc13705858526bcc158c1a0d`
- `window-player-initial450-gate-failure.json`: `f4ae55b8d82d5763e72292be270795a88341225af4ebea3e9b63072921ba571e`
- `window-player-combined-preservation.json`: `2f3c0388dbce1d28f3150ba7958e993f01a0982cb5ce6f5bb49fe9ac78a11edd`
- `window-player-required-definition-proof.json`: `9a2a254c4526f94da89b4824d2fced6ed2c22e49f91ae6b9dfcee5b203bee3e6`
- `window-bindings-tests/executed-comparison-receipt.json`: `d0529dc6e79ee0903069759944d7ed2551b141da4c47e6278975e65f92a69bc5`
- `window-bindings-tests/negative-controls.json`: `6c3cfd66e2e0645b00ede6d564d094065c8dfb333f691fef7fbe274d83b8bcf4`
- `player-rebinding-tests/focused.json`: `a53c1b8c8d51f3ab69f38bd01743164cc331bbef09878b2ea546220ad43862f9`
- `player-rebinding-tests/negative.json`: `dabaa5e85fa1953753a7b87d57e15e1f91f7e5572da55b911cbde038f3c51eda`
- `window-bindings-tests/cleanup-executed-receipt.json`: `5e40e39ee62d411dc48245b2e60ae93e1702a8ef58a77edda038a36af75fb22c`
- `window-bindings-tests/cleanup-negative-controls.json`: `b7601ed1b92d03d4a0755eb49c7bf6cb9b2fefdd34778d26ea26a1973b2e31a2`
- `window-player-independent-review/REVIEW.md`: `260e0ba2455ab966efcc7d3079b0e34017ccc39e49551d9532577b47cb99d342`
