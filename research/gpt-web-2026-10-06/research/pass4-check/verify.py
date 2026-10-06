import sys,subprocess,json
from pathlib import Path
sys.path.insert(0,str(Path.cwd()/'tools/decomp'));import ghidra_cpp
p=Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/pass4-check');results={}
def run(name,source):
 f=p/(name+'.cpp');f.write_text(source);exe=p/name
 subprocess.run(['g++','-std=c++98','-O2',str(f),'-o',str(exe)],check=True,capture_output=True)
 return subprocess.check_output([str(exe)],text=True).strip()
for name,draft,main,expected in [
 ('boolean','int probe(int x)\n{\n return x != false;\n}\n','int main(){printf("%d %d %d\\n",probe(-3),probe(0),probe(2));}', '1 0 1'),
 ('literal','const char* probe()\n{\n return "bad UTF-8 continuation byte";\n}\n','int main(){puts(probe());}','bad UTF-8 continuation byte'),
 ('comment_in_literal','const char* probe()\n{\n return "keep /* payload */ exact";\n}\n','int main(){puts(probe());}','keep /* payload */ exact')]:
 fixed=ghidra_cpp.convert(draft,set());before=run(name+'_before','#include <cstdio>\n'+draft+main);after=run(name+'_converted','#include <cstdio>\n'+fixed+main)
 assert before==expected and before!=after;results[name]={'before':before,'after':after,'converted':fixed}
draft='int probe(CBase* object)\n{\n return CBase::step(object);\n}\n';converted=ghidra_cpp.convert(draft,{('CBase','step')});head='#include <cstdio>\nstruct CBase { virtual int step(){return 11;} }; struct CDerived:CBase {int step(){return 22;}};\n';main='int main(){CDerived d;printf("%d\\n",probe(&d));}'
before=run('dispatch_before',head+'int probe(CBase* object){return object->CBase::step();}\n'+main);after=run('dispatch_converted',head+converted+main);assert (before,after)==('11','22');results['dispatch']={'before':before,'after':after,'converted':converted}
f={'demangled':'CProbe::get() const','params':'','cv':'const','kind':'function'}
cv=ghidra_cpp.convert('int __thiscall CProbe::get(CProbe *this)\n{\n return this->x;\n}\n',set(),f)
assert 'get() const' not in cv;results['cv']={'converted':cv}
(p/'results.json').write_text(json.dumps(results,indent=2)+'\n');print(json.dumps(results,indent=2))
