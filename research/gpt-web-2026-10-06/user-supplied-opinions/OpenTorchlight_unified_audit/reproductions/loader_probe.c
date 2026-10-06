
#define __libc_start_main audit_unused_libc_start_main
#include "loader.c"
#undef __libc_start_main
static int invoked;
static int good(const tlhybrid_host *h) { (void)h; invoked++; return 0; }
static int bad(const tlhybrid_host *h) { (void)h; invoked++; return 1; }
int main(void) {
 tlhybrid_test tests[2]={{"good",good},{"bad",bad}};
 Elf64_Ehdr eh={0}; Elf64_Shdr sh={0}; struct blob b={0};
 eh.e_shnum=1; sh.sh_name=1;sh.sh_addr=(uintptr_t)tests;sh.sh_size=sizeof tests;
 b.eh=&eh;b.sh=&sh;b.shstr="\0.tlhybrid.tests\0";
 unsetenv("TLHYBRID_FILTER");invoked=0;int all_rc=run_tests(&b), all_calls=invoked;
 setenv("TLHYBRID_FILTER","not_present",1);invoked=0;int none_rc=run_tests(&b), none_calls=invoked;
 setenv("TLHYBRID_FILTER","good",1);invoked=0;int one_rc=run_tests(&b), one_calls=invoked;
 printf("{\"all_rc\":%d,\"all_invoked\":%d,\"none_rc\":%d,\"none_invoked\":%d,\"one_rc\":%d,\"one_invoked\":%d}\n",all_rc,all_calls,none_rc,none_calls,one_rc,one_calls);
 return !(all_rc==1 && all_calls==2 && none_rc==0 && none_calls==0 && one_calls==1);
}
