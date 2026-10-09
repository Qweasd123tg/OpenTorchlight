# CJournalMenu::updateLayout(), 2026-10-08

Original ELF 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
Address 0xe3c460; 33545 original bytes. This reconstructs the character statistics
journal, not a speculative quest interface.

The readable C++98 candidate passes 1152 completed original-versus-compiled
comparisons, with two rebuilds per case, both standalone and in the combined
build containing CStatsMenu::update. The combined run also passes Stats' 4608
pairs, the 72 UTF-8 verifier pairs and 1800 UTF-16 mutation pairs. Stage publication completed with 157 tests and zero failures: 1175 accepted
functions, 542082 original bytes, preserving all 1174 previous addresses.
The independent repository check passed, as recorded below.

The fixture uses original CCharacter and CPlayer RTTI. Null and non-player owners
return without clearing the existing children. A valid player detaches each old
child from its actual parent, destroys it, clears/reallocates the tracking list,
then creates 40 windows, or 41 when the Hardcore heading is present. Window calls,
text, colours, alignments, parent identity, order, always-on-top, pass-through,
list count/capacity and all 28 translation caches are observed. Six menu fields,
four player-view fields and client difficulty have compile-time offset checks.

The 18 statistic rows are resolved from the original jump table at 0xffee60.
Time is ceil-rounded, split using the original unsigned arithmetic and formatted
without a space between a number and its translated unit: “0hrs 0mins 0secs”.
The numeric formatting call order is seconds, minutes, hours. Other rows read
signed counters at player+0x7dc+index*4. Difficulty values 0..3 select Easy,
Normal, Hard, Very Hard; other values retain EMPTY_WSTRING. Ancestors and the
Hardcore flag are read from the current owner, while statistics use the player
captured by the original dynamic_cast.

The matrix covers null/character/player, both Hardcore states, all four valid
and two invalid difficulty values, empty/cached/translated BMP Unicode labels,
four scales, old children with different or absent parents, changing UI pointers,
negative/extreme counters, sub-second/minute/hour boundaries and non-finite
playtime. The target is the pinned original ABI/compiler, not a portability claim
for undefined floating-to-integer cases. The same CEGUI supplementary-plane
limitation documented by the Stats update applies; uninitialized library output
is not normalized into a passing comparison.

Six intentionally wrong variants were all rejected with completed differences:
missing root move-to-back, wrong row spacing, wrong counter index, omitted mouse
pass-through, floor instead of ceil, and wrong Hard difficulty label. An initial
number/unit spacing error was also exposed and corrected.

Only authorized headless comparisons were run, exiting before game main. No
rendered UI or full-game playthrough is claimed. Original assets remain read-only.

## Final validation

The independent root tools/decomp/check.py exited 0 with 157 tests, zero failures.
Final acceptance: 1175/5247, 542082 original bytes; 1149 normalized MATCH and 26
behavioral acceptances. All 941 original baseline addresses remain accepted.
The root tooling suite ran 442 tests: 441 passed, 1 existing Ghidra/Java skip.
Upstream aa472cf8982c0efcb89fbf7203ba64f2e2cfacce was preserved through a clean
three-way merge of 19 files. Every fetched file matches its canonical Git blob
hash. No candidate code from the upstream Luna pilot was installed.
