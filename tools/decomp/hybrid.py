#!/usr/bin/env python3
"""Hybrid build: decompiled TUs linked into the original game process.

Every decomp/src/**/*.cpp is compiled with the original toolchain to assembly.
Data the original already owns (globals, TU-local statics, vtables, RTTI, guard
variables) is redirected to its original address, so decompiled code operates on
the game's real objects; the TU's static constructors are dropped because the
original already ran them. The objects are linked at a fixed address within
rel32 range of the non-PIE executable; every other symbol resolves to the
original function, data or PLT entry. Functions of a decompiled TU replace the
original ones through 5-byte jumps installed by decomp/hybrid/loader.c.

    python3 tools/decomp/hybrid.py build
    python3 tools/decomp/hybrid.py selftest        # original vs decomp, exits before main
    python3 tools/decomp/hybrid.py run [-- ARGS]   # play with decompiled code (explicit task)
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import elfimage  # noqa: E402
import objdiff  # noqa: E402
import toolchain  # noqa: E402
import resource_slots  # noqa: E402

ROOT = elfdb.ROOT
SRC = ROOT / "decomp" / "src"
HYBRID = ROOT / "decomp" / "hybrid"
TESTS = HYBRID / "tests"
OUT = ROOT / "build-decomp" / "hybrid"
# Within rel32 and imm32 reach of the executable (0x400000..0x1600000), and above
# the brk heap: on x86-64 the kernel places it up to 1 GiB past the end of .bss.
BLOB_BASE = 0x60000000

LINKER_SCRIPT = """\
SECTIONS
{{
  . = {base:#x};
  __tlhybrid_text_start = .;
  .text : {{ *(.text .text.* .gnu.linkonce.t.*) }}
  __tlhybrid_text_end = .;
  . = ALIGN(4096);
  .rodata : {{ *(.rodata .rodata.* .gnu.linkonce.r.*) }}
  .eh_frame : {{ KEEP(*(.eh_frame)) LONG(0) }}
  .gcc_except_table : {{ *(.gcc_except_table .gcc_except_table.*) }}
  .tlhybrid.hooks : {{ KEEP(*(.tlhybrid.hooks)) }}
  .tlhybrid.comparisons : {{ KEEP(*(.tlhybrid.comparisons)) }}
  .tlhybrid.tests : {{ KEEP(*(.tlhybrid.tests)) }}
  .tlhybrid.imports : {{ KEEP(*(.tlhybrid.imports)) }}
  .tlhybrid.copies : {{ KEEP(*(.tlhybrid.copies)) }}
  . = ALIGN(4096);
  .data : {{ *(.data .data.* .gnu.linkonce.d.* .data.rel.ro .data.rel.ro.*) }}
  .tlhybrid.ctors : {{ KEEP(*(.ctors)) }}
  .bss : {{ *(.bss .bss.* .gnu.linkonce.b.*) *(COMMON) }}
  /DISCARD/ : {{ *(.note.GNU-stack) *(.comment) *(.dtors) *(.jcr) *(.eh_frame_hdr) }}
}}
INCLUDE originals.ld
"""


# Symbols the linker script defines for the blob's own code.
LINKER_DEFINED = {"__tlhybrid_text_start", "__tlhybrid_text_end"}


class Context:
    def __init__(self):
        self.db = elfdb.load_db()
        self.image = elfimage.load(elfdb.default_elf())
        self.functions = {int(a, 16): f for a, f in self.db["functions"].items()}
        self.order = sorted(self.functions)
        self.global_data = {}
        self.local_data = {}
        for g in self.db["globals"]:
            address = int(g["address"], 16)
            if g["bind"] == "local":
                self.local_data.setdefault(g["file"], {})[g["name"]] = address
            else:
                self.global_data[g["name"]] = address

    def tu_functions(self, tu):
        names = {}
        for address, f in self.functions.items():
            if f["tu"] == tu["id"]:
                for name in f["names"]:
                    names[name] = f
        return names


# --------------------------------------------------------------------------
# Assembly rewrite


SECTION_DIRECTIVE = re.compile(r"^\s*\.(text|data|bss|section\s+([^,\s]+).*|previous|pushsection\s+([^,\s]+).*|popsection)\s*$")
OBJECT_DIRECTIVE = re.compile(r"^\s*\.type\s+([^,\s]+),\s*@(?:gnu_unique_)?object\b")
COMM_DIRECTIVE = re.compile(r"^\s*\.(?:comm|lcomm)\s+([^,\s]+),")
ASM_LABEL = re.compile(r"^([^\s:.][^\s:]*):\s*$")
QUAD_DIRECTIVE = re.compile(r"^\s*\.quad\s")


def rewrite_assembly(text, redirect, drop_ctors):
    """Redirect owned data to original addresses; optionally drop .ctors entries."""
    lines = text.splitlines()
    objects = set()
    for line in lines:
        stripped = line.lstrip()
        if stripped.startswith(".type"):
            m = OBJECT_DIRECTIVE.match(line)
            if m:
                objects.add(m.group(1))
        elif stripped.startswith((".comm", ".lcomm")):
            m = COMM_DIRECTIVE.match(line)
            if m:
                objects.add(m.group(1))
    targets = {name: redirect[name] for name in objects if name in redirect}
    out, section, stack, dead = [], ".text", [], 0
    previous = ".text"
    for line in lines:
        stripped = line.lstrip()
        m = SECTION_DIRECTIVE.match(line) if stripped.startswith(".") else None
        if m:
            word = m.group(1).split()[0]
            if word in ("text", "data", "bss"):
                previous, section = section, "." + word
            elif word == "section":
                previous, section = section, m.group(2)
            elif word == "previous":
                previous, section = section, previous
            elif word == "pushsection":
                stack.append(section)
                section = m.group(3)
            elif word == "popsection":
                section = stack.pop()
            out.append(line)
            continue
        if drop_ctors and section == ".ctors" and stripped.startswith(".quad") and QUAD_DIRECTIVE.match(line):
            continue
        label = ASM_LABEL.match(line) if line.rstrip().endswith(":") else None
        if label and label.group(1) in targets:
            out.append(f".Ltlhybrid_dead_{dead}:")
            dead += 1
            continue
        comm = COMM_DIRECTIVE.match(line) if stripped.startswith((".comm", ".lcomm")) else None
        if comm and comm.group(1) in targets:
            continue
        out.append(line)
    for name, address in sorted(targets.items()):
        out.append(f"\t.set\t{name}, {address:#x}")
    return "\n".join(out) + "\n", sorted(targets)


# --------------------------------------------------------------------------


def defined_functions(obj_path):
    obj = elfimage.load_object(obj_path)
    return [(s.name, s.bind) for s in obj.symbols if s.type == elfimage.STT_FUNC and s.defined]


def undefined_symbols(obj_path):
    obj = elfimage.load_object(obj_path)
    return {s.name for s in obj.symbols if not s.defined and s.name}


def defined_symbols(obj_path):
    obj = elfimage.load_object(obj_path)
    return {s.name for s in obj.symbols if s.defined and s.name and s.bind != elfimage.STB_LOCAL}


def patch_window_ok(ctx, address):
    """5-byte jmp must fit before the next function and not hit an internal branch target."""
    i = ctx.order.index(address)
    nxt = ctx.order[i + 1] if i + 1 < len(ctx.order) else address + ctx.functions[address]["size"]
    if nxt - address < 5:
        return "function slot shorter than 5 bytes"
    f = ctx.functions[address]
    insns = objdiff.parse_insns(objdiff.run_objdump([f"--start-address={address:#x}",
                                                     f"--stop-address={address + f['size']:#x}",
                                                     str(ctx.image.path)]))
    for _, mnemonic, operands in insns:
        m = re.match(r"^([0-9a-f]+) <", operands)
        if m and mnemonic.startswith(("j", "loop", "call")):
            target = int(m.group(1), 16)
            if address < target < address + 5:
                return f"internal branch into the patched bytes ({target:#x})"
    return None


def originals_script(ctx, extra_aliases):
    lines = []
    seen = set()

    def provide(name, address):
        if name and name not in seen and '"' not in name:
            seen.add(name)
            lines.append(f'PROVIDE("{name}" = {address:#x});')

    local_counts = {}
    for f in ctx.functions.values():
        for name, bind in zip(f["names"], f["bind"]):
            if bind == "local":
                local_counts[name] = local_counts.get(name, 0) + 1
    for address, f in sorted(ctx.functions.items()):
        for name, bind in zip(f["names"], f["bind"]):
            if bind != "local":
                provide(name, address)
            if bind != "local" or local_counts.get(name) == 1:
                provide("__tlorig_" + name, address)
    for name, address in sorted(ctx.global_data.items()):
        provide(name, address)
    # Unique local data (e.g. the hidden __dso_handle) is unambiguous by name.
    local_data_counts = {}
    for symbols in ctx.local_data.values():
        for name in symbols:
            local_data_counts[name] = local_data_counts.get(name, 0) + 1
    for symbols in ctx.local_data.values():
        for name, address in symbols.items():
            if local_data_counts[name] == 1:
                provide(name, address)
    for address, name in sorted(ctx.image.plt.items()):
        provide(name.split("@")[0], address)
    for s in ctx.image.dynsyms:
        if s.defined and s.value and s.name:
            provide(s.name.split("@")[0], s.value)
    for name, address in extra_aliases:
        provide(name, address)
    return "\n".join(lines) + "\n", seen


def hooks_assembly(hooks, section=".tlhybrid.hooks", prefix="hook"):
    out = [f"\t.section {section},\"a\",@progbits", "\t.align 8"]
    names = ["\t.section .rodata.tlhybrid_names,\"a\",@progbits"]
    for i, hook in enumerate(hooks):
        out.append(f"\t.quad {hook['original']:#x}, {hook['symbol']}, .Ltlhybrid_{prefix}_name_{i}")
        out.append("\t.byte " + ", ".join(f"{b:#x}" for b in hook["expected"]))
        names.append(f".Ltlhybrid_{prefix}_name_{i}:\n\t.string \"{hook['demangled'][:200]}\"")
    return "\n".join(out + names) + "\n"


def comparison_entries(ctx, defined, hooks):
    """Callable emitted definitions outside their historical TU are testable too.

    These entries never patch the original executable. They bind real linked
    production symbols for execution receipts; test-only definitions are excluded.
    """
    by_name = {name: f for f in ctx.functions.values() for name in f["names"]
               if f["kind"] != "compiler"}
    hooked = {(h["original"], h["symbol"]) for h in hooks}
    rows = []
    for name in sorted(defined):
        f = by_name.get(name)
        if not f:
            continue
        address = int(f["address"], 16)
        if (address, name) in hooked:
            continue
        rows.append({"original": address, "symbol": name, "demangled": f["demangled"],
                     "expected": list(ctx.image.read(address, 8))})
    return rows


C_LOCALE = {**os.environ, "LC_ALL": "C"}


def needed_libraries(elf):
    """Paths of the executable's DT_NEEDED libraries, searched as the run sets LD_LIBRARY_PATH
    (the game's lib64, the game directory) and then as the system linker would."""
    game = Path(elf).parent
    dynamic = subprocess.run(["readelf", "-d", "-W", str(elf)], capture_output=True, text=True, check=True,
                             env=C_LOCALE).stdout
    system = {}
    for line in subprocess.run([shutil.which("ldconfig") or "/sbin/ldconfig", "-p"], capture_output=True, text=True, env=C_LOCALE).stdout.splitlines():
        m = re.match(r"\s+(\S+) \(([^)]*)\) => (\S+)", line)
        if m and "x86-64" in m.group(2):
            system.setdefault(m.group(1), m.group(3))
    out = []
    for name in re.findall(r"\(NEEDED\)\s+Shared library: \[([^\]]+)\]", dynamic):
        for candidate in (game / "lib64" / name, game / name, Path(system.get(name, "/nonexistent"))):
            if candidate.exists():
                out.append(candidate)
                break
    return out


def library_objects(elf, names):
    """name -> size of the data objects among names, from the libraries' dynamic symbols."""
    wanted, found = set(names), {}
    for lib in needed_libraries(elf):
        text = subprocess.run(["readelf", "--dyn-syms", "-W", str(lib)], capture_output=True, text=True,
                              env=C_LOCALE).stdout
        for line in text.splitlines():
            parts = line.split()
            if len(parts) < 8 or parts[3] not in ("OBJECT", "TLS") or parts[6] == "UND":
                continue
            name = parts[7].split("@")[0]
            if name in wanted and name not in found:
                found[name] = int(parts[2], 16) if parts[2].startswith("0x") else int(parts[2])
    return found


# Library data a copy may stand for: RTTI and vtables are never written, and type_info
# equality falls back to the name (libstdc++ __GXX_MERGED_TYPEINFO_NAMES == 0).
COPYABLE = ("_ZTI", "_ZTS", "_ZTV", "_ZTT")


def imports_assembly(names, objects=None):
    """Library symbols the original executable never imported. A function becomes a jump
    through a slot the loader fills. Code addresses data with 32-bit absolute relocations,
    so an object needs a place in the blob, which the loader fills with the library's bytes
    (what a COPY relocation would do for the executable)."""
    objects = objects or {}
    out = ["\t.text"]
    data = ["\t.data", "\t.align 8"]
    table = ["\t.section .tlhybrid.imports,\"a\",@progbits", "\t.align 8"]
    strings = ["\t.section .rodata.tlhybrid_imports,\"a\",@progbits"]
    copies = ["\t.section .tlhybrid.copies,\"a\",@progbits", "\t.align 8"]
    for i, name in enumerate(sorted(names)):
        strings.append(f".Ltlhybrid_import_{i}:\n\t.string \"{name}\"")
        if name in objects:
            data += ["\t.align 16", f"\t.globl {name}", f"\t.type {name}, @object", f"\t.size {name}, {objects[name]}",
                     f"{name}:", f"\t.zero {objects[name]}"]
            copies.append(f"\t.quad .Ltlhybrid_import_{i}, {name}, {objects[name]}")
            continue
        out += [f"\t.globl {name}", f"\t.type {name}, @function", f"{name}:",
                f"\tjmp *.Ltlhybrid_slot_{i}(%rip)"]
        data.append(f".Ltlhybrid_slot_{i}:\n\t.quad 0")
        table.append(f"\t.quad .Ltlhybrid_import_{i}, .Ltlhybrid_slot_{i}")
    return "\n".join(out + data + table + copies + strings) + "\n"


def build(out=OUT, verbose=True, src=SRC, tests=None):
    import publication
    with publication.tree_lock():
        return _build(out, verbose, src, tests)


def _build(out=OUT, verbose=True, src=SRC, tests=None):
    """src: decompiled sources (a mutated copy for tools/decomp/mutate.py);
    tests: test sources, by default decomp/hybrid/tests plus generated
    autotests when OTL_AUTOTEST=1."""
    ctx = Context()
    out.mkdir(parents=True, exist_ok=True)
    objects, hooks, notes = [], [], []
    production_undefined, production_defined = set(), set()
    data_redirects, omitted_initializers, source_versions = {}, {}, {}
    if tests is None:
        tests = sorted(TESTS.glob("*.cpp"))
        if os.environ.get("OTL_AUTOTEST"):
            # Generated differential tests (tools/decomp/autotest.py).
            tests += sorted((ROOT / "build-decomp" / "hybrid" / "autotests").glob("*.cpp"))
    units = [(p, False) for p in sorted(Path(src).rglob("*.cpp"))] + [(p, True) for p in tests]

    def compile_unit(unit):
        source, is_test = unit
        asm = out / f"{'test_' if is_test else ''}{source.stem}.s"
        toolchain.compile_source(source, asm, ["-I", str(HYBRID)], assembly=True)
    toolchain.parallel_map(compile_unit, units, phase="build")
    for source, is_test in units:
        tu = None if is_test else objdiff.tu_for_source(ctx.db, source)
        if not is_test and tu is None:
            raise SystemExit(f"{source}: no unique original TU named {source.name}")
        stem = ("test_" if is_test else "") + source.stem
        asm = out / f"{stem}.s"
        redirect = dict(ctx.global_data)
        if tu:
            redirect.update(ctx.local_data.get(tu["name"], {}))
        text, redirected = rewrite_assembly(asm.read_text(), redirect, drop_ctors=not is_test)
        if not is_test:
            relative = str(source.relative_to(ROOT))
            source_versions[relative] = hashlib.sha256(source.read_bytes()).hexdigest()
            data_redirects[relative] = sorted(redirected)
            omitted_initializers[relative] = sorted(set(re.findall(
                r"\.type\s+([^,\s]*(?:_GLOBAL__I_|__static_initialization)[^,\s]*),\s*@function", asm.read_text())))
        patched = out / f"{stem}.hybrid.s"
        patched.write_text(text)
        obj = out / f"{stem}.o"
        toolchain.assemble(patched, obj)
        objects.append(obj)
        if not is_test:
            production_defined |= defined_symbols(obj)
            production_undefined |= undefined_symbols(obj)
        unit_hooks = 0
        if tu:
            owned = ctx.tu_functions(tu)
            for name, bind in defined_functions(obj):
                f = owned.get(name)
                if not f or f["kind"] == "compiler":
                    continue
                address = int(f["address"], 16)
                if any(h["original"] == address for h in hooks):
                    continue
                problem = patch_window_ok(ctx, address)
                if problem:
                    notes.append(f"not hooked {f['demangled']}: {problem}")
                    continue
                hooks.append({"original": address, "symbol": name, "demangled": f["demangled"],
                              "expected": list(ctx.image.read(address, 8)), "unit": str(source.relative_to(ROOT))})
                unit_hooks += 1
        if verbose:
            print(f"  {source.relative_to(ROOT)}: {len(redirected)} data symbols redirected, {unit_hooks} hooks")

    hooks_s = out / "hooks.s"
    comparisons = comparison_entries(ctx, production_defined, hooks)
    hooks_s.write_text(hooks_assembly(hooks) + hooks_assembly(comparisons, ".tlhybrid.comparisons", "comparison"))
    toolchain.assemble(hooks_s, out / "hooks.o")
    script, provided = originals_script(ctx, [])
    (out / "originals.ld").write_text(script)
    defined = set()
    undefined = set()
    for obj in objects + [out / "hooks.o"]:
        defined |= defined_symbols(obj)
        undefined |= undefined_symbols(obj)
    missing = sorted(n for n in undefined - defined - provided - LINKER_DEFINED if not n.startswith(".L"))
    absent = objdiff.unknown_members(ctx.db, objdiff.image_symbol_names(ctx.image), missing)
    if absent:
        raise SystemExit("the decompiled code calls members the original does not have:\n" + "\n".join(
            f"  {n}; the original has: {'; '.join(objdiff.known_overloads(ctx.db, n)) or 'no such member'}"
            for n in absent))
    copies = library_objects(ctx.image.path, missing)
    shared = sorted(n for n in copies if not n.startswith(COPYABLE))
    if shared:
        raise SystemExit("the decompiled code uses library data the original never imported; a copy in the "
                         "blob would be a different object:\n" + "\n".join(f"  {n}" for n in shared))
    imports_s = out / "imports.s"
    imports_s.write_text(imports_assembly(missing, copies))
    toolchain.assemble(imports_s, out / "imports.o")
    (out / "hybrid.ld").write_text(LINKER_SCRIPT.format(base=BLOB_BASE))
    blob = out / "tlhybrid-blob.elf"
    subprocess.run(["ld", "-nostdlib", "-static", "-e", "0", "--build-id=none", "-z", "noexecstack",
                    "-z", "max-page-size=4096", "--no-warn-rwx-segments", "-T", "hybrid.ld", "-o", blob.name,
                    *[o.name for o in objects], "hooks.o", "imports.o"], cwd=out, check=True)
    loader = out / "libtlhybrid.so"
    toolchain.run_compiler(["cc", "-O2", "-Wall", "-Wextra", "-fPIC", "-shared", "-I", str(HYBRID), "-o", str(loader),
                    str(HYBRID / "loader.c"), "-ldl"], check=True)
    manifest = {"schema": 1, "original_elf_sha256": ctx.image.sha256, "blob_base": f"{BLOB_BASE:#x}",
                "hooks": [{k: (f"{v:#x}" if k == "original" else v) for k, v in h.items() if k != "expected"}
                          for h in hooks],
                "comparison_only": [{"original": f"{h['original']:#x}", "symbol": h["symbol"]} for h in comparisons],
                "runtime_imports": [n for n in missing if n not in copies],
                "runtime_copies": sorted(copies), "notes": notes}
    manifest["standalone_residual"] = {
        "schema": 1, "source_sha256": source_versions,
        "original_imports": sorted((production_undefined - production_defined) & provided),
        "runtime_library_imports": sorted((production_undefined - production_defined) & set(missing)),
        "original_data_redirects": {k: v for k, v in data_redirects.items() if v},
        "original_initializers_omitted": {k: v for k, v in omitted_initializers.items() if v},
        "rtti_imports": sorted(n for n in production_undefined - production_defined if n.startswith(("_ZTI", "_ZTS"))),
        "vtable_imports": sorted(n for n in production_undefined - production_defined if n.startswith("_ZTV")),
        "standalone_link_closed": False,
        "reason": "hybrid resolves original ELF addresses and omits original entrypoint/initialization; this is not a standalone game"}
    (out / "manifest.json").write_text(json.dumps(manifest, indent=1))
    if verbose:
        print(f"blob {blob.relative_to(ROOT)}: {len(hooks)} hooks, {len(missing) - len(copies)} runtime imports, "
              f"{len(copies)} copied library objects")
        for note in notes:
            print("  note:", note)
    return blob, loader


def stage_runtime(blob, loader):
    """ld.so splits LD_PRELOAD on spaces and colons; the repository path has a space."""
    payloads = [(Path(path), Path(path).read_bytes()) for path in (blob, loader)]
    identity = hashlib.sha256()
    for path, data in payloads:
        identity.update(path.name.encode() + b"\0" + hashlib.sha256(data).digest())
    # Separate immutable blob/loader pairs even within the same checkout.
    runtime = toolchain.cache_dir() / "hybrid" / hashlib.sha1(str(ROOT).encode()).hexdigest()[:12] / identity.hexdigest()
    runtime.mkdir(parents=True, exist_ok=True)
    staged = []
    for path, data in payloads:
        target = runtime / path.name
        if not target.exists() or target.read_bytes() != data:
            fd, temporary = tempfile.mkstemp(prefix=".stage-", dir=runtime)
            try:
                with os.fdopen(fd, "wb") as stream:
                    stream.write(data)
                os.replace(temporary, target)
            finally:
                Path(temporary).unlink(missing_ok=True)
        staged.append(target)
    for path in staged:
        if re.search(r"[\s:]", str(path)):
            raise SystemExit(f"runtime path unusable for LD_PRELOAD: {path}")
    return staged


def steam_runtime_fallback(game, env):
    """Directory with links to the libraries the system lacks (libGLU on a bare
    Fedora), taken from the game's own Steam runtime; None when nothing is missing.
    Only the missing ones are linked so the system copies of the rest still win."""
    result = subprocess.run(["ldd", str(game / "Torchlight.bin.x86_64")], env=env, capture_output=True, text=True)
    missing = re.findall(r"^\s*(\S+) => not found", result.stdout, re.M)
    if not missing:
        return None
    target = toolchain.cache_dir() / "hybrid" / "missing-libs"
    target.mkdir(parents=True, exist_ok=True)
    for name in missing:
        found = [p for d in ("usr/lib/x86_64-linux-gnu", "lib/x86_64-linux-gnu")
                 for p in [game / "steam-runtime" / d / name] if p.exists()]
        if not found:
            raise SystemExit(f"the game needs {name}: install it or put it into {target}")
        link = target / name
        if not link.exists():
            link.symlink_to(found[0].resolve())
    return target


def game_env(blob, loader, extra=None, headless=False):
    blob, loader = stage_runtime(blob, loader)
    game = Path(os.environ.get("TORCHLIGHT_GAME_DIR", Path.home() / "Games/Torchlight/game"))
    env = dict(os.environ)
    if headless:
        # Safety net: if the loader is not injected the game must not open a window.
        for name in ("DISPLAY", "WAYLAND_DISPLAY", "XAUTHORITY"):
            env.pop(name, None)
        env["SDL_VIDEODRIVER"] = "offscreen"
        env["SDL_AUDIODRIVER"] = "dummy"
    env["LD_LIBRARY_PATH"] = f"{game / 'lib64'}:{game}" + (":" + env["LD_LIBRARY_PATH"] if env.get("LD_LIBRARY_PATH") else "")
    fallback = steam_runtime_fallback(game, env)
    if fallback:
        env["LD_LIBRARY_PATH"] += f":{fallback}"
    env["LD_PRELOAD"] = str(loader)
    env["TLHYBRID_BLOB"] = str(blob)
    env.update(extra or {})
    return game, env


def selftest(blob, loader, only=None, shards=None):
    """Runs the blob's tests before main; only: test name prefix. Returns (code, report lines).
    The tests are split over `shards` game processes running at once (OTL_SELFTEST_SHARDS,
    by default up to 4); each process gets the whole timeout."""
    shards = shards or int(os.environ.get("OTL_SELFTEST_SHARDS", "0")) or min(4, toolchain.jobs())
    if shards < 1:
        raise ValueError("selftest needs at least one shard")
    extra = {"TLHYBRID_SELFTEST": "1"}
    if only:
        extra["TLHYBRID_FILTER"] = only

    game, env = game_env(blob, loader, extra, headless=True)  # stages the runtime once for all
    if not only:
        env.pop("TLHYBRID_FILTER", None)

    def run(index):
        try:
            with resource_slots.slot("selftest"):
                return subprocess.run([str(game / "Torchlight.bin.x86_64")], cwd=game,
                                      env={**env, "TLHYBRID_SHARD": f"{index}/{shards}"},
                                      capture_output=True, text=True,
                                      timeout=int(os.environ.get("OTL_SELFTEST_TIMEOUT", "120")))
        except subprocess.TimeoutExpired as error:
            from types import SimpleNamespace
            partial = error.stderr or ""
            if isinstance(partial, bytes):
                partial = partial.decode(errors="replace")
            return SimpleNamespace(returncode=2, stderr=partial +
                                   f"\nselftest: shard {index}/{shards} timeout after {error.timeout} seconds\n")
    code, report, ran, failed = 0, [], 0, 0
    for result in toolchain.parallel_map(run, range(shards), phase="selftest"):
        # Loader lines plus the indented details tests log under a failure.
        lines = [line for line in result.stderr.splitlines() if line.startswith(("tlhybrid:", "selftest:", "    "))]
        summary = next((re.match(r"tlhybrid: (\d+) tests, (\d+) failed", l) for l in lines if " tests, " in l), None)
        if not summary:
            return 2, report + lines + [result.stderr[-2000:],
                                        "selftest: complete loader report missing"]
        shard_ran, shard_failed = int(summary.group(1)), int(summary.group(2))
        expected_exit = 1 if shard_failed else 0
        if result.returncode != expected_exit:
            return 2, report + lines + [f"selftest: process exited {result.returncode}; report is not acceptance evidence"]
        ran += shard_ran
        failed += shard_failed
        report += [l for l in lines if l is not summary.string]
        code = max(code, result.returncode)
    if not ran:
        return 2, report + ["selftest: no tests executed"]
    return code, report + [f"tlhybrid: {ran} tests, {failed} failed"]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    sub.add_parser("build")
    sub.add_parser("selftest")
    run = sub.add_parser("run")
    run.add_argument("args", nargs="*")
    args = parser.parse_args()
    blob, loader = build()
    if args.command == "build":
        return 0
    if args.command == "selftest":
        code, report = selftest(blob, loader)
        print("\n".join(report))
        return code
    game, env = game_env(blob, loader)
    return subprocess.run([str(game / "Torchlight.bin.x86_64")] + args.args, cwd=game, env=env).returncode


if __name__ == "__main__":
    sys.exit(main())
