# Finite consumable recovery — large-12

Inputs: Linux x86-64 ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`;
pak SHA-256 `8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`.
Original inputs remain external and read-only.

## Original-code / resource-derived

* `CEquipment::canUseOnTarget` 0x86e710 and `useOnTarget` 0x86e910:
  require a usable target, level, remaining uses, and at least one applicable
  effect. No accepted effect means no debit. Stack >=2 decrements the stack;
  otherwise uses decrements except sentinel -9999; exhausted item is removed.
* `CCharacter::isEffectValidForUnit` 0x813f20: positive recovery potion effects
  6,7,123,124 with DONT_USE_ON_FULL are rejected when integer current HP/MP is
  already at maximum or an active effect has the same name. A mixed potion
  can still apply its other valid component.
* `CEffect` constructor/init: LEVEL defaults to zero, USEOWNERLEVEL=false.
  This is not the item's LEVEL. LEVEL_REQUIRED defaults to zero on equipment
  (0x880058); potion level is not an inferred player-level requirement.
* `calculateBaseValue` 0x7dc9f0: MAX=0 uses MIN. A constant graphed effect is
  (raw / 100) * graph(effect level), with default modifier one. Catalog graph
  and GRAPHOVERRIDE/NOGRAPH determine whether the graph is applied.
* Finite recovery accumulation (`CEffectManager`, `getEffectValue` 0x7eb5f0)
  multiplies the evaluated value by float at 0xfa86dc: bytes `6f12833c`,
  exactly the binary32 representation of 0.016f. It does not divide by duration.
* Actual catalog has 145 effect slots. Types 6/7/123/124 use the corresponding
  MANA RECHARGE, HP RECHARGE, MANA RECHARGE PLAYER, HP RECHARGE PLAYER records.
  Twelve actual recovery potion definitions fit this supported boundary.

## Portable behavior, not an original parity claim

The runtime clips integration at timer expiry, uses simulation (not wall-clock)
time, and preserves evaluated amounts and remaining time in OTC v4. Pausing,
loading, inventory opening and frame size cannot grant an extra full duration.
The complete original update-effects scheduler, all float operation ordering,
original SAVE semantics, original inventory capacity/layout, and original save
format are not claimed recovered. Death removes pending recovery; it does not
revive. Q/E and inventory Enter are explicitly port controls.

Only positive, constant, finite DYNAMIC recovery is enabled. Random magnitudes,
conditional effects, timed buffs, active skills, instant consumables and other
unrecovered descriptors are rejected without consuming the bottle. Supported
components are not applied from an otherwise unsupported item.

Tests cover the actual resource catalog and authored end-to-end spawn, pickup,
stack merge, partial/full stacks, use, pause, same-name blocking, mixed recovery,
level rejection, death, expiry, corrupt state rejection and independent-process
save continuation. Native original-instruction comparison is recorded separately
in the final verification; merely reading this evidence is not an oracle run.

## Executed bounded original comparison

`original_gameplay_numeric_comparison` executes the original bounded
`getEffectValue` instructions with synthetic effect-manager records and original
constants. 10,040 cases across types 6/7/123/124 match the portable binary32
result exactly. This does not execute the full original update-effects scheduler,
owner/cache lifecycle or save implementation. The same test's population part
is described in `population-evidence.md`. The original SHA is checked first.

When a non-PIE Python occupies the original address window, the reference runner
uses an explicitly selected PIE launcher. `tools/testing/build_pie_python.py`
builds one from the installed Python development files; no address collision is
ignored, no existing mapping is overwritten and no SKIP is reported as PASS.
