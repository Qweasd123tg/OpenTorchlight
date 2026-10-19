#include "AutoTest.h"
#include "GameMainRuntime.h"
#include "MainFileSandbox.h"
#include <cstdio>
TL_ORIGINAL(void,confirmOriginal,(),"_Z14confirmbackupsv")
extern "C" void confirmCandidate() __asm__("_Z14confirmbackupsv");
namespace {
struct Case{unsigned mode,count;};
void side(void* raw,autotest::Capture& out,bool ours){Case c=*static_cast<Case*>(raw);mainfiles::Sandbox s;std::string root=s.app+"saveBackup/",backup=root+"backup/",tmp=root+"tmpBackup/";mkdir(root.c_str(),0700);mkdir(tmp.c_str(),0700);
 if(c.mode!=1)mkdir(backup.c_str(),0700);if(c.mode==2){mainfiles::clear(backup);mainfiles::put(root+"backup","blocked");}if(c.mode==3)mainfiles::clear(tmp);if(c.mode==4)mainfiles::clear(root);
 if(c.mode!=2&&c.mode!=4){mainfiles::put(backup+"old.svt","old");mainfiles::put(backup+"old.bin","oldbin");mainfiles::put(backup+"README","readme");mainfiles::put(backup+".hidden","hidden");mkdir((backup+"folder").c_str(),0700);}
 mainfiles::put(s.save+"original.svt","untouched");mainfiles::put(tmp+"ignored.bin","bin");mainfiles::put(tmp+"README","readme");mainfiles::put(tmp+"UPPER.SVT","upper");
 for(unsigned i=0;i<c.count;++i){char n[40];std::sprintf(n,"slot_%02u.svt",i);std::string bytes(i*19,'\0');for(unsigned j=0;j<bytes.size();++j)bytes[j]=(j*5+i)%251;mainfiles::put(tmp+n,bytes);}if(c.count)mainfiles::put(tmp+"данные.svt","unicode");
 void(*fn)()=ours?confirmCandidate:confirmOriginal;if(autotest::beginInvocation(out,fn)){fn();out.callCompleted=1;}mainfiles::capture(out,s.base,".runicgames");}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_main_confirm_backups){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_main_confirm_backups",reinterpret_cast<uintptr_t>(&confirmOriginal));const unsigned counts[]={0,1,2,9,10,11,24};for(unsigned mode=0;mode<5;++mode)for(unsigned i=0;i<7;++i){Case c={mode,counts[i]};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_main_confirm_backups",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
