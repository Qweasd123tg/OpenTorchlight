# Player vitals: static reconstruction and boundaries

## Inputs and claims

The working baseline is **OpenTorchlight-gpt-pro-fresh.zip**, not large-10.
The supplied full-disasm bundle declares original ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Its objdump text has addresses and instructions but no machine-code bytes or
`.rodata`. Bounded exports and their hashes are in
`disassembly/vitals-static/manifest.json`. No original ELF was executed.
No real pak was available in this pass. Authored fixtures are not original
resource measurements.

## Restored arithmetic (`original-code`, static evidence)

* `CCharacter::maxHP @0x813e60`: ordinary, unowned character: integer base plus
  integer growth, clamp base to at least one, then
  `base + ceil(float(base) * (effect(0x14)/100)) + ceil(effect(5))`.
  **Division precedes multiplication for HP**, unlike maxMana @0x813a10.
  Owner bonus `effect(0x68)` belongs to a pet/owner lifecycle not implemented here.
* `CCharacter::updateMana @0x815c90`: states 5/6 excluded,
  `modifyMana((float(maxMana)/100) * globals.MANA_RECHARGE_RATE * dt)`, then
  `modifyMana((effect(0x7b) + effect(6)) * dt)`. The two clamps are distinct.
* `CCharacter::updateHP @0x83d930`: normal non-pet branch uses
  `HP_RECHARGE_RATE` similarly, followed by effect rate times dt.
* `CCharacter::getEffectValuesOfDamage @0x816d70`: positive effect(0x34) is
  negated; signed rate is `effect(0x7c) + effect(7) + damage`.
* `CCharacter::modifyHP @0x838a50` has a no-partial-revival gate at
  0x838c70..0x838c9c: after reaching zero, a positive source below the entire
  maximum is rejected. `advance_health` retains this between its two sources;
  the player lifecycle independently skips all regeneration while dead.
  Owner/pet/invulnerability/attacker-side branches are not reproduced here.
* `CGameGlobals::reload @0xa4efdb..0xa4f0cb` loads `HP_RECHARGE_RATE`,
  `PET_HP_RECHARGE_RATE`, `MANA_RECHARGE_RATE`.
  `CMasterResourceManager` constructs globals from `media/globals.dat`; the
  compiled archive input is `media/globals.dat.adm`, root `GLOBALS`.
  The percentage divisor 100 is independently byte-exported in
  `original-combat-inputs.json` at 0xfa483c.

## Supported runtime domain

Finite, constant, passive effects accepted by the existing strict effect loader
are combined from the class and equipped items. Missing globals/rates stay
optional/unknown: no invented recharge defaults. Zero explicitly means zero.
The same `application.cpp` loop advances recovery for desktop and scenario
hosts. Inventory clocks now use the addressed original side-coverage predicate
in [ui-game-pause.md](ui-game-pause.md); death overlay timing remains a prototype.
Dead players do not regenerate or revive; recovery-at-entry remains explicit.
The pure numeric step supports signed rates and clamps each source separately.
Periodic player damage does not add the original attacker XP/fame credit system.
No claim is made about pet regen, owner effects, temporary effects, bosses,
consumables, skill regeneration, or full original frame scheduling.

## Save migration (portable format, not original-code)

Checkpoint v3 stores pre-effect base HP separately from the derived maximum.
V1/v2 ignored maximum-HP effects; their old maximum is the migration base,
validated against the level graph where available. New maxima are then derived
exactly once from the equipment. Current HP is preserved and only clamped when
the new maximum is smaller; loading must never refill a damaged character.
V3 validates its derived maximum against the stored base and current effects.
An old DTO decoded and directly re-encoded without constructing a session may
still have no `base_health` even under header v3. Absence is an explicit pending
legacy-migration marker; it is resolved only when a player session is restored
and recaptured. New session captures always write the integer base. The old
1e9 scalar checkpoint limit is unchanged. Integer base HP is not reconstructed
from a rounded float maximum when the explicit field is available.

Frozen v2 fixtures for levels 1 and 3 were created by compiling
`tests/fixtures/vitals-v2-writer.cpp` against the **unchanged fresh** library.
Its static assertion requires version 2. The writer is not compiled as part of
the new build; hashes and provenance accompany the two hex fixtures.
`vitals_fresh_process` also starts independent current-code writer/reader
processes. These are port-save tests, not original SVB compatibility.

## Why consumables are not declared complete

`CEquipment::useOnTarget @0x86e910` consumes a use/stack only after an effect
is accepted; `CBaseUnit::dontUseOnFull @0x804f50` reads `DONT_USE_ON_FULL`.
Timed regeneration differs from passive rates: `CEffectManager::getEffectValue`
multiplies finite-duration types 6,7,0x7b,0x7c by `.rodata` at **0xfa86dc**.
This value is not present in the supplied disassembly or existing constant
exports. It is **not assumed to be 0.5**. Effect value graph evaluation, timer
phase, use counters, activation conditions, and stack rules must be recovered
before enabling actual potions. The original ELF plus pak are the next inputs.

## Verification in this pass

The baseline fresh core run passed 44/44; the updated core run passed 49/49,
with no skipped tests. Eleven selected C++/subprocess checks passed under
AddressSanitizer and UndefinedBehaviorSanitizer. Groups overlap; counts are
not additive. The new numeric tests use authored expected values and operation
order discriminators, **not calls into original maxHP/updateHP machine code**.
Original assets, new original-function parity, full-scene rendering and desktop
were not run. Existing core Mesa UI checks are not a whole-game rendering test.
See `../verification/large-11/` and `../PLAYER_VITALS_RESULT_RU.md`.
