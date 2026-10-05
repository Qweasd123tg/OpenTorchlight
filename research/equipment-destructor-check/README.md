# Equipment destruction

Primary destructor D1/D2:0x87d770,1645 bytes. Deleting destructor D0:0x87de00,
18 bytes. D0 and both secondary-base thunks are normalized MATCH; D1 is97.2%,
with the remaining normalized differences confined to equivalent container
comparison operand directions and temporary registers. No shared container
helper was rewritten just to increase this score.

The fixture compares4352 cases. Original Equipment construction initializes
real Item/BaseUnit state and real member strings/containers; its helper is an
extern original alias, deliberately not TL_ORIGINAL coverage for the constructor.
Owned visual, particle, sound, path, attack and model deleting destructors are
controlled spies. Socket deletion, list growth, weak registrations, string COW
aliases and the real Item/BaseUnit destructor chain run normally. Cases cover
all ownership flags, null/expired/live references, duplicate or wrong-subobject
listeners, socket null entries, callback count/pointer changes and a throwing
reset callback. A false initial exception failure was fixed: the fixture had a
raw entity with null SceneManager, and early unwinding bypassed Equipment's
entity reset. The exception fixture now leaves that entity null. Neither
original-and-recovered failure was counted as success.

The opt-in glibc watcher observes seven selected member buffers, never alters
allocation behavior and requires every allocated watched buffer to be freed
exactly once. It compares free order in normal and exception cleanup. Five
intentional buffer-leak mutations demonstrate that these checks are effective.
The ordinary integrated check also runs all4352 behavioral cases without the
watcher; check_frees.py and the mutation scripts require it explicitly.

19/19 sampled viable mutations and27/27 targeted mutations killed. The preserved
behavior removes Equipment's secondary iMissile listener but does not delete
its live heap safe-reference objects here; external registrations after the
call match the original. The fixture cleans surviving registered references
after observing them. It does not claim global missile lifetime is leak-free.

The storage at+398/+3b0 has the verified zero-init/trivial-vector-free layout.
Exact original POD element types remain unknown. Byte-vector members preserve
these observed construction/destruction operations and automatic cleanup order;
this is an explicit provisional element type, not an invented gameplay meaning.
Size0x438 and offsets are checked. Other owner TUs and generic pipeline tools
are unchanged. This verifies Equipment's ownership protocol, not the complete
implementations of every render/audio collaborator destructor.
