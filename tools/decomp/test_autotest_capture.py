#!/usr/bin/env python3
"""Compile-run regressions against the actual bounded observer and fork protocol."""
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest import mock

import autotest
import toolchain


FIXTURE = r'''
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <cstdarg>
#include <cstdio>

// Inject real short transfers and EINTR into the runtime's pipe operations.
static int mode, reads, writes, waits;
ssize_t observedRead(int fd, void* p, size_t n) {
    ++reads;
    if (mode == 1 && reads == 1) { errno = EINTR; return -1; }
    return ::read(fd, p, mode == 1 && n > 1 ? 1 : n);
}
ssize_t observedWrite(int fd, const void* p, size_t n) {
    ++writes;
    if (mode == 1 && writes == 1) { errno = EINTR; return -1; }
    if (mode == 2 && writes == 1) { ::write(fd, p, n-1); _exit(0); }
    if (mode == 3 && writes == 2) { ::write(fd, p, 1); _exit(0); }
    if (mode == 4 && writes == 1) { ::write(fd, p, n-1); _exit(7); }
    if (mode == 5) { errno = EIO; return -1; }
    return ::write(fd, p, mode == 1 && n > 1 ? 1 : n);
}
pid_t observedWait(pid_t pid, int* status, int options) {
    ++waits;
    if (mode == 1 && waits == 1) { errno = EINTR; return -1; }
    return ::waitpid(pid, status, options);
}
#define read observedRead
#define write observedWrite
#define waitpid observedWait
#include "AutoTest.h"
#undef read
#undef write
#undef waitpid

namespace autotest {
char g_arena[kArenaSize];
size_t g_arenaUsed;
Pool g_pool;
Outcome g_outcomes[2];
}
static void logline(const char* fmt, ...) {
    va_list args; va_start(args,fmt); vprintf(fmt,args); va_end(args);
}
static tlhybrid_host host = {TLHYBRID_ABI_VERSION,logline};
static int x=10,y=20;
static void complete(void* p,autotest::Capture& c) { c.add(p,sizeof(int)); }
static void empty(void*,autotest::Capture&) {}
static void absent(void*,autotest::Capture&) { _exit(0); }
static void crash(void*,autotest::Capture&) { raise(SIGSEGV); }
static void tailA(void*,autotest::Capture& c) {
    autotest::g_arena[300000]=1; c.add(autotest::g_arena,300001);
}
static void tailB(void*,autotest::Capture& c) {
    autotest::g_arena[300000]=2; c.add(autotest::g_arena,300001);
}
static void externalA(void*,autotest::Capture& c) { c.addPointer(&x); }
static void externalB(void*,autotest::Capture& c) { c.addPointer(&y); }
static void arenaA(void*,autotest::Capture& c) { c.addPointer(autotest::g_arena+10); }
static void arenaB(void*,autotest::Capture& c) { c.addPointer(autotest::g_arena+20); }
static void nullPointer(void*,autotest::Capture& c) { c.addPointer(0); }
static void childPointer(void*,autotest::Capture& c) {
    int* p=new int(23); c.addPointer(p); delete p;
}
static void full(void*,autotest::Capture& c) { c.add(autotest::g_arena,c.kSize); }
static void overflow(void*,autotest::Capture& c) {
    full(0,c); c.add(&x,1);
}
static void huge(void*,autotest::Capture& c) { c.add(&x,(size_t)-1); }
static void sleepComplete(void*,autotest::Capture& c) { usleep(400000); c.add(&x,sizeof(x)); }
static void spin(void*,autotest::Capture&) { for(;;) {} }
static void block(void*,autotest::Capture&) { for(;;) pause(); }

static bool compare(autotest::Body a,autotest::Body b,int same,int failed,int different,int incomplete) {
    autotest::Stats stats={0,0,0};
    reads=writes=waits=0;
    bool accepted=autotest::compareCase(a,b,&x,stats,&host,"capture-regression",0);
    return stats.same==same && stats.bothFailed==failed && stats.different==different &&
           stats.incomplete==incomplete && accepted==(different==0 && incomplete==0);
}

static bool frame(autotest::ReportHeader header,const char* payload,size_t bytes,bool expected,
                  bool extra=false,size_t headerBytes=sizeof(autotest::ReportHeader)) {
    int fds[2]; if(pipe(fds)!=0)return false;
    if(::write(fds[1],&header,headerBytes)!=(ssize_t)headerBytes)return false;
    if(bytes && ::write(fds[1],payload,bytes)!=(ssize_t)bytes)return false;
    if(extra && ::write(fds[1],"x",1)!=1)return false;
    close(fds[1]);
    autotest::Capture capture={};
    bool valid=autotest::readReport(fds[0],capture); close(fds[0]);
    return valid==expected && (valid || (capture.length==0 && capture.issue==capture.InvalidReport));
}

#define CHECK(expression) do { if(!(expression)) { \
    fprintf(stderr,"capture regression line %d: %s\n",__LINE__,#expression); return 1; } } while(0)
int main() {
    CHECK(compare(complete,complete,1,0,0,0));
    CHECK(compare(empty,empty,1,0,0,0)); // Valid empty frame differs from absent report.
    CHECK(compare(full,full,1,0,0,0)); // Exact capacity is complete.
    CHECK(compare(tailA,tailB,0,0,0,1));
    CHECK(compare(overflow,overflow,0,0,0,1));
    CHECK(compare(huge,huge,0,0,0,1));
    CHECK(compare(externalA,externalB,0,0,0,1));
    CHECK(compare(externalA,externalA,0,0,0,1));
    CHECK(compare(childPointer,childPointer,0,0,0,1));
    CHECK(compare(arenaA,arenaA,1,0,0,0));
    CHECK(compare(arenaA,arenaB,0,0,1,0));
    CHECK(compare(nullPointer,nullPointer,1,0,0,0));
    CHECK(compare(absent,absent,0,0,0,1));
    CHECK(compare(absent,empty,0,0,0,1));
    CHECK(compare(crash,crash,0,1,0,0));
    CHECK(compare(crash,complete,0,0,1,0));
    CHECK(compare(crash,externalA,0,0,0,1));
    mode=1; CHECK(compare(complete,complete,1,0,0,0));
    mode=2; CHECK(compare(complete,complete,0,0,0,1)); // Truncated header, exit 0.
    mode=3; CHECK(compare(complete,complete,0,0,0,1)); // Truncated payload, exit 0.
    mode=4; CHECK(compare(complete,complete,0,0,0,1)); // Partial frame remains incomplete on exit 7.
    mode=5; CHECK(compare(complete,complete,0,0,0,1)); // Observer write failure is not a killed mutation.
    mode=0;
    autotest::Outcome outcome;
    autotest::runChild(sleepComplete,0,outcome);
    CHECK(outcome.reportValid && !autotest::incomplete(outcome)); // no old 300ms wall false alarm
    autotest::runChild(spin,0,outcome,25,1000);
    CHECK(WIFSIGNALED(outcome.childStatus) && WTERMSIG(outcome.childStatus)==SIGPROF && autotest::incomplete(outcome));
    autotest::runChild(block,0,outcome,1000,25);
    CHECK(WIFSIGNALED(outcome.childStatus) && WTERMSIG(outcome.childStatus)==SIGALRM && autotest::incomplete(outcome));
    autotest::runChild(absent,0,outcome);
    CHECK(!outcome.reportValid && outcome.childStatus==0 && WEXITSTATUS(outcome.status)!=0);
    autotest::runChild(externalA,0,outcome);
    CHECK(outcome.reportValid && outcome.capture.issue==autotest::Capture::UnsupportedPointer &&
          outcome.childStatus==0 && WEXITSTATUS(outcome.status)!=0);
    const char data[]="abc";
    autotest::ReportHeader header={autotest::kReportMagic,2,3,0};
    CHECK(frame(header,data,3,true));
    CHECK(frame(header,data,2,false));
    CHECK(frame(header,data,0,false,false,sizeof(header)-1));
    CHECK(frame(header,data,3,false,true));
    header.magic=0; CHECK(frame(header,data,3,false));
    header.magic=autotest::kReportMagic;header.version=1; CHECK(frame(header,data,3,false));
    header.version=2;header.length=autotest::Capture::kSize+1; CHECK(frame(header,data,3,false));
    header.length=3;header.issue=99; CHECK(frame(header,data,3,false));
    return 0;
}
'''


class CaptureProtocol(unittest.TestCase):
    def test_actual_runtime(self):
        with tempfile.TemporaryDirectory(prefix="otl-capture-test-") as folder:
            source = Path(folder) / "capture.cpp"
            obj = Path(folder) / "capture.o"
            binary = Path(folder) / "capture"
            source.write_text(FIXTURE)
            toolchain.compile_source(source, obj, ["-std=gnu++98", "-I", str(toolchain.ROOT / "decomp/hybrid")],
                                     cache=False)
            subprocess.run(["c++", "-no-pie", str(obj), "-o", str(binary)], check=True)
            subprocess.run([str(binary)], check=True, timeout=15, capture_output=True)

    def test_generated_acceptance_requires_complete_minimum(self):
        # Small synthetic class exercises generation without the game database.
        generator = object.__new__(autotest.Generator)
        generator.headers = {"Fixture": "Fixture.h"}
        generator.classes = {"Fixture": {"size": 4, "bases": [], "fields": []}}
        generator.vtables = {}
        generator.enums = {}
        generator.is_static = lambda *args: False
        function = {
            "scope": "Fixture", "demangled": "Fixture::value()", "params": "", "kind": "function",
            "names": ["_ZN7Fixture5valueEv"], "address": "0x1234",
        }
        with mock.patch.object(autotest, "CASES", autotest.MIN_COMPLETED - 1):
            _, short = generator.test_for(function)
        with mock.patch.object(autotest, "CASES", autotest.MIN_COMPLETED):
            _, enough = generator.test_for(dict(function, address="0x1235"))
        text = r'''
#include "AutoTest.h"
namespace autotest {
char g_arena[kArenaSize]; size_t g_arenaUsed; Pool g_pool; Outcome g_outcomes[2];
}
static int mode;
struct Fixture { int dummy; int value(); };
int Fixture::value() { if(mode==1)raise(SIGSEGV); return 23; }
extern "C" int originalValue(void*) __asm__("__tlorig__ZN7Fixture5valueEv");
extern "C" int originalValue(void*) {
    if(mode==1)raise(SIGSEGV);
    if(mode==2)_exit(0);
    return 23;
}
static void logline(const char*, ...) {}
''' + short + enough + r'''
static int pair(uint64_t a,uint64_t b) {
    return a==(uint64_t)(uintptr_t)&originalValue && b==(uint64_t)(uintptr_t)ours_1234;
}
int main() {
    tlhybrid_host host={TLHYBRID_ABI_VERSION,logline,pair};
    if(auto_1234(&host)==0)return 1; // Equal but fewer than MIN_COMPLETED cases.
    if(auto_1235(&host)!=0)return 2; // Equal and sufficient completed cases.
    mode=1;if(auto_1235(&host)==0)return 3; // Both crashes: zero completed cases.
    mode=2;if(auto_1235(&host)==0)return 4; // A missing report is never accepted.
    return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="otl-generated-capture-test-") as folder:
            source = Path(folder) / "generated.cpp"
            obj = Path(folder) / "generated.o"
            binary = Path(folder) / "generated"
            source.write_text(text)
            toolchain.compile_source(source, obj, ["-std=gnu++98", "-I", str(toolchain.ROOT / "decomp/hybrid")],
                                     cache=False)
            subprocess.run(["c++", "-no-pie", str(obj), "-o", str(binary)], check=True)
            subprocess.run([str(binary)], check=True, timeout=15, capture_output=True)


if __name__ == "__main__":
    unittest.main()
