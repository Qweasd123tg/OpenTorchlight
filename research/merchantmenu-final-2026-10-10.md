# Complete MerchantMenu measured surface

Restores updateLayout, constructor and both destructors: four unique members, 5226 original bytes. Two generated destructor thunks add 15 bytes. All 31 measured CMerchantMenu member addresses are now accepted.

## Verification

- updateLayout: 18432 completed original/candidate pairs and 24 expected exception unwinds. Covers null/empty followers, nullable inventories, all merchant and pet tabs plus out-of-range tabs, capacity fallback, inventory mutation and collaborator replacement. Main slots 19-144 and pet slots 19-81 are cleared in their original property order. Pane selection reloads list elements before and after getItemPane.
- Constructor: 32 completed pairs across memory patterns, sound availability, alternate collaborators and GUID extremes; 56 expected exception unwinds. Injected callback-owned array storage checks cleanup when menu creation throws.
- D1/D0: 3072 completed pairs each, with 12 expected exception unwinds. Owner is cleared before player, followed by model, sound bank and array storage. Callback replacement, nullable inventories and both array ownership states are observable.
- Header tail +0x3460 has the proven 24-byte TArrayList ownership/layout and grow-by 10. The original element type remains unknown; unsigned-char storage models only the observed initialization and delete[] cleanup. Object size and surrounding offsets are unchanged.
- Fifteen deliberately compiled defects rejected with completed differences and no incomplete pairs. Twenty-seven focused tests pass.
- Full Stage validation and independent root check pass 346 tests. No accepted address is lost; no acceptance policy changed.

Totals: 1588 accepted entries, 1421 MATCH + 167 behavioral, 1052345 original bytes. Headless evidence does not establish interactive playability.
