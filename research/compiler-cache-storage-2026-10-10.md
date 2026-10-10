# Bounded compiler-cache storage, 10 October 2026

The shared compiler cache retained expanded input files after compilation. A read-only inventory before the explicitly approved cleanup found 7,101,114,155 bytes in cache payloads, including about 5.43 GB of plain/compressed expanded inputs. SHA-256 checks found 644,337,086 bytes of byte-identical output duplication. Different semantic keys often reflected real header revisions even when resulting assembly was identical; those keys must remain distinct.

## Changes

- Newly expanded input.ii files live only in the existing per-compilation temporary directory. The basename and preprocessed line prefix are unchanged.
- Output bytes use a SHA-256-addressed content store. Distinct semantic keys retain their own locks and checksum-verified manifests while identical outputs share a hardlinked inode.
- Content digest locks follow key locks. Atomic replacement repairs corrupted storage without writing through other aliases. Caller outputs remain copies. Filesystems that reject hardlinks fall back to copying.
- Compiler identity, include/header resolution, flags, preprocessing, cache keys, acceptance thresholds, and generated game code are unchanged. There is no automatic purge of existing cache data.

## Verification

All 108 storage/compiler/pipeline controls pass with no skips: 9 synthetic storage controls, 15 pinned GCC controls, and 84 related publication/resource-slot/pipeline controls. Tests cover original versus temporary backend paths, uncached byte identity, path macros, header and flag invalidation, shadow headers, corruption, concurrent keys, caller isolation, and copy fallback.

A cold isolated full game check passed all 411 headless tests. Its 278 translation-unit object digests are identical to the accepted pre-change baseline. An independent root check of the final three-file tool/test change again passed all 411 tests with identical object digests and acceptance: 2348 / 5247 addresses, 2116 MATCH and 232 behavioral, 1,140,362 accepted original bytes.

The first full check used a previously emptied shared cache, so it exercised the new implementation rather than old retained payloads. Its stats and the independent root stats are recorded below. No retained input.ii files were observed. Interrupted processes may leave temporary artifacts; automatic cache garbage collection is outside this change.

Compiler cache observations:

- stage-check: {"fallback": 0, "hit": 278, "miss": 533}
- root: {"fallback": 0, "hit": 728, "miss": 83}
