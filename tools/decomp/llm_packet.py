#!/usr/bin/env python3
"""One short task for the model: the exact symbol, its header, its ASM, its draft.

    from llm_packet import build_prompt
    prompt = build_prompt(f, root=root, tu="RunicCore.cpp", headers={"CRunicCore": "RunCore.h"},
                          draft=converted, idioms=IDIOMS.read_text(), examples=rendered)

The model never reads the repository (llm_loop.py): everything it gets is packed here, so this
only ever reads the owning class header, one disassembly and the texts the caller passes in.
No database, no types.json, no Ghidra: build_prompt() reads the header and packet
ASM, or asks objdump for just the requested range of the original ELF.

Which header goes in is deliberate: only the one that owns the class, whole. A trimmed class body
(a field left out, a virtual moved, a declaration dropped) compiles into a different object, so
there is no per-field trimming here. A function without a class scope (free or static) gets every
mapped header instead, bounded by the budget.

ASM comes from build-decomp/scaffold/<TU>/asm/<address>_*.s when the packet holds exactly one file
for that address, otherwise from objdump of that address range alone (scaffold.disassemble).

max_chars is a hard budget. The optional examples go first; if the mandatory part still does not
fit, ValueError names the sizes instead of quietly cutting the ASM, a declaration or the draft.
"""
from __future__ import annotations

from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import scaffold  # noqa: E402

NO_ASM = "(no ASM for this function: the scaffold packet has none and objdump could not run)"
NO_DRAFT = "(no Ghidra draft for this function)"
DEFAULT_MAX_CHARS = 131072

RULES = (
    "Rules: C++98, the GNU++98 dialect GCC 4.4.7 understands; use the names of the header above; call "
    "the other functions normally (std::wstring, TArrayList methods instead of inlined internals, objects "
    "through their classes); globals are declared in GenGlobals.h, other classes in their own headers; "
    "add no #include; answer with exactly one fenced ```cpp block that holds this one definition and "
    "nothing else; never bind a symbol with an __asm__ label and never leave a stub or a placeholder body."
)


# -- names and addresses ---------------------------------------------------


def plain_name(name, what):
    """A bare file name: no directory, no traversal, no hidden file. Raises otherwise."""
    if not isinstance(name, str) or not name.strip():
        raise ValueError(f"{what}: expected a file name, got {name!r}")
    if any(c in name for c in ("/", "\\", "\0")) or name in (".", "..") or name.startswith("."):
        raise ValueError(f"{what}: {name!r} must be a plain file name inside the tree, not a path")
    return name


def include_dir(root):
    return Path(root) / "decomp" / "include"


def header_path(root, name):
    """root/decomp/include/<name>, and nothing outside it."""
    path = include_dir(root) / plain_name(name, "header")
    base = include_dir(root).resolve()
    if path.resolve().parent != base:
        raise ValueError(f"header: {name!r} resolves outside {base}")
    return path


def asm_dir(root, tu):
    return Path(root) / "build-decomp" / "scaffold" / plain_name(tu, "TU") / "asm"


def address_of(f):
    """The function address as the canonical nonzero hex the packet and the ELF use."""
    raw = f.get("address")
    if isinstance(raw, int):
        value = raw
    else:
        text = str(raw).strip()
        try:
            value = int(text, 16)
        except ValueError:
            raise ValueError(f"address: {raw!r} is not a hex address") from None
    if value <= 0:
        raise ValueError(f"address: {raw!r} is not a nonzero ELF address")
    return f"0x{value:x}"


def owning_class(f):
    scope = f.get("scope") or ""
    return scope.split("::")[0] if scope else ""


# -- header selection ------------------------------------------------------


def _unique(names):
    seen, out = set(), []
    for name in names:
        if name not in seen:
            seen.add(name)
            out.append(name)
    return out


def _mapped(headers, cls):
    value = headers.get(cls) if cls else None
    if value is None:
        return []
    return [value] if isinstance(value, str) else list(value)


def header_names(f, headers):
    """Header basenames for this function, in packet order: the owning class, or all of them
    for a function without a class scope."""
    cls = owning_class(f)
    if cls:
        return _unique(_mapped(headers, cls))
    return _unique([name for value in headers.values()
                    for name in ([value] if isinstance(value, str) else value)])


# -- ASM -------------------------------------------------------------------


def asm_of(root, tu, f):
    """The function's disassembly: the scaffold packet file when there is exactly one for the
    address, otherwise objdump over that address range only."""
    address = address_of(f)
    packet = asm_dir(root, tu)
    found = sorted(packet.glob(f"{address}_*.s")) if packet.is_dir() else []
    if len(found) == 1:
        text = found[0].read_text(errors="replace")
        stamp = f"{int(address, 16):016x}"
        return text[text.find(stamp):] if stamp in text else text
    if len(found) > 1:
        print(f"  {tu} {address}: {len(found)} ASM files in the packet, disassembling instead", flush=True)
    try:
        return scaffold.disassemble(elfdb.default_elf(), dict(f, address=address))
    except Exception as error:  # noqa: BLE001 - the draft is still worth sending
        print(f"  {tu} {address}: objdump failed ({error})", flush=True)
        return ""


# -- the prompt ------------------------------------------------------------


def _task(f, address):
    demangled = f.get("demangled") or f.get("mangled") or address
    lines = [f"Write the C++98 definition of `{demangled}`."]
    symbol = f.get("mangled")
    lines.append("The original symbol is "
                 + (f"`{symbol}`" if symbol else "this one")
                 + f" at {address}, {f.get('size', '?')} bytes"
                 + (f", kind {f['kind']}" if f.get("kind") else "") + ".")
    if f.get("vslots"):
        slots = ", ".join(f"{v.get('class')}[{v.get('slot')}]" for v in f["vslots"][:4]
                          if isinstance(v, dict))
        if slots:
            lines.append(f"Vtable slots of the original: {slots}.")
    lines.append("A mangled name encodes neither the return type nor `static`, and nothing here proves the "
                 "ABI: read both out of the machine code and the callers instead of assuming them.")
    return "\n".join(lines)


def _header_block(root, wanted, owned):
    """Every chosen header in full: fields, vtable slots and declarations are never cut."""
    blocks, missing = [], []
    for name in wanted:
        path = header_path(root, name)
        if path.exists():
            blocks.append(f"```cpp\n{path.read_text(errors='replace').rstrip()}\n```")
        else:
            missing.append(name)
    if not blocks:
        return "", missing
    what = ("Class header, whole, as it is in decomp/include:" if owned
            else "Headers of this TU, whole, as they are in decomp/include:")
    return f"{what}\n" + "\n\n".join(blocks), missing


def build_prompt(f, *, root, tu, headers, draft, idioms, examples="", stale_note="", max_chars=DEFAULT_MAX_CHARS):
    """The whole task as one string. See the module docstring for what goes in and why."""
    root = Path(root)
    address = address_of(f)
    plain_name(tu, "TU")  # the name also builds the packet path asm_of() uses
    owned = bool(owning_class(f))
    wanted = header_names(f, headers)
    headers_text, missing = _header_block(root, wanted, owned)
    shown = [name for name in wanted if name not in missing]
    others = [name for name in _unique([h for v in headers.values()
                                        for h in ([v] if isinstance(v, str) else v)])
              if name not in shown and header_path(root, name).exists()]
    asm = asm_of(root, tu, f)
    draft_text = (draft or "").strip()

    # Same text first for every call of a class (the provider caches the prefix), then this
    # function: idioms, header, other header names, optional examples, task, ASM, draft.
    fixed = [idioms.rstrip(), headers_text]
    if others:
        fixed.append("Other headers of this TU, by name only, if you need them: " + ", ".join(others))
    if missing:
        fixed.append("Headers this function needs that are not in decomp/include yet: "
                     + ", ".join(missing))
    tail = [_task(f, address),
            f"Original machine code (objdump of {address}):\n```\n{asm.strip() or NO_ASM}\n```",
            f"Ghidra decompilation (a draft; types and temporaries may be wrong{stale_note}):\n"
            f"```cpp\n{draft_text or NO_DRAFT}\n```",
            RULES]

    mandatory = "\n\n".join(part for part in fixed + tail if part)
    if examples:
        optional = ("Accepted functions of the game next to their drafts, for the style and the idioms:\n\n"
                    f"{examples.strip()}")
        full = "\n\n".join(part for part in fixed + [optional] + tail if part)
        if len(full) <= max_chars:
            return full
    if len(mandatory) > max_chars:
        raise ValueError(f"{f.get('demangled') or address}: the mandatory part is {len(mandatory)} chars, "
                         f"over the {max_chars} budget (idioms {len(idioms)}, headers {len(headers_text)}, "
                         f"ASM {len(asm)}, draft {len(draft_text)}); raise max_chars or map fewer headers")
    return mandatory
