#!/usr/bin/env python3
"""Compile actual bounded spies with GCC 4.4.7; reject every unobserved tail.

Run with the normal pinned toolchain environment:
    python3 tools/decomp/test_remaining_observation_completeness.py
OTL_REMAINING_OBSERVER_ROOT optionally selects a candidate tree for the eleven
handwritten test sources. AutoTest.h and toolchain configuration stay repository-
local. These observer-only controls do not invoke any original game function.
"""
from pathlib import Path
import os
import subprocess
import tempfile
import unittest

import toolchain

TEST_ROOT = Path(os.environ.get("OTL_REMAINING_OBSERVER_ROOT", str(toolchain.ROOT)))
STRING_FIXTURES = (
    "StashMenuCreateResourceTest", "MerchantMenuCreateResourceTest", "InventoryCreateTest",
    "StatsMenuCreateTest", "JournalCreateTest", "PetCreateTest", "SkillMenuCreateTest",
    "EnchantCreateTest", "CombineCreateTest",
)

FIXTURE = r'''
#include <cstdio>
#include <cstring>
#include <limits>
#include <vector>
#include <sys/mman.h>
#include "AutoTest.h"
namespace autotest {
char g_arena[kArenaSize]; size_t g_arenaUsed; Pool g_pool; Outcome g_outcomes[2];
}
#define CHECK(x) do { if (!(x)) { std::fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while (0)
static uint64_t expectedOriginal, expectedReplacement;
static int pair(uint64_t a, uint64_t b) {
    return a == expectedOriginal && b == expectedReplacement && a != b;
}
static void logline(const char*, ...) {}
static tlhybrid_host host = {TLHYBRID_ABI_VERSION, logline, pair};
static bool receipt(autotest::Body a, autotest::Body b, void* input,
                    uint64_t original, uint64_t replacement, unsigned complete,
                    unsigned different, unsigned missing) {
    expectedOriginal = original; expectedReplacement = replacement;
    autotest::Outcome left, right;
    autotest::runChild(a, input, left);
    autotest::runChild(b, input, right);
    autotest::Coverage coverage("observer-limits", original);
    int result = coverage.observe(&host, left, right);
    return result == (missing ? 2 : different ? 1 : 0) &&
        coverage.completed == complete && coverage.different == different &&
        coverage.missing == missing && left.reportValid && right.reportValid;
}
// Each buffer is genuinely readable through its budget and PROT_NONE afterwards.
struct GuardedText {
    void* mapping;
    size_t mappingBytes;
    wchar_t* text;
    GuardedText(size_t count) : mapping(MAP_FAILED), mappingBytes(0), text(0) {
        size_t page = static_cast<size_t>(sysconf(_SC_PAGESIZE));
        size_t bytes = count * sizeof(wchar_t);
        size_t readable = (bytes + page - 1) / page * page;
        mappingBytes = readable + page;
        mapping = mmap(0, mappingBytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (mapping == MAP_FAILED) return;
        if (mprotect(static_cast<char*>(mapping) + readable, page, PROT_NONE)) {
            munmap(mapping, mappingBytes); mapping = MAP_FAILED; return;
        }
        text = reinterpret_cast<wchar_t*>(static_cast<char*>(mapping) + readable - bytes);
    }
    ~GuardedText() { if (mapping != MAP_FAILED) munmap(mapping, mappingBytes); }
};

// @TELEPORT@
namespace teleport {
std::vector<unsigned int> trace;
unsigned int gTraceOverflow;
unsigned int who(void* p) { return p ? 1 : 0; }
// @TELEPORT_FUNCTIONS@
struct Input { unsigned int leftCount, rightCount, leftTail, rightTail; };
autotest::Capture* cap;
void fill(unsigned int count, unsigned int tail) {
    resetTrace();
    for (unsigned i = 0; i < count; ++i) record(i+1 == count ? tail : 7, 0);
    captureTrace(*cap);
}
void original(Input* input) { fill(input->leftCount, input->leftTail); }
void restored(Input* input) { fill(input->rightCount, input->rightTail); }
void a(void* input, autotest::Capture& out) { cap=&out; autotest::invoke(out,&original,static_cast<Input*>(input)); }
void b(void* input, autotest::Capture& out) { cap=&out; autotest::invoke(out,&restored,static_cast<Input*>(input)); }
int run() {
    const unsigned maxEvents = 4096 / 6; // 4092 words; the final four cannot hold an event.
    Input input = {maxEvents, maxEvents, 9, 9};
    autotest::Outcome observedA, observedB;
    autotest::runChild(a,&input,observedA);autotest::runChild(b,&input,observedB);
    CHECK(sameTraceObservation(observedA,observedB));
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,1,0,0));
    input.rightTail=10;
    autotest::runChild(a,&input,observedA);autotest::runChild(b,&input,observedB);
    CHECK(!sameTraceObservation(observedA,observedB));
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,1,1,0));
    input.leftCount=input.rightCount=maxEvents+1;
    autotest::runChild(a,&input,observedA);autotest::runChild(b,&input,observedB);
    CHECK(!sameTraceObservation(observedA,observedB));
    CHECK(observedA.capture.issue==autotest::Capture::Overflow && observedB.capture.issue==autotest::Capture::Overflow);
    // A nominally successful legacy wait status must never override an incomplete capture.
    observedA.status=observedB.status=0;
    CHECK(!sameTraceObservation(observedA,observedB));
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,0,0,1));
    input.rightTail=input.leftTail;
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,0,0,1));
    input.leftCount=maxEvents;
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,0,0,1));
    autotest::Capture first, second;
    first.reset();cap=&first;fill(maxEvents+1,11);
    second.reset();cap=&second;fill(maxEvents+1,12);
    CHECK(first.issue==first.Overflow && second.issue==second.Overflow);
    CHECK(first.length==second.length && !std::memcmp(first.data,second.data,first.length));
    CHECK(trace.size()==maxEvents*6 && gTraceOverflow==1);
    gTraceOverflow=std::numeric_limits<unsigned int>::max();record(13,0);
    CHECK(gTraceOverflow==std::numeric_limits<unsigned int>::max());
    resetTrace(); CHECK(trace.empty() && !gTraceOverflow);
    first.reset();cap=&first;fill(1,17);
    CHECK(first.issue==first.Complete && trace.size()==6 && !gTraceOverflow);
    first.reset(); first.issue=first.UnsupportedPointer; captureTrace(first);
    CHECK(first.issue==first.UnsupportedPointer);
    input.leftCount=input.rightCount=1;
    input.leftTail=input.rightTail=7;
    autotest::runChild(a,&input,observedA);autotest::runChild(b,&input,observedB);
    CHECK(sameTraceObservation(observedA,observedB));
    observedA.reportValid=false; CHECK(!sameTraceObservation(observedA,observedB));
    std::puts("PASS Teleport: 682/683 events, complete difference, equal discarded prefixes, one-side overflow, reset, saturation, incomplete receipts");
    return 0;
}
}

namespace deletion {
// @DELETION_FUNCTIONS@
int run() {
    DeletionLog a,b;
    CHECK(a.complete() && b.complete() && sameDeletionLog(a,b));
    for(unsigned i=0;i<31;++i) { a.add(i);b.add(i); }
    CHECK(a.complete() && sameDeletionLog(a,b));
    a.add(31);b.add(31);
    CHECK(a.total==32 && a.stored==32 && a.complete() && sameDeletionLog(a,b));
    b.ids[31]=90;CHECK(!sameDeletionLog(a,b));b.ids[31]=31;
    b.add(32); CHECK(!sameDeletionLog(a,b));
    a.add(99);CHECK(a.total==33 && b.total==33 && a.stored==32 && b.stored==32);
    CHECK(!std::memcmp(a.ids,b.ids,sizeof(a.ids)));
    CHECK(a.overflow && b.overflow && !sameDeletionLog(a,b));
    a.reset();b.reset();a.add(5);b.add(5);
    CHECK(a.total==1 && a.stored==1 && !a.overflow && sameDeletionLog(a,b));
    a.total=static_cast<size_t>(-1);a.add(2);
    CHECK(a.total==static_cast<size_t>(-1) && a.overflow && !sameDeletionLog(a,b));
    a.reset();b.reset();a.stored=b.stored=33;a.total=b.total=33;
    CHECK(!sameDeletionLog(a,b)); // No byte comparison with an invalid stored count.
    a.reset();b.reset();a.total=b.total=33;
    CHECK(!sameDeletionLog(a,b)); // Equal totals cannot conceal missing stored IDs.
    std::puts("PASS FileSystem: 0/31/32/33 deletions, complete difference, identical-prefix different-tail, one-side overflow, reset, saturation, invalid counts");
    return 0;
}
}

// @STRING_NAMESPACES@
int main() {
    CHECK(teleport::run()==0);
    CHECK(deletion::run()==0);
    // @STRING_RUNS@
    return 0;
}
'''

STRING_FIXTURE = r'''
namespace @NAMESPACE@ {
autotest::Capture* cap;
class CResourceManager {};
class CGenericModel {};
namespace Ogre { class SceneManager {}; }
struct Menu {
    CResourceManager* m_pResourceManager;
    Ogre::SceneManager* m_pUnknown78;
    Ogre::SceneManager* m_pInventorySceneManager;
    Ogre::SceneManager* m_pSceneManager;
    Ogre::SceneManager* m_pPetSceneManager;
};
Menu menuStorage = {};
Menu* menu = &menuStorage;
CGenericModel modelStorage;
CGenericModel* model = &modelStorage;
void number(int value) { cap->add(&value,sizeof(value)); }
// @STRING_FUNCTION@
// @CREATE_FUNCTION@
struct Input { const wchar_t* left; const wchar_t* right; };
void original(const wchar_t* s) { create(0,0,s,L"",false,false,false); }
void restored(const wchar_t* s) { create(0,0,s,L"",false,false,false); }
void originalSecond(const wchar_t* s) { create(0,0,L"",s,false,false,false); }
void restoredSecond(const wchar_t* s) { create(0,0,L"",s,false,false,false); }
void a(void* input,autotest::Capture& out) { cap=&out;autotest::invoke(out,&original,static_cast<Input*>(input)->left); }
void b(void* input,autotest::Capture& out) { cap=&out;autotest::invoke(out,&restored,static_cast<Input*>(input)->right); }
void aSecond(void* input,autotest::Capture& out) { cap=&out;autotest::invoke(out,&originalSecond,static_cast<Input*>(input)->left); }
void bSecond(void* input,autotest::Capture& out) { cap=&out;autotest::invoke(out,&restoredSecond,static_cast<Input*>(input)->right); }
int run() {
    GuardedText guarded(1024), last(1);
    CHECK(guarded.text && last.text);
    for(unsigned i=0;i<1024;++i) guarded.text[i]=L'x';
    last.text[0]=0;
    autotest::Capture capture;
    capture.reset();cap=&capture;modelText(last.text);
    CHECK(capture.issue==capture.Complete && capture.length==sizeof(int));
    int value=1;std::memcpy(&value,capture.data,sizeof(value));CHECK(value==0);
    // The terminator at the very last readable element is complete.
    guarded.text[1023]=0;
    capture.reset();modelText(guarded.text);
    CHECK(capture.issue==capture.Complete && capture.length==1024*sizeof(int));
    Input input={guarded.text,guarded.text};
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,1,0,0));
    CHECK(receipt(aSecond,bSecond,&input,(uint64_t)(uintptr_t)&originalSecond,(uint64_t)(uintptr_t)&restoredSecond,1,0,0));
    guarded.text[1023]=L'x';
    capture.reset();cap=&capture;modelText(guarded.text);
    CHECK(capture.issue==capture.Overflow && capture.length==1024*sizeof(int));
    // Both readable buffers have equal prefixes but unobserved differing tails.
    wchar_t left[1026],right[1026];
    for(unsigned i=0;i<1024;++i) left[i]=right[i]=L'x';
    left[1024]=L'A';right[1024]=L'B';left[1025]=right[1025]=0;
    input.left=left;input.right=right;
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,0,0,1));
    CHECK(receipt(aSecond,bSecond,&input,(uint64_t)(uintptr_t)&originalSecond,(uint64_t)(uintptr_t)&restoredSecond,0,0,1));
    input.right=left;
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,0,0,1));
    input.left=last.text;input.right=guarded.text;
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,0,0,1));
    input.left=L"a";input.right=L"b";
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,1,1,0));
    left[1023]=right[1023]=0;input.left=left;input.right=right;
    CHECK(receipt(a,b,&input,(uint64_t)(uintptr_t)&original,(uint64_t)(uintptr_t)&restored,1,0,0));
    capture.reset();cap=&capture;modelText(last.text);
    CHECK(capture.issue==capture.Complete && capture.length==sizeof(int));
    capture.reset();modelText(0);CHECK(capture.issue==capture.UnsupportedPointer);
    modelText(guarded.text+1024);CHECK(capture.issue==capture.UnsupportedPointer); // Must not touch PROT_NONE after an issue.
    capture.reset();capture.length=capture.kSize;modelText(last.text);
    CHECK(capture.issue==capture.Overflow && capture.length==capture.kSize);
    modelText(guarded.text+1024); // Must not read after Capture's own overflow either.
    std::puts("PASS @NAMESPACE@: guarded 0/1023-character strings, 1024-character exhaustion, complete difference, equal-prefix tails, both model arguments, both/one-side overflow, reset, incomplete receipts");
    return 0;
}
}
'''


def definition(text, signature):
    """Extract a balanced C++ definition, retaining its actual implementation."""
    start = text.index(signature)
    end = text.index("{", start) + 1
    level = 1
    while level:
        level += (text[end] == "{") - (text[end] == "}")
        end += 1
    return text[start:end]


def regression_source():
    tests = TEST_ROOT / "decomp/hybrid/tests"
    teleport = (tests / "TeleportTest.cpp").read_text()
    filesystem = (tests / "FileSystemTest.cpp").read_text()
    # Assert the real fixtures use the bodies exercised below.
    assert "    captureTrace(out);" in teleport
    assert "    resetTrace();" in teleport
    assert "bool ok = sameTraceObservation(a, b);" in teleport
    assert "!autotest::incomplete(a) && !autotest::incomplete(b)" in teleport
    assert "sameDeletionLog(logs[0], logs[1])" in filesystem
    assert "g_deleted.reset();" in filesystem
    assert "g_deleted.add(self->id);" in filesystem
    source = FIXTURE.replace("// @TELEPORT_FUNCTIONS@", "\n".join(
        definition(teleport, signature) for signature in
        ("void record(", "void resetTrace()", "void captureTrace(", "bool sameTraceObservation(")))
    source = source.replace("// @DELETION_FUNCTIONS@",
                            definition(filesystem, "struct DeletionLog") + ";\n" +
                            definition(filesystem, "bool sameDeletionLog("))
    strings, calls = [], []
    for name in STRING_FIXTURES:
        text = (tests / (name + ".cpp")).read_text()
        assert "modelText(a);number(-7);modelText(b);" in text
        assert "coverage.observe(host,u,v)" in text
        strings.append(STRING_FIXTURE.replace("@NAMESPACE@", name)
                       .replace("// @STRING_FUNCTION@", definition(text, "void modelText("))
                       .replace("// @CREATE_FUNCTION@", definition(text, "CGenericModel* create(")))
        calls.append("CHECK(" + name + "::run()==0);")
    return source.replace("// @STRING_NAMESPACES@", "\n".join(strings)).replace(
        "// @STRING_RUNS@", "\n".join(calls))


class RemainingObservationCompleteness(unittest.TestCase):
    def test_actual_observers_and_incomplete_receipts(self):
        with tempfile.TemporaryDirectory(prefix="otl-remaining-observers-") as folder:
            folder = Path(folder)
            source, obj, binary = [folder / name for name in
                                   ("observers.cpp", "observers.o", "observers")]
            source.write_text(regression_source())
            toolchain.compile_source(source, obj, ["-std=gnu++98", "-I",
                                     str(toolchain.ROOT / "decomp/hybrid")], cache=False)
            comment = subprocess.run(["readelf", "-p", ".comment", str(obj)],
                                     check=True, capture_output=True, text=True).stdout
            self.assertIn(toolchain.EXPECTED_COMMENT, comment)
            subprocess.run(["c++", "-no-pie", str(obj), "-o", str(binary)], check=True)
            result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            print(result.stdout, end="")


if __name__ == "__main__":
    unittest.main()
