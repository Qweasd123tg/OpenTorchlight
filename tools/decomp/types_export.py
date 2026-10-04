#!/usr/bin/env python3
"""Class layouts of the recovered headers, read from GCC 4.4.7 debug info.

Compiles every decomp/include header into one object with -g, parses
`readelf --debug-dump=info` and writes build-decomp/types.json:

    {"classes": {"CLogicTimer": {"size": 120, "bases": [{"name": ..., "offset": 0}],
                                 "fields": [{"offset": 88, "name": "m_fMinTime", "type": "float", "size": 4}]}}}

Classes without a recovered header are added from tools/decomp/layout.py
(names are hints there). Used by tools/decomp/ghidra_draft.py.

    python3 tools/decomp/types_export.py
"""
from __future__ import annotations

import json
from pathlib import Path
import re
import subprocess
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import toolchain  # noqa: E402

ROOT = elfdb.ROOT
OUT = ROOT / "build-decomp" / "types.json"


def compile_headers(tmp):
    headers = sorted(p.name for p in (ROOT / "decomp" / "include").glob("*.h"))
    first = ["EmptyStrings.h"] if "EmptyStrings.h" in headers else []
    source = Path(tmp) / "all_headers.cpp"
    source.write_text("".join(f'#include "{h}"\n' for h in first + [h for h in headers if h not in first]))
    return toolchain.compile_source(source, Path(tmp) / "all_headers.o",
                                    ["-g", "-O0", "-fno-eliminate-unused-debug-types", "-femit-class-debug-always"])


def parse_dies(obj):
    text = subprocess.run(["readelf", "--debug-dump=info", "-W", str(obj)], capture_output=True, text=True,
                          check=True, env={"LC_ALL": "C", "PATH": "/usr/bin:/bin"}).stdout
    dies, stack = {}, []
    current = None
    for line in text.splitlines():
        m = re.match(r"^\s*<(\d+)><([0-9a-f]+)>: Abbrev Number: (\d+)(?: \((\w+)\))?", line)
        if m:
            depth, offset, tag = int(m.group(1)), int(m.group(2), 16), m.group(4)
            if tag is None:  # null entry closes a sibling list
                continue
            current = {"tag": tag, "depth": depth, "children": [], "attrs": {}}
            dies[offset] = current
            del stack[depth:]
            if stack:
                stack[-1]["children"].append(offset)
            stack.append(current)
            continue
        a = re.match(r"^\s*<[0-9a-f]+>\s+(DW_AT_\w+)\s*:\s*(.*)$", line)
        if a and current is not None:
            name, value = a.group(1), a.group(2).strip()
            # binutils >= 2.40 prefixes values with their form: "(data1) 104", "(ref4) <0x2d>, Name".
            form = re.match(r"^\((\w+)\)\s*(.*)$", value)
            if form and form.group(1) not in ("indirect",):
                value = form.group(2)
            if name in ("DW_AT_type", "DW_AT_specification"):
                ref = re.search(r"<0x([0-9a-f]+)>", value)
                current["attrs"][name] = int(ref.group(1), 16) if ref else None
            elif name == "DW_AT_data_member_location":
                n = re.search(r"DW_OP_plus_uconst: (\d+)", value)
                current["attrs"][name] = int(n.group(1)) if n else (int(value, 0) if re.fullmatch(r"0x[0-9a-f]+|\d+", value) else None)
            elif name in ("DW_AT_byte_size", "DW_AT_upper_bound"):
                current["attrs"][name] = int(value, 0) if re.fullmatch(r"0x[0-9a-f]+|\d+", value) else None
            elif name in ("DW_AT_name", "DW_AT_MIPS_linkage_name", "DW_AT_linkage_name"):
                current["attrs"]["DW_AT_linkage_name" if "linkage" in name else name] = value.split(": ")[-1].strip()
            elif name in ("DW_AT_declaration", "DW_AT_artificial"):
                current["attrs"][name] = True
    return dies


def type_name(dies, ref, depth=0):
    if ref is None or depth > 20:
        return "void"
    d = dies.get(ref)
    if not d:
        return "?"
    tag, attrs = d["tag"], d["attrs"]
    inner = lambda: type_name(dies, attrs.get("DW_AT_type"), depth + 1)  # noqa: E731
    if tag in ("DW_TAG_base_type", "DW_TAG_class_type", "DW_TAG_structure_type", "DW_TAG_union_type",
               "DW_TAG_enumeration_type", "DW_TAG_typedef"):
        name = attrs.get("DW_AT_name", "?")
        if name == "basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >" or name == "wstring":
            return "std::wstring"
        if name in ("basic_string<char, std::char_traits<char>, std::allocator<char> >", "string"):
            return "std::string"
        return name
    if tag == "DW_TAG_pointer_type":
        return inner() + "*"
    if tag == "DW_TAG_reference_type":
        return inner() + "&"
    if tag in ("DW_TAG_const_type", "DW_TAG_volatile_type"):
        return inner()
    if tag == "DW_TAG_array_type":
        bounds = [dies[c]["attrs"].get("DW_AT_upper_bound") for c in d["children"]
                  if dies[c]["tag"] == "DW_TAG_subrange_type"]
        return inner() + "".join(f"[{(b or 0) + 1}]" for b in bounds)
    if tag == "DW_TAG_subroutine_type":
        return "code"
    return "?"


def type_size(dies, ref, depth=0):
    d = dies.get(ref)
    if not d or depth > 20:
        return 0
    if "DW_AT_byte_size" in d["attrs"] and d["attrs"]["DW_AT_byte_size"]:
        return d["attrs"]["DW_AT_byte_size"]
    if d["tag"] in ("DW_TAG_pointer_type", "DW_TAG_reference_type"):
        return 8
    if d["tag"] == "DW_TAG_array_type":
        n = 1
        for c in d["children"]:
            if dies[c]["tag"] == "DW_TAG_subrange_type":
                n *= (dies[c]["attrs"].get("DW_AT_upper_bound") or 0) + 1
        return n * type_size(dies, d["attrs"].get("DW_AT_type"), depth + 1)
    return type_size(dies, d["attrs"].get("DW_AT_type"), depth + 1)


def header_dies():
    with tempfile.TemporaryDirectory(prefix="otl-types-") as tmp:
        return parse_dies(compile_headers(tmp))


def header_classes(dies):
    classes = {}
    for d in dies.values():
        if d["tag"] not in ("DW_TAG_class_type", "DW_TAG_structure_type") or d["attrs"].get("DW_AT_declaration"):
            continue
        name = d["attrs"].get("DW_AT_name")
        if not name or name.startswith(("_", "basic_string", "char_traits", "allocator")) or d["depth"] > 2:
            continue
        entry = {"size": d["attrs"].get("DW_AT_byte_size") or 0, "bases": [], "fields": [], "source": "header"}
        for c in d["children"]:
            child = dies[c]
            off = child["attrs"].get("DW_AT_data_member_location")
            if child["tag"] == "DW_TAG_inheritance":
                entry["bases"].append({"name": type_name(dies, child["attrs"].get("DW_AT_type")), "offset": off or 0})
            elif child["tag"] == "DW_TAG_member" and off is not None:
                ref = child["attrs"].get("DW_AT_type")
                entry["fields"].append({"offset": off, "name": child["attrs"].get("DW_AT_name", f"field_{off:x}"),
                                        "type": type_name(dies, ref), "size": type_size(dies, ref)})
        if name not in classes or len(entry["fields"]) > len(classes[name]["fields"]):
            classes[name] = entry
    return classes


PRIMITIVE = {"bool", "char", "short", "int", "unsigned int", "long long", "float", "double", "std::wstring",
             "std::string"}


def strip(dies, ref, depth=0):
    """The DIE behind typedefs, const and volatile."""
    d = dies.get(ref)
    while d and d["tag"] in ("DW_TAG_typedef", "DW_TAG_const_type", "DW_TAG_volatile_type") and depth < 20:
        ref = d["attrs"].get("DW_AT_type")
        d = dies.get(ref)
        depth += 1
    return d


def by_hidden_pointer(dies, ref, depth=0):
    """Itanium C++ ABI: a class with a user-declared copy constructor or destructor, or a base or
    member with one, comes back through a hidden pointer whatever its size; so does any object
    over 16 bytes."""
    d = strip(dies, ref)
    if not d or depth > 12 or d["tag"] not in ("DW_TAG_class_type", "DW_TAG_structure_type", "DW_TAG_union_type"):
        return False
    # GCC completes a class declared elsewhere in a separate DIE that points back to the declaration.
    spec = dies.get(d["attrs"].get("DW_AT_specification")) or {"attrs": {}, "children": []}
    attrs = {**spec["attrs"], **d["attrs"]}
    children = d["children"] + spec["children"]
    name = (attrs.get("DW_AT_name") or "").split("<")[0]
    if name in ("basic_string", "vector", "map", "set", "list", "deque", "multimap", "TArrayList"):
        return True
    if (attrs.get("DW_AT_byte_size") or 0) > 16:
        return True
    for c in children:
        child = dies[c]
        if child["tag"] == "DW_TAG_subprogram" and not child["attrs"].get("DW_AT_artificial"):
            n = child["attrs"].get("DW_AT_name", "")
            params = [dies[p] for p in child["children"] if dies[p]["tag"] == "DW_TAG_formal_parameter"
                      and not dies[p]["attrs"].get("DW_AT_artificial")]
            if n == "~" + name or (n == name and len(params) == 1
                                    and type_name(dies, params[0]["attrs"].get("DW_AT_type")).endswith("&")
                                    and strip(dies, (strip(dies, params[0]["attrs"].get("DW_AT_type")) or {})
                                              .get("attrs", {}).get("DW_AT_type")) is d):
                return True
        elif child["tag"] in ("DW_TAG_inheritance", "DW_TAG_member") and child["attrs"].get(
                "DW_AT_data_member_location") is not None:
            if by_hidden_pointer(dies, child["attrs"].get("DW_AT_type"), depth + 1):
                return True
    return False


def ghidra_type(dies, ref):
    """(type, size) spelled for DecompDrafts.java: references become pointers, enums int."""
    d = strip(dies, ref)
    if d is None:
        return "void", 0
    if d["tag"] == "DW_TAG_enumeration_type":
        return "int", d["attrs"].get("DW_AT_byte_size") or 4
    name = type_name(dies, ref)
    if name.endswith("&"):
        name = name[:-1] + "*"
    return name, type_size(dies, ref) or (8 if name.endswith("*") else 0)


# What generated headers write for a return value they could not type: never trusted unchecked.
PLACEHOLDER_RETURNS = {"long long int", "long long", "long int", "long", "void*", "long long int*"}


def prototypes(dies, db, promoted, matched):
    """Method prototypes the headers declare, keyed by the address of the original function
    with the same mangled name (so the parameter list is the symbol's). The return type is
    trusted where the function matches byte for byte, or the header was written for the class
    (not a promoted placeholder) and the type is not a generated placeholder; elsewhere
    Ghidra's guess stays. A function accepted by a self-test can still return the wrong width."""
    address_of = {}
    for a, f in db["functions"].items():
        for n in f["names"]:
            address_of.setdefault(n, a)
    out = {}
    for d in dies.values():
        link = d["attrs"].get("DW_AT_linkage_name")
        if d["tag"] != "DW_TAG_subprogram" or not link or link not in address_of:
            continue
        address = address_of[link]
        if address in out:
            continue
        params = [dies[c] for c in d["children"] if dies[c]["tag"] == "DW_TAG_formal_parameter"]
        method = bool(params) and bool(params[0]["attrs"].get("DW_AT_artificial"))
        ret_ref = d["attrs"].get("DW_AT_type")
        ret, ret_size = ghidra_type(dies, ret_ref)
        cls = db["functions"][address].get("scope") or ""
        out[address] = {
            "name": db["functions"][address]["demangled"],
            "static": not method and bool(cls) and cls in db["classes"],
            "ret": ret, "ret_size": ret_size,
            "sret": ret_ref is not None and by_hidden_pointer(dies, ret_ref),
            "trusted": address in matched or (cls not in promoted and ret not in PLACEHOLDER_RETURNS),
            "params": [dict(zip(("type", "size"), ghidra_type(dies, p["attrs"].get("DW_AT_type"))))
                       for p in params[1 if method else 0:]],
        }
    return out


def promoted_classes():
    """Classes whose header is a promoted placeholder (tools/decomp/promote.py)."""
    out = set()
    for h in (ROOT / "decomp" / "include").glob("*.h"):
        text = h.read_text(errors="replace")
        if "Partial: generated from symbols, RTTI and recovered layouts" in text:
            out.update(re.findall(r"^(?:class|struct)\s+(\w+)\s*(?::[^{;]*)?\{", text, re.M))
    return out


def is_class(db, name):
    """Real class (RTTI, vtable or constructor), not a namespace of free functions."""
    c = db["classes"].get(name)
    if not c:
        return False
    if c.get("typeinfo") or c.get("vtable"):
        return True
    return any(db["functions"][a]["kind"] in ("ctor", "dtor") for a in c.get("methods", []))


def sane_type(ctype, width, db, known):
    """Draft field types Ghidra can place: primitives, pointers, or an integer of the observed width."""
    by_width = {1: "char", 2: "short", 4: "int", 8: "long long"}
    if ctype in PRIMITIVE and not (ctype.startswith("std::") and width != 8):
        return ctype
    if ctype.endswith("*"):
        inner = ctype[:-1].strip()
        return ctype if inner in PRIMITIVE or is_class(db, inner) or inner in known else "void*"
    return by_width.get(width, "char")


def draft_classes(db, known):
    import layout
    lay = layout.Layout(db, layout.load_insns(db))
    out = {}
    for name, c in db["classes"].items():
        if name in known or "::" in name or "<" in name or not c.get("methods") or not is_class(db, name):
            continue
        try:
            start, size, rows = lay.rows(name)
        except Exception:
            continue
        fields = []
        for off, fd, ctype, note, fname in rows:
            width = 0x18 if ctype.startswith("TArrayList") else (fd.width or 8)
            fields.append({"offset": off, "name": fname, "type": sane_type(ctype, width, db, known), "size": width})
        out[name] = {"size": size or (max([f["offset"] + f["size"] for f in fields], default=start)),
                     "bases": [{"name": b["class"], "offset": b["offset"]} for b in c.get("bases", [])],
                     "fields": fields, "source": "layout"}
    return out


def vtables(db):
    """Primary vtable slot names per class, for readable virtual calls."""
    out = {}
    for name, vt in db["vtables"].items():
        if not vt["groups"]:
            continue
        slots, seen = [], {}
        for i, slot in enumerate(vt["groups"][0]["slots"]):
            f = db["functions"].get(slot) if isinstance(slot, str) else None
            short = f["demangled"].split("(")[0].split("::")[-1] if f else f"slot{i}"
            short = re.sub(r"\W", "_", short.replace("~", "dtor_"))
            seen[short] = seen.get(short, 0) + 1
            slots.append(short if seen[short] == 1 else f"{short}_{seen[short]}")
        out[name] = slots
    return out


def main():
    db = elfdb.load_db()
    dies = header_dies()
    classes = header_classes(dies)
    drafts = draft_classes(db, classes)
    merged = {**drafts, **classes}
    progress = ROOT / "build-decomp" / "progress.json"
    matched = {r["address"] for u in json.loads(progress.read_text())["units"] for r in u["functions"]
               if r["status"] == "MATCH"} if progress.exists() else set()
    protos = prototypes(dies, db, promoted_classes(), matched)
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps({"schema": 1, "classes": merged, "vtables": vtables(db), "prototypes": protos},
                              indent=1))
    print(f"{OUT.relative_to(ROOT)}: {len(classes)} classes from headers, {len(drafts)} from layout drafts, "
          f"{len(protos)} method prototypes ({sum(1 for p in protos.values() if p['sret'])} by hidden pointer, "
          f"{sum(1 for p in protos.values() if p['static'])} static, "
          f"{sum(1 for p in protos.values() if p['trusted'])} with a trusted return type)")


if __name__ == "__main__":
    main()
