#!/usr/bin/env python3
"""Run eligible uploaded tests without pretending the host compiler is GCC 4.4.7.
Tests that unconditionally need the unavailable pinned compiler are listed as
not run. Existing @skipUnless SDK/compiler tests keep their normal skip status.
"""
import argparse,contextlib,io,json,os
from pathlib import Path
import sys,unittest

def leaves(suite):
 for item in suite:
  if isinstance(item,unittest.TestSuite):yield from leaves(item)
  else:yield item

def main():
 p=argparse.ArgumentParser();p.add_argument('--project',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
 sys.dont_write_bytecode=True;sys.path.insert(0,str(a.project.resolve()/'tools/decomp'))
 import toolchain
 pinned=(toolchain.cache_dir()/'gcc447/.complete.json').exists()
 tests=list(leaves(unittest.defaultTestLoader.discover(str(a.project/'tools/decomp'),pattern='test_*.py')))
 excluded=[];selected=[]
 for t in tests:
  name=t.id()
  needs=(name.startswith(('test_autotest_capture.','test_autotest_returns.','test_types_export_identity.'))
        or 'test_generated_property_belongs_to_tu_as_a_strong_definition' in name
        or 'test_new_higher_priority_header_changes_real_object_and_warm_hit' in name)
  if needs and not pinned:excluded.append({'test':name,'reason':'requires installed GCC 4.4.7; not substituted with host compiler'})
  else:selected.append(t)
 a.out.mkdir(parents=True,exist_ok=True)
 with (a.out/'existing-eligible.txt').open('w') as log,contextlib.redirect_stdout(log),contextlib.redirect_stderr(log):
  result=unittest.TextTestRunner(stream=log,verbosity=2).run(unittest.TestSuite(selected))
 data={'discovered':len(tests),'run':result.testsRun,'passed':result.testsRun-len(result.skipped)-len(result.errors)-len(result.failures),
       'skipped':[{'test':t.id(),'reason':reason}for t,reason in result.skipped],
       'not_run':excluded,'errors':[{'test':t.id(),'trace':msg}for t,msg in result.errors],
       'failures':[{'test':t.id(),'trace':msg}for t,msg in result.failures],'pinned_available':pinned}
 (a.out/'existing-summary.json').write_text(json.dumps(data,indent=2,ensure_ascii=False)+'\n')
 print(json.dumps({k:len(v)if isinstance(v,list)else v for k,v in data.items()},indent=2))
 return int(bool(result.errors or result.failures))
if __name__=='__main__':raise SystemExit(main())
