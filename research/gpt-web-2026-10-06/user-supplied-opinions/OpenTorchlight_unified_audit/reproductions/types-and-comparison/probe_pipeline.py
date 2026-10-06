#!/usr/bin/env python3
"""Read-only probes of the supplied OpenTorchlight tools.

Requires Python 3.10+, g++, readelf, and objdump. Uses the HOST compiler, not
Torchlight's GCC 4.4.7. No game binary, game process, or network is used.

Usage: python3 probe_pipeline.py /path/to/OpenTorchlight --out results.json
These are diagnostic reproductions, not patches or game verification.
"""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile


def run(args: list[str]) -> str:
    p = subprocess.run(args, text=True, capture_output=True, timeout=30)
    if p.returncode:
        raise RuntimeError(f'Command failed: {args!r}\n{p.stdout}\n{p.stderr}')
    return p.stdout


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('repo', type=Path)
    ap.add_argument('--out', type=Path, default=Path('probe-results.json'))
    a = ap.parse_args()
    repo = a.repo.resolve()
    tools = repo / 'tools/decomp'
    if not (tools / 'types_export.py').is_file():
        ap.error('Not an OpenTorchlight checkout: tools/decomp/types_export.py missing')
    for cmd in ('g++', 'readelf', 'objdump'):
        if shutil.which(cmd) is None:
            ap.error(f'Required command missing: {cmd}')
    sys.path.insert(0, str(tools))
    import types_export as te
    import objdiff
    import elfimage

    result = {'scope': 'synthetic host-compiler tests; no original ELF and no Ghidra run',
              'compiler': run(['g++', '--version']).splitlines()[0], 'probes': {}}
    out = result['probes']
    with tempfile.TemporaryDirectory(prefix='otl-probes-') as td:
        root = Path(td)
        def compile_obj(name: str, code: str, debug: bool = False) -> Path:
            src, obj = root / (name + '.cpp'), root / (name + '.o')
            src.write_text(code, encoding='utf-8')
            flags = ['-std=gnu++98', '-O2', '-fno-pie', '-fno-reorder-blocks-and-partition']
            if debug:
                flags += ['-g', '-gdwarf-2', '-O0', '-fno-eliminate-unused-debug-types',
                          '-femit-class-debug-always']
            run(['g++', *flags, '-c', str(src), '-o', str(obj)])
            return obj

        # Real DWARF, not a fabricated DIE graph.
        obj = compile_obj('types', '''
namespace First { struct Cell { int a; }; }
namespace Second { struct Cell { double b; long c; }; }
struct Holder { First::Cell *one; Second::Cell *two; long amount; unsigned long *indices; };
First::Cell first; Second::Cell second; Holder holder;
''', debug=True)
        dies = te.parse_dies(obj)
        classes = te.header_classes(dies)
        holder = classes.get('Holder', {})
        cell_records = [{'ref': hex(ref), 'size': d['attrs'].get('DW_AT_byte_size'),
                         'depth': d['depth']} for ref, d in dies.items()
                        if d['tag'] in ('DW_TAG_structure_type', 'DW_TAG_class_type')
                        and d['attrs'].get('DW_AT_name') == 'Cell'
                        and not d['attrs'].get('DW_AT_declaration')]
        out['namespace_identity'] = {
            'input': ['First::Cell (sizeof=4)', 'Second::Cell (sizeof=16)'],
            'dwarf_cell_definitions': cell_records,
            'exported_keys': list(classes), 'exported_cell': classes.get('Cell'),
            'holder_fields': holder.get('fields'),
            'collision_observed': len(cell_records) == 2 and 'Cell' in classes
                and 'First::Cell' not in classes and 'Second::Cell' not in classes,
        }
        java = (tools / 'ghidra/DecompDrafts.java').read_text()
        amount = next((x for x in holder.get('fields', []) if x['name'] == 'amount'), None)
        out['lp64_importer'] = {
            'host_dwarf_amount_field': amount,
            'signed_long_mapped_to_IntegerDataType_in_java':
                'case "int": case "long int": return IntegerDataType.dataType;' in java,
            'unsigned_long_pointer_pointee_uses_size_zero':
                'primitive(inner, 0)' in java,
            'note': 'Java behavior established by source inspection, not execution in Ghidra.'}

        fake_db = {'functions': {
            '0x100': {'demangled': 'Derived::mainVirtual(int)'},
            '0x200': {'demangled': 'Derived::secondaryVirtual(float)'}},
            'vtables': {'Derived': {'groups': [
                {'offset_to_top': 0, 'slots': ['0x100']},
                {'offset_to_top': -16, 'slots': ['0x200']} ]}}}
        exported = te.vtables(fake_db)
        out['secondary_vtable'] = {
            'input_groups': 2, 'input_slots': 2, 'exported': exported,
            'secondary_slot_missing': 'secondaryVirtual' not in json.dumps(exported),
            'void_slot_pointer_in_java':
                'new PointerDataType(VoidDataType.dataType, 8, dtm), 8, slot.getAsString()' in java}

        # Complete function-normalization route, including ELF relocation parsing.
        def call_literal(name: str, value: str) -> Path:
            return compile_obj(name, 'extern "C" void sink(const char*);\n'
                               'extern "C" void probe(){sink(' + json.dumps(value) + ');}\n')
        o1, o2 = call_literal('literal_a', 'A' * 80 + 'X'), call_literal('literal_b', 'A' * 80 + 'Y')
        o3 = call_literal('literal_control', 'B' + 'A' * 79 + 'X')
        n1, n2, n3 = [objdiff.object_functions(p)['probe']['norm'] for p in (o1,o2,o3)]
        out['long_literal_normalization'] = {
            'different_values_after_character_80': True,
            'normalized_functions_equal': n1 == n2,
            'code_digest_equal': objdiff.code_digest(n1) == objdiff.code_digest(n2),
            'changed_first_character_detected': n1 != n3,
            'normalized_instructions': n1}

        # Identical instruction streams can hide different typed catch clauses.
        def catch_obj(name: str, typ: str) -> Path:
            return compile_obj(name, '''extern "C" void raise_value();
extern "C" int probe() { try { raise_value(); } catch (''' + typ + ''') { return 7; } return 0; }
''')
        ci, cd = catch_obj('catch_int', 'int'), catch_obj('catch_double', 'double')
        ni, nd = [objdiff.object_functions(p)['probe']['norm'] for p in (ci,cd)]
        driver = root/'driver.cpp'
        driver.write_text('''#include <cstdio>
extern "C" int probe();
extern "C" void raise_value(){throw 1;}
int main(){int value;try{value=probe();}catch(...){value=99;}std::printf("%d\\n",value);return 0;}
''')
        outputs = []
        for i, ob in enumerate((ci, cd)):
            binary = root / f'catch_demo_{i}'
            run(['g++', '-std=gnu++98', '-no-pie', str(ob), str(driver), '-o', str(binary)])
            outputs.append(run([str(binary)]).strip())
        def eh_refs(p: Path) -> list[str]:
            ob = elfimage.load_object(p)
            result = []
            for idx, rs in ob.relocs.items():
                if ob.sections[idx].name.startswith('.gcc_except_table') or ob.sections[idx].name.startswith('.data'):
                    result.extend(r.symbol.name for r in rs if r.symbol.name)
            return sorted(set(result))
        out['typed_catch_normalization'] = {
            'normalized_functions_equal': ni == nd,
            'code_digest_equal': objdiff.code_digest(ni) == objdiff.code_digest(nd),
            'catch_int_runtime_output': outputs[0], 'catch_double_runtime_output': outputs[1],
            'runtime_behavior_differs': outputs[0] != outputs[1],
            'exception_table_references': {'int':eh_refs(ci),'double':eh_refs(cd)},
            'normalized_instructions': {'int':ni,'double':nd},
            'note': 'Outputs 7 and 99 are deliberately distinct catch paths, not crashes.'}

    # Current archive counts. These are declarations, not verified game coverage.
    multiple = []
    for h in sorted((repo/'decomp/include').glob('*.h')):
        for m in re.finditer(r'^\s*(?:class|struct)\s+(\w+)\s*:\s*([^\{;]+)\{', h.read_text(), re.M):
            if len(re.findall(r'\b(?:public|protected|private)\b', m[2])) >= 2:
                multiple.append({'header':str(h.relative_to(repo)), 'class':m[1],
                                 'bases':' '.join(m[2].split())})
    result['multiple_inheritance_declarations'] = {'count':len(multiple), 'items':multiple}
    a.out.parent.mkdir(parents=True, exist_ok=True)
    a.out.write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    print(json.dumps(result, ensure_ascii=False, indent=2))

if __name__ == '__main__':
    main()
