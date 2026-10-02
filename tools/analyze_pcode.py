#!/usr/bin/env python3
"""Summarize raw Ghidra operations, widths and local data flow without naming fields.

This is bounded evidence collection, not a C++ lifter or semantic proof. Values
at block entry are symbolic register inputs. Joins/calls/internal p-code control
flow stay explicit; no inferred object owner or initializer is manufactured.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
from automation_state import validate_output, write_json
from original import SUPPORTED_SHA256

ROOT = Path(__file__).resolve().parents[1]


def key(node): return (node['space'], int(node['offset'], 16), node['size'])


def location(expression):
    """Describe addressing, never assign an object/field type or name."""
    if expression['operation'] == 'constant':
        return {'base':'absolute','offset':expression['value']}
    if expression['operation'] == 'block_input':
        return {'base':'block-register-input','register':expression['register'],
                'block':expression['block'],'offset':'0x0'}
    if expression['operation'] in ('INT_ADD','INT_SUB'):
        left,right=expression['inputs']
        if right['operation']=='constant':
            base=location(left)
            if base is not None:
                amount=int(right['value'],16)
                if expression['operation']=='INT_SUB':amount=-amount
                base['offset']=hex((int(base['offset'],16)+amount)&((1<<(8*expression['size']))-1))
                return base
    if expression['operation']=='LOAD':
        return {'base':'loaded-value-used-as-address','load_site':expression['site'],
                'load_bytes':expression['size'],'offset':'0x0'}
    return None


def analyze(function: dict) -> dict:
    if function.get('schema') != 2 or function.get('original_elf_sha256') != SUPPORTED_SHA256:
        raise ValueError('Need schema-2 structured raw p-code from the pinned original')
    instructions = function.get('instructions', [])
    if not isinstance(instructions, list) or len(instructions) > 100000:
        raise ValueError('Invalid/unbounded instruction collection')
    block_entries = {row['entry'] for row in function.get('basic_blocks', [])}
    block_entries.add(function['address'])
    values, written, events, branches, unknown = {}, [], [], [], []
    block = function['address']
    registers = {(n['space'],int(n['offset'],16),int(n['offset'],16)+n['size'])
                 for row in instructions for op in row['pcode'] for n in op['inputs']
                 if n['space'] == 'register'}

    def remember(space, start, end):
        nonlocal written
        untouched = []
        for old_space, old_start, old_end in written:
            if old_space == space and start <= old_end and old_start <= end:
                start, end = min(start,old_start), max(end,old_end)
            else: untouched.append((old_space,old_start,old_end))
        written = untouched + [(space,start,end)]

    def value(node):
        if not isinstance(node, dict) or not isinstance(node.get('size'), int) or not 1 <= node['size'] <= 64:
            raise ValueError('Invalid raw varnode width')
        if node['constant']:
            return {'operation': 'constant', 'size': node['size'], 'value': node['offset']}
        slot = key(node)
        if slot in values: return values[slot]
        overlap = any(node['space'] == space and slot[1] < end and start < slot[1] + node['size']
                      for space, start, end in written)
        return {'operation': 'unknown' if overlap or node['space'] == 'unique' else 'block_input',
                'size': node['size'], 'space': node['space'], 'offset': node['offset'],
                'register': node['register'], 'block': block}

    def assign(node, expression):
        if node is None: return
        slot = key(node)
        for old in list(values):
            if old[0] == slot[0] and old[1] < slot[1] + slot[2] and slot[1] < old[1] + old[2]:
                values.pop(old)
        remember(slot[0], slot[1], slot[1] + slot[2])
        if len(json.dumps(expression)) > 8192:
            expression = {'operation': 'unknown', 'size': node['size'], 'reason': 'expression_limit'}
            unknown.append({'code': 'expression_limit', 'block': block})
        values[slot] = expression

    for instruction in instructions:
        address = instruction['address']
        if address in block_entries:
            block = address
            values, written = {}, []
        # Ghidra unique temporaries are instruction-local; never invent a value
        # from the same numeric unique address used by a previous instruction.
        values = {slot: expr for slot, expr in values.items() if slot[0] != 'unique'}
        written = [item for item in written if item[0] != 'unique']
        for op in instruction['pcode']:
            name, output = op['operation'], op['output']
            inputs = [value(node) for node in op['inputs']]
            if name in ('BRANCH','CBRANCH','CALL') and op['inputs'][0]['space'] != 'const':
                target = op['inputs'][0]
                inputs[0] = {'operation':'address','space':target['space'],'size':target['size'],'value':target['offset']}
            expression = {'operation': name, 'size': output['size'] if output else None,
                          'inputs': inputs, 'site': address, 'index': op['index']}
            if name == 'COPY' and inputs: expression = inputs[0]
            if name in ('INT_ADD', 'INT_SUB') and all(i['operation'] == 'constant' for i in inputs):
                lhs, rhs = [int(i['value'], 16) for i in inputs]
                result = lhs + rhs if name == 'INT_ADD' else lhs - rhs
                expression = {'operation': 'constant', 'size': output['size'],
                              'value': hex(result & ((1 << (8 * output['size'])) - 1))}
            if name in ('LOAD', 'STORE'):
                if len(inputs) < 2: raise ValueError('Invalid memory p-code')
                width = output['size'] if name == 'LOAD' else op['inputs'][2]['size']
                event = {'site': address, 'index': op['index'], 'block': block,
                         'kind': 'read' if name == 'LOAD' else 'write', 'bytes': width,
                         'memory_space_id': op['inputs'][0]['offset'], 'address_expression': inputs[1]}
                if name == 'STORE': event['value_expression'] = inputs[2]
                events.append(event)
            if name in ('BRANCH', 'CBRANCH', 'BRANCHIND', 'CALL', 'CALLIND', 'RETURN'):
                branches.append({'site': address, 'index': op['index'], 'operation': name,
                                 'inputs': inputs, 'flows': instruction['flows'],
                                 'fallthrough': instruction['fallthrough']})
            if name in ('CALL', 'CALLIND', 'CALLOTHER'):
                unknown.append({'site': address, 'code': 'external_effects_not_modeled', 'operation': name})
                # Preserve graph evidence, discard register value conclusions.
                values = {}
                for space,start,end in registers: remember(space,start,end)
            if name in ('BRANCH', 'CBRANCH') and op['inputs'][0]['constant']:
                unknown.append({'site': address, 'code': 'internal_pcode_flow_not_solved'})
                values = {}
                # Subsequent operations are only raw evidence: don't pretend
                # mutually exclusive micro-paths were executed sequentially.
                for remaining in instruction['pcode'][op['index'] + 1:]:
                    if remaining['output']:
                        n = remaining['output'];remember(n['space'],int(n['offset'],16),int(n['offset'],16)+n['size'])
                    if remaining['operation'] in ('LOAD','STORE'):
                        nodes = remaining['inputs'];out = remaining['output']
                        events.append({'site':address,'index':remaining['index'],'block':block,
                            'kind':'read' if remaining['operation']=='LOAD' else 'write',
                            'bytes':out['size'] if out else nodes[2]['size'],
                            'memory_space_id':nodes[0]['offset'],
                            'address_expression':{'operation':'unknown','reason':'internal_pcode_flow_not_solved'},
                            'raw_inputs':nodes})
                break
            assign(output, expression)
        if instruction['is_computed'] and not instruction['is_terminal']:
            unknown.append({'site': address, 'code': 'computed_target_unresolved'})
    locations=[]
    for event in events:
        address=location(event['address_expression'])
        locations.append({'site':event['site'],'kind':event['kind'],'bytes':event['bytes'],
                          'location':address,'status':'local-address-expression' if address else 'unresolved-address'})
    return {'schema': 1, 'kind': 'raw-pcode-evidence', 'address': function['address'],
            'symbol': function['symbol'], 'original_elf_sha256': SUPPORTED_SHA256,
            'memory_accesses': events, 'locations':locations,'control_flow': branches, 'unresolved': unknown,
            'basic_blocks': function.get('basic_blocks', []),
            'scope': 'Instruction widths and basic-block-local expression graphs. No global SSA, object ownership, ABI inference, valid-state proof or automatic completion.',
            'original_status_promotions': 0}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('packet', type=Path)
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    try:
        validate_output(ROOT, args.out, [args.packet])
        report = analyze(json.loads(args.packet.read_text()))
        report['input_sha256'] = hashlib.sha256(args.packet.read_bytes()).hexdigest()
        write_json(args.out, report)
        print(f"p-code: {len(report['memory_accesses'])} accesses, {len(report['control_flow'])} flows, {len(report['unresolved'])} open effects")
        return 0
    except (OSError, ValueError, KeyError, TypeError) as exc: parser.exit(2, f'p-code analysis: {exc}\n')


if __name__ == '__main__': raise SystemExit(main())
