#!/usr/bin/env python3
"""Bounded raw CALLIND dispatch, guest effects and host-budget contracts."""
import copy
import hashlib
import json
from pathlib import Path
import tempfile
import unittest

import pcode_lifter_test as fixtures

ROOT, lift = fixtures.ROOT, fixtures.lift
node, op, instruction, ret, function = (
    fixtures.node, fixtures.op, fixtures.instruction, fixtures.ret, fixtures.function)


def profile(**extra):
    result = dict(schema=1, original_elf_sha256=fixtures.SHA, memory_space_id=433,
                  execution_mode='shared_machine')
    result.update(extra)
    return result


def push(return_address):
    return [op('INT_SUB', node('register', 0x20, 8), node('register', 0x20, 8), node('const', 8, 8)),
            op('STORE', None, node('const', 433, 8), node('register', 0x20, 8), node('const', return_address, 8))]


def indirect_caller(target=None, prefix=None, continuation=None):
    return function([
        instruction(0x100, (prefix or []) + push(0x105) +
                    [op('CALLIND', None, target or node('register', 0x38, 8))], 0x105),
        instruction(0x105, (continuation or []) + ret())])


class SharedMachineIndirectTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='shared-machine-indirect-', dir='/tmp')
        self.addCleanup(self.temp.cleanup)
        self.path = Path(self.temp.name)

    def generate(self, data, descriptor=None):
        return fixtures.PcodeLifterTest.generate(self, data, descriptor or profile())

    def execute(self, data, body, descriptor=None, import_method=''):
        return fixtures.PcodeLifterTest.execute(self, data, body, descriptor or profile(), import_method)

    def test_nested_register_and_unique_targets_share_guest_state_and_exact_continuation(self):
        caller = indirect_caller(prefix=[
            op('LOAD', node('register', 0x38, 8), node('const', 433, 8), node('const', 0x3000, 8)),
            op('COPY', node('register', 0x10, 8), node('const', 7, 8))], continuation=[
            op('INT_ADD', node('register', 0, 8), node('register', 0, 8), node('const', 1, 8))])
        # An operation following CALLIND in the same raw instruction must run.
        caller['instructions'][0]['pcode'].append(dict(
            op('COPY', node('register', 0x18, 8), node('const', 41, 8)), index=5))
        middle = function([
            instruction(0x200, [
                op('LOAD', node('unique', 0x80, 8), node('const', 433, 8), node('const', 0x3010, 8)),
                *push(0x205), op('CALLIND', None, node('unique', 0x80, 8)),
                op('INT_ADD', node('register', 0x10, 8), node('register', 0x10, 8), node('const', 3, 8))], 0x205),
            instruction(0x205, ret())])
        leaf = function([instruction(0x300, [
            op('COPY', node('register', 0, 8), node('const', 17, 8)),
            op('COPY', node('register', 0x38, 8), node('const', 0xdead, 8)),
            op('COPY', node('register', 0x200, 1), node('const', 1, 1)),
            op('STORE', None, node('const', 433, 8), node('const', 0x4000, 8), node('register', 0x10, 8)),
            *ret()])])
        self.execute([caller, middle, leaf], '''memory.write(0x3000,8,0x200);memory.write(0x3010,8,0x300);
torchlight::pcode::CallDepth depth(3);
torchlight::pcode_machine::fn_00000100(memory,registers,0xf00d,depth);
assert(depth.current()==0);assert(registers.read(0,8)==18);assert(registers.read(0x10,8)==10);
assert(registers.read(0x18,8)==41);assert(registers.read(0x38,8)==0xdead);
assert(registers.read(0x200,1)==1);assert(!registers.initialized(8,8));
assert(memory.read(0x4000,8)==7);assert(memory.read(0xff8,8)==0x105);assert(memory.read(0xff0,8)==0x205);
assert(registers.read(0x20,8)==0x1008);assert(registers.read(0x288,8)==0xf00d);''')
        header, report = self.generate([caller, middle, leaf])
        self.assertEqual(report['indirect_dispatch']['compiled_entries'], ['0x00000100', '0x00000200', '0x00000300'])
        self.assertEqual(report['closure']['maximum_selected_depth'], 1)
        indirect = [d for row in report['functions'] for d in row['approved_dependencies'] if d['kind'] == 'indirect_call']
        self.assertEqual(len(indirect), 2)
        self.assertTrue(all(d['target'] is None for d in indirect))
        self.assertNotIn('reinterpret_cast', header)
        self.assertNotIn('merge_initialized(machine)', header)

    def test_unknown_zero_interior_and_noncompiled_targets_preserve_prior_raw_push(self):
        caller = indirect_caller(prefix=[op('COPY', node('register', 0, 8), node('const', 7, 8))],
                                 continuation=[op('COPY', node('register', 0, 8), node('const', 10, 8))])
        leaf = function([instruction(0x200, [op('COPY', node('register', 0, 8), node('const', 9, 8)), *ret()])])
        self.execute([caller, leaf], '''torchlight::pcode::CallDepth depth(2);
for(std::uint64_t target : {UINT64_C(0),UINT64_C(0x201),UINT64_C(0x900),UINT64_MAX}) {
 registers.write(0x20,8,0x1000);registers.write(0x38,8,target);bool trapped=false;
 try{torchlight::pcode_machine::fn_00000100(memory,registers,0xf00d,depth);}
 catch(const torchlight::pcode::UntranslatedCallTarget& e){trapped=e.target==target;}
 assert(trapped);assert(depth.current()==0);assert(registers.read(0,8)==7);
 assert(registers.read(0x20,8)==0xff8);assert(memory.read(0xff8,8)==0x105);
 assert(!registers.initialized(0x288,8));
}''')

    def test_uninitialized_and_partial_target_bytes_trap_after_original_push(self):
        caller = indirect_caller()
        self.execute(caller, '''torchlight::pcode::CallDepth depth(1);
for(int partial=0;partial<2;++partial){
 torchlight::pcode::RegisterFile bank;bank.write(0x20,8,0x1000);
 if(partial){bank.write(0x38,4,0x100);}bool trapped=false;
 try{torchlight::pcode_machine::fn_00000100(memory,bank,0xf00d,depth);}
 catch(const std::runtime_error& e){trapped=std::string(e.what()).find("uninitialized register 0x38")!=std::string::npos;}
 assert(trapped);assert(depth.current()==0);assert(bank.read(0x20,8)==0xff8);
 assert(memory.read(0xff8,8)==0x105);assert(!bank.initialized(0x3c,4));
}''')

    def test_missing_or_wrong_guest_return_slot_is_not_repaired(self):
        leaf = function([instruction(0x200, ret())])
        for pushed in (False, True):
            ops = push(0x999) if pushed else []
            caller = function([instruction(0x100, [*ops, op('CALLIND', None, node('register', 0x38, 8))], 0x105),
                               instruction(0x105, ret())])
            with self.subTest(pushed=pushed):
                self.execute([caller, leaf], f'''registers.write(0x38,8,0x200);
torchlight::pcode::CallDepth depth(2);bool trapped=false;
try{{torchlight::pcode_machine::fn_00000100(memory,registers,0xf00d,depth);}}
catch(const std::runtime_error& e){{trapped=std::string(e.what()).find("sentinel")!=std::string::npos;}}
assert(trapped);assert(depth.current()==0);assert(registers.read(0x20,8)=={hex(0x1000 if pushed else 0x1008)});
assert(registers.read(0x288,8)=={hex(0x999 if pushed else 0xf00d)});''')

    def test_dynamic_recursion_budget_unwinds_and_retains_guest_effects(self):
        recursive = indirect_caller(prefix=[
            op('INT_ADD', node('register', 0, 8), node('register', 0, 8), node('const', 1, 8))])
        leaf = function([instruction(0x200, [op('COPY', node('register', 0, 8), node('const', 23, 8)), *ret()])])
        self.execute([recursive, leaf], '''registers.write(0,8,0);registers.write(0x38,8,0x100);
torchlight::pcode::CallDepth depth(3);bool trapped=false;
try{torchlight::pcode_machine::fn_00000100(memory,registers,0xf00d,depth);}
catch(const std::runtime_error& e){trapped=std::string(e.what()).find("adapter budget exceeded")!=std::string::npos;}
assert(trapped);assert(depth.current()==0);assert(depth.limit()==3);assert(registers.read(0,8)==3);
assert(registers.read(0x20,8)==0xfe8);assert(memory.read(0xfe8,8)==0x105);
assert(!registers.initialized(0x288,8));registers.write(0x20,8,0x1000);
torchlight::pcode_machine::fn_00000200(memory,registers,0xf00d,depth);
assert(depth.current()==0);assert(registers.read(0,8)==23);
registers.write(0x20,8,0x1000);registers.write(0,8,0);
trapped=false;try{torchlight::pcode_machine::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){trapped=std::string(e.what()).find("adapter budget exceeded")!=std::string::npos;}
assert(trapped);assert(registers.read(0,8)==2);assert(registers.read(0x20,8)==0xff0);''', profile(max_call_depth=2))
        _, report = self.generate([recursive, leaf], profile(max_call_depth=2))
        self.assertEqual(report['host_call_depth_budget']['default_limit'], 2)
        self.assertIn('not original guest semantics', report['host_call_depth_budget']['failure'])

    def test_direct_and_tail_entries_share_the_same_guard_before_callee_effects(self):
        leaf = function([instruction(0x200, [op('COPY', node('register', 0, 8), node('const', 99, 8)), *ret()])])
        for kind in ('CALL', 'BRANCH'):
            caller = (function([instruction(0x100, [*push(0x105), op('CALL', None, node('ram', 0x200, 8))], 0x105),
                                instruction(0x105, ret())]) if kind == 'CALL' else
                      function([instruction(0x100, [op('BRANCH', None, node('ram', 0x200, 8))])]))
            with self.subTest(kind=kind):
                self.execute([caller, leaf], f'''registers.write(0,8,7);torchlight::pcode::CallDepth depth(1);bool trapped=false;
try{{torchlight::pcode_machine::fn_00000100(memory,registers,0xf00d,depth);}}
catch(const std::runtime_error& e){{trapped=std::string(e.what()).find("adapter budget exceeded")!=std::string::npos;}}
assert(trapped);assert(depth.current()==0);assert(registers.read(0,8)==7);
assert(registers.read(0x20,8)=={hex(0xff8 if kind == 'CALL' else 0x1000)});''')

    def test_explicit_import_descriptor_does_not_allow_indirect_entry(self):
        direct = fixtures.PcodeLifterTest.imported_caller(self, address=0x400)
        method = '''void invoke_import(const torchlight::pcode::ImportCall&,
const torchlight::pcode::RegisterFile&,torchlight::pcode::RegisterFile&) override {
 throw std::runtime_error("import must not execute");
}'''
        descriptor = fixtures.PcodeLifterTest.imported_abi(self, direct, method)
        del descriptor['functions']
        descriptor['execution_mode'] = 'shared_machine'
        caller = indirect_caller()
        self.execute([caller, direct], '''registers.write(0x38,8,0x900);bool trapped=false;
try{torchlight::pcode_machine::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){trapped=std::string(e.what()).find("exact compiled raw entries")!=std::string::npos;}
assert(trapped);assert(registers.read(0x20,8)==0xff8);assert(!registers.initialized(0,8));''',
                     descriptor, '#include "import-method.hpp"')
        _, report = self.generate([caller, direct], descriptor)
        self.assertNotIn('0x00000900', report['indirect_dispatch']['compiled_entries'])

    def test_preflight_rejects_wrong_opcode_width_space_effect_fallthrough_and_byte_identity(self):
        valid = indirect_caller()
        cases = []
        for target in (node('const', 0x200, 8), node('ram', 0x200, 8), node('register', 0x38, 4)):
            cases.append((indirect_caller(target), 'pointer64'))
        for key, value, message in (('opcode', 7, 'opcode/index'), ('index', 7, 'opcode/index'),
                                    ('inputs', [], 'expected 1'), ('output', node('register', 0, 8), 'effect opcode')):
            data = copy.deepcopy(valid)
            data['instructions'][0]['pcode'][-1][key] = value
            cases.append((data, message))
        for fall in (None, '0x00000400'):
            data = copy.deepcopy(valid)
            data['instructions'][0]['fallthrough'] = fall
            cases.append((data, 'exact original return fallthrough'))
        missing_id = copy.deepcopy(valid)
        del missing_id['instructions'][0]['pcode'][-1]['inputs'][0]['space_id']
        cases.append((missing_id, 'space id'))
        for rawbytes in ('', 'nothex'):
            data = copy.deepcopy(valid)
            data['instructions'][0]['bytes'] = rawbytes
            cases.append((data, 'instruction bytes'))
        changed = copy.deepcopy(valid)
        changed['instructions'][0]['bytes'] = 'c3'
        cases.append((changed, 'SHA differs'))
        cases.append((indirect_caller(node('unique', 0x88, 8)), 'use before definition'))
        for data, message in cases:
            with self.subTest(message=message, data=data), self.assertRaisesRegex(lift.LiftError, message):
                self.generate(data)

    def test_profile_and_runtime_limits_are_bounded_and_scalar_indirect_stays_rejected(self):
        leaf = function([instruction(0x100, ret())])
        with self.assertRaisesRegex(lift.LiftError, 'zero cannot be'):
            self.generate(function([instruction(0, ret())]))
        for limit in (0, -1, 65, True, None, '2', 2.0):
            with self.subTest(limit=limit), self.assertRaisesRegex(lift.LiftError, 'max_call_depth'):
                self.generate(leaf, profile(max_call_depth=limit))
        scalar = fixtures.abi(leaf)
        scalar['max_call_depth'] = 2
        with self.assertRaisesRegex(lift.LiftError, 'only in shared_machine'):
            self.generate(leaf, scalar)
        caller = indirect_caller()
        with self.assertRaisesRegex(lift.LiftError, 'unsupported opcode'):
            self.generate(caller, fixtures.abi(caller))
        for operation in ('BRANCHIND', 'CALLOTHER'):
            data = function([instruction(0x100, [op(operation, None, node('register', 0x38, 8))])])
            with self.subTest(operation=operation), self.assertRaisesRegex(lift.LiftError, 'unsupported opcode'):
                self.generate(data)
        recursive = function([instruction(0x100, [op('CALL', None, node('ram', 0x100, 8))], 0x105),
                              instruction(0x105, ret())])
        with self.assertRaisesRegex(lift.LiftError, 'recursive direct-call'):
            self.generate(recursive)
        self.execute(leaf, '''for(std::size_t value : {std::size_t{0},std::size_t{65},SIZE_MAX}){
 bool trapped=false;try{torchlight::pcode::CallDepth depth(value);}
 catch(const std::runtime_error& e){trapped=std::string(e.what()).find("outside 1..64")!=std::string::npos;}
 assert(trapped);
}
torchlight::pcode::CallDepth depth(64);assert(depth.current()==0);assert(depth.limit()==64);
torchlight::pcode_machine::fn_00000100(memory,registers,0xf00d,depth);assert(depth.current()==0);''')

    def test_accepted_scalar_eleven_header_and_report_remain_byte_identical(self):
        directory = ROOT / 'research/lifted-ui'
        descriptor = json.loads((directory / 'abi.json').read_text())
        paths = [directory / (lift.address(a)[2:] + '.json') for a in descriptor['functions']]
        header, report = lift.generate(paths, descriptor)
        self.assertEqual(hashlib.sha256(header.encode()).hexdigest(),
                         'bf1321aa8853d132e7a8fe7373242c1c316c54c02e3fbdf5606f875eae95565f')
        self.assertEqual(hashlib.sha256(json.dumps(report, indent=2, sort_keys=True).encode()).hexdigest(),
                         '7a581ab3aeb4cea0b7c88175a20c2b2ef3e11820ae10ea5e4280de2124310853')
        shared, result = lift.generate(paths, profile(original_elf_sha256=descriptor['original_elf_sha256']))
        self.assertEqual(len(result['functions']), 11)
        self.assertEqual(shared.count('pcode::CallDepthGuard call_guard(call_depth);'), 11)
        self.assertEqual(result['host_call_depth_budget']['default_limit'], 64)
        self.assertEqual(result['original_status_promotions'], 0)


if __name__ == '__main__':
    unittest.main()
