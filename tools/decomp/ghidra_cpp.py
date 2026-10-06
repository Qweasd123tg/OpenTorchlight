#!/usr/bin/env python3
"""Clean Ghidra C output into a C++ draft.

    python3 tools/decomp/ghidra_cpp.py build-decomp/drafts/AIFlag.cpp/raw/*.c > draft.cpp

Rewrites, each one local and conservative:
- `void __thiscall C::m(C *this, ...)` -> `void C::m(...)`;
- `this->field` -> `field`; `(*p->_vptr->Method)(p, a)` -> `p->Method(a)`;
- `C::m(this, a)` -> `C::m(a)`, `C::m(p, a)` -> `p->C::m(a)` for known methods;
- Ghidra integer types -> C++ types;

Lifecycle/idiom cleanup requires experimental_cleanup=True. It is a diagnostic
experiment without ownership, effect or type proofs and is disabled by default.

The output is a draft for a human or agent; it is not expected to compile as is.
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import sys
from functools import wraps

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402

ROOT = elfdb.ROOT


def protect_lexical(text):
    """Hide literal contents and comments from textual rewrites, retaining syntax.

    The tokens are private to this input and restored after every rewrite. Keeping
    quotes lets argument and string-constructor patterns still recognize literals.
    """
    prefix = "__OTL_LEX_"
    while prefix in text:
        prefix += "_"
    tokens = {}
    pattern = re.compile(r'//[^\n]*|/\*.*?\*/|(?:L)?"(?:[^"\\]|\\.)*"|(?:L)?\'(?:[^\'\\]|\\.)*\'', re.S)

    def hide(m):
        original = m.group(0)
        token = f"{prefix}{len(tokens)}__"
        if original.startswith(("//", "/*")):
            replacement = f"/*{token}*/"
        else:
            wide = "L" if original.startswith("L") else ""
            quote = original[len(wide)]
            replacement = f"{wide}{quote}{token}{quote}"
        # Reindentation may join a comment to a following declaration. A restored
        # line comment must always terminate before the next code token.
        tokens[replacement] = original + ("\n" if original.startswith("//") else "")
        return replacement

    protected = pattern.sub(hide, text)

    def restore(result):
        for token, original in tokens.items():
            result = result.replace(token, original)
        return result
    return protected, restore


def lexical_rewrite(fn):
    @wraps(fn)
    def protected(text, *args, **kwargs):
        code, restore = protect_lexical(text)
        return restore(fn(code, *args, **kwargs))
    return protected


def cv_suffix(f):
    """elfdb stores textual cv qualifiers, not Itanium mangling letters."""
    cv = f.get("cv")
    if cv is None:
        cv = elfdb.parse_demangled(f.get("demangled", ""))[2]
    words = set((cv or "").split())
    return "".join(" " + word for word in ("const", "volatile") if word in words)


def signature_key(f):
    qualified = f.get("qualified") or elfdb.parse_demangled(f["demangled"])[0]
    params = tuple(re.sub(r"\s+", "", cxx_type(t)) for t in split_args(f.get("params") or "") if t != "void")
    return qualified, params, cv_suffix(f).strip(), f.get("static")

TYPES = [
    (r"\bundefined1\b", "char"), (r"\bundefined2\b", "short"), (r"\bundefined4\b", "int"),
    (r"\bundefined8\b", "long long"), (r"\bundefined\b", "char"), (r"\bulonglong\b", "unsigned long long"),
    (r"\blonglong\b", "long long"), (r"\bulong\b", "unsigned long"), (r"\buint\b", "unsigned int"),
    (r"\bushort\b", "unsigned short"), (r"\bbyte\b", "unsigned char"), (r"\bsbyte\b", "signed char"),
    (r"\buchar\b", "unsigned char"),
    (r"\bfloat10\b", "long double"), (r"\bwchar32\b", "wchar_t"), (r"\bwstring_conflict\b", "std::wstring"), (r"(?<!::)\bwstring\b", "std::wstring"),
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


def _cast_to(arg, cls):
    """arg is `(cls *)expr` (possibly with namespace differences)."""
    m = re.match(r"\(([\w:<>, ]+?)\s*\*\)", arg)
    if not m:
        return False
    norm = lambda t: re.sub(r"\s+", "", t)  # noqa: E731
    return norm(m.group(1)) == norm(cls)


@lexical_rewrite
def call_rewrite(text, methods):
    """Explicit C::m(obj, args) stays a qualified direct call in C++ syntax."""
    out, i = [], 0
    pattern = re.compile(r"\b((?:[A-Za-z_]\w*(?:<[^()]*?>)?::)*[A-Za-z_]\w*(?:<[^()]*?>)?)::(~?[A-Za-z_]\w*)\(")
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
            # The receiver cast may encode a base adjustment or a void* type;
            # keep it rather than guessing that it is redundant.
            obj = args[0]
            rest = ", ".join(args[1:])
            if obj == "this":
                out.append(f"{cls}::{meth}({rest})")
            elif re.fullmatch(r"&?[\w.\->\[\]]+", obj):
                out.append(f"{obj[1:]}.{cls}::{meth}({rest})" if obj.startswith("&") else f"{obj}->{cls}::{meth}({rest})")
            else:
                out.append(f"({obj})->{cls}::{meth}({rest})")
        else:
            # A cast of the first argument alone does not establish an implicit
            # receiver: a static method can also take a pointer to its class.
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
        # A callable: a replacement string would reinterpret the literal's backslashes.
        text = re.sub(rf"\([\w:]+ \*\)&?{local}\b", lambda _m, lit=literal: lit, text)
        text = re.sub(rf"&{local}\b|\b{local}\b(?!\s*\[)", lambda _m, lit=literal: lit, text)
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
        overloads = [p for p in signatures.get(name, []) if len(p) == len(args)]
        params = overloads[0] if overloads and all(p == overloads[0] for p in overloads) else None
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
    return re.sub(r"\b((?:\w+::)*\w+)\(((?:[^()]|\([^()]*\))*)\)", fix, text)


def closing_paren(text):
    """Index of the parenthesis closing an already opened one."""
    depth = 1
    for i, ch in enumerate(text):
        depth += {"(": 1, ")": -1}.get(ch, 0)
        if depth == 0:
            return i
    return len(text)


# An object expression Ghidra prints for a TArrayList: (this->m_List), (p->m_List), local_x.m_List, local_x
_OBJ = r"(?:\([\w\->.\[\]]+\)|[\w]+(?:\.\w+)*(?:\[0\])?)"
_ELEMENT_CAST = r"(?:\([\w:<>, ]+ \*+\))?"


def _bare(obj):
    """(this->m_List) -> this->m_List."""
    return obj[1:-1] if obj.startswith("(") and obj.endswith(")") else obj


def _element(m):
    """`X.m_pData + i` or `(T *)((ulong)i * 8 + (long)X.m_pData)`: element i of X."""
    x, i = re.escape(m.group("x")), re.escape(m.group("i"))
    forms = [rf"{_ELEMENT_CAST}{x}\.m_pData \+ (?:\(\w+\))?{i}",
             rf"{_ELEMENT_CAST}\(\(ulong\){i} \* (?:0x[0-9a-f]+|\d+) \+ \(long\){x}\.m_pData\)"]
    return any(re.fullmatch(f, m.group("data")) for f in forms)


def tarraylist_access(text):
    """The inlined TArrayList::operator[] -> `p = &X[i];` (its capacity check and fallback to
    element 0 are the operator's). Ghidra prints it either as
    `if (i < X.m_nCapacity) p = X.m_pData + i; else p = X.m_pData;` or with the fallback first:
    `p = X.m_pData; if (i < X.m_nCapacity) p = X.m_pData + i;`."""
    check = rf"if \((?P<i>\w+) < (?P<x>{_OBJ})\.m_nCapacity\) \{{\s*(?P<p>\w+) = (?P<data>[^;\n]+);\s*\}}"
    with_else = re.compile(rf"(?P<indent>\n[ \t]*){check}\s*else \{{\s*(?P=p) = {_ELEMENT_CAST}(?P=x)\.m_pData;\s*\}}")
    fallback_first = re.compile(rf"(?P<indent>\n[ \t]*)(?P<p0>\w+) = {_ELEMENT_CAST}(?P<x0>{_OBJ})\.m_pData;\s*{check}")

    def fix(m):
        if not _element(m) or ("p0" in m.groupdict() and (m.group("p0"), m.group("x0")) != (m.group("p"), m.group("x"))):
            return m.group(0)
        return f"{m.group('indent')}{m.group('p')} = &{_bare(m.group('x'))}[{m.group('i')}];"
    text = fallback_first.sub(fix, with_else.sub(fix, text))

    # The element itself rather than its address.
    head = rf"(?P<indent>\n[ \t]*)if \((?P<i>\w+) < (?P<x>{_OBJ})\.m_nCapacity\) \{{\s*"
    value = rf"{_ELEMENT_CAST}(?P=x)\.m_pData\[(?P=i)\]"
    first = rf"\*{_ELEMENT_CAST}(?P=x)\.m_pData"
    text = re.sub(rf"{head}(?P<v>\w+) = {value};\s*\}}\s*else \{{\s*(?P=v) = {first};\s*\}}",
                  lambda m: f"{m.group('indent')}{m.group('v')} = {_bare(m.group('x'))}[{m.group('i')}];", text)
    return re.sub(rf"{head}return {value};\s*\}}\s*return {first};",
                  lambda m: f"{m.group('indent')}return {_bare(m.group('x'))}[{m.group('i')}];", text)


def tarraylist_count(text):
    """Reading X.m_nCount (not writing it: that is an inlined add/removeAt/clear) -> X.size()."""
    return re.sub(rf"(?<![&\w>.+-])({_OBJ})\.m_nCount\b(?!\s*(?:=[^=]|\+\+|--|\+=|-=))",
                  lambda m: f"{_bare(m.group(1))}.size()", text)

RETURN_STORAGE = "__return_storage_ptr__"
_SRET = None
_SRET_INPUT = None


def returned_by_pointer():
    """Qualified names of the functions that return an object through a hidden pointer, from
    the header prototypes types_export.py writes (Ghidra gets them as custom storage)."""
    global _SRET, _SRET_INPUT
    import hashlib
    path = ROOT / "build-decomp" / "types.json"
    raw = path.read_bytes() if path.exists() else b"{}"
    key = hashlib.sha256(raw).hexdigest()
    if _SRET is None or _SRET_INPUT != key:
        protos = json.loads(raw).get("prototypes", {})
        # Draft call text has no exact symbol identity. A qualified name shared
        # by overloads cannot identify the hidden-return ABI safely.
        grouped = {}
        for prototype in protos.values():
            grouped.setdefault(prototype["name"].split("(")[0], []).append(prototype)
        _SRET = {name for name, rows in grouped.items()
                 if len(rows) == 1 and rows[0].get("sret")}
        _SRET_INPUT = key
    return _SRET


def hidden_return_signature(head):
    """`wstring * C::f(wstring *__return_storage_ptr__, C *this, T param_3)` -> `wstring C::f(T param_3)`
    and how many hidden parameters preceded the real ones (Ghidra numbers params by position)."""
    m = re.search(rf"\(\s*([\w:<>, ]+?)\s*\*\s*{RETURN_STORAGE}\s*,?\s*", head)
    if not m:
        return head, 0
    hidden = 1
    head = head[:m.start()] + "(" + head[m.end():]
    this = re.match(r"\(\s*[\w:<>, ]+? \*this\s*,?\s*", head[m.start():])
    if this:
        head = head[:m.start()] + "(" + head[m.start() + this.end():]
        hidden += 1
    head = re.sub(rf"^(\s*){re.escape(m.group(1))}\s*\*\s*", lambda _m: _m.group(1) + m.group(1) + " ", head, count=1)
    return head, hidden


def renumber_params(text, hidden):
    return re.sub(r"\bparam_(\d+)\b", lambda m: f"param_{int(m.group(1)) - hidden}"
                  if int(m.group(1)) > hidden else m.group(0), text)


def hidden_return_body(text):
    """Inside a function returning through the hidden pointer: constructing the result or
    passing the pointer on to another such call is a return statement."""
    storage = rf"(?:\([\w:<>, ]+ \*\))?{RETURN_STORAGE}"

    def construct(m):
        args = split_args(m.group(2))
        if args and re.fullmatch(r"&?local_\w+|\(\w+ \*\)&?local_\w+|&local_\w+", args[-1]) and len(args) > 1:
            args = args[:-1]  # the allocator temporary
        if len(args) == 1 and re.fullmatch(r'L?"(?:[^"\\]|\\.)*"', args[0]):
            return f"{m.group(1)}return {args[0]};"
        if len(args) == 1:
            copy = re.fullmatch(r"(?:\([\w:<>, ]+ \*\))?(&?)([\w.\->\[\]]+)", args[0])
            if copy:
                return f"{m.group(1)}return {copy.group(2) if copy.group(1) else '*' + copy.group(2)};"
        return f"{m.group(1)}return std::wstring({', '.join(args)});"
    text = re.sub(rf"(\n[ \t]*)std::w?string::(?:w?string|basic_string)\s*\(\s*{storage}\s*,\s*([^;]*)\);",
                  construct, text)
    text = re.sub(rf"(\n[ \t]*)((?:[A-Za-z_]\w*::)*[A-Za-z_~]\w*)\(\s*{storage}\s*,\s*([^;]*)\);",
                  lambda m: f"{m.group(1)}return {m.group(2)}({m.group(3)});", text)
    if len(re.findall(RETURN_STORAGE, text)) == len(re.findall(rf"\breturn {RETURN_STORAGE};", text)):
        text = re.sub(rf"\n[ \t]*return {RETURN_STORAGE};", "", text)
    return text


def recoverable_hidden_return(text):
    """Only terminal construction/forwarding can become an early C++ return.

    Subsequent cleanup, effects, an overwrite or an unknown storage consumer
    requires structured lifetime analysis. Keep that draft ABI explicit instead
    of silently deleting those statements by returning too early.
    """
    storage = rf"(?:\([\w:<>, ]+ \*\))?{RETURN_STORAGE}"
    pattern = re.compile(rf"\n[ \t]*((?:[A-Za-z_]\w*::)*[A-Za-z_~]\w*)\(\s*{storage}\s*,\s*[^;]*\);")
    calls = list(pattern.finditer(text))
    if not calls:
        return False
    known = returned_by_pointer()
    for call in calls:
        if not re.fullmatch(r"std::w?string::(?:w?string|basic_string)", call.group(1)) and call.group(1) not in known:
            return False
    # The first result write must end its branch. An overwrite in the same
    # branch would otherwise be replaced by an unconditional early return.
    for call in calls:
        next_close = text.find("}", call.end())
        tail = text[call.end():next_close if next_close >= 0 else len(text)]
        tail = re.sub(rf"\breturn\s+{RETURN_STORAGE}\s*;", "", tail)
        if tail.strip():
            return False
    suffix = text[calls[0].start():]
    for call in reversed(calls):
        begin, end = call.start() - calls[0].start(), call.end() - calls[0].start()
        suffix = suffix[:begin] + suffix[end:]
    suffix = re.sub(rf"\breturn\s+{RETURN_STORAGE}\s*;", "", suffix)
    suffix = re.sub(r"\belse\b|[{}\s]", "", suffix)
    return not suffix and RETURN_STORAGE not in text[:calls[0].start()]


def hidden_return_calls(text):
    """`C::getName(&local_40, obj, args)` of a function returning through a hidden pointer ->
    `local_40 = C::getName(obj, args)`, which call_rewrite then turns into a method call."""
    sret = returned_by_pointer()

    def fix(m):
        if m.group(2) not in sret:
            return m.group(0)
        return f"{m.group(1)}{m.group(3)} = {m.group(2)}({m.group(4)});"
    return re.sub(r"(\n[ \t]*)((?:[A-Za-z_]\w*::)+[A-Za-z_]\w*)\(\s*(?:\([\w:<>, ]+ \*\))?&(local_\w+)\s*,?\s*([^;]*)\);",
                  fix, text)


def reference_arguments(text, signatures):
    """`&x` passed where every overload of that arity takes a reference -> `x`."""
    def fix(m):
        name, args = m.group(1), split_args(m.group(2))
        overloads = [p for p in signatures.get(name, []) if len(p) == len(args)]
        if not overloads:
            return m.group(0)
        changed = False
        for i, arg in enumerate(args):
            if all(p[i].strip().endswith("&") for p in overloads):
                plain = re.fullmatch(r"(?:\([\w:<>, ]+ \*\))?&([\w.\->\[\]]+)", arg)
                if plain:
                    args[i] = plain.group(1)
                    changed = True
        return f"{name}({', '.join(args)})" if changed else m.group(0)
    return re.sub(r"\b((?:\w+::)*\w+)\(((?:[^()]|\([^()]*\))*)\)", fix, text)


NAN_GUARD = r"(?:!NAN\(([^()]*)\)|\(!NAN\(([^()]*)\)\))"
NAN_GROUP = rf"(?:{NAN_GUARD}|\({NAN_GUARD}(?:\s*&&\s*{NAN_GUARD})+\))"
# An ordered comparison without parentheses or logical operators in its operands.
ORDERED = r"[\w.\->\[\]*+/ ]+?\s(?:==|<=?|>=?)\s-?[\w.\->\[\]*+/ ]+?"
CLAUSE_END = r"(?=\s*(?:\)|&&|\|\||;|$))"


def drop_nan_guards(text):
    """`!NAN(x) && x < y` -> `x < y`. An ordered comparison (==, <, <=, >, >=) is already false
    when an operand is NaN, so a guard on one of its operands is redundant. Every other NAN() stays:
    `!NAN(x) && !(x < y)` or `!NAN(x) && x != y` differ from the unguarded expression for NaN, and
    so does `!NAN(x) && p->x < y`: the guarded expression must be a whole operand, not a name in it."""
    def bare(expr):
        return re.sub(r"\s+", "", expr)

    def guarded(group, comparison):
        names = [bare(n) for n in re.findall(r"NAN\(([^()]*)\)", group)]
        operands = re.split(r"\s(?:==|<=?|>=?)\s", comparison.strip(), maxsplit=1)
        if len(operands) != 2:
            return False
        # A negated operand is NaN exactly when the operand is.
        whole = {bare(o)[1:] if bare(o).startswith("-") else bare(o) for o in operands}
        return bool(names) and all(n in whole for n in names)

    def before(m):
        return m.group("cmp") if guarded(m.group("nan"), m.group("cmp")) else m.group(0)

    def after(m):
        return m.group("cmp") if guarded(m.group("nan"), m.group("cmp")) else m.group(0)

    for _ in range(8):
        new = re.sub(rf"(?P<nan>{NAN_GROUP})\s*&&\s*(?P<cmp>(?<![!\w]){ORDERED}){CLAUSE_END}", before, text)
        new = re.sub(rf"(?<=[(&|]\s)(?P<cmp>{ORDERED})\s*&&\s*(?P<nan>{NAN_GROUP}){CLAUSE_END}", after, new)
        new = re.sub(rf"(?<=\()(?P<cmp>{ORDERED})\s*&&\s*(?P<nan>{NAN_GROUP}){CLAUSE_END}", after, new)
        if new == text:
            break
        text = new
    return text


@lexical_rewrite
def tidy_expressions(text, *, proven_nan_operands=False):
    text = re.sub(r"\boperator_new__\(", "operator new[](", text)
    text = re.sub(r"\boperator_delete__\(", "operator delete[](", text)
    text = re.sub(r"\boperator_new\(", "operator new(", text)
    text = re.sub(r"\boperator_delete\(", "operator delete(", text)
    # Comparisons produce a boolean even when their operand is an integer or
    # pointer. Without a proven boolean type, replacing one with its operand
    # changes values in returns, arithmetic, assignments and call arguments.
    text = re.sub(r"\(\(([^()]*)\)\)", r"(\1)", text)
    if proven_nan_operands:
        text = drop_nan_guards(text)
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


def convert(code, methods, f=None, signatures=None, enums=None, *, experimental_cleanup=False):
    text, restore = protect_lexical(code)
    # Ghidra wraps long calls between the name and the parenthesis, and long
    # qualified names before `::`.
    text = re.sub(r"(\w)\s*\n\s*\(", r"\1(", text)
    text = re.sub(r"([\w>])\s*\n\s*::", r"\1::", text)
    for pattern, repl in TYPES:
        text = re.sub(pattern, repl, text)
    # Signature (everything before the opening brace): drop __thiscall and `this`.
    brace = re.search(r"\n\{", text)
    head, text = (text[:brace.start()], text[brace.start():]) if brace else ("", text)
    head = re.sub(r"__thiscall\s+", "", head)
    proposed_head, hidden = hidden_return_signature(head)
    if hidden and not recoverable_hidden_return(text):
        hidden = 0
    else:
        head = proposed_head
    if hidden:
        head = renumber_params(head, hidden)
        text = hidden_return_body(renumber_params(text, hidden))
    head = re.sub(r"\(([\w:<>, ]+) \*this,?\s*", "(", head, count=1)
    head = re.sub(r"\(void\)", "()", head, count=1)
    head = re.sub(r"\s+", " ", head).strip()
    if f is not None:
        # Parameter types from the symbol (Ghidra drops const), names from Ghidra.
        names = re.findall(r"(\w+)\s*(?:,|\)$)", head.split("(", 1)[1]) if "(" in head else []
        types = [t for t in split_args(f.get("params") or "") if t != "void"]
        if len(names) == len(types):
            params = ", ".join(f"{cxx_type(t)} {n}" for t, n in zip(types, names))
            qualified = f.get("qualified") or elfdb.parse_demangled(f["demangled"])[0]
            prefix = "" if f["kind"] in ("ctor", "dtor") else head.split(qualified)[0]
            head = f"{prefix}{qualified}({params}){cv_suffix(f)}"
        elif cv_suffix(f) and not head.endswith(cv_suffix(f)):
            head += cv_suffix(f)
    if experimental_cleanup:
        text = drop_refcount_blocks(text)
        text = inline_temp_strings(text)
        text = tarraylist_count(tarraylist_access(text))
    # Constructors: base-constructor calls and vptr stores are implicit in C++.
    init = re.search(r"\n[ \t]*(\w+)::\1\s*\(\s*\(\w+ \*\)this\s*,?\s*([^;]*)\);", text)
    if experimental_cleanup and init and f is not None and f["kind"] == "ctor":
        head += f"\n    : {init.group(1)}({re.sub(chr(10) + r'\s*', ' ', init.group(2)).rstrip(')').strip()})"
        text = text[:init.start()] + text[init.end():]
    if experimental_cleanup and f is not None and f["kind"] in ("ctor", "dtor"):
        text = re.sub(r"\n[ \t]*(?:\*\([^;]*\*\*\)\s*)?\(?this\)?->_vptr\s*=\s*[^;]*;", "", text)
        text = re.sub(r"\n[ \t]*\*\(\w+ \*\*\*?\)this = [^;]*;", "", text)
    # new: allocation followed by the constructor call on the same pointer.
    if experimental_cleanup:
        text = re.sub(r"(\w+) = \((\w+) \*\)(?:Ogre::NedAllocImpl::allocBytes|operator_new)\([^;]*\);\n([ \t]*)"
                      r"\2::\2\(\1(?:,\s*)?([^;]*)\);",
                      lambda m: f"{m.group(1)} = new {m.group(2)}({m.group(4)});", text)
    # Virtual calls through typed vtables.
    text = re.sub(r"\(\*\(?this\)?->_vptr->(\w+)\)\(this,?\s*", r"\1(", text)
    text = re.sub(r"\(\*\(?([\w\[\]]+)\)?->_vptr->(\w+)\)\(\1,?\s*", r"\1->\2(", text)
    text = hidden_return_calls(text)
    text = call_rewrite(text, methods)
    if signatures:
        text = reference_arguments(text, signatures)
    if signatures and enums:
        text = enum_arguments(text, signatures, enums)
    # AddProperty takes the accessors as void*.
    text = re.sub(r"\b(AddProperty(?:WithInterpreterFunctions)?\([^;]*?,\s*)(\w+),\s*(\w+),",
                  lambda m: f"{m.group(1)}(void*){m.group(2)}, (void*){m.group(3)},", text)
    text = re.sub(r"\bthis->(?=\w)", "", text)
    # Base and member destructor calls on this are implicit in a destructor.
    if experimental_cleanup and f is not None and f["kind"] == "dtor":
        text = re.sub(r"\n[ \t]*~\w+\(\);", "", text)
    # Unqualified helper(this, ...) may be a real free function, not a member.
    text = tidy_expressions(text, proven_nan_operands=experimental_cleanup)
    if experimental_cleanup:
        text = drop_dead_stores(text)
        text = drop_unused_locals(text)
    text = reindent(text)
    text = re.sub(r"\n[ \t]*return;\n\}\s*$", "\n}", text)
    text = re.sub(r"\n{3,}", "\n\n", head + text)
    return restore(text.strip()) + "\n"


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
    """Complete qualified name -> overloads; never merge unrelated scopes."""
    out = {}
    for f in db["functions"].values():
        qualified = f.get("qualified") or elfdb.parse_demangled(f["demangled"])[0]
        params = [p for p in split_args(f.get("params") or "") if p != "void"]
        if params not in out.setdefault(qualified, []):
            out[qualified].append(params)
    return out


def known_methods(db):
    """(class, method) pairs of real classes; namespaces such as UTILITIES are excluded."""
    import types_export
    real = {name for name in db["classes"] if types_export.is_class(db, name)}
    path = ROOT / "build-decomp" / "types.json"
    protos = json.loads(path.read_text()).get("prototypes", {}) if path.exists() else {}
    out = set()
    for f in db["functions"].values():
        prototype = protos.get(f["address"], {})
        member = (prototype.get("static") is False or f["kind"] == "dtor"
                  or bool(f.get("vslots")) or bool(cv_suffix(f)))
        if (f.get("scope") in real and f["kind"] in ("function", "dtor", "inline_or_template")
                and member and prototype.get("static") is not True):
            out.add((f["scope"], f.get("method") or elfdb.parse_demangled(f["demangled"])[0].split("::")[-1]))
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
