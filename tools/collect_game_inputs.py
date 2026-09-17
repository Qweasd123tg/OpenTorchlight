#!/usr/bin/env python3
"""Collect private read-only game inputs, not saves/settings, without executing the game.

Usage: python3 collect_game_inputs.py --game-dir /path/to/Torchlight --output /outside/game-inputs.zip
The output must be outside the game and source-repository directories, and must not exist.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import tempfile
import zipfile

EXPECTED_ELF = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
EXPECTED_PAK = "8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8"
REQUIRED_NAMES = ("pak.zip", "Torchlight.bin.x86_64")
LIBRARY_PATTERNS = ("libOgreMain*.so*", "libCEGUIBase*.so*", "libCEGUIOgreRenderer*.so*")
BLOCK = 2 * 1024 * 1024


def within(path: Path, parent: Path) -> bool:
    try:
        path.relative_to(parent)
        return True
    except ValueError:
        return False


def signature(path: Path) -> tuple[int, int, int, int]:
    stat = path.stat()
    return stat.st_dev, stat.st_ino, stat.st_size, stat.st_mtime_ns


def collect(game_dir: Path, output: Path, *, libraries: bool = True) -> dict:
    root = game_dir.resolve(strict=True)
    if not root.is_dir():
        raise ValueError("game-dir must be the directory containing pak.zip and/or the Linux executable")
    target = output.resolve()
    repository = Path(__file__).resolve().parents[1]
    if within(target, root):
        raise ValueError("output must be outside the read-only game directory")
    if (repository / "CMakeLists.txt").is_file() and (repository / "AGENTS.md").is_file() and within(target, repository):
        raise ValueError("private original inputs must not be written inside the source repository")
    if target.exists() or output.is_symlink():
        raise FileExistsError("output already exists; choose a new filename")
    selected: dict[str, Path] = {}
    missing, ignored = [], []
    for name in REQUIRED_NAMES:
        source = root / name
        if source.is_file() and within(source.resolve(), root):
            selected[name] = source
        else:
            missing.append(name)
    if not selected:
        raise FileNotFoundError("neither pak.zip nor Torchlight.bin.x86_64 was found in game-dir")
    if libraries:
        for folder in (root, root / "lib", root / "lib64"):
            if not folder.is_dir():
                continue
            for pattern in LIBRARY_PATTERNS:
                for source in sorted(folder.glob(pattern)):
                    name = source.relative_to(root).as_posix()
                    if not source.is_file() or not within(source.resolve(), root):
                        ignored.append(name + ": not a regular file inside the authorized game directory")
                        continue
                    selected[name] = source
    target.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=".ot-original-inputs-", suffix=".tmp", dir=target.parent)
    os.close(fd)
    temp_path = Path(temporary)
    manifest = {
        "schema": 1, "kind": "private-original-input-bundle", "not_a_game_build": True,
        "original_executed": False, "missing": missing, "ignored": sorted(set(ignored)),
        "excluded": "all files except the named pak, Linux executable and optional OGRE/CEGUI libraries; no saves or settings",
        "files": [],
    }
    try:
        with zipfile.ZipFile(temp_path, "w", compression=zipfile.ZIP_DEFLATED, compresslevel=3, allowZip64=True) as archive:
            for name, source in sorted(selected.items()):
                before = signature(source)
                digest, size = hashlib.sha256(), 0
                with source.open("rb") as src, archive.open(name, "w", force_zip64=True) as dst:
                    for block in iter(lambda: src.read(BLOCK), b""):
                        digest.update(block)
                        size += len(block)
                        dst.write(block)
                if before != signature(source) or size != before[2]:
                    raise RuntimeError("source changed during collection: " + name)
                item = {"path": name, "bytes": size, "sha256": digest.hexdigest()}
                if name in REQUIRED_NAMES:
                    expected = EXPECTED_PAK if name == "pak.zip" else EXPECTED_ELF
                    item["matches_previously_inspected_build"] = item["sha256"] == expected
                    item["expected_sha256"] = expected
                manifest["files"].append(item)
            archive.writestr("INPUTS_MANIFEST.json", json.dumps(manifest, ensure_ascii=False, indent=2) + "\n")
        # Atomic publication with no overwrite, including a concurrently-created target.
        # Temporary and output are on the same filesystem. No source is modified.
        os.link(temp_path, target)
    finally:
        temp_path.unlink(missing_ok=True)
    return manifest


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--game-dir", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--no-libraries", action="store_true")
    args = parser.parse_args()
    try:
        manifest = collect(args.game_dir, args.output, libraries=not args.no_libraries)
    except (OSError, ValueError, RuntimeError, zipfile.BadZipFile) as error:
        parser.exit(1, f"ERROR: {error}\n")
    print(f"Created {args.output}: {len(manifest['files'])} input files; game not executed")
    if manifest["missing"]:
        print("INCOMPLETE INPUT SET: missing " + ", ".join(manifest["missing"]))
    for item in manifest["files"]:
        if item.get("matches_previously_inspected_build") is False:
            print("BUILD MISMATCH (requires review, not an execution authorization): " + item["path"])
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
