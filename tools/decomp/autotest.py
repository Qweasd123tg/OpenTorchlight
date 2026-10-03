#!/usr/bin/env python3
"""Generate differential self-tests for decompiled functions.

    python3 tools/decomp/autotest.py                 # every DIFF function of decomp/src
    python3 tools/decomp/autotest.py 0x988020 ...    # chosen functions (original addresses)
    python3 tools/decomp/autotest.py --run           # generate, then run the hybrid self-test

For each function the generator builds the object under test from the
recovered layout (build-decomp/types.json): random primitives, fake objects
behind class pointers, real std::wstring and TArrayList members, the original
vtable. Arguments come from the symbol's parameter types. decomp/hybrid/AutoTest.h
runs the original and the decompiled function in forked children and compares
return value, arena bytes and list/string contents.

Generated sources go to build-decomp/hybrid/autotests/ (ignored); hybrid.py
compiles them into the blob when OTL_AUTOTEST=1. A test passes when no case
differs and enough cases completed in both children.
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import ghidra_cpp  # noqa: E402
import toolchain  # noqa: E402

ROOT = elfdb.ROOT
OUT = ROOT / "build-decomp" / "hybrid" / "autotests"
TYPES = ROOT / "build-decomp" / "types.json"
CASES = 200
BUDGET_SECONDS = 8
MIN_COMPLETED = 20

INTS = {"int", "unsigned int", "long", "unsigned long", "long long", "unsigned long long", "short",
        "unsigned short", "char", "unsigned char", "signed char", "wchar_t", "long int", "long unsigned int",
        "long long int", "long long unsigned int", "short int", "short unsigned int"}
FLOATS = {"float", "double"}
WSTRING = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >"
OGRE_VALUES = {"Ogre::Vector3": 3, "Ogre::Vector2": 2, "Ogre::Quaternion": 4, "Ogre::ColourValue": 4}


class Unsupported(Exception):
    pass


def is_list(t):
    return t.startswith("TArrayList<") and t.endswith(">")


class Generator:
    def __init__(self):
        self.db = elfdb.load_db()
        if not TYPES.exists():
            subprocess.run([sys.executable, str(ROOT / "tools" / "decomp" / "types_export.py")], check=True)
        types = json.loads(TYPES.read_text())
        self.classes = types["classes"]
        self.enums = ghidra_cpp.parse_enums()
        self.headers = self.class_headers()
        self.vtables = {name: vt["address"] + 0x10 for name, vt in self.db["vtables"].items()}
        self.lines = []
        self.counter = 0

    # -- knowledge --------------------------------------------------------
    def class_headers(self):
        out = {}
        for h in sorted((ROOT / "decomp" / "include").glob("*.h")):
            for m in re.finditer(r"^(?:class|struct)\s+(\w+)\s*(?::[^{;]*)?\{", h.read_text(errors="replace"), re.M):
                out.setdefault(m.group(1), h.name)
        return out

    def flat_fields(self, cls, base=0, depth=0):
        c = self.classes.get(cls)
        if not c or depth > 10:
            return []
        out = []
        for b in c["bases"]:
            out += self.flat_fields(b["name"], base + b["offset"], depth + 1)
        for f in c["fields"]:
            out.append(dict(f, offset=base + f["offset"]))
        return out

    def size_of(self, cls):
        c = self.classes.get(cls)
        return c["size"] if c and c["size"] else None

    def is_static(self, cls, method):
        header = self.headers.get(cls)
        if not header:
            return False
        text = (ROOT / "decomp" / "include" / header).read_text(errors="replace")
        return bool(re.search(rf"\bstatic\b[^;{{}}]*\b{re.escape(method)}\s*\(", text))

    # -- value builders (emit C++ statements) --------------------------------
    def kind_of(self, cls):
        """Pool id of a class: pointers of one class may be reused as arguments and list elements."""
        return self.kinds.setdefault(cls, len(self.kinds) + 1)

    def object_size(self, cls):
        if self.size_of(cls):
            return str(self.size_of(cls))
        base = re.match(r"\w+", cls).group(0)
        if base in self.headers:
            self.used.add(base)
            return f"sizeof({cls})"
        return "64"  # unknown class: a zeroed block

    def fake(self, cls, depth, emit):
        """Variable with a pointer to a fake object of cls (may be NULL)."""
        if depth > 1:
            return "0"
        if cls in self.classes or re.match(r"\w+", cls).group(0) in self.headers:
            self.used.add(re.match(r"\w+", cls).group(0))
        self.counter += 1
        var = f"fake{self.counter}"
        emit(f"char* {var} = (r.next() % 5 == 0) ? 0 : (char*)autotest::allocate({self.object_size(cls)});")
        emit(f"if ({var}) {{")
        emit(f"    autotest::remember({var}, {self.kind_of(cls)});")
        if cls in self.classes:
            self.fill(cls, var, depth, emit, indent="    ")
        emit("}")
        return var

    def pointer_to(self, cls, depth, emit):
        """Pointer expression: a new fake or, sometimes, one made earlier."""
        var = self.fake(cls, depth, emit)
        if var == "0":
            return "0"
        return f"autotest::pick(r, {self.kind_of(cls)}, {var})"

    def fill(self, cls, var, depth, emit, indent=""):
        if cls in self.vtables:
            emit(f"{indent}*(unsigned long*)({var}) = {self.vtables[cls]:#x}UL;")
        for f in self.flat_fields(cls):
            off, t, size = f["offset"], f["type"].replace("const ", "").strip(), f["size"]
            if f["name"].startswith("_vptr"):
                continue
            at = f"({var} + {off:#x})"
            if t in INTS or t in self.enums:
                emit(f"{indent}{{ long long v = autotest::randomInt(r); memcpy({at}, &v, {min(size or 4, 8)}); }}")
            elif t == "bool":
                emit(f"{indent}*(unsigned char*){at} = r.next() & 1;")
            elif t == "float":
                emit(f"{indent}*(float*){at} = (float)autotest::randomFloat(r);")
            elif t == "double":
                emit(f"{indent}*(double*){at} = autotest::randomFloat(r);")
            elif t == "std::wstring":
                emit(f"{indent}new ({at}) std::wstring(autotest::randomText(r));")
            elif is_list(t):
                self.fill_list(t[len("TArrayList<"):-1].strip(), at, depth, emit, indent)
            elif t.endswith("*") and is_list(t[:-1].strip()):
                self.fill_list(t[:-1].strip()[len("TArrayList<"):-1].strip(), at, depth, emit, indent, heap=True)
            elif t.endswith("*") and t[:-1].strip() in self.classes:
                inner = self.fake(t[:-1].strip(), depth + 1, lambda s: emit(indent + s))
                emit(f"{indent}*(char**){at} = {inner};")
            # other types (STL containers, Ogre objects) stay zero

    def element(self, t, depth, emit):
        t = t.replace("const ", "").strip()
        if t in INTS or t in self.enums:
            return f"({t})autotest::randomInt(r)"
        if t == "bool":
            return "(r.next() & 1) != 0"
        if t in FLOATS:
            return f"({t})autotest::randomFloat(r)"
        if t.endswith("*") and re.fullmatch(r"[\w:<>*, ]+", t[:-1]) and t[:-1].strip() not in INTS | FLOATS:
            return f"({t}){self.pointer_to(t[:-1].strip(), depth + 1, emit)}"
        raise Unsupported(t)

    def fill_list(self, t, at, depth, emit, indent, heap=False):
        """A TArrayList<t> at `at`, or (heap) a new one whose pointer is stored at `at`."""
        buffer = []
        for name in re.findall(r"[A-Za-z_]\w*", t):
            if name in self.classes or name in self.headers:
                self.used.add(name)
        try:
            self.counter += 1
            n = f"n{self.counter}"
            values = [self.element(t, depth, lambda s: buffer.append(indent + s)) for _ in range(4)]
            buffer.append(f"{indent}{{ unsigned int {n} = r.next() % 5;")
            if heap:
                buffer.append(f"{indent}  TArrayList<{t} >* list = (r.next() % 5 == 0) ? 0 : new TArrayList<{t} >(1 + r.next() % 4);")
                buffer.append(f"{indent}  *(void**){at} = list;")
            else:
                buffer.append(f"{indent}  TArrayList<{t} >* list = new ({at}) TArrayList<{t} >(1 + r.next() % 4);")
            buffer.append(f"{indent}  {t} values[4] = {{{', '.join(values)}}};")
            if t.endswith("*"):
                # Listed pointers weigh more in the pool: arguments then often name a listed object.
                buffer.append(f"{indent}  for (unsigned int i = 0; list && i < {n}; i++) {{ list->add(values[i % 4]); "
                              f"autotest::remember(values[i % 4], {self.kind_of(t[:-1].strip())}); }} }}")
            else:
                buffer.append(f"{indent}  for (unsigned int i = 0; list && i < {n}; i++) list->add(values[i % 4]); }}")
        except Unsupported:
            buffer = [] if heap else [f"{indent}new ({at}) TArrayList<{t} >();"]
        for line in buffer:
            emit(line)

    def argument(self, ptype, index, emit, members, dumps):
        t = ghidra_cpp.cxx_type(ptype).replace(WSTRING, "std::wstring")
        core = t.replace("const ", "").strip()
        name = f"a{index}"
        if core in INTS or core in self.enums:
            members.append(f"{core} {name};")
            emit(f"c.{name} = ({core})autotest::randomInt(r);")
        elif core == "bool":
            members.append(f"bool {name};")
            emit(f"c.{name} = (r.next() & 1) != 0;")
        elif core in FLOATS:
            members.append(f"{core} {name};")
            emit(f"c.{name} = ({core})autotest::randomFloat(r);")
        elif core == "wchar_t*":
            members.append(f"const wchar_t* {name};")
            emit(f"c.{name} = autotest::randomText(r);")
        elif core in ("std::wstring&", "std::wstring"):
            members.append(f"std::wstring* {name};")
            emit(f"c.{name} = new (autotest::allocate(sizeof(std::wstring))) std::wstring(autotest::randomText(r));")
            return f"*c.{name}", f"c.{name}"
        elif core.rstrip("&").strip() in OGRE_VALUES:
            vt = core.rstrip("&").strip()
            members.append(f"{vt}* {name};")
            emit(f"c.{name} = ({vt}*)autotest::allocate(sizeof({vt}));")
            emit(f"for (int i = 0; i < {OGRE_VALUES[vt]}; i++) ((float*)c.{name})[i] = (float)autotest::randomFloat(r);")
            return f"*c.{name}", (f"c.{name}" if core.endswith("&") else f"*c.{name}")
        elif core.endswith("&") and core[:-1].strip() in INTS | FLOATS | {"bool"}:
            vt = core[:-1].strip()
            members.append(f"{vt}* {name};")
            emit(f"c.{name} = ({vt}*)autotest::allocate(sizeof({vt}));")
            return f"*c.{name}", f"c.{name}"
        elif core.endswith("*") and core[:-1].strip() in self.classes and core[:-1].strip() in self.headers:
            cls = core[:-1].strip()
            members.append(f"{cls}* {name};")
            emit(f"c.{name} = ({cls}*){self.pointer_to(cls, 1, emit)};")
        elif core.endswith("&") and core[:-1].strip() in self.classes and core[:-1].strip() in self.headers:
            cls = core[:-1].strip()
            members.append(f"{cls}* {name};")
            var = self.fake(cls, 1, emit)
            emit(f"if (!{var}) {var} = (char*)autotest::allocate({self.object_size(cls)});")
            emit(f"c.{name} = ({cls}*)autotest::pick(r, {self.kind_of(cls)}, {var});")
            return f"*c.{name}", f"c.{name}"
        else:
            raise Unsupported(ptype)
        return f"c.{name}", f"c.{name}"

    def dump(self, cls, var, emit):
        for f in self.flat_fields(cls):
            t, at = f["type"].replace("const ", "").strip(), f"({var} + {f['offset']:#x})"
            if t == "std::wstring":
                emit(f"out.addText(*(std::wstring*){at});")
            elif is_list(t) or (t.endswith("*") and is_list(t[:-1].strip())):
                elem = t.rstrip("*").strip()[len("TArrayList<"):-1].strip()
                list_at = f"*(TArrayList<{elem} >**){at}" if t.endswith("*") else f"(TArrayList<{elem} >*){at}"
                emit(f"{{ TArrayList<{elem} >* list = {list_at}; unsigned int n = list ? list->size() : 0;")
                emit("  out.add(&n, sizeof(n));")
                if elem.endswith("*"):
                    emit("  for (unsigned int i = 0; i < n; i++) out.addPointer((*list)[i]); }")
                elif elem in ("std::wstring", WSTRING):
                    emit("  for (unsigned int i = 0; i < n; i++) out.addText((*list)[i]); }")
                else:
                    emit(f"  for (unsigned int i = 0; i < n; i++) {{ {elem} v = (*list)[i]; out.add(&v, sizeof(v)); }} }}")

    # -- one test ------------------------------------------------------------
    def test_for(self, f):
        cls = f.get("scope")
        if not cls or cls not in self.headers or cls not in self.classes or "::" in cls:
            raise Unsupported(f"class {cls} without recovered header")
        method = f["demangled"].split("(")[0].split("::")[-1]
        params = [p for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void"]
        static = self.is_static(cls, method)
        kind = f["kind"]
        mangled = next((n for n in f["names"] if "C1E" in n or "D1E" in n), f["names"][0])
        if kind == "dtor" and any(n.endswith("D0Ev") for n in f["names"]):
            raise Unsupported("deleting destructor")
        self.counter = 0
        self.used = set()
        self.kinds = {}
        tag = f["address"][2:]
        build, members, call_args = [], [], []
        emit = build.append
        if not static:
            size = self.size_of(cls)
            if not size:
                raise Unsupported("unknown size")
            emit(f"c.self = (char*)autotest::allocate({size});")
            if kind != "ctor":
                self.fill(cls, "c.self", 0, emit)
        orig_list = []
        for i, p in enumerate(params):
            ours_arg, orig_arg = self.argument(p, i, emit, members, None)
            call_args.append(ours_arg)
            orig_list.append(orig_arg)
        args = ", ".join(call_args)
        # References and non-trivial classes by value travel as pointers in the ABI.
        orig_params = ", ".join((["void*"] if not static else []) + [f"__typeof__({a})" for a in orig_list])
        orig_args = ", ".join((["c.self"] if not static else []) + orig_list)
        prelude = []
        if kind == "ctor":
            # Our constructor through its symbol, like the original: works for abstract classes too.
            ours = f"(((void (*)({orig_params}))ours_{tag})({orig_args}), autotest::Void())"
            original = f"(((void (*)({orig_params}))orig_{tag})({orig_args}), autotest::Void())"
        elif kind == "dtor":
            ours = f"(((({cls}*)c.self)->{cls}::~{cls}()), autotest::Void())"
            original = f"(((void (*)(void*))orig_{tag})(c.self), autotest::Void())"
        else:
            call = f"{cls}::{method}({args})" if static else f"(({cls}*)c.self)->{cls}::{method}({args})"
            ours = f"({call}, autotest::Void())"
            original = f"(((Fn)orig_{tag})({orig_args}), autotest::Void())"
            prelude = [f"typedef __typeof__({call}) Result;", f"typedef Result (*Fn)({orig_params});"]
        dumps = []
        if not static and kind != "dtor":
            self.dump(cls, "c.self", dumps.append)
        name = f"auto_{tag}"
        code = [f"// {f['address']} {f['demangled']}",
                f'extern "C" char orig_{tag}[] __asm__("__tlorig_{mangled}");',
                f'extern "C" char ours_{tag}[] __asm__("{mangled}");',
                f"namespace t{tag} {{",
                "struct Context", "{", "    char* self;", *[f"    {m}" for m in members], "};",
                "void build(autotest::Rng& r, Context& c)", "{", "    c.self = 0;", *[f"    {l}" for l in build], "}",
                "void report(Context& c, autotest::Capture& out)", "{",
                "    (void)c;", "    out.addHeapInUse();", "    out.add(autotest::g_arena, autotest::g_arenaUsed);",
                *[f"    {l}" for l in dumps], "}",
                "void original(void* p, autotest::Capture& out)", "{", "    Context& c = *(Context*)p;",
                *[f"    {l}" for l in prelude],
                f"    autotest::record(out, {original});", "    report(c, out);", "}",
                "void ours(void* p, autotest::Capture& out)", "{", "    Context& c = *(Context*)p;",
                f"    autotest::record(out, {ours});", "    report(c, out);", "}",
                "}", "",
                f"TL_TEST({name})", "{",
                "    autotest::Stats stats = {0, 0, 0};",
                "    double started = autotest::seconds();",
                f"    for (int i = 0; i < {CASES} && stats.different == 0 && autotest::seconds() - started < {BUDGET_SECONDS}; i++)",
                "    {",
                "        autotest::g_arenaUsed = 0;",
                "        autotest::g_pool.count = 0;",
                f"        autotest::Rng r({int(f['address'], 16)}ULL + i);",
                f"        t{tag}::Context c;", f"        t{tag}::build(r, c);",
                f'        autotest::compareCase(t{tag}::original, t{tag}::ours, &c, stats, host, "{name}", i);',
                "    }",
                '    host->log("    stats %s same %d both-failed %d different %d\\n", "' + name +
                '", stats.same, stats.bothFailed, stats.different);',
                "    return stats.different;", "}"]
        includes = {self.headers[cls]}
        for p in params:
            core = ghidra_cpp.cxx_type(p).replace("const ", "").strip().rstrip("*&").strip()
            if core in self.headers:
                includes.add(self.headers[core])
        forward = []
        for name in sorted(self.used):
            if name in self.headers:  # noqa: SIM114
                includes.add(self.headers[name])
            elif re.fullmatch(r"\w+", name):
                forward.append(f"class {name};")
        return includes, "\n".join(forward + code) + "\n"

    def write(self, functions):
        OUT.mkdir(parents=True, exist_ok=True)
        for old in list(OUT.glob("*.cpp")) + list(OUT.glob("*.failed")):
            old.unlink()
        (OUT / "AutoTestRuntime.cpp").write_text(
            '#include "AutoTest.h"\n\nnamespace autotest\n{\n'
            "char g_arena[kArenaSize] __attribute__((aligned(16)));\nsize_t g_arenaUsed;\nPool g_pool;\n"
            "Outcome g_outcomes[2];\n}\n")
        made, skipped = [], {}
        for f in functions:
            try:
                includes, code = self.test_for(f)
            except Unsupported as why:
                skipped[f["address"]] = str(why)
                continue
            path = OUT / f"Auto_{f['address'][2:]}.cpp"
            head = ['#include "EmptyStrings.h"'] + [f'#include "{h}"' for h in sorted(includes)] + \
                   ['#include "TArrayList.h"', '#include "AutoTest.h"', "#include <cstring>", ""]
            path.write_text("\n".join(head) + code)
            try:
                toolchain.compile_source(path, path.with_suffix(".o"), ["-I", str(ROOT / "decomp" / "hybrid")])
                made.append(f)
            except SystemExit as error:
                skipped[f["address"]] = "test does not compile"
                path.rename(path.with_suffix(".cpp.failed"))
            path.with_suffix(".o").unlink(missing_ok=True)
        return made, skipped


def diff_functions(db):
    progress = ROOT / "build-decomp" / "progress.json"
    if not progress.exists():
        raise SystemExit("run tools/decomp/check.py first")
    rows = json.loads(progress.read_text())["units"]
    out = []
    for unit in rows:
        for row in unit["functions"]:
            if row["status"] == "DIFF" and not row.get("weak") and row.get("address") in db["functions"]:
                out.append(db["functions"][row["address"]])
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("addresses", nargs="*")
    parser.add_argument("--run", action="store_true")
    args = parser.parse_args()
    gen = Generator()
    db = gen.db
    functions = [db["functions"][hex(int(a, 16))] for a in args.addresses] if args.addresses else diff_functions(db)
    seen, unique = set(), []
    for f in functions:
        if f["address"] not in seen:
            seen.add(f["address"])
            unique.append(f)
    made, skipped = gen.write(unique)
    print(f"generated {len(made)} tests in {OUT.relative_to(ROOT)}; skipped {len(skipped)}")
    for address, why in sorted(skipped.items()):
        print(f"  skip {address} {db['functions'][address]['demangled'][:60]}: {why}")
    if args.run:
        env = dict(__import__("os").environ, OTL_AUTOTEST="1", OTL_SELFTEST_TIMEOUT=str(60 + 12 * len(made)))
        result = subprocess.run([sys.executable, str(ROOT / "tools" / "decomp" / "hybrid.py"), "selftest"], env=env,
                                capture_output=True, text=True)
        print("\n".join(l for l in result.stdout.splitlines() if "auto_" in l or "tests," in l))


if __name__ == "__main__":
    main()
