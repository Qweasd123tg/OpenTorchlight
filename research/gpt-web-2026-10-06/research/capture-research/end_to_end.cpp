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
int main(){
 tlhybrid_host host={TLHYBRID_ABI_VERSION,logline};
 autotest::Stats a={0,0,0},b={0,0,0};
 autotest::g_arenaUsed=300001;
 bool ta=autotest::compareCase(tail_original,tail_wrong,0,a,&host,"different-tail",0);
 autotest::g_arenaUsed=0;
 bool pb=autotest::compareCase(pointer_original,pointer_wrong,0,b,&host,"different-pointer",0);
 printf("different_tail accepted=%d same=%d failed=%d different=%d\n",ta,a.same,a.bothFailed,a.different);
 printf("different_pointer accepted=%d same=%d failed=%d different=%d\n",pb,b.same,b.bothFailed,b.different);
 return !(ta&&pb&&a.same==1&&b.same==1);
}
