// Runtime for generated differential self-tests (tools/decomp/autotest.py).
// Each case builds the same object state and arguments, then runs the original
// function and the decompiled one in two forked children of the game process.
// The children report the return value and the bytes of the object and its
// fake collaborators; any difference fails the test. A crash or a timeout in
// both children is inconclusive, in one of them it is a failure.
#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <cstring>
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
    return (const char*)p >= g_arena && (const char*)p < g_arena + kArenaSize;
}

struct Capture
{
    enum { kSize = 256 * 1024 };
    size_t length;
    char data[kSize];

    void add(const void* p, size_t n)
    {
        if (length + n > kSize)
            n = kSize - length;
        std::memcpy(data + length, p, n);
        length += n;
    }
    void addPointer(const void* p)
    {
        // Heap addresses may legitimately differ; keep nullness and arena offsets.
        long long token = p == 0 ? 0 : inArena(p) ? 1 + ((const char*)p - g_arena) : -1;
        add(&token, sizeof(token));
    }
    void addText(const std::wstring& s)
    {
        size_t n = s.size();
        add(&n, sizeof(n));
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
    int status;
    Capture capture;
};

extern Outcome g_outcomes[2];

inline void crashed(int signal)
{
    _exit(128 + signal);
}

// Runs body in a forked child; the child reports its capture through a pipe.
inline void runChild(Body body, void* context, Outcome& outcome)
{
    int fds[2];
    outcome.capture.length = 0;
    outcome.status = -1;
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
        struct itimerval limit;
        std::memset(&limit, 0, sizeof(limit));
        limit.it_value.tv_usec = 300000;  // a hang (e.g. an endless loop in the original) is a SIGALRM
        setitimer(ITIMER_REAL, &limit, 0);
        Capture& capture = g_outcomes[0].capture;
        capture.length = 0;
        body(context, capture);
        size_t done = 0;
        if (write(fds[1], &capture.length, sizeof(capture.length)) < 0)
            _exit(3);
        while (done < capture.length)
        {
            ssize_t n = write(fds[1], capture.data + done, capture.length - done);
            if (n <= 0)
                _exit(3);
            done += n;
        }
        _exit(0);
    }
    close(fds[1]);
    size_t length = 0;
    if (pid > 0 && read(fds[0], &length, sizeof(length)) == (ssize_t)sizeof(length) && length <= Capture::kSize)
    {
        size_t done = 0;
        while (done < length)
        {
            ssize_t n = read(fds[0], outcome.capture.data + done, length - done);
            if (n <= 0)
                break;
            done += n;
        }
        outcome.capture.length = done;
    }
    close(fds[0]);
    if (pid > 0)
        waitpid(pid, &outcome.status, 0);
}

struct Stats
{
    int same;
    int bothFailed;
    int different;
};

// One differential case; returns false on a behavioural difference.
inline bool compareCase(Body original, Body ours, void* context, Stats& stats, const tlhybrid_host* host,
                        const char* name, int index)
{
    runChild(original, context, g_outcomes[0]);
    runChild(ours, context, g_outcomes[1]);
    const Outcome& a = g_outcomes[0];
    const Outcome& b = g_outcomes[1];
    bool okA = WIFEXITED(a.status) && WEXITSTATUS(a.status) == 0;
    bool okB = WIFEXITED(b.status) && WEXITSTATUS(b.status) == 0;
    if (!okA && !okB && a.status == b.status)
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
