#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "SkillEffectAndAffixes.h"
#include "Effect.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,oldDuration,newDuration,(void*,float),"_ZN22CSkillEffectAndAffixes19setDurationOverrideEf")
DECL(bool,oldEnemy,newEnemy,(void*,void*),"_ZN22CSkillEffectAndAffixes18effectsTargetEnemyEP9CBaseUnit")
DECL(std::wstring,oldPortal,newPortal,(void*),"_ZN22CSkillEffectAndAffixes18getPortalSkillNameEv")
DECL(void,oldAppend,newAppend,(void*,const std::wstring&),"_ZN22CSkillEffectAndAffixes10appendNameERKSbIwSt11char_traitsIwESaIwEE")
#undef DECL
TL_FUNCTION(unitISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;unsigned mask;void*unitAddress;
bool isa(void*self,unsigned type){cap->add(&type,4);if(self!=unitAddress)cap->issue=autotest::Capture::InvalidReport;return type<8&&(mask&(1u<<type));}
void text(autotest::Capture&out,const std::wstring&s){unsigned n=s.size();out.add(&n,4);if(n)out.add(s.data(),4*n);}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);cap=&out;
 typedef CSkillEffectAndAffixes::CSkillAffixData A;typedef CSkillEffectAndAffixes::CSkillEffectData D;
 uint64_t object[(sizeof(CSkillEffectAndAffixes)+7)/8],affix[4][(sizeof(A)+7)/8],data[3][(sizeof(D)+7)/8],effect[6][(sizeof(CEffect)+7)/8],unit[64];
 std::memset(object,0xa5,sizeof(object));std::memset(effect,0x3c,sizeof(effect));CSkillEffectAndAffixes*self=reinterpret_cast<CSkillEffectAndAffixes*>(object);
 new(&self->m_affixData)TArrayList<A*>(2);new(&self->m_effectData)TArrayList<D*>(2);
 A*as[4];D*ds[3];CEffect*es[6];std::wstring expected[6];float durations[6];float input[]={-1.0f,0.0f,0.25f,8.0f};float duration=input[(c.seed/7)%4];
 const wchar_t*names[]={L"",L"A",L"Ж",L"AA"};
 for(unsigned i=0;i<6;++i){es[i]=reinterpret_cast<CEffect*>(effect[i]);es[i]->m_eType=static_cast<EEFFECT_TYPE>((i+c.seed)%4==0?0x71:3);es[i]->m_bFlag28=(i+c.seed)%3==0;es[i]->m_fValue24=-3.0f-i;new(&es[i]->m_sName)std::wstring(names[(i+c.seed/9)%4]);expected[i]=es[i]->m_sName;durations[i]=es[i]->m_fValue24;}
 for(unsigned i=0;i<4;++i){as[i]=reinterpret_cast<A*>(affix[i]);as[i]->m_unitType=(i+c.seed/3)%6;as[i]->m_targetType=(i+c.seed/5)%3;as[i]->m_durationOverride=-5.0f-i;if(i<c.seed%5)self->m_affixData.add(as[i]);}
 for(unsigned i=0;i<3;++i){ds[i]=reinterpret_cast<D*>(data[i]);new(&ds[i]->m_effects)TArrayList<CEffect*>(2);for(unsigned j=0;j<(c.seed+i*2)%6;++j)ds[i]->m_effects.add(es[(j+i)%6]);
  // The original duration loop indexes the inner list with outer i, not j.
  // Keep logical sizes unchanged and give every allocated spare slot a live
  // effect, including seed11's list1 slot1 (count1, capacity2).
  for(unsigned j=ds[i]->m_effects.m_nCount;j<ds[i]->m_effects.m_nCapacity;++j)ds[i]->m_effects.m_pData[j]=es[(j+i)%6];
  if((c.seed&16)&&ds[i]->m_effects.m_nCount)ds[i]->m_effects.m_nCapacity=(c.seed/8)%2;if(i<c.seed%4)self->m_effectData.add(c.mode==3&&(c.seed&8)&&i==1?NULL:ds[i]);}
 if(c.seed&32){if(self->m_affixData.m_nCount)self->m_affixData.m_nCapacity=(c.seed/8)%2;if(self->m_effectData.m_nCount)self->m_effectData.m_nCapacity=(c.seed/8)%2;}
 mask=(c.seed*13)%64;unitAddress=unit;std::wstring suffix=names[(c.seed/4)%4];
 if(c.mode==0){for(unsigned i=0;i<self->m_effectData.size();++i){D*d=self->m_effectData[i];for(unsigned j=0;j<d->m_effects.size();++j){CEffect*e=d->m_effects[i];for(unsigned k=0;k<6;++k)if(es[k]==e&&!e->m_bFlag28)durations[k]=duration;}}
  void(*fn)(void*,float)=ours?newDuration:oldDuration;if(!autotest::beginInvocation(out,fn))return;fn(self,duration);out.callCompleted=1;
  for(unsigned i=0;i<self->m_affixData.size();++i)if(self->m_affixData[i]->m_durationOverride!=duration)out.issue=autotest::Capture::InvalidReport;
  for(unsigned i=0;i<6;++i){out.add(&es[i]->m_fValue24,4);if(es[i]->m_fValue24!=durations[i])out.issue=autotest::Capture::InvalidReport;}
 }else if(c.mode==1){bool expectedValue=false;void*target=(c.seed&1)?unit:NULL;if(target)for(unsigned i=0;i<self->m_affixData.size();++i){A*a=self->m_affixData[i];if((mask&(1u<<a->m_unitType))&&a->m_targetType==0){expectedValue=true;break;}}
  detour::Set patches;TL_REDIRECT(patches,unitISA,&isa);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  bool(*fn)(void*,void*)=ours?newEnemy:oldEnemy;if(!autotest::beginInvocation(out,fn))return;bool value=fn(self,target);out.callCompleted=1;out.add(&value,1);if(value!=expectedValue)out.issue=autotest::Capture::InvalidReport;
 }else if(c.mode==2){std::wstring wanted;bool found=false;for(unsigned i=0;i<self->m_effectData.size()&&!found;++i){D*d=self->m_effectData[i];for(unsigned j=0;j<d->m_effects.size();++j)if(d->m_effects[j]->m_eType==0x71){wanted=d->m_effects[j]->m_sName;found=true;break;}}
  std::wstring(*fn)(void*)=ours?newPortal:oldPortal;if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(self);out.callCompleted=1;text(out,value);if(value!=wanted)out.issue=autotest::Capture::InvalidReport;
 }else{for(unsigned i=0;i<self->m_effectData.size();++i){D*d=self->m_effectData[i];if(!d)continue;for(unsigned j=0;j<d->m_effects.size();++j)for(unsigned k=0;k<6;++k)if(es[k]==d->m_effects[j])expected[k]+=suffix;}
  void(*fn)(void*,const std::wstring&)=ours?newAppend:oldAppend;if(!autotest::beginInvocation(out,fn))return;fn(self,suffix);out.callCompleted=1;for(unsigned i=0;i<6;++i){text(out,es[i]->m_sName);if(es[i]->m_sName!=expected[i])out.issue=autotest::Capture::InvalidReport;}
 }
 for(unsigned i=0;i<6;++i)es[i]->m_sName.~basic_string();for(unsigned i=0;i<3;++i)ds[i]->m_effects.~TArrayList();self->m_affixData.~TArrayList();self->m_effectData.~TArrayList();
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t addr){autotest::Coverage coverage(name,addr);for(unsigned n=0;n<120;++n){Case c={mode,n};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    skill state mode %u seed %u issue %u/%u exits %d/%d\n",mode,n,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(state_skill_duration){return run(host,0,"state_skill_duration",(uintptr_t)&oldDuration);}
TL_TEST(state_skill_enemy){return run(host,1,"state_skill_enemy",(uintptr_t)&oldEnemy);}
TL_TEST(state_skill_portal){return run(host,2,"state_skill_portal",(uintptr_t)&oldPortal);}
TL_TEST(state_skill_append){return run(host,3,"state_skill_append",(uintptr_t)&oldAppend);}
