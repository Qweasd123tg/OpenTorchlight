# CombineMenu original-item tracking and return

Restores itemUpdatedInMenu, returnItemsToCorrectLocation and equipmentUsed
(974 original bytes), plus the six-byte equipmentUsed listener adjustment thunk.
The original TU-local tracking flag is bound to its verified local ELF symbol.
The Inventory declarations for isEquipmentInInventory, getEquipmentEquippedAt
and equipEquipmentIntoSpecificLocation now use the return types established from
both original callees and callers: bool, CEquipment*, and bool respectively.
No foreign Inventory method body is changed.

## Completed comparisons

- Tracking: 8960 pairs cover global suppression, insertion/removal, existing and
  missing target keys among other keys, nullable source inventory, alternate
  inventory identities and signed/full-width equipment-location values. Existing
  mappings must not be overwritten and unrelated mappings remain observable.
- Return: 44544 pairs cover nullable item, missing/stored locations, nullable
  original inventory, slot bounds -1/0/18/19 and signed extremes, occupied slots,
  successful/failed equip, inventory membership, pickup success/failure and world
  fallback. Position, nullable level, drop order and collaborator-driven player
  replacement are captured. Original-null-player combinations that dereference
  null are excluded; no source guard is invented for those invalid inputs.
- equipmentUsed: 44544 pairs with tracking enabled and 44544 with suppression;
  the real return implementation executes on both sides, with a controlled
  virtual layout collaborator and observable final map state.
- Existing performInteraction comparisons execute real itemUpdatedInMenu on both
  sides with initialized, populated maps and observable membership/value snapshots;
  256 normal and 120 expected-unwind cases retain their branch requirements.
- Eight compiled defects are rejected by completed differences with zero
  incomplete pairs; all clean Combine focused tests pass.
- Stage.validate/publish and independent root check.py pass all 274 tests.

No previously accepted address is lost; acceptance criteria are unchanged.
Bounded headless evidence does not establish interactive playability.

Totals: 1478 accepted entries, 1356 MATCH + 122 behavioral, 1015659 original bytes.
