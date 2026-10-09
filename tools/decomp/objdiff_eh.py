"""Conservative per-function EH gate, not an EH equivalence checker.

Read CIE/FDE associations from .eh_frame. An actual LSDA blocks an
instruction-only MATCH; personality targets are resolved and compared.
Malformed or unsupported associations fail closed. Ordinary unwind-only
FDEs do not reject unrelated functions in the same TU.
"""
from bisect import bisect_left
from dataclasses import dataclass


class FrameError(ValueError):
    pass


class Reader:
    def __init__(self, data, start=0, end=None):
        self.data, self.pos = data, start
        self.end = len(data) if end is None else end

    def take(self, size):
        if size < 0 or self.pos + size > self.end:
            raise FrameError("truncated EH frame")
        out = self.data[self.pos:self.pos + size]
        if len(out) != size:
            raise FrameError("truncated EH section")
        self.pos += size
        return out

    def number(self, size, signed=False):
        return int.from_bytes(self.take(size), "little", signed=signed)

    def leb(self, signed=False):
        value = shift = 0
        for _ in range(10):
            byte = self.number(1)
            value |= (byte & 127) << shift
            shift += 7
            if not byte & 128:
                return value - (1 << shift) if signed and byte & 64 else value
        raise FrameError("oversized EH LEB128")

    def encoded(self, encoding, base):
        if encoding == 255:
            raise FrameError("omitted FDE address")
        form = encoding & 15
        pos = self.pos
        if form == 0:
            value = self.number(8)
        elif form in (1, 9):
            value = self.leb(form == 9)
        elif form in (2, 3, 4, 10, 11, 12):
            value = self.number({2: 2, 3: 4, 4: 8}[form & 7], bool(form & 8))
        else:
            raise FrameError("unsupported EH pointer format")
        application = encoding & 112
        if application == 16:
            value += base + pos
        elif application:
            raise FrameError("unsupported EH pointer base")
        if encoding & 128:
            raise FrameError("indirect FDE address")
        return value


@dataclass(frozen=True)
class Frames:
    # (code section index or None for a linked ELF, start, end, reason, personality)
    ranges: tuple
    error: str | None = None
    # Independently resolved LSDA locations; the ordinary gate stays closed.
    # (code section, start, end, data section, data offset, resolution error)
    lsdas: tuple = ()

    def __post_init__(self):
        # Parsed metadata is an immutable snapshot; no stale index after mutation.
        object.__setattr__(self, "ranges", tuple(self.ranges))
        groups = {}
        for row in self.ranges:
            groups.setdefault(row[0], []).append(row)
        index = {}
        for section, rows in groups.items():
            rows.sort(key=lambda row: row[1])
            starts, maximum = [], []
            high = None
            for row in rows:
                starts.append(row[1])
                high = row[2] if high is None else max(high, row[2])
                maximum.append(high)
            index[section] = (tuple(rows), tuple(starts), tuple(maximum))
        object.__setattr__(self, "_index", index)
        object.__setattr__(self, "lsdas", tuple(self.lsdas))
        object.__setattr__(self, "_lsda_index", {
            (row[0], row[1], row[2]): row for row in self.lsdas})

    def _overlapping(self, start, size, section):
        rows, starts, maximum = self._index.get(section, ((), (), ()))
        i = bisect_left(starts, start + size) - 1
        # Prefix maxima retain nested/overlapping FDEs, not just the nearest one.
        while i >= 0 and maximum[i] > start:
            row = rows[i]
            if start < row[2]:
                yield row
            i -= 1

    def reason(self, start, size, section=None):
        if self.error:
            return self.error
        matches = list(self._overlapping(start, size, section))
        if any(row[1] > start or row[2] < start + size for row in matches):
            return "EH FDE partially overlaps function; association unverified"
        if len(matches) > 1:
            return "multiple EH FDEs overlap function; association unverified"
        return matches[0][3] if matches else None

    def personalities(self, start, size, section=None):
        return sorted({row[4] for row in self._overlapping(start, size, section) if row[4]})


def personality_name(image, field, width, value, encoding, relocatable, relocs):
    if relocatable:
        relocation = relocs.get(field)
        if relocation is None or relocation.type not in (1, 2, 10, 11):
            raise FrameError("unresolved EH personality relocation")
        expected = {1: (0, 8), 2: (16, 4), 10: (0, 4), 11: (0, 4)}[relocation.type]
        if (encoding & 112, width) != expected:
            raise FrameError("unsupported EH personality relocation encoding")
        symbol, addend = relocation.symbol, relocation.addend
        if encoding & 128:
            if not symbol.defined or not 0 < symbol.shndx < len(image.sections):
                raise FrameError("unresolved indirect EH personality")
            targets = [r for r in image.relocs.get(symbol.shndx, []) if r.offset == symbol.value + addend]
            if len(targets) != 1 or targets[0].type != 1:
                raise FrameError("unresolved indirect EH personality relocation")
            symbol, addend = targets[0].symbol, targets[0].addend
        if addend or not symbol.name or symbol.type == 3:
            raise FrameError("unresolved EH personality symbol")
        return symbol.name.split("@")[0]
    if encoding & 128:
        relocation = image.relocs.get(value)
        if relocation and relocation.symbol and relocation.addend == 0:
            return relocation.symbol.split("@")[0]
        value = image.u64(value)
    if value in image.plt:
        return image.plt[value].split("@")[0]
    names = {s.name.split("@")[0] for s in image.symbols + image.dynsyms
             if s.defined and s.value == value and s.name}
    if len(names) != 1:
        raise FrameError("unresolved linked EH personality")
    return names.pop()


def inspect(image, relocatable=False):
    ranges = []
    lsdas = []
    sections = [s for s in image.sections if s.name == ".eh_frame" or s.name.startswith(".eh_frame.")]
    if not sections and any(s.size and s.name in (".gcc_except_table", ".eh_frame_hdr") for s in image.sections):
        return Frames([], "EH sections present without .eh_frame; association unverified")
    try:
        for section in sections:
            data = image.data[section.offset:section.offset + section.size]
            if len(data) != section.size:
                raise FrameError("truncated EH section")
            relocs = {}
            if relocatable:
                for relocation in image.relocs.get(section.index, []):
                    if relocation.offset in relocs:
                        raise FrameError("overlapping EH relocations")
                    relocs[relocation.offset] = relocation
            cies = {}
            pos = 0
            while pos < len(data):
                reader = Reader(data, pos)
                length = reader.number(4)
                if length == 0:
                    if any(data[reader.pos:]):
                        raise FrameError("data after EH terminator")
                    break
                if length == 0xffffffff:
                    raise FrameError("unsupported 64-bit EH frame length")
                end = reader.pos + length
                if end > len(data) or length < 4:
                    raise FrameError("invalid EH frame length")
                reader.end = end
                id_pos = reader.pos
                cie_id = reader.number(4)
                if cie_id == 0:
                    version = reader.number(1)
                    if version not in (1, 3):
                        raise FrameError("unsupported EH CIE version")
                    augmentation = bytearray()
                    while True:
                        byte = reader.number(1)
                        if byte == 0:
                            break
                        augmentation.append(byte)
                    augmentation = augmentation.decode("ascii")
                    reader.leb()
                    reader.leb(True)
                    reader.number(1) if version == 1 else reader.leb()
                    encoding = 0
                    personality = None
                    lsda_encoding = 255
                    if augmentation:
                        if not augmentation.startswith("z"):
                            raise FrameError("unsupported EH CIE augmentation")
                        aug_size = reader.leb()
                        aug = Reader(data, reader.pos, reader.pos + aug_size)
                        reader.take(aug_size)
                        for char in augmentation[1:]:
                            if char == "R":
                                encoding = aug.number(1)
                            elif char == "L":
                                lsda_encoding = aug.number(1)
                            elif char == "P":
                                personality_encoding = aug.number(1)
                                field = aug.pos
                                value = aug.encoded(personality_encoding & ~128, section.addr)
                                personality = personality_name(image, field, aug.pos - field, value,
                                                               personality_encoding, relocatable, relocs)
                            elif char != "S":
                                raise FrameError("unsupported EH CIE augmentation")
                        if aug.pos != aug.end:
                            raise FrameError("unparsed EH CIE augmentation")
                    cies[pos] = (encoding, augmentation.startswith("z"), lsda_encoding, personality)
                else:
                    cie = cies.get(id_pos - cie_id)
                    if cie is None:
                        raise FrameError("unresolved EH CIE reference")
                    encoding, augmented, lsda_encoding, personality = cie
                    field = reader.pos
                    start = reader.encoded(encoding, section.addr)
                    size = reader.encoded(encoding & 15, 0)
                    code_section = None
                    if relocatable:
                        relocation = relocs.get(field)
                        if relocation is None or relocation.type not in (1, 2, 10, 11):
                            raise FrameError("unresolved FDE code relocation")
                        symbol = relocation.symbol
                        if not symbol.defined or not 0 < symbol.shndx < len(image.sections):
                            raise FrameError("unresolved FDE code symbol")
                        expected = {1: (0, 8), 2: (16, 4), 10: (0, 4), 11: (0, 4)}[relocation.type]
                        if encoding & 112 != expected[0] or reader.pos - field != expected[1] * 2:
                            raise FrameError("unsupported FDE relocation encoding")
                        code_section = symbol.shndx
                        start = symbol.value + relocation.addend
                    if size <= 0 or start < 0:
                        raise FrameError("invalid FDE code range")
                    code = image.sections[code_section] if relocatable else image.section_at(start)
                    code_start = 0 if relocatable else code.addr if code else 0
                    if code is None or not code.flags & 4 or start < code_start or start + size > code_start + code.size:
                        raise FrameError("FDE range outside executable section")
                    if augmented:
                        aug_size = reader.leb()
                        aug = Reader(data, reader.pos, reader.pos + aug_size)
                        reader.take(aug_size)
                        lsda = False
                        location = None
                        if lsda_encoding != 255:
                            lsda_field = aug.pos
                            value = aug.encoded(lsda_encoding & ~128, section.addr)
                            # Zero is the absent-LSDA sentinel even for PC-relative encoding.
                            raw_nonzero = any(data[lsda_field:aug.pos])
                            lsda = raw_nonzero or (relocatable and lsda_field in relocs)
                            if lsda:
                                try:
                                    location = lsda_location(image, value, lsda_encoding,
                                                             aug.pos - lsda_field,
                                                             relocs.get(lsda_field), relocatable)
                                except FrameError as exc:
                                    location = (None, None, str(exc))
                        if aug.pos != aug.end:
                            raise FrameError("unparsed EH FDE augmentation")
                    else:
                        lsda = False
                    reason = "EH LSDA equivalence unverified" if lsda else None
                    ranges.append((code_section, start, start + size, reason, personality))
                    if lsda:
                        lsdas.append((code_section, start, start + size, *location))
                pos = end
        return Frames(ranges, lsdas=tuple(lsdas))
    except (FrameError, UnicodeError, IndexError, ValueError) as exc:
        return Frames([], f"EH metadata unverified: {exc}")


def lsda_location(image, value, encoding, width, relocation, relocatable):
    """Resolve the FDE's LSDA pointer, without interpreting its contents."""
    if encoding & 128:
        raise FrameError("indirect LSDA pointer unsupported")
    if relocatable:
        expected = {1: (0, 8), 2: (16, 4), 10: (0, 4), 11: (0, 4)}
        if relocation is None or expected.get(relocation.type) != (encoding & 112, width):
            raise FrameError("unresolved LSDA relocation or encoding")
        symbol = relocation.symbol
        if not symbol.defined or not 0 < symbol.shndx < len(image.sections):
            raise FrameError("unresolved LSDA section")
        section = image.sections[symbol.shndx]
        offset = symbol.value + relocation.addend
    else:
        section = image.section_at(value)
        offset = value - section.addr if section else -1
    if (section is None or section.type != 1 or not section.flags & 2
            or section.flags & 5 or not 0 <= offset < section.size
            or not section.name.startswith(".gcc_except_table")):
        raise FrameError("LSDA outside read-only exception section")
    return section.index, offset, None


def cleanup_signature(image, frames, start, size, insns, section=None):
    """A strict cleanup-only LSDA certificate, or None for unsupported input.

    GCC 4.4.7 eh_personality.cc: omitted LPStart means region start; omitted
    TType and zero actions admit cleanups only. Preserve *all* call-site rows:
    a missing row terminates, whereas a zero landing pad continues unwinding.
    Exact instruction byte offsets and function size are part of the key.
    No catch, filter, type table or instruction-layout relaxation is supported.
    This function never changes Frames.reason(): both sides must be compared.
    """
    if frames.reason(start, size, section) != "EH LSDA equivalence unverified":
        return None
    matches = list(frames._overlapping(start, size, section))
    if (len(matches) != 1 or matches[0][1:3] != (start, start + size)
            or matches[0][4] != "__gxx_personality_v0"):
        return None
    location = frames._lsda_index.get((section, start, start + size))
    if location is None or location[5] is not None:
        return None
    data_section, offset = image.sections[location[3]], location[4]
    bound = min((r[4] for r in frames.lsdas
                 if r[3] == location[3] and r[4] > offset), default=data_section.size)
    data = image.data[data_section.offset:data_section.offset + data_section.size]
    if len(data) != data_section.size:
        return None
    offsets = tuple(i[0] - start for i in insns)
    if (not offsets or offsets[0] != 0 or tuple(sorted(set(offsets))) != offsets
            or offsets[-1] >= size):
        return None
    boundaries = set(offsets) | {size}
    try:
        reader = Reader(data, offset, bound)
        if reader.number(1) != 255 or reader.number(1) != 255:
            return None  # Explicit LPStart, catches and exception specifications.
        if reader.number(1) != 1:
            return None  # Only absolute ULEB128 call-site displacements.
        length = reader.leb()
        end = reader.pos + length
        if end > bound:
            return None
        reader.end = end
        rows, previous_end = [], 0
        while reader.pos < end:
            begin, count, pad, action = (reader.leb() for _ in range(4))
            if (action != 0 or count <= 0 or begin < previous_end
                    or begin not in boundaries or begin + count not in boundaries
                    or begin + count > size or (pad and pad not in set(offsets))):
                return None
            rows.append((begin, count, pad, 0))
            previous_end = begin + count
        if not rows:
            return None
        # Displacements must be literal bytes, not unmodelled relocations.
        if section is not None:
            if any(r.offset < end and r.offset + 8 > offset
                   for r in image.relocs.get(data_section.index, [])):
                return None
        elif any(a < data_section.addr + end and a + 8 > data_section.addr + offset for a in image.relocs):
            return None
        return ("gcc447-cleanup-v1", size, offsets, tuple(rows))
    except (FrameError, ValueError, IndexError):
        return None
