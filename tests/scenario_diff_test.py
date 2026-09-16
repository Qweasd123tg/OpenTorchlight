#!/usr/bin/env python3
"""Negative checks: one lost bone/texture/RNG call/pixel must never pass."""
import importlib.util,json,shutil,sys,tempfile,unittest
from pathlib import Path
root=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('comparison',root/'tools/compare_scenarios.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
class DiffTests(unittest.TestCase):
    def test_boundaries(self):
        with tempfile.TemporaryDirectory() as temp:
            a,b=Path(temp)/'a',Path(temp)/'b';a.mkdir();b.mkdir()
            def reset():
                for p in b.iterdir():p.unlink()
                for p in a.iterdir():shutil.copyfile(p,b/p.name)
            (a/'environment.json').write_text(json.dumps({'status':'PASSED',
                'pak_sha256':'authored-unit-fixture-not-an-original-pak',
                'script_sha256':'authored-unit-script', 'graphics':{'kind':'authored-comparison-fixture'}}))
            (a/'frame.state.json').write_text(json.dumps({'bones':[{'position':[0.0,1.0,2.0]}],'hp':100}))
            (a/'frame.render.json').write_text(json.dumps({'instances':[{'texture':'sword.dds'}]}))
            (a/'frame.image.json').write_text(json.dumps({'viewport':[2,2]}))
            (a/'rng.jsonl').write_text('{"sequence":0,"result":7}\n')
            (a/'frame.rgba').write_bytes(bytes(range(16)))
            reset();self.assertEqual(m.compare(a,b)['status'],'PASSED')
            cases=[('frame.state.json',{'bones':[{'position':[0.0,1.001,2.0]}],'hp':100},'state'),
                   ('frame.render.json',{'instances':[{'texture':'axe.dds'}]},'render-state')]
            for file,data,boundary in cases:
                reset();(b/file).write_text(json.dumps(data))
                result=m.compare(a,b);self.assertEqual(result['status'],'FAILED');self.assertEqual(result['boundary'],boundary)
            reset();(b/'rng.jsonl').write_text('')
            self.assertEqual(m.compare(a,b)['boundary'],'RNG-order')
            reset();raw=bytearray(range(16));raw[9]^=1;(b/'frame.rgba').write_bytes(raw)
            r=m.compare(a,b);self.assertEqual(r['boundary'],'pixels');self.assertEqual(r['first_difference']['x'],0)
            self.assertEqual(r['first_difference']['y_from_top'],0);self.assertEqual(r['first_difference']['channel'],'G')
            reset();(b/'frame.render.json').unlink();self.assertEqual(m.compare(a,b)['status'],'FAILED')
            reset();(b/'environment.json').unlink()
            with self.assertRaises(ValueError):m.compare(a,b)
    def test_no_vacuous_success(self):
        with tempfile.TemporaryDirectory() as temp:
            a,b=Path(temp)/'a',Path(temp)/'b';a.mkdir();b.mkdir()
            with self.assertRaises(ValueError):m.compare(a,b)
if __name__=='__main__':unittest.main()
