#include "AutoTest.h"
#include "GameMainRuntime.h"
#include <vector>
TL_ORIGINAL(bool,restartArgsOriginal,(int,char**),"_Z27CheckForRestartProcessStartiPPc")
extern "C" bool restartArgsCandidate(int,char**) __asm__("_Z27CheckForRestartProcessStartiPPc");
namespace {
struct Case{int count;unsigned mode;};
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);std::vector<std::string> strings;strings.push_back(c.mode==1?"--restart":"torchlight");
 for(int i=1;i<c.count;++i){std::string s=c.mode==2?"--Restart":c.mode==3?"--restart=1":c.mode==4?std::string(8192,'x'):"";if((c.mode==5&&i==1)||(c.mode==6&&i==c.count-1)||(c.mode==7&&i==c.count/2))s="--restart";strings.push_back(s);}
 std::vector<char*> args;for(unsigned i=0;i<strings.size();++i)args.push_back(const_cast<char*>(strings[i].c_str()));args.push_back(NULL);bool(*fn)(int,char**)=ours?restartArgsCandidate:restartArgsOriginal;if(autotest::beginInvocation(out,fn)){bool r=fn(c.count,c.count<=0?NULL:&args[0]);out.callCompleted=1;out.add(&r,sizeof(r));}
 for(unsigned i=0;i<strings.size();++i)out.addText(strings[i]);}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_main_restart_args){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_main_restart_args",reinterpret_cast<uintptr_t>(&restartArgsOriginal));const int counts[]={-1,0,1,2,3,15};for(unsigned i=0;i<6;++i)for(unsigned mode=0;mode<8;++mode){Case c={counts[i],mode};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_main_restart_args",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
