# Pass11 integration, 10 October 2026

Source package: OpenTorchlight-pass11-20261010.zip supplied by the user, based on historical handoff cd9873907a120008134e7284b32f88a642476338. All 907 snapshot hashes and the patch hash were verified before reconciliation. The supplied restore script was not executed.

## Reconciliation

The package claims 403 additional strong gameplay MATCH addresses relative to its historical base. Against the already integrated PR70 baseline, 149 were accepted already and 254 were potential additions. These counters must not be added without overlap removal.

Three-way reconciliation retains the current headers, previously accepted definitions, full GameUI call-boundary/OGRE compatibility fixes and corrected EffectManager behavior. All 171 prior top-level definitions in the seven conflicted source files remain present. EquipmentRef keeps the old field aliases alongside the refined typed pointer and effects flag. Character's 0x778 layout is supported by original writes through +0x774 and Monster's string at +0x778. Player's overlapping raw journal/identified-field view preserves original absolute offsets.

The mutable CPath::GetPoint call used by dyingAI is bound explicitly to the original symbol, leaving the existing const path implementation's overload resolution unchanged. EditorScene retains the original gObjectsCreated binding instead of creating a separate counter. No acceptance tools, thresholds or TU ownership assignments were changed.

## Verification

An enum-only OGRE utility header prevents new static string initializers from changing unrelated translation units. Seven affected objects were restored exactly to their baseline digests. The unused QuestManager type refinement was deferred, and EditorDLL retains the original GetTimeline helper boundary. New receipt-bearing graph and math fixtures cover 2,560 normal completed original/recovered pairs; all 15 deliberately incorrect target variants were rejected. Three additional layout/lifetime fixtures cover 896 completed pairs. They exposed a pre-existing CLevelState layout bug: the first four collections are std::vector, not TArrayList. Original insertion symbols confirm all four types. Correcting the members and removing the redundant local overlay restores strong MATCH for the constructor; the exact-byte fixture failed all 128 constructor cases before the fix and passes afterward. Quest reward cleanup passes 768 mixed-type, duplicate, and callback-mutation cases.

All 403 claimed addresses have fresh strong MATCH in the final combined build. Strict isolated Stage validation and the independent root check each pass all 404 headless tests. Existing comparison cases, assertions and failure conditions are retained. Of 20 incoming fixture changes, 11 were already integrated; the other nine update exact layout assertions, typed buffers and full-object capture sizes without reducing coverage.

This establishes original-code/object and headless comparison evidence, not a standalone build or live gameplay claim. Original game binaries, runtime libraries and compiler archives are not included.

Final accepted gameplay addresses: 2342 / 5247, including 2113 MATCH and 229 behavioral acceptances. Accepted original machine-code bytes: 1137990. Net increase: 269 addresses, with no prior accepted address lost.
