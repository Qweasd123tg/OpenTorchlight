import contextlib,io,json,sys
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import toolchain,elfdb,ghidra_cpp
from rewrite_geometry import rewrite
root=Path('build-decomp/sdk-prototype-experiment/geometry');root.mkdir(parents=True,exist_ok=True)
source='''#include <CEGUI.h>
void geometry(CEGUI::Window* window) {
    CEGUI::UVector2 size; CEGUI::UDim width,height;
    CEGUI::Window::getSize(&size,window);
    CEGUI::Window::getWidth(&width,window);
    CEGUI::Window::getHeight(&height,window);
    CEGUI::Window::setSize(window,&size);
    CEGUI::Window::setPosition(window,&size);
}
'''
fixed,records=rewrite(source);assert len(records)==5
negative=['CEGUI::Window::getSize();','CEGUI::Window::getSize(&size,nextWindow());','CEGUI::Window::setSize(window,&array[index++]);','CEGUI::Window::setSize(window,value);','// CEGUI::Window::getSize(&size,window);','const char* s="CEGUI::Window::getSize(&size,window)";']
for text in negative:assert rewrite(text)==(text,[]),text
results=[]
db=elfdb.load_db();converted=ghidra_cpp.convert(fixed,ghidra_cpp.known_methods(db),signatures=ghidra_cpp.signatures_of(db),enums=ghidra_cpp.parse_enums())
for label,text in [('baseline',source),('repaired',fixed),('after_legacy_conversion',converted)]:
 file=root/(label+'.cpp');file.write_text(text);errors=io.StringIO();ok=True
 try:
  with contextlib.redirect_stderr(errors):toolchain.compile_source(file,root/(label+'.o'))
 except SystemExit:ok=False
 (root/(label+'.errors.txt')).write_text(errors.getvalue())
 results.append({'arm':label,'compiles':ok})
assert results==[{'arm':'baseline','compiles':False},{'arm':'repaired','compiles':True},{'arm':'after_legacy_conversion','compiles':True}],results
out={'changed_calls':records,'negative_cases':len(negative),'compiler':results,'scope':'only a geometry-call microfixture against real SDK headers; no whole-function acceptance'}
Path('research/decomp-acceleration-2026-10-05/results/geometry-microfixture.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out))
