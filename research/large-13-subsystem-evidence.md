# large-13: source-grounded subsystem boundaries

Input is large-12. Reference ELF SHA-256:
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Original pak and ELF remain external/read-only. This document records evidence
before implementation; a listed address is NOT a claim that the whole function
or feature is implemented.

## Skill definitions and state

- `CSkill::getLevelRequiredForInvestment`, 0xc9cc40: next property's level gate;
  fallback base required level plus invested rank. No interpolated rank curve.
- `CSkill::getManaCost`, 0xc9cd90: property float converted to integer.
- `CSkillProperty::CSkillProperty`, 0xce5f90; `CSkill` constructor: successive
  LEVELn properties inherit preceding property, not just root defaults.
- `CCharacter::canCastCurrentSkill`, 0x8258a0: owner alive, integer mana,
  cooldown, target and skill-specific gates. A catalog is not a caster.
- `CSkill::startSkill`, 0xca9150; `CSkill::updateSkill`, 0xca6160: cooldown
  belongs to skill and uses simulation seconds, not wall-clock time; CSkillProperty divides COOLDOWNMS by 1000 at 0xce765c.
- `CSkillProperty::getCoolDown`, 0xcdd1f0: player and monster cooldown fields
  are distinct.

Resource example: Ember Bolt/EMBERFIREBALL has rank-dependent layouts with
2/3/4 bolts, poison damage, MAGIC scaling and a linked knockback effect.
A single instant fire hit is NOT an implementation of this skill.

## Missile numeric integration

`CMissile::initialize` 0xd00650; `updatePositionByVelocity` 0xd02720;
`checkCollision` 0xd038a0. Homing uses a 1/30 second accumulator and normalized
linear interpolation, not an angular degrees-per-second turn. Float constant
at ELF 0xff6858 is 0x3d088889. Target Y offset is twice missile radius.
Collision uses a swept sphere in the original; a point ray is not equivalent.
Life cycle, reflections, spline paths, hit effects and scene collision must be
reported separately from the numeric kernel.

## Equipment economy

`CEquipment::recalculatePrice` 0x883e20: ceil(graph(max(1,level))*VALUE/100),
separate NORMAL/MAGIC/UNIQUE buy/sell graphs, VALUE default 100; VALUE zero
leaves constructor prices 1. Unidentified price always uses NORMAL graphs.
`buyPrice` 0x86fc20; `sellPrice` 0x86fb40: multiply by max(1,count), barter
(effect 0x53, channel 7) only on identified items; integer truncation before
subtract/add; positive buy price clamped to at least 1.
Out-of-domain integer overflow is rejected, not assigned a fictitious price.
Vendor stock/quality, identification and services are independent features;
price arithmetic alone does not implement those.

## Quests

`CQuestRequirements::parseRequirementTag` 0xdfe5d0;
`questRequirmentsHaveBeenMet` 0xdfec90: QUESTSCOMPLETE, QUESTSNOTCOMPLETE,
QUESTSACTIVE lists; inclusive level/depth limits; sentinel -1; depth is
max(0, player's maximum visited depth + 1), not current floor. RULESET selects
the dungeon template at that depth. Self-completion dependency exception is
retained. Already completed quest cannot be offered again.
`CQuest::isComplete` 0xd0cc10: QUESTCONTROLLERCOMPLETES prevents automatic
objective completion. Never substitute "all enemies killed".
`CQuestController::setQuestComplete` 0xde6b20; setQuestAccepted 0xde6c00;
updateLevelObject 0xde6ec0: controller input and output events are separate
from reward payout and dialog. No fake completion or unearned rewards.

All novel architecture/serialization adapters must be labelled portable, while
resource rules and recovered formulas are labelled resource-derived/original-code.

## Finite self-buff executable slice

`CCharacter::castSkill` 0x827eb0, especially 0x82852c onward: successful
start before mana debit, then cast animation; 0x82860e onward computes
max(0.2,(1+cast_speed/100)*SPEED), with slow resistance only for negative speed.
`CEffectManager::addNewEffect` 0x7f2f10: incoming EXCLUSIVE terminates prior
effects with equal NAME AND TYPE; it does not retain the stronger magnitude.
Infuse's real alchemist.animation has HIT at frame 6.295503. Its gauntlet
affixes supply 30..75 seconds and 30..75 percent melee/ranged bonuses.
UNIT THEME is retained as metadata, not replaced by a fake particle.
Rendering of those themes, sound and hand particles remains incomplete.
The current compiler accepts only explicit single TRIGGER, finite deterministic
DYNAMIC modifiers with existing consumers, and an original single cast clip.
No partial execution of other skill event chains is allowed.
Portable adapter: zero-canonicalized ready cooldowns, atomic mutation, bounded
serialization and HIT ownership ledger. Mid-cast saves are refused.

## Source event/merchant/controller details confirmed in this pass

- `CCharacter::updateSkillKeys` 0x811650: HIT key type 0 calls the current skill
  trigger event (index 2), conditional on matching animation state.
- `generateMerchantInventory` 0x836cb0: player-level factor >0 uses
  ceil(player level * factor); `playerLevelForMerchantInventory` 0x834b90
  reads PLAYER_LEVEL_FOR_MERCHANT, default 0.
- `CSpawnClassData::fillRandomizer` 0xa7cf40, especially 0xa7d1cc..0xa7d286:
  explicit MINLEVEL/MAXLEVEL inclusive bounds. Equipment MAXLEVEL=0 instead
  uses item-range graphs and is outside the new potion-stock slice.
- `CGameUI` item transfer near 0xa90a00: an infinite merchant item with stack
  count one is recreated from its original data, transferred first, and money
  debited on successful pickup. Finite stock and buyback are NOT the same path.
- `giveQuest` 0xd33150 original ASM (the Ghidra export fails) does not call the
  requirements matcher. Forced controller inputs therefore bypass offer gates;
  normal NPC offering must not reuse that bypass.
- `CQuestController` inputs 53..56 are Force Accept / Force Not Accepted /
  Force Complete / Force Not Complete. Outputs 98..102 are Quest Active /
  Quest Not Active / Quest Complete / Quest Not Complete / Quest Abandoned.
  Force Not Accepted passes false to removeQuest and does NOT emit Abandoned.
- `CQuest::giveRewardForQuest` 0xd1d270 increments journal statistic 4, gives
  chained quests with giveQuest(false), then cleanup. The new flag-only slice
  rejects reward/population/objective/pet side effects as a unit, not just the
  unknown individual fields. `completeQuest` starts at 0xd32600 (corrected from
  exploratory address); no "kill all" substitute is introduced.

Portable presentation boundary: minimal purchase panel exposes only verified
infinite potions, using the player level at opening for the eligible resource
projection. It is not a complete copy of native merchant inventory refresh,
finite stock, sale/buyback or CEGUI merchant layout. Unsupported source entries
remain recorded. Original sound/particles/dialog presentation are still pending.


## Portable lifecycle and verification limits

`CPlayer::levelResetting @0x8f5810` calls `removeNonSavedEffects @0x7f3b50`.
Effect SAVE flag is read near `0x7e169f`; Infuse does not set it. The port
clears offensive transient buffs on death/recovery, but the exact original
scheduler ordering between death and level-reset has NOT been reproduced.
OTC preserving a running buff across save/load is a portable checkpoint
contract, NOT original SVB parity or a claim that SAVE has the same meaning.

Tarn stock is an eligible resource projection at opening/current player level,
not the full original refresh timer, ownership or randomization machinery.
Original interaction radii/gates are still an independent pending boundary.
The per-command all-or-nothing restrictions intentionally block unsupported
quests/skills/services rather than invent their missing side effects.

Normal NPC offer/dialog and manager-wide automatic dependent-quest propagation
remain pending. The new controller slice proves order within the supported
explicit forced commands, not all of CQuestManager::questEventUpdate.

The common service/skill scenario creates an Alchemist normally, then a named
test fixture awards source-graph XP to level 10 and supplies gold. It does NOT
inject skill ranks/effects, NPCs, purchased equipment or quest completion. It
verifies shop input, investment, clip HIT, finite bonus, pause, OTC roundtrip
and expiry in the shared application. This is not a campaign playthrough or
an original-process behavior trace. Native economy comparison uses the actual
buyPrice/sellPrice instructions with TWO explicit external-call stubs (player
lookup and effect sum); graph computation and merchant UI are tested separately.
