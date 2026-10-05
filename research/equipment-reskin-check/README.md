# Equipment class-based reskin

Original reskinByClass(std::wstring), 0x888920, 2027 bytes. The model path is
+0x110 (verified by copy at 888bc1), not the +0x120 getName() field. Carving the
wstring preserves CGenericModel size 0x250, with compile-time fixture checks.
No GenericModel source TU, constructor or destructor was changed.

2520 cases twice per side use real DataGroups and string case conversion;
loadModel alone is a controlled collaborator. Tests cover missing models,
class case, empty class, missing/empty/different mesh paths, matching and
nonmatching current paths, duplicate case-equivalent classes, last-match
clears, secondary preservation/clears and a warm second call after model-path
update. The caller's by-value query is also compared.

Unlike isWardrobed, an empty class query is not a wildcard. Matching groups
accumulate ITEM_MESH and ITEM_MESH_SECONDARY with previous local values as
fallbacks, but explicitly empty strings clear those values. Only a nonempty
changed primary path triggers loadModel; secondary-only changes do not.
Comparison is case-insensitive; no slash normalization occurs here.

5/5 sampled viable mutations killed (6 candidates probed); 14/14 targeted
semantic mutations killed. This tests selection/reload decisions, not rendered
mesh results. The separately recovered loadModel has its own fixture.
