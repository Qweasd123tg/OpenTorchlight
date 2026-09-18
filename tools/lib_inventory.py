#!/usr/bin/env python3
"""Static upstream-library inventory for the original Torchlight Linux build.

Reads ONLY: the pinned ELF, its NEEDED entries, shipped .so files, and our
symbol/coverage lists. Never executes the game, never copies proprietary
binaries into the repo. Output: research/lib-inventory.json (+ .md).

Purpose: separate dynamically-linked library code (lives in .so files, NOT in
the 17k main-binary functions) from statically-linked third-party code (in
the main binary: lodepng, ParticleUniverse, ConvertUTF, STL/GCC runtime), so
source-matching effort goes to real static code instead of import glue.
"""
from __future__ import annotations
import argparse, csv, json, re, subprocess
from collections import Counter
from pathlib import Path

GAME_BIN = Path("/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64")
GAME_LIB = Path("/home/qweasd123tg/Games/Torchlight/game/lib64")
ELF_SHA = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"

STATIC_PATTERNS = [
    ("lodepng", re.compile(r"lodepng_|LodePNG|LODEPNG")),
    ("particle_universe", re.compile(r"ParticleUniverse|PU_")),
    ("convert_utf", re.compile(r"ConvertUTF")),
    ("stl_libstdcxx", re.compile(r"std::|__gnu_cxx|__cxxabiv")),
    ("cegui_inline", re.compile(r"CEGUI::")),
    ("ogre_inline", re.compile(r"Ogre::")),
    ("fmod", re.compile(r"FMOD")),
    ("zzip", re.compile(r"zzip_|ZZIP")),
    ("pcre", re.compile(r"pcre")),
    ("sdl", re.compile(r"SDL_")),
]


def needed(path: Path) -> list[str]:
    o = subprocess.run(["readelf", "-d", str(path)], capture_output=True, text=True).stdout
    return re.findall(r"\(NEEDED\)[^[]*\[([^\]]+)\]", o)


def dynsym_count(path: Path) -> int | None:
    o = subprocess.run(["nm", "-D", "--defined-only", str(path)], capture_output=True, text=True).stdout
    if not o.strip():
        return None
    return len(o.splitlines())


def version_strings(path: Path, patterns: list[str]) -> list[str]:
    o = subprocess.run(["strings", "-a", str(path)], capture_output=True, text=True).stdout
    hits = set()
    for ln in o.splitlines():
        for p in patterns:
            if re.search(p, ln, re.IGNORECASE) and len(ln) < 160:
                hits.add(ln.strip())
    return sorted(hits)[:12]


def main() -> int:
    a = argparse.ArgumentParser(description=__doc__)
    a.add_argument("--root", type=Path, default=Path("."))
    a.add_argument("--json", type=Path, default=Path("research/lib-inventory.json"))
    a.add_argument("--out", type=Path, default=Path("research/lib-inventory.md"))
    args = a.parse_args()
    root = args.root.resolve()

    dynamic, shipped = [], []
    if GAME_BIN.is_file():
        for lib in needed(GAME_BIN):
            where = GAME_LIB / lib
            shipped_path = str(where) if where.is_file() else None
            dynamic.append({"soname": lib, "shipped": shipped_path,
                            "dynsym": dynsym_count(where) if where.is_file() else None})

    static_hits: dict[str, int] = {}
    total_syms = 0
    sym_path = root / "research/original-symbols.txt"
    if sym_path.is_file():
        syms = sym_path.read_text(encoding="utf-8", errors="replace").splitlines()
        total_syms = len(syms)
        buckets: Counter[str] = Counter()
        for ln in syms:
            for name, rx in STATIC_PATTERNS:
                if rx.search(ln):
                    buckets[name] += 1
                    break
        static_hits = dict(buckets)

    versions = {}
    if GAME_BIN.is_file():
        versions["main_binary"] = version_strings(
            GAME_BIN, [r"ogre.*1\.6", r"cegui.*ogre", r"lodepng.*20\d{6}", r"built with",
                        r"GCC.*\(GNU\)", r"fmod.*4\.", r"ParticleUniverse.*\.h"])
    cegui = GAME_LIB / "libCEGUIBase.so.1"
    if cegui.is_file():
        versions["libCEGUIBase"] = version_strings(
            cegui, [r"0\.[67]\.\d+", r"crazy eddie", r"version"])

    data = {"elf_sha256": ELF_SHA, "dynamic_libraries": dynamic,
            "shipped_lib_dir": str(GAME_LIB),
            "main_binary_symbol_lines": total_syms,
            "static_symbol_hits": static_hits, "version_strings": versions}
    args.json.parent.mkdir(parents=True, exist_ok=True)
    args.json.write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

    lines = ["# Upstream library inventory (static read-only scan)", "",
             f"Main binary symbols scanned: {total_syms}", "",
             "## Dynamically linked (code lives in .so, not in the 17k)", ""]
    for d in dynamic:
        lines.append(f"- `{d['soname']}` shipped={d['shipped'] is not None} dynsym={d['dynsym']}")
    lines += ["", "## Static third-party symbol hits in the main binary", ""]
    for k, v in sorted(static_hits.items(), key=lambda kv: -kv[1]):
        lines.append(f"- {k}: {v}")
    lines += ["", "## Version strings", ""]
    for k, v in versions.items():
        lines += [f"### {k}"] + [f"- {s}" for s in v] + [""]
    args.out.write_text("\n".join(lines), encoding="utf-8")
    print("wrote", args.json, "and", args.out)


if __name__ == "__main__":
    raise SystemExit(main())
