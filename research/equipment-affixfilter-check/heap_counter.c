#include <stddef.h>
extern void *__libc_malloc(size_t);
extern void __libc_free(void*);
static __thread unsigned long long allocated __attribute__((tls_model("initial-exec")));
static __thread unsigned long long released __attribute__((tls_model("initial-exec")));
static __thread int enabled __attribute__((tls_model("initial-exec")));
void* malloc(size_t n){if(enabled)++allocated;return __libc_malloc(n);}
void free(void*p){if(enabled&&p)++released;__libc_free(p);}
void otl_begin_filter_heap_count(void){allocated=released=0;enabled=1;}
void otl_end_filter_heap_count(unsigned long long*a,unsigned long long*f){enabled=0;*a=allocated;*f=released;}
