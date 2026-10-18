#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#define private public
#define protected public
#include "Player.h"
#include "CharacterSaveState.h"
#include "FileSystem.h"
#include "GenericModel.h"
#include "Level.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerFill,(CPlayer*,CCharacterSaveState&),"_ZN7CPlayer13fillSaveStateER19CCharacterSaveState")
extern "C" void newPlayerFill(CPlayer*,CCharacterSaveState&) __asm__("_ZN7CPlayer13fillSaveStateER19CCharacterSaveState");
TL_ORIGINAL(void,oldPlayerApply,(CPlayer*,CCharacterSaveState&),"_ZN7CPlayer14applySaveStateER19CCharacterSaveState")
extern "C" void newPlayerApply(CPlayer*,CCharacterSaveState&) __asm__("_ZN7CPlayer14applySaveStateER19CCharacterSaveState");
TL_ORIGINAL(void,oldPlayerFishing,(CPlayer*,float,CLevel&),"_ZN7CPlayer9fishingAIEfR6CLevel")
extern "C" void newPlayerFishing(CPlayer*,float,CLevel&) __asm__("_ZN7CPlayer9fishingAIEfR6CLevel");
TL_FUNCTION(pcore_baseFill,"_ZN10CCharacter13fillSaveStateER19CCharacterSaveState")
TL_FUNCTION(pcore_baseApply,"_ZN10CCharacter14applySaveStateER19CCharacterSaveState")
TL_FUNCTION(pcore_armor,"_ZN7CPlayer21calculateNaturalArmorEv")
TL_FUNCTION(pcore_fileSystem,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(pcore_modNames,"_ZN11CFileSystem18getEnabledModNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(pcore_rng,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(pcore_animation,"_ZNK13CGenericModel25animationPlayingSubstringERKSs")
TL_FUNCTION(pcore_splash,"_ZN10CCharacter13fishingSplashEv")
namespace {
struct Case{unsigned mode,index;};struct State{Case c;autotest::Capture*out;CPlayer*self;CCharacterSaveState*save;CFileSystem*files;unsigned rolls;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned v){active->out->add(&v,4);}void fp(float v){active->out->add(&v,4);}void text(const std::string&s){num(s.size());active->out->add(s.data(),s.size());}void wide(const std::wstring&s){num(s.size());active->out->add(s.data(),s.size()*4);}void strings(const TArrayList<std::wstring>&l){num(l.m_nCount);num(l.m_nCapacity);num(l.m_nGrowBy);for(unsigned i=0;i<l.size();++i)wide(l[i]);}
void baseFill(CCharacter*p,CCharacterSaveState&s){num(1);num(p==active->self);num(&s==active->save);active->self->m_cheatMarker=hash(1)&255;active->self->m_levelSaveSerial=int(hash(2));active->self->m_playTime=float(hash(3)%100)*.25f;}
void baseApply(CCharacter*p,CCharacterSaveState&s){num(2);num(p==active->self);num(&s==active->save);s.m_flag34=hash(4)&255;s.m_value68=int(hash(5));s.m_playTime=float(hash(6)%100)*.25f;}
void armor(CPlayer*p){num(3);p->m_naturalArmor=17;}
CFileSystem*files(){num(4);return active->files;}
void modNames(CFileSystem*p,TArrayList<std::wstring>*list){num(5);num(p==active->files);num(list->m_nGrowBy);for(unsigned i=0;i<hash(7)%6;++i)list->add(i&1?L"MOD B":L"mod-a");}
bool enabled(CSceneNodeObject*p){num(6);return p->m_bEnabled;}void setEnabled(CSceneNodeObject*p,bool value){num(7);num(value);p->m_bEnabled=value;}
float rng(float low,float high){num(8);fp(low);fp(high);unsigned v=hash(20+active->rolls++);return v%3==0?low:v%3==1?high:(low+high)*.5f;}
bool animation(const CGenericModel*,const std::string&name){num(9);text(name);return(hash(name=="FISHING_CAST"?30:31)&3)==0;}
void splash(CCharacter*){num(10);}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;active=&s;s.c=c;s.out=&out;s.rolls=0;s.self=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));s.files=static_cast<CFileSystem*>(autotest::allocate(sizeof(CFileSystem)));
 if(c.mode<2){s.save=new CCharacterSaveState;new(&s.self->m_loadedModNames)TArrayList<std::wstring>(1+hash(8)%3);for(unsigned i=0;i<hash(9)%5;++i)s.self->m_loadedModNames.add(i&1?L"old-b":L"old-a");for(unsigned i=0;i<hash(10)%5;++i)s.save->m_strings.add(i&1?L"saved-b":L"saved-a");s.self->m_cheatMarker=78;s.self->m_levelSaveSerial=-7;s.self->m_playTime=-3.5f;s.save->m_flag34=78;s.save->m_value68=-17;s.save->m_playTime=-11.5f;s.self->m_bEnabled=c.index&1;s.self->m_naturalArmor=-1;
 void**table=static_cast<void**>(autotest::allocate(0x50));table[0x40/8]=reinterpret_cast<void*>(&setEnabled);table[0x48/8]=reinterpret_cast<void*>(&enabled);*reinterpret_cast<void***>(s.self)=table;
 typedef void(*F)(CPlayer*,CCharacterSaveState&);F f=c.mode==0?(ours?newPlayerFill:oldPlayerFill):(ours?newPlayerApply:oldPlayerApply);if(!autotest::beginInvocation(out,f))return;f(s.self,*s.save);out.callCompleted=1;
 num(s.self->m_cheatMarker);num(s.self->m_levelSaveSerial);fp(s.self->m_playTime);num(s.save->m_flag34);num(s.save->m_value68);fp(s.save->m_playTime);num(s.self->m_bEnabled);num(s.self->m_naturalArmor);strings(s.self->m_loadedModNames);strings(s.save->m_strings);s.self->m_loadedModNames.~TArrayList();delete s.save;
 }else{const float values[]={-1,0,.999f,1,1.001f,1.749f,1.75f,1.751f,1.999f,2,2.001f,3,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};const float delays[]={-10,-4.001f,-4,-3.99f,0,1,9.99f,10,10.01f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};s.self->m_fishingTime=values[c.index%14];s.self->m_fishingDelay=delays[hash(11)%11];s.self->m_fishingValue854=float(hash(12)%101)*.125f;s.self->m_fishingValue860=float(int(hash(13)%7)-2)*.25f;s.self->m_pUnitModel=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));CLevel*level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));float elapsed=float(hash(14)%7)*.125f;typedef void(*F)(CPlayer*,float,CLevel&);F f=ours?newPlayerFishing:oldPlayerFishing;if(!autotest::beginInvocation(out,f))return;f(s.self,elapsed,*level);out.callCompleted=1;fp(s.self->m_fishingTime);fp(s.self->m_fishingDelay);fp(s.self->m_fishingValue854);fp(s.self->m_fishingValue860);num(s.rolls);}
}
void before(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void after(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address,unsigned count){detour::Set hooks;TL_REDIRECT(hooks,pcore_baseFill,&baseFill);TL_REDIRECT(hooks,pcore_baseApply,&baseApply);TL_REDIRECT(hooks,pcore_armor,&armor);TL_REDIRECT(hooks,pcore_fileSystem,&files);TL_REDIRECT(hooks,pcore_modNames,&modNames);TL_REDIRECT(hooks,pcore_rng,&rng);TL_REDIRECT(hooks,pcore_animation,&animation);TL_REDIRECT(hooks,pcore_splash,&splash);if(hooks.failed())return 1;autotest::Coverage coverage(name,address);for(unsigned i=0;i<count;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player mode%u seed%u status%d/%d bytes%lu/%lu\n",mode,i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=count||coverage.different||coverage.missing;}
}
TL_TEST(all_player_fill_save){return run(host,0,"all_player_fill_save",0x8fbf60,1024);}
TL_TEST(all_player_apply_save){return run(host,1,"all_player_apply_save",0x8f8680,1024);}
TL_TEST(all_player_fishing_ai){return run(host,2,"all_player_fishing_ai",0x8f0f60,4096);}
