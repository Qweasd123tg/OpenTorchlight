#include "AutoTest.h"
#include <cstdlib>
#include <clocale>
#include <cstring>
TL_ORIGINAL(unsigned,fltkFromMbOriginal,(char*,unsigned,const char*,unsigned),"fl_utf8from_mb")
TL_ORIGINAL(unsigned,fltkToMbOriginal,(const char*,unsigned,char*,unsigned),"fl_utf8to_mb")
extern "C" unsigned fltkFromMbCandidate(char*,unsigned,const char*,unsigned) __asm__("fl_utf8from_mb");
extern "C" unsigned fltkToMbCandidate(const char*,unsigned,char*,unsigned) __asm__("fl_utf8to_mb");
namespace {
struct Case{unsigned target,length,capacity,locale,data;};
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);unsetenv("LC_CTYPE");unsetenv("LANG");setenv("LC_ALL",c.locale&1?"UTF-8":"C",1);char*actual=setlocale(LC_CTYPE,c.locale&2?"C.UTF-8":"C");unsigned available=actual!=NULL;out.add(&available,4);char source[2048],dest[4160];std::memset(source,c.data?0x80:'A',sizeof(source));source[c.length]=0;std::memset(dest,0xa5,sizeof(dest));unsigned r=0;if(c.target){unsigned(*fn)(const char*,unsigned,char*,unsigned)=ours?fltkToMbCandidate:fltkToMbOriginal;if(autotest::beginInvocation(out,fn)){r=fn(source,c.length,dest+16,c.capacity);out.callCompleted=1;}}else{unsigned(*fn)(char*,unsigned,const char*,unsigned)=ours?fltkFromMbCandidate:fltkFromMbOriginal;if(autotest::beginInvocation(out,fn)){r=fn(dest+16,c.capacity,source,c.length);out.callCompleted=1;}}out.add(&r,4);out.add(dest,sizeof(dest));}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
static int runFltkMbLarge(const tlhybrid_host*host,unsigned target){int failures=0;const unsigned lengths[]={0,1,1023,1024,1025,1100};const unsigned caps[]={0,1,1023,1024,1101,4095};autotest::Stats stats={0,0,0};autotest::Coverage coverage(target?"complete_fltk_to_mb_large":"complete_fltk_from_mb_large",reinterpret_cast<uintptr_t>(target?reinterpret_cast<void(*)()>(&fltkToMbOriginal):reinterpret_cast<void(*)()>(&fltkFromMbOriginal)));unsigned cases=0;for(unsigned len=0;len<6;++len)for(unsigned cap=0;cap<6;++cap)for(unsigned locale=0;locale<4;++locale)for(unsigned data=0;data<2;++data){Case c={target,lengths[len],caps[cap],locale,data};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_fltk_source_mb_large",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);failures+=stats.incomplete+(coverage.completed!=cases);return failures;}

TL_TEST(complete_fltk_from_mb_large){return runFltkMbLarge(host,0);}
TL_TEST(complete_fltk_to_mb_large){return runFltkMbLarge(host,1);}
