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
            elif name == "DW_AT_name":
                current["attrs"][name] = value.split(": ")[-1].strip()
            elif name == "DW_AT_declaration":
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


def header_classes():
    with tempfile.TemporaryDirectory(prefix="otl-types-") as tmp:
        dies = parse_dies(compile_headers(tmp))
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
    classes = header_classes()
    drafts = draft_classes(db, classes)
    merged = {**drafts, **classes}
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps({"schema": 1, "classes": merged, "vtables": vtables(db)}, indent=1))
    print(f"{OUT.relative_to(ROOT)}: {len(classes)} classes from headers, {len(drafts)} from layout drafts")


if __name__ == "__main__":
    main()
