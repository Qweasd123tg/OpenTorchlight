from pathlib import Path
from unittest.mock import patch
import sys,tempfile,subprocess,json,hashlib
sys.path.insert(0,str(Path.cwd()/'tools/decomp'));import toolchain,objdiff
out=Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/cache-audit')
with tempfile.TemporaryDirectory() as td:
 p=Path(td);high=p/'hand';low=p/'generated';cache=p/'cache'
 for x in (high,low,cache):x.mkdir()
 source=p/'probe.cpp';source.write_text('#include <Value.h>\nextern "C" int probe(){return VALUE;}\n');(low/'Value.h').write_text('#define VALUE 1\n')
 cmd=['g++','-std=c++98','-O2','-I'+str(high),'-I'+str(low),'-c']
 before=cache/'old.o';subprocess.run(cmd+[str(source),'-o',str(before)],check=True)
 deps=[str(low/'Value.h')]
 with patch.object(toolchain,'CC_CACHE',cache):
  index,miss=toolchain._cache_lookup(cmd,source);assert miss is None
  index.write_text(json.dumps({'deps':deps,'digest':toolchain._digest(cmd,source,deps),'output':'old.o'}))
  _,warm=toolchain._cache_lookup(cmd,source);assert warm==before
  (high/'Value.h').write_text('#define VALUE 2\n')
  _,stale=toolchain._cache_lookup(cmd,source)
  after=p/'fresh.o';subprocess.run(cmd+[str(source),'-o',str(after)],check=True)
  a=objdiff.object_functions(before)['probe']['norm'];b=objdiff.object_functions(after)['probe']['norm']
  assert stale==before and a!=b
  result={'unchanged_command':True,'old_recorded_dependency_unchanged':True,'new_higher_priority_header':'hand/Value.h','cache_returns_old_object':True,'cached_norm':a,'fresh_norm':b,'scope':'real _cache_lookup/_digest with synthetic dependency index and system GCC14.2; no production cache changed'}
(out/'include-shadow-results.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result,indent=2))
