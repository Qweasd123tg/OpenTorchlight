#!/usr/bin/env python3
"""Shared package collection, exact-source gates and bounded export contracts."""
import copy
import hashlib
import json
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import assemble_machine_package as machine
from setup_ghidra import VERSION
from shared_machine_indirect_test import function, instruction, op, node, ret, push, indirect_caller


class MachinePackageTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='machine-package-', dir='/tmp')
        self.addCleanup(self.temp.cleanup)
        self.base = Path(self.temp.name)
        self.original = self.base / 'source' / 'original'
        self.original.parent.mkdir(); self.original.write_bytes(b'isolated unit source')
        self.sha = machine.digest(self.original)
        self.profile = self.base / 'profile.json'
        self.profile.write_text(json.dumps(dict(schema=1, execution_mode='shared_machine',
            memory_space_id=433, original_elf_sha256=self.sha)))
        self.caller = function([instruction(0x100, push(0x105)+[
            op('CALL', None, node('ram', 0x200, 8))], 0x105), instruction(0x105, ret())])
        self.leaf = function([instruction(0x200, ret())])
        self.other = function([instruction(0x300, ret())])
        self.packets = {p['address']: p for p in (self.caller, self.leaf, self.other)}
        for p in self.packets.values():
            p['original_elf_sha256'] = self.sha
            lo=int(p['address'],16); hi=max(int(i['address'],16) for i in p['instructions'])+1
            p['body_ranges']=[dict(start=hex(lo),end_inclusive=hex(hi-1))]
        self.symbols = [SimpleNamespace(address=int(a,16),size=16,kind='T') for a in self.packets]
        self.source = dict(sha256='unchanged')
        self.raw = self.base / 'raw'; self.raw.mkdir()
        self.batch(self.raw, [self.caller])

    def batch(self, path, packets):
        path.mkdir(exist_ok=True,parents=True)
        rows=[]
        for p in packets:
            name=p['address'][2:]+'.json'; (path/name).write_text(json.dumps(p))
            rows.append(dict(address=p['address'],status='exported',json=name))
        (path/'manifest.json').write_text(json.dumps(dict(schema=2,original_elf_sha256=self.sha,
            ghidra_version=VERSION,language='x86:LE:64:default',functions=rows,
            program_modified_by_script=False,game_executed=False)))

    def original_factory(self, _):
        byte_map={int(i['address'],16):bytes.fromhex(i['bytes'])[0]
                  for p in self.packets.values() for i in p['instructions']}
        return SimpleNamespace(sha256=self.sha,symbols=self.symbols,
            read=lambda a,n: bytes(byte_map.get(i,0) for i in range(a,a+n)))

    def options(self, **changes):
        values=dict(output=self.base/'output',entries=('0x100',),raw_dirs=(self.raw,),
            profile=self.profile,original=self.original,home=self.base/'tool',
            analysis_root=self.base/'project',max_functions=8,max_rounds=2)
        values.update(changes);return machine.Options(**values)

    def run_package(self, runner=None, **changes):
        return machine.run(self.options(**changes),runner=runner,snapshotter=lambda _:dict(self.source),
                           original_factory=self.original_factory)

    def child(self, command, log):
        log.write_text('synthetic exact child\n')
        out=Path(command[command.index('--output')+1]);out.mkdir()
        entries=Path(command[command.index('--targets-file')+1]).read_text().splitlines()
        if Path(command[1]).name=='prepare_lift_project.py':
            report=dict(schema=1,kind='bounded-lift-project-preparation',status='PREPARED',
                source_consistent=True,original_status_promotions=0,original_modified=False,
                game_executed=False,analysis_requested=False,decompiler_requested=False,
                project_database_modified=True,requested_targets=entries)
        else:
            self.batch(out/'raw',[self.packets[e] for e in entries])
            report=dict(schema=1,kind='raw-function-lift-screening',status='SCREENED',source_consistent=True,
                original_status_promotions=0,game_executed=False,original_modified=False,
                selection=dict(selected=[dict(address=e) for e in entries]))
        (out/'report.json').write_text(json.dumps(report));return 0

    def test_static_dependency_collected_and_emitted_without_function_abi(self):
        result=self.run_package(self.child,export=True,prepare_project=True)
        self.assertEqual(result['status'],'GENERATED',result.get('error'))
        self.assertEqual(result['selected_entries'],['0x00000100','0x00000200'])
        self.assertEqual(result['counts'],dict(exported=1,rounds=1))
        self.assertEqual([Path(c['command'][1]).name for c in result['commands']],
                         ['prepare_lift_project.py','screen_function_lifts.py'])
        report=json.loads((self.base/'output/generation.json').read_text())
        self.assertEqual(report['execution_mode'],'shared_machine')
        self.assertEqual(report['closure']['maximum_selected_depth'],2)
        self.assertFalse(result['game_executed']);self.assertEqual(result['original_status_promotions'],0)

    def test_missing_dependency_is_a_plan_until_export_is_explicit(self):
        result=self.run_package()
        self.assertEqual(result['status'],'NEEDS_EXPORT')
        self.assertEqual((self.base/'output/missing-targets.txt').read_text(),'0x00000200\n')
        self.assertFalse((self.base/'output/program.hpp').exists());self.assertFalse(result['commands'])

    def test_reuses_supplied_body_without_export_and_ignores_unrelated_unsupported(self):
        bad=copy.deepcopy(self.other);bad['instructions'][0]['pcode'][0]['operation']='CALLOTHER'
        self.batch(self.raw,[self.caller,self.leaf,bad])
        result=self.run_package()
        self.assertEqual(result['status'],'GENERATED',result.get('error'))
        self.assertNotIn('0x00000300',result['selected_entries']);self.assertFalse(result['commands'])

    def observation(self, **changes):
        value=dict(schema=1,kind='observed-machine-call-targets',original_elf_sha256=self.sha,targets=['0x200'])
        value.update(changes);path=self.base/'observed.json';path.write_text(json.dumps(value));return path

    def test_observed_target_extends_indirect_dispatch_only_after_exact_source_check(self):
        caller=indirect_caller();caller['original_elf_sha256']=self.sha
        caller['body_ranges']=self.caller['body_ranges'];self.packets[caller['address']]=caller
        self.batch(self.raw,[caller,self.leaf])
        result=self.run_package(observed_targets=(self.observation(),))
        self.assertEqual(result['status'],'GENERATED',result.get('error'))
        self.assertEqual(len(result['dynamic_callsites']),1)
        self.assertEqual(result['selected_entries'],['0x00000100','0x00000200'])
        self.assertFalse(result['replay_performed']);self.assertIn('not exhaustive',result['dynamic_target_coverage'])

    def test_observation_rejects_wrong_elf_interior_zero_and_non_address(self):
        for changes in (dict(original_elf_sha256='f'*64),dict(targets=['0x201']),
                        dict(targets=['0x0']),dict(targets=[512]),dict(targets=[])):
            with self.subTest(changes=changes):
                result=self.run_package(output=self.base/('out'+str(len(list(self.base.glob('out*'))))),
                    observed_targets=(self.observation(**changes),))
                self.assertEqual(result['status'],'BLOCKED');self.assertIn('error',result)
                self.assertFalse(result['commands'])

    def test_stale_source_or_external_raw_stops_before_publication(self):
        for external in (False,True):
            with self.subTest(external=external):
                self.source['sha256']='unchanged'
                def change(command,log):
                    result=self.child(command,log)
                    if external:(self.raw/'manifest.json').write_text('{}')
                    else:self.source['sha256']='changed'
                    return result
                result=self.run_package(change,export=True,output=self.base/('ext' if external else 'src'))
                self.assertEqual(result['status'],'STALE');self.assertFalse(result['source_consistent'])
                self.assertEqual(len(result['commands']),1)

    def test_failed_export_is_not_retried(self):
        def fail(command,log):log.write_text('failure');return 2
        result=self.run_package(fail,export=True)
        self.assertEqual(result['status'],'BLOCKED');self.assertEqual(len(result['commands']),1)
        self.assertEqual(result['counts']['exported'],0)

    def test_symbol_ambiguity_budget_and_profile_gate(self):
        self.symbols.append(SimpleNamespace(address=0x200,size=17,kind='T'))
        result=self.run_package()
        self.assertIn('Ambiguous original symbol sizes',result['error'])
        self.symbols.pop()
        result=self.run_package(output=self.base/'small',max_functions=1)
        self.assertIn('budget exceeded',result['error'])
        profile=json.loads(self.profile.read_text());profile['execution_mode']='scalar';self.profile.write_text(json.dumps(profile))
        result=self.run_package(output=self.base/'scalar')
        self.assertIn('shared_machine profile',result['error'])

    def test_duplicate_packet_conflict_and_failed_packet_are_not_silently_repaired(self):
        extra=self.base/'extra';changed=copy.deepcopy(self.caller);changed['symbol']='different'
        self.batch(extra,[changed])
        result=self.run_package(raw_dirs=(self.raw,extra))
        self.assertIn('Conflicting duplicate',result['error'])
        manifest=json.loads((self.raw/'manifest.json').read_text());manifest['functions'][0]['status']='missing_function'
        (self.raw/'manifest.json').write_text(json.dumps(manifest))
        result=self.run_package(output=self.base/'failed')
        self.assertIn('requires review',result['error']);self.assertFalse(result['commands'])

    def test_child_wrong_selection_and_source_bytes_fail(self):
        def wrong(command,log):
            result=self.child(command,log);out=Path(command[command.index('--output')+1])
            report=json.loads((out/'report.json').read_text());report['selection']['selected']=[]
            (out/'report.json').write_text(json.dumps(report));return result
        result=self.run_package(wrong,export=True)
        self.assertIn('selection',result['error'])
        packet=json.loads((self.raw/'00000100.json').read_text());packet['instructions'][0]['bytes']='91'
        (self.raw/'00000100.json').write_text(json.dumps(packet))
        result=self.run_package(output=self.base/'byte-drift')
        self.assertIn('bytes differ',result['error'])

    def test_round_budget_and_fresh_output_are_explicit(self):
        middle=function([instruction(0x200,push(0x205)+[op('CALL',None,node('ram',0x300,8))],0x205),
                         instruction(0x205,ret())]);middle['original_elf_sha256']=self.sha
        middle['body_ranges']=[dict(start='0x200',end_inclusive='0x205')];self.packets[middle['address']]=middle
        result=self.run_package(self.child,export=True,max_rounds=1)
        self.assertEqual(result['status'],'ROUND_BUDGET');self.assertEqual(result['missing_entries'],['0x00000300'])
        self.assertFalse((self.base/'output/program.hpp').exists())
        with self.assertRaisesRegex(ValueError,'fresh output'):self.run_package()
        with self.assertRaisesRegex(ValueError,'requires explicit'):self.run_package(output=self.base/'fresh',prepare_project=True)


if __name__=='__main__':unittest.main()
