#include <string>
#include <cstring>
#include <limits>
#define private public
#include "EffectManager.h"
#include "Effect.h"
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,oldHasType,(CEffectManager*,EEFFECT_TYPE),"_ZN14CEffectManager9hasEffectE12EEFFECT_TYPE")
TL_ORIGINAL(bool,oldHasName,(CEffectManager*,const std::wstring&),"_ZN14CEffectManager9hasEffectERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(float,oldValue,(CEffectManager*,EEFFECT_TYPE,EDAMAGE_TYPES),"_ZN14CEffectManager14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_ORIGINAL(float,oldActive,(CEffectManager*,EEFFECT_ACTIVATION,EEFFECT_TYPE,EDAMAGE_TYPES),"_ZN14CEffectManager14getEffectValueE18EEFFECT_ACTIVATION12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_ORIGINAL(float,oldNamed,(CEffectManager*,EEFFECT_TYPE,const std::wstring&),"_ZN14CEffectManager14getEffectValueE12EEFFECT_TYPERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(bool,oldRemove,(CEffectManager*,const std::wstring&,bool),"_ZN14CEffectManager12removeEffectERKSbIwSt11char_traitsIwESaIwEEb")
extern "C" bool newHasType(CEffectManager*,EEFFECT_TYPE) __asm__("_ZN14CEffectManager9hasEffectE12EEFFECT_TYPE");
extern "C" bool newHasName(CEffectManager*,const std::wstring&) __asm__("_ZN14CEffectManager9hasEffectERKSbIwSt11char_traitsIwESaIwEE");
extern "C" float newValue(CEffectManager*,EEFFECT_TYPE,EDAMAGE_TYPES) __asm__("_ZN14CEffectManager14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES");
extern "C" float newActive(CEffectManager*,EEFFECT_ACTIVATION,EEFFECT_TYPE,EDAMAGE_TYPES) __asm__("_ZN14CEffectManager14getEffectValueE18EEFFECT_ACTIVATION12EEFFECT_TYPE13EDAMAGE_TYPES");
extern "C" float newNamed(CEffectManager*,EEFFECT_TYPE,const std::wstring&) __asm__("_ZN14CEffectManager14getEffectValueE12EEFFECT_TYPERKSbIwSt11char_traitsIwESaIwEE");
extern "C" bool newRemove(CEffectManager*,const std::wstring&,bool) __asm__("_ZN14CEffectManager12removeEffectERKSbIwSt11char_traitsIwESaIwEEb");
TL_FUNCTION(clearDescriptions,"_ZN14CEffectManager20clearOutDescriptionsEv")
namespace {
struct Case { unsigned mode,seed; };autotest::Capture* cap;CEffectManager* manager;CEffect* fx[3][4];unsigned dead[3][4];
void n(unsigned x){cap->add(&x,4);}void clear(CEffectManager* p){n(20);n(p==manager);}
void destroy(CEffect* p){n(10);for(unsigned l=0;l<3;++l)for(unsigned i=0;i<4;++i)if(p==fx[l][i]){n(l);n(i);++dead[l][i];return;}_exit(61);}
void side(void* data,autotest::Capture& out,bool ours){
 Case c=*(Case*)data;cap=&out;unsigned long long memory[(sizeof(CEffectManager)+7)/8],objects[3][4][(sizeof(CEffect)+7)/8];std::memset(memory,0,sizeof(memory));std::memset(objects,0,sizeof(objects));std::memset(dead,0,sizeof(dead));manager=(CEffectManager*)memory;
 void* vtable[2]={(void*)&destroy,(void*)&destroy};CEffect* refs[3][4];const unsigned types[]={0,5,6,7,123,124};unsigned wanted=types[c.seed%6];EDAMAGE_TYPES damage=static_cast<EDAMAGE_TYPES>((c.seed/6)%4==3?7:(c.seed/6)%4);
 const float cache[]={0.f,1.f,-1.f,std::numeric_limits<float>::quiet_NaN()};reinterpret_cast<float*>((char*)manager+0x80)[wanted]=cache[(c.seed/24)%4];
 const float adjustments[]={-900.f,-1000.f,0.f,1.f,std::numeric_limits<float>::quiet_NaN()};const float values[]={0.f,1.f,-3.f,100.f};std::wstring name=(c.seed/96)%3==0?L"":(c.seed/96)%3==1?L"match":std::wstring(L"a\0b",3);
 for(unsigned l=0;l<3;++l){TArrayList<CEffect*>& list=*reinterpret_cast<TArrayList<CEffect*>*>((char*)manager+0x28+l*24);list.m_pData=refs[l];list.m_nCount=(c.seed/288+l)%5;list.m_nCapacity=c.mode==5?4:(c.seed/1440+l)%5;list.m_nGrowBy=7;
  for(unsigned i=0;i<4;++i){fx[l][i]=refs[l][i]=(CEffect*)objects[l][i];std::memcpy(objects[l][i],&vtable,sizeof(void*));void** vt=vtable;std::memcpy(objects[l][i],&vt,sizeof(vt));fx[l][i]->m_eType=static_cast<EEFFECT_TYPE>((i+l+c.seed/8)%3?int(wanted):int(types[(c.seed+1)%6]));fx[l][i]->m_eDamageType=static_cast<EDAMAGE_TYPES>((i+l+c.seed/11)%4);fx[l][i]->m_fValue24=adjustments[(i+l+c.seed/13)%5];fx[l][i]->m_fValueC0=values[(i+l+c.seed/17)%4];new(&fx[l][i]->m_sName)std::wstring((i+l+c.seed/19)%3?name:L"different");}
 }
 detour::Set d;TL_REDIRECT(d,clearDescriptions,&clear);if(d.failed())_exit(60);
 EEFFECT_TYPE type=static_cast<EEFFECT_TYPE>(wanted);EEFFECT_ACTIVATION activation=static_cast<EEFFECT_ACTIVATION>((c.seed/5)%3);
 if(c.mode==0)autotest::invoke(out,ours?&newHasType:&oldHasType,manager,type);
 if(c.mode==1){typedef bool(*Fn)(CEffectManager*,const std::wstring&);autotest::invoke<Fn,CEffectManager*,const std::wstring&>(out,ours?&newHasName:&oldHasName,manager,name);}
 if(c.mode==2)autotest::invoke(out,ours?&newValue:&oldValue,manager,type,damage);
 if(c.mode==3)autotest::invoke(out,ours?&newActive:&oldActive,manager,activation,type,damage);
 if(c.mode==4){typedef float(*Fn)(CEffectManager*,EEFFECT_TYPE,const std::wstring&);autotest::invoke<Fn,CEffectManager*,EEFFECT_TYPE,const std::wstring&>(out,ours?&newNamed:&oldNamed,manager,type,name);}
 if(c.mode==5){typedef bool(*Fn)(CEffectManager*,const std::wstring&,bool);autotest::invoke<Fn,CEffectManager*,const std::wstring&,bool>(out,ours?&newRemove:&oldRemove,manager,name,bool(c.seed&1));}
 for(unsigned l=0;l<3;++l){TArrayList<CEffect*>& list=*reinterpret_cast<TArrayList<CEffect*>*>((char*)manager+0x28+l*24);n(list.m_nCount);n(list.m_nCapacity);n(list.m_nGrowBy);n(list.m_pData==refs[l]);for(unsigned i=0;i<4;++i){unsigned id=99;for(unsigned j=0;j<4;++j)if(refs[l][i]==fx[l][j])id=j;n(id);n(dead[l][i]);out.addText(fx[l][i]->m_sName);fx[l][i]->m_sName.~basic_string();}}
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode){void* addresses[]={(void*)&oldHasType,(void*)&oldHasName,(void*)&oldValue,(void*)&oldActive,(void*)&oldNamed,(void*)&oldRemove};const char* names[]={"pass10_effect_has_type","pass10_effect_has_name","pass10_effect_value","pass10_effect_active","pass10_effect_named","pass10_effect_remove"};autotest::Coverage cov(names[mode],(uint64_t)(uintptr_t)addresses[mode]);for(unsigned seed=0;seed<2880;++seed){Case c={mode,seed};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(cov.observe(host,x,y)||autotest::incomplete(x)||autotest::incomplete(y)||x.childStatus||y.childStatus){host->log("    legacy effect %u seed %u exits %d/%d\n",mode,seed,x.childStatus,y.childStatus);cov.report(host);return 1;}}cov.report(host);return 0;}
}
TL_TEST(pass10_effect_has_type){return run(host,0);}TL_TEST(pass10_effect_has_name){return run(host,1);}TL_TEST(pass10_effect_value){return run(host,2);}TL_TEST(pass10_effect_active){return run(host,3);}TL_TEST(pass10_effect_named){return run(host,4);}TL_TEST(pass10_effect_remove){return run(host,5);}
