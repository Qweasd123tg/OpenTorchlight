# PetMenu controls and inventory notifications

22 original entries restored: 16 strict MATCH and 6 accepted only through
fresh completed original/candidate comparisons. Original no-op callbacks remain
no-op because their original bodies were inspected, not because they are stubs.

## Behavioral comparisons

- Tab click: 48 cases covering closed/open state, all three tabs, unknown action
  values, visibility, selected radio buttons, notification reset, image properties
  and update ordering.
- Click dispatch: 576 cases covering button filtering, null windows, user-data
  actions and returned results.
- Owner: 144 cases covering unchanged/changed owners, inventory presence,
  listener offsets, notification reset and collaborator replacement.
- Notifications: 4800 cases covering null item/inventory, pane and slot boundaries,
  visibility, full menu bytes and update calls.
- Mouse out: 1728 cases covering null window/owner, item identity, focus type,
  tooltip-overlay visibility and hover clearing.
- Input: 3072 cases covering active/inactive modes, deferred close, focus type,
  hover flags, glow parents, click resets, UI ordering and return values.
- Existing createMenus: all 4704 completed cases remain passing. Callback capture
  now recognizes six additional exact original/replacement identities; unknown
  pointers, member-pointer this-adjustment and receiver are still compared.

Initial negative control exposed coupled fixture inputs: item presence also
set an already-true notification flag, masking an inverted visibility condition.
Notification initial flags now vary independently across all eight combinations;
the expanded 4800 cases reject the inversion by completed differences.

Eight deliberately compiled defects are rejected by completed differences,
including a wrong callback in createMenus. A clean final focused run passes all
seven tests. No acceptance condition was relaxed.

Added the verified nonvirtual checkForUpdate(CEquipment*) declaration and
regenerated prepare-only context before implementation. No virtual slots or
class layout changed. Source remains readable C++98; no emulation layer added.

Normal Stage.validate/publish and independent root check.py pass all 234 tests.
The newly emitted UTF-16 reserve helper lost a strict MATCH after the TU changed;
added 1600 original/candidate comparisons of the actual linked helper, covering
empty strings, embedded NULs, non-ASCII units, growth/shrink requests, sharing,
copy-on-write detachment, capacity, terminator and reference counts.
Exactly 22 member-entry addresses and six 6-byte compiler-generated listener
this-adjustment thunks are added; all six thunks are strict MATCH. These are
reported separately rather than presented as six additional restored methods.
All prior accepted addresses remain. Total 28 newly accepted original entries
are added and all prior accepted addresses remain.
Totals: 1418 accepted entries, 1319 MATCH and 99 behavioral.
Headless bounded comparisons do not establish interactive playability.

Restored member bytes: 1941; listener thunk bytes: 36; total accepted original bytes: 997808.
