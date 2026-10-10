#include <cstring>
#include <new>
#include <climits>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Character.h"
#include "Effect.h"
#include "EffectManager.h"
#include "SkillManager.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalCanUse,(CEquipment*,CCharacter*,CBaseUnit*),"_ZN10CEquipment14canUseOnTargetEP10CCharacterP9CBaseUnit")
TL_FUNCTION(cuIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(cuLevel,"_ZN10CEquipment19getLevelRequirementEP10CCharacter")
TL_FUNCTION(cuBusy,"_ZN10CCharacter20performingSkillLooseEv")
TL_FUNCTION(cuSkill,"_ZN6CSkill35canAffixesAndEffectsBeAppliedToUnitEP9CBaseUnitP10CCharacter")
extern "C" void* canUseEquipmentTable[] __asm__("_ZTV10CEquipment");
extern "C" void* canUseCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" bool tracedoriginalCanUse(CEquipment*,CCharacter*,CBaseUnit*) __asm__("_ZN10CEquipment14canUseOnTargetEP10CCharacterP9CBaseUnit");
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,flags,effects,skills,results,mode,target;int charges,level,requirement;};
const Case*input;autotest::Capture*capture;
void number(int x){capture->add(&x,sizeof(x));}
TArrayList<CEffect*>& effects(CEffectManager*p){return *reinterpret_cast<TArrayList<CEffect*>*>(p->m_EffectData10+0x30);}
struct World;World*world;
struct World{
 Raw<CEquipment>item,targetItem;Raw<CCharacter>actor,target;Raw<CBaseUnit>owners[2];Raw<CEffect>eff[4];Raw<CEffectManager>managers[2];Raw<CSkillManager>skills[2];unsigned long long tokens[4];void*table[112];void*otherTable[112];unsigned validCalls,skillCalls;bool changed;CBaseUnit*selected;
 World():validCalls(0),skillCalls(0),changed(false){
  std::memcpy(table,canUseCharacterTable,sizeof(table));void**t=table+2;std::memcpy(target.get(),&t,sizeof(t));
  std::memcpy(otherTable,canUseEquipmentTable,sizeof(otherTable));t=otherTable+2;std::memcpy(targetItem.get(),&t,sizeof(t));
  for(unsigned j=0;j<2;++j){new(&effects(managers[j].get()))TArrayList<CEffect*>;new(&skills[j].get()->m_OtherSkills)TArrayList<CSkill*>;}
  for(unsigned j=0;j<4;++j){CBaseUnit*owner=j==3?NULL:owners[j%2].get();std::memcpy(reinterpret_cast<char*>(eff[j].get())+0x48,&owner,sizeof(owner));}
  for(unsigned j=0;j<input->effects;++j)effects(managers[0].get()).add(eff[j].get());effects(managers[1].get()).add(eff[3].get());
  for(unsigned j=0;j<input->skills;++j)skills[0].get()->m_OtherSkills.add(reinterpret_cast<CSkill*>(&tokens[j]));
  skills[1].get()->m_OtherSkills.add(reinterpret_cast<CSkill*>(&tokens[3]));
  selected=input->target==0?static_cast<CBaseUnit*>(target.get()):input->target==1?static_cast<CBaseUnit*>(targetItem.get()):NULL;
 }
 ~World(){for(unsigned j=0;j<2;++j){effects(managers[j].get()).~TArrayList<CEffect*>();skills[j].get()->m_OtherSkills.~TArrayList<CSkill*>();}}
 int effectID(CEffect*e){for(unsigned j=0;j<4;++j)if(e==eff[j].get())return j;return -1;}
};
bool valid(CBaseUnit*t,CCharacter*c,CBaseUnit*owner,CEffect*e){number(10);number(t==world->selected);number(c==world->actor.get());number(owner==world->owners[0].get()?0:owner==world->owners[1].get()?1:owner?3:2);number(world->effectID(e));unsigned call=world->validCalls++;
 if(input->mode==1&&!world->changed){world->changed=true;effects(world->managers[0].get()).add(world->eff[3].get());}
 if(input->mode==2)world->item.get()->m_pEffectManager=world->managers[1].get();
 if(input->mode==3&&effects(world->managers[0].get()).size()>1)effects(world->managers[0].get())[1]=world->eff[3].get();
 if(input->mode==4)world->item.get()->m_pSkillManager=world->skills[1].get();
 if(input->mode==5)world->target.get()->m_pMaster=world->actor.get();
 return (input->results>>(call%4))&1;
}
int level(CEquipment*p,CCharacter*c){number(11);number(p==world->item.get());number(c==world->actor.get());if(input->mode==6){world->actor.get()->m_iUnitLevel=INT_MIN;world->target.get()->m_iUnitLevel=INT_MIN;}return input->requirement;}
bool busy(CCharacter*c){number(12);number(c==world->target.get());if(input->mode==7)world->item.get()->m_pSkillManager=world->skills[1].get();return (input->flags&16)!=0;}
bool skill(CSkill*s,CBaseUnit*t,CCharacter*c){number(13);int id=-1;for(unsigned j=0;j<4;++j)if(s==reinterpret_cast<CSkill*>(&world->tokens[j]))id=j;number(id);number(t==world->selected);number(c==world->actor.get());unsigned call=world->skillCalls++;
 if(input->mode==8)world->item.get()->m_pSkillManager=world->skills[1].get();
 if(input->mode==9&&!world->changed){world->changed=true;world->skills[0].get()->m_OtherSkills.add(reinterpret_cast<CSkill*>(&world->tokens[3]));}
 if(input->mode==10&&world->skills[0].get()->m_OtherSkills.size()>1)world->skills[0].get()->m_OtherSkills[1]=reinterpret_cast<CSkill*>(&world->tokens[3]);
 if(input->mode==11)world->target.get()->m_pMaster=world->actor.get();
 return (input->results>>(4+call%4))&1;
}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){number(14);number(p==world->item.get());number(t);return t==UNITTYPES::NOPETS?(input->flags&1)!=0:t==UNITTYPES::PETONLY&&(input->flags&2)!=0;}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;w.table[73]=reinterpret_cast<void*>(&valid);w.otherTable[73]=reinterpret_cast<void*>(&valid);
 CEquipment*p=w.item.get();p->m_iUnknown248=c.charges;p->m_pEffectManager=c.flags&4?NULL:w.managers[0].get();p->m_pSkillManager=c.flags&8?NULL:w.skills[0].get();w.actor.get()->m_iUnitLevel=c.level;w.target.get()->m_iUnitLevel=c.level+1;w.target.get()->m_pMaster=c.flags&32?w.actor.get():NULL;
 if(c.mode==12&&c.effects>1)effects(w.managers[0].get()).m_nCapacity=1;
 if(c.mode==13&&c.skills>1)w.skills[0].get()->m_OtherSkills.m_nCapacity=1;
 detour::Set patches;TL_REDIRECT(patches,cuIsa,&isa);TL_REDIRECT(patches,cuLevel,&level);TL_REDIRECT(patches,cuBusy,&busy);TL_REDIRECT(patches,cuSkill,&skill);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(repeat==0){autotest::invoke(out,ours?&tracedoriginalCanUse:&originalCanUse,p,w.actor.get(),w.selected);}else{bool result=ours?p->canUseOnTarget(w.actor.get(),w.selected):originalCanUse(p,w.actor.get(),w.selected);number(result);}number(w.validCalls);number(w.skillCalls);number(w.target.get()->m_pMaster!=NULL);number(effects(w.managers[0].get()).size());number(w.skills[0].get()->m_OtherSkills.size());}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_canuse_differential){
autotest::Coverage coverage0("equipment_canuse_differential",(uint64_t)(uintptr_t)&originalCanUse);
int failures=0;for(unsigned n=0;n<8192;++n){Case c={n,n%64,(n/64)%4,(n/256)%4,(n*73)%256,0,(n/1024)%3,1,10,10};if(c.target==2)c.effects=0;
 if(n>=3072){unsigned q=n-3072;c.flags=q%64;c.mode=1+(q/64)%13;c.effects=1+(q/832)%3;c.skills=1+(q/2496)%3;c.results=255;c.target=(q/32)%2;}
 static const int charges[]={-9999,-1,0,1,4};c.charges=charges[(n/7)%5];
 if(n>=7168){unsigned q=n-7168;c.flags=q%64;c.mode=q%2?6:0;c.effects=0;c.skills=0;c.target=(q/64)%3;static const int levels[]={INT_MIN,-1,0,9,10,11,INT_MAX-1};c.level=levels[(q/3)%7];c.requirement=levels[(q/21)%7];c.charges=1;}
 autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    canUse case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}
 host->log("    canUse: 8192 cases, two calls per side\n");{coverage0.report(host);return failures;}}
