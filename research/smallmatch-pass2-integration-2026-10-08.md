# User smallmatch-pass2 integration

Source: [user-supplied archive](https://drive.google.com/file/d/1uuXTSp3KrRBFFvEbH-a7fUORp7nE-mTh/view), received 2026-10-08.
Its 385 manifest hashes verified. Full tool suite: 420 tests, 419 passed and one
Java-dependent skip. Original ELF and pinned compiler unchanged.

The archive reports 211 additional normalized MATCH addresses in its <1000-byte
queue: 147 existing implementations gain strict metadata proof; 42 generated
C++ definitions cover 64 addresses including ABI variants. It does not claim
211 newly written bodies or a byte-identical full executable.

The cleanup-only LSDA proof is narrow: single exact FDE, supported personality,
identical function size/instruction offsets and complete zero-action call-site
rows, with no catches/type tables or relaxed instruction layouts. The memory
jump-table bound proof requires a dominating unsigned guard and same-cell load;
all destinations still verified. Unsupported metadata remains DIFF.

Initial whole-source Stage passed all 146 headless tests but refused publication:
four appended TUs changed complete objects containing old unaccepted bodies.
No gate was relaxed. Those four were temporarily restored to baseline, and a
fresh Stage accepted the remaining 17 TUs with all 146 tests passing.

Verified partial result: 1162 accepted / 407894 original bytes, 1144 MATCH plus
18 behavioral. This adds 209 addresses to the previous 953 with no losses:
207 of the package's 211 plus two existing larger bodies proved by the improved
matcher: CDescriptor::~CDescriptor 0x6fdbf0 (1549 bytes), and CEquipment::drop
0x87aaa0 (6775 bytes). The latter two are outside the small kit's target queue.

The held-back additions are CMissileDescriptor::CreateObject (85 bytes),
COutputIncrementorDescriptor::CreateObject (85), and EditorButton/Image descriptor
scene-activation methods (95 each). Their old bodies are being independently
compared before reintegration; partial acceptance is not reported as full import.

That review exposed a real old bug: EditorButtonDescriptor::InputLogicEvent used
dynamic_cast<CEditorImage*> while the original RTTI target is CEditorButton.
The original rejected a plain image; the old C++ acted on it. A real-RTTI fixture
reproduced this and the corrected candidate passes. Four constructor registration
fixtures compare strings, types, callbacks, flags, base arguments, logic events
and final state. Pointer canonicalization is limited to independently MATCHed
getter/setter pairs; wrong callback selection is detected by a negative control.

Full reintegration and the SkillMenu candidate are still under final validation.
No rendered-editor/gameplay or constructor-exception-injection claim is made.

Independent check.py on the partial 1162-function tree also passed all146 tests,
exit0. This checkpoint is committed separately from the pending full import.

## Full integration checkpoint

Stage tu-peatmdps revalidated from scratch with the stronger constructor matrix
and passed all153 tests. It published1173 functions /474878 original bytes:
1149 normalized MATCH and24 behavioral. All211 claimed package addresses and
all original941 baseline addresses are present. The four held-back definitions
are included, with fresh evidence for their six previously unaccepted bodies.

Constructor coverage is48 cases for each fixed constructor and192 for the
parameterized incrementor:8 flag patterns,3 initial-memory fills,2 registration
return sequences, and4 distinct argument-text profiles where applicable. With
128 input-handler cases, the descriptor fixtures compare464 cases. The initial
8-case fixed-constructor runs were below the existing20-comparison acceptance
minimum; they were expanded, not accepted through a lowered threshold.

The corrected button InputLogicEvent is now also normalized MATCH. The five
constructor negative controls and original wrong-cast fixture all detect their
intended faults. The independent final root check also passed all153 tests and exited0.
All54 callback identity pairs remain MATCH in the final combined objects.
