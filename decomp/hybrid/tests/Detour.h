// Temporary redirection of collaborator functions to test fakes. Both the
// original entry and the address the blob links against (a decompiled
// replacement, when the blob has one) get a 5-byte jmp to the fake, so the
// original code and the decompiled code under test call the same fake. The
// bytes are restored when the set goes out of scope.
#ifndef DETOUR_H
#define DETOUR_H

#include <cstdio>
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
    Set() : m_count(0), m_failed(false) {}
    ~Set() { restore(); }

    template <class F>
    void redirect(char* original, char* linked, F fake)
    {
        void* target = reinterpret_cast<void*>(fake);
        patch(reinterpret_cast<unsigned char*>(original), target);
        if (linked != original)
            patch(reinterpret_cast<unsigned char*>(linked), target);
    }

    bool failed() const { return m_failed; }

    void restore()
    {
        while (m_count > 0)
        {
            Patch& p = m_patches[--m_count];
            if (writable(p.at, p.protection | PROT_WRITE))
            {
                std::memcpy(p.at, p.saved, sizeof(p.saved));
                writable(p.at, p.protection);
            }
        }
    }

private:
    static const int kMaxPatches = 64;

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
        for (int i = 0; i < m_count; i++)
        {
            if (m_patches[i].at == at)
                return;
        }
        int64_t rel = (int64_t)(uintptr_t)target - (int64_t)((uintptr_t)at + 5);
        if (m_count == kMaxPatches || rel < -0x80000000LL || rel > 0x7fffffffLL)
        {
            m_failed = true;
            return;
        }
        Patch& p = m_patches[m_count];
        p.at = at;
        p.protection = protection(at);
        std::memcpy(p.saved, at, sizeof(p.saved));
        if (!writable(at, p.protection | PROT_WRITE))
        {
            m_failed = true;
            return;
        }
        int32_t rel32 = (int32_t)rel;
        at[0] = 0xE9;
        std::memcpy(at + 1, &rel32, sizeof(rel32));
        writable(at, p.protection);
        m_count++;
    }

    Patch m_patches[kMaxPatches];
    int m_count;
    bool m_failed;
};

} // namespace detour

#endif
