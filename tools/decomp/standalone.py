#!/usr/bin/env python3
"""Link-only residual without originals.ld, hooks or original data redirects.

    python3 tools/decomp/standalone.py [--tu T.cpp] [--library /pinned/library.so]

Builds ordinary GCC 4.4 objects. A failed link is the expected remaining work;
no unresolved symbol is replaced by a stub or an original ELF address.
Even a closed link-only slice is not evidence of a runnable standalone game.
"""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess

import elfdb
import elfimage
import hybrid
import publication
import toolchain


def classify(names, db, image):
    game = {t["id"] for t in db["tus"] if t["kind"] == "game"}
    functions = {n for f in db["functions"].values() if f["tu"] in game for n in f["names"]}
    files = {t["name"] for t in db["tus"] if t["kind"] == "game"}
    data = {g["name"] for g in db["globals"] if g.get("file") in files}
    external = {s.name.split("@")[0] for s in image.dynsyms if not s.defined}
    rows = {key: [] for key in ("game_functions", "game_data", "rtti", "vtables", "library_imports", "unknown")}
    for name in sorted(names):
        kind = ("game_functions" if name in functions else "game_data" if name in data else
                "rtti" if name.startswith(("_ZTI", "_ZTS")) else "vtables" if name.startswith(("_ZTV", "_ZTT")) else
                "library_imports" if name in external else "unknown")
        rows[kind].append(name)
    return rows


def inspect(tus=(), libraries=(), out=None):
    root = elfdb.ROOT
    out = out or root / "build-decomp/standalone"
    out.mkdir(parents=True, exist_ok=True)
    db = elfdb.load_db()
    image = elfimage.load(elfdb.default_elf())
    if image.sha256 != elfimage.ORIGINAL_SHA256:
        raise RuntimeError("original ELF identity changed")
    sources = sorted((root / "decomp/src").rglob("*.cpp"))
    if tus:
        unknown = set(tus) - {p.name for p in sources}
        if unknown:
            raise ValueError("no source for " + ", ".join(sorted(unknown)))
        sources = [p for p in sources if p.name in tus]
    if not sources:
        raise ValueError("no source slice")
    libraries = [Path(p).resolve(strict=True) for p in libraries]
    versions = {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in libraries}
    def compile_unit(source):
        # Ordinary objects retain source data and static initialization.
        path = out / (source.name + ".o")
        toolchain.compile_source(source, path, quiet=True, cache=False)
        return path
    with publication.tree_lock():
        snapshot = publication.tree_state(root)
        objects = toolchain.parallel_map(compile_unit, sources)
        defined, undefined, initializers, locals_ = set(), set(), set(), []
        for path in objects:
            obj = elfimage.load_object(path)
            defined |= hybrid.defined_symbols(path)
            undefined |= hybrid.undefined_symbols(path)
            initializers |= {s.name for s in obj.symbols if s.defined and s.name.startswith(("_GLOBAL__I_", "_GLOBAL__sub_I"))}
            locals_ += [{"object": path.name, "symbol": s.name, "size": s.size} for s in obj.symbols
                        if s.defined and s.bind == elfimage.STB_LOCAL and s.type == elfimage.STT_OBJECT]
        unresolved = undefined - defined
        output = out / "link-only.elf"
        output.unlink(missing_ok=True)  # never leave a previous success next to a failed probe
        command = ["ld", "-nostdlib", "-e", "0", "--build-id=none", "-o", str(output),
                   *map(str, objects), *map(str, libraries)]
        result = subprocess.run(command, capture_output=True, text=True)
        if snapshot != publication.tree_state(root):
            raise RuntimeError("source/header tree changed during link probe")
    report = {"schema": 1, "original_elf_sha256": image.sha256,
              "sources_sha256": {str(p.relative_to(root)): hashlib.sha256(p.read_bytes()).hexdigest() for p in sources},
              "libraries_sha256": versions, "command": command, "link_exit": result.returncode,
              "link_closed": result.returncode == 0, "standalone_game_verified": False,
              "residual_before_libraries": classify(unresolved, db, image),
              "static_initializers": sorted(initializers), "local_static_data": locals_,
              "diagnostics": result.stderr, "no_original_resolution": True,
              "limitation": "link-only probe, entrypoint 0; no process execution or behavioral parity inferred"}
    (out / "report.json").write_text(json.dumps(report, indent=1, ensure_ascii=False) + "\n")
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--tu", action="append", default=[])
    parser.add_argument("--library", action="append", default=[])
    parser.add_argument("--out", type=Path)
    args = parser.parse_args()
    report = inspect(args.tu, args.library, args.out)
    print(json.dumps({"link_exit": report["link_exit"], "link_closed": report["link_closed"],
                      "standalone_game_verified": False,
                      "residual": {k: len(v) for k, v in report["residual_before_libraries"].items()}}, indent=1))
    # A nonzero link is a reported residual, not a failed inspection command.


if __name__ == "__main__":
    main()
