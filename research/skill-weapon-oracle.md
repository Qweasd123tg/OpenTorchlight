# Skill weapon arithmetic: original-execution pilot

Source: `original-code`, external Linux ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

This experiment extends the existing `tests/native_typed_reference.py`
fixture, rather than writing a second transcription of the algorithm.
The original `CCharacter::rollAttack @0x843ed0` executes through damage
channel assembly; the existing interception at `0x844d98` captures ordered
channels, maximum, roll, applied damage and final volatile RNG state.
Constructors, effect getters, weapon/type selection and critical=false are
controlled inputs. HP, skill activation, procs and graphics are outside it.

## Inputs and branches

- First float argument: weapon fraction, saved at `0x843efa`.
- Second float: soak multiplier, saved at `0x843f00`.
- `flags & 0x400`: USEDPS. Speed is `attackDesc+0x70` (`0x844157`).
- Percentage branch `0x845338`: multiply and truncate, entered when the
  fraction differs from **1**, not from zero (`0x844150..0x84416c`).
- DPS branch `0x84530f`: `ceil(maximum / (speed * k))`, with exact
  `k = 0x1.777778p-1f`, bits `0x3f3bbbbc` at `0xfce530`.
  Decimal `0.7333333f` selects the adjacent float and is NOT equivalent.
- Both return to `0x844180`: recompute minimum as
  `ceil(new_maximum * 0.5f)` before the original RNG call at `0x8441dd`.

- Bonus percentage branches `0x8442bc` / `0x844738`: scale raw bonus before
  attribute/effect enhancement. A zero raw bonus with positive flat effect is
  still a channel; the original presence gate precedes scaling.
- DPS on bonuses: the total-maximum pass `0x8444e2..0x84451e` adds the flat
  effect AFTER DPS, but the roll pass `0x844958..0x844995` adds it BEFORE DPS.
  Thus total maximum is not always the sum of rolled-channel maxima. Keep the
  original distinction for the mitigation denominator.

## Measured result (2026-09-19)

Against the pre-change port at `279c0f2`, the first deterministic suite had
**1216 mismatches / 1478 cases**. Base=100, percentage=40, speed=1, DPS=false,
seed=1, no effects/defense:

| Value | Original | Previous port |
|---|---:|---:|
| maximum | 40 | 40 |
| rolled / applied | 23 / 23 | 50 / 50 |
| final RNG | 695696193 | 1 |

The implementation had four independent mistakes: zero percentage skipped
scaling; minimum stayed unscaled; bonus channels skipped percentage/DPS;
DPS constant lost a float bit. Base=99, percentage=100, DPS=true, speed=1
exposes the latter: original maximum **135**, previous constant gives **136**.

After correction and production integration: **2126 / 2126** comparisons pass
(including 600 flat-bonus/DPS and 48 single-left-hand cases), about 0.3 seconds
locally excluding build. Compared:
channel count/order, maximum, rolled/applied totals, per-channel applied
values, final RNG. Existing **12088** allocation/MAGIC/defense/ordinary
comparisons also pass; the shared ordinary path is unchanged numerically.

Final input SHA-256:
`5ebd48d94b3c821a5db71596082b8f02e56de64b6b5e5547f2db371ade9b76f1`;
original-result SHA-256:
`2f17449315b03fb7701bf3cb495e70ec554de7c171ca6221863875af95bf2023`.

Comparison domain: finite nonnegative percentages, positive finite DPS
speeds when enabled, bounded int32-safe damage/effect inputs, one selected
right- or left-hand weapon. Left-hand fixtures select inventory slot 1,
getWeaponInLeftHand and equipment+0x2a8; right-hand baseline stays unchanged.
Caller selection and resource-to-speed mapping have separate static evidence
in [production dispatch](skill-production-dispatch.md), not in this numeric
oracle. Full performAttack flags and full skill-event execution remain open.

Reproduce with `tests/compare_skill_weapon_damage.py --original <ELF>
--probe <build>/torchlight_typed_damage_probe --output <report.json>`.
CTest name: `original_skill_weapon_damage_comparison`, label `reference`;
included by `tools/check.sh --reference <ELF>`. The subsequent production
tranche connects this arithmetic to a request-driven HP sink; `compared` is
still this bounded arithmetic, not whole rollAttack or full SEEKING parity.
