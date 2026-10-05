# Equipment proc execution

Original executeProcs(CCharacter*,EEFFECT_TYPE,CBaseUnit*) is0x86f4a0/561 bytes.
The fixture compares9284 cases, twice per side, with real Ogre parent/node
transforms and forwarding calls to the original getPosition(bool). Effect
presence/value, random draws, skill lookup and execution are controlled services.
The explicit final132 cases independently cross all six draws and eleven
chance values, with and without a target, while ensuring the execution gates
are active. A fourth populated list detects an extra activation iteration.

The original uses absolute target and caster positions but the node's LOCAL
orientation. An initial implementation mistakenly used derived orientation;
case1224 with a rotated parent exposed different quaternion components. It was
corrected before acceptance. The original Ogre vtable slot0xc8 is getOrientation,
not _getDerivedOrientation. This is deliberately not "fixed" into a uniform
coordinate convention.

Another decompiler trap: Ghidra expresses the skip as chance<draw, which would
let NaN proceed. Actual UCOMISS/JB skips unordered as well: the positive branch
must be chance>=float(draw). Equality succeeds; NaN fails. The deterministic
draw fixture does not assert a statistical probability distribution for the
external random generator.

Tests cover all three activation lists, matching/nonmatching effect types,
missing skills/managers, target fallback, strict/equal/NaN boundaries, callback
entry replacement, count growth, manager replacement between groups, late skill
manager reads, list-capacity fallback and orientation reference aliasing across
the caster-position callback. External skill mechanics remain outside this
method's acceptance scope. No rendering or game-main loop is run.

Final fixture:12/12 viable sampled and22/22 targeted mutations killed.
