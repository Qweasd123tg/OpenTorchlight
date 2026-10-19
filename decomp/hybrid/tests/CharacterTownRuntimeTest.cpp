#include <cstring>
#include <execinfo.h>
#include <fcntl.h>
#include <ucontext.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Equipment.h"
#include "Inventory.h"
#include "LevelTemplateData.h"
#include "GameUI.h"
#include "SoundBank.h"
#undef private
#undef protected
#include "MenuGuiFixture.h"
#include "tests/FinishLevelFixture.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(void,ctNativeCtor,(CCharacter*,CResourceManager*),"_ZN10CCharacterC1EP16CResourceManager")
TL_ORIGINAL(void,ctOld,(CCharacter*,float,CLevel&),"_ZN10CCharacter17updateInTownTimerEfR6CLevel")
extern "C" void ctNew(CCharacter*,float,CLevel&) __asm__("_ZN10CCharacter17updateInTownTimerEfR6CLevel");
TL_FUNCTION(ctUI,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(ctCinematic,"_ZN7CGameUI18getUIIsInCinematicEv")
TL_FUNCTION(ctMax,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(ctHP,"_ZN10CCharacter8modifyHPEf")
TL_FUNCTION(ctRandom,"_ZN6CLevel23randomOpenPositionRangeERKN4Ogre7Vector3Effb")
TL_FUNCTION(ctDrop,"_ZN10CCharacter12dropToGroundER6CLevelfb")
TL_FUNCTION(ctSound,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(ctQuest,"_ZN9CBaseUnit14getIsQuestUnitEv")
TL_FUNCTION(ctRemove,"_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(ctPrice,"_ZN10CEquipment9sellPriceEv")
TL_FUNCTION(ctGold,"_ZN10CCharacter8giveGoldEi")
TL_FUNCTION(ctTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(ctModal,"_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b")
namespace {
struct Case{unsigned seed,control;};unsigned seed;bool armed;autotest::Capture*out;nativegame::Services*services;menugui::Fixture*menu;finishlevel::Fixture*world;CCharacter*self,*master;CEquipment*items[4];
unsigned diagnosticPhase,diagnosticOperation;bool diagnosticOurs;
void signalTrace(int signal,siginfo_t*info,void*context){
 int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-town-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);
 if(fd>=0){char line[220];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal=%d side=%u op=%u seed=%u phase=%u rip=%llx addr=%p\n",signal,unsigned(diagnosticOurs),diagnosticOperation,seed,diagnosticPhase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[48];int count=backtrace(stack,48);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);
}
void installSignalTrace(){struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&signalTrace;sigemptyset(&action.sa_mask);action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);}

void num(unsigned x){if(armed)out->add(&x,4);}void fp(float x){if(armed)out->add(&x,4);}void wide(const std::wstring&s){num(s.size());if(armed)out->add(s.data(),s.size()*sizeof(wchar_t));}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}unsigned id(const void*p){if(!p)return 0;if(p==self)return 1;if(p==master)return 2;for(unsigned i=0;i<4;++i)if(p==items[i])return 10+i;return 99;}
class Actor:public CCharacter{public:Actor():CCharacter(NULL){}virtual void setAIState(EAIState state){num(101);num(id(this));num(state);m_eAIState=state;}};
class Equipment:public CEquipment{public:Equipment():CEquipment(&world->resources){}virtual~Equipment(){num(103);num(id(this));}};
CGameUI*ui(CResourceManager*p){num(107);num(p==&world->resources);return seed%7?menu->ui:NULL;}
bool cinematic(CGameUI*p){num(109);num(p==menu->ui);return (seed/7)%5==0;}
int hpMax(CCharacter*p){num(113);num(id(p));return 39+seed%23;}
void hp(CCharacter*p,float amount){num(127);num(id(p));fp(amount);p->m_fHPFloat+=amount;}
Ogre::Vector3 random(CLevel*p,const Ogre::Vector3&v,float low,float high,bool include){num(131);num(p==&world->level);vec(v);fp(low);fp(high);num(include);return v+Ogre::Vector3(-3,2,5);}
void drop(CCharacter*p,CLevel&level,float height,bool force){num(137);num(id(p));num(&level==&world->level);fp(height);num(force);p->m_vPosition.y=-7;}
void sound(CSoundBank*p,int sample,float low,float high){num(139);num(p==master->m_levelSound);num(sample);fp(low);fp(high);}
bool quest(CBaseUnit*p){num(149);num(id(p));return !self->m_pMaster||(seed+id(p))%3==0;}
long long remove(CInventory*p,CEquipment*item){num(151);num(p==self->m_pInventory);num(id(item));for(unsigned i=0;i<p->m_equipmentRefs.size();++i)if(p->m_equipmentRefs[i]->m_pEquipment==item){CEquipmentRef*r=p->m_equipmentRefs[i];p->m_equipmentRefs.removeAt(i);r->m_pEquipment=NULL;delete r;break;}return 0;}
int price(CEquipment*p){num(157);num(id(p));return int((seed*11+id(p))%39)-17;}
void gold(CCharacter*p,int amount){num(163);num(id(p));num(amount);p->m_iGold+=amount;}
std::wstring translate(CStringTranslate*,const wchar_t*text){num(167);wide(text);return std::wstring(L"localized ")+text;}
void modal(CGameUI*p,std::wstring title,std::wstring message,bool flag){num(173);num(p==menu->ui);wide(title);wide(message);num(flag);}
void side(void*input,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(input);seed=c.seed;diagnosticOurs=ours;diagnosticOperation=0;diagnosticPhase=1;installSignalTrace();armed=false;out=&capture;self=new Actor;master=new Actor;self->m_pResourceManager=&world->resources;self->m_pMaster=seed&16?master:NULL;self->m_pInventory=new CInventory(self,17);self->m_vPosition=Ogre::Vector3(1,-2,3);master->m_vPosition=Ogre::Vector3(seed*.5f,4,-7);self->m_fHPFloat=-3;master->m_iGold=27;master->m_levelSound=seed&64?new CSoundBank(*services->master->m_pSoundManager,false):NULL;
 float times[]={-1,0,.1f,.5f,2,17};self->m_townTravelTime=times[(seed/3)%6];float deltas[]={0,.016f,.5f,5,-.25f};float elapsed=deltas[(seed/19)%5];CLevelTemplateData*data=new CLevelTemplateData(NULL);data->m_isTown=(seed/5)%2;world->level.m_pLevelTemplateData=data;world->level.m_iLevelDepth=(seed/11)%3-1;world->level.m_pGameClient=menu->nativeClient.client;menu->nativeClient.client->m_pGameUI=menu->ui;
 for(unsigned i=0;i<4;++i){items[i]=new Equipment;if(i<(seed/13)%5){CEquipmentRef*r=new CEquipmentRef;r->m_pEquipment=items[i];r->m_iSlot=int((seed+i*3)%23)-3;self->m_pInventory->m_equipmentRefs.add(r);}}
 detour::Set patches;
#define P(name,fn) TL_REDIRECT(patches,ct##name,&fn)
 P(UI,ui);P(Cinematic,cinematic);P(Max,hpMax);P(HP,hp);P(Random,random);P(Drop,drop);P(Sound,sound);P(Quest,quest);P(Remove,remove);P(Price,price);P(Gold,gold);P(Translate,translate);P(Modal,modal);
#undef P
 if(patches.failed())_exit(43);armed=true;typedef void(*F)(CCharacter*,float,CLevel&);F f=ours?ctNew:ctOld;diagnosticPhase=100;if(!autotest::beginInvocation(capture,f))return;f(self,elapsed,world->level);capture.callCompleted=1;diagnosticPhase=101;if(ours&&c.control)self->m_townTravelTime+=7;fp(self->m_townTravelTime);fp(self->m_fHPFloat);num(self->m_eAIState);vec(self->m_vPosition);num(master->m_iGold);num(self->m_pInventory->m_equipmentRefs.size());for(unsigned i=0;i<self->m_pInventory->m_equipmentRefs.size();++i){num(id(self->m_pInventory->m_equipmentRefs[i]->m_pEquipment));num(self->m_pInventory->m_equipmentRefs[i]->m_iSlot);}armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_town_runtime){initEmptyGlobals();tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);CStringTranslate translate(L"");services=&native;menugui::Fixture gui(*native.settings,native.scene);menu=&gui;finishlevel::Fixture level;world=&level;world->resources.m_pLevel=&world->level;world->resources.m_pSceneManager=native.scene;int failures=0;autotest::Coverage coverage("character_town_runtime",(uintptr_t)&ctOld);for(unsigned i=0;i<768;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    town seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);unsigned lo=j>20?j-20:0;lo=lo/4*4;for(unsigned k=lo;k<a.capture.length&&k<b.capture.length&&k<j+40;k+=4){unsigned x,y;std::memcpy(&x,a.capture.data+k,4);std::memcpy(&y,b.capture.data+k,4);host->log("    word%u %08x/%08x\n",k,x,y);}break;}coverage.report(host);return failures;}}coverage.report(host);Case c={37,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    town negative detected%u\n",unsigned(caught));return failures;}
