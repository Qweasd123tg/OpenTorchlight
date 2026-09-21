# Resource-driven skill dispatch into the application

Evidence recorded before implementation, 2026-09-19. External ELF SHA-256:
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
The prior `trace_skill_events.py` oracle already reproduces 15 original cases;
The numeric oracle initially covered 2078 cases; production integration adds
48 left-hand cases, now 2126 including ordered channels and RNG.

## Function family and evidence

- `original-code`: `CSkill::startSkill @0xca9150` activates state before
  posting START and succeeds even when START has no handlers. Null caster /
  null property are distinct from an empty event scene.
- `original-code`: `CSkill::triggerEvent @0xca5950` dispatches the indexed
  event list; START (0) and TRIGGER (2) cannot share an implicit scene.
  Clone/allocation branches remain explicitly outside the simple scene path.
- `original-code`: `CCharacter::updateSkillKeys @0x811650`, inspected in
  `decompiled-core/character.c` and original disassembly, filters animation
  owner indices and sends key type 0 (HIT) to `triggerSkillEvent(2)`; key
  0x1c sends event 3. Preserve playback ownership/replay protection.
- `original-code`: `CSkillEvent::CSkillEvent @0xcc71d0` reads USEDPS at
  `0xcc770f` (default false), WEAPONDAMAGEPCT at `0xcc77f6` (default 0),
  SOAKSCALEPCT at `0xcc7874` (default 100). Damage and soak fractions divide
  by 100 and clamp to nonnegative. Do not omit USEDPS from the damage request.
- `original-code`: `CEquipment::calculateCombatStats @0x880950` reads SPEED
  (wstring at `0xfae9d0`) as integer default 100 (`0x880bda`), stores it at
  stack+0x3c (`0x880be7`), divides by 100 (`0x881470`), and stores that
  float into attackDesc+0x70 (`0x881528`). Thus the existing portable
  `AttackDescription::speed_denominator = equipment.SPEED / 100` is the
  same input read by rollAttack at `0x844157`, not animation playback speed.
- `original-code`: `missileApplyingEffects @0xcb8360` calls the weapon leg
  AFTER the initial MISSILEHIT post, then effects/hit-skill posters. HP/death must come from the weapon sink
  before UNITDIE is selected, not be supplied before creating the request.
  `applyWeaponDamage @0xcb7b70` selects right weapon, otherwise left at
  `0xcb7d93`; Vanquisher's starting bow is LEFTHAND. Dual branches remain refused.
  Its own internal UNITDIE and invokeHitSkills' second death post are not yet
  mirrored: portable outcome delivery currently posts one unit-death notification.
- `original-code`: `assignSkillAnimations @0xca4a00` uses the equipped
  weapon prefix (+0x2a0 right, +0x2a8 left). `castSkill` still uses effects
  0x1d/0x8c and skill SPEED for playback, not ordinary weapon attack speed.

## Resource boundary

`media/skills/vanquisher/seeking/SEEKING.DAT.adm`: NORMAL, EVIL,
USEWEAPONANIMATION=true, ranged weapon requirements; LEVEL1 has mana cost 10,
START=`warmup.layout`, TRIGGER=`seeking.layout`, damage 40%, soak 60%,
USEDPS=true. Existing `SkillCatalog` owns rank inheritance/cost/cooldown;
the old parallel `load_skill_trigger_levels` parser has been removed.

Supported program compilation must refuse unhandled gameplay fields/effects,
not turn arbitrary skills into this template. Cosmetic START layout state may
be recorded without claiming complete particle/sound rendering. Spawner
COUNT, spread/homing/anchor math and full canEffectPosObject/performAttack
gates need independent original evidence before full SEEKING parity claims.

## Integration contract

Use the existing cast admission, mana/cooldown state and authenticated
animation playback. START occurs on admission; only the cast's genuine HIT
can post TRIGGER. The application remains the missile-runtime owner. Resource
scalars travel with each launch/impact. Cast records outlive their animation
while missiles remain; changing level/death cancels pending cast work. Damage
uses the existing combat RNG and world outcome tail. Self buffs retain their
existing behavior; no second skill inventory or cooldown clock is introduced.

Implemented in `SkillCatalog` -> `SkillCast` / `PlayerSession` ->
`SkillEventRuntime` -> application-owned `MissileRuntime` ->
`CombatController::apply_skill_weapon_impact` -> `RuntimeEntityWorld`.
`original-code` applies only to the documented branches/numeric slices;
ID ownership and replay guards are `inferred` portable policy. The application
facing-vector aim and untransformed launch anchor are explicitly `prototype`.

The strict compiler rejects arbitrary scene objects/logic graphs, nested
effects, unsupported events/fields, missing assets, missile-spawning START
and a cosmetic-only TRIGGER. It does not check skill NAME. The accepted
SEEKING scene still reports COUNT=3 as one launch with `repeated_count_open`;
it is shown as PARTIAL PROJECTILE in the UI. No guessed spread is added.

Cleanup replaces the duplicated rung parser, synthetic single-layout ctor,
caller-supplied pre-damage death fact, unused effect-execution facade and
second cooldown clock. `SelfBuffCast` is generalized to `SkillCast`; existing
self-buff effects and save format remain. Research history, decompiler data,
original assets and user saves are not deleted. Removed tracked code remains
recoverable from Git history.

Ownership guards cover last-frame HIT before animation completion, casts
whose missiles outlive the animation, later casts while prior missiles fly,
per-victim deduplication, and world-terminal-before-splash batches. Retirement
is after the whole impact batch. Level changes/death cancel pending work;
missiles now use simulation time, so opening inventory does not advance them.
Checkpoint capture refuses in-flight skill projectiles instead of silently
discarding their pending damage (their transient state is not serialized).

## New native hook trace

`tests/trace_skill_missile_hooks.py` executes the unchanged 370-byte
`missileApplyingEffects @0xcb8360`; function SHA-256:
`076b3464160e169afbe42f44eba2904709178a1744f0a8d4f84c55821d3d7fce`.
Six scenarios cover normal, canEffect refusal, reflected, source event 6,
missing parent skill, and both appliers returning false. Confirmed normal
call order: canEffect -> orientation -> MISSILEHIT -> weapon -> effects ->
invokeHitSkills. Forwarded pointers, coordinates, scales and flags are checked.
External calls are controlled recording callbacks, NOT executions of their
bodies. Native internal UNITDIE duplication, full canEffect and native HP remain
open; the portable runtime currently emits one outcome-based unit-death post.

CTest `original_skill_missile_hook_trace` is in `reference`; output is
`<build>/skill-missile-hooks.json`. These traces do not turn the lifecycle's
`compared` flag true.

## Verification and next boundary

- `original_skill_event_program`: real rank inheritance/scenes plus compiler
  refusals. `original_skill_event_resource_composition`: real START/TRIGGER,
  request scalars and callback ordering, not full-game parity.
- `original_skill_production`: real Vanquisher bow/animation and SEEKING,
  controlled monster HP/armor fixture; admission/mana, genuine HIT, launch,
  impact, damage/HP/death/credit, delayed ownership, cancellation and saves.
- `application_skill_projectile_render`: real frontend creates Vanquisher;
  an explicit isolated XP/gold fixture reaches level 10. Menu investment/F,
  START/HIT/launch/terminal order, inventory pause/resume and actor rendering
  run through the common application loop. No campaign-completion claim.
- `original_skill_weapon_damage_comparison`: 2126/2126 arithmetic comparisons;
  existing 12088 ordinary/allocation/defense comparisons remain green.

Validation on 2026-09-19: **80 core + 48 assets + 21 reference** CTest cases
passed, no failures/skips, including optional pinned external lodepng source.
Report: `build-verification/skill-production-check.json`. Additionally all
three focused common-loop/GLES scenarios passed: skill projectile, existing
Infuse/merchant/save flow, and existing ordinary missile flow. The complete
render group and desktop/Wayland shell were not run. Terminal/splash and
zero-COUNT fixes were followed by another run of the three affected runtime,
resource-composition and production tests.

The next high-value unit is the original spawner function family
(`spawnUnitByIndex`, `createAndFireMissile`) for COUNT, timing and complete
launch transform, followed by CMissile homing/target gates. Restore those with
function-level native input/output fixtures; do not multiply the current
approximate projectile three times and call that recovered SEEKING.
Full UI/campaign/effects and whole-game parity are separate unfinished work.
