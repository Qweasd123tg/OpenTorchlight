# Equipment prices

Original recalculatePrice(), 0x883e20, 1949 bytes. Fixture: 4896 cases twice per
side, real DataGroups and controlled graph/type services. Captures include
curve names, ordering, evaluated x/line, prices observable during callbacks,
final four price fields and level/inventory state. Base matrix independently
crosses rarity flags, six VALUE/default cases, six levels, four inventory/owner
states and eight curve-value patterns. Callbacks modify data/level, install or
remove inventory between curve evaluation and the late gambler check.

Original behavior retained:
- Reset buy/sell fields264/268 to1 before reading VALUE(default100). VALUE0
  returns without resetting normal/base fields26c/270.
- Snapshot max(item level,1) and VALUE. UNIQUE takes precedence over isMagical.
  Resolve both rarity curves, evaluate both, then write both prices.
- Late inventory owner GAMBLER check replaces buy only with the gamble curve.
- Resolve/evaluate normal curves again to fill26c/270 regardless rarity.
- Float32 value/100, then multiplication, then ceilf. Negative prices are not
  clamped. Reordering multiply/divide changes answers: VALUE1 and graph float
  0x42c80001 (100.00000762939453) distinguish1 from2; the fixture includes it.

24/24 sampled viable and20/20 targeted mutations killed, including rounding
and float operation-order faults in all four result fields. Exceptional or
nonfinite/overflow curve outputs and graph loading itself are outside scope.
