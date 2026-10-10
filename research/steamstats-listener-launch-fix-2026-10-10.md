# SteamStats listener map: interactive-launch crash

The requested hybrid launch reached OGRE initialization, then aborted with
`munmap_chunk(): invalid pointer` while constructing achievements. The blob
frame resolved to `CSteamStats::addStatListener(ESTATS, iStatListener*)`.

At original address `0xece980`, the map node's value at `+0x28` is loaded as a
pointer; the list's count/capacity are then accessed at `+0x08`/`+0x0c` through
that pointer. The recovered header instead declared an inline list value,
causing the replacement to interpret and free the list object as its array.
Correct the map value to `TArrayList<iStatListener*>*` and call `second->add`.

The function remains DIFF (97.4% similarity); the remaining normalized
differences concern register choice around the post-allocation capacity load.
Similarity is not the acceptance basis.

`steamstats_listener_differential` compares actual original/replacement calls
on empty/missing/present map entries, boundary and middle keys, zero/partial/
full lists, two growth increments, and null/repeated/new listener identities.
It observes map keys/list identities, all three lists' count/capacity/growth
metadata and element identities, including lists not selected by the lookup.
Focused headless run: 384 completed comparisons, zero differences, zero
incomplete calls; one test PASS. Allocation failures are not covered.

A separately compiled ignored calibration reinterprets the pointer-valued map
entry as an inline list, reproducing the previous defect. The fixture rejects
it: 240 completed comparisons and 144 incomplete pairs, fixture FAIL. Crashes
are rejection, not behavioral acceptance.

The full `check.py` run was interrupted to prioritize the requested interactive
launch after compilation/linking had completed. No full-suite PASS or global
acceptance-count update is claimed.

The interactive retry passed the achievement/listener failure but still did
not reach a game window: SIGSEGV at original `CEffect` constructor address
`0x7e160d`, called through `CAffix::parseAffixGroup`, `CAffix` construction and
`CEffectGroupManager::reload`. The recovered group-manager constructor appears
in the caller stack. This second crash's cause is not yet established; the
listener fix is not a claim that the complete hybrid is playable.
