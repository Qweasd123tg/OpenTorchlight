#include <cstring>
#include <stdint.h>
#include <typeinfo>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "SkillProperty.h"
#include "SkillEffectAndAffixes.h"
#include "Skill.h"
#include "Character.h"
TL_ORIGINAL(bool,oApply,(CSkillProperty*,CCharacter*,const Ogre::Vector3*),"_ZN14CSkillProperty28applyAffixesAndEffectsToUnitEP10CCharacterPKN4Ogre7Vector3E")
extern "C" bool nApply(CSkillProperty*,CCharacter*,const Ogre::Vector3*) __asm__("_ZN14CSkillProperty28applyAffixesAndEffectsToUnitEP10CCharacterPKN4Ogre7Vector3E");
TL_FUNCTION(skillOwner,"_ZN6CSkill14getMasterOwnerEv")
TL_FUNCTION(effectApply,"_ZN22CSkillEffectAndAffixes22applyAffixesAndEffectsEP9CBaseUnitP10CCharacterPKN4Ogre7Vector3Eb")
namespace {
autotest::Capture*cap;void*objects[5];unsigned seed;int id(void*p){if(!p)return -1;for(unsigned i=0;i<5;++i)if(objects[i]==p)return i;return -2;}
CBaseUnit*owner(void*p){int v=id(p);cap->add(&v,4);return seed%3==0?NULL:static_cast<CBaseUnit*>(objects[3]);}
bool apply(void*p,void*target,void*source,const Ogre::Vector3*position,bool flag){int values[]={id(p),id(target),id(source)};cap->add(values,sizeof(values));bool hasPosition=position;cap->add(&hasPosition,1);if(position)cap->add(position,sizeof(*position));cap->add(&flag,1);return seed&4;}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);cap=&out;uint64_t ps[(sizeof(CSkillProperty)+7)/8],os[5][(sizeof(CCharacter)+7)/8];std::memset(ps,0,sizeof(ps));CSkillProperty*self=reinterpret_cast<CSkillProperty*>(ps);for(unsigned i=0;i<5;++i)objects[i]=os[i];void*vt[3]={0,const_cast<std::type_info*>(seed%3==1?&typeid(CBaseUnit):&typeid(CCharacter)),0};*reinterpret_cast<void***>(objects[3])=vt+2;self->m_pSkill=reinterpret_cast<CSkill*>(objects[0]);self->m_pSkillEffectAndAffixes=seed&1?reinterpret_cast<CSkillEffectAndAffixes*>(objects[1]):NULL;CCharacter*target=seed&2?static_cast<CCharacter*>(objects[2]):NULL;Ogre::Vector3 vector(float(seed),-1,0);detour::Set patches;TL_REDIRECT(patches,skillOwner,&owner);TL_REDIRECT(patches,effectApply,&apply);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}bool(*fn)(CSkillProperty*,CCharacter*,const Ogre::Vector3*)=ours?nApply:oApply;if(!autotest::beginInvocation(out,fn))return;bool result=fn(self,target,seed&8?&vector:NULL);out.callCompleted=1;out.add(&result,1);}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(state_skill_property_apply){autotest::Coverage coverage("state_skill_property_apply",(uintptr_t)&oApply);for(unsigned seed=0;seed<120;++seed){autotest::Outcome x,y;autotest::runChild(a,&seed,x);autotest::runChild(b,&seed,y);if(coverage.observe(host,x,y)){host->log("    skill property seed %u issue %u/%u exits %d/%d\n",seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
