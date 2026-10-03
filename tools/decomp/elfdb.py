#!/usr/bin/env python3
"""Build the decompilation database from the original Torchlight ELF.

Everything here is mechanical (`original-code`): symbols, STT_FILE groups,
vtables, RTTI, operator-new sizes and caller-side return-register use.
Heuristic fields are named *_hint / confidence and are never promoted to facts.

Output (ignored build dir): elfdb.json, SUMMARY.md.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import json
import os
from pathlib import Path
import re
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfimage  # noqa: E402
from elfimage import STB_GLOBAL, STB_LOCAL, STB_WEAK, STT_FUNC, STT_OBJECT  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_OUT = ROOT / "build-decomp" / "db"
SCHEMA = 1


def default_elf():
    env = os.environ.get("TORCHLIGHT_ELF")
    if env:
        return Path(env)
    game = os.environ.get("TORCHLIGHT_GAME_DIR", str(Path.home() / "Games/Torchlight/game"))
    return Path(game) / "Torchlight.bin.x86_64"


# --------------------------------------------------------------------------
# Demangled-name structure


def split_top(text, sep="::"):
    """Split on `sep` outside <> and () nesting."""
    parts, depth, start, i = [], 0, 0, 0
    while i < len(text):
        if text.startswith("operator", i) and (i == 0 or not (text[i - 1].isalnum() or text[i - 1] == "_")):
            j = i + len("operator")
            m = re.match(r"\s*(\(\)|\[\]|<<=|>>=|<<|>>|->\*|->|<=|>=|[<>=!+\-*/%^&|~,]=?|&&|\|\||\+\+|--|new\[\]|delete\[\]|new|delete)", text[j:])
            if m:
                i = j + m.end()
                continue
        c = text[i]
        if c in "<(":
            depth += 1
        elif c in ">)":
            depth -= 1
        elif depth == 0 and text.startswith(sep, i):
            parts.append(text[start:i])
            i += len(sep)
            start = i
            continue
        i += 1
    parts.append(text[start:])
    return parts


def parse_demangled(text):
    """Return (qualified_name, params, cv) for a demangled function name."""
    clone = ""
    m = re.search(r" \[clone [^\]]+\]$", text)
    if m:
        clone, text = m.group(0), text[:m.start()]
    depth, i, open_paren = 0, 0, -1
    while i < len(text):
        if text.startswith("operator", i) and (i == 0 or not (text[i - 1].isalnum() or text[i - 1] == "_")):
            j = i + len("operator")
            m = re.match(r"\s*(\(\)|\[\]|<<=|>>=|<<|>>|->\*|->|<=|>=|[<>=!+\-*/%^&|~,]=?|&&|\|\||\+\+|--)", text[j:])
            if m:
                i = j + m.end()
                continue
        c = text[i]
        if c == "<":
            depth += 1
        elif c == ">":
            depth -= 1
        elif c == "(" and depth == 0:
            open_paren = i
            break
        i += 1
    if open_paren < 0:
        return text, None, "", clone
    head, rest = text[:open_paren], text[open_paren:]
    # Template functions carry a return type: "ret ns::f<...>"; keep the name.
    depth, cut = 0, -1
    for k, c in enumerate(head):
        if c == "<":
            depth += 1
        elif c == ">":
            depth -= 1
        elif c == " " and depth == 0 and not head[:k].endswith("operator"):
            cut = k
    qualified = head[cut + 1:] if cut >= 0 else head
    depth, close = 0, -1
    for k, c in enumerate(rest):
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                close = k
                break
    params = rest[1:close]
    cv = rest[close + 1:].strip()
    return qualified, params, cv, clone


def strip_template(name):
    depth, out = 0, []
    for c in name:
        if c == "<":
            depth += 1
        elif c == ">":
            depth -= 1
        elif depth == 0:
            out.append(c)
    return "".join(out)


def name_key(text):
    base = re.sub(r"\.(cpp|cc|c|cxx)$", "", text.rsplit("/", 1)[-1], flags=re.I)
    return re.sub(r"[^a-z0-9]", "", base.lower())


def class_key(name):
    name = strip_template(name.split("::")[-1])
    if re.match(r"C[A-Z]", name):
        name = name[1:]
    return re.sub(r"[^a-z0-9]", "", name.lower())


# FLTK's C helpers linked inside the FLTK block (fl_*.cxx are caught by extension).
FLTK_C_FILES = {"flstring.c", "is_spacing.c", "case.c", "utf8utils.c", "keysym2ucs.c", "vsnprintf.c",
                "numericsort.c", "scandir.c", "fl_call_main.c", "screen_xywh.c", "xutf8.c"}

SPECIAL = re.compile(r"^(_GLOBAL__[ID]_|__static_initialization_and_destruction_|__tcf_\d+|_init$|_fini$|_start$|"
                     r"__do_global|frame_dummy|call_gmon_start|__libc_csu)")


def classify_tu(name, scopes):
    low = name.lower()
    if low.startswith("crt") or low in {"init.c", "elf-init.c", "start.s"}:
        return "runtime"
    if low.startswith("particleuniverse") or scopes.get("ParticleUniverse", 0) > max(1, sum(scopes.values()) // 2):
        return "particle_universe"
    if "lodepng" in low:
        return "lodepng"
    if low.startswith("convertutf"):
        return "convert_utf"
    if low.endswith(".cxx") or low in FLTK_C_FILES:
        return "fltk"
    return "game"


# --------------------------------------------------------------------------
# Disassembly scan: operator-new sizes and caller-side return use

INSN = re.compile(r"^\s*([0-9a-f]+):\s+(\S+)\s*(.*)$")
FUNC_HEADER = re.compile(r"^([0-9a-f]+) <(.+)>:$")
RAX = {"%rax": 8, "%eax": 4, "%ax": 2, "%al": 1}
WRITE_ONLY = re.compile(r"^(mov|lea|pop|set|cvt|movz|movs|cmov)")


def split_operands(text):
    text = text.split("#", 1)[0].strip()
    out, depth, start = [], 0, 0
    for i, c in enumerate(text):
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        elif c == "," and depth == 0:
            out.append(text[start:i].strip())
            start = i + 1
    if text[start:].strip():
        out.append(text[start:].strip())
    return out


def return_use(insns):
    """First touch of rax-family/xmm0 after a call: ('read', kind) | ('write', None) | None."""
    for mnemonic, operands in insns:
        if mnemonic.startswith(("call", "jmp", "ret", "j")):
            return None
        ops = split_operands(operands)
        regs_in = []
        for idx, op in enumerate(ops):
            for reg, width in RAX.items():
                if re.search(re.escape(reg) + r"\b", op):
                    regs_in.append((idx, reg, width))
            if re.search(r"%xmm0\b", op):
                regs_in.append((idx, "%xmm0", 0))
        if not regs_in:
            continue
        last = len(ops) - 1
        zeroing = mnemonic.startswith(("xor", "pxor", "sub")) and len(ops) == 2 and ops[0] == ops[1]
        for idx, reg, width in regs_in:
            reading = idx < last or not (WRITE_ONLY.match(mnemonic) or zeroing) or "(" in ops[idx]
            if reading:
                if reg == "%xmm0":
                    if mnemonic.endswith("sd") or "sd2" in mnemonic:
                        return ("read", "double")
                    if mnemonic.endswith("ss") or "ss2" in mnemonic:
                        return ("read", "float")
                    return ("read", "xmm")
                return ("read", {1: "int8", 2: "int16", 4: "int32", 8: "int64"}[width])
        return ("write", None)
    return None


def scan_text(image, func_by_addr, ctor_class, vtable_class, new_targets):
    text = image.section(".text")
    proc = subprocess.Popen(["objdump", "-d", "--no-show-raw-insn", "-w",
                             f"--start-address={text.addr:#x}", f"--stop-address={text.addr + text.size:#x}",
                             str(image.path)], stdout=subprocess.PIPE, text=True, bufsize=1 << 20)
    sizes = defaultdict(lambda: defaultdict(list))
    ret_use = defaultdict(Counter)
    call_counts = Counter()
    current = []

    def flush(block):
        for i, (address, mnemonic, operands) in enumerate(block):
            if not mnemonic.startswith("call"):
                continue
            m = re.match(r"([0-9a-f]+) <", operands)
            if not m:
                continue
            target = int(m.group(1), 16)
            if target in func_by_addr:
                call_counts[target] += 1
                use = return_use([(b[1], b[2]) for b in block[i + 1:i + 9]])
                if use and use[0] == "read":
                    ret_use[target][use[1]] += 1
                elif use and use[0] == "write":
                    ret_use[target]["unused"] += 1
            if target in new_targets:
                imm = None
                for back in block[max(0, i - 5):i][::-1]:
                    if back[1].startswith("call"):
                        break
                    mm = re.match(r"\$0x([0-9a-f]+),%(e|r)di$", back[2].strip())
                    if back[1].startswith("mov") and mm:
                        imm = int(mm.group(1), 16)
                        break
                if imm is None:
                    continue
                for j in range(i + 1, min(len(block), i + 7)):
                    nxt = block[j]
                    if not nxt[1].startswith("call"):
                        continue
                    mt = re.match(r"([0-9a-f]+) <", nxt[2])
                    cls = ctor_class.get(int(mt.group(1), 16)) if mt else None
                    if cls:
                        # An inlined derived constructor stores its own vptr after the base ctor call.
                        for k in range(j + 1, min(len(block), j + 16)):
                            mv = re.match(r"\$0x([0-9a-f]+),", block[k][2].strip())
                            if block[k][1].startswith("mov") and mv:
                                owner = vtable_class.get(int(mv.group(1), 16))
                                if owner and owner != cls:
                                    cls = owner
                                    break
                            # Further base-class constructors (multiple inheritance) may precede the vptr store.
                            if block[k][1].startswith("call") and not re.search(r"C[12]E", block[k][2]):
                                break
                        sizes[cls][imm].append(address)
                    break

    for line in proc.stdout:
        line = line.rstrip("\n")
        if FUNC_HEADER.match(line):
            flush(current)
            current = []
            continue
        m = INSN.match(line)
        if m:
            current.append((int(m.group(1), 16), m.group(2), m.group(3)))
    flush(current)
    if proc.wait():
        raise RuntimeError("objdump failed")
    return sizes, ret_use, call_counts


# --------------------------------------------------------------------------


def build(elf_path):
    image = elfimage.load(elf_path)
    text = image.section(".text")
    in_text = lambda a: text.addr <= a < text.addr + text.size  # noqa: E731

    funcs = {}
    for sym in image.symbols:
        if sym.type != STT_FUNC or not sym.defined or not in_text(sym.value):
            continue
        entry = funcs.setdefault(sym.value, {"address": sym.value, "size": sym.size, "names": [],
                                             "bind": [], "file": None})
        entry["size"] = max(entry["size"], sym.size)
        if sym.name not in entry["names"]:
            entry["names"].append(sym.name)
            entry["bind"].append({STB_LOCAL: "local", STB_GLOBAL: "global", STB_WEAK: "weak"}.get(sym.bind, "?"))
        if sym.bind == STB_LOCAL and sym.file:
            entry["file"] = sym.file
            entry["file_index"] = sym.index

    data_syms = [s for s in image.symbols if s.type == STT_OBJECT and s.defined and s.shndx < 0xFF00]
    all_names = [n for f in funcs.values() for n in f["names"]] + [s.name for s in data_syms]
    readable = elfimage.demangle(all_names)

    # STT_FILE groups in symtab order = link order.
    files = []
    file_of_symbol_index = {}
    for sym in image.symbols:
        if sym.type == elfimage.STT_FILE:
            files.append({"id": len(files), "name": sym.name, "anchors": []})
        elif sym.bind == STB_LOCAL and files:
            file_of_symbol_index[sym.index] = len(files) - 1
    for f in funcs.values():
        if "file_index" in f:
            files[file_of_symbol_index[f["file_index"]]]["anchors"].append(f["address"])
            f["tu"] = file_of_symbol_index[f["file_index"]]
            f["tu_confidence"] = "local-symbol"
            del f["file_index"]

    # Function structure.
    for f in funcs.values():
        primary = sorted(zip(f["bind"], f["names"]),
                         key=lambda bn: ({"global": 0, "weak": 1, "local": 2}.get(bn[0], 3), bn[1]))[0][1]
        f["mangled"] = primary
        f["demangled"] = readable.get(primary, primary)
        qualified, params, cv, clone = parse_demangled(f["demangled"])
        scopes = split_top(qualified)
        f["qualified"] = qualified
        f["params"] = params
        f["cv"] = cv
        f["clone"] = bool(clone)
        f["scope"] = "::".join(scopes[:-1])
        f["method"] = scopes[-1]
        cls_last = strip_template(scopes[-2]) if len(scopes) > 1 else ""
        bare = strip_template(scopes[-1])
        if any(SPECIAL.match(n) for n in f["names"]) or "__static_initialization_and_destruction_" in f["demangled"]:
            kind = "compiler"
        elif "weak" in f["bind"] and "global" not in f["bind"]:
            kind = "inline_or_template"
        elif cls_last and bare == cls_last:
            kind = "ctor"
        elif bare.startswith("~"):
            kind = "dtor"
        elif f["bind"] == ["local"] or all(b == "local" for b in f["bind"]):
            kind = "static"
        else:
            kind = "function"
        f["kind"] = kind

    # Vtables and RTTI.
    func_addrs = set(funcs)
    sym_at = defaultdict(list)
    for s in image.symbols:
        if s.defined and s.name:
            sym_at[s.value].append(s)
    dyn_at = {s.value: s.name for s in image.dynsyms if s.defined and s.value}
    # COPY-relocated library objects (e.g. __cxxabiv1 vtables) are referenced at an offset.
    dyn_objects = sorted((s.value, s.size, s.name) for s in image.dynsyms
                         if s.defined and s.value and s.size and s.type == STT_OBJECT)

    def dyn_object(value):
        for start, size, name in dyn_objects:
            if start <= value < start + size:
                return name, value - start
        return None

    def pointer_name(slot_address):
        reloc = image.relocs.get(slot_address)
        if reloc:
            return ("import", reloc.symbol, reloc.addend)
        value = image.u64(slot_address)
        if value in func_addrs:
            return ("func", value, 0)
        if value in image.plt:
            return ("import", image.plt[value], 0)
        if value in dyn_at:
            return ("import", dyn_at[value], 0)
        inside = dyn_object(value) if value > text.addr + text.size else None
        if inside:
            return ("import", inside[0], inside[1])
        return ("value", value, 0)

    def file_backed(sym):
        # COPY-relocated library RTTI/vtables live in .bss and are not part of this image.
        return sym.shndx < len(image.sections) and image.sections[sym.shndx].type != 8

    typeinfo = {}
    for s in image.symbols:
        if not (s.name.startswith("_ZTI") and s.type == STT_OBJECT and s.defined and file_backed(s)):
            continue
        kind = pointer_name(s.value)
        cls = readable.get(s.name, s.name).removeprefix("typeinfo for ")
        ti = {"address": s.value, "class": cls, "bases": []}
        abi = kind[1] if kind[0] == "import" else str(kind)
        ti["abi"] = abi
        if "__si_class_type_info" in abi:
            base = pointer_name(s.value + 16)
            ti["bases"].append({"typeinfo": base[1] if base[0] == "import" else base[1], "offset": 0,
                                "virtual": False, "public": True})
        elif "__vmi_class_type_info" in abi:
            ti["flags"] = image.u32(s.value + 16)
            count = image.u32(s.value + 20)
            for i in range(count):
                base = pointer_name(s.value + 24 + 16 * i)
                offset_flags = image.i64(s.value + 32 + 16 * i)
                ti["bases"].append({"typeinfo": base[1], "offset": offset_flags >> 8,
                                    "virtual": bool(offset_flags & 1), "public": bool(offset_flags & 2)})
        typeinfo[s.value] = ti
    ti_name_by_addr = {a: t["class"] for a, t in typeinfo.items()}
    for ti in typeinfo.values():
        for base in ti["bases"]:
            ref = base.pop("typeinfo")
            if isinstance(ref, int):
                base["class"] = ti_name_by_addr.get(ref, f"?{ref:#x}")
            else:
                base["class"] = elfimage.demangle([ref]).get(ref, ref).removeprefix("typeinfo for ")
                base["external"] = True

    vtables = {}
    vtable_class = {}
    for s in image.symbols:
        if not (s.name.startswith("_ZTV") and s.type == STT_OBJECT and s.defined and s.size and file_backed(s)):
            continue
        cls = readable.get(s.name, s.name).removeprefix("vtable for ")
        words = [pointer_name(s.value + 8 * i) for i in range(s.size // 8)]
        ti_ptr = words[1]
        groups, current = [], None
        signed = lambda v: v - (1 << 64) if v >= 1 << 63 else v  # noqa: E731
        i = 0
        while i < len(words):
            w = words[i]
            if (i + 1 < len(words) and words[i + 1] == ti_ptr and w[0] == "value"
                    and -(1 << 20) < signed(w[1]) <= 0):
                current = {"offset_to_top": signed(w[1]), "slots": []}
                groups.append(current)
                i += 2
                continue
            i += 1
            if current is None:
                continue
            if w[0] == "func":
                current["slots"].append(f"{w[1]:#x}")
            elif w[0] == "import":
                current["slots"].append(w[1])
            elif w[1] == 0:
                current["slots"].append(None)
            else:
                current["slots"].append({"value": w[1]})
                current["suspect_vbase_offsets"] = True
        vtables[cls] = {"address": s.value, "size": s.size, "groups": groups}
        vtable_class[s.value + 16] = cls
        for g_index, g in enumerate(groups):
            for slot_index, slot in enumerate(g["slots"]):
                if isinstance(slot, str) and slot.startswith("0x"):
                    f = funcs[int(slot, 16)]
                    f.setdefault("vslots", []).append({"class": cls, "group": g_index, "slot": slot_index})

    # operator new and constructors.
    # Plain operator new plus OGRE_NEW (AllocatedObject::operator new inlines NedAllocImpl::allocBytes).
    allocators = ("_Znwm", "_Znam", "_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_")
    new_targets = {a for a, n in image.plt.items() if n in allocators}
    for f in funcs.values():
        if f["mangled"] in ("_Znwm", "_Znam"):
            new_targets.add(f["address"])
    ctor_class = {}
    for f in funcs.values():
        if f["kind"] == "ctor":
            ctor_class[f["address"]] = f["scope"]
    sizes, ret_use, call_counts = scan_text(image, funcs, ctor_class, vtable_class, new_targets)
    for address, counter in ret_use.items():
        if funcs[address]["kind"] in ("ctor", "dtor"):
            continue
        used = {k: v for k, v in counter.items() if k != "unused"}
        hint = max(used, key=used.get) if used else ("void?" if counter.get("unused", 0) >= 2 else "unknown")
        funcs[address]["return_hint"] = {"kind": hint, "observations": dict(counter)}
    for address, count in call_counts.items():
        funcs[address]["direct_callers"] = count

    # TU partition.
    order = sorted(funcs)
    # crtbegin/crtend locals are listed first but crtend code is linked last.
    runtime_ids = {f["id"] for f in files if classify_tu(f["name"], {}) == "runtime"}
    file_ids_with_anchors = [f["id"] for f in files if f["anchors"] and f["id"] not in runtime_ids]
    inversions = 0
    for left, right in zip(file_ids_with_anchors, file_ids_with_anchors[1:]):
        if min(files[right]["anchors"]) < max(files[left]["anchors"]):
            inversions += 1

    def scope_class(f):
        return f["scope"].split("::")[0] if f["scope"] else ""

    # Class home from anchored and bracketed functions.
    def assign_runs(first_pass):
        anchored = [i for i, a in enumerate(order) if funcs[a].get("tu_confidence") == "local-symbol"
                    and funcs[a]["tu"] not in runtime_ids]
        home = {}
        if not first_pass:
            votes = defaultdict(Counter)
            for a in order:
                f = funcs[a]
                if f.get("tu_confidence") in ("local-symbol", "bracketed") and f["kind"] != "inline_or_template":
                    if scope_class(f):
                        votes[scope_class(f)][f["tu"]] += 1
            home = {c: v.most_common(1)[0][0] for c, v in votes.items()}

        def match(f, tu):
            weight = 0.25 if f["kind"] == "inline_or_template" else 1.0
            cls = scope_class(f)
            if not cls:
                return 0.0
            if home.get(cls) == tu:
                return weight
            if class_key(cls) and class_key(cls) == name_key(files[tu]["name"]):
                return weight
            return 0.0

        bounds = [-1] + anchored + [len(order)]
        for left, right in zip(bounds, bounds[1:]):
            run = list(range(left + 1, right))
            if not run:
                continue
            tu_left = funcs[order[left]]["tu"] if left >= 0 else None
            tu_right = funcs[order[right]]["tu"] if right < len(order) else None
            if tu_left is not None and tu_left == tu_right:
                for i in run:
                    funcs[order[i]]["tu"] = tu_left
                    funcs[order[i]]["tu_confidence"] = "bracketed"
                continue
            lo = tu_left if tu_left is not None else 0
            hi = tu_right if tu_right is not None else len(files) - 1
            candidates = [lo] + [t for t in range(lo + 1, hi) if not files[t]["anchors"]
                                 and t not in runtime_ids] + ([hi] if hi != lo else [])
            candidates = [t for t in candidates if t not in runtime_ids] or [lo]
            # Monotone DP: assign each function in the run to a non-decreasing candidate index.
            n, m = len(run), len(candidates)
            neg = float("-inf")
            score = [[neg] * m for _ in range(n + 1)]
            back = [[0] * m for _ in range(n + 1)]
            for j in range(m):
                score[0][j] = 0.0
            for i in range(1, n + 1):
                f = funcs[order[run[i - 1]]]
                best, best_j = neg, 0
                for j in range(m):
                    if score[i - 1][j] > best:
                        best, best_j = score[i - 1][j], j
                    # Prefer staying on the previous TU on ties: strict improvement required.
                    score[i][j] = best + match(f, candidates[j])
                    back[i][j] = best_j
            j = max(range(m), key=lambda k: (score[n][k], -k))
            for i in range(n, 0, -1):
                f = funcs[order[run[i - 1]]]
                f["tu"] = candidates[j]
                f["tu_confidence"] = "class-split" if match(f, candidates[j]) else "position-guess"
                j = back[i][j]

    for f in funcs.values():
        if f.get("tu_confidence") != "local-symbol":
            f.pop("tu", None)
            f.pop("tu_confidence", None)
    assign_runs(True)
    for f in funcs.values():
        if f.get("tu_confidence") not in ("local-symbol", "bracketed"):
            f.pop("tu", None)
            f.pop("tu_confidence", None)
    assign_runs(False)

    # TU summaries.
    tu_funcs = defaultdict(list)
    for a in order:
        tu_funcs[funcs[a]["tu"]].append(a)
    tus = []
    for f in files:
        members = tu_funcs.get(f["id"], [])
        scopes = Counter(funcs[a]["scope"].split("::")[0] for a in members if funcs[a]["scope"])
        conf = Counter(funcs[a]["tu_confidence"] for a in members)
        tus.append({
            "id": f["id"], "name": f["name"], "kind": classify_tu(f["name"], scopes),
            "start": members[0] if members else None,
            "end": (members[-1] + funcs[members[-1]]["size"]) if members else None,
            "functions": len(members), "bytes": sum(funcs[a]["size"] for a in members),
            "confidence": dict(conf), "top_scopes": dict(scopes.most_common(6)),
        })

    # Classes.
    classes = {}

    def cls_entry(name):
        return classes.setdefault(name, {"name": name, "methods": [], "size_observed": {}, "tus": Counter()})

    for a in order:
        f = funcs[a]
        if f["scope"] and f["kind"] != "compiler":
            c = cls_entry(f["scope"])
            c["methods"].append(f"{a:#x}")
            c["tus"][f["tu"]] += 1
    for ti in typeinfo.values():
        c = cls_entry(ti["class"])
        c["typeinfo"] = f"{ti['address']:#x}"
        c["bases"] = ti["bases"]
    for name, vt in vtables.items():
        c = cls_entry(name)
        c["vtable"] = f"{vt['address']:#x}"
    for name, observed in sizes.items():
        c = cls_entry(name)
        # Allocation size before a constructor call: a hint, verify against field accesses.
        c["size_observed"] = {str(k): [f"{a:#x}" for a in v[:4]] + ([f"+{len(v) - 4}"] if len(v) > 4 else [])
                              for k, v in sorted(observed.items())}
        if len(observed) == 1:
            c["size_hint"] = next(iter(observed))
    for c in classes.values():
        c["tus"] = {str(k): v for k, v in c["tus"].most_common()}

    globals_ = []
    for s in data_syms:
        section = image.sections[s.shndx].name if s.shndx < len(image.sections) else "?"
        globals_.append({"address": f"{s.value:#x}", "size": s.size, "name": s.name,
                         "demangled": readable.get(s.name, s.name), "section": section,
                         "bind": {STB_LOCAL: "local", STB_GLOBAL: "global", STB_WEAK: "weak"}.get(s.bind, "?"),
                         "file": s.file})

    imports = {"plt": {f"{a:#x}": n for a, n in sorted(image.plt.items())},
               "copy": {f"{r.offset:#x}": r.symbol for r in image.relocs.values()
                        if r.type == elfimage.R_X86_64_COPY}}

    out_funcs = {}
    for a in order:
        f = dict(funcs[a])
        f["address"] = f"{a:#x}"
        out_funcs[f"{a:#x}"] = f
    return {
        "schema": SCHEMA,
        "original_elf_sha256": image.sha256,
        "text": {"start": f"{text.addr:#x}", "end": f"{text.addr + text.size:#x}"},
        "meaning": "Mechanical index of the original ELF. *_hint and tu_confidence other than "
                   "local-symbol/bracketed are heuristics; verify against ASM before relying on them.",
        "link_order_inversions": inversions,
        "tus": tus,
        "functions": out_funcs,
        "classes": classes,
        "typeinfo": {f"{a:#x}": t for a, t in sorted(typeinfo.items())},
        "vtables": vtables,
        "globals": globals_,
        "imports": imports,
    }


def summary_markdown(db):
    tus = db["tus"]
    funcs = db["functions"].values()
    kinds = Counter(t["kind"] for t in tus if t["functions"])
    by_kind_funcs = Counter()
    by_kind_bytes = Counter()
    for t in tus:
        by_kind_funcs[t["kind"]] += t["functions"]
        by_kind_bytes[t["kind"]] += t["bytes"]
    conf = Counter(f["tu_confidence"] for f in funcs)
    fkinds = Counter(f["kind"] for f in funcs)
    lines = [
        "# Decomp database summary", "",
        f"ELF `{db['original_elf_sha256']}`; link-order inversions: {db['link_order_inversions']}.", "",
        "| TU kind | TUs | functions | bytes |", "|---|---:|---:|---:|",
    ]
    for k in sorted(by_kind_funcs, key=lambda k: -by_kind_bytes[k]):
        lines.append(f"| {k} | {kinds[k]} | {by_kind_funcs[k]} | {by_kind_bytes[k]} |")
    lines += ["", "| function kind | count |", "|---|---:|"]
    lines += [f"| {k} | {v} |" for k, v in fkinds.most_common()]
    lines += ["", "| TU confidence | functions |", "|---|---:|"]
    lines += [f"| {k} | {v} |" for k, v in conf.most_common()]
    sized = sum(1 for c in db["classes"].values() if "size_hint" in c)
    conflicting = sum(1 for c in db["classes"].values() if len(c["size_observed"]) > 1)
    lines += ["", f"Classes: {len(db['classes'])}; with RTTI {len(db['typeinfo'])}; vtables "
              f"{len(db['vtables'])}; single allocation-size hint {sized}; conflicting hints {conflicting}.", "",
              "## Game TUs by size", "", "| id | file | functions | bytes | confidence |", "|---:|---|---:|---:|---|"]
    for t in sorted((t for t in tus if t["kind"] == "game" and t["functions"]), key=lambda t: -t["bytes"]):
        c = ", ".join(f"{k} {v}" for k, v in t["confidence"].items())
        lines.append(f"| {t['id']} | {t['name']} | {t['functions']} | {t['bytes']} | {c} |")
    return "\n".join(lines) + "\n"


def load_db(path=None):
    path = Path(path) if path else DEFAULT_OUT / "elfdb.json"
    if not path.exists():
        raise SystemExit(f"{path} missing; run tools/decomp/elfdb.py first")
    return json.loads(path.read_text())


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--elf", type=Path, default=default_elf())
    parser.add_argument("--out", type=Path, default=DEFAULT_OUT)
    args = parser.parse_args()
    db = build(args.elf)
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out / "elfdb.json").write_text(json.dumps(db, indent=1, sort_keys=True))
    (args.out / "SUMMARY.md").write_text(summary_markdown(db))
    print(f"wrote {args.out / 'elfdb.json'} ({len(db['functions'])} functions, {len(db['tus'])} TUs)")


if __name__ == "__main__":
    main()
