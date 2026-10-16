#include <cstring>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "SkillController.h"
#include "SkillManager.h"
#include "Skill.h"
#include "Character.h"
#include "GameClient.h"
#undef private
#undef protected
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,oLearn,nLearn,(CSkillController*),"_ZN16CSkillController10learnSkillEv")
DECL(CCharacter*,oTarget,nTarget,(CSkillController*),"_ZN16CSkillController14getSkillTargetEv")
#undef DECL
TL_FUNCTION(configure,"_ZN16CSkillController13configureUnitEv")
TL_FUNCTION(skillKnows,"_ZN13CSkillManager10knowsSkillERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(unitAddSkill,"_ZN9CBaseUnit14addSkillByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(skillLevel,"_ZN13CSkillManager13setSkillLevelEP6CSkillj")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;void*objects[8];unsigned seed;
int id(void*p){if(!p)return -1;for(unsigned i=0;i<8;++i)if(p==objects[i])return i;return -2;}
void event(unsigned k,void*p){int n=id(p);cap->add(&k,4);cap->add(&n,4);}
bool config(void*p){event(1,p);return seed&1;}bool knows(void*p,const std::wstring&s){event(2,p);cap->addText(s);return seed&4;}
CSkill*add(void*p,const std::wstring&s,bool b){event(3,p);cap->addText(s);cap->add(&b,1);return seed&8?static_cast<CSkill*>(objects[7]):NULL;}
void level(void*p,void*s,unsigned n){event(4,p);event(5,s);cap->add(&n,4);}void broadcast(void*p,unsigned n){event(6,p);cap->add(&n,4);}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;uint64_t ss[(sizeof(CSkillController)+7)/8],cs[(sizeof(CCharacter)+7)/8],rs[(sizeof(CResourceManager)+7)/8],gs[2][(sizeof(CGameClient)+7)/8],ps[2][(sizeof(CPlayer)+7)/8],ms[32],skill[32];std::memset(ss,0,sizeof(ss));std::memset(cs,0x5a,sizeof(cs));CSkillController*self=reinterpret_cast<CSkillController*>(ss);CCharacter*character=reinterpret_cast<CCharacter*>(cs);CResourceManager*resources=reinterpret_cast<CResourceManager*>(rs);objects[0]=self;objects[1]=character;objects[2]=gs[0];objects[3]=gs[1];objects[4]=ps[0];objects[5]=ps[1];objects[6]=ms;objects[7]=skill;void*vt[7]={0};vt[6]=reinterpret_cast<void*>(&broadcast);*reinterpret_cast<void***>(self)=vt;new(&self->m_sSkillName)std::wstring(seed%3?L"Skill_A":L"");self->m_pRunicCore=seed%7?character:NULL;self->m_pResourceManager=resources;self->m_bUsePlayerAsTarget=seed&2;self->m_bUseUnitTarget=seed&4;character->m_eBaseUnitType=static_cast<EBASEUNIT_TYPE>((seed/3)%4);character->m_targetCharacter.m_pObject=seed&8?reinterpret_cast<CCharacter*>(ps[0]):NULL;character->m_pSkillManager=seed&16?reinterpret_cast<CSkillManager*>(ms):NULL;new(&resources->m_GameClients)TArrayList<CGameClient*>(2);resources->m_GameClients.add(reinterpret_cast<CGameClient*>(gs[seed%2]));for(unsigned i=0;i<2;++i)reinterpret_cast<CGameClient*>(gs[i])->m_pPlayer=seed&32?NULL:reinterpret_cast<CPlayer*>(ps[i]);
 detour::Set patches;TL_REDIRECT(patches,configure,&config);TL_REDIRECT(patches,skillKnows,&knows);TL_REDIRECT(patches,unitAddSkill,&add);TL_REDIRECT(patches,skillLevel,&level);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.mode==0){void(*fn)(CSkillController*)=ours?nLearn:oLearn;if(!autotest::beginInvocation(out,fn))return;fn(self);out.callCompleted=1;}else{CCharacter*(*fn)(CSkillController*)=ours?nTarget:oTarget;if(!autotest::beginInvocation(out,fn))return;CCharacter*r=fn(self);out.callCompleted=1;int n=id(r);out.add(&n,4);CCharacter*expected=NULL;if(self->m_bUsePlayerAsTarget)expected=reinterpret_cast<CGameClient*>(gs[seed%2])->m_pPlayer;else if(self->m_bUseUnitTarget&&self->m_pRunicCore&&character->m_eBaseUnitType==0)expected=character->m_targetCharacter.m_pObject;if(r!=expected)out.issue=autotest::Capture::InvalidReport;}out.addText(self->m_sSkillName);self->m_sSkillName.~basic_string();resources->m_GameClients.~TArrayList();
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned m,const char*n,uintptr_t address){autotest::Coverage coverage(n,address);for(unsigned i=0;i<120;++i){Case c={m,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    skill controller mode %u seed %u issue %u/%u exits %d/%d\n",m,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(state_skill_controller_learn,0,oLearn)
TEST(state_skill_controller_target,1,oTarget)
