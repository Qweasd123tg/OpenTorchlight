#!/usr/bin/env python3
"""Plan exact raw dependency exports without inference or acceptance changes.

The input is screen_function_lifts.make_report() plus the exact ELF symbol
index. Only direct CALL and unconditional tail edges extend an export plan.
Existing verified packets are reused even when their lowering is unsupported.
"""
from __future__ import annotations

import json
from collections import Counter

from function_package import normalize

MAX_BATCH = 1024
STATIC_EDGES = frozenset({'direct_call', 'tail_jump'})


def _address(value):
    if not isinstance(value, str):
        raise ValueError('exact hexadecimal address must be a string')
    return '0x' + normalize(value)


def _sort_address(value):
    return int(value, 16)


def _site(caller, edge):
    instruction = edge.get('instruction')
    if instruction is not None:
        instruction = _address(instruction)
    index = edge.get('pcode_index')
    if index is not None and (not isinstance(index, int) or isinstance(index, bool) or index < 0):
        raise ValueError('invalid p-code site index')
    return {'address': caller, 'instruction': instruction,
            'pcode_index': index, 'kind': edge.get('kind')}


def _site_key(site):
    return (_sort_address(site['address']),
            _sort_address(site['instruction']) if site['instruction'] is not None else -1,
            site['pcode_index'] if site['pcode_index'] is not None else -1,
            str(site['kind']))


def build_dependency_plan(report, symbols, max_batch=MAX_BATCH):
    """Return a deterministic, deduplicated export frontier for selected roots.

    ``symbols`` accepts FunctionPackageBuilder's normalized keys with
    aliases/size, or equivalent address/symbol/size rows. Symbol interiors,
    unknown entries and unresolved control flow never become export targets.
    A retry of a supplied failed export is explicit; it is not a claim that a
    repeated Ghidra export will repair an absent function boundary.
    """
    if not isinstance(max_batch, int) or isinstance(max_batch, bool) or not 1 <= max_batch <= MAX_BATCH:
        raise ValueError('max_batch must be 1..1024')
    if not isinstance(report, dict) or not isinstance(report.get('functions'), list):
        raise ValueError('screening report requires functions')
    if report.get('kind') != 'raw-function-lift-screening' or report.get('schema') != 1:
        raise ValueError('unsupported screening report schema/kind')
    if report.get('status') not in (None, 'SCREENED') or report.get('source_consistent') is False:
        raise ValueError('dependency planning requires a current screening report')
    if not isinstance(symbols, dict):
        raise ValueError('exact symbol index must be a dictionary')

    rows = {}
    for row in report['functions']:
        entry = _address(row['address'])
        if entry in rows:
            raise ValueError('duplicate normalized report entry: ' + entry)
        rows[entry] = row
    exact = {}
    for key, symbol in symbols.items():
        entry = _address(key)
        if entry in exact:
            raise ValueError('duplicate normalized symbol entry: ' + entry)
        if not isinstance(symbol, dict):
            raise ValueError('exact symbol row must be a dictionary')
        if symbol.get('address') is not None and _address(symbol['address']) != entry:
            raise ValueError('symbol row address differs from exact index key: ' + entry)
        size = symbol.get('size')
        if not isinstance(size, int) or isinstance(size, bool) or size < 0:
            raise ValueError('invalid exact symbol size: ' + entry)
        if int(entry, 16) + size > 1 << 64:
            raise ValueError('exact symbol range exceeds address space: ' + entry)
        aliases = symbol.get('aliases', [])
        name = symbol.get('symbol')
        if name is None:
            if not isinstance(aliases, list) or any(not isinstance(a, str) for a in aliases):
                raise ValueError('invalid exact symbol aliases: ' + entry)
            name = min(aliases) if aliases else ''
        if not isinstance(name, str):
            raise ValueError('invalid exact symbol name: ' + entry)
        exact[entry] = {'address': entry, 'symbol': name, 'size': size,
                        'ambiguous_sizes': symbol.get('ambiguous_sizes') is True}

    roots = sorted((a for a, row in rows.items() if row.get('selected_residual') is True), key=_sort_address)
    targets, blocked = {}, {}

    def add_block(root, kind, target=None, **detail):
        value = {'kind': kind, 'target': target, **detail}
        key = json.dumps(value, sort_keys=True, separators=(',', ':'))
        if key not in blocked:
            blocked[key] = {**value, 'roots': set()}
        blocked[key]['roots'].add(root)

    def need_export(root, entry, site=None):
        source = rows.get(entry)
        status = source.get('raw_status', 'missing_packet') if source else 'missing_packet'
        if status == 'verified':
            return
        symbol = exact.get(entry)
        if symbol and symbol['ambiguous_sizes']:
            add_block(root, 'ambiguous_symbol_size', entry, previous_raw_status=status,
                      **({'site': site} if site else {}))
            return
        if symbol is None or not symbol['size']:
            containing = next((s['address'] for a, s in sorted(exact.items(), key=lambda pair: _sort_address(pair[0]))
                               if int(a, 16) < int(entry, 16) < int(a, 16) + s['size']), None)
            add_block(root, 'not_exact_sized_symbol', entry, previous_raw_status=status,
                      containing_symbol=containing, **({'site': site} if site else {}))
            return
        if entry not in targets:
            retry = status != 'missing_packet'
            targets[entry] = {**{k: v for k, v in symbol.items() if k != 'ambiguous_sizes'},
                              'roots': set(), 'callers': {},
                              'previous_raw_status': status, 'retry': retry,
                              'export_reason': ('retry_missing_function' if status == 'missing_function' else
                                                'retry_unverified_packet' if retry else 'missing_packet')}
        targets[entry]['roots'].add(root)
        if site is not None:
            targets[entry]['callers'][_site_key(site)] = site

    for root in roots:
        visited, pending = set(), [root]
        while pending:
            entry = pending.pop()
            if entry in visited:
                continue
            visited.add(entry)
            row = rows[entry]
            need_export(root, entry)
            if row.get('raw_status') == 'verified' and not row.get('local_structural_candidate'):
                reasons = [{'kind': r.get('kind'), 'context': r.get('context'), 'detail': r.get('detail')}
                           for r in row.get('structural_reasons', [])]
                reasons.sort(key=lambda r: json.dumps(r, sort_keys=True))
                add_block(root, 'unsupported_supplied', entry, reasons=reasons)
            for edge in row.get('dependencies', []):
                site = _site(entry, edge)
                kind, raw_target = edge.get('kind'), edge.get('target')
                if kind not in STATIC_EDGES:
                    # A candidate attached to an indirect edge is still not an
                    # approved target. Never export it or traverse its body.
                    target = None
                    if kind == 'external_conditional_branch' and raw_target is not None:
                        try:
                            target = _address(raw_target)
                        except ValueError:
                            pass
                    add_block(root, kind or 'unresolved_dependency', target, site=site,
                              detail='control dependency requires explicit resolution; not an export edge')
                    continue
                try:
                    target = _address(raw_target)
                except ValueError:
                    add_block(root, 'invalid_static_target', site=site,
                              detail='direct/tail dependency lacks an exact hexadecimal target')
                    continue
                need_export(root, target, site)
                if target in rows:
                    pending.append(target)
            # These are preflight barriers, not missing exports. Preserve the
            # screen's whole reachable-cycle/depth result without inferring ABI.
        for reason in rows[root].get('closure_reasons', []):
            if reason.get('kind') in {'recursive_dependency_cycle', 'closure_depth_limit'}:
                add_block(root, reason['kind'], root,
                          **{k: reason[k] for k in ('depth', 'maximum') if k in reason})

    target_rows = []
    for entry, value in sorted(targets.items(), key=lambda pair: _sort_address(pair[0])):
        target_rows.append({**value, 'roots': sorted(value['roots'], key=_sort_address),
                            'callers': [value['callers'][k] for k in sorted(value['callers'])]})
    blocked_rows = [{**value, 'roots': sorted(value['roots'], key=_sort_address)} for value in blocked.values()]
    blocked_rows.sort(key=lambda value: (_sort_address(value['target']) if value['target'] else -1,
                                         value['kind'], json.dumps(value, sort_keys=True)))
    batches = [{'index': n // max_batch, 'targets': [v['address'] for v in target_rows[n:n + max_batch]]}
               for n in range(0, len(target_rows), max_batch)]
    root_rows = [{'address': root, 'export_targets': [v['address'] for v in target_rows if root in v['roots']],
                  'blocked_count': sum(root in b['roots'] for b in blocked_rows)} for root in roots]
    return {'schema': 1, 'kind': 'raw-lift-dependency-plan',
            'meaning': 'Exact raw export frontier only; no ABI, ownership or completion inference.',
            'max_batch': max_batch, 'roots': root_rows, 'targets': target_rows,
            'batches': batches, 'blocked': blocked_rows,
            'counts': {'roots': len(roots), 'targets': len(target_rows), 'batches': len(batches),
                       'retry_targets': sum(v['retry'] for v in target_rows), 'blocked': len(blocked_rows),
                       'blocked_kinds': dict(sorted(Counter(v['kind'] for v in blocked_rows).items()))},
            'original_status_promotions': 0, 'game_executed': False, 'original_modified': False}


def dependency_plan_markdown(plan):
    """A compact summary; detailed sites stay in the JSON rather than chat."""
    counts = plan['counts']
    lines = [f"Dependency exports: {counts['targets']} targets in {counts['batches']} batches "
             f"for {counts['roots']} roots; {counts['retry_targets']} explicit retries.",
             f"Unresolved blockers: {counts['blocked']}. No acceptance promotions."]
    if counts['blocked_kinds']:
        lines += ['', '| Blocker | Records |', '| --- | ---: |']
        lines += [f'| {kind} | {count} |' for kind, count in sorted(counts['blocked_kinds'].items())]
    return '\n'.join(lines) + '\n'
