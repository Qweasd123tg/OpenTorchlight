#include <cstring>
#include <map>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "EffectGroupManager.h"
#include "MissilePreloader.h"
TL_ORIGINAL(void*,oldAffixLookup,(void*,const std::wstring&),"_ZN19CEffectGroupManager8getAffixERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void*newAffixLookup(void*,const std::wstring&) __asm__("_ZN19CEffectGroupManager8getAffixERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void*,oldMissileLookup,(void*,const std::wstring&),"_ZN17CMissilePreloader13getMissileRefERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void*newMissileLookup(void*,const std::wstring&) __asm__("_ZN17CMissilePreloader13getMissileRefERKSbIwSt11char_traitsIwESaIwEE");
namespace {
struct Case{unsigned mode,seed;};
int id(void*p,uint64_t*values){if(!p)return -1;for(unsigned i=0;i<5;++i)if(p==values+i)return i;return -2;}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);uint64_t values[5],affixSpace[(sizeof(CEffectGroupManager)+7)/8],missileSpace[2][(sizeof(CMissilePreloader)+7)/8];std::memset(affixSpace,0xa5,sizeof(affixSpace));std::memset(missileSpace,0x5a,sizeof(missileSpace));
 CEffectGroupManager*affixes=reinterpret_cast<CEffectGroupManager*>(affixSpace);typedef std::map<std::wstring,CAffix*>Affixes;Affixes*affixMap=new(&affixes->m_mapAffixes)Affixes;
 CMissilePreloader*missiles[2]={reinterpret_cast<CMissilePreloader*>(missileSpace[0]),reinterpret_cast<CMissilePreloader*>(missileSpace[1])};typedef std::map<std::wstring,CMissile*>Missiles;Missiles*maps[2]={new(&missiles[0]->m_missilesToLoad)Missiles,new(&missiles[1]->m_missilesToLoad)Missiles};
 const wchar_t*keys[]={L"",L"A",L"AA",L"B",L"Ж"};const wchar_t*queries[]={L"",L"a",L"aa",L"ab",L"b",L"Ж",L"missing"};
 for(unsigned i=0;i<c.seed%6;++i){(*affixMap)[keys[i]]=c.seed&32?NULL:reinterpret_cast<CAffix*>(values+i);(*maps[0])[keys[i]]=c.seed&32?NULL:reinterpret_cast<CMissile*>(values+i);}
 (*maps[1])[L"MISSING"]=reinterpret_cast<CMissile*>(values+4);
 std::wstring query=queries[(c.seed/6)%7],upper=query;for(unsigned i=0;i<upper.size();++i)if(upper[i]>=L'a'&&upper[i]<=L'z')upper[i]-=L'a'-L'A';
 // Original local singleton address is supplied by the d0a2b0 packet. Tests run in forked children.
 void**slot=reinterpret_cast<void**>(0x14f9fc0);void*saved=*slot;*slot=c.seed%4==0?NULL:missiles[0];
 void*expected=NULL;void*result;
 if(c.mode==0){Affixes::const_iterator i=affixMap->find(upper);if(i!=affixMap->end())expected=i->second;void*(*fn)(void*,const std::wstring&)=ours?newAffixLookup:oldAffixLookup;if(!autotest::beginInvocation(out,fn))return;result=fn(affixes,query);out.callCompleted=1;}
 else{if(*slot){Missiles::const_iterator i=maps[0]->find(upper);if(i!=maps[0]->end())expected=i->second;}void*(*fn)(void*,const std::wstring&)=ours?newMissileLookup:oldMissileLookup;if(!autotest::beginInvocation(out,fn))return;result=fn(missiles[1],query);out.callCompleted=1;}
 int resultID=id(result,values);out.add(&resultID,4);if(result!=expected)out.issue=autotest::Capture::InvalidReport;
 *slot=saved;maps[0]->~Missiles();maps[1]->~Missiles();affixMap->~Affixes();
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned n=0;n<126;++n){Case c={mode,n};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    resource lookup mode %u seed %u issue %u/%u exits %d/%d\n",mode,n,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(resource_affix_lookup){return run(host,0,"resource_affix_lookup",(uintptr_t)&oldAffixLookup);}
TL_TEST(resource_missile_lookup){return run(host,1,"resource_missile_lookup",(uintptr_t)&oldMissileLookup);}
