# Equipment eligibility (recovered again after workspace replacement)

- `canEquip`, 0x86f150, 513 original bytes: 6,939 differential cases, two calls
  per side. All 23 targeted mutations are killed.
- `canUseOnTarget`, 0x86e710, 506 bytes: 8,192 differential cases, two calls per
  side. All 23 targeted mutations are killed.

Both sides must exit normally and produce identical traces and final sampled
state. There is no acceptance of paired crashes. The test directly qualifies
`CEquipment::canEquip` on its raw fixture so a missing fixture vtable does not
turn the recovered call into an unrelated virtual-dispatch failure.

## Boundaries exercised

Equipment eligibility checks merchant/stash, player-owned pets, category
filtering, identification, signed level and four signed stat comparisons.
Level is captured before requirement callbacks; a nonzero level requirement
causes a second query. The opaque Character flag at 0x4a0 is re-read between
stat checks. Its gameplay name is deliberately not invented. Thresholds,
negative values, integer extremes, category combinations and flag/level changes
inside callbacks are included.

Use eligibility exercises positive/zero/negative charges, Character versus
non-Character/null targets, target-level versus caster-level selection,
dynamic effect traversal, list-capacity fallback, owner/effect arguments,
all-validity-call behavior, busy targets, skill failures and callback-driven
skill-manager/list changes. Pet-only and no-pet items are tested independently.
Null targets are used only with empty effect lists, matching the original's
precondition for its virtual target calls.

Services are controlled spies. The real RTTI machinery and TArrayList storage
are used; this is not a live combat or UI test. See the two fixtures and the
standalone mutation scripts for the exact covered inputs.
