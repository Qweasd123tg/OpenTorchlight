#include <cstring>
#define private public
#define protected public
#include <CEGUI.h>
#include "PetMenu.h"
#include "Character.h"
#include "Equipment.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "Achievements.h"
#include "Achievement.h"
#include "SoundBank.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalSpell,(CPetMenu*,const CEGUI::EventArgs*),"_ZN8CPetMenu15handle_SetSpellERKN5CEGUI9EventArgsE")
extern "C" bool candidateSpell(CPetMenu*,const CEGUI::EventArgs*) __asm__("_ZN8CPetMenu15handle_SetSpellERKN5CEGUI9EventArgsE");
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(keyFn,"_ZN11CKeyManager7keyHeldEj")
TL_FUNCTION(unlearnFn,"_ZN10CCharacter12unLearnSpellEi")
TL_FUNCTION(useFn,"_ZN7CGameUI14performItemUseER6CLevelP10CEquipmentP10CCharacterS5_S5_")
TL_FUNCTION(achievementsFn,"_ZN13CAchievements12getSingletonEv")
TL_FUNCTION(achievementFn,"_ZN13CAchievements14getAchievementE13EACHIEVEMENTS")
TL_FUNCTION(completeFn,"_ZN12CAchievement13forceCompleteEv")
TL_FUNCTION(soundFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
namespace {
struct Stop{};struct Case {unsigned mask,state,id,mutation,fault;};const Case* cs;autotest::Capture* cap;CPetMenu* menu;CCharacter* actors[3];CEquipment* items[2];CGameUI* uis[2];CSoundBank* banks[2];void* levels[2];CAchievements* achievements;CAchievement* achievement;unsigned calls;
template<class T>T& at(void* p,size_t off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}void n(int v){cap->add(&v,4);}int aid(void* p){if(!p)return 0;for(int i=0;i<3;++i)if(p==actors[i])return i+1;return 99;}int uid(void* p){return p==uis[0]?1:p==uis[1]?2:99;}int iid(void* p){return !p?0:p==items[0]?1:p==items[1]?2:99;}
void event(int kind){n(kind);++calls;if(cs->fault==calls)throw Stop();}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){event(1);n(aid(p));n(iid(p));n(int(type));if(cs->mutation){menu->m_pGameUI=uis[1];menu->m_pCharacter=actors[1];}return int(type)==41?bool(cs->mask&4):bool(cs->mask&16);}
bool key(CKeyManager* p,unsigned code){event(2);n((char*)p==(char*)uis[0]+0x590?1:(char*)p==(char*)uis[1]+0x590?2:99);n(code);if(cs->mutation==2)menu->m_pCharacter=actors[1];return cs->mask&32;}
void unlearn(CCharacter* p,int slot){event(3);n(aid(p));n(slot);if(cs->mutation)menu->m_pSoundBank=banks[1];}
// Reference ABI is a pointer, which also records the original's null-level path.
void use(CGameUI* p,CLevel* level,CEquipment* item,CCharacter* a,CCharacter* b,CCharacter* target){event(4);n(uid(p));n(!level?0:level==levels[0]?1:level==levels[1]?2:99);n(iid(item));n(aid(a));n(aid(b));n(aid(target));if(cs->mutation)menu->m_pCharacter=actors[2];}
void layout(CPetMenu* p){event(5);n(p==menu);n(aid(menu->m_pCharacter));if(cs->mutation)menu->m_pSoundBank=banks[1];}
CAchievements* singleton(){event(6);return achievements;}
CAchievement* lookup(CAchievements* p,EACHIEVEMENTS id){event(7);n(p==achievements);n(int(id));return achievement;}
void complete(CAchievement* p){event(8);n(p==achievement);}
void sound(CSoundBank* p,int index,Ogre::SceneNode* node,float a,float b,bool v){event(9);n(p==banks[0]?1:p==banks[1]?2:99);n(index);n(node==0);cap->add(&a,4);cap->add(&b,4);n(v);}
void ptr(unsigned char* p,size_t off,unsigned value){uintptr_t v=value;std::memcpy(p+off,&v,sizeof(v));}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;unsigned long long mm[(sizeof(CPetMenu)+16+7)/8],am[3][(sizeof(CCharacter)+7)/8]={0},em[2][(sizeof(CEquipment)+7)/8]={0},um[2][0x1000/8]={0},bm[2][32]={0},rm[2][(sizeof(CResourceManager)+7)/8]={0},lm[2][8]={0},acs[8]={0},ac[8]={0},wm[(sizeof(CEGUI::Window)+7)/8]={0};std::memset(mm,0xa5,sizeof(mm));cs=&c;cap=&out;calls=0;menu=(CPetMenu*)mm;achievements=(CAchievements*)acs;achievement=(CAchievement*)ac;void* vt[10]={0};vt[9]=(void*)&layout;*(void***)menu=vt;
 int states[]={2,40,41,42,43};for(unsigned i=0;i<3;++i){actors[i]=(CCharacter*)am[i];actors[i]->m_eAIState=static_cast<EAIState>(states[c.state]);actors[i]->m_pMaster=actors[0];}for(unsigned i=0;i<2;++i){items[i]=(CEquipment*)em[i];uis[i]=(CGameUI*)um[i];banks[i]=(CSoundBank*)bm[i];levels[i]=lm[i];CResourceManager* resource=(CResourceManager*)rm[i];resource->m_pLevel=(CLevel*)levels[i];actors[i]->m_pResourceManager=c.mask&64?resource:0;at<CEquipment*>(uis[i],0xb8)=c.mask&8?items[i]:0;at<CCharacter*>(uis[i],0xc8)=c.mask&2?actors[2]:0;}actors[0]->m_pMaster=actors[2];actors[1]->m_pMaster=0;
 menu->m_pGameUI=uis[0];menu->m_pCharacter=actors[0];menu->m_pSoundBank=banks[0];CEGUI::Window* window=(CEGUI::Window*)wm;unsigned ids[]={0,1,3,0xffffffffu};window->d_ID=ids[c.id];CEGUI::WindowEventArgs e(c.mask&1?window:0);detour::Set d;
#define R(N,F) TL_REDIRECT(d,N##Fn,&F)
 R(isa,isa);R(key,key);R(unlearn,unlearn);R(use,use);R(achievements,singleton);R(achievement,lookup);R(complete,complete);R(sound,sound);
#undef R
 if(d.failed())_exit(60);bool threw=false;try{if(ours)autotest::invoke(out,&candidateSpell,menu,static_cast<const CEGUI::EventArgs*>(&e));else autotest::invoke(out,&originalSpell,menu,static_cast<const CEGUI::EventArgs*>(&e));}catch(const Stop&){threw=true;}catch(...){_exit(61);}n(threw);n(calls);unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0,1);ptr(snapshot,0x58,aid(menu->m_pCharacter));ptr(snapshot,0x90,uid(menu->m_pGameUI));ptr(snapshot,0x91b8,menu->m_pSoundBank==banks[0]?1:menu->m_pSoundBank==banks[1]?2:99);cap->add(snapshot,sizeof(snapshot));}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(petmenu_set_spell){autotest::Coverage coverage("petmenu_set_spell",(uint64_t)(uintptr_t)&originalSpell);for(unsigned mask=0;mask<128;++mask)for(unsigned state=0;state<5;++state)for(unsigned id=0;id<4;++id)for(unsigned mutation=0;mutation<3;++mutation){Case c={mask,state,id,mutation,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    spell mismatch %u/%u/%u/%u exits %d/%d first %lu\n",mask,state,id,mutation,u.childStatus,v.childStatus,(unsigned long)f);coverage.report(host);return 1;}}coverage.report(host);return 0;}
TL_TEST(petmenu_spell_expected_exceptions){unsigned count=0;for(unsigned route=0;route<3;++route)for(unsigned fault=1;fault<=(route==0?6:route==1?4:2);++fault)for(unsigned mutation=0;mutation<3;++mutation){Case c={route==1?33u:25u,route==2?2u:0u,3,mutation,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    spell unwind mismatch %u/%u/%u exits %d/%d completed %u/%u\n",route,fault,mutation,u.childStatus,v.childStatus,u.capture.callCompleted,v.capture.callCompleted);return 1;}++count;}host->log("    EXPECTED SPELL EXCEPTIONS: %u matching unwinds, excluded from normal completion coverage\n",count);return 0;}
