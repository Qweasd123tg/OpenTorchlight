# Missile runtime packet (Line B1)

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Full ASM reports from two agents are the evidence base (method: objdump
linear reads + function_package call sets; decomp navigation-only). This note
is the distilled contract. Compared=false throughout (no original execution).

## 1. Delivery decision (who flies at all)

`performAttack @0x847280`: `doWeaponSkill @0x8245c0` → `fireMissiles @0x87f120`
→ melee strike/ray. Prior port finding (ranged-direct-evidence.md, kept):
ordinary bows/pistols/rifles/staves are DIRECT-physical (DAMAGE_PHYSICAL=100,
no MISSILE — "a visual arrow trail does not make that a simulated missile").
Wands carry MISSILE (e.g. FIREWAND). First port consumer: wand weapons.

## 2. Creation (`fireMissiles` + `fireMissile @0xd04610` + `initialize @0xd00650`)

- Exactly 1 missile per call: preloader by `equipment+0x400` MISSILE name
  (`getMissilePreloader` + `createNewMissileRef`; null → return 0).
- Owner = `equipment->v[0x340]()`; safeptr swap into `missile+0x220/228`;
  equipment↔missile lists maintained both directions.
- Launch pos = anchor + dir·range·WEAPON_SCALE·0.8 (`WEAPON_SCALE` data value
  default 1.0; `0.8 @0xfc676c`; range from attack-desc, INF/ ZERO cases);
  orient = `Quaternion::FromAxes`, target null → ZERO-vector path.
- Velocity = dir · template `+0x158` (default 1.0; **no rodata speed** —
  do not invent m/s). `+0x250` arch factor template-only (not written here).
- Resets: hit lists cleared, particles stopped/re-anchored, homing state
  zeroed, `+0x1b0=[+0x1ac]`, `+0x258=[+0x254]`, target select (closest-target
  when homing), aim via `calculateLaunchOrientation @0xd01090` (±100.0 ray
  test, CPath when `+0x19c>0`), immediate short-range (4.0) collision probe,
  `+0x185=1`.
- `initialize` defaults = template fallback table (speed 1.0, radius 0.2
  `0x3e4ccccd`, lifetime 25.0 `0x41c80000`, `+0x1b4`=1000.0, vel 0, flags…).
  Called only from ctors.

## 3. Per-frame (`update @0xd04120`)

Guards `+0x81/+0x185` → particle/anchor upkeep → distance accumulators
(`+0x1bc/+0x1c0`) → dying branch (`handleDeathOfMissile`) → lifetime gates
(`+0x1c0>=+0x1b8`, or `+0x186 && +0x1bc>=+0x198`) → `killMissile + doAOEDamage`
→ save pos → `updatePositionByVelocity` (already ported bit-exact) →
`checkCollision` loop (repeats while `+0x142 && unit-out`, i.e. pierce) →
`setPosition` → trail-particle upkeep. Editor-running short-circuit kept open.

## 4. Collision (`checkCollision @0xd038a0`)

Level: `sortForCollisionByPoints` + `preSortedSphereCollision` → impact point,
normals, code, adjusted end, unit out. Unit path: owner-exclusion
(`+0x144==0 && unit==+0x220` → no-hit), pierce type filter (ISA 0x19/0x1d
excluded, meanings open), `handleMissileHitUnit`; single-hit via `+0x298`
duplicate scan (+`+0x2b0` flags). World path: `+0x188==0` or slope
(`param_8.Y<=~0.2 @0xfa86e8`) → hit; else wall-slide (copy-through +
`+0x178` lift). Ricochet (`+0x180/+0x17c` budget) rebuilds path, clears lists.
Kill/AOE unless piercing-with-unit or already dying (`+0x184`).

## 5. Delivery (`handleMissileHitUnit @0xd034c0` + `doDamageToCharacter @0xcf9620`)

Veto loop (effect `+0x28`), ISA(0x20) = no-damage hit, ISA(0x02) branch,
reflect path (`getDmgToReflectFromMissile>0`: negate velocity, clear travel,
`setTarget(0)`), else `doDamageToCharacter(dir, 1.0, +0x280)`:
graph-damage(`this+0x68`) at `target+0x100` × `randomBetweenVolatile
(+0x284,+0x288)` × `+0x290` → `CCharacter::applyDamage(pos, dmg, vec, +0x28c,
…0x200)`. No `this` writes in the damage path.

## 6. Destruction (`killMissile @0xd014a0` + `handleDeathOfMissile @0xcf9840`)

`kill`: `+0x184=1`, `+0x1b4=1.0`, death-particle start, effect loop. `handleDeath`:
`+0x1b4-=dt` → stop particles, wait for drain, destroy virtual `+0x50`,
clear effect list, detach scene nodes. Removable=0. List removal caller-side.

## 7. Port mapping (new code, no behavior invention)

- Template: `media/Missiles/<NAME>.LAYOUT.adm` via `parse_adm` (fields incl.
  original typo `AOE RAIDUS`); `initialize()` defaults = fallbacks.
  Measured: FIREWAND dist=8 vel=17 r=0.2 aoe_r=2.0 aoe_s=0.33;
  BOWMISSILE dist=8 vel=60 r=0.1 (skill-only consumer: BOWARROW skill).
- Motion: reuse `missile_motion_step`. Machine-code fact found by testing:
  EVERY missile rotates dt·π/180 per tick (~1°/s; verified `0xfc4588` =
  π/180 from rodata) — reproduced bit-exact, not "fixed".
- Obstruction: `collision_segment_clear` (same primitive as ranged-direct).
- Units: `entity_world` positions + radii; owner exclusion; hit-set.
- Delivery: per-victim `roll_missile_impact_damage` (NEW twin of the
  ordinary roll sharing one loop; the ordinary gate is untouched — the
  typed_damage_test missile-refusal pin stays green) + `apply_damage` +
  existing death/loot. The original graph decomposition stays open; the
  port maps the observable contract (wand deals wand damage). AOE splash =
  full base damage to all others in radius (the 0.33 scale feeds effect
  hooks only — proven from doAOEDamage body, hooks absent in port).
- Open (no sink): missile MODEL/particles/trails rendering (same category as
  skill visuals); reflect; ricochet budget; pierce (`+0x142`); homing
  (arch>0, e.g. POISONWAND HOMING SPEED); breakable smash (virtual+0x280);
  enemy casters (enemy gate still refuses).
