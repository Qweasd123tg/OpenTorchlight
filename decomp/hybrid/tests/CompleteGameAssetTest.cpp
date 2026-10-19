#include "AutoTest.h"
#include <ucontext.h>
#include <execinfo.h>
#include "tests/SystemsNativeGame.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "Layout.h"
#include "DataGroup.h"
#include "FileUtilities.h"
TL_ORIGINAL(void,assetOriginal,(CGame*),"_ZN5CGame21convertAssetsToBinaryEv")
extern "C" void assetCandidate(CGame*) __asm__("_ZN5CGame21convertAssetsToBinaryEv");
TL_FUNCTION(assetApplication,"_ZN10FILESYSTEM18GetApplicationPathEv")
TL_FUNCTION(assetList,"_ZN10FILESYSTEM20GetFileListRecursiveERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES5_")
TL_FUNCTION(assetExists,"_ZN10FILESYSTEM10FileExistsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(assetLayoutLoad,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(assetEditorQuery,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(assetDataLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")

namespace {
const tlhybrid_host*fixtureHost;
void fault(int signal,siginfo_t*info,void*context){ucontext_t*uc=static_cast<ucontext_t*>(context);void*pc=reinterpret_cast<void*>(uc->uc_mcontext.gregs[REG_RIP]);Dl_info dl;std::memset(&dl,0,sizeof dl);dladdr(pc,&dl);fixtureHost->log("    asset-bootstrap signal=%d address=%p pc=%p symbol=%s offset=%lx\n",signal,info->si_addr,pc,dl.dli_sname?dl.dli_sname:"?",static_cast<unsigned long>(reinterpret_cast<uintptr_t>(pc)-reinterpret_cast<uintptr_t>(dl.dli_fbase)));void*stack[12];int n=backtrace(stack,12);for(int i=0;i<n;++i){std::memset(&dl,0,sizeof dl);dladdr(stack[i],&dl);fixtureHost->log("    asset-bootstrap frame %s +%lx\n",dl.dli_sname?dl.dli_sname:"?",static_cast<unsigned long>(reinterpret_cast<uintptr_t>(stack[i])-reinterpret_cast<uintptr_t>(dl.dli_fbase)));}_exit(128+signal);}
autotest::Capture*cap;unsigned mode,cacheMask;CGameClient*client;CResourceManager*resources;
void number(unsigned n){cap->add(&n,4);}
bool editorQuery(CResourceManager*receiver){number(7);number(receiver==resources);return false;}
std::wstring application(){number(1);return L"/asset/base/";}
const wchar_t*layouts[]={L"/asset/UI/skip.layout",L"/UI/root.layout",L"Mixed/Castle.layout",L"/asset/\u0417\u0430\u043c\u043e\u043a.layout",L"notui.layout"};
void list(const std::wstring&base,TArrayList<std::wstring>&files,const std::wstring&pattern){number(2);cap->addText(base);cap->addText(pattern);number(files.size());
 if(pattern==L"*.layout"){if(mode==0||mode==1)return;for(unsigned i=0;i<(mode==2?1u:5u);++i)files.add(layouts[i]);}
 else if(mode!=0){if(pattern==L"*.dat"){files.add(L"one.dat");if(mode>=4)files.add(L"second.dat");}else if(pattern==L"*.hie")files.add(L"tree.hie");else if(pattern==L"*.animation")files.add(L"walk.animation");}
}
bool exists(const std::wstring&path){number(3);cap->addText(path);return mode==5 || ((cacheMask&1)&&path.find(L"ROOT")!=std::wstring::npos) || ((cacheMask&2)&&path.find(L"CASTLE")!=std::wstring::npos);}
void loadLayout(CLayout*layout,const std::wstring&path,bool objects,CTimerStatics*timer,bool force,bool ignore,unsigned seed){number(4);number(layout->getResourceManager()==resources);cap->addText(path);number(objects);number(timer==NULL);number(force);number(ignore);number(seed);}
void loadData(CDataGroup*group,const std::wstring&path,CTimerStatics*timer){number(5);cap->addText(path);number(timer==NULL);number(group->m_pParent==NULL);number(group->m_DataValues.size());number(group->m_DataGroups.size());}
void log(Ogre::LogManager*logger,const std::string&message,Ogre::LogMessageLevel level,bool mask){number(6);number(logger==Ogre::LogManager::getSingletonPtr());cap->addText(message);number(level);number(mask);}
struct Case{unsigned mode,cache,missing;};
void initLayoutGlobals(){const uintptr_t addresses[]={0x145b3e0,0x1462960,0x14646a0,0x1466280,0x14a4320};for(unsigned i=0;i<5;++i){void*p;std::memcpy(&p,reinterpret_cast<void*>(addresses[i]),8);if(!p)new(reinterpret_cast<void*>(addresses[i]))std::string;std::memcpy(&p,reinterpret_cast<void*>(addresses[i]+8),8);if(!p)new(reinterpret_cast<void*>(addresses[i]+8))std::wstring;}}
struct DefaultScene{CMasterResourceManager*master;Ogre::SceneManager*previous;DefaultScene(CMasterResourceManager*m,Ogre::SceneManager*s):master(m),previous(m->m_pDefaultSceneManager){m->m_pDefaultSceneManager=s;}~DefaultScene(){master->m_pDefaultSceneManager=previous;}};

void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;struct sigaction action;std::memset(&action,0,sizeof action);action.sa_sigaction=&fault;sigemptyset(&action.sa_mask);action.sa_flags=SA_SIGINFO;sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);mode=c.mode;cacheMask=c.cache;SystemsNativeGame native(Ogre::Root::getSingletonPtr(),CMasterResourceManager::getSingleton()->m_pSettings);CGame*g=native.game;g->m_gameClient=c.missing==1?NULL:client;CResourceManager*saved=client->m_gameResources;if(c.missing==2)client->m_gameResources=NULL;
 detour::Set boundary;TL_REDIRECT(boundary,assetEditorQuery,&editorQuery);TL_REDIRECT(boundary,assetApplication,&application);TL_REDIRECT(boundary,assetList,&list);TL_REDIRECT(boundary,assetExists,&exists);TL_REDIRECT(boundary,assetLayoutLoad,&loadLayout);TL_REDIRECT(boundary,assetDataLoad,&loadData);
 void*bridge=mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);if(bridge==MAP_FAILED)_exit(68);unsigned char jump[]={0x48,0xb8,0,0,0,0,0,0,0,0,0xff,0xe0};void(*callback)(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool)=&log;std::memcpy(jump+2,&callback,8);std::memcpy(bridge,jump,12);if(mprotect(bridge,4096,PROT_READ|PROT_EXEC))_exit(68);void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)_exit(68);char*entry=static_cast<char*>(dlsym(lib,"_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb"));dlclose(lib);if(!entry)_exit(68);boundary.redirect(entry,entry,reinterpret_cast<void(*)(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool)>(bridge));if(boundary.failed())_exit(64);
 void(*fn)(CGame*)=ours?assetCandidate:assetOriginal;if(autotest::beginInvocation(out,fn)){fn(g);out.callCompleted=1;}
 boundary.restore();munmap(bridge,4096);client->m_gameResources=saved;g->m_gameClient=NULL;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){fixtureHost=host;nativegame::Services native;initLayoutGlobals();DefaultScene defaults(native.master,native.scene);menugui::Audio audio(native.master);menugui::Client actual(*native.settings,native.master,*native.master->m_pSoundManager);client=actual.client;resources=actual.resources;autotest::Stats stats={0,0,0};autotest::Coverage cov("complete_game_asset",reinterpret_cast<uintptr_t>(assetOriginal));unsigned n=0;int failures=0;for(unsigned mode=0;mode<6;++mode)for(unsigned cache=0;cache<4;++cache)for(unsigned missing=0;missing<3;++missing){if(missing&&mode>1&&mode!=5)continue;Case c={mode,cache,missing};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_game_asset",n++,&cov);TL_CHECK(failures,ok);}cov.report(host);return failures+stats.incomplete+(cov.completed!=n);}
}
TL_TEST(complete_game_asset){return systems_fixture::isolated(&worker,host);}
