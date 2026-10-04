/* Per-thread, opt-in malloc call counting for headless differential tests.
 * GNU/Linux glibc only. No allocation is failed or redirected to another heap.
 */
#include <stddef.h>
extern void *__libc_malloc(size_t);
static __thread unsigned long long calls __attribute__((tls_model("initial-exec")));
static __thread int enabled __attribute__((tls_model("initial-exec")));
void *malloc(size_t size)
{
    if (enabled) ++calls;
    return __libc_malloc(size);
}
void otl_begin_alloc_count(void) { calls=0; enabled=1; }
unsigned long long otl_end_alloc_count(void) { enabled=0; return calls; }
