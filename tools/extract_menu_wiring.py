#!/usr/bin/env python3
"""Extract CEGUI wiring facts from an objdump slice of a *Menu::createMenus.

Mechanical layer of code-first analysis (original-code: the ASM slice;
judgement about CEGUI semantics stays manual). Reports:
  - rodata literal pool referenced by immediates,
  - string copy-loop resolutions [start, end) -> bytes,
  - WindowManager::createWindow sites with menu-field stores,
  - recursiveChildSearch sites with resolved keys and stores,
  - MemberFunctionSlot subscription sites (handler addr -> symbol),
  - counter loops (addl/cmpl on the same stack slot),
  - direct internal calls (non-PLT).

Usage:
  python3 tools/extract_menu_wiring.py --asm research/disassembly/XXXX.asm \
      --symbols research/original-symbols.txt [--elf PATH] [--json-out FILE]
"""
import argparse
import json
import re
import struct
import sys


def load_segments(elf_path):
    f = open(elf_path, "rb")
    f.seek(0x20)
    (e_phoff,) = struct.unpack("<Q", f.read(8))
    f.seek(0x36)
    e_phentsize, e_phnum = struct.unpack("<HH", f.read(4))
    segs = []
    for i in range(e_phnum):
        f.seek(e_phoff + i * e_phentsize)
        (p_type, _flags, p_offset, p_vaddr, _paddr,
         p_filesz, _memsz, _align) = struct.unpack("<IIQQQQQQ", f.read(56))
        if p_type == 1:
            segs.append((p_vaddr, p_offset, p_filesz))
    return f, segs


def read_range(f, segs, va, n):
    for vaddr, off, filesz in segs:
        if vaddr <= va < vaddr + filesz:
            f.seek(off + (va - vaddr))
            return f.read(n)
    return None


def load_symbols(path):
    syms = {}
    if not path:
        return syms
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = re.match(r"([0-9a-fA-F]+)\s+[0-9a-fA-F]+\s+\S+\s+(.+)", line.strip())
            if m:
                syms[int(m.group(1), 16)] = m.group(2).strip()
    return syms


def parse_lines(asm_path):
    with open(asm_path, encoding="utf-8", errors="replace") as fh:
        raw = fh.read().split("\n")
    items = []
    for idx, line in enumerate(raw):
        m = re.match(r"\s*([0-9a-f]+):\t(.*)$", line)
        if m:
            items.append((idx, m.group(1), m.group(2)))
    return raw, items


def find_copy_loops(raw):
    """Find byte-copy loops: mov $START,%eax ... cmp $END,%rax."""
    loops = []
    for i, line in enumerate(raw):
        m = re.search(r"mov\s+\$0x([0-9a-f]+),%eax", line)
        if not m:
            continue
        start = int(m.group(1), 16)
        for j in range(i + 1, min(i + 25, len(raw))):
            m2 = re.search(r"cmp\s+\$0x([0-9a-f]+),%rax", raw[j])
            if m2:
                end = int(m2.group(1), 16)
                if 0 < end - start < 256:
                    addr = raw[i].split(":")[0].strip()
                    loops.append({"at": addr, "line": i + 1,
                                  "start": hex(start), "end": hex(end)})
                break
            if "ret" in raw[j]:
                break
    return loops


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--asm", required=True)
    ap.add_argument("--symbols", default="")
    ap.add_argument("--elf", default="/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64")
    ap.add_argument("--json-out", default="")
    args = ap.parse_args()

    raw, items = parse_lines(args.asm)
    syms = load_symbols(args.symbols)
    try:
        elf, segs = load_segments(args.elf)
    except OSError:
        elf, segs = None, []

    def resolve(va, n):
        if elf is None:
            return None
        return read_range(elf, segs, va, n)

    result = {"asm": args.asm}

    # 1. literal pool: immediates that read as printable C strings
    pool = {}
    for m in set(re.findall(r"\$0x([0-9a-f]{6,})", "\n".join(raw))):
        va = int(m, 16)
        if va < 0x400000:
            continue
        data = resolve(va, 120)
        if not data:
            continue
        end = data.find(b"\x00")
        s = data[:end] if end >= 0 else data
        if len(s) >= 2 and all(32 <= c < 127 for c in s):
            pool[hex(va)] = s.decode()
    result["literal_pool"] = pool

    # 2. copy loops with resolved bytes
    loops = find_copy_loops(raw)
    for lp in loops:
        s, e = int(lp["start"], 16), int(lp["end"], 16)
        data = resolve(s, e - s)
        lp["bytes"] = data.decode("utf-8", "replace") if data else None
    result["copy_loops"] = loops

    # 3. createWindow sites. this-register first (see section 4 note).
    from collections import Counter as _Counter
    _base_hits = _Counter()
    for _idx, _addr, _text in items:
        _m = re.search(r"mov\s+%rax,0x[0-9a-f]+\(%(r1[0-5]|r[89]|rbx|r[a-d][xsi]|rbp)\)",
                       _text)
        if _m:
            _base_hits[_m.group(1)] += 1
    _this_reg = _base_hits.most_common(1)[0][0] if _base_hits else "rbx"
    result["this_register"] = _this_reg
    creates = []
    for idx, addr, text in items:
        if "WindowManager12createWindow" not in text and "createWindow" not in text:
            continue
        store = "?"
        _pat = (r"mov\s+%rax,(0x[0-9a-f]+)\(%" +
                re.escape(_this_reg) + r"\)")
        for k in range(idx + 1, min(idx + 14, len(raw))):
            m = re.search(_pat, raw[k])
            if m:
                store = m.group(1) + "(%menu)"
                break
        creates.append({"addr": addr, "line": idx + 1, "menu_store": store})
    result["createWindow_sites"] = creates

    # 4b. CEGUI::String ctor literals: StringC1EPKh/c call sites with a
    # preceding mov $IMM,%esi give key strings directly.
    ctor_keys = {}  # line idx -> resolved string
    for idx, addr, text in items:
        if "CEGUI6StringC1EPK" not in text:
            continue
        for j in range(max(0, idx - 8), idx):
            m = re.search(r"mov\s+\$0x([0-9a-f]+),%esi", raw[j])
            if not m:
                continue
            va = int(m.group(1), 16)
            data = resolve(va, 64) if elf is not None else None
            if data:
                end = data.find(b"\x00")
                s = data[:end] if end >= 0 else data
                if len(s) >= 1 and all(32 <= c < 127 for c in s):
                    ctor_keys[idx] = s.decode()
                    break
    result["string_ctor_keys"] = [
        {"line": k + 1, "key": v} for k, v in sorted(ctor_keys.items())]

    # 4. recursiveChildSearch sites + nearest copy-loop key.
    # this-register already detected above (most common store base).
    this_reg = result["this_register"]
    searches = []
    for idx, addr, text in items:
        if "recursiveChildSearch" not in text:
            continue
        key = None
        for lp in loops:
            if 0 < idx + 1 - lp["line"] <= 60:
                if key is None or lp["line"] > key["line"]:
                    key = lp
        dynamic = None
        inline_key = None
        if key is None:
            window = raw[max(0, idx - 120):idx]
            prefix = None
            for l in reversed(window):
                m = re.search(r"mov\s+\$0x([0-9a-f]+),%esi", l)
                if m:
                    va = int(m.group(1), 16)
                    data = resolve(va, 40) if elf is not None else None
                    if data:
                        end = data.find(b"\x00")
                        s = data[:end] if end >= 0 else data
                        if len(s) >= 1 and all(32 <= c < 127 for c in s):
                            prefix = s.decode()
                    break
            if any("GetValueAsString" in l for l in window):
                dynamic = ((prefix + "+") if prefix else "prefix+") + \
                    "GetValueAsString(counter)"
            else:
                tab = None
                for l in window:
                    m = re.search(r"lea\s+(0x[0-9a-f]+)\(,%r\w+,8\)", l)
                    if m:
                        tab = m.group(1)
                if tab:
                    dynamic = "runtime table %s[counter]" % tab
            if dynamic is None:
                # inline utf32 chars: movl $0xUU,(%reg) sequences (e.g. "XP")
                chars = []
                for l in raw[max(0, idx - 30):idx]:
                    m = re.search(r"movl\s+\$0x([0-9a-f]+),", l)
                    if m:
                        v = int(m.group(1), 16)
                        if 0x20 <= v < 0x110000:
                            chars.append(chr(v))
                if 1 <= len(chars) <= 8:
                    inline_key = "".join(chars)
            if key is None and inline_key is None and dynamic is None:
                # CEGUI::String temp built from a literal just above
                best = None
                for ck, cv in ctor_keys.items():
                    if 0 <= idx - ck <= 15 and (best is None or ck > best[0]):
                        best = (ck, cv)
                if best:
                    inline_key = best[1]
        store = "?"
        store_pat = (r"mov\s+%rax,(0x[0-9a-f]+)\(%" +
                     re.escape(this_reg) + r"\)")
        for k in range(idx + 1, min(idx + 6, len(raw))):
            m = re.search(store_pat, raw[k])
            if m:
                store = m.group(1) + "(%menu)"
                break
        searches.append({"addr": addr, "line": idx + 1,
                         "key": key["bytes"] if key else inline_key,
                         "dynamic": dynamic,
                         "menu_store": store})
    result["child_searches"] = searches

    # 5. subscription functors: movq $HANDLER,0x8(%rax) + nearby new
    subs = []
    for idx, addr, text in items:
        m = re.search(r"movq\s+\$0x([0-9a-f]+),0x8\(%rax\)", text)
        if m:
            handler = int(m.group(1), 16)
            subs.append({"addr": addr, "line": idx + 1,
                         "handler": hex(handler),
                         "symbol": syms.get(handler, "unknown")})
    result["subscriptions"] = subs

    # 6. counter loops: addl $1,N(%rsp) ... cmpl $BOUND,N(%rsp)
    # (same slot may be reused by several loops: keep each inc site)
    counters = []
    for idx, addr, text in items:
        m = re.search(r"addl?\s+\$0x1,(0x[0-9a-f]+)\(%rsp\)", text)
        if not m:
            continue
        slot = m.group(1)
        bound = None
        for j in range(idx + 1, min(idx + 400, len(raw))):
            m2 = re.search(r"cmpl?\s+\$0x([0-9a-f]+),"
                           + re.escape(slot) + r"\(%rsp\)", raw[j])
            if m2:
                bound = int(m2.group(1), 16)
                break
        counters.append({"slot": slot, "inc_addr": addr,
                         "inc_line": idx + 1, "bound": bound})
    result["counter_loops"] = counters

    # 6c. stack compare-exit bounds without a visible addl (combine keeps the
    # counter via reload: cmpl $IMM,slot + jcc).
    for idx, addr, text in items:
        m = re.search(r"cmpl?\s+\$(0x[0-9a-f]+),(0x[0-9a-f]+)\(%rsp\)", text)
        if not m:
            continue
        bound = int(m.group(1), 16)
        if bound == 0 or bound > 0x1000:
            continue
        if any(c["slot"] == m.group(2) and c.get("bound") == bound
               for c in counters):
            continue
        nxt = raw[idx + 1] if idx + 1 < len(raw) else ""
        mj = re.search(r"\bj([a-z]+)\s+", nxt)
        counters.append({"slot": m.group(2), "inc_addr": None,
                         "inc_line": None, "bound": bound,
                         "exit_jump": mj.group(0).strip() if mj else None})
    result["counter_loops"] = counters

    # 6b. register counters: cmp $IMM,%reg + jcc (register-held loop bounds,
    # e.g. combine's r13 ItemSlot loop). Heuristic: small immediate.
    reg_loops = []
    for idx, addr, text in items:
        m = re.search(r"cmp\s+\$(0x[0-9a-f]+),%(e[a-z]{2}|r\d+d)\b", text)
        if not m:
            continue
        bound = int(m.group(1), 16)
        if bound == 0 or bound > 0x1000:
            continue
        nxt = raw[idx + 1] if idx + 1 < len(raw) else ""
        mj = re.search(r"\bj([a-z]+)\s+", nxt)
        reg_loops.append({"addr": addr, "line": idx + 1,
                          "reg": m.group(2), "bound": bound,
                          "jump_next": mj.group(0).strip() if mj else None})
    result["register_loops"] = reg_loops

    # 7. direct internal calls
    internal = []
    for idx, addr, text in items:
        m = re.search(r"call\s+[0-9a-f]+\s+<([^>@]+)>", text)
        if m:
            internal.append({"addr": addr, "target": m.group(1)})
    result["internal_calls"] = internal

    # 8. back-pointer wiring: lea IMM(%rbx,REG,4) (menu array slot refs)
    #    and index adjusts (add $IMM,%r13d/%r14d) near them.
    back_ptrs = []
    for idx, addr, text in items:
        m = re.search(r"lea\s+(0x[0-9a-f]+)\(%r(?:bx|12),%(r1[0-9]|r[89]|r[a-d][xsi]),4\)",
                      text)
        if m:
            back_ptrs.append({"addr": addr, "line": idx + 1,
                              "base": m.group(1), "index_reg": m.group(2)})
    result["back_pointers"] = back_ptrs
    index_offsets = []
    for idx, addr, text in items:
        m = re.search(r"add\s+\$(0x[0-9a-f]+),%(r1[0-9]d)", text)
        if m:
            index_offsets.append({"addr": addr, "line": idx + 1,
                                  "add": m.group(1), "reg": m.group(2)})
    result["index_offsets"] = index_offsets

    text_report = []
    text_report.append("literal pool: %d strings" % len(pool))
    text_report.append("copy loops: %d" % len(loops))
    text_report.append("createWindow sites: %d" % len(creates))
    for c in creates:
        text_report.append("  %s -> %s" % (c["addr"], c["menu_store"]))
    text_report.append("child searches: %d" % len(searches))
    for s in searches:
        text_report.append("  %s key=%r dyn=%s -> %s"
                           % (s["addr"], s["key"], s["dynamic"],
                              s["menu_store"]))
    text_report.append("subscriptions: %d" % len(subs))
    for s in subs:
        text_report.append("  %s %s %s"
                           % (s["addr"], s["handler"], s["symbol"]))
    text_report.append("counter loops: %d" % len(result["counter_loops"]))
    for c in result["counter_loops"]:
        text_report.append("  slot %s bound=%s" % (c["slot"], c.get("bound")))
    text_report.append("internal calls: %d" % len(internal))
    if back_ptrs:
        text_report.append("back pointers: %s"
                           % sorted(set(b["base"] for b in back_ptrs)))
    if index_offsets:
        text_report.append("index offsets: %s"
                           % sorted(set(o["add"] for o in index_offsets)))
    print("\n".join(text_report))

    if args.json_out:
        with open(args.json_out, "w", encoding="utf-8") as fh:
            json.dump(result, fh, ensure_ascii=False, indent=1)
            fh.write("\n")


if __name__ == "__main__":
    main()
