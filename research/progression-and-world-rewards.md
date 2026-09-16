# Progression and world rewards — large-8 continuation

## Inputs and evidence boundary

Source ELF SHA-256: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`,
original `pak.zip` SHA-256 `8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`.
The large-8 authoring pass saw only targeted exports and authored fixtures.
This pass also ran on a machine with both originals present read-only: focused
disassembly and the scalar reference below were checked against them.

* `original-code`: `CMasterResourceManager::experienceGate` @`0xa549d0` returns
  zero for level zero, clamps to graph control-point count, evaluates
  `EXPERIENCEGATE` at the level, and truncates to int. `getMaxLevel` @`0xa549c0`
  uses that point count, not the last X coordinate.
* `original-code`: `CPlayer::calculateMaxHP` @`0x8e4f80`, `calculateMaxMana`
  @`0x8e4d60`, stat points @`0x8e4f00`, skill points @`0x8e4e80` evaluate their
  configured graphs and use ceil. UNIT graph keys/defaults are in `player.c`.
* `original-code`: `CCharacter::awardExperience` @`0x822850` adds a ceil bonus
  from effect `0x44`, clamps the signed XP accumulator and tests the current
  level's gate. `CCharacter::levelUp` @`0x822e10` refills HP/mana and awards
  points for the NEW level. `CPlayer::levelUp` @`0x8f9ad0` failed decompilation:
  the portable repeated-level loop and single-player attribution are `inferred`,
  NOT a verified port of that override, parties, pets, or champion/fame rewards.
* `original-code`: ordinary monster reward = `trunc((g / 100) * g)` where `g` is
  `EXPERIENCE_MONSTER[_difficulty].getValue(unit level, 0)`.
  `CCharacter::setLevel` @0x83ecdd..0x83ecfd emits `cvtsi2ssl level; call getValue;
  movaps; divss [fa483c=100.0f]; mulss; cvttss2si; mov [this+0x454]`. The earlier
  Ghidra output `(fVar23 / DAT_00fa483c) * fVar23` is faithful, not corrupted: the
  second operand is the same graph value, not `UNIT.XP`.
  `CCharacter::makeChampion` @0x85191b..0x85192e repeats the identical scalar for
  `EXPERIENCE_CHAMPIONMONSTER[_difficulty]`.
  The unit data `XP` field is only a nonzero gate: `CCharacter::unitInit`
  @0x852c48 stores it in +0x454 and then invokes the virtual setLevel (slot
  +0x318 @0x852b50); setLevel overwrites +0x454 only when it was nonzero.
  `CCharacter::awardExperience` @0x822850 receives victim +0x454 and adds the
  `ceil(amount * effect0x44% )` bonus. Missing graph => unknown reward, never an
  invented constant. Only Normal difficulty is supported by the application.
* `original-code` bounded: `tests/compare_monster_experience.py` executed the
  unchanged span `0x83ecea..0x83ecfd` (digest `9aa637a7...`) and matched
  `original_monster_experience` on 20 031 scalar cases; `--original` re-checks the
  SHA-pinned ELF and the `100.0f` divisor. This is a scalar formula check, not a
  whole `setLevel`, spawner or award-flow test.
* `original-code`: `CItemGold::unitInit` @`0x8ca940` reads MINVALUE/MAXVALUE (defaults
  100), samples the volatile random source, and calculates
  ceil(GOLDDROP(rank+1) * (sample/100)). The unchanged numeric span
  `0x8cad46..0x8cad5b` is suitable for bounded differential execution; see
  `tests/compare_world_gold.py`. Invalid/out-of-int32 values are rejected before
  a C++ conversion (portable safety boundary).
* Correction to earlier notes: the pointer reached via resource-manager +0x18
  is CLevel, not CGameClient. The gold graph coordinate is CLevel+0x1a8 plus one.
  CLevel construction initializes +0x1a4/+0x1a8 from its final int argument.
  Mapping that rank to the portable world's spawn_level-1 is `prototype`, not
  proven dungeon-rank propagation. The world still supports Normal only.

## Portable policy, not claims about the original UI/save format

Rules are immutable and shared; state belongs to PlayerSession, not a floor.
Graph lookup is case-insensitive by basename below media/graphs, rejects
ambiguous names, and does not substitute guessed graph values. This is a
bounded resource resolver, not a reproduction of all CGraphManager behavior.
Stat points are spent one-for-one with explicit portable validation; only the
existing physical STR/DEX/DEF consumers are wired. MAGIC is retained, not
advertised as a working spell system. Skill points are stored but cannot yet be
spent. No active skills, fame, timed effects, regeneration, or projectiles are
implemented by this pass.

Only a lethal player CombatController HIT sets player credit. Script kill and
spawn destruction do not. Each entity stores its resolved XP/gold and consumed
reward state. A dead player cannot defer a positive reward until recovery.
Gold moves to the saturated wallet, never into an equipment slot. Zero-value
piles remain valid pickups. Restore never rolls either amount again.

Checkpoint v2 preserves these fields. v1 decode is explicitly retained: absent
progression starts at level one, old entity reward values remain unknown, and
old corpses are never retroactively rewarded. v2 state is validated against the
current class graphs before commit; player/floor restore remains transactional.
The fixture `tests/fixtures/checkpoint-v1.hex` was generated by the unmodified
large-7 save writer using its authored frontend fixture before codec changes.
