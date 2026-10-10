# InventoryMenu controls and listener notifications

Restores 14 member entries: inventoryDestroyed, handle_ItemClick,
handle_MouseThrough, setTab, handle_onClick, handle_SpellMouseOver,
handle_SpellMouseOut, processInput, handle_MouseOut, setOwner,
checkForUpdate, equipmentUnequipped, equipmentPickedUp and onClick.
Nine are strict MATCH and five have completed original/candidate comparisons.
Three additional 6-byte listener adjustment thunks are strict MATCH, counted
separately from recovered methods. inventoryDestroyed and spell mouse-out are
original no-op bodies confirmed by MATCH, not placeholders.

## Behavioral evidence

- Tab click: 48 cases; radio buttons, pane visibility, images and notifications.
  Unlike PetMenu, the original InventoryMenu does not store a current-tab index.
- Click dispatch: 576 cases including absent window and non-left buttons.
- Owner: 144 cases cover inventory presence, owner replacement, listener order,
  weapon checkbox state and collaborator mutation including removal of the owner.
- Notifications: 4800 cases. Initial notification flags vary independently from
  equipment/inventory presence, so incorrect unconditional resets are observable.
- Mouse-out: 1728 cases exercise hover, dragged item, window and UI state.
- Input: 3072 cases. Inactive hiding orders overlay before icon parent; active
  no-hover handling uses the opposite order, as shown in the original.
- Existing createMenus: 3136 cases. Callback comparison adds only exact restored
  handler identities and retains receiver, this-adjustment and unknown pointers.

Eight deliberate compiled defects are rejected by completed differences with
zero incomplete pairs: tab notification, button dispatch, owner listener, owner
checkbox, notification boundary, hover clearing, inactive hide order and wrong
createMenus callback. All seven clean focused tests pass afterward.

Header changes expose observed fields at +0x62, +0x78 and +0x7c without changing
layout, and declare nonvirtual checkForUpdate after inspecting its original body
and callers. Fresh prepare-only packets resolve the dependency before recovery.

Stage.validate/publish and independent root check.py pass all 252 tests.
No earlier accepted address is lost. Bounded headless comparisons do not establish
interactive playability.

Totals: 1444 accepted entries, 1005930 original bytes, 1335 MATCH and 109 behavioral.
