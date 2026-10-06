#ifndef EXPECT_NO_RC
#define EXPECT_NO_RC 0
#endif
#define __libc_start_main research_unused_start
#include "loader.c"
#undef __libc_start_main
static int calls;
static int pass_case(const tlhybrid_host *h) { (void)h; ++calls; return 0; }
static int fail_case(const tlhybrid_host *h) { (void)h; ++calls; return 1; }
int main(void) {
 tlhybrid_test tests[2] = {{"control_pass",pass_case},{"control_fail",fail_case}};
 Elf64_Ehdr eh = {0}; Elf64_Shdr sh = {0}; struct blob b = {0};
 eh.e_shnum = 1; sh.sh_name = 1; sh.sh_addr = (uintptr_t)tests; sh.sh_size = sizeof(tests);
 b.eh=&eh; b.sh=&sh; b.shstr="\0.tlhybrid.tests\0";
 setenv("TLHYBRID_FILTER","missing_case",1); calls=0;
 int no_rc=run_tests(&b), no_calls=calls;
 unsetenv("TLHYBRID_FILTER"); calls=0;
 int all_rc=run_tests(&b), all_calls=calls;
 printf("empty: rc=%d calls=%d; all: rc=%d calls=%d\n",no_rc,no_calls,all_rc,all_calls);
 return !(no_rc==EXPECT_NO_RC && no_calls==0 && all_rc==1 && all_calls==2);
}
