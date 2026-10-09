"""C++98 value capture records string bytes, including embedded NUL."""
from pathlib import Path
import subprocess,tempfile,unittest
import toolchain
class NarrowTextCapture(unittest.TestCase):
    def test_actual_header_semantic_capture(self):
        text=r'''
#include "AutoTest.h"
int main(){
 autotest::Capture a,b,c;
 std::string first("a\0b",3), equal(first.data(),first.size()), different("a\0c",3);
 a.reset();b.reset();c.reset();
 autotest::Value<std::string> value={equal};
 autotest::observeReturn(a,first);autotest::record(b,value);
 autotest::observeReturn(c,different);
 if(a.issue||b.issue||c.issue)return 1;
 if(a.length!=sizeof(size_t)+3||a.length!=b.length||memcmp(a.data,b.data,a.length))return 2;
 if(c.length!=a.length||!memcmp(a.data,c.data,a.length))return 3;
 a.reset();a.addText(std::string());return a.length==sizeof(size_t)?0:4;
}
'''
        with tempfile.TemporaryDirectory() as folder:
            p=Path(folder);(p/'test.cpp').write_text(text)
            toolchain.compile_source(p/'test.cpp',p/'test.o',['-std=gnu++98','-I',str(toolchain.ROOT/'decomp/hybrid')])
            subprocess.run(['c++','-no-pie',str(p/'test.o'),'-o',str(p/'test')],check=True)
            subprocess.run([str(p/'test')],check=True)
