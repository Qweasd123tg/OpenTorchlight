#!/usr/bin/env python3
"""Generates the editor descriptor TUs (*Descriptor.cpp): class header, constructor, destructor.

    python3 tools/decomp/descriptors.py [--force] [TU ...]   # default: every descriptor TU not in decomp/src

A descriptor constructor is a base constructor call and a chain of AddProperty,
AddPropertyWithInterpreterFunctions, AddInputLogic and AddOutputLogic calls
with literal arguments; calls.py resolves all of them from the machine code,
stack arguments included. The class declaration comes from the generated
header (bases, virtual order, fields at verified offsets); the property and
interpreter functions the constructor takes the address of are declared as
static members. Bases are generated first. Each TU is compiled and compared;
the remaining methods (CreateObject, InputLogicEvent, the property bodies...)
are left to llm_loop.py --resume or to hand work.
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import calls  # noqa: E402
import elfdb  # noqa: E402
import ghidra_cpp  # noqa: E402
import headers  # noqa: E402
import objdiff  # noqa: E402

ROOT = elfdb.ROOT
INCLUDE = ROOT / "decomp" / "include"
SRC = ROOT / "decomp" / "src"
GEN = headers.OUT
WSTRING = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >"
CTOR_PARAMS = ("name", "group", "description")
CALLS = ("AddProperty", "AddPropertyWithInterpreterFunctions", "AddInputLogic", "AddOutputLogic", "LinkProperty")
# Ghidra temporaries: a draft line with one of these is not taken over.
JUNK = re.compile(r"\b(?:[a-z]Var\d+|in_stack\w*|local_\w+|param_\d+|CONCAT\d+|SUB\d+|extraout\w*)\b|\*\(")


def header_name(cls):
    return (cls[1:] if re.match(r"C[A-Z]", cls) else cls) + ".h"


def cpp_type(t):
    t = t.strip().replace(WSTRING, "std::wstring")
    m = re.match(r"(.+?) const([*&])$", t)
    return f"const {m.group(1)}{m.group(2)}" if m else t


def split_args(text):
    out, depth, quote, cur = [], 0, False, ""
    for i, ch in enumerate(text):
        if ch == '"' and (i == 0 or text[i - 1] != "\\"):
            quote = not quote
        elif not quote and ch in "(<":
            depth += 1
        elif not quote and ch in ")>":
            depth -= 1
        elif not quote and ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
            continue
        cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def enum_names(path, name):
    """Enumerator names by value."""
    text = (INCLUDE / path).read_text()
    body = re.search(r"enum " + name + r"\s*\{(.*?)\};", text, re.S).group(1)
    names, value = {}, -1
    for item in body.split(","):
        item = re.sub(r"//.*", "", item).strip()
        if not item:
            continue
        m = re.match(r"(\w+)\s*(?:=\s*(\w+))?", item)
        value = int(m.group(2), 0) if m.group(2) else value + 1
        names.setdefault(value, m.group(1))
    return names


def flags_expr(value, flags):
    """m_iFlags constant as an OR of the DESCRIPTOR_FLAG_ names when it is exactly one."""
    names = [n for v, n in sorted(flags.items()) if value & v]
    if names and sum(v for v, n in flags.items() if n in names) == value:
        return " | ".join(names) if len(names) == 1 else "(" + " | ".join(names) + ")"
    return hex(value)


def property_variable(args):
    words = re.findall(r"[A-Za-z0-9]+", args[1] if len(args) > 1 else "") if args and args[1].startswith('L"') else []
    words = [w.lower() for w in words[1:]] if words and words[0] == "L" else [w.lower() for w in words]
    return (words[0] + "".join(w.capitalize() for w in words[1:]) + "Property") if words else "property"


class Generator:
    def __init__(self):
        self.db = elfdb.load_db()
        self.tracer = calls.Tracer(self.db)
        self.types = enum_names("DescriptorProp.h", "EVARIABLE_TYPES")
        self.inputs = enum_names("InputEvents.h", "EINPUT_EVENTS")
        self.outputs = enum_names("OutputEvents.h", "EOUTPUT_EVENTS")
        self.tus = {t["id"]: t["name"] for t in self.db["tus"]
                    if t["kind"] == "game" and t["name"].endswith("Descriptor.cpp")}
        text = (INCLUDE / "Descriptor.h").read_text()
        self.flags = {int(v, 16): n for n, v in re.findall(r"(DESCRIPTOR_FLAG_\w+) = (0x[0-9a-f]+)", text)}
        self.methods = ghidra_cpp.known_methods(self.db)
        self.signatures = ghidra_cpp.signatures_of(self.db)
        self.enums = ghidra_cpp.parse_enums()
        self.by_name = {}
        for f in self.db["functions"].values():
            for n in f["names"]:
                self.by_name.setdefault(f["demangled"].split("(")[0], f)

    def ctor(self, tu_id):
        found = [f for f in self.db["functions"].values() if f["tu"] == tu_id and f["kind"] == "ctor"]
        return max(found, key=lambda f: f["size"]) if found else None

    def trace(self, f):
        lines = []
        for line in self.tracer.trace(f):
            if line.startswith("// --- after the first ret"):
                break
            m = re.match(r"0x[0-9a-f]+\s+(\[[^\]]*\]\s*)?([\w:~]+)\((.*)\)$", line)
            if m and m.group(1):
                continue
            lines.append((m.group(2), split_args(m.group(3))) if m else ("?", []))
        return lines

    def draft(self, tu, f):
        """Statements of the Ghidra draft: ("call", method, variable, args) and ("store", text)."""
        raw = ROOT / "build-decomp" / "drafts" / tu / "raw" / f"{f['address']}.c"
        if not raw.exists():
            return []
        text = ghidra_cpp.convert(raw.read_text(errors="replace"), self.methods, f, self.signatures, self.enums)
        out = []
        for line in text.split("{", 1)[-1].splitlines():
            line = line.strip()
            m = re.match(r"(?:(\w+) = )?(\w+)\((.*)\);$", line)
            if m and m.group(2) in CALLS:
                out.append(("call", m.group(2), m.group(1), split_args(m.group(3))))
            elif re.match(r"m_\w+(?:\.\w+)* (?:[|&+-]?=) .*;$", line) and not JUNK.search(line):
                m = re.match(r"(m_iFlags) = m_iFlags & (0x[0-9a-f]+) \| (0x[0-9a-f]+);$", line)
                if m:
                    # The original sets before it clears; Ghidra folds both into one expression.
                    clear = ~int(m.group(2), 16) & 0xffffffff
                    out.append(("store", f"m_iFlags |= {flags_expr(int(m.group(3), 16), self.flags)};"))
                    out.append(("store", f"m_iFlags &= ~{flags_expr(clear, self.flags)};"))
                    continue
                m = re.match(r"(m_iFlags) = m_iFlags (\||&) (0x[0-9a-f]+);$", line)
                if m:
                    value = int(m.group(3), 16)
                    if m.group(2) == "&":
                        out.append(("store", f"m_iFlags &= ~{flags_expr(~value & 0xffffffff, self.flags)};"))
                    else:
                        out.append(("store", f"m_iFlags |= {flags_expr(value, self.flags)};"))
                    continue
                out.append(("store", line))
        return out

    def static_decl(self, cls, name):
        f = self.by_name.get(f"{cls}::{name}")
        if not f:
            return None
        params = [cpp_type(p) for p in split_args(f["demangled"].split("(", 1)[1].rsplit(")", 1)[0])]
        if name.startswith("Get_"):
            ret, names = "UNIONDATA8BIT*", ["object", "count"]
        elif name.startswith("Set_"):
            ret, names = "void", ["object", "data", "count"]
        elif params and params[-2:] == ["const std::wstring&", "void*"]:
            ret, names = "unsigned int", ["scene", "object", "value", "userData"]
        elif params and params[-2:] == ["unsigned int", "void*"]:
            ret, names = "std::wstring", ["scene", "object", "index", "userData"]
        else:
            ret, names = "void", []
        args = ", ".join(f"{p} {names[i]}" if i < len(names) else p for i, p in enumerate(params))
        return f"    static {ret} {name}({args});"

    def value(self, arg, cls, kind):
        """C++ for one traced argument; None when the tracer could not resolve it."""
        if arg in ("?", "...") or arg.startswith("&this"):
            return None
        m = re.match(r"arg(\d)$", arg)
        if m:
            n = int(m.group(1))
            return CTOR_PARAMS[n - 1] if n <= len(CTOR_PARAMS) else f"option{n - len(CTOR_PARAMS)}"
        if "::" in arg and not arg.startswith('L"'):
            scope, _, name = arg.rpartition("::")
            name = name if scope == cls else arg
            return f"(void*){name}" if kind == "void*" else name
        if kind == "type" and re.match(r"\d+$", arg):
            return self.types.get(int(arg), arg)
        if kind == "bool" and arg in ("0", "1"):
            return "true" if arg == "1" else "false"
        if kind == "pointer" and arg == "0":
            return "NULL"
        return arg

    def generate(self, tu_id):
        """(header text, source text, complete?) for one descriptor TU."""
        tu = self.tus[tu_id]
        ctor = self.ctor(tu_id)
        cls = ctor["scope"]
        gen = (GEN / f"{cls}.h").read_text()
        body = re.search(r"^class .*?^};", gen, re.M | re.S).group(0)
        base = re.match(r"class \w+ : public (\w+)", body).group(1)
        complete = True
        statics, stmts = [], []
        traced = self.trace(ctor)
        # Align the draft's calls with the traced ones: the draft knows saved results and field stores.
        draft = self.draft(tu, ctor)
        draft_calls = [d for d in draft if d[0] == "call"]
        before = {}  # traced call index -> stores that precede it
        variables = {}  # Ghidra variable -> our name
        assigned = {}  # traced call index -> our variable
        link_args = {}  # traced call index -> resolved LinkProperty arguments
        k = 0
        pending_stores = []
        traced_methods = [c.rpartition("::")[2] for c, _ in traced]
        positions = []
        for d in draft:
            if d[0] == "store":
                pending_stores.append(d[1])
                continue
            while k < len(traced_methods) and traced_methods[k] != d[1]:
                k += 1
            if k >= len(traced_methods):
                break
            before.setdefault(k, []).extend(pending_stores)
            pending_stores = []
            if d[2]:
                name = property_variable(traced[k][1])
                while name in variables.values():
                    name += "2"
                variables[d[2]] = name
                assigned[k] = name
            if d[1] == "LinkProperty":
                link_args[k] = [variables.get(a) for a in d[3]]
            k += 1
        trailing = pending_stores
        params = split_args(ctor["demangled"].split("(", 1)[1].rsplit(")", 1)[0])
        params = [] if params == ["void"] else params
        init = ""
        for index, (callee, args) in enumerate(traced):
            stmts.extend(f"    {s}" for s in before.get(index, []))
            if callee == f"{base}::{base}":
                base_ctor = self.by_name.get(f"{base}::{base}")
                kinds = [cpp_type(p) for p in split_args(base_ctor["demangled"].split("(", 1)[1].rsplit(")", 1)[0])] \
                    if base_ctor else []
                vals = [self.value(a, cls, kinds[i] if i < len(kinds) else "") for i, a in enumerate(args)]
                if None in vals:
                    complete = False
                init = f"    : {base}({', '.join(v or '/*?*/' for v in vals)})\n"
                continue
            method = callee.rpartition("::")[2]
            if method == "LinkProperty" and index in link_args and None not in link_args[index]:
                stmts.append(f"    LinkProperty({', '.join(link_args[index])});")
                continue
            if method == "AddProperty":
                kinds = ["", "", "", "void*", "void*", "type", ""]
            elif method == "AddPropertyWithInterpreterFunctions":
                kinds = ["", "", "", "void*", "void*", "", "", "pointer", "type", ""]
            elif method in ("AddInputLogic", "AddOutputLogic") and len(args) == 1 and args[0].isdigit():
                names = self.inputs if method == "AddInputLogic" else self.outputs
                stmts.append(f"    {method}({names.get(int(args[0]), args[0])});")
                continue
            else:
                kinds = []
            vals = [self.value(a, cls, kinds[i] if i < len(kinds) else "") for i, a in enumerate(args)]
            if None in vals or not callee.startswith(("CDescriptor::", f"{cls}::", f"{base}::")):
                complete = False
                continue
            for a in args:
                if a.startswith(f"{cls}::"):
                    decl = self.static_decl(cls, a.rpartition("::")[2])
                    if decl and decl not in statics:
                        statics.append(decl)
            prefix = f"unsigned int {assigned[index]} = " if index in assigned else ""
            stmts.append(f"    {prefix}{method}({', '.join(vals)});")
        stmts.extend(f"    {s}" for s in trailing)
        # Class declaration: generated body, parameter names, the static functions.
        named = [f"{cpp_type(p)} {CTOR_PARAMS[i] if i < len(CTOR_PARAMS) else f'option{i - len(CTOR_PARAMS) + 1}'}"
                 for i, p in enumerate(params)]
        decl_params = ", ".join(named)
        body = re.sub(rf"^(\s+){cls}\([^)]*\);", lambda m: f"{m.group(1)}{cls}({decl_params});", body, flags=re.M)
        for decl in statics:
            name = re.search(r"(\w+)\(", decl).group(1)
            body = re.sub(rf"^\s+[^\n;]*\b{name}\([^\n]*\);\n", "", body, flags=re.M)
        body = body.replace("CreateObject(CEditorScene*)", "CreateObject(CEditorScene* scene)")
        body = body.replace("\n    // fields\n", "\n")
        if statics:
            body = body.replace("\n};", "\n\n" + "\n".join(statics) + "\n};")
        includes = []
        for inc in re.findall(r'^#include "([^"]+)"', gen, re.M):
            stem = inc[:-2]
            if (INCLUDE / inc).exists():
                includes.append(inc)
            elif re.match(r"C[A-Z]\w*Descriptor$", stem):
                includes.append(header_name(stem))
            else:
                complete = False
                includes.append(inc)
        includes.append("DescriptorProp.h")
        guard = re.sub(r"\W", "_", header_name(cls)).upper()
        header = (f"#ifndef {guard}\n#define {guard}\n\n"
                  + "".join(f'#include "{i}"\n' for i in dict.fromkeys(includes))
                  + f"\n{body}\n\n#endif\n")
        sig = decl_params
        source = (f'#include "EmptyStrings.h"\n#include "{header_name(cls)}"\n\n'
                  f"{cls}::{cls}({sig})\n{init}{{\n" + "\n".join(stmts) + "\n}\n\n"
                  f"{cls}::~{cls}()\n{{\n}}\n")
        return cls, base, header, source, complete

    def run(self, names, force):
        tracked = set(subprocess.run(["git", "ls-files", "decomp/src"], cwd=ROOT, capture_output=True,
                                     text=True).stdout.split())
        todo = {tid: n for tid, n in self.tus.items()
                if (not names or n in names) and f"decomp/src/{n}" not in tracked
                and (force or not (SRC / n).exists()) and self.ctor(tid)}
        results = {}
        while todo:
            progress = False
            for tid, tu in sorted(todo.items(), key=lambda x: x[1]):
                cls = self.ctor(tid)["scope"]
                gen = GEN / f"{cls}.h"
                if not gen.exists():
                    results[tu] = "no generated header"
                    del todo[tid]
                    progress = True
                    continue
                base = re.search(r"class \w+ : public (\w+)", gen.read_text()).group(1)
                if not (INCLUDE / header_name(base)).exists():
                    continue
                cls, base, header, source, complete = self.generate(tid)
                (INCLUDE / header_name(cls)).write_text(header)
                (SRC / tu).write_text(source)
                results[tu] = self.check(tu, cls, complete)
                print(f"{tu:45} {results[tu]}", flush=True)
                del todo[tid]
                progress = True
            if not progress:
                for tid, tu in todo.items():
                    results[tu] = "base header missing"
                    print(f"{tu:45} base header missing", flush=True)
                break
        return results

    def check(self, tu, cls, complete):
        try:
            rows = objdiff.compare_source(SRC / tu, objdiff.Original(db=self.db), quiet=True)["functions"]
        except SystemExit as error:
            return "compile error: " + " | ".join(l.split(": error: ", 1)[-1] for l in str(error).splitlines()
                                                    if ": error: " in l)[:300]
        mine = [r for r in rows if r.get("demangled", "").startswith((f"{cls}::{cls}(", f"{cls}::~{cls}("))]
        status = sorted({r["status"] for r in mine})
        return f"ctor/dtor {'/'.join(status)}" + ("" if complete else " (incomplete trace)")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("tus", nargs="*")
    parser.add_argument("--force", action="store_true", help="regenerate TUs that already exist")
    args = parser.parse_args()
    results = Generator().run(set(args.tus), args.force)
    from collections import Counter
    print(Counter(r.split(" (")[0] if r.startswith("ctor") else r.split(":")[0] for r in results.values()))


if __name__ == "__main__":
    main()
