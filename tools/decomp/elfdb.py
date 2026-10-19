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
FLTK_C_FILES = {"utf8input.c", "fl_utf.c", "flstring.c", "is_spacing.c", "case.c", "utf8utils.c", "keysym2ucs.c", "vsnprintf.c",
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


WIN_MOUSE_HELPERS = (
    ('_Z15UpdateCursorPosll', 0xf63210, 15, '48893de9ac5e00488935eaac5e00c3'),
    ('_Z12GetCursorPosP5POINT', 0xf63220, 24, '488b05d9ac5e00488907488b05d7ac5e004889470831c0c3'),
    ('_Z12SetCursorPosii', 0xf63240, 3, '31c0c3'),
    ('_Z14UpdateKeyStatejb', 0xf63250, 10, '89ff4088b700de5401c3'),
    ('_Z16GetAsyncKeyStatej', 0xf63260, 18, '89ff80bf00de54010119c0f7d066250080c3'),
    ('_Z11GetKeyStatej', 0xf63280, 18, '89ff80bf00de54010119c0f7d066250080c3'),
    ('_Z24LinuxMapVirtual2Scancodej', 0xf632a0, 10, '89ff8b04bda0380201c3'),
    ('_Z13ClearKeyStatev', 0xf632b0, 19, 'ba00de5401b92000000031c04889d7f348abc3'),
)


def assign_win_mouse_helpers(image, files, funcs):
    """Resolve the pinned input block from exact STT_FILE-owned local data.

    There is no local function anchor in WinMouseAndKeys.cpp, so the general
    position tie-break assigns this whole block to the preceding LinuxUtils.
    Keep the correction bounded to the original ELF and its unchanged block.
    """
    if image.sha256 != elfimage.ORIGINAL_SHA256:
        return 0
    owners = {name: [f for f in files if f["name"] == name]
              for name in ("LinuxUtils.cpp", "WinMouseAndKeys.cpp", "ShellUtils.cpp")}
    if any(len(group) != 1 for group in owners.values()):
        return 0
    left, owner, right = (owners[name][0]["id"] for name in owners)
    if not left < owner < right:
        return 0
    required = {"_ZL6MouseX": (8, ".bss"), "_ZL6MouseY": (8, ".bss"),
                "_ZL9keyStates": (256, ".bss"), "_ZL12virt2scanMap": (892, ".rodata")}
    for name, (size, section) in required.items():
        symbols = [s for s in image.symbols if s.name == name]
        if (len(symbols) != 1 or symbols[0].bind != STB_LOCAL
                or symbols[0].type != STT_OBJECT or symbols[0].file != "WinMouseAndKeys.cpp"
                or symbols[0].size != size or image.sections[symbols[0].shndx].name != section):
            return 0
    block = WIN_MOUSE_HELPERS
    addresses = [address for name, address, size, code in block]
    # A new/foreign function inside the block, a stronger ownership claim, or
    # moved boundaries must return to investigation rather than bypass the DP.
    if sorted(a for a in funcs if addresses[0] <= a <= addresses[-1]) != addresses:
        return 0
    order = sorted(funcs)
    lo, hi = order.index(addresses[0]), order.index(addresses[-1])
    if lo == 0 or hi+1 == len(order) or funcs[order[lo-1]].get("tu") != left or funcs[order[hi+1]].get("tu") != right:
        return 0
    for name, address, size, code in block:
        f = funcs[address]
        if (f.get("mangled") != name or f.get("size") != size
                or f.get("tu") != left or f.get("tu_confidence") != "position-guess"
                or image.read(address, size) != bytes.fromhex(code)):
            return 0
    for address in addresses:
        funcs[address]["tu"] = owner
        funcs[address]["tu_confidence"] = "local-data-owner"
    return len(addresses)


import hashlib

FLTK_UTF_FUNCTIONS = (('gb2312_mbtowc', 16328704, 146, '44347da7bf2e89d3fd80197f0000432a4a7f69475c5a0cfa78c3ad2e73d3d0f1', 'utf8Input.c'), ('XConvertEucJpToUtf8', 16328864, 737, 'd7dac5f775cbc3792d6e1c7552cea77858d0c0e033c46a7d2e1b131861c48e18', 'utf8Input.c'), ('XConvertEucCnToUtf8', 16329616, 226, 'e14afa22542c071714247188cf2cc237be20219e6b29acd640086bf6622bc09c', 'utf8Input.c'), ('XConvertGb2312ToUtf8', 16329856, 278, '3e555a9f38e4861de20d50a34c7858f166f508619048057e254d7e193d6b4837', 'utf8Input.c'), ('XConvertCp936extToUtf8', 16330144, 176, '7365c75f2523de00bc3330489c39a71c117089b7d0a5dfe38b245f6f7f9f8389', 'utf8Input.c'), ('XConvertBig5ToUtf8', 16330320, 338, 'b38323f72782e70acd62e78eb2d525b769460ca5e36e43ccdfeffe85e682b085', 'utf8Input.c'), ('XConvertEucKrToUtf8', 16330672, 315, 'fe282090593b01b71bec2250388f89aface1e311dccb0e719df9a65dadf9a584', 'utf8Input.c'), ('XConvertEucTwToUtf8', 16330992, 214, 'd59823b5ebbc3c08587b2ab1644709c5e4f2159c1880b6a5cbc26d324d9e2229', 'utf8Input.c'), ('XConvertEucToUtf8', 16331216, 573, '165657e8261a60002041a86d6c4d6d2654340ffd53f98889ce50eebda33adfa0', 'utf8Input.c'), ('XUtf8LookupString', 16331792, 374, 'a2a13efd3deffebb9c8eb0f67aa59764f8117c1f00e163caf1ed3ba0d3f622d4', 'utf8Input.c'), ('XConvertUtf8ToUcs', 16332176, 513, '1957646e17c912b222d58e4ec1a1a038de2c44578312dc9bb578a84af4039a7b', 'utf8Utils.c'), ('XConvertUcsToUtf8', 16332704, 249, 'ad6122931b4380da28c7e15adf678595e7cc786ba3fcfd828f3fdbe784d08c19', 'utf8Utils.c'), ('XUtf8CharByteLen', 16332960, 19, '923f3173376bf470d8baef759e0e2871ca78cd456b035ae9e2f5653901abb5ec', 'utf8Utils.c'), ('XCountUtf8Char', 16332992, 65, '2539a97e73747cbd4dd0155affd587be9a85a1969fb735ab92a4395ee04ed98b', 'utf8Utils.c'), ('XFastConvertUtf8ToUcs', 16333072, 271, 'b053c80135359374884e48a67ff6fd86e7823626261aac72de4fec07bf4c2240', 'utf8Utils.c'), ('KeySymToUcs4', 16333344, 559, '450ee7089ca02374f1454c5632482a7a0eefef270d90e8b227e6505a3e722c0d', 'keysym2Ucs.c'), ('XKeysymToUcs', 16333904, 8, 'ab9e9916108b0f30b3b65dd91bf7e3518d63429a0e68744d5c3fdf8af85d167e', 'keysym2Ucs.c'), ('fl_utf8decode', 16333920, 424, 'ec37a4b01769fd0aa30a644a27fb1b2aa8e1e064fc090872db807ff539c5e92c', 'fl_utf.c'), ('fl_utf8fwd', 16334352, 118, '3d1ccb5d9caa6fb1525563bde731b601c965e0753b62138b5b6959ffb60fabb3', 'fl_utf.c'), ('fl_utf8back', 16334480, 118, 'fddf32240fd2be6a8ab720249fd8206fd2972576492d83e70b9ddde93b04925c', 'fl_utf.c'), ('fl_utf8bytes', 16334608, 46, '7bb78904c51e437c0d8edb4e9ca53c0c51e2d29c454f85fba9e2ab42aefb06c0', 'fl_utf.c'), ('fl_utf8encode', 16334656, 180, '1eb810b0ab581591a001d93e8779a1b9da198e864a75ad64e0d7e76c78ae41ec', 'fl_utf.c'), ('fl_ucs_to_Utf16', 16334848, 140, 'becddbb0aca68f0fde9efd3567582e81c523fd291de20863cbda4d42016c2d54', 'fl_utf.c'), ('fl_utf8toUtf16', 16334992, 357, '8a59128cc7d37ba6a4d6ade6f4489539dad2ee85c51db198297883fefae384b6', 'fl_utf.c'), ('fl_utf8towc', 16335360, 248, 'd327b60f92caca3fb81e472d91ec8814407bdd48ef0f185c7b570f2ffd8e8246', 'fl_utf.c'), ('fl_utf8toa', 16335616, 263, '5e5fffbd88dbedc41e07e1368191a518f73832d01e74a9837155329c35a63c53', 'fl_utf.c'), ('fl_utf8fromwc', 16335888, 405, 'b839a8bb147f2e9bcc55c6ac5698e722bbc643009be07be00de294c8aa28502a', 'fl_utf.c'), ('fl_utf8froma', 16336304, 204, '084a7c8bc24ccc8c2fbca20d0f02766c9f3a60ea16134765d406b4794addd709', 'fl_utf.c'), ('fl_utf8test', 16336512, 121, '971c02e85d9138619f183a53dd7f2f4d65e483c0b287db80de5db65a7ff908ae', 'fl_utf.c'), ('fl_wcwidth_', 16336640, 270, '0a124ab39d95222d3b8ca05d33c3fd780998f4a63e8c70181d6a43c7195f0ce0', 'fl_utf.c'), ('fl_wcwidth', 16336912, 56, '16852b19c40530a453f5cc141b00cd408114d30f52bb9de685c8f170befdc630', 'fl_utf.c'), ('fl_utf8locale', 16336976, 157, '048c81cbb2773e8525f7acea5c617434091700b562bc9e0458012ba7f1cb93ee', 'fl_utf.c'), ('fl_utf8from_mb', 16337136, 305, '52ff2748c3e9f1428a25ff71a95ddc7a93442964b5d2114fbd2ccce3a251305a', 'fl_utf.c'), ('fl_utf8to_mb', 16337456, 300, 'df6ec4e0a5b6c5120342ded3c452d0594ee1ddb379ef8fe1af73df0ae04ace67', 'fl_utf.c'))
FLTK_UTF_DATA = (('gb2312_2uni_page30', 16973248, 13536, 'd1b7999f10f4e67c2bae80eb56682c6d74dfcd542f3744edf2551ca6936e9e97', 'utf8Input.c', '.rodata'), ('gb2312_2uni_page21', 16971584, 1662, 'cac0a18abd4b66f9005e47c50907e94dc9e9bff3679c04b269fd9a6234d85593', 'utf8Input.c', '.rodata'), ('jisx0208_2uni_page21', 16944608, 1380, '12ddb1fc8bd60eee61eafa2189b75ccc731c6e579ae85912e095ededed5d356f', 'utf8Input.c', '.rodata'), ('jisx0212_2uni_page22', 16958816, 162, 'b9e1de3d33142560a44b9f0c087bba9f49c6372d3dde80eceefde8a09dcfe547', 'utf8Input.c', '.rodata'), ('jisx0208_2uni_page30', 16946016, 12796, '0fc2298445b24c1f477bd70967c16e7fbfbab49e63be794b9a37bbd4f5a5ac10', 'utf8Input.c', '.rodata'), ('jisx0212_2uni_page26', 16959008, 376, '8025df3028370b02cf531b727d225468dc577f5af067f0bfa80ded8b67af7e41', 'utf8Input.c', '.rodata'), ('jisx0212_2uni_page29', 16959392, 550, '224199e67607ff2eb1348fcd7d0b38b510a46a8bef6f19bfe206f42de21d6af5', 'utf8Input.c', '.rodata'), ('jisx0212_2uni_page30', 16959968, 11602, '4434f8cf02ce8fc185c0431f17a5e2ef66a69781377258774e3778ae43c11c79', 'utf8Input.c', '.rodata'), ('big5_2uni_pagea1', 16986784, 12242, '5330e8dde1e4720de4d7ba90845a9e78429da21e8211e3229c5660607cdf2b1e', 'utf8Input.c', '.rodata'), ('big5_2uni_pagec9', 16999040, 15304, '2173a175130c699cc96a820e252d2dfedeb1cb395055cd358c9f3a99e8bcb8aa', 'utf8Input.c', '.rodata'), ('ksc5601_2uni_page21', 17014368, 2230, 'a5b27a819fb173c757e86e39fbe6d9723d05842e3b63fc0549caeb2e026eb694', 'utf8Input.c', '.rodata'), ('ksc5601_2uni_page30', 17016608, 4700, '776ce8d3b0686291cbcba0b9121c3f59a457ff7400a45bc291ae684c24895a68', 'utf8Input.c', '.rodata'), ('ksc5601_2uni_page4a', 17021312, 9776, 'b2a3044161498fdeff1dc2b47a24e5ca44c687bae70b45236a124f4efb91283f', 'utf8Input.c', '.rodata'), ('keysym_to_unicode_2a1_2fe', 17031296, 188, '4cee9f360f17ea5edb5c56456a6bc085ae87235148b872fab6386a618b76bfe3', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_1a1_1ff', 17031104, 190, 'ca5447ef6e04e1507d715bc3e7584267fcf6996d693276cc6cf3beb758786ed1', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_4a1_4df', 17031680, 126, '39908b964a9210dabe9c54baeaa4aa7b61625ff355fa20fe9cac2f655f7df398', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_3a2_3fe', 17031488, 186, '6dea15acf8d8312f243eabee29c7cf356d7ec6b6938485b79b701c76e901043f', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_590_5fe', 17031808, 222, 'f3d833fa0e7c62e02aee74e01ddd1c20dd5f359828cdfb78b1987271d5ac9baa', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_680_6ff', 17032032, 256, '3b5d8483d5d76609c99eda2a8999f28c1039d45172a1e90a6d5046076b2bbc76', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_7a1_7f9', 17032288, 178, '16b38abcf1f9916f01e0ef76158b7fbaacacf89cd89640d643e6ec13e91f92fa', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_8a4_8fe', 17032480, 182, 'f5f4af2db3ecb98bcdf71090400d5f591efeea5752eca602050f68a418bbcb9b', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_9df_9f8', 17032672, 52, 'c929c0228aedbafb2ccae9d73a19a5d179e6314f6e77db4cd7f937029555e03e', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_aa1_afe', 17032736, 188, '44f07b366041e350412d7e8a75ed34df87b6444d8b9a678b780fa02e3da2ac77', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_cdf_cfa', 17032928, 56, '7b09f8c45ca841cef63d3f4cf7e0f5eb2d3d788e0d47d5eb6ca3c8e34036fb33', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_da1_df9', 17032992, 178, '149c0b452450fc768d79c0931858a45a20a1db69b4c172c1c9297acfaa2b11be', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_ea0_eff', 17033184, 192, 'ba30199cc7145b34c65319de87a0da3275db89ec7c93230fa65ed3b5239e2121', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_12a1_12fe', 17033376, 188, '49784a41328525f58a4ee9d62a62667375c11d282e36fdb610d7312d378cb605', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_13bc_13be', 17033564, 6, 'd691e5713005b2b2a3ea9349b65d05e1b51c33c1fde9546f2864d6aee534dec0', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_14a1_14ff', 17033600, 190, '7ff5fd6fd261d872d54437e21e6a6820af6204e34d402e8bbdf89df92229d84d', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_15d0_15f6', 17033792, 78, '63d5023fc66a0206102c0ee6f138c1faa7f73d5207a3c61ecb64b390fd34f75c', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_16a0_16f6', 17033888, 174, 'aca1bf2cde0ed4fd9b06e4c95ffd5f15bd264d27f11d68dd73f6947a1308059b', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_1e9f_1eff', 17034080, 194, '0e27167860b0567b48144c2ccf09c35d58f42bea783a5ee777f47c87a1f56450', 'keysym2Ucs.c', '.rodata'), ('keysym_to_unicode_20a0_20ac', 17034288, 26, '3758639380aea833b157ab17fb6046fcbf12d1e6ebd82f77ffa1adf6a2d5dc1c', 'keysym2Ucs.c', '.rodata'), ('cp1252', 17035488, 64, '7a250d67e391d3b0830b16b3705836244ec37c60e113c4c96bf082c404f2dc5f', 'fl_utf.c', '.rodata'), ('combining.7336', 17034336, 1136, 'f7d9ea2f673cf12fd228cae5e5a7f9d2c54dd78fa35e6b369053415f6629acb3', 'fl_utf.c', '.rodata'), ('ret.7209', 21115752, 4, '26b25d457597a7b0463f9620f666dd10aa2c4373a505967c7c8d70922a2d6ece', 'fl_utf.c', '.data'))


def assign_fltk_utf_sources(image, files, funcs):
    """Pinned native UTF block: actual C source files, never decomp wrappers.

    The generic position DP has only gb2312_mbtowc as a local function anchor;
    it assigns all34 to utf8Input.c across the three following empty C groups.
    Source/table and full native code identities bound this correction exactly.
    Completion accounting must retain all34 addresses as library-source targets.
    """
    if image.sha256 != elfimage.ORIGINAL_SHA256:
        return 0
    names = ("utf8Input.c", "utf8Utils.c", "keysym2Ucs.c", "fl_utf.c")
    groups = {n: [f for f in files if f["name"] == n] for n in names}
    if any(len(v) != 1 for v in groups.values()):
        return 0
    owners = {n: groups[n][0]["id"] for n in names}
    ids = list(owners.values())
    if ids != list(range(ids[0], ids[0]+4)):
        return 0
    addresses = [a for n,a,size,digest,owner in FLTK_UTF_FUNCTIONS]
    if sorted(a for a in funcs if addresses[0] <= a <= addresses[-1]) != addresses:
        return 0
    order = sorted(funcs)
    lo, hi = order.index(addresses[0]), order.index(addresses[-1])
    if (lo == 0 or hi+1 == len(order)
            or funcs[order[lo-1]].get("tu", ids[0]) >= ids[0]
            or funcs[order[hi+1]].get("tu", ids[-1]) <= ids[-1]):
        return 0
    for name,address,size,digest,owner in FLTK_UTF_FUNCTIONS:
        f = funcs[address]
        confidence = "local-symbol" if name == "gb2312_mbtowc" else "position-guess"
        if (f.get("mangled") != name or f.get("size") != size
                or f.get("tu") != ids[0] or f.get("tu_confidence") != confidence
                or hashlib.sha256(image.read(address,size)).hexdigest() != digest):
            return 0
    for name,address,size,digest,owner,section in FLTK_UTF_DATA:
        symbols = [s for s in image.symbols if s.name == name and s.file == owner]
        if (len(symbols) != 1 or symbols[0].bind != STB_LOCAL
                or symbols[0].type != STT_OBJECT or symbols[0].value != address
                or symbols[0].size != size
                or image.sections[symbols[0].shndx].name != section
                or hashlib.sha256(image.read(address,size)).hexdigest() != digest):
            return 0
    for name,address,size,digest,owner in FLTK_UTF_FUNCTIONS:
        funcs[address]["tu"] = owners[owner]
        if owner != names[0]:
            funcs[address]["tu_confidence"] = "pinned-library-source"
    return len(addresses)


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
            # Free-function namespaces live in a TU named after them with a prefix
            # (MATH:: in UtilitiesMath.cpp); upper-case scope = namespace, not a class.
            if cls.isupper() and len(cls) >= 4 and name_key(files[tu]["name"]).endswith(cls.lower()):
                return weight * 0.5
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

    assign_win_mouse_helpers(image, files, funcs)

    assign_fltk_utf_sources(image, files, funcs)

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
