#!/usr/bin/env python3
"""Generates the property accessors of the editor descriptors: CXDescriptor::Set_setY / Get_getY.

    python3 tools/decomp/properties.py [--dry-run] [TU ...]   # default: every descriptor TU in decomp/src

They are inline static members of the descriptor class (weak symbols in the original),
one pair per property the constructor registers:

    if (object) static_cast<CX*>(object)->setY(value);
    count = sizeof(value); gUnionOf32BitData[0] = static_cast<CX*>(object)->getY(); return gUnionOf32BitData;

The machine code says what setY/getY is: a field store or load is an inline accessor (added
to the class that declares the field when no class of the hierarchy has that name; only in
headers of our own TUs), a direct or virtual tail call is the method it calls. Shapes it does
not know (strings, vectors, arithmetic) are left declared. Each TU is compiled and compared;
only byte-exact functions stay, with the accessors they use.
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import descriptors  # noqa: E402
import elfdb  # noqa: E402
import objdiff  # noqa: E402

ROOT = elfdb.ROOT
INCLUDE = ROOT / "decomp" / "include"
SRC = ROOT / "decomp" / "src"

LOAD_DATA = {"mov eax,DWORD PTR [rsi]": 4, "mov esi,DWORD PTR [rsi]": 4, "movzx eax,BYTE PTR [rsi]": 1,
             "movzx esi,BYTE PTR [rsi]": 1, "movss xmm0,DWORD PTR [rsi]": "float"}
SCALARS = {"float": 4, "int": 4, "unsigned int": 4, "bool": 1}
MEMBER = {"float": "m_fValue", "int": "m_iValue", "unsigned int": "m_uValue", "bool": "m_bValue"}
PROPERTY_TYPES = {"VARIABLE_TYPE_INTEGER": "int", "VARIABLE_TYPE_FLOAT": "float",
                  "VARIABLE_TYPE_UNSIGNED_INTEGER": "unsigned int", "VARIABLE_TYPE_BOOL": "bool"}
# Unlisted TUs another worker writes (owners.json lists ours and pc2's).
OTHERS = re.compile(r"(?i)(baseunit|character|item|player|monster|inventory)")
ACCESSORS = "    // Inline accessors behind the descriptors' property functions."


def disassemble(elf, start, end):
    """address -> [(instruction, symbol of the comment)] for every instruction in [start, end)."""
    out = subprocess.run(["objdump", "-d", "-w", "--no-show-raw-insn", "-M", "intel", f"--start-address={start:#x}",
                          f"--stop-address={end:#x}", str(elf)], capture_output=True, text=True, check=True).stdout
    insns = {}
    for line in out.splitlines():
        m = re.match(r"\s+([0-9a-f]+):\s+(.*)$", line)
        if not m:
            continue
        text, _, comment = m.group(2).partition("#")
        sym = re.search(r"<([^>+]+)", comment)
        callee = re.match(r"(?:call|jmp)\s+[0-9a-f]+ <([^>+@]+)(?:@plt)?>$", text.strip())
        text = re.sub(r"\s*<[^>]*>", "", text).strip()
        text = re.sub(r"\s+", " ", text)
        insns[int(m.group(1), 16)] = (text, sym.group(1) if sym else None, callee.group(1) if callee else None)
    return insns


def body(insns, f, named=False):
    """The instructions of f joined by "; " (calls by symbol when named)."""
    start = int(f["address"], 16)
    lines = []
    for a in sorted(x for x in insns if start <= x < start + f["size"]):
        text, sym, callee = insns[a]
        if callee and named:
            text = f"{text.split()[0]} {callee}"
        if sym and sym.endswith("gUnionOf32BitData"):
            text = re.sub(r"\[rip\+0x[0-9a-f]+\]", "[gUnionOf32BitData]", text)
        if re.match(r"nop|xchg ax,ax|data16", text):
            continue
        lines.append(text)
    return "; ".join(lines)


SET_FIELD = re.compile(r"test rdi,rdi; je \w+; (?P<load>[^;]+); (?P<op>mov|movss) (?P<w>DWORD|BYTE) PTR "
                       r"\[rdi\+(?P<off>0x[0-9a-f]+)\],(?:eax|al|xmm0); repz ret$")
SET_CALL = re.compile(r"test rdi,rdi; je \w+; (?P<load>[^;]+); jmp (?P<target>[0-9a-f]+); repz ret$")
SET_VIRTUAL = re.compile(r"test rdi,rdi; je \w+; (?:mov rax,QWORD PTR \[rdi\]; (?P<load>[^;]+)|(?P<load2>[^;]+); "
                         r"mov rax,QWORD PTR \[rdi\]); mov rax,QWORD PTR \[rax\+(?P<slot>0x[0-9a-f]+)\]; jmp rax; "
                         r"repz ret$")
WSTRING = "_ZNSbIwSt11char_traitsIwESaIwEE"
STRING_FROM_CHARS = WSTRING + "C1EPKwRKS1_"
STRING_COPY = WSTRING + "C1ERKS2_"
STRING_ASSIGN = WSTRING + "6assignERKS2_"
GET_STORE = r"(?:mov|movss) (?P<w>DWORD|BYTE) PTR \[gUnionOf32BitData\],(?P<reg>eax|al|xmm0)"
GET_FIELD = re.compile(r"xor eax,eax; test rdi,rdi; je \w+; mov DWORD PTR \[rsi\],(?P<size>0x[0-9a-f]+); "
                       r"(?:mov eax,DWORD|movzx eax,BYTE|movss xmm0,DWORD) PTR \[rdi\+(?P<off>0x[0-9a-f]+)\]; "
                       + GET_STORE + r"; mov eax,0x[0-9a-f]+; repz ret$")
GET_CALL = re.compile(r"sub rsp,0x8; xor eax,eax; test rdi,rdi; je \w+; mov DWORD PTR \[rsi\],(?P<size>0x[0-9a-f]+); "
                      r"(?:call (?P<target>[0-9a-f]+)|mov rax,QWORD PTR \[rdi\]; call QWORD PTR "
                      r"\[rax\+(?P<slot>0x[0-9a-f]+)\]); " + GET_STORE + r"; mov eax,0x[0-9a-f]+; add rsp,0x8; ret$")


class Generator:
    def __init__(self, dry_run=False):
        self.dry_run = dry_run
        self.db = elfdb.load_db()
        self.elf = elfdb.default_elf()
        types = json.loads((ROOT / "build-decomp" / "types.json").read_text())
        self.classes, self.vtables = types["classes"], types["vtables"]
        self.owners = json.loads((ROOT / "decomp" / "owners.json").read_text())["tus"]
        self.tu_names = {t["id"]: t["name"] for t in self.db["tus"]}
        self.headers = {}
        for h in INCLUDE.glob("*.h"):
            for name in re.findall(r"^(?:class|struct) (\w+)\b[^;{]*\{", h.read_text(errors="replace"), re.M):
                self.headers.setdefault(name, h)
        self.by_mangled = {f["mangled"]: f for f in self.db["functions"].values() if f.get("mangled")}
        self.original = objdiff.Original(db=self.db)

    # --- classes -------------------------------------------------------------------------
    def hierarchy(self, cls, offset=0):
        """(class, offset of its subobject) for cls and all its bases."""
        yield cls, offset
        for b in self.classes.get(cls, {}).get("bases", []):
            yield from self.hierarchy(b["name"], offset + b["offset"])

    def field_at(self, cls, offset, size):
        for c, base in self.hierarchy(cls):
            for fl in self.classes.get(c, {}).get("fields", []):
                if fl["offset"] + base == offset and fl["size"] == size:
                    return c, fl
        return None, None

    def owned(self, cls):
        """The class's header belongs to a TU of ours."""
        tus = self.db["classes"].get(cls, {}).get("tus") or {}
        if not tus:
            return False
        home = self.tu_names.get(int(max(tus, key=tus.get)))  # most methods; others got inline copies
        owner = self.owners.get(home)
        return owner == "opencode" or owner is None and not OTHERS.match(home or "")

    def declaration(self, cls, method):
        """(header, line, inline?) of the first declaration of method in cls's hierarchy."""
        for c, _ in self.hierarchy(cls):
            h = self.headers.get(c)
            if not h:
                continue
            block = self.class_block(h.read_text(), c)
            if block is None:
                continue
            m = re.search(rf"^[ \t]*[^\n;{{}}]*\b{method}\s*\([^\n]*$", block[2], re.M)
            if m:
                return h, m.group(0), "{" in m.group(0)
        return None

    @staticmethod
    def class_block(text, cls):
        m = re.search(rf"^(?:class|struct) {cls}\b[^;{{]*\{{", text, re.M)
        if not m:
            return None
        end = text.find("\n};", m.end())
        return (m.start(), end, text[m.start():end]) if end >= 0 else None

    # --- one property function -------------------------------------------------------------
    def string_plan(self, f, code, target):
        """Strings travel as wchar_t text: Set_ builds a std::wstring from it, Get_ copies the value
        into sEditorTmpMemory (at most 999999 characters, count in bytes)."""
        is_set = f["method"].startswith("Set_")
        accessor = f["method"][4:]
        cast = f"static_cast<{target}*>(object)"
        add = None
        if is_set:
            if f"call {STRING_FROM_CHARS}" not in code:
                return None, None, "shape"
            field = re.search(rf"lea rdi,\[rbx\+(0x[0-9a-f]+)\]; mov rsi,rsp; call {STRING_ASSIGN}", code)
            call = re.search(r"mov rsi,rsp; mov rdi,rbx; call (\w+)", code)
        else:
            if "sEditorTmpMemory" not in code and "0x145e620" not in code:
                return None, None, "shape"
            field = (re.search(rf"lea rsi,\[rdi\+(0x[0-9a-f]+)\]; mov rdi,rsp; xor ebx,ebx; call {STRING_COPY}", code)
                     or re.search(r"mov rsi,QWORD PTR \[rdi\+(0x[0-9a-f]+)\]; xor ebx,ebx", code))
            call = re.search(r"mov rsi,rdi; mov rdi,rsp; xor ebx,ebx; call (\w+)", code)
        by_ref = not is_set and field is not None and "QWORD PTR" in field.group(0)
        if field:
            owner, fl = self.field_at(target, int(field.group(1), 16), 8)
            if not fl or fl["type"] not in ("std::wstring", "std::basic_string<wchar_t>"):
                return None, None, "field"
            found = self.declaration(target, accessor)
            if found and not found[2]:
                return None, None, "declared, not inline"
            if not found:
                if not self.owned(owner) or owner not in self.headers:
                    return None, None, f"accessor in {owner}"
                add = (owner, f"    void {accessor}(const std::wstring& value) {{ {fl['name']} = value; }}" if is_set
                       else f"    {'const std::wstring&' if by_ref else 'std::wstring'} {accessor}() const "
                            f"{{ return {fl['name']}; }}")
            name = accessor
        elif call:
            callee = self.by_mangled.get(call.group(1))
            if not callee or callee.get("scope") not in dict(self.hierarchy(target)):
                return None, None, "callee"
            name = callee["method"]
            if not self.declaration(target, name):
                return None, None, "callee not declared"
        else:
            return None, None, "shape"
        if is_set:
            return ["if (object)", f"    {cast}->{name}((const wchar_t*)data);"], add, "ok"
        value = "const std::wstring& value" if by_ref else "std::wstring value"
        return ["if (!object)", "    return NULL;", "{",
                f"    {value} = {cast}->{name}();",
                "    unsigned int length = value.length();",
                "    unsigned int size = 0;",
                "    if (length < 1000000)",
                "    {",
                "        size = length * sizeof(wchar_t);",
                "        memcpy(sEditorTmpMemory, value.c_str(), size);",
                "        *(wchar_t*)&sEditorTmpMemory[size] = 0;",
                "    }",
                "    count = size;",
                "}",
                "return (UNIONDATA8BIT*)sEditorTmpMemory;"], add, "ok"

    def plan(self, f, code, target, prop_type):
        """(C++ body lines, accessor to add or None, reason) for one Set_/Get_ function."""
        name = f["method"]
        is_set = name.startswith("Set_")
        accessor = name[4:]
        cast = f"static_cast<{target}*>(object)"
        if is_set:
            m = SET_FIELD.match(code) or SET_CALL.match(code) or SET_VIRTUAL.match(code)
            if not m:
                return None, None, "shape"
            load = m.groupdict().get("load") or m.groupdict().get("load2")
            width = LOAD_DATA.get(load)
            if width is None:
                return None, None, "load"
        else:
            m = GET_FIELD.match(code) or GET_CALL.match(code)
            if not m:
                return None, None, "shape"
            width = "float" if m.group("reg") == "xmm0" else 1 if m.group("reg") == "al" else 4
        add = None
        if "off" in m.groupdict() and m.group("off"):
            owner, field = self.field_at(target, int(m.group("off"), 16), 1 if width == 1 else 4)
            if not field:
                return None, None, "field"
            vtype = field["type"]
            found = self.declaration(target, accessor)
            if found and not found[2]:
                return None, None, "declared, not inline"
            if not found:
                if not self.owned(owner) or owner not in self.headers:
                    return None, None, f"accessor in {owner}"
                add = (owner, f"    void {accessor}({vtype} value) {{ {field['name']} = value; }}" if is_set
                       else f"    {vtype} {accessor}() const {{ return {field['name']}; }}")
            call = accessor
        else:
            if m.groupdict().get("target"):
                callee = self.db["functions"].get(f"0x{int(m.group('target'), 16):x}")
                if not callee or not callee.get("scope") or callee["scope"] not in dict(self.hierarchy(target)):
                    return None, None, "callee"
                call = callee["method"]
                params = [p.strip() for p in (callee.get("params") or "").split(",") if p.strip() not in ("", "void")]
                if is_set and len(params) != 1:
                    return None, None, "callee params"
                vtype = params[0] if is_set else prop_type
            else:
                slots = self.vtables.get(target) or []
                slot = int(m.group("slot"), 16) // 8
                if slot >= len(slots) or not isinstance(slots[slot], str):
                    return None, None, "slot"
                call = slots[slot]
                vtype = prop_type
            if not self.declaration(target, call):
                return None, None, "callee not declared"
        if vtype not in SCALARS:
            return None, None, f"type {vtype}"
        # A float field is copied through eax when nothing computes on it.
        fits = {"bool": width == 1, "int": width == 4, "unsigned int": width == 4,
                "float": width == "float" or (width == 4 and add is not None or width == 4 and call == accessor
                                              and "off" in m.groupdict() and bool(m.group("off")))}
        if not fits[vtype]:
            return None, None, "width"
        if is_set:
            value = "data->m_bValue" if vtype == "bool" else f"((const UNIONDATA32BIT*)data)->{MEMBER[vtype]}"
            lines = ["if (object)", f"    {cast}->{call}({value});"]
        else:
            size = int(m.group("size"), 16)
            count = f"sizeof({vtype})" if size == SCALARS[vtype] else str(size)
            store = f"gUnionOf32BitData[0].{MEMBER[vtype]}"
            lines = ["if (!object)", "    return NULL;", f"count = {count};", f"{store} = {cast}->{call}();",
                     "return (UNIONDATA8BIT*)gUnionOf32BitData;"]
        return lines, add, "ok"

    # --- one TU ------------------------------------------------------------------------
    def property_types(self, tu):
        text = (SRC / tu).read_text(errors="replace")
        out = {}
        for s, g, t in re.findall(r"\(void\*\)(Set_\w+), \(void\*\)(Get_\w+), (VARIABLE_TYPE_\w+)", text):
            out[s] = out[g] = PROPERTY_TYPES.get(t)
        return out

    def target(self, cls):
        """The edited class: CXDescriptor describes CX or, for the particle and collider ones, CXWrapper."""
        name = cls[:-len("Descriptor")]
        for c in (name, name + "Wrapper"):
            if c in self.classes and any(b == "CEditorBaseObject" for b, _ in self.hierarchy(c)):
                return c
        return None

    def generate(self, tu_id):
        tu = self.tu_names[tu_id]
        funcs = [f for f in self.db["functions"].values()
                 if f["tu"] == tu_id and re.match(r"(Get|Set)_", f.get("method") or "")]
        if not funcs:
            return Counter()
        cls = funcs[0]["scope"]
        target = self.target(cls)
        header = INCLUDE / descriptors.header_name(cls)
        if not target or not header.exists() or target not in self.headers:
            return Counter({"no target class": len(funcs)})
        start = min(int(f["address"], 16) for f in funcs)
        end = max(int(f["address"], 16) + f["size"] for f in funcs)
        insns = disassemble(self.elf, start, end)
        types = self.property_types(tu)
        stats = Counter()
        plans = {}
        for f in funcs:
            lines, add, reason = self.plan(f, body(insns, f), target, types.get(f["method"]))
            if reason == "shape":
                lines, add, reason = self.string_plan(f, body(insns, f, named=True), target)
            stats[reason] += 1
            if lines:
                plans[f["method"]] = (lines, add)
        if not plans or self.dry_run:
            return stats
        saved = {p: p.read_text() for p in {header, *(self.headers[a[0]] for _, a in plans.values() if a)}}
        target_header = self.headers[target].name
        self.write(header, cls, plans, target_header)
        result = self.compare(tu)
        bad = {m for m in plans if result.get(m) != "MATCH"}
        if bad:
            for p, text in saved.items():
                p.write_text(text)
            plans = {m: v for m, v in plans.items() if m not in bad}
            if plans:
                self.write(header, cls, plans, target_header)
                result = self.compare(tu)
                if any(result.get(m) != "MATCH" for m in plans):
                    for p, text in saved.items():
                        p.write_text(text)
                    plans = {}
        stats["MATCH"] = len(plans)
        stats["compiled, no match"] = len(bad)
        return stats

    def write(self, header, cls, plans, target_header):
        text = header.read_text()
        for method, (lines, _) in plans.items():
            m = re.search(rf"^(    static [^\n;]*\b{method}\(([^)]*)\));\n", text, re.M)
            if not m:
                continue
            body_text = "".join(f"        {l}\n" for l in lines)
            text = text[:m.start()] + f"{m.group(1)}\n    {{\n{body_text}    }}\n" + text[m.end():]
        if f'#include "{target_header}"' not in text and header.name != target_header:
            text = text.replace('#include "DescriptorProp.h"\n', f'#include "DescriptorProp.h"\n#include "{target_header}"\n', 1)
        header.write_text(text)
        for owner, line in dict.fromkeys(a for _, a in plans.values() if a):
            h = self.headers[owner]
            t = h.read_text()
            if line in t:
                continue
            start, end, block = self.class_block(t, owner)
            if ACCESSORS in block:
                t = t[:end] + "\n" + line + t[end:]
            else:
                t = t[:end] + f"\n\npublic:\n{ACCESSORS}\n{line}" + t[end:]
            h.write_text(t)

    def compare(self, tu):
        try:
            rows = objdiff.compare_source(SRC / tu, self.original, quiet=True)["functions"]
        except SystemExit:
            return {}
        return {r["demangled"].split("::")[-1].split("(")[0]: r["status"] for r in rows if r.get("demangled")}

    def run(self, names):
        total = Counter()
        for tu_id, tu in sorted(self.tu_names.items(), key=lambda x: x[1]):
            if not tu.endswith("Descriptor.cpp") or not (SRC / tu).exists() or (names and tu not in names):
                continue
            if self.owners.get(tu) != "opencode":
                continue
            stats = self.generate(tu_id)
            if stats:
                print(f"{tu:45} {dict(stats)}", flush=True)
                total.update(stats)
        print(dict(total))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("tus", nargs="*")
    parser.add_argument("--dry-run", action="store_true", help="classify only, write nothing")
    args = parser.parse_args()
    Generator(args.dry_run).run(set(args.tus))


if __name__ == "__main__":
    main()
