#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include "ParentPairs.h"
#include "Detour.h"
#define private public
#define protected public
#include "SkillManager.h"
#include "Skill.h"
#include "BaseUnit.h"
#include "Character.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(void,dsStopOld,dsStopNew,(CSkillManager*,bool,bool,bool),"_ZN13CSkillManager13stopAllSkillsEbbb")
DECL(void,dsDeleteOld,dsDeleteNew,(CSkillManager*,CSkill*),"_ZN13CSkillManager19deleteSpecificSkillEP6CSkill")
DECL(void,dsPassiveOld,dsPassiveNew,(CSkillManager*,CBaseUnit*,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&),"_ZN13CSkillManager18startPassiveSkillsEP9CBaseUnitRKN4Ogre7Vector3ERKNS2_10QuaternionES5_")
DECL(void,dsLevelOld,dsLevelNew,(CSkillManager*,CSkill*,unsigned),"_ZN13CSkillManager13setSkillLevelEP6CSkillj")
DECL(void,dsDeathOld,dsDeathNew,(CSkillManager*,CBaseUnit*,ESKILL_ACTIVATION_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CCharacter*),"_ZN13CSkillManager17fireSkillsOnDeathEP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS3_10QuaternionES6_P10CCharacter")
#undef DECL
TL_FUNCTION(dsName,"_ZN6CSkill7getNameEv")
TL_FUNCTION(dsStop,"_ZN6CSkill9stopSkillEv")
TL_FUNCTION(dsAttempt,"_ZN6CSkill18attemptToStopSkillEv")
TL_FUNCTION(dsHas,"_ZN6CSkill8hasEventE17ESKILL_EVENT_TYPE")
TL_FUNCTION(dsCalculate,"_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(dsWeapon,"_ZN6CSkill21weaponRequirementsMetEP10CCharacter")
TL_FUNCTION(dsSkillLevel,"_ZN6CSkill32_setLevelOfSkillFromSkillManagerEj")
TL_FUNCTION(dsTarget,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(dsPosition,"_ZN13CSkillManager19getPositionForSkillEP6CSkillP9CBaseUnit")
TL_FUNCTION(dsUpdate,"_ZN13CSkillManager6updateEf")
TL_FUNCTION(dsExecute,"_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
TL_FUNCTION(dsEvent,"_ZN13CSkillManager17triggerSkillEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnit")
TL_FUNCTION(dsUnitPosition,"_ZN19CPositionableObject11getPositionEb")
namespace {
autotest::Capture*cap;unsigned seed,op,positionCalls;CSkillManager*manager;CSkill*skills[6];std::wstring names[6];CBaseUnit*caster;CBaseUnit*target;
void n(unsigned v){cap->add(&v,4);}int id(void*p){if(!p)return -1;for(unsigned i=0;i<6;++i)if(p==skills[i])return i;return p==manager?10:p==caster?11:p==target?12:99;}void ptr(void*p){int v=id(p);cap->add(&v,4);}void event(unsigned e,void*p){n(e);ptr(p);}
struct SkillLife:CRunicCore{unsigned char fields[sizeof(CSkill)-sizeof(CRunicCore)];unsigned identity;SkillLife(unsigned i):identity(i){std::memset(fields,0,sizeof(fields));new(&reinterpret_cast<CSkill*>(this)->m_Target)TSafePointer<CBaseUnit>();}virtual~SkillLife(){event(100,this);n(identity);reinterpret_cast<CSkill*>(this)->m_Target.~TSafePointer<CBaseUnit>();}};
const std::wstring& name(CSkill*s){event(1,s);return names[id(s)];}
void stopped(CSkill*s,unsigned tag){event(tag,s);s->m_interruptible=false;if(seed%11==0)manager->m_UpdatingSkills.remove(s);}
void stop(CSkill*s){stopped(s,2);}void attempt(CSkill*s){stopped(s,3);}
bool has(CSkill*s,ESKILL_EVENT_TYPE e){event(4,s);n(e);return (seed/5+id(s)*3)%4==0;}
bool calculate(CSkill*s){event(5,s);s->m_iEffectiveSkillLevel=(seed+id(s))%3;return seed%2;}
bool weapon(CSkill*s,CCharacter*c){event(6,s);ptr(c);return (seed/7+id(s))%3!=0;}
void setLevel(CSkill*s,unsigned value){event(7,s);n(value);s->m_skillLevel=value;}
int targetType(CSkill*s){event(8,s);const int values[]={0,1,5,6,2,7};return values[(seed/3+id(s))%6];}
Ogre::Vector3* position(CSkillManager*m,CSkill*s,CBaseUnit*u){event(9,m);ptr(s);ptr(u);m->m_skillPosition=Ogre::Vector3(float(seed),float(id(s)),-2);return (seed/11+id(s))%3?&m->m_skillPosition:NULL;}
void update(CSkillManager*m,float f){event(10,m);cap->add(&f,4);if(seed%13==0)m->m_OtherSkills.clear();}
CSkill* execute(CSkillManager*m,CSkill*s,CBaseUnit*c,ESKILL_ACTIVATION_TYPE a,const Ogre::Vector3&v,const Ogre::Quaternion&q,const Ogre::Vector3&to,CBaseUnit*t){event(11,m);ptr(s);ptr(c);n(a);cap->add(&v,sizeof(v));cap->add(&q,sizeof(q));cap->add(&to,sizeof(to));ptr(t);return s;}
void trigger(CSkillManager*m,ESKILL_EVENT_TYPE e,const Ogre::Vector3&v,const Ogre::Quaternion&q,CBaseUnit*t){event(12,m);n(e);cap->add(&v,sizeof(v));cap->add(&q,sizeof(q));ptr(t);}
Ogre::Vector3 unitPosition(CPositionableObject*u,bool absolute){event(13,u);n(absolute);return Ogre::Vector3(float(++positionCalls),float(seed),absolute?-3:3);}
Ogre::Quaternion orientation(CPositionableObject*u){event(14,u);return Ogre::Quaternion(0.5f,float(seed),-0.75f,1.0f);}
void passive(CSkillManager*m,CBaseUnit*c,const Ogre::Vector3&v,const Ogre::Quaternion&q,const Ogre::Vector3&to){event(15,m);ptr(c);cap->add(&v,sizeof(v));cap->add(&q,sizeof(q));cap->add(&to,sizeof(to));}
void side(void*raw,autotest::Capture&out,bool ours,unsigned mode){seed=static_cast<parentpairs::Case*>(raw)->seed;op=mode;cap=&out;positionCalls=0;
 uint64_t us[(sizeof(CCharacter)+7)/8],ts[8];std::memset(us,0,sizeof(us));caster=reinterpret_cast<CBaseUnit*>(us);target=reinterpret_cast<CBaseUnit*>(ts);void*vt[34]={0};vt[1]=const_cast<std::type_info*>(seed%5==1?&typeid(CBaseUnit):&typeid(CCharacter));vt[32]=reinterpret_cast<void*>(&orientation);*reinterpret_cast<void***>(caster)=vt+2;
 manager=new CSkillManager(NULL,NULL);manager->m_Owner.m_pObject=caster;manager->m_Owner.m_nIndex=0;TSafePointer<CSkill> witnesses[6];for(unsigned i=0;i<6;++i){skills[i]=reinterpret_cast<CSkill*>(new SkillLife(i));witnesses[i].setObject(skills[i]);names[i]=i<2?L"Alpha":i<4?L"Beta":i==4?L"ALPHA":L"orphan";CSkill*s=skills[i];s->m_skillLevel=seed%2?(seed/6+i/2)%3:(seed+i)%3;s->m_eActivationType=static_cast<ESKILL_ACTIVATION_TYPE>((seed+i)%5);s->m_suppressNormalStop=(seed+i)%2;s->m_interruptible=true;}
 for(unsigned i=0;i<seed%7;++i)manager->m_UpdatingSkills.add(skills[i]);for(unsigned i=0;i<(seed/2)%7;++i)manager->m_OtherSkills.add(skills[i]);for(unsigned group=0;group<seed%4;++group){TArrayList<CSkill*>* list=new TArrayList<CSkill*>(1);list->add(skills[group*2]);list->add(skills[group*2+1]);manager->m_SkillsByName[group==0?L"ALPHA":group==1?L"BETA":L"ORPHAN"]=list;}
 detour::Set patches;TL_REDIRECT(patches,dsName,&name);TL_REDIRECT(patches,dsStop,&stop);TL_REDIRECT(patches,dsAttempt,&attempt);TL_REDIRECT(patches,dsHas,&has);TL_REDIRECT(patches,dsCalculate,&calculate);TL_REDIRECT(patches,dsWeapon,&weapon);TL_REDIRECT(patches,dsSkillLevel,&setLevel);TL_REDIRECT(patches,dsTarget,&targetType);TL_REDIRECT(patches,dsPosition,&position);TL_REDIRECT(patches,dsUpdate,&update);TL_REDIRECT(patches,dsExecute,&execute);TL_REDIRECT(patches,dsEvent,&trigger);TL_REDIRECT(patches,dsUnitPosition,&unitPosition);if(mode==3)patches.redirect(reinterpret_cast<char*>(&dsPassiveOld),reinterpret_cast<char*>(&dsPassiveNew),&passive);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 Ogre::Vector3 v(float(seed),2,-3),to(-4,5,float(seed));Ogre::Quaternion q(1,0.25f,0.5f,-0.5f);CSkill* skill=skills[seed%6];
 if(mode==0){typedef void(*Fn)(CSkillManager*,bool,bool,bool);Fn f=ours?dsStopNew:dsStopOld;if(!autotest::beginInvocation(out,f))return;f(manager,seed&1,seed&2,seed&4);}
 if(mode==1){typedef void(*Fn)(CSkillManager*,CSkill*);Fn f=ours?dsDeleteNew:dsDeleteOld;if(!autotest::beginInvocation(out,f))return;f(manager,skill);}
 if(mode==2){typedef void(*Fn)(CSkillManager*,CBaseUnit*,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&);Fn f=ours?dsPassiveNew:dsPassiveOld;if(!autotest::beginInvocation(out,f))return;f(manager,seed%7?caster:NULL,v,q,to);}
 if(mode==3){typedef void(*Fn)(CSkillManager*,CSkill*,unsigned);Fn f=ours?dsLevelNew:dsLevelOld;if(!autotest::beginInvocation(out,f))return;f(manager,skill,seed%4);}
 if(mode==4){typedef void(*Fn)(CSkillManager*,CBaseUnit*,ESKILL_ACTIVATION_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CCharacter*);Fn f=ours?dsDeathNew:dsDeathOld;if(!autotest::beginInvocation(out,f))return;f(manager,caster,static_cast<ESKILL_ACTIVATION_TYPE>(seed%5),v,q,to,seed%2?reinterpret_cast<CCharacter*>(target):NULL);}
 out.callCompleted=1;n(200);for(unsigned i=0;i<6;++i){bool live=witnesses[i].getObject()!=NULL;n(live);if(live){n(skills[i]->m_skillLevel);n(skills[i]->m_iEffectiveSkillLevel);n(skills[i]->m_interruptible);}}for(unsigned a=0;a<2;++a){TArrayList<CSkill*>&list=a?manager->m_OtherSkills:manager->m_UpdatingSkills;n(list.size());for(unsigned i=0;i<list.size();++i)ptr(list[i]);}n(manager->m_SkillsByName.size());for(std::map<std::wstring,TArrayList<CSkill*>*>::iterator i=manager->m_SkillsByName.begin();i!=manager->m_SkillsByName.end();++i){cap->addText(i->first);n(i->second->size());for(unsigned j=0;j<i->second->size();++j)ptr((*i->second)[j]);delete i->second;}
 manager->m_SkillsByName.clear();manager->m_UpdatingSkills.clear();manager->m_OtherSkills.clear();manager->m_Owner.m_pObject=NULL;delete manager;for(unsigned i=0;i<6;++i)if(witnesses[i].getObject())delete reinterpret_cast<SkillLife*>(skills[i]);out.addHeapInUse();}
#define BODY(name,num) void name##a(void*p,autotest::Capture&c){side(p,c,false,num);}void name##b(void*p,autotest::Capture&c){side(p,c,true,num);}
BODY(stop,0)BODY(del,1)BODY(pass,2)BODY(lvl,3)BODY(death,4)
#undef BODY
}
#define TEST(name,old,a,b) TL_TEST(name){return parentpairs::run(host,#name,(uintptr_t)&old,120,a,b);}
TEST(deepen_skill_stop,dsStopOld,stopa,stopb)
TEST(deepen_skill_delete_specific,dsDeleteOld,dela,delb)
TEST(deepen_skill_passive,dsPassiveOld,passa,passb)
TEST(deepen_skill_set_level,dsLevelOld,lvla,lvlb)
TEST(deepen_skill_death,dsDeathOld,deatha,deathb)
