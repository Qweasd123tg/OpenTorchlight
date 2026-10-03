#!/usr/bin/env python3
"""Bounded C++17 lowering of ORIGINAL schema-2 raw Ghidra p-code.

No decompiler text/analysis graph is consumed. Scalar mode uses a reviewed ABI
with exact initialized register bytes. Shared-machine mode borrows the caller's
initialized guest bank without inferring an ABI. Both pin ELF/RAM identity and
reject unsupported contracts before publishing any generated header.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import sys
import tempfile


class LiftError(ValueError):
    pass


# Ghidra PcodeOp numeric identifiers are checked as well as mnemonics.
OPCODES = dict(COPY=1, LOAD=2, STORE=3, BRANCH=4, CBRANCH=5, CALL=7, CALLIND=8, RETURN=10,
               INT_EQUAL=11, INT_NOTEQUAL=12, INT_SLESS=13, INT_SLESSEQUAL=14,
               INT_LESS=15, INT_LESSEQUAL=16, INT_ZEXT=17, INT_SEXT=18,
               INT_ADD=19, INT_SUB=20, INT_CARRY=21, INT_SCARRY=22,
               INT_SBORROW=23, INT_2COMP=24, INT_NEGATE=25, INT_XOR=26,
               INT_AND=27, INT_OR=28, INT_LEFT=29, INT_RIGHT=30,
               INT_SRIGHT=31, INT_MULT=32, BOOL_NEGATE=37, BOOL_XOR=38,
               BOOL_AND=39, BOOL_OR=40, FLOAT_EQUAL=41, FLOAT_NOTEQUAL=42,
               FLOAT_LESS=43, FLOAT_LESSEQUAL=44, FLOAT_NAN=46,
               FLOAT_MULT=49,
               PIECE=62, SUBPIECE=63, POPCOUNT=72)
UNARY = {'COPY', 'INT_ZEXT', 'INT_SEXT', 'INT_2COMP', 'INT_NEGATE',
         'BOOL_NEGATE', 'FLOAT_NAN', 'POPCOUNT'}
PREDICATES = {n for n in OPCODES if n.startswith('BOOL_')} | {
    'INT_EQUAL', 'INT_NOTEQUAL', 'INT_SLESS', 'INT_SLESSEQUAL', 'INT_LESS',
    'INT_LESSEQUAL', 'INT_CARRY', 'INT_SCARRY', 'INT_SBORROW',
    'FLOAT_EQUAL', 'FLOAT_NOTEQUAL', 'FLOAT_LESS', 'FLOAT_LESSEQUAL', 'FLOAT_NAN'}
ROOT = Path(__file__).resolve().parents[1]


def integer(value):
    if isinstance(value, bool) or not isinstance(value, (int,str)):
        raise LiftError(f'invalid integer {value!r}')
    try:
        return int(value, 0) if isinstance(value, str) else int(value)
    except (ValueError, TypeError) as exc:
        raise LiftError(f'invalid integer {value!r}') from exc


def address(value):
    value=integer(value)
    if not 0 <= value <= (1<<64)-1:
        raise LiftError(f'invalid x86-64 address {value}')
    return f'0x{value:08x}'


def literal(value):
    return f'UINT64_C(0x{value:x})'


def failure(context, message):
    raise LiftError(f'{context}: {message}')


def validate_node(node, context, ram_id, output=False, abi=False):
    if not isinstance(node, dict):
        failure(context, 'missing varnode')
    size, offset = integer(node.get('size')), integer(node.get('offset'))
    if not 1 <= size <= 8 or not 0 <= offset <= (1 << 64)-1:
        failure(context, f'unsupported varnode width/offset: {size}/{offset}')
    space = node.get('space')
    if space not in {'const', 'register', 'unique', 'ram'}:
        failure(context, f'unsupported varnode space {space!r}')
    # ABI register declarations have no raw space id; exported varnodes do.
    expected_ids={'const':48,'register':548,'unique':291,'ram':ram_id}
    if not abi and 'space_id' not in node:
        failure(context,'raw varnode lacks explicit space id')
    if 'space_id' in node and integer(node['space_id'])!=expected_ids[space]:
        failure(context,'varnode space id differs from pinned x86-64 language')
    if node.get('constant') is not (space == 'const'):
        failure(context, 'varnode constant flag disagrees with space')
    if output and space == 'const':
        failure(context, 'constant output')
    if space == 'register' and offset+size > 8192:
        failure(context, 'register byte range exceeds bounded RegisterFile')
    if space == 'ram' and integer(node.get('space_id')) != ram_id:
        failure(context, 'RAM varnode space id differs from reviewed ABI')


def implementation_paths(abi):
    """Also protect recognizable inputs in a malformed descriptor from CLI writes."""
    result = set()
    imports = abi.get('imports', {}) if isinstance(abi, dict) else {}
    for descriptor in imports.values() if isinstance(imports, dict) else ():
        inputs = descriptor.get('implementation_inputs', {}) if isinstance(descriptor, dict) else {}
        for name in inputs if isinstance(inputs, dict) else ():
            if isinstance(name, str) and name:
                path = Path(name)
                result.add((path if path.is_absolute() else ROOT / path).resolve())
    return result


def validate_imports(abi):
    """No target, callsite, register contract or implementation identity is inferred."""
    descriptors = abi.get('imports', {})
    if not isinstance(descriptors, dict):
        raise LiftError('reviewed imports must be an explicit mapping')
    imports, sites = {}, set()
    for target, descriptor in descriptors.items():
        target = address(target)
        if target in imports or not isinstance(descriptor, dict):
            raise LiftError('duplicate normalized or invalid import target: ' + target)
        expected = {'input_registers', 'output_registers', 'clobber_registers',
                    'callsites', 'implementation_inputs'}
        if set(descriptor) != expected:
            raise LiftError(target + ': import requires exact inputs/outputs/clobbers/callsites/implementation_inputs')
        normalized = {}
        covered = {}
        for role in ('input_registers', 'output_registers', 'clobber_registers'):
            rows = descriptor[role]
            if not isinstance(rows, list):
                raise LiftError(target + ': ' + role + ' must be explicit list')
            normalized[role], covered[role] = [], set()
            for row in rows:
                if not isinstance(row, dict) or set(row) != {'offset', 'size'}:
                    raise LiftError(target + ': imported register range requires exact offset/size')
                node = dict(row, space='register', constant=False)
                validate_node(node, target + ' ' + role, 433, abi=True)
                offset, size = integer(row['offset']), integer(row['size'])
                span = set(range(offset, offset + size))
                if span & covered[role]:
                    raise LiftError(target + ': overlapping ' + role)
                if span & (set(range(0x20, 0x28)) | set(range(0x288, 0x290))):
                    raise LiftError(target + ': import cannot expose or modify RSP/RIP')
                if role != 'input_registers' and span & (
                        set(range(0x18, 0x20)) | set(range(0x28, 0x30)) | set(range(0xa0, 0xc0))):
                    raise LiftError(target + ': import cannot modify System V callee-saved registers')
                covered[role].update(span)
                normalized[role].append(dict(offset=hex(offset), size=size))
        if covered['output_registers'] & covered['clobber_registers']:
            raise LiftError(target + ': output/clobber register ranges overlap')
        callsites = descriptor['callsites']
        if not isinstance(callsites, list) or not callsites:
            raise LiftError(target + ': imported callsites must be a nonempty explicit list')
        normalized['callsites'] = []
        for row in callsites:
            if not isinstance(row, dict) or set(row) != {'caller', 'instruction', 'pcode_index', 'kind'}:
                raise LiftError(target + ': imported callsite requires exact caller/instruction/pcode_index/kind')
            index = integer(row['pcode_index'])
            if index < 0 or row['kind'] != 'direct_call':
                raise LiftError(target + ': only explicit direct_call imports are supported')
            caller, instruction = address(row['caller']), address(row['instruction'])
            site = (caller, instruction, index)
            if site in sites:
                raise LiftError(target + ': duplicate or ambiguous imported callsite')
            sites.add(site)
            normalized['callsites'].append(dict(caller=caller, instruction=instruction,
                                               pcode_index=index, kind='direct_call'))
        inputs = descriptor['implementation_inputs']
        if not isinstance(inputs, dict) or not inputs:
            raise LiftError(target + ': implementation_inputs must pin reviewed implementation files')
        normalized['implementation_inputs'] = {}
        for name, expected_sha in inputs.items():
            if (not isinstance(name, str) or not name or not isinstance(expected_sha, str)
                    or not re.fullmatch('[0-9a-f]{64}', expected_sha)):
                raise LiftError(target + ': invalid implementation input path/SHA-256')
            path = Path(name)
            path = path if path.is_absolute() else ROOT / path
            if not path.is_file() or path.is_symlink() or hashlib.sha256(path.read_bytes()).hexdigest() != expected_sha:
                raise LiftError(target + ': stale or missing implementation input: ' + name)
            normalized['implementation_inputs'][name] = expected_sha
        imports[target] = normalized
    return imports


def compile_function(data, abi, ram_id, input_sha, approved_entries, imports=None, shared_machine=False):
    imports = imports or {}
    entry = address(data['address'])
    if shared_machine:
        ret, return_node, initial_nodes = 'void', None, []
    else:
        ret = abi.get('return')
        if ret not in {'void', 'uint64'}:
            failure(entry, 'ABI return must explicitly be void or uint64')
        return_node=dict(abi.get('return_register',dict(offset='0x0',size=8)),
                         space='register',constant=False)
        validate_node(return_node,entry+' ABI return register',ram_id,abi=True)
        initial = abi.get('input_registers')
        if not isinstance(initial, list):
            failure(entry, 'ABI input_registers must be explicit list')
        initial_nodes=[]
        seen=set()
        for r in initial:
            n=dict(r, space='register', constant=False)
            validate_node(n, entry+' ABI', ram_id,abi=True)
            offset,size=integer(n['offset']),integer(n['size'])
            covered=set(range(offset,offset+size))
            if seen & covered:
                failure(entry, 'overlapping ABI input register declarations')
            seen |= covered
            initial_nodes.append((offset,size))
        if not set(range(0x20,0x28)) <= seen:
            failure(entry, 'ABI must explicitly initialize RSP bytes 0x20..0x27 for real RET')
    instructions=data.get('instructions')
    if not isinstance(instructions,list) or not instructions:
        failure(entry, 'missing original raw instructions')
    addresses=[address(i['address']) for i in instructions]
    if len(set(addresses)) != len(addresses) or entry not in addresses:
        failure(entry, 'duplicate instruction addresses or missing exact entry')
    rows={address(i['address']):i for i in instructions}
    inventory=Counter()
    temps={}
    contexts={}
    successors={}
    dependencies=[]
    external_edges={}
    imported_edges={}
    byte_hash=hashlib.sha256()
    for ins in instructions:
        a=address(ins['address'])
        try:
            instruction_bytes=bytes.fromhex(ins['bytes'])
        except (ValueError,KeyError,TypeError):
            failure(a,'missing/malformed original instruction bytes')
        if not instruction_bytes:
            failure(a,'empty instruction bytes')
        # Preserve the export's literal address spelling in the pinned hash.
        byte_hash.update(ins['address'].encode());byte_hash.update(instruction_bytes)
        pc=ins.get('pcode')
        if not isinstance(pc,list):
            failure(a,'missing original raw pcode (analysis graphs are not accepted)')
        unique_bytes=set()
        for idx,op in enumerate(pc):
            context=f'{a} pcode[{idx}] {op.get("operation")}'
            contexts[(a,idx)]=context
            name=op.get('operation')
            if name not in OPCODES or (name == 'CALLIND' and not shared_machine):
                dependency='; unresolved dependency '+json.dumps(op.get('inputs',[]),sort_keys=True) if name in {'CALL','CALLIND','CALLOTHER','BRANCHIND'} else ''
                failure(context,'unsupported opcode'+dependency)
            if integer(op.get('opcode')) != OPCODES[name] or integer(op.get('index')) != idx:
                failure(context,'opcode/index disagrees with raw operation')
            inventory[name]+=1
            nodes=op.get('inputs')
            if not isinstance(nodes,list):
                failure(context,'inputs must be a list')
            arity=3 if name=='STORE' else 2 if name in {'LOAD','CBRANCH'} else 1 if name in UNARY|{'BRANCH','CALL','CALLIND','RETURN'} else 2
            if len(nodes)!=arity:
                failure(context,f'expected {arity} inputs')
            for n in nodes:
                validate_node(n,context,ram_id)
            out=op.get('output')
            effect=name in {'STORE','BRANCH','CBRANCH','CALL','CALLIND','RETURN'}
            if effect and out is not None:
                failure(context,'effect opcode has output')
            if not effect:
                validate_node(out,context,ram_id,output=True)
            for n in nodes+([out] if out else []):
                if n['space']=='unique':
                    unique_bytes.update(range(integer(n['offset']),integer(n['offset'])+integer(n['size'])))
            sizes=[integer(n['size']) for n in nodes]
            width=integer(out['size']) if out else None
            if name in {'LOAD','STORE'}:
                if nodes[0]['space']!='const' or integer(nodes[0]['offset'])!=ram_id:
                    failure(context,'LOAD/STORE space is not reviewed RAM id')
                if sizes[1]!=8:
                    failure(context,'memory pointer width must be 8 in pinned x86-64 export')
            elif name in {'BRANCH','CBRANCH'}:
                target=nodes[0]
                if target['space']=='ram':
                    if sizes[0]!=8:
                        failure(context,'static RAM branch target width must be 8')
                    ta=address(target['offset'])
                    if ta not in rows:
                        if name!='BRANCH' or ta not in approved_entries:
                            failure(context,f'branch leaves approved function: unresolved dependency {ta}')
                        external_edges[(a,idx)]=ta
                        dependencies.append(dict(kind='tail_jump',instruction=a,pcode_index=idx,target=ta))
                    else:
                        successors[(a,idx)]=(ta,0,True)
                elif target['space']=='const':
                    bits=sizes[0]*8;delta=integer(target['offset']) & ((1<<bits)-1)
                    if delta & (1<<(bits-1)): delta-=1<<bits
                    dest=idx+delta
                    if not 0<=dest<=len(pc):
                        failure(context,f'internal relative branch target {dest} outside instruction p-code')
                    successors[(a,idx)]=(a,dest,False)
                else:
                    failure(context,'non-static branch target: unresolved dependency')
                if name=='CBRANCH' and sizes[1]!=1:
                    failure(context,'CBRANCH condition must be one byte')
            elif name=='CALL':
                if nodes[0]['space']!='ram' or sizes[0]!=8:
                    failure(context,'CALL requires static RAM entry target: unresolved dependency')
                ta=address(nodes[0]['offset'])
                if ta in imports:
                    site = dict(caller=entry, instruction=a, pcode_index=idx, kind='direct_call')
                    if site not in imports[ta]['callsites']:
                        failure(context, 'CALL target/callsite differs from explicit imported boundary')
                    imported_edges[(a,idx)] = ta
                elif ta not in approved_entries:
                    failure(context,f'CALL target outside approved raw/ABI closure: unresolved dependency {ta}')
                fall=ins.get('fallthrough')
                if fall is None or address(fall) not in rows:
                    failure(context,'CALL lacks exact original return fallthrough inside caller')
                if (a,idx) not in imported_edges:
                    external_edges[(a,idx)]=ta
                dependencies.append(dict(kind='imported_direct_call' if (a,idx) in imported_edges else 'direct_call',
                                         instruction=a,pcode_index=idx,target=ta,return_address=address(fall)))
            elif name=='CALLIND':
                if nodes[0]['space'] not in {'register','unique'} or sizes[0]!=8:
                    failure(context,'CALLIND requires register/unique pointer64 target')
                fall=ins.get('fallthrough')
                if fall is None or address(fall) not in rows:
                    failure(context,'CALLIND lacks exact original return fallthrough inside caller')
                dependencies.append(dict(kind='indirect_call',instruction=a,pcode_index=idx,
                                         target=None,return_address=address(fall),target_varnode=dict(nodes[0])))
            elif name=='RETURN':
                if sizes[0]!=8: failure(context,'RETURN target width must be 8')
            elif name in {'INT_ZEXT','INT_SEXT'}:
                if width<sizes[0]: failure(context,'extension narrows')
            elif name=='SUBPIECE':
                if nodes[1]['space']!='const': failure(context,'SUBPIECE byte count must be constant')
                if integer(nodes[1]['offset'])+width>sizes[0]: failure(context,'SUBPIECE extracts outside input')
            elif name=='PIECE':
                if width!=sum(sizes): failure(context,'PIECE output width differs from joined inputs')
            elif name=='POPCOUNT':
                pass
            elif name=='FLOAT_MULT':
                if width not in {4,8} or any(s!=width for s in sizes):
                    failure(context,'float arithmetic requires matching binary32/binary64 input/output widths')
                # Payload ordering is scalar SSE destination-before-source;
                # reject x87/vector/other multiplication rather than silently
                # extending this source-specific rule to all FLOAT_MULT ops.
                prefix=0xf3 if width==4 else 0xf2
                opcode_start=1
                if len(instruction_bytes)>1 and 0x40<=instruction_bytes[1]<=0x4f:
                    opcode_start+=1
                if (instruction_bytes[0]!=prefix or
                        instruction_bytes[opcode_start:opcode_start+2]!=b'\x0f\x59' or
                        len(instruction_bytes)<=opcode_start+2):
                    failure(context,'FLOAT_MULT requires scalar SSE MULSS/MULSD instruction bytes matching operand width')
            elif name in PREDICATES:
                if width!=1: failure(context,'predicate output width must be one byte')
                if name.startswith('BOOL_') and any(s!=1 for s in sizes): failure(context,'boolean input width must be one byte')
                if len(sizes)==2 and sizes[0]!=sizes[1]: failure(context,'predicate input widths differ')
                if name.startswith('FLOAT_') and sizes[0] not in {4,8}: failure(context,'float input must be binary32/binary64')
            elif name in {'INT_LEFT','INT_RIGHT','INT_SRIGHT'}:
                if width!=sizes[0]: failure(context,'shift input/output widths differ')
            elif any(s!=width for s in sizes):
                failure(context,'scalar input/output widths differ')
        if len(unique_bytes)>4096:
            failure(a,'instruction unique bytes exceed bounded temporary storage')
        # A linear instruction has a complete local definition order. Reject
        # provably undefined uniques here. Relative p-code control creates
        # path-dependent definitions, so ByteState checks each executed read.
        relative_control=any(o['operation'] in {'BRANCH','CBRANCH'} and
                             o['inputs'][0]['space']=='const' for o in pc)
        if not relative_control:
            defined=set()
            for idx,o in enumerate(pc):
                for n in o['inputs']:
                    if n['space']=='unique':
                        needed=set(range(integer(n['offset']),integer(n['offset'])+integer(n['size'])))
                        if not needed <= defined:
                            failure(contexts[(a,idx)],f'uninitialized instruction-local unique {n["offset"]} (use before definition)')
                out=o.get('output')
                if out and out['space']=='unique':
                    defined.update(range(integer(out['offset']),integer(out['offset'])+integer(out['size'])))
                if o['operation'] in {'BRANCH','RETURN'}:
                    break
        temps[a]={byte:idx for idx,byte in enumerate(sorted(unique_bytes))}
        fall=ins.get('fallthrough')
        if fall is not None and address(fall) not in rows:
            failure(a,f'fallthrough leaves approved function: {fall}')
        if not pc and fall is None:
            failure(a,'empty p-code without fallthrough')
        if pc and pc[-1]['operation'] not in {'BRANCH','RETURN'} and fall is None:
            failure(a,'execution falls out of function')
    recorded=data.get('address_and_instruction_bytes_sha256')
    if not isinstance(recorded,str) or recorded!=byte_hash.hexdigest():
        failure(entry,'address/instruction byte SHA differs from original raw export')

    def label(a,idx=0,entry=False):
        return ('i_' if entry else 'p_')+a[2:]+('' if entry else f'_{idx}')

    def expr(n,a,context):
        off,size=integer(n['offset']),integer(n['size'])
        if n['space']=='const': return literal(off & ((1<<(size*8))-1))
        if n['space']=='ram': return f'(memory.read({literal(off)}, {size}) & pcode::mask({size}))'
        storage='machine' if n['space']=='register' else 'unique'
        index=off if storage=='machine' else temps[a][off]
        return f'{storage}.read({index}, {size}, {json.dumps(context+": uninitialized "+n["space"]+" "+hex(off))})'

    def write(n,value,a):
        off,size=integer(n['offset']),integer(n['size'])
        if n['space']=='ram': return f'memory.write({literal(off)}, {size}, ({value}) & pcode::mask({size}));'
        storage='machine' if n['space']=='register' else 'unique'
        index=off if storage=='machine' else temps[a][off]
        return f'{storage}.write({index}, {size}, {value});'

    size=max(1,max(map(len,temps.values())))
    name='fn_'+entry[2:]
    lines=[f'// Original ELF {data["original_elf_sha256"]}; raw JSON SHA-256 {input_sha}',
           f'inline {"void" if ret=="void" else "std::uint64_t"} {name}(pcode::Memory& memory, pcode::RegisterFile& registers, std::uint64_t return_sentinel'+(', pcode::CallDepth& call_depth' if shared_machine else '')+') {',
           '    auto& machine = registers;' if shared_machine else '    pcode::RegisterFile machine;',
           f'    pcode::ByteState<{size}> unique;',
           '    [[maybe_unused]] std::uint64_t v0, v1, v2;']
    if shared_machine:
        symbol = json.dumps(str(data.get('symbol', '<not supplied>')), ensure_ascii=True)
        lines.insert(1, '// Source symbol (navigation only): ' + symbol)
        lines.insert(3, '    pcode::CallDepthGuard call_guard(call_depth);')
    for off,width in initial_nodes:
        lines.append(f'    machine.write({off}, {width}, registers.read({off}, {width}, "{entry}: missing reviewed ABI input"));')
    lines.append(f'    goto {label(entry,entry=True)};')
    binary={'INT_ADD':'+','INT_SUB':'-','INT_MULT':'*','INT_AND':'&','INT_OR':'|','INT_XOR':'^',
            'INT_EQUAL':'==','INT_NOTEQUAL':'!=','INT_LESS':'<','INT_LESSEQUAL':'<='}
    helper={'INT_CARRY':'carry','INT_SCARRY':'signed_carry','INT_SBORROW':'signed_borrow',
            'INT_LEFT':'shift_left','INT_RIGHT':'shift_right','INT_SRIGHT':'shift_signed_right'}
    def finish(a):
        if shared_machine:
            return ['    return;']
        ro,rw=integer(return_node['offset']),integer(return_node['size'])
        return ['    registers.merge_initialized(machine);',
                '    return;' if ret=='void' else f'    return machine.read({ro}, {rw}, "{a}: ABI reads uninitialized return register");']
    for ins in instructions:
        a=address(ins['address']);pc=ins['pcode']
        lines += [f'{label(a,entry=True)}:', '    unique.reset();']
        for idx,op in enumerate(pc):
            # Every p-code label is a potential intra-instruction relative target.
            lines.append(f'{label(a,idx)}:;')
            context=contexts[(a,idx)];name_op=op['operation'];nodes=op['inputs'];out=op.get('output')
            # A scalar register self-XOR defines zero independently of its old
            # bytes (e.g. xor EAX,EAX). Fold only this exact varnode identity:
            # RAM reads are effects and unique reads retain definition checks.
            register_self_xor=(name_op=='INT_XOR' and
                all(n['space']=='register' for n in nodes) and
                integer(nodes[0]['offset'])==integer(nodes[1]['offset']) and
                integer(nodes[0]['size'])==integer(nodes[1]['size']))
            args=[] if register_self_xor else [expr(n,a,context) for n in nodes]
            # Evaluate data inputs once, in their raw order, before mutation.
            # RAM control targets and LOAD/STORE space ids are address metadata.
            for ni,arg in enumerate(args):
                if ni==0 and name_op in {'BRANCH','CBRANCH','CALL','LOAD','STORE'}:
                    continue
                lines.append(f'    v{ni} = {arg};')
                args[ni]=f'v{ni}'
            w=integer(nodes[0]['size']); value=None
            if register_self_xor: value='UINT64_C(0)'
            elif name_op=='COPY' or name_op=='INT_ZEXT': value=args[0]
            elif name_op=='INT_SEXT': value=f'pcode::sign_extend({args[0]}, {w})'
            elif name_op in binary: value=f'({args[0]} {binary[name_op]} {args[1]})'
            elif name_op=='INT_NEGATE': value=f'~{args[0]}'
            elif name_op=='INT_2COMP': value=f'(UINT64_C(0) - {args[0]})'
            elif name_op in helper: value=f'pcode::{helper[name_op]}({args[0]}, {args[1]}, {w})'
            elif name_op in {'INT_SLESS','INT_SLESSEQUAL'}:
                v=f'pcode::signed_less({args[0]}, {args[1]}, {w})'
                value=v if name_op=='INT_SLESS' else f'({v} || {args[0]} == {args[1]})'
            elif name_op=='BOOL_NEGATE': value=f'({args[0]} == 0)'
            elif name_op.startswith('BOOL_'):
                operator={'BOOL_AND':'&&','BOOL_OR':'||','BOOL_XOR':'!='}[name_op]
                value=f'(({args[0]} != 0) {operator} ({args[1]} != 0))'
            elif name_op=='SUBPIECE': value=f'pcode::subpiece({args[0]}, {args[1]})'
            elif name_op=='PIECE': value=f'(({args[0]} << {integer(nodes[1]["size"])*8}) | {args[1]})'
            elif name_op=='POPCOUNT': value=f'pcode::popcount({args[0]})'
            elif name_op=='FLOAT_MULT': value=f'pcode::float_multiply({args[0]}, {args[1]}, {w})'
            elif name_op.startswith('FLOAT_'):
                fargs=[f'pcode::floating({arg}, {integer(n["size"])})' for arg,n in zip(args,nodes)]
                if name_op=='FLOAT_NAN': value=f'std::isnan({fargs[0]})'
                else:
                    operator={'FLOAT_EQUAL':'==','FLOAT_NOTEQUAL':'!=','FLOAT_LESS':'<','FLOAT_LESSEQUAL':'<='}[name_op]
                    value=f'({fargs[0]} {operator} {fargs[1]})'
            elif name_op=='LOAD': value=f'memory.read({args[1]}, {integer(out["size"])})'
            elif name_op=='STORE': lines.append(f'    memory.write({args[1]}, {integer(nodes[2]["size"])}, {args[2]});')
            elif name_op in {'BRANCH','CBRANCH'}:
                if (a,idx) in external_edges:
                    ta=external_edges[(a,idx)]
                    lines.append(f'    (void)fn_{ta[2:]}(memory, machine, return_sentinel'+(', call_depth' if shared_machine else '')+');')
                    lines.extend(finish(a))
                else:
                    dest,di,is_entry=successors[(a,idx)];target=label(dest,di,is_entry)
                    lines.append(f'    {"if ("+args[1]+" != 0) " if name_op=="CBRANCH" else ""}goto {target};')
            elif name_op=='CALL':
                if (a,idx) in imported_edges:
                    ta=imported_edges[(a,idx)]
                    def ranges(role):
                        rows=imports[ta][role]
                        values=', '.join('{'+str(integer(row['offset']))+', '+str(integer(row['size']))+'}' for row in rows)
                        return f'std::array<pcode::RegisterRange, {len(rows)}>'+'{{'+values+'}}'
                    call=f'pcode::ImportCall{{{literal(integer(entry))}, {literal(integer(a))}, {idx}, {literal(integer(ta))}}}'
                    lines.append(f'    pcode::invoke_import(memory, machine, {call}, {literal(integer(ins["fallthrough"]))}, '
                                 +', '.join(ranges(role) for role in ('input_registers','output_registers','clobber_registers'))+');')
                else:
                    ta=external_edges[(a,idx)]
                    lines.append(f'    (void)fn_{ta[2:]}(memory, machine, {literal(integer(ins["fallthrough"]))}'+(', call_depth' if shared_machine else '')+');')
            elif name_op=='CALLIND':
                lines.append(f'    dispatch_call({args[0]}, memory, machine, {literal(integer(ins["fallthrough"]))}, call_depth);')
            elif name_op=='RETURN':
                lines.append(f'    pcode::check_return({args[0]}, return_sentinel);')
                lines.extend(finish(a))
            if value is not None: lines.append('    '+write(out,value,a))
            # Explicit successors avoid accidental fallthrough after arbitrary
            # target layouts, including p-code following conditional transfers.
            if name_op not in {'BRANCH','RETURN'}: lines.append(f'    goto {label(a,idx+1)};')
        lines.append(f'{label(a,len(pc))}:;')
        fall=ins.get('fallthrough')
        lines.append('    goto '+label(address(fall),entry=True)+';' if fall else '    throw std::runtime_error("p-code reached instruction with no fallthrough");')
    lines.append('}')
    # Mark unused labels explicitly for strict -Wall/-Werror compilers; labels
    # are otherwise useful when a future export gains an internal relative edge.
    referenced={m.group(1) for line in lines for m in re.finditer(r'goto (\w+);',line)}
    lines=[line for line in lines if not re.match(r'^(?:i_|p_)\w+:;?$',line) or line.split(':')[0] in referenced]
    namespace = 'pcode_machine' if shared_machine else 'pcode_generated'
    report = dict(address=entry,generated_symbol='torchlight::'+namespace+'::'+name,
        input_sha256=input_sha,address_and_instruction_bytes_sha256=recorded,
        original_elf_sha256=data['original_elf_sha256'],abi=None if shared_machine else abi,
        effective_return_register=None if ret=='void' else dict(offset=hex(integer(return_node['offset'])),size=integer(return_node['size'])),
        instructions=len(instructions),pcode_operations=sum(inventory.values()),
        opcode_inventory=dict(sorted(inventory.items())),approved_dependencies=dependencies,unresolved_dependencies=[])
    if shared_machine:
        report['execution_mode'] = 'shared_machine'
        report['register_input_policy'] = 'caller-initialized shared guest bank; undefined byte reads trap'
    return '\n'.join(lines), report


def generate(paths, abi):
    if abi.get('schema')!=1:
        raise LiftError('reviewed ABI schema must be 1')
    sha=abi.get('original_elf_sha256')
    if not isinstance(sha,str) or not re.fullmatch('[0-9a-f]{64}',sha):
        raise LiftError('reviewed ABI must pin original_elf_sha256')
    ram_id=integer(abi.get('memory_space_id'))
    if ram_id!=433:
        raise LiftError('bounded emitter requires pinned x86-64 RAM space id 433 (0x1b1)')
    mode = abi.get('execution_mode', 'scalar')
    if mode not in ('scalar', 'shared_machine'):
        raise LiftError('unsupported execution_mode; choose scalar or shared_machine')
    shared_machine = mode == 'shared_machine'
    if shared_machine:
        if 'functions' in abi:
            raise LiftError('shared_machine forbids individual ABI functions descriptors')
        max_call_depth = abi.get('max_call_depth', 64)
        if type(max_call_depth) is not int or not 1 <= max_call_depth <= 64:
            raise LiftError('shared_machine max_call_depth must be an integer in 1..64')
        normalized = {}
    else:
        if 'max_call_depth' in abi:
            raise LiftError('max_call_depth is supported only in shared_machine mode')
        descriptors=abi.get('functions')
        if not isinstance(descriptors,dict): raise LiftError('missing explicit ABI functions')
        normalized={address(k):v for k,v in descriptors.items()}
        if len(normalized)!=len(descriptors): raise LiftError('duplicate normalized ABI address')
    imports=validate_imports(abi)
    files=[]
    for path in paths:
        path=Path(path)
        files.extend(sorted(p for p in path.glob('*.json') if p.name!='manifest.json') if path.is_dir() else [path])
    sources={}
    for path in files:
        raw=path.read_bytes();data=json.loads(raw)
        if data.get('schema')!=2 or data.get('original_elf_sha256')!=sha:
            raise LiftError(f'{path}: original schema-2 ELF metadata differs from pinned ABI')
        entry=address(data['address'])
        if shared_machine and integer(entry)==0:
            raise LiftError(f'{path}: zero cannot be a shared-machine callable entry')
        if entry in sources: raise LiftError(f'{path}: duplicate input function {entry}')
        if not shared_machine and entry not in normalized: raise LiftError(f'{entry}: no explicit reviewed ABI')
        sources[entry]=(data,hashlib.sha256(raw).hexdigest())
    if not sources: raise LiftError('no original raw functions selected')
    if shared_machine:
        normalized = {entry: {'return': 'void', 'input_registers': []} for entry in sources}
    elif set(sources)!=set(normalized): raise LiftError('ABI function set differs from exact selected raw function set')
    if set(sources) & set(imports): raise LiftError('import target conflicts with an original raw body')
    namespace = 'pcode_machine' if shared_machine else 'pcode_generated'
    code=['#pragma once','#include "torchlight/pcode_runtime.hpp"','namespace torchlight::'+namespace+' {']
    reports=[]
    declarations=[]
    for entry,(data,input_sha) in sorted(sources.items()):
        body,report=compile_function(data,normalized[entry],ram_id,input_sha,set(sources),imports,shared_machine)
        declarations.append(f'inline {"void" if normalized[entry]["return"]=="void" else "std::uint64_t"} fn_{entry[2:]}(pcode::Memory&, pcode::RegisterFile&, std::uint64_t'+(', pcode::CallDepth&' if shared_machine else '')+');')
        code.append(body);reports.append(report)
    used_sites={(r['address'], d['instruction'], d['pcode_index'], d['target'])
                for r in reports for d in r['approved_dependencies'] if d['kind']=='imported_direct_call'}
    declared_sites={(site['caller'],site['instruction'],site['pcode_index'],target)
                    for target,descriptor in imports.items() for site in descriptor['callsites']}
    if used_sites!=declared_sites:
        raise LiftError('unused or mismatched imported callsite descriptors')
    graph={r['address']:{d['target'] for d in r['approved_dependencies'] if d['kind'] in {'direct_call','tail_jump'}} for r in reports}
    visited=set();active=[];depths={}
    def depth(entry):
        if entry in active:
            cycle=active[active.index(entry):]+[entry]
            raise LiftError('recursive direct-call/tail-jump closure is unsupported: '+' -> '.join(cycle))
        if entry in visited:return depths[entry]
        if len(active)>=64:
            raise LiftError(f'{entry}: approved closure nesting exceeds bounded maximum 64')
        active.append(entry)
        value=1+max((depth(target) for target in sorted(graph[entry])),default=0)
        active.pop();visited.add(entry);depths[entry]=value
        if value>64:raise LiftError(f'{entry}: approved closure depth {value} exceeds bounded maximum 64')
        return value
    for entry in sorted(graph):depth(entry)
    if shared_machine:
        declarations.append('inline void dispatch_call(std::uint64_t, pcode::Memory&, pcode::RegisterFile&, std::uint64_t, pcode::CallDepth&);')
        dispatcher=['inline void dispatch_call(std::uint64_t target, pcode::Memory& memory, pcode::RegisterFile& registers, std::uint64_t return_sentinel, pcode::CallDepth& call_depth) {',
                    '    switch (target) {']
        for entry in sorted(sources):
            dispatcher.append(f'    case {literal(integer(entry))}: fn_{entry[2:]}(memory, registers, return_sentinel, call_depth); return;')
        dispatcher += ['    default: throw pcode::UntranslatedCallTarget(target);', '    }', '}']
        code.append('\n'.join(dispatcher))
        for entry in sorted(sources):
            code.append(f'inline void fn_{entry[2:]}(pcode::Memory& memory, pcode::RegisterFile& registers, std::uint64_t return_sentinel) {{\n'
                        f'    pcode::CallDepth call_depth({max_call_depth});\n'
                        f'    fn_{entry[2:]}(memory, registers, return_sentinel, call_depth);\n'+'}')
    code[3:3]=declarations
    code.append('} // namespace torchlight::'+namespace+'\n')
    header='\n\n'.join(code)
    report=dict(schema=1,status='generated',original_elf_sha256=sha,
        emitter='raw-schema2-shared-machine-cpp17-v2' if shared_machine else 'raw-schema2-scalar-cpp17-v3',
        abi_sha256=hashlib.sha256(json.dumps(abi,sort_keys=True,separators=(',',':')).encode()).hexdigest(),
        generated_header_sha256=hashlib.sha256(header.encode()).hexdigest(),functions=reports,
        closure=dict(recursion='rejected',maximum_allowed_depth=64,maximum_selected_depth=max(depths.values()),
                     dependencies={entry:sorted(targets) for entry,targets in sorted(graph.items())}),
        warning='Generated code is a bounded raw p-code translation; this report does not promote transfer/completion status.')
    if imports:
        if validate_imports(abi)!=imports:
            raise LiftError('import implementation inputs changed during generation')
        report['imported_boundaries']=imports
    if shared_machine:
        report['execution_mode'] = 'shared_machine'
        report['closure']['recursion'] = 'direct-call/tail-jump rejected; indirect calls use explicit host depth budget'
        report['guest_register_initialization'] = 'external caller only; no ABI inference or zero-fill'
        report['guest_memory_owner'] = 'external caller-supplied Memory; no field bindings inferred'
        report['indirect_dispatch'] = dict(operation='CALLIND', target_space=['register','unique'],
                                          target_width=8, compiled_entries=sorted(sources),
                                          unknown_target='trap before callee execution; prior guest effects retained',
                                          imported_targets='excluded')
        report['host_call_depth_budget'] = dict(default_limit=max_call_depth, maximum_allowed_limit=64,
                                               owner='caller-owned CallDepth; three-argument entries create a fresh owner',
                                               failure='explicit adapter budget error; not original guest semantics',
                                               counts='every shared entry including direct calls and tail jumps')
        report['original_status_promotions'] = 0
    return header,report


def atomic_write(path,content):
    path=Path(path);path.parent.mkdir(parents=True,exist_ok=True)
    with tempfile.NamedTemporaryFile('w',encoding='utf-8',dir=path.parent,delete=False) as f:
        f.write(content);stage=Path(f.name)
    stage.replace(path)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('inputs',nargs='+',help='original schema-2 raw JSON files/directories')
    parser.add_argument('--abi',required=True,help='reviewed, pinned ABI JSON')
    parser.add_argument('--out',required=True,help='generated C++ header (ignored build or /tmp)')
    parser.add_argument('--report',required=True,help='generation report JSON')
    args=parser.parse_args()
    try:
        reviewed_abi=json.loads(Path(args.abi).read_text())
    except (ValueError,OSError) as exc:
        print('p-code lowering rejected: '+str(exc),file=sys.stderr)
        return 2
    protected={Path(args.abi).resolve()}
    protected.update(implementation_paths(reviewed_abi))
    for p in map(Path,args.inputs):
        if p.is_dir(): protected.update(q.resolve() for q in p.glob('*.json'))
        else: protected.add(p.resolve())
    out,report_path=Path(args.out).resolve(),Path(args.report).resolve()
    if out==report_path or out in protected or report_path in protected:
        print('p-code lowering rejected: output/report must be distinct and cannot overwrite source inputs or ABI',file=sys.stderr)
        return 2
    try:
        header,report=generate(args.inputs,reviewed_abi)
    except (LiftError,ValueError,KeyError,TypeError,OSError) as exc:
        atomic_write(args.report,json.dumps(dict(schema=1,status='rejected',error=str(exc)),indent=2)+'\n')
        print(f'p-code lowering rejected: {exc}',file=sys.stderr)
        return 2
    atomic_write(args.out,header)
    atomic_write(args.report,json.dumps(report,indent=2,sort_keys=True)+'\n')
    print(f'Generated {len(report["functions"])} functions: {args.out}')
    return 0


if __name__=='__main__':
    sys.exit(main())
