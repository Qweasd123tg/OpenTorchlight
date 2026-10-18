#include <cstring>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "BaseUnit.h"
#include "Skill.h"
#include "Affix.h"
#include "Effect.h"
#include "EffectManager.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,afOldBonuses,afNewBonuses,(CAffix*,float(&)[6],bool),"_ZN6CAffix18fillOutStatBonusesERA6_fb")
DECL(void,afOldPercent,afNewPercent,(CAffix*,char),"_ZN6CAffix10setPercentEc")
DECL(void,afOldClone,afNewClone,(CAffix*,const CAffix*),"_ZN6CAffix5cloneEPKS_")
DECL(void,afOldNamed,afNewNamed,(CAffix*,const std::wstring&),"_ZN6CAffixC1ERKSbIwSt11char_traitsIwESaIwEE")
DECL(void,afOldCopy,afNewCopy,(CAffix*,CAffix*,unsigned),"_ZN6CAffixC1EPS_j")
DECL(void,afOldDtor,afNewDtor,(CAffix*),"_ZN6CAffixD1Ev")
#undef DECL
TL_FUNCTION(afParse,"_ZN6CAffix15parseAffixGroupEv")
TL_FUNCTION(afCalculate,"_ZN7CEffect18calculateBaseValueENS_15ECALCULATETYPESE")
namespace {
struct Case{unsigned op,seed,fault;};struct Stop{};autotest::Capture* capture;unsigned seed;bool shouldThrow;TSafePointer<CAffix>* weakSink;
void number(unsigned n){capture->add(&n,4);}void text(const std::wstring& s){capture->addText(s);}
void effectState(CEffect* e){capture->add(&e->m_iLevel,4);capture->add(&e->m_fValueC0,12);unsigned n=e->m_statModifiers.size();number(n);for(unsigned i=0;i<n;++i)capture->add(&e->m_statModifiers[i],4);n=e->m_statModifierValues.size();number(n);for(unsigned i=0;i<n;++i)capture->add(&e->m_statModifierValues[i],4);}
void state(CAffix* a){text(a->m_sAffixFileName);text(a->m_sDisplayName);text(a->m_sPrefix);text(a->m_sSuffix);capture->add(&a->m_iMinSpawnRange,4);capture->add(&a->m_iMaxSpawnRange,4);capture->add(&a->m_cLevelPercent,1);capture->add(&a->m_iRank,4);capture->add(&a->m_iSlotsOccupy,4);capture->add(&a->m_uiLevel,4);capture->add(&a->m_bTemporary,1);capture->add(&a->m_bDataFileInitialized,1);capture->add(&a->m_fDuration,4);capture->add(&a->m_bHasDuration,1);capture->add(&a->m_iWeight,4);number(a->m_ApplicableUnitTypes.m_nGrowBy);number(a->m_ApplicableUnitTypes.size());for(unsigned i=0;i<a->m_ApplicableUnitTypes.size();++i)number(a->m_ApplicableUnitTypes[i]);number(a->m_Effects.m_nGrowBy);number(a->m_Effects.size());for(unsigned i=0;i<a->m_Effects.size();++i)effectState(a->m_Effects[i]);}
void parse(CAffix* a){
 number(41);text(a->m_sAffixFileName);capture->add(&a->m_uiLevel,4);capture->add(&a->m_fDuration,4);number(a->m_Effects.m_nGrowBy);number(a->m_ApplicableUnitTypes.m_nGrowBy);number(a->m_bDataFileInitialized);
 a->m_sDisplayName=seed%2?L"display Ж":L"";a->m_sPrefix=L"prefix";a->m_sSuffix=seed%3?L"suffix":L"";
 a->m_iMinSpawnRange=2;a->m_iMaxSpawnRange=32;a->m_fDuration=seed%2?-1.0f:2.5f;a->m_bHasDuration=seed%2;a->m_iRank=3;a->m_iWeight=7;a->m_iSlotsOccupy=seed%3+1;
 for(unsigned i=0;i<seed%4;++i){CEffect* e=new CEffect(static_cast<EEFFECT_TYPE>(i),false,EFFECT_ACTIVATION_PASSIVE,1,2,3,false);e->m_fValueC4=static_cast<float>(i)-3.5f;e->m_fValueC8=i%2?0.0f:static_cast<float>(i)+7;for(unsigned stat=0;stat<(seed+i)%7;++stat){e->m_statModifiers.add(static_cast<EEFFECT_STAT_MODIFIERS>((stat+i)%6));e->m_statModifierValues.add(float(stat*3)-4.5f);}a->m_Effects.add(e);}
 for(unsigned i=0;i<seed%5;++i)a->m_ApplicableUnitTypes.add(i*7+seed);
 if(weakSink)weakSink->setObject(a);
 if(shouldThrow)throw Stop();
}
float calculate(CEffect* e,CEffect::ECALCULATETYPES kind){number(43);capture->add(&kind,4);capture->add(&e->m_iLevel,4);capture->add(&e->m_fValueC4,8);e->m_fValueC0=e->m_fValueC4+e->m_fValueC8+static_cast<float>(e->m_iLevel);return e->m_fValueC0;}
void side(void* raw,autotest::Capture& out,bool ours){
 Case c=*static_cast<Case*>(raw);capture=&out;seed=c.seed;shouldThrow=false;weakSink=NULL;detour::Set patches;TL_REDIRECT(patches,afParse,&parse);if(patches.failed())_exit(42);
 uint64_t sourceMemory[(sizeof(CAffix)+7)/8],targetMemory[(sizeof(CAffix)+7)/8];std::memset(sourceMemory,0xa3,sizeof(sourceMemory));std::memset(targetMemory,0xb7,sizeof(targetMemory));CAffix* source=reinterpret_cast<CAffix*>(sourceMemory);CAffix* target=reinterpret_cast<CAffix*>(targetMemory);
 std::wstring name=c.seed%2?L"affix-Ж":L"";afOldNamed(source,name);source->m_uiLevel=7;
 if(c.op!=3&&c.op!=4)afOldNamed(target,L"existing");
 TL_REDIRECT(patches,afCalculate,&calculate);if(patches.failed())_exit(42);
 float bonuses[6]={-9,0,1,5,-2,17};
 TSafePointer<CAffix> weak;
 if(c.op==0){for(unsigned i=0;i<target->m_Effects.size();++i)if(c.seed%6==0)target->m_Effects[i]->m_statModifierValues.m_nCapacity=0;
  autotest::invoke<void(*)(CAffix*,float(&)[6],bool),CAffix*,float(&)[6],bool>(out,ours?&afNewBonuses:&afOldBonuses,target,bonuses,(c.seed&1)!=0);
 }
 if(c.op==1){target->m_pOriginalAffix=c.seed%5?source:NULL;source->m_Effects.setGrowBy(1);static const char values[]={-128,-1,0,1,50,99,100,101,127};static const unsigned levels[]={0,1,1000,1001,0xffffffffu};target->m_uiLevel=levels[c.seed%5];for(unsigned i=0;i<source->m_Effects.size();++i)if((c.seed+i)%6==0)source->m_Effects[i]->m_graphs[(c.seed/2)%4]=reinterpret_cast<CGraph*>(source);
  autotest::invoke(out,ours?&afNewPercent:&afOldPercent,target,values[c.seed%9]);
 }
 if(c.op==2){if(c.seed%5==0)source->m_bDataFileInitialized=false;target->m_uiLevel=c.seed%33;const CAffix* arg=c.seed%7==0?NULL:source;autotest::invoke(out,ours?&afNewClone:&afOldClone,target,arg);}
 bool constructed=true,caught=false;
 if(c.op==3){weakSink=&weak;shouldThrow=c.fault!=0;typedef void(*Fn)(CAffix*,const std::wstring&);Fn fn=ours?&afNewNamed:&afOldNamed;if(!autotest::beginInvocation(out,fn))return;try{fn(target,name);out.callCompleted=1;}catch(const Stop&){caught=true;constructed=false;}weakSink=NULL;shouldThrow=false;}
 if(c.op==4)autotest::invoke(out,ours?&afNewCopy:&afOldCopy,target,source,c.seed%9==0?0xffffffffu:c.seed%33);
 if(c.op!=5&&constructed){state(target);state(source);out.add(bonuses,sizeof(bonuses));}
 if(constructed){weak.setObject(target);bool registered=weak.getObject()==target;out.add(&registered,1);if(!registered)out.issue=autotest::Capture::InvalidReport;if(c.op==5)autotest::invoke(out,ours?&afNewDtor:&afOldDtor,target);else afOldDtor(target);}
 bool invalidated=weak.getObject()==NULL;out.add(&invalidated,1);out.add(&weak.m_nIndex,4);out.add(&caught,1);if(!invalidated)out.issue=autotest::Capture::InvalidReport;
 for(unsigned i=0;i<source->m_Effects.size();++i)for(unsigned j=0;j<4;++j)source->m_Effects[i]->m_graphs[j]=NULL;
 afOldDtor(source);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void recovered(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(continuation_affix_values_and_lifetime){
 int failures=0;const uintptr_t functions[]={reinterpret_cast<uintptr_t>(&afOldBonuses),reinterpret_cast<uintptr_t>(&afOldPercent),reinterpret_cast<uintptr_t>(&afOldClone),reinterpret_cast<uintptr_t>(&afOldNamed),reinterpret_cast<uintptr_t>(&afOldCopy),reinterpret_cast<uintptr_t>(&afOldDtor)};
 for(unsigned op=0;op<6;++op){autotest::Coverage coverage("continuation_affix_values_and_lifetime",functions[op]);for(unsigned i=0;i<32;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;TL_CHECK(failures,ok);if(!ok){host->log("    affix op %u seed %u status %d/%d bytes %lu/%lu\n",op,i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k<a.capture.length&&k<b.capture.length;++k)if(a.capture.data[k]!=b.capture.data[k])host->log("    affix diff byte%u %02x/%02x\n",k,a.capture.data[k],b.capture.data[k]);coverage.report(host);return failures;}}coverage.report(host);}
 for(unsigned i=0;i<4;++i){Case c={3,i,1};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==reinterpret_cast<uintptr_t>(&afOldNamed)&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,ok);}
 return failures;
}
