#include <new>
#include <malloc.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#ifndef DETOUR_HEADER
#define DETOUR_HEADER "Detour.h"
#endif
#include DETOUR_HEADER

// These deliberately synthetic functions are the only code patched or executed.
// Separate pages make the exact LIFO order independently observable at mprotect.
#define PROOF_PAGE_BYTES 4096
#define PROOF_LARGE_SITES 4097
#define PROOF_ARENA_BYTES ((PROOF_LARGE_SITES + 4) * PROOF_PAGE_BYTES)
#define PROOF_STRINGIFY_INNER(x) #x
#define PROOF_STRINGIFY(x) PROOF_STRINGIFY_INNER(x)
enum { kPage = PROOF_PAGE_BYTES, kLarge = PROOF_LARGE_SITES, kSites = kLarge + 4,
       kArenaBytes = PROOF_ARENA_BYTES, kEvents = kSites * 8 };
extern "C" {
unsigned char proofArena[kArenaBytes] __attribute__((aligned(PROOF_PAGE_BYTES)));
}
asm(".globl __tlhybrid_text_start\n.set __tlhybrid_text_start, proofArena\n"
    ".globl __tlhybrid_text_end\n.set __tlhybrid_text_end, proofArena + " PROOF_STRINGIFY(PROOF_ARENA_BYTES) "\n");

static unsigned char originalCode[] = {0xb8, 17, 0, 0, 0, 0xc3};
static bool observing = false;
static int mapCalls, unmapCalls, protectCalls, allocatorCalls;
static int failMapAt, failUnmapAt, failProtectAt;
static bool failProtectAlways;
static bool auditRestoreFailure;
static int auditPending, auditTotal;
struct Event { uintptr_t at; size_t bytes; int prot; bool success; };
static Event events[kEvents];
static int eventCount;
static void* leaked;
static size_t leakedBytes;
static unsigned char* site(int i) { return proofArena + i * kPage; }
static void require(bool condition, const char* message)
{
    if (!condition) { std::fprintf(stderr, "FAIL: %s\n", message); std::exit(1); }
}
extern "C" void* __real_mmap(void*, size_t, int, int, int, off_t);
extern "C" int __real_munmap(void*, size_t);
extern "C" int __real_mprotect(void*, size_t, int);
extern "C" void* __real_malloc(size_t);
extern "C" void* __real_calloc(size_t, size_t);
extern "C" void* __real_realloc(void*, size_t);
extern "C" void __real_free(void*);
extern "C" void* __wrap_mmap(void* at, size_t bytes, int prot, int flags, int fd, off_t off)
{
    if (observing && ++mapCalls == failMapAt) { errno = ENOMEM; return MAP_FAILED; }
    return __real_mmap(at, bytes, prot, flags, fd, off);
}
extern "C" int __wrap_munmap(void* at, size_t bytes)
{
    if (observing && ++unmapCalls == failUnmapAt)
    {
        leaked = at; leakedBytes = bytes; errno = EINVAL; return -1;
    }
    return __real_munmap(at, bytes);
}
extern "C" int __wrap_mprotect(void* at, size_t bytes, int prot)
{
    if (!observing) return __real_mprotect(at, bytes, prot);
    ++protectCalls;
    bool fail = failProtectAlways || protectCalls == failProtectAt;
    int result;
    if (fail)
    {
        if (auditRestoreFailure)
        {
            for (int i = 0; i < auditPending; ++i)
                require(site(i)[0] == 0xe9, "earlier restoration records must still be live");
            for (int i = auditPending + 1; i < auditTotal; ++i)
                require(std::memcmp(site(i), originalCode, sizeof(originalCode)) == 0, "later restoration records already restored");
            if (protectCalls % 2)
                require(site(auditPending)[0] == 0xe9, "failed writable transition retains current jump");
            else
                require(std::memcmp(site(auditPending), originalCode, sizeof(originalCode)) == 0, "failed protection reset follows restored bytes");
        }
        errno = EACCES; result = -1;
    }
    else result = __real_mprotect(at, bytes, prot);
    require(eventCount < kEvents, "proof event storage must not overflow");
    Event e = { (uintptr_t)at, bytes, prot, result == 0 }; events[eventCount++] = e;
    return result;
}
extern "C" void* __wrap_malloc(size_t n) { if (observing) ++allocatorCalls; return __real_malloc(n); }
extern "C" void* __wrap_calloc(size_t n, size_t z) { if (observing) ++allocatorCalls; return __real_calloc(n, z); }
extern "C" void* __wrap_realloc(void* p, size_t n) { if (observing) ++allocatorCalls; return __real_realloc(p, n); }
extern "C" void __wrap_free(void* p) { if (observing) ++allocatorCalls; __real_free(p); }
// Executable-owned new/delete detect any future switch to a C++ container.
void* operator new(size_t n) throw(std::bad_alloc)
{
    if (observing) ++allocatorCalls;
    void* p = __real_malloc(n); if (!p) std::abort(); return p;
}
void* operator new[](size_t n) throw(std::bad_alloc) { return ::operator new(n); }
void operator delete(void* p) throw() { if (observing) ++allocatorCalls; __real_free(p); }
void operator delete[](void* p) throw() { ::operator delete(p); }

static int fakeCalls;
static int fake() { ++fakeCalls; return 73; }
static int otherFake() { return 91; }
static int invoke(int i) { return reinterpret_cast<int (*)()>(site(i))(); }
static bool original(int i) { return std::memcmp(site(i), originalCode, sizeof(originalCode)) == 0; }
static void resetObservation()
{
    observing = true; mapCalls = unmapCalls = protectCalls = allocatorCalls = eventCount = 0;
    fakeCalls = 0;
    failMapAt = failUnmapAt = failProtectAt = 0; failProtectAlways = false; auditRestoreFailure = false;
    leaked = 0; leakedBytes = 0;
}
static void resetEvents() { eventCount = protectCalls = 0; }
static void addSites(detour::Set& set, int count)
{
    for (int i = 0; i < count; i += 2)
        set.redirect((char*)site(i), (char*)site(i + (i + 1 < count ? 1 : 0)), &fake);
}
static void checkRestored(int count)
{
    for (int i = 0; i < count; ++i)
    {
        require(original(i), "all original bytes must be restored");
        require(invoke(i) == 17, "restored function result");
    }
}
static void checkReverseEvents(int count, int start = 0)
{
    require(eventCount == start + count * 2, "exact number of restoration protection changes");
    for (int i = 0; i < count; ++i)
    {
        const Event& write = events[start + i * 2];
        const Event& back = events[start + i * 2 + 1];
        require(write.at == (uintptr_t)site(count - 1 - i), "reverse restoration site order");
        require(back.at == write.at && write.bytes == kPage && back.bytes == kPage, "exact restored page extent");
        require(write.prot == (PROT_READ | PROT_WRITE | PROT_EXEC) && back.prot == (PROT_READ | PROT_EXEC), "restore original protection");
        require(write.success && back.success, "restoration permissions succeeded");
    }
}
static void growth(int count)
{
    require(count > 0 && count <= kLarge, "requested count fits the explicit synthetic fixture");
    resetObservation();
    int heapBefore = mallinfo().uordblks;
    {
        detour::Set set;
        addSites(set, count);
        require(!set.failed(), "requested patch count must fit");
        for (int i = 0; i < count; ++i)
        {
            require(site(i)[0] == 0xe9 && invoke(i) == 73, "every original and linked address must reach fake");
            require(site(i)[5] == originalCode[5], "patch must change only the five-byte prefix");
            int32_t actual; std::memcpy(&actual, site(i) + 1, sizeof(actual));
            require(actual == (int64_t)(uintptr_t)&fake - (int64_t)((uintptr_t)site(i) + 5), "exact rel32 target");
        }
        require(fakeCalls == count, "patching itself must not invoke captured collaborator callbacks");
        require(mallinfo().uordblks == heapBefore, "growth must not change captured mallinfo heap bytes");
        require(mapCalls == (count - 1) / 64, "one allocation for each added storage chunk");
        int maps = mapCalls, protects = protectCalls;
        // Same address, repeated pair and cross-block aliases retain first fake.
        for (int i = count - 1; i >= 0; --i)
            set.redirect((char*)site(i), (char*)site((i + 1) % count), &otherFake);
        require(!set.failed() && maps == mapCalls && protects == protectCalls, "dedup must neither allocate nor rewrite");
        for (int i = 0; i < count; ++i) require(invoke(i) == 73, "aliases preserve first installed target");
        require(allocatorCalls == 0, "growth must not invoke application heap callbacks");
        resetEvents(); set.restore();
        require(!set.failed(), "successful restoration");
        checkReverseEvents(count); checkRestored(count);
        require(unmapCalls == mapCalls, "all spill mappings released");
        int n = eventCount; set.restore(); require(eventCount == n, "restore idempotent");
    }
    require(allocatorCalls == 0, "storage lifecycle must avoid application heap callbacks");
    observing = false;
}
#ifndef BASELINE_PROOF
static void storageFailure(int boundary, bool splitPair)
{
    resetObservation();
    detour::Set set; addSites(set, boundary);
    require(!set.failed(), "pre-failure full chunks");
    failMapAt = mapCalls + 1;
    int protects = protectCalls;
    if (splitPair)
        set.redirect((char*)site(boundary - 1), (char*)site(boundary), &fake);
    else set.redirect((char*)site(boundary), (char*)site(boundary), &fake);
    require(set.failed() && set.failure() == detour::Set::StorageFailure, "insufficient storage must be explicit failure");
    require(set.failureSite() == site(boundary), "allocation failure site");
    require(original(boundary) && protectCalls == protects, "allocation failure precedes all code writes");
    set.redirect((char*)site(boundary + 1), (char*)site(boundary + 1), &fake);
    require(original(boundary + 1) && protectCalls == protects, "failed set stops later redirects");
    resetEvents(); set.restore(); checkReverseEvents(boundary); checkRestored(boundary + 2);
    require(set.failed(), "restore must not clear failure evidence");
    require(allocatorCalls == 0, "failure must not invoke application allocator");
    observing = false;
}
static void newPairStorageFailure()
{
    resetObservation(); detour::Set set; addSites(set, 63);
    require(!set.failed(), "pair-boundary setup"); failMapAt = 1;
    set.redirect((char*)site(63), (char*)site(64), &fake);
    require(set.failed() && set.failure() == detour::Set::StorageFailure, "partially installed new pair must report failure");
    require(invoke(63) == 73 && original(64), "first pair half installed, second untouched on exhaustion");
    require(set.failureSite() == site(64), "linked half storage failure site");
    resetEvents(); set.restore(); checkReverseEvents(64); checkRestored(65);
    observing = false;
}
static void installFailure(int failAt)
{
    resetObservation();
    detour::Set set; failProtectAt = failAt;
    set.redirect((char*)site(0), (char*)site(1), &fake);
    require(set.failed() && set.failure() == detour::Set::ProtectionFailure, "install protection failure");
    require(set.failureSite() == site(0), "install protection failure site");
    require(original(1), "linked site cannot be patched after original failure");
    require(failAt == 2 ? invoke(0) == 73 : original(0), "installed jump retained only if bytes written");
    failProtectAt = 0; resetEvents(); set.restore();
    checkRestored(2); require(set.failed(), "failure stays sticky after successful rollback");
    require(eventCount == (failAt == 2 ? 2 : 0), "only installed entries are restored");
    observing = false;
}
static void restoreFailure(int failureAt, bool destructorOnly)
{
    pid_t pid = fork(); require(pid >= 0, "fork");
    if (pid == 0)
    {
        struct rlimit limit = {0, 0}; setrlimit(RLIMIT_CORE, &limit);
        resetObservation();
        {
            detour::Set set; addSites(set, 130); require(!set.failed(), "restoration failure setup");
            resetEvents(); failProtectAt = failureAt;
            auditRestoreFailure = true; auditTotal = 130;
            auditPending = 129 - (failureAt - 1) / 2;
            if (!destructorOnly)
            {
                set.restore();
                _exit(91); // Must never execute after an unsuccessful restore().
            }
        }
        _exit(92); // Must never execute after an unsuccessful destructor.
    }
    int status; require(waitpid(pid, &status, 0) == pid, "waitpid");
    require(WIFSIGNALED(status) && WTERMSIG(status) == SIGABRT,
            "failed restoration must abort before any following statement");
}
static void reuseAfterRestore()
{
    resetObservation();
    detour::Set set; addSites(set, 65); require(!set.failed(), "reuse initial spill");
    set.restore(); checkRestored(65);
    set.redirect((char*)site(0), (char*)site(1), &otherFake);
    require(!set.failed() && invoke(0) == 91 && invoke(1) == 91, "reused set records fresh target and backups");
    resetEvents(); set.restore(); checkReverseEvents(2); checkRestored(65);
    addSites(set, 129); require(!set.failed(), "reused set grows again after storage release");
    resetEvents(); set.restore(); checkReverseEvents(129); checkRestored(129);
    require(mapCalls == unmapCalls && allocatorCalls == 0, "reused set releases all storage without heap calls");
    observing = false;
}
static void releaseFailure()
{
    resetObservation();
    {
        detour::Set set; addSites(set, 130); require(!set.failed(), "release setup");
        failUnmapAt = 1; resetEvents(); set.restore();
        require(set.failed() && set.failure() == detour::Set::StorageReleaseFailure, "release failure reported");
        checkReverseEvents(130); checkRestored(130);
        require(unmapCalls == 2 && leaked != 0, "release failure must not block earlier storage or patches");
    }
    require(__real_munmap(leaked, leakedBytes) == 0, "proof cleans deliberate mapping leak");
    observing = false;
}
static void destructorReleaseFailure()
{
    resetObservation();
    {
        detour::Set set; addSites(set, 130); require(!set.failed(), "destructor release setup");
        failUnmapAt = 1; resetEvents();
    }
    checkReverseEvents(130); checkRestored(130);
    require(unmapCalls == 2 && leaked != 0, "destructor may return only with no live backups in leaked block");
    require(__real_munmap(leaked, leakedBytes) == 0, "proof cleans destructor-only empty storage leak");
    observing = false;
}
static void relativeRange(int64_t delta, bool valid)
{
    resetObservation();
    detour::Set set;
    void* target = reinterpret_cast<void*>((uintptr_t)site(0) + 5 + delta);
    set.redirect((char*)site(0), (char*)site(0), target);
    require(set.failed() != valid, "rel32 signed boundary status");
    if (valid)
    {
        int32_t stored; std::memcpy(&stored, site(0) + 1, sizeof(stored));
        require(site(0)[0] == 0xe9 && stored == delta, "exact rel32 boundary bytes");
    }
    else require(original(0) && protectCalls == 0 && mapCalls == 0 && set.failure() == detour::Set::JumpRangeFailure, "out-of-range target must not mutate");
    set.restore(); checkRestored(1); observing = false;
}
static void crossingPage()
{
    resetObservation(); unsigned char* at = site(kLarge + 1) + kPage - 3;
    unsigned char saved[7]; std::memcpy(saved, at - 1, sizeof(saved));
    detour::Set set; set.redirect((char*)at, (char*)at, (void*)(at + 100));
    require(!set.failed() && at[0] == 0xe9, "cross-page patch");
    require(eventCount == 2 && events[0].bytes == 2 * kPage && events[1].bytes == 2 * kPage, "whole five-byte prefix made writable");
    set.restore(); require(std::memcmp(saved, at - 1, sizeof(saved)) == 0, "cross-page prefix and neighboring bytes restored");
    observing = false;
}
#endif
int main(int argc, char** argv)
{
    require(__tlhybrid_text_end - __tlhybrid_text_start == kArenaBytes, "assembly range matches arena");
    for (int i = 0; i < kSites; ++i) std::memcpy(site(i), originalCode, sizeof(originalCode));
    require(__real_mprotect(proofArena, sizeof(proofArena), PROT_READ | PROT_EXEC) == 0, "make synthetic code executable");
    if (argc > 1) { growth(std::atoi(argv[1])); std::puts("PASS requested growth control"); return 0; }
    const int sizes[] = {1, 2, 63, 64, 65, 127, 128, 129, 4097};
    for (unsigned i = 0; i < sizeof(sizes) / sizeof(sizes[0]); ++i)
    { growth(sizes[i]); std::printf("PASS growth/coverage/dedup/LIFO/heap-isolation %d\n", sizes[i]); }
#ifndef BASELINE_PROOF
    storageFailure(64, false); storageFailure(64, true); storageFailure(128, false); newPairStorageFailure();
    std::puts("PASS allocation failure at first and later spill, alias pairs, sticky failure");
    installFailure(1); installFailure(2); std::puts("PASS install writable/protection-reset failures");
    restoreFailure(5, false); restoreFailure(6, false); restoreFailure(7, false); restoreFailure(132, false);
    restoreFailure(1, true); restoreFailure(6, true); restoreFailure(260, true);
    std::puts("PASS failed explicit/destructor restoration aborts before next statement across blocks");
    reuseAfterRestore(); std::puts("PASS successful restore, redirect again, restore reuse");
    releaseFailure(); destructorReleaseFailure(); std::puts("PASS explicit/destructor release failure leaks only empty storage, restores remaining entries");
    relativeRange(-0x80000000LL, true); relativeRange(0x7fffffffLL, true);
    relativeRange(-0x80000001LL, false); relativeRange(0x80000000LL, false);
    std::puts("PASS signed rel32 exact boundaries and out-of-range rejections");
    crossingPage(); std::puts("PASS whole five-byte prefix across page boundary");
#endif
    std::puts("PASS all requested Detour capacity controls"); return 0;
}
