import json,sys,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from archive import remove_comments,split_args,close_paren
from binding_recipes import extract,decode_pmf
from resource_recipes import extract as extract_reads
from snapshot_to_cpp import emit,wide_literal

BIND='''local_48[0] = operator_new(0x20);
local_48[0][3] = this;
*local_48[0] = &PTR__MemberFunctionSlot_00001010;
local_48[0][2] = 0;
local_48[0][1] = handle_Close;
'''
VT={0x1010:'CProbe'}
class BindingTests(unittest.TestCase):
    def test_direct(self):self.assertEqual(extract(BIND,VT)[0]['construction_candidate'],'CEGUI::SubscriberSlot(&CProbe::handle_Close, this)')
    def test_virtual(self):
        r=extract(BIND.replace('handle_Close','0x59'),VT)[0]
        self.assertEqual(r['member_pointer']['vtable_byte_offset'],0x58);self.assertNotIn('construction_candidate',r)
    def test_adjustment_not_discarded(self):
        r=extract(BIND.replace('[2] = 0','[2] = 16'),VT)[0]
        self.assertEqual(r['member_pointer']['this_adjustment'],16);self.assertNotIn('construction_candidate',r)
    def test_missing_field_rejected(self):self.assertEqual(extract(BIND.replace('local_48[0][2] = 0;',''),VT),[])
    def test_duplicate_field_rejected(self):self.assertEqual(extract(BIND.replace('[2] = 0','[1] = 0'),VT),[])
    def test_branch_rejected(self):self.assertEqual(extract(BIND.replace('local_48[0][2]','if (flag) { local_48[0][2]'),VT),[])
    def test_unknown_type_not_emitted(self):self.assertNotIn('construction_candidate',extract(BIND,{})[0])
    def test_null(self):self.assertEqual(decode_pmf('0','0')['kind'],'null')
    def test_invalid_slot(self):self.assertEqual(decode_pmf('3','0')['kind'],'invalid_virtual_offset')
    def test_string_fake_alloc(self):self.assertEqual(extract(json.dumps(BIND),VT),[])
    def test_comment_fake_alloc(self):self.assertEqual(extract('/*'+BIND+'*/',VT),[])

class ResourceTests(unittest.TestCase):
    text='''CVar1 = this[0x33];
std::wstring::wstring((wstring_conflict *)local_108,L"SAVE",&alloc);
CVar1 = (CEffect)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_108,(bool)CVar1);
this[0x33] = CVar1;
'''
    def test_bool_default_preserved(self):self.assertEqual(extract_reads(self.text)[0]['pattern'],'bool_read_with_existing_field_default')
    def test_no_nearest_unrelated(self):self.assertNotIn('key_literal',extract_reads(self.text.replace('local_108,L','local_109,L'))[0])
    def test_different_destination(self):self.assertNotIn('pattern',extract_reads(self.text.replace('this[0x33] = CVar1','this[0x36] = CVar1'))[0])
    def test_fixed_default_not_field_default(self):self.assertNotIn('pattern',extract_reads(self.text.replace('(bool)CVar1','false'))[0])
    def test_literal_preservation(self):self.assertIn('L"A, byte false"',extract_reads(self.text.replace('L"SAVE"','L"A, byte false"'))[0]['key_literal'])
    def test_key_reconstruction_still_candidate(self):self.assertEqual(extract_reads(self.text)[0]['status'],'CANDIDATE_ONLY')

class TableTests(unittest.TestCase):
    def snapshot(self):return {'format':'typed-logical-tables-v1','tables':[{'name':'names','type':'wstring','shape':[1],'values':[[65,0,66]]}]}
    def test_embedded_nul_length(self):self.assertIn('L"A\\000B", 3',emit(self.snapshot()))
    def test_unknown_rejected(self):
        s=self.snapshot();s['tables'][0]['values']=[None]
        with self.assertRaises(ValueError):emit(s)
    def test_surrogate_rejected(self):
        with self.assertRaises(ValueError):wide_literal([0xd800])
    def test_shape_mismatch(self):
        s=self.snapshot();s['tables'][0]['shape']=[2]
        with self.assertRaises(ValueError):emit(s)
    def test_type_not_guessed(self):
        s=self.snapshot();s['tables'][0]['type']='pointer'
        with self.assertRaises(ValueError):emit(s)
    def test_int_min(self):
        s=self.snapshot();s['tables'][0].update(type='int32',values=[-2147483648]);self.assertIn('(-2147483647 - 1)',emit(s))
    def test_2d(self):
        s=self.snapshot();s['tables'][0].update(type='int32',shape=[2,2],values=[1,2,3,4]);self.assertIn('names[2][2]',emit(s))
    def test_duplicate_names_rejected(self):
        s=self.snapshot();s['tables'].append(s['tables'][0])
        with self.assertRaises(ValueError):emit(s)

class LexicalTests(unittest.TestCase):
    def test_nested_comma(self):self.assertEqual(len(split_args('x, f(y, z), L"a,b"')),3)
    def test_string_comment_marker(self):self.assertIn('"/*keep*/"',remove_comments('"/*keep*/" /* remove */'))
    def test_closing_paren_in_string(self):self.assertEqual(close_paren('(f(")"))',0),7)

if __name__=='__main__':unittest.main(verbosity=2)
