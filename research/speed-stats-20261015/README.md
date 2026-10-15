# Steam stats and test scheduling, 2026-10-15

Baseline `266f9b29e4e62d0c79493fbe401d13e0e47538b1`: **3238 → 3241/5247** accepted,
with **2426 MATCH + 815 BEHAVIORAL**.
The tranche adds one MATCH and two behavioral acceptances. Every prior accepted
address retains acceptance; all 3276 prior strong matches retain code/metadata.

`SStatChange` now defaults both fields to zero, as both allocation loops in the
original `statModified` do. Its caller uses ordinary default construction and
field assignments. Before the fix, the synthetic regression reports one normal
completed original/replacement pair with a difference. `negative-control.json`
gives the exact one-replacement derivation of that fixture from the current fixture
and binds it to the baseline source/header hashes. After the fix, the method
is MATCH and its regression passes 30 normal pairs covering duplicate positions,
first allocation, growth, no growth, capacity fallback and four payload bit patterns.
The 160-byte `CSteamStats` and 8-byte entry layouts remain unchanged; the DWARF
anonymous-union identifier changes only because debug-record offsets move.

Two existing implementations gain sufficient real comparison coverage:
`CDataValue::GetValueTypeAsString` has 45 pairs across type boundaries and other
storage fields; `FILESYSTEM::GetApplicationPath` has 32 pairs across cold/empty,
shared/unshared cache states and varied strings. The minimum remains 20.

The scheduler can reuse advisory durations for unchanged compiled test objects
when the fixture inventory expands. The sidecar binds blob bytes and object SHAs;
actual ELF relocations supply the exact linked name-to-object mapping. Shared
runtime/header inputs and registration-free compiled helpers form the common key.
Unknown durations use the median of known selected tests. Missing/malformed inputs
fall back to index order; every shard still executes and fresh inventory/report
validation is unchanged. No verdict or acceptance receipt enters these profiles.

Forty tooling tests pass. A read-only check of the previous 422 objects / 999
registrations reconstructs the exact same costs/order from 420 object profiles as
the old whole-inventory profile, with every one of the 60 shards present.
Historical durations were explicitly imported as ordering hints before integration.
The fresh full run reuses 994 known durations and estimates
6 new ones; details are in `scheduler-verification.json`.

- Focused: all 290 production TUs, 14 tests, 1936 completed pairs,
  no differences or incomplete calls; build 40.03s.
- Mandatory full `python3 tools/decomp/check.py`: **1000 tests / 0 failures**,
  60 shards, 1195.50s. The preceding 999-test run took 1173.46s.
  The inventory changed and there is one sample per run; these timings are not a
  controlled speedup measurement. Compiler/selftest capacities remain 2/6.
- All behavioral receipts bind current object digests and one current input digest;
  types are current. Only `SteamStats.cpp` changes among production source files.

Recovery uses targeted checks inside the batch and one final canonical full gate
before commit. This is headless pre-main evidence; windowed gameplay is unverified.
