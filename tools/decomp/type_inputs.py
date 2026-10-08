"""Read-only identity of the inputs that shape a generated types.json.

Logical paths let a Stage copy keep the same identity. All pinned compiler and
configured SDK inputs are included; no size, ABI or container shape is inferred.
The actual generated-header fallback search mode is recorded as well as its
contents: enabling it can shadow an SDK header even if no file changed.
"""
import hashlib
import json
import os
from pathlib import Path

import elfdb
import toolchain

SCHEMA = 1
TOOLS = ("types_export.py", "type_inputs.py", "layout.py", "elfdb.py", "elfimage.py", "toolchain.py")
SEARCH_ENV = ("CPATH", "CPLUS_INCLUDE_PATH", "C_INCLUDE_PATH", "GCC_EXEC_PREFIX", "COMPILER_PATH")


def matched_addresses(root):
    progress = Path(root) / "build-decomp/progress.json"
    return sorted({row["address"] for unit in json.loads(progress.read_text())["units"]
                   for row in unit["functions"] if row["status"] == "MATCH"}) if progress.exists() else []


def capture(root):
    root = Path(root)
    files = {}

    def add(name, path):
        path = Path(path)
        files[name] = toolchain.sha256(path) if path.is_file() else None

    def directory(name, path):
        path = Path(path)
        files[name + "/"] = path.is_dir()
        if path.is_dir():
            for item in sorted(path.rglob("*")):
                if item.is_file() and "__pycache__" not in item.parts:
                    add(name + "/" + item.relative_to(path).as_posix(), item)

    config = root / "decomp/config.json"
    add("config", config)
    cfg = json.loads(config.read_text())
    compiler = toolchain.cache_dir() / "gcc447"
    directory("compiler", compiler)
    include_root = Path(os.environ.get("OTL_INCLUDE_ROOT", root))
    generated = root / "build-decomp/include-gen"
    directory("headers", root / "decomp/include")
    directory("generated", generated)
    for kind in ("include", "system_include"):
        for index, item in enumerate(cfg.get(kind, [])):
            item = item.replace("@OGRE@", str(compiler / "ogre-1.6.5/ogre"))
            path = Path(item)
            if not path.is_absolute():
                path = (include_root if kind == "include" and item.startswith("decomp/") else root) / item
            directory(f"{kind}/{index}", path)
    extra_search = []
    for index, item in enumerate(filter(None, os.environ.get("OTL_EXTRA_INCLUDE", "").split(":"))):
        path = Path(item)
        try:
            location = "@ROOT@/" + path.resolve().relative_to(root.resolve()).as_posix()
        except ValueError:
            location = str(path.resolve())
        extra_search.append(location)
        if path.resolve() != generated.resolve():
            directory(f"extra/{index}", path)
    # GCC may search these paths in addition to explicit -I/-isystem arguments.
    environment = {name: os.environ.get(name, "") for name in SEARCH_ENV}
    for name in ("CPATH", "CPLUS_INCLUDE_PATH", "C_INCLUDE_PATH"):
        value = environment[name]
        if value:
            for index, item in enumerate(value.split(":")):
                directory(f"environment/{name}/{index}", Path(item) if item else root)
    for name in TOOLS:
        add("tools/" + name, root / "tools/decomp" / name)
    add("database", root / "build-decomp/db/elfdb.json")
    add("elf", elfdb.default_elf())
    payload = {"schema": SCHEMA, "files": files, "matched": matched_addresses(root),
               "environment": environment, "extra_search": extra_search}
    return {"schema": SCHEMA, "sha256": hashlib.sha256(json.dumps(
        payload, sort_keys=True, separators=(",", ":")).encode()).hexdigest()}


def current(types, root):
    stamp = types.get("source_inputs")
    if not isinstance(stamp, dict) or stamp.get("schema") != SCHEMA:
        return False
    try:
        return stamp == capture(root)
    except (OSError, ValueError, KeyError):
        return False
