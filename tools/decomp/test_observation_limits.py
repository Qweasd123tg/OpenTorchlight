#!/usr/bin/env python3
"""Compile/run actual hand-written observers and reject their old truncation rules.

The game is not needed: complete observer functions are extracted unchanged from
production test sources, then driven at their existing observation boundaries.
OTL_TEST_OBSERVATION_ROOT permits validation of a candidate overlay without
editing the checkout. Each test also runs an isolated old-behavior mutation and
requires it to fail the same controls.
"""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

import toolchain

ROOT = Path(os.environ.get('OTL_TEST_OBSERVATION_ROOT', toolchain.ROOT))
TESTS = ROOT / 'decomp/hybrid/tests'
PRELUDE = r'''
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#define CHECK(x) do { if (!(x)) { std::fprintf(stderr,"line %d: %s\n",__LINE__,#x); return 1; } } while(0)
'''


def function(text, signature):
    """Copy one complete brace-delimited function/loop from these fixed sources."""
    start = text.index(signature)
    brace = text.index('{', start)
    depth = 1
    end = brace + 1
    while depth:
        if text[end] == '{':
            depth += 1
        elif text[end] == '}':
            depth -= 1
        end += 1
    return text[start:end]


class ObservationLimits(unittest.TestCase):
    def compile_run(self, body, success=True):
        with tempfile.TemporaryDirectory(prefix='otl-observation-limits-') as directory:
            directory = Path(directory)
            source, obj, binary = (directory / name for name in ('control.cpp', 'control.o', 'control'))
            source.write_text(PRELUDE + body)
            toolchain.compile_source(source, obj,
                ['-std=gnu++98', '-I', str(toolchain.ROOT / 'decomp/hybrid')], cache=False)
            subprocess.run(['c++', '-no-pie', str(obj), '-o', str(binary)], check=True,
                           capture_output=True, text=True)
            result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=10)
            if success:
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            else:
                self.assertEqual(result.returncode, 1, 'Old behavior was not rejected: ' + result.stdout + result.stderr)

    def test_fake_vtable(self):
        observer = (TESTS / 'FakeVtable.h').read_text()
        control = r'''
int main() {
    fake::Object object; fake::init(object);
    fake::setArguments(0, 2);
    fake::setResult(object, 0, &object);
    fake::Log a,b; a.clear(); b.clear();
    for (int total = fake::kMaxCalls-1; total <= fake::kMaxCalls+1; ++total) {
        a.clear(); b.clear();
        for (int side=0; side<2; ++side) {
            fake::currentLog() = side ? &b : &a;
            for (int i=0; i<total; ++i)
                CHECK(fake::slotThunk<0>(&object, i, i < fake::kMaxCalls ? 7 : side) == &object);
        }
        CHECK(a.count == (total > fake::kMaxCalls ? fake::kMaxCalls : total));
        CHECK(a.count == b.count);
        CHECK(a.overflow == (total > fake::kMaxCalls) && b.overflow == a.overflow);
        CHECK(std::memcmp(a.calls,b.calls,a.count*sizeof(fake::Call)) == 0);
        CHECK((a == b) == (total <= fake::kMaxCalls));
        CHECK((b == a) == (total <= fake::kMaxCalls));
    }
    b.clear(); fake::currentLog() = &b;
    for(int i=0;i<fake::kMaxCalls;++i) fake::slotThunk<0>(&object,i,7);
    CHECK(!(a == b) && !(b == a)); // Only one observation is incomplete.
    a.clear(); b.clear(); CHECK(!a.overflow && !b.overflow && a.count==0 && a==b);
    fake::currentLog()=&a; fake::slotThunk<0>(&object,10,20);
    fake::currentLog()=&b; fake::slotThunk<0>(&object,10,21);
    CHECK(!(a == b)); // Complete differing prefixes remain unequal.
    fake::currentLog()=0; fake::slotThunk<0>(&object,0,0);
    CHECK(a.count==1 && b.count==1);
    return 0;
}
'''
        self.compile_run(observer + control)
        mutant = observer.replace('!overflow && !other.overflow && ', '', 1)
        self.assertNotEqual(mutant, observer)
        self.compile_run(mutant + control, success=False)

    def test_logic_events(self):
        text = (TESTS / 'LogicObjectsTest.cpp').read_text()
        observer = text[text.index('const int kMaxEvents'):text.index('unsigned int g_seed')]
        observer += function(text, 'bool sameLogs()')
        # Both existing call sites must reset overflow, while retaining identity.
        self.assertEqual(text.count('g_logs[0].clear();'), 2)
        self.assertEqual(text.count('g_logs[1].clear();'), 2)
        self.assertNotIn('g_logs[0].count = g_logs[1].count = 0;', text)
        control = r'''
int main() {
    int objects[3]={};
    g_logs[0].object=&objects[0]; g_logs[1].object=&objects[1];
    for(int total=kMaxEvents-1;total<=kMaxEvents+1;++total) {
        for(int side=0;side<2;++side) {
            g_logs[side].clear();
            CHECK(g_logs[side].object==&objects[side]);
            for(int i=0;i<total;++i) recordEvent(&objects[side], i<kMaxEvents ? i : side);
        }
        CHECK(g_logs[0].count==(total>kMaxEvents ? kMaxEvents : total));
        CHECK(g_logs[0].count==g_logs[1].count);
        CHECK(g_logs[0].overflow==(total>kMaxEvents));
        CHECK(g_logs[1].overflow==g_logs[0].overflow);
        CHECK(std::memcmp(g_logs[0].events,g_logs[1].events,g_logs[0].count*sizeof(unsigned int))==0);
        CHECK(sameLogs()==(total<=kMaxEvents));
    }
    g_logs[1].clear();
    for(int i=0;i<kMaxEvents;++i)recordEvent(&objects[1],i);
    CHECK(!sameLogs());
    g_logs[0].clear(); g_logs[1].clear();
    CHECK(!g_logs[0].overflow && !g_logs[1].overflow && sameLogs());
    recordEvent(&objects[2],1); CHECK(sameLogs() && g_logs[0].count==0);
    recordEvent(&objects[0],1); recordEvent(&objects[1],2); CHECK(!sameLogs());
    return 0;
}
'''
        self.compile_run(observer + control)
        mutant = observer.replace('g_logs[0].overflow || g_logs[1].overflow || ', '', 1)
        self.assertNotEqual(mutant, observer)
        self.compile_run(mutant + control, success=False)

    def test_ai_calls(self):
        text = (TESTS / 'AIStatWatcherTest.cpp').read_text()
        observer = text[text.index('struct Call\n'):text.index('struct Node\n')]
        control = r'''
int main() {
    Log a,b; int object;
    for(int total=kMaxCalls-1;total<=kMaxCalls+1;++total) {
        a.clear(); b.clear();
        for(int i=0;i<total;++i) {
            a.add(7,&object).a=i;
            b.add(7,&object).a=i<kMaxCalls ? i : i+1;
        }
        CHECK(a.count==(total>kMaxCalls ? kMaxCalls : total) && a.count==b.count);
        CHECK(a.overflow==(total>kMaxCalls) && b.overflow==a.overflow);
        CHECK(std::memcmp(a.calls,b.calls,a.count*sizeof(Call))==0);
        CHECK(sameLogs(a,b)==(total<=kMaxCalls));
        CHECK(sameLogs(b,a)==(total<=kMaxCalls));
    }
    b.clear(); for(int i=0;i<kMaxCalls;++i)b.add(7,&object).a=i;
    CHECK(!sameLogs(a,b) && !sameLogs(b,a));
    a.clear(); b.clear(); CHECK(!a.overflow && !b.overflow && a.count==0 && sameLogs(a,b));
    a.add(7,&object).f[3]=1; b.add(7,&object).f[3]=2; CHECK(!sameLogs(a,b));
    return 0;
}
'''
        self.compile_run(observer + control)
        mutant = observer.replace('a.overflow || b.overflow || a.count != b.count',
                                  'a.count != b.count || a.overflow != b.overflow', 1)
        self.assertNotEqual(mutant, observer)
        self.compile_run(mutant + control, success=False)

    def test_ai_targets(self):
        text = (TESTS / 'AIStatWatcherTest.cpp').read_text()
        begin = text.index('            TL_CHECK(failures, targetCount[0] == targetCount[1]);')
        end = text.index('            failures += compareWatchers(', begin)
        observer = text[begin:end]
        before = r'''
#include "HybridTest.h"
const int kUnits=6;
static void logline(const char*,...) {}
static tlhybrid_host testHost={TLHYBRID_ABI_VERSION,logline,0};
static const tlhybrid_host* host=&testHost;
static int compareTargets(unsigned int first,unsigned int second,bool change=false) {
    unsigned int targetCount[2]={first,second};
    void* targets[2][kUnits*4]={};
    if(change) targets[1][0]=targets;
    int failures=0;
'''
        after = r'''
    return failures;
}
int main() {
    for(unsigned int total=kUnits*4-1;total<=kUnits*4+1;++total)
        CHECK((compareTargets(total,total)==0)==(total<=kUnits*4));
    CHECK(compareTargets(kUnits*4+1,kUnits*4)>0);
    CHECK(compareTargets(kUnits*4,kUnits*4+1)>0);
    CHECK(compareTargets(1,1,true)>0);
    CHECK(compareTargets(0,0)==0); // A fresh comparison is complete after overflow.
    return 0;
}
'''
        self.compile_run(before + observer + after)
        mutant = observer.replace('            TL_CHECK(failures, targetCount[0] <= kUnits * 4);\n', '', 1)
        mutant = mutant.replace('            TL_CHECK(failures, targetCount[1] <= kUnits * 4);\n', '', 1)
        self.assertNotEqual(mutant, observer)
        self.compile_run(before + mutant + after, success=False)

    def test_gameui_lists(self):
        text = (TESTS / 'GameUICreateTest.cpp').read_text()
        observer = r'''
#include "AutoTest.h"
#include "TextEvent.h"
#include "TLinkedList.h"
static autotest::Capture* cap;
static char game[0x2000];
static const void* identities[1024]; static unsigned identityCount;
'''
        observer += function(text, 'template<class T>T& field(') + '\n'
        observer += function(text, 'static void n(') + '\n'
        observer += function(text, 'static void ptr(') + '\n'
        observer += 'static void snapshotLists() {' + function(text, 'for(unsigned off=0x1698;') + '}\n'
        control = r'''
static void logline(const char* fmt,...) { va_list args; va_start(args,fmt); std::vfprintf(stderr,fmt,args); va_end(args); }
static int pair(uint64_t a,uint64_t b) { return a==1 && b==2; }
static tlhybrid_host host={TLHYBRID_ABI_VERSION,logline,pair};
static autotest::Outcome outcomes[2];
static TLinkedListNode<CTextEvent*> nodes[102];
static unsigned long long eventStorage[sizeof(CTextEvent)/8+1];
static CTextEvent* event=reinterpret_cast<CTextEvent*>(eventStorage);
static void observe(int total,int side,bool cycle=false) {
    autotest::Outcome& out=outcomes[side];
    out.childStatus=0; out.reportStarted=true; out.reportValid=true;
    out.capture.reset(); out.capture.callStarted=out.capture.callCompleted=1; out.capture.callTarget=side+1;
    cap=&out.capture; identityCount=1; identities[0]=event;
    event->m_pWindow=0;
    for(int i=0;i<total;++i) {
        nodes[i].m_Data=event;
        nodes[i].m_pPrevious=i ? &nodes[i-1] : 0;
        nodes[i].m_pNext=i+1<total ? &nodes[i+1] : 0;
    }
    // Two differing tails have identical observed prefixes. The tail's data is
    // never dereferenced: the actual loop stops after 101 nodes.
    if(total>101 && side) nodes[101].m_Data=0;
    if(cycle && total) nodes[total-1].m_pNext=&nodes[total-1];
    TLinkedListNode<CTextEvent*>* head=total ? nodes : 0;
    field<void*>(game,0x1698)=&head; field<void*>(game,0x16a0)=&head;
    snapshotLists();
}
int main() {
    for(int total=100;total<=102;++total) {
        observe(total,0); observe(total,1);
        const autotest::Capture& a=outcomes[0].capture; const autotest::Capture& b=outcomes[1].capture;
        CHECK(a.issue==(total>101 ? autotest::Capture::Overflow : autotest::Capture::Complete));
        CHECK(b.issue==a.issue);
        CHECK(a.length==b.length && std::memcmp(a.data,b.data,a.length)==0);
        autotest::Coverage coverage("list-boundary",1);
        CHECK(coverage.observe(&host,outcomes[0],outcomes[1])==(total>101 ? 2 : 0));
        CHECK(coverage.completed==(total>101 ? 0u : 1u));
        CHECK(coverage.missing==(total>101 ? 1u : 0u));
    }
    observe(101,1); CHECK(autotest::incomplete(outcomes[0]) && !autotest::incomplete(outcomes[1]));
    autotest::Coverage mixed("list-mixed",1); CHECK(mixed.observe(&host,outcomes[0],outcomes[1])==2);
    observe(101,0,true); observe(101,1,true);
    autotest::Coverage cycle("list-cycle",1); CHECK(cycle.observe(&host,outcomes[0],outcomes[1])==2);
    observe(0,0); observe(0,1);
    autotest::Coverage reset("list-reset",1); CHECK(reset.observe(&host,outcomes[0],outcomes[1])==0);
    CHECK(outcomes[0].capture.issue==autotest::Capture::Complete);
    observe(100,0); observe(101,1);
    autotest::Coverage changed("list-changed",1); CHECK(changed.observe(&host,outcomes[0],outcomes[1])==1);
    return 0;
}
'''
        self.compile_run(observer + control)
        mutant = observer.replace('if(p)cap->issue=autotest::Capture::Overflow;', '', 1)
        self.assertNotEqual(mutant, observer)
        self.compile_run(mutant + control, success=False)

    def test_astar_stack(self):
        text = (TESTS / 'AstarPathfinderTest.cpp').read_text()
        observer = r'''
#include "AstarPathfinder.h"
#include <malloc.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
typedef CAstarPathfinder Pathfinder;
typedef Pathfinder::CAstarNode Node;
typedef Pathfinder::NodeStack Stack;
'''
        observer += text[text.index('struct Context\n'):text.index('void execute(')]
        # Exercise capture with the real child pipe/reset/status implementation;
        # the original game operation is intentionally not part of these controls.
        observer += 'void execute(Context& c,bool,Snapshot& out) { capture(c,out); }\n'
        observer += function(text, 'void crashed(') + '\n'
        observer += function(text, 'int run(') + '\n'
        control = r'''
int main() {
    Context c={}; Node node={},tail={}; Stack stack[102]={};
    tail.m_iTile=1;
    Pathfinder* p=static_cast<Pathfinder*>(std::calloc(1,sizeof(Pathfinder)));
    CHECK(p); c.path=p; c.nodes[0]=&node; p->m_pStack=stack;
    static Snapshot a,b;
    for(int total=99;total<=101;++total) {
        for(int i=0;i<=total;++i) { stack[i].m_pNode=&node; stack[i].m_pNext=i<total ? &stack[i+1] : 0; }
        int statusA=run(c,true,a);
        if(total>100) stack[total].m_pNode=&tail; // Differ only in the omitted tail.
        int statusB=run(c,false,b);
        CHECK(WIFEXITED(statusA) && WIFEXITED(statusB));
        CHECK(WEXITSTATUS(statusA)==(total>100 ? 6 : 0));
        CHECK(WEXITSTATUS(statusB)==(total>100 ? 6 : 0));
        // This is the exact status prerequisite in the production comparison.
        CHECK((statusA==0 && statusB==0)==(total<=100));
        if(total<=100) {
            CHECK(a.size==125u+4u*total && a.size==b.size);
            CHECK(std::memcmp(a.bytes,b.bytes,a.size)==0);
        }
    }
    // Reusing the output after an incomplete child must reset, not append.
    stack[99].m_pNext=0;
    CHECK(run(c,true,a)==0 && run(c,false,b)==0);
    CHECK(a.size==521 && a.size==b.size && std::memcmp(a.bytes,b.bytes,a.size)==0);
    stack[99].m_pNext=&stack[100]; stack[100].m_pNext=&stack[100];
    int cycleStatus=run(c,true,a);
    CHECK(WIFEXITED(cycleStatus) && WEXITSTATUS(cycleStatus)==6); // Bounded cycle is incomplete too.
    std::free(p);
    return 0;
}
'''
        self.compile_run(observer + control)
        mutant = observer.replace('if (entry)\n        _exit(6);', '', 1)
        self.assertNotEqual(mutant, observer)
        self.compile_run(mutant + control, success=False)


if __name__ == '__main__':
    unittest.main()
