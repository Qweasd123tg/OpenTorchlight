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
import os
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
    # GCC omits uninstantiated template pointees from DWARF. These exact
    # source-defined types are the RunicCore pointer chain, not inferred layouts.
    if "SafePointer.h" in headers and "TArrayList.h" in headers:
        with source.open("a") as stream:
            stream.write("typedef char force_safe_pointer[(sizeof(TSafePointer<void*>) > 0) ? 1 : -1];\n"
                         "typedef char force_safe_pointer_list[(sizeof(TArrayList<TSafePointer<void*>*>) > 0) ? 1 : -1];\n")
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
            current = {"tag": tag, "depth": depth, "children": [], "attrs": {},
                       "parent": stack[depth - 1]["offset"] if depth and len(stack) >= depth else None, "offset": offset}
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
            if name in ("DW_AT_type", "DW_AT_specification", "DW_AT_abstract_origin"):
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


def die_attrs(dies, ref, seen=None):
    seen = set() if seen is None else seen
    d = dies.get(ref)
    if not d or ref in seen:
        return {}
    seen.add(ref)
    inherited = d["attrs"].get("DW_AT_specification", d["attrs"].get("DW_AT_abstract_origin"))
    return {**die_attrs(dies, inherited, seen), **d["attrs"]}


def qualified_name(dies, ref, seen=None):
    """Identity follows namespace/class parents and out-of-line definition specifications."""
    seen = set() if seen is None else seen
    d = dies.get(ref)
    if not d or ref in seen:
        return "?"
    seen.add(ref)
    spec = d["attrs"].get("DW_AT_specification")
    if spec in dies:
        return qualified_name(dies, spec, seen)
    name = d["attrs"].get("DW_AT_name", "?")
    parent_ref = d.get("parent")
    parent = dies.get(parent_ref)
    if parent and parent["tag"] in ("DW_TAG_namespace", "DW_TAG_class_type", "DW_TAG_structure_type",
                                    "DW_TAG_union_type"):
        prefix = qualified_name(dies, parent_ref, seen)
        if prefix != "?":
            return prefix + "::" + name
    return name


def type_name(dies, ref, depth=0):
    if ref is None:
        return "void"
    if depth > 40 or ref not in dies:
        return "?"
    d = dies[ref]
    tag, attrs = d["tag"], die_attrs(dies, ref)
    inner = lambda: type_name(dies, attrs.get("DW_AT_type"), depth + 1)  # noqa: E731
    if tag == "DW_TAG_base_type":
        return attrs.get("DW_AT_name", "?")
    if tag in ("DW_TAG_class_type", "DW_TAG_structure_type", "DW_TAG_union_type", "DW_TAG_enumeration_type"):
        name = qualified_name(dies, ref)
        if name.startswith("std::basic_string<wchar_t,"):
            return "std::wstring"
        if name.startswith("std::basic_string<char,"):
            return "std::string"
        return name
    if tag == "DW_TAG_typedef":
        # Resolve the actual type, retaining alias identity separately in type_identities.
        return inner()
    if tag == "DW_TAG_pointer_type":
        return inner() + "*"
    if tag == "DW_TAG_reference_type":
        return inner() + "&"
    if tag in ("DW_TAG_const_type", "DW_TAG_volatile_type"):
        return ("const " if tag == "DW_TAG_const_type" else "volatile ") + inner()
    if tag == "DW_TAG_array_type":
        bounds = [dies[c]["attrs"].get("DW_AT_upper_bound") for c in d["children"]
                  if dies[c]["tag"] == "DW_TAG_subrange_type"]
        return inner() + "".join(f"[{b + 1}]" if b is not None else "[]" for b in bounds)
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
                bound = dies[c]["attrs"].get("DW_AT_upper_bound")
                if bound is None:
                    return 0
                n *= bound + 1
        return n * type_size(dies, d["attrs"].get("DW_AT_type"), depth + 1)
    return type_size(dies, d["attrs"].get("DW_AT_type"), depth + 1)


def header_dies():
    with tempfile.TemporaryDirectory(prefix="otl-types-") as tmp:
        return parse_dies(compile_headers(tmp))


def header_classes(dies, conflicts=None):
    classes = {}
    conflicts = {} if conflicts is None else conflicts
    for ref, d in dies.items():
        attrs = die_attrs(dies, ref)
        if d["tag"] not in ("DW_TAG_class_type", "DW_TAG_structure_type") or d["attrs"].get("DW_AT_declaration"):
            continue
        name = qualified_name(dies, ref)
        short = attrs.get("DW_AT_name", "")
        if not short or short.startswith("_") or name.startswith("std::"):
            continue
        entry = {"size": attrs.get("DW_AT_byte_size") or 0, "bases": [], "fields": [], "source": "header"}
        for c in d["children"]:
            child = dies[c]
            off = child["attrs"].get("DW_AT_data_member_location")
            if child["tag"] == "DW_TAG_inheritance":
                entry["bases"].append({"name": type_name(dies, child["attrs"].get("DW_AT_type")), "offset": off})
            elif child["tag"] == "DW_TAG_member" and off is not None:
                target = child["attrs"].get("DW_AT_type")
                entry["fields"].append({"offset": off, "name": child["attrs"].get("DW_AT_name", f"field_{off:x}"),
                                        "type": type_name(dies, target), "ghidra_type": ghidra_type(dies, target)[0],
                                        "size": type_size(dies, target)})
        if name in conflicts:
            if entry not in conflicts[name]:
                conflicts[name].append(entry)
        elif name in classes and classes[name] != entry:
            conflicts[name] = [classes.pop(name), entry]
        else:
            classes[name] = entry
    return classes


def type_identities(dies):
    """Lossless named DIE index; qualified identity and aliases survive the layout projection."""
    return {f"{ref:#x}": {"name": qualified_name(dies, ref), "tag": d["tag"],
                          "parent": d.get("parent"), "type": d["attrs"].get("DW_AT_type"),
                          "size": type_size(dies, ref)}
            for ref, d in dies.items() if "DW_AT_name" in d["attrs"] and d["tag"] in (
                "DW_TAG_base_type", "DW_TAG_class_type", "DW_TAG_structure_type", "DW_TAG_union_type",
                "DW_TAG_namespace", "DW_TAG_typedef", "DW_TAG_enumeration_type")}


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
    name = re.sub(r"^(?:const |volatile )+", "", type_name(dies, ref))
    if name.endswith("&"):
        name = name[:-1] + "*"
    return name, type_size(dies, ref) or (8 if name.endswith("*") else 0)


# What generated headers write for a return value they could not type: never trusted unchecked.
PLACEHOLDER_RETURNS = {"long long int", "long long", "long int", "long", "void*", "long long int*"}


def prototypes(dies, db, promoted, matched, conflicts=None):
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
    conflicts = {} if conflicts is None else conflicts
    for ref, d in dies.items():
        attrs = die_attrs(dies, ref)
        link = attrs.get("DW_AT_linkage_name")
        if d["tag"] != "DW_TAG_subprogram" or not link or link not in address_of:
            continue
        address = address_of[link]
        children = d["children"]
        if not any(dies[c]["tag"] == "DW_TAG_formal_parameter" for c in children):
            spec = dies.get(d["attrs"].get("DW_AT_specification", d["attrs"].get("DW_AT_abstract_origin")))
            if spec:
                children = spec["children"]
        params = [dies[c] for c in children if dies[c]["tag"] == "DW_TAG_formal_parameter"]
        method = bool(params) and bool(params[0]["attrs"].get("DW_AT_artificial"))
        ret_ref = attrs.get("DW_AT_type")
        ret, ret_size = ghidra_type(dies, ret_ref)
        cls = db["functions"][address].get("scope") or ""
        candidate = {
            "name": db["functions"][address]["demangled"],
            "static": not method and bool(cls) and cls in db["classes"],
            "member": method,
            "variadic": any(dies[c]["tag"] == "DW_TAG_unspecified_parameters" for c in children),
            "ret": ret, "ret_size": ret_size,
            "sret": ret_ref is not None and by_hidden_pointer(dies, ret_ref),
            "trusted": address in matched or (cls not in promoted and ret not in PLACEHOLDER_RETURNS),
            "params": [dict(zip(("type", "size"), ghidra_type(dies, p["attrs"].get("DW_AT_type"))))
                       for p in params[1 if method else 0:]],
        }
        if address in conflicts:
            if candidate not in conflicts[address]:
                conflicts[address].append(candidate)
        elif address in out and out[address] != candidate:
            conflicts[address] = [out.pop(address), candidate]
        else:
            out[address] = candidate
    return out


def sdk_prototypes(dies, db, conflicts=None):
    """Exact symbols declared in the already compiled pinned headers, never inferred by short name."""
    conflicts = {} if conflicts is None else conflicts
    imported = set()
    for entries in db.get("imports", {}).values():
        if isinstance(entries, dict):
            imported.update(v.split("@", 1)[0] for v in entries.values() if isinstance(v, str))
    allowed = ("Ogre::", "CEGUI::", "FMOD::", "ParticleUniverse::", "std::", "__gnu_cxx::")
    links = {}
    normalized = dict(dies)
    for ref, d in dies.items():
        if d["tag"] != "DW_TAG_subprogram":
            continue
        attrs = die_attrs(dies, ref)
        link = attrs.get("DW_AT_linkage_name")
        name = qualified_name(dies, ref)
        # C declarations often have no DW_AT_linkage_name; require the exact original import.
        if not link and attrs.get("DW_AT_name") in imported and "::" not in name:
            link = attrs["DW_AT_name"]
            normalized[ref] = {**d, "attrs": {**d["attrs"], "DW_AT_linkage_name": link}}
        if link and (name.startswith(allowed) or link in imported):
            links[link] = name
    # Reuse the same declaration and conflict projection rather than a second ABI parser.
    synthetic = {"functions": {link: {"names": [link], "demangled": name,
                                      "scope": name.rsplit("::", 1)[0] if "::" in name else ""}
                               for link, name in links.items()}, "classes": db["classes"]}
    out = prototypes(normalized, synthetic, set(), set(), conflicts)
    for link, p in out.items():
        p["trusted"] = True
        p["source"] = "pinned-header-dwarf"
        p["imported"] = link in imported
        scalar = lambda ty: ty.endswith("*") or ty in (
            "void", "bool", "char", "signed char", "unsigned char", "short", "short int",
            "short unsigned int", "unsigned short", "int", "unsigned int", "long", "long int",
            "long unsigned int", "unsigned long", "long long", "long long int",
            "long long unsigned int", "unsigned long long", "float", "double", "wchar_t")
        safe = not p["sret"] and not p["variadic"] and scalar(p["ret"]) and all(scalar(arg["type"]) for arg in p["params"])
        p["abi_status"] = "SCALAR_OR_POINTER" if safe else "AGGREGATE_UNVERIFIED"
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
    # An observed 24-byte span is not a one-byte char. Preserve its unknown
    # representation explicitly; no container/aggregate semantics are inferred.
    return by_width.get(width, f"undefined{width}" if width > 0 else "undefined1")


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
        if not vt["groups"] or vt["groups"][0]["offset_to_top"] != 0:
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


def vtable_groups(db, protos):
    """Preserve every RTTI group and slot target; secondary target ABI remains explicitly unknown."""
    out = {}
    for name, table in db["vtables"].items():
        groups = []
        for index, group in enumerate(table["groups"]):
            slots = []
            secondary = group["offset_to_top"] != 0
            for slot in group["slots"]:
                fn = db["functions"].get(slot) if isinstance(slot, str) else None
                item = {"target": slot, "name": fn["demangled"] if fn else None,
                        "prototype": protos.get(slot) if isinstance(slot, str) and not secondary else None,
                        "abi_status": "SECONDARY_UNVERIFIED" if secondary else
                                      "PRIMARY_PROTOTYPE" if isinstance(slot, str) and slot in protos else "UNKNOWN"}
                slots.append(item)
            groups.append({"index": index, "offset_to_top": group["offset_to_top"],
                           "object_vptr_offset": -group["offset_to_top"],
                           "suspect_vbase_offsets": group.get("suspect_vbase_offsets", False),
                           "slots": slots})
        out[name] = {"address": table.get("address"), "size": table.get("size"), "groups": groups}
    return out


def main():
    db = elfdb.load_db()
    dies = header_dies()
    conflicts = {}
    classes = header_classes(dies, conflicts)
    drafts = draft_classes(db, set(classes) | set(conflicts))
    merged = {**drafts, **classes}
    progress = ROOT / "build-decomp" / "progress.json"
    matched = {r["address"] for u in json.loads(progress.read_text())["units"] for r in u["functions"]
               if r["status"] == "MATCH"} if progress.exists() else set()
    proto_conflicts = {}
    protos = prototypes(dies, db, promoted_classes(), matched, proto_conflicts)
    sdk_conflicts = {}
    sdk = sdk_prototypes(dies, db, sdk_conflicts)
    OUT.parent.mkdir(parents=True, exist_ok=True)
    output = json.dumps({"schema": 2, "original_elf_sha256": db["original_elf_sha256"],
                              "classes": merged, "class_conflicts": conflicts,
                              "type_identities": type_identities(dies), "vtables": vtables(db),
                              "vtable_groups": vtable_groups(db, protos), "prototypes": protos,
                              "prototype_conflicts": proto_conflicts, "sdk_prototypes": sdk,
                              "sdk_prototype_conflicts": sdk_conflicts},
                              indent=1)
    fd, temporary = tempfile.mkstemp(prefix="types-", dir=OUT.parent)
    try:
        with os.fdopen(fd, "w") as stream:
            stream.write(output)
        os.replace(temporary, OUT)
    finally:
        Path(temporary).unlink(missing_ok=True)
    print(f"{OUT.relative_to(ROOT)}: {len(classes)} classes from headers, {len(drafts)} from layout drafts, "
          f"{len(protos)} method prototypes ({sum(1 for p in protos.values() if p['sret'])} by hidden pointer, "
          f"{sum(1 for p in protos.values() if p['static'])} static, "
          f"{sum(1 for p in protos.values() if p['trusted'])} with a trusted return type); "
          f"{len(sdk)} exact SDK declarations ({sum(p['imported'] for p in sdk.values())} original imports, "
          f"{len(sdk_conflicts)} conflicts)")


if __name__ == "__main__":
    main()
