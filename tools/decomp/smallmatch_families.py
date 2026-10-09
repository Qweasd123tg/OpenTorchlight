"""Additional source hypotheses, always subject to pinned object comparison.

Uses existing declarations/layouts only. Constructors and destructors are
ordinary C++ definitions; all ABI variants/thunks must match as a closure.
No instruction emulation, game execution or acceptance by similarity.
"""
import re

import llm_definitions
import mutate
import objdiff
from smallmatch import Unsupported, primitive, type_key


def instructions(g, f):
    return [(a, m, p.split('#', 1)[0].strip())
            for a, m, p in objdiff.parse_insns((g.kit / f['assembly']).read_text())
            if not objdiff.Normalizer.padding(m, p)]


def direct_calls(g, insns):
    result = []
    for _, op, operand in insns:
        match = re.fullmatch(r'([0-9a-f]+)\s+<(.+)>', operand)
        if op in ('call', 'jmp') and match and '+0x' not in match[2]:
            result.append((g.by_address.get(hex(int(match[1], 16))), match[2]))
    return result


def field_at(g, scope, offset, width=None):
    fields = [field for at, field in g.fields(scope)
              if at == offset and (width is None or field['size'] == width)
              and '[' not in field['type']]
    if len(fields) != 1:
        raise Unsupported('additional family: no unique named header field')
    return fields[0]


def derived_from(g, scope, base):
    if scope == base:
        return True
    return any(b.get('offset') == 0 and derived_from(g, b['name'], base)
               for b in g.types['classes'].get(scope, {}).get('bases', []))


def special_member(g, f, insns):
    declarations = g.declarations.get(f['qualified'], [])
    declarations = [(h, d) for h, d in declarations
                    if re.search(re.escape(f['method']) + r'\s*\(\s*\)', d)]
    if len(declarations) != 1 or f.get('params'):
        raise Unsupported('special member needs one existing no-argument declaration')
    closure = llm_definitions.closure(f, g.db)
    if any(g.by_address[a]['size'] >= 1000 for a in closure):
        raise Unsupported('special-member closure includes an excluded large function')
    body = []
    family = 'implicit_member_destruction'
    calls = direct_calls(g, insns)
    if f['kind'] == 'ctor':
        ops = [(m, p) for _, m, p in insns]
        if len(ops) != 2 or ops[-1] != ('ret', '') or ops[0][0] != 'movq' or not re.fullmatch(r'\$0x[0-9a-f]+,\(%rdi\)', ops[0][1]):
            raise Unsupported('constructor is not the vtable-only idiom')
        family = 'implicit_vtable_constructor'
    else:
        # An optional explicit, no-argument cleanup on this precedes automatic
        # destruction. Other ordinary game calls make this family unsupported.
        ordinary = []
        for callee, name in calls:
            if callee and callee['kind'] == 'function' and not name.startswith(('std::', 'TArrayList<', 'TSafePointer<')):
                if callee['qualified'] == 'CRunicCore::removeSafePointer':
                    continue  # may be inlined TSafePointer member destruction
                ordinary.append(callee)
            elif not callee and not any(s in name for s in ('::~', '::_M_', 'operator delete', 'deallocBytes', '_Unwind_Resume')):
                raise Unsupported('destructor contains an unmodelled external call')
        if ordinary:
            first = ordinary[0]
            if any(c['address'] != first['address'] for c in ordinary) or first['scope'] != f['scope'] or first.get('params'):
                raise Unsupported('destructor has nontrivial explicit cleanup')
            decl = g.declaration(first)
            if decl['static'] or decl['ret'] != 'void':
                raise Unsupported('destructor cleanup declaration is not void this-method')
            body = [first['method'] + '();']
            family = 'cleanup_then_member_destruction'
    code = f['qualified'] + '()\n{\n' + ''.join('    ' + s + '\n' for s in body) + '}\n'
    reason = llm_definitions.single_definition(f, code)
    if reason:
        raise Unsupported(reason)
    dependencies = set()
    for _, field in g.fields(f['scope']):
        # These member destructors require complete pointee/value types. Other
        # pointer members deliberately do not force unrelated definitions in.
        match = re.fullmatch(r'(?:TSafePointer|TArrayList)<([A-Za-z_]\w*)>', field['type'])
        if match:
            name = match[1]
            if primitive(name):
                continue
            headers = {h for q, items in g.declarations.items() if q.startswith(name + '::') for h, _ in items}
            if len(headers) == 1:
                dependencies.update(headers)
            elif not headers:
                complete = [h.name for h in (g.root / 'decomp/include').glob('*.h')
                            if re.search(r'\b(?:class|struct)\s+' + re.escape(name) + r'\s*(?:\{|:)', h.read_text())]
                if len(complete) == 1:
                    dependencies.add(complete[0])
                else:
                    raise Unsupported('member destruction needs a complete existing type: ' + name)
    return {'address': f['address'], 'name': f['demangled'], 'tu': f['tu_name'],
            'family': family, 'header': declarations[0][0], 'source': code,
            'original_size': f['size'], 'status': 'UNVERIFIED', 'closure': sorted(closure),
            'extra_headers': sorted(dependencies)}


def generate(g, f):
    if f['source_status'] != 'MISSING' or f.get('clone') or 'thunk to ' in f['demangled']:
        raise Unsupported('additional families apply to missing C++ definitions only')
    if g.types['classes'].get(f['scope'], {}).get('source') != 'header':
        raise Unsupported('additional family requires a header-derived class')
    prior = g.root / 'decomp/src' / f['tu_name']
    if prior.exists() and mutate.definition(prior.read_text(), mutate.mask(prior.read_text()), f):
        raise Unsupported('prior definition is preserved')
    insns = instructions(g, f)
    if f['kind'] in ('ctor', 'dtor'):
        return special_member(g, f, insns)
    if f['kind'] != 'function':
        raise Unsupported('unsupported definition kind')
    decl = g.declaration(f)
    emit = lambda family, body: g.source(f, decl, family, body)
    ops = [(m, p) for _, m, p in insns]
    calls = direct_calls(g, insns)

    # Address of a real member object, including aggregate members.
    if len(ops) == 2 and ops[-1] == ('ret', '') and not decl['static'] and not decl['params']:
        match = re.fullmatch(r'0x([0-9a-f]+)\(%rdi\),%rax', ops[0][1])
        if ops[0][0] == 'lea' and match:
            field = field_at(g, f['scope'], int(match[1], 16))
            if type_key(decl['ret']) == type_key(field['type'] + '*'):
                return emit('member_address', ['return &' + field['name'] + ';'])

    # Null-guarded scalar/pointer member of a typed pointer member.
    if len(ops) == 6 and not decl['static'] and not decl['params']:
        first = re.fullmatch(r'(0x[0-9a-f]+)?\(%rdi\),(%r[a-z0-9]+)', ops[0][1])
        second = re.fullmatch(r'(0x[0-9a-f]+)?\((%r[a-z0-9]+)\),(%rax|%eax)', ops[4][1])
        if (first and second and first[2] == second[2] and ops[0][0] == 'mov'
                and ops[1] == ('xor', '%eax,%eax') and ops[2] == ('test', first[2] + ',' + first[2])
                and ops[3][0] == 'je' and ops[4][0] == 'mov' and ops[-1] in (('ret', ''), ('repz ret', ''))
                and int(ops[3][1].split()[0], 16) == insns[-1][0]):
            parent = field_at(g, f['scope'], int(first[1] or '0', 16), 8)
            if parent['type'].endswith('*'):
                scope = parent['type'][:-1].strip()
                child = field_at(g, scope, int(second[1] or '0', 16), 8 if second[3] == '%rax' else 4)
                if type_key(decl['ret']) == type_key(child['type']):
                    row = emit('nullable_member', ['return ' + parent['name'] + ' ? ' + parent['name'] + '->' + child['name'] + ' : 0;'])
                    headers = [h for h, _ in g.declarations.get(scope + '::~' + scope, [])]
                    row['extra_headers'] = sorted(set(headers))
                    return row

    # Two-register tail forwarding: the sole argument is the receiver.
    if (len(ops) == 2 and ops[0] == ('mov', '%rsi,%rdi') and ops[1][0] == 'jmp'
            and len(calls) == 1 and not decl['static'] and decl['ret'] == 'void'
            and len(decl['params']) == 1):
        callee = calls[0][0]
        if callee and callee['kind'] == 'function' and not callee.get('params'):
            other = g.declaration(callee)
            base = decl['params'][0][0].rstrip('*').strip()
            if not other['static'] and other['ret'] == 'void' and derived_from(g, callee['scope'], base):
                row = emit('argument_receiver_wrapper', ['static_cast<' + callee['scope'] + '*>(' + decl['params'][0][1] + ')->' + callee['method'] + '();'])
                row['callee_header'] = other['header']
                return row

    # Descriptor object lists use TArrayList's original capacity fallback.
    if derived_from(g, f['scope'], 'CDescriptor') and decl['ret'] == 'void' and not decl['static']:
        members = [field for off, field in g.fields(f['scope'])
                   if off == 0xe0 and type_key(field['type']) == 'TArrayList<CEditorBaseObject*>']
        if len(members) == 1 and f['size'] in (95, 103):
            name = members[0]['name']
            if len(calls) == 1 and calls[0][0] and not any(p.startswith('*') for _, m, p in insns if m == 'call'):
                callee = calls[0][0]
                other = g.declaration(callee)
                if (not other['static'] and other['ret'] == 'void'
                        and derived_from(g, callee['scope'], 'CEditorBaseObject')
                        and [type_key(t) for t, n in other['params']] in ([], [type_key(t) for t, n in decl['params']])):
                    args = ', '.join(n for t, n in decl['params']) if other['params'] else ''
                    row = emit('descriptor_object_loop', ['for (unsigned int i = 0; i < ' + name + '.size(); ++i)',
                        '    static_cast<' + callee['scope'] + '*>(' + name + '[i])->' + callee['method'] + '(' + args + ');'])
                    row['callee_header'] = other['header']
                    operation = 'static_cast<' + callee['scope'] + '*>(' + name + '[i])->' + callee['method'] + '(' + args + ');'
                    # A small, semantics-preserving source search; exact object
                    # comparison alone decides whether any spelling is usable.
                    variants = [
                        ['for (unsigned int i = 0; i < ' + name + '.size();)',
                         '    ' + operation.replace('[i]', '[i++]')],
                        ['if (' + name + '.size() != 0)', '{', '    unsigned int i = 0;', '    do', '    {',
                         '        ' + operation, '        ++i;', '    } while (i < ' + name + '.size());', '}'],
                        ['for (unsigned int i = 0; i < ' + name + '.size(); ++i)', '{',
                         '    ' + callee['scope'] + '* object = static_cast<' + callee['scope'] + '*>(' + name + '[i]);',
                         '    object->' + callee['method'] + '(' + args + ');', '}']]
                    row['alternatives'] = [emit('descriptor_object_loop', body)['source'] for body in variants]
                    return row
            if f['method'] == 'deleteNotification' and not decl['params'] and not calls and ('call', '*%rax') in ops and ('mov', '0x60(%rax),%rax') in ops:
                return emit('descriptor_delete_notification', ['for (unsigned int i = 0; i < ' + name + '.size(); ++i)', '    DescriptorObjectBeingDeleted(' + name + '[i]);'])
    raise Unsupported('no additional supported source hypothesis')
