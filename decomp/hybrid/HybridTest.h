/* Helpers for hybrid self-tests (compiled with the original toolchain into the blob). */
#ifndef HYBRIDTEST_H
#define HYBRIDTEST_H

#include "hybrid_abi.h"

/* Untouched original function, declared as a free function (explicit `this`
 * first for methods). The linker resolves __tlorig_<mangled> to the original
 * address even when the decomp code defines <mangled> itself. */
#define TL_ORIGINAL(ret, name, params, mangled) \
    extern "C" ret name params __asm__("__tlorig_" mangled);

#define TL_TEST(fn)                                                                      \
    static int fn(const tlhybrid_host* host);                                            \
    static const tlhybrid_test fn##_entry __attribute__((used, section(".tlhybrid.tests"))) = \
        {#fn, fn};                                                                       \
    static int fn(const tlhybrid_host* host)

#define TL_CHECK(failures, cond)                                                  \
    do {                                                                          \
        if (!(cond)) {                                                            \
            if ((failures)++ < 20)                                                \
                host->log("    %s:%d: check failed: %s\n", __FILE__, __LINE__, #cond); \
        }                                                                         \
    } while (0)

#endif
