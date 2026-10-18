#include <cstring>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "BaseUnit.h"
#include "Character.h"
#include "EffectManager.h"
#include "Effect.h"
#include "Affix.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,emOldClear,emNewClear,(CEffectManager*,bool),"_ZN14CEffectManager12clearEffectsEb")
DECL(void,emOldValues,emNewValues,(CEffectManager*),"_ZN14CEffectManager21calculateEffectValuesEv")
DECL(void,emOldTransfer,emNewTransfer,(CEffectManager*,CCharacter*,EEFFECT_ACTIVATION,EEFFECT_TYPE),"_ZN14CEffectManager15transferEffectsEP10CCharacter18EEFFECT_ACTIVATION12EEFFECT_TYPE")
DECL(CEffect*,emOldAdd,emNewAdd,(CEffectManager*,CEffect*),"_ZN14CEffectManager12addNewEffectEP7CEffect")
DECL(void,emOldDead,emNewDead,(CEffectManager*),"_ZN14CEffectManager17deleteDeadEffectsEv")
DECL(void,emOldDtor,emNewDtor,(CEffectManager*),"_ZN14CEffectManagerD1Ev")
DECL(void,emOldCtor,emNewCtor,(CEffectManager*,CBaseUnit*),"_ZN14CEffectManagerC1EP9CBaseUnit")
#undef DECL
TL_FUNCTION(emParse,"_ZN6CAffix15parseAffixGroupEv")
TL_FUNCTION(emSetOwner,"_ZN7CEffect8setOwnerEP9CBaseUnitb")
namespace {
struct Case{unsigned op,seed;};autotest::Capture* cap;unsigned seed;CCharacter* receiver;CBaseUnit* owner;CEffect* effects[12];CUnitTheme* themes[3];
void number(unsigned n){cap->add(&n,4);}int id(CEffect* e){for(int i=0;i<12;++i)if(effects[i]==e)return i;return -1;}int themeId(CUnitTheme*t){for(int i=0;i<3;++i)if(themes[i]==t)return i;return -1;}
void noParse(CAffix*){}
void effectState(CEffect*e){cap->add(&e->m_eType,4);cap->add(&e->m_activation,4);cap->add(&e->m_fValue24,4);cap->add(&e->m_fRemainingDuration,4);cap->add(&e->m_fValueC0,4);cap->add(&e->m_flag31,1);cap->add(&e->m_flag33,1);cap->add(&e->m_bDead,1);cap->addText(e->m_sName);cap->addText(e->m_name88);int t=themeId(e->m_pUnitTheme);cap->add(&t,4);bool owned=e->m_Owner.getObject()==owner;cap->add(&owned,1);}
void setOwner(CEffect*e,CBaseUnit*u,bool recalc){number(51);int n=id(e);cap->add(&n,4);cap->add(&recalc,1);if(u&&u!=owner){std::fprintf(stderr,"    owner mismatch seed %u null %d\n",seed,u==NULL);cap->issue=autotest::Capture::InvalidReport;}e->m_Owner.setObject(u);}
bool valid(CCharacter*self,CCharacter*source,CBaseUnit*target,CEffect*e){number(53);int n=id(e);cap->add(&n,4);if(self!=receiver||source!=receiver||target!=owner)cap->issue=autotest::Capture::InvalidReport;return (seed+n)%3!=0;}
bool apply(CCharacter*self,CCharacter*source,CBaseUnit*target,CEffect*e){number(59);if(self!=receiver||source!=receiver||target!=owner)cap->issue=autotest::Capture::InvalidReport;effectState(e);return (seed%2)!=0;}
void state(CEffectManager*m){for(unsigned g=0;g<3;++g){number(m->m_Effects[g].size());number(m->m_Effects[g].m_nGrowBy);for(unsigned i=0;i<m->m_Effects[g].size();++i){int n=id(m->m_Effects[g][i]);cap->add(&n,4);}}number(m->m_Affixes.size());number(m->m_Affixes.m_nGrowBy);number(m->m_UnitThemes.size());number(m->m_UnitThemes.m_nGrowBy);for(unsigned i=0;i<m->m_UnitThemes.size();++i){int n=themeId(m->m_UnitThemes[i]);cap->add(&n,4);}cap->add(m->m_EffectValues,sizeof(m->m_EffectValues));cap->addText(m->m_EffectString2E0);cap->addText(m->m_EffectString2E8);cap->addText(m->m_EffectString2F0);bool own=m->m_Owner.getObject()==owner;cap->add(&own,1);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;std::memset(effects,0,sizeof(effects));CRunicCore ownerLife,themeLife[3];owner=seed%4?reinterpret_cast<CBaseUnit*>(&ownerLife):NULL;for(unsigned i=0;i<3;++i)themes[i]=reinterpret_cast<CUnitTheme*>(&themeLife[i]);void*vt[0x248/8];std::memset(vt,0,sizeof(vt));vt[0x238/8]=reinterpret_cast<void*>(&valid);vt[0x240/8]=reinterpret_cast<void*>(&apply);void**recv=vt;receiver=reinterpret_cast<CCharacter*>(&recv);
 detour::Set patches;TL_REDIRECT(patches,emParse,&noParse);TL_REDIRECT(patches,emSetOwner,&setOwner);if(patches.failed())_exit(43);
 uint64_t memory[(sizeof(CEffectManager)+7)/8];std::memset(memory,0xa5,sizeof(memory));CEffectManager*m=reinterpret_cast<CEffectManager*>(memory);
 if(c.op==5)autotest::invoke(out,ours?&emNewCtor:&emOldCtor,m,owner);else emOldCtor(m,owner);
 TSafePointer<CEffectManager> selfWeak;selfWeak.setObject(m);TSafePointer<CEffect> weak[12];TSafePointer<CAffix> affixWeak[4];
 if(c.op!=5){m->m_EffectString2E0=L"first";m->m_EffectString2E8=seed%2?L"second Ж":L"";m->m_EffectString2F0=L"third";for(unsigned i=0;i<145;++i)m->m_EffectValues[i]=float(i)-7;
  static const int types[]={0,6,7,123,124,62,144,145};static const float durations[]={-900,-1000,0,1,2.5f};
  for(unsigned i=0;i<seed%10;++i){CEffect*e=new CEffect(static_cast<EEFFECT_TYPE>(types[(i+seed)%8]),false,static_cast<EEFFECT_ACTIVATION>((i+seed/3)%3),1,2,3,false);effects[i]=e;weak[i].setObject(e);e->m_fValue24=durations[(i+seed/2)%5];e->m_fRemainingDuration=(int((i+seed)%5)-2)*1.0f;e->m_fValueC0=(int(i)-3)*1.25f;e->m_bDead=(i+seed)%7==0;e->m_flag31=(i+seed)%2;e->m_sName=(i+seed)%3?L"repeat":L"other";e->m_name88=(i+seed)%4?L"":L"repeat";e->m_pUnitTheme=(i+seed)%4?themes[(i+seed)%3]:NULL;m->m_Effects[e->m_activation].add(e);}
  for(unsigned i=0;i<seed%4;++i){CAffix*a=new CAffix(L"fixture");affixWeak[i].setObject(a);m->m_Affixes.add(a);}
  if(c.op==3&&seed%2&&effects[0]&&m->m_Affixes.size())effects[0]->m_pAffixOwner=m->m_Affixes[0];
  m->m_UnitThemes.add(themes[2]);
 }
 if(c.op==0)autotest::invoke(out,ours?&emNewClear:&emOldClear,m,seed%2!=0);
 if(c.op==1)autotest::invoke(out,ours?&emNewValues:&emOldValues,m);
 if(c.op==2)autotest::invoke(out,ours?&emNewTransfer:&emOldTransfer,m,receiver,static_cast<EEFFECT_ACTIVATION>(seed%3),static_cast<EEFFECT_TYPE>(seed%2?7:62));

 if(c.op==3)autotest::invoke(out,ours?&emNewDead:&emOldDead,m);
 if(c.op!=4)state(m);
 if(c.op==4)autotest::invoke(out,ours?&emNewDtor:&emOldDtor,m);else emOldDtor(m);
 bool invalid=selfWeak.getObject()==NULL;out.add(&invalid,1);if(!invalid){std::fprintf(stderr,"    self live seed %u\n",seed);out.issue=autotest::Capture::InvalidReport;}
 for(unsigned i=0;i<12;++i){CEffect*e=weak[i].getObject();bool live=e!=NULL;out.add(&live,1);if(e){effectState(e);e->m_pAffixOwner=NULL;delete e;}}
 for(unsigned i=0;i<4;++i){bool live=affixWeak[i].getObject()!=NULL;out.add(&live,1);if(live){std::fprintf(stderr,"    affix live seed %u idx %u\n",seed,i);out.issue=autotest::Capture::InvalidReport;}}
 if(out.issue)std::fprintf(stderr,"    raw issue %u bytes %lu op%u seed%u ours%d\n",out.issue,(unsigned long)out.length,c.op,seed,ours);
 unsigned owners=ownerLife.m_pSafePointers?ownerLife.m_pSafePointers->size():0;number(owners);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void recovered(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(continuation_effect_manager_lifetime){int failures=0;const uintptr_t functions[]={(uintptr_t)&emOldClear,(uintptr_t)&emOldValues,(uintptr_t)&emOldTransfer,(uintptr_t)&emOldDead,(uintptr_t)&emOldDtor,(uintptr_t)&emOldCtor};for(unsigned op=0;op<6;++op){autotest::Coverage coverage("continuation_effect_manager_lifetime",functions[op]);for(unsigned i=0;i<40;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;TL_CHECK(failures,ok);if(!ok){host->log("    manager op %u seed %u status %d/%d issue %u/%u bytes %lu/%lu\n",op,i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k<a.capture.length&&k<b.capture.length;++k)if(a.capture.data[k]!=b.capture.data[k])host->log("    manager diff byte%u %02x/%02x\n",k,a.capture.data[k],b.capture.data[k]);coverage.report(host);return failures;}}coverage.report(host);}return failures;}
