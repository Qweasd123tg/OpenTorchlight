"""Read-only helpers for the inspected Linux ELF. No third-party packages."""

from dataclasses import dataclass
import hashlib
from pathlib import Path
import re
import struct
import subprocess


SUPPORTED_SHA256 = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"


@dataclass(frozen=True)
class Symbol:
    address: int
    size: int
    kind: str
    name: str


class Original:
    def __init__(self, path):
        self.path = Path(path).resolve()
        self.data = self.path.read_bytes()
        self.sha256 = hashlib.sha256(self.data).hexdigest()
        if self.sha256 != SUPPORTED_SHA256:
            raise ValueError(f"Unsupported original build: {self.sha256}")
        if self.data[:6] != b"\x7fELF\x02\x01":
            raise ValueError("Expected a little-endian ELF64 executable")
        phoff = struct.unpack_from("<Q", self.data, 32)[0]
        phsize, phcount = struct.unpack_from("<HH", self.data, 54)
        self.segments = [
            struct.unpack_from("<IIQQQQQQ", self.data, phoff + i * phsize)
            for i in range(phcount)
        ]
        output = subprocess.check_output(
            ["nm", "-S", "-C", "--defined-only", str(self.path)], text=True
        )
        self.symbols = []
        for line in output.splitlines():
            match = re.fullmatch(r"([0-9a-f]+) (?:(\w{16}) )?([A-Za-z?]) (.+)", line)
            if match:
                self.symbols.append(Symbol(int(match[1], 16), int(match[2], 16) if match[2] else 0,
                                           match[3], match[4]))

    def symbol(self, name, address=None):
        matches = {s for s in self.symbols if s.name == name
                   and (address is None or s.address == address)}
        if len(matches) != 1:
            raise ValueError(f"Expected one definition of {name}; found {len(matches)}")
        return matches.pop()

    def read(self, address, size):
        for kind, _, offset, start, _, file_size, _, _ in self.segments:
            if kind == 1 and start <= address and address + size <= start + file_size:
                begin = offset + address - start
                return self.data[begin:begin + size]
        raise ValueError(f"Not file-backed: {address:#x}+{size:#x}")

    def string(self, address):
        result = bytearray()
        for i in range(512):
            byte = self.read(address + i, 1)
            if byte == b"\0":
                return result.decode("ascii")
            result.extend(byte)
        raise ValueError(f"Unterminated string at {address:#x}")

    def disassemble(self, address, size):
        return subprocess.check_output([
            "objdump", "-d", "-C", "--no-show-raw-insn",
            f"--start-address={address}", f"--stop-address={address + size}",
            str(self.path),
        ], text=True)

    def function(self, name):
        symbol = self.symbol(name)
        return self.disassemble(symbol.address, symbol.size)


def instructions(disassembly):
    result = []
    for line in disassembly.splitlines():
        match = re.match(r"\s*([0-9a-f]+):\s+(\S+)\s*(.*)", line)
        if match:
            result.append((int(match[1], 16), match[2], match[3]))
    return result


def direct_transfers(disassembly):
    result = []
    for address, op, operands in instructions(disassembly):
        target = re.match(r"([0-9a-f]+) <(.+)>", operands)
        if op in {"call", "callq", "jmp", "jmpq"} and target:
            result.append({
                "instruction": hex(address), "kind": op,
                "address": hex(int(target[1], 16)), "symbol": target[2],
            })
    return result
