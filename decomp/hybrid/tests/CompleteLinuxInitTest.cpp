#include "AutoTest.h"
#include "tests/Detour.h"
#include "LinuxUtils.h"
#include <binreloc.h>
#include <clocale>
#include <cstdlib>
#include <cstring>
TL_ORIGINAL(void,linuxInitOriginal,(),"_ZN10LinuxUtils4InitEv")
extern "C" void linuxInitCandidate() __asm__("_ZN10LinuxUtils4InitEv");
TL_FUNCTION(initReloc,"ZOLu33026715730109_br_init")
TL_FUNCTION(initFind,"ZOLu33026715730109_br_find_exe_dir")
TL_FUNCTION(initMessage,"_Z11MessageBoxAPvPKcS1_i")
TL_FUNCTION(initCrash,"_ZN10LinuxUtils13crash_handlerEi")
namespace {
struct Case{unsigned mode,path,temp;};const Case*current;autotest::Capture*cap;int terminationFd=-1;
void word(unsigned x){cap->add(&x,sizeof(x));}
int reloc(BrInitError*error){word(1);word(error!=NULL);if(error)*error=BR_INIT_ERROR_DISABLED;return current->mode!=1;}
char*find(const char*fallback){word(2);word(fallback!=NULL);const char*paths[]={"/game","/game/","/игра/游戏"};return current->mode==2?NULL:strdup(paths[current->path]);}
char*locale(int category,const char*name){word(3);word(category);if(name)cap->addText(std::string(name));else word(0x1234);return current->mode==3?NULL:const_cast<char*>("C.UTF-8");}
char*environment(const char*name){word(4);cap->addText(std::string(name));if(!std::strcmp(name,"HOME")){const char*paths[]={"/home/test","/home/test/","/дом/用户"};return current->mode==4?NULL:const_cast<char*>(paths[(current->path+current->temp)%3]);}if(!std::strcmp(name,"TMPDIR")){const char*paths[]={NULL,"/tmp","/tmp/","/временно/目录"};return const_cast<char*>(paths[current->temp]);}cap->issue=autotest::Capture::InvalidReport;return NULL;}
typedef void(*Handler)(int);
Handler signals(int number,Handler callback){word(5);word(number);word(reinterpret_cast<char*>(callback)==initCrash_original||reinterpret_cast<char*>(callback)==initCrash_linked);return SIG_DFL;}
int message(void*owner,const char*text,const char*title,int type){word(6);word(owner!=NULL);cap->addText(std::string(text));cap->addText(std::string(title));word(type);return 1;}
void stop(int status){word(7);word(status);word(1);cap->addText(LinuxUtils::gameDataPath);cap->addText(LinuxUtils::gameHomePath);cap->addText(LinuxUtils::gameTempPath);if(terminationFd>=0&&!autotest::writeReport(terminationFd,*cap))_exit(253);_exit(status);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;LinuxUtils::gameDataPath=L"old-data/";LinuxUtils::gameHomePath=L"old-home/";LinuxUtils::gameTempPath=L"old-temp/";
 detour::Set d;TL_REDIRECT(d,initReloc,&reloc);TL_REDIRECT(d,initFind,&find);TL_REDIRECT(d,initMessage,&message);d.redirect(reinterpret_cast<char*>(&setlocale),reinterpret_cast<char*>(&setlocale),&locale);d.redirect(reinterpret_cast<char*>(&getenv),reinterpret_cast<char*>(&getenv),&environment);d.redirect(reinterpret_cast<char*>(&signal),reinterpret_cast<char*>(&signal),&signals);d.redirect(reinterpret_cast<char*>(&exit),reinterpret_cast<char*>(&exit),&stop);if(d.failed())_exit(64);
 void(*fn)()=ours?linuxInitCandidate:linuxInitOriginal;if(autotest::beginInvocation(out,fn)){fn();out.callCompleted=1;}
 word(0);out.addText(LinuxUtils::gameDataPath);out.addText(LinuxUtils::gameHomePath);out.addText(LinuxUtils::gameTempPath);d.restore();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_linux_init){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_linux_init",reinterpret_cast<uintptr_t>(&linuxInitOriginal));for(unsigned path=0;path<3;++path)for(unsigned temp=0;temp<4;++temp){Case c={0,path,temp};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_linux_init",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
namespace {
void terminationChild(Case& c,autotest::Outcome& outcome,bool ours){int fd[2];outcome.capture.reset();outcome.reportValid=false;outcome.childStatus=-1;if(pipe(fd))return;pid_t pid=fork();if(!pid){close(fd[0]);terminationFd=fd[1];alarm(3);autotest::Capture capture;capture.reset();side(&c,capture,ours);_exit(252);}close(fd[1]);if(pid>0)outcome.reportValid=autotest::readReport(fd[0],outcome.capture,&outcome.reportStarted);close(fd[0]);if(pid>0){int status;while(waitpid(pid,&status,0)<0&&errno==EINTR){}outcome.childStatus=status;}}
}
TL_TEST(complete_linux_init_expected_termination){unsigned count=0;for(unsigned mode=1;mode<5;++mode)for(unsigned path=0;path<3;++path){Case c={mode,path,0};autotest::Outcome a,b;terminationChild(c,a,false);terminationChild(c,b,true);if(!a.reportValid||!b.reportValid||!WIFEXITED(a.childStatus)||!WIFEXITED(b.childStatus)||WEXITSTATUS(a.childStatus)!=1||WEXITSTATUS(b.childStatus)!=1||!a.capture.callStarted||!b.capture.callStarted||a.capture.callCompleted||b.capture.callCompleted||a.capture.issue||b.capture.issue||a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length)){host->log("    expected Linux termination mismatch %u/%u statuses %d/%d valid %u/%u\n",mode,path,a.childStatus,b.childStatus,a.reportValid,b.reportValid);return 1;}++count;}host->log("    Linux Init: %u matching expected exit-boundary reports, started1/completed0; no completion credit\n",count);return 0;}
