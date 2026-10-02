#!/usr/bin/env python3
"""Repeatable raw-pcode generation feasibility, never completion promotion.

Select residual manual routes in explicit batches of 1..1024. Export mode uses
the pinned saved project read-only with no analysis or decompiler; raw-dir mode
verifies existing schema-2 packets against the external ELF. Structural lowering
and explicit reviewed ABI/production ownership are independent report fields.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

import auto_triage
from automation_state import validate_output, write_json
from function_package import ELF_PATH, ELF_SHA, FunctionPackageBuilder, normalize
import lift_pcode as lift
from original import Original
from setup_ghidra import DIRECTORY, VERSION, verify_installation
from transfer_contract import completion, in_scope

ROOT = Path(__file__).resolve().parents[1]
MAX_BATCH = 1024


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def canonical(value):
    return '0x' + normalize(value)


def select(root, scope, limit, offset=0, requested=()):
    """Return exact residual starts, exclusions, and validated source index."""
    if scope not in {'ui', 'all'} or not 1 <= limit <= MAX_BATCH or offset < 0:
        raise ValueError('scope ui/all, limit 1..1024 and nonnegative offset required')
    builder = FunctionPackageBuilder(root)
    contour = json.loads((root / 'research/ui-contour.json').read_text())
    if contour.get('original_elf_sha256') != ELF_SHA:
        raise ValueError('UI contour ELF identity differs from supported original')
    wanted = {canonical(a) for a in requested}
    rows = auto_triage.build(root, 4)['functions']
    candidates, exclusions, hashes = [], [], {}
    seen = set()
    for row in rows:
        entry = canonical(row['address'])
        if entry in seen:
            raise ValueError('Duplicate coverage source entry: ' + entry)
        seen.add(entry)
        if wanted and entry not in wanted:
            continue
        if not in_scope(row['symbol'], entry, {**contour, 'name': scope}):
            continue
        state = completion(builder.transfers.get(normalize(entry)), root, hashes)
        item = {**row, 'address': entry, 'completion_status': state['status'],
                'indexed_direct_calls': builder.callsite_out.get(normalize(entry), []),
                'indexed_indirect_calls': builder.indirect_calls.get(normalize(entry), []),
                'callsite_index_available': builder.have_callsites}
        if state['status'] == 'reviewed_full':
            exclusions.append({**item, 'screening_status': 'excluded_reviewed_full'})
        elif (row.get('current_status') in {'closed', 'full', 'reviewed_full'} and
              state['status'] not in {'stale', 'invalid'}):
            exclusions.append({**item, 'screening_status': 'excluded_closed'})
        elif row['recommended_action'] != 'manual_reverse':
            exclusions.append({**item, 'screening_status': 'excluded_nonmanual_route'})
        elif normalize(entry) not in builder.symbols or not builder.symbols[normalize(entry)]['size']:
            exclusions.append({**item, 'screening_status': 'invalid_exact_symbol'})
        else:
            candidates.append(item)
    if wanted - seen:
        raise ValueError('Requested entries absent from source registry: ' + ', '.join(sorted(wanted - seen)))
    candidates.sort(key=lambda r: int(r['address'], 16))
    return {'scope': scope, 'offset': offset, 'limit': limit,
            'residual_manual_total': len(candidates), 'selected': candidates[offset:offset + limit],
            'excluded': exclusions}, builder


def validate_raw(packet, original, symbol, expected_entry):
    """Fail closed on identity/hash/byte or exact-entry mismatch."""
    if (packet.get('schema') != 2 or packet.get('original_elf_sha256') != original.sha256 or
            canonical(packet['address']) != expected_entry):
        raise ValueError(expected_entry + ': raw schema/ELF/exact-entry mismatch')
    instructions = packet.get('instructions')
    if not isinstance(instructions, list) or not instructions:
        raise ValueError(expected_entry + ': missing original raw instructions')
    hashes = hashlib.sha256()
    seen, covered = set(), set()
    for ins in instructions:
        location = canonical(ins['address'])
        start = int(location, 16)
        raw = bytes.fromhex(ins['bytes'])
        if location in seen or not raw:
            raise ValueError(location + ': duplicate instruction or empty bytes')
        seen.add(location)
        if start < symbol.address or start + len(raw) > symbol.address + symbol.size:
            raise ValueError(location + ': instruction outside full ELF symbol range')
        span = set(range(start, start + len(raw)))
        if covered & span:
            raise ValueError(location + ': overlapping instruction byte ranges')
        covered |= span
        if original.read(start, len(raw)) != raw:
            raise ValueError(location + ': instruction bytes differ from external original ELF')
        hashes.update(ins['address'].encode()); hashes.update(raw)
    if expected_entry not in seen:
        raise ValueError(expected_entry + ': exact entry not in instruction body')
    if packet.get('address_and_instruction_bytes_sha256') != hashes.hexdigest():
        raise ValueError(expected_entry + ': address/instruction hash mismatch')
    ranges = packet.get('body_ranges')
    if not isinstance(ranges, list) or not ranges:
        raise ValueError(expected_entry + ': missing explicit Ghidra body ranges')
    for row in ranges:
        lo, hi = int(row['start'], 16), int(row['end_inclusive'], 16)
        if lo < symbol.address or hi >= symbol.address + symbol.size or hi < lo:
            raise ValueError(expected_entry + ': Ghidra body outside exact ELF symbol')
    if any(not any(int(r['start'], 16) <= a <= int(r['end_inclusive'], 16) for r in ranges)
           for a in covered):
        raise ValueError(expected_entry + ': instruction outside declared Ghidra body')
    full = original.read(symbol.address, symbol.size)
    return {'full_symbol_size': symbol.size, 'full_symbol_sha256': hashlib.sha256(full).hexdigest(),
            'verified_instruction_bytes': len(covered),
            'symbol_bytes_without_exported_instruction': symbol.size - len(covered),
            'address_and_instruction_bytes_sha256': hashes.hexdigest()}


def screen_packet(data):
    """Structural checks only: never fabricate an ABI to invoke the emitter."""
    reasons, dependencies = [], []
    inventory = Counter()
    instructions = data['instructions']
    rows = {canonical(i['address']): i for i in instructions}

    def reason(kind, context, detail):
        item = {'kind': kind, 'context': context, 'detail': detail}
        if item not in reasons:
            reasons.append(item)

    for ins in instructions:
        a = canonical(ins['address'])
        pc = ins.get('pcode')
        if not isinstance(pc, list):
            reason('raw_pcode_missing', a, 'structured raw p-code list required')
            continue
        uniques = set()
        for idx, op in enumerate(pc):
            if not isinstance(op, dict):
                reason('raw_operation_invalid', a + f'[{idx}]', 'operation must be an object')
                continue
            name = op.get('operation')
            context = a + f' pcode[{idx}] {name}'
            inventory[str(name)] += 1
            nodes, out = op.get('inputs'), op.get('output')
            if not isinstance(nodes, list):
                reason('raw_operation_invalid', context, 'inputs must be a list')
                continue
            if name in {'CALLIND', 'BRANCHIND', 'CALLOTHER'}:
                dependencies.append({'kind': {'CALLIND': 'indirect_call', 'BRANCHIND': 'indirect_branch',
                                             'CALLOTHER': 'userop'}[name], 'instruction': a,
                                     'pcode_index': idx, 'target': None, 'inputs': nodes})
                reason('indirect_dependency' if name != 'CALLOTHER' else 'userop_dependency',
                       context, 'explicit target/behavior resolution required')
            if name in {'CALL', 'BRANCH', 'CBRANCH'} and nodes and isinstance(nodes[0], dict):
                target = nodes[0]
                if target.get('space') == 'ram':
                    try:
                        ta = lift.address(target['offset'])
                        if name == 'CALL' or ta not in rows:
                            dependencies.append({'kind': 'direct_call' if name == 'CALL' else
                                                 'tail_jump' if name == 'BRANCH' else 'external_conditional_branch',
                                                 'instruction': a, 'pcode_index': idx, 'target': ta})
                    except (ValueError, KeyError) as exc:
                        reason('raw_operation_invalid', context, str(exc))
                elif name == 'CALL' or target.get('space') != 'const':
                    reason('indirect_dependency', context, 'non-static control target')
            if name not in lift.OPCODES:
                reason('unsupported_opcode', context, str(name))
                for n in nodes + ([out] if out is not None else []):
                    try:
                        lift.validate_node(n, context, 433, output=n is out)
                    except (ValueError, TypeError, KeyError) as exc:
                        reason('unsupported_width_space', context, str(exc))
                continue
            try:
                if lift.integer(op.get('opcode')) != lift.OPCODES[name] or lift.integer(op.get('index')) != idx:
                    reason('opcode_index_mismatch', context, 'numeric opcode or sequence differs')
                arity = (3 if name == 'STORE' else 2 if name in {'LOAD', 'CBRANCH'} else
                         1 if name in lift.UNARY | {'BRANCH', 'CALL', 'RETURN'} else 2)
                if len(nodes) != arity:
                    reason('arity', context, f'expected {arity} inputs'); continue
                valid = True
                for n in nodes + ([out] if out is not None else []):
                    try:
                        lift.validate_node(n, context, 433, output=n is out)
                        if n['space'] == 'unique':
                            uniques.update(range(lift.integer(n['offset']), lift.integer(n['offset']) + lift.integer(n['size'])))
                    except (ValueError, TypeError, KeyError) as exc:
                        reason('unsupported_width_space', context, str(exc)); valid = False
                effect = name in {'STORE', 'BRANCH', 'CBRANCH', 'CALL', 'RETURN'}
                if effect and out is not None or not effect and out is None:
                    reason('output_contract', context, 'effect/output varnode mismatch'); valid = False
                if not valid:
                    continue
                sizes = [lift.integer(n['size']) for n in nodes]
                width = lift.integer(out['size']) if out else None
                if name in {'LOAD', 'STORE'}:
                    if nodes[0]['space'] != 'const' or lift.integer(nodes[0]['offset']) != 433 or sizes[1] != 8:
                        reason('memory_contract', context, 'requires explicit RAM 433 and eight-byte pointer')
                elif name in {'BRANCH', 'CBRANCH', 'CALL'}:
                    if nodes[0]['space'] == 'ram':
                        ta = lift.address(nodes[0]['offset'])
                        if sizes[0] != 8:
                            reason('control_width', context, 'static RAM target must be eight bytes')
                        if name == 'CBRANCH' and ta not in rows:
                            reason('external_conditional_branch', context, 'emitter supports only unconditional tail closure')
                        if name == 'CALL' and (ins.get('fallthrough') is None or canonical(ins['fallthrough']) not in rows):
                            reason('call_fallthrough', context, 'CALL needs exact return fallthrough inside caller')
                    elif nodes[0]['space'] == 'const' and name != 'CALL':
                        bits = sizes[0] * 8
                        delta = lift.integer(nodes[0]['offset']) & ((1 << bits) - 1)
                        if delta & (1 << (bits - 1)):
                            delta -= 1 << bits
                        if not 0 <= idx + delta <= len(pc):
                            reason('relative_branch', context, 'relative p-code target outside instruction')
                    if name == 'CBRANCH' and sizes[1] != 1:
                        reason('control_width', context, 'CBRANCH condition must be one byte')
                elif name == 'RETURN':
                    if sizes[0] != 8:
                        reason('control_width', context, 'RETURN target must be eight bytes')
                elif name in {'INT_ZEXT', 'INT_SEXT'}:
                    if width < sizes[0]:
                        reason('width_contract', context, 'extension narrows')
                elif name == 'SUBPIECE':
                    if nodes[1]['space'] != 'const' or lift.integer(nodes[1]['offset']) + width > sizes[0]:
                        reason('width_contract', context, 'SUBPIECE requires in-range constant byte offset')
                elif name == 'PIECE':
                    if width != sum(sizes):
                        reason('width_contract', context, 'PIECE width differs from joined inputs')
                elif name == 'POPCOUNT':
                    pass
                elif name == 'FLOAT_MULT':
                    if width not in {4, 8} or any(s != width for s in sizes):
                        reason('width_contract', context, 'float multiply requires matching binary32/binary64 widths')
                    else:
                        raw = bytes.fromhex(ins['bytes'])
                        start = 2 if len(raw) > 1 and 0x40 <= raw[1] <= 0x4f else 1
                        if (not raw or raw[0] != (0xf3 if width == 4 else 0xf2) or
                                raw[start:start+2] != b'\x0f\x59' or len(raw) <= start+2):
                            reason('unsupported_instruction', context,
                                   'FLOAT_MULT requires scalar SSE MULSS/MULSD payload ordering')
                elif name in lift.PREDICATES:
                    if (width != 1 or name.startswith('BOOL_') and any(s != 1 for s in sizes) or
                            len(sizes) == 2 and sizes[0] != sizes[1] or
                            name.startswith('FLOAT_') and sizes[0] not in {4, 8}):
                        reason('width_contract', context, 'predicate/float input or output width mismatch')
                elif name in {'INT_LEFT', 'INT_RIGHT', 'INT_SRIGHT'}:
                    if width != sizes[0]:
                        reason('width_contract', context, 'shift input/output widths differ')
                elif any(s != width for s in sizes):
                    reason('width_contract', context, 'scalar input/output widths differ')
            except (ValueError, TypeError, KeyError) as exc:
                reason('raw_operation_invalid', context, str(exc))
        if len(uniques) > 4096:
            reason('temporary_storage', a, 'unique storage exceeds 4096 instruction-local bytes')
        fall = ins.get('fallthrough')
        if fall is not None and canonical(fall) not in rows:
            reason('external_fallthrough', a, canonical(fall))
        if fall is None and (not pc or not isinstance(pc[-1], dict) or pc[-1].get('operation') not in {'BRANCH', 'RETURN'}):
            reason('missing_fallthrough', a, 'execution falls out of function')
        # Match the emitter's provable straight-line unique definition check.
        relative = any(isinstance(op, dict) and op.get('operation') in {'BRANCH', 'CBRANCH'} and
                       isinstance(op.get('inputs'), list) and op['inputs'] and
                       isinstance(op['inputs'][0], dict) and op['inputs'][0].get('space') == 'const' for op in pc)
        if not relative:
            defined = set()
            for idx, op in enumerate(pc):
                if not isinstance(op, dict):
                    continue
                for n in op.get('inputs', []) if isinstance(op.get('inputs'), list) else []:
                    if isinstance(n, dict) and n.get('space') == 'unique':
                        try:
                            offset, size = lift.integer(n['offset']), lift.integer(n['size'])
                            if not 1 <= size <= 8:
                                continue
                            needed = set(range(offset, offset + size))
                            if not needed <= defined:
                                reason('uninitialized_unique', a + f' pcode[{idx}]', str(n['offset']))
                        except (ValueError, KeyError):
                            pass  # Already recorded as invalid varnode above.
                n = op.get('output')
                if isinstance(n, dict) and n.get('space') == 'unique':
                    try:
                        offset, size = lift.integer(n['offset']), lift.integer(n['size'])
                        if 1 <= size <= 8:
                            defined.update(range(offset, offset + size))
                    except (ValueError, KeyError):
                        pass
                if op.get('operation') in {'BRANCH', 'RETURN'}:
                    break
    return {'local_structural_candidate': not reasons, 'structural_reasons': reasons,
            'opcode_inventory': dict(sorted(inventory.items())), 'dependencies': dependencies}


def closure_groups(functions):
    """Retain every edge; SCCs expose cycles without exponential traversal."""
    by_entry = {f['address']: f for f in functions}
    graph = {a: {e['target'] for e in f['dependencies'] if e.get('target') in by_entry}
             for a, f in by_entry.items()}
    # Iterative transitive closure avoids recursion limits for 1024-entry batches.
    groups = []
    for entry, row in by_entry.items():
        reached, pending = set(), list(graph[entry])
        while pending:
            target = pending.pop()
            if target not in reached:
                reached.add(target); pending.extend(graph[target] - reached)
        row['transitive_dependencies_in_batch'] = sorted(reached - {entry})
        row['recursive_closure'] = entry in reached
        missing = sorted({edge['target'] for a in reached | {entry}
                          for edge in by_entry[a]['dependencies']
                          if edge.get('target') and edge['target'] not in by_entry})
        row['missing_dependency_packets'] = missing
        blockers = []
        for a in sorted(reached | {entry}):
            member = by_entry[a]
            if not member['local_structural_candidate']:
                blockers.append({'kind': 'dependency_unsupported', 'target': a})
            if member.get('raw_status') != 'verified':
                blockers.append({'kind': 'dependency_raw_unverified', 'target': a})
            for edge in member['dependencies']:
                if edge.get('target') is None:
                    blockers.append({'kind': 'unresolved_dependency', 'target': a, 'edge': edge})
        blockers += [{'kind': 'missing_dependency', 'target': a} for a in missing]
        # Detect every reachable cycle, including a cycle beyond this entry,
        # using Kahn's acyclic elimination.
        active = reached | {entry}
        indegree = {a: 0 for a in active}
        for a in active:
            for b in graph[a] & active:
                indegree[b] += 1
        queue = [a for a, degree in indegree.items() if not degree]
        order = []
        while queue:
            a = queue.pop(); order.append(a)
            for b in graph[a] & active:
                indegree[b] -= 1
                if indegree[b] == 0:
                    queue.append(b)
        if len(order) != len(active):
            blockers.append({'kind': 'recursive_dependency_cycle', 'target': entry})
        else:
            depths = {}
            for a in reversed(order):
                depths[a] = 1 + max((depths[b] for b in graph[a]), default=0)
            row['closure_depth'] = depths[entry]
            if depths[entry] > 64:
                blockers.append({'kind': 'closure_depth_limit', 'target': entry,
                                 'depth': depths[entry], 'maximum': 64})
        row['closure_reasons'] = blockers
        row['structural_closure_candidate'] = not blockers
        if row['structural_closure_candidate']:
            groups.append(sorted(active))
    unique = sorted({tuple(g) for g in groups})
    return [{'entries': list(g), 'meaning': 'structural closure only; ABI and ownership review required'} for g in unique]


def load_raw(raw_dir, original):
    """Validate manifest strictly; no absent/stale index entries silently skipped."""
    raw_dir = raw_dir.resolve()
    manifest_path = raw_dir / 'manifest.json'
    manifest = json.loads(manifest_path.read_text())
    if (manifest.get('schema') != 2 or manifest.get('original_elf_sha256') != original.sha256 or
            manifest.get('ghidra_version') != VERSION or manifest.get('language') != 'x86:LE:64:default' or
            manifest.get('program_modified_by_script') is not False or manifest.get('game_executed') is not False):
        raise ValueError('Raw manifest schema/program/tool identity or read-only flags differ')
    entries, inputs = {}, [manifest_path]
    rows = manifest.get('functions')
    if not isinstance(rows, list) or not 1 <= len(rows) <= MAX_BATCH:
        raise ValueError('Raw manifest must contain 1..1024 exact function entries')
    symbols = {}
    for s in original.symbols:
        if s.size and s.kind in 'TtWw':
            previous = symbols.get(s.address)
            if previous and previous.size != s.size:
                raise ValueError(f'Ambiguous original symbol sizes at {s.address:#x}')
            symbols[s.address] = s
    for row in rows:
        entry = canonical(row['address'])
        if entry in entries:
            raise ValueError('Duplicate normalized manifest function: ' + entry)
        path = (raw_dir / row['json']).resolve()
        if not path.is_relative_to(raw_dir) or not path.is_file() or (raw_dir / row['json']).is_symlink():
            raise ValueError('Raw manifest references missing/unsafe packet: ' + row['json'])
        inputs.append(path)
        packet_bytes = path.read_bytes()
        packet = json.loads(packet_bytes)
        packet_sha = hashlib.sha256(packet_bytes).hexdigest()
        if row.get('status') != 'exported':
            if canonical(packet.get('address')) != entry or packet.get('original_elf_sha256') != original.sha256:
                raise ValueError('Failed raw entry identity differs: ' + entry)
            entries[entry] = {'raw_status': row.get('status', 'failed'), 'packet': packet,
                              'raw_sha256': packet_sha, 'raw_path': str(path),
                              'identity_error': packet.get('error', 'not exported')}
            continue
        symbol = symbols.get(int(entry, 16))
        if symbol is None:
            raise ValueError('Exported address is not an exact sized ELF function symbol: ' + entry)
        verification = validate_raw(packet, original, symbol, entry)
        entries[entry] = {'raw_status': 'verified', 'packet': packet,
                          'raw_sha256': packet_sha, 'raw_path': str(path),
                          'original_verification': verification}
    return entries, inputs, manifest


def merge_raw(existing, members):
    """Join independently validated batches without dropping contradictory status.

    Exact duplicate packet bytes with the same export status are reusable. A
    hash or status conflict rejects the union before any member is inserted;
    otherwise input fingerprints/manifests retain both source provenances.
    """
    for entry, source in members.items():
        previous = existing.get(entry)
        if previous is not None and (previous['raw_sha256'] != source['raw_sha256'] or
                                     previous['raw_status'] != source['raw_status']):
            raise ValueError('Conflicting duplicate raw entry across batches: ' + entry)
    for entry, source in members.items():
        existing.setdefault(entry, source)


def make_report(selection, raw, abi=None):
    """No ledger writes or generated C++ publication anywhere in screening."""
    if abi is not None and (abi.get('schema') != 1 or abi.get('original_elf_sha256') != ELF_SHA or
                            lift.integer(abi.get('memory_space_id')) != 433 or
                            not isinstance(abi.get('functions'), dict)):
        raise ValueError('Explicit reviewed ABI schema/ELF/RAM identity differs')
    descriptors = {canonical(k): v for k, v in (abi or {}).get('functions', {}).items()}
    if len(descriptors) != len((abi or {}).get('functions', {})):
        raise ValueError('Duplicate normalized reviewed ABI address')
    functions = []
    # Available dependency packets remain in the report even outside the selected
    # scheduling slice. They are not promoted to residual candidates.
    selected = {r['address']: r for r in selection['selected']}
    for entry in sorted(selected.keys() | raw.keys()):
        source = raw.get(entry)
        row = {**selected.get(entry, {}), 'address': entry,
               'selected_residual': entry in selected,
               'raw_status': source['raw_status'] if source else 'missing_packet',
               'abi_status': 'missing_reviewed_abi', 'owner_status': 'missing_production_owner_review',
               'production_ready': False,
               'readiness_reasons': [{'kind': 'owner_gap', 'detail': 'production state owner and real effect consumers require review'}]}
        if source and source['raw_status'] == 'verified':
            row.update(screen_packet(source['packet']))
            row.update({k: v for k, v in source.items() if k != 'packet'})
            if entry in descriptors:
                try:
                    # An actual supplied ABI can be checked by the current
                    # emitter. No synthetic registers/returns are introduced.
                    lift.compile_function(source['packet'], descriptors[entry], 433,
                                          source['raw_sha256'], set(raw) & descriptors.keys())
                    row['abi_status'] = 'explicit_abi_preflight_passed'
                except (ValueError, KeyError, TypeError) as exc:
                    row['abi_status'] = 'explicit_abi_rejected'
                    row['readiness_reasons'].append({'kind': 'abi_gap', 'detail': str(exc)})
        else:
            row.update(local_structural_candidate=False, dependencies=[], opcode_inventory={},
                       structural_reasons=[{'kind': 'raw_gap', 'context': entry,
                                            'detail': source.get('identity_error', 'raw export absent') if source else 'raw export absent'}])
        if entry not in descriptors:
            row['readiness_reasons'].append({'kind': 'abi_gap', 'detail': 'exact input register bytes and return contract not reviewed'})
        functions.append(row)
    groups = closure_groups(functions)
    counts = Counter()
    for row in functions:
        if row['selected_residual']:
            counts['selected'] += 1
            counts['local_structural_candidate'] += row['local_structural_candidate']
            counts['structural_closure_candidate'] += row['structural_closure_candidate']
            for reason in row['structural_reasons'] + row['closure_reasons']:
                counts['reason:' + reason['kind']] += 1
    verified = [row for row in functions if row['address'] in raw and row['raw_status'] == 'verified']
    raw_counts = {
        'supplied_unique_entries': len(raw),
        'status_counts': dict(sorted(Counter(source['raw_status'] for source in raw.values()).items())),
        'verified': len(verified),
        'local_structural_candidate': sum(row['local_structural_candidate'] for row in verified),
        'structural_closure_candidate': sum(row['structural_closure_candidate'] for row in verified),
        'production_ready': sum(row['production_ready'] for row in verified),
        'abi_status_counts': dict(sorted(Counter(row['abi_status'] for row in verified).items())),
        'owner_status_counts': dict(sorted(Counter(row['owner_status'] for row in verified).items())),
        'structural_reason_occurrences': dict(sorted(Counter(
            reason['kind'] for row in verified for reason in row['structural_reasons']).items())),
        'structural_reason_function_counts': dict(sorted(Counter(
            kind for row in verified for kind in {r['kind'] for r in row['structural_reasons']}).items())),
        'closure_reason_occurrences': dict(sorted(Counter(
            reason['kind'] for row in verified for reason in row['closure_reasons']).items())),
        'closure_reason_function_counts': dict(sorted(Counter(
            kind for row in verified for kind in {r['kind'] for r in row['closure_reasons']}).items())),
    }
    return {'schema': 1, 'kind': 'raw-function-lift-screening',
            'meaning': 'Generation feasibility only. No ABI inference, production acceptance or original completion promotion.',
            'selection': selection, 'counts': dict(sorted(counts.items())), 'functions': functions,
            'raw_packet_counts': raw_counts,
            'counts_meaning': {
                'counts': 'Selected residual rows only; reason:* counts occurrences, not affected functions.',
                'raw_packet_counts': 'Unique supplied raw entries; structural, readiness and reason totals cover verified raw rows, including dependency-only rows outside the selection limit.',
                'closure_reason_occurrences': 'Edges/blockers propagated through each caller closure; one original dependency may recur for many callers. Distinct affected functions are separate *_function_counts.',
                'structural_closure_candidate': 'All required raw dependencies across supplied batches structurally supported, with no missing/indirect/cyclic/depth blocker. ABI and production owner review remain separate.'},
            'structural_closure_groups': groups, 'original_status_promotions': 0,
            'game_executed': False, 'original_modified': False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--scope', choices=['ui', 'all'], default='all')
    parser.add_argument('--limit', type=int, required=True, help='explicit bounded batch size, 1..1024')
    parser.add_argument('--offset', type=int, default=0, help='deterministic residual-manual queue offset')
    parser.add_argument('--address', action='append', default=[])
    parser.add_argument('--output', type=Path, required=True, help='fresh directory under ignored build or /tmp')
    parser.add_argument('--original', type=Path, default=Path(ELF_PATH))
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--raw-dir', type=Path, action='append', help='analyze existing exported packets; repeat to join dependency batches')
    mode.add_argument('--export', action='store_true', help='export selected raw p-code from saved pinned project, read-only')
    parser.add_argument('--abi', type=Path, help='optional actual reviewed ABI; no defaults are invented')
    parser.add_argument('--home', type=Path, default=ROOT / 'build-source-cache/ghidra' / DIRECTORY)
    parser.add_argument('--analysis-root', type=Path, default=ROOT / 'build-ghidra')
    args = parser.parse_args()
    published = False
    try:
        selection, builder = select(ROOT, args.scope, args.limit, args.offset, args.address)
        protected = [args.original.resolve().parent, *builder.input_paths]
        protected += (args.raw_dir or []) + [p for p in (args.abi, args.home, args.analysis_root) if p]
        validate_output(ROOT, args.output, protected, directory=True)
        if args.output.exists():
            raise ValueError('Use a fresh output directory; existing evidence is preserved')
        input_paths = list(builder.input_paths) + [ROOT / 'research/ui-contour.json']
        # Whole-function exclusion freshness depends on these reviewed pins,
        # as well as the transfer ledger itself.
        for record in builder.transfers.values():
            accepted = record.get('completion') if isinstance(record, dict) else None
            pins = accepted.get('inputs', {}) if isinstance(accepted, dict) else {}
            if isinstance(pins, dict):
                for relative in pins:
                    if not isinstance(relative, str):
                        continue
                    path = ROOT / relative
                    if path.is_file() and not path.is_symlink() and path.resolve().is_relative_to(ROOT):
                        input_paths.append(path)
        tiny = ROOT / 'research/tiny-functions.json'
        if tiny.is_file():
            input_paths.append(tiny)
        for name in ('screen_function_lifts.py', 'lift_pcode.py', 'auto_triage.py',
                     'original.py', 'automation_state.py', 'transfer_contract.py', 'setup_ghidra.py',
                     'ghidra/ExportLiftBatch.java'):
            input_paths.append(ROOT / 'tools' / name)
        if args.abi:
            input_paths.append(args.abi)
        before = {str(p.resolve()): digest(p) for p in input_paths}
        original = Original(args.original) if args.export or args.raw_dir else None
        args.output.mkdir(parents=True)
        published = True
        write_json(args.output / 'selection.json', selection)
        targets = args.output / 'targets.txt'
        targets.write_text(''.join(r['address'] + '\n' for r in selection['selected']))
        raw_dirs, installation = args.raw_dir or [], None
        if args.export:
            if not selection['selected']:
                raise ValueError('No residual manual entries selected; no Ghidra export launched')
            home = args.home.resolve(); project = args.analysis_root.resolve()
            installation = verify_installation(home)
            if not (project / 'project/OpenTorchlight.gpr').is_file():
                raise ValueError('Saved pinned Ghidra project absent')
            raw_dir = args.output / 'raw'
            raw_dirs = [raw_dir]
            command = [str(home / 'support/analyzeHeadless'), str(project / 'project'), 'OpenTorchlight',
                       '-max-cpu', '2', '-process', original.path.name, '-noanalysis', '-readOnly',
                       '-scriptPath', str(ROOT / 'tools/ghidra'), '-postScript', 'ExportLiftBatch.java',
                       str(targets.resolve()), str(raw_dir.resolve()), original.sha256]
            env = {**os.environ, 'XDG_CONFIG_HOME': str(project / 'config'),
                   'XDG_CACHE_HOME': str(project / 'cache')}
            with (args.output / 'headless.log').open('w') as log:
                subprocess.run(command, env=env, stdout=log, stderr=subprocess.STDOUT, check=True, timeout=900)
        raw, manifests = {}, []
        for raw_dir in raw_dirs:
            manifest_path = raw_dir.resolve() / 'manifest.json'
            before[str(manifest_path)] = digest(manifest_path)
            members, raw_inputs, manifest = load_raw(raw_dir, original)
            manifests.append(manifest)
            merge_raw(raw, members)
            input_paths.extend(raw_inputs)
            before.update({source['raw_path']: source['raw_sha256'] for source in members.values()})
            if args.export and set(raw) != {r['address'] for r in selection['selected']}:
                raise ValueError('Export manifest differs from exact selected source entries')
        abi = json.loads(args.abi.read_text()) if args.abi else None
        report = make_report(selection, raw, abi)
        after = {p: digest(Path(p)) for p in before}
        report['status'] = 'SCREENED' if before == after else 'STALE'
        report['source_consistent'] = before == after
        report['input_sha256'] = {str(p.resolve()): digest(p) for p in input_paths}
        report['original_elf'] = {'path': str(args.original.resolve()), 'sha256': ELF_SHA,
                                  'verified_this_run': original is not None}
        report['ghidra_manifest'] = manifests[0] if len(manifests) == 1 else None
        report['ghidra_manifests'] = manifests
        report['tool_installation'] = installation
        report['callsite_index'] = {'available': builder.have_callsites,
                                    'metadata_validated': builder.callsites_metadata is not None,
                                    'metadata': builder.callsites_metadata,
                                    'boundary': 'direct CALL scheduling context only; no-CALL does not imply leaf; raw tail and indirect edges retained'}
        write_json(args.output / 'report.json', report)
        print(f"Screened {len(selection['selected'])}/{selection['residual_manual_total']} residual manual entries: {args.output / 'report.json'}")
        return 0 if report['source_consistent'] else 2
    except (OSError, ValueError, KeyError, TypeError, subprocess.SubprocessError) as exc:
        if published:
            write_json(args.output / 'report.json', {'schema': 1, 'kind': 'raw-function-lift-screening',
                       'status': 'FAILED', 'reason': str(exc), 'original_status_promotions': 0})
        parser.exit(2, f'Function lift screening rejected: {exc}\n')


if __name__ == '__main__':
    raise SystemExit(main())
