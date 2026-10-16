#include <cstring>
#include <stdint.h>
#include <typeinfo>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "Affix.h"
#include "Effect.h"
#include "Skill.h"
#include "BaseUnit.h"
#include "Character.h"
#include "EffectManager.h"
#include "MasterResourceManager.h"
#include "Hierarchy.h"
#undef private
extern "C" char originalCharacterVTable[] __asm__("_ZTV10CCharacter");
extern "C" const std::type_info originalCharacterRTTI __asm__("_ZTI10CCharacter");
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,oSaves,nSaves,(CAffix*,bool),"_ZN6CAffix8setSavesEb")
DECL(bool,oDuration,nDuration,(CAffix*,float),"_ZN6CAffix19updateAffixDurationEf")
DECL(bool,oCan,nCan,(CAffix*,unsigned),"_ZN6CAffix22canBeAppliedToUnitTypeEj")
DECL(void,oOwner,nOwner,(CAffix*,CBaseUnit*),"_ZN6CAffix8setOwnerEP9CBaseUnit")
DECL(void,oSkill,nSkill,(CAffix*,CSkill*),"_ZN6CAffix13setSkillOwnerEP6CSkill")
DECL(void,oClear,nClear,(CAffix*),"_ZN6CAffix21clearEffectsFromOwnerEv")
DECL(void,oAdd,nAdd,(CAffix*,CEffectManager*),"_ZN6CAffix25addEffectsToEffectManagerEP14CEffectManager")
#undef DECL
TL_FUNCTION(addSafe,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(removeSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(effectOwner,"_ZN7CEffect8setOwnerEP9CBaseUnitb")
TL_FUNCTION(effectSkill,"_ZN7CEffect13setSkillOwnerEP6CSkill")
TL_FUNCTION(effectAffix,"_ZN7CEffect13setAffixOwnerEP6CAffix")
TL_FUNCTION(effectRemove,"_ZN14CEffectManager12removeEffectEP7CEffectb")
TL_FUNCTION(effectClone,"_ZN14CEffectManager11cloneEffectEP9CBaseUnitP7CEffect")
TL_FUNCTION(effectActivate,"_ZN9CBaseUnit14activateEffectEP7CEffect")
TL_FUNCTION(masterSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(hierarchyISA,"_ZN10CHierarchy3ISAEjj")
namespace {
// Bounded machine-level witness: owns Character-sized storage and the original
// primary address point. Only RTTI/source identity is observed; no Character
// constructor, virtual behavior, or destructor runs on this storage.
struct CharacterRTTIWitness {
    uint64_t storage[(sizeof(CCharacter)+7)/8];
    CharacterRTTIWitness() {
        std::memset(storage,0,sizeof(storage));
        void** addressPoint=reinterpret_cast<void**>(originalCharacterVTable+2*sizeof(void*));
        std::memcpy(storage,&addressPoint,sizeof(addressPoint));
    }
    CBaseUnit* base() { return reinterpret_cast<CBaseUnit*>(storage); }
    CCharacter* character() { return reinterpret_cast<CCharacter*>(storage); }
};
struct Case{unsigned mode,seed;};autotest::Capture*cap;CAffix*affix;void*objects[13];CCharacter*expectedSource;CBaseUnit*expectedOwner;CBaseUnit*expectedReceiver;unsigned validCalls,applyCalls;CMasterResourceManager*master;CHierarchy*hierarchy;unsigned seed,registrations;
int id(void*p){if(!p)return -1;if(p==affix)return 20;for(unsigned i=0;i<13;++i)if(p==objects[i])return i;return -2;}
void event(unsigned kind,void*p){int v=id(p);cap->add(&kind,4);cap->add(&v,4);}
unsigned reg(void*p,void*pair){event(1,p);int off=static_cast<char*>(pair)-reinterpret_cast<char*>(affix);cap->add(&off,4);int old=id(*static_cast<void**>(pair));cap->add(&old,4);return 17+registrations++;}
void unreg(void*p,void*pair,unsigned ix){event(2,p);int off=static_cast<char*>(pair)-reinterpret_cast<char*>(affix);cap->add(&off,4);cap->add(&ix,4);int old=id(*static_cast<void**>(pair));cap->add(&old,4);}
void owner(void*p,void*v,bool b){event(3,p);event(4,v);cap->add(&b,1);}
void skill(void*p,void*v){event(5,p);event(6,v);}
void setAffix(void*p,void*v){event(7,p);event(8,v);}
bool remove(void*p,void*e,bool b){event(9,p);event(10,e);cap->add(&b,1);return seed&1;}
void deactivate(void*p,void*e){event(11,p);event(12,e);}
bool valid(void*p,void*source,void*target,void*e){event(13,p);event(14,source);event(15,target);event(16,e);++validCalls;if(source!=expectedSource||target!=expectedOwner||p!=expectedReceiver)cap->issue=autotest::Capture::InvalidReport;return (seed+id(e))%3!=0;}
bool apply(void*p,void*source,void*target,void*e){event(17,p);event(18,source);event(19,target);event(21,e);++applyCalls;if(source!=expectedSource||target!=expectedOwner||p!=expectedReceiver)cap->issue=autotest::Capture::InvalidReport;return false;}
void activate(void*p,void*e){event(22,p);event(23,e);}
void*clone(void*p,void*s,void*e){event(24,p);event(25,s);event(26,e);return e;}
CMasterResourceManager*singleton(){unsigned x=27;cap->add(&x,4);return master;}
bool isa(void*self,unsigned type,unsigned parent){unsigned x=28;cap->add(&x,4);cap->add(&type,4);cap->add(&parent,4);if(self!=hierarchy)cap->issue=autotest::Capture::InvalidReport;return type==parent||(parent<8&&((seed>>parent)&1));}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;registrations=0;validCalls=applyCalls=0;CharacterRTTIWitness characterWitness;objects[12]=characterWitness.base();
 uint64_t as[(sizeof(CAffix)+7)/8],es[5][(sizeof(CEffect)+7)/8],ss[2][(sizeof(CSkill)+7)/8],us[2][(sizeof(CBaseUnit)+7)/8],ms[2][(sizeof(CEffectManager)+7)/8],masters[(sizeof(CMasterResourceManager)+7)/8],hs[(sizeof(CHierarchy)+7)/8];
 std::memset(as,0,sizeof(as));std::memset(es,0,sizeof(es));std::memset(ss,0,sizeof(ss));std::memset(us,0,sizeof(us));std::memset(ms,0,sizeof(ms));affix=reinterpret_cast<CAffix*>(as);master=reinterpret_cast<CMasterResourceManager*>(masters);hierarchy=reinterpret_cast<CHierarchy*>(hs);master->m_pHierarchy=hierarchy;
 void*vt[82]={0};vt[1]=const_cast<std::type_info*>(&typeid(CBaseUnit));vt[2+0x238/8]=reinterpret_cast<void*>(&valid);vt[2+0x240/8]=reinterpret_cast<void*>(&apply);vt[2+0x260/8]=reinterpret_cast<void*>(&deactivate);
 for(unsigned i=0;i<5;++i)objects[i]=es[i];for(unsigned i=0;i<2;++i){objects[5+i]=us[i];objects[7+i]=ss[i];objects[9+i]=ms[i];*reinterpret_cast<void***>(us[i])=vt+2;CSkill*s=reinterpret_cast<CSkill*>(ss[i]);s->m_pOwner=(seed&8)?reinterpret_cast<CBaseUnit*>(us[i]):NULL;reinterpret_cast<CEffectManager*>(ms[i])->getOwnerReference().m_pObject=(seed&4)?reinterpret_cast<CBaseUnit*>(us[i]):NULL;}objects[11]=hierarchy;
 new(&affix->m_Effects)TArrayList<CEffect*>(2);for(unsigned i=0;i<seed%6;++i)affix->m_Effects.add(reinterpret_cast<CEffect*>(es[i]));if((seed&16)&&affix->m_Effects.size())affix->m_Effects.m_nCapacity=(seed/8)%2;
 new(&affix->m_ApplicableUnitTypes)TArrayList<unsigned>(2);for(unsigned i=0;i<seed%6;++i)affix->m_ApplicableUnitTypes.add((i+seed/3)%10);if((seed&16)&&affix->m_ApplicableUnitTypes.size())affix->m_ApplicableUnitTypes.m_nCapacity=seed%2;
 for(unsigned i=0;i<5;++i){CEffect*e=reinterpret_cast<CEffect*>(es[i]);e->m_flag33=(i+seed)%2;e->m_Owner.m_pObject=(i+seed)%3?reinterpret_cast<CBaseUnit*>(us[i%2]):NULL;}
 affix->m_pOwner=seed&1?reinterpret_cast<CBaseUnit*>(us[0]):NULL;affix->m_iOwnerSafePointerId=7;affix->m_pSkillOwner=seed&1?reinterpret_cast<CSkill*>(ss[0]):NULL;affix->m_iSkillOwnerSafePointerId=8;affix->m_pEffectManager=seed&1?reinterpret_cast<CEffectManager*>(ms[0]):NULL;affix->m_iEffectManagerSafePointerId=9;
 unsigned durations[]={0xbf800000,0x80000000,0,0x3f000000,0x3f800000,0x7f800000,0x7fc00001};float dt[]={-1,0,0.25f,1,2};std::memcpy(&affix->m_fDuration,&durations[(seed/2)%7],4);float elapsed=dt[(seed/3)%5];float expected=affix->m_fDuration;bool expectedAlive=true;if(!(expected<0)){expected-=elapsed;if(expected<=0){expected=0;expectedAlive=false;}}
 unsigned sourceKind=(seed/4)%3;
 if(c.mode==6){
    void**addressPoint=*reinterpret_cast<void***>(characterWitness.base());
    if(addressPoint!=reinterpret_cast<void**>(originalCharacterVTable+2*sizeof(void*))||addressPoint[-2]!=NULL||addressPoint[-1]!=&originalCharacterRTTI||dynamic_cast<CCharacter*>(characterWitness.base())!=characterWitness.character()){
        out.issue=autotest::Capture::InvalidReport;return;
    }
    affix->m_pOwner=sourceKind==0?NULL:sourceKind==1?reinterpret_cast<CBaseUnit*>(us[0]):characterWitness.base();
 }
 CBaseUnit*newOwner=(seed/2)%3==0?NULL:reinterpret_cast<CBaseUnit*>(us[(seed/2)%2]);CSkill*newSkill=(seed/2)%3==0?NULL:reinterpret_cast<CSkill*>(ss[(seed/2)%2]);CEffectManager*newManager=reinterpret_cast<CEffectManager*>(ms[(seed/2)%2]);
 expectedSource=c.mode==6&&sourceKind==2?characterWitness.character():NULL;
 expectedOwner=affix->m_pOwner;
 expectedReceiver=newManager->getOwnerReference().getObject();
 unsigned wantedValid=0,wantedApply=0;
 if(c.mode==6&&affix->m_pEffectManager!=newManager&&expectedReceiver){
    wantedValid=affix->m_Effects.size();
    for(unsigned i=0;i<wantedValid;++i)if((seed+id(affix->m_Effects[i]))%3!=0)++wantedApply;
 }
 detour::Set patches;TL_REDIRECT(patches,addSafe,&reg);TL_REDIRECT(patches,removeSafe,&unreg);TL_REDIRECT(patches,effectOwner,&owner);TL_REDIRECT(patches,effectSkill,&skill);TL_REDIRECT(patches,effectAffix,&setAffix);TL_REDIRECT(patches,effectRemove,&remove);TL_REDIRECT(patches,effectClone,&clone);TL_REDIRECT(patches,effectActivate,&activate);TL_REDIRECT(patches,masterSingleton,&singleton);TL_REDIRECT(patches,hierarchyISA,&isa);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 bool result=false;
 if(c.mode==0){void(*fn)(CAffix*,bool)=ours?nSaves:oSaves;if(!autotest::beginInvocation(out,fn))return;fn(affix,seed&2);}
 else if(c.mode==1){bool(*fn)(CAffix*,float)=ours?nDuration:oDuration;if(!autotest::beginInvocation(out,fn))return;result=fn(affix,elapsed);}
 else if(c.mode==2){bool(*fn)(CAffix*,unsigned)=ours?nCan:oCan;if(!autotest::beginInvocation(out,fn))return;result=fn(affix,(seed/7)%11);}
 else if(c.mode==3){void(*fn)(CAffix*,CBaseUnit*)=ours?nOwner:oOwner;if(!autotest::beginInvocation(out,fn))return;fn(affix,newOwner);}
 else if(c.mode==4){void(*fn)(CAffix*,CSkill*)=ours?nSkill:oSkill;if(!autotest::beginInvocation(out,fn))return;fn(affix,newSkill);}
 else if(c.mode==5){void(*fn)(CAffix*)=ours?nClear:oClear;if(!autotest::beginInvocation(out,fn))return;fn(affix);}
 else{void(*fn)(CAffix*,CEffectManager*)=ours?nAdd:oAdd;if(!autotest::beginInvocation(out,fn))return;fn(affix,newManager);}out.callCompleted=1;
 if(c.mode==6){
    if(validCalls!=wantedValid||applyCalls!=wantedApply)out.issue=autotest::Capture::InvalidReport;
    out.add(&sourceKind,4);int sourceIdentity=id(expectedSource);out.add(&sourceIdentity,4);out.add(&validCalls,4);out.add(&applyCalls,4);
 }
 if(c.mode==1&&(result!=expectedAlive||std::memcmp(&expected,&affix->m_fDuration,4)))out.issue=autotest::Capture::InvalidReport;
 out.add(&result,1);out.add(&affix->m_fDuration,4);void*p[]={affix->m_pOwner,affix->m_pSkillOwner,affix->m_pEffectManager};for(unsigned i=0;i<3;++i){int v=id(p[i]);out.add(&v,4);}out.add(&affix->m_iOwnerSafePointerId,4);out.add(&affix->m_iSkillOwnerSafePointerId,4);out.add(&affix->m_iEffectManagerSafePointerId,4);for(unsigned i=0;i<5;++i)out.add(&reinterpret_cast<CEffect*>(es[i])->m_flag33,1);
 affix->m_Effects.~TArrayList<CEffect*>();affix->m_ApplicableUnitTypes.~TArrayList<unsigned>();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void replacement(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<120;++seed){Case c={mode,seed};autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(replacement,&c,y);if(coverage.observe(h,x,y)){h->log("    affix mode %u seed %u issue %u/%u exits %d/%d\n",mode,seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(state_affix_saves,0,oSaves)
TEST(state_affix_duration,1,oDuration)
TEST(state_affix_can_apply,2,oCan)
TEST(state_affix_owner,3,oOwner)
TEST(state_affix_skill_owner,4,oSkill)
TEST(state_affix_clear_owner,5,oClear)
TEST(state_affix_add_manager,6,oAdd)
