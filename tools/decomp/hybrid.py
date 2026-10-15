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
from dataclasses import dataclass
import hashlib
import json
import os
from pathlib import Path
import re
import resource
import shutil
import subprocess
import sys
import tempfile
import time

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import elfimage  # noqa: E402
import objdiff  # noqa: E402
import hybrid_disasm  # noqa: E402
import toolchain  # noqa: E402
import resource_slots  # noqa: E402
import selftest_schedule  # noqa: E402

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



def export_local_functions(text, owned, tu_id):
    """Expose recovered file-local functions to hooks without changing their linkage.

    Hook records live in a separate object, so a local symbol cannot satisfy
    their relocation. A TU-specific alias names the same code and avoids
    collisions between static helpers with identical names in different TUs.
    """
    labels = set(re.findall(r"^([^\s:.][^\s:]*):\s*$", text, re.M))
    aliases = {}
    for name, function in sorted(owned.items()):
        bindings = dict(zip(function["names"], function.get("bind", [])))
        if bindings.get(name) != "local" or name not in labels:
            continue
        alias = "__tlhybrid_local_%s_%s" % (tu_id, name)
        text += "\n\t.globl %s\n\t.set %s, %s\n" % (alias, alias, name)
        aliases[name] = alias
    return text, aliases

def defined_functions(obj_path):
    obj = elfimage.load_object(obj_path)
    return [(s.name, s.bind) for s in obj.symbols if s.type == elfimage.STT_FUNC and s.defined]


def undefined_symbols(obj_path):
    obj = elfimage.load_object(obj_path)
    return {s.name for s in obj.symbols if not s.defined and s.name}


def defined_symbols(obj_path):
    obj = elfimage.load_object(obj_path)
    return {s.name for s in obj.symbols if s.defined and s.name and s.bind != elfimage.STB_LOCAL}


@dataclass(frozen=True)
class ObjectSymbols:
    """Build-local immutable snapshot; never cache metadata by mutable path."""
    functions: tuple
    defined: frozenset
    undefined: frozenset


def object_symbols(obj_path):
    obj = elfimage.load_object(obj_path)
    return ObjectSymbols(
        tuple((s.name, s.bind) for s in obj.symbols if s.type == elfimage.STT_FUNC and s.defined),
        frozenset(s.name for s in obj.symbols if s.defined and s.name and s.bind != elfimage.STB_LOCAL),
        frozenset(s.name for s in obj.symbols if not s.defined and s.name))


def _replay_assembly_diagnostics(result):
    # Capture in workers and replay in input order, including the first failure.
    # Preserve bytes on ordinary streams; StringIO is useful to callers/tests.
    for stream, data in ((sys.stdout, result.stdout), (sys.stderr, result.stderr)):
        if data:
            stream.flush()
            if hasattr(stream, "buffer"):
                stream.buffer.write(data)
                stream.buffer.flush()
            else:
                stream.write(data.decode(errors="replace"))


class _BuildTimings:
    """Non-overlapping monotonic phases with measured process/child CPU.

    CPU counters are process-wide (including worker threads and reaped children),
    not sums of concurrent task wall times. Compiler slot waits remain included
    in phase wall time; they cannot be attributed from these counters alone.
    """
    def __init__(self):
        self.rows = []
        self.current = None
        self.started = self.sample()
        self.previous = self.started

    @staticmethod
    def sample():
        children = resource.getrusage(resource.RUSAGE_CHILDREN)
        return (time.monotonic(), time.process_time(), children.ru_utime + children.ru_stime)

    def phase(self, name):
        now = self.sample()
        if self.current is not None:
            self.rows.append(dict(name=self.current, **self.delta(self.previous, now)))
        self.current, self.previous = name, now

    @staticmethod
    def delta(start, end):
        return dict(wall_seconds=end[0] - start[0], process_cpu_seconds=end[1] - start[1],
                    children_cpu_seconds=end[2] - start[2])

    def write(self, out, status):
        self.phase(None)
        report = dict(schema=1, status=status, phases=self.rows,
                      total=self.delta(self.started, self.previous),
                      compiler_slot_wait_seconds=None,
                      note="CPU is process-wide; phase wall time includes unseparated compiler slot waits.")
        out.mkdir(parents=True, exist_ok=True)
        fd, temporary = tempfile.mkstemp(prefix=".build-timings-", dir=out)
        try:
            with os.fdopen(fd, "w") as stream:
                json.dump(report, stream, indent=1)
                stream.write("\n")
            os.replace(temporary, out / "build-timings.json")
        finally:
            Path(temporary).unlink(missing_ok=True)


def patch_window_ok(ctx, address):
    """5-byte jmp must fit before the next function and not hit an internal branch target."""
    i = ctx.order.index(address)
    nxt = ctx.order[i + 1] if i + 1 < len(ctx.order) else address + ctx.functions[address]["size"]
    if nxt - address < 5:
        return "function slot shorter than 5 bytes"
    f = ctx.functions[address]
    if int(f["address"], 16) != address:
        raise RuntimeError("original function address disagrees with patch-window address")
    if not hasattr(ctx, "_patch_window_instructions"):
        ctx._patch_window_instructions = hybrid_disasm.PatchWindowInstructions(
            ctx.db, ctx.image, objdiff.run_objdump, objdiff.parse_insns)
    insns = ctx._patch_window_instructions.instructions(
        ctx.image, f, objdiff.run_objdump, objdiff.parse_insns)
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


def _write_build_timings(timing, out, status):
    # Observational instrumentation must not replace success or the real error,
    # including when disk space or the diagnostic stream is exhausted.
    try:
        timing.write(out, status)
    except Exception as error:
        try:
            print(f"could not write hybrid build timings: {error}", file=sys.stderr)
        except Exception:
            pass


def _independent_unit_outputs(out, stems):
    output_stems = [*stems, "hooks", "imports"]
    if len(set(output_stems)) != len(output_stems):
        return False
    for stem in output_stems:
        for suffix in (".s", ".hybrid.s", ".o"):
            path = out / (stem + suffix)
            try:
                if path.is_symlink() or (path.exists() and path.stat().st_nlink != 1):
                    return False
            except OSError:
                return False
    return True


def _build(out=OUT, verbose=True, src=SRC, tests=None):
    timing = _BuildTimings()
    try:
        result = _build_impl(out, verbose, src, tests, timing)
    except BaseException:
        _write_build_timings(timing, out, "failed")
        raise
    _write_build_timings(timing, out, "completed")
    return result


def _build_impl(out, verbose, src, tests, timing):
    """src: decompiled sources (a mutated copy for tools/decomp/mutate.py);
    tests: test sources, by default decomp/hybrid/tests plus generated
    autotests when OTL_AUTOTEST=1."""
    timing.phase("context")
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
        extra = ["-I", str(HYBRID)] if is_test else []
        toolchain.compile_source(source, asm, extra, assembly=True)
    timing.phase("compile")
    toolchain.parallel_map(compile_unit, units, phase="build")
    timing.phase("rewrite_assemble_metadata")

    def prepare_unit(unit):
        # Workers never mutate shared reductions. Return failures so diagnostics
        # and the first exception can be replayed in the original source order.
        try:
            return prepare_one(unit)
        except (Exception, SystemExit) as error:
            return {"error": error}

    def prepare_one(unit):
        source, is_test = unit
        tu = None if is_test else objdiff.tu_for_source(ctx.db, source)
        if not is_test and tu is None:
            raise SystemExit(f"{source}: no unique original TU named {source.name}")
        stem = ("test_" if is_test else "") + source.stem
        asm = out / f"{stem}.s"
        redirect = dict(ctx.global_data)
        if tu:
            redirect.update(ctx.local_data.get(tu["name"], {}))
        text, redirected = rewrite_assembly(asm.read_text(), redirect, drop_ctors=not is_test)
        local_aliases = {}
        if tu:
            text, local_aliases = export_local_functions(text, ctx.tu_functions(tu), tu["id"])
        source_sha256 = None
        omitted = []
        if not is_test:
            source_sha256 = hashlib.sha256(source.read_bytes()).hexdigest()
            omitted = sorted(set(re.findall(
                r"\.type\s+([^,\s]*(?:_GLOBAL__I_|__static_initialization)[^,\s]*),\s*@function", asm.read_text())))
        patched = out / f"{stem}.hybrid.s"
        patched.write_text(text)
        obj = out / f"{stem}.o"
        diagnostics = toolchain.assemble(patched, obj, capture_output=True)
        try:
            symbols = object_symbols(obj)
        except (Exception, SystemExit) as error:
            return {"error": error, "diagnostics": diagnostics}
        return dict(tu=tu, obj=obj, symbols=symbols, redirected=redirected, local_aliases=local_aliases,
                    source_sha256=source_sha256, omitted=omitted, diagnostics=diagnostics)

    stems = [("test_" if is_test else "") + source.stem for source, is_test in units]
    independent_outputs = _independent_unit_outputs(out, stems)
    if independent_outputs:
        prepared = toolchain.parallel_map(prepare_unit, units, phase="build")
    else:
        # Legacy layouts or pre-existing links can alias an output path. Keep
        # serial writes and refresh final summaries after all such writes.
        prepared = [prepare_unit(unit) for unit in units]
    timing.phase("hook_reduction")
    final_symbols = {}
    for (source, is_test), result in zip(units, prepared):
        error = result.get("error")
        diagnostics = result.get("diagnostics")
        if diagnostics is not None:
            _replay_assembly_diagnostics(diagnostics)
        if error is not None:
            if isinstance(error, subprocess.CalledProcessError):
                _replay_assembly_diagnostics(error)
            raise error
        tu, obj, symbols = result["tu"], result["obj"], result["symbols"]
        redirected = result["redirected"]
        objects.append(obj)
        final_symbols[obj] = symbols
        if not is_test:
            relative = str(source.relative_to(ROOT))
            source_versions[relative] = result["source_sha256"]
            data_redirects[relative] = sorted(redirected)
            omitted_initializers[relative] = result["omitted"]
            production_defined |= symbols.defined
            production_undefined |= symbols.undefined
        unit_hooks = 0
        if tu:
            owned = ctx.tu_functions(tu)
            for name, bind in symbols.functions:
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
                hooks.append({"original": address, "symbol": result["local_aliases"].get(name, name), "demangled": f["demangled"],
                              "expected": list(ctx.image.read(address, 8)), "unit": str(source.relative_to(ROOT))})
                unit_hooks += 1
        if verbose:
            print(f"  {source.relative_to(ROOT)}: {len(redirected)} data symbols redirected, {unit_hooks} hooks")

    timing.phase("hooks_imports")
    hooks_s = out / "hooks.s"
    comparisons = comparison_entries(ctx, production_defined, hooks)
    hooks_s.write_text(hooks_assembly(hooks) + hooks_assembly(comparisons, ".tlhybrid.comparisons", "comparison"))
    toolchain.assemble(hooks_s, out / "hooks.o")
    script, provided = originals_script(ctx, [])
    (out / "originals.ld").write_text(script)
    defined = set()
    undefined = set()
    if not independent_outputs:
        final_symbols = {obj: object_symbols(obj) for obj in dict.fromkeys(objects)}
    final_symbols[out / "hooks.o"] = object_symbols(out / "hooks.o")
    for obj in objects + [out / "hooks.o"]:
        symbols = final_symbols[obj]
        defined |= symbols.defined
        undefined |= symbols.undefined
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
    timing.phase("link")
    blob = out / "tlhybrid-blob.elf"
    subprocess.run(["ld", "-nostdlib", "-static", "-e", "0", "--build-id=none", "-z", "noexecstack",
                    "-z", "max-page-size=4096", "--no-warn-rwx-segments", "-T", "hybrid.ld", "-o", blob.name,
                    *[o.name for o in objects], "hooks.o", "imports.o"], cwd=out, check=True)
    timing.phase("loader")
    loader = out / "libtlhybrid.so"
    toolchain.run_compiler(["cc", "-O2", "-Wall", "-Wextra", "-fPIC", "-shared", "-I", str(HYBRID), "-o", str(loader),
                    str(HYBRID / "loader.c"), "-ldl"], check=True)
    timing.phase("manifest")
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
    selftest_schedule.write_inputs(blob, [obj for (_, is_test), obj in zip(units, objects) if is_test], ROOT)
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
    started = time.monotonic()
    evidence = {"schema": 1, "clock": "time.monotonic", "started": started,
                "shard_count": shards, "phases": {}, "shards": []}
    try:
        return _selftest(blob, loader, only, shards, evidence)
    finally:
        evidence["ended"] = time.monotonic()
        evidence["elapsed"] = evidence["ended"] - started
        selftest_schedule.write_timing(blob, evidence)


def _selftest(blob, loader, only, shards, evidence):
    phase = time.monotonic()
    extra = {"TLHYBRID_SELFTEST": "1"}
    if only:
        extra["TLHYBRID_FILTER"] = only

    game, env = game_env(blob, loader, extra, headless=True)  # stages the runtime once for all
    if not only:
        env.pop("TLHYBRID_FILTER", None)
    evidence["phases"]["environment"] = time.monotonic() - phase
    phase = time.monotonic()
    schedule = selftest_schedule.plan(blob, ROOT, only, shards)
    order = schedule["order"]
    if sorted(order) != list(range(shards)):
        raise ValueError("selftest schedule must execute every shard exactly once")
    evidence["schedule"] = schedule
    evidence["phases"]["schedule"] = time.monotonic() - phase
    # Enqueue timestamps precede submission. Workers timestamp actual dispatch
    # separately so executor queue wait and shared-slot wait remain distinguishable.
    timings = [{"index": index, "enqueued": None, "dispatched": None, "slot_acquired": None,
                "process_started": None, "ended": None, "elapsed": None, "returncode": None}
               for index in range(shards)]
    evidence["shards"] = timings
    def queued_indices():
        for index in order:
            timings[index]["enqueued"] = time.monotonic()
            yield index

    def run(index):
        row = timings[index]
        row["dispatched"] = time.monotonic()
        try:
            with resource_slots.slot("selftest"):
                row["slot_acquired"] = time.monotonic()
                row["process_started"] = time.monotonic()
                try:
                    result = subprocess.run([str(game / "Torchlight.bin.x86_64")], cwd=game,
                                            env={**env, "TLHYBRID_SHARD": f"{index}/{shards}"},
                                            capture_output=True, text=True,
                                            timeout=int(os.environ.get("OTL_SELFTEST_TIMEOUT", "120")))
                except subprocess.TimeoutExpired as error:
                    from types import SimpleNamespace
                    partial = error.stderr or ""
                    if isinstance(partial, bytes):
                        partial = partial.decode(errors="replace")
                    result = SimpleNamespace(returncode=2, stderr=partial +
                                             f"\nselftest: shard {index}/{shards} timeout after {error.timeout} seconds\n")
                    row["timeout"] = error.timeout
                row["returncode"] = result.returncode
                return index, result
        except BaseException as error:
            row["error"] = type(error).__name__ + ": " + str(error)
            raise
        finally:
            row["ended"] = time.monotonic()
            if row["process_started"] is not None:
                row["elapsed"] = row["ended"] - row["process_started"]
            row["queue_elapsed"] = row["dispatched"] - row["enqueued"]
            row["slot_wait_elapsed"] = ((row["slot_acquired"] or row["ended"]) - row["dispatched"])

    phase = time.monotonic()
    try:
        rows = toolchain.parallel_map(run, queued_indices(), phase="selftest")
        results = selftest_schedule.ordered_results(rows, shards)
    except ValueError as error:
        evidence["error"] = str(error)
        return 2, ["selftest: " + str(error)]
    finally:
        evidence["phases"]["execute"] = time.monotonic() - phase
    phase = time.monotonic()
    try:
        selftest_schedule.validate_inventory(results, schedule["selected"])
        code, report = _selftest_report(results)
        evidence["returncode"] = code
        if code in (0, 1):
            try:
                selftest_schedule.save_costs(schedule, results)
            except (OSError, ValueError) as error:
                evidence["timing_hint_error"] = str(error)
        return code, report
    except ValueError as error:
        evidence["error"] = str(error)
        # Keep the complete fresh process diagnostics on rejected inventories.
        return 2, [result.stderr for result in results] + ["selftest: " + str(error)]
    finally:
        evidence["phases"]["parse"] = time.monotonic() - phase


def _selftest_report(results):
    code, report, ran, failed = 0, [], 0, 0
    for result in results:
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
