# doWeaponSkill cluster (caller-side continuation of the missile packet)

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Status: analyzed (structure + key sites verified in ASM); NOT ported/wired —
bottoms out in the skill-execution engine. Compared=false.

## 1. `CCharacter::doWeaponSkill @0x8245c0` (0x354 B) — contract

Role in `performAttack`: weapon-attached skill fires INSTEAD of the ordinary
strike; nonzero return ends the attack (verified: entry guards, loop, OR-
accumulate sites read in objdump, rest decomp-guided).
- Guards: null equipment/owner → 0; skill-manager `+0x1c8` null → 0
  (`8245de-8245f8`).
- Anchor check via `getEquipmentEquippedAt` (`824601-824639`); position via
  `getPosition` (`824649`).
- Skill loop: index compare against `skill+0x68`, gate
  `(skill+0x6d & (skill+0x6b ^ 1))` (`824790-8247ba`, semantics of the two
  bytes open), `executeSkill(skillmgr, skill, attacker, 2, calcPos, quat,
  offsetPos, owner)` @0xcd4930 (`824860`); nonzero result OR-accumulates and
  returns early (`82486c`); else next skill via `knownSkills` count.
- Launch position math (subagent-read, spot-unverified): attacker pos +
  dir·max(dist, 0.6·[attacker+0x194]) (`0xfa4838`), Y +0.5 (`0xfa4810`),
  offset +10.0·dir (`0xfa86e0`).

## 2. Callees (call order, not bodies)

`getEquipmentEquippedAt @0x91b460`, `getPosition`, `CSkillManager::
knownSkills`, `executeSkill(CSkill*,...) @0xcd4930` → `executeSkill(wstring,
...) @0xcd45c0` (name management: find/start/stop/charges) → `CSkill::
startSkill` + effect application with `EVENT_*` dispatch (engine).

## 3. Why this cluster stops here (code-order boundary)

Projectile creation for SKILLS does not go through `fireMissile` (verified:
exactly one direct caller of `d04610` in `.text`, the equipment path) nor
through `createNewMissileRef` (single caller, same). Skill missiles arrive
via the effect engine (`EVENT_MISSILEHIT/MISSILEDIE` exist as event types;
creation site unrecovered). Porting doWeaponSkill correctly therefore needs
the skill-execution engine first — implementing a shape-alike now would be
exactly the scenario-first invention the project forbids. The weapon_skill
delivery refusal stays.

## 4. Next code-chosen target

Skill effect application chain (`startSkill` → effect appliers → EVENT
dispatch): it unlocks doWeaponSkill AND cast-skill projectiles AND the
magic/skills runtime in one move.
