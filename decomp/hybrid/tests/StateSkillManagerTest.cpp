#include <cstring>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "SkillManager.h"
#include "Skill.h"
#include "BaseUnit.h"
#include "Character.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(bool,oKnows,nKnows,(CSkillManager*,const std::wstring&),"_ZN13CSkillManager10knowsSkillERKSbIwSt11char_traitsIwESaIwEE")
DECL(bool,oUpdating,nUpdating,(CSkillManager*,const std::wstring&),"_ZN13CSkillManager24getSkillIsUpdatingByNameERKSbIwSt11char_traitsIwESaIwEE")
DECL(bool,oCooling,nCooling,(CSkillManager*,CSkill*),"_ZN13CSkillManager17getSkillIsCoolingEP6CSkill")
DECL(float,oTime,nTime,(CSkillManager*,CSkill*),"_ZN13CSkillManager19getSkillCoolingTimeEP6CSkill")
DECL(void,oClear,nClear,(CSkillManager*),"_ZN13CSkillManager22clearAllUnitReferencesEv")
DECL(void,oDelete,nDelete,(CSkillManager*,CSkill*),"_ZN13CSkillManager20attemptDeleteOfSkillEP6CSkill")
DECL(void,oUpdate,nUpdate,(CSkillManager*,float),"_ZN13CSkillManager6updateEf")
DECL(void,oEvent,nEvent,(CSkillManager*,ESKILL_EVENT_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,CBaseUnit*),"_ZN13CSkillManager17triggerSkillEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnit")
DECL(void,oCreate,nCreate,(CSkillManager*,CBaseUnit*,ESKILL_ACTIVATION_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CCharacter*),"_ZN13CSkillManager18fireSkillsOnCreateEP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS3_10QuaternionES6_P10CCharacter")
#undef DECL
TL_FUNCTION(skillName,"_ZN6CSkill7getNameEv")
TL_FUNCTION(skillTarget,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(skillEvent,"_ZN6CSkill12triggerEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnitPS3_")
TL_FUNCTION(skillHasEvent,"_ZN6CSkill8hasEventE17ESKILL_EVENT_TYPE")
TL_FUNCTION(skillUpdate,"_ZN6CSkill11updateSkillEf")
TL_FUNCTION(skillStop,"_ZN6CSkill9stopSkillEv")
TL_FUNCTION(skillCalculate,"_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(skillLevel,"_ZN13CSkillManager13setSkillLevelEP6CSkillj")
TL_FUNCTION(skillExecute,"_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
TL_FUNCTION(removeSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;CSkillManager*manager;CSkill*skills[6];void*units[3];std::wstring names[6];unsigned seed;
int id(void*p){if(!p)return -1;if(p==manager)return 20;for(unsigned i=0;i<6;++i)if(p==skills[i])return i;for(unsigned i=0;i<3;++i)if(p==units[i])return 10+i;return -2;}
void event(unsigned k,void*p){int n=id(p);cap->add(&k,4);cap->add(&n,4);}
const std::wstring&name(void*p){event(1,p);return names[id(p)];}
int targetType(void*p){event(2,p);return int((seed+id(p))%10)-1;}
bool trigger(void*p,int e,const Ogre::Vector3&v,const Ogre::Quaternion&q,void*t,const Ogre::Vector3*position){event(3,p);cap->add(&e,4);cap->add(&v,sizeof(v));cap->add(&q,sizeof(q));event(4,t);bool b=position;cap->add(&b,1);if(b)cap->add(position,sizeof(*position));return (seed+id(p))%2;}
bool hasEvent(void*p,int e){event(5,p);cap->add(&e,4);return (seed+id(p))%3!=0;}
void update(void*p,float f){event(6,p);cap->add(&f,4);CSkill*s=static_cast<CSkill*>(p);s->m_coolingTime-=f;if((seed+id(p))%7==0)s->m_interruptible=false;}
void stop(void*p){event(7,p);}bool calculate(void*p){event(8,p);return (seed+id(p))%2;}
void level(void*p,void*s,unsigned n){event(9,p);event(10,s);cap->add(&n,4);}
void*execute(void*p,void*s,void*c,int a,const Ogre::Vector3&v,const Ogre::Quaternion&q,const Ogre::Vector3&to,void*t){event(11,p);event(12,s);event(13,c);cap->add(&a,4);cap->add(&v,sizeof(v));cap->add(&q,sizeof(q));cap->add(&to,sizeof(to));event(14,t);return s;}
void destroy(void*p){event(15,p);}
void unreg(void*p,void*pair,unsigned index){event(16,p);int owner=-1,off=0;for(unsigned i=0;i<6;++i){ptrdiff_t d=static_cast<char*>(pair)-reinterpret_cast<char*>(skills[i]);if(d==0x30||d==0x40){owner=i;off=d;break;}}cap->add(&owner,4);cap->add(&off,4);cap->add(&index,4);event(17,*static_cast<void**>(pair));}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;uint64_t ms[(sizeof(CSkillManager)+7)/8],ss[6][(sizeof(CSkill)+7)/8],us[3][16];std::memset(ms,0,sizeof(ms));std::memset(ss,0,sizeof(ss));manager=reinterpret_cast<CSkillManager*>(ms);void*vt[2]={reinterpret_cast<void*>(&destroy),reinterpret_cast<void*>(&destroy)};const wchar_t*texts[]={L"",L"a",L"A",L"aa",L"AB",L"missing"};unsigned floats[]={0xbf800000,0x80000000,0,0x3f000000,0x40000000,0x7f800000,0x7fc00001};
 for(unsigned i=0;i<3;++i)units[i]=us[i];for(unsigned i=0;i<6;++i){skills[i]=reinterpret_cast<CSkill*>(ss[i]);*reinterpret_cast<void***>(skills[i])=vt;names[i]=texts[(i+seed/9)%6];skills[i]->m_pDataGroup=reinterpret_cast<CDataGroup*>(units[(i+seed/4)%3]);std::memcpy(&skills[i]->m_coolingTime,&floats[(i+seed/3)%7],4);skills[i]->m_pOwner=(seed+i)%3?static_cast<CBaseUnit*>(units[i%3]):NULL;skills[i]->m_iOwnerSafePointerId=30+i;skills[i]->m_Target.m_pObject=(seed+i)%2?static_cast<CBaseUnit*>(units[(i+1)%3]):NULL;skills[i]->m_Target.m_nIndex=40+i;skills[i]->m_targetPosition=Ogre::Vector3(float(i),float(seed),-float(i+seed));skills[i]->m_interruptible=(seed+i)%2;skills[i]->m_eActivationType=static_cast<ESKILL_ACTIVATION_TYPE>((seed+i)%6);skills[i]->m_skillLevel=100+i;}
 new(&manager->m_UpdatingSkills)TArrayList<CSkill*>(2);new(&manager->m_OtherSkills)TArrayList<CSkill*>(2);new(&manager->m_SkillsByName)std::map<std::wstring,TArrayList<CSkill*>*>();TArrayList<CSkill*>entries[3];for(unsigned i=0;i<3;++i){entries[i].add(skills[i]);if(seed&16)entries[i].add(skills[i+3]);}
 for(unsigned i=0;i<seed%7;++i)manager->m_UpdatingSkills.add(skills[i]);for(unsigned i=0;i<(seed/2)%7;++i)manager->m_OtherSkills.add(skills[5-i]);if(c.mode!=6&&(seed&16)){if(manager->m_UpdatingSkills.size())manager->m_UpdatingSkills.m_nCapacity=(seed/8)%2;if(manager->m_OtherSkills.size())manager->m_OtherSkills.m_nCapacity=(seed/8)%2;}
 const wchar_t*keys[]={L"",L"A",L"AA"};for(unsigned i=0;i<seed%4;++i)manager->m_SkillsByName[keys[i]]=c.mode<4&&(seed&8)?NULL:&entries[i];
 detour::Set patches;TL_REDIRECT(patches,skillName,&name);TL_REDIRECT(patches,skillTarget,&targetType);TL_REDIRECT(patches,skillEvent,&trigger);TL_REDIRECT(patches,skillHasEvent,&hasEvent);TL_REDIRECT(patches,skillUpdate,&update);TL_REDIRECT(patches,skillStop,&stop);TL_REDIRECT(patches,skillCalculate,&calculate);TL_REDIRECT(patches,skillLevel,&level);TL_REDIRECT(patches,skillExecute,&execute);TL_REDIRECT(patches,removeSafe,&unreg);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 std::wstring query=texts[(seed/6)%6];CSkill*s=skills[seed%6];Ogre::Vector3 v(float(seed),2,3),to(-1,float(seed),-3);Ogre::Quaternion q(1,2,3,float(seed));CBaseUnit*caster=static_cast<CBaseUnit*>(units[0]);CCharacter*t=seed&1?reinterpret_cast<CCharacter*>(units[1]):NULL;bool result=false;float time=0;
 if(c.mode<3){bool(*old[])(CSkillManager*,const std::wstring&)={oKnows,oUpdating};bool(*now[])(CSkillManager*,const std::wstring&)={nKnows,nUpdating};if(c.mode<2){bool(*fn)(CSkillManager*,const std::wstring&)=ours?now[c.mode]:old[c.mode];if(!autotest::beginInvocation(out,fn))return;result=fn(manager,query);}else{bool(*fn)(CSkillManager*,CSkill*)=ours?nCooling:oCooling;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,s);}}
 else if(c.mode==3){float(*fn)(CSkillManager*,CSkill*)=ours?nTime:oTime;if(!autotest::beginInvocation(out,fn))return;time=fn(manager,s);}
 else if(c.mode==4){void(*fn)(CSkillManager*)=ours?nClear:oClear;if(!autotest::beginInvocation(out,fn))return;fn(manager);}
 else if(c.mode==5){void(*fn)(CSkillManager*,CSkill*)=ours?nDelete:oDelete;if(!autotest::beginInvocation(out,fn))return;fn(manager,s);}
 else if(c.mode==6){void(*fn)(CSkillManager*,float)=ours?nUpdate:oUpdate;if(!autotest::beginInvocation(out,fn))return;fn(manager,float(int(seed%5)-2)*0.5f);}
 else if(c.mode==7){void(*fn)(CSkillManager*,ESKILL_EVENT_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,CBaseUnit*)=ours?nEvent:oEvent;if(!autotest::beginInvocation(out,fn))return;fn(manager,static_cast<ESKILL_EVENT_TYPE>(seed%13),v,q,reinterpret_cast<CBaseUnit*>(t));}
 else{void(*fn)(CSkillManager*,CBaseUnit*,ESKILL_ACTIVATION_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CCharacter*)=ours?nCreate:oCreate;if(!autotest::beginInvocation(out,fn))return;fn(manager,caster,static_cast<ESKILL_ACTIVATION_TYPE>(seed%6),v,q,to,t);}out.callCompleted=1;out.add(&result,1);out.add(&time,4);
 for(unsigned i=0;i<6;++i){int a=id(skills[i]->m_pOwner),b=id(skills[i]->m_Target.m_pObject);out.add(&a,4);out.add(&b,4);out.add(&skills[i]->m_iOwnerSafePointerId,4);out.add(&skills[i]->m_Target.m_nIndex,4);out.add(&skills[i]->m_coolingTime,4);}unsigned n=manager->m_UpdatingSkills.size();out.add(&n,4);for(unsigned i=0;i<n;++i){int v=id(manager->m_UpdatingSkills.m_pData[i]);out.add(&v,4);}manager->m_UpdatingSkills.~TArrayList();manager->m_OtherSkills.~TArrayList();manager->m_SkillsByName.~map();
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned m,const char*n,uintptr_t address){autotest::Coverage coverage(n,address);for(unsigned i=0;i<120;++i){Case c={m,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    skill manager mode %u seed %u issue %u/%u exits %d/%d\n",m,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(state_skill_manager_knows,0,oKnows)
TEST(state_skill_manager_updating,1,oUpdating)
TEST(state_skill_manager_cooling,2,oCooling)
TEST(state_skill_manager_cooling_time,3,oTime)
TEST(state_skill_manager_clear_units,4,oClear)
TEST(state_skill_manager_delete,5,oDelete)
TEST(state_skill_manager_update,6,oUpdate)
TEST(state_skill_manager_event,7,oEvent)
TEST(state_skill_manager_create,8,oCreate)
