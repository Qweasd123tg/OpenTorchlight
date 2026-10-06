/* Hybrid runtime loader for the original Torchlight executable.
 *
 * Preloaded into Torchlight.bin.x86_64 (non-PIE, fixed addresses). After the
 * game's own static initialization and before main it maps the decomp blob
 * (fully linked at a fixed address by tools/decomp/hybrid.py), registers its
 * unwind tables, resolves extra imports, runs the blob's own constructors,
 * optionally runs the self-tests against the untouched original code, and then
 * redirects every replaced original function to its decompiled version with a
 * 5-byte jmp.
 *
 * Environment:
 *   TLHYBRID_BLOB      path of the blob ELF (required)
 *   TLHYBRID_SELFTEST  1: run tests, print a report and exit before main
 *   TLHYBRID_FILTER    run only tests whose names start with one of these
 *                      comma-separated prefixes
 *   TLHYBRID_NOHOOK    1: map the blob but leave original code untouched
 *   TLHYBRID_VERBOSE   1: log every hook
 */
#define _GNU_SOURCE
#include <dlfcn.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "hybrid_abi.h"

typedef int (*main_fn)(int, char **, char **);
typedef int (*libc_start_main_fn)(main_fn, int, char **, void (*)(void), void (*)(void),
                                  void (*)(void), void *);

static main_fn g_game_main;
static int g_verbose;

static void fail(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fputs("tlhybrid: ", stderr);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
    _exit(97);
}

static void host_log(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}

static const tlhybrid_host g_host = {TLHYBRID_ABI_VERSION, host_log};

struct blob {
    unsigned char *file;
    size_t size;
    const Elf64_Ehdr *eh;
    const Elf64_Shdr *sh;
    const char *shstr;
};

static const Elf64_Shdr *find_section(const struct blob *b, const char *name)
{
    for (int i = 0; i < b->eh->e_shnum; i++)
        if (strcmp(b->shstr + b->sh[i].sh_name, name) == 0)
            return &b->sh[i];
    return NULL;
}

static void load_blob(struct blob *b, const char *path)
{
    int fd = open(path, O_RDONLY | O_CLOEXEC);
    struct stat st;
    if (fd < 0 || fstat(fd, &st) != 0)
        fail("cannot open blob %s: %s", path, strerror(errno));
    b->size = (size_t)st.st_size;
    b->file = mmap(NULL, b->size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (b->file == MAP_FAILED)
        fail("cannot read blob %s", path);
    b->eh = (const Elf64_Ehdr *)b->file;
    if (memcmp(b->eh->e_ident, ELFMAG, SELFMAG) != 0 || b->eh->e_type != ET_EXEC ||
        b->eh->e_machine != EM_X86_64)
        fail("%s is not an x86-64 ET_EXEC blob", path);
    b->sh = (const Elf64_Shdr *)(b->file + b->eh->e_shoff);
    b->shstr = (const char *)(b->file + b->sh[b->eh->e_shstrndx].sh_offset);

    const Elf64_Phdr *ph = (const Elf64_Phdr *)(b->file + b->eh->e_phoff);
    for (int i = 0; i < b->eh->e_phnum; i++) {
        if (ph[i].p_type != PT_LOAD || ph[i].p_memsz == 0)
            continue;
        uintptr_t page = 4096;
        uintptr_t start = ph[i].p_vaddr & ~(page - 1);
        uintptr_t end = (ph[i].p_vaddr + ph[i].p_memsz + page - 1) & ~(page - 1);
        void *at = mmap((void *)start, end - start, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
        if (at != (void *)start) {
            /* Show what occupies the range, then give up. */
            int saved = errno;
            FILE *maps = fopen("/proc/self/maps", "r");
            char line[512];
            while (maps && fgets(line, sizeof(line), maps)) {
                unsigned long lo, hi;
                if (sscanf(line, "%lx-%lx", &lo, &hi) == 2 && lo < end && hi > start)
                    fprintf(stderr, "tlhybrid: occupied: %s", line);
            }
            if (maps)
                fclose(maps);
            fail("cannot map blob segment at %#lx (%s)", (unsigned long)start, strerror(saved));
        }
        memcpy((void *)ph[i].p_vaddr, b->file + ph[i].p_offset, ph[i].p_filesz);
        int prot = ((ph[i].p_flags & PF_R) ? PROT_READ : 0) | ((ph[i].p_flags & PF_W) ? PROT_WRITE : 0) |
                   ((ph[i].p_flags & PF_X) ? PROT_EXEC : 0);
        if (mprotect((void *)start, end - start, prot) != 0)
            fail("mprotect blob segment: %s", strerror(errno));
    }
}

static void register_unwind(const struct blob *b)
{
    const Elf64_Shdr *eh = find_section(b, ".eh_frame");
    if (!eh || eh->sh_size == 0)
        return;
    void (*reg)(const void *, void *) = (void (*)(const void *, void *))dlsym(RTLD_DEFAULT, "__register_frame_info");
    if (!reg)
        fail("__register_frame_info not available");
    /* libgcc keeps a pointer to this object for the lifetime of the process. */
    static unsigned char object[64];
    reg((const void *)eh->sh_addr, object);
}

static void resolve_imports(const struct blob *b)
{
    const Elf64_Shdr *s = find_section(b, ".tlhybrid.imports");
    if (!s)
        return;
    const tlhybrid_import *imp = (const tlhybrid_import *)s->sh_addr;
    size_t count = s->sh_size / sizeof(*imp);
    for (size_t i = 0; i < count; i++) {
        void *address = dlsym(RTLD_DEFAULT, imp[i].name);
        if (!address)
            fail("unresolved import %s", imp[i].name);
        *imp[i].slot = address;
    }
}

static void copy_library_data(const struct blob *b)
{
    const Elf64_Shdr *s = find_section(b, ".tlhybrid.copies");
    if (!s)
        return;
    const tlhybrid_copy *copy = (const tlhybrid_copy *)s->sh_addr;
    size_t count = s->sh_size / sizeof(*copy);
    for (size_t i = 0; i < count; i++) {
        void *address = dlsym(RTLD_DEFAULT, copy[i].name);
        if (!address)
            fail("unresolved data import %s", copy[i].name);
        Dl_info info;
        const Elf64_Sym *sym = NULL;
        if (dladdr1(address, &info, (void **)&sym, RTLD_DL_SYMENT) && sym && sym->st_size != copy[i].size)
            fail("data import %s: %lu bytes in %s, %lu reserved in the blob", copy[i].name,
                 (unsigned long)sym->st_size, info.dli_fname, (unsigned long)copy[i].size);
        memcpy(copy[i].dest, address, copy[i].size);
    }
}

static void run_constructors(const struct blob *b)
{
    const Elf64_Shdr *s = find_section(b, ".tlhybrid.ctors");
    if (!s)
        return;
    void (*const *ctor)(void) = (void (*const *)(void))s->sh_addr;
    size_t count = s->sh_size / sizeof(*ctor);
    for (size_t i = 0; i < count; i++)
        ctor[i]();
}

static int name_selected(const char *name, const char *prefixes)
{
    for (const char *p = prefixes; *p;) {
        size_t n = strcspn(p, ",");
        if (n && strncmp(name, p, n) == 0)
            return 1;
        p += n + (p[n] == ',');
    }
    return 0;
}

static int run_tests(const struct blob *b)
{
    const Elf64_Shdr *s = find_section(b, ".tlhybrid.tests");
    if (!s) {
        fprintf(stderr, "tlhybrid: no tests in blob\n");
        return 1;
    }
    const tlhybrid_test *test = (const tlhybrid_test *)s->sh_addr;
    size_t count = s->sh_size / sizeof(*test);
    const char *only = getenv("TLHYBRID_FILTER");
    /* TLHYBRID_SHARD=i/n: every n-th selected test from the i-th, for parallel processes. */
    const char *shard = getenv("TLHYBRID_SHARD");
    unsigned shard_index = 0, shard_count = 1;
    if (shard && (sscanf(shard, "%u/%u", &shard_index, &shard_count) != 2 || shard_count == 0 ||
                  shard_index >= shard_count))
        fail("TLHYBRID_SHARD must be i/n with i < n: %s", shard);
    int failed = 0;
    size_t selected = 0, ran = 0;
    for (size_t i = 0; i < count; i++) {
        if (only && !name_selected(test[i].name, only))
            continue;
        if (selected++ % shard_count != shard_index)
            continue;
        ran++;
        struct timespec started, finished;
        clock_gettime(CLOCK_MONOTONIC, &started);
        fprintf(stderr, "tlhybrid: begin %s\n", test[i].name);
        int failures = test[i].run(&g_host);
        clock_gettime(CLOCK_MONOTONIC, &finished);
        fprintf(stderr, "tlhybrid: timing %s %.3f seconds\n", test[i].name,
                (finished.tv_sec - started.tv_sec) + (finished.tv_nsec - started.tv_nsec) / 1e9);
        fprintf(stderr, "tlhybrid: %-48s %s (%d)\n", test[i].name, failures ? "FAIL" : "PASS", failures);
        failed += failures != 0;
    }
    fprintf(stderr, "tlhybrid: %zu tests, %d failed\n", ran, failed);
    if (!selected) {
        fprintf(stderr, "tlhybrid: no tests selected; refusing a successful selftest\n");
        return 2;
    }
    /* An empty shard is valid when other shards own the selected tests. */
    return failed ? 1 : 0;
}

static void install_hooks(const struct blob *b)
{
    const Elf64_Shdr *s = find_section(b, ".tlhybrid.hooks");
    if (!s)
        return;
    const tlhybrid_hook *hook = (const tlhybrid_hook *)s->sh_addr;
    size_t count = s->sh_size / sizeof(*hook);
    long page = sysconf(_SC_PAGESIZE);
    for (size_t i = 0; i < count; i++) {
        unsigned char *at = (unsigned char *)hook[i].original;
        if (memcmp(at, hook[i].expected, sizeof(hook[i].expected)) != 0)
            fail("original bytes differ at %p (%s): wrong executable?", at, hook[i].name);
        int64_t rel = (int64_t)hook[i].replacement - (int64_t)(hook[i].original + 5);
        if (rel < INT32_MIN || rel > INT32_MAX)
            fail("replacement for %s out of rel32 range", hook[i].name);
        uintptr_t start = (uintptr_t)at & ~(uintptr_t)(page - 1);
        uintptr_t end = ((uintptr_t)at + 5 + page - 1) & ~(uintptr_t)(page - 1);
        if (mprotect((void *)start, end - start, PROT_READ | PROT_WRITE | PROT_EXEC) != 0)
            fail("mprotect original text: %s", strerror(errno));
        int32_t rel32 = (int32_t)rel;
        at[0] = 0xE9;
        memcpy(at + 1, &rel32, 4);
        if (mprotect((void *)start, end - start, PROT_READ | PROT_EXEC) != 0)
            fail("restore original text protection: %s", strerror(errno));
        if (g_verbose)
            fprintf(stderr, "tlhybrid: hook %p -> %p %s\n", at, (void *)hook[i].replacement, hook[i].name);
    }
    fprintf(stderr, "tlhybrid: %zu original functions redirected to decomp code\n", count);
}

static int hybrid_main(int argc, char **argv, char **envp)
{
    const char *path = getenv("TLHYBRID_BLOB");
    if (!path)
        fail("TLHYBRID_BLOB is not set");
    g_verbose = getenv("TLHYBRID_VERBOSE") && atoi(getenv("TLHYBRID_VERBOSE"));
    struct blob b;
    load_blob(&b, path);
    register_unwind(&b);
    resolve_imports(&b);
    copy_library_data(&b);
    run_constructors(&b);
    if (getenv("TLHYBRID_SELFTEST") && atoi(getenv("TLHYBRID_SELFTEST")))
        exit(run_tests(&b));
    if (!(getenv("TLHYBRID_NOHOOK") && atoi(getenv("TLHYBRID_NOHOOK"))))
        install_hooks(&b);
    return g_game_main(argc, argv, envp);
}

int __libc_start_main(main_fn main, int argc, char **argv, void (*init)(void), void (*fini)(void),
                      void (*rtld_fini)(void), void *stack_end)
{
    libc_start_main_fn real = (libc_start_main_fn)dlsym(RTLD_NEXT, "__libc_start_main");
    if (!real)
        fail("cannot find the real __libc_start_main");
    g_game_main = main;
    return real(hybrid_main, argc, argv, init, fini, rtld_fini, stack_end);
}
