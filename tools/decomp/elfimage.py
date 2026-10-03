"""Read-only ELF64 reader for the original Torchlight executable.

Parses sections, the full .symtab in file order (including STT_FILE groups),
.dynsym, dynamic relocations and the PLT. No third-party packages.
"""
from __future__ import annotations

from dataclasses import dataclass, field
import hashlib
from pathlib import Path
import struct
import subprocess

ORIGINAL_SHA256 = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"

STT_NOTYPE, STT_OBJECT, STT_FUNC, STT_SECTION, STT_FILE = 0, 1, 2, 3, 4
STB_LOCAL, STB_GLOBAL, STB_WEAK = 0, 1, 2
SHN_UNDEF, SHN_ABS = 0, 0xFFF1
R_X86_64_64, R_X86_64_COPY, R_X86_64_GLOB_DAT, R_X86_64_JUMP_SLOT = 1, 5, 6, 7


@dataclass
class Section:
    index: int
    name: str
    type: int
    flags: int
    addr: int
    offset: int
    size: int
    link: int
    info: int
    entsize: int


@dataclass
class Symbol:
    index: int
    name: str
    value: int
    size: int
    type: int
    bind: int
    other: int
    shndx: int
    file: str | None = None  # STT_FILE group for local symbols

    @property
    def defined(self):
        return self.shndx != SHN_UNDEF


@dataclass
class Reloc:
    offset: int
    type: int
    symbol: str
    addend: int


@dataclass
class Image:
    path: Path
    data: bytes
    sha256: str
    sections: list[Section] = field(default_factory=list)
    symbols: list[Symbol] = field(default_factory=list)
    dynsyms: list[Symbol] = field(default_factory=list)
    relocs: dict[int, Reloc] = field(default_factory=dict)
    plt: dict[int, str] = field(default_factory=dict)
    segments: list[tuple] = field(default_factory=list)

    def section(self, name):
        for section in self.sections:
            if section.name == name:
                return section
        raise KeyError(name)

    def section_at(self, address):
        for section in self.sections:
            if section.addr and section.addr <= address < section.addr + section.size:
                return section
        return None

    def read(self, address, size):
        for kind, _, offset, vaddr, _, filesz, _, _ in self.segments:
            if kind == 1 and vaddr <= address and address + size <= vaddr + filesz:
                start = offset + address - vaddr
                return self.data[start:start + size]
        raise ValueError(f"not file-backed: {address:#x}+{size:#x}")

    def u64(self, address):
        return struct.unpack("<Q", self.read(address, 8))[0]

    def i64(self, address):
        return struct.unpack("<q", self.read(address, 8))[0]

    def u32(self, address):
        return struct.unpack("<I", self.read(address, 4))[0]

    def cstring(self, address, limit=4096):
        out = bytearray()
        for i in range(limit):
            byte = self.read(address + i, 1)
            if byte == b"\0":
                return out.decode("latin-1")
            out += byte
        raise ValueError(f"unterminated string at {address:#x}")


def _parse_symbols(data, sections, symtab, track_files):
    strtab = sections[symtab.link]
    result = []
    current_file = None
    for i in range(symtab.size // 24):
        name_off, info, other, shndx, value, size = struct.unpack_from(
            "<IBBHQQ", data, symtab.offset + i * 24)
        end = data.index(b"\0", strtab.offset + name_off)
        name = data[strtab.offset + name_off:end].decode("latin-1")
        sym = Symbol(i, name, value, size, info & 0xF, info >> 4, other, shndx)
        if track_files:
            if sym.type == STT_FILE:
                current_file = name
            elif sym.bind == STB_LOCAL and i:
                sym.file = current_file
        result.append(sym)
    return result


def load(path, require_original=True):
    path = Path(path).resolve()
    data = path.read_bytes()
    sha = hashlib.sha256(data).hexdigest()
    if require_original and sha != ORIGINAL_SHA256:
        raise ValueError(f"unsupported ELF {path}: sha256 {sha}")
    if data[:6] != b"\x7fELF\x02\x01":
        raise ValueError("expected little-endian ELF64")
    image = Image(path, data, sha)
    phoff, shoff = struct.unpack_from("<QQ", data, 32)
    phentsize, phnum, shentsize, shnum, shstrndx = struct.unpack_from("<HHHHH", data, 54)
    image.segments = [struct.unpack_from("<IIQQQQQQ", data, phoff + i * phentsize)
                      for i in range(phnum)]
    raw = [struct.unpack_from("<IIQQQQIIQQ", data, shoff + i * shentsize) for i in range(shnum)]
    shstr = raw[shstrndx][4]
    for i, (name, typ, flags, addr, off, size, link, info, _, entsize) in enumerate(raw):
        end = data.index(b"\0", shstr + name)
        image.sections.append(Section(i, data[shstr + name:end].decode(), typ, flags, addr,
                                      off, size, link, info, entsize))
    by_type = {s.name: s for s in image.sections}
    if ".symtab" in by_type:
        image.symbols = _parse_symbols(data, image.sections, by_type[".symtab"], True)
    if ".dynsym" in by_type:
        image.dynsyms = _parse_symbols(data, image.sections, by_type[".dynsym"], False)
    for name in (".rela.dyn", ".rela.plt"):
        if name not in by_type:
            continue
        section = by_type[name]
        for i in range(section.size // 24):
            offset, info, addend = struct.unpack_from("<QQq", data, section.offset + i * 24)
            symbol = image.dynsyms[info >> 32].name if info >> 32 else ""
            image.relocs[offset] = Reloc(offset, info & 0xFFFFFFFF, symbol, addend)
    if ".plt" in by_type and ".rela.plt" in by_type:
        plt = by_type[".plt"]
        rela = by_type[".rela.plt"]
        for i in range(rela.size // 24):
            offset, info, _ = struct.unpack_from("<QQq", data, rela.offset + i * 24)
            # Classic lazy PLT: entry 0 is the resolver stub, 16 bytes per entry.
            image.plt[plt.addr + 16 * (i + 1)] = image.dynsyms[info >> 32].name
    return image


@dataclass
class ObjReloc:
    offset: int
    type: int
    symbol: Symbol
    addend: int


@dataclass
class Object:
    """A relocatable object (ET_REL) produced by the decomp toolchain."""
    path: Path
    data: bytes
    sections: list[Section] = field(default_factory=list)
    symbols: list[Symbol] = field(default_factory=list)
    relocs: dict[int, list[ObjReloc]] = field(default_factory=dict)  # by target section index

    def section_bytes(self, index):
        s = self.sections[index]
        if s.type == 8:  # NOBITS
            return bytes(s.size)
        return self.data[s.offset:s.offset + s.size]


def load_object(path):
    path = Path(path)
    data = path.read_bytes()
    if data[:6] != b"\x7fELF\x02\x01":
        raise ValueError("expected little-endian ELF64 object")
    obj = Object(path, data)
    shoff = struct.unpack_from("<Q", data, 40)[0]
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 58)
    raw = [struct.unpack_from("<IIQQQQIIQQ", data, shoff + i * shentsize) for i in range(shnum)]
    shstr = raw[shstrndx][4]
    for i, (name, typ, flags, addr, off, size, link, info, _, entsize) in enumerate(raw):
        end = data.index(b"\0", shstr + name)
        obj.sections.append(Section(i, data[shstr + name:end].decode(), typ, flags, addr, off, size,
                                    link, info, entsize))
    symtab = next(s for s in obj.sections if s.type == 2)
    obj.symbols = _parse_symbols(data, obj.sections, symtab, False)
    for s in obj.sections:
        if s.type == 4:  # SHT_RELA
            rows = []
            for i in range(s.size // 24):
                offset, info, addend = struct.unpack_from("<QQq", data, s.offset + i * 24)
                rows.append(ObjReloc(offset, info & 0xFFFFFFFF, obj.symbols[info >> 32], addend))
            obj.relocs[s.info] = rows
    return obj


def demangle(names):
    """Batch-demangle with binutils c++filt; returns dict mangled -> readable."""
    names = list(dict.fromkeys(names))
    if not names:
        return {}
    output = subprocess.run(["c++filt"], input="\n".join(names) + "\n", text=True,
                            capture_output=True, check=True).stdout.splitlines()
    if len(output) != len(names):
        raise RuntimeError("c++filt output size mismatch")
    return dict(zip(names, output))
