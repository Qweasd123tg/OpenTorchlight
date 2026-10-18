#include <cstring>
#include <map>
#include <string>
#include <new>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillEvent.h"
#include "SkillProperty.h"
#include "SkillEffectAndAffixes.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(void,prOldStats,prNewStats,(CSkillProperty*,float(&)[6],bool),"_ZN14CSkillProperty18fillOutStatBonusesERA6_fb")
DECL(bool,prOldCan,prNewCan,(CSkillProperty*,CBaseUnit*,CCharacter*),"_ZN14CSkillProperty35canAffixesAndEffectsBeAppliedToUnitEP9CBaseUnitP10CCharacter")
DECL(void,prOldMin,prNewMin,(CSkillProperty*,CResourceManager*,unsigned,float&,float&),"_ZN14CSkillProperty28addMinAndMaxValuesOfAnEffectEP16CResourceManagerjRfS2_")
DECL(CSkillEvent*,prOldClone,prNewClone,(CSkillProperty*,CSkillEvent*),"_ZN14CSkillProperty18cloneEventForSkillEP11CSkillEvent")
DECL(void,prOldDtor,prNewDtor,(CSkillProperty*),"_ZN14CSkillPropertyD1Ev")
#undef DECL
TL_ORIGINAL(void,prCtor,(CSkillProperty*,CSkill*,CResourceManager*,CSkillProperty*,CDataGroup*,unsigned),"_ZN14CSkillPropertyC1EP6CSkillP16CResourceManagerPS_P10CDataGroupj")
TL_ORIGINAL(void,prEventCtor,(CSkillEvent*,CSkill*,CSkillProperty*,CResourceManager*,CDataGroup*),"_ZN11CSkillEventC1EP6CSkillP14CSkillPropertyP16CResourceManagerP10CDataGroup")
TL_FUNCTION(prEffectStats,"_ZN22CSkillEffectAndAffixes18fillOutStatBonusesERA6_fb")
TL_FUNCTION(prEffectCan,"_ZN22CSkillEffectAndAffixes35canAffixesAndEffectsBeAppliedToUnitEP9CBaseUnitP10CCharacter")
TL_FUNCTION(prEffectMin,"_ZN22CSkillEffectAndAffixes28addMinAndMaxValuesOfAnEffectEP16CResourceManagerjRfS2_")
TL_FUNCTION(prCloneCtor,"_ZN11CSkillEventC1EP6CSkillP14CSkillPropertyP16CResourceManagerP10CDataGroup")
namespace {
using namespace smallmass;
unsigned seed;void*ids[24];detour::Set* ctorHook;CSkillEvent*cloned;
int id(const void*p){if(!p)return -1;for(unsigned i=0;i<24;++i)if(p==ids[i])return i;return -2;}
void call(unsigned k,const void*p){number(k);number(id(p));}
void stats(CSkillEffectAndAffixes*p,float(&v)[6],bool base){call(1,p);number(base);for(unsigned i=0;i<6;++i)v[i]+=float(id(p)+1)*float(i+1)*(base?2:1);}
bool can(CSkillEffectAndAffixes*p,CBaseUnit*u,CCharacter*c){call(2,p);number(id(u));number(id(c));return (unsigned(id(p))+(seed>>4))%3!=0;}
void minimum(CSkillEffectAndAffixes*p,CResourceManager*r,unsigned e,float&lo,float&hi){call(3,p);number(id(r));number(e);lo+=float(id(p)+1);hi+=float(id(p)+11);}
void destroyEffect(CSkillEffectAndAffixes*p){call(4,p);}
void cloneCtor(CSkillEvent*p,CSkill*skill,CSkillProperty*property,CResourceManager*r,CDataGroup*data){
 call(5,skill);number(id(property));number(id(r));number(id(data));ctorHook->restore();prEventCtor(p,NULL,NULL,NULL,NULL);TL_REDIRECT(*ctorHook,prCloneCtor,&cloneCtor);if(ctorHook->failed())std::abort();cloned=p;ids[23]=p;
 p->m_pSkill=skill;p->m_pSkillProperty=property;p->m_pResourceManager=r;p->m_data=data;
}
void propertySide(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;cloned=NULL;for(unsigned i=0;i<24;++i)ids[i]=object(0x400);
 CSkillProperty*self=static_cast<CSkillProperty*>(Ogre::GeneralAllocPolicy::allocateBytes(sizeof(CSkillProperty)));prCtor(self,NULL,NULL,NULL,NULL,0);ids[0]=self;
 self->m_pSkill=static_cast<CSkill*>(ids[1]);self->m_pResourceManager=static_cast<CResourceManager*>(ids[2]);
 CSkillEffectAndAffixes*effects[5];void*effectVT[2]={NULL,reinterpret_cast<void*>(&destroyEffect)};
 for(unsigned i=0;i<5;++i){effects[i]=static_cast<CSkillEffectAndAffixes*>(ids[3+i]);*reinterpret_cast<void***>(effects[i])=effectVT;}
 self->m_pSkillEffectAndAffixes=seed&1?effects[0]:NULL;
 CSkillEvent*events[9];unsigned count=0;
 const unsigned groups=c.op==3?11:seed%4;
 for(unsigned i=0;i<groups;++i){
  TArrayList<CSkillEvent*>*list=new TArrayList<CSkillEvent*>(2);self->m_eventLists.add(list);
  unsigned n=c.op==3?(i==unsigned(seed%13)?1:0):(seed+i)%3;
  for(unsigned j=0;j<n;++j){
   CSkillEvent*e=static_cast<CSkillEvent*>(Ogre::GeneralAllocPolicy::allocateBytes(sizeof(CSkillEvent)));prEventCtor(e,NULL,NULL,NULL,NULL);events[count]=e;ids[9+count]=e;++count;
   e->m_pSkillEffectAndAffixes=(seed+i+j)&2?effects[1+(i+j)%4]:NULL;e->m_weaponDamageScale=0;e->m_eventType=static_cast<ESKILL_EVENT_TYPE>(i);e->m_data=static_cast<CDataGroup*>(ids[8]);list->add(e);
  }
 }
 CSkillEvent*original=count?events[0]:NULL;
 if(c.op==3){
  if(!original){original=static_cast<CSkillEvent*>(Ogre::GeneralAllocPolicy::allocateBytes(sizeof(CSkillEvent)));prEventCtor(original,NULL,NULL,NULL,NULL);events[count++]=original;}
  original->m_eventType=static_cast<ESKILL_EVENT_TYPE>(seed%13);original->m_data=static_cast<CDataGroup*>(ids[8]);
 }
 float values[]={0,1,-2,3,-4,5};float lo=-2,hi=10;bool result=false;CSkillEvent*clone=NULL;int before=g_iTotalCountOfObjects;
 if(c.op==0){typedef void(*Fn)(CSkillProperty*,float(&)[6],bool);Fn fn=ours?prNewStats:prOldStats;if(!autotest::beginInvocation(out,fn))return;fn(self,values,seed&8);}
 if(c.op==1){typedef bool(*Fn)(CSkillProperty*,CBaseUnit*,CCharacter*);Fn fn=ours?prNewCan:prOldCan;if(!autotest::beginInvocation(out,fn))return;result=fn(self,static_cast<CBaseUnit*>(ids[20]),static_cast<CCharacter*>(ids[21]));}
 if(c.op==2){typedef void(*Fn)(CSkillProperty*,CResourceManager*,unsigned,float&,float&);Fn fn=ours?prNewMin:prOldMin;if(!autotest::beginInvocation(out,fn))return;fn(self,self->m_pResourceManager,seed%7,lo,hi);}
 if(c.op==3){typedef CSkillEvent*(*Fn)(CSkillProperty*,CSkillEvent*);Fn fn=ours?prNewClone:prOldClone;if(!autotest::beginInvocation(out,fn))return;clone=fn(self,seed&16?NULL:original);}
 if(c.op==4){typedef void(*Fn)(CSkillProperty*);Fn fn=ours?prNewDtor:prOldDtor;for(unsigned i=0;i<count;++i)events[i]->m_pSkillEffectAndAffixes=NULL;if(!autotest::beginInvocation(out,fn))return;fn(self);}
 out.callCompleted=1;out.add(values,sizeof(values));floating(lo);floating(hi);number(result);number(id(clone));number(clone?clone->m_cloneSource==original:0);number(g_iTotalCountOfObjects-before);
 number(self->m_eventLists.size());number(self->m_eventLists.m_nCapacity);number(self->m_eventLists.m_pData!=NULL);number(self->m_pSkillEffectAndAffixes!=NULL);
 if(c.op!=4){
  self->m_pSkillEffectAndAffixes=NULL;for(unsigned i=0;i<count;++i)events[i]->m_pSkillEffectAndAffixes=NULL;
  // The source event used for a failed clone can be outside the owning list.
  bool inList=false;for(unsigned i=0;i<self->m_eventLists.size();++i)for(unsigned j=0;j<self->m_eventLists[i]->size();++j)if((*self->m_eventLists[i])[j]==original)inList=true;
  if(c.op==3 && original && !inList)delete original;
  prOldDtor(self);
 }
 Ogre::GeneralAllocPolicy::deallocateBytes(self);
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address){
 detour::Set ctor;ctorHook=&ctor;TL_REDIRECT(ctor,prCloneCtor,&cloneCtor);
 detour::Set h;TL_REDIRECT(h,prEffectStats,&stats);TL_REDIRECT(h,prEffectCan,&can);TL_REDIRECT(h,prEffectMin,&minimum);if(h.failed()||ctor.failed())return 1;
 return smallmass::run(host,op,name,address,&propertySide,128);
}
}
TL_TEST(complete_property_stat_bonuses){return run(host,0,"complete_property_stat_bonuses",0xcdce70);}
TL_TEST(complete_property_can_apply){return run(host,1,"complete_property_can_apply",0xcdcf70);}
TL_TEST(complete_property_min_max){return run(host,2,"complete_property_min_max",0xcdd060);}
TL_TEST(complete_property_clone_event){return run(host,3,"complete_property_clone_event",0xcdd240);}
TL_TEST(complete_property_destructor){return run(host,4,"complete_property_destructor",0xce5940);}
