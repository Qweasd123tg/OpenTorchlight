# MerchantMenu controls, tabs and owner listeners

Restores 17 unique members (2521 original bytes): eleven strict MATCH and six behavioral comparisons. Six generated listener thunks add 36 bytes separately.

## Verification

- Tab controls: 2880 completed original/candidate pairs cover closed/open state, pet actions 14-16, merchant actions 64-66, boundaries and mutable collaborators. Both selected-tab fields, radio/panel call order and virtual layout updates remain observable.
- Close: 768 pairs; virtual click dispatch: 1440 pairs; recursive event mapping: 2304 pairs. Four exact callback identities are compared in existing menu creation fixtures, preserving unknown identities and receiver adjustments.
- Owner and player switching: 512 pairs each across null/same/different pointers, nullable inventories, follower profiles and callback replacement. Twenty-eight expected listener exception unwinds.
- Thirteen compiled defects rejected with completed differences and no incomplete pairs. Eleven focused tests pass.
- Full Stage.validate/publish and independent root check.py pass 330 tests. No accepted address is lost and acceptance policy is unchanged.

Character.h adds CMerchantMenu friendship and the existing getDefaultMerchantTab declaration, whose int return is verified from the original GetDataValue integer call and eax preservation. No Character implementation or object layout changes. Preparation uses the canonical merchantmenu.cpp spelling in an isolated copy; integration retains MerchantMenu.cpp.

Totals: 1575 accepted entries, 1418 MATCH + 157 behavioral, 1041473 original bytes. Headless verification does not establish interactive playability.
