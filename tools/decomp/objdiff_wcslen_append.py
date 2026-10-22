"""Original-only paired length/append proof, not an append consumer whitelist.

The explicit versioned C/old-COW C++ contracts consume character contents, not
source identity. They may preserve incoming volatile raw arguments: RDI must be
killed before append and RSI must pass the existing normal/cleanup lifetime proof.
"""
import hashlib
import re
import struct

APPEND = '_ZNSbIwSt11char_traitsIwESaIwEE6appendEPKwm'
CONTRACTS = {'wcslen': ('libc.so.6', 'GLIBC_2.2.5'),
             APPEND: ('libstdc++.so.6', 'GLIBCXX_3.4')}


# Exact published PR165 protection predicates, carried locally because clean
# PR178 does not include the cumulative comparator's guard-store methods.
def readonly_section(section, offset, size, executable=False):
    """Complete SHF_ALLOC range with no SHF_WRITE (and executable code)."""
    return bool(section and size > 0 and 0 <= offset and offset + size <= section.size
                and section.flags & 2 and not section.flags & 1
                and (not executable or section.flags & 4))


def immutable_loaded_range(side, address, size, executable=False):
    """Both section attributes and actual ELF PT_LOAD permissions agree.

    The existing static-image contract excludes runtime remapping or
    self-modifying code. A successful ordinary store cannot alter a
    non-writable mapped code/table range. Reject overlapping writable
    mappings and incomplete or non-file-backed ranges.
    """
    section = side.image.section_at(address)
    if not section or not readonly_section(section, address - section.addr, size, executable):
        return False
    covered = False
    for kind, flags, offset, vaddr, paddr, filesz, memsz, align in side.image.segments:
        if kind != 1:
            continue
        if (offset < 0 or filesz < 0 or memsz < filesz
                or offset + filesz > len(side.image.data)
                or (offset - vaddr) & 0xfff):
            return False
        if memsz <= 0:
            continue
        # x86-64 Linux maps PT_LOAD at 4 KiB page granularity. An
        # overlapping writable page invalidates protection even when
        # the declared segment byte intervals themselves are disjoint.
        page_start = vaddr & ~0xfff
        page_end = (vaddr + memsz + 0xfff) & ~0xfff
        if flags & 2 and address < page_end and address + size > page_start:
            return False
        if vaddr <= address and address + size <= vaddr + filesz and flags & 4:
            covered = covered or not executable or bool(flags & 1)
    return covered


def import_identity(image, name, expected=None):
    """Bind the explicit semantics to unique original dynamic version metadata."""
    try:
        syms = [s for s in image.dynsyms if s.name == name and not s.defined
                and s.bind == 1 and s.type == 2]
        expected = CONTRACTS.get(name) if expected is None else expected
        if len(syms) != 1 or expected is None:
            return None
        def data(name):
            s = image.section(name)
            return image.data[s.offset:s.offset + s.size]
        versions, needs, strings = (data(n) for n in ('.gnu.version', '.gnu.version_r', '.dynstr'))
        index = struct.unpack_from('<H', versions, 2 * syms[0].index)[0] & 0x7fff
        def string(offset):
            if not 0 <= offset < len(strings):
                raise ValueError('version string offset')
            end = strings.find(b'\0', offset)
            if end < offset:
                raise ValueError('version string terminator')
            return strings[offset:end].decode('ascii')
        found, visited, off = [], set(), 0
        while True:
            if off in visited:
                return None
            visited.add(off)
            version, count, file, aux, nxt = struct.unpack_from('<HHIII', needs, off)
            if version != 1 or not 0 < count <= 256:
                return None
            library, a, seen = string(file), off + aux, set()
            for _ in range(count):
                if a in seen:
                    return None
                seen.add(a)
                _, flags, other, label, following = struct.unpack_from('<IHHII', needs, a)
                if other & 0x7fff == index:
                    found.append((library, string(label), flags))
                a += following
            if not nxt:
                break
            off += nxt
        if found != [(*expected, 0)]:
            return None
        return {'symbol': name, 'soname': found[0][0], 'version': found[0][1],
                'evidence': 'original dynamic version tables; explicit nonretaining ABI contract'}
    except (AttributeError, KeyError, IndexError, ValueError, UnicodeError, struct.error):
        return None


def certify(side, k, insns, start, end):
    if start is None or end is None or not insns or insns[0][0] != start:
        return None
    # One joint certificate for two operands, never a fact about the address.
    args = insns[k][2]
    first = k if re.fullmatch(r'\$0x[0-9a-f]+,%edi', args) else k - 2
    if first < 0 or first + 6 >= len(insns) or k not in (first, first + 2):
        return None
    rows = insns[first:first + 6]
    if (any(rows[j][1] not in ('mov', 'movl') for j in (0, 2))
            or any(rows[j][1] not in ('mov', 'movq') for j in (3, 4))):
        return None
    literal = re.fullmatch(r'\$0x([0-9a-f]+),%edi', rows[0][2])
    if (literal is None or rows[2][2] != '$0x' + literal[1] + ',%esi'
            or rows[3][2] != '%rax,%rdx'
            or not re.fullmatch(r'%(?:rbx|rbp|r12|r13|r14|r15),%rdi', rows[4][2])):
        return None
    if any(rows[j][1] not in ('call', 'callq') for j in (1, 5)):
        return None
    image = side.image
    if not isinstance(getattr(image, 'data', None), bytes) or hashlib.sha256(image.data).hexdigest() != getattr(image, 'sha256', None):
        return None
    imports = []
    for j, name in ((1, 'wcslen'), (5, APPEND)):
        if image.plt.get(side.direct_target(rows[j][2]), '').split('@')[0] != name:
            return None
        identity = import_identity(image, name)
        if identity is None:
            return None
        imports.append(identity)
    eh = side._literal_eh(insns, start, end)
    if eh is None:
        return None
    low, high = rows[0][0], rows[-1][0]
    if (any(low < pc <= high for pc in side.func_start)
            or any(s.defined and low < s.value <= high for s in image.symbols + image.dynsyms)):
        return None
    # Reuse the published closed caller transfer/stack grammar. Unknown opcodes
    # are not guessed to fall through, even on paths outside this literal use.
    import objdiff_null_field
    from objdiff_saved_argument import Reject
    if (len({r[0] for r in insns}) != len(insns)
            or any(not start <= r[0] < end for r in insns)
            or any(a[0] >= b[0] for a, b in zip(insns, insns[1:]))):
        return None
    try:
        edges = objdiff_null_field.graph(side, insns, start, eh)
    except Reject:
        return None
    for _, op, operands in insns:
        if op in ('call', 'callq'):
            target = side.direct_target(operands)
            if target is None or low < target <= high:
                return None
    predecessors = {rows[j][0]: rows[j-1][0] for j in range(1, 6)}
    for source, targets in edges.items():
        if any(target in predecessors and source != predecessors[target] for target in targets):
            return None
    if any(pad and low < start + pad <= high for _, _, pad, _ in eh['rows']):
        return None
    address = int(literal[1], 16)
    if address > 0xffffffff:  # EDI/ESI writes zero-extend exactly 32 bits.
        return None
    section = image.section_at(address)
    if (section is None or not section.name.startswith('.rodata')
            or not section.flags & 2 or section.flags & 1 or address % 4):
        return None
    try:
        raw = image.read(address, section.addr + section.size - address)
        # Bound the complete first UTF-32 NUL, not a narrow prefix or fixed count.
        size = next(i + 4 for i in range(0, len(raw) - 3, 4) if raw[i:i+4] == b'\0' * 4)
    except (ValueError, StopIteration):
        return None
    if not immutable_loaded_range(side, address, size):
        return None
    # Even a partial readonly PT_LOAD can replace an entire payload page with
    # another file mapping. Conservatively require exactly one overlapping load,
    # rather than trusting only segments covering the complete literal interval.
    overlaps = []
    for segment in image.segments:
        kind, flags, offset, vaddr, _, filesz, memsz, align = segment
        if kind != 1 or memsz <= 0:
            continue
        page_start = vaddr & ~0xfff
        page_end = (vaddr + memsz + 0xfff) & ~0xfff
        if address < page_end and address + size > page_start:
            overlaps.append(segment)
    if len(overlaps) != 1:
        return None
    _, _, offset, vaddr, _, _, _, _ = overlaps[0]
    if offset + address - vaddr != section.offset + address - section.addr:
        return None
    normal = side._rsi_normal_dead(insns, insns[first + 6][0], start, eh)
    if normal is None:
        return None
    cleanups = []
    for begin, count, pad, _ in eh['rows']:
        if begin <= high - start < begin + count and pad:
            proof = side._rsi_cleanup_dead(insns, start + pad, start, eh)
            if proof is None:
                return None
            cleanups.append(proof)
    return {'model': 'original-paired-wcslen-append-v1', 'load': insns[k][0],
            'paired_loads': [rows[0][0], rows[2][0]], 'literal': address, 'width': 4,
            'argument': 'rdi' if k == first else 'rsi', 'call': high,
            'image_sha256': image.sha256, 'imports': imports,
            'payload_size': size, 'payload_sha256': hashlib.sha256(raw[:size]).hexdigest(),
            'character_count': size // 4 - 1, 'count_lineage': [rows[1][0], rows[3][0], high],
            'rdi_kill': rows[4][0], 'normal': normal, 'cleanup': cleanups, 'eh_kind': eh['kind']}
