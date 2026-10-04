#!/usr/bin/env python3
"""Compare decompiled functions with the original machine code.

Compiles a decomp source with the original toolchain (GCC 4.1.2-51), then
compares every function symbol of the object with the original function of the
same mangled name. Instructions are normalized: relocated operands and absolute
addresses become symbol names, string literals become their contents, float
constants become their bytes and intra-function branches become instruction
indices. Exact equality of the normalized streams is reported as MATCH.

    python3 tools/decomp/objdiff.py decomp/src/RunicCore.cpp
    python3 tools/decomp/objdiff.py decomp/src/RunicCore.cpp --show _ZN10CRunicCoreC2Ev
    python3 tools/decomp/objdiff.py --all --json build-decomp/progress.json
"""
from __future__ import annotations

import argparse
import bisect
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import elfimage  # noqa: E402
import toolchain  # noqa: E402

ROOT = elfdb.ROOT
SRC = ROOT / "decomp" / "src"
INSN = re.compile(r"^\s*([0-9a-f]+):\s+(\S+(?: \S+)?)\s*(.*)$")
PREFIXES = ("rep", "repz", "repnz", "lock", "data16", "cs", "ds", "addr32", "rex", "rex.W")
PC_RELATIVE = {2, 4}          # R_X86_64_PC32, R_X86_64_PLT32
ABSOLUTE = {1, 10, 11}        # R_X86_64_64, R_X86_64_32, R_X86_64_32S
PACKED = ("ps", "pd", "dqa", "dqu", "aps", "apd")


def const_size(mnemonic):
    if mnemonic.endswith(PACKED) or mnemonic in ("pxor", "pand", "por", "andps", "xorps"):
        return 16
    if "sd" in mnemonic or mnemonic.endswith("q"):
        return 8
    return 4


def printable_string(raw):
    """Literal token for narrow (ASCII) or wide (UTF-32LE wchar_t) strings."""
    wide = []
    for i in range(0, len(raw) - 3, 4):
        code = int.from_bytes(raw[i:i + 4], "little")
        if code == 0:
            break
        if not (32 <= code < 0x10000 or code in (9, 10, 13)):
            wide = None
            break
        wide.append(chr(code))
    else:
        wide = None
    if wide:
        return 'L"' + "".join(wide)
    end = raw.find(b"\0")
    if end <= 0:
        return None
    text = raw[:end]
    if all(32 <= b < 127 or b in (9, 10, 13) for b in text):
        return text.decode("ascii")
    return None


def literal_token(raw):
    # Width is not part of the token: L"1" and "1" plus padding share bytes, and
    # the consuming call (string vs wstring) already tells them apart.
    text = printable_string(raw)
    if text is None:
        return None
    if text.startswith('L"'):
        text = text[2:]
    return f'lit:"{text[:80]}"'


def run_objdump(args):
    env = dict(os.environ, LC_ALL="C")
    return subprocess.run(["objdump", "-d", "-w", "--no-show-raw-insn"] + args, check=True,
                          capture_output=True, text=True, env=env).stdout


def parse_insns(text):
    out = []
    for line in text.splitlines():
        m = INSN.match(line)
        if m and not line.lstrip().startswith(("R_X86", "Disassembly")):
            mnemonic, operands = m.group(2), m.group(3).strip()
            # objdump prints prefixes as part of the mnemonic field ("repz ret").
            first = mnemonic.split(" ")
            if len(first) == 2 and first[0] not in PREFIXES:
                mnemonic, operands = first[0], (first[1] + " " + operands).strip()
            out.append([int(m.group(1), 16), mnemonic, operands])
    return out


class Normalizer:
    """Shared operand normalization; subclasses resolve addresses to tokens."""

    JUMP_TABLE = re.compile(r"^\*(0x[0-9a-f]+)\(,(%\w+),8\)$")

    def branch(self, insn_index, target, start, end, offsets):
        if start <= target < end:
            labels = getattr(self, "labels", None)
            if labels and target in labels:
                return f"L{labels[target]}"
            pos = bisect.bisect_left(offsets, target)
            return f"L{pos}" if pos < len(offsets) and offsets[pos] == target else f"L?{target - start:#x}"
        return None

    @staticmethod
    def table_size(k, insns):
        """Entries of a switch table from the bound check (`cmp $N` before the jump)."""
        for _, mnemonic, operands in reversed(insns[max(0, k - 6):k]):
            m = re.match(r"^\$0x([0-9a-f]+),", operands)
            if mnemonic.startswith("cmp") and m:
                return int(m.group(1), 16) + 1
        return None

    def jump_table(self, k, entries, register, start, end, offsets, insns):
        """Token for `jmp *table(,%reg,8)`: the table's targets as instruction labels."""
        count = self.table_size(k, insns)
        labels = []
        for target in entries:
            if count is not None and len(labels) == count:
                break
            if target is None or not start <= target < end:
                break
            labels.append(self.branch(k, target, start, end, offsets))
        return f"jmp *[table:{','.join(labels)}](,{register},8)"

    @staticmethod
    def padding(mnemonic, operands):
        return (mnemonic in ("nop", "nopw", "nopl", "xchg") and (mnemonic != "xchg" or operands == "%ax,%ax")
                or mnemonic.startswith(("data16", "cs")))

    def normalize(self, insns, start, end):
        offsets = [i[0] for i in insns]
        # Branch labels count kept instructions only: alignment padding differs
        # between the original and our object and must not shift the indices.
        self.labels = {}
        kept = 0
        for address, mnemonic, operands in insns:
            self.labels[address] = kept
            if not self.padding(mnemonic, operands):
                kept += 1
        result = []
        for k, (address, mnemonic, operands) in enumerate(insns):
            if self.padding(mnemonic, operands):
                continue
            nxt = offsets[k + 1] if k + 1 < len(offsets) else end
            operands = operands.split("#", 1)[0].strip() if "#" in operands and "(%rip)" in operands else operands
            result.append(self.token(k, address, nxt, mnemonic, operands, start, end, offsets, insns))
        while result and result[-1].split(" ")[0] in ("nop", "xchg"):
            result.pop()
        return result


class OriginalSide(Normalizer):
    def __init__(self, image, db):
        self.image = image
        self.func_start = {int(a, 16): f["mangled"] for a, f in db["functions"].items()}
        objects = []
        for s in image.symbols:
            if s.type == elfimage.STT_OBJECT and s.defined and s.size and s.name:
                objects.append((s.value, s.size, s.name))
        for s in image.dynsyms:
            if s.type == elfimage.STT_OBJECT and s.defined and s.size and s.name:
                objects.append((s.value, s.size, s.name))
        objects.sort()
        self.obj_starts = [o[0] for o in objects]
        self.objects = objects
        # Exact-address names, including zero-sized markers such as __dso_handle.
        self.exact = {}
        for s in list(image.symbols) + list(image.dynsyms):
            if s.defined and s.name and s.type in (elfimage.STT_OBJECT, elfimage.STT_NOTYPE) and s.value:
                self.exact.setdefault(s.value, s.name.split("@")[0])
        self.rodata = [image.section(n) for n in (".rodata",) if n]
        self.low, self.high = 0x400000, max(s.addr + s.size for s in image.sections if s.addr)

    def name_at(self, address, mnemonic):
        if address in self.func_start:
            return self.func_start[address]
        if address in self.image.plt:
            return self.image.plt[address].split("@")[0]
        i = bisect.bisect_right(self.obj_starts, address) - 1
        if i >= 0:
            start, size, name = self.objects[i]
            name = name.split("@")[0]
            if start <= address < start + size:
                return name if address == start else f"{name}+{address - start:#x}"
        if address in self.exact:
            return self.exact[address]
        section = self.image.section_at(address)
        if section and section.name.startswith(".rodata"):
            try:
                raw = self.image.read(address, 256)
            except ValueError:
                raw = b""
            token = literal_token(raw)
            if token is not None:
                return token
            if mnemonic == "mov" and raw[:1] == b"\0":
                # An empty string literal: its neighbours are arbitrary.
                return 'lit:""'
            n = const_size(mnemonic)
            return "const:" + raw[:n].hex()
        if section:
            return f"{section.name}:{address:#x}"
        return f"{address:#x}"

    def token(self, k, address, nxt, mnemonic, operands, start, end, offsets, insns):
        m = re.match(r"^([0-9a-f]+) <([^>]+)>$", operands)
        if m and (mnemonic.startswith(("j", "call", "loop"))):
            target = int(m.group(1), 16)
            label = self.branch(k, target, start, end, offsets)
            if label:
                return f"{mnemonic} {label}"
            return f"{mnemonic} {self.name_at(target, mnemonic)}"
        table = self.JUMP_TABLE.match(operands) if mnemonic == "jmp" else None
        if table:
            base = int(table.group(1), 16)

            def entries():
                for i in range(4096):
                    try:
                        yield int.from_bytes(self.image.read(base + 8 * i, 8), "little")
                    except ValueError:
                        return
            return self.jump_table(k, entries(), table.group(2), start, end, offsets, insns)

        def rip(mm):
            target = nxt + int(mm.group(1), 16) * (-1 if mm.group(0).startswith("-") else 1)
            return f"[{self.name_at(target, mnemonic)}](%rip)"
        operands = re.sub(r"-?0x([0-9a-f]+)\(%rip\)", rip, operands)

        def absolute(mm):
            value = int(mm.group(2), 16)
            if self.low <= value < self.high:
                return f"{mm.group(1)}[{self.name_at(value, mnemonic)}]"
            return mm.group(0)
        operands = re.sub(r"(\$|(?<![\w%]))0x([0-9a-f]+)(?=\b)", absolute, operands)
        return f"{mnemonic} {operands}".strip()


class ObjectSide(Normalizer):
    def __init__(self, obj, resolve=None, name_at=None):
        self.obj = obj
        self.resolve = resolve or (lambda name: None)
        self.name_at = name_at
        self.funcs_by_section = {}
        for s in obj.symbols:
            if s.type == elfimage.STT_FUNC and s.defined:
                self.funcs_by_section.setdefault(s.shndx, {})[s.value] = s.name
        self.locals_by_section = {}
        for s in obj.symbols:
            if s.type == elfimage.STT_OBJECT and s.defined and s.shndx < len(obj.sections):
                self.locals_by_section.setdefault(s.shndx, {})[s.value] = s.name

    def target_name(self, symbol, offset, mnemonic):
        obj = self.obj
        if symbol.name and not symbol.name.startswith(".L") and symbol.type != elfimage.STT_SECTION:
            # Same token as the original side: symbol + addend mapped to the original address.
            address = self.resolve(symbol.name)
            if address is not None and self.name_at:
                return self.name_at(address + offset, mnemonic)
        if symbol.defined and symbol.shndx < len(obj.sections) and (
                symbol.type == elfimage.STT_SECTION or not symbol.name or symbol.name.startswith(".L")):
            offset += symbol.value if symbol.type != elfimage.STT_SECTION else 0
            section = obj.sections[symbol.shndx]
            name = section.name
            if name.startswith(".rodata"):
                raw = obj.section_bytes(symbol.shndx)[offset:offset + 256]
                token = literal_token(raw)
                if token is not None:
                    return token
                if name.startswith(".rodata.str") and raw[:1] == b"\0":
                    return 'lit:""'
                return "const:" + raw[:const_size(mnemonic)].hex()
            named = self.locals_by_section.get(symbol.shndx, {}).get(offset)
            if named:
                return named
            func = self.funcs_by_section.get(symbol.shndx, {}).get(offset)
            if func:
                return func
            return f"{name}+{offset:#x}"
        return symbol.name if offset == 0 else f"{symbol.name}+{offset:#x}"

    def prepare(self, section_index):
        self.relocs = sorted(self.obj.relocs.get(section_index, []), key=lambda r: r.offset)
        self.reloc_offsets = [r.offset for r in self.relocs]
        self.section_index = section_index

    def token(self, k, address, nxt, mnemonic, operands, start, end, offsets, insns):
        lo = bisect.bisect_left(self.reloc_offsets, address)
        hi = bisect.bisect_left(self.reloc_offsets, nxt)
        relocs = self.relocs[lo:hi]
        table = self.JUMP_TABLE.match(operands) if mnemonic == "jmp" and len(relocs) == 1 else None
        if table and relocs[0].symbol.shndx < len(self.obj.sections):
            symbol = relocs[0].symbol
            base = relocs[0].addend + (symbol.value if symbol.type != elfimage.STT_SECTION else 0)
            rows = {r.offset: r for r in self.obj.relocs.get(symbol.shndx, [])}

            def entries():
                for i in range(4096):
                    r = rows.get(base + 8 * i)
                    if r is None or r.symbol.shndx != self.section_index:
                        return
                    yield r.addend + (r.symbol.value if r.symbol.type != elfimage.STT_SECTION else 0)
            return self.jump_table(k, entries(), table.group(2), start, end, offsets, insns)
        m = re.match(r"^([0-9a-f]+) <([^>]+)>$", operands)
        if m and mnemonic.startswith(("j", "call", "loop")):
            if relocs:
                r = relocs[0]
                offset = r.addend + (nxt - r.offset) if r.type in PC_RELATIVE else r.addend
                if r.symbol.name and r.symbol.name == getattr(self, "current", None) and offset == 0:
                    # Direct recursion: the original side sees a branch to its own entry.
                    return f"{mnemonic} {self.branch(k, start, start, end, offsets)}"
                return f"{mnemonic} {self.target_name(r.symbol, offset, mnemonic)}"
            target = int(m.group(1), 16)
            label = self.branch(k, target, start, end, offsets)
            if label:
                return f"{mnemonic} {label}"
            func = self.funcs_by_section.get(self.section_index, {}).get(target)
            return f"{mnemonic} {func or hex(target)}"
        for r in relocs:
            if r.type in PC_RELATIVE:
                name = self.target_name(r.symbol, r.addend + (nxt - r.offset), mnemonic)
                operands = re.sub(r"-?0x[0-9a-f]+\(%rip\)", lambda _: f"[{name}](%rip)", operands, count=1)
            elif r.type in ABSOLUTE:
                name = self.target_name(r.symbol, r.addend, mnemonic)
                imm_last = r.offset == nxt - 4 and "$" in operands
                if imm_last:
                    operands = re.sub(r"\$0x[0-9a-f]+", lambda _: f"$[{name}]", operands, count=1)
                else:
                    operands = re.sub(r"(?<![\w%$])0x[0-9a-f]+(?=\()", lambda _: f"[{name}]", operands, count=1)
        return f"{mnemonic} {operands}".strip()


def object_functions(obj_path, resolve=None, name_at=None, globalized=()):
    obj = elfimage.load_object(obj_path)
    text = run_objdump([str(obj_path)])
    sections = {}
    current = None
    for line in text.splitlines():
        m = re.match(r"^Disassembly of section (.+):$", line)
        if m:
            current = m.group(1)
            sections[current] = []
            continue
        if current is not None:
            sections[current].append(line)
    by_name = {s.name: s.index for s in obj.sections}
    side = ObjectSide(obj, resolve, name_at)
    result = {}
    for sym in obj.symbols:
        if sym.type != elfimage.STT_FUNC or not sym.defined:
            continue
        section = obj.sections[sym.shndx]
        insns = [i for i in parse_insns("\n".join(sections.get(section.name, [])))
                 if sym.value <= i[0] < sym.value + sym.size]
        side.prepare(by_name[section.name])
        side.current = sym.name
        bind = elfimage.STB_LOCAL if sym.name in globalized else sym.bind
        result[sym.name] = {"size": sym.size, "bind": bind,
                            "norm": side.normalize(insns, sym.value, sym.value + sym.size)}
    return result


class Original:
    def __init__(self, db=None, elf=None):
        self.db = db or elfdb.load_db()
        self.image = elfimage.load(elf or elfdb.default_elf())
        self.side = OriginalSide(self.image, self.db)
        self.by_name = {}
        for address, f in self.db["functions"].items():
            for name in f["names"]:
                self.by_name.setdefault(name, []).append(f)

    def resolver(self, tu):
        data = {}
        for g in self.db["globals"]:
            if g["bind"] != "local":
                data.setdefault(g["name"], int(g["address"], 16))
        if tu:
            for g in self.db["globals"]:
                if g["bind"] == "local" and g["file"] == tu["name"]:
                    data[g["name"]] = int(g["address"], 16)
        imports = {n.split("@")[0]: a for a, n in self.image.plt.items()}
        for s in self.image.dynsyms:
            if s.defined and s.value and s.name:
                imports.setdefault(s.name.split("@")[0], s.value)

        def resolve(name):
            if name in data:
                return data[name]
            f = self.function(name, False, tu)
            if f and any(b != "local" for n, b in zip(f["names"], f["bind"]) if n == name):
                return int(f["address"], 16)
            f = self.function(name, True, tu)
            if f:
                return int(f["address"], 16)
            return imports.get(name)
        return resolve

    def function(self, name, local=False, tu=None):
        found = self.by_name.get(name) or []
        if local:
            # Local names (__tcf_0, _GLOBAL__I_..., static functions) repeat across TUs.
            found = [f for f in found if tu is not None and f["tu"] == tu["id"]]
        return found[0] if found else None

    def normalized(self, f):
        """Normalized original function; cached on disk (the original never changes)."""
        cache = self.__dict__.get("_norm_cache")
        if cache is None:
            cache = self.__dict__["_norm_cache"] = _load_norm_cache()
        key = f["address"]
        if key not in cache:
            start = int(f["address"], 16)
            end = start + f["size"]
            insns = parse_insns(run_objdump([f"--start-address={start:#x}", f"--stop-address={end:#x}",
                                             str(self.image.path)]))
            cache[key] = self.side.normalize(insns, start, end)
            _NORM_DIRTY.add(key)
        return cache[key]


NORM_CACHE = Path(__file__).resolve().parents[2] / "build-decomp" / "db" / "orig-normalized.pickle"
_NORM_DIRTY = set()


def _norm_key():
    # Normalization depends on this file, the database and the ELF image reader.
    here = Path(__file__).resolve().parent
    return [p.stat().st_mtime for p in (here / "objdiff.py", here / "elfimage.py",
                                        NORM_CACHE.parent / "elfdb.json") if p.exists()]


def _load_norm_cache():
    import pickle
    try:
        data = pickle.loads(NORM_CACHE.read_bytes())
        if data.get("key") == _norm_key():
            return data["functions"]
    except (OSError, ValueError, EOFError, pickle.UnpicklingError, AttributeError):
        pass
    return {}


def save_norm_cache(original):
    import pickle
    cache = original.__dict__.get("_norm_cache")
    if cache and _NORM_DIRTY:
        NORM_CACHE.write_bytes(pickle.dumps({"key": _norm_key(), "functions": cache}))
        _NORM_DIRTY.clear()


def tu_for_source(db, source):
    name = Path(source).name
    matches = [t for t in db["tus"] if t["name"].lower() == name.lower()]
    return matches[0] if len(matches) == 1 else None


def globalize_locals(text):
    """Make file-local symbols global so relocations keep symbol+addend (codegen unchanged)."""
    names = set()
    out = []
    declared = set(re.findall(r"^\s*\.(?:globl|weak)\s+(\S+)", text, re.M))
    for line in text.splitlines():
        m = re.match(r"^\s*\.local\s+(\S+)\s*$", line)
        if m:
            names.add(m.group(1))
            out.append(f"\t.globl\t{m.group(1)}")
            continue
        m = re.match(r"^([A-Za-z_][\w.$]*):\s*$", line)
        if m and m.group(1) not in declared:
            names.add(m.group(1))
            out.append(f"\t.globl\t{m.group(1)}")
        out.append(line)
    return "\n".join(out) + "\n", names


def compile_for_diff(source, tmp, extra=(), quiet=False):
    asm = toolchain.compile_source(source, Path(tmp) / "unit.s", extra, assembly=True, quiet=quiet)
    text, globalized = globalize_locals(Path(asm).read_text())
    patched = Path(tmp) / "unit.global.s"
    patched.write_text(text)
    return toolchain.assemble(patched, Path(tmp) / "unit.o"), globalized


def code_digest(norm):
    """Identity of a compiled function: its normalized instructions. A test result
    stays valid while this holds, whatever happens to the source text or headers."""
    return hashlib.sha256("\n".join(norm).encode()).hexdigest()[:16]


def compare_source(source, original, show=None, extra=(), quiet=False):
    """quiet: compiler errors go into the SystemExit message instead of stderr."""
    tu = tu_for_source(original.db, source)
    with tempfile.TemporaryDirectory(prefix="otl-diff-") as tmp:
        obj, globalized = compile_for_diff(source, tmp, extra, quiet)
        ours = object_functions(obj, original.resolver(tu), original.side.name_at, globalized)
    rows = []
    seen = set()
    for name, mine in sorted(ours.items()):
        f = original.function(name, mine["bind"] == elfimage.STB_LOCAL, tu)
        if not f:
            rows.append({"name": name, "status": "EXTRA", "size": mine["size"]})
            continue
        theirs = original.normalized(f)
        seen.add(f["address"])
        if mine["norm"] == theirs:
            status, score = "MATCH", 1.0
        else:
            score = difflib.SequenceMatcher(None, mine["norm"], theirs, autojunk=False).ratio()
            status = "DIFF"
        row = {"name": name, "demangled": f["demangled"], "address": f["address"], "status": status,
               "score": round(score, 4), "size": mine["size"], "original_size": f["size"],
               "weak": mine["bind"] == elfimage.STB_WEAK, "code": code_digest(mine["norm"])}
        rows.append(row)
        if show and (show == "all" or show in (name, f["demangled"])):
            print(f"--- ours {name}\n+++ original {f['address']} {f['demangled']}")
            for line in difflib.unified_diff(mine["norm"], theirs, lineterm="", n=1000):
                if not line.startswith(("---", "+++")):
                    print(line)
    if tu:
        for address, f in original.db["functions"].items():
            if f["tu"] == tu["id"] and address not in seen and f["kind"] not in ("compiler", "inline_or_template"):
                rows.append({"name": f["mangled"], "demangled": f["demangled"], "address": address,
                             "status": "MISSING", "original_size": f["size"]})
    return {"source": str(Path(source).resolve().relative_to(ROOT)) if Path(source).resolve().is_relative_to(ROOT) else str(source),
            "tu": tu["name"] if tu else None, "functions": rows}


def report(result):
    print(f"{result['source']}  (original TU: {result['tu'] or '?'})")
    for row in result["functions"]:
        label = row.get("demangled") or row["name"]
        score = f"{row['score'] * 100:5.1f}%" if "score" in row else "     "
        weak = " (inline)" if row.get("weak") else ""
        print(f"  {row['status']:7} {score} {row.get('address', ''):>9} {label}{weak}")
    counts = {}
    for row in result["functions"]:
        counts[row["status"]] = counts.get(row["status"], 0) + 1
    print("  " + ", ".join(f"{k} {v}" for k, v in sorted(counts.items())))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("sources", nargs="*", type=Path)
    parser.add_argument("--all", action="store_true", help="every decomp/src/**/*.cpp")
    parser.add_argument("--show", help="mangled/demangled name or 'all': print normalized diff")
    parser.add_argument("--json", type=Path)
    parser.add_argument("--elf", type=Path, default=None)
    args = parser.parse_args()
    sources = list(args.sources)
    if args.all:
        sources += sorted(SRC.rglob("*.cpp"))
    if not sources:
        parser.error("no sources")
    original = Original(elf=args.elf)
    results = [compare_source(s, original, args.show) for s in sources]
    save_norm_cache(original)
    for r in results:
        report(r)
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps({"schema": 1, "elf": original.image.sha256, "units": results}, indent=1))
    bad = sum(1 for r in results for f in r["functions"] if f["status"] == "DIFF")
    return 1 if bad and not args.show else 0


if __name__ == "__main__":
    sys.exit(main())
