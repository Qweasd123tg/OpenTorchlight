#!/usr/bin/env python3
"""Compare decompiled functions with the original machine code.

Compiles a decomp source with the original toolchain (GCC 4.4.7-3), then
compares every function symbol of the object with the original function of the
same mangled name. Instructions are normalized: relocated operands and absolute
addresses become symbol names, string literals become their contents, float
constants become their bytes and intra-function branches become instruction
indices. Exact instruction equality is MATCH only when referenced data is
complete and there is no unverified per-function personality/LSDA metadata.

    python3 tools/decomp/objdiff.py decomp/src/RunicCore.cpp
    python3 tools/decomp/objdiff.py decomp/src/RunicCore.cpp --show _ZN10CRunicCoreC2Ev
    python3 tools/decomp/objdiff.py --all --json build-decomp/progress.json
"""
from __future__ import annotations

import argparse
import bisect
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import threading

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import elfimage  # noqa: E402
import objdiff_eh  # noqa: E402
import objdiff_disasm  # noqa: E402
import toolchain  # noqa: E402

ROOT = elfdb.ROOT
SRC = ROOT / "decomp" / "src"
INSN = re.compile(r"^\s*([0-9a-f]+):\s+(\S+(?: \S+)?)\s*(.*)$")
PREFIXES = ("rep", "repz", "repnz", "lock", "data16", "cs", "ds", "addr32", "rex", "rex.W")
PC_RELATIVE = {2, 4}          # R_X86_64_PC32, R_X86_64_PLT32
ABSOLUTE = {1, 10, 11}        # R_X86_64_64, R_X86_64_32, R_X86_64_32S
PACKED = ("ps", "pd", "dqa", "dqu", "aps", "apd")


def const_size(mnemonic):
    if mnemonic.startswith("data-size:"):
        return int(mnemonic.split(":")[1])
    integer = re.match(r"^(?:mov|add|sub|and|or|xor|cmp|test|imul|inc|dec|neg|not)([bwlq])$", mnemonic)
    if integer:
        return {"b": 1, "w": 2, "l": 4, "q": 8}[integer.group(1)]
    if mnemonic in ("flds", "fldl", "fldt", "movlps", "movhps", "movlpd", "movhpd"):
        return {"flds": 4, "fldl": 8, "fldt": 10}.get(mnemonic, 8)
    if mnemonic.endswith(PACKED) or mnemonic in ("pxor", "pand", "por", "andps", "xorps"):
        return 16
    if "sd" in mnemonic or mnemonic.endswith("q"):
        return 8
    return 4


def memory_mnemonic(mnemonic, operands):
    """objdump omits integer width suffixes when the destination determines it."""
    if mnemonic.startswith(("movzb", "movsb")):
        return "data-size:1"
    if mnemonic.startswith(("movzw", "movsw")):
        return "data-size:2"
    if mnemonic.startswith("movsl"):
        return "data-size:4"
    integer = ("mov", "movabs", "add", "sub", "and", "or", "xor", "cmp", "test", "imul")
    if mnemonic in integer:
        register = operands.rsplit(",", 1)[-1].strip()
        if re.fullmatch(r"%(?:r(?:ax|bx|cx|dx|si|di|bp|sp|[0-9]+))", register):
            return "data-size:8"
        if re.fullmatch(r"%(?:[abcd]x|si|di|bp|sp|r[0-9]+w)", register):
            return "data-size:2"
        if re.fullmatch(r"%(?:[abcd][lh]|sil|dil|bpl|spl|r[0-9]+b)", register):
            return "data-size:1"
    return mnemonic


def printable_string(raw):
    """Literal token for narrow (ASCII) or wide (UTF-32LE wchar_t) strings."""
    wide = []
    for i in range(0, len(raw) - 3, 4):
        code = int.from_bytes(raw[i:i + 4], "little")
        if code == 0:
            break
        if not (32 <= code < 0x10000 or code in (9, 10, 13)):
            wide = None
            break
        wide.append(chr(code))
    else:
        wide = None
    if wide:
        return 'L"' + "".join(wide)
    end = raw.find(b"\0")
    if end <= 0:
        return None
    text = raw[:end]
    if all(32 <= b < 127 or b in (9, 10, 13) for b in text):
        return text.decode("ascii")
    return None


class UnverifiedData(ValueError):
    pass


def literal_token(raw, width=None):
    """Full terminated bytes, including character width and payload length.

    Linked .rodata has lost string-section width. If both interpretations are
    possible, instruction equality cannot establish the width of the literal.
    """
    def narrow():
        end = raw.find(b"\0")
        if end < 0:
            return None
        if width is None and not all(32 <= b < 127 or b in (9, 10, 13) for b in raw[:end]):
            return None
        return raw[:end]

    def wide():
        for end in range(0, len(raw) - 3, 4):
            code = int.from_bytes(raw[end:end + 4], "little")
            if code == 0:
                return raw[:end]
            if width is None and (code > 0x10ffff or 0xd800 <= code <= 0xdfff
                                  or not (chr(code).isprintable() or code in (9, 10, 13))):
                return None
        return None

    if width not in (None, 1, 4):
        raise UnverifiedData("unsupported string width")
    candidates = [(w, payload) for w, payload in
                  ((1, narrow() if width in (None, 1) else None),
                   (4, wide() if width in (None, 4) else None)) if payload is not None]
    if len(candidates) > 1:
        raise UnverifiedData("ambiguous narrow/wide literal in linked rodata")
    if not candidates:
        raise UnverifiedData("unterminated or unclassified literal")
    w, payload = candidates[0]
    return f"lit:w{w}:n{len(payload) // w}:{payload.hex()}"


def string_width(section):
    match = re.match(r"^\.rodata\.str([0-9]+)\.", section.name)
    return int(match.group(1)) if match else None


def run_objdump(args):
    env = dict(os.environ, LC_ALL="C")
    return subprocess.run(["objdump", "-d", "-w", "--no-show-raw-insn"] + args, check=True,
                          capture_output=True, text=True, env=env).stdout


def parse_insns(text):
    out = []
    for line in text.splitlines():
        m = INSN.match(line)
        if m and not line.lstrip().startswith(("R_X86", "Disassembly")):
            mnemonic, operands = m.group(2), m.group(3).strip()
            # objdump prints prefixes as part of the mnemonic field ("repz ret").
            first = mnemonic.split(" ")
            if len(first) == 2 and first[0] not in PREFIXES:
                mnemonic, operands = first[0], (first[1] + " " + operands).strip()
            out.append([int(m.group(1), 16), mnemonic, operands])
    return out


class Normalizer:
    """Shared operand normalization; subclasses resolve addresses to tokens."""

    JUMP_TABLE = re.compile(r"^\*(0x[0-9a-f]+)\(,(%\w+),8\)$")

    def data_token(self, raw, mnemonic, address_operand=False, width=None):
        try:
            if address_operand:
                return literal_token(raw, width)
            size = const_size(mnemonic)
            if len(raw) < size:
                raise UnverifiedData(f"truncated {size}-byte constant")
            return "const:" + raw[:size].hex()
        except UnverifiedData as exc:
            if not hasattr(self, "unverified"):
                self.unverified = []
            self.unverified.append(str(exc))
            return "unverified-data:" + hashlib.sha256(raw).hexdigest()

    def branch(self, insn_index, target, start, end, offsets):
        if start <= target < end:
            labels = getattr(self, "labels", None)
            if labels and target in labels:
                return f"L{labels[target]}"
            pos = bisect.bisect_left(offsets, target)
            return f"L{pos}" if pos < len(offsets) and offsets[pos] == target else f"L?{target - start:#x}"
        return None

    @staticmethod
    def register(operand):
        """Canonical integer register and width; partial writes still clobber it."""
        old = {"ax": "a", "bx": "b", "cx": "c", "dx": "d",
               "si": "si", "di": "di", "bp": "bp", "sp": "sp"}
        for suffix, family in old.items():
            if operand == "%r" + suffix:
                return family, 64
            if operand == "%e" + suffix:
                return family, 32
            if operand == "%" + suffix:
                return family, 16
        byte = {"al": "a", "ah": "a", "bl": "b", "bh": "b", "cl": "c", "ch": "c",
                "dl": "d", "dh": "d", "sil": "si", "dil": "di", "bpl": "bp", "spl": "sp"}
        if operand.lstrip("%") in byte and operand.startswith("%"):
            return byte[operand[1:]], 8
        m = re.fullmatch(r"%r(8|9|1[0-5])([dwb]?)", operand)
        return (m.group(1), {"": 64, "d": 32, "w": 16, "b": 8}[m.group(2)]) if m else None

    @staticmethod
    def direct_target(operands):
        match = re.fullmatch(r"([0-9a-f]+)(?: <[^>]+>)?", operands)
        return int(match.group(1), 16) if match else None

    @classmethod
    def reaches_without(cls, entry, goal, blocked, insns):
        """Conservative CFG reachability; an unknown indirect edge may reach goal."""
        positions = {row[0]: i for i, row in enumerate(insns)}
        pending, seen = [entry], set()
        while pending:
            i = pending.pop()
            if i == blocked or i in seen or i is None or not 0 <= i < len(insns):
                continue
            if i == goal:
                return True
            seen.add(i)
            _, mnemonic, operands = insns[i]
            if mnemonic.startswith("ret") or mnemonic in ("ud2", "hlt"):
                continue
            if mnemonic.startswith(("j", "loop")):
                target = cls.direct_target(operands)
                if target is None:
                    return True
                if target not in positions:
                    return True  # external/unparsed continuation is not a proved exit
                pending.append(positions[target])
                if mnemonic == "jmp":
                    continue
            pending.append(i + 1)
        return False

    @classmethod
    def table_size(cls, k, insns, register=None):
        """Prove an unsigned guard of this index, rather than use a nearby cmp.

        Supported guards dominate the dispatch and their in-range edge follows
        one straight path to it. Register copies are tracked, including the
        zero extension needed when a 32-bit comparison bounds a 64-bit index.
        Unsupported control/data flow deliberately leaves the range unknown.
        """
        if register is None:
            table = cls.JUMP_TABLE.match(insns[k][2])
            register = table.group(2) if table else None
        index = cls.register(register or "")
        positions = {row[0]: i for i, row in enumerate(insns)}
        for compare in range(k - 1, -1, -1):
            _, mnemonic, operands = insns[compare]
            match = re.fullmatch(r"\$0x([0-9a-f]+),(%\w+)", operands)
            bound = cls.register(match.group(2)) if match and mnemonic in ("cmp", "cmpl", "cmpq") else None
            if not bound or bound[1] not in (32, 64):
                continue
            guard = compare + 1
            while guard < k and cls.padding(insns[guard][1], insns[guard][2]):
                guard += 1
            if guard >= k:
                continue
            _, jump, target_operand = insns[guard]
            if jump not in ("ja", "jae", "jbe", "jb"):
                continue
            target = cls.direct_target(target_operand)
            if target is None:
                continue
            count = int(match.group(1), 16) + (jump in ("ja", "jbe"))
            if not 0 < count <= 4096:
                continue
            taken = positions.get(target)
            if taken is None:  # an external guard edge has unverified continuation
                continue
            inside, outside = ((guard + 1, taken) if jump in ("ja", "jae") else (taken, guard + 1))
            if (cls.reaches_without(0, guard, compare, insns)
                    or cls.reaches_without(0, k, guard, insns)
                    or cls.reaches_without(outside, k, guard, insns)):
                continue
            values = {bound[0]: bound[1] == 64}
            # A dominating 32-bit write may already have cleared the upper half.
            if bound[1] == 32:
                for before in range(compare - 1, -1, -1):
                    _, op, args = insns[before]
                    if op.startswith(("j", "call", "ret", "loop")):
                        break
                    dest = cls.register(args.rsplit(",", 1)[-1].strip())
                    if dest and dest[0] == bound[0] and op not in ("cmp", "cmpl", "cmpq", "test", "testl", "testq"):
                        if (op in ("mov", "movl") and dest[1] == 32
                                and not cls.reaches_without(0, compare, before, insns)):
                            values[bound[0]] = True
                        break
            cursor, visited = inside, set()
            while cursor is not None and cursor != k and cursor not in visited:
                if not 0 <= cursor < len(insns):
                    break
                visited.add(cursor)
                _, op, args = insns[cursor]
                if cls.padding(op, args):
                    cursor += 1
                    continue
                if op == "jmp":
                    cursor = positions.get(cls.direct_target(args))
                    continue
                if op not in ("mov", "movb", "movw", "movl", "movq", "cmp", "cmpb", "cmpw", "cmpl", "cmpq",
                              "test", "testb", "testw", "testl", "testq") and not op.startswith("set"):
                    break
                source, _, destination = args.rpartition(",")
                dest = cls.register(destination.strip())
                src = cls.register(source.strip())
                if not op.startswith(("cmp", "test")) and dest:
                    old = values.get(src[0]) if src else None
                    values.pop(dest[0], None)
                    if op in ("mov", "movl", "movq") and old is not None and src[1] == dest[1] and dest[1] in (32, 64):
                        values[dest[0]] = dest[1] == 32 or old
                cursor += 1
            if cursor == k and index and values.get(index[0]) is True:
                return count
        return None

    @classmethod
    def memory_table_size(cls, k, insns, register):
        """A dominating unsigned memory guard followed by its immediate load.

        Narrow GCC idiom: cmp[lq] immediate, cell; jbe/jb/ja/jae; then
        mov the *same cell* into the table index, with only padding before jmp.
        No intervening writes, calls, base changes or alternative entries.
        """
        index = cls.register(register or '')
        if not index or index[1] != 64:
            return None
        positions = {row[0]: i for i, row in enumerate(insns)}
        for compare in range(k - 1, -1, -1):
            _, op, operand = insns[compare]
            match = re.fullmatch(r'\$0x([0-9a-f]+),((?:-?0x[0-9a-f]+)?\(%(?:rdi|rsi|rdx|rcx|rbx|rbp|r8|r9|r10|r11|r12|r13|r14|r15)\))', operand)
            if not match or op not in ('cmpl', 'cmpq'):
                continue
            width = 32 if op == 'cmpl' else 64
            guard = compare + 1
            while guard < k and cls.padding(insns[guard][1], insns[guard][2]):
                guard += 1
            if guard >= k:
                continue
            _, jump, target_operand = insns[guard]
            if jump not in ('ja', 'jae', 'jbe', 'jb'):
                continue
            taken = positions.get(cls.direct_target(target_operand))
            if taken is None:
                continue
            count = int(match[1], 16) + (jump in ('ja', 'jbe'))
            inside, outside = ((guard + 1, taken) if jump in ('ja', 'jae') else (taken, guard + 1))
            if (not 0 < count <= 4096 or not inside < k
                    or cls.reaches_without(0, guard, compare, insns)
                    or cls.reaches_without(0, k, guard, insns)
                    or cls.reaches_without(outside, k, guard, insns)):
                continue
            path = [(m, p) for _, m, p in insns[inside:k] if not cls.padding(m, p)]
            if len(path) != 1 or path[0][0] not in ('mov', 'movl', 'movq'):
                continue
            source, _, destination = path[0][1].rpartition(',')
            dest = cls.register(destination)
            if source == match[2] and dest and dest[0] == index[0] and dest[1] == width:
                return count
        return None

    def jump_table(self, k, entries, register, start, end, offsets, insns):
        """Compare every entry of a proved range; missing targets forbid MATCH."""
        count = self.table_size(k, insns, register)
        if count is None:
            count = self.memory_table_size(k, insns, register)
        if count is None:
            self.unverified.append("jump table index range unverified")
            return f"jmp *[unverified-table:range](,{register},8)"
        labels, entries = [], iter(entries)
        for i in range(count):
            target = next(entries, None)
            if isinstance(target, str):
                labels.append(target)
                continue
            label = self.branch(k, target, start, end, offsets) if target is not None else None
            if label is None or label.startswith("L?"):
                self.unverified.append(f"jump table entry {i} target unverified")
                labels.append(f"unverified:{target!r}")
            else:
                labels.append(label)
        return f"jmp *[table:{','.join(labels)}](,{register},8)"

    @staticmethod
    def padding(mnemonic, operands):
        # objdump may put the third word of a long prefixed nop in operands.
        # A segment/size prefix alone does not make a real instruction padding.
        words = (mnemonic + " " + operands).split()
        while words and words[0] in ("data16", "cs"):
            words.pop(0)
        if not words:
            return False
        return (words[0] in ("nop", "nopw", "nopl")
                or words[0] == "xchg" and "".join(words[1:]) == "%ax,%ax")

    def normalize(self, insns, start, end):
        self.unverified = []
        self.literal_proofs = []
        offsets = [i[0] for i in insns]
        # Branch labels count kept instructions only: alignment padding differs
        # between the original and our object and must not shift the indices.
        self.labels = {}
        kept = 0
        for address, mnemonic, operands in insns:
            self.labels[address] = kept
            if not self.padding(mnemonic, operands):
                kept += 1
        result = []
        for k, (address, mnemonic, operands) in enumerate(insns):
            if self.padding(mnemonic, operands):
                continue
            nxt = offsets[k + 1] if k + 1 < len(offsets) else end
            operands = operands.split("#", 1)[0].strip() if "#" in operands and "(%rip)" in operands else operands
            result.append(self.token(k, address, nxt, mnemonic, operands, start, end, offsets, insns))
        return result


OGRE_LITERAL_SHA256 = "bef109bfdc1210ede92731ead4a2b3fae76a8905f10bac14d5fdb54ae5474c31"


def literal_library_path():
    game = Path(os.environ.get("TORCHLIGHT_GAME_DIR", Path(elfdb.default_elf()).parent))
    return game / "lib64" / "libOgreMain-1.6.5.so"


def literal_library_identity():
    try:
        return hashlib.sha256(literal_library_path().read_bytes()).hexdigest()
    except OSError:
        return "missing"


class OriginalSide(Normalizer):
    def __init__(self, image, db):
        self.image = image
        self.func_start = {int(a, 16): f["mangled"] for a, f in db["functions"].items()}
        objects = []
        for s in image.symbols:
            if s.type == elfimage.STT_OBJECT and s.defined and s.size and s.name:
                objects.append((s.value, s.size, s.name))
        for s in image.dynsyms:
            if s.type == elfimage.STT_OBJECT and s.defined and s.size and s.name:
                objects.append((s.value, s.size, s.name))
        objects.sort()
        self.obj_starts = [o[0] for o in objects]
        self.objects = objects
        # Exact-address names, including zero-sized markers such as __dso_handle.
        self.exact = {}
        for s in list(image.symbols) + list(image.dynsyms):
            if s.defined and s.name and s.type in (elfimage.STT_OBJECT, elfimage.STT_NOTYPE) and s.value:
                self.exact.setdefault(s.value, s.name.split("@")[0])
        self.rodata = [image.section(n) for n in (".rodata",) if n]
        self.low, self.high = 0x400000, max(s.addr + s.size for s in image.sections if s.addr)

    WSTRING_CTOR = "_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_"

    STRING_DTOR = "_ZNSsD1Ev"
    WSTRING_DTOR = "_ZNSbIwSt11char_traitsIwESaIwEED1Ev"
    WSTRING_COMPARE = "_ZNKSbIwSt11char_traitsIwESaIwEE7compareEPKw"

    def _prefix_wide_literal_use(self, k, insns, start=None, end=None):
        """Prove one immediate's width from an original imported consumer.

        Legacy, deliberately tiny straight-line SysV idiom, never candidate
        types or a global address override. Its conservative prefix recognizer
        rejects prior calls, branches and known interior function entries; this
        is not a claim to enumerate arbitrary whole-program machine-code entries.
        """
        address, op, args = insns[k]
        match = re.fullmatch(r"\$0x([0-9a-f]+),%(?:esi|rsi)", args)
        if op not in ("mov", "movl", "movq", "movabs") or not match:
            return None
        if any(m.startswith(("j", "loop")) for _, m, _ in insns):
            return None
        # Only explicitly understood setup instructions are admitted. In
        # particular partial writes, pointer copies, string ops and unknown
        # implicit-register instructions cannot silently cross this proof.
        for i, (pc, mnemonic, operands) in enumerate(insns):
            if i != 0 and pc in self.func_start:
                return None
            if i == k:
                continue
            if mnemonic in ("call", "callq"):
                if i <= k:
                    return None
                target = self.direct_target(operands)
                callee = self.image.plt.get(target, "").split("@")[0]
                if callee != self.WSTRING_CTOR:
                    return None
                # A proven consumer establishes width, but not that pointer
                # identity is unobservable afterwards. The old prefix shape is
                # never sufficient to bypass normal/EH lifetime validation.
                if start is None or end is None:
                    return None
                return self._forward_wide_literal_use(k, insns, start, end)
            if self.padding(mnemonic, operands):
                continue
            if i > k and any(self.register(r) == ("si", bits)
                             for r in re.findall(r"%\w+", operands)
                             for bits in (8, 16, 32, 64)):
                return None
            registers = operands.split(",")
            if (mnemonic == "push" and len(registers) == 1
                    and self.register(registers[0]) is not None):
                continue
            if (mnemonic in ("mov", "movl", "movq") and len(registers) == 2
                    and all(self.register(r) is not None for r in registers)):
                continue
            if mnemonic == "sub" and re.fullmatch(r"\$0x[0-9a-f]+,%rsp", operands):
                continue
            if mnemonic == "lea" and re.fullmatch(r"0x[0-9a-f]+\(%rsp\),%rdx", operands):
                continue
            return None
        return None

    @classmethod
    def _mentions_rsi(cls, operands):
        return any(cls.register(r) and cls.register(r)[0] == "si"
                   for r in re.findall(r"%\w+", operands))

    @classmethod
    def _rsi_kill(cls, mnemonic, operands):
        # 32-bit writes zero the high half. Partial writes are never kills.
        source, comma, dest = operands.rpartition(",")
        if not comma or cls.register(dest) not in (("si", 32), ("si", 64)):
            return False
        if mnemonic in ("mov", "movl", "movq", "movabs", "lea"):
            return not cls._mentions_rsi(source)
        return mnemonic in ("xor", "xorl", "xorq") and source == dest

    @classmethod
    def _literal_independent_instruction(cls, mnemonic, operands, blocked=("si",)):
        """Small explicit-effect whitelist; no implicit RSI or string ops."""
        if cls.padding(mnemonic, operands):
            return True
        if any(cls.register(r) and cls.register(r)[0] in blocked
               for r in re.findall(r"%\w+", operands)):
            return False
        if mnemonic in ("seta", "setae", "setb", "setbe", "setc", "sete", "setg", "setge",
                        "setl", "setle", "setna", "setnae", "setnb", "setnbe", "setnc",
                        "setne", "setng", "setnge", "setnl", "setnle", "setno", "setnp",
                        "setns", "setnz", "seto", "setp", "setpe", "setpo", "sets", "setz"):
            # Exact legacy SETcc reads flags and writes one byte, not a full GPR.
            # Blocked register families were excluded above; this never kills
            # a raw alias or supplies a branch predicate. No memory/prefix/SP.
            return bool(re.fullmatch(r"%(?:[abcd][lh]|[sd]il|bpl|r(?:[89]|1[0-5])b)", operands))
        if mnemonic in ("mov", "movb", "movw", "movl", "movq", "movabs", "lea",
                        "xor", "xorl", "xorq", "or", "orl", "orq", "test", "testl", "testq", "cmp", "cmpl", "cmpq",
                        "add", "addl", "addq", "sub", "subl", "subq", "shl", "shr", "sar"):
            # Only ordinary AT&T operands. Reject segments, unsupported prefixes,
            # and implicit-register forms even if disassembly was unfamiliar.
            return (
                len(operands.split(",")) >= 2 and ":" not in operands
                and not any(x in operands for x in ("*", "#")))
        if mnemonic in ("movslq", "movzbl", "movss"):
            # Exact extension/scalar-float forms have only explicit operands;
            # no implicit integer-register reads and no flags inputs/outputs.
            source, comma, dest = operands.rpartition(",")
            if not comma:
                return False
            def base_memory(value):
                match = re.fullmatch(r"(?:-?0x[0-9a-f]+)?\((%[a-z0-9]+)\)", value)
                reg = cls.register(match.group(1)) if match else None
                return bool(reg and reg[1] == 64)
            src, dst = cls.register(source), cls.register(dest)
            if mnemonic == "movslq":
                return bool(src and src[1] == 32 and dst and dst[1] == 64)
            if mnemonic == "movzbl":
                return bool(dst and dst[1] == 32
                            and ((src and src[1] == 8) or base_memory(source)))
            xmm = lambda operand: bool(re.fullmatch(r"%xmm(?:[0-9]|1[0-5])", operand))
            return ((xmm(source) and (xmm(dest) or base_memory(dest)))
                    or (base_memory(source) and xmm(dest)))
        if mnemonic == "xorps":
            # Register-only SSE bitwise XOR reads/writes only named XMM regs;
            # no integer-register or flags input/output, no memory addressing.
            return bool(re.fullmatch(r"%xmm(?:[0-9]|1[0-5]),%xmm(?:[0-9]|1[0-5])", operands))
        if mnemonic in ("lock xadd", "lock xaddl", "lock xaddq"):
            # Exact ordinary XADD register -> base+displacement memory form.
            # Both explicit operands exclude RSI above; XADD has no implicit
            # integer-register inputs (flags are outputs, not inputs).
            match = re.fullmatch(r"(%[a-z0-9]+),(-?0x[0-9a-f]+)?\((%[a-z0-9]+)\)", operands)
            if match:
                source, base = cls.register(match.group(1)), cls.register(match.group(3))
                return bool(source and source[1] in (32, 64) and base and base[1] == 64)
            return False
        return mnemonic in ("push", "pop") and cls.register(operands) is not None

    def _literal_eh(self, insns, start, end):
        frames = getattr(self, "frames", None)
        if frames is None or frames.error:
            return None
        reason = frames.reason(start, end - start)
        if reason is None:
            return {"rows": [], "kind": "no-lsda"}
        if reason != "EH LSDA equivalence unverified":
            return None
        signature = objdiff_eh.cleanup_signature(self.image, frames, start, end - start, insns)
        if signature is None:
            return None
        return {"rows": signature[3], "kind": signature[0]}

    def _callee_body(self, image, target, max_bytes=1024):
        """Exact original STT_FUNC bounds, never reconstructed declarations."""
        symbols = [s for s in list(image.symbols) + list(image.dynsyms)
                   if s.defined and s.type == elfimage.STT_FUNC and s.value == target and s.size]
        sizes = {s.size for s in symbols}
        if len(sizes) != 1 or not 0 < next(iter(sizes)) <= max_bytes:
            return None
        size = next(iter(sizes))
        section = image.section_at(target)
        if not section or not section.flags & 4 or target + size > section.addr + section.size:
            return None
        try:
            if hashlib.sha256(image.data).hexdigest() != image.sha256:
                return None
            raw = image.read(target, size)
            # Decode the exact immutable snapshot whose bytes are hashed. Two
            # hashes around a mutable path would not prevent replace-and-restore.
            with tempfile.NamedTemporaryFile(prefix="otl-literal-body-", suffix=".elf") as snapshot:
                snapshot.write(image.data)
                snapshot.flush()
                rows = parse_insns(run_objdump([snapshot.name, f"--start-address={target}",
                                               f"--stop-address={target + size}"]))
        except (OSError, ValueError, subprocess.CalledProcessError):
            return None
        pcs = [r[0] for r in rows]
        if not pcs or pcs[0] != target or pcs != sorted(set(pcs)) or pcs[-1] >= target + size:
            return None
        return {"start": target, "size": size, "rows": rows,
                "names": sorted({x.name for x in symbols}),
                "body_sha256": hashlib.sha256(raw).hexdigest()}

    def _pinned_literal_library(self):
        # Each comparison session pins one read-only snapshot. A changed/missing
        # backing input must not silently reuse a proof under a new cache key.
        identity = getattr(self, "library_identity", None)
        if identity != OGRE_LITERAL_SHA256 or literal_library_identity() != identity:
            return None
        if not hasattr(self, "_literal_library"):
            try:
                image = elfimage.load(literal_library_path(), require_original=False)
            except (OSError, ValueError):
                return None
            if image.sha256 != identity:
                return None
            self._literal_library = image
        return self._literal_library

    def _nonobserving_callee(self, image, target, depth=0, active=()):
        """May preserve RSI, but cannot observe its incoming value.

        This is deliberately NOT a kill summary. Callers continue checking RSI
        after the call, including a nullable wrapper's preserve-and-return path.
        Apart from explicit standard/import ABI contracts, only original bodies,
        supported cleanup EH and pinned library bytes are evidence. A callee name
        alone is never sufficient for a local call.
        """
        if depth > 4 or target is None:
            return None
        name = image.plt.get(target, "").split("@")[0]
        if name in (self.WSTRING_DTOR, self.STRING_DTOR):
            # Explicit standard-library ABI contract, NOT a claim to have the
            # original libstdc++ DSO. Complete char/wchar basic_string destruction
            # has only `this` in RDI; the incoming volatile RSI is not an input.
            return {"kind": "standard-library-abi-no-rsi-input", "callee": name,
                    "contract": ("wstring-D1-this-only-v1" if name == self.WSTRING_DTOR
                                 else "string-D1-this-only-v1"),
                    "effect": "may-preserve-not-observe"}
        if name in ("_ZdlPv", "_ZdaPv", "_Unwind_Resume"):
            return {"kind": "known-import-no-rsi-argument", "callee": name,
                    "effect": "may-preserve-not-observe"}
        if name:
            library = self._pinned_literal_library()
            if library is None:
                return None
            candidates = {s.value for s in library.dynsyms
                          if s.defined and s.type == elfimage.STT_FUNC and s.name.split("@")[0] == name}
            if len(candidates) != 1:
                return None
            proof = self._nonobserving_callee(library, candidates.pop(), depth + 1, active)
            if proof is None:
                return None
            return {"kind": "pinned-library-import", "callee": name,
                    "library_sha256": library.sha256, "body": proof,
                    "effect": "may-preserve-not-observe"}
        if not getattr(image, "sha256", None) or (image.sha256, target) in active:
            return None
        body = self._callee_body(image, target)
        if body is None:
            return None
        frames = objdiff_eh.inspect(image)
        proxy = OriginalSide.__new__(OriginalSide)
        proxy.image = image; proxy.frames = frames
        eh = proxy._literal_eh(body["rows"], target, target + body["size"])
        if eh is None:
            return None
        rows = body["rows"]; positions = {r[0]: i for i, r in enumerate(rows)}
        pending, seen, calls, kills, returns = [0], set(), [], [], []
        active = active + ((image.sha256, target),)
        while pending:
            i = pending.pop()
            if i in seen:
                continue
            if not 0 <= i < len(rows):
                return None
            seen.add(i)
            pc, op, args = rows[i]
            args = args.split("#", 1)[0].strip()
            if self._rsi_kill(op, args):
                kills.append(pc)
                continue
            if op in ("ret", "retq", "repz ret", "repz retq") and not args:
                returns.append(pc)
                continue
            if op in ("call", "callq") or op == "jmp" and self.direct_target(args) not in positions:
                callee = self.direct_target(args)
                proof = self._nonobserving_callee(image, callee, depth + 1, active)
                if proof is None:
                    return None
                calls.append({"pc": pc, "target": callee, "proof": proof})
                if op == "jmp" or proof.get("callee") == "_Unwind_Resume":
                    continue
                # Recursive summaries can preserve RSI, so never stop here.
                pending.append(i + 1)
                for begin, count, pad, _ in eh["rows"]:
                    if begin <= pc - target < begin + count and pad:
                        if target + pad not in positions:
                            return None
                        pending.append(positions[target + pad])
            elif op.startswith("j"):
                if op not in ("jmp", "je", "jne", "ja", "jae", "jb", "jbe", "jg", "jge", "jl", "jle", "js", "jns"):
                    return None
                dest = self.direct_target(args)
                if dest not in positions:
                    return None
                pending.append(positions[dest])
                if op != "jmp":
                    pending.append(i + 1)
            elif self._literal_independent_instruction(op, args):
                pending.append(i + 1)
            else:
                return None
        return {"kind": "original-body-no-rsi-observation", "effect": "may-preserve-not-observe",
                "image_sha256": image.sha256, "start": target, "size": body["size"],
                "body_sha256": body["body_sha256"], "names": body["names"],
                "visited": sorted(rows[i][0] for i in seen), "kills": kills,
                "preserving_returns": returns, "calls": calls, "eh": eh}

    def _rsi_cleanup_dead(self, insns, entry, start, eh):
        """No observation of old volatile RSI in supported cleanup-only code.

        This is not a whole-program entry certificate. Traverse only continuations
        of this call. Unknown calls/implicit effects are refused, not guessed.
        """
        positions = {row[0]: i for i, row in enumerate(insns)}
        if entry not in positions:
            return None
        pending, seen, calls = [positions[entry]], set(), []
        while pending:
            i = pending.pop()
            if i in seen:
                continue
            if not 0 <= i < len(insns):
                return None
            seen.add(i)
            pc, op, args = insns[i]
            if self._rsi_kill(op, args):
                continue
            if op in ("call", "callq"):
                target = self.direct_target(args)
                callee = self.image.plt.get(target, "").split("@")[0]
                proof = self._nonobserving_callee(self.image, target)
                if proof is None:
                    return None
                calls.append({"pc": pc, "callee": callee, "proof": proof})
                if callee == "_Unwind_Resume":
                    continue
                # A cleanup delete may unwind too; follow its supported pad.
                for begin, count, pad, _ in eh["rows"]:
                    if begin <= pc - start < begin + count and pad:
                        if start + pad not in positions:
                            return None
                        pending.append(positions[start + pad])
                pending.append(i + 1)
            elif op.startswith("j"):
                if op not in ("jmp", "je", "jne", "ja", "jae", "jb", "jbe", "jg", "jge", "jl", "jle", "js", "jns"):
                    return None
                target = self.direct_target(args)
                if target not in positions:
                    return None
                pending.append(positions[target])
                if op != "jmp":
                    pending.append(i + 1)
            elif self._literal_independent_instruction(op, args):
                pending.append(i + 1)
            else:
                return None
        return {"entry": entry, "visited": sorted(insns[i][0] for i in seen), "calls": calls}

    def _rsi_normal_dead(self, insns, entry, start, eh):
        """Finite acyclic CFG: incoming RSI is never observed before kill/return.

        RSI is not a SysV return register. A normal return ends this function's
        obligation under the existing ABI-normalized comparator contract. Calls
        may preserve RSI: their summaries never replace checking the continuation.
        Backward layout edges are allowed; DFS gray-state edges reject actual cycles.
        """
        positions = {row[0]: i for i, row in enumerate(insns)}
        if entry not in positions:
            return None
        pending, state, kills, returns, calls, cleanups = [(positions[entry], False)], {}, [], [], [], []
        while pending:
            i, leaving = pending.pop()
            if leaving:
                state[i] = 2
                continue
            if state.get(i) == 2:
                continue
            if state.get(i) == 1 or not 0 <= i < len(insns):
                return None
            state[i] = 1
            pending.append((i, True))
            pc, op, args = insns[i]
            args = args.split("#", 1)[0].strip()
            if self._rsi_kill(op, args):
                kills.append(pc)
            elif op in ("ret", "retq") and not args:
                returns.append(pc)
            elif op in ("call", "callq"):
                target = self.direct_target(args)
                proof = self._nonobserving_callee(self.image, target)
                if proof is None:
                    return None
                calls.append({"pc": pc, "proof": proof})
                for begin, count, pad, _ in eh["rows"]:
                    if begin <= pc - start < begin + count and pad:
                        cleanup = self._rsi_cleanup_dead(insns, start + pad, start, eh)
                        if cleanup is None:
                            return None
                        cleanups.append(cleanup)
                if self.image.plt.get(target, "").split("@")[0] != "_Unwind_Resume":
                    pending.append((i + 1, False))
            elif op.startswith("j"):
                if op not in ("jmp", "je", "jne", "ja", "jae", "jb", "jbe", "jg", "jge", "jl", "jle", "js", "jns"):
                    return None
                target = self.direct_target(args)
                if target not in positions:
                    return None
                pending.append((positions[target], False))
                if op != "jmp":
                    pending.append((i + 1, False))
            elif self._literal_independent_instruction(op, args):
                pending.append((i + 1, False))
            else:
                return None
        return {"entry": entry, "visited": sorted(insns[i][0] for i in state),
                "kills": sorted(kills), "returns": sorted(returns),
                "calls": calls, "cleanup": cleanups, "cfg": "acyclic-dfs-v1"}

    @classmethod
    def _forward_independent_and(cls, mnemonic, operands):
        """Exact scalar AND only before the selected imported consumer.

        No earlier RSI copy/spill/use crosses the forward scan, so this
        register-only effect cannot observe or create an alias of that load.
        This supplies no value/provenance facts or branch predicate, and does
        not extend the normal, cleanup, or callee instruction whitelist.
        """
        if mnemonic != "and":
            return False
        match = re.fullmatch(r"\$0x([0-9a-f]{1,8}),(%[a-z0-9]+)", operands)
        reg = cls.register(match.group(2)) if match else None
        return bool(reg and reg[1] == 32 and reg[0] not in ("si", "sp", "bp"))

    def _forward_wide_literal_use(self, k, insns, start, end):
        """Classify this executed load, not all possible entries to its consumer.

        Under the existing symbol/ABI-normalized comparator contract, the exact
        imported wstring constructor/compare consumes a NUL-terminated wchar_t
        sequence without retaining its source pointer. From this load there must be no alias,
        escape, address observation or alternative consumer. The normal return
        must not observe RSI before a full kill or ABI return; cleanups are also
        checked. Incoming edges which skip the load do not execute this operand.
        """
        address, op, args = insns[k]
        match = re.fullmatch(r"\$0x([0-9a-f]+),%(?:esi|rsi)", args)
        if op not in ("mov", "movl", "movq", "movabs") or not match:
            return None
        if not insns or insns[0][0] != start or not start <= address < end:
            return None
        eh = self._literal_eh(insns, start, end)
        if eh is None:
            return None
        for i in range(k + 1, len(insns)):
            pc, mnemonic, operands = insns[i]
            if mnemonic in ("call", "callq"):
                target = self.direct_target(operands)
                callee = self.image.plt.get(target, "").split("@")[0]
                if callee not in (self.WSTRING_CTOR, self.WSTRING_COMPARE):
                    return None
                break
            if not (self._literal_independent_instruction(mnemonic, operands)
                    or self._forward_independent_and(mnemonic, operands)):
                return None
        else:
            return None
        if i + 1 >= len(insns):
            return None
        normal = self._rsi_normal_dead(insns, insns[i + 1][0], start, eh)
        if normal is None:
            return None
        kill = normal["kills"][0] if len(normal["kills"]) == 1 else None
        cleanups = []
        for begin, count, pad, _ in eh["rows"]:
            if begin <= pc - start < begin + count and pad:
                proof = self._rsi_cleanup_dead(insns, start + pad, start, eh)
                if proof is None:
                    return None
                cleanups.append(proof)
        return {"load": address, "call": pc, "callee": callee,
                "argument": "rsi", "width": 4, "literal": int(match.group(1), 16),
                "model": "original-operand-forward-lifetime-v1",
                "normal_kill": kill, "normal": normal, "cleanup": cleanups, "eh_kind": eh["kind"]}

    def _saved_argument_wide_literal_use(self, k, insns, start, end):
        """Conditional original RDX operand, bounded saved-alias copy closure.

        The explicit C++/SysV object/import model forbids reading uninitialized
        abandoned callee stack bytes. Normal and exceptional aliases are checked
        separately; no callee address/name admits a local body without evidence.
        """
        if start is None or end is None or not insns or insns[0][0] != start:
            return None
        address, op, args = insns[k]
        match = re.fullmatch(r"\$0x([0-9a-f]+),%(?:edx|rdx)", args)
        if op not in ("mov", "movl", "movq", "movabs") or not match or not start <= address < end:
            return None
        eh = self._literal_eh(insns, start, end)
        if eh is None:
            return None
        for i in range(k + 1, len(insns)):
            pc, mnemonic, operands = insns[i]
            if mnemonic in ("call", "callq"):
                target = self.direct_target(operands)
                if target is None or target in self.image.plt:
                    return None
                import objdiff_saved_argument
                cached = getattr(self, "_saved_argument_engine", None)
                if cached is None or cached[0] != self.image.sha256:
                    cached = (self.image.sha256, objdiff_saved_argument.Engine(self))
                    self._saved_argument_engine = cached
                proof = cached[1].run(target, frozenset({"d"}), wrapper=True)
                if proof is None:
                    return None
                break
            if not self._literal_independent_instruction(mnemonic, operands, blocked={"d"}):
                return None
        else:
            return None
        normal_aliases = set(proof["normal_aliases"])
        exception_aliases = set(proof["exception_aliases"])
        if not (normal_aliases | exception_aliases) <= {"si"} or i + 1 >= len(insns):
            return None
        normal = {"aliases": []}
        if normal_aliases:
            normal = self._rsi_normal_dead(insns, insns[i + 1][0], start, eh)
            if normal is None:
                return None
        cleanups = []
        if exception_aliases:
            for begin, count, pad, _ in eh["rows"]:
                if begin <= pc - start < begin + count and pad:
                    cleanup = self._rsi_cleanup_dead(insns, start + pad, start, eh)
                    if cleanup is None:
                        import objdiff_null_field
                        cleanup = objdiff_null_field.certify(self, insns, k, i, start, end, eh, start + pad, cached[1])
                    if cleanup is None:
                        return None
                    cleanups.append(cleanup)
        return {"load": address, "call": pc, "argument": "rdx", "width": 4,
                "literal": int(match.group(1), 16), "model": "original-saved-wide-argument-v1",
                "consumer": proof, "normal": normal, "cleanup": cleanups, "eh_kind": eh["kind"]}

    def wide_literal_use(self, k, insns, start=None, end=None):
        proof = self._prefix_wide_literal_use(k, insns, start, end)
        if proof is not None or start is None or end is None:
            return proof
        proof = self._forward_wide_literal_use(k, insns, start, end)
        if proof is not None:
            return proof
        import objdiff_literal_flow
        proof = objdiff_literal_flow.wide_literal_use(self, k, insns, start, end)
        if proof is not None:
            return proof
        proof = self._saved_argument_wide_literal_use(k, insns, start, end)
        if proof is not None:
            return proof
        import objdiff_wcslen_append
        return objdiff_wcslen_append.certify(self, k, insns, start, end)

    def name_at(self, address, mnemonic, address_operand=False, literal_proof=None):
        if address in self.func_start:
            return self.func_start[address]
        if address in self.image.plt:
            return self.image.plt[address].split("@")[0]
        i = bisect.bisect_right(self.obj_starts, address) - 1
        if i >= 0:
            start, size, name = self.objects[i]
            name = name.split("@")[0]
            if start <= address < start + size:
                return name if address == start else f"{name}+{address - start:#x}"
        if address in self.exact:
            return self.exact[address]
        section = self.image.section_at(address)
        if section and section.name.startswith(".rodata"):
            try:
                available = section.addr + section.size - address
                raw = self.image.read(address, available if address_operand else min(available, const_size(mnemonic)))
            except ValueError:
                raw = b""
            width = string_width(section)
            if literal_proof is not None and address_operand:
                try:
                    token = literal_token(raw, 4)
                except UnverifiedData:
                    pass  # Preserve the ordinary fail-closed diagnostic below.
                else:
                    length = int(token.split(":n", 1)[1].split(":", 1)[0]) * 4 + 4
                    proof = dict(literal_proof, size=length,
                                 end=address + length,
                                 sha256=hashlib.sha256(raw[:length]).hexdigest())
                    self.literal_proofs.append(proof)
                    return token
                width = 4
            return self.data_token(raw, mnemonic, address_operand, width)
        if section:
            return f"{section.name}:{address:#x}"
        return f"{address:#x}"

    def token(self, k, address, nxt, mnemonic, operands, start, end, offsets, insns):
        m = re.match(r"^([0-9a-f]+) <([^>]+)>$", operands)
        if m and (mnemonic.startswith(("j", "call", "loop"))):
            target = int(m.group(1), 16)
            label = self.branch(k, target, start, end, offsets)
            if label:
                return f"{mnemonic} {label}"
            return f"{mnemonic} {self.name_at(target, mnemonic)}"
        table = self.JUMP_TABLE.match(operands) if mnemonic == "jmp" else None
        if table:
            base = int(table.group(1), 16)

            def entries():
                section = self.image.section_at(base)
                for i in range(4096):
                    address = base + 8 * i
                    if not section or address + 8 > section.addr + section.size:
                        return
                    try:
                        target = int.from_bytes(self.image.read(address, 8), "little")
                    except ValueError:
                        return
                    if not start <= target < end:
                        name = self.func_start.get(target) or self.image.plt.get(target)
                        yield "external:" + name.split("@")[0] if name else target
                    else:
                        yield target
            return self.jump_table(k, entries(), table.group(2), start, end, offsets, insns)

        def rip(mm):
            target = nxt + int(mm.group(1), 16) * (-1 if mm.group(0).startswith("-") else 1)
            return f"[{self.name_at(target, memory_mnemonic(mnemonic, operands), mnemonic.startswith('lea'))}](%rip)"
        operands = re.sub(r"-?0x([0-9a-f]+)\(%rip\)", rip, operands)

        literal_proof = self.wide_literal_use(k, insns, start, end)

        def absolute(mm):
            value = int(mm.group(2), 16)
            if self.low <= value < self.high:
                return f"{mm.group(1)}[{self.name_at(value, memory_mnemonic(mnemonic, operands), mm.group(1) == '$' or mnemonic.startswith('lea'), literal_proof=literal_proof)}]"
            return mm.group(0)
        operands = re.sub(r"(\$|(?<![\w%]))0x([0-9a-f]+)(?=\b)", absolute, operands)
        return f"{mnemonic} {operands}".strip()


class ObjectSide(Normalizer):
    def __init__(self, obj, resolve=None, name_at=None):
        self.obj = obj
        self.resolve = resolve or (lambda name: None)
        self.name_at = name_at
        self.funcs_by_section = {}
        for s in obj.symbols:
            if s.type == elfimage.STT_FUNC and s.defined:
                self.funcs_by_section.setdefault(s.shndx, {})[s.value] = s.name
        self.locals_by_section = {}
        for s in obj.symbols:
            if s.type == elfimage.STT_OBJECT and s.defined and s.shndx < len(obj.sections):
                self.locals_by_section.setdefault(s.shndx, {})[s.value] = s.name

    def target_name(self, symbol, offset, mnemonic, address_operand=False):
        obj = self.obj
        if symbol.name and not symbol.name.startswith(".L") and symbol.type != elfimage.STT_SECTION:
            # Same token as the original side: symbol + addend mapped to the original address.
            address = self.resolve(symbol.name)
            if address is not None and self.name_at:
                return self.name_at(address + offset, mnemonic, address_operand)
        if symbol.defined and symbol.shndx < len(obj.sections) and (
                symbol.type == elfimage.STT_SECTION or not symbol.name or symbol.name.startswith(".L")):
            offset += symbol.value if symbol.type != elfimage.STT_SECTION else 0
            section = obj.sections[symbol.shndx]
            name = section.name
            if name.startswith(".rodata"):
                data = obj.section_bytes(symbol.shndx)
                stop = section.size if address_operand else offset + const_size(mnemonic)
                raw = data[offset:stop] if 0 <= offset < section.size and len(data) == section.size else b""
                return self.data_token(raw, mnemonic, address_operand, string_width(section))
            named = self.locals_by_section.get(symbol.shndx, {}).get(offset)
            if named:
                return named
            func = self.funcs_by_section.get(symbol.shndx, {}).get(offset)
            if func:
                return func
            return f"{name}+{offset:#x}"
        return symbol.name if offset == 0 else f"{symbol.name}+{offset:#x}"

    def prepare(self, section_index):
        self.relocs = sorted(self.obj.relocs.get(section_index, []), key=lambda r: r.offset)
        self.reloc_offsets = [r.offset for r in self.relocs]
        self.section_index = section_index

    def token(self, k, address, nxt, mnemonic, operands, start, end, offsets, insns):
        lo = bisect.bisect_left(self.reloc_offsets, address)
        hi = bisect.bisect_left(self.reloc_offsets, nxt)
        relocs = self.relocs[lo:hi]
        table = self.JUMP_TABLE.match(operands) if mnemonic == "jmp" and len(relocs) == 1 else None
        if table and relocs[0].symbol.shndx < len(self.obj.sections):
            symbol = relocs[0].symbol
            base = relocs[0].addend + (symbol.value if symbol.type != elfimage.STT_SECTION else 0)
            rows = {r.offset: r for r in self.obj.relocs.get(symbol.shndx, [])}

            def entries():
                section = self.obj.sections[symbol.shndx]
                for i in range(4096):
                    offset = base + 8 * i
                    if offset < 0 or offset + 8 > section.size:
                        return
                    r = rows.get(offset)
                    if r is None or r.type != 1:  # R_X86_64_64, a complete pointer relocation
                        yield None
                        continue
                    target = r.addend + (r.symbol.value if r.symbol.type != elfimage.STT_SECTION else 0)
                    if r.symbol.shndx == self.section_index and start <= target < end:
                        yield target
                        continue
                    name = (self.funcs_by_section.get(r.symbol.shndx, {}).get(target)
                            if r.symbol.defined else r.symbol.name if target == 0 else None)
                    resolved = self.resolve(name) if name else None
                    token = self.name_at(resolved, "jmp") if resolved is not None and self.name_at else None
                    if token and token == name:
                        yield "external:" + token
                    else:
                        yield None
            return self.jump_table(k, entries(), table.group(2), start, end, offsets, insns)
        m = re.match(r"^([0-9a-f]+) <([^>]+)>$", operands)
        if m and mnemonic.startswith(("j", "call", "loop")):
            if relocs:
                r = relocs[0]
                offset = r.addend + (nxt - r.offset) if r.type in PC_RELATIVE else r.addend
                if r.symbol.name and r.symbol.name == getattr(self, "current", None) and offset == 0:
                    # Direct recursion: the original side sees a branch to its own entry.
                    return f"{mnemonic} {self.branch(k, start, start, end, offsets)}"
                return f"{mnemonic} {self.target_name(r.symbol, offset, mnemonic)}"
            target = int(m.group(1), 16)
            label = self.branch(k, target, start, end, offsets)
            if label:
                return f"{mnemonic} {label}"
            func = self.funcs_by_section.get(self.section_index, {}).get(target)
            return f"{mnemonic} {func or hex(target)}"
        for r in relocs:
            if r.type in PC_RELATIVE:
                name = self.target_name(r.symbol, r.addend + (nxt - r.offset), memory_mnemonic(mnemonic, operands), mnemonic.startswith("lea"))
                operands = re.sub(r"-?0x[0-9a-f]+\(%rip\)", lambda _: f"[{name}](%rip)", operands, count=1)
            elif r.type in ABSOLUTE:
                imm_last = r.offset == nxt - 4 and "$" in operands
                name = self.target_name(r.symbol, r.addend, memory_mnemonic(mnemonic, operands), imm_last or mnemonic.startswith("lea"))
                if imm_last:
                    operands = re.sub(r"\$0x[0-9a-f]+", lambda _: f"$[{name}]", operands, count=1)
                else:
                    operands = re.sub(r"(?<![\w%$])0x[0-9a-f]+(?=\()", lambda _: f"[{name}]", operands, count=1)
        return f"{mnemonic} {operands}".strip()


def object_functions(obj_path, resolve=None, name_at=None, globalized=()):
    obj = elfimage.load_object(obj_path)
    frames = objdiff_eh.inspect(obj, relocatable=True)
    text = run_objdump([str(obj_path)])
    sections = {}
    current = None
    for line in text.splitlines():
        m = re.match(r"^Disassembly of section (.+):$", line)
        if m:
            current = m.group(1)
            sections[current] = []
            continue
        if current is not None:
            sections[current].append(line)
    parsed = {name: parse_insns("\n".join(lines)) for name, lines in sections.items()}
    addresses = {name: [i[0] for i in insns] for name, insns in parsed.items()}
    by_name = {s.name: s.index for s in obj.sections}
    side = ObjectSide(obj, resolve, name_at)
    result = {}
    for sym in obj.symbols:
        if sym.type != elfimage.STT_FUNC or not sym.defined:
            continue
        section = obj.sections[sym.shndx]
        positions = addresses.get(section.name, [])
        insns = parsed.get(section.name, [])[bisect.bisect_left(positions, sym.value):
                                            bisect.bisect_left(positions, sym.value + sym.size)]
        side.prepare(by_name[section.name])
        side.current = sym.name
        bind = elfimage.STB_LOCAL if sym.name in globalized else sym.bind
        norm = side.normalize(insns, sym.value, sym.value + sym.size)
        reasons = list(dict.fromkeys(side.unverified))
        eh = frames.reason(sym.value, sym.size, sym.shndx)
        if eh:
            reasons.append(eh)
        result[sym.name] = {"size": sym.size, "bind": bind, "norm": norm,
                            "metadata_reasons": reasons,
                            "personalities": frames.personalities(sym.value, sym.size, sym.shndx),
                            "cleanup_eh": objdiff_eh.cleanup_signature(
                                obj, frames, sym.value, sym.size, insns, sym.shndx)}
    return result


def image_symbol_names(image):
    """Every symbol name of the original executable, its PLT included."""
    names = {s.name.split("@")[0] for s in list(image.symbols) + list(image.dynsyms) if s.name}
    return names | {n.split("@")[0] for n in image.plt.values()}


def unknown_members(db, original_names, symbols):
    """Symbols naming a member of a game class the original does not have: a wrong
    signature (constness, reference, parameter type) or an invented method."""
    out = []
    for name in symbols:
        if name in original_names:
            continue
        m = re.match(r"_ZNK?(\d+)", name)
        scope = m and name[m.end():m.end() + int(m.group(1))]
        if scope and scope in db["classes"] and scope not in ("Ogre", "CEGUI", "std", "ParticleUniverse"):
            out.append(name)
    return sorted(set(out))


def known_overloads(db, mangled):
    """Demangled signatures the original has for the class member `mangled` names."""
    m = re.match(r"_ZNK?(\d+)", mangled)
    scope = mangled[m.end():m.end() + int(m.group(1))]
    rest = mangled[m.end() + int(m.group(1)):]
    n = re.match(r"(\d+)", rest)
    method = rest[n.end():n.end() + int(n.group(1))] if n else None
    return sorted(f["demangled"] for f in db["functions"].values()
                  if f.get("scope") == scope and f.get("method") == method)


class Original:
    def __init__(self, db=None, elf=None):
        self.db = db or elfdb.load_db()
        self.image = elfimage.load(elf or elfdb.default_elf())
        self.side = OriginalSide(self.image, self.db)
        self.frames = objdiff_eh.inspect(self.image)
        self.side.frames = self.frames
        self._normalization_key = _norm_key()
        self._literal_library_identity = self._normalization_key[1]
        self.side.library_identity = self._literal_library_identity
        self._lock = threading.RLock()  # the normalizer keeps per-function state
        self.by_name = {}
        for address, f in self.db["functions"].items():
            for name in f["names"]:
                self.by_name.setdefault(name, []).append(f)

    def _prepare_indexes(self):
        if "_global_data" in self.__dict__:
            return
        global_data, local_data = {}, {}
        for g in self.db["globals"]:
            address = int(g["address"], 16)
            if g["bind"] != "local":
                global_data.setdefault(g["name"], address)
            else:
                local_data.setdefault(g["file"], {})[g["name"]] = address
        imports = {n.split("@")[0]: a for a, n in self.image.plt.items()}
        for symbol in self.image.dynsyms:
            if symbol.defined and symbol.value and symbol.name:
                imports.setdefault(symbol.name.split("@")[0], symbol.value)
        disassembly = objdiff_disasm.OriginalInstructions(
            self.db, self.image, run_objdump, parse_insns,
            mode=os.environ.get("OTL_ORIGINAL_DISASM", "function"))
        self._local_data, self._imports = local_data, imports
        self._disassembly = disassembly
        self._global_data = global_data  # Publish the ready marker last.

    def _instructions(self, f):
        self._prepare_indexes()
        return self._disassembly.instructions(f)

    def symbol_names(self):
        with self._lock:
            if not hasattr(self, "_names"):
                self._names = image_symbol_names(self.image)
            return self._names

    def unknown_references(self, obj):
        return unknown_members(self.db, self.symbol_names(),
                               (s.name for s in elfimage.load_object(obj).symbols if not s.defined and s.name))

    def known_overloads(self, mangled):
        return known_overloads(self.db, mangled)

    def resolver(self, tu):
        # Original/db are immutable for this comparison session. Preserve the
        # old local-over-global and first-global-wins precedence without copying
        # the entire global table into every TU.
        with self._lock:
            self._prepare_indexes()
        local_data = self._local_data.get(tu["name"], {}) if tu else {}
        data, imports = self._global_data, self._imports

        def resolve(name):
            if name in local_data:
                return local_data[name]
            if name in data:
                return data[name]
            f = self.function(name, False, tu)
            if f and any(b != "local" for n, b in zip(f["names"], f["bind"]) if n == name):
                return int(f["address"], 16)
            f = self.function(name, True, tu)
            if f:
                return int(f["address"], 16)
            return imports.get(name)
        return resolve


    def function(self, name, local=False, tu=None):
        found = self.by_name.get(name) or []
        if local:
            # Local names (__tcf_0, _GLOBAL__I_..., static functions) repeat across TUs.
            found = [f for f in found if tu is not None and f["tu"] == tu["id"]]
        return found[0] if found else None

    def normalized(self, f):
        """Normalized original function; cached on disk (the original never changes)."""
        with self._lock:
            cache = self.__dict__.get("_norm_cache")
            # Do not adopt disk proofs made with a different library snapshot.
            if (hasattr(self, "_literal_library_identity")
                    and self._literal_library_identity != literal_library_identity()):
                cache = self.__dict__["_norm_cache"] = {}
                self.side.library_identity = None
            if cache is None:
                if hasattr(self, "_normalization_key"):
                    cache = _load_norm_cache(self._normalization_key)
                else:
                    cache = _load_norm_cache()
                self._norm_cache = cache
            key = self.image.sha256 + ":" + f["address"]
            if key not in cache:
                start = int(f["address"], 16)
                end = start + f["size"]
                insns = self._instructions(f)
                norm = self.side.normalize(insns, start, end)
                cache[key] = {"norm": norm, "metadata_reasons": list(dict.fromkeys(self.side.unverified)),
                              "literal_proofs": list(self.side.literal_proofs)}
                _NORM_DIRTY.add(key)
            return cache[key]["norm"]

    def metadata_reasons(self, f):
        with self._lock:
            self.normalized(f)
            reasons = list(self._norm_cache[self.image.sha256 + ":" + f["address"]]["metadata_reasons"])
            reason = self.frames.reason(int(f["address"], 16), f["size"])
            if reason:
                reasons.append(reason)
            return reasons

    def cleanup_eh(self, f):
        with self._lock:
            # The original's cleanup metadata is immutable just like its code.
            # Store the fully checked signature (including an unsupported None)
            # in the same ELF/parser-bound cache, not in a per-process-only dict.
            self.normalized(f)
            key = self.image.sha256 + ":" + f["address"]
            entry = self._norm_cache[key]
            if "cleanup_eh" not in entry:
                start = int(f["address"], 16)
                if self.frames.reason(start, f["size"]) != "EH LSDA equivalence unverified":
                    signature = None
                else:
                    insns = self._instructions(f)
                    signature = objdiff_eh.cleanup_signature(
                        self.image, self.frames, start, f["size"], insns)
                entry["cleanup_eh"] = signature
                _NORM_DIRTY.add(key)
            return entry["cleanup_eh"]



NORM_CACHE = Path(__file__).resolve().parents[2] / "build-decomp" / "db" / "orig-normalized.pickle"
_NORM_DIRTY = set()
NORMALIZER_VERSION = 3


def _norm_key():
    # Normalization depends on this file, the database and the ELF image reader.
    here = Path(__file__).resolve().parent
    return [NORMALIZER_VERSION, literal_library_identity()] + [hashlib.sha256(p.read_bytes()).hexdigest()
                                   for p in (here / "objdiff.py", here / "elfimage.py", here / "objdiff_eh.py", here / "objdiff_disasm.py", here / "objdiff_literal_flow.py",
                                             here / "objdiff_saved_argument.py", here / "objdiff_literal_frames.py",
                                             here / "objdiff_null_field.py", here / "objdiff_wcslen_append.py",
                                             NORM_CACHE.parent / "elfdb.json") if p.exists()]


def _load_norm_cache(expected_key=None):
    import pickle
    try:
        data = pickle.loads(NORM_CACHE.read_bytes())
        if data.get("key") == (expected_key if expected_key is not None else _norm_key()):
            return data["functions"]
    except (OSError, ValueError, EOFError, pickle.UnpicklingError, AttributeError):
        pass
    return {}


def save_norm_cache(original):
    # A mid-session library change cannot relabel old proofs with the new key.
    if (hasattr(original, "_literal_library_identity")
            and original._literal_library_identity != literal_library_identity()):
        return
    import pickle
    cache = original.__dict__.get("_norm_cache")
    if cache and _NORM_DIRTY:
        # Freeze the label with the session, rather than hashing a dependency
        # again after checking it (which could relabel A proofs with a B key).
        key = getattr(original, "_normalization_key", None)
        if key is None:
            key = _norm_key()
        if (hasattr(original, "_literal_library_identity")
                and key[1] != original._literal_library_identity):
            return
        payload = pickle.dumps({"key": key, "functions": cache})
        temporary = None
        try:
            with tempfile.NamedTemporaryFile(dir=NORM_CACHE.parent,
                                             prefix=NORM_CACHE.name + ".",
                                             suffix=".tmp", delete=False) as stream:
                temporary = Path(stream.name)
                stream.write(payload)
            os.replace(temporary, NORM_CACHE)
        finally:
            if temporary is not None:
                temporary.unlink(missing_ok=True)
        _NORM_DIRTY.clear()


def tu_for_source(db, source):
    name = Path(source).name
    matches = [t for t in db["tus"] if t["name"].lower() == name.lower()]
    return matches[0] if len(matches) == 1 else None


LOCAL_DIRECTIVE = re.compile(r"^\s*\.local\s+(\S+)\s*$")
GLOBAL_LABEL = re.compile(r"^([A-Za-z_][\w.$]*):\s*$")


def globalize_locals(text):
    """Make file-local symbols global so relocations keep symbol+addend (codegen unchanged)."""
    names = set()
    out = []
    declared = set(re.findall(r"^\s*\.(?:globl|weak)\s+(\S+)", text, re.M))
    for line in text.splitlines():
        m = LOCAL_DIRECTIVE.match(line) if line.lstrip().startswith(".local") else None
        if m:
            names.add(m.group(1))
            out.append(f"\t.globl\t{m.group(1)}")
            continue
        m = GLOBAL_LABEL.match(line) if line.rstrip().endswith(":") else None
        if m and m.group(1) not in declared:
            names.add(m.group(1))
            out.append(f"\t.globl\t{m.group(1)}")
        out.append(line)
    return "\n".join(out) + "\n", names


def compile_for_diff(source, tmp, extra=(), quiet=False):
    asm = toolchain.compile_source(source, Path(tmp) / "unit.s", extra, assembly=True, quiet=quiet)
    text, globalized = globalize_locals(Path(asm).read_text())
    patched = Path(tmp) / "unit.global.s"
    patched.write_text(text)
    return toolchain.assemble(patched, Path(tmp) / "unit.o"), globalized


def code_digest(norm):
    """Progress fingerprint of normalized instructions, not full object identity.

    Acceptance evidence must use object_digest, which includes data, EH and
    relocations as well as code.
    """
    return hashlib.sha256("\n".join(norm).encode()).hexdigest()[:16]


def compiled_identity(source, original, extra=(), quiet=False):
    """Complete object identity and unknown references, without function analysis.

    For verifying live paths against an already validated object. This is not
    MATCH or behavioral acceptance of a new object: data/EH/relocations must be
    byte-identical to the one whose functions were checked.
    """
    with tempfile.TemporaryDirectory(prefix="otl-identity-") as tmp:
        obj, _ = compile_for_diff(source, tmp, extra, quiet)
        digest = hashlib.sha256(Path(obj).read_bytes()).hexdigest()
        unknown = original.unknown_references(obj)
    return {"object_digest": digest,
            "unknown": [{"name": n, "known": original.known_overloads(n)} for n in unknown]}


def compare_source(source, original, show=None, extra=(), quiet=False, *, scores=True):
    """quiet: compiler errors go into the SystemExit message instead of stderr.

    scores=False omits cosmetic DIFF similarity percentages, never code/data/EH
    checks. Explicit diagnostics retain the original exact score calculation.
    """
    tu = tu_for_source(original.db, source)
    with tempfile.TemporaryDirectory(prefix="otl-diff-") as tmp:
        obj, globalized = compile_for_diff(source, tmp, extra, quiet)
        object_digest = hashlib.sha256(Path(obj).read_bytes()).hexdigest()
        ours = object_functions(obj, original.resolver(tu), original.side.name_at, globalized)
        unknown = original.unknown_references(obj)
    rows = []
    seen = set()
    for name, mine in sorted(ours.items()):
        f = original.function(name, mine["bind"] == elfimage.STB_LOCAL, tu)
        if not f:
            rows.append({"name": name, "status": "EXTRA", "size": mine["size"],
                         "object_digest": object_digest})
            continue
        theirs = original.normalized(f)
        metadata_reasons = list(dict.fromkeys(mine["metadata_reasons"] + original.metadata_reasons(f)))
        if mine["personalities"] != original.frames.personalities(int(f["address"], 16), f["size"]):
            metadata_reasons.append("EH personality differs")
        cleanup_equal = (mine.get("cleanup_eh") is not None
                         and mine["cleanup_eh"] == original.cleanup_eh(f))
        if cleanup_equal:
            metadata_reasons = [reason for reason in metadata_reasons
                                if reason != "EH LSDA equivalence unverified"]
        seen.add(f["address"])
        if mine["norm"] == theirs and not metadata_reasons:
            status, score = "MATCH", 1.0
        else:
            score = difflib.SequenceMatcher(None, mine["norm"], theirs, autojunk=False).ratio() if scores else None
            status = "DIFF"
        row = {"name": name, "demangled": f["demangled"], "address": f["address"], "status": status,
               "size": mine["size"], "original_size": f["size"],
               "weak": mine["bind"] == elfimage.STB_WEAK, "code": code_digest(mine["norm"]),
               "object_digest": object_digest}
        if metadata_reasons:
            row["metadata_reasons"] = metadata_reasons
        if cleanup_equal:
            row["eh_verified"] = "gcc447-cleanup-v1"
        if score is not None:
            row["score"] = round(score, 4)
        rows.append(row)
        if show and (show == "all" or show in (name, f["demangled"])):
            print(f"--- ours {name}\n+++ original {f['address']} {f['demangled']}")
            for line in difflib.unified_diff(mine["norm"], theirs, lineterm="", n=1000):
                if not line.startswith(("---", "+++")):
                    print(line)
    if tu:
        for address, f in original.db["functions"].items():
            if f["tu"] == tu["id"] and address not in seen and f["kind"] not in ("compiler", "inline_or_template"):
                rows.append({"name": f["mangled"], "demangled": f["demangled"], "address": address,
                             "status": "MISSING", "original_size": f["size"], "object_digest": object_digest})
    return {"source": str(Path(source).resolve().relative_to(ROOT)) if Path(source).resolve().is_relative_to(ROOT) else str(source),
            "tu": tu["name"] if tu else None, "functions": rows,
            "object_digest": object_digest,
            "unknown": [{"name": n, "known": original.known_overloads(n)} for n in unknown]}


def report(result):
    print(f"{result['source']}  (original TU: {result['tu'] or '?'})")
    for row in result["functions"]:
        label = row.get("demangled") or row["name"]
        score = f"{row['score'] * 100:5.1f}%" if "score" in row else "     "
        weak = " (inline)" if row.get("weak") else ""
        print(f"  {row['status']:7} {score} {row.get('address', ''):>9} {label}{weak}")
        for reason in row.get("metadata_reasons", []):
            print(f"          {reason}")
    counts = {}
    for row in result["functions"]:
        counts[row["status"]] = counts.get(row["status"], 0) + 1
    for ref in result.get("unknown", []):
        print(f"  UNKNOWN {ref['name']}: not in the original; it has: {'; '.join(ref['known']) or 'no such member'}")
    print("  " + ", ".join(f"{k} {v}" for k, v in sorted(counts.items())))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("sources", nargs="*", type=Path)
    parser.add_argument("--all", action="store_true", help="every decomp/src/**/*.cpp")
    parser.add_argument("--show", help="mangled/demangled name or 'all': print normalized diff")
    parser.add_argument("--json", type=Path)
    parser.add_argument("--elf", type=Path, default=None)
    args = parser.parse_args()
    sources = list(args.sources)
    if args.all:
        sources += sorted(SRC.rglob("*.cpp"))
    if not sources:
        parser.error("no sources")
    original = Original(elf=args.elf)
    results = [compare_source(s, original, args.show) for s in sources]
    save_norm_cache(original)
    for r in results:
        report(r)
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps({"schema": 1, "elf": original.image.sha256, "units": results}, indent=1))
    bad = sum(1 for r in results for f in r["functions"] if f["status"] == "DIFF")
    return 1 if bad and not args.show else 0


if __name__ == "__main__":
    sys.exit(main())
