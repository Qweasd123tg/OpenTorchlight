#!/usr/bin/env python3
"""Recover string-table definitions from original static initializers.

Many headers define internal-linkage tables such as
`static const std::wstring g_AIFLAG_TYPE_NAMES[] = { L"AWARE", ... };` that every
including TU constructs in its static initializer. This reads the initializer
of a TU that owns the table, maps each `basic_string(const T*, alloc)` call to
its array slot and prints the C++ definition.

    python3 tools/decomp/name_tables.py g_AIFLAG_TYPE_NAMES g_AISTAT_TYPE_NAMES
    python3 tools/decomp/name_tables.py --tu AIFlag.cpp
"""
from __future__ import annotations

import argparse
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import elfimage  # noqa: E402
import objdiff  # noqa: E402

STRING_CTORS = {
    "_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_": ("std::wstring", "L"),
    "_ZNSsC1EPKcRKSaIcE": ("std::string", ""),
}


def c_literal(text):
    return text.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n").replace("\t", "\\t")


class Tables:
    def __init__(self, db=None, elf=None):
        self.db = db or elfdb.load_db()
        self.image = elfimage.load(elf or elfdb.default_elf())
        self.locals = [g for g in self.db["globals"] if g["bind"] == "local" and g["size"]]

    def symbols_of(self, tu_name):
        return [g for g in self.locals if g["file"] == tu_name]

    def initializers(self, tu_name):
        tu = next(t for t in self.db["tus"] if t["name"] == tu_name)
        return [f for f in self.db["functions"].values() if f["tu"] == tu["id"] and f["kind"] == "compiler"
                and ("_GLOBAL__I_" in f["mangled"] or "__static_initialization" in f["mangled"])]

    def disassembly(self, f):
        cache = self.__dict__.setdefault("_insns", {})
        if f["address"] not in cache:
            a = int(f["address"], 16)
            cache[f["address"]] = objdiff.parse_insns(objdiff.run_objdump(
                [f"--start-address={a:#x}", f"--stop-address={a + f['size']:#x}", str(self.image.path)]))
        return cache[f["address"]]

    def read_text(self, address):
        raw = self.image.read(address, 4096)
        text = objdiff.printable_string(raw)
        if text is None:
            return None
        return text[2:] if text.startswith('L"') else text

    def recover(self, name, tu_name=None):
        """Return (owner, (kind, [strings], missing)) for a local table; tries a few owning TUs."""
        owners = [g for g in self.locals if (g["demangled"] == name or g["name"] == name)
                  and (tu_name is None or g["file"] == tu_name)]
        if not owners:
            raise SystemExit(f"no local table named {name}")
        for owner in owners[:3]:
            result = self._recover_in(owner)
            if result:
                return owner, result
        raise SystemExit(f"{name}: no string-constructor initializer found")

    def _recover_in(self, owner):
        start, size = int(owner["address"], 16), owner["size"]
        slots = {}
        kind = None
        for f in self.initializers(owner["file"]):
            insns = self.disassembly(f)
            regs = {}
            for _, mnemonic, operands in insns:
                m = re.match(r"\$0x([0-9a-f]+),%(e|r)(si|di)$", operands)
                if mnemonic.startswith("mov") and m:
                    regs[m.group(3)] = int(m.group(1), 16)
                    continue
                if mnemonic.startswith(("call", "jmp")):
                    target = re.match(r"([0-9a-f]+) <", operands)
                    callee = self.image.plt.get(int(target.group(1), 16), "") if target else ""
                    callee = callee.split("@")[0]
                    if callee in STRING_CTORS and "di" in regs and "si" in regs:
                        dest = regs["di"]
                        if start <= dest < start + size:
                            kind = STRING_CTORS[callee]
                            slots[(dest - start) // 8] = self.read_text(regs["si"])
                    regs = {}
        if not slots:
            return None
        count = size // 8
        missing = [i for i in range(count) if i not in slots]
        return kind, [slots.get(i) for i in range(count)], missing

    def definition(self, name, tu_name=None):
        owner, (kind, values, missing) = self.recover(name, tu_name)
        cxx_type, prefix = kind
        lines = [f"static const {cxx_type} {owner['demangled']}[] =", "{"]
        for i, value in enumerate(values):
            lines.append(f'    {prefix}"{c_literal(value)}",' if value is not None else f"    /* slot {i} not recovered */")
        lines.append("};")
        if missing:
            lines.insert(0, f"// WARNING: slots {missing} not found in {owner['file']}")
        return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("names", nargs="*")
    parser.add_argument("--tu", help="every local table of this TU, in address order")
    args = parser.parse_args()
    tables = Tables()
    names = list(args.names)
    if args.tu:
        # Arrays only: single EMPTY_STRING-style objects are default-constructed.
        names += [g["demangled"] for g in sorted(tables.symbols_of(args.tu), key=lambda g: int(g["address"], 16))
                  if g["size"] >= 16 and g["size"] % 8 == 0]
    for name in names:
        try:
            print(tables.definition(name, args.tu) + "\n")
        except SystemExit as error:
            print(f"// {error}\n")


if __name__ == "__main__":
    main()
