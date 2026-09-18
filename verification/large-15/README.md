# Evidence index — large-15

`verification.json` combines the final executed checks and their limits.
`run-groups.json` is the unedited tools/check.py output; four JUnit XML files
retain individual stdout. `verified-final.log` records configure/build/test.

`character-stats-original.json` and `item-graph-original.json` report bounded
execution of fingerprint-gated original functions. No full game constructors
are called. Stubbed dependencies are described in each report and probe.

`baseline-verification.json` describes large-14 plus the prior UI patchset.
`intermediate-verification.json` retains actual failing expectations discovered
during correction; it is not the final result. The final suite changes preserve
the test's real gameplay checks rather than suppress them. The initial Release
warning/error is retained separately; the final Release log confirms the fix.

`before-after-*.json`, the two small `authored-stats-*-v5.otc` files, and
`authentic-v5-provenance.json` document a genuinely unchanged previous writer.
The saves contain only an authored test character/item, not user or original
game saves. New loading runs in another process and checks raw roll, HP, RNG,
derived armor and unequip. Compile tests/gameplay_before_after_probe.cpp against
each baseline's core library separately, with its own include directory, then
run `probe character-stats.pak.zip output.otc`. New reader:
`character_stats_test --read character-stats.pak.zip old-output.otc`.

`gameplay-catalog.json` uses the actual inherited UNIT loader and type tree.
`raw-resource-summary.json` counts local ADM groups without inheritance; the
two inventories are intentionally not mixed. Counts are not gameplay coverage.

`prior-original-ui-probes.json` is explicitly historical native UI evidence,
not a new current-port run. Current HUD timing is checked by core and real GL
common-application tests.

No proprietary pak, ELF, library or font bytes are distributed. Paths in raw
logs refer to this verification environment and are not paths to install on
a user's machine. Package hashes/patch checks are reported outside the source
tree so they cannot create circular checksums.

Only trailing whitespace in packaged log copies is normalized to allow clean
patch application. Original and packaged hashes are in verification.json.
The original build logs remain unchanged in the verification environment.
