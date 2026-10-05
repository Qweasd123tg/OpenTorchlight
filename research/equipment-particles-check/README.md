# Equipment particle selection and attachment

Original createParticles() 0x885a70, 1679 bytes. UTF32 literals were read from
the pinned ELF (see original-literals.json). Custom drop effects preload only
when absent; existing custom particles are retained without a name comparison.
Default drop priority is quest, unique, magical, generic. Existing names are
uppercased for comparison; mismatches delete/reset/recreate. Drop attachment
requires visible, unequipped and model present. Active weapon effects require
only a model, independently of those drop restrictions.

Element priority on ties: electricity, fire, ice, poison. All four bonuses are
queried in this order. No positive value leaves an empty name; the original
still calls the factory with that empty name. Pistol-specific strings are used
only for a winning element. Parent(false), zero position and Start ordering is
preserved; factory/singleton/deletion callback field changes are re-read.

The final 2144-case fixture runs twice per side. Its selection matrix crosses
32 classification combinations, 13 damage patterns and three existing-particle
states. Separate matrices cover all eight attachment-state combinations,
custom/default paths, per-call creation failures and callback state changes.
Real string operations and Ogre nodes are used. Particle loading, creation,
deleting destructors, attachment/position/start and bonus/type services are
controlled collaborators. This verifies orchestration, not actual particle
rendering, simulation or destructor correctness.

An initial 21/23 sampled score was rejected: all positive bonuses were >=2,
so two changes moving the positive threshold to1 survived. Four unit-damage
patterns were added. The final pass kills 23/23 viable sampled mutations and
23/23 targeted mutations. Initial evidence is retained explicitly.

The original particle-name wstring at+0x110 is borrowed through a const view.
Particle.h and Particle.cpp are unchanged: that TU is still partial in this
snapshot (empty destructor and a self-recursive updateLevelObject). Making its
scaffold void* field an owning wstring here would implicitly alter the foreign
destructor. This declaration debt is explicit, size/offset checked, and should
be resolved with the Particle owner's full reconstruction. The Master's
preloader pointer+0xf8 and pointer-only preloader interface preserve layouts;
CRunicCore base and size0xc8 come from RTTI and observed allocation size.
