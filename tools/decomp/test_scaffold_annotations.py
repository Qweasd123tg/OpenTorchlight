import sys
import unittest
from types import SimpleNamespace
from pathlib import Path
import scaffold

def sym(name, value, defined=True, kind=1):
    return SimpleNamespace(name=name,value=value,defined=defined,type=kind)

def image(symbols, rodata=False):
    return SimpleNamespace(symbols=symbols, section_at=lambda a: SimpleNamespace(name='.rodata') if rodata else None,
                           read=lambda a,n: b'hello\0'+b'\0'*506)

class AnnotationsTest(unittest.TestCase):
    def test_distinct_demangled_caches(self):
        a='_ZZN12CEnchantMenu12updateLayoutEvE12g_MaxEnchant'
        b=a+'_0'
        result=scaffold.annotate('mov # 100 <same>\nmov # 108 <same>',image([sym(a,0x100),sym(b,0x108)]))
        lines=result.splitlines()
        self.assertTrue(lines[0].endswith('symbols '+a));self.assertTrue(lines[1].endswith('symbols '+b))
    def test_guard_and_duplicate_targets(self):
        a='_ZGVZN1A1fEvE1x'
        result=scaffold.annotate('mov $0x100 # 100',image([sym(a,0x100),sym(a,0x100)]))
        self.assertEqual(result.count(a),1)
    def test_excludes_undefined_functions_and_globals(self):
        result=scaffold.annotate('mov # 100',image([sym('_ZZbad',0x100,False),sym('_ZZfunc',0x100,kind=2),sym('global',0x100)]))
        self.assertEqual(result,'mov # 100\n')
    def test_literals_still_annotated(self):
        result=scaffold.annotate('mov $0x100',image([],True))
        self.assertIn('"hello"',result)
    def test_sorted_aliases(self):
        result=scaffold.annotate('mov # 100',image([sym('_ZZb',0x100),sym('_ZZa',0x100)]))
        self.assertIn('symbols _ZZa,_ZZb',result)


class ScalarAnnotationsTest(unittest.TestCase):
    def scalar_image(self, raw, section='.rodata'):
        def read(address, count):
            if address != 0x100 or count > len(raw):
                raise ValueError('outside file-backed constant')
            return raw[:count]
        return SimpleNamespace(symbols=[],section_at=lambda a: SimpleNamespace(name=section),read=read)

    def test_float_at_end_of_rodata(self):
        result=scaffold.annotate('  200: movss 0(%rip),%xmm0 # 100',self.scalar_image(bytes.fromhex('00000042')))
        self.assertIn('f32 32.0 (0x42000000)',result)

    def test_double(self):
        result=scaffold.annotate('  200: addsd 0(%rip),%xmm0 # 100',self.scalar_image(bytes.fromhex('000000000000f83f')))
        self.assertIn('f64 1.5 (0x3ff8000000000000)',result)

    def test_nan_payload_and_negative_zero(self):
        for raw,note in [('4523c17f','f32 nan (0x7fc12345)'),('00000080','f32 -0.0 (0x80000000)')]:
            with self.subTest(raw=raw):
                self.assertIn(note,scaffold.annotate('  200: minss 0(%rip),%xmm0 # 100',self.scalar_image(bytes.fromhex(raw))))

    def test_conversion_uses_source_width(self):
        result=scaffold.annotate('  200: cvtss2sd 0(%rip),%xmm0 # 100',self.scalar_image(bytes.fromhex('00000042')))
        self.assertIn('f32 32.0',result)
        result=scaffold.annotate('  200: cvtsd2ss 0(%rip),%xmm0 # 100',self.scalar_image(bytes.fromhex('000000000000f83f')))
        self.assertIn('f64 1.5',result)

    def test_non_scalar_instruction_is_not_interpreted(self):
        result=scaffold.annotate('  200: mov 0(%rip),%eax # 100',self.scalar_image(bytes.fromhex('00000042')))
        self.assertNotIn('f32',result)

    def test_mutable_data_is_not_interpreted(self):
        result=scaffold.annotate('  200: movss 0(%rip),%xmm0 # 100',self.scalar_image(bytes.fromhex('00000042'),'.data'))
        self.assertNotIn('f32',result)

if __name__=='__main__':unittest.main()
