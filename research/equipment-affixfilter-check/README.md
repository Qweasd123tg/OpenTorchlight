# Affix filtering and socket insertion

- `removeAffixesThatDontSupportUnitType`, 0x86e020, 431 bytes: 5,120 differential
  cases, two calls per side. Ten targeted mutations killed; one equivalent
  early-return deletion survived.
- `addContainerItem`, 0x86e1d0, 380 bytes: 5,760 differential cases, two calls
  per side. All nine targeted mutations are killed.

Filtering captures the original affix list, traverses its dynamic entries/count,
collects rejected affixes with a grow-by-one TArrayList, then deletes through
its current effect manager on each call. The fixture checks callback-driven
list changes and manager replacement, plus predicate/deletion exceptions.
Removing only the empty-list early return changes neither allocation nor calls
because the empty temporary allocates nothing. This survivor is not reported
as a killed mutation or evidence of an untested behavioral branch.

Socket insertion compares unsigned count/capacity, appends first, filters a
non-randommagic socketable child's affixes by the parent's current type, then
re-reads the child's manager for effect recalculation. An exception retains
the already appended child, as the original does. Filtering is independently
compared against its own original entry; insertion is not treated as independent
proof of the nested filtering implementation.

`check_heap.py` observes glibc malloc/free only during the call/catch region.
It requires instrumentation to be loaded and compares both sides' counts as
well as their traces and state. The grow-by-two and leaked-temporary mutations
are both killed by this scoped observer. Cleanup of fixture-owned arrays is
outside the counted region. This is allocation/free parity, not an exhaustive
heap-safety proof or fault-injection campaign.

Typed exceptions use std::runtime_error. An independently reproduced generic
hybrid-import bug breaks int RTTI; see ../hybrid-object-import-probe. Both
sides crashing is never accepted as equivalence.
