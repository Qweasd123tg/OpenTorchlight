#include <cstring>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "BaseUnit.h"
#include "Skill.h"
#include "SkillEffectAndAffixes.h"
#include "Affix.h"
#include "Effect.h"
#include "EffectManager.h"
#include "DataGroup.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,seOldMin,seNewMin,(CSkillEffectAndAffixes*,CResourceManager*,unsigned,float&,float&),"_ZN22CSkillEffectAndAffixes28addMinAndMaxValuesOfAnEffectEP16CResourceManagerjRfS2_")
DECL(void,seOldCreate,seNewCreate,(CSkillEffectAndAffixes*,CResourceManager*),"_ZN22CSkillEffectAndAffixes23createAffixesForDisplayEP16CResourceManager")
DECL(bool,seOldDamage,seNewDamage,(CSkillEffectAndAffixes*),"_ZN22CSkillEffectAndAffixes10isDamagingEv")
DECL(void,seOldBonuses,seNewBonuses,(CSkillEffectAndAffixes*,float(&)[6],bool),"_ZN22CSkillEffectAndAffixes18fillOutStatBonusesERA6_fb")
DECL(void,seOldDtor,seNewDtor,(CSkillEffectAndAffixes*),"_ZN22CSkillEffectAndAffixesD1Ev")
#undef DECL
TL_FUNCTION(seTarget,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(seParse,"_ZN6CAffix15parseAffixGroupEv")
TL_FUNCTION(seNewAffix,"_ZN16CResourceManager17getNewAffixByNameERKSbIwSt11char_traitsIwESaIwEEj")
TL_FUNCTION(seSkillOwner,"_ZN6CAffix13setSkillOwnerEP6CSkill")
TL_FUNCTION(seMinimum,"_ZN7CEffect20getMinCaculatedValueEv")
TL_FUNCTION(seMaximum,"_ZN7CEffect20getMaxCaculatedValueEv")
TL_FUNCTION(seDisplay,"_ZN22CSkillEffectAndAffixes15getDisplayStatsEv")
namespace {
struct Case{unsigned op,seed;};autotest::Capture*cap;unsigned seed;CSkill*skill;CResourceManager*resources;CEffect*effects[24];unsigned effectCount;CSkillEffectAndAffixes*self;TSafePointer<CEffect>*effectWeak;TSafePointer<CAffix>*affixWeak;unsigned affixCount;
void number(unsigned n){cap->add(&n,4);}int id(CEffect*e){for(unsigned i=0;i<effectCount;++i)if(effects[i]==e)return i;return -1;}
int target(CSkill*){return 0;}void noParse(CAffix*){}
CEffect*makeEffect(unsigned n){static const int types[]={0,52,7,124,6,144,145};CEffect*e=new CEffect(static_cast<EEFFECT_TYPE>(types[(n+seed)%7]),false,EFFECT_ACTIVATION_PASSIVE,1,2,3,false);if(effectCount>=24)_exit(51);effects[effectCount]=e;effectWeak[effectCount++].setObject(e);e->m_fValueC4=float(n)-2.5f;e->m_fValueC8=float(n)+3.25f;for(unsigned stat=0;stat<(n+seed)%7;++stat){e->m_statModifiers.add(static_cast<EEFFECT_STAT_MODIFIERS>((stat+n)%6));e->m_statModifierValues.add(float(stat*3)-6.5f);}if(seed%5==0)e->m_statModifierValues.m_nCapacity=0;return e;}
CAffix*makeAffix(unsigned n){CAffix*a=new CAffix(n%2?L"made":L"Ж");if(affixCount>=12)_exit(52);affixWeak[affixCount++].setObject(a);a->m_bHasDuration=(seed+n)%2;a->m_fDuration=-1.5f;for(unsigned i=0;i<(n+seed)%3;++i)a->m_Effects.add(makeEffect(n*3+i));return a;}
CAffix*newAffix(CResourceManager*r,const std::wstring&name,unsigned level){number(151);cap->addText(name);number(level);if(r!=resources)cap->issue=autotest::Capture::InvalidReport;if((level+seed)%4==0)return NULL;return makeAffix(level%4);}
void skillOwner(CAffix*a,CSkill*s){number(157);if(s!=skill)cap->issue=autotest::Capture::InvalidReport;a->m_SkillOwner.setObject(s);}
float minimum(CEffect*e){number(163);int n=id(e);cap->add(&n,4);e->m_iLevel++;return e->m_fValueC4;}
float maximum(CEffect*e){number(167);int n=id(e);cap->add(&n,4);e->m_iLevel++;return e->m_fValueC8;}
std::wstring display(CSkillEffectAndAffixes*p){number(173);if(p!=self)cap->issue=autotest::Capture::InvalidReport;if(seed%3)p->m_displayAffixes.add(makeAffix(1));return seed%2?L"lazy":L"";}
void state(CSkillEffectAndAffixes*p){number(p->m_displayAffixes.size());for(unsigned i=0;i<p->m_displayAffixes.size();++i){CAffix*a=p->m_displayAffixes[i];cap->addText(a->m_sAffixFileName);cap->add(&a->m_fDuration,4);cap->add(&a->m_bHasDuration,1);bool owned=a->m_SkillOwner.getObject()==skill;cap->add(&owned,1);number(a->m_Effects.size());}for(unsigned i=0;i<effectCount;++i)if(effectWeak[i].getObject()){number(i);cap->add(&effects[i]->m_iLevel,4);cap->add(&effects[i]->m_eType,4);}}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;effectCount=affixCount=0;TSafePointer<CEffect> ew[24];TSafePointer<CAffix> aw[12];effectWeak=ew;affixWeak=aw;uint64_t skillStorage[(sizeof(CSkill)+7)/8];std::memset(skillStorage,0,sizeof(skillStorage));CRunicCore*skillLife=new(skillStorage)CRunicCore;skill=reinterpret_cast<CSkill*>(skillLife);uint64_t resourcesWitness=0;resources=reinterpret_cast<CResourceManager*>(&resourcesWitness);detour::Set patches;TL_REDIRECT(patches,seTarget,&target);TL_REDIRECT(patches,seParse,&noParse);TL_REDIRECT(patches,seNewAffix,&newAffix);TL_REDIRECT(patches,seSkillOwner,&skillOwner);TL_REDIRECT(patches,seMinimum,&minimum);TL_REDIRECT(patches,seMaximum,&maximum);if(patches.failed())_exit(43);CDataGroup data(L"empty",NULL,1,1,NULL);uint64_t storage[(sizeof(CSkillEffectAndAffixes)+7)/8];self=new(storage)CSkillEffectAndAffixes(skill,&data,NULL);TSafePointer<CSkillEffectAndAffixes> weak;weak.setObject(self);
 for(unsigned i=0;i<seed%4;++i){CSkillEffectAndAffixes::CSkillAffixData*a=new CSkillEffectAndAffixes::CSkillAffixData;a->m_name=i%2?L"named":L"Ж";a->m_value18=i+1;a->m_unitType=i;a->m_targetType=i%3;static const float durations[]={-1,0,0.25f,3};a->m_durationOverride=durations[(i+seed)%4];self->m_affixData.add(a);}
 for(unsigned i=0;i<(seed/2)%4;++i){CSkillEffectAndAffixes::CSkillEffectData*g=new CSkillEffectAndAffixes::CSkillEffectData;g->m_flag10=(seed+i)%2;g->m_value30=i;g->m_value34=i%3;for(unsigned j=0;j<(seed+i)%4;++j)g->m_effects.add(makeEffect(i*3+j));if(c.op==0&&seed%4==0)g->m_effects.add(NULL);self->m_effectData.add(g);}
 if(c.op!=1||seed%3==0)for(unsigned i=0;i<(seed/3)%3;++i){CAffix*a=makeAffix(i);if(c.op==0&&seed%4==0)a->m_Effects.add(NULL);self->m_displayAffixes.add(a);}
 self->m_affixNames.add(L"affix");self->m_effectNames.add(L"effect-Ж");self->m_name=L"group";float lo=-3.5f,hi=7.25f,bonuses[6]={-9,0,1,5,-2,17};
 if(c.op==0)autotest::invoke<void(*)(CSkillEffectAndAffixes*,CResourceManager*,unsigned,float&,float&),CSkillEffectAndAffixes*,CResourceManager*,unsigned,float&,float&>(out,ours?&seNewMin:&seOldMin,self,resources,seed%2?7u:144u,lo,seed%6==0?lo:hi);
 if(c.op==1)autotest::invoke(out,ours?&seNewCreate:&seOldCreate,self,resources);
 if(c.op==2){typedef bool(*Fn)(CSkillEffectAndAffixes*);Fn f=ours?&seNewDamage:&seOldDamage;if(!autotest::beginInvocation(out,f))return;bool value=f(self);out.callCompleted=1;out.add(&value,1);}
 if(c.op==3){TL_REDIRECT(patches,seDisplay,&display);if(patches.failed())_exit(43);autotest::invoke<void(*)(CSkillEffectAndAffixes*,float(&)[6],bool),CSkillEffectAndAffixes*,float(&)[6],bool>(out,ours?&seNewBonuses:&seOldBonuses,self,bonuses,seed%2!=0);}
 out.add(&lo,4);out.add(&hi,4);out.add(bonuses,sizeof(bonuses));if(c.op!=4)state(self);if(c.op==4)autotest::invoke(out,ours?&seNewDtor:&seOldDtor,self);else seOldDtor(self);bool invalid=weak.getObject()==NULL;out.add(&invalid,1);if(!invalid)out.issue=autotest::Capture::InvalidReport;for(unsigned i=0;i<effectCount;++i){bool live=ew[i].getObject()!=NULL;out.add(&live,1);if(live)delete ew[i].getObject();}for(unsigned i=0;i<affixCount;++i){bool live=aw[i].getObject()!=NULL;out.add(&live,1);if(live)out.issue=autotest::Capture::InvalidReport;}skillLife->~CRunicCore();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void recovered(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(continuation_skill_effect_values){int failures=0;const uintptr_t functions[]={(uintptr_t)&seOldMin,(uintptr_t)&seOldCreate,(uintptr_t)&seOldDamage,(uintptr_t)&seOldBonuses,(uintptr_t)&seOldDtor};for(unsigned op=0;op<5;++op){autotest::Coverage coverage("continuation_skill_effect_values",functions[op]);for(unsigned i=0;i<40;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;TL_CHECK(failures,ok);if(!ok){host->log("    skill effects op %u seed %u status %d/%d issue %u/%u bytes %lu/%lu\n",op,i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k<a.capture.length&&k<b.capture.length;++k)if(a.capture.data[k]!=b.capture.data[k])host->log("    skill effects diff byte%u %02x/%02x\n",k,a.capture.data[k],b.capture.data[k]);coverage.report(host);return failures;}}coverage.report(host);}return failures;}
