# Heirloom improvement

`CEquipment::improveHeirloom`, 0x882330, 446 original bytes.

The standalone comparison passes 4,608 cases twice per side. All 23 primary
and five additional targeted mutations are killed. Combat-stat calculation,
base-value recalculation, description invalidation and requirement setting are
controlled services. CEffect::value runs the original ELF implementation
through an observing wrapper, with null graph pointers and varied finite,
signed-zero, infinity and NaN input values.

The original recalculates combat stats first, then checks signed field +0x28c
against 10 and the current manager. All three activation lists are visited;
each group's current list is retained while its entries/count are re-read
after callbacks. C4 and C8 each receive value(index) * 1.1f, followed by
calculateBaseValue(0). C0 is restored from its pre-callback snapshot * 1.1f.
A double-precision 1.1 literal is not equivalent and is caught by the fixture.
Descriptions are invalidated only inside the gate, while requirements are
always updated. The field +0x28c remains generically named in production.

Fixtures vary list growth/shrinkage, fallback indexing, entry replacement,
manager replacement, gate changes during combat recalculation and overwritten
C0 values. They do not claim a full validation of external graph curves,
combat statistics or base-value recalculation.

Shared Effect fields C4/C8 were carved from the existing opaque region;
allocation size remains 0x138. No effect.cpp implementation was changed.
