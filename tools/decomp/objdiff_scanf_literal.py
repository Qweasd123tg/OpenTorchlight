"""One fixed numeric wide-format use under explicit C/SysV import semantics.

Only %lld is modeled, not a generic variadic consumer. Conversion can fail: this
certificate never exports output initialization or success facts. The unchanged
scalar result load is subject to the existing defined-execution premise. The
original format may remain in RSI; normal continuation must not observe it.
"""
import hashlib
import re
import struct
import objdiff_literal_frames as frames
from objdiff_wcslen_append import import_identity, immutable_loaded_range

FORMAT = '%lld\0'.encode('utf-32le')
OFFSETS = (0, 4, 7, 12, 17, 19, 24, 29, 33)


def _unique_mapping(side, address, size, executable=False):
    if not immutable_loaded_range(side, address, size, executable):
        return False
    image = side.image
    section = image.section_at(address)
    loads = [s for s in image.segments if s[0] == 1 and s[6] > 0
             and address < ((s[3] + s[6] + 0xfff) & ~0xfff)
             and address + size > (s[3] & ~0xfff)]
    return (len(loads) == 1 and loads[0][2] + address - loads[0][3]
            == section.offset + address - section.addr)


def certify(side, k, insns, start, end):
    if (start is None or end != start + 34 or k != 2 or len(insns) != 9
            or tuple(r[0] - start for r in insns) != OFFSETS):
        return None
    # Full operation/operand grammar: no implicit transfer, prefixes, aliases,
    # extra paths, calls, saves, partial writes or forgotten instructions.
    ops = ('sub', 'mov', 'mov', 'lea', 'xor', 'call', 'mov', 'add', 'ret')
    if tuple(r[1] for r in insns) != ops:
        return None
    args = [r[2] for r in insns]
    allocation = re.fullmatch(r'\$0x([0-9a-f]+),%rsp', args[0])
    literal = re.fullmatch(r'\$0x([0-9a-f]+),%esi', args[2])
    output = re.fullmatch(r'0x([0-9a-f]+)\(%rsp\),%rdx', args[3])
    if not allocation or not literal or not output:
        return None
    size, address, offset = (int(x[1], 16) for x in (allocation, literal, output))
    if (not 8 <= size <= 120 or size % 16 != 8 or offset % 8
            or not 8 <= offset <= size - 8 or address > 0xffffffff or address % 4
            or args[1] != '(%rdi),%rdi' or args[4] != '%eax,%eax'
            or args[6] != f'0x{offset:x}(%rsp),%rax'
            or args[7] != args[0] or args[8]):
        return None
    image = side.image
    if (not isinstance(getattr(image, 'data', None), bytes)
            or hashlib.sha256(image.data).hexdigest() != image.sha256):
        return None
    target = side.direct_target(args[5])
    if image.plt.get(target) != 'swscanf':
        return None
    # Reloc stores a symbol name, not its dynsym index. Reject every same-name
    # ambiguity before the shared parser selects the eligible global FUNC.
    if len([s for s in image.dynsyms if s.name == 'swscanf']) != 1:
        return None
    identity = import_identity(image, 'swscanf', ('libc.so.6', 'GLIBC_2.2.5'))
    if identity is None:
        return None
    try:
        symbols = image.symbols + image.dynsyms
        if (not any(s.defined and s.type == 2 and s.value == start and s.size == 34 for s in symbols)
                or any(s.defined and start < s.value < end for s in symbols)
                or any(start < pc < end for pc in side.func_start)):
            return None
        body = (bytes.fromhex('4883ec') + bytes([size]) + bytes.fromhex('488b3fbe')
                + struct.pack('<I', address) + bytes.fromhex('488d5424') + bytes([offset])
                + bytes.fromhex('31c0e8') + struct.pack('<i', target - (start + 24))
                + bytes.fromhex('488b4424') + bytes([offset])
                + bytes.fromhex('4883c4') + bytes([size]) + b'\xc3')
        if image.read(start, 34) != body or not _unique_mapping(side, start, 34, True):
            return None
        stub = image.read(target, 6)
        if len(stub) != 6 or stub[:2] != b'\xff\x25' or not _unique_mapping(side, target, 16, True):
            return None
        got = target + 6 + struct.unpack('<i', stub[2:])[0]
        relocation = image.relocs.get(got)
        if (relocation is None or (relocation.type, relocation.symbol, relocation.addend)
                != (7, 'swscanf', 0)):
            return None
        section = image.section_at(address)
        if (section is None or not section.name.startswith('.rodata')
                or image.read(address, len(FORMAT)) != FORMAT
                or not _unique_mapping(side, address, len(FORMAT))):
            return None
    except (AttributeError, KeyError, ValueError, OverflowError, struct.error):
        return None
    # No local EH is admitted, regardless of an imported __THROW declaration.
    eh = side._literal_eh(insns, start, end)
    if eh is None or eh['rows'] or side.frames.error:
        return None
    if any(s < end and start < e for _, s, e, *_ in side.frames.lsdas):
        return None
    table = frames.cfi(side, {'start': start, 'size': 34})
    spans = []
    for i, pc in enumerate(OFFSETS):
        sp = 0 if i in (0, 8) else -size
        proof = frames.span_rules(table, start + pc,
                                  start + (OFFSETS[i+1] if i < 8 else 34), sp, {})
        if proof is None:
            return None
        spans.append(proof)
    normal = side._rsi_normal_dead(insns, start + 24, start, eh)
    if normal is None:
        return None
    return {'model': 'original-fixed-swscanf-lld-v1', 'load': start + 7,
            'literal': address, 'width': 4, 'argument': 'rsi', 'call': start + 19,
            'image_sha256': image.sha256, 'body_sha256': hashlib.sha256(body).hexdigest(),
            'payload_size': len(FORMAT), 'payload_sha256': hashlib.sha256(FORMAT).hexdigest(),
            'import': identity, 'plt': target, 'got': got, 'variadic_vector_count': 0,
            'output': {'entry_sp_offset': offset-size, 'size': 8,
                       'initialization': 'not-proved', 'conversion_success': 'not-proved'},
            'semantics': 'defined C++/SysV execution; valid disjoint objects; exact nonretaining numeric-format import; no arbitrary interposition',
            'cfi': spans, 'normal': normal, 'cleanup': [], 'eh_kind': eh['kind']}
