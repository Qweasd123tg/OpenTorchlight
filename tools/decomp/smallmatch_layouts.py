#!/usr/bin/env python3
"""Discover typed member evidence and validate a reviewed header recovery.

Discovery emits hypotheses, never accepted types or MATCH. Named template
receivers supply a container specialization and a byte offset. In particular,
_Rb_tree alone does NOT distinguish map from multimap: unique insertion needs
separate evidence. Header edits require explicit old/new hashes, layout checks,
reviewed provenance and a complete machine regression pass.
"""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re

import ghidra_cpp
import objdiff
import toolchain


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def canonical(text):
    return re.sub(r'\s+', '', text)


def template(text, name):
    prefix = name + '<'
    if not text.startswith(prefix) or not text.endswith('>'):
        return None
    return ghidra_cpp.split_args(text[len(prefix):-1])


def container_type(symbol):
    """Return a named container or an explicitly ambiguous tree representation."""
    # Parameters can contain :: themselves: find the outer template close.
    depth, end = 0, None
    for i, char in enumerate(symbol):
        if char == '<': depth += 1
        elif char == '>':
            depth -= 1
            if depth == 0:
                end = i + 1
                break
    if end is None or not symbol[end:].startswith('::'):
        return None
    scope, method = symbol[:end], symbol[end + 2:].split('(', 1)[0]
    args = template(scope, 'TArrayList')
    if args and len(args) == 1 and method in ('~TArrayList', 'add', 'clear', 'remove', 'find'):
        return {'type': scope, 'kind': 'TArrayList', 'size': 24, 'method': method,
                'representation': 'named_container'}
    args = template(scope, 'std::vector')
    if args and len(args) == 2 and canonical(args[1]) == canonical('std::allocator<' + args[0] + '>'):
        return {'type': 'std::vector<' + args[0] + '>', 'kind': 'std::vector', 'size': 24,
                'method': method, 'representation': 'named_container'}
    args = template(scope, 'std::_Rb_tree')
    if not args or len(args) != 5:
        return None
    key, pair, select, less, alloc = args
    pair_args = template(pair, 'std::pair')
    if not pair_args or len(pair_args) != 2:
        return None
    pair_key = re.sub(r'\bconst\b', '', pair_args[0]).strip()
    if canonical(pair_key) != canonical(key) or 'const' not in pair_args[0].split():
        return None
    expected = ['std::_Select1st<' + pair + '>', 'std::less<' + key + '>', 'std::allocator<' + pair + '>']
    if [canonical(x) for x in (select, less, alloc)] != [canonical(x) for x in expected]:
        return None
    return {'type': 'std::map<' + key + ', ' + pair_args[1] + '>', 'kind': 'std::_Rb_tree',
            'tree_type': scope, 'size': 48, 'method': method,
            'representation': 'unique_map' if method.startswith('_M_insert_unique') else 'map_or_multimap'}


def epilogue_restore(index, insns):
    """A callee-saved restore cannot reach a later call in this basic block."""
    for _, op, arg in insns[index + 1:index + 12]:
        if op in ('ret', 'repz ret', 'rep ret'):
            return True
        if op == 'jmp':
            target = re.match(r'^([0-9a-f]+)(?:\s|$)', arg)
            return target is not None and int(target[1], 16) not in {row[0] for row in insns}
        if op.startswith(('j', 'call', 'loop')):
            return False
        if op not in ('mov', 'pop', 'add', 'lea') and not objdiff.Normalizer.padding(op, arg):
            return False
    return False


def stable_this_registers(insns):
    aliases = set()
    for _, op, arg in insns:
        if op.startswith(('call', 'j', 'ret')):
            break
        match = re.fullmatch(r'%rdi,(%(?:rbx|rbp|r12|r13|r14|r15))', arg)
        if op == 'mov' and match:
            aliases.add(match[1])
    result = set()
    for reg in aliases:
        family = objdiff.Normalizer.register(reg)[0]
        safe = True
        for i, (_, op, arg) in enumerate(insns):
            dest = objdiff.Normalizer.register(arg.rsplit(',', 1)[-1].strip())
            if not dest or dest[0] != family or op.startswith(('cmp', 'test', 'call')) or op == 'push':
                continue
            if op == 'mov' and arg == '%rdi,' + reg:
                # The anchor must precede every clobber of incoming rdi.
                if any(m.startswith(('call', 'j')) or
                       (objdiff.Normalizer.register(p.rsplit(',', 1)[-1].strip()) or (None,))[0] == 'di'
                       for _, m, p in insns[:i] if m not in ('cmp', 'test', 'push')):
                    safe = False
                continue
            restore = op == 'pop' or (op == 'mov' and '%rsp)' in arg)
            if restore and epilogue_restore(i, insns):
                continue
            safe = False
        if safe:
            result.add(reg)
    return result


def receiver_offset(insns, call_index, aliases):
    """Only a same-block LEA from a stable this register; no guessed dataflow."""
    family = objdiff.Normalizer.register('%rdi')[0]
    for i in range(call_index - 1, max(-1, call_index - 9), -1):
        _, op, arg = insns[i]
        if op.startswith(('call', 'j', 'ret', 'loop')):
            return None
        dest = objdiff.Normalizer.register(arg.rsplit(',', 1)[-1].strip())
        if not dest or dest[0] != family or op.startswith(('cmp', 'test')):
            continue
        match = re.fullmatch(r'(0x[0-9a-f]+)?\((%r\w+)\),%rdi', arg)
        if op == 'lea' and match and match[2] in aliases:
            protected = {row[0] for row in insns[i + 1:call_index + 1]}
            for _, branch, operand in insns:
                if not branch.startswith(('j', 'loop')):
                    continue
                target = re.match(r'^([0-9a-f]+)(?:\s|$)', operand)
                if target is None or int(target[1], 16) in protected:
                    return None  # a path can bypass the receiver-defining LEA
            return int(match[1] or '0', 16), insns[i][0]
        return None
    return None


def discover(kit):
    kit = Path(kit)
    targets = json.loads((kit / 'targets.json').read_text())
    evidence = []
    for f in targets:
        if not f.get('scope') or f.get('clone') or 'thunk to ' in f['demangled']:
            continue
        path = kit / f['assembly']
        insns = [(a, m, p.split('#', 1)[0].strip()) for a, m, p in objdiff.parse_insns(path.read_text())]
        aliases = stable_this_registers(insns)
        for i, (address, op, operand) in enumerate(insns):
            match = re.fullmatch(r'([0-9a-f]+)\s+<(.+)>', operand)
            if op != 'call' or not match:
                continue
            kind = container_type(match[2])
            location = receiver_offset(insns, i, aliases) if kind else None
            if not location:
                continue
            evidence.append({**kind, 'class': f['scope'], 'offset': location[0],
                'function': f['address'], 'assembly': f['assembly'], 'assembly_sha256': digest(path),
                'receiver_instruction': hex(location[1]), 'call_instruction': hex(address),
                'callee': hex(int(match[1], 16)), 'symbol': match[2], 'status': 'EVIDENCE_ONLY'})
    return {'schema': 1, 'target_count': len(targets), 'evidence_count': len(evidence),
            'class_count': len({r['class'] for r in evidence}), 'evidence': evidence,
            'note': 'Discovery does not edit headers, infer ownership, resolve map/multimap, or certify MATCH.'}


def validate_manifest(kit, root, manifest):
    kit, root = Path(kit), Path(root)
    original = kit / 'original/Torchlight.bin.x86_64'
    if digest(original) != manifest.get('original_elf_sha256'):
        raise ValueError('original ELF differs from recovery evidence')
    if manifest.get('schema') != 1 or manifest.get('base_commit') != '824e3d3a33242c9ea775ca8a5ff36e87d6fd23ee':
        raise ValueError('unsupported recovery manifest/base commit')
    seen = set()
    for header in manifest['headers']:
        name = header['path']
        if name in seen or Path(name).name != name or not name.endswith('.h'):
            raise ValueError('duplicate or invalid recovery header path')
        seen.add(name)
        before = kit / 'project/decomp/include' / name
        after = root / 'decomp/include' / name
        if (digest(before) if before.exists() else None) != header['before_sha256']:
            raise ValueError('recovery header base differs: ' + name)
        if not after.is_file() or digest(after) != header['after_sha256']:
            raise ValueError('recovery header differs from reviewed content: ' + name)
    baseline = {p.relative_to(kit / 'project/decomp/include').as_posix(): digest(p)
                for p in (kit / 'project/decomp/include').rglob('*') if p.is_file()}
    actual = {p.relative_to(root / 'decomp/include').as_posix(): digest(p)
              for p in (root / 'decomp/include').rglob('*') if p.is_file()}
    changed = {n for n in set(baseline) | set(actual) if baseline.get(n) != actual.get(n)}
    if changed != seen:
        raise ValueError('header changes are absent from the recovery manifest')
    db = json.loads((kit / 'reference/elfdb.json').read_text())
    evidence = {(r['function'], r['call_instruction'], r['class'], r['offset']): r
                for r in discover(kit)['evidence']}
    for cls in manifest['classes']:
        if cls['header'] not in seen or not cls.get('provenance'):
            raise ValueError('class needs a reviewed header and provenance')
        intervals = []
        for member in cls['members']:
            begin, size = member['offset'], member['size']
            if not isinstance(begin, int) or not isinstance(size, int) or begin < 0 or size <= 0 or begin + size > cls['size']:
                raise ValueError('member lies outside the recovered object')
            if any(begin < end and left < begin + size for left, end in intervals):
                raise ValueError('overlapping recovered members')
            intervals.append((begin, begin + size))
            if not member.get('witnesses'):
                raise ValueError('member has no named original-call witness')
            for witness in member['witnesses']:
                key = (witness['function'], witness['call_instruction'], cls['name'], begin)
                item = evidence.get(key)
                if item is None or item['assembly_sha256'] != witness['assembly_sha256']:
                    raise ValueError('original receiver evidence does not reproduce')
                if canonical(item['type']) != canonical(member['evidence_type']) or item['size'] != size:
                    raise ValueError('recovered member contradicts named container evidence')
            if member['type'].startswith('std::map<'):
                unique = member.get('unique_key_evidence', {})
                function = db['functions'].get(unique.get('callee'), {})
                specialization = container_type(function.get('demangled', ''))
                if (not specialization or specialization['representation'] != 'unique_map'
                        or canonical(specialization['type']) != canonical(member['evidence_type'])
                        or not unique.get('receiver_review')):
                    raise ValueError('tree destructor alone cannot establish a unique-key map')
    return True


def layout_source(manifest):
    lines = ['// Compile-only layout assertions; this file has no main().']
    lines += ['#include "' + h['path'] + '"' for h in manifest['headers']]
    number = 0
    def check(expression):
        nonlocal number
        lines.append('typedef char layout_check_' + str(number) + '[(' + expression + ') ? 1 : -1];')
        number += 1
    for cls in manifest['classes']:
        check('sizeof(' + cls['name'] + ') == ' + str(cls['size']))
        for member in cls['members']:
            check('sizeof(((' + cls['name'] + '*)0)->' + member['name'] + ') == ' + str(member['size']))
            check('__builtin_offsetof(' + cls['name'] + ', ' + member['name'] + ') == ' + str(member['offset']))
        for member in cls.get('boundary_fields', []):
            check('__builtin_offsetof(' + cls['name'] + ', ' + member['name'] + ') == ' + str(member['offset']))
    return '\n'.join(lines) + '\n', number


def verify_layouts(kit, root, manifest_path, output):
    manifest = json.loads(Path(manifest_path).read_text())
    validate_manifest(kit, root, manifest)
    output = Path(output); output.mkdir(parents=True, exist_ok=True)
    source, count = layout_source(manifest)
    path, obj = output / 'layout-check.cpp', output / 'layout-check.o'
    path.write_text(source)
    toolchain.compile_source(path.resolve(), obj.resolve(), quiet=True)
    compiler = toolchain.compile_source(None, None, probe=True)
    result = {'status': 'PASS', 'assertions': count, 'manifest_sha256': digest(manifest_path),
              'source_sha256': digest(path), 'object_sha256': digest(obj), 'compiler': compiler,
              'original_executions': 0, 'fixture_executions': 0}
    (output / 'layout-check.json').write_text(json.dumps(result, indent=2) + '\n')
    return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--kit', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--manifest', type=Path)
    args = parser.parse_args()
    if args.manifest:
        result = verify_layouts(args.kit, Path(__file__).resolve().parents[2], args.manifest, args.output)
    else:
        result = discover(args.kit)
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n')
    print(json.dumps({k: v for k, v in result.items() if k != 'evidence'}, indent=2))
