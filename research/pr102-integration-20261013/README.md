# PR102 integrated on current main — 13 October 2026

This is the scoped successor to [PR102](https://github.com/Qweasd123tg/OpenTorchlight/pull/102), importing its complete two-batch delta from head `5194eb31eb2f2f8876c4f673d5f85040c8d77a6a` onto main `00429ea7e60ce69633f1d4d38ada171937cda0b3` after PR108. The unrelated handoff branch history is not merged.

## Fresh result

- 111 explicit C++98 definitions, 114 unique original addresses, 39,390 original bytes.
- **2,755 → 2,869 accepted functions**, with all prior addresses preserved, including NPC `0xd15210`.
- **2,213 MATCH + 656 BEHAVIORAL**, covering 1,366,827 original bytes.
- Added addresses: **27 MATCH + 87 BEHAVIORAL**. All 25 addresses without direct fixtures and all three deleting-destructor D0 addresses have fresh MATCH.
- **840 tests, 0 failed**, with 840 distinct PASS frames and all eight shard processes exiting 0.
- The scoped fixtures compare 89 distinct original/replacement addresses: **14,080 completed pairs, 0 different, 0 incomplete**, including the 128-pair `CDungeonTracker::save(FILE*)` preservation guard.
- All 281 production TUs were checked. The shared-header change reaches 191 TUs; validation was not restricted to edited sources.

`Stage.validate()` and `Stage.publish()` ran on the same live Stage instance. Production inputs were not edited after validation. Publication rechecked the complete production-object identities and external input fingerprint; the published root and validated Stage have the same input digest:

`842cf75885cad13f05db27685829123454cc497a05bb31fbf583faf01f9a671e`

An independent read-only audit checked the current input manifests, original/replacement ELF symbol bindings, all address evidence, unique test frames, shard exits and exact source scope before publication. The pinned GCC 4.4.7/C++98 configuration, original ELF and repository pipeline were used unchanged.

## Integration scope

The runtime delta is 43 files: 11 source TUs, 19 headers, 11 fixture translation units plus their comparison helper, and the owner registry. Existing owner assignments are preserved. `ResourceManager.h` combines the PR's declarations with main's `CDungeon` and `getDungeonByName` declarations; its existing `getGameClient` accessor is preserved.

The ten reports under `research/smallmass2-20261012/` and `research/restore69-20261012/` are preserved byte-for-byte as historical author evidence. Their old baseline totals and acceptance statuses do not describe this integrated snapshot. Use the fresh reports in this directory. In particular, the current result accepts `CDungeonTracker::save` by comparison and `CCharacter::removePet(std::wstring)` by MATCH.

PR100/savehold and the separate held B definition/parser work are not imported.

## What this proves and does not prove

The comparisons use finite synthetic objects and recording substitutes for collaborators. They verify original/replacement call binding and observed state, outputs and call order for the listed inputs. Existing harness negative controls cover wrong or identical targets, missing/doubled invocation, changed output, crashes, overflow, malformed reports and timeouts. No fixture-specific source-mutation campaign was added or claimed.

These fixtures do not establish composed gameplay, exhaustive branches, heap leak/ownership correctness or allocation-failure cleanup. Dungeon fixtures exercise well-formed bounded data and supported versions, not every truncated-file or I/O-failure case. Raw pointer observations rely on the common fork/arena setup.

Windowed gameplay, a complete playthrough and standalone execution without the original binary were not tested. The original ELF, game resources and generated binaries are not included.

Evidence: [per-address results](functions.json), [validation](validation.json), [complete selftest report](selftest.log), [production object identities](objects.json).
