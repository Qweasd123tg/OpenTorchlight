# Equipment save-state capture

`CEquipment::fillSaveState(CItemSaveState&,int,bool)`, original `0x8867c0`,
1394 bytes. The implementation follows the original ELF; Ghidra is navigation.
The normalized instruction comparison is DIFF, so acceptance requires the hand
fixture and mutation checks, not the similarity percentage.

The fixture compares 5120 cases, with two calls per side. It runs real
CItemSaveState construction/destruction, CEffect copy construction, owner and
skill-owner setters, strings, vectors, TArrayLists and recursive Equipment save
calls. Parent Item serialization, classification, affix removal/restoration,
name-cache refresh and elemental-damage creation are controlled collaborators.
Their call order, arguments and resulting state are recorded. It is a test of
Equipment's save protocol, not a second claim to recover all these services.

Coverage includes independent dropping/enabled/base-save/identified flags,
three effect activation lists, distinct populated manager lists, nested socket
children and grandchildren, retained destination entries, cache side effects,
manager/type changes during callbacks, captured socket count, a growing effect
list, manager replacement between activation lists and post-copy source entry
or value replacement. Real effect-copy helpers are not advertised as recovered
functions. A fourth sentinel list detects an accidental extra activation pass.
An initial mutation pass missed exactly this extra pass (22/23); that gap was
fixed rather than accepted merely for exceeding the mutation threshold.

The save payload has verified size 0x180. Effect vectors start at 0xe0; socket
snapshots at 0x128; damage types and bonuses at 0x140/0x158. CEffect remains 0x138,
with its copied/restored float at 0xc0. Shared declarations preserve layout and
ABI; no other source TU or general pipeline tool was changed.

Limits: the input socket graph is finite and acyclic, source entries are valid,
and parallel damage arrays have equal length. Allocation failure, corrupt
pointers and whole-game persistence/load compatibility are not claimed. The
original non-RAII affix restoration on exceptional exits is preserved; this
fixture does not claim new exception safety or fix the original behavior.

Final fixture: 23/23 sampled viable mutations and 23/23 targeted mutations killed.
