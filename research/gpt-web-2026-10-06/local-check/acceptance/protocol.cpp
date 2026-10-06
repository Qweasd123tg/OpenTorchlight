#include "AutoTest.h"
#include <cstdio>
#include <cstdarg>
namespace autotest { char g_arena[kArenaSize];size_t g_arenaUsed=0;Outcome g_outcomes[2]; }
static int x=10,y=20;
static void logline(const char* f,...){va_list a;va_start(a,f);vprintf(f,a);va_end(a);}
static void report(autotest::Capture& c){c.addHeapInUse();c.add(autotest::g_arena,autotest::g_arenaUsed);}
static void tail_original(void*,autotest::Capture& c){autotest::g_arena[300000]=1;report(c);}
static void tail_wrong(void*,autotest::Capture& c){autotest::g_arena[300000]=2;report(c);}
static void pointer_original(void*,autotest::Capture& c){c.addPointer(&x);report(c);}
static void pointer_wrong(void*,autotest::Capture& c){c.addPointer(&y);report(c);}
static void incomplete(void*,autotest::Capture&){_exit(0);}
static void complete(void*,autotest::Capture&){}
int main(){
 tlhybrid_host host={TLHYBRID_ABI_VERSION,logline}; autotest::Stats s={0,0,0};
 bool accepted=autotest::compareCase(incomplete,complete,0,s,&host,"incomplete-protocol",0);
 printf("incomplete_protocol accepted=%d same=%d failed=%d different=%d\n",accepted,s.same,s.bothFailed,s.different);
 return 0;
}
