# Ordinary dungeon population — large-12

Pinned original hashes are listed in finite-recovery-evidence.md. This is not
champion/boss/NPC/prop/formation/quest population and does not claim campaign completion.

## Original-code / actual resources

`CLevelTemplateData::getNumberOfUnitsToCreate` 0x971530, size 0xaf: if either
explicit count is positive, sort endpoints and use inclusive random integers
with truncated endpoints. Otherwise both density endpoints must be positive;
count = ceil(random(min,max) * area), with the original operation order actually
random(density_min * (float(pathable_nodes)/6.5f), density_max * area).
The divisor lives at 0xfce4e0. Pathable node count is accumulated from the level
path grid, not the one-meter movement grid. The original grid uses 0.4f
(0xfa4830), center offset 0.2f (0xfa86e8).

Template default monster class MONSTERSET, densities 0.01f/0.0125f, counts zero;
chooseUnitSpawners 0x974f80 chooses one nested spawn class when randomized-class
is requested. Ordinary SpawnClassCatalog weight/count handling is reused.

MAIN STRATA0 overrides class to MINEFLOOR1, density 0.0175/0.0175 and monster
level 1. The fifth floor is GOTHICFLOOR1, monster level 4, not depth 5. Mine boss
stratum says NONE and must not acquire ordinary mobs by fallback. These values
were previously discarded by LevelSceneLoader and are now retained/applied.

## Explicitly portable / incomplete

Collision reconstruction, connected-component selection, five-unit entry safe
zone, three-unit warp safe zone, spacing, shuffled candidate cells, batch limit
and group truncation are portable placement policies. Exact original locations,
formation geometry, all shared RNG ordering and original collision are not
reproduced. Population uses a distinct fine grid; the existing movement grid
and its tested behavior are unchanged. Resource levels and stats are evaluated
before storing entities. The enclosing world's spawn rank is restored afterward.

Creation is transactional (entities, identifiers, RNG and rank). A persisted
completion flag prevents duplicate population. Existing v1–v3 floors are never
silently regenerated. Category zero refuses non-MONSTER records rather than
turning NPCs, pets or props hostile. Failure/omission counts are visible.

Tests exercise authored classes, bounds, same-seed determinism, no repeat after
save/load, non-hostile rejection, death/loot, rollback, and an actual generated
mine with actual resource classes and mesh paths. Resource tests are not native
code parity; the count arithmetic oracle is recorded separately.

## Executed numerical comparison and actual placement limit

`original_gameplay_numeric_comparison` directly executes the original bounded
count function and original RNG, with the original 6.5f divisor and real ceilf.
10,055 input cases match both the count and final RNG state. This compares only
count arithmetic, not the original whole-floor random sequence or locations.

The seed-42 actual mine resource test creates 61/61 requested ordinary monsters
with no missing or unsupported resource. In the seed-491 common-application
scenario the portable connected-component/spacing policy can place 51 of 76
requested monsters; 25 are explicitly reported as unplaced. This is a known
placement/navigation limitation, NOT full population parity. The remaining
placed units still take part in combat/rewards/checkpoint persistence; failure
to place every requested unit is not silently claimed as success.
