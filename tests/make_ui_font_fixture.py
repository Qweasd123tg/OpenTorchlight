#!/usr/bin/env python3
"""Generate a tiny authored TrueType and test pak, using only Python stdlib.
No original/system fonts are read or copied. Generated outputs stay in build/.
Glyphs are rectangles; this tests atlas upload, not original typography parity.
"""
from pathlib import Path
import struct
import sys
import zipfile


def test_font():
    def u16(*values): return struct.pack('>' + 'H' * len(values), *values)
    def i16(*values): return struct.pack('>' + 'h' * len(values), *values)
    def u32(*values): return struct.pack('>' + 'I' * len(values), *values)
    def pad(data): return data + b'\0' * (-len(data) % 4)
    def checksum(data):
        data = pad(data)
        return sum(struct.unpack('>' + 'I' * (len(data) // 4), data)) & 0xffffffff
    glyphs = [b'', b'']
    for left, right, top in [(50, 450, 700), (0, 600, 800), (150, 350, 600)]:
        glyphs.append(i16(1, left, 0, right, top) + u16(3, 0) + b'\1' * 4 +
                      i16(left, right - left, 0, left - right) + i16(0, 0, top, 0))
    offsets, glyf = [0], b''
    for g in glyphs:
        glyf += pad(g)
        offsets.append(len(glyf))
    codes = list(range(32, 127)) + [0x3a0, 0x3a9, 0x42f, 0xffff]
    mapping = {c: (1 if c == 32 else 3 if c == 66 else 4 if c > 126 else 2) for c in codes}
    mapping[0xffff] = 0
    n = len(codes)
    power = 1 << (n.bit_length() - 1)
    cmap = (u16(4, 16 + 8*n, 0, 2*n, 2*power, power.bit_length()-1, 2*n-2*power) +
            u16(*codes) + u16(0) + u16(*codes) +
            u16(*((mapping[c]-c) & 0xffff for c in codes)) + u16(*([0]*n)))
    head = struct.pack('>IIIIHHQQhhhhHHhhh', 0x10000, 0x10000, 0, 0x5f0f3cf5,
                       0, 1000, 0, 0, 0, 0, 600, 800, 0, 8, 2, 1, 0)
    hhea = u32(0x10000) + i16(800, -200, 0) + u16(600) + i16(0, 0, 600, 1, 0, 0, 0, 0, 0, 0, 0) + u16(len(glyphs))
    assert len(head) == 54 and len(hhea) == 36
    family, style = 'OT Authored Fixture'.encode('utf-16-be'), 'Regular'.encode('utf-16-be')
    name = u16(0, 2, 30) + u16(3, 1, 0x409, 1, len(family), 0) + u16(3, 1, 0x409, 2, len(style), len(family)) + family + style
    tables = {'head': head, 'hhea': hhea, 'maxp': u32(0x10000) + u16(len(glyphs), 4, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0),
              'hmtx': b''.join(u16(600) + i16(0) for _ in glyphs), 'loca': u32(*offsets), 'glyf': glyf,
              'cmap': u16(0, 1, 3, 1) + u32(12) + cmap, 'name': name,
              'post': u32(0x30000) + b'\0' * 28}
    count = len(tables); power = 1 << (count.bit_length()-1)
    directory = u32(0x10000) + u16(count, 16*power, power.bit_length()-1, 16*count-16*power)
    data = b''; head_offset = None
    for tag, table in sorted(tables.items()):
        offset = 12 + 16*count + len(data)
        directory += tag.encode('ascii') + u32(checksum(table), offset, len(table))
        if tag == 'head': head_offset = offset
        data += pad(table)
    result = bytearray(directory + data)
    struct.pack_into('>I', result, head_offset + 8, (0xb1b0afba - checksum(result)) & 0xffffffff)
    return bytes(result)


def write_fixture(path):
    path = Path(path); path.parent.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(path, 'w', zipfile.ZIP_DEFLATED) as z:
        z.writestr('media/ui/authored.ttf', test_font())
        for name in ['SerifSmall', 'Serif', 'FrizQuadrata', 'FrizQuadrataBig', 'Fixture']:
            z.writestr('media/ui/' + name + '.font',
                f'<Font Name="{name}" Filename="media/ui/authored.ttf" Size="18" NativeHorzRes="1024" NativeVertRes="768" AutoScaled="true" AntiAlias="true"/>')

if __name__ == '__main__':
    write_fixture(sys.argv[1])
