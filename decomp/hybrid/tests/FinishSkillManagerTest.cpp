#include <cstring>
#include <map>
#include <string>
#include <new>
#include "SmallMassCompare.h"
#define private public
#define protected public
#include "SkillManager.h"
#include "Skill.h"
#include "SkillProperty.h"
#include "BaseUnit.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(CSkill*,fmOldAdd,fmNewAdd,(CSkillManager*,CSkill*,bool,bool),"_ZN13CSkillManager8addSkillEP6CSkillbb")
DECL(CSkill*,fmOldName,fmNewName,(CSkillManager*,const std::wstring&,CBaseUnit*,ESKILL_ACTIVATION_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CBaseUnit*,int),"_ZN13CSkillManager12executeSkillERKSbIwSt11char_traitsIwESaIwEEP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS9_10QuaternionESC_S7_i")
DECL(CSkill*,fmOldPointer,fmNewPointer,(CSkillManager*,CSkill*,CBaseUnit*,ESKILL_ACTIVATION_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CBaseUnit*),"_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
#undef DECL
TL_FUNCTION(fmName,"_ZN6CSkill7getNameEv")
TL_FUNCTION(fmConstructor,"_ZN6CSkillC1EP16CResourceManagerP10CDataGroup")
TL_FUNCTION(fmSetLevel,"_ZN6CSkill32_setLevelOfSkillFromSkillManagerEj")
TL_FUNCTION(fmExclusive,"_ZN6CSkill14getIsExclusiveEv")
TL_FUNCTION(fmStop,"_ZN6CSkill9stopSkillEv")
TL_FUNCTION(fmStart,"_ZN6CSkill10startSkillEP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS3_10QuaternionES6_S1_")
TL_FUNCTION(fmCharges,"_ZN13CSkillManager21decrementSkillChargesEP6CSkill")
namespace {
using namespace smallmass;
CSkillManager*manager;CSkill*skills[5];CSkill*cloned;CBaseUnit*caster;CBaseUnit*target;CResourceManager*resources;CDataGroup*group;std::wstring names[6];unsigned seed,calls;
int id(const void*p){if(!p)return -1;if(p==manager)return 0;if(p==caster)return 1;if(p==target)return 2;if(p==resources)return 3;if(p==group)return 4;if(p==cloned)return 15;for(unsigned i=0;i<5;++i)if(p==skills[i])return 10+i;return 99;}
void ev(unsigned k,const void*p){number(k);number(id(p));++calls;}
const std::wstring&name(void*p){ev(1,p);int i=id(p);return names[i==15?5:(i>=10&&i<15?i-10:0)];}
void ctor(CSkill*p,CResourceManager*r,CDataGroup*d){cloned=p;ev(2,p);number(id(r));number(id(d));std::memset(p,0,sizeof(*p));p->m_pDataGroup=d;p->m_iColumn=91;p->m_iCharges=92;p->m_bEnabled=true;}
void setLevel(CSkill*p,unsigned value){ev(3,p);number(value);p->m_skillLevel=value;}
bool exclusive(CSkill*p){ev(4,p);return seed&4;}
void stop(CSkill*p){ev(5,p);p->m_interruptible=false;if(seed&128&&manager->m_UpdatingSkills.m_nCount>1)manager->m_UpdatingSkills.m_nCount=1;}
bool start(CSkill*p,CBaseUnit*c,ESKILL_ACTIVATION_TYPE a,const Ogre::Vector3&v,const Ogre::Quaternion&q,const Ogre::Vector3&t,CBaseUnit*unit){ev(6,p);number(id(c));number(a);vector(v);output->add(&q,sizeof(q));vector(t);number(id(unit));p->m_coolingTime=17.5f;return seed&8;}
void charges(CSkillManager*p,CSkill*s){ev(7,p);number(id(s));--s->m_iCharges;}
bool install(detour::Set&p){TL_REDIRECT(p,fmName,&name);TL_REDIRECT(p,fmConstructor,&ctor);TL_REDIRECT(p,fmSetLevel,&setLevel);TL_REDIRECT(p,fmExclusive,&exclusive);TL_REDIRECT(p,fmStop,&stop);TL_REDIRECT(p,fmStart,&start);TL_REDIRECT(p,fmCharges,&charges);return !p.failed();}
void skillCapture(CSkill*s){number(id(s));number(s->m_skillLevel);number(s->m_iCharges);number(s->m_iColumn);number(s->m_bExecutedByProperty);number(s->m_bEnabled);number(s->m_interruptible);number(id(s->m_pSkillManager));floating(s->m_coolingTime);}
void listCapture(TArrayList<CSkill*>&items){number(items.size());number(items.m_nCapacity);number(items.m_nGrowBy);for(unsigned i=0;i<items.size();++i)number(id(items[i]));}
void execute(Case&c,bool ours,autotest::Capture&out)
{
 input=&c;output=&out;autotest::g_arenaUsed=0;seed=c.index;calls=0;cloned=NULL;
 manager=static_cast<CSkillManager*>(object(sizeof(CSkillManager)));resources=reinterpret_cast<CResourceManager*>(object(0x200));caster=static_cast<CBaseUnit*>(object(sizeof(CBaseUnit)));target=static_cast<CBaseUnit*>(object(sizeof(CBaseUnit)));group=reinterpret_cast<CDataGroup*>(object(0x80));manager->m_pResourceManager=resources;
 new(&manager->m_SkillsByName)std::map<std::wstring,TArrayList<CSkill*>*>;new(&manager->m_OtherSkills)TArrayList<CSkill*>(2);new(&manager->m_UpdatingSkills)TArrayList<CSkill*>(2);
 const wchar_t*labels[]={L"Fire",L"ICE",L"fire",L"",L"Third"};
 for(unsigned i=0;i<5;++i){skills[i]=static_cast<CSkill*>(object(sizeof(CSkill)));names[i]=labels[i];skills[i]->m_pDataGroup=group;skills[i]->m_skillLevel=(seed+i)%4;skills[i]->m_iCharges=30+i;skills[i]->m_iColumn=40+i;skills[i]->m_bEnabled=(seed+i)&1;skills[i]->m_bExecutedByProperty=(seed+i)&2;skills[i]->m_interruptible=(seed/4+i)%3!=0;skills[i]->m_Guid=(seed/8+i)%3;}
 names[5]=names[0];
 TArrayList<CSkill*>*named=new TArrayList<CSkill*>(1);unsigned namedCount=seed/8%5;
 for(unsigned i=0;i<namedCount;++i)named->add(skills[i]);if(seed%4)manager->m_SkillsByName[L"FIRE"]=named;
 TArrayList<CSkill*>*ice=new TArrayList<CSkill*>(2);ice->add(skills[1]);manager->m_SkillsByName[L"ICE"]=ice;
 for(unsigned i=0;i<seed/16%5;++i)manager->m_OtherSkills.add(skills[i]);
 for(unsigned i=0;i<seed/32%5;++i)manager->m_UpdatingSkills.add(skills[i]);
 m_gDisableSkillFromBeingCasted=c.op?bool(seed&64):false;
 Ogre::Vector3 position(1,-2,3),targetPosition(4,5,-6);Ogre::Quaternion orientation(1,0.25f,-0.5f,0.75f);CSkill*result=NULL;
 if(c.op==0){typedef CSkill*(*Fn)(CSkillManager*,CSkill*,bool,bool);Fn fn=ours?fmNewAdd:fmOldAdd;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,seed%7?skills[0]:NULL,bool(seed&1),bool(seed&2));}
 else if(c.op==1){typedef CSkill*(*Fn)(CSkillManager*,const std::wstring&,CBaseUnit*,ESKILL_ACTIVATION_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CBaseUnit*,int);Fn fn=ours?fmNewName:fmOldName;std::wstring label=seed%9?L"fiRE":L"unknown";if(!autotest::beginInvocation(out,fn))return;result=fn(manager,label,caster,static_cast<ESKILL_ACTIVATION_TYPE>(seed%5),position,orientation,targetPosition,target,int(seed%5)-1);text(label);}
 else {typedef CSkill*(*Fn)(CSkillManager*,CSkill*,CBaseUnit*,ESKILL_ACTIVATION_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CBaseUnit*);Fn fn=ours?fmNewPointer:fmOldPointer;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,seed%7?skills[0]:NULL,caster,static_cast<ESKILL_ACTIVATION_TYPE>(seed%5),position,orientation,targetPosition,target);}
 out.callCompleted=1;number(id(result));number(calls);listCapture(manager->m_OtherSkills);listCapture(manager->m_UpdatingSkills);number(manager->m_SkillsByName.size());
 for(std::map<std::wstring,TArrayList<CSkill*>*>::iterator i=manager->m_SkillsByName.begin();i!=manager->m_SkillsByName.end();++i){text(i->first);listCapture(*i->second);}
 for(unsigned i=0;i<5;++i)skillCapture(skills[i]);if(cloned)skillCapture(cloned);
}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address,unsigned count){detour::Set patches;if(!install(patches))return 1;return smallmass::run(host,op,name,address,execute,count);}
}
TL_TEST(finish_skill_manager_add){return run(host,0,"finish_skill_manager_add",(uintptr_t)&fmOldAdd,384);}
TL_TEST(finish_skill_manager_execute_name){return run(host,1,"finish_skill_manager_execute_name",(uintptr_t)&fmOldName,512);}
TL_TEST(finish_skill_manager_execute_pointer){return run(host,2,"finish_skill_manager_execute_pointer",(uintptr_t)&fmOldPointer,512);}
