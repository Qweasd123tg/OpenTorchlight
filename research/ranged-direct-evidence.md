# Ordinary physical ranged attacks — large-12

Inputs: original Linux ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`;
pak `8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`.
External originals are read-only and are not distributed in this source tree.

## Original-code and resource-derived boundary

`CCharacter::performAttack` at 0x847280, retained in
`research/decompiled-core/character.c`, first tries the weapon skill and
`CEquipment::fireMissiles` (0x87f120). A handled missile/skill path returns.
Otherwise the ordinary strike/ray path checks the target and rolls direct
physical damage; a visual arrow trail does not make that a simulated missile.
`fireMissiles` checks the MISSILE descriptor. Its absence is NOT permission to
ignore a weapon skill or an unknown damage allocation.

The inherited normal pistol, bow, rifle and crossbow resources have explicit
DAMAGE_PHYSICAL=100 and no MISSILE. Their prototype RANGE/STRIKERANGE pairs are
6/7, 7/8, 9/10, 11/12 respectively. Wands have an explicit missile descriptor
(e.g. FIREWAND) and cannot use this direct-physical path. These are weapon
prototype values, not a replacement for the existing computed attack range.
The actual Vanquisher starts with LEFT `Loose Shortbow`, not a pistol.

The runtime now classifies inherited weapon definitions as direct physical,
missile, weapon-skill, unsupported mixed damage or unverified. Only positively
identified direct-physical ranged attacks are enabled. Missing metadata is
not guessed. Damage is dispatched at the selected animation clip's actual
HIT key, with the existing action ownership/duplicate-event ledger. Target
life, current range and line of sight are rechecked at HIT. A blocked or moved
target produces a consumed miss, not delayed free damage. Enemy ordinary
physical attacks use the same delivery and line-of-sight boundary.

## Explicitly portable / still incomplete

The two-sided segment/triangle test uses the reconstructed static collision
scene. The 0.8-unit body-center ray, triangle epsilon, missing-geometry rejection
and lack of dynamic doors are portable policies, not original physics parity.
Full mesh collision equivalence, bone muzzle origin, faction/dodge/crit/proc
handling, aiming and tactical movement around blocking walls remain open.
No missile flight, wand behavior, skill AoE or visual ArrowTrail was added.

Weapon delivery and the current recovery state are persisted in OTC v4.
Old saved weapon metadata is hydrated from the actual definition without
rerolling concrete damage, changing HP or advancing RNG. Player facing is
stored directly in the common loop instead of converting matrix -> atan2 on
every save; frozen save/load no longer causes repeated floating-point drift.

## Reproducible tests

`ranged_cycle` uses authored player/enemy animations and descriptors: actual
HIT, duplicate key, wall/backface/coplanar/parallel geometry, out-of-range target,
missing context, unsupported damage/skills/missiles and old delivery hydration.
It includes 2,000 randomized line-segment symmetry cases.

`original_ranged` loads actual resource families and the actual Vanquisher bow
manifest. A test wall prevents damage; removing that obstruction permits the
same real HIT path. This proves the specified resource-backed port behavior,
not execution of the original performAttack function.

`application_combat_render` creates Vanquisher through the actual common menu,
clicks the real Town portal, loads Main 1, selects an ordinary populated monster
with pointer input, kills it at HIT, observes the XP transaction and writes a
checkpoint. A second process checks the saved player, reward, entities, RNG,
facing and population flag. No monster, item, HP or damage is injected.
The real renderer runs in Mesa/EGL; no Wayland window or original process is
claimed. Detailed outputs are in `verification/large-12/`.
