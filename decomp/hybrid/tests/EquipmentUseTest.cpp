#include <cstring>
#include <new>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Character.h"
#include "Effect.h"
#include "EffectManager.h"
#include "SkillManager.h"
#include "SoundBank.h"
#include "SteamStats.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentUse,(CEquipment*,CCharacter*,CBaseUnit*),"_ZN10CEquipment11useOnTargetEP10CCharacterP9CBaseUnit")
TL_FUNCTION(usIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(usJournal,"_ZN10CCharacter25incrementJournalStatisticE17EJournalStatistici")
TL_FUNCTION(usSkill,"_ZN10CCharacter19performUnknownSkillEP6CSkill")
TL_FUNCTION(usStats,"_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(usIncrement,"_ZN11CSteamStats13incrementStatE6ESTATSi")
TL_FUNCTION(usSound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
extern "C" void* useEquipmentTable[] __asm__("_ZTV10CEquipment");
extern "C" void* useCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" void tracedoriginalEquipmentUse(CEquipment*,CCharacter*,CBaseUnit*) __asm__("_ZN10CEquipment11useOnTargetEP10CCharacterP9CBaseUnit");
namespace {
typedef char effect_size[sizeof(CEffect)==0x138?1:-1];
typedef char character_size[sizeof(CCharacter)==0x778?1:-1];
typedef char owner_offset[__builtin_offsetof(CEffect,m_Owner)==0x48?1:-1];
typedef char master_offset[__builtin_offsetof(CCharacter,m_pMaster)==0x640?1:-1];
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T* get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned id,stack,charges,effects,skills,results,flags,mode;};
struct World;World* world;const Case* input;autotest::Capture* capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
TArrayList<CEffect*>& dynamicEffects(CEffectManager* p){return *reinterpret_cast<TArrayList<CEffect*>*>(p->m_EffectData10+0x30);}
struct World{
 Raw<CEquipment> item;Raw<CCharacter> actor,target;Raw<CBaseUnit> owners[2];Raw<CEffect> effects[4];Raw<CEffectManager> managers[2];Raw<CSkillManager> skills;Raw<CSoundBank> sounds;Raw<CSteamStats> stats;unsigned long long skillTokens[2];void* itemTable[112];void* targetTable[112];Ogre::SceneNode node;unsigned validCalls,applyCalls,journalCalls,skillCalls,soundCalls,stackCalls;bool changed;
 World():node(NULL),validCalls(0),applyCalls(0),journalCalls(0),skillCalls(0),soundCalls(0),stackCalls(0),changed(false){std::memcpy(itemTable,useEquipmentTable,sizeof(itemTable));std::memcpy(targetTable,useCharacterTable,sizeof(targetTable));void** t=itemTable+2;std::memcpy(item.get(),&t,sizeof(t));t=targetTable+2;std::memcpy(target.get(),&t,sizeof(t));for(unsigned m=0;m<2;++m)new(&dynamicEffects(managers[m].get()))TArrayList<CEffect*>;new(&skills.get()->m_OtherSkills)TArrayList<CSkill*>;for(unsigned i=0;i<4;++i){CBaseUnit* owner=i==3?NULL:owners[i%2].get();std::memcpy(reinterpret_cast<char*>(effects[i].get())+0x48,&owner,sizeof(owner));}for(unsigned i=0;i<input->effects;++i)dynamicEffects(managers[0].get()).add(effects[i].get());dynamicEffects(managers[1].get()).add(effects[3].get());for(unsigned i=0;i<(input->skills==3?1:input->skills);++i)skills.get()->m_OtherSkills.add(reinterpret_cast<CSkill*>(&skillTokens[i]));}
 ~World(){skills.get()->m_OtherSkills.~TArrayList<CSkill*>();for(unsigned m=0;m<2;++m)dynamicEffects(managers[m].get()).~TArrayList<CEffect*>();}
 int effectID(CEffect* e){for(unsigned i=0;i<4;++i)if(e==effects[i].get())return i;return -1;}
};
void arguments(CBaseUnit* target,CCharacter* actor,CBaseUnit* owner,CEffect* effect){number(target==world->target.get());number(actor==world->actor.get()?1:actor==NULL?0:-1);number(owner==world->owners[0].get()?0:owner==world->owners[1].get()?1:owner==NULL?2:-1);number(world->effectID(effect));}
bool valid(CBaseUnit* target,CCharacter* actor,CBaseUnit* owner,CEffect* effect){number(10);arguments(target,actor,owner,effect);unsigned n=world->validCalls++;if(input->mode==1&&!world->changed){world->changed=true;dynamicEffects(world->managers[0].get()).add(world->effects[3].get());}if(input->mode==2&&!world->changed){world->changed=true;dynamicEffects(world->managers[0].get())[0]=world->effects[2].get();}if(input->mode==3)world->item.get()->m_pEffectManager=world->managers[1].get();return (input->results>>(n%4))&1;}
bool apply(CBaseUnit* target,CCharacter* actor,CBaseUnit* owner,CEffect* effect){number(11);arguments(target,actor,owner,effect);unsigned n=world->applyCalls++;if(input->mode==4){world->item.get()->m_iUnknown238=3;world->item.get()->m_iUnknown248=8;}if(input->mode==5)world->item.get()->m_pSkillManager=world->skills.get();return (input->results>>(4+n%4))&1;}
bool isa(CBaseUnit* item,UNITTYPES::EUNITTYPES type){number(12);number(item==world->item.get());number(type);return type==UNITTYPES::POTION&&(input->flags&1);}
void journal(CCharacter* actor,EJournalStatistic statistic,int amount){number(13);number(actor==world->actor.get());number(statistic);number(amount);++world->journalCalls;if(input->mode==6)world->target.get()->m_pMaster=world->actor.get();}
CSteamStats* stats(){number(14);return world->stats.get();}
void increment(CSteamStats* p,ESTATS statistic,int amount){number(15);number(p==world->stats.get());number(statistic);number(amount);}
void skill(CCharacter* actor,CSkill* skill){number(16);number(actor==world->actor.get());number(skill==reinterpret_cast<CSkill*>(&world->skillTokens[0]));++world->skillCalls;if(input->mode==7){world->item.get()->m_iUnknown238=1;world->item.get()->m_iUnknown248=2;}}
void* sound(CSoundBank* p,int id,Ogre::SceneNode* node,float a,float b,bool flag){number(17);number(p==world->sounds.get());number(id);number(node==&world->node);real(a);real(b);number(flag);++world->soundCalls;if(input->mode==8){world->item.get()->m_iUnknown238=4;world->item.get()->m_iUnknown248=9;}return NULL;}
void stack(CEquipment* p,int amount){number(18);number(p==world->item.get());number(amount);++world->stackCalls;p->m_iUnknown238+=amount;}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;World w;world=&w;w.itemTable[105]=reinterpret_cast<void*>(&stack);w.targetTable[73]=reinterpret_cast<void*>(&valid);w.targetTable[74]=reinterpret_cast<void*>(&apply);static const int stacks[]={-3,0,1,2,5};static const int charges[]={-9999,-1,0,1,4};CEquipment* p=w.item.get();p->m_iUnknown238=stacks[c.stack];p->m_iUnknown248=charges[c.charges];p->m_pEffectManager=c.flags&2?NULL:w.managers[0].get();p->m_pSkillManager=c.skills==3?NULL:w.skills.get();p->m_pSoundBank=c.flags&4?w.sounds.get():NULL;w.target.get()->m_pMaster=c.flags&8?w.actor.get():NULL;w.actor.get()->m_pSceneNode=&w.node;if(c.mode==9&&c.effects>1)dynamicEffects(w.managers[0].get()).m_nCapacity=1;
 detour::Set patches;TL_REDIRECT(patches,usIsa,&isa);TL_REDIRECT(patches,usJournal,&journal);TL_REDIRECT(patches,usSkill,&skill);TL_REDIRECT(patches,usStats,&stats);TL_REDIRECT(patches,usIncrement,&increment);TL_REDIRECT(patches,usSound,&sound);if(patches.failed())_exit(42);for(unsigned repeat=0;repeat<2;++repeat){CCharacter* actor=c.flags&32?NULL:w.actor.get();CBaseUnit* target=c.flags&16?NULL:w.target.get();if(repeat==0){autotest::invoke(out,ours?&tracedoriginalEquipmentUse:&originalEquipmentUse,p,actor,target);}else{if(ours)p->useOnTarget(actor,target);else originalEquipmentUse(p,actor,target);}number(p->m_iUnknown238);number(p->m_iUnknown248);number(w.validCalls);number(w.applyCalls);number(w.journalCalls);number(w.skillCalls);number(w.soundCalls);number(w.stackCalls);number(dynamicEffects(w.managers[0].get()).size());} }
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_use_differential){
autotest::Coverage coverage0("equipment_use_differential",(uint64_t)(uintptr_t)&originalEquipmentUse);
int failures=0;for(unsigned n=0;n<14944;++n){Case c={n,n%5,(n/5)%5,(n/25)%4,(n/100)%4,(n/7)%256,(n/400)%32,0};if(n>=12800){unsigned j=n-12800;c.stack=3;c.charges=j%5;c.effects=1+j%3;c.skills=(j/3)%4;c.results=255;c.flags=j%16;c.mode=1+(j/128)%9;if(j>=1152){c.flags=32+(j%2?4:0);c.skills=0;c.mode=0;c.effects=j%4;c.results=255;}}autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    use case %u status %d/%d lengths %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    equipment use: 14944 cases, two calls per side\n");{coverage0.report(host);return failures;}}
