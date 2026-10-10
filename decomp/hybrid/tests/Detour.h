// Temporary redirection of collaborator functions to test fakes. Both the
// original entry and the address the blob links against (a decompiled
// replacement, when the blob has one) get a 5-byte jmp to the fake, so the
// original code and the decompiled code under test call the same fake. The
// bytes are restored when the set goes out of scope.
#ifndef DETOUR_H
#define DETOUR_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <link.h>
#include <stdint.h>
#include <sys/mman.h>

// Original entry (__tlorig_) and linked address of a function, by mangled name.
#define TL_FUNCTION(name, mangled)                                  \
    extern "C" char name##_original[] __asm__("__tlorig_" mangled); \
    extern "C" char name##_linked[] __asm__(mangled);

// Bounds of the blob's code (tools/decomp/hybrid.py linker script).
extern "C" char __tlhybrid_text_start[];
extern "C" char __tlhybrid_text_end[];

#define TL_REDIRECT(set, name, fake) (set).redirect(name##_original, name##_linked, (fake))

namespace detour
{

struct Patch
{
    unsigned char* at;
    unsigned char saved[5];
    int protection;
};

class Set
{
public:
    enum Failure
    {
        NoFailure,
        StorageFailure,
        JumpRangeFailure,
        ProtectionFailure,
        StorageReleaseFailure
    };

    Set() : m_last(&m_inline), m_failure(NoFailure), m_failureSite(0)
    {
        m_inline.previous = 0;
        m_inline.count = 0;
    }

    ~Set() { restore(); }

    template <class F>
    void redirect(char* original, char* linked, F fake)
    {
        if (failed())
            return;
        void* target = reinterpret_cast<void*>(fake);
        patch(reinterpret_cast<unsigned char*>(original), target);
        if (!failed() && linked != original)
            patch(reinterpret_cast<unsigned char*>(linked), target);
    }

    bool failed() const { return m_failure != NoFailure; }
    Failure failure() const { return m_failure; }
    const unsigned char* failureSite() const { return m_failureSite; }

    void restore()
    {
        for (;;)
        {
            while (m_last->count != 0)
            {
                Patch& p = m_last->patches[m_last->count - 1];
                if (!writable(p.at, p.protection | PROT_WRITE))
                {
                    // Existing callers invoke restore() before calling original
                    // code and do not check a result: continuing would be unsafe.
                    fail(ProtectionFailure, p.at);
                    std::abort();
                }
                std::memcpy(p.at, p.saved, sizeof(p.saved));
                if (!writable(p.at, p.protection))
                {
                    // Existing callers invoke restore() before calling original
                    // code and do not check a result: continuing would be unsafe.
                    fail(ProtectionFailure, p.at);
                    std::abort();
                }
                // A backup stays live until both bytes and permissions are back.
                --m_last->count;
            }
            if (m_last == &m_inline)
                return;
            Block* previous = m_last->previous;
            if (munmap(m_last, sizeof(Block)) != 0)
            {
                // This empty mapping contains no live backups. A release
                // failure may leak storage, but must not block earlier patches.
                fail(StorageReleaseFailure, 0);
            }
            m_last = previous;
        }
    }

private:
    // Preserve the allocation-free common case. This is a chunk size, not a
    // total limit: more blocks are mapped as necessary, without new/malloc or
    // reallocating backups while application allocators may be detoured.
    static const size_t kPatchesPerBlock = 64;
    struct Block
    {
        Block* previous;
        size_t count;
        Patch patches[kPatchesPerBlock];
    };

    Set(const Set&);
    Set& operator=(const Set&);

    void fail(Failure reason, const unsigned char* at)
    {
        if (!failed())
        {
            m_failure = reason;
            m_failureSite = at;
        }
    }

    Patch* nextPatch(unsigned char* at)
    {
        if (m_last->count == kPatchesPerBlock)
        {
            void* memory = mmap(0, sizeof(Block), PROT_READ | PROT_WRITE,
                                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            if (memory == MAP_FAILED)
            {
                fail(StorageFailure, at);
                return 0;
            }
            Block* block = static_cast<Block*>(memory);
            block->previous = m_last;
            block->count = 0;
            m_last = block;
        }
        return &m_last->patches[m_last->count];
    }

    struct Segment
    {
        uintptr_t at;
        int prot;
    };

    static int executableSegment(struct dl_phdr_info* info, size_t, void* data)
    {
        Segment* s = (Segment*)data;
        for (int i = 0; i < info->dlpi_phnum; i++)
        {
            const ElfW(Phdr)& ph = info->dlpi_phdr[i];
            uintptr_t lo = info->dlpi_addr + ph.p_vaddr;
            if (ph.p_type == PT_LOAD && (ph.p_flags & PF_X) && lo <= s->at && s->at < lo + ph.p_memsz)
            {
                s->prot = ((ph.p_flags & PF_R) ? PROT_READ : 0) | ((ph.p_flags & PF_W) ? PROT_WRITE : 0) | PROT_EXEC;
                return 1;
            }
        }
        return 0;
    }

    // Current protection of the page holding `at`: the loaded segment's flags for code of the
    // executable and libraries (the loader restores exactly those after installing its hooks),
    // otherwise /proc/self/maps. Tests patch in thousands of forked children; reading maps
    // each time cost more than the code under test.
    static int protection(const unsigned char* at)
    {
        if (__tlhybrid_text_start <= (const char*)at && (const char*)at < __tlhybrid_text_end)
            return PROT_READ | PROT_EXEC;  // the blob's code, loaded by decomp/hybrid/loader.c
        Segment segment = {(uintptr_t)at, 0};
        if (dl_iterate_phdr(executableSegment, &segment))
            return segment.prot;
        FILE* maps = std::fopen("/proc/self/maps", "r");
        char line[512];
        int result = PROT_READ | PROT_EXEC;
        while (maps && std::fgets(line, sizeof(line), maps))
        {
            unsigned long lo, hi;
            char perms[5];
            if (std::sscanf(line, "%lx-%lx %4s", &lo, &hi, perms) == 3 && lo <= (uintptr_t)at && (uintptr_t)at < hi)
            {
                result = (perms[0] == 'r' ? PROT_READ : 0) | (perms[1] == 'w' ? PROT_WRITE : 0) |
                         (perms[2] == 'x' ? PROT_EXEC : 0);
                break;
            }
        }
        if (maps)
            std::fclose(maps);
        return result;
    }

    static bool writable(unsigned char* at, int prot)
    {
        uintptr_t page = 4096;
        uintptr_t start = (uintptr_t)at & ~(page - 1);
        uintptr_t end = ((uintptr_t)at + 5 + page - 1) & ~(page - 1);
        return mprotect((void*)start, end - start, prot) == 0;
    }

    void patch(unsigned char* at, void* target)
    {
        for (Block* block = m_last; block; block = block->previous)
        {
            for (size_t i = 0; i < block->count; ++i)
            {
                if (block->patches[i].at == at)
                    return;
            }
        }
        int64_t rel = (int64_t)(uintptr_t)target - (int64_t)((uintptr_t)at + 5);
        if (rel < -0x80000000LL || rel > 0x7fffffffLL)
        {
            fail(JumpRangeFailure, at);
            return;
        }
        Patch* p = nextPatch(at);
        if (!p)
            return;
        p->at = at;
        p->protection = protection(at);
        std::memcpy(p->saved, at, sizeof(p->saved));
        if (!writable(at, p->protection | PROT_WRITE))
        {
            fail(ProtectionFailure, at);
            return;
        }
        int32_t rel32 = (int32_t)rel;
        at[0] = 0xE9;
        std::memcpy(at + 1, &rel32, sizeof(rel32));
        ++m_last->count; // An installed jump must have a live backup on failure.
        if (!writable(at, p->protection))
            fail(ProtectionFailure, at);
    }

    Block m_inline;
    Block* m_last;
    Failure m_failure;
    const unsigned char* m_failureSite;
};

} // namespace detour

#endif
