# Equipment price and missile firing: executed comparison evidence

Existing game bodies are unchanged: `CEquipment::recalculatePrice()` at
`0x883e20` (1949 original bytes) and `CEquipment::fireMissiles()` at `0x87f120`
(1881 original bytes). These are evidence upgrades, not newly written bodies
or claims of byte-for-byte MATCH.

## Preparation and source review

Owner `dot` verified. `llm_loop.py --prepare-only` recognized both existing
bodies without invoking a model. A fresh strict price packet was complete.
The missile packet initially refused unknown OGRE data declarations.

Added only the exact pinned `Ogre::Math::POS_INFINITY` (Real, four bytes) and
`Ogre::Vector3::UNIT_Y` (twelve bytes) declarations. Identity requires the
original ELF OBJECT symbols, matching COPY relocations, size/binding/section,
pinned header contents and float ABI. `OgreMath.h` SHA-256 is
`01516be146b17a6a3700f2001f2f33e89953b0f738b5c23ca4475075f33b88f1`.
Header pinning now covers eight SDK headers. Interior references do not create
separate symbols. The missile strict packet then completed. No unresolved
context was accepted or bypassed. Context tests include both exact symbols,
interior offsets, wrong metadata/declarations and changed SDK headers.

Review compared ASM call/order/field behavior with the existing bodies:
price initialization, default VALUE=100, level floor, unique-before-magic
selection, ceilf conversion, gambler buy-price override and independent normal
prices; missile early guards, hand selection, target-relative normalization,
weapon-scale/model bounds, repeated model lookup, preloader arguments,
adjusted iMissile pointer, deduplication, repeated target position read,
quaternion axes, virtual equipped owner and safe-pointer registration.

## Runtime comparisons

Each function passed 9792 original-versus-replacement cases, cold and warm,
with zero differences or incomplete observations. Each measured call uses
`autotest::invoke` on the real function pointer and reports the exact original
address under its registered fixture name. Matching crashes are not evidence.

Price observes full initialized equipment/inventory/owner buffers with narrow
canonicalization of known pointers, all four price fields, level, VALUE,
callback arguments/order and callback-induced state changes. Cases include
zero/missing/negative VALUE, level boundaries, normal/magic/unique precedence,
missing inventory/owner, gambler/non-gambler and callbacks changing level,
VALUE or inventory during evaluation. Twelve separately compiled deliberate
faults all caused completed differences.

Missile observes return, callback arguments/order, launch/target/orientation,
listener identity/order/capacity, active references and safe-pointer indices,
full initialized equipment/missile buffers with narrow known-pointer
canonicalization, logical string/list values, scene positions, forward vector,
WEAPON_SCALE and bounding-box kind/extents. Cases cover early guards, left and
right weapons, no/near/coincident target, finite/null/infinite model bounds,
scale/default values, missing missile, existing/wrong-base listeners and
callback changes to target position/equipped owner. Fourteen separately compiled
deliberate faults all caused completed differences.

These are bounded collaborator-based observations. They do not establish
universal allocator failures, exceptions, arbitrary engine state or all inputs.
The missile test's first compilation used a nonexistent SDK getExtent method;
the fixture was corrected to pinned isNull/isInfinite accessors before any pass
was counted. Game implementation was not changed.

## Validation

Price isolated Stage: all 192 hybrid tests passed, including executed coverage
for 0x883e20. Both focused tests and all 26 controls passed before copying the
fixtures into the main working tree; game source hashes remained identical.
Combined current-tree check: all 192 hybrid tests passed; 1325/5247 functions
accepted (958262 original bytes), including 70 behavioral acceptances. Both
newly covered addresses are present; all prior acceptances preserved. Python
suite: 587 tests OK, one skip. The initial combined run was interrupted by
executor restart; the complete repeated run passed. No CI claim is made.
