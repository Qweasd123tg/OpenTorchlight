// Runtime for generated differential self-tests (tools/decomp/autotest.py).
// Each case builds the same object state and arguments, then runs the original
// function and the decompiled one in two forked children of the game process.
// The children report the return value and the bytes of the object and its
// fake collaborators; any difference fails the test. A crash or a timeout in
// both children is inconclusive, in one of them it is a failure.
#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <cstring>
#include <errno.h>
#include <malloc.h>
#include <new>
#include <string>
#include <signal.h>
#include <stdint.h>
#include <sys/prctl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "HybridTest.h"

namespace autotest
{

struct Rng
{
    uint64_t state;
    explicit Rng(uint64_t seed) : state(seed * 2654435761u + 1) {}
    unsigned int next()
    {
        state = state * 6364136223846793005ULL + 1442695040888963407ULL;
        return (unsigned int)(state >> 33);
    }
};

// Values close to the boundaries code usually tests, plus random ones.
inline long long randomInt(Rng& r)
{
    static const long long picks[] = {0, 1, -1, 2, 3, 4, 5, 7, 10, 16, 100, -2, -100, 255, 1000};
    unsigned int k = r.next() % 20;
    if (k < sizeof(picks) / sizeof(picks[0]))
        return picks[k];
    return (long long)(r.next() % 2001) - 1000;
}

inline double randomFloat(Rng& r)
{
    static const double picks[] = {0.0, 1.0, -1.0, 0.5, 2.0, -0.25, 10.0, 0.001, 100.0};
    unsigned int k = r.next() % 14;
    if (k < sizeof(picks) / sizeof(picks[0]))
        return picks[k];
    return ((double)(r.next() % 20001) - 10000.0) / 100.0;
}

inline const wchar_t* randomText(Rng& r)
{
    static const wchar_t* picks[] = {L"", L"a", L"TEST", L"Hello World", L"media/test.dat", L"0", L"12"};
    return picks[r.next() % (sizeof(picks) / sizeof(picks[0]))];
}

// Arena for the object under test and fake collaborators: same addresses in
// both children, so pointers into it compare equal.
const size_t kArenaSize = 1 << 20;
extern char g_arena[kArenaSize];
extern size_t g_arenaUsed;

inline void* allocate(size_t size)
{
    size_t at = (g_arenaUsed + 15) & ~(size_t)15;
    if (at + size > kArenaSize)
        return 0;
    g_arenaUsed = at + size;
    std::memset(g_arena + at, 0, size);
    return g_arena + at;
}

inline bool inArena(const void* p)
{
    uintptr_t at = reinterpret_cast<uintptr_t>(p);
    uintptr_t start = reinterpret_cast<uintptr_t>(g_arena);
    return at >= start && at - start < kArenaSize;
}

// Fake objects made for a case, by class; arguments and list elements
// sometimes reuse them, so lookups and removals find what they look for.
struct Pool
{
    enum { kSize = 256 };
    void* pointer[kSize];
    int kind[kSize];
    int count;
};
extern Pool g_pool;

inline void remember(void* p, int kind)
{
    if (g_pool.count < Pool::kSize)
    {
        g_pool.pointer[g_pool.count] = p;
        g_pool.kind[g_pool.count] = kind;
        g_pool.count++;
    }
}

inline void* pick(Rng& r, int kind, void* fresh)
{
    int n = 0;
    for (int i = 0; i < g_pool.count; i++)
        n += g_pool.kind[i] == kind && g_pool.pointer[i] != fresh;
    if (n == 0 || r.next() % 3 == 0)
        return fresh;
    int k = r.next() % n;
    for (int i = 0; i < g_pool.count; i++)
        if (g_pool.kind[i] == kind && g_pool.pointer[i] != fresh && k-- == 0)
            return g_pool.pointer[i];
    return fresh;
}

struct Capture
{
    enum { kSize = 256 * 1024 };
    enum Issue { Complete = 0, Overflow = 1, UnsupportedPointer = 2, InvalidReport = 3 };
    size_t length;
    unsigned int issue;
    char data[kSize];

    void reset()
    {
        length = 0;
        issue = Complete;
    }
    void add(const void* p, size_t n)
    {
        if (issue != Complete)
            return;
        // A bounded buffer is intentional; an unobserved tail is never equal.
        if (length > kSize || n > kSize - length)
        {
            issue = Overflow;
            return;
        }
        if (!n)
            return;
        std::memcpy(data + length, p, n);
        length += n;
    }
    void addPointer(const void* p)
    {
        if (issue != Complete)
            return;
        // Pool's generated fake objects live in the arena and retain identity
        // across forks. Child allocations and other external pointers have no
        // logical identity here; neither raw addresses nor malloc totals prove it.
        if (p && !inArena(p))
        {
            issue = UnsupportedPointer;
            return;
        }
        long long token = p == 0 ? 0 : 1 + ((const char*)p - g_arena);
        add(&token, sizeof(token));
    }
    // Bytes in use on the malloc heap: both children start from the same heap,
    // so a missing delete or an extra allocation shows here.
    void addHeapInUse()
    {
        struct mallinfo info = mallinfo();
        long long used = info.uordblks;
        add(&used, sizeof(used));
    }
    void addText(const std::wstring& s)
    {
        if (issue != Complete)
            return;
        size_t n = s.size();
        add(&n, sizeof(n));
        if (n > kSize / sizeof(wchar_t))
        {
            issue = Overflow;
            return;
        }
        add(s.data(), n * sizeof(wchar_t));
    }
};

// Return values of any type (void included) through the comma operator.
struct Void
{
};
template <class T>
struct Value
{
    T value;
};
template <class T>
Value<T> operator,(const T& value, Void)
{
    Value<T> v = {value};
    return v;
}
inline void record(Capture&, Void) {}
template <class T>
void record(Capture& out, const Value<T>& v)
{
    out.add(&v.value, sizeof(T));
}
template <class T>
void record(Capture& out, const Value<T*>& v)
{
    out.addPointer(v.value);
}
inline void record(Capture& out, const Value<std::wstring>& v)
{
    out.addText(v.value);
}
inline void record(Capture& out, const Value<bool>& v)
{
    unsigned char b = v.value ? 1 : 0;
    out.add(&b, 1);
}

typedef void (*Body)(void* context, Capture& out);

struct Outcome
{
    // status stays compatible with handwritten tests: clean exit is exposed
    // only when a complete report arrived. childStatus is the actual wait status.
    int status;
    int childStatus;
    bool reportValid;
    bool reportStarted;
    Capture capture;
};

extern Outcome g_outcomes[2];

inline void crashed(int signal)
{
    _exit(128 + signal);
}

struct ReportHeader
{
    uint32_t magic;
    uint32_t version;
    uint32_t length;
    uint32_t issue;
};
const uint32_t kReportMagic = 0x544c4350;
// Reserved by the observer; a failed pipe write is not a function failure.
const int kReportWriteFailure = 253;

inline bool writeExact(int fd, const void* data, size_t length)
{
    const char* at = (const char*)data;
    while (length)
    {
        ssize_t n = write(fd, at, length);
        if (n < 0 && errno == EINTR)
            continue;
        if (n <= 0)
            return false;
        at += n;
        length -= n;
    }
    return true;
}

inline bool readExact(int fd, void* data, size_t length, size_t* completed = 0)
{
    char* at = (char*)data;
    if (completed)
        *completed = 0;
    while (length)
    {
        ssize_t n = read(fd, at, length);
        if (n < 0 && errno == EINTR)
            continue;
        if (n <= 0)
            return false;
        at += n;
        length -= n;
        if (completed)
            *completed += n;
    }
    return true;
}

inline bool writeReport(int fd, const Capture& capture)
{
    ReportHeader header = {kReportMagic, 1, (uint32_t)capture.length, capture.issue};
    return writeExact(fd, &header, sizeof(header)) && writeExact(fd, capture.data, capture.length);
}

inline bool readReport(int fd, Capture& capture, bool* started = 0)
{
    capture.reset();
    capture.issue = Capture::InvalidReport;
    ReportHeader header;
    size_t headerBytes;
    bool gotHeader = readExact(fd, &header, sizeof(header), &headerBytes);
    if (started)
        *started = headerBytes != 0;
    if (!gotHeader || header.magic != kReportMagic || header.version != 1 ||
        header.length > Capture::kSize || header.issue > Capture::UnsupportedPointer ||
        !readExact(fd, capture.data, header.length))
        return false;
    // Exactly one frame, including EOF, is required; no trailing partial frame.
    char extra;
    ssize_t n;
    do { n = read(fd, &extra, 1); } while (n < 0 && errno == EINTR);
    if (n != 0)
        return false;
    capture.length = header.length;
    capture.issue = header.issue;
    return true;
}

// Runs body in a forked child; the child reports its capture through a pipe.
inline void runChild(Body body, void* context, Outcome& outcome)
{
    int fds[2];
    outcome.capture.reset();
    outcome.capture.issue = Capture::InvalidReport;
    outcome.status = -1;
    outcome.childStatus = -1;
    outcome.reportValid = false;
    outcome.reportStarted = false;
    if (pipe(fds) != 0)
        return;
    pid_t pid = fork();
    if (pid == 0)
    {
        close(fds[0]);
        // A crash ends the child at once: no game crash handler, no core dump.
        prctl(PR_SET_DUMPABLE, 0, 0, 0, 0);
        signal(SIGSEGV, crashed);
        signal(SIGBUS, crashed);
        signal(SIGFPE, crashed);
        signal(SIGILL, crashed);
        signal(SIGABRT, crashed);
        signal(SIGALRM, SIG_DFL);
        struct itimerval limit;
        std::memset(&limit, 0, sizeof(limit));
        limit.it_value.tv_usec = 300000;  // a hang (e.g. an endless loop in the original) is a SIGALRM
        setitimer(ITIMER_REAL, &limit, 0);
        // A child-local buffer also lets hand-written tests call runChild
        // without linking the generated runtime's global outcome storage.
        Capture capture;
        capture.reset();
        body(context, capture);
        if (!writeReport(fds[1], capture))
            _exit(kReportWriteFailure);
        _exit(0);
    }
    close(fds[1]);
    if (pid > 0)
        outcome.reportValid = readReport(fds[0], outcome.capture, &outcome.reportStarted);
    close(fds[0]);
    if (pid > 0)
    {
        int status;
        pid_t waited;
        do { waited = waitpid(pid, &status, 0); } while (waited < 0 && errno == EINTR);
        if (waited == pid)
        {
            outcome.childStatus = status;
            outcome.status = status;
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0 &&
                (!outcome.reportValid || outcome.capture.issue != Capture::Complete))
                outcome.status = 4 << 8;
        }
    }
}

struct Stats
{
    int same;
    int bothFailed;
    int different;
    int incomplete;
};

inline bool incomplete(const Outcome& outcome)
{
    if (outcome.childStatus < 0 || (outcome.reportStarted && !outcome.reportValid) ||
        (outcome.reportValid && outcome.capture.issue != Capture::Complete))
        return true;
    return WIFEXITED(outcome.childStatus) &&
           (WEXITSTATUS(outcome.childStatus) == kReportWriteFailure ||
            (WEXITSTATUS(outcome.childStatus) == 0 && !outcome.reportValid));
}

// One differential case; incomplete observation is separate from a difference.
inline bool compareCase(Body original, Body ours, void* context, Stats& stats, const tlhybrid_host* host,
                        const char* name, int index)
{
    runChild(original, context, g_outcomes[0]);
    runChild(ours, context, g_outcomes[1]);
    const Outcome& a = g_outcomes[0];
    const Outcome& b = g_outcomes[1];
    bool okA = a.childStatus >= 0 && WIFEXITED(a.childStatus) && WEXITSTATUS(a.childStatus) == 0;
    bool okB = b.childStatus >= 0 && WIFEXITED(b.childStatus) && WEXITSTATUS(b.childStatus) == 0;
    if (incomplete(a) || incomplete(b))
    {
        stats.incomplete++;
        if (stats.incomplete <= 3)
            host->log("    %s case %d: incomplete observation, original report %d issue %u, ours report %d issue %u\n",
                      name, index, a.reportValid, a.capture.issue, b.reportValid, b.capture.issue);
        return false;
    }
    if (!okA && !okB && a.childStatus == b.childStatus)
    {
        stats.bothFailed++;
        return true;
    }
    if (okA && okB && a.capture.length == b.capture.length &&
        std::memcmp(a.capture.data, b.capture.data, a.capture.length) == 0)
    {
        stats.same++;
        return true;
    }
    stats.different++;
    if (stats.different <= 3)
    {
        size_t at = 0;
        while (at < a.capture.length && at < b.capture.length && a.capture.data[at] == b.capture.data[at])
            at++;
        host->log("    %s case %d: original status %d len %lu, ours status %d len %lu, first difference at %lu\n",
                  name, index, a.status, (unsigned long)a.capture.length, b.status,
                  (unsigned long)b.capture.length, (unsigned long)at);
    }
    return false;
}

inline double seconds()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec * 1e-9;
}

} // namespace autotest

#endif
