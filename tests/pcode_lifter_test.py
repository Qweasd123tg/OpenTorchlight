#!/usr/bin/env python3
"""Compiler/runtime semantics and fail-closed tests; synthetic raw fixtures only.

Original-source differential comparison is a separate production test. These
fixtures exercise aliasing, instruction-local temporaries, checked ABI and
control transfers, without claiming an original function is fully closed.
"""
import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('lift_pcode',ROOT/'tools/lift_pcode.py')
lift=importlib.util.module_from_spec(spec);spec.loader.exec_module(lift)
SHA='1'*64


def node(space,offset,size):
    return dict(space=space,space_id={'const':48,'register':548,'unique':291,'ram':433}[space],
                offset=hex(offset),size=size,constant=space=='const',register=None)


def op(name,out,*inputs):
    return dict(operation=name,opcode=lift.OPCODES.get(name,7),output=out,inputs=list(inputs))


def instruction(addr,ops,fall=None):
    return dict(address=f'0x{addr:08x}',bytes='90',fallthrough=None if fall is None else f'0x{fall:08x}',
                pcode=[dict(o,index=i) for i,o in enumerate(ops)])


def ret():
    return [op('LOAD',node('register',0x288,8),node('const',433,8),node('register',0x20,8)),
            op('INT_ADD',node('register',0x20,8),node('register',0x20,8),node('const',8,8)),
            op('RETURN',None,node('register',0x288,8))]


def function(rows):
    sha=hashlib.sha256()
    for i in rows: sha.update(i['address'].encode());sha.update(bytes.fromhex(i['bytes']))
    return dict(schema=2,address=rows[0]['address'],original_elf_sha256=SHA,
                address_and_instruction_bytes_sha256=sha.hexdigest(),instructions=rows)


def abi(data,inputs=(),returns='uint64'):
    return {
                    'schema':1,'original_elf_sha256':SHA,'memory_space_id':433,
                    'functions':{data['address']:{'return':returns,'input_registers':
                       [dict(offset='0x20',size=8)]+[dict(offset=hex(o),size=s) for o,s in inputs]}}}


def closure_abi(*descriptors):
    result=dict(descriptors[0],functions={})
    for descriptor in descriptors:result['functions'].update(descriptor['functions'])
    return result


class PcodeLifterTest(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory(prefix='pcode-lifter-',dir='/tmp')
        self.path=Path(self.temp.name)

    def tearDown(self):
        self.temp.cleanup()

    def generate(self,data,descriptor=None):
        functions=data if isinstance(data,list) else [data]
        paths=[]
        for i,function in enumerate(functions):
            p=self.path/f'raw{i}.json';p.write_text(json.dumps(function));paths.append(p)
        return lift.generate(paths,descriptor or closure_abi(*(abi(d) for d in functions)))

    def execute(self,data,body,descriptor=None,import_method=''):
        compiler=shutil.which('g++') or shutil.which('clang++')
        if not compiler:self.skipTest('C++17 compiler unavailable')
        header,_=self.generate(data,descriptor)
        (self.path/'generated.hpp').write_text(header)
        source='''#include "generated.hpp"
#include <cassert>
#include <map>
struct Memory : torchlight::pcode::Memory {
 std::map<std::uint64_t,std::uint8_t> bytes;
 std::size_t reads=0;
 std::uint64_t read(std::uint64_t a,std::size_t w) override {
  ++reads; std::uint64_t v=0;for(std::size_t i=0;i<w;++i)v|=std::uint64_t{bytes.at(a+i)}<<(i*8);return v;
 }
 void write(std::uint64_t a,std::size_t w,std::uint64_t v) override {
  for(std::size_t i=0;i<w;++i)bytes[a+i]=static_cast<std::uint8_t>(v>>(i*8));
 }
'''+import_method+'''
};
int main(){Memory memory; memory.write(0x1000,8,0xf00d);
 torchlight::pcode::RegisterFile registers; registers.write(0x20,8,0x1000);
'''+body+'\n}\n'
        (self.path/'test.cpp').write_text(source)
        result=subprocess.run([compiler,'-std=c++17','-O2','-Wall','-Wextra','-Werror','-pedantic',
             '-fsanitize=undefined','-fsanitize-undefined-trap-on-error','-I',str(ROOT/'include'),
             str(self.path/'test.cpp'),'-o',str(self.path/'run')],text=True,capture_output=True)
        self.assertEqual(result.returncode,0,result.stderr)
        result=subprocess.run([str(self.path/'run')],text=True,capture_output=True)
        self.assertEqual(result.returncode,0,result.stderr)

    def test_register_byte_aliases_and_real_ret(self):
        data=function([instruction(0x100,[op('COPY',node('register',0,8),node('const',0x1122334455667788,8)),
             op('COPY',node('register',0,1),node('const',0xaa,1)),
             op('COPY',node('register',1,1),node('const',0xbb,1))]+ret())])
        self.execute(data,'''auto value=torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);
assert(value==0x112233445566bbaaULL);assert(registers.read(0,4)==0x5566bbaa);
assert(registers.read(0x20,8)==0x1008);assert(registers.read(0x288,8)==0xf00d);assert(memory.reads==1);''')

    def test_alias_zext_and_masked_constant(self):
        data=function([instruction(0x100,[op('COPY',node('register',0,8),node('const',0xffffffffffffffff,8)),
              op('COPY',node('register',0,4),node('const',0x123456789,4)),
              op('INT_ZEXT',node('register',0,8),node('register',0,4))]+ret())])
        self.execute(data,'assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==0x23456789);')

    def test_register_self_xor_defines_eax_before_source_zero_extension(self):
        row=instruction(0x100,[op('INT_XOR',node('register',0,4),
            node('register',0,4),node('register',0,4)),
            op('INT_ZEXT',node('register',0,8),node('register',0,4))],0x102)
        row['bytes']='31c0'  # x86 xor EAX,EAX; raw source also defines high RAX.
        end=instruction(0x102,ret());end['bytes']='c3'
        data=function([row,end])
        self.execute(data,'''assert(!registers.initialized(0,8));
assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==0);
assert(registers.initialized(0,8));assert(registers.read(0,8)==0);
assert(registers.read(0x20,8)==0x1008);assert(memory.reads==1);''')

    def test_register_xor_different_missing_inputs_still_rejected(self):
        data=function([instruction(0x100,[op('INT_XOR',node('register',0,4),
            node('register',0,4),node('register',8,4)),
            op('INT_ZEXT',node('register',0,8),node('register',0,4))]+ret())])
        self.execute(data,'''bool rejected=false;
try{torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){rejected=std::string(e.what()).find("pcode[0] INT_XOR")!=std::string::npos;}
assert(rejected);assert(!registers.initialized(0,8));''')

    def test_register_self_other_operations_keep_missing_input_check(self):
        for name in ('COPY','INT_SUB'):
            inputs=[node('register',0,8)]*(1 if name=='COPY' else 2)
            data=function([instruction(0x100,[op(name,node('register',0,8),*inputs)]+ret())])
            with self.subTest(operation=name):
                self.execute(data,'''bool rejected=false;
try{torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error&){rejected=true;}assert(rejected);''')

    def test_same_ram_and_unique_xor_are_not_register_zero_idioms(self):
        data=function([instruction(0x100,[op('INT_XOR',node('register',0,8),
            node('ram',0x2000,8),node('ram',0x2000,8))]+ret())])
        self.execute(data,'''memory.write(0x2000,8,0x123456789abcdef0ULL);
assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==0);
assert(memory.reads==3);''')
        data=function([instruction(0x100,[op('INT_XOR',node('register',0,8),
            node('unique',0,8),node('unique',0,8))]+ret())])
        with self.assertRaisesRegex(lift.LiftError,'use before definition'):self.generate(data)

    def test_reviewed_al_return_does_not_leak_pointer_high_bytes(self):
        data=function([instruction(0x100,[op('COPY',node('register',0,8),node('const',0x100000,8)),
              op('COPY',node('register',0,1),node('const',0,1))]+ret())])
        descriptor=abi(data)
        descriptor['functions'][data['address']]['return_register']=dict(offset='0x0',size=1)
        self.execute(data,'''assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==0);
assert(registers.read(0,8)==0x100000);''',descriptor)

    def test_unique_alias_piece_subpiece_and_signed_extension(self):
        data=function([instruction(0x100,[
             op('COPY',node('unique',0x100,8),node('const',0x1122334455667788,8)),
             op('COPY',node('unique',0x101,1),node('const',0xaa,1)),
             op('SUBPIECE',node('unique',0x200,2),node('unique',0x100,8),node('const',0,4)),
             op('PIECE',node('unique',0x300,4),node('const',0x1234,2),node('unique',0x200,2)),
             op('INT_SEXT',node('register',0,8),node('const',0x80,1)),
             op('INT_ZEXT',node('unique',0x400,8),node('unique',0x300,4)),
             op('INT_ADD',node('register',0,8),node('register',0,8),node('unique',0x400,8))]+ret())])
        self.execute(data,'assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==0x1234aa08);')

    def test_scalar_overflow_signed_boundaries_and_large_shifts(self):
        data=function([instruction(0x100,[
             op('INT_ADD',node('register',0,1),node('const',255,1),node('const',1,1)),
             op('INT_ZEXT',node('register',0,8),node('register',0,1)),
             op('INT_LEFT',node('unique',0x100,8),node('const',1,8),node('const',64,8)),
             op('INT_RIGHT',node('unique',0x200,8),node('const',1,8),node('const',255,8)),
             op('INT_SRIGHT',node('unique',0x300,8),node('const',1<<63,8),node('const',255,8)),
             op('INT_SCARRY',node('unique',0x400,1),node('const',127,1),node('const',1,1)),
             op('INT_SBORROW',node('unique',0x500,1),node('const',128,1),node('const',1,1)),
             op('INT_CARRY',node('unique',0x600,1),node('const',255,1),node('const',1,1)),
             op('INT_SLESS',node('unique',0x700,1),node('const',128,1),node('const',127,1)),
             op('INT_ADD',node('register',0,8),node('register',0,8),node('unique',0x100,8)),
             op('INT_ADD',node('register',0,8),node('register',0,8),node('unique',0x200,8)),
             op('INT_ADD',node('register',0,8),node('register',0,8),node('unique',0x300,8)),
             *[op('INT_ZEXT',node('unique',o+8,8),node('unique',o,1)) for o in [0x400,0x500,0x600,0x700]],
             *[op('INT_ADD',node('register',0,8),node('register',0,8),node('unique',o+8,8)) for o in [0x400,0x500,0x600,0x700]],
             ]+ret())])
        self.execute(data,'assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==3);')

    def test_internal_relative_target_and_address_branch(self):
        data=function([instruction(0x100,[
            op('COPY',node('register',0,8),node('const',1,8)),
            op('CBRANCH',None,node('const',2,4),node('const',1,1)),
            op('COPY',node('register',0,8),node('const',99,8)),
            op('INT_ADD',node('register',0,8),node('register',0,8),node('const',3,8)),
            op('BRANCH',None,node('ram',0x200,8))]),
            instruction(0x150,[op('COPY',node('register',0,8),node('const',999,8))],0x200),
            instruction(0x200,ret())])
        self.execute(data,'assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==4);')

    def test_static_ram_internal_branches_require_eight_byte_targets(self):
        for name in ('BRANCH','CBRANCH'):
            for width in (1,2,4):
                inputs=[node('ram',0x200,width)]
                if name=='CBRANCH':inputs.append(node('const',1,1))
                data=function([instruction(0x100,[op(name,None,*inputs)],
                                           0x200 if name=='CBRANCH' else None),
                               instruction(0x200,ret())])
                with self.subTest(operation=name,width=width),self.assertRaisesRegex(
                        lift.LiftError,'static RAM branch target width must be 8'):
                    self.generate(data)

    def test_eight_byte_internal_branches_keep_taken_and_fallthrough_paths(self):
        for name,condition,expected in (('BRANCH',None,9),('CBRANCH',0,4),('CBRANCH',1,9)):
            inputs=[node('ram',0x200,8)]
            if name=='CBRANCH':inputs.append(node('const',condition,1))
            data=function([instruction(0x100,[op(name,None,*inputs)],
                                       0x150 if name=='CBRANCH' else None),
                           instruction(0x150,[op('COPY',node('register',0,8),node('const',4,8)),
                                              op('BRANCH',None,node('ram',0x300,8))]),
                           instruction(0x200,[op('COPY',node('register',0,8),node('const',9,8))],0x300),
                           instruction(0x300,ret())])
            with self.subTest(operation=name,condition=condition):
                self.execute(data,f'assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)=={expected});')

    def test_temporaries_reset_at_instruction_boundary(self):
        data=function([instruction(0x100,[op('COPY',node('unique',0x100,8),node('const',99,8))],0x101),
                       instruction(0x101,[op('COPY',node('register',0,8),node('unique',0x100,8))]+ret())])
        with self.assertRaisesRegex(lift.LiftError,'0x00000101 pcode\\[0\\].*use before definition'):
            self.generate(data)

    def test_path_dependent_unique_is_checked_on_executed_read(self):
        data=function([instruction(0x100,[
             op('CBRANCH',None,node('const',2,4),node('const',1,1)),
             op('COPY',node('unique',0x100,8),node('const',99,8)),
             op('COPY',node('register',0,8),node('unique',0x100,8))]+ret())])
        self.execute(data,'''bool failed=false;try{torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){failed=std::string(e.what()).find("0x00000100 pcode[2]")!=std::string::npos;}assert(failed);''')

    def test_unreviewed_register_is_not_silently_initialized(self):
        data=function([instruction(0x100,[op('COPY',node('register',0,8),node('register',0x38,8))]+ret())])
        self.execute(data,'''registers.write(0x38,8,42);bool failed=false;
try{torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}catch(const std::runtime_error&){failed=true;}assert(failed);''')
        self.execute(data,'''registers.write(0x38,8,42);
assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==42);''',abi(data,[(0x38,8)]))

    def test_missing_required_input_and_invalid_return_sentinel(self):
        data=function([instruction(0x100,[op('COPY',node('register',0,8),node('const',1,8))]+ret())])
        self.execute(data,'''bool failed=false;try{torchlight::pcode_generated::fn_00000100(memory,registers,0xbad);}
catch(const std::runtime_error&){failed=true;}assert(failed);''')
        descriptor=abi(data,[(0x38,8)])
        self.execute(data,'''bool failed=false;try{torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error&){failed=true;}assert(failed);''',descriptor)

    def test_float_nan_comparison_and_memory_read_order(self):
        data=function([instruction(0x100,[
             op('FLOAT_NAN',node('unique',0,1),node('ram',0x2000,4)),
             op('FLOAT_EQUAL',node('unique',1,1),node('ram',0x2000,4),node('const',0,4)),
             op('FLOAT_NOTEQUAL',node('unique',2,1),node('ram',0x2000,4),node('const',0,4)),
             op('INT_ZEXT',node('register',0,8),node('unique',0,1)),
             op('INT_ZEXT',node('unique',0x100,8),node('unique',1,1)),
             op('INT_ZEXT',node('unique',0x200,8),node('unique',2,1)),
             op('INT_ADD',node('register',0,8),node('register',0,8),node('unique',0x100,8)),
             op('INT_ADD',node('register',0,8),node('register',0,8),node('unique',0x200,8))]+ret())])
        self.execute(data,'''memory.write(0x2000,4,0x7fc00000);
assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==2);assert(memory.reads==4);''')

    def test_float_multiply_rounding_edges_and_raw_operands(self):
        # The generated opcode reads two initialized integer bit patterns, and
        # returns precision-rounded float bits rather than converting the value.
        for width,cases in ((4,[
            (0x3f800001,0x3f800001,0x3f800002),
            (0x7f7fffff,0x40000000,0x7f800000),
            (0x00800000,0x3f000000,0x00400000),
            (0x00000001,0x3f000000,0x00000000),
            (0x00000001,0x3fc00000,0x00000002),
            (0x80000000,0x40000000,0x80000000),
            (0x7f800000,0xbf800000,0xff800000),
            (0xbf000000,0x40400000,0xbfc00000),
        ]),(8,[
            (0x3ff0000000000001,0x3ff0000000000001,0x3ff0000000000002),
            (0x7fefffffffffffff,0x4000000000000000,0x7ff0000000000000),
            (0x0010000000000000,0x3fe0000000000000,0x0008000000000000),
            (1,0x3fe0000000000000,0),
            (1,0x3ff8000000000000,2),
            (0x8000000000000000,0x4000000000000000,0x8000000000000000),
            (0x7ff0000000000000,0xbff0000000000000,0xfff0000000000000),
            (0xbfe0000000000000,0x4008000000000000,0xbff8000000000000),
        ])):
            row=instruction(0x100,[op('FLOAT_MULT',node('register',0,width),
                node('register',0x30,width),node('register',0x38,width))]+ret())
            row['bytes']='f30f59c1' if width==4 else 'f20f59c1'
            data=function([row])
            checks=''
            for left,right,expected in cases:
                checks+=f'''registers.write(0x20,8,0x1000);
registers.write(0x30,{width},UINT64_C({left}));registers.write(0x38,{width},UINT64_C({right}));
assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==UINT64_C({expected}));\n'''
            nan,one,inf=(0x7fc12345,0x3f800000,0x7f800000) if width==4 else (0x7ff8123456789abc,0x3ff0000000000000,0x7ff0000000000000)
            # Result classification remains useful beside exact payload tests.
            for left,right in [(nan,one),(one,nan),(inf,0),(nan,nan+1)]:
                checks+=f'''registers.write(0x20,8,0x1000);
registers.write(0x30,{width},UINT64_C({left}));registers.write(0x38,{width},UINT64_C({right}));
assert(std::isnan(torchlight::pcode::floating(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d),{width})));\n'''
            descriptor=abi(data,[(0x30,width),(0x38,width)])
            descriptor['functions'][data['address']]['return_register']=dict(offset='0x0',size=width)
            with self.subTest(width=width):
                self.execute(data,checks,descriptor)
                _,report=self.generate(data,descriptor)
                self.assertEqual(report['functions'][0]['opcode_inventory']['FLOAT_MULT'],1)

    def test_scalar_sse_multiply_nan_payload_order_and_indefinite(self):
        for width,one,inf,quiet_a,quiet_b,signaling_a,signaling_b,quiet_bit,indefinite in [
            (4,0x3f800000,0x7f800000,0x7fc12345,0xffc23456,
             0x7f800001,0xff800123,0x00400000,0xffc00000),
            (8,0x3ff0000000000000,0x7ff0000000000000,
             0x7ff8123456789abc,0xfff83456789abcde,
             0x7ff0000000000001,0xfff0000000000123,
             0x0008000000000000,0xfff8000000000000),
        ]:
            row=instruction(0x100,[op('FLOAT_MULT',node('register',0,width),
                node('register',0x30,width),node('register',0x38,width))]+ret())
            row['bytes']='f30f59c1' if width==4 else 'f20f59c1'
            data=function([row])
            descriptor=abi(data,[(0x30,width),(0x38,width)])
            descriptor['functions'][data['address']]['return_register']=dict(offset='0x0',size=width)
            nan_cases=[(left,right,left | quiet_bit)
                for left in (quiet_a,quiet_b,signaling_a,signaling_b)
                for right in (quiet_a,quiet_b,signaling_a,signaling_b)]
            nan_cases += [(one,nan,nan | quiet_bit) for nan in (quiet_a,quiet_b,signaling_a,signaling_b)]
            sign=1 << (width*8-1)
            nan_cases += [(a,b,indefinite) for a,b in
                [(inf,0),(inf,sign),(inf | sign,0),(inf | sign,sign),
                 (0,inf),(sign,inf),(0,inf | sign),(sign,inf | sign)]]
            checks=''
            for left,right,expected in nan_cases:
                checks+=f'''registers.write(0x20,8,0x1000);
registers.write(0x30,{width},UINT64_C({left}));registers.write(0x38,{width},UINT64_C({right}));
assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==UINT64_C({expected}));\n'''
            with self.subTest(width=width):self.execute(data,checks,descriptor)

    def test_float_multiply_rejects_non_scalar_sse_instruction(self):
        for width,raw in [(4,'90'),(4,'d8c9'),(4,'0f59c1'),(4,'f20f59c1'),
                          (8,'f30f59c1'),(8,'f20f')]:
            row=instruction(0x100,[op('FLOAT_MULT',node('register',0,width),
                node('const',0,width),node('const',0,width))]+ret())
            row['bytes']=raw
            with self.subTest(width=width,raw=raw),self.assertRaisesRegex(lift.LiftError,'scalar SSE'):
                self.generate(function([row]))

    def test_rejects_float_multiply_widths(self):
        for left,right,out in [(1,1,1),(2,2,2),(3,3,3),(5,5,5),(6,6,6),(7,7,7),
                               (4,8,4),(4,4,8),(8,8,4),(16,16,16)]:
            data=function([instruction(0x100,[op('FLOAT_MULT',node('register',0,out),
                node('const',0,left),node('const',0,right))]+ret())])
            with self.subTest(widths=(left,right,out)),self.assertRaisesRegex(lift.LiftError,'width'):
                self.generate(data)

    def test_float_runtime_width_and_fast_math_fail_closed(self):
        data=function([instruction(0x100,ret())])
        self.execute(data,'''for (auto width : {1u,2u,3u,5u,6u,7u,9u}) {
bool rejected=false;try{torchlight::pcode::float_multiply(0,0,width);}
catch(const std::runtime_error&){rejected=true;}assert(rejected);}
''')
        compiler=shutil.which('g++') or shutil.which('clang++')
        result=subprocess.run([compiler,'-std=c++17','-ffast-math','-I',str(ROOT/'include'),
            '-x','c++','-fsyntax-only','-'],input='#include "torchlight/pcode_runtime.hpp"\n',text=True,capture_output=True)
        self.assertNotEqual(result.returncode,0)
        self.assertIn('disable fast-math',result.stderr)

    def test_rejects_unsupported_calls_external_targets_spaces_and_widths(self):
        base=function([instruction(0x100,[op('COPY',node('register',0,8),node('const',1,8))]+ret())])
        cases=[]
        d=copy.deepcopy(base);d['instructions'][0]['pcode'][0]=dict(op('CALL',None,node('ram',0x900,8)),index=0);cases.append((d,'unresolved dependency'))
        d=copy.deepcopy(base);d['instructions'][0]['pcode'][0]=dict(op('BRANCH',None,node('ram',0x900,8)),index=0);cases.append((d,'branch leaves approved function'))
        d=copy.deepcopy(base);d['instructions'][0]['pcode'][0]['inputs'][0]['size']=16;cases.append((d,'unsupported varnode width'))
        d=copy.deepcopy(base);d['instructions'][0]['pcode'][0]['inputs'][0]['space']='bogus';cases.append((d,'unsupported varnode space'))
        d=copy.deepcopy(base);d['instructions'][0]['pcode'][1]['inputs'][0]['offset']='0xdead';cases.append((d,'not reviewed RAM id'))
        d=copy.deepcopy(base);d['instructions'][0]['pcode'][0]['opcode']=999;cases.append((d,'opcode/index disagrees'))
        d=copy.deepcopy(base);d['address_and_instruction_bytes_sha256']='0'*64;cases.append((d,'instruction byte SHA differs'))
        for data,error in cases:
            with self.subTest(error=error),self.assertRaisesRegex(lift.LiftError,error):self.generate(data)

    def test_rejected_cli_never_publishes_partial_header(self):
        data=function([instruction(0x100,[op('CALL',None,node('ram',0x900,8))]+ret())])
        p=self.path/'raw.json';p.write_text(json.dumps(data))
        ap=self.path/'abi.json';ap.write_text(json.dumps(abi(data)))
        out=self.path/'generated.hpp';out.write_text('previous valid output\n')
        report=self.path/'report.json'
        result=subprocess.run(['python3',str(ROOT/'tools/lift_pcode.py'),str(p),'--abi',str(ap),
             '--out',str(out),'--report',str(report)],capture_output=True,text=True)
        self.assertEqual(result.returncode,2)
        self.assertEqual(out.read_text(),'previous valid output\n')
        self.assertEqual(json.loads(report.read_text())['status'],'rejected')

    def test_cli_cannot_overwrite_original_source_inputs(self):
        data=function([instruction(0x100,ret())])
        p=self.path/'raw.json';p.write_text(json.dumps(data));original=p.read_bytes()
        ap=self.path/'abi.json';ap.write_text(json.dumps(abi(data,returns='void')))
        for out,report in [(p,self.path/'report.json'),(self.path/'header.hpp',p)]:
            result=subprocess.run(['python3',str(ROOT/'tools/lift_pcode.py'),str(p),'--abi',str(ap),
                 '--out',str(out),'--report',str(report)],capture_output=True,text=True)
            self.assertEqual(result.returncode,2)
            self.assertEqual(p.read_bytes(),original)

    def test_deterministic_output_and_precise_inventory(self):
        data=function([instruction(0x100,[op('COPY',node('register',0,8),node('const',1,8))]+ret())])
        first=self.generate(data);second=self.generate(data)
        self.assertEqual(first,second)
        self.assertEqual(first[1]['functions'][0]['opcode_inventory'],{'COPY':1,'INT_ADD':1,'LOAD':1,'RETURN':1})
        self.assertEqual(first[1]['functions'][0]['unresolved_dependencies'],[])
        self.assertIn('input_sha256',first[1]['functions'][0])

    def test_direct_call_raw_stack_effects_and_preserved_caller_register(self):
        caller=function([instruction(0x100,[
            op('COPY',node('register',0x18,8),node('const',40,8)),
            op('INT_SUB',node('register',0x20,8),node('register',0x20,8),node('const',8,8)),
            op('STORE',None,node('const',433,8),node('register',0x20,8),node('const',0x105,8)),
            op('CALL',None,node('ram',0x200,8)),
            # This raw effect after CALL must still consume the real callee state.
            op('INT_ADD',node('register',0,8),node('register',0,8),node('register',0x18,8))],0x105),
            instruction(0x105,ret())])
        callee=function([instruction(0x200,[op('COPY',node('register',0,8),node('const',2,8))]+ret())])
        self.execute([caller,callee],'''registers.write(0x30,8,0x9876);
assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==42);
assert(registers.read(0x20,8)==0x1008);assert(registers.read(0x18,8)==40);
assert(registers.read(0x30,8)==0x9876);assert(memory.read(0xff8,8)==0x105);''')
        _,report=self.generate([caller,callee])
        self.assertEqual(report['closure']['maximum_selected_depth'],2)
        self.assertEqual(report['functions'][0]['approved_dependencies'],[
            dict(kind='direct_call',instruction='0x00000100',pcode_index=3,target='0x00000200',return_address='0x00000105')])

    def test_direct_call_does_not_invent_missing_raw_stack_push(self):
        caller=function([instruction(0x100,[op('CALL',None,node('ram',0x200,8))],0x105),instruction(0x105,ret())])
        callee=function([instruction(0x200,ret())])
        self.execute([caller,callee],'''bool failed=false;
try{torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){failed=std::string(e.what()).find("sentinel")!=std::string::npos;}assert(failed);''',
                     closure_abi(abi(caller,returns='void'),abi(callee,returns='void')))

    def imported_caller(self,address=0x100,push=True):
        rows=[op('COPY',node('register',0x38,8),node('const',0x5000,8)),
              op('COPY',node('register',0x30,4),node('const',7,4)),
              op('COPY',node('register',0x18,8),node('const',40,8)),
              op('COPY',node('register',0x10,8),node('const',123,8))]
        if push:
            rows += [op('INT_SUB',node('register',0x20,8),node('register',0x20,8),node('const',8,8)),
                     op('STORE',None,node('const',433,8),node('register',0x20,8),node('const',address+5,8))]
        rows += [op('CALL',None,node('ram',0x900,8)),
                 op('INT_ADD',node('register',0,8),node('register',0,8),node('register',0x18,8))]
        return function([instruction(address,rows,address+5),instruction(address+5,ret())])

    def imported_abi(self,caller,method,inputs=((0x38,8),(0x30,4)),outputs=((0,8),),clobbers=((0x10,8),)):
        implementation=self.path/'import-method.hpp'
        implementation.write_text(method)
        descriptor=abi(caller)
        site=next((row['address'],op['index']) for row in caller['instructions']
                  for op in row['pcode'] if op['operation']=='CALL')
        descriptor['imports']={'0x900':{
            'input_registers':[dict(offset=hex(offset),size=size) for offset,size in inputs],
            'output_registers':[dict(offset=hex(offset),size=size) for offset,size in outputs],
            'clobber_registers':[dict(offset=hex(offset),size=size) for offset,size in clobbers],
            'callsites':[dict(caller=caller['address'],instruction=site[0],pcode_index=site[1],kind='direct_call')],
            'implementation_inputs':{str(implementation):hashlib.sha256(implementation.read_bytes()).hexdigest()}}}
        return descriptor

    def test_reviewed_direct_import_exact_banks_effects_ret_and_clobber_propagation(self):
        caller=self.imported_caller()
        method='''std::size_t calls=0;
void invoke_import(const torchlight::pcode::ImportCall& call,
 const torchlight::pcode::RegisterFile& in,torchlight::pcode::RegisterFile& out) override {
 ++calls;assert(call.caller==0x100&&call.instruction==0x100&&call.pcode_index==6&&call.target==0x900);
 assert(in.initialized_count()==12);assert(in.read(0x38,8)==0x5000);assert(in.read(0x30,4)==7);
 bool denied=false;try{(void)in.read(0x18,8);}catch(const std::runtime_error&){denied=true;}assert(denied);
 write(0x5000,4,in.read(0x30,4));out.write(0,8,2);
}'''
        descriptor=self.imported_abi(caller,method)
        self.execute(caller,'''for(std::uint64_t i=0;i<16;++i)memory.write(0x5000+i,1,0xaa);
registers.write(0x10,8,999);
assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==42);
assert(memory.calls==1);assert(memory.read(0x5000,4)==7);assert(memory.read(0x5004,4)==0xaaaaaaaa);
assert(registers.read(0x18,8)==40);assert(registers.read(0x20,8)==0x1008);
assert(registers.read(0x288,8)==0xf00d);assert(memory.read(0xff8,8)==0x105);
assert(!registers.initialized(0x10,8));''',descriptor,'#include "import-method.hpp"')
        _,report=self.generate(caller,descriptor)
        self.assertEqual(report['functions'][0]['approved_dependencies'][0]['kind'],'imported_direct_call')
        self.assertIn('0x00000900',report['imported_boundaries'])
        self.assertEqual(report['closure']['maximum_selected_depth'],1)

    def test_direct_import_rejects_missing_or_mutated_actual_return_slot(self):
        for pushed in (False,True):
            caller=self.imported_caller(push=pushed)
            method='''std::size_t calls=0;
void invoke_import(const torchlight::pcode::ImportCall&,
 const torchlight::pcode::RegisterFile&,torchlight::pcode::RegisterFile& out) override {
 ++calls;write(0xff8,8,0xbaad);out.write(0,8,999);
}'''
            descriptor=self.imported_abi(caller,method)
            self.execute(caller,'''registers.write(0,8,1234);bool failed=false;
try{(void)torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){failed=std::string(e.what()).find("sentinel")!=std::string::npos;}
assert(failed);assert(registers.read(0,8)==1234);assert(registers.read(0x20,8)==0x1000);
assert(memory.calls=='''+str(int(pushed))+');',descriptor,'#include "import-method.hpp"')

    def test_direct_import_fails_closed_for_missing_extra_or_partial_outputs(self):
        for writes in ('', 'out.write(0,4,2);', 'out.write(0,8,2);out.write(0x10,1,3);'):
            method='''void invoke_import(const torchlight::pcode::ImportCall&,
 const torchlight::pcode::RegisterFile&,torchlight::pcode::RegisterFile& out) override {
 (void)out;'''+writes+'\n}'
            caller=self.imported_caller()
            descriptor=self.imported_abi(caller,method)
            self.execute(caller,'''registers.write(0,8,1234);registers.write(0x10,8,555);bool failed=false;
try{(void)torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){failed=std::string(e.what()).find("output")!=std::string::npos;}
assert(failed);assert(registers.read(0,8)==1234);assert(registers.read(0x10,8)==555);
assert(registers.read(0x20,8)==0x1000);''',descriptor,'#include "import-method.hpp"')

    def test_direct_import_does_not_stub_absent_callback_or_expose_undeclared_inputs(self):
        caller=self.imported_caller()
        for method,include,error in (
            ('// deliberately absent implementation\n','', 'no production implementation'),
            ('''void invoke_import(const torchlight::pcode::ImportCall&,
 const torchlight::pcode::RegisterFile& in,torchlight::pcode::RegisterFile&) override {
 (void)in.read(0x18,8);
}''','#include "import-method.hpp"','p-code')):
            descriptor=self.imported_abi(caller,method)
            self.execute(caller,'''bool failed=false;
try{(void)torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){failed=std::string(e.what()).find("'''+error+'''")!=std::string::npos;}
assert(failed);assert(registers.read(0x20,8)==0x1000);''',descriptor,include)

    def test_direct_import_missing_input_is_rejected_before_callback_effects(self):
        caller=self.imported_caller()
        rows=copy.deepcopy(caller['instructions'])
        rows[0]['pcode'].pop(0) # RDI is neither supplied by the ABI nor defined.
        for index,operation in enumerate(rows[0]['pcode']):operation['index']=index
        caller=function(rows)
        method='''std::size_t calls=0;
void invoke_import(const torchlight::pcode::ImportCall&,
 const torchlight::pcode::RegisterFile&,torchlight::pcode::RegisterFile& out) override {
 ++calls;write(0x5000,4,7);out.write(0,8,2);
}'''
        descriptor=self.imported_abi(caller,method)
        self.execute(caller,'''memory.write(0x5000,4,999);bool failed=false;
try{(void)torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){failed=std::string(e.what()).find("uninitialized declared input")!=std::string::npos;}
assert(failed);assert(memory.calls==0);assert(memory.read(0x5000,4)==999);
assert(registers.read(0x20,8)==0x1000);''',descriptor,'#include "import-method.hpp"')

    def test_import_clobber_tombstones_cross_generated_callee_boundary(self):
        inner=self.imported_caller(address=0x200)
        outer=function([instruction(0x100,[op('BRANCH',None,node('ram',0x200,8))])])
        method='''void invoke_import(const torchlight::pcode::ImportCall&,
 const torchlight::pcode::RegisterFile&,torchlight::pcode::RegisterFile& out) override {out.write(0,8,2);}'''
        descriptor=self.imported_abi(inner,method)
        descriptor['functions'].update(abi(outer,inputs=((0x10,8),))['functions'])
        self.execute([outer,inner],'''registers.write(0x10,8,555);
assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==42);
assert(!registers.initialized(0x10,8));''',descriptor,'#include "import-method.hpp"')

    def test_direct_import_exception_keeps_prior_owner_effects_without_postcall_publish(self):
        caller=self.imported_caller()
        method='''void invoke_import(const torchlight::pcode::ImportCall&,
 const torchlight::pcode::RegisterFile&,torchlight::pcode::RegisterFile& out) override {
 write(0x5000,4,7);out.write(0,8,999);throw std::logic_error("effect failure");
}'''
        descriptor=self.imported_abi(caller,method)
        self.execute(caller,'''registers.write(0,8,1234);bool failed=false;
try{(void)torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::logic_error&){failed=true;}
assert(failed);assert(memory.read(0x5000,4)==7);assert(registers.read(0,8)==1234);
assert(registers.read(0x20,8)==0x1000);''',descriptor,'#include "import-method.hpp"')

    def test_import_contract_rejects_implicit_aliasing_control_registers_and_unused_sites(self):
        caller=self.imported_caller()
        descriptor=self.imported_abi(caller,'// reviewed fixture\n')
        changes=[('output_registers',[dict(offset='0x20',size=8)]),
                 ('input_registers',[dict(offset='0x288',size=8)]),
                 ('clobber_registers',[dict(offset='0x18',size=8)]),
                 ('output_registers',[dict(offset='0x0',size=8),dict(offset='0x4',size=4)]),
                 ('clobber_registers',[dict(offset='0x4',size=4)]),
                 ('output_registers',[dict(offset='0x0',size=16)])]
        for key,value in changes:
            changed=copy.deepcopy(descriptor);changed['imports']['0x900'][key]=value
            with self.subTest(key=key,value=value),self.assertRaises(lift.LiftError):self.generate(caller,changed)
        for role in ('input_registers','output_registers','clobber_registers','callsites','implementation_inputs'):
            changed=copy.deepcopy(descriptor);del changed['imports']['0x900'][role]
            with self.subTest(missing=role),self.assertRaises(lift.LiftError):self.generate(caller,changed)
        changed=copy.deepcopy(descriptor)
        changed['imports']['0x900']['callsites'][0]['pcode_index']=5
        with self.assertRaisesRegex(lift.LiftError,'callsite differs'):self.generate(caller,changed)
        changed=copy.deepcopy(descriptor)
        changed['imports']['0x900']['callsites'].append(dict(caller='0x100',instruction='0x105',pcode_index=0,kind='direct_call'))
        with self.assertRaisesRegex(lift.LiftError,'unused or mismatched'):self.generate(caller,changed)
        changed=copy.deepcopy(descriptor);changed['imports']['0x900']['callsites'][0]['kind']='indirect_call'
        with self.assertRaisesRegex(lift.LiftError,'only explicit direct_call'):self.generate(caller,changed)

    def test_direct_import_stale_implementation_rejected_and_cli_cannot_overwrite_it(self):
        caller=self.imported_caller()
        descriptor=self.imported_abi(caller,'// reviewed implementation\n')
        implementation=self.path/'import-method.hpp'
        paths=self.path/'raw.json';paths.write_text(json.dumps(caller))
        ap=self.path/'abi.json';ap.write_text(json.dumps(descriptor))
        before=implementation.read_bytes()
        for output,report in ((implementation,self.path/'report.json'),(self.path/'header.hpp',implementation)):
            result=subprocess.run(['python3',str(ROOT/'tools/lift_pcode.py'),str(paths),'--abi',str(ap),
                '--out',str(output),'--report',str(report)],capture_output=True,text=True)
            self.assertEqual(result.returncode,2)
            self.assertEqual(implementation.read_bytes(),before)
        implementation.write_text('// modified implementation\n')
        with self.assertRaisesRegex(lift.LiftError,'stale or missing implementation'):self.generate(caller,descriptor)

    def test_two_level_tail_jump_returns_reviewed_al_without_second_ret(self):
        outer=function([instruction(0x100,[op('BRANCH',None,node('ram',0x200,8))])])
        inner=function([instruction(0x200,[op('BRANCH',None,node('ram',0x300,8))])])
        leaf=function([instruction(0x300,[op('COPY',node('register',0,8),node('const',0x12345600,8)),
                   op('COPY',node('register',0,1),node('const',0,1))]+ret())])
        descriptors=[abi(d) for d in [outer,inner,leaf]]
        for descriptor in descriptors:
            next(iter(descriptor['functions'].values()))['return_register']=dict(offset='0x0',size=1)
        self.execute([outer,inner,leaf],'''assert(torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d)==0);
assert(registers.read(0,8)==0x12345600);assert(registers.read(0x20,8)==0x1008);assert(memory.reads==1);''',closure_abi(*descriptors))

    def test_callee_entry_does_not_read_undeclared_caller_register(self):
        caller=function([instruction(0x100,[op('COPY',node('register',0x18,8),node('const',40,8)),
                                           op('BRANCH',None,node('ram',0x200,8))])])
        callee=function([instruction(0x200,[op('COPY',node('register',0,8),node('register',0x18,8))]+ret())])
        self.execute([caller,callee],'''bool failed=false;
try{torchlight::pcode_generated::fn_00000100(memory,registers,0xf00d);}
catch(const std::runtime_error& e){failed=std::string(e.what()).find("uninitialized register 0x18")!=std::string::npos;}assert(failed);''')

    def test_recursive_closure_and_unknown_indirect_dependencies_are_rejected(self):
        a=function([instruction(0x100,[op('BRANCH',None,node('ram',0x200,8))])])
        b=function([instruction(0x200,[op('BRANCH',None,node('ram',0x100,8))])])
        with self.assertRaisesRegex(lift.LiftError,'recursive direct-call/tail-jump closure'):
            self.generate([a,b])
        self_call=function([instruction(0x100,[op('CALL',None,node('ram',0x100,8))],0x105),instruction(0x105,ret())])
        with self.assertRaisesRegex(lift.LiftError,'recursive direct-call/tail-jump closure'):
            self.generate(self_call)
        for operation in ['CALLIND','CALLOTHER','BRANCHIND']:
            data=function([instruction(0x100,[op(operation,None,node('register',0,8))]+ret())])
            with self.subTest(operation=operation),self.assertRaisesRegex(lift.LiftError,'unresolved dependency'):
                self.generate(data)

    def test_public_runtime_helpers_reject_invalid_width_before_shift(self):
        data=function([instruction(0x100,ret())])
        self.execute(data,'''using namespace torchlight::pcode;
for(std::size_t width : {std::size_t{0},std::size_t{9},std::size_t{1000},std::size_t{SIZE_MAX}}){
 unsigned failed=0;
 try{(void)sign_extend(1,width);}catch(const std::runtime_error&){++failed;}
 try{(void)signed_less(1,2,width);}catch(const std::runtime_error&){++failed;}
 try{(void)carry(1,2,width);}catch(const std::runtime_error&){++failed;}
 try{(void)signed_carry(1,2,width);}catch(const std::runtime_error&){++failed;}
 try{(void)signed_borrow(1,2,width);}catch(const std::runtime_error&){++failed;}
 try{(void)shift_left(1,64,width);}catch(const std::runtime_error&){++failed;}
 try{(void)shift_right(1,64,width);}catch(const std::runtime_error&){++failed;}
 try{(void)shift_signed_right(1,64,width);}catch(const std::runtime_error&){++failed;}
 assert(failed==8);
}''',abi(data,returns='void'))


if __name__=='__main__':unittest.main()
