#include <cstring>
#include <map>
#include <string>
#include "tests/SmallMassCompare.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "EffectDefines.h"
TL_ORIGINAL(void,epOld,(),"_Z12parseEffectsv")
extern "C" void epNew() __asm__("_Z12parseEffectsv");
TL_ORIGINAL(void,epNativeCtor,(CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_FUNCTION(epCtor,"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_FUNCTION(epLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
extern "C" char epLogSingleton[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char epLogMessage[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
using namespace smallmass;
unsigned seed,count;detour::Set*ctorHooks;int logger;
void ctor(CDataGroup*p,const std::wstring&name,CDataGroup*parent,unsigned values,unsigned groups,TRepository<std::wstring>*repo){
 number(1);text(name);number(parent!=NULL);number(values);number(groups);number(repo!=NULL);ctorHooks->restore();epNativeCtor(p,name,parent,values,groups,repo?repo:new TRepository<std::wstring>(L""));TL_REDIRECT(*ctorHooks,epCtor,&ctor);if(ctorHooks->failed())std::abort();
}
void load(CDataGroup*p,const std::wstring&name,CTimerStatics*timers){
 number(2);text(name);number(timers!=NULL);const wchar_t*keys[]={L"NAME",L"GOODDES",L"GOODDESOT",L"BADDES",L"BADDESOT",L"VALUE1",L"VALUE2",L"VALUE3",L"VALUE4",L"VALUE5",L"GRAPH1",L"GRAPH2",L"GRAPH3",L"GRAPH4",L"GRAPH5"};
 for(unsigned i=0;i<count;++i){CDataGroup*g=p->AddDataGroup(L"EFFECT");for(unsigned k=0;k<15;++k)if((seed+i+k)%4){std::wstring value=keys[k];value+=static_cast<wchar_t>(L'А'+i%20);g->SetDataValue(keys[k],value,false);}const wchar_t*types[]={L"percent",L"None",L"VALUE",L"weird"};if((seed+i)%5)g->SetDataValue(L"TYPE",types[(seed+i)%4],false);if(i%3)g->SetDataValue(L"MINVAL",int(i)-73);if(i%5)g->SetDataValue(L"MAXVAL",int(i)*3-19);}
}
void*singleton(){number(3);return &logger;}
void epLog(void*p,const std::string&message,int priority,bool debug){number(4);number(p==&logger);text(message);number(priority);number(debug);}
void epSide(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;const unsigned counts[]={0,1,4,144,145};count=counts[seed%5];const unsigned cells[]={0x14dd9c8,0x14dd9d8,0x14dda88,0x152f138,0x1508990};for(unsigned i=0;i<5;++i)new(reinterpret_cast<void*>(cells[i]))std::wstring();
 for(unsigned i=0;i<145;++i){new(&gEFFECT_TYPE_NAMES[i])std::wstring(L"prior name");new(&gEFFECT_TYPE_DESCRIPTIONS_GOOD[i])std::wstring(L"prior good");new(&gEFFECT_TYPE_DESCRIPTIONS_GOOD_OT[i])std::wstring(L"prior good OT");new(&gEFFECT_TYPE_DESCRIPTIONS_BAD[i])std::wstring(L"prior bad");new(&gEFFECT_TYPE_DESCRIPTIONS_BAD_OT[i])std::wstring(L"prior bad OT");for(unsigned k=0;k<5;++k){new(&gEFFECT_TYPE_PROPERTY_TAGS[i][k])std::wstring(L"prior value");new(&gEFFECT_TYPE_GRAPHS[i][k])std::wstring(L"prior graph");}gEFFECT_TYPE_BONUS[i]=-9;gEFFECT_TYPE_MIN_VALUES[i]=-77;gEFFECT_TYPE_MAX_VALUES[i]=88;}
 typedef void(*Fn)();Fn fn=ours?epNew:epOld;if(!autotest::beginInvocation(out,fn))return;fn();out.callCompleted=1;
 for(unsigned i=0;i<145;++i){text(gEFFECT_TYPE_NAMES[i]);text(gEFFECT_TYPE_DESCRIPTIONS_GOOD[i]);text(gEFFECT_TYPE_DESCRIPTIONS_GOOD_OT[i]);text(gEFFECT_TYPE_DESCRIPTIONS_BAD[i]);text(gEFFECT_TYPE_DESCRIPTIONS_BAD_OT[i]);for(unsigned k=0;k<5;++k){text(gEFFECT_TYPE_PROPERTY_TAGS[i][k]);text(gEFFECT_TYPE_GRAPHS[i][k]);}number(gEFFECT_TYPE_BONUS[i]);number(gEFFECT_TYPE_MIN_VALUES[i]);number(gEFFECT_TYPE_MAX_VALUES[i]);}
}
}
TL_TEST(complete_effects_header_parse){detour::Set ctorSet;ctorHooks=&ctorSet;TL_REDIRECT(ctorSet,epCtor,&ctor);detour::Set h;TL_REDIRECT(h,epLoad,&load);h.redirect(epLogSingleton,epLogSingleton,&singleton);h.redirect(epLogMessage,epLogMessage,&epLog);if(ctorSet.failed()||h.failed())return 1;return smallmass::run(host,0,"complete_effects_header_parse",0xd608f0,&epSide,15);}
