# BaseUnit culling bounds evidence upgrade, 2026-10-09

CBaseUnit::updateCullingBounds(), original 0x7fff00, 2845 bytes. Existing production body unchanged, candidate 2789 bytes, normalized DIFF, no unknown references. The strict original packet is completed using the separately reviewed pinned OGRE constant context. Review covered null/position/model-call control flow, transformation and bounds expansion, and final corner stores; no claim of byte identity.

720 completed original/candidate cold/warm comparisons, zero differences or incomplete observations. Null bounds leave state alone. World-position selection and repeated model virtual lookups preserve the branch where the second lookup becomes null. Model-local position is added when present; orientation is copied and its translation replaced. The eight transformed corners expand the world AABB and populate the final ordered corner array.

Inputs retain real headless Ogre nodes and position/math helpers. They cover identity, negative/nonuniform scale, rotation, shear, projective and zero-denominator matrices; ordinary/reversed bounds, NaN, infinity and signed zero; scene-node/parent combinations and missing/changing model results. Exact invocation and complete-report requirements replace the old matching-exit-only check.

Observations include all initialized base-unit/model/bounds bytes with only known base/node/bounds/vtable pointers canonicalized, repeated lookup counts, original orientation and node position. This is bounded evidence, not exhaustive Ogre internal state or arbitrary callback/exception equivalence.

All twelve independently compiled deliberate faults were rejected by completed differences with zero incomplete observations. Strict full Stage and independent root validation each passed all 192 tests. Root acceptance: 1316/5247 functions, 938549 original bytes, with 1255 MATCH and 61 behavioral acceptances.
