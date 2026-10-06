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
               "pair": "utility", "char_traits": "string", "allocator": "memory", "less": "functional",
               "basic_ofstream": "fstream", "basic_ifstream": "fstream", "basic_fstream": "fstream",
               "basic_ostream": "ostream", "basic_istream": "istream"}
GHIDRA_SCALARS = {"undefined": "bool", "undefined1": "bool", "byte": "bool", "char": "char", "uchar": "unsigned char",
                  "bool": "bool", "undefined2": "short", "short": "short", "ushort": "unsigned short",
                  "undefined4": "int", "int": "int", "uint": "unsigned int", "undefined8": "long",
                  "long": "long", "ulong": "unsigned long", "longlong": "long long", "ulonglong": "unsigned long long",
                  "float": "float", "double": "double", "void": "void", "wchar_t": "wchar_t"}
SYSTEM_TYPEDEFS = {"int32_t": "stdint.h", "uint32_t": "stdint.h", "int64_t": "stdint.h", "uint64_t": "stdint.h",
                   "size_t": "stddef.h", "FILE": "stdio.h", "_IO_FILE": "stdio.h", "timespec": "time.h"}


def ogre_dir():
    return toolchain.cache_dir() / "gcc447" / "ogre-1.6.5" / "ogre" / "OgreMain" / "include"


def class_dump(source, extra=()):
    """Compiles `source` and returns GCC's -fdump-class-hierarchy text."""
    import tempfile
    with tempfile.TemporaryDirectory(prefix="otl-classes-") as tmp:
        toolchain.compile_source(source, Path(tmp) / "out.o",
                                 [*extra, "-fdump-class-hierarchy", "-dumpbase", str(Path(tmp) / "classes")],
                                 quiet=True, cache=False)
        dumps = list(Path(tmp).glob("classes*.class"))
        return dumps[0].read_text(errors="replace") if dumps else ""


def dumped_vtable(dump, cls):
    """Groups of slot names of `cls` in a class dump (None without a vtable).
    A slot is 'Scope::method', a thunk's mangled name or __cxa_pure_virtual."""
    m = re.search(rf"^Vtable for {re.escape(cls)}\n[^\n]*\n((?:\d+ +[^\n]*\n)*)", dump, re.M)
    if not m:
        return None
    groups, current = [], None
    for line in m.group(1).splitlines():
        entry = line.split(None, 1)[1].strip()
        if entry.startswith("(int (*)(...))"):
            current = [] if "_ZTI" in entry else None
            if current is not None:
                groups.append(current)
            continue
        if current is None:
            continue
        last = entry.rsplit("::", 1)[-1]
        current.append(last if last.startswith("_ZT") else entry.replace(" ", ""))
    return groups


def original_vtable(db, cls, demangled=None):
    """Groups of slots of the original vtable of `cls`, named like dumped_vtable (None without one).
    Thunk slots are given as the set of their mangled names."""
    vt = db["vtables"].get(cls)
    if not vt:
        return None
    imports = [s for g in vt["groups"] for s in g["slots"]
               if isinstance(s, str) and s not in db["functions"] and s.startswith("_Z")]
    if imports and demangled is None:
        import subprocess
        out = subprocess.run(["c++filt"], input="\n".join(imports), capture_output=True, text=True).stdout
        demangled = dict(zip(imports, out.splitlines()))
    groups = []
    for g in vt["groups"]:
        slots = []
        for s in g["slots"]:
            f = db["functions"].get(s) if isinstance(s, str) else None
            if f and any(n.startswith(("_ZTh", "_ZTv", "_ZTc")) for n in f["names"]):
                slots.append(set(f["names"]))
            elif f:
                slots.append(f"{f['scope']}::{f['method']}".replace(" ", ""))
            elif isinstance(s, str) and s.startswith("_Z"):
                slots.append(ghidra_cpp.split_args(demangled.get(s, s))[0].split("(")[0].replace(" ", ""))
            else:
                slots.append(str(s))
        groups.append(slots)
    return groups


def vtable_mismatch(db, cls, dump):
    """None when the compiled vtable of `cls` has the original slots in the original
    order, otherwise what differs first (for a person or a model)."""
    want, got = original_vtable(db, cls), dumped_vtable(dump, cls)
    if not want and not got:
        return None
    if not got:
        return f"{cls} has no virtual methods, but the original has a vtable"
    if not want:
        return f"{cls} must not have virtual methods: the original has no vtable"
    if len(got) != len(want):
        return f"{cls}: {len(got)} vtable groups (one per polymorphic base), the original has {len(want)}"
    for group in db["vtables"][cls]["groups"]:
        identities = {}
        for slot in group["slots"]:
            f = db["functions"].get(slot) if isinstance(slot, str) else None
            if f is None or f["kind"] in ("ctor", "dtor"):
                continue
            key = ghidra_cpp.signature_key(f)
            identities.setdefault(key[0], set()).add(key[1:])
        if any(len(overloads) > 1 for overloads in identities.values()):
            return f"{cls}: overloaded virtual slots need relocation identities; class-dump names are insufficient"
    for k, (g, w) in enumerate(zip(got, want)):
        for i in range(max(len(g), len(w))):
            a = g[i] if i < len(g) else "(nothing)"
            b = w[i] if i < len(w) else "(nothing)"
            if a == b or (isinstance(b, set) and a in b):
                continue
            where = f"slot {i}" + (f" of vtable group {k}" if k else "")
            b = sorted(b)[0] if isinstance(b, set) else b
            return (f"{cls}: virtual {where} is {a} in your header, {b} in the original; "
                    f"original order: {', '.join(sorted(s)[0] if isinstance(s, set) else s for s in w)}")
    return None


def declared_signatures(text, name):
    """Parameter/cv/static identities of simple declarations at this scope.

    Nested class, namespace and inline-function bodies are excluded. Unknown
    declarator forms stay unresolved rather than suppressing every overload.
    """
    code, _ = ghidra_cpp.protect_lexical(text)
    depth, direct = 0, []
    for ch in code:
        if ch == "{":
            depth += 1
            direct.append(";" if depth == 1 else " ")
        elif ch == "}":
            depth -= 1
            direct.append(" ")
        else:
            direct.append(ch if depth == 0 else ("\n" if ch == "\n" else " "))
    direct = "".join(direct)
    result = set()
    keywords = {"void", "bool", "char", "short", "int", "long", "float", "double",
                "signed", "unsigned", "const", "volatile", "wchar_t"}
    for m in re.finditer(rf"(?P<prefix>[^;{{}}]*?)\b{re.escape(name)}\s*\((?P<params>[^()]*)\)\s*"
                         r"(?P<cv>(?:(?:const|volatile)\s*)*)\s*(?:;|=)", direct):
        params = []
        for p in ghidra_cpp.split_args(m.group("params")):
            p = p.split("=", 1)[0].strip()
            if p == "void":
                continue
            named = re.fullmatch(r"(.+?)[\s*&]+([A-Za-z_]\w*)", p)
            if named and named.group(2) not in keywords and named.group(1).strip() not in keywords:
                # Preserve pointer/reference declarators while dropping the name.
                p = p[:p.rfind(named.group(2))].strip()
            elif named and named.group(2) not in keywords and named.group(1).strip() in keywords - {"const", "volatile"}:
                p = p[:p.rfind(named.group(2))].strip()
            params.append(re.sub(r"\s+", "", ghidra_cpp.cxx_type(p)))
        cv = ghidra_cpp.cv_suffix({"cv": m.group("cv")}).strip()
        result.add((tuple(params), cv, bool(re.search(r"\bstatic\b", m.group("prefix")))))
    return result


def namespace_bodies(text, scope):
    """Only bodies belonging to the complete requested namespace path."""
    current = [text]
    for part in scope.split("::"):
        nested = []
        for body in current:
            code, _ = ghidra_cpp.protect_lexical(body)
            for m in re.finditer(rf"\bnamespace\s+{re.escape(part)}\s*\{{", code):
                before = code[:m.start()]
                if before.count("{") != before.count("}"):
                    continue
                end = ghidra_cpp.balanced_block_end(code, m.start())
                # Protected text retains the declarations needed here.
                nested.append(code[m.end():end - 1])
        current = nested
    return current


class Gen:
    def __init__(self):
        self.db = elfdb.load_db()
        exported = json.loads(TYPES.read_text())
        self.types = exported["classes"]
        self.prototypes = exported.get("prototypes", {})
        self.funcs = self.db["functions"]
        self.tu_names = {t["id"]: t["name"] for t in self.db["tus"]}
        game = {t["id"] for t in self.db["tus"] if t["kind"] == "game"}
        # Real classes only: namespaces of free functions (Ogre, std, MATH) also show up as scopes.
        self.game_classes = {name for name, c in self.db["classes"].items()
                             if "<" not in name and "::" not in name and not name.startswith("Fl_")
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
        self.hand_templates = set()
        for h in sorted(INCLUDE.glob("*.h")):
            text = h.read_text(errors="replace")
            for m in re.finditer(r"^\s*(template\s*<[^>]*>\s*)?(?:class|struct|union)\s+(\w+)\s*(?::[^{;]*)?\{",
                                 text, re.M):
                classes.setdefault(m.group(2), h.name)
                if m.group(1):
                    self.hand_templates.add(m.group(2))
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
        cv = ghidra_cpp.cv_suffix(f)
        name = f["method"]
        if name == cls:
            return f"{cls}({', '.join(out)});"
        if name.startswith("~"):
            return f"{'virtual ' if virtual else ''}~{cls}();"
        prototype = getattr(self, "prototypes", {}).get(f.get("address"))
        static_fact = (prototype or {}).get("static")
        if static_fact is None:
            if virtual or f.get("vslots") or cv:
                static_fact = False
            else:
                return None  # member/static is not encoded by the symbol name
        if static_fact and (virtual or cv):
            return None
        static = "static " if static_fact else ""
        if ret is None:
            ret = self.ghidra_return(f) or "void"
        rt = self.resolve(ret, deps) or "void*" if ret.endswith("*") else self.resolve(ret, deps) or "int"
        return f"{'virtual ' if virtual else static}{rt} {name}({', '.join(out)}){cv};"

    def virtual_signature(self, f):
        return (f["method"], tuple(re.sub(r"\s+", "", ghidra_cpp.cxx_type(p))
                                  for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void"),
                ghidra_cpp.cv_suffix(f).strip())

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
            for m in re.finditer(rf"\bvirtual\s+([\w:<>,*& ]+?)\s*\b{re.escape(sig[0])}\s*"
                                 r"\([^()]*\)\s*(?:(?:const|volatile)\s*)*(?:;|=|\{)", text):
                if (sig[1], sig[2], False) in declared_signatures(m.group(0), sig[0]):
                    return m.group(1).strip()
        for b in self.db["classes"].get(cls, {}).get("bases", []):
            r = self.root_return(b["class"], sig)
            if r:
                return r
        for i, a in enumerate(self.own_slots(cls)):
            f = self.funcs.get(a) if a != "__cxa_pure_virtual" else self.pure_overriders().get((cls, i))
            if f and f["kind"] not in ("ctor", "dtor") and self.virtual_signature(f) == sig:
                return self.return_types.setdefault(f["address"], self.ghidra_return(f) or "void")
        return None

    def own_slots(self, cls):
        vt = self.db["vtables"].get(cls)
        if not vt:
            return []
        return [s for s in vt["groups"][0]["slots"]]

    def base_offsets(self, cls, at=0, out=None):
        """Every base of cls, direct or not -> its offset in cls."""
        out = {} if out is None else out
        for b in self.db["classes"].get(cls, {}).get("bases", []):
            out.setdefault(b["class"], at + b["offset"])
            self.base_offsets(b["class"], at + b["offset"], out)
        return out

    def pure_overriders(self):
        """(class, slot) -> a function overriding that pure virtual slot in some derived class.
        Pure virtuals have no symbol; an override names the slot and gives its signature."""
        if hasattr(self, "_pure"):
            return self._pure
        by_name = {f["demangled"]: f for f in self.funcs.values() if not f["demangled"].startswith(("non-virtual", "virtual"))}
        self._pure = {}
        for derived, vt in sorted(self.db["vtables"].items()):
            for base, offset in self.base_offsets(derived).items():
                pure = [i for i, s in enumerate(self.own_slots(base)) if s == "__cxa_pure_virtual"]
                group = next((g for g in vt["groups"] if g.get("offset_to_top") == -offset), None)
                if not pure or not group:
                    continue
                for i in pure:
                    slot = group["slots"][i] if i < len(group["slots"]) else None
                    f = self.funcs.get(slot) if isinstance(slot, str) else None
                    if not f or (base, i) in self._pure or f["method"].startswith("~"):
                        continue
                    target = re.sub(r"^(?:non-virtual|virtual) thunk to ", "", f["demangled"])
                    self._pure[(base, i)] = by_name.get(target, f)
        return self._pure

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
                    over = self.pure_overriders().get((cls, i))
                    decl = over and self.method_decl(
                        over, cls, deps, virtual=True,
                        ret=self.return_types.setdefault(over["address"], self.ghidra_return(over) or "void"))
                    lines.append(f"    {decl[:-1]} = 0;" if decl else f"    virtual void pureVirtualSlot{i}() = 0;")
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
        lines += ["", "// Ghidra's opaque types in drafts: a byte for pointer arithmetic, a function type for",
                  "// indirect calls (variadic, so floats would be promoted: tests catch that).",
                  "typedef unsigned char allocator;", "typedef long code(...);", "",
                  "// Ghidra's helper operators.",
                  "#define CONCAT11(a, b) ((unsigned short)(((unsigned short)(unsigned char)(a) << 8) | (unsigned char)(b)))",
                  "#define CONCAT22(a, b) ((unsigned int)(((unsigned int)(unsigned short)(a) << 16) | (unsigned short)(b)))",
                  "#define CONCAT31(a, b) ((unsigned int)(((unsigned int)(a) << 8) | (unsigned char)(b)))",
                  "#define CONCAT44(a, b) ((unsigned long long)(((unsigned long long)(unsigned int)(a) << 32) | "
                  "(unsigned int)(b)))",
                  "#define CONCAT71(a, b) ((unsigned long long)(((unsigned long long)(a) << 8) | (unsigned char)(b)))",
                  "#define CONCAT17(a, b) ((unsigned long long)(((unsigned long long)(unsigned char)(a) << 56) | "
                  "((unsigned long long)(b) & 0xffffffffffffffULL)))",
                  "#define SUB41(x, c) ((unsigned char)((unsigned int)(x) >> ((c) * 8)))",
                  "#define SUB42(x, c) ((unsigned short)((unsigned int)(x) >> ((c) * 8)))",
                  "#define SUB81(x, c) ((unsigned char)((unsigned long long)(x) >> ((c) * 8)))",
                  "#define SUB84(x, c) ((unsigned int)((unsigned long long)(x) >> ((c) * 8)))",
                  "#define ZEXT48(x) ((unsigned long long)(unsigned int)(x))",
                  "#define ZEXT18(x) ((unsigned long long)(unsigned char)(x))",
                  "#define SEXT48(x) ((long long)(int)(x))"]
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

    def trial_include(self):
        """build-decomp/include-trial: decomp/include with partial classes completed by
        declarations of their missing non-virtual methods (trial builds only)."""
        out = ROOT / "build-decomp" / "include-trial"
        shutil.rmtree(out, ignore_errors=True)
        shutil.copytree(INCLUDE, out)
        added = 0
        for path in sorted(out.glob("*.h")):
            text = path.read_text(errors="replace")
            for m in reversed(list(re.finditer(r"^(?:class|struct)\s+(\w+)\s*(?::[^{;]*)?\{", text, re.M))):
                cls = m.group(1)
                if cls not in self.db["classes"]:
                    continue
                end = text.find("\n};", m.end())
                if end < 0:
                    continue
                body = text[m.end():end]
                deps = {"sys": set(), "local": set(), "forward": set()}
                extra, seen = [], set()
                for a in self.db["classes"][cls].get("methods", []):
                    f = self.funcs[a]
                    name = f["method"]
                    key = ghidra_cpp.signature_key(f)
                    prototype = getattr(self, "prototypes", {}).get(f.get("address"), {})
                    key = key[:3] + (prototype.get("static", False if ghidra_cpp.cv_suffix(f) else key[3]),)
                    identity = (key[1], key[2], key[3])
                    if (f.get("scope") != cls or f.get("vslots") or key in seen or name.startswith("~")
                            or name == cls or identity in declared_signatures(body, name)):
                        continue
                    seen.add(key)
                    trial = {"sys": set(), "local": set(), "forward": set()}
                    decl = self.method_decl(f, cls, trial)
                    # Only declarations whose types are already visible or can be forward-declared.
                    names = set(re.findall(r"\b[A-Za-z_]\w*\b", decl or ""))
                    classes = {n for n in names if (n in self.game_classes or n in self.hand)
                               and n not in self.hand_templates}
                    if (decl and not trial["sys"] - {"string"} and "GenTypes.h" not in trial["local"]
                            and not any(n in self.hand_enums and n not in text for n in names)):
                        extra.append("    " + decl)
                        deps["forward"] |= classes
                if extra:
                    fwd = "".join(f"class {n};\n" for n in sorted(deps["forward"] - {cls}))
                    text = (text[:m.start()] + fwd + text[m.start():end] + "\npublic: // added for trial builds\n" +
                            "\n".join(extra) + text[end:])
                    added += len(extra)
            path.write_text(text)
        return added

    def namespaces_header(self):
        """Free functions of game namespaces (STRINGS::, FILESYSTEM::, ...) no hand header declares."""
        game = {t["id"] for t in self.db["tus"] if t["kind"] == "game"}
        hand_text = "\n".join(h.read_text(errors="replace") for h in INCLUDE.glob("*.h"))
        groups = {}
        deps = {"sys": set(), "local": set(), "forward": set()}
        for f in self.funcs.values():
            scope = f.get("scope") or ""
            if (f["tu"] not in game or not scope or scope in self.game_classes
                    or scope in self.hand or scope.split("::")[0] in ("Ogre", "std", "CEGUI") or re.match(r"C[A-Z]", scope)
                    or not re.fullmatch(r"[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*", scope) or f["kind"] not in ("function", "static")):
                continue
            key = ghidra_cpp.signature_key(f)
            identity = (key[1], key[2], False)  # free namespace function, no implicit receiver
            if any(identity in declared_signatures(body, f["method"]) for body in namespace_bodies(hand_text, scope)):
                continue
            params = []
            for p in ghidra_cpp.split_args(f.get("params") or ""):
                if p == "void":
                    continue
                t = self.resolve(ghidra_cpp.cxx_type(p), deps)
                if t is None:
                    break
                params.append(t)
            else:
                ret = self.ghidra_return(f) or "void"
                rt = self.resolve(ret, deps) or ("void*" if ret.endswith("*") else "int")
                decl = f"{rt} {f['method']}({', '.join(params)});"
                groups.setdefault(scope, set()).add(decl)
        lines = ["#ifndef GEN_NAMESPACES_H", "#define GEN_NAMESPACES_H", "",
                 "// Free functions of game namespaces, from symbols; return types from Ghidra.", ""]
        lines += [f"#include <{h}>" for h in sorted(deps["sys"])]
        lines += [f'#include "{h}"' for h in sorted(deps["local"]) if not h.startswith("C")]
        lines += [f"class {n};" for n in sorted(deps["forward"])]
        for scope, decls in sorted(groups.items()):
            parts = scope.split("::")
            lines += [""] + [f"namespace {part} {{" for part in parts]
            lines += [f"    {d}" for d in sorted(decls)] + ["}" for _ in parts]
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
        self.trial_added = self.trial_include()
        (OUT / "GenNamespaces.h").write_text(self.namespaces_header())
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
                vtable = vtable_mismatch(self.db, cls, class_dump(src, ["-I", str(OUT), "-w"]))
                if vtable:
                    bad[cls] = vtable
                else:
                    ok.append(cls)
            except SystemExit as error:
                lines = [l for l in str(error).splitlines() if "error" in l]
                bad[cls] = lines[0].split("error:", 1)[-1].strip() if lines else "?"
        return ok, bad


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    gen = Gen()
    made, failed = gen.write()
    print(f"{len(made)} headers in {OUT.relative_to(ROOT)}; {len(failed)} classes skipped; "
          f"{gen.trial_added} method declarations added to partial classes in build-decomp/include-trial")
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
