# JournalMenu remaining controls, lifetime and update

Restored nine original entries (3369 original bytes). Strict machine MATCH:
setOwner 0xe332a0, close callback 0xe332b0, mouse-through callback 0xe332d0,
processInput 0xe332e0, deleting destructor 0xe39f10, and setOpen 0xe3a680.
Constructor 0xe3c070, complete/base destructor 0xe39e60 and update 0xe3a180
remain DIFF and are accepted only through fresh original/candidate comparisons.
No acceptance or normalization rule was changed.

Fresh prepare-only packets cover all eight selectable entries; C++ generates
the deleting-destructor entry. Layout is checked through size 0xa8: parent +0x10,
owner +0x30, open/closed/input flags +0x38/+0x39/+0x3a, settings +0x40,
UI +0x48, model +0x58, resource manager +0x60, edges +0x70/+0x74,
sound bank +0x80, cached seconds +0x88, children array +0x90. The array grows by
10 (the generic container default of 2 does not match this constructor).
JournalMenu friendship exposes the existing model skeleton field without adding
an invented accessor or changing object layout; packets were refreshed afterward.

## Runtime evidence

Constructor: 64 completed equal cases cover all 16 missing/present sound masks,
two byte patterns and two collaborator-identity profiles. Exact string keys are
INVENTORYOPEN, INVENTORYCLOSE, POINTASSIGN and ASSIGNSKILL; sample IDs 22,66,27,30.
The two singleton lookups, allocation/bank arguments, full object plus canaries,
sound-bank contents, width/height reads and create call are observed. Alternate
callbacks replace sound-bank/settings identities. Thirteen fault sites across
both profiles/patterns give 52 matching expected unwinds, excluded from normal
completion acceptance. Original partial-initialization/cleanup behavior remains.

D1 and D0: 32 completed comparisons each cover null/present model and bank,
four empty/nonempty child-array shapes and callbacks replacing the owned pointers.
Capture includes deletion order, conditional clearing, child-array release, actual
base-destructor transition into a controlled core, complete bytes plus canaries,
and deleting-destructor deallocation. Sixteen expected exception unwinds are
checked separately. Pointer-array deletion does not delete its Window elements.

Update: 1536 scenarios of two frames each cover all four open/closed combinations,
cached/changed played time, finite/negative/fractional/large/NaN/infinite values,
playing/queued animation combinations, two geometries and callback mutations.
Settings, skeleton/bone lookup, model and derived positions, scaling, window
positions, layout updates, visibility and parent removal are captured in order,
as are full menu/canary bytes, actor states and floating-point exception flags.
All six branch witnesses were reached. The original converts ceilf to signed
64 bits and retains the low 32 bits: invalid conversion therefore stores zero,
not INT_MIN, while raising FE_INVALID. This is preserved without undefined
out-of-range C++ floating conversion.

Ten independently compiled intentional defects are caught by completed differences:
array growth, sample ID, omitted height read, uncleared model, uncleared bank,
invalid-conversion value, invalid flag, time rounding, panel-Y sign and cache-write
order. The final clean candidate passes all six focused tests again. These are
bounded collaborator-based runtime comparisons, not a proof for arbitrary engine
state or interactive rendering.

## Integration and resource recovery

The first aggregate assembly attempt stopped because the workspace disk was full;
no test/acceptance result was claimed from it. Four old, completed skill-task cache
trees were compressed reversibly with decompressed size/SHA256 verification and
source-preservation checks, freeing 2480933770 bytes. The same current candidate
Stage was resumed; its source was not changed to work around the failure.

Normal Stage.validate passed all 214 headless tests, enforced prior acceptance
preservation, and Stage.publish atomically verified current-root object identities.
An independent root check.py also passed all 214 tests. Exactly these nine entries
are added; all previous accepted addresses remain.
Pre-PR48 total: 1373/5247 functions, 991196 original bytes, 1288 MATCH and 85 behavioral.

After PR48 merged, the single JournalMenu commit was rebased onto main
96fca7c4c29feb28ca4d023bc9db5d616322c04e (tree
3316c8bbdff5f1031154def4603ea4d96ab2c755). The combined root check passed
all 215 tests, retaining every PR48 and JournalMenu accepted address.
Combined total: 1374/5247 functions, 991426 original bytes, 1288 MATCH and
86 behavioral. GitHub CI is not configured; these are completed local checks.
All measured CJournalMenu member addresses in this TU are accepted; aliases are
not double counted. A standalone rebuilt game and interactive UI were not tested.
