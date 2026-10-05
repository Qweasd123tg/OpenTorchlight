/* Opt-in per-thread observation only. GNU/Linux glibc; never fails or delays free. */
#include <stddef.h>
extern void __libc_free(void*);
static __thread void* watched[32] __attribute__((tls_model("initial-exec")));
static __thread unsigned counts[32] __attribute__((tls_model("initial-exec")));
static __thread unsigned order[64] __attribute__((tls_model("initial-exec")));
static __thread unsigned length,used __attribute__((tls_model("initial-exec")));
static __thread int active __attribute__((tls_model("initial-exec")));
void free(void* p){if(active&&p){unsigned i;for(i=0;i<length;++i)if(watched[i]==p){++counts[i];if(used<64)order[used++]=i;}}__libc_free(p);}
void otl_watch_frees(void** p,unsigned n){unsigned i;active=0;length=n<32?n:32;used=0;for(i=0;i<length;++i){watched[i]=p[i];counts[i]=0;}active=1;}
unsigned otl_end_frees(unsigned* result,unsigned* sequence,unsigned capacity){unsigned i;active=0;for(i=0;i<length;++i)result[i]=counts[i];for(i=0;i<used&&i<capacity;++i)sequence[i]=order[i];return used;}
