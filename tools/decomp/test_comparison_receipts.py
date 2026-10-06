"""Actual C++98 calls and observer outcomes are required to emit coverage."""
from pathlib import Path
import subprocess
import tempfile
import unittest

import toolchain


FIXTURE = r'''
#include <cstdio>
#include <cstdarg>
#include "AutoTest.h"
namespace autotest {
char g_arena[kArenaSize]; size_t g_arenaUsed; Pool g_pool; Outcome g_outcomes[2];
}
static int mode;
static int original(int x) { return x+11; }
static int restored(int x) { return x+(mode==1 ? 22 : 11); }
static int other(int x) { return x+11; }
static int pair(uint64_t a,uint64_t b) {
 return a==(uint64_t)(uintptr_t)&original && b==(uint64_t)(uintptr_t)&restored && a!=b;
}
static void logline(const char*, ...) {}
static tlhybrid_host host={TLHYBRID_ABI_VERSION,logline,pair};
static void a(void* p,autotest::Capture& out) { autotest::invoke(out,&original,*(int*)p); }
static void b(void* p,autotest::Capture& out) { autotest::invoke(out,&restored,*(int*)p); }
static void wrong(void* p,autotest::Capture& out) { autotest::invoke(out,&other,*(int*)p); }
static void empty(void* p,autotest::Capture& out) { int x=*(int*)p+11;out.add(&x,sizeof(x)); }
static void doubled(void* p,autotest::Capture& out) { b(p,out);b(p,out); }
static void crash(void*,autotest::Capture&) { raise(SIGSEGV); }
#define CHECK(x) do { if(!(x)) { std::fprintf(stderr,"line %d\n",__LINE__);return 1; } } while(0)
static bool compare(autotest::Body body, unsigned completed,unsigned different,unsigned incomplete) {
 int x=3;autotest::Stats stats={0,0,0};
 autotest::Coverage coverage("receipt",(uint64_t)(uintptr_t)&original);
 bool ok=autotest::compareCase(a,body,&x,stats,&host,"receipt",0,&coverage);
 return coverage.completed==completed && coverage.different==different && coverage.missing==incomplete &&
        ok==(different==0 && incomplete==0);
}
int main() {
 CHECK(compare(b,1,0,0));
 mode=1;CHECK(compare(b,1,1,0));mode=0;
 CHECK(compare(wrong,0,0,1));
 CHECK(compare(a,0,0,1)); // Original compared with itself has no replacement execution.
 CHECK(compare(empty,0,0,1)); // Same captured value without target invocation is incomplete.
 CHECK(compare(doubled,0,0,1));
 CHECK(compare(crash,0,0,1));
 host.comparison_pair=0;CHECK(compare(b,0,0,1));
 return 0;
}
'''


class ReceiptRuntime(unittest.TestCase):
    def test_real_calls_and_negative_controls(self):
        with tempfile.TemporaryDirectory(prefix="otl-receipts-") as folder:
            source, obj, binary = [Path(folder)/p for p in ("receipt.cpp", "receipt.o", "receipt")]
            source.write_text(FIXTURE)
            toolchain.compile_source(source,obj,["-std=gnu++98","-I",str(toolchain.ROOT/"decomp/hybrid")],cache=False)
            subprocess.run(["c++","-no-pie",str(obj),"-o",str(binary)],check=True,capture_output=True)
            subprocess.run([str(binary)],check=True,timeout=15,capture_output=True)


if __name__ == "__main__":
    unittest.main()
