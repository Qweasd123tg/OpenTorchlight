#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdint.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "LinuxUtils.h"
TL_ORIGINAL(bool,mainWaitOriginal,(),"_Z28WaitForPreviousProcessFinishv")
extern "C" bool mainWaitCandidate() __asm__("_Z28WaitForPreviousProcessFinishv");
extern int g_hRestartingFile;
namespace {
struct Case{unsigned mode;};const Case*current;autotest::Capture*cap;detour::Set*patch;
void word(unsigned x){cap->add(&x,sizeof(x));}
int lock(int fd,int operation){word(fd>=0);word(operation);patch->restore();if(current->mode==2&&fd>=0)close(fd);return flock(fd,operation);}
void side(void*raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);current=&c;cap=&out;
 char folder[]="/tmp/otl-lock-XXXXXX";if(!mkdtemp(folder))_exit(65);std::string base=std::string(folder)+"/";std::wstring old=LinuxUtils::gameHomePath;LinuxUtils::gameHomePath=std::wstring(base.begin(),base.end());
 if(c.mode!=1){mkdir((base+".runicgames").c_str(),0700);mkdir((base+".runicgames/Torchlight").c_str(),0700);}if(c.mode==3)mkdir((base+".runicgames/Torchlight/restarting.lock").c_str(),0700);
 g_hRestartingFile=71;detour::Set d;patch=&d;d.redirect(reinterpret_cast<char*>(&flock),reinterpret_cast<char*>(&flock),&lock);if(d.failed())_exit(64);
 bool(*fn)()=ours?mainWaitCandidate:mainWaitOriginal;if(autotest::beginInvocation(out,fn)){bool result=fn();out.callCompleted=1;word(result);}
 word(g_hRestartingFile);struct stat st;int exists=stat((base+".runicgames/Torchlight/restarting.lock").c_str(),&st);word(exists==0);if(!exists)word(S_ISREG(st.st_mode));
 d.restore();LinuxUtils::gameHomePath=old;unlink((base+".runicgames/Torchlight/restarting.lock").c_str());rmdir((base+".runicgames/Torchlight/restarting.lock").c_str());rmdir((base+".runicgames/Torchlight").c_str());rmdir((base+".runicgames").c_str());rmdir(folder);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_main_restart_wait){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_main_restart_wait",reinterpret_cast<uintptr_t>(&mainWaitOriginal));for(unsigned mode=0;mode<4;++mode){Case c={mode};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_main_restart_wait",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
