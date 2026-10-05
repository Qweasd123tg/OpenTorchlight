# Equipment save-state application

Original applySaveState(CItemSaveState&) is0x8863b0/814 bytes. The
fixture compares8960 cases, twice per side, with real save-state objects,
strings, vectors, RTTI/dynamic_cast and recursive Equipment application.
Services outside this method are controlled collaborators: Item application,
unit creation, socket attachment, effect insertion/activation/recalculation,
elemental damage, price and requirements. This does not claim full save-file
or campaign loading.

Cases cover scalar/base-damage/base-armor sentinels, skip GUID=-1, recursive
children, repeated application, effect ownership transfer, null and replacement
effect results, restoration of pre-callback effect values, per-activation
clearing, bonus reset to the current type count, and final service order.
Callback cases grow socket/effect/damage lists, replace a child's snapshot
during the factory call and install a previously absent effect manager.

An initial fixture used a mixed signed/unsigned ternary for GUID=-1 and
accidentally produced4294967295. Both sides correctly rejected that test input;
that result was not accepted. The fixture now uses explicit signed64-bit
literals. Null/non-Equipment factory returns and cyclic snapshot graphs are
not valid inputs in this fixture; the original has no defensive guard for
those cases and this implementation does not invent one.

The fixture cleans controlled effect objects after observing the transferred
state. It does not claim that every failure path of the external effect manager
is leak-free. No generic pipeline tools or other source TUs were edited.

Normalized instruction comparison is MATCH100%. Additional independent checks
kill24/24 sampled viable mutations and34/34 targeted mutations.
