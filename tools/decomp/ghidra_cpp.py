#!/usr/bin/env python3
"""Clean Ghidra C output into a C++ draft.

    python3 tools/decomp/ghidra_cpp.py build-decomp/drafts/AIFlag.cpp/raw/*.c > draft.cpp

Rewrites, each one local and conservative:
- `void __thiscall C::m(C *this, ...)` -> `void C::m(...)`;
- `this->field` -> `field`; `(*p->_vptr->Method)(p, a)` -> `p->Method(a)`;
- `C::m(this, a)` -> `m(a)`, `C::m(p, a)` -> `p->m(a)` for known methods;
- Ghidra integer types -> C++ types;
- removes inlined std::string refcount blocks, try/catch markers,
  compiler-generated vptr stores and base-constructor calls in constructors;
- `p = (C *)Ogre::NedAllocImpl::allocBytes(n, 0, 0, 0); C::C(p, a);` -> `p = new C(a);`.

The output is a draft for a human or agent; it is not expected to compile as is.
"""
from __future__ import annotations

import argparse
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402

ROOT = elfdb.ROOT

TYPES = [
    (r"\bundefined1\b", "char"), (r"\bundefined2\b", "short"), (r"\bundefined4\b", "int"),
    (r"\bundefined8\b", "long long"), (r"\bundefined\b", "char"), (r"\bulonglong\b", "unsigned long long"),
    (r"\blonglong\b", "long long"), (r"\bulong\b", "unsigned long"), (r"\buint\b", "unsigned int"),
    (r"\bushort\b", "unsigned short"), (r"\bbyte\b", "unsigned char"), (r"\bsbyte\b", "signed char"),
    (r"\buchar\b", "unsigned char"),
    (r"\bfloat10\b", "long double"), (r"\bwchar32\b", "wchar_t"), (r"\bwstring_conflict\b", "std::wstring"),
    (r"\bstd::wstring::wstring\b", "std::wstring::basic_string"),
    # Ghidra spells multi-word template arguments with underscores.
    (r"\bunsigned_(short|int|long|char)\b", r"unsigned \1"), (r"\b(std::w?string)_const\b", r"const \1"),
    (r"\b(\w+)_const\b(?=\s*[,>*&])", r"const \1"),
]


def balanced_block_end(text, start):
    """Index just past the `}` that closes the first `{` at or after start."""
    depth = 0
    i = text.index("{", start)
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return len(text)


def drop_refcount_blocks(text):
    # if (... != &..._S_empty_rep_storage) { LOCK(); ... _M_destroy(...); }
    while True:
        m = re.search(r"\n[ \t]*if \([^{};]*?_S_empty_rep_storage[^{};]*\{", text)
        if not m:
            return text
        end = balanced_block_end(text, m.start())
        text = text[:m.start()] + text[end:]


def split_args(text):
    """Splits on top-level commas; <> count as brackets in types, not as ->, <=, << or a < b."""
    out, depth, cur, quote, escape = [], 0, "", None, False
    for k, ch in enumerate(text):
        if quote:
            cur += ch
            if escape:
                escape = False
            elif ch == "\\":
                escape = True
            elif ch == quote:
                quote = None
            continue
        if ch in "\"'":
            quote = ch
            cur += ch
            continue
        prev, after = text[k - 1] if k else "", text[k + 1:k + 8]
        operator = ch in "<>" and (
            (ch == ">" and prev == "-") or after[:1] in ("=", ch) or prev in ("<", ">") or
            (prev == " " and (k < 2 or text[k - 2] not in "<>") and re.match(r" (?!const\b)[\w(*&!-]", after)))
        if ch in "([" or (ch == "<" and not operator):
            depth += 1
        elif ch in ")]" or (ch == ">" and not operator):
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


STATIC_METHODS = {"getSingleton", "getSingletonPtr"}


def _cast_to(arg, cls):
    """arg is `(cls *)expr` (possibly with namespace differences)."""
    m = re.match(r"\(([\w:<>, ]+?)\s*\*\)", arg)
    if not m:
        return False
    norm = lambda t: re.sub(r"\s+|std::", "", t).split("::")[-1]  # noqa: E731
    return norm(m.group(1)) == norm(cls)


def call_rewrite(text, methods):
    """C::m(obj, args) -> obj->m(args) / m(args) for this."""
    out, i = [], 0
    pattern = re.compile(r"\b([A-Za-z_]\w*(?:<[^()]*?>)?)::(~?[A-Za-z_]\w*)\(")
    while True:
        m = pattern.search(text, i)
        if not m:
            out.append(text[i:])
            return "".join(out)
        cls, meth = m.group(1), m.group(2)
        start = m.end()
        depth, j = 1, start
        while j < len(text) and depth:
            depth += {"(": 1, ")": -1}.get(text[j], 0)
            j += 1
        args = split_args(text[start:j - 1])
        out.append(text[i:m.start()])
        if (cls, meth) in methods and args and meth != cls:
            obj = re.sub(r"^\((\w[\w:<>, ]*?) \*\)", "", args[0])
            rest = ", ".join(args[1:])
            if meth in STATIC_METHODS and (cls, meth) in methods:
                # Ghidra gives static methods a bogus `this` (they all got __thiscall).
                out.append(f"{cls}::{meth}({rest})")
            elif obj == "this":
                out.append(f"{meth}({rest})")
            elif re.fullmatch(r"&?[\w.\->\[\]]+", obj):
                out.append(f"{obj[1:]}.{meth}({rest})" if obj.startswith("&") else f"{obj}->{meth}({rest})")
            else:
                out.append(f"({obj})->{meth}({rest})")
        elif args and meth != cls.split("<")[0] and _cast_to(args[0], cls):
            # Library method with explicit `this`: X::m((X *)obj, args) -> ((X *)obj)->m(args).
            out.append(f"({args[0]})->{meth}({', '.join(args[1:])})")
        else:
            out.append(text[m.start():j])
        i = j


def parse_enums():
    """enum name -> {value: enumerator} from the recovered headers."""
    enums = {}
    for h in (ROOT / "decomp" / "include").glob("*.h"):
        for m in re.finditer(r"\benum\s+(\w+)\s*\{([^}]*)\}", h.read_text(errors="replace")):
            value, table = -1, {}
            for item in m.group(2).split(","):
                item = re.sub(r"//[^\n]*", "", item).strip()
                if not item:
                    continue
                name, _, expr = item.partition("=")
                name = name.strip()
                expr = expr.strip()
                try:
                    value = int(expr, 0) if expr else value + 1
                except ValueError:
                    break
                table.setdefault(value, name)
            enums[m.group(1)] = table
    return enums


def inline_temp_strings(text):
    """std::wstring::wstring((T *)local_x, L"lit", &alloc); ... (T *)local_x  ->  L"lit"."""
    temps = {}

    def capture(m):
        temps[m.group(1)] = m.group(2)
        return ""
    text = re.sub(r"\n[ \t]*std::w?string::(?:w?string|basic_string)\s*\(\s*\([\w:]+ \*\)&?(local_\w+)\s*,\s*"
                  r"(L?\"(?:[^\"\\]|\\.)*\")\s*,\s*&?local_\w+\s*\);", capture, text)
    for local, literal in temps.items():
        text = re.sub(rf"\n[ \t]*[\w:<>]+[ \t]*\**[ \t]*{local}[ \t]*(?:\[\d*\])?;", "", text)
        text = re.sub(rf"\([\w:]+ \*\)&?{local}\b", literal, text)
        text = re.sub(rf"&{local}\b|\b{local}\b(?!\s*\[)", literal, text)
    return text


TEMP = r"(?:local_\w+|[a-z]{1,4}Var\d+|extraout_\w+|in_\w+)"


def side_effects(expr):
    """A call (named or through a pointer), assignment or increment inside expr."""
    return bool(re.search(r"\w\s*\(|\)\)\s*\(|\+\+|--|(?<![=!<>])=(?!=)", expr))


def drop_dead_stores(text):
    """Stores into Ghidra temporaries nothing reads (left over when an inlined idiom
    is removed, e.g. the string pointer of a dropped refcount block)."""
    while True:
        changed = False
        for name in sorted(set(re.findall(rf"\b({TEMP})\b", text))):
            stores = list(re.finditer(rf"\n[ \t]*{name} = (?!=)([^;]*);", text))
            if not stores:
                continue
            uses = len(re.findall(rf"\b{name}\b", text))
            decls = len(re.findall(rf"\n[ \t]*[\w:<>*& ]+?[ *&]{name}(?: ?\[\d+\])?;", text))
            if uses != len(stores) + decls or any(side_effects(m.group(1)) for m in stores):
                continue
            for m in reversed(stores):
                text = text[:m.start()] + text[m.end():]
            changed = True
        if not changed:
            return text


def drop_unused_locals(text):
    lines = text.split("\n")
    out = []
    for i, line in enumerate(lines):
        m = re.match(r"^\s+[\w:<>*& ]+?[ *&](\w+)(?: ?\[\d+\])?;$", line)
        if m and re.fullmatch(TEMP, m.group(1)):
            rest = "\n".join(lines[:i] + lines[i + 1:])
            if not re.search(rf"\b{m.group(1)}\b", rest):
                continue
        out.append(line)
    return "\n".join(out)


def enum_arguments(text, signatures, enums):
    """Integer literals passed to enum-typed parameters -> enumerator names."""
    def fix(m):
        name, args = m.group(1), split_args(m.group(2))
        params = next((p for p in signatures.get(name, []) if len(p) == len(args)), None)
        if params is not None and name in PARAM_ENUMS:
            params = list(params)
            for i, enum in PARAM_ENUMS[name].items():
                params[i] = enum
        if not params:
            return m.group(0)
        for i, (arg, ptype) in enumerate(zip(args, params)):
            table = enums.get(ptype.strip())
            if table and re.fullmatch(r"-?\d+|0x[0-9a-f]+", arg) and int(arg, 0) in table:
                args[i] = table[int(arg, 0)]
        return f"{name}({', '.join(args)})"
    return re.sub(r"\b(\w+)\(((?:[^()]|\([^()]*\))*)\)", fix, text)


def closing_paren(text):
    """Index of the parenthesis closing an already opened one."""
    depth = 1
    for i, ch in enumerate(text):
        depth += {"(": 1, ")": -1}.get(ch, 0)
        if depth == 0:
            return i
    return len(text)


def tidy_expressions(text):
    text = re.sub(r"\boperator_new__\(", "operator new[](", text)
    text = re.sub(r"\boperator_delete__\(", "operator delete[](", text)
    text = re.sub(r"\boperator_new\(", "operator new(", text)
    text = re.sub(r"\boperator_delete\(", "operator delete(", text)
    text = re.sub(r"\b([\w.\->\[\]]+) != (?:false|'\\0')", r"\1", text)
    text = re.sub(r"\b([\w.\->\[\]]+) == (?:false|'\\0')", r"!\1", text)
    text = re.sub(r"\(\(([^()]*)\)\)", r"(\1)", text)
    text = re.sub(r"\s*&&\s*\(?!NAN\([^()]*\)\)?", "", text)
    text = re.sub(r"\(?!NAN\([^()]*\)\)?\s*&&\s*", "", text)
    text = re.sub(r"\([\w:<> ]+ \*\)0x0\b", "NULL", text)
    text = re.sub(r"\+ -(\d)", r"- \1", text)
    return text


def reindent(text):
    """Join Ghidra's wrapped statements and re-indent by brace depth (4 spaces)."""
    lines = [l.strip() for l in text.split("\n")]
    joined, buf = [], ""
    for line in lines:
        if not line:
            if buf:
                joined.append(buf)
                buf = ""
            joined.append("")
            continue
        buf = f"{buf} {line}".strip() if buf else line
        if buf.endswith((";", "{", "}", "*/")) or buf.startswith(("#", "//")) or buf.count("(") <= buf.count(")") \
                and not buf.endswith((",", "(", "&&", "||", "=")) and (buf.startswith((":", "CL", "C")) or True):
            if buf.count("(") <= buf.count(")"):
                joined.append(buf)
                buf = ""
    if buf:
        joined.append(buf)
    out, depth = [], 0
    for line in joined:
        line = re.sub(r"\(\s+", "(", re.sub(r"\s+\)", ")", line))
        if line.startswith("}"):
            depth = max(depth - 1, 0)
        out.append(("    " * depth + line) if line else "")
        if line.endswith("{"):
            depth += 1
    text = "\n".join(out)
    return re.sub(r"\n{3,}", "\n\n", text)


def convert(code, methods, f=None, signatures=None, enums=None):
    text = re.sub(r"/\*.*?\*/", "", code, flags=re.S)
    # Ghidra wraps long calls between the name and the parenthesis, and long
    # qualified names before `::`.
    text = re.sub(r"(\w)\s*\n\s*\(", r"\1(", text)
    text = re.sub(r"([\w>])\s*\n\s*::", r"\1::", text)
    for pattern, repl in TYPES:
        text = re.sub(pattern, repl, text)
    # Signature (everything before the opening brace): drop __thiscall and `this`.
    brace = re.search(r"\n\{", text)
    head, text = (text[:brace.start()], text[brace.start():]) if brace else ("", text)
    head = re.sub(r"/\*[^*]*\*/\n?", "", head)
    head = re.sub(r"__thiscall\s+", "", head)
    head = re.sub(r"\(([\w:<>, ]+) \*this,?\s*", "(", head, count=1)
    head = re.sub(r"\(void\)", "()", head, count=1)
    head = re.sub(r"\s+", " ", head).strip()
    if f is not None:
        # Parameter types from the symbol (Ghidra drops const), names from Ghidra.
        names = re.findall(r"(\w+)\s*(?:,|\)$)", head.split("(", 1)[1]) if "(" in head else []
        types = [t for t in split_args(f.get("params") or "") if t != "void"]
        if len(names) == len(types):
            params = ", ".join(f"{cxx_type(t)} {n}" for t, n in zip(types, names))
            prefix = "" if f["kind"] in ("ctor", "dtor") else head.split(f["demangled"].split("(")[0])[0]
            head = f"{prefix}{f['demangled'].split('(')[0]}({params})"
    text = drop_refcount_blocks(text)
    text = inline_temp_strings(text)
    # Constructors: base-constructor calls and vptr stores are implicit in C++.
    init = re.search(r"\n[ \t]*(\w+)::\1\s*\(\s*\(\w+ \*\)this\s*,?\s*([^;]*)\);", text)
    if init and f is not None and f["kind"] == "ctor":
        head += f"\n    : {init.group(1)}({re.sub(chr(10) + r'\s*', ' ', init.group(2)).rstrip(')').strip()})"
        text = text[:init.start()] + text[init.end():]
    text = re.sub(r"\n[ \t]*(?:\*\([^;]*\*\*\)\s*)?\(?this\)?->_vptr\s*=\s*[^;]*;", "", text)
    text = re.sub(r"\n[ \t]*\*\(\w+ \*\*\*?\)this = [^;]*;", "", text)
    # new: allocation followed by the constructor call on the same pointer.
    text = re.sub(r"(\w+) = \((\w+) \*\)(?:Ogre::NedAllocImpl::allocBytes|operator_new)\([^;]*\);\n([ \t]*)"
                  r"\2::\2\(\1(?:,\s*)?([^;]*)\);",
                  lambda m: f"{m.group(1)} = new {m.group(2)}({m.group(4)});", text)
    # Virtual calls through typed vtables.
    text = re.sub(r"\(\*\(?this\)?->_vptr->(\w+)\)\(this,?\s*", r"\1(", text)
    text = re.sub(r"\(\*\(?([\w\[\]]+)\)?->_vptr->(\w+)\)\(\1,?\s*", r"\1->\2(", text)
    text = call_rewrite(text, methods)
    if signatures and enums:
        text = enum_arguments(text, signatures, enums)
    # AddProperty takes the accessors as void*.
    text = re.sub(r"\b(AddProperty(?:WithInterpreterFunctions)?\([^;]*?,\s*)(\w+),\s*(\w+),",
                  lambda m: f"{m.group(1)}(void*){m.group(2)}, (void*){m.group(3)},", text)
    text = re.sub(r"\bthis->(?=\w)", "", text)
    # Base and member destructor calls on this are implicit in a destructor.
    text = re.sub(r"\n[ \t]*~\w+\(\);", "", text)
    text = re.sub(r"(?<![>.\w])(\w+)\(this\)", r"\1()", text)
    text = re.sub(r"(?<![>.\w])(\w+)\(this,\s*", r"\1(", text)
    text = tidy_expressions(text)
    text = drop_dead_stores(text)
    text = drop_unused_locals(text)
    text = reindent(text)
    text = re.sub(r"\n[ \t]*return;\n\}\s*$", "\n}", text)
    text = re.sub(r"\n{3,}", "\n\n", head + text)
    return text.strip() + "\n"


def cxx_type(demangled):
    t = demangled.strip()
    m = re.fullmatch(r"(.+?) const\*", t)
    if m:
        return f"const {m.group(1)}*"
    m = re.fullmatch(r"(.+?) const&", t)
    if m:
        return f"const {m.group(1)}&"
    return t.replace("std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >", "std::wstring")


# Parameters declared as plain integers whose values are known enums.
PARAM_ENUMS = {"BroadcastEvent": {0: "EOUTPUT_EVENTS"}}


def signatures_of(db):
    """short name -> list of parameter type lists (all overloads)."""
    out = {}
    for f in db["functions"].values():
        short = f["demangled"].split("(")[0].split("::")[-1]
        params = [p for p in split_args(f.get("params") or "") if p != "void"]
        if params not in out.setdefault(short, []):
            out[short].append(params)
    return out


def known_methods(db):
    """(class, method) pairs of real classes; namespaces such as UTILITIES are excluded."""
    import types_export
    real = {name for name in db["classes"] if types_export.is_class(db, name)}
    out = set()
    for f in db["functions"].values():
        if f.get("scope") in real and f["kind"] in ("function", "dtor", "inline_or_template"):
            out.add((f["scope"], f["demangled"].split("(")[0].split("::")[-1]))
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("files", nargs="+", type=Path)
    args = parser.parse_args()
    db = elfdb.load_db()
    methods, signatures, enums = known_methods(db), signatures_of(db), parse_enums()
    for path in args.files:
        f = db["functions"].get(path.stem)
        print(convert(path.read_text(), methods, f, signatures, enums))


if __name__ == "__main__":
    main()
