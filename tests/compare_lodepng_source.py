#!/usr/bin/env python3
"""Compare the pinned lodepng source functions with the shipped ELF.

This is deliberately an opt-in probe: it downloads nothing and never copies
the proprietary ELF into the repository.  The original function is executed
from read-only bytes mapped at its linked addresses, with only its CRC globals
provided as writable fixture memory.
"""
import argparse, ctypes as C, hashlib, json, os, random, subprocess, tempfile, platform, time
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from original import Original
from native_typed_reference import Memory

COMMIT = "bf09e0a5f173ba07821b782b8297dbfc139d5fed"
SOURCE_SHA256 = {"lodepng.cpp": "8f6810a4b848e1e45ec8559df121f90342078b1af3a1c4d0ccbd86d91bc1391d", "lodepng.h": "c44978696b0e2eb40b573d65e3dd16f7fa7f1202cf0cf862802493aeaf861ee0"}

def sha(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""): h.update(b)
    return h.hexdigest()

def source_build(root, td):
    wrapper = Path(td) / "wrapper.cpp"
    wrapper.write_text('#include "lodepng.h"\nunsigned lodepng_read32bitInt(const unsigned char*); unsigned lodepng_crc32(const unsigned char*, size_t);\nextern "C" unsigned lodepng_read32bitInt_c(const unsigned char* p) { return lodepng_read32bitInt(p); }\nextern "C" unsigned lodepng_crc32_c(const unsigned char* p, size_t n) { return lodepng_crc32(p, n); }\n', encoding="utf-8")
    out = Path(td) / "liblodepng.so"
    subprocess.run(["c++", "-shared", "-fPIC", "-O2", "-std=c++11", "-I", str(root), "-o", str(out), str(root / "lodepng.cpp"), str(wrapper)],
                   cwd=root, check=True)
    return out

def original_functions(elf):
    o, m = Original(elf), Memory()
    funcs = {}
    for name, addr in [("read32", 0xf633c0), ("crc32", 0xf635a0)]:
        s = o.symbol("lodepng_read32bitInt(unsigned char const*)" if name == "read32" else
                     "lodepng_crc32(unsigned char const*, unsigned long)", addr)
        m.put(s.address, o.read(s.address, s.size))
        funcs[name] = (C.CFUNCTYPE(C.c_uint, C.c_void_p) if name == "read32" else
                       C.CFUNCTYPE(C.c_uint, C.c_void_p, C.c_size_t))(s.address)
    # crc32's lazy table and guard are linked writable globals in this build.
    m.put(0x154df20, b"\0" * (0x154df40 + 256 * 4 - 0x154df20))
    # Keep every page touched by the 0x400-byte table writable; the function
    # lazily fills it before setting the guard.
    m.protect(tuple(range(0x154df20 & ~4095, ((0x154df40 + 256 * 4 - 1) & ~4095) + 4096, 4096)))
    return o, m, funcs

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--original", required=True)
    ap.add_argument("--source-dir", required=True)
    ap.add_argument("--output", required=True)
    a = ap.parse_args()
    if platform.system() != "Linux" or platform.machine() != "x86_64" or os.sysconf("SC_PAGESIZE") != 4096:
        return 77
    began = time.monotonic()
    root = Path(a.source_dir).resolve()
    if not (root / "lodepng.cpp").is_file(): raise SystemExit("source-dir lacks lodepng.cpp")
    actual_commit = subprocess.check_output(["git", "-C", str(root), "rev-parse", "HEAD"], text=True).strip()
    if actual_commit != COMMIT: raise SystemExit(f"source checkout is {actual_commit}, expected {COMMIT}")
    source_hashes = {name: sha(root / name) for name in SOURCE_SHA256}
    if source_hashes != SOURCE_SHA256: raise SystemExit(f"source hash mismatch: {source_hashes}")
    with tempfile.TemporaryDirectory(prefix="lodepng-compare-") as td:
        libpath = source_build(root, td)
        lib = C.CDLL(str(libpath))
        read_src = lib.lodepng_read32bitInt_c; read_src.argtypes = [C.c_void_p]; read_src.restype = C.c_uint
        crc_src = lib.lodepng_crc32_c; crc_src.argtypes = [C.c_void_p, C.c_size_t]; crc_src.restype = C.c_uint
        o, mem, orig = original_functions(a.original)
        rng = random.Random(0xC0DEC0DE)
        read_cases = [b'\0\0\0\0', b'\xff\xff\xff\xff', b'\x01\x23\x45\x67', b'\x80\0\0\0']
        read_cases += [bytes(rng.randrange(256) for _ in range(4)) for _ in range(256)]
        lengths = [0, 1, 2, 3, 4, 7, 8, 15, 16, 31, 32, 255, 256, 257, 1023, 4096]
        lengths += [rng.randrange(8193) for _ in range(64)]
        cases = [b'\0', b'123456789', bytes(range(256))]
        cases += [bytes(rng.randrange(256) for _ in range(n)) for n in lengths]
        read_results, crc_results = [], []
        try:
            for raw in read_cases:
                buf = C.create_string_buffer(raw); p = C.addressof(buf)
                read_results.append({"hex": raw.hex(), "original": orig["read32"](p), "source": read_src(p)})
            for raw in cases:
                buf = C.create_string_buffer(raw or b"\0"); p = C.addressof(buf)
                mem.put(0x154df20, b"\0" * (0x154df40 + 256 * 4 - 0x154df20))
                cold = orig["crc32"](p, len(raw)); warm = orig["crc32"](p, len(raw))
                src = crc_src(p, len(raw))
                crc_results.append({"len": len(raw), "sha256": hashlib.sha256(raw).hexdigest(), "cold": cold, "warm": warm, "source": src})
        finally:
            mem.close()
        result = {"status": "pass" if all(x["original"] == x["source"] for x in read_results) and all(x["cold"] == x["warm"] == x["source"] for x in crc_results) else "FAIL",
                  "commit": COMMIT, "source_sha256": source_hashes,
                  "original_sha256": o.sha256, "source_commit": actual_commit,
                  "comparisons": len(read_results) + 2 * len(crc_results),
                  "generator_seed": "0xc0dec0de", "elapsed_seconds": round(time.monotonic() - began, 3),
                  "scope": "Two original leaf functions versus pinned upstream source, not whole-library or port equivalence",
                  "read32": read_results, "crc32": crc_results}
        output = Path(a.output)
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
        print(f"{result['status']}: read32={len(read_results)} crc32={len(crc_results)} source={actual_commit}")
    return 0 if result["status"] == "pass" else 1

if __name__ == "__main__": raise SystemExit(main())
