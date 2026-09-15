# OpenTorchlight checkpoint schema 1 (port-native)

Status: **implemented port format**, not original binary save compatibility.
The sources of truth for the exact field order are `src/save_codec.cpp` and the
DTOs in `include/torchlight/checkpoint.hpp`. Do not dump C++ structs/ABI bytes.

## File and compatibility

Extension `.otc`, independent user save directory. The 20-byte header is:
8-byte `OTCHKPT\0`, little-endian u32 version=1, u32 payload length, u32 CRC32.
The payload uses explicit little-endian integers, IEEE f32 values, strict
boolean bytes, length-prefixed strings/arrays and tagged optionals. UTF-16
resource identifiers are preserved separately from the character-name byte
string. The physical US input frontend is more restricted than the codec.

Maximum payload: 32 MiB. Shared encoder/decoder allocation accounting: 64 MiB
and 500,000 cumulative container elements; additional per-field limits and
128 visited floors. Save-store listing currently limits 128 slots. A file that
exceeds limits is rejected, not truncated. Version mismatch is an error; there
is no migration yet. The allocation budget bounds charged DTO allocations,
not every incidental allocation of the whole C++ process/graphics runtime.

CRC catches accidental byte corruption; it is not authentication. Pak identity
is a deterministic FNV64 over sorted entry names/size/CRC; layout identity
includes objects, reference IDs, transforms, all typed ADM property values and
logic routes. These detect ordinary incompatible inputs, not maliciously chosen
hash collisions. This is not a security boundary against a hostile local
filesystem owner or a signed save format.

## Persisted boundary

Campaign: slot/revision/resource identity/seed/class GUID/name/Normal difficulty,
current dungeon/depth and last dungeon, player state, visited floor snapshots.
Player: separate evaluated item instances, unique item IDs/next ID/slots;
HP/max, optional mana/max, wallet/hardcore state, base defense, combat RNG and
hand preference. Reconstructed derived equipment/mana must match the snapshot.

Floor: dungeon address/layout identity/player position/facing/recovery anchor/
vertical offset; placed and dynamic entity IDs, resource references, evaluated
weapons/armor/effects, live/enabled/visible/health state, owner/loot references;
logic node state/counters/timers/RNG; enemy signed AI clocks, alertness/hand and
RNG. Only fields supported by the current port are promised. Full quests,
timelines, skills, pets and dynamic effects are not fabricated as empty original
records. Dead bodies remain logically dead; original corpse animation pose and
exact visual presentation after reload are not serialized.

Not saved: native pointers, mesh/GPU buffers, callbacks, navigation paths,
interaction requests, current attacks or pending HITs. These are cancelled
before resuming. Checkpoints with pending deaths/loot/logic work/requests are
rejected. Desktop captures after settled logic and death finalization, or caches
the departing floor after draining its request. Pausing itself does not process
additional zero-time simulation steps.

## Restore / transaction

Decode and validate before changing live state. Reject invalid IDs/enums/counts,
nonfinite numerics, missing slot members, duplicate instances, inconsistent
resource/layout/placed-object identities or spawner/loot references. Restore
uses candidates: validate resource existence, regenerate geometry, verify current
save position against an existing walkable navigation cell/height, then commit.
Do not silently teleport an invalid save to PlayerStart.

A loaded/cached floor does NOT receive new `activate_level()` startup effects.
The evaluated items are not rerolled. Live-world entity IDs, RNG and independent
AI cooldowns are preserved. Transient execution tokens are not. Cached inactive
floors do not simulate elapsed wall-clock time; original volatile/reset timing
remains a separate unimplemented policy.

## POSIX write protocol

Validate/encode → create destination directory → acquire advisory `.write-lock`
with flock → read and compare existing revision → write new mode-0600 temporary
file → fsync(temp) → atomic rename over slot → fsync(directory). New revision
is returned only on full success. Name input never becomes a path; slot IDs are
restricted ASCII identifiers allocated from non-game entropy.

Failure before rename preserves previous bytes. A killed process may leave an
ignored `.checkpoint-*` orphan; normal exceptions remove it. Failure after
rename but during directory fsync reports that the file was already committed
and a revision reload is necessary. Two simultaneous writers using one old
revision cannot both commit. Readers see complete old/new files; tests exercise
one real abrupt process exit and real competing child processes, not merely a
mock write failure. Directory fsync does not make claims about every filesystem,
storage controller or malicious process modifying the directory.

Non-POSIX atomic writing is explicitly unsupported. Android storage/lifecycle
not tested. Original `.SVB` files and installation files are never accessed as
write targets. Full slot backup/delete/recovery UI is not implemented.

## Verification

`save_checkpoint` exercises roundtrip, invalid structures, valid-CRC mutations,
write exceptions and identity mismatches. `save_fresh_process` separates writer
and reader; `save_atomic_process` crashes between fsync and rename and races two
writers. `frontend_campaign_cycle` runs New → authored Town walk/state → save,
Load → Main/death/return → second save, final verify in three processes.
`original_frontend_checkpoint` is prepared for the external pak, but was NOT
executed on original resources in large-5. None tests original save compatibility.
