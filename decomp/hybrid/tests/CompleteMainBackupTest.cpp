#include "AutoTest.h"
#include "GameMainRuntime.h"
#include "MainFileSandbox.h"
#include <cstdio>
TL_ORIGINAL(void,backupOriginal,(std::wstring),"_Z19backupOldSavesToTmpSbIwSt11char_traitsIwESaIwEE")
extern "C" void backupCandidate(std::wstring) __asm__("_Z19backupOldSavesToTmpSbIwSt11char_traitsIwESaIwEE");
namespace {
struct Case {unsigned mode,count;};
void side(void* raw,autotest::Capture& out,bool ours) {
 Case c=*static_cast<Case*>(raw);mainfiles::Sandbox s;mkdir((s.save+"tmpBackup").c_str(),0700);mainfiles::put(s.save+"tmpBackup/old.svt","old");mainfiles::put(s.save+"tmpBackup/.hidden","hidden");
 mkdir((s.save+"tmpBackup/empty").c_str(),0700);mainfiles::put(s.save+"ignored.txt","unchanged");mainfiles::put(s.save+"UPPER.SVT","upper");mkdir((s.save+"folder.svt").c_str(),0700);
 for(unsigned i=0;i<c.count;++i){char n[40];std::sprintf(n,"save_%02u.%s",i,i%2?"svt":"bin");std::string bytes(i*29,'\0');for(unsigned j=0;j<bytes.size();++j)bytes[j]=(j*j+7*i)%251;mainfiles::put(s.save+n,bytes);}
 if(c.count){mainfiles::put(s.save+"данные.bin","unicode");mainfiles::put(s.save+".hidden.svt","hidden source");}
 std::wstring target=L"Save/tmpBackup/";
 if(c.mode==1){target=L"Save/altBackup/";mkdir((s.save+"altBackup").c_str(),0700);mainfiles::put(s.save+"altBackup/keep.txt","keep");}
 if(c.mode==2){target=L"Save/blocked/";mainfiles::put(s.save+"blocked","blocked");}
 if(c.mode==3)target=L"Save/missing/child/";
 if(c.mode==4){mainfiles::clear(s.save);target=L"Save/tmpBackup/";}
 if(c.mode==5)target=L"Save/备份/";
 void(*fn)(std::wstring)=ours?backupCandidate:backupOriginal;if(autotest::beginInvocation(out,fn)){fn(target);out.callCompleted=1;}mainfiles::capture(out,s.base,".runicgames");
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_main_backup_saves) {
 autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_main_backup_saves",reinterpret_cast<uintptr_t>(&backupOriginal));
 const unsigned counts[]={0,1,2,9,10,11,24};for(unsigned mode=0;mode<6;++mode)for(unsigned i=0;i<7;++i){Case c={mode,counts[i]};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_main_backup_saves",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
