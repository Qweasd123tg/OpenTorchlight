# lodepng source pilot

`tests/compare_lodepng_source.py` is an opt-in, no-download differential probe.
The external source directory passed to the optional CMake test is exactly the
checkout root containing `lodepng.cpp` and `lodepng.h` (for example
`/tmp/lodepng/src`); it is never vendored.
Fetch `lvandeve/lodepng` outside the repository and pin
[commit bf09e0a5f173ba07821b782b8297dbfc139d5fed](https://github.com/lvandeve/lodepng/tree/bf09e0a5f173ba07821b782b8297dbfc139d5fed)
(2014-12-01), then run:

```sh
python3 tests/compare_lodepng_source.py --original /home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64 --source-dir /tmp/lodepng/src --output /tmp/lodepng-result.json
```

The probe compiles only the upstream translation unit, maps the two original
functions (`lodepng_read32bitInt @0xf633c0`, `lodepng_crc32 @0xf635a0`)
at their ELF addresses, and supplies the original CRC guard/table
globals (`0x154df20`/`0x154df40`) as writable fixture memory. It compares
big-endian 32-bit reads (4 boundary + 256 deterministic random cases) and
83 CRC inputs: NUL, canonical `123456789`, all byte values, lengths
0,1,2,3,4,7,8,15,16,31,32,255,256,257,1023,4096 and 64 random lengths up to
8192 bytes. Each CRC case resets the
original table for a cold call and repeats it warm. The tested original ELF is
SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

The script validates the external git HEAD and both source-file SHA-256 values
before compilation; `Original` rejects a different ELF. It requires Linux
x86-64 / 4096-byte pages, uses non-replacing mappings, and marks code RX while
keeping BOTH pages spanned by the lazy CRC table writable. The initial fixture
crashed because its second table page was RX; this was a harness bug, not a
source mismatch. The complete game is never launched.

Source files pinned by hash:

- `lodepng.cpp`: `8f6810a4b848e1e45ec8559df121f90342078b1af3a1c4d0ccbd86d91bc1391d`
- `lodepng.h`: `c44978696b0e2eb40b573d65e3dd16f7fa7f1202cf0cf862802493aeaf861ee0`

Boundary: `original-code` execution versus a pinned upstream candidate,
**426 numerical comparisons**. This does not identify the exact historical
lodepng version, prove whole-library/decoder equivalence, compare a port
implementation, or establish thread safety of the lazy CRC table.

Enable CTest `original_lodepng_source_comparison` (label `reference`) with
`-DTORCHLIGHT_LODEPNG_SOURCE_DIR=/absolute/path/to/checkout` alongside
`TORCHLIGHT_ORIGINAL`. `tools/check.sh --reference <ELF> --build-dir <same-build>`
retains that cache setting and runs the test. The default gate needs no
external checkout and never downloads or vendors source automatically.
