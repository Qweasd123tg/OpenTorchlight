#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include "ParentPairs.h"
#include "Detour.h"
#define private public
#define protected public
#include "ExecuteSkillProps.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Character.h"
#include "ResourceManager.h"
#include "Level.h"
#include "DataGroup.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(void,exCtorOld,exCtorNew,(CExecuteSkillProps*,CSkill*,CSkillEvent*,CDataGroup*),"_ZN18CExecuteSkillPropsC1EP6CSkillP11CSkillEventP10CDataGroup")
DECL(bool,exOld,exNew,(CExecuteSkillProps*,CBaseUnit*,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CBaseUnit*,int),"_ZN18CExecuteSkillProps12executeSkillEP9CBaseUnitRKN4Ogre7Vector3ERKNS2_10QuaternionES5_S1_i")
#undef DECL
TL_FUNCTION(exAdd,"_ZN13CSkillManager8addSkillERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(exLevel,"_ZN6CSkill32_setLevelOfSkillFromSkillManagerEj")
TL_FUNCTION(exRange,"_ZN6CSkill8getRangeEv")
TL_FUNCTION(exAngle,"_ZN6CSkill18getFindTargetAngleEv")
TL_FUNCTION(exFind,"_ZN6CLevel23findCharacterWithinViewERKN4Ogre7Matrix4E10EAlignmentfffbP10CCharacterP6CSkill")
TL_FUNCTION(exCan,"_ZN13CSkillManager21getSkillCanBeExecutedEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ES3_b")
TL_FUNCTION(exRun,"_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
namespace {
autotest::Capture* cap;unsigned seed;CSkill* skill;CSkillManager* manager;CBaseUnit* caster;CBaseUnit* target;CLevel* level;unsigned char* owner;
void n(unsigned v){cap->add(&v,4);}void pointer(void*p){n(!p?0:p==skill?1:p==manager?2:p==caster?3:p==target?4:p==level?5:p==owner?6:99);}
CSkill* add(CSkillManager*m,const std::wstring&s,bool b){n(10);pointer(m);cap->addText(s);n(b);return skill;}
void setLevel(CSkill*s,unsigned v){n(11);pointer(s);n(v);n(s->m_bExecutedByProperty);s->m_skillLevel=v;}
float range(CSkill*s){n(12);pointer(s);return seed%2?-0.25f:3.5f;}
float angle(CSkill*s){n(13);pointer(s);return seed%2?0.75f:1.5f;}
CCharacter* find(CLevel*l,const Ogre::Matrix4&m,EAlignment a,float f,float g,float h,bool b,CCharacter*c,CSkill*s){n(14);pointer(l);cap->add(&m,sizeof(m));n(a);cap->add(&f,4);cap->add(&g,4);cap->add(&h,4);n(b);pointer(c);pointer(s);return seed%5?reinterpret_cast<CCharacter*>(target):NULL;}
bool can(CSkillManager*m,CSkill*s,CBaseUnit*c,ESKILL_ACTIVATION_TYPE a,const Ogre::Vector3&v,CBaseUnit*t,bool b){n(15);pointer(m);pointer(s);pointer(c);n(a);cap->add(&v,sizeof(v));pointer(t);n(b);return seed%3!=0;}
CSkill* run(CSkillManager*m,CSkill*s,CBaseUnit*c,ESKILL_ACTIVATION_TYPE a,const Ogre::Vector3&v,const Ogre::Quaternion&q,const Ogre::Vector3&to,CBaseUnit*t){n(16);pointer(m);pointer(s);pointer(c);n(a);cap->add(&v,sizeof(v));cap->add(&q,sizeof(q));cap->add(&to,sizeof(to));pointer(t);return seed%4?skill:NULL;}
void side(void* raw,autotest::Capture& out,bool ours,unsigned op){seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;
 uint64_t ss[2][(sizeof(CSkill)+7)/8],ms[(sizeof(CSkillManager)+7)/8],cs[(sizeof(CCharacter)+7)/8],rs[(sizeof(CResourceManager)+7)/8],ls[8],ts[8],os[(sizeof(CCharacter)+7)/8],es[8];
 std::memset(ss,0,sizeof(ss));std::memset(ms,0,sizeof(ms));std::memset(cs,0,sizeof(cs));std::memset(rs,0,sizeof(rs));std::memset(os,0,sizeof(os));
 CSkill*own=reinterpret_cast<CSkill*>(ss[0]);skill=reinterpret_cast<CSkill*>(ss[1]);manager=reinterpret_cast<CSkillManager*>(ms);caster=reinterpret_cast<CBaseUnit*>(cs);target=reinterpret_cast<CBaseUnit*>(ts);level=reinterpret_cast<CLevel*>(ls);owner=reinterpret_cast<unsigned char*>(os);
 // Borrowed owner prefix is used only by the real RTTI query. No Character
 // methods or fabricated virtual callbacks run on this storage.
 void*vt[3]={0,const_cast<std::type_info*>(seed%3==1?&typeid(CBaseUnit):&typeid(CCharacter)),0};*reinterpret_cast<void***>(owner)=vt+2;
 own->m_pSkillManager=seed%7?manager:NULL;own->m_pOwner=seed%4?reinterpret_cast<CBaseUnit*>(owner):NULL;skill->m_iTargetAlignment=int(seed%5);
 CResourceManager* resources=reinterpret_cast<CResourceManager*>(rs);resources->m_pLevel=seed%9?level:NULL;caster->m_pResourceManager=seed%8?resources:NULL;
 detour::Set patches;TL_REDIRECT(patches,exAdd,&add);TL_REDIRECT(patches,exLevel,&setLevel);TL_REDIRECT(patches,exRange,&range);TL_REDIRECT(patches,exAngle,&angle);TL_REDIRECT(patches,exFind,&find);TL_REDIRECT(patches,exCan,&can);TL_REDIRECT(patches,exRun,&run);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 CDataGroup data(L"EXECUTE",NULL,2,2,NULL);if(seed%3)data.AddDataValue(L"SKILL",seed%2?L"Fire Bolt":L"ЖЁЛТЫЙ",false);
 uint64_t storage[(sizeof(CExecuteSkillProps)+7)/8];std::memset(storage,0xa5,sizeof(storage));CExecuteSkillProps* props=reinterpret_cast<CExecuteSkillProps*>(storage);CSkillEvent* event=reinterpret_cast<CSkillEvent*>(es);
 if(op==0){typedef void(*Fn)(CExecuteSkillProps*,CSkill*,CSkillEvent*,CDataGroup*);Fn f=ours?exCtorNew:exCtorOld;int before=g_iTotalCountOfObjects;if(!autotest::beginInvocation(out,f))return;f(props,seed%5?own:NULL,seed%2?event:NULL,seed%4?&data:NULL);out.callCompleted=1;n(g_iTotalCountOfObjects-before);n(props->m_pSkill==(seed%5?own:NULL));n(props->m_pSkillEvent==(seed%2?event:NULL));cap->addText(props->m_sSkillName);}
 else {exCtorOld(props,seed%11?own:NULL,event,NULL);props->m_sSkillName=seed%2?L"Fire Bolt":L"ЖЁЛТЫЙ";Ogre::Vector3 v(float(seed),-1,2),to(3,-4,float(seed)*0.5f);Ogre::Quaternion q(0.5f,0.25f,-0.75f,1.0f);typedef bool(*Fn)(CExecuteSkillProps*,CBaseUnit*,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,CBaseUnit*,int);Fn f=ours?exNew:exOld;if(!autotest::beginInvocation(out,f))return;bool value=f(props,caster,v,q,to,seed%2?target:NULL,int(seed%8)-2);out.callCompleted=1;n(value);n(skill->m_bExecutedByProperty);n(skill->m_skillLevel);cap->addText(props->m_sSkillName);}
 props->~CExecuteSkillProps();out.addHeapInUse();}
void ca(void*p,autotest::Capture&c){side(p,c,false,0);}void cb(void*p,autotest::Capture&c){side(p,c,true,0);}void a(void*p,autotest::Capture&c){side(p,c,false,1);}void b(void*p,autotest::Capture&c){side(p,c,true,1);}
}
TL_TEST(deepen_execute_skill_ctor){return parentpairs::run(host,"deepen_execute_skill_ctor",(uintptr_t)&exCtorOld,64,ca,cb);}
TL_TEST(deepen_execute_skill){return parentpairs::run(host,"deepen_execute_skill",(uintptr_t)&exOld,96,a,b);}
