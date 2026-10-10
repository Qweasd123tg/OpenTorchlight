# Phase-specific local concurrency

Measured in the current cloud workspace: AMD EPYC 9V74 host, nine available
logical CPUs, approximately 10 GB memory. Host topology is not a promise of
80 dedicated cores. Shared-machine measurements can vary; no universal speedup
is claimed and no repository-wide default is raised.

## Measurements

Uncached GCC 4.4.7 assembly compilation of 24 large current translation units
(16 source, eight test), three repeats per setting, mixed order:

- 4 workers: median 14.818482 s.
- 6 workers: median 13.707050 s, 7.5% less wall time.
- 8 workers: median 13.982594 s.

All 24 output assembly hashes match at all nine runs. Peak aggregate sampled
RSS rose from approximately 1.40 GB to 1.92 GB at six and 2.30 GB at eight;
available memory stayed above 6.6 GB. These are sampled values, not hard bounds.

Warm full static comparison, two runs per setting:

- 4 workers: median 19.119506 s.
- 6 workers: median 21.930509 s.
- 8 workers: median 23.121781 s.

All complete static JSON reports are equal, with 1277 MATCH. More workers made
this phase slower, so it retains four.

Full existing headless suite, 60 shards, one completed run per setting:

- 4 workers: 287.476603 s wall, 992.326703 s child CPU.
- 6 workers: 225.442343 s wall, 1095.008004 s child CPU.
- 8 workers: 209.291247 s wall, 1248.377932 s child CPU.

Each run passed all 205 tests. Eight workers reduced wall time by 27.2% while
increasing cumulative child CPU by 25.8% versus four. This is a speed/resource
tradeoff, not a reduction of all resource consumption. The additional gain
versus six was 7.2%. One earlier interrupted benchmark produced no completed
selftest result and is excluded. Per-shard subprocess diagnostics returned the
original results unchanged to the strict existing test parser.

## Selected configuration and behavior

For this workspace only: OTL_JOBS=4, OTL_COMPARE_JOBS=4, OTL_BUILD_JOBS=6,
OTL_SELFTEST_JOBS=8, compiler pool=6 and selftest pool=8. Pool capacities are
changed through resource_slots.configure only while idle. The existing timeout
and shard count are retained. No additional LLM workers or model queries are
needed for this change.

The optional phase variables preserve the existing OTL_JOBS fallback. Empty
values use that fallback; invalid values fail clearly. Input/result order,
finish-before-propagating exceptions, cross-worktree resource limits, compiler
flags, comparison, and acceptance are unchanged. All seven production
parallel_map call sites are routed, including standalone compilation.

Unit coverage checks independent overrides, legacy fallback, invalid values,
real bounded parallel execution, ordering, SystemExit propagation and call-site
routing. The full Python suite passes 639 tests with one existing skip.
Both the isolated candidate and independently checked integrated root pass all
205 headless tests. Every prior unit result and accepted address is unchanged:
1356/5247 accepted, 985776 original bytes, 1277 MATCH and 79 behavioral.
Neither source recovery nor strict acceptance was altered by this scheduling change.
