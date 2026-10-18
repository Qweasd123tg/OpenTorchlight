#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "LinuxUtils.h"
#include "GameMainRuntime.h"
TL_ORIGINAL(void,removeOriginal,(),"_Z14removeTmpFilesv")
extern "C" void removeCandidate() __asm__("_Z14removeTmpFilesv");
TL_ORIGINAL(bool,activateOriginal,(CGame*),"_Z22ActivateRestartProcessP5CGame")
extern "C" bool activateCandidate(CGame*) __asm__("_Z22ActivateRestartProcessP5CGame");
TL_FUNCTION(filesLaunch,"_ZN10ShellUtils13LaunchProgramERKSsRKSt6vectorISsSaISsEE")
extern int g_hRestartingFile;
extern std::wstring UTF8ToUTF32(const std::string&);
namespace {
struct Case{unsigned target,mode;};autotest::Capture*cap;std::string base;void word(unsigned x){cap->add(&x,sizeof(x));}
void launch(const std::string&p,const std::vector<std::string>&args){word(1);cap->addText(p.substr(base.size()));word(args.size());for(unsigned i=0;i<args.size();++i)cap->addText(args[i]);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;char folder[]="/tmp/otl-main-files-XXXXXX";if(!mkdtemp(folder))_exit(65);base=std::string(folder)+"/";std::wstring oldHome=LinuxUtils::gameHomePath,oldData=LinuxUtils::gameDataPath;LinuxUtils::gameHomePath=UTF8ToUTF32(base);LinuxUtils::gameDataPath=UTF8ToUTF32(base);
 std::string app=base+".runicgames/Torchlight/",backup=app+"Save/tmpBackup/";mkdir((base+".runicgames").c_str(),0700);if(c.mode!=1)mkdir(app.c_str(),0700);mkdir((app+"Save").c_str(),0700);mkdir(backup.c_str(),0700);
 const char*files[]={"a.svt","данные.bin","README",".hidden","folder"};if(c.target==0&&c.mode>=2)for(unsigned i=0;i<5;++i){if(i==4)mkdir((backup+files[i]).c_str(),0700);else{std::ofstream f((backup+files[i]).c_str());f<<i;}}int held=-1;
 if(c.target==1&&c.mode==2){held=open((app+"restarting.lock").c_str(),O_CREAT|O_RDWR,0600);if(held<0||flock(held,LOCK_EX|LOCK_NB))_exit(66);}if(c.target==1&&c.mode==3)mkdir((app+"restarting.lock").c_str(),0700);g_hRestartingFile=0;
 detour::Set d;TL_REDIRECT(d,filesLaunch,&launch);if(d.failed())_exit(64);
 if(c.target==0){void(*fn)()=ours?removeCandidate:removeOriginal;if(autotest::beginInvocation(out,fn)){fn();out.callCompleted=1;}for(unsigned i=0;i<5;++i){struct stat st;word(stat((backup+files[i]).c_str(),&st)==0);}}
 else{bool(*fn)(CGame*)=ours?activateCandidate:activateOriginal;if(autotest::beginInvocation(out,fn)){bool r=fn(NULL);out.callCompleted=1;word(r);}word(g_hRestartingFile>=0);if(g_hRestartingFile>=0)close(g_hRestartingFile);if(held>=0)close(held);}
 d.restore();LinuxUtils::gameHomePath=oldHome;LinuxUtils::gameDataPath=oldData;for(unsigned i=0;i<5;++i){unlink((backup+files[i]).c_str());rmdir((backup+files[i]).c_str());}unlink((app+"restarting.lock").c_str());rmdir((app+"restarting.lock").c_str());rmdir(backup.c_str());rmdir((app+"Save").c_str());rmdir(app.c_str());rmdir((base+".runicgames").c_str());rmdir(folder);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned target){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;const char*name=target?"complete_main_activate_restart":"complete_main_remove_tmp";autotest::Coverage coverage(name,target?reinterpret_cast<uintptr_t>(&activateOriginal):reinterpret_cast<uintptr_t>(&removeOriginal));for(unsigned mode=0;mode<4;++mode){Case c={target,mode};bool ok=autotest::compareCase(original,candidate,&c,stats,host,name,cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
}
TL_TEST(complete_main_remove_tmp){return run(host,0);}TL_TEST(complete_main_activate_restart){return run(host,1);}
