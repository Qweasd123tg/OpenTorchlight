/* Tables shared by the hybrid loader (host C) and the decomp blob (GCC 4.4.7 C++). */
#ifndef TLHYBRID_ABI_H
#define TLHYBRID_ABI_H

#include <stdint.h>

#define TLHYBRID_ABI_VERSION 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tlhybrid_host {
    int abi_version;
    void (*log)(const char *fmt, ...);
} tlhybrid_host;

/* .tlhybrid.hooks: original entry -> decompiled replacement. */
typedef struct tlhybrid_hook {
    uint64_t original;
    uint64_t replacement;
    const char *name;
    unsigned char expected[8]; /* first bytes of the original entry */
} tlhybrid_hook;

/* .tlhybrid.imports: library symbols the original executable never imported. */
typedef struct tlhybrid_import {
    const char *name;
    void **slot;
} tlhybrid_import;

/* .tlhybrid.tests: self-tests run against the untouched original code. */
typedef struct tlhybrid_test {
    const char *name;
    int (*run)(const tlhybrid_host *host);
} tlhybrid_test;

#ifdef __cplusplus
}
#endif

#endif
