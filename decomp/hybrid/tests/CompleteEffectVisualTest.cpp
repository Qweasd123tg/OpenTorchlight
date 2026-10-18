#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "EffectManager.h"
#include "Effect.h"
#include "EffectDisplayValues.h"
#include "Affix.h"
#include "StringTranslate.h"
#undef protected
#undef private
TL_ORIGINAL(const std::wstring&,evOld,(CEffectManager*,EEFFECT_ACTIVATION,unsigned,bool,bool),"_ZN14CEffectManager20getVisualDescriptionE18EEFFECT_ACTIVATIONjbb")
extern "C" const std::wstring& evNew(CEffectManager*,EEFFECT_ACTIVATION,unsigned,bool,bool) __asm__("_ZN14CEffectManager20getVisualDescriptionE18EEFFECT_ACTIVATIONjbb");
TL_FUNCTION(evValues,"_ZN7CEffect25getVisualCalculatedValuesEjb")
TL_FUNCTION(evStats,"_ZN7CEffect15getDisplayStatsER20CEffectDisplayValues")
TL_FUNCTION(evCan,"_ZN6CAffix22canBeAppliedToUnitTypeEj")
TL_FUNCTION(evSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(evTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
namespace {
using namespace smallmass;
unsigned seed,callIndex;CEffect*effects[24];CAffix*affix;CEffectManager*manager;CStringTranslate*translator;
int effectId(CEffect*p){if(!p)return -1;for(unsigned i=0;i<24;++i)if(effects[i]==p)return i;return -2;}
float value(unsigned n,unsigned field){unsigned bits=(seed/19+n+field)%13;if(bits==0){unsigned nan=0x7fc00000;float f;std::memcpy(&f,&nan,4);return f;}return (int((seed+n*7+field*11)%31)-15)*0.25f;}
CEffectDisplayValues visual(CEffect*p,unsigned level,bool scaled){number(1);number(effectId(p));number(level);number(scaled);unsigned n=effectId(p);CEffectDisplayValues v;v.m_duration=value(n,0);v.m_minimum=value(n,1);v.m_maximum=value(n,2);v.m_secondaryMinimum=value(n,3);v.m_secondaryMaximum=value(n,4);v.m_value24=value(n,5);v.m_scaled=(seed/7+n)%2;v.m_effectType=seed&512?int(n+100):seed&16?0x52:int((seed/3+n)%3);v.m_effect=!(seed&512) && seed%17==0 && n>0 && n%6==0?NULL:p;return v;}
std::wstring stats(CEffect*p,CEffectDisplayValues&v){number(2);number(effectId(p));floating(v.m_duration);floating(v.m_minimum);floating(v.m_maximum);floating(v.m_secondaryMinimum);floating(v.m_secondaryMaximum);floating(v.m_value24);number(v.m_scaled);number(v.m_effectType);number(effectId(v.m_effect));return (seed+effectId(p))%5==0?L"":(effectId(p)%2?L"value ж":L"value");}
bool can(CAffix*p,unsigned type){number(3);number(p==affix);number(type);++callIndex;bool result=type==8?seed&64:seed&128;if(seed&256 && callIndex%3==1)for(unsigned i=0;i<24;++i)effects[i]->m_pAffixOwner=NULL;return result;}
CStringTranslate*singleton(){number(4);return translator;}
std::wstring translate(CStringTranslate*p,const wchar_t*key){number(5);number(p==translator);text(std::wstring(key));return std::wstring(L"tr:")+key;}
void visualSide(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;callIndex=0;
 new(reinterpret_cast<void*>(0x14781e8))std::wstring();new(reinterpret_cast<void*>(0x14dd9c8))std::wstring();new(reinterpret_cast<void*>(0x14dd9d8))std::wstring();new(reinterpret_cast<void*>(0x14dda88))std::wstring();new(reinterpret_cast<void*>(0x152f138))std::wstring();
 int before=g_iTotalCountOfObjects;
 manager=static_cast<CEffectManager*>(object(sizeof(CEffectManager)));affix=static_cast<CAffix*>(object(sizeof(CAffix)));translator=static_cast<CStringTranslate*>(object(sizeof(CStringTranslate)));
 std::wstring*caches=&manager->m_EffectString2E0;for(unsigned i=0;i<3;++i){new(&manager->m_Effects[i])TArrayList<CEffect*>(4);new(&caches[i])std::wstring(seed%11==0?L"already cached":L"");}
 unsigned group=seed%3;unsigned count=seed/3%25;
 // Keep at least one nonnull representative per merged bucket. Null sources are followed by an equivalent nonnull source only.
 for(unsigned i=0;i<24;++i){effects[i]=static_cast<CEffect*>(object(sizeof(CEffect)));new(&effects[i]->m_sName)std::wstring((seed/13+i)%3==0?L"alpha":L"beta");effects[i]->m_eDamageType=static_cast<EDAMAGE_TYPES>((seed/5+i)%3);effects[i]->m_pAffixOwner=seed&32?affix:NULL;if(i<count)manager->m_Effects[group].add(effects[i]);}
 typedef const std::wstring&(*Fn)(CEffectManager*,EEFFECT_ACTIVATION,unsigned,bool,bool);Fn fn=ours?evNew:evOld;if(!autotest::beginInvocation(out,fn))return;const std::wstring&result=fn(manager,static_cast<EEFFECT_ACTIVATION>(group),seed%37,seed&1,seed&2);out.callCompleted=1;number(&result==&caches[group]);text(result);for(unsigned i=0;i<3;++i){text(caches[i]);caches[i].~basic_string();manager->m_Effects[i].~TArrayList<CEffect*>();}for(unsigned i=0;i<24;++i)effects[i]->m_sName.~basic_string();number(g_iTotalCountOfObjects-before);
}
}
TL_TEST(complete_effect_visual){detour::Set h;TL_REDIRECT(h,evValues,&visual);TL_REDIRECT(h,evStats,&stats);TL_REDIRECT(h,evCan,&can);TL_REDIRECT(h,evSingleton,&singleton);TL_REDIRECT(h,evTranslate,&translate);if(h.failed())return 1;return smallmass::run(host,0,"complete_effect_visual",0x7f4810,&visualSide,2048);}
