#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "GameClientOwnedNative.h"
#include "GameClientUiOwner.h"
#include "tests/NativeEditorControls.h"
#include "NativeLevelPreloader.h"
#include "GameClientCpuTextures.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgreRectangle2D.h>
#include <OgreLight.h>
#include "GenericModel.h"
#include "Layout.h"
#include <fcntl.h>
#include <ucontext.h>
#include <execinfo.h>
TL_ORIGINAL(bool,gcuOld,(CGameClient*,bool),"_ZN11CGameClient18unloadCurrentLevelEb")
extern "C" bool gcuNew(CGameClient*,bool) __asm__("_ZN11CGameClient18unloadCurrentLevelEb");
TL_FUNCTION(gcuUIPlayer,"_ZN7CGameUI9setPlayerEP10CCharacter")
TL_FUNCTION(gcuUILevel,"_ZN7CGameUI8setLevelEP6CLevel")
TL_FUNCTION(gcuUICleanup,"_ZN7CGameUI17cleanupReferencesEv")
TL_FUNCTION(gcuUINotify,"_ZN7CGameUI16notifyOfDeletionEP10CCharacter")
namespace {
unsigned phase;
void fault(int sig,siginfo_t*info,void*raw){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/skills/ui-rest-20261019/gameclient-lifetime-signal.log",O_WRONLY|O_APPEND|O_CREAT,0600);if(fd>=0){ucontext_t*c=static_cast<ucontext_t*>(raw);char text[200];int n=std::snprintf(text,sizeof(text),"signal%d phase%u rip%llx address%p\n",sig,phase,(unsigned long long)c->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,text,n);void*frames[30];int count=backtrace(frames,30);backtrace_symbols_fd(frames,count,fd);close(fd);}signal(sig,SIG_DFL);raise(sig);}
void rectangleMaterial(Ogre::SimpleRenderable*,const std::string&name){if(name!="BaseWhiteNoLighting")std::abort();}
struct RectangleDuringConstruction {
    void* trampoline;detour::Set hooks;
    RectangleDuringConstruction():trampoline(MAP_FAILED){
        void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)std::abort();
        void*entry=dlsym(lib,"_ZN4Ogre16SimpleRenderable11setMaterialERKSs");dlclose(lib);if(!entry)std::abort();
        trampoline=mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);if(trampoline==MAP_FAILED)std::abort();
        unsigned char code[12]={0x48,0xb8,0,0,0,0,0,0,0,0,0xff,0xe0};
        typedef void(*Fn)(Ogre::SimpleRenderable*,const std::string&);Fn callback=&rectangleMaterial;std::memcpy(code+2,&callback,8);std::memcpy(trampoline,code,12);
        if(mprotect(trampoline,4096,PROT_READ|PROT_EXEC))std::abort();
        hooks.redirect(static_cast<char*>(entry),static_cast<char*>(entry),reinterpret_cast<Fn>(trampoline));if(hooks.failed())std::abort();
    }
    ~RectangleDuringConstruction(){hooks.restore();if(munmap(trampoline,4096))std::abort();}
};
nativegame::Services*native;
struct Case{unsigned seed;};
bool collecting;
void num(autotest::Capture&o,unsigned n){if(collecting)o.add(&n,4);}
autotest::Capture*capture;CGameClient*target;
void uiPlayer(CGameUI*p,CCharacter*c){num(*capture,301);num(*capture,p==target->m_pGameUI);num(*capture,c==NULL);}
void uiLevel(CGameUI*p,CLevel*l){num(*capture,307);num(*capture,p==target->m_pGameUI);num(*capture,l==NULL);}
void uiCleanup(CGameUI*p){num(*capture,311);num(*capture,p==target->m_pGameUI);}
void uiNotify(CGameUI*p,CCharacter*c){num(*capture,313);num(*capture,p==target->m_pGameUI);num(*capture,c==target->m_pPlayer?1:c==target->m_creationPet?2:99);}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=static_cast<Case*>(raw)->seed;phase=1000+seed;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_flags=SA_SIGINFO|SA_RESETHAND;action.sa_sigaction=&fault;sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);menugui::OwnedClient owner(*native->settings,native->master,*native->master->m_pSoundManager);CGameClient*client=owner.client;
 gameclient_cpu::Textures textures;Ogre::TexturePtr shadow,light;
 if(seed&1){shadow=textures.createManual("lifetime-shadow","General",Ogre::TEX_TYPE_2D,16+seed,16,0,Ogre::PF_A8R8G8B8,Ogre::TU_RENDERTARGET);client->m_shadowTexture=shadow.getPointer();shadow->getBuffer()->getRenderTarget()->addListener(client);}
 if(seed&2){light=textures.createManual("lifetime-light","General",Ogre::TEX_TYPE_2D,32,8+seed,0,Ogre::PF_A8R8G8B8,Ogre::TU_RENDERTARGET);client->m_lightTexture=light.getPointer();light->getBuffer()->getRenderTarget()->addListener(client);}
 if(seed&4)client->m_ambientLight=owner.scenes[0]->createLight("lifetime-light");
 {RectangleDuringConstruction graphics;
 if(seed&8)client->m_playerLight=new Ogre::Rectangle2D(true);
 if(seed&16)client->m_lightMultiplyQuad=new Ogre::Rectangle2D(false);
 if(seed&32)client->m_shadowQuad=new Ogre::Rectangle2D(true);}
 if(seed&64)client->m_menuSound=new CSoundBank(*native->master->m_pSoundManager,false);
 TSafePointer<CGenericModel> modelWeak[4];CGenericModel**slots[]={&client->m_menuModel0,&client->m_menuModel1,&client->m_menuModel2,&client->m_menuModel3};for(unsigned k=0;k<4;++k)if((seed>>(k+2))&1){*slots[k]=new CGenericModel(NULL,owner.scenes[0],static_cast<OGRE_UTILITIES::EPRIMITIVES>(0));(*slots[k])->setResourceManager(client->m_gameResources);modelWeak[k].setObject(*slots[k]);}
 TSafePointer<CLayout> layoutWeak;if(seed&16){client->m_menuLayout=new CLayout(client->m_gameResources,static_cast<ELAYOUT_TYPES>(0));layoutWeak.setObject(client->m_menuLayout);}
 TSafePointer<CGameUI> uiWeak;if(seed&32){gameclient_fixture::UiOwner ui(*native->settings,*client,owner.camera->m_cameras[0],owner.scenes[0],owner.scenes[1],owner.scenes[2],owner.resources);client->m_pGameUI=ui.release();uiWeak.setObject(client->m_pGameUI);}
 TSafePointer<CCharacter> playerWeak,petWeak;if(seed&64){client->m_pPlayer=nativegame::createPlayer(client->m_gameResources);playerWeak.setObject(client->m_pPlayer);}if(seed&8){client->m_creationPet=nativegame::createPlayer(client->m_gameResources);petWeak.setObject(client->m_creationPet);}
 TSafePointer<CLevel> levelWeak;if((seed&4)&&!(seed&(8|64))){editorlevel::ensurePreloader(native->master);client->m_level=new CLevel(L"client lifetime",native->settings,client,client->m_gameResources,owner.scenes[0],NULL,17,3);client->m_gameResources->m_pLevel=client->m_level;levelWeak.setObject(client->m_level);}
 TSafePointer<CGameClient> clientWeak;clientWeak.setObject(client);TSafePointer<CQuestManager> questWeak;questWeak.setObject(client->m_questManager);TSafePointer<CResourceManager> resourcesWeak;resourcesWeak.setObject(client->m_gameResources);TSafePointer<CSoundBank> bankWeak;bankWeak.setObject(client->m_menuSound);
 capture=&out;target=client;collecting=true;detour::Set uiServices;TL_REDIRECT(uiServices,gcuUIPlayer,&uiPlayer);TL_REDIRECT(uiServices,gcuUILevel,&uiLevel);TL_REDIRECT(uiServices,gcuUICleanup,&uiCleanup);TL_REDIRECT(uiServices,gcuUINotify,&uiNotify);if(uiServices.failed())_exit(64);
 typedef bool(*F)(CGameClient*,bool);F fn=ours?gcuNew:gcuOld;if(autotest::beginInvocation(out,fn)){num(out,fn(client,(seed&1)!=0));out.callCompleted=1;}num(out,clientWeak.getObject()==NULL);num(out,questWeak.getObject()==NULL);num(out,resourcesWeak.getObject()==NULL);num(out,bankWeak.getObject()==NULL);num(out,uiWeak.getObject()==NULL);num(out,levelWeak.getObject()==NULL);num(out,playerWeak.getObject()==NULL);num(out,petWeak.getObject()==NULL);for(unsigned k=0;k<4;++k)num(out,modelWeak[k].getObject()==NULL);num(out,layoutWeak.getObject()==NULL);
 if(seed&1)num(out,static_cast<gameclient_cpu::Target*>(shadow->getBuffer()->getRenderTarget())->listenerCount());
 if(seed&2)num(out,static_cast<gameclient_cpu::Target*>(light->getBuffer()->getRenderTarget())->listenerCount());
 num(out,owner.scenes[0]->hasLight("lifetime-light"));
 // The genuine complete D1 already ended the client, its members and bases.
 // The graph keeps only the external camera/dungeon/scene owners for cleanup.
 num(out,client->m_pPlayer==NULL);num(out,client->m_creationPet==NULL);num(out,client->m_level==NULL);num(out,client->m_gameResources->m_pLevel==NULL);num(out,client->m_targetCharacter.getObject()==NULL);num(out,client->m_targetItem.getObject()==NULL);collecting=false;
 if(playerWeak.getObject())nativegame::destroyPlayer(static_cast<CPlayer*>(playerWeak.getObject()));if(petWeak.getObject())nativegame::destroyPlayer(static_cast<CPlayer*>(petWeak.getObject()));mgClientDtor(client);owner.client=NULL;Ogre::NedAllocImpl::deallocBytes(client);
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_flags=SA_SIGINFO|SA_RESETHAND;action.sa_sigaction=&fault;sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;nativeeditor::Controls editor(services);native=&services;menugui::Audio audio(native->master);autotest::Stats stats={0,0,0};autotest::Coverage coverage("gameclient_unload",(uintptr_t)gcuOld);int failures=0;for(unsigned i=0;i<128;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool ok=!coverage.observe(host,a,b);if(!ok)host->log("    dtor case%u status%d/%d child%d/%d started%u/%u completed%u/%u\n",i,a.status,b.status,a.childStatus,b.childStatus,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);TL_CHECK(failures,ok);if(!ok)break;}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=128);}
}
TL_TEST(gameclient_unload){return systems_fixture::isolated(&worker,host);}
