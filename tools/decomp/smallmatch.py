#!/usr/bin/env python3
"""Deterministic small-function candidates from an immutable MATCH kit.

Only existing, trusted declarations and header-derived fields are used.
The output is a full isolated TU with all previous definitions preserved.
Generation is not acceptance; use the pinned objdiff afterwards. No game,
model, publication, credentials or network operations are implemented.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import re
import sys

import ghidra_cpp
import layout
import llm_context
import llm_definitions
import mutate
import objdiff


class Unsupported(ValueError):
    pass


def spelling(text):
    return ghidra_cpp.cxx_type(text).replace(
        "std::basic_string<char, std::char_traits<char>, std::allocator<char> >", "std::string")


def type_key(text):
    return mutate.canonical_parameter(spelling(text))


def primitive(text):
    return type_key(text) in {
        "bool", "char", "signedchar", "unsignedchar", "short", "unsignedshort",
        "int", "unsignedint", "long", "unsignedlong", "longlong", "unsignedlonglong",
        "float", "double"}


class Generator:
    def __init__(self, kit, root):
        self.kit, self.root = Path(kit).resolve(), Path(root).resolve()
        self.targets = json.loads((self.kit / "targets.json").read_text())
        self.types = json.loads((self.kit / "reference/types.json").read_text())
        self.db = json.loads((self.kit / "reference/elfdb.json").read_text())
        self.declarations, self.data = defaultdict(list), defaultdict(list)
        for path in sorted((self.root / "decomp/include").glob("*.h")):
            for decl in llm_context._scan(path.read_text())[0]:
                (self.declarations if decl.kind == "function" else self.data)[decl.qualified].append(
                    (path.name, decl.text))
        self.by_address = self.db["functions"]
        self.globals = {int(g["address"], 16) if isinstance(g["address"], str) else g["address"]: g
                        for g in self.db["globals"]}

    def declaration(self, f):
        method = f.get("method") or ""
        found = []
        for header, text in self.declarations.get(f.get("qualified"), []):
            pattern = re.search(r"\b" + re.escape(method) + r"\s*\(", text)
            if not pattern:
                continue
            end = mutate.matching(text, pattern.end() - 1, "(", ")")
            if end < 0:
                continue
            params = ghidra_cpp.split_args(text[pattern.end():end])
            params = [p for p in params if p not in ("", "void")]
            wanted = ghidra_cpp.split_args(f.get("params") or "")
            wanted = [p for p in wanted if p not in ("", "void")]
            if [mutate.canonical_parameter(spelling(p), named=True) for p in params] != [
                    type_key(p) for p in wanted]:
                continue
            suffix = text[end + 1:].strip().rstrip(";").strip()
            if suffix != f.get("cv", ""):
                continue
            prefix = text[:pattern.start()].strip()
            static = bool(re.search(r"\bstatic\b", prefix))
            ret = re.sub(r"\b(?:virtual|static|inline|explicit)\s+", "", prefix).strip()
            if not ret or re.search(r"[{};=]", ret):
                continue
            names = []
            for i, (param, typ) in enumerate(zip(params, wanted)):
                name = re.search(r"(?:[*&]\s*|\s+)([A-Za-z_]\w*)$", param)
                if name and type_key(param[:name.start(1)]) == type_key(typ):
                    names.append(name[1])
                else:
                    names.append("value" if len(wanted) == 1 else "arg" + str(i + 1))
            found.append({"header": header, "ret": ret, "static": static,
                          "params": list(zip(map(spelling, wanted), names))})
        unique = {json.dumps(d, sort_keys=True): d for d in found}
        if len(unique) != 1:
            raise Unsupported("no unique existing declaration with the exact parameter types and cv")
        decl = next(iter(unique.values()))
        prototype = self.types["prototypes"].get(f["address"], {})
        if not prototype.get("trusted") or prototype.get("variadic") or prototype.get("sret"):
            raise Unsupported("return/static ABI not trusted, variadic or hidden object return")
        if decl["static"] != prototype.get("static"):
            raise Unsupported("static declaration conflicts with exported ABI")
        return decl

    def fields(self, scope, offset=0, seen=()):
        if scope in seen:
            return []
        cls = self.types["classes"].get(scope, {})
        if cls.get("source") != "header":
            return []
        result = [(offset + f["offset"], f) for f in cls.get("fields", [])]
        for base in cls.get("bases", []):
            if isinstance(base.get("offset"), int):
                result += self.fields(base["name"], offset + base["offset"], (*seen, scope))
        return result

    def field(self, f, operand, width):
        match = re.fullmatch(r"(0x[0-9a-f]+)?\(%rdi\)", operand)
        if not match:
            raise Unsupported("not a direct this-field access")
        off = int(match[1] or "0", 16)
        fields = [field for at, field in self.fields(f["scope"]) if at == off and field["size"] == width
                  and "[" not in field["type"] and field["name"]]
        if len(fields) != 1:
            raise Unsupported("field offset/width/type not uniquely established by an existing header")
        field = fields[0]
        if not (primitive(field["type"]) or "*" in field["type"]):
            raise Unsupported("field is not a supported scalar or pointer")
        return field

    def source(self, f, decl, family, body):
        parameters = ", ".join(t + " " + name for t, name in decl["params"])
        cv = (" " + f["cv"]) if f.get("cv") else ""
        code = (decl["ret"] + " " + f["qualified"] + "(" + parameters + ")" + cv + "\n{\n"
                + "".join("    " + line + "\n" for line in body) + "}\n")
        reason = llm_definitions.single_definition(f, code)
        if reason:
            raise Unsupported(reason)
        return {"address": f["address"], "name": f["demangled"], "tu": f["tu_name"],
                "family": family, "header": decl["header"], "source": code,
                "original_size": f["size"], "status": "UNVERIFIED",
                "closure": sorted(llm_definitions.closure(f, self.db))}

    @staticmethod
    def constant(number, typ):
        if type_key(typ) == "bool":
            if number not in (0, 1):
                raise Unsupported("noncanonical bool constant")
            return "true" if number else "false"
        if "*" in typ:
            if number != 0:
                raise Unsupported("non-null numeric pointer")
            return "NULL"
        if type_key(typ) in ("float", "double"):
            if number:
                raise Unsupported("nonzero integer-to-float constant not supported")
            return "0.0f" if type_key(typ) == "float" else "0.0"
        if not primitive(typ):
            raise Unsupported("enum/aggregate immediate needs independent type evidence")
        if number > 0x7fffffff:
            raise Unsupported("large immediate requires signedness review")
        return str(number)

    def generate(self, f):
        if f["source_status"] != "MISSING" or f.get("clone") or f["kind"] != "function":
            raise Unsupported("only missing ordinary method definitions; ABI thunks are compiler output")
        if not f.get("scope") or f["scope"] not in self.types["classes"]:
            raise Unsupported("namespace/free function requires a separate generator")
        prior = self.root / 'decomp/src' / f['tu_name']
        if prior.exists():
            text = prior.read_text()
            if mutate.definition(text, mutate.mask(text), f):
                raise Unsupported('definition already present in the supplied source tree')
        decl = self.declaration(f)
        insns = objdiff.parse_insns((self.kit / f["assembly"]).read_text())
        ops = [(m, p.split("#", 1)[0].strip()) for _, m, p in insns
               if not objdiff.Normalizer.padding(m, p)]
        emit = lambda family, body: self.source(f, decl, family, body)
        if f['method'] == 'CreateObject' and f['size'] in (67, 85):
            calls = []
            for m, p in ops:
                address = re.match(r'([0-9a-f]+)\s*<', p)
                if m == 'call' and address:
                    calls.append((self.by_address.get(hex(int(address[1], 16))), p))
            constructors = [callee for callee, _ in calls if callee and callee['kind'] == 'ctor']
            allocators = [p for _, p in calls if 'Ogre::NedAllocImpl::allocBytes(' in p]
            if (len(calls) != 4 or len(constructors) != 1 or len(allocators) != 1
                    or not any('Ogre::NedAllocImpl::deallocBytes(' in p for _, p in calls)
                    or not any('_Unwind_Resume' in p for _, p in calls)):
                raise Unsupported('factory is not the bounded new/constructor/cleanup idiom')
            ctor = constructors[0]
            cls = self.types['classes'].get(ctor['scope'], {})
            allocations = [int(match[1], 16) for m, p in ops
                           if m == 'mov' and (match := re.fullmatch(r'\$0x([0-9a-f]+),%edi', p))]
            if cls.get('source') != 'header' or allocations != [cls.get('size')]:
                raise Unsupported('factory allocation size not confirmed by existing class header')
            ctors = self.declarations.get(ctor['qualified'], [])
            ctor_params = ghidra_cpp.split_args(ctor.get('params') or '')
            matching = []
            for header, text in ctors:
                match = re.search(re.escape(ctor['method']) + r'\s*\(', text)
                if match:
                    end = mutate.matching(text, match.end() - 1, '(', ')')
                    args = ghidra_cpp.split_args(text[match.end():end])
                    if [mutate.canonical_parameter(spelling(p), named=True) for p in args] == [type_key(p) for p in ctor_params]:
                        matching.append(header)
            if len(set(matching)) != 1:
                raise Unsupported('constructor parameters not declared uniquely')
            if not ctor_params:
                expression = 'new ' + ctor['scope'] + '()'
            elif (ctor_params == ['CResourceManager*'] and len(decl['params']) == 1
                  and type_key(decl['params'][0][0]) == 'CEditorScene*'
                  and any(m == 'mov' and p == '0x68(%rsi),%rbp' for m, p in ops)):
                fields = [field for off, field in self.fields('CEditorScene')
                          if off == 0x68 and type_key(field['type']) == 'CResourceManager*']
                getter = self.root / 'decomp/include/SceneNodeObject.h'
                if len(fields) != 1 or not re.search(
                        r'CResourceManager\s*\*\s*getResourceManager\(\)\s*\{\s*return\s+'
                        + re.escape(fields[0]['name']) + r'\s*;\s*\}', getter.read_text()):
                    raise Unsupported('resource-manager field and existing accessor disagree')
                expression = 'new ' + ctor['scope'] + '(' + decl['params'][0][1] + '->getResourceManager())'
            else:
                raise Unsupported('factory constructor arguments not supported')
            row = emit('object_factory', ['return ' + expression + ';'])
            row['callee_header'] = matching[0]
            row['extra_headers'] = ['EditorScene.h']
            return row
        if ops in ([('ret', '')], [('repz ret', '')]) and decl["ret"] == "void":
            return emit("original_empty_body", [])
        terminal = ops and ops[-1] in [('ret', ''), ('repz ret', '')]
        if terminal:
            body = ops[:-1]
            if len(body) == 1 and decl["ret"] != "void":
                m, p = body[0]
                if (m == "xor" and p == "%eax,%eax") or (m in ("xorps", "pxor") and p == "%xmm0,%xmm0"):
                    return emit("constant_return", ["return " + self.constant(0, decl["ret"]) + ";"])
                imm = re.fullmatch(r"\$0x([0-9a-f]+),%eax", p)
                if m == "mov" and imm:
                    return emit("constant_return", ["return " + self.constant(int(imm[1], 16), decl["ret"]) + ";"])
                load = re.fullmatch(r"(.+),(%rax|%eax|%xmm0)", p)
                if load and not decl["static"] and not decl["params"]:
                    width = {"movzbl": 1, "movsbl": 1, "movss": 4, "movsd": 8}.get(m)
                    if m == "mov":
                        width = 8 if load[2] == "%rax" else 4 if load[2] == "%eax" else None
                    if width:
                        field = self.field(f, load[1], width)
                        if type_key(decl["ret"]) != type_key(field["type"]):
                            raise Unsupported("accessor return and field types differ")
                        return emit("field_getter", ["return " + field["name"] + ";"])
            if decl["ret"] == "void" and not decl["static"] and 1 <= len(body) <= 4:
                registers, integer, floating = {}, 1, 0
                for typ, name in decl["params"]:
                    if type_key(typ) in ("float", "double"):
                        registers['%xmm' + str(floating)] = (name, typ, 4 if type_key(typ) == 'float' else 8)
                        floating += 1
                    else:
                        if integer >= 6:
                            raise Unsupported("stack arguments are unsupported")
                        base = ['rdi', 'rsi', 'rdx', 'rcx', 'r8', 'r9'][integer]
                        for reg, fam in layout.REG64.items():
                            if fam == base:
                                registers['%' + reg] = (name, typ, layout.REG_WIDTH.get(reg))
                        integer += 1
                statements = []
                for m, p in body:
                    pieces = layout.split_operands(p)
                    if len(pieces) != 2:
                        raise Unsupported("not a bounded scalar store sequence")
                    source, dest = pieces
                    if m == 'mov' and source in registers:
                        name, typ, width = registers[source]
                        field = self.field(f, dest, width)
                        if type_key(typ) != type_key(field['type']):
                            raise Unsupported("setter argument/field types differ")
                        statements.append(field['name'] + ' = ' + name + ';')
                    elif m in ('movss', 'movsd') and source in registers:
                        name, typ, width = registers[source]
                        field = self.field(f, dest, 4 if m == 'movss' else 8)
                        if type_key(typ) != type_key(field['type']):
                            raise Unsupported("floating argument/field types differ")
                        statements.append(field['name'] + ' = ' + name + ';')
                    elif m in ('movb', 'movl', 'movq') and source.startswith('$0x'):
                        field = self.field(f, dest, {'movb': 1, 'movl': 4, 'movq': 8}[m])
                        statements.append(field['name'] + ' = ' + self.constant(int(source[1:], 16), field['type']) + ';')
                    else:
                        raise Unsupported("not a supported scalar store")
                return emit('field_stores', statements)
        if len(ops) == 1 and ops[0][0] == 'jmp':
            address = re.match(r'([0-9a-f]+)\s*<', ops[0][1])
            callee = self.by_address.get(hex(int(address[1], 16))) if address else None
            if not callee or callee.get('kind') != 'function':
                raise Unsupported('tail target is not a known ordinary function')
            other = self.declaration(callee)
            if type_key(other['ret']) != type_key(decl['ret']):
                raise Unsupported('tail-call return types differ')
            if [type_key(t) for t, _ in other['params']] != [type_key(t) for t, _ in decl['params']]:
                raise Unsupported('tail-call parameter ABI differs')
            if not other['static'] and (decl['static'] or callee['scope'] != f['scope']):
                bases = self.types['classes'].get(f['scope'], {}).get('bases', [])
                if decl['static'] or not any(b['name'] == callee['scope'] and b['offset'] == 0 for b in bases):
                    raise Unsupported('tail-call receiver adjustment not proven')
            if other['static'] and decl['params'] and not decl['static']:
                raise Unsupported('member-to-static argument registers differ')
            call = callee['qualified'] + '(' + ', '.join(n for _, n in decl['params']) + ');'
            row = emit('direct_tail_wrapper', [("return " if decl['ret'] != 'void' else '') + call])
            row['callee_header'] = other['header']
            return row
        raise Unsupported('no supported semantic idiom')

    def run(self, output):
        output = Path(output); output.mkdir(parents=True, exist_ok=True)
        candidates, blocked = [], []
        for f in self.targets:
            try:
                row = self.generate(f)
                candidates.append(row)
            except Unsupported as exc:
                blocked.append({'address': f['address'], 'name': f['demangled'], 'tu': f['tu_name'],
                                'original_size': f['size'], 'status': 'BLOCKED', 'reason': str(exc)})
        units = defaultdict(list)
        for row in candidates:
            units[row['tu']].append(row)
        for name, rows in units.items():
            prior = self.root / 'decomp/src' / name
            text = prior.read_text() if prior.exists() else ''
            headers = sorted({r['header'] for r in rows} | {r['callee_header'] for r in rows if 'callee_header' in r}
                             | {h for r in rows for h in r.get('extra_headers', [])})
            missing = [h for h in headers if '#include "' + h + '"' not in text]
            result = ''.join('#include "' + h + '"\n' for h in missing) + text
            result += '\n' + '\n'.join(r['source'] for r in rows)
            (output / name).write_text(result)
        report = {'schema': 1, 'policy': 'smallmatch-v1', 'candidates': candidates, 'blocked': blocked,
                  'candidate_count': len(candidates), 'candidate_bytes': sum(r['original_size'] for r in candidates),
                  'families': dict(Counter(r['family'] for r in candidates)), 'tu_count': len(units),
                  'accepted_count': 0, 'note': 'Generation only; no function is accepted by this report.'}
        (output / 'generation.json').write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n')
        return {k: v for k, v in report.items() if k not in ('candidates', 'blocked')}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--kit', type=Path, required=True)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(Generator(args.kit, args.root).run(args.output), indent=2))


if __name__ == '__main__':
    main()
