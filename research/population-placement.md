# Population placement — original-code reconstruction (pass 1)

Status of this document: `original-code` for the ASM-verified items below,
`inferred` where marked, `prototype` remains for everything not listed here
(BFS candidates, full-shuffle, entry/warp exclusion distances, 2.25 spacing,
formations, spawn nodes, NPCS/CREEPS/PROPS sections).

Pinned inputs (read-only, never copied into the repo):

- ELF `Torchlight.bin.x86_64`
  SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`
- pak.zip SHA-256 `8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`
- Decompilation under study: `research/decompiled-core/level.c`
  (Ghidra output, used as index only — decisive facts below are re-verified
  against `objdump -d` of the pinned ELF).

## 1. Entry points (symbols from research/original-symbols.txt)

| Symbol | Address | Size | Role |
|---|---|---|---|
| `CLevel::populate(bool)` | `0x962630` | `0x38c2` | 5 section calls + retry driver |
| `CLevel::populateSectionOfLevel(min, max, class, b1, b2)` | `0x95d220` | `0xa1c` | per-entry rejection sampling |
| `CLevel::populateFormations(CRandomizer&, boxes)` | `0x95dc40` | `0xc64` | NOT studied this pass (open) |
| `CLevel::randomOpenPosition(pos, radius, bool)` | `0x9459a0` | `0x2b` | wrapper, min radius `0.0` |
| `CLevel::randomOpenPositionRange(pos, minR, maxR, bool)` | `0x945770` | `0x224` | single polar pick (see §3) |
| `CLevel::isInNoSpawnRegion(pos, radius)` | `0x9453f0` | `0x1e2` | region test, radius `1.0` here |
| `MATH::rotateY(Ogre::Vector3*, float)` | `0xc7a400` | `0x59` | `x'=x·cosA+z·sinA`, `z'=z·cosA−x·sinA`, y untouched |
| `CLevelTemplateData::getNumberOfUnitsToCreate` | `0x971530` | `0xaf` | already ported + compared (10 055 cases) |
| `chooseUnitSpawners` | `0x974f80` | — | already ported |

Vector3 layout confirmed by `rotateY` ASM: `+0=x`, `+4=y`, `+8=z`.

## 2. Section dispatch (`CLevel::populate`, ASM truth — decompiler labels unreliable here)

Five `call 0x95d220` sites, `(r8=b1 useNodes, r9=b2 champions)`:

| Call site | Class source | b1 nodes | b2 champions |
|---|---|---|---|
| `0x963468` | template+`0x578` (fallback `MONSTERSET`) | 0 | 0 |
| `0x964498` | template+`0x580` | **1** | 0 |
| `0x96466d` | template+`0x590` | 0 | **1** |
| `0x96483f` | template+`0x598` | 0 | 0 |
| `0x964a1b` | template+`0x588` | 0 | 0 |

Note: the Ghidra decompilation prints literal `true` as 5th argument at the
second site; the ASM shows `xor r9d,r9d` immediately before the call, so the
decompiler is wrong there — **nodes and champions are used by two different
sections**, never together. Which template field maps to
MONSTERSETCHAMPION/NPCS/CREEPS/PROPS is unresolved (`inferred` candidates only);
the fallback literals appear in decomp order but the template offsets
(`0x578/0x580/0x588/0x590/0x598`) are non-monotonic across calls, so no mapping
is claimed.

This pass ports only the `b1=0` rejection-sampling path. The spawn-node branch
(`CLevel+0xf0` node array, `+0xf8` count, per-node use counter `+0x114`,
≤10 tries preferring unused nodes) stays open: the port has no spawn-node
structure at all. `populateFormations` stays open entirely.

Return-value driver (ASM `0x963487–0x9634b6`): section counts accumulate into a
running total; `inferred` details of the "force progress after 10 empty
sections" branch are not ported yet.

## 3. `randomOpenPositionRange` — verified behaviour (ASM, not decomp)

Input: center `(px,py,pz)`, `(minR, maxR)`, `checkNoSpawn`. Reachable path:

1. `r = randomBetweenVolatile(minR, maxR)`; `Adeg = randomBetweenVolatile(0.0, 360.0)`.
2. `A = Adeg * *(float*)0xfce49c`, single-precision (`mulss` at `0x9457d2`).
   `DAT_00fce49c = 0.01745329238f` = (float)(π/180), pinned f32 read; the C++
   literal `0.017453292F` assembles to identical bytes (verified). NOTE: the
   *facing* setup in `populateSectionOfLevel` uses the double path instead
   (`cvtps2pd/mulsd/cvtpd2ps` at `0x95d723–0x95d732` with the f64 at
   `0xfc4588 = 0.01745329252`); the two must not be unified.
3. `rotateY((0,0,r), A)` = `(r·sinA, 0, r·cosA)` via `sincosf` (one call that
   yields both parts — a split `sinf`/`cosf` port is NOT bitwise-identical).
4. Candidate `(px+dx, py, pz+dz)`. Return `(x, y)` as 64-bit + `z` in `xmm1`
   (the `randomOpenPosition` wrapper at `0x9459a0` explicitly propagates it:
   `movss [rsp+8],xmm1` round-trip; observed, not assumed).
5. The bounds pre-check (`UCOMISS xmm3,[mem]` at `0x945835`, AT&T operand
   order verified under GDB: it tests `(x'+0.8) < (x'−0.8)`) falls through to
   the grid scan in the normal case. The scan tests ONE polar candidate per
   attempt for `mapPassable` + `positionPassable` (+ `isInNoSpawnRegion(·,0.0)`
   when flagged); its elaborate x/z loop bounds collapse to a single
   evaluation — confirmed both by the structurally identical sibling
   `randomOpenItemPositionRange @0x9455e0` (single test per attempt, plain
   `R += 0.1` schedule) and by GDB control-flow observation. ≤100 attempts;
   the radius schedule is `R = max(5.0, R + 0.1)` after 5 failures
   (`DAT_00fa86d0 = 5.0`, `DAT_00fa480c = 0.1`); give-up returns the input
   position. An earlier revision of this document misread the operand order
   and wrongly called the scan dead — corrected after live debugging.
6. `this` (`CLevel*`) IS dereferenced by the scan's map queries. Native
   coverage therefore executes the sampling prefix piece by piece
   (volatile draws + native `rotateY`, see §6), while the loop itself is
   control-flow verified under GDB.

Consequence: the port's BFS-connected-component + spacing policy was a
stricter invention and the prime suspect for the 51/76 shortfall — confirmed
by the scenario re-run (§6).

> Audit correction (2026-09-18): the sentence that previously stood here
> claiming NO map-collision filtering was a leftover of the early dead-scan
> misread and contradicted §3 item 5. The live scan DOES test
> `mapPassable`/`positionPassable` per attempt; the port maps both layers to
> its single walkable flag (open approximation, §5). Do not use the removed
> sentence as guidance.

## 4. Per-entry loop (`populateSectionOfLevel`, `b1=0` path, ASM `0x95d548–0x95d690`)

RNG consumption order per attempt (register-verified, note Z before X):

1. `z = randomBetweenVolatile(min.z, max.z)` → slot `0x68`
2. `x = randomBetweenVolatile(min.x, max.x)` → slot `0x150`
3. input triple `(x, 27.5, z)`: `0x41dc0000 = 27.5f` is a code-immediate height
   guess, passed as Vector3 y.
4. `(x', y'=27.5, z') = randomOpenPosition(triple, 3.0, true)` with
   `DAT_00fa86d4 = 3.0f` (pinned f32 read). So `r ∈ [0,3]`, `A ∈ [0°,360°)`.
5. Accept unless `x'==x && y'==27.5 && z'==z` (three `ucomiss`+`jne`/`jp`
   pairs; NaN/unordered accepts — identical to C++ chained `!=`).
   Retry counter `ebp ≤ 0x31` → at most 50 attempts, else the entry is skipped
   (falls to the next rolled entry, no spawn).
6. After accept: `isInNoSpawnRegion((x',27.5,z'), DAT_00fa47fc = 1.0f)` —
   inside → back to step 1 (same 50-attempt budget). Radius `1.0` pinned.

Then per accepted entry:

- `createUnit(manager, datagroup, level = CLevel+0x1a8, false, false)`.
  The `+0x1a8` rank field confirms the earlier `inferred` rank wiring.
- Facing (non-node path, ASM `0x95d6ec–0x95d758`): `A2 = (float)((double)
  randomBetweenVolatile(0.0, 360.0) * π/180)`, direction `(sin A2, 0, cos A2)`
  via `rotateY((0,0,1), A2)`, installed through vfunc `+0x120`.
- Node path (`b1=1`): rotation installed through vfunc `+0x108` — open.
- Item leaves: four `passableBetween` corner checks with half-extents
  `DAT_00fa4824 = +2.0`, `DAT_00fc4568 = −2.0` (pinned); any failure destroys
  the item. Open in the port (port spawns monsters only).
- Character leaves with `b2=1`: `CRandomNames::generateName` +
  `CCharacter::makeChampion(name, level + 1)`. Champion **level+1**, not level.
- Return value accumulates created characters + placed items.

## 5. Port boundary for this pass

Port: §4 steps 1–6 + live scan (§3). The `level+1` champion rule is RECORDED
from ASM but NOT implemented (no `makeChampion` port exists anywhere in the
tree — only an XP-formula comment; nothing is wired to this path). Open in
the port (no code, documented): node branch, formations, item corners, NPCS/CREEPS/PROPS
sections, section-rect plumbing (the port uses its 0.4-grid bounds as the
section rect), no-spawn regions (the port tests carried points with the
original 1.0 radius instead of region boxes), spawn facing (no facing state
in the port), second 0.4 layer semantics (both original layers map to the
port's single walkable flag; the walkable flag itself carries the port's
actor-radius inflation, unlike the original path grid).

Known deviation (documented, not hidden): spawn height. Original passes the
constant `27.5` and lets the engine settle; the port has no settle step, so it
samples ground height from its own grid at `(x',z')` (nearest walkable cell,
entry height fallback). Only the isolated sampling-prefix X/Z values have
been compared bitwise (§6); accepted world positions depend on the
approximated walkability predicate and a different RNG stream, so they do
NOT claim parity. Y differs as well.

## 6. Verification (2026-09-18)

- `original_population_placement_comparison`: 3005 sampling prefixes
  (volatile radius/angle draws + native `rotateY`) with bitwise-equal
  candidate coordinates AND volatile RNG states
  (`tests/compare_population_placement.py`, probe
  `tests/population_placement_probe.cpp`). Covers the sampling mechanics;
  the loop is GDB-verified control flow, see §3/§5.
- Authored fixture (`population_cycle`): 12/12 requested/created, same-seed
  determinism, save/load stability — unchanged.
- Real pak mine, seed 42 (`original_population`): requested=61, created=61,
  unplaced=0 (previously 61/61 via the prototype filter — same totals, now
  through original-order sampling).
- Common-application scenario, seed 491: requested=76, created=76,
  unplaced=0 in 3 runs — previously 51/76 with 25 unplaced. The connectivity
  filter was the cause; no requested count was lowered to green the test.
- Full suite: 137/137 (core 68, assets 43, reference 17, render 11 with
  group overlaps).

Open questions (do not guess): template-field → section-class mapping;
`CLevel::populate` force-progress branch; `populateFormations` box semantics;
`isInNoSpawnRegion` region storage (only its call radius is pinned).
