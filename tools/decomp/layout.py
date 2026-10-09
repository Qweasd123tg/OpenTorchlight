#!/usr/bin/env python3
"""Class layout recovery from machine code.

For a class, scans its methods (and constructors) for accesses through `this`:
field offsets, widths, value kinds (float, bool, pointer, ...), constructor
initial values, embedded strings/lists/objects, setter parameter types and
accessor names. Also recognises trivial functions (getters, setters, empty
bodies, empty destructors) and writes their C++ bodies.

    python3 tools/decomp/layout.py CLogicTimer            # field table
    python3 tools/decomp/layout.py --header CLogicTimer   # draft header

Everything here is a draft for a human or agent: names are hints from accessor
names, types are guesses from instruction forms. objdiff and self-tests decide.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from dataclasses import dataclass, field
from pathlib import Path
import pickle
import os
import tempfile
import re
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402

CACHE = elfdb.DEFAULT_OUT / "insns.pickle"
WSTRING_EMPTY = 0x1424558
STRING_EMPTY = 0x1423A38

REG64 = {}
for fam, names in {
    "rax": "rax eax ax al ah", "rbx": "rbx ebx bx bl bh", "rcx": "rcx ecx cx cl ch", "rdx": "rdx edx dx dl dh",
    "rsi": "rsi esi si sil", "rdi": "rdi edi di dil", "rbp": "rbp ebp bp bpl", "rsp": "rsp esp sp spl",
}.items():
    for n in names.split():
        REG64[n] = fam
for i in range(8, 16):
    for suffix in ("", "d", "w", "b"):
        REG64[f"r{i}{suffix}"] = f"r{i}"
REG_WIDTH = {**{n: 8 for n in "rax rbx rcx rdx rsi rdi rbp rsp".split()},
             **{n: 4 for n in "eax ebx ecx edx esi edi ebp esp".split()},
             **{n: 2 for n in "ax bx cx dx si di bp sp".split()},
             **{n: 1 for n in "al bl cl dl ah bh ch dh sil dil bpl spl".split()}}
for i in range(8, 16):
    REG_WIDTH.update({f"r{i}": 8, f"r{i}d": 4, f"r{i}w": 2, f"r{i}b": 1})
CALLER_SAVED = {"rax", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "r10", "r11"}
ARG_REGS = ["rdi", "rsi", "rdx", "rcx", "r8", "r9"]
FLOAT_OPS = re.compile(r"^(movss|addss|subss|mulss|divss|ucomiss|comiss|maxss|minss|sqrtss|cvtss2sd|cvttss2si)")
DOUBLE_OPS = re.compile(r"^(movsd|addsd|subsd|mulsd|divsd|ucomisd|comisd|maxsd|minsd|sqrtsd|cvtsd2ss|cvttsd2si)")
MEM = re.compile(r"^(-?0x[0-9a-f]+|-?\d+)?\(%(\w+)(?:,%(\w+),(\d))?\)$")
WRITES = re.compile(r"^(mov|add|sub|and|or|xor|inc|dec|neg|not|shl|shr|sar|set|cmov|imul|lea|pop|cvt|movz|movs)")


def split_operands(text):
    out, depth, cur = [], 0, ""
    for ch in text:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def split_params(text):
    out, depth, cur = [], 0, ""
    for ch in text:
        depth += ch in "<(" and 1 or 0
        depth -= ch in ">)" and 1 or 0
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return [p for p in out if p and p != "void"]


def load_insns(db, elf=None):
    """address -> [(addr, mnemonic, operands-without-comment)] for every function."""
    if CACHE.exists() and CACHE.stat().st_mtime >= (elfdb.DEFAULT_OUT / "elfdb.json").stat().st_mtime:
        with CACHE.open("rb") as stream:
            return pickle.load(stream)
    elf = elf or elfdb.default_elf()
    starts = sorted(int(a, 16) for a in db["functions"])
    sizes = {int(a, 16): f["size"] for a, f in db["functions"].items()}
    result = defaultdict(list)
    import bisect
    # Stream the large disassembly instead of retaining stdout and splitlines
    # at once. Parse identically; never publish an incomplete cache on failure.
    with tempfile.TemporaryFile(mode="w+") as errors:
        proc = subprocess.Popen(["objdump", "-d", "--no-show-raw-insn", "-w", "-j", ".text", str(elf)],
                                stdout=subprocess.PIPE, stderr=errors, text=True,
                                env={"LC_ALL": "C", "PATH": "/usr/bin:/bin"})
        try:
            for line in proc.stdout:
                m = re.match(r"^\s+([0-9a-f]+):\t(\S+)\s*(.*)$", line)
                if not m:
                    continue
                addr = int(m.group(1), 16)
                i = bisect.bisect_right(starts, addr) - 1
                if i < 0 or addr >= starts[i] + sizes[starts[i]]:
                    continue
                ops = m.group(3).split("#")[0].split("<")[0].strip() if m.group(2).startswith(("call", "j")) \
                    else m.group(3).split("#")[0].strip()
                target = re.search(r"<([^>+]+)", m.group(3))
                result[f"{starts[i]:#x}"].append((addr, m.group(2), ops, target.group(1) if target else ""))
            if proc.wait():
                errors.seek(0)
                raise subprocess.CalledProcessError(proc.returncode, proc.args, stderr=errors.read())
        finally:
            if proc.poll() is None:
                proc.kill()
            proc.wait()
            if proc.stdout:
                proc.stdout.close()
    result = dict(result)
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix="insns-", dir=CACHE.parent)
    try:
        with os.fdopen(fd, "wb") as stream:
            pickle.dump(result, stream)
        os.replace(temporary, CACHE)
    finally:
        Path(temporary).unlink(missing_ok=True)
    return result


@dataclass
class Field:
    offset: int
    widths: Counter = field(default_factory=Counter)
    kinds: Counter = field(default_factory=Counter)
    reads: set = field(default_factory=set)
    writes: set = field(default_factory=set)
    init: list = field(default_factory=list)
    types: Counter = field(default_factory=Counter)
    names: Counter = field(default_factory=Counter)

    @property
    def width(self):
        return max(self.widths) if self.widths else 0


class Layout:
    def __init__(self, db, insns):
        self.db = db
        self.insns = insns
        self.vtable_class = {}
        for name, vt in db["vtables"].items():
            self.vtable_class[vt["address"] + 0x10] = name
        self.function_by_name = {}
        for f in db["functions"].values():
            for n in f["names"]:
                self.function_by_name[n] = f

    # -- per-function scan -------------------------------------------------
    def scan(self, f, fields, method_label):
        insns = self.insns.get(f["address"], [])
        this = {"rdi": 0}          # register -> offset of `this` subobject it points to
        loaded = {}                # register -> field offset it was loaded from (8-byte)
        params = {}
        if f["kind"] in ("ctor", "function", "dtor"):
            for reg, ptype in zip(ARG_REGS[1:], [p for p in split_params(f.get("params") or "")
                                                 if p not in ("float", "double")]):
                params[reg] = ptype

        def touch(off, width, kind, write, insn_text):
            fd = fields.setdefault(off, Field(off))
            if width:
                fd.widths[width] += 1
            if kind:
                fd.kinds[kind] += 1
            (fd.writes if write else fd.reads).add(method_label)
            return fd

        for addr, mnem, ops_text, target in insns:
            ops = split_operands(ops_text) if ops_text else []
            mem_index = None
            for i, op in enumerate(ops):
                m = MEM.match(op)
                if m and m.group(3) and REG64.get(m.group(2)) in this and mnem != "lea":
                    off = this[REG64[m.group(2)]] + (int(m.group(1), 0) if m.group(1) else 0)
                    touch(off, 0, f"array{m.group(4)}", False, ops_text)
                    break
                if m and not m.group(3) and REG64.get(m.group(2)) in this:
                    mem_index = i
                    off = this[REG64[m.group(2)]] + (int(m.group(1), 0) if m.group(1) else 0)
                    write = i == len(ops) - 1 and len(ops) >= 1 and bool(WRITES.match(mnem)) and mnem != "lea"
                    if mnem.startswith(("cmp", "test", "ucomi", "comi")):
                        write = False
                    other = [o for j, o in enumerate(ops) if j != i]
                    width, kind = 0, ""
                    if FLOAT_OPS.match(mnem):
                        width, kind = 4, "float"
                    elif DOUBLE_OPS.match(mnem) and other:
                        width, kind = 8, "double"
                    elif mnem.startswith(("movzb", "movsb")):
                        width, kind = 1, "byte"
                    elif mnem.startswith(("movzw", "movsw")):
                        width, kind = 2, "short"
                    elif mnem == "movslq":
                        width, kind = 4, "int"
                    elif mnem.startswith("cvtsi2"):
                        width, kind = (8 if mnem.endswith("q") else 4), "int"
                    elif mnem == "lea":
                        dest = REG64.get(other[-1].lstrip("%")) if other else None
                        if dest:
                            this[dest] = off
                        touch(off, 0, "address", False, ops_text)
                        break
                    elif mnem.startswith("call") or mnem.startswith("jmp"):
                        touch(off, 8, "fnptr", False, ops_text)
                        break
                    else:
                        regs = [o.lstrip("%") for o in other if o.startswith("%")]
                        if regs and regs[0] in REG_WIDTH:
                            width = REG_WIDTH[regs[0]]
                        elif regs and regs[0].startswith("xmm"):
                            width = 8 if mnem in ("movq",) else 4
                        else:
                            width = {"b": 1, "w": 2, "l": 4, "q": 8}.get(mnem[-1], 0)
                        if width == 1:
                            kind = "byte"
                    fd = touch(off, width, kind, write, ops_text)
                    if write and other and other[0].startswith("$"):
                        value = int(other[0][1:], 16)
                        if width == 8 and value == WSTRING_EMPTY:
                            fd.types["std::wstring"] += 3
                        elif width == 8 and value == STRING_EMPTY:
                            fd.types["std::string"] += 3
                        elif width == 8 and value in self.vtable_class:
                            fd.types["vptr:" + self.vtable_class[value]] += 3
                        elif f["kind"] == "ctor":
                            fd.init.append(value)
                    if write and other and other[0].startswith("%"):
                        src = REG64.get(other[0].lstrip("%"))
                        if src in params:
                            fd.types[params[src]] += 2
                        if f["kind"] == "ctor" and other[0] == "%xmm0" or other[0].startswith("%xmm"):
                            pass
                    if not write and width == 8 and other and other[-1].startswith("%"):
                        dest = REG64.get(other[-1].lstrip("%"))
                        if dest:
                            loaded[dest] = off
                    if kind == "float" and f["kind"] == "ctor" and write:
                        pass
                    break
            # Pointer evidence: a register loaded from a field used as a base.
            for op in ops:
                m = MEM.match(op)
                if m and REG64.get(m.group(2)) in loaded and (mem_index is None or op != ops[mem_index]):
                    fields[loaded[REG64[m.group(2)]]].kinds["deref"] += 1
            if mnem.startswith("call"):
                callee = self.function_by_name.get(target)
                cls = callee["scope"] if callee and callee.get("scope") else None
                if cls and "rdi" in this and this["rdi"]:
                    fields.setdefault(this["rdi"], Field(this["rdi"])).types[f"member:{cls}"] += 1
                if cls and "rdi" in loaded:
                    fields[loaded["rdi"]].types[f"{cls}*"] += 1
                if not callee and target and "basic_string" in target and "rdi" in this and this["rdi"]:
                    fields.setdefault(this["rdi"], Field(this["rdi"])).types["string-member"] += 1
            # Register bookkeeping.
            if mnem.startswith("call"):
                for r in CALLER_SAVED:
                    this.pop(r, None)
                    loaded.pop(r, None)
                    params.pop(r, None)
                continue
            if ops and ops[-1].startswith("%") and not mnem.startswith(("cmp", "test", "push", "ucomi", "comi")):
                dest = REG64.get(ops[-1].lstrip("%"))
                if dest:
                    src = REG64.get(ops[0].lstrip("%")) if len(ops) == 2 and ops[0].startswith("%") else None
                    is_copy = mnem in ("mov", "movq") and src is not None
                    if mnem == "lea" and mem_index is not None:
                        continue
                    if is_copy and src in this:
                        this[dest] = this[src]
                    else:
                        this.pop(dest, None)
                    if is_copy and src in params:
                        params[dest] = params[src]
                    elif dest in params:
                        params.pop(dest, None)
                    if not (mem_index is not None and dest in loaded):
                        if not (is_copy and src in loaded):
                            loaded.pop(dest, None)
                        else:
                            loaded[dest] = loaded[src]

    # -- class -------------------------------------------------------------
    def base_end(self, cls):
        c = self.db["classes"].get(cls, {})
        end = 0
        for b in c.get("bases", []):
            size = self.class_size(b["class"]) or self.extent(b["class"])
            end = max(end, b["offset"] + (size or 8))
        return end

    def extent(self, cls):
        """Size from the class's own accesses, rounded to 8, when no allocation size is known."""
        if cls not in self.db["classes"]:
            return None
        fields = self.analyse(cls)
        end = max([self.base_end(cls)] + [off + (fd.width or 8) for off, fd in fields.items()])
        return (end + 7) & ~7

    def class_size(self, cls):
        c = self.db["classes"].get(cls, {})
        observed = c.get("size_observed") or {}
        if len(observed) == 1:
            return int(next(iter(observed)))
        if c.get("size_hint"):
            return c["size_hint"]
        return None

    def analyse(self, cls):
        memo = self.__dict__.setdefault("_memo", {})
        if cls in memo:
            return memo[cls]
        c = self.db["classes"].get(cls)
        if not c:
            raise SystemExit(f"unknown class {cls}")
        fields = {}
        methods = [self.db["functions"][a] for a in c["methods"]]
        for f in methods:
            self.scan(f, fields, f["demangled"].split("::", 1)[-1])
        self.name_from_accessors(methods, fields)
        self.name_from_descriptor(cls, fields)
        memo[cls] = fields
        return fields

    def name_from_descriptor(self, cls, fields):
        """Editor property accessors: static CXDescriptor::Get_getName/Set_setName(CEditorBaseObject*, ...)."""
        d = self.db["classes"].get(cls + "Descriptor")
        if not d:
            return
        for a in d["methods"]:
            f = self.db["functions"][a]
            method = f["demangled"].split("(")[0].split("::")[-1]
            m = re.match(r"^(Get_get|Set_set|Get_|Set_)(\w+)$", method)
            if not m or not (f.get("params") or "").startswith("CEditorBaseObject*"):
                continue
            seen = {}
            self.scan(dict(f, kind="static"), seen, f"{d['name']}::{method}")
            stem = m.group(2)
            first = True
            for off in sorted(seen, key=lambda o: 0):
                if off < 0x10:
                    continue
                fd = fields.setdefault(off, Field(off))
                for k, v in seen[off].widths.items():
                    fd.widths[k] += v
                for k, v in seen[off].kinds.items():
                    fd.kinds[k] += v
                fd.reads |= seen[off].reads
                fd.writes |= seen[off].writes
                fd.names[stem] += 3 if first else 1
                first = False

    def accessor(self, f):
        """('get'|'set'|'empty', offset, register/width) for one-instruction bodies."""
        body = [i for i in self.insns.get(f["address"], []) if i[1] not in ("nop", "xchg", "data16")]
        while body and body[-1][1].startswith(("nop", "xchg", "data16", "cs")):
            body.pop()
        if len(body) == 1 and body[0][1] in ("ret", "repz"):
            return ("empty", None, None)
        if len(body) != 2 or body[1][1] not in ("ret", "repz"):
            return None
        mnem, ops = body[0][1], split_operands(body[0][2])
        if len(ops) != 2:
            return None
        src, dst = ops
        msrc, mdst = MEM.match(src), MEM.match(dst)
        if msrc and msrc.group(2) == "rdi" and not msrc.group(3) and dst in ("%eax", "%rax", "%al", "%xmm0", "%ax"):
            return ("get", int(msrc.group(1) or "0", 0), (mnem, dst))
        if mdst and mdst.group(2) == "rdi" and not mdst.group(3) and src in (
                "%esi", "%rsi", "%sil", "%xmm0", "%si", "%dl", "%edx", "%rdx"):
            return ("set", int(mdst.group(1) or "0", 0), (mnem, src))
        return None

    def name_from_accessors(self, methods, fields):
        for f in methods:
            acc = self.accessor(f)
            if not acc or acc[0] == "empty":
                continue
            kind, off, (mnem, reg) = acc
            method = f["demangled"].split("(")[0].split("::")[-1]
            stem = re.sub(r"^(Get_get|Set_set|get|Get|set|Set|is|Is|has|Has)_?", "", method)
            if not stem or off not in fields:
                continue
            fields[off].names[stem[0].upper() + stem[1:]] += 2
            if kind == "set":
                params = split_params(f.get("params") or "")
                if len(params) == 1:
                    fields[off].types[params[0].replace("const&", "").replace(" const", "").strip()] += 2

    # -- rendering ---------------------------------------------------------
    def field_type(self, fd):
        types = Counter({k: v for k, v in fd.types.items() if not k.startswith(("member:", "string-member"))})
        member = [k[7:] for k in fd.types if k.startswith("member:")]
        if any(k.startswith("vptr:") for k in types):
            return next(k[5:] for k in types if k.startswith("vptr:")), "embedded object (has vptr)"
        if types:
            best = types.most_common(1)[0][0]
            return best, ""
        if member:
            return member[0], "embedded (method called on it)"
        if fd.kinds.get("float"):
            return "float", ""
        if fd.kinds.get("double"):
            return "double", ""
        w = fd.width
        if w == 1:
            return "bool", ""
        if w == 2:
            return "short", ""
        if w == 4:
            return "int", ""
        if w == 8:
            if fd.kinds.get("deref") or fd.kinds.get("fnptr"):
                return "void*", "pointer: dereferenced"
            return "long long", "8 bytes, pointer or integer"
        if fd.kinds.get("address"):
            return "?", "address taken (embedded object)"
        return "?", ""

    def field_name(self, fd, ctype):
        stem = fd.names.most_common(1)[0][0] if fd.names else None
        if not stem and re.match(r"^C[A-Z]\w*\*$", ctype):
            stem = ctype[1:-1]
        prefix = {"bool": "b", "float": "f", "double": "d", "int": "i", "unsigned int": "i", "long long": "i",
                  "short": "i", "std::wstring": "s", "std::string": "s"}.get(ctype, "p" if ctype.endswith("*") else "")
        if stem:
            return f"m_{prefix}{stem}"
        return f"m_{prefix}Unknown{fd.offset:X}"

    def rows(self, cls):
        fields = self.analyse(cls)
        start = self.base_end(cls)
        size = self.class_size(cls)
        rows = []
        skip = set()
        used = Counter()
        for off in sorted(fields):
            fd = fields[off]
            if off < start or (size and off >= size) or off in skip:
                continue
            ctype, note = self.field_type(fd)
            grow = fields.get(off + 16)
            if (fd.width == 8 and fd.init == [0] and grow and grow.init and grow.width == 4
                    and all(fields.get(off + k) and fields[off + k].width == 4 for k in (8, 12))):
                # {T* data; unsigned count, capacity, growBy} with ctor init 0,0,0,N
                ctype, note = "TArrayList<?>", f"growBy {grow.init[0]}"
                fd = Field(off, widths=Counter({0x18: 1}), reads=fd.reads, writes=fd.writes, init=[],
                           names=fd.names)
                skip |= {off + 8, off + 12, off + 16}
            elif ctype == "int" and fd.init and all((v & 0xffff) == 0 and 0x30000000 <= (v & 0x7fffffff) < 0x50000000
                                                     for v in fd.init):
                ctype, note = "float", "ctor stores a float bit pattern"
            arrays = [k for k in fd.kinds if k.startswith("array")]
            if arrays:
                note = (note + "; " if note else "") + f"indexed access, element size {arrays[0][5:]}: array"
            name = self.field_name(fd, ctype)
            used[name] += 1
            if used[name] > 1:
                name += f"_{off:X}"
            rows.append((off, fd, ctype, note, name))
        return start, size, rows

    def table(self, cls):
        start, size, rows = self.rows(cls)
        lines = [f"Layout of {cls}: own fields from {start:#x}" + (f", size {size:#x}" if size else ""), "",
                 "| offset | width | type guess | name hint | ctor init | read by | written by | note |",
                 "|---|---|---|---|---|---|---|---|"]
        for off, fd, ctype, note, name in rows:
            init = ", ".join(self.show_value(v, ctype) for v in fd.init[:2])
            reads = ", ".join(sorted(fd.reads))[:80]
            writes = ", ".join(sorted(fd.writes))[:80]
            lines.append(f"| {off:#x} | {fd.width or '?'} | `{ctype}` | {name} | {init} | {reads} | {writes} | {note} |")
        return "\n".join(lines)

    @staticmethod
    def show_value(value, ctype):
        if ctype in ("float", "double") and value < 1 << 32:
            import struct
            return repr(struct.unpack("<f", value.to_bytes(4, "little"))[0])
        if value >= 1 << 31 and value < 1 << 32:
            return str(value - (1 << 32))
        return str(value) if value < 0x10000 else hex(value)

    def header(self, cls):
        c = self.db["classes"][cls]
        start, size, rows = self.rows(cls)
        bases = ", ".join(f"public {b['class']}" for b in c.get("bases", []))
        guard = cls.lstrip("C").upper() + "_H"
        out = [f"#ifndef {guard}", f"#define {guard}", "", "// DRAFT from tools/decomp/layout.py: verify types,",
               "// names and gaps against the machine code before use.", "",
               f"class {cls}" + (f" : {bases}" if bases else ""), "{", "public:"]
        virtual = set()
        vt = self.db["vtables"].get(cls)
        if vt:
            for group in vt["groups"]:
                for slot in group["slots"]:
                    if isinstance(slot, str) and slot in self.db["functions"]:
                        virtual.add(slot)
        seen = set()
        for a in c["methods"]:
            f = self.db["functions"][a]
            sig = f["demangled"].split("::", 1)[-1]
            if sig in seen:
                continue
            seen.add(sig)
            ret = self.return_type(f)
            prefix = "virtual " if a in virtual else ""
            if f["kind"] in ("ctor", "dtor"):
                out.append(f"    {prefix}{sig};")
            else:
                out.append(f"    {prefix}{ret} {sig};")
        out += ["", "private:"]
        pos = start
        for off, fd, ctype, note, name in rows:
            if off < pos:
                continue
            align = 8 if ctype.endswith("*") or ctype.startswith(("std::", "TArrayList")) else min(fd.width or 1, 8)
            if off > (pos + align - 1) // align * align:
                out.append(f"    char m_gap{pos:X}[{off - pos:#x}]; // not accessed by methods of this class")
            width = fd.width or 8
            ctype_out = "std::wstring" if ctype == "string-member" else ctype
            out.append(f"    {ctype_out} {name};" + (f" // {note}" if note else ""))
            pos = off + (8 if ctype_out.startswith("std::") else 0x18 if ctype_out.startswith("TArrayList") else width)
        if size and size > (pos + 7) // 8 * 8:
            out.append(f"    char m_gap{pos:X}[{size - pos:#x}]; // tail (size from allocation)")
        out += ["};", "", "#endif"]
        return "\n".join(out) + "\n"

    def return_type(self, f):
        hint = (f.get("return_hint") or {}).get("kind")
        acc = self.accessor(f)
        if acc and acc[0] == "get":
            mnem, reg = acc[2]
            return {"%al": "bool", "%eax": "int", "%xmm0": "float", "%rax": "void*", "%ax": "short"}.get(reg, "int")
        return {"int8": "bool", "int32": "int", "int64": "long long", "float": "float", "double": "double",
                "pointer": "void*", None: "void"}.get(hint, "void /* ? */")

    def trivial_body(self, f, names):
        """C++ body for a trivial function, or None. `names`: offset -> field name."""
        acc = self.accessor(f)
        if acc:
            kind, off, extra = acc
            if kind == "empty":
                return "{\n}"
            if off in names:
                if kind == "get":
                    return f"{{\n    return {names[off]};\n}}"
                params = split_params(f.get("params") or "")
                if len(params) == 1:
                    return f"{{\n    {names[off]} = value;\n}}"
        if f["kind"] == "dtor":
            body = [i for i in self.insns.get(f["address"], []) if not i[1].startswith(("nop", "xchg", "data16", "cs"))]
            # vptr store + tail call of the base destructor, or just the tail call.
            tail = body[-1] if body else None
            if (tail and tail[1] == "jmp" and re.search(r"D[12]Ev$", tail[3]) and
                    (len(body) == 1 or (len(body) == 2 and body[0][1] == "movq" and body[0][2].endswith(",(%rdi)")))):
                return "{\n}"
        return None


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("classes", nargs="+")
    parser.add_argument("--header", action="store_true")
    args = parser.parse_args()
    db = elfdb.load_db()
    layout = Layout(db, load_insns(db))
    for cls in args.classes:
        print(layout.header(cls) if args.header else layout.table(cls) + "\n")


if __name__ == "__main__":
    main()
