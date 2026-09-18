#!/usr/bin/env python3
"""Large pass over templated menu methods.

Picks *Menu::createMenus/setOpen/update(+ctors) from original-symbols.txt,
dumps each body with objdump, runs extract_menu_wiring on it, and aggregates
one JSON report: per-function counts (creates, searches+keys, subscriptions,
counter loops, internal calls) plus the shared literal pool.

Working slices land in research/disassembly/batch/ (working material, NOT
for blind commit). The aggregate report is the reviewable artifact.

Usage:
  python3 tools/batch_menu_pass.py [--methods createMenus,setOpen,update]
      [--out research/batch-menu-pass.json] [--max-bytes 70000]
"""
import argparse
import json
import os
import re
import subprocess
import sys

ELF = "/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64"
HERE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def parse_symbols(path):
    out = []
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = re.match(r"([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(\S)\s+(.+)",
                         line.strip())
            if not m:
                continue
            addr, size, typ, sym = m.groups()
            out.append((int(addr, 16), int(size, 16), typ, sym.strip()))
    return out


def pick(symbols, methods):
    picks = []
    for addr, size, typ, sym in symbols:
        if typ not in ("T", "W"):
            continue
        m = re.match(r"(C\w*Menu)::(\w+)\(", sym)
        if not m:
            continue
        cls, meth = m.groups()
        if meth in methods and size > 0:
            picks.append((addr, size, cls, meth, sym))
    return picks


def slug(sym):
    s = re.sub(r"[^0-9A-Za-z]+", "-", sym).strip("-")
    return s[:80]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--methods", default="createMenus,setOpen,update")
    ap.add_argument("--symbols", default=os.path.join(
        HERE, "research", "original-symbols.txt"))
    ap.add_argument("--batch-dir", default=os.path.join(
        HERE, "research", "disassembly", "batch"))
    ap.add_argument("--out", default=os.path.join(
        HERE, "research", "batch-menu-pass.json"))
    ap.add_argument("--max-bytes", type=int, default=70000)
    ap.add_argument("--refresh", action="store_true",
                    help="re-dump even if the slice exists")
    args = ap.parse_args()

    methods = set(args.methods.split(","))
    symbols = parse_symbols(args.symbols)
    picks = pick(symbols, methods)
    print("%d candidate menu methods" % len(picks))
    os.makedirs(args.batch_dir, exist_ok=True)

    report = {"methods": [], "functions": []}
    if os.path.exists(args.out):
        with open(args.out, encoding="utf-8") as fh:
            try:
                report = json.load(fh)
            except ValueError:
                pass
    report["methods"] = sorted(set(report.get("methods", [])) | methods)
    by_addr = {f["address"]: f for f in report.get("functions", [])}
    for addr, size, cls, meth, sym in sorted(picks):
        if size > args.max_bytes:
            print("skip %s (%s too big)" % (sym, hex(size)))
            continue
        name = "%x-%s.asm" % (addr, slug(sym))
        path = os.path.join(args.batch_dir, name)
        if args.refresh or not os.path.exists(path):
            cmd = ["objdump", "-d",
                   "--start-address=%d" % addr,
                   "--stop-address=%d" % (addr + size), ELF]
            with open(path, "w", encoding="utf-8") as fh:
                subprocess.run(cmd, stdout=fh, check=True)
        js = path + ".wiring.json"
        if args.refresh or not os.path.exists(js):
            cmd = [sys.executable,
                   os.path.join(HERE, "tools", "extract_menu_wiring.py"),
                   "--asm", path, "--symbols", args.symbols,
                   "--elf", ELF, "--json-out", js]
            r = subprocess.run(cmd, capture_output=True, text=True)
            if r.returncode != 0:
                print("EXTRACT FAIL", sym, r.stderr[-500:])
                continue
        with open(js, encoding="utf-8") as fh:
            w = json.load(fh)
        searches = w.get("child_searches", [])
        by_addr[hex(addr)] = {
            "address": hex(addr), "size": size, "class": cls,
            "method": meth, "symbol": sym,
            "creates": len(w.get("createWindow_sites", [])),
            "searches": len(searches),
            "static_keys": sorted(s["key"] for s in searches if s["key"]),
            "dynamic_searches": sum(1 for s in searches if not s["key"]),
            "subscriptions": [(s["handler"], s["symbol"])
                              for s in w.get("subscriptions", [])],
            "counter_loops": [(c["slot"], c.get("bound"))
                              for c in w.get("counter_loops", [])],
            "register_loops": [(c["reg"], c.get("bound"))
                               for c in w.get("register_loops", [])],
            "back_pointers": sorted(set(b["base"]
                                        for b in w.get("back_pointers", []))),
            "index_offsets": sorted(set(o["add"]
                                        for o in w.get("index_offsets", []))),
            "internal_calls": len(w.get("internal_calls", [])),
            "literals": len(w.get("literal_pool", {})),
        }
        print("%s %s creates=%d searches=%d subs=%d loops=%s" % (
            hex(addr), sym, len(w.get("createWindow_sites", [])),
            len(searches), len(w.get("subscriptions", [])),
            [(c["slot"], c.get("bound"))
             for c in w.get("counter_loops", [])]))

    report["functions"] = sorted(by_addr.values(),
                                 key=lambda f: int(f["address"], 16))

    with open(args.out, "w", encoding="utf-8") as fh:
        json.dump(report, fh, ensure_ascii=False, indent=1)
        fh.write("\n")
    print("wrote %s (%d functions)" % (args.out, len(report["functions"])))


if __name__ == "__main__":
    main()
