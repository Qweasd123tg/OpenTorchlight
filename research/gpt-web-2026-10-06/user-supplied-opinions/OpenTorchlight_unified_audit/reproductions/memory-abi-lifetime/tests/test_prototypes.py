import sys,unittest,tempfile
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from math_shapes import squared_length
from memory_transfers import Analysis,Ptr,recover,split_operands,integer_bytes
from native_capsule import translate,read_rows
from static_guards import pair

class MathTests(unittest.TestCase):
 def test_ordered(self):self.assertIsNotNone(squared_length('x*x+y*y+z*z',{'x','y','z'}))
 def test_explicit_left(self):self.assertIsNotNone(squared_length('(x*x+y*y)+z*z',{'x','y','z'}))
 def test_right_rejected(self):self.assertIsNone(squared_length('x*x+(y*y+z*z)',{'x','y','z'}))
 def test_changed_factor(self):self.assertIsNone(squared_length('x*x+y*z+z*z',{'x','y','z'}))
 def test_unknown_type(self):self.assertIsNone(squared_length('x*x+y*y+z*z',{'x','y'}))
 def test_call_rejected(self):self.assertIsNone(squared_length('f()*f()+y*y+z*z',{'y','z'}))
 def test_invalid_rejected(self):self.assertIsNone(squared_length('x +(',{'x'}))
 def test_repeated_component(self):self.assertEqual(squared_length('x*x+x*x+x*x',{'x'})['components'],['x']*3)

class MemoryTests(unittest.TestCase):
 def apply(self,*instructions):
  a=Analysis()
  for t in instructions:a.execute(t)
  return a
 def test_operand_split(self):self.assertEqual(split_operands('0x11(%rdi,%rsi,1),%eax'),['0x11(%rdi,%rsi,1)','%eax'])
 def test_copy(self):
  a=self.apply('mov 0x10(%rdi),%rax','mov %rax,0x20(%rdi)')
  self.assertEqual(a.recipes(),[{'operation':'memcpy','destination':32,'source':16,'bytes':8}])
 def test_zero_merge(self):
  a=self.apply('movb $0,0x20(%rdi)','movw $0,0x21(%rdi)')
  self.assertEqual(a.recipes()[0]['bytes'],3)
 def test_zero_extension(self):
  a=self.apply('mov $0xffffffffffffffff,%rax','mov $0x1234,%eax');self.assertEqual(a.number('%rax'),0x1234)
 def test_low_byte(self):
  a=self.apply('mov $0x1234,%rcx','mov $0x56,%cl');self.assertEqual(a.number('%rcx'),0x1256)
 def test_rep(self):
  a=self.apply('mov %rdi,%rdx','lea 0x10(%rdx),%rsi','lea 0x40(%rdx),%rdi','mov $2,%ecx','rep movsq (%rsi),(%rdi)')
  self.assertEqual(a.recipes()[0]['bytes'],16);self.assertEqual(a.number('%rcx'),0)
 def test_overlap_rejected(self):
  a=self.apply('mov 0x10(%rdi),%rax','mov %rax,0x14(%rdi)')
  with self.assertRaises(ValueError):a.recipes()
 def test_stale_load_rejected(self):
  a=self.apply('movzbl 0x10(%rdi),%eax','movb $0,0x10(%rdi)','mov %al,0x20(%rdi)')
  with self.assertRaises(ValueError):a.recipes()
 def test_unknown_opcode(self):
  with self.assertRaises(ValueError):self.apply('call 0x123')
 def test_unknown_address(self):
  with self.assertRaises(ValueError):self.apply('mov (%rax),%eax')
 def test_constant_nonzero_rejected(self):
  a=self.apply('movb $1,0x10(%rdi)')
  with self.assertRaises(ValueError):a.recipes()
 def test_unbounded_rep(self):
  with self.assertRaises(ValueError):self.apply('mov $9000,%ecx','rep movsq (%rsi),(%rdi)')
 def test_pointer_escape(self):
  with self.assertRaises(ValueError):self.apply('mov %rdi,0x10(%rdi)')
 def test_symbolic_check(self):
  rows=[{'text':x} for x in ['mov 0x10(%rdi),%rax','mov %rax,0x20(%rdi)','ret']]
  self.assertTrue(recover(rows)['symbolic_final_byte_maps_equal'])

class CapsuleTests(unittest.TestCase):
 def test_internal_jump(self):
  out=translate([{'address':100,'text':'je 66'},{'address':102,'text':'ret'}],'probe',100)
  self.assertIn('je .L_probe_66',out)
 def test_external_branch(self):
  with self.assertRaises(ValueError):translate([{'address':100,'text':'jmp 999'}],'probe',100)
 def test_call_rejected(self):
  with self.assertRaises(ValueError):translate([{'address':100,'text':'call 999'}],'probe',100)
 def test_rip_rejected(self):
  with self.assertRaises(ValueError):translate([{'address':100,'text':'mov (%rip),%eax'}],'probe',100)
 def test_demangled_comment_not_opcode(self):
  with tempfile.TemporaryDirectory() as td:
   p=Path(td)/'x';p.write_text('64: je 66 <C::f(unsigned int)>\n66: ret\n')
   self.assertEqual(read_rows(p,100,3)[0]['text'],'je 66')
 def test_missing_end(self):
  with tempfile.TemporaryDirectory() as td:
   p=Path(td)/'x';p.write_text('64: mov %eax,%eax\n')
   with self.assertRaises(ValueError):read_rows(p,100,2)

class GuardTests(unittest.TestCase):
 def test_unique(self):self.assertEqual(pair([{'name':'guard variable for A::f()::x'},{'name':'A::f()::x'}])['unique_pairs'],1)
 def test_missing(self):self.assertEqual(pair([{'name':'guard variable for A::f()::x'}])['unique_pairs'],0)
 def test_duplicate(self):self.assertEqual(pair([{'name':'guard variable for A::f()::x'},{'name':'A::f()::x'},{'name':'A::f()::x'}])['unique_pairs'],0)
 def test_namespaces(self):self.assertEqual(pair([{'name':'guard variable for A::f()::x'},{'name':'B::f()::x'}])['unique_pairs'],0)

if __name__=='__main__':unittest.main(verbosity=2)
