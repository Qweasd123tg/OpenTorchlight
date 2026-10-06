import json, tempfile, unittest
from pathlib import Path
import audit_snapshot as a

class AuditTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory(); self.root=Path(self.tmp.name)/'repo'
        for p in ('decomp/include','decomp/src','decomp/hybrid/tests','tools/decomp','research'):
            (self.root/p).mkdir(parents=True,exist_ok=True)
        (self.root/'decomp/config.json').write_text('{}')
    def tearDown(self):self.tmp.cleanup()
    def test_symbol_alias_dedup(self):
        d=a.parse_symbols('00001000 00000010 T CThing::a()\n00001000 00000010 T CThing::b()\n')
        self.assertEqual(len(d),1);self.assertEqual(d['0x1000']['size'],16);self.assertEqual(len(d['0x1000']['names']),2)
    def test_nonsized_and_data_symbols_not_functions(self):
        self.assertFalse(a.parse_symbols('00001000 T x\n00001100 00000008 B global\n'))
    def test_cycles_in_include_graph(self):
        (self.root/'decomp/include/A.h').write_text('#include "B.h"\n')
        (self.root/'decomp/include/B.h').write_text('#include "A.h"\n')
        (self.root/'decomp/src/test.cpp').write_text('#include "A.h"\n')
        d=a.include_graph(self.root);self.assertEqual([x['source_dependents'] for x in d],[1,1])
    def test_missing_historical_corpus_is_unknown(self):
        self.assertEqual(a.largest_corpus(self.root,{}),{'available':False})
    def test_files_ignore_build_and_symlinks(self):
        (self.root/'build-decomp').mkdir();(self.root/'build-decomp/x').write_text('x')
        (self.root/'link').symlink_to(self.root/'decomp/config.json')
        self.assertEqual([str(x.relative_to(self.root)) for x in a.safe_files(self.root)],['decomp/config.json'])
    def test_output_may_not_write_source_tree(self):
        with self.assertRaises(ValueError):a.run(self.root,self.root/'report')
    def test_invalid_root_rejected(self):
        with self.assertRaises(ValueError):a.run(Path(self.tmp.name),Path(self.tmp.name)/'out')
    def test_inventory_preserves_source_hash(self):
        before=a.sha(self.root/'decomp/config.json');out=Path(self.tmp.name)/'out'
        result=a.run(self.root,out);self.assertEqual(before,a.sha(self.root/'decomp/config.json'))
        self.assertEqual(result['files'],1);self.assertTrue((out/'source_manifest.json').is_file())
if __name__=='__main__':unittest.main(verbosity=2)
