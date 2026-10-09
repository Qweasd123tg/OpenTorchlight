# CPetMenu::updateLayout(), 2026-10-08

Original ELF 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
Address 0xba26b0; 10957 original bytes. Complete readable C++98 candidate for
pet equipment, socket-gem, spell and backpack layout. The accepted Pet creation
and update source bodies are preserved exactly as the candidate's source prefix.

## Differential evidence

Three full-entry fixtures complete 4768 original/compiled pairs with no
incomplete comparisons: 3840 empty/backpack cases, 864 equipped-item cases and
64 spell cases. Spell cases run two frames. The final passing standalone run is
r4; all eight intentionally wrong variants produce completed differences.

The matrix covers absent owner, closed menu, absent inventory, zero/one/two
children, missing equipped windows, list count/capacity fallback, selected panes
-1..3, reentrant inventory changes, zero/one/two gems, identification, icon reuse,
creation success/failure, parent visibility, ordinary/unique/magical categories,
spell presence/empty icons, and empty/repeated/BMP translations. Window, image,
icon, inventory and slot-rendering collaborators are controlled. No rendered UI
or actual file/audio/input activity is invoked by these fixtures.

Observations include call order, arguments, window identities, child counts,
parentage, icon size/position, properties, tooltip text, GUID/user-data bindings,
and repeated-frame cache behavior. The inventory callback changes current pane
and list capacity: the caller retains the previously captured item but reloads
the slot reference after getItemPane. A detach callback reparents a gem into the
socket layer, exercising both outcomes of the subsequent isChild query.

The eight negative controls are: removing all equipment-slot children rather
than one; ignoring the selected pane; using a stale slot reference; newline
instead of space between spell tooltip fragments; processing only one spell
window; omitting child-membership checking; the wrong icon reset position; and
raising the wrong final layer. All failures are completed differences, not just
compiler errors or interrupted runs.

## Original details retained

The guard checks owner, open state and inventory. All children of the socket
parent are detached, but only one child per equipped slot is removed. The order
is equipped slots, two spell windows, backpack clearing, filtered inventory refs,
then final layer ordering. getItemPane must match the integer at menu+0x6c.

The three spell translation caches are std::string values created by
StringConvertToNarrow. Removal-tooltip fragments are joined with a space, unlike
InventoryMenu's newline. Empty spell handling clears Image, assigns NoSpell user
data, then sets the tooltip. Existing gem membership is checked after detaching,
so an event callback that reparents the gem does not cause duplicate attachment.
The final raised socket overlay is at 0x40, not the icon layer at 0x38.

An equipped-icon difference was exposed by the first comparison: Pet first sets
position (0,1), then resets (0,0), and only afterward obtains the slot size and
sets height to width*1.5. It does not use InventoryMenu's vertical-centering step.
That copy-derived error was corrected against instructions 0xba3cce..0xba3d9d.

## Limits

This is behavioral comparison under controlled collaborators, not normalized byte
MATCH, complete UI rendering or proof for every possible input/failure. The
original setSlotIcon method remains a collaborator; this does not claim that its
body has been newly restored. Original ELF and assets remain read-only. No game
window or full-game playthrough is claimed.

## Validation scheduling

The validation queue now uses 60 modulo shards, still at six concurrent workers
and the same six self-test resource slots. All test names were audited: the
161-test Pet-update runs retained all 160 previous names and added only the new
fixture. No test or acceptance gate was removed. Observed stderr lifetimes for
the prior 6-shard Stage/root runs were 935/884 seconds; the subsequent 60-shard
Stage/root runs were 649/616 seconds. These are successive 160/161-test revisions,
not a controlled A/B or a guarantee for another machine. Timing uses filesystem
birth-to-last-flush intervals, at one-second resolution, for one run per blob.

The reproducible configuration is OTL_JOBS=6, OTL_SELFTEST_SHARDS=60 and
OTL_SELFTEST_TIMEOUT=1800; the existing resource-slot limits remain in force.
Compilation time is not included in those self-test intervals.

The full Stage and independent repository check passed, as recorded below.

## Final validation

Stage publication and the independent root tools/decomp/check.py both pass:
164 tests, zero failures, exit 0. Acceptance is 1179/5247 functions, 643054
original bytes: 1149 normalized MATCH and 30 behavioral acceptances. This adds
one address and 10957 bytes to the previous 1178-function result. Eight negative
controls were rejected with completed differences. No remote push was performed.
