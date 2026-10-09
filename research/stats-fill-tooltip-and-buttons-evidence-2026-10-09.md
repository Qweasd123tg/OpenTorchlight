# StatsMenuFill tooltip and button slice

Restored five measured entries (2282 original bytes):
- calculateMouseOver, 0xc20dc0, 1909 bytes: behavioral acceptance.
- handle_onMouseUp, 0xc18890, 79 bytes: byte-MATCH.
- getStatBarTotalAmount, 0xc18cc0, 124 bytes: byte-MATCH.
- handle_AddToStat, 0xc18b80, 85 bytes: behavioral acceptance.
- handle_RemoveFromStat, 0xc18be0, 85 bytes: behavioral acceptance.

The misleadingly named calculateMouseOver updates the four stat-slot tooltips.
It captures each window before collaborator calls, uses the player's corresponding
base stat plus one (or one without a player), and retains original text, including
capitalization and newlines. Text was read to the terminating wide NUL directly
from the pinned original ELF. The source reuses the existing named player view.

Mouse release clears eight held flags, the float at +0x168, and the flag at
+0x190. The cost getter preserves invalid-stat handling and calls the graph at
+0x170 with float(base stat)+1 and line zero. Three view offsets are asserted.
The add/remove callbacks find the first matching event window by list count,
set the corresponding held flag only on a match, and always return true.

Strict prepare-only packets for the large entry and four companions were
complete before implementation. No ABI declaration was guessed from a name.
The float at +0x168 was also confirmed by its addss/movss use in update.

## Executed observations

Tooltip fixture: 540 completed original/candidate comparisons, zero differences
or incomplete observations. It covers absent/present/replaced players, distinct
signed stat values up to INT_MAX-1 (increment stays defined), capacities zero
through four and differing counts, first-element fallback, window-list mutation,
Unicode and embedded-NUL collaborator strings. Complete menu/player/window data,
collaborator order/arguments and resulting tooltip UTF32 codepoints are compared.

Button fixture: 120 completed comparisons per callback, zero different/incomplete.
Cases cover empty lists, all valid counts, first/later/absent/null windows,
duplicated windows, independent existing held flags and capacity/count differences.
Both sides receive a pointer to the same correctly constructed WindowEventArgs
object using its reference ABI; no EventArgs copy or slicing occurs.

Seven separately compiled tooltip defects and four button defects were detected
by completed differences. The final unmodified combined candidate passed both
fixtures again (780 total completed comparisons). These are bounded controlled
collaborator observations, not exhaustive exception or arbitrary-memory proofs.
The callback candidates retain a small code-generation DIFF; no assembly or
register pinning was used to force them into MATCH.

## Final gate

Current-tree check.py: 202 tests, zero failures. All 1342 prior accepted addresses
preserved; exactly five added. Total 1347/5247 accepted, 983179 original bytes,
1270 machine MATCH plus 77 behavioral. No comparator, threshold or toolchain
changes; the separate incoming pass-8 overlay is not part of these totals.

The first aggregate run exposed a creation-fixture comparison of raw callback
addresses after these handlers became recovered. Normalize only the three exact
original/replacement identity pairs; retain the full member-pointer adjustment
and object identity. A deliberately wrong registered handler was rejected by a
completed difference. The repaired creation fixture passed 1730 cases, alongside
the 780 new comparisons, before the final aggregate pass.
