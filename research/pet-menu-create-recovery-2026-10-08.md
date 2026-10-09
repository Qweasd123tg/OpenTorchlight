# CPetMenu::createMenus, 2026-10-08

Original ELF 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
Address 0xb93350; 30488 original bytes. Full readable C++98 reconstruction of
pet-menu creation, including its model, layout, equipment and backpack overlays,
spell bindings, wardrobe camera and skill tooltip. No renderer is started.

## Evidence and observations

The first passing full-entry fixture compares 4704 original/compiled pairs.
The matrix crosses seven resolution values per axis, eight Y ratios (including
signed zero, infinities and NaN), replacement settings objects and six equipment
name/availability patterns: ordinary, empty, alternating, non-ASCII byte names,
all equipped windows absent, or one absent. Original ELF-local equipment names
are initialized at their verified Pet TU address 0x14cc220. Input files stay
read-only; this is isolated process memory, not a patched original on disk.

The fixture observes ordered collaborator calls and arguments, actual handler
member pointers including this-adjustment, event connection reference lifetimes,
window hierarchy/flags/user data, all slot arrays, original/default/tab strings,
stat-window identities, GUID/index initialization, camera settings and skill-tooltip construction. File lookup, layout loading, resource/model creation,
mesh, camera, window and event collaborators are intercepted before invoking the
actual original and compiled entry. Failed redirects abort the fixture.

Forty-five original field offsets plus size 0x9620 are checked with the pinned
compiler, and are asserted inside the reconstructed method. The two spell
windows occupy 0x1040..0x104f. The five 82-entry slot arrays start at 0x1378;
the default strings start at 0x2048 and 0x58a8. Nine stat widgets span
0x9118..0x9158; their search order is name, level, XP, HP, mana, melee, ranged,
magic, defense. No arbitrary fields or mechanics are invented.

The existing Inventory reconstruction helped navigate the similar code, but
several Pet differences were proven against ASM and exposed by comparisons:
negative model horizontal scale; a missing-equipped-window guard; two calls to
moveToFront around equipment-event binding; reversed icon/socket layer offsets;
different overlay parents and always-on-top behavior; only two spell windows;
no Money or WeaponSwitch lookup; PetWardrobeCam. The original repeats setID
for each spell window. The model uses generateExtremes(5,true), bounds of
plus/minus 100000, and a camera at (0,1,3.5), looking at (0,1,0), clips 0.1/20.

## Limits

Controlled headless differential testing does not establish full-game playability
or every possible allocation/exception path. Non-finite numeric cases compare
the pinned original ABI, not portable language semantics. Byte MATCH is not
claimed. The separate prepare-only packet was blocked by missing indexed
implicit-destructor, initialized-array and SDK declarations; its exit code was
not treated as readiness or acceptance. This reconstruction used direct original
ASM review, not an incomplete model-generated packet.

The strengthened fixture also passes all 4704 pairs, including top-level window fields.

## Final validation

Stage publication and the independent root tools/decomp/check.py both pass:
160 tests, zero failures, exit 0. Acceptance is 1177/5247 functions, 606028
original bytes: 1149 normalized MATCH and 28 behavioral acceptances. This adds
one address and 30488 bytes to the previous 1176-function result. Seven negative
controls were rejected with completed differences. No remote push was performed.
