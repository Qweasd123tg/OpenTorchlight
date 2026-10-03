#!/usr/bin/env python3
"""Generated class headers for every game class without a hand-written one.

    python3 tools/decomp/headers.py           # write build-decomp/include-gen/
    python3 tools/decomp/headers.py --check   # also compile them and verify sizes/offsets

One header per class (`<Class>.h`), from mechanical sources only:
- bases and their offsets from RTTI (elfdb);
- virtual methods in the order of the class's own slots in the primary
  vtable, so new virtuals land in the original slots; pure virtual slots
  get placeholders; an override takes its base's return type;
- other methods from the symbols, return types from the Ghidra prototypes
  (build-decomp/drafts/<TU>/raw, see ghidra_draft.py);
- fields from build-decomp/types.json; unknown or unsupported fields become
  aligned byte arrays so that offsets and size stay the original ones.

Hand-written headers in decomp/include always win: a generated header
includes them for bases and members instead of generating the class again.
GenTypes.h declares enums and typedefs no hand-written header declares.
Everything is public. The output is a draft for compiling Ghidra drafts and
generated tests, not source to commit.
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import shutil
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import ghidra_cpp  # noqa: E402
import toolchain  # noqa: E402

ROOT = elfdb.ROOT
OUT = ROOT / "build-decomp" / "include-gen"
DRAFTS = ROOT / "build-decomp" / "drafts"
TYPES = ROOT / "build-decomp" / "types.json"
INCLUDE = ROOT / "decomp" / "include"
WSTRING = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >"
STRING = "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"
PRIMITIVE = {"void", "bool", "char", "signed char", "unsigned char", "short", "unsigned short", "int",
             "unsigned int", "long", "unsigned long", "long long", "unsigned long long", "float", "double",
             "long double", "wchar_t"}
STD_HEADERS = {"basic_string": "string", "wstring": "string", "string": "string", "vector": "vector",
               "map": "map", "multimap": "map", "set": "set", "list": "list", "deque": "deque",
               "pair": "utility", "char_traits": "string", "allocator": "memory", "less": "functional"}
GHIDRA_SCALARS = {"undefined": "bool", "undefined1": "bool", "byte": "bool", "char": "char", "uchar": "unsigned char",
                  "bool": "bool", "undefined2": "short", "short": "short", "ushort": "unsigned short",
                  "undefined4": "int", "int": "int", "uint": "unsigned int", "undefined8": "long",
                  "long": "long", "ulong": "unsigned long", "longlong": "long long", "ulonglong": "unsigned long long",
                  "float": "float", "double": "double", "void": "void", "wchar_t": "wchar_t"}
SYSTEM_TYPEDEFS = {"int32_t": "stdint.h", "uint32_t": "stdint.h", "int64_t": "stdint.h", "uint64_t": "stdint.h",
                   "size_t": "stddef.h", "FILE": "stdio.h", "_IO_FILE": "stdio.h", "timespec": "time.h"}


def ogre_dir():
    return toolchain.cache_dir() / "gcc447" / "ogre-1.6.5" / "ogre" / "OgreMain" / "include"


class Gen:
    def __init__(self):
        self.db = elfdb.load_db()
        self.types = json.loads(TYPES.read_text())["classes"]
        self.funcs = self.db["functions"]
        self.tu_names = {t["id"]: t["name"] for t in self.db["tus"]}
        game = {t["id"] for t in self.db["tus"] if t["kind"] == "game"}
        # Real classes only: namespaces of free functions (Ogre, std, MATH) also show up as scopes.
        self.game_classes = {name for name, c in self.db["classes"].items()
                             if "<" not in name and "::" not in name
                             and name not in ("Ogre", "std", "CEGUI", "ParticleUniverse", "__gnu_cxx")
                             and (c.get("typeinfo") or c.get("vtable") or name in self.types)
                             and (any(int(t) in game for t in c.get("tus", {})) or name in self.types)}
        self.hand, self.hand_enums, self.hand_types = self.scan_hand_headers()
        self.ogre = {p.stem for p in ogre_dir().glob("Ogre*.h")}
        cegui = ROOT / "third_party" / "cegui-0.6.2" / "include"
        self.cegui = {p.stem for p in cegui.glob("CEGUI*.h")}
        self.enums, self.typedefs = set(), set()
        self.return_types = {}

    def scan_hand_headers(self):
        classes, enums, others = {}, {}, {}
        for h in sorted(INCLUDE.glob("*.h")):
            text = h.read_text(errors="replace")
            for m in re.finditer(r"^\s*(?:template\s*<[^>]*>\s*)?(?:class|struct|union)\s+(\w+)\s*(?::[^{;]*)?\{",
                                 text, re.M):
                classes.setdefault(m.group(1), h.name)
            for m in re.finditer(r"\benum\s+(\w+)\s*\{", text):
                enums.setdefault(m.group(1), h.name)
            for m in re.finditer(r"\btypedef\b[^;]*?\b(\w+)\s*;", text):
                others.setdefault(m.group(1), h.name)
        return classes, enums, others

    # -- types ------------------------------------------------------------------
    def resolve(self, ctype, deps):
        """C++ spelling of a type and what it needs; None when unknown."""
        t = ctype.replace(WSTRING, "std::wstring").replace(STRING, "std::string").strip()
        names = re.findall(r"[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*", t)
        pointer_only = bool(re.search(r"[*&]\s*(?:const\s*)?$", t)) and "<" not in t
        for n in names:
            if n in ("const", "unsigned", "signed", "long", "short", "int", "char", "bool", "float", "double",
                     "void", "wchar_t", "volatile"):
                continue
            if not self.need(n, deps, pointer_only):
                return None
        return t

    def need(self, n, deps, pointer_only):
        if n in ("std::wstring", "std::string"):
            deps["sys"].add("string")
        elif n.startswith("std::"):
            head = n.split("::")[1]
            if head not in STD_HEADERS:
                return False
            deps["sys"].add(STD_HEADERS[head])
        elif n.startswith("Ogre::"):
            head = n.split("::")[1]
            deps["sys"].add(f"Ogre{head}.h" if f"Ogre{head}" in self.ogre else "Ogre.h")
        elif n.startswith("CEGUI::"):
            head = n.split("::")[1]
            deps["sys"].add(f"CEGUI{head}.h" if f"CEGUI{head}" in self.cegui else "CEGUI.h")
        elif "::" in n:
            return False
        elif n in self.hand:
            deps["local"].add(self.hand[n])
        elif n in self.hand_enums or n in self.hand_types:
            deps["local"].add(self.hand_enums.get(n) or self.hand_types[n])
        elif n in SYSTEM_TYPEDEFS:
            deps["sys"].add(SYSTEM_TYPEDEFS[n])
        elif n in self.game_classes:
            if pointer_only:
                deps["forward"].add(n)
            else:
                deps["local"].add(f"{n}.h")
        elif re.fullmatch(r"E[A-Z]\w*", n) or re.fullmatch(r"[A-Z][A-Z0-9_]*_TYPES?", n):
            self.enums.add(n)
            deps["local"].add("GenTypes.h")
        elif n in ("uint32", "int32", "uint16", "uint8", "int16", "int8"):
            self.typedefs.add(n)
            deps["local"].add("GenTypes.h")
        else:
            return False
        return True

    def ghidra_return(self, f):
        """Return type from the Ghidra prototype of f, or None."""
        raw = DRAFTS / self.tu_names.get(f["tu"], "") / "raw" / f"{f['address']}.c"
        if not raw.exists():
            return None
        proto = re.search(r"^(?!/\*)(\S.*?)\s*(?:__thiscall\s+|__cdecl\s+)?" + re.escape(f["qualified"]) + r"\s*\(([^)]*)",
                          raw.read_text(errors="replace"), re.M)
        if not proto:
            return None
        ret, params = proto.group(1).strip(), proto.group(2)
        for pattern, repl in ghidra_cpp.TYPES:
            ret = re.sub(pattern, repl, ret)
        if "__return_storage_ptr__" in params and ret.endswith("*"):
            return ret[:-1].strip()  # returned by value through a hidden pointer
        if re.fullmatch(r"undefined1?\s*\[(?:12|16)\]", ret):
            return "Ogre::Vector3"  # three floats come back in xmm0:xmm1; the usual case in this code
        if "[" in ret:
            return None
        base = ret.rstrip("* ").strip()
        stars = ret.count("*")
        if base in GHIDRA_SCALARS:
            mapped = GHIDRA_SCALARS[base]
            if stars:
                return mapped.replace("bool", "char") + "*" * stars if mapped != "void" else "void" + "*" * stars
            if mapped == "long" and (f.get("return_hint") or {}).get("kind") == "pointer":
                return "void*"
            return mapped
        return base + "*" * stars

    # -- one class --------------------------------------------------------------
    def method_decl(self, f, cls, deps, virtual=False, ret=None):
        params = [p for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void"]
        out = []
        for p in params:
            t = self.resolve(ghidra_cpp.cxx_type(p), deps)
            if t is None:
                return None
            out.append(t)
        cv = " const" if "K" in (f.get("cv") or "") else ""
        name = f["method"]
        if name == cls:
            return f"{cls}({', '.join(out)});"
        if name.startswith("~"):
            return f"{'virtual ' if virtual else ''}~{cls}();"
        static = ""
        if name in ("getSingleton", "getSingletonPtr") and not params:
            static, ret = "static ", f"{cls}*"
        if ret is None:
            ret = self.ghidra_return(f) or "void"
        rt = self.resolve(ret, deps) or "void*" if ret.endswith("*") else self.resolve(ret, deps) or "int"
        return f"{'virtual ' if virtual else static}{rt} {name}({', '.join(out)}){cv};"

    def virtual_signature(self, f):
        return (f["method"], f.get("params") or "", "K" in (f.get("cv") or ""))

    def root_return(self, cls, sig, seen=None):
        """Return type of the virtual `sig` in the topmost game base that declares it."""
        library = None
        if cls.startswith("Ogre::"):
            library = ogre_dir() / f"Ogre{cls.split('::')[1]}.h"
        elif cls.startswith("CEGUI::"):
            library = ROOT / "third_party" / "cegui-0.6.2" / "include" / f"CEGUI{cls.split('::')[1]}.h"
        if library or cls in self.hand:
            path = library or INCLUDE / self.hand[cls]
            text = path.read_text(errors="replace") if path.exists() else ""
            m = re.search(rf"\bvirtual\s+([\w:<>,*& ]+?)\s*\b{re.escape(sig[0])}\s*\(", text)
            if m:
                return m.group(1).strip()
        for b in self.db["classes"].get(cls, {}).get("bases", []):
            r = self.root_return(b["class"], sig)
            if r:
                return r
        for a in self.own_slots(cls):
            f = self.funcs.get(a)
            if f and f["kind"] not in ("ctor", "dtor") and self.virtual_signature(f) == sig:
                return self.return_types.setdefault(a, self.ghidra_return(f) or "void")
        return None

    def own_slots(self, cls):
        vt = self.db["vtables"].get(cls)
        if not vt:
            return []
        return [s for s in vt["groups"][0]["slots"]]

    def primary_base_slots(self, cls):
        bases = sorted(self.db["classes"].get(cls, {}).get("bases", []), key=lambda b: b["offset"])
        if not bases or bases[0]["offset"] != 0:
            return 0
        vt = self.db["vtables"].get(bases[0]["class"])
        return len(vt["groups"][0]["slots"]) if vt else None

    def header(self, cls):
        c = self.db["classes"][cls]
        deps = {"sys": set(), "local": set(), "forward": set()}
        bases = sorted(c.get("bases", []), key=lambda b: b["offset"])
        base_list = []
        for b in bases:
            name = b["class"]
            if not self.need(name, deps, False):
                return None, f"base {name} unknown"
            base_list.append(f"public {name}")
        lines, declared = [], set()
        # Virtuals in slot order.
        base_slots = self.primary_base_slots(cls)
        own = self.own_slots(cls)
        dtor_done = False
        for i, slot in enumerate(own):
            f = self.funcs.get(slot) if isinstance(slot, str) else None
            if slot == "__cxa_pure_virtual":
                if base_slots is not None and i >= base_slots:
                    lines.append(f"    virtual void pureVirtualSlot{i}() = 0;")
                continue
            if not f or f.get("scope") != cls or f["address"] in declared:
                continue
            declared.add(f["address"])
            if f["method"].startswith("~"):
                if not dtor_done:
                    lines.append(f"    virtual ~{cls}();")
                    dtor_done = True
                continue
            sig = self.virtual_signature(f)
            ret = None
            for b in bases:
                ret = ret or self.root_return(b["class"], sig)
            decl = self.method_decl(f, cls, deps, virtual=True, ret=ret)
            if decl is None:
                if base_slots is not None and i >= base_slots:
                    lines.append(f"    virtual void unresolvedSlot{i}(); // {f['demangled']}")
                continue
            lines.append("    " + decl)
        # Other methods.
        seen = {(self.funcs[a]["method"], self.funcs[a].get("params"), self.funcs[a].get("cv"))
                for a in declared if a in self.funcs}
        for a in c.get("methods", []):
            f = self.funcs[a]
            if a in declared or f["kind"] not in ("function", "ctor", "dtor", "static") or f.get("scope") != cls:
                continue
            key = (f["method"], f.get("params"), f.get("cv"))
            if key in seen or (f["method"].startswith("~") and dtor_done):
                continue
            seen.add(key)
            decl = self.method_decl(f, cls, deps)
            if decl is None:
                lines.append(f"    // unresolved: {f['demangled']}")
                continue
            if f["method"].startswith("~"):
                dtor_done = True
            lines.append("    " + decl)
        fields = self.fields(cls, bases, deps)
        if fields is None:
            return None, "layout"
        guard = f"GEN_{cls.upper()}_H"
        head = [f"#ifndef {guard}", f"#define {guard}", "",
                "// Generated by tools/decomp/headers.py; a draft, not recovered source.", ""]
        head += [f"#include <{h}>" for h in sorted(deps["sys"])]
        head += [f'#include "{h}"' for h in sorted(deps["local"] - {f"{cls}.h"})]
        head += [f"class {n};" for n in sorted(deps["forward"] - {cls})]
        body = [f"class {cls}" + (f" : {', '.join(base_list)}" if base_list else ""), "{", "public:"]
        body += lines + fields + ["};", "", "#endif"]
        return "\n".join(head + [""] + body) + "\n", None

    def fields(self, cls, bases, deps):
        layout = self.types.get(cls)
        size = (layout or {}).get("size")
        start = 0
        for b in bases:
            bl = self.types.get(b["class"])
            if bl and bl.get("size"):
                start = max(start, b["offset"] + bl["size"])
            elif b["offset"] == 0 and not bl:
                return None if not b["class"].startswith(("Ogre::", "CEGUI::")) else []
        if self.db["vtables"].get(cls) and not bases:
            start = 8
        out = ["", "    // fields"]
        pos = start
        for fd in sorted((layout or {}).get("fields", []), key=lambda x: x["offset"]):
            off, width = fd["offset"], fd.get("size") or 0
            if off < pos or fd["name"].startswith("_vptr"):
                continue
            t = None if fd["type"] in ("?", "") else self.resolve(fd["type"], deps)
            if t == "void*" or (t and t.endswith("*")):
                width = 8
            elif t and self.natural_size(t) != width:
                t = None  # e.g. a 24-byte member recorded as "char": keep the bytes, not the guess
            if off > pos:
                out.append(self.gap(pos, off - pos))
            if t is None or not width:
                if not width:
                    continue
                out.append(self.gap(off, width, fd["name"]))
            else:
                out.append(f"    {t} {fd['name']};")
            pos = off + width
        if size and size > pos:
            tail = size - pos
            align = 8 if any(f.get("type", "").endswith("*") for f in (layout or {}).get("fields", [])) else 4
            if (pos + tail) % align or tail >= align:
                out.append(self.gap(pos, tail))
        return out

    def natural_size(self, t):
        sizes = {"bool": 1, "char": 1, "signed char": 1, "unsigned char": 1, "short": 2, "unsigned short": 2,
                 "int": 4, "unsigned int": 4, "float": 4, "wchar_t": 4, "long": 8, "unsigned long": 8,
                 "long long": 8, "unsigned long long": 8, "double": 8, "std::wstring": 8, "std::string": 8,
                 "Ogre::Vector2": 8, "Ogre::Vector3": 12, "Ogre::Vector4": 16, "Ogre::Quaternion": 16,
                 "Ogre::ColourValue": 16, "Ogre::Matrix3": 36, "Ogre::Matrix4": 64, "Ogre::Radian": 4,
                 "Ogre::Degree": 4, "Ogre::Real": 4}
        if t in sizes:
            return sizes[t]
        if t.startswith("TArrayList<"):
            return 24
        if t in self.enums or t in self.hand_enums:
            return 4
        layout = self.types.get(t)
        return layout.get("size") if layout else None

    @staticmethod
    def gap(off, n, name=None):
        aligned = " __attribute__((aligned(8)))" if off % 8 == 0 and n % 8 == 0 else \
                  " __attribute__((aligned(4)))" if off % 4 == 0 and n % 4 == 0 else ""
        return f"    unsigned char {name or f'm_gap{off:X}'}[{n:#x}]{aligned};"

    def types_header(self):
        lines = ["#ifndef GEN_TYPES_H", "#define GEN_TYPES_H", "",
                 "// Enums and typedefs named in symbols that no hand-written header declares.", ""]
        for e in sorted(self.enums - set(self.hand_enums)):
            lines.append(f"enum {e} {{ {e}_GEN_LAST = 0x7fffffff }};")
        sizes = {"uint32": "unsigned int", "int32": "int", "uint16": "unsigned short", "int16": "short",
                 "uint8": "unsigned char", "int8": "signed char"}
        for t in sorted(self.typedefs - set(self.hand_types)):
            lines.append(f"typedef {sizes[t]} {t};")
        return "\n".join(lines + ["", "#endif"]) + "\n"

    def globals_header(self):
        """extern declarations of plain-named game globals no hand-written header declares."""
        game_files = {t["name"] for t in self.db["tus"] if t["kind"] == "game"}
        hand_text = "\n".join(h.read_text(errors="replace") for h in INCLUDE.glob("*.h"))
        seen, lines = set(), ["#ifndef GEN_GLOBALS_H", "#define GEN_GLOBALS_H", "",
                              "// Game globals by symbol; types from Hungarian prefixes or sizes (a guess).", "",
                              "#include <string>", ""]
        for g in self.db["globals"]:
            # File-local statics from shared headers (_ZL...) repeat per TU: declare them static,
            # the hybrid maps each TU's copy to the original one.
            local = g["name"].startswith("_ZL") and re.fullmatch(r"[A-Za-z]\w*", g["demangled"])
            name = g["demangled"] if local else g["name"]
            if (name in seen or not re.fullmatch(r"[A-Za-z]\w*", name) or (g["demangled"] != name and not local)
                    or g.get("section") not in (".data", ".bss", ".rodata")
                    or (g.get("file") and g["file"] not in game_files)
                    or re.search(rf"\b{re.escape(name)}\b", hand_text)):
                continue
            seen.add(name)
            size = g.get("size") or 0
            prefix = re.match(r"g_?([a-z]+)", name)
            kind = prefix.group(1) if prefix else ""
            if kind == "b" and size == 1:
                decl = f"bool {name}"
            elif kind in ("i", "n", "u", "e") and size == 4:
                decl = f"int {name}"
            elif kind == "f" and size == 4:
                decl = f"float {name}"
            elif kind == "p" and size == 8:
                decl = f"void* {name}"
            elif kind in ("s", "str", "ws") and size == 8:
                decl = f"std::wstring {name}"
            elif size in (1, 4, 8) and not kind:
                decl = {1: f"bool {name}", 4: f"int {name}", 8: f"long {name}"}[size]
            else:
                decl = f"unsigned char {name}[{max(size, 1)}]"
            lines.append(f"{'static' if local else 'extern'} {decl};")
        return "\n".join(lines + ["", "#endif"]) + "\n"

    def write(self):
        OUT.mkdir(parents=True, exist_ok=True)
        for old in OUT.glob("*.h"):
            old.unlink()
        made, failed = [], {}
        for cls in sorted(self.game_classes - set(self.hand)):
            text, why = self.header(cls)
            if text is None:
                failed[cls] = why
                continue
            (OUT / f"{cls}.h").write_text(text)
            made.append(cls)
        (OUT / "GenTypes.h").write_text(self.types_header())
        (OUT / "GenGlobals.h").write_text(self.globals_header())
        return made, failed

    def check(self, made):
        """Compiles every generated header and checks sizeof and field offsets."""
        probe = OUT / "check"
        shutil.rmtree(probe, ignore_errors=True)
        probe.mkdir()
        ok, bad = [], {}
        for cls in made:
            layout = self.types.get(cls) or {}
            asserts = []
            if layout.get("size"):
                # The recorded size may be the end of the last field rather than sizeof.
                size = layout["size"]
                asserts.append(f"typedef char size_ok[sizeof({cls}) >= {size} && sizeof({cls}) <= "
                               f"{(size + 7) // 8 * 8} ? 1 : -1];")
            text = (OUT / f"{cls}.h").read_text()
            for fd in layout.get("fields", []):
                if re.search(rf"\s{re.escape(fd['name'])}(\[|;)", text):
                    asserts.append(f"typedef char off_{fd['name']}[__builtin_offsetof({cls}, {fd['name']}) == "
                                   f"{fd['offset']} ? 1 : -1];")
            src = probe / f"{cls}.cpp"
            src.write_text(f'#include "{cls}.h"\n' + "\n".join(asserts) + "\n")
            try:
                toolchain.compile_source(src, src.with_suffix(".o"), ["-I", str(OUT), "-w"], quiet=True)
                ok.append(cls)
            except SystemExit as error:
                lines = [l for l in str(error).splitlines() if "error" in l]
                bad[cls] = lines[0].split("error:", 1)[-1].strip() if lines else "?"
            src.with_suffix(".o").unlink(missing_ok=True)
        return ok, bad


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    gen = Gen()
    made, failed = gen.write()
    print(f"{len(made)} headers in {OUT.relative_to(ROOT)}; {len(failed)} classes skipped")
    for cls, why in sorted(failed.items()):
        print(f"  skip {cls}: {why}")
    if args.check:
        ok, bad = gen.check(made)
        print(f"check: {len(ok)} compile with original size and offsets, {len(bad)} do not")
        from collections import Counter
        reasons = Counter(re.sub(r"'[^']*'", "X", why) for why in bad.values())
        for why, n in reasons.most_common(15):
            print(f"  {n:4} {why}")


if __name__ == "__main__":
    main()
