import sys,inspect,re,json,pathlib
sys.path.insert(0,'tools/decomp');import ghidra_cpp
original=ghidra_cpp.inline_temp_strings
source=inspect.getsource(original).replace(', literal, text)', ', lambda _match: literal, text)')
namespace={'re':re}; exec(source,namespace); fixed=namespace['inline_temp_strings']
cases=[r'L"media\\resources.dat"',r'L"media\\levelsets\\"',r'L"line\nnext"',r'L"quote\"here"',r'L"simple"']
results=[]
for lit in cases:
 fixture='\n  long local_a[2];\n  std::wstring::wstring((wstring_conflict *)local_a,'+lit+',&local_b);\n  consume((wstring_conflict *)local_a);\n'
 before=original(fixture);after=fixed(fixture)
 row={'literal':lit,'before':before.strip(),'after':after.strip(),'preserved_before':('consume('+lit+');') in before,'preserved_after':('consume('+lit+');') in after}
 results.append(row)
 assert row['preserved_after']
print(json.dumps(results,indent=2))
pathlib.Path('build-decomp/automation-audit/literal-probe.json').write_text(json.dumps(results,indent=2))
pathlib.Path('build-decomp/automation-audit/literal-rule-prototype.py').write_text('import re\n\n'+source)
