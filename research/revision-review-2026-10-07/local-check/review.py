#!/usr/bin/env python3
"""Extra isolated candidate QA. Real pinned EH; explicitly mocked queue/Stage IO."""
from contextlib import contextmanager, ExitStack
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
from unittest.mock import patch

REPO = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(REPO / 'tools/decomp'))
import acceptance
import candidate
import check
import elfdb
import evidence
import llm_loop
import no_llm_loop
import objdiff
import publication
import toolchain

OUT = REPO / 'build-decomp/revision-review/local-candidate'
OUT.mkdir(parents=True, exist_ok=True)
RESULTS = {}

def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()

def run(command):
    p = subprocess.run([str(x) for x in command], check=True, capture_output=True, text=True, timeout=30)
    return p.stdout.strip()

def require(condition, message):
    if not condition:
        raise AssertionError(message)

def fixture(name):
    root = OUT / name
    if root.exists():
        shutil.rmtree(root)
    (root / 'decomp/src').mkdir(parents=True, exist_ok=True)
    (root / 'decomp/include').mkdir(exist_ok=True)
    (root / 'decomp/config.json').write_text(json.dumps({'cflags': ['-O2', '-fno-strict-aliasing'], 'include': [], 'system_include': []}))
    return root

def eh_probe():
    source = '#include "Types.h"\nextern void raise_value();\nint probe() { try { raise_value(); return 0; } catch(ErrorType) { return 7; } }\n'
    main = '#include <cstdio>\nvoid raise_value(){throw 1;}\nint probe(); int main(){try{std::printf("%d",probe());}catch(...){std::printf("99");}}\n'
    rows, sources = [], []
    for name, typ in [('before', 'int'), ('after', 'double')]:
        d = OUT / 'eh' / name
        d.mkdir(parents=True, exist_ok=True)
        s, m, o, mo, exe = [d / p for p in ('Probe.cpp', 'Main.cpp', 'probe.o', 'main.o', 'probe.exe')]
        s.write_text(source); m.write_text(main)
        (d / 'Types.h').write_text('typedef %s ErrorType;\n' % typ)
        toolchain.compile_source(s, o, cache=False)
        toolchain.compile_source(m, mo, cache=False)
        run(['c++', '-no-pie', o, mo, '-o', exe])
        mine = objdiff.object_functions(o)['_Z5probev']
        rows.append({'address': '0x100', 'status': 'DIFF', 'code': objdiff.code_digest(mine['norm']),
                     'metadata_reasons': mine['metadata_reasons'], 'object_digest': sha(o), 'execution': int(run([exe]))})
        sources.append(s)
    f = {'address': '0x100', 'demangled': 'probe()', 'scope': '', 'method': 'probe', 'params': '', 'cv': '', 'kind': 'function'}
    kept = candidate.preserve_existing(sources[0], sources[1], {'0x100': rows[0]}, [rows[1]], {'functions': {'0x100': f}},
                                      before_object=rows[0]['object_digest'], after_object=rows[1]['object_digest'])
    require(sources[0].read_bytes() == sources[1].read_bytes(), 'EH source bodies changed')
    require(rows[0]['code'] == rows[1]['code'], 'EH normalized code differs; no intended regression reproduction')
    require(rows[0]['object_digest'] != rows[1]['object_digest'], 'EH full objects did not change')
    require([r['execution'] for r in rows] == [7, 99], 'EH catch outcomes wrong')
    require(not kept, 'changed EH context was incorrectly preserved')
    return {'proof': 'real pinned GCC 4.4.7 compile, real objdiff normalization, real native execution; host linker/runtime',
            'rows': rows, 'same_function_source': True, 'same_normalized_code': True, 'preserve_existing': kept,
            'compiler_comment': run(['readelf', '-p', '.comment', OUT / 'eh/before/probe.o'])}

def function(address, name):
    return {'address': address, 'demangled': name + '()', 'scope': '', 'method': name, 'params': '', 'cv': '', 'kind': 'function'}

class FakeStage:
    """Only compiler/Stage IO is mocked; covered comes from actual report parser."""
    def __init__(self, root, rows, digest, report=()):
        self.path = fixture(root.name + '-stage')
        self.root = root
        self.rows, self.digest, self.report = rows, digest, list(report)
        self.baseline = publication.tree_state(root)
        self.validate_calls = 0
        self.final_units = []
        self.covered = set()
        self.validated_inputs = 'fresh-stage-inputs'
    @contextmanager
    def activate(self):
        saved = {k: os.environ.get(k) for k in ('OTL_EXTRA_INCLUDE', 'OTL_INCLUDE_ROOT')}
        try:
            os.environ['OTL_INCLUDE_ROOT'] = str(self.path)
            yield self
        finally:
            for key, value in saved.items():
                if value is None:
                    os.environ.pop(key, None)
                else:
                    os.environ[key] = value
    def validate(self):
        self.validate_calls += 1
        self.final_units = [{'source': str(self.path / 'decomp/src/Unit.cpp'), 'functions': self.rows,
                             'unknown': [], 'object_digest': self.digest}]
        self.covered = check.shadow_covered(self.db, self.report)
        return self.final_units

def mocked_candidate(root, stage, db, before_rows, after_rows, before_digest, after_digest):
    stack = ExitStack()
    stage.db = db
    def compare(path, *args, **kwargs):
        baseline = Path(path) == root / 'decomp/src/Unit.cpp'
        return {'source': str(path), 'functions': before_rows if baseline else after_rows,
                'unknown': [], 'object_digest': before_digest if baseline else after_digest}
    stack.enter_context(patch.object(candidate.elfdb, 'load_db', return_value=db))
    stack.enter_context(patch.object(candidate.evidence, 'input_digest', return_value='same-inputs'))
    stack.enter_context(patch.object(candidate.objdiff, 'Original', return_value=object()))
    compiler = stack.enter_context(patch.object(candidate.objdiff, 'compare_source', side_effect=compare))
    stack.enter_context(patch.object(candidate.promote, 'promote'))
    return stack, compiler

def cache_probe():
    root = fixture('cache')
    old = root / 'decomp/src/Unit.cpp'; old.write_text('int value(){return 7;}\n')
    proposed = root / 'candidate.cpp'; proposed.write_text(old.read_text() + 'int added(){return 8;}\n')
    prior = {'address': '0x1', 'status': 'DIFF', 'code': 'same', 'metadata_reasons': ['unverified EH']}
    added = {'address': '0x2', 'status': 'MATCH', 'code': 'new'}
    db = {'original_elf_sha256': 'fake-original', 'tus': [{'name': 'Unit.cpp', 'kind': 'game'}],
          'functions': {'0x1': function('0x1', 'value'), '0x2': function('0x2', 'added')}}
    stage = FakeStage(root, [prior, added], 'same-full-object')
    (stage.path / 'decomp/src/Unit.cpp').write_bytes(proposed.read_bytes())
    stack, compiler = mocked_candidate(root, stage, db, [prior], [prior, added], 'same-full-object', 'same-full-object')
    with stack:
        a = candidate.evaluate('Unit.cpp', proposed, root=root, stage=stage, incremental=False)
        n = compiler.call_count
        b = candidate.evaluate('Unit.cpp', proposed, root=root, stage=stage, incremental=True)
        require(compiler.call_count > n, 'incremental candidate incorrectly reused nonincremental failure')
        n = compiler.call_count
        c = candidate.evaluate('Unit.cpp', proposed, root=root, stage=stage, incremental=False)
        require(c.get('cached_failure') is True, 'same nonincremental failure did not reuse cache')
        require(compiler.call_count == n, 'cache hit unexpectedly recompiled')
    require(a['status'] == 'DIFF' and b['status'] == 'MATCH' and c['status'] == 'DIFF', 'cache mode outcomes wrong')
    return {'proof': 'real candidate control flow/cache/preservation/report parser; compiler/digests and Stage validation IO explicitly mocked',
            'nonincremental': a, 'incremental': b, 'repeated_nonincremental': c, 'compiler_calls': compiler.call_count,
            'stage_validate_calls': stage.validate_calls}

def preservation_probe():
    out = {}
    old_row = {'address': '0x1', 'status': 'DIFF', 'code': 'unchanged', 'metadata_reasons': ['unverified EH']}
    new_row = {'address': '0x2', 'status': 'MATCH', 'code': 'new'}
    db = {'original_elf_sha256': 'fake-original', 'tus': [{'name': 'Unit.cpp', 'kind': 'game'}],
          'functions': {'0x1': function('0x1', 'value'), '0x2': function('0x2', 'added')}}
    for name, digest, report, expected in [
        ('same_object', 'old-object', [], 'MATCH'),
        ('missing_object', None, [], 'DIFF'),
        ('changed_object', 'changed-object', [], 'DIFF'),
        ('fresh_changed_object', 'changed-object',
         ['tlhybrid: Existing PASS (0)', '  coverage Existing 0x1 completed 20 different 0 incomplete 0'], 'MATCH'),
    ]:
        root = fixture('preservation-' + name)
        old = root / 'decomp/src/Unit.cpp'; old.write_text('int value(){return 7;}\n')
        proposed = root / 'candidate.cpp'; proposed.write_text(old.read_text() + 'int added(){return 8;}\n')
        stage = FakeStage(root, [old_row, new_row], digest, report)
        stack, compiler = mocked_candidate(root, stage, db, [old_row], [old_row, new_row], 'old-object', digest)
        with stack:
            result = candidate.evaluate('Unit.cpp', proposed, root=root, stage=stage, incremental=True)
        require(result['status'] == expected, 'candidate full-object preservation wrong: ' + name)
        out[name] = result
    out['proof'] = 'real candidate preservation/control flow; identical function source and normalized rows, explicitly mocked full-object digests/Stage IO'
    return out

def behavioral_probe():
    out = {}
    row = {'address': '0x3', 'status': 'DIFF', 'code': 'new', 'metadata_reasons': ['unverified EH']}
    db = {'original_elf_sha256': 'fake-original', 'tus': [{'name': 'Unit.cpp', 'kind': 'game'}],
          'functions': {'0x3': function('0x3', 'new_value')}}
    reports = {
        'fresh': ['tlhybrid: NewValue PASS (0)', '  coverage NewValue 0x3 completed 20 different 0 incomplete 0'],
        'absent': ['tlhybrid: NewValue PASS (0)'],
        'incomplete': ['tlhybrid: NewValue PASS (0)', '  coverage NewValue 0x3 completed 20 different 0 incomplete 1'],
        'different': ['tlhybrid: NewValue PASS (0)', '  coverage NewValue 0x3 completed 20 different 1 incomplete 0'],
    }
    for name, report in reports.items():
        root = fixture('behavioral-' + name)
        proposed = root / 'candidate.cpp'; proposed.write_text('int new_value(){return 7;}\n')
        stage = FakeStage(root, [row], 'validated-final-object', report)
        stack, compiler = mocked_candidate(root, stage, db, [], [row], None, 'earlier-final-object')
        with stack:
            result = candidate.evaluate('Unit.cpp', proposed, root=root, stage=stage, incremental=True)
        require(result['status'] == ('BEHAVIORAL' if name == 'fresh' else 'DIFF'), 'behavioral outcome wrong: ' + name)
        out[name] = result
        if name == 'fresh':
            receipt = result['comparison_evidence']['0x3']
            require(evidence.current(receipt, 'validated-final-object', 'fresh-stage-inputs'), 'fresh binding rejected')
            require(not evidence.current(receipt, None, 'fresh-stage-inputs'), 'missing final object accepted')
            require(not evidence.current(receipt, 'changed-final-object', 'fresh-stage-inputs'), 'changed final object accepted')
            require(not evidence.current(receipt, 'validated-final-object', 'changed-inputs'), 'changed inputs accepted')
            (root / 'build-decomp').mkdir(exist_ok=True)
            (root / 'build-decomp/progress.json').write_text(json.dumps({'comparison_evidence': {'0x3': receipt}}))
            require(acceptance.prior_compared(root, db) == {'0x3'}, 'accepted prior comparison not loaded')
            out['object_binding_negative_controls'] = {'missing_object': False, 'changed_object': False, 'changed_inputs': False,
                                                      'fresh_object': True}
    out['proof'] = 'real candidate, check receipt parser, acceptance binding/load, evidence identity; compiler rows and Stage execution mocked, no Torchlight execution'
    return out

def provider_probe():
    root = fixture('provider')
    input_dir = root / 'input'; input_dir.mkdir(exist_ok=True)
    source = input_dir / 'Equipment.cpp'; source.write_text('int candidate_input(){return 11;}\n')
    db = {'tus': [{'id': 1, 'name': 'Equipment.cpp', 'kind': 'game'},
                  {'id': 2, 'name': 'FooDescriptor.cpp', 'kind': 'game'}]}
    dummy = type('StagePath', (), {'path': root})()
    with patch.object(no_llm_loop.elfdb, 'ROOT', root), patch.object(no_llm_loop.elfdb, 'load_db', return_value=db), \
         patch.object(no_llm_loop.evidence, 'input_digest', return_value='same-inputs'), \
         patch.object(no_llm_loop.publication, 'Stage', return_value=dummy), \
         patch.object(no_llm_loop.candidate, 'evaluate', return_value={'tu': 'Equipment.cpp', 'status': 'MATCH', 'published': False}) as evaluate, \
         patch.object(no_llm_loop, 'provide', side_effect=AssertionError('universal generation must not occur')), \
         patch.object(llm_loop.Model, '__init__', side_effect=AssertionError('model construction forbidden')), \
         patch.object(llm_loop.Model, 'ask', side_effect=AssertionError('model call forbidden')):
        result = no_llm_loop.run(['Equipment.cpp'], 'candidate', input_dir=input_dir)
        require(evaluate.call_count == 1 and evaluate.call_args.args == ('Equipment.cpp', source), 'explicit candidate did not route correctly')
        require(evaluate.call_args.kwargs.get('incremental') is True, 'candidate should be incremental')
        failures = {}
        for label, tus, provider, supplied in [('implicit_candidate', [], 'candidate', input_dir),
                                              ('missing_input', ['Equipment.cpp'], 'candidate', None),
                                              ('unsupported_descriptor', ['Equipment.cpp'], 'descriptor', None)]:
            try:
                no_llm_loop.run(tus, provider, input_dir=supplied)
            except ValueError as error:
                failures[label] = str(error)
            else:
                raise AssertionError('unsupported generation request accepted: ' + label)
    return {'proof': 'real provider routing and argument guards; evaluate and Stage IO mocked, model/generator methods forbidden',
            'explicit_candidate': result, 'negative_controls': failures, 'model_calls': 0, 'generator_calls': 0}

def main():
    OUT.mkdir(parents=True, exist_ok=True)
    for name, probe in [('eh', eh_probe), ('cache_modes', cache_probe), ('preservation', preservation_probe), ('behavioral', behavioral_probe), ('provider', provider_probe)]:
        try:
            RESULTS[name] = {'status': 'PASS', 'result': probe()}
        except Exception as error:
            RESULTS[name] = {'status': 'FAIL', 'error': '%s: %s' % (type(error).__name__, error)}
        (OUT / 'results.json').write_text(json.dumps(RESULTS, indent=2, ensure_ascii=False) + '\n')
        print(name, RESULTS[name]['status'], RESULTS[name].get('error', ''), flush=True)
    return 0 if all(row['status'] == 'PASS' for row in RESULTS.values()) else 1

if __name__ == '__main__':
    raise SystemExit(main())
