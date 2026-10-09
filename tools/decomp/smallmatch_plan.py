#!/usr/bin/env python3
"""Read-only small-function triage and complete, deduplicated review packets.

This is an ignored planning report, not a new acceptance registry. Historical
MATCH receipts are used only to avoid re-proposing work. Neither shape groups,
header exports nor generated hypotheses constitute new MATCH evidence.
"""
import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import re
import time

import llm_definitions
import objdiff
import smallmatch
import smallmatch_families


def sha(path):
    h = hashlib.sha256()
    with Path(path).open('rb') as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b''):
            h.update(chunk)
    return h.hexdigest()


def safe_child(root, relative):
    root = Path(root).resolve()
    path = (root / relative).resolve()
    if not path.is_relative_to(root):
        raise ValueError('input path escapes its declared root: ' + str(relative))
    return path


def historical_ids(targets, ledger, summary, elf_hash):
    if ledger is None:
        if summary is not None:
            raise ValueError('a prior summary requires its ledger')
        return set()
    if summary is None or summary.get('original_elf_sha256') != elf_hash:
        raise ValueError('prior receipt must refer to this original ELF')
    if summary.get('target_count') != len(targets):
        raise ValueError('prior receipt target scope differs')
    seen, accepted = set(), set()
    for row in ledger:
        address = row.get('address')
        if address in seen or address not in targets:
            raise ValueError('duplicate or foreign address in prior ledger')
        seen.add(address)
        if row.get('original_size') != targets[address]['size']:
            raise ValueError('prior ledger size differs from original target')
        if row.get('status') == 'MATCH':
            accepted.add(address)
    if seen != set(targets) or len(accepted) != summary.get('new_match_count'):
        raise ValueError('prior ledger is incomplete or disagrees with its summary')
    return accepted


def family_hint(f, insns):
    """Navigation only; operands and per-target ASM remain in the evidence."""
    ops = [(m, p) for _, m, p in insns if not objdiff.Normalizer.padding(m, p)]
    if f.get('kind') in ('ctor', 'dtor'):
        return 'constructors' if f['kind'] == 'ctor' else 'destructors'
    if len(ops) <= 2 and ops and ops[-1][0] in ('ret', 'repz ret'):
        if len(ops) == 1:
            return 'empty_or_return'
        if any('(%rdi)' in p for _, p in ops):
            return 'direct_field_access'
        return 'constant_or_direct_return'
    if len(ops) == 1 and ops[0][0] == 'jmp':
        return 'tail_wrappers'
    if any('std::' in p or 'TArrayList<' in p for _, p in ops):
        return 'containers_or_strings'
    if len(ops) <= 20:
        return 'short_guards_and_wrappers'
    return 'control_flow_review'


def definition_groups(targets, db, previous):
    index = llm_definitions.DefinitionIndex(db)
    grouped = defaultdict(list)
    for f in targets.values():
        if f['address'] not in previous:
            grouped[(f.get('tu'), llm_definitions.identity(f))].append(f)
    result = []
    for rows in grouped.values():
        rows.sort(key=lambda f: ('thunk to ' in f['demangled'], bool(f.get('clone')),
                                f.get('kind') == 'compiler', int(f['address'], 16)))
        primary = rows[0]
        closure = index.closure(primary)
        outside = sorted(a for a in closure if a not in targets or db['functions'][a]['size'] >= 1000)
        result.append((primary, sorted(f['address'] for f in rows), sorted(closure), outside))
    return sorted(result, key=lambda row: (row[0]['tu_name'], int(row[0]['address'], 16)))


def build(kit, root, output, ledger=None, summary=None, owner=None, packets=0,
          packet_definitions=12, max_packet_chars=350000):
    started = time.perf_counter()
    kit, root, output = [Path(p).resolve() for p in (kit, root, output)]
    for forbidden in (root / 'decomp', root / 'tools', root / 'third_party', kit / 'original'):
        if output.is_relative_to(forbidden):
            raise ValueError('planning output must not overwrite source or original inputs')
    if output.exists() and any(output.iterdir()):
        raise ValueError('use a new empty planning directory; existing work is not deleted')
    if packets < 0 or packet_definitions < 1 or max_packet_chars < 1024:
        raise ValueError('invalid packet limits')
    g = smallmatch.Generator(kit, root)
    targets = {f['address']: f for f in g.targets}
    if len(targets) != len(g.targets):
        raise ValueError('duplicate target addresses')
    original_hash = sha(kit / 'original/Torchlight.bin.x86_64')
    if original_hash != g.db.get('original_elf_sha256') or original_hash != g.types.get('original_elf_sha256'):
        raise ValueError('original ELF, database and type export disagree')
    for f in targets.values():
        original = g.db['functions'].get(f['address'], {})
        if any(f.get(k) != original.get(k) for k in ('size', 'tu', 'mangled')) or f['size'] >= 1000:
            raise ValueError('target identity or small-function scope differs from database')
        safe_child(kit, f['assembly'])
    previous = historical_ids(targets, ledger, summary, original_hash)
    owners_path = root / 'decomp/owners.json'
    ownership = json.loads(owners_path.read_text()) if owners_path.exists() else {}
    owners = ownership.get('tus', {})
    if packets and (not owner or owner not in ownership.get('owners', {})):
        raise ValueError('packet preparation requires an existing worker name via --owner; ownership is never reassigned')
    source_hashes = {p.relative_to(root).as_posix(): sha(p)
                     for folder in ('decomp/include', 'decomp/src')
                     for p in sorted((root / folder).rglob('*')) if p.is_file()}
    target_rows, proposals = [], []
    for f, pending, closure, outside in definition_groups(targets, g.db, previous):
        asm = safe_child(kit, f['assembly'])
        insns = objdiff.parse_insns(asm.read_text())
        row = {'address': f['address'], 'name': f['demangled'], 'tu': f['tu_name'],
               'scope': f.get('scope', ''), 'pending_addresses': pending, 'abi_closure': closure,
               'original_bytes': sum(targets[a]['size'] for a in pending),
               'owner': owners.get(f['tu_name']), 'family_hint': family_hint(f, insns),
               'shape_hint': f.get('opcode_shape_hash'), 'assembly': f['assembly'],
               'assembly_sha256': sha(asm), 'status': 'REVIEW', 'reasons': []}
        if outside:
            row.update(status='OUT_OF_SCOPE_ABI', reasons=['ABI variants require work outside the fixed small queue'],
                       excluded_siblings=outside)
        elif f.get('clone') or 'thunk to ' in f['demangled'] or f.get('kind') == 'compiler':
            row.update(status='COMPILER_OUTPUT', reasons=['No ordinary source-definition representative in this scope'])
        elif f.get('source_status') != 'MISSING' or g.prior_definition(f):
            row.update(status='EXISTING_SOURCE_REVIEW', reasons=['Preserve the existing definition; it is not accepted by this planner'])
        else:
            for provider in (g.generate, lambda target: smallmatch_families.generate(g, target)):
                try:
                    proposal = provider(f)
                except smallmatch.Unsupported as exc:
                    row['reasons'].append(str(exc))
                else:
                    row.update(status='HYPOTHESIS', family_hint=proposal['family'], reasons=[])
                    proposal['status'] = 'UNVERIFIED'
                    proposals.append(proposal)
                    break
        if row['owner'] and row['owner'] != owner:
            row['scheduling'] = 'OWNED_BY_OTHER_WORKER'
        else:
            row['scheduling'] = 'REVIEW_ONLY' if not owner else 'ELIGIBLE_FOR_REVIEW_PACKET'
        target_rows.append(row)
    groups = defaultdict(list)
    for row in target_rows:
        groups[(row['tu'], row['family_hint'], row['status'])].append(row)
    priority = {'HYPOTHESIS': 0, 'REVIEW': 1, 'EXISTING_SOURCE_REVIEW': 2,
                'COMPILER_OUTPUT': 3, 'OUT_OF_SCOPE_ABI': 4}
    clusters = []
    for (tu, family, status), rows in groups.items():
        clusters.append({'tu': tu, 'family_hint': family, 'status': status,
                         'definitions': len(rows), 'pending_addresses': sum(len(r['pending_addresses']) for r in rows),
                         'original_bytes': sum(r['original_bytes'] for r in rows),
                         'representatives': [r['address'] for r in rows], 'owner': rows[0]['owner']})
    clusters.sort(key=lambda x: (priority[x['status']], -x['definitions'], -x['original_bytes'], x['tu'], x['family_hint']))
    output.mkdir(parents=True, exist_ok=True)
    packet_log = []
    packet_groups = sorted(clusters, key=lambda x: (-min(x['definitions'], packet_definitions),
                                                    priority[x['status']], -x['original_bytes'], x['tu'], x['family_hint']))
    for group in packet_groups:
        if sum(r['status'] == 'WRITTEN' for r in packet_log) >= packets:
            break
        if group['status'] not in ('REVIEW', 'HYPOTHESIS') or (group['owner'] and group['owner'] != owner):
            continue
        selected = group['representatives'][:packet_definitions]
        functions = []
        headers = set()
        missing = []
        callees = {}
        for address in selected:
            f = targets[address]
            functions.append({'original_symbol': f,
                'asm': safe_child(kit, f['assembly']).read_text(),
                'historical_type_export_not_live_proof': g.types['prototypes'].get(address),
                'historical_class_export_not_live_proof': g.types['classes'].get(f.get('scope'))})
            headers.update(h for h, _ in g.declarations.get(f.get('qualified'), ()))
            for callee_address in f.get('direct_targets', []):
                if callee_address in callees:
                    continue
                cf = g.db['functions'].get(callee_address)
                if not cf:
                    callees[callee_address] = {'symbol': None, 'asm': None}
                    missing.append({'address': callee_address, 'reason': 'external/unknown symbol'})
                    continue
                headers.update(h for h, _ in g.declarations.get(cf.get('qualified'), ()))
                cp = safe_child(kit, targets[callee_address]['assembly']) if callee_address in targets else kit / 'reference/direct-callees' / (callee_address + '.asm')
                callees[callee_address] = {'symbol': cf, 'asm': cp.read_text() if cp.is_file() else None}
                if not cp.is_file():
                    missing.append({'address': callee_address, 'reason': 'direct-callee ASM unavailable'})
        header_texts = {name: safe_child(root / 'decomp/include', name).read_text() for name in sorted(headers)}
        source_path = safe_child(root / 'decomp/src', group['tu'])
        packet = {'schema': 1, 'status': 'REVIEW_ONLY', 'tu': group['tu'], 'family_hint': group['family_hint'],
                  'original_elf_sha256': original_hash, 'owner': group['owner'],
                  'functions': functions, 'headers': header_texts, 'direct_callees': callees,
                  'missing_context': missing,
                  'existing_full_tu': source_path.read_text() if source_path.exists() else '',
                  'limits': 'Navigation input, not a COMPLETE Ghidra receipt or an accepted implementation. Use llm_loop --prepare-only before a subagent writes code.'}
        payload = json.dumps(packet, ensure_ascii=False, indent=1) + '\n'
        if len(payload) > max_packet_chars:
            packet_log.append({'tu': group['tu'], 'status': 'BLOCKED_PACKET_SIZE', 'characters': len(payload),
                               'limit': max_packet_chars, 'addresses': selected})
            continue
        packet_id = hashlib.sha256(json.dumps([group['tu'], selected]).encode()).hexdigest()[:12]
        path = output / 'packets' / (packet_id + '.json')
        path.parent.mkdir(exist_ok=True)
        path.write_text(payload)
        packet_log.append({'tu': group['tu'], 'status': 'WRITTEN', 'path': str(path.relative_to(output)),
                           'addresses': selected, 'characters': len(payload), 'missing_context_items': len(missing),
                           'sha256': sha(path)})
    # Detect concurrent edits instead of stamping old packets with a new source tree.
    current = {p.relative_to(root).as_posix(): sha(p)
               for folder in ('decomp/include', 'decomp/src')
               for p in sorted((root / folder).rglob('*')) if p.is_file()}
    if current != source_hashes:
        raise RuntimeError('Source/header snapshot changed during planning; rerun in a fresh output directory')
    report = {'schema': 1, 'mode': 'READ_ONLY_PLANNING', 'original_elf_sha256': original_hash,
              'target_count': len(targets), 'historical_match_addresses': len(previous),
              'remaining_addresses': len(targets) - len(previous), 'remaining_definition_groups': len(target_rows),
              'clusters': len(clusters), 'states': dict(Counter(r['status'] for r in target_rows)),
              'hypotheses_unverified': len(proposals), 'new_match_claims': 0,
              'owner_filter': owner, 'packet_log': packet_log,
              'snapshot_sha256': hashlib.sha256(json.dumps(source_hashes, sort_keys=True).encode()).hexdigest(),
              'source_file_sha256': source_hashes,
              'type_export_sha256': sha(kit / 'reference/types.json'),
              'elf_database_sha256': sha(kit / 'reference/elfdb.json'),
              'target_json_sha256': sha(kit / 'targets.json'),
              'game_executions': 0, 'compiler_executions': 0, 'model_calls': 0,
              'elapsed_seconds': time.perf_counter() - started}
    for name, value in [('summary', report), ('queue', target_rows), ('clusters', clusters), ('hypotheses', proposals)]:
        (output / (name + '.json')).write_text(json.dumps(value, ensure_ascii=False, indent=1) + '\n')
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('kit', 'root', 'output'):
        parser.add_argument('--' + name, type=Path, required=True)
    parser.add_argument('--previous-ledger', type=Path)
    parser.add_argument('--previous-summary', type=Path)
    parser.add_argument('--owner')
    parser.add_argument('--packets', type=int, default=0)
    parser.add_argument('--packet-definitions', type=int, default=12)
    parser.add_argument('--max-packet-chars', type=int, default=350000)
    args = parser.parse_args()
    load = lambda p: json.loads(p.read_text()) if p else None
    r = build(args.kit, args.root, args.output, load(args.previous_ledger), load(args.previous_summary),
              args.owner, args.packets, args.packet_definitions, args.max_packet_chars)
    print(json.dumps({k: v for k, v in r.items() if k != 'source_file_sha256'}, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()
