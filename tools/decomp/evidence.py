#!/usr/bin/env python3
"""Conservative identities for reusing differential/mutation test results.

An instruction digest is a similarity key, not an identity of a tested build.
Old unversioned results must be rerun rather than stamped with current inputs.
"""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess

import elfdb
import toolchain

SCHEMA = 1
INPUT_SUFFIXES = {".cpp", ".c", ".h", ".hpp", ".s", ".S", ".py", ".java", ".json"}


def file_digest(path):
    h = hashlib.sha256()
    with Path(path).open("rb") as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def digest_paths(paths, context=None):
    """Names and complete contents; additions/deletions change the identity too."""
    rows = []
    for name, path in sorted(paths, key=lambda row: row[0]):
        rows.append([name, file_digest(path)])
    data = {"schema": SCHEMA, "files": rows, "context": context or {}}
    return hashlib.sha256(json.dumps(data, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def directory_inputs(name, directory, suffixes=None):
    directory = Path(directory)
    if not directory.is_dir():
        return []
    return [(name + "/" + p.relative_to(directory).as_posix(), p)
            for p in sorted(directory.rglob("*")) if p.is_file()
            and "__pycache__" not in p.parts and (suffixes is None or p.suffix in suffixes)]


def runtime_inputs(elf):
    """The libraries resolved by the same search order as the hybrid runtime."""
    game = Path(os.environ.get("TORCHLIGHT_GAME_DIR", Path.home() / "Games/Torchlight/game"))
    env = dict(os.environ)
    env.pop("LD_PRELOAD", None)
    fallback = toolchain.cache_dir() / "hybrid" / "missing-libs"
    env["LD_LIBRARY_PATH"] = ":".join(filter(None, [str(game / "lib64"), str(game),
                                                  env.get("LD_LIBRARY_PATH"), str(fallback)]))
    result = subprocess.run(["ldd", str(elf)], env=env, capture_output=True, text=True, check=True)
    paths = {}
    for line in result.stdout.splitlines():
        missing = re.match(r"\s*(\S+) => not found", line)
        if missing:
            name = missing.group(1)
            found = [game / "steam-runtime" / d / name
                     for d in ("usr/lib/x86_64-linux-gnu", "lib/x86_64-linux-gnu")]
            path = next((p for p in found if p.is_file()), None)
            if path is None:
                raise SystemExit("cannot fingerprint unresolved runtime library: " + name)
            paths[name] = path
        else:
            found = re.search(r"(?:=>\s*)?(/\S+)\s+\(0x", line)
            if found:
                path = Path(found.group(1))
                paths[path.name] = path
    if not paths:
        raise SystemExit("runtime dependency list missing; test evidence is unavailable")
    return [("runtime/" + name, path) for name, path in sorted(paths.items())]


def input_digest(db, root=None):
    root = Path(root) if root is not None else elfdb.ROOT
    paths = []
    for name in ("decomp", "tools/decomp", "third_party"):
        paths += directory_inputs(name, root / name, INPUT_SUFFIXES)
    # Recording accepted results must not invalidate itself.
    paths = [(name, path) for name, path in paths if name != "decomp/autotests.json"]
    types = root / "build-decomp/types.json"
    if not types.is_file():
        raise SystemExit("types.json missing; generate tests before fingerprinting their inputs")
    paths.append(("generated/types.json", types))
    compiler_root = toolchain.cache_dir() / "gcc447"
    paths += directory_inputs("toolchain", compiler_root)
    cfg = toolchain.config()
    for kind in ("include", "system_include"):
        for index, item in enumerate(cfg.get(kind, [])):
            item = item.replace("@OGRE@", str(compiler_root / "ogre-1.6.5/ogre"))
            directory = Path(item) if os.path.isabs(item) else root / item
            paths += directory_inputs("configured-" + kind + "/" + str(index), directory)
    for index, directory in enumerate(filter(None, os.environ.get("OTL_EXTRA_INCLUDE", "").split(":"))):
        paths += directory_inputs("extra-include/" + str(index), directory)
    elf = elfdb.default_elf()
    elf_hash = file_digest(elf)
    if elf_hash != db["original_elf_sha256"]:
        raise SystemExit("test evidence inputs use a different original ELF")
    paths += runtime_inputs(elf)
    for program in ("cc", "ld", "ldd"):
        executable = shutil.which(program)
        if not executable:
            raise SystemExit("missing evidence tool: " + program)
        paths.append(("host-tool/" + program, Path(executable)))
    db_hash = hashlib.sha256(json.dumps(db, sort_keys=True, separators=(",", ":")).encode()).hexdigest()
    context = {"original_elf_sha256": elf_hash, "database_digest": db_hash, "config": cfg,
               "extra_include": os.environ.get("OTL_EXTRA_INCLUDE", ""),
               "ld_library_path": os.environ.get("LD_LIBRARY_PATH", ""),
               "locale": {key: os.environ.get(key, "") for key in ("LANG", "LC_ALL", "TZ")}}
    return digest_paths(paths, context)


def tested(object_digest, inputs_digest, parameters):
    if not object_digest or not inputs_digest:
        raise ValueError("complete build and input digests are required")
    return {"schema": SCHEMA, "object_digest": object_digest,
            "inputs_digest": inputs_digest, "parameters": dict(parameters)}


def current(entry, object_digest, inputs_digest):
    value = entry.get("evidence") or {}
    return (value.get("schema") == SCHEMA and bool(object_digest) and bool(inputs_digest)
            and value.get("object_digest") == object_digest
            and value.get("inputs_digest") == inputs_digest and bool(value.get("parameters")))
