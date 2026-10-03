#!/usr/bin/env python3
"""Shared guest-state lifting contracts; no ABI inference or game execution."""
import copy
import hashlib
import json
from pathlib import Path
import tempfile
import unittest

import pcode_lifter_test as fixtures

ROOT = fixtures.ROOT
lift = fixtures.lift
node, op, instruction, ret, function = (
    fixtures.node, fixtures.op, fixtures.instruction, fixtures.ret, fixtures.function)
SCALAR_11_HEADER_SHA = 'bf1321aa8853d132e7a8fe7373242c1c316c54c02e3fbdf5606f875eae95565f'
SCALAR_11_REPORT_SHA = '7a581ab3aeb4cea0b7c88175a20c2b2ef3e11820ae10ea5e4280de2124310853'


def shared_descriptor(sha=fixtures.SHA):
    return {'schema': 1, 'original_elf_sha256': sha, 'memory_space_id': 433,
            'execution_mode': 'shared_machine'}


class SharedMachineLifterTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='shared-machine-lifter-', dir='/tmp')
        self.addCleanup(self.temp.cleanup)
        self.path = Path(self.temp.name)

    def generate(self, data, descriptor=None):
        return fixtures.PcodeLifterTest.generate(self, data, descriptor or shared_descriptor())

    def execute(self, data, body, descriptor=None, import_method=''):
        body = body.replace('torchlight::pcode_generated::', 'torchlight::pcode_machine::')
        return fixtures.PcodeLifterTest.execute(self, data, body,
            descriptor or shared_descriptor(), import_method)

    def test_direct_call_shares_every_initialized_register_alias_flag_and_owner_effect(self):
        caller = function([
            instruction(0x100, [
                op('COPY', node('register', 0x18, 8), node('const', 17, 8)),
                op('COPY', node('register', 0x10, 8), node('const', 29, 8)),
                op('COPY', node('register', 0x200, 1), node('const', 1, 1)),
                op('INT_SUB', node('register', 0x20, 8), node('register', 0x20, 8), node('const', 8, 8)),
                op('STORE', None, node('const', 433, 8), node('register', 0x20, 8), node('const', 0x105, 8)),
                op('CALL', None, node('ram', 0x200, 8))], 0x105),
            instruction(0x105, [
                op('INT_ADD', node('register', 0x18, 8), node('register', 0x18, 8), node('register', 0x10, 8)),
                op('COPY', node('register', 1, 1), node('const', 0xa5, 1)), *ret()])])
        callee = function([instruction(0x200, [
            op('INT_ADD', node('register', 0x10, 8), node('register', 0x10, 8), node('const', 3, 8)),
            op('COPY', node('register', 0x200, 1), node('const', 0, 1)),
            op('STORE', None, node('const', 433, 8), node('register', 0x38, 8), node('register', 0x10, 8)),
            op('COPY', node('register', 0, 1), node('const', 0x5a, 1)), *ret()])])
        self.execute([caller, callee], '''registers.write(0x38,8,0x3000);
torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);
assert(registers.read(0x18,8)==49);assert(registers.read(0x10,8)==32);
assert(registers.read(0x200,1)==0);assert(registers.read(0,2)==0xa55a);
assert(!registers.initialized(2,6));assert(!registers.initialized(8,8));
assert(memory.read(0x3000,8)==32);assert(memory.read(0xff8,8)==0x105);
assert(registers.read(0x20,8)==0x1008);assert(registers.read(0x288,8)==0xf00d);''')
        header, report = self.generate([caller, callee])
        self.assertIn('auto& machine = registers;', header)
        self.assertNotIn('pcode::RegisterFile machine;', header)
        self.assertNotIn('merge_initialized(machine)', header)
        self.assertEqual(report['execution_mode'], 'shared_machine')
        self.assertEqual(report['closure']['maximum_selected_depth'], 2)
        self.assertTrue(all(r['abi'] is None and r['effective_return_register'] is None
                            for r in report['functions']))

    def test_undefined_guest_bytes_and_real_ret_slot_trap_without_fabricated_initialization(self):
        partial = function([instruction(0x100, [
            op('COPY', node('register', 0, 1), node('const', 7, 1)),
            op('COPY', node('register', 0x10, 8), node('register', 0, 8)), *ret()])])
        self.execute(partial, '''bool trapped=false;
try{torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){trapped=std::string(e.what()).find("uninitialized register 0x0")!=std::string::npos;}
assert(trapped);assert(registers.read(0,1)==7);assert(!registers.initialized(1,7));
assert(registers.read(0x20,8)==0x1000);assert(!registers.initialized(0x10,8));''')
        requires_stack = function([instruction(0x100, [
            op('COPY', node('register', 0, 1), node('const', 9, 1)), *ret()])])
        self.execute(requires_stack, '''torchlight::pcode::RegisterFile absent;
bool trapped=false;
try{torchlight::pcode_generated::fn_00000100(memory,absent,0xf00d);}
catch(const std::runtime_error& e){trapped=std::string(e.what()).find("uninitialized register 0x20")!=std::string::npos;}
assert(trapped);assert(absent.read(0,1)==9);assert(!absent.initialized(0x20,8));''')

    def test_call_without_original_stack_push_is_not_repaired(self):
        caller = function([instruction(0x100, [op('CALL', None, node('ram', 0x200, 8))], 0x105),
                           instruction(0x105, ret())])
        callee = function([instruction(0x200, ret())])
        self.execute([caller, callee], '''bool trapped=false;
try{torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){trapped=std::string(e.what()).find("sentinel")!=std::string::npos;}
assert(trapped);assert(registers.read(0x20,8)==0x1008);assert(registers.read(0x288,8)==0xf00d);''')

    def test_strict_closure_and_metadata_reject_unknown_indirect_recursive_or_individual_abi(self):
        leaf = function([instruction(0x100, ret())])
        for functions in ({}, fixtures.abi(leaf)['functions'], None):
            descriptor = shared_descriptor()
            descriptor['functions'] = functions
            with self.subTest(functions=functions), self.assertRaisesRegex(lift.LiftError, 'individual|functions'):
                self.generate(leaf, descriptor)
        for mode in ('guess_abi', 1, None):
            descriptor = shared_descriptor()
            descriptor['execution_mode'] = mode
            with self.subTest(mode=mode), self.assertRaisesRegex(lift.LiftError, 'execution_mode'):
                self.generate(leaf, descriptor)
        missing = function([instruction(0x100, [op('CALL', None, node('ram', 0x200, 8))], 0x105),
                            instruction(0x105, ret())])
        with self.assertRaisesRegex(lift.LiftError, 'outside approved'):
            self.generate(missing)
        recursive = function([instruction(0x100, [op('CALL', None, node('ram', 0x100, 8))], 0x105),
                              instruction(0x105, ret())])
        with self.assertRaisesRegex(lift.LiftError, 'recursive'):
            self.generate(recursive)
        for operation in ('CALLOTHER', 'BRANCHIND'):
            data = function([instruction(0x100, [op(operation, None, node('register', 0x38, 8))])])
            with self.subTest(operation=operation), self.assertRaisesRegex(lift.LiftError, 'unsupported opcode'):
                self.generate(data)
        altered = copy.deepcopy(leaf)
        altered['instructions'][0]['bytes'] = 'c3'
        with self.assertRaisesRegex(lift.LiftError, 'SHA differs'):
            self.generate(altered)

    def test_reviewed_imports_keep_exact_banks_and_clobbers_in_shared_state(self):
        caller = fixtures.PcodeLifterTest.imported_caller(self)
        method = '''void invoke_import(const torchlight::pcode::ImportCall&,
const torchlight::pcode::RegisterFile& in,torchlight::pcode::RegisterFile& out) override {
assert(in.read(0x30,4)==7);write(0x5000,4,7);out.write(0,8,2);
}'''
        descriptor = fixtures.PcodeLifterTest.imported_abi(self, caller, method)
        del descriptor['functions']
        descriptor['execution_mode'] = 'shared_machine'
        self.execute(caller, '''torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);
assert(registers.read(0,8)==42);assert(memory.read(0x5000,4)==7);
assert(registers.read(0x18,8)==40);assert(!registers.initialized(0x10,8));
assert(registers.read(0x20,8)==0x1008);''', descriptor, '#include "import-method.hpp"')

    def test_source_symbols_are_single_line_navigation_comments_only_in_new_mode(self):
        leaf = function([instruction(0x100, ret())])
        leaf['symbol'] = 'CExample::method()\n#error unsafe\r\x00\\'
        header, _ = self.generate(leaf)
        self.assertEqual(sum('Source symbol' in line for line in header.splitlines()), 1)
        self.assertNotIn('\n#error', header)
        self.assertNotIn('\x00', header)
        self.assertTrue(all(not line.endswith('\\') for line in header.splitlines()))
        scalar, _ = self.generate(leaf, fixtures.abi(leaf, returns='void'))
        self.assertNotIn('Source symbol', scalar)

    def test_accepted_eleven_bodies_generate_without_individual_abi_and_scalar_bytes_unchanged(self):
        directory = ROOT / 'research/lifted-ui'
        descriptor = json.loads((directory / 'abi.json').read_text())
        paths = [directory / (lift.address(a)[2:] + '.json') for a in descriptor['functions']]
        self.assertEqual(len(paths), 11)
        header, report = lift.generate(paths, descriptor)
        self.assertEqual(hashlib.sha256(header.encode()).hexdigest(), SCALAR_11_HEADER_SHA)
        self.assertEqual(hashlib.sha256(json.dumps(report, indent=2, sort_keys=True).encode()).hexdigest(),
                         SCALAR_11_REPORT_SHA)
        shared, result = lift.generate(paths, shared_descriptor(descriptor['original_elf_sha256']))
        self.assertEqual(len(result['functions']), 11)
        self.assertEqual(shared.count('auto& machine = registers;'), 11)
        self.assertNotIn('missing reviewed ABI input', shared)
        self.assertNotIn('merge_initialized(machine)', shared)
        self.assertFalse(any(r['unresolved_dependencies'] for r in result['functions']))
        # Execute unchanged accepted default/GetInt source through the shared
        # entry API. The host's initialized memory/register owner is explicit.
        data = [json.loads(p.read_text()) for p in paths]
        self.execute(data, '''torchlight::pcode_generated::fn_00b05e80(memory,registers,0xf00d);
assert(registers.read(0,1)==1);assert(registers.read(0x20,8)==0x1008);
memory.write(0x3040,8,0x4000);memory.write(0x3048,8,0x4004);memory.write(0x4000,4,0x80000000);
registers.write(0x38,8,0x3000);registers.write(0x30,4,0);registers.write(0x20,8,0x1000);
torchlight::pcode_generated::fn_00c6e440(memory,registers,0xf00d);
assert(registers.read(0,4)==0x80000000);assert(registers.read(0x20,8)==0x1008);''',
            shared_descriptor(descriptor['original_elf_sha256']))


if __name__ == '__main__':
    unittest.main()
