#include "tests/MenuGuiFixture.h"
#include "tests/SystemsFixtureWorker.h"
#include "GameClientUiOwner.h"
#include <fcntl.h>
#include <ucontext.h>
#include <execinfo.h>
TL_ORIGINAL(void,gcuDtor,(CGameUI*),"_ZN7CGameUID1Ev")
namespace {
unsigned phase;
void fault(int sig,siginfo_t*info,void*raw){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/skills/ui-rest-20261019/gameclient-ui-lifetime-signal.log",O_WRONLY|O_APPEND|O_CREAT,0600);if(fd>=0){ucontext_t*c=static_cast<ucontext_t*>(raw);char text[200];int n=std::snprintf(text,sizeof(text),"signal%d phase%u rip%llx address%p\n",sig,phase,(unsigned long long)c->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,text,n);void*frames[30];int count=backtrace(frames,30);backtrace_symbols_fd(frames,count,fd);close(fd);}signal(sig,SIG_DFL);raise(sig);}
int worker(const tlhybrid_host*host){struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_flags=SA_SIGINFO|SA_RESETHAND;action.sa_sigaction=&fault;sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);phase=1;tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);menugui::Client owner(*native.settings,native.master,*native.master->m_pSoundManager);phase=2;
 TSafePointer<CGameUI> weak;{
 gameclient_fixture::UiOwner ui(*native.settings,*owner.client,owner.camera->m_cameras[0],owner.scenes[0],owner.scenes[1],owner.scenes[2],owner.resources);weak.setObject(ui.ui);phase=3;host->log("    genuine UI C1 and typed empty owned pools completed; entering original D1\n");
 }phase=4;int failures=0;TL_CHECK(failures,weak.getObject()==NULL);host->log("    genuine UI C1/D1 lifetime completed; weak observer expired\n");return failures;
}
}
TL_TEST(gameclient_ui_lifetime){return systems_fixture::isolated(&worker,host);}
