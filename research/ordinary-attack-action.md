# Ordinary attack action: evidence and implementation boundary

Work based on the supplied `OpenTorchlight-gpt-pro-large-3.zip`. The original ELF and
`pak.zip` remain external read-only inputs and are not included. Local integration
verified the recorded original ELF hash:
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

## large-4 continuation update

See [gameplay-continuation.md](gameplay-continuation.md) for the current boundary.
The exact effect path, innate defaults and vertical cutoff are now connected.
The 1.5 AI-flag branch is an explicitly evaluated input only; flag producers and
lifetime are NOT implemented. Entry-mode death recovery now shares the same live
floor/controllers and invalidates old actions. Ranged and global phase ordering
remain open. The 15/15 and 52/52 below describe the previous stage/integration,
not new original-game validation. New tests: 21/21 portable and separate ASan/UBSan.

## Sources before integration

- **original-code** `CCharacter::selectAttack @0x811bc0`: current description is
  retained while action time is positive. Normal selection chooses right hand,
  alternate left weapon, only-left weapon, or a random innate description. It
  does not ask for the first generic `Attack*` animation independently of gear.
- **original-code** `CCharacter::setLevel @0x83ead0` creates the innate `ATTACK`
  description with speed denominator 1; UNIT supplies `ATTACK_RANGE` and
  `STRIKE_RANGE`, not a made-up `ATTACKANIMATION` field.
- **original-code** `CEquipment::calculateCombatStats @0x880950`, selected blocks
  from `0x881470`: equipment SPEED/100 -> description+0x70. Weapon type branches
  allocate hand-specific prefixes: BOW (left only), CROSSBOW/RIFLE/POLEARM (right
  only), RPISTOL/LPISTOL, RWAND/LWAND, RSLASH/LSLASH. STAFF and POLEARM share the
  latter polearm family. Weapon constructor boolean is NOT a ranged flag.
- **original-code** `CGenericModel::findRandomAnimation @0x8a2de0` keeps the first
  prefix match, with each later match independently replacing it at probability
  1/2. Manifest ordering and loaded clip identity must be preserved.
- **original-code** `CCharacter::attack @0x82b550`: effect 0x16 changes playback
  speed. If negative, its magnitude is reduced by clamped effect 0x8c/100.
  `max(.2,(1+effectiveSpeed/100)/descriptionSpeed)` is used for BOTH the clip
  and action duration. UNIT ATTACKSPEED is not a substitute. AI-flag extra
  multiplier branch was excluded in the previous stage; large-4 now accepts
  the evaluated flag and applies the confirmed 1.5 after the clamp.
- **original-code** `CCharacter::updateAnimation @0x848870`, `updateAttack
  @0x848790`: model advances, bones update, then every applicable HIT is consumed.
  `performAttack @0x847280` toggles normal hand alternation per HIT, including
  misses. Ranged missile/weapon-skill execution is a different path and is not
  implemented as instant melee damage here.
- **original-code** `CMonster::attackAI @0x8dfd80`: AI cooldown starts only after
  a successful action; the existing independently verified signed scalar timer
  is retained, advancing concurrently with the clip.
- **original-code** `CCharacter::maxDamage @0x815d40`, `strength @0x813930`,
  `dexterity @0x8139a0`: physical branch supports attribute percentage/flat
  effects, melee/ranged damage %, dual/type bonuses, physical/all-channel %,
  corresponding flat damage; USEWEAPONDAMAGE=false uses the first innate base
  even when the selected weapon supplies animation/range/speed. No crit, block,
  dodge, pet-owner multiplier or elemental attack is claimed by this patch.
- **original-code** `attackRange @0x812580`, `inAttackRange @0x826140`,
  `inStrikeRange @0x824a50`: acquisition and strike use different description
  ranges; include scaled reach, .2 contact allowance and RANGE_MULTIPLIER;
  horizontal distance subtracts nonnegative collision radii. Vertical cutoff
  at 0xfce4c4 is now supplied by the pinned-ELF JSON and integrated as 2.5.
- **original-code** `parseEffects @0xd608f0`: 145 ordered children populate the
  effect-name table (`0xd60a27`), not hardcoded guessed English effect names.
  `CEffect` reads TYPE, ACTIVATION (default DYNAMIC), DURATION (default ALWAYS),
  then its value/conditions. Constant unconditional PASSIVE effects are a
  deliberately bounded loader; unresolved graph/rank/random/proc effects are
  reported, never falsely certified as zero.

Some narrow instruction exports come from an earlier user-supplied archive
`OpenTorchlight-gpt-pro(2).zip`, `original-analysis/full-intel-disassembly.asm`,
which declares the same ELF hash. The full dump is NOT copied to this project.
Its origin and the ELF hash were not independently verified against an ELF.

## Portable decisions, not original ABI claims

- **inferred** immutable `OrdinaryAttackAction` clip/description snapshot,
  monotonic execution token, per-key consumption ledger and explicit
  advance -> pose -> deliver -> finish phases prevent duplicate/replayed HITs,
  stale world references, and renderer/logic clip divergence.
- **original-code** the read-only extraction at 0xff82c8 resolves to
  `media/EffectsList.dat`. large-4 uses exactly the normalized compiled ADM path;
  the old structural discovery is removed, including silent corrupt-file fallback.
  No assumed spelling -> effect ordinal mapping is used.
- **prototype retained** global update/substep scheduling, AI perception/path
  refresh, damage mitigation's supported subset and absent dynamic effect
  lifecycle. This work is not the whole original combat system.

Final test results and remaining exports are recorded in the delivered Russian
report. Synthetic fixtures are authored data, not captured original gameplay.


## Final validation / remaining inputs

Portable CTest 15/15, separate GCC ASan/UBSan 15/15; 50 shared-action and
132 authored resource-backed combat assertions. Local full validation passed
52/52. The speed comparison produced 12,392 float32 bit matches against the
SHA-checked ELF slices and constants. `research/original-combat-inputs.json`
records the seven float32 values and UTF-32 effect path with addresses and bytes.

Attribute and damage sums preserve the integer additions visible at
0x813982..0x813993 and 0x815f69..0x815f9e before final float conversion.
Out-of-domain integer overflow is rejected rather than wrapped. Constant effects
are bounded using `CEffect::calculateBaseValue @0x7dc9f0` and
`modifyEffectsByCharacter @0x7e4520`; character-dependent/grouped/graph/conditional
fields are rejected by the loader, not silently treated as constant.

`inferred`: an execution generation token is distinct from action/entity IDs;
it survives fresh-controller ID reuse without consuming gameplay RNG. Desktop
phase ordering across different characters remains prototype, not a recovered
whole-level scheduler. Entry-mode death/recovery is now implemented in the large-4 continuation;
projectile execution and the other recovery modes are not implemented.
