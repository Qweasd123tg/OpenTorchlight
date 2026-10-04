#!/usr/bin/env python3
"""Readable call trace of a function: each call with its resolved arguments.

Constructors of descriptors and menus are thousands of instructions that boil
down to calls with literal arguments. This folds them into lines such as

    CDescriptor::AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the ...",
        CLogicTimerDescriptor::Set_setEnabled, CLogicTimerDescriptor::Get_getEnabled, 6, 0)

Arguments resolve to string literals (also through std::string/std::wstring
temporaries built on the stack), immediates, function addresses, `this`,
`this+off` members and known globals. Unknown values print as `?`. Branches are
not followed: the trace is in address order and is a reading aid only.

    python3 tools/decomp/calls.py 0x66a940
    python3 tools/decomp/calls.py "CLogicTimerDescriptor::CLogicTimerDescriptor"
"""
from __future__ import annotations

import argparse
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import elfimage  # noqa: E402
import layout  # noqa: E402
import objdiff  # noqa: E402

STRING_CTORS = {"_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_": "L", "_ZNSsC1EPKcRKSaIcE": ""}
NOISE = re.compile(r"^(_ZdlPv|_ZdaPv|_Unwind_Resume|__cxa_end_cleanup|_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroy"
                   r"|_ZNSs4_Rep10_M_destroy|_ZNSbIwSt11char_traitsIwESaIwEED1Ev|_ZNSsD1Ev)")
ARGS = ["rdi", "rsi", "rdx", "rcx", "r8", "r9"]


class Tracer:
    def __init__(self, db=None):
        self.db = db or elfdb.load_db()
        self.insns = layout.load_insns(self.db)
        self.image = elfimage.load(elfdb.default_elf())
        self.by_name = {}
        for f in self.db["functions"].values():
            for n in f["names"]:
                self.by_name[n] = f
        self.globals = {int(g["address"], 16): g["demangled"] for g in self.db["globals"]}
        self.plt = {a: n.split("@")[0] for a, n in self.image.plt.items()}

    def find(self, text):
        if text.startswith("0x"):
            return self.db["functions"][hex(int(text, 16))]
        hits = [f for f in self.db["functions"].values() if f["demangled"].startswith(text) or text in f["names"]]
        if not hits:
            raise SystemExit(f"no function {text}")
        return max(hits, key=lambda f: f["size"])

    def literal(self, address):
        raw = None
        for size in (8192, 512, 64):  # long wide literals need more than 512 bytes
            try:
                raw = self.image.read(address, size)
                break
            except ValueError:
                continue
        if raw is None:
            return None
        section = self.image.section_at(address)
        if not section or not section.name.startswith(".rodata"):
            return None
        text = objdiff.printable_string(raw)
        if text is None:
            return None
        return text + '"' if text.startswith('L"') else f'"{text}"'

    def immediate(self, value):
        f = self.db["functions"].get(hex(value))
        if f:
            return ("func", f["demangled"].split("(")[0])
        lit = self.literal(value)
        if lit:
            return ("str", lit)
        if value in self.globals:
            return ("global", "&" + self.globals[value])
        return ("imm", value)

    @staticmethod
    def show(value):
        kind, v = value
        if kind == "imm" and isinstance(v, int):
            return str(v - (1 << 32)) if (1 << 31) <= v < (1 << 32) else (str(v) if v < 0x10000 else hex(v))
        if kind == "this":
            return "this" if not v else f"&this->+{v:#x}"
        return str(v)

    def trace(self, f):
        regs = {"rdi": ("this", 0)}
        own = layout.split_params(f.get("params") or "")
        is_static = not f.get("scope") or f["kind"] == "static"
        int_params = [i for i, p in enumerate(own) if p not in ("float", "double")]
        for n, i in enumerate(int_params[: 6 - (0 if is_static else 1)]):
            regs[ARGS[n + (0 if is_static else 1)]] = ("param", f"arg{i + 1}")
        after_ret = False
        slots = {}
        stack_args = {}
        lines = []
        for addr, mnem, ops_text, target in self.insns.get(f["address"], []):
            ops = layout.split_operands(ops_text) if ops_text else []
            dest = layout.REG64.get(ops[-1].lstrip("%")) if ops and ops[-1].startswith("%") else None
            callee = target.split("@")[0] if target else ""
            tail = False
            if mnem == "jmp" and callee and re.fullmatch(r"[0-9a-f]+", ops_text or ""):
                dest_addr = int(ops_text, 16)
                known = self.by_name.get(callee)
                tail = (known is not None and int(known["address"], 16) == dest_addr) or dest_addr in self.plt
            if mnem in ("ret", "repz") and not after_ret:
                after_ret = True
                lines.append("// --- after the first ret: shared tails, slow paths, EH cleanups ---")
                continue
            if mnem.startswith("call") or tail:
                if callee in STRING_CTORS and regs.get("rdi", ("",))[0] == "slot":
                    src = regs.get("rsi")
                    if src and src[0] == "str":
                        slots[regs["rdi"][1]] = ("str", src[1])
                elif callee and not NOISE.match(callee):
                    f2 = self.by_name.get(callee)
                    name = f2["demangled"].split("(")[0] if f2 else elfimage.demangle([callee]).get(callee, callee)
                    params = layout.split_params(f2.get("params") or "") if f2 else []
                    is_method = bool(f2 and f2.get("scope") and f2["kind"] != "static")
                    count = len(params) + (1 if is_method else 0)
                    int_args = []
                    for p in ([None] if is_method else []) + params:
                        int_args.append(p not in ("float", "double"))
                    values = []
                    reg_i, stack_i = 0, 0
                    for is_int in int_args or [True] * 0:
                        if not is_int:
                            values.append(("imm", "<xmm>"))
                            continue
                        if reg_i < 6:
                            values.append(regs.get(ARGS[reg_i], ("unknown", "?")))
                            reg_i += 1
                        else:
                            values.append(stack_args.get(stack_i, ("unknown", "?")))
                            stack_i += 8
                    shown = []
                    for v in values:
                        if v[0] == "slot":
                            shown.append(self.show(slots.get(v[1], ("unknown", f"tmp@{v[1]:#x}"))))
                        else:
                            shown.append(self.show(v))
                    if is_method and shown and shown[0] == "this":
                        call = f"{name}({', '.join(shown[1:])})"
                    elif is_method and shown:
                        call = f"[{shown[0]}] {name}({', '.join(shown[1:])})"
                    else:
                        call = f"{name}({', '.join(shown) if f2 else '...'})"
                    lines.append(f"{addr:#x}  {call}")
                for r in layout.CALLER_SAVED:
                    regs.pop(r, None)
                stack_args = {}
                continue
            if mnem in ("mov", "movq", "movl") and len(ops) == 2:
                src, dst = ops
                m = layout.MEM.match(dst)
                if m and m.group(2) == "rsp" and not m.group(3) and src.startswith("$"):
                    stack_args[int(m.group(1) or "0", 0)] = self.immediate(int(src[1:], 16))
                    continue
                if m and m.group(2) == "rsp" and src.startswith("%"):
                    stack_args[int(m.group(1) or "0", 0)] = regs.get(layout.REG64.get(src.lstrip("%")), ("unknown", "?"))
                    continue
                if dest:
                    if src.startswith("$"):
                        regs[dest] = self.immediate(int(src[1:], 16))
                    elif src.startswith("%") and layout.REG64.get(src.lstrip("%")) in regs:
                        regs[dest] = regs[layout.REG64[src.lstrip("%")]]
                    else:
                        msrc = layout.MEM.match(src)
                        if msrc and not msrc.group(3) and regs.get(layout.REG64.get(msrc.group(2)), ("",))[0] == "this":
                            off = regs[layout.REG64[msrc.group(2)]][1] + int(msrc.group(1) or "0", 0)
                            regs[dest] = ("member", f"this->+{off:#x}")
                        elif src.startswith("0x") and "(%rip)" in src:
                            regs[dest] = ("unknown", "?")
                        else:
                            regs.pop(dest, None)
                    continue
            if mnem == "lea" and dest and ops:
                m = layout.MEM.match(ops[0])
                if m and not m.group(3):
                    off = int(m.group(1) or "0", 0)
                    base = layout.REG64.get(m.group(2))
                    if base == "rsp":
                        regs[dest] = ("slot", off)
                    elif regs.get(base, ("",))[0] == "this":
                        regs[dest] = ("this", regs[base][1] + off)
                    else:
                        regs.pop(dest, None)
                    continue
            if mnem.startswith("xor") and len(ops) == 2 and ops[0] == ops[1] and dest:
                regs[dest] = ("imm", 0)
                continue
            if dest and not mnem.startswith(("cmp", "test", "push", "ucomi", "comi")):
                regs.pop(dest, None)
        return lines

    def plt_names(self):
        cache = self.__dict__.get("_pltn")
        if cache is None:
            cache = self.__dict__["_pltn"] = dict.fromkeys(self.plt.values())
        return cache


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("function", help="address (0x...) or demangled prefix")
    args = parser.parse_args()
    tracer = Tracer()
    f = tracer.find(args.function)
    print(f"// {f['address']} {f['demangled']} ({f['size']} bytes)")
    for line in tracer.trace(f):
        print(line)


if __name__ == "__main__":
    main()
