#include <cstring>
#include <new>
#include <limits>
#define private public
#define protected public
#include "Equipment.h"
#include "EffectManager.h"
#include "Effect.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(long long,originalEffects,(CEquipment*),"_ZN10CEquipment10hasEffectsEv")
TL_ORIGINAL(bool,originalMagic,(CEquipment*),"_ZN10CEquipment9isMagicalEv")
TL_ORIGINAL(void,originalStack,(CEquipment*,int),"_ZN10CEquipment16incrementStackByEi")
extern "C" long long candidateEffects(CEquipment*) __asm__("_ZN10CEquipment10hasEffectsEv");
extern "C" bool candidateMagic(CEquipment*) __asm__("_ZN10CEquipment9isMagicalEv");
extern "C" void candidateStack(CEquipment*,int) __asm__("_ZN10CEquipment16incrementStackByEi");
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
namespace {
struct Case{unsigned mode,mask,profile,mutation;};const Case* cs;autotest::Capture* cap;CEquipment* item;CEffectManager* managers[2];
void n(int x){cap->add(&x,4);}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){
 n(p==item);n(int(type));
 if(cs->mutation==1)item->m_pEffectManager=managers[1];
 if(cs->mutation==2&&!item->m_ElementalDamageBonuses.empty())item->m_ElementalDamageBonuses[0]=int(type)-55;
 return type==static_cast<UNITTYPES::EUNITTYPES>(55)?bool(cs->mask&8):bool(cs->mask&16);
}
void ptr(unsigned char* p,unsigned off,uintptr_t x){std::memcpy(p+off,&x,8);}
void side(void* data,autotest::Capture& out,bool ours){
 Case c=*(Case*)data;cs=&c;cap=&out;
 unsigned long long em[(sizeof(CEquipment)+23)/8],mm[2][(sizeof(CEffectManager)+7)/8],fx[2][5][(sizeof(CEffect)+7)/8];
 std::memset(em,0xa5,sizeof(em));std::memset(mm,0,sizeof(mm));std::memset(fx,0,sizeof(fx));item=(CEquipment*)em;
 CEffect* refs[2][5];
 for(unsigned m=0;m<2;++m){
  managers[m]=(CEffectManager*)mm[m];
  managers[m]->getAffixes().m_nCount=(c.mask&2)?(m?0:1):0;
  TArrayList<CEffect*>& effects=*reinterpret_cast<TArrayList<CEffect*>*>(managers[m]->m_EffectData10+0x18);
  effects.m_pData=refs[m];effects.m_nCount=c.profile==6?0xffffffffu:c.profile;effects.m_nCapacity=c.mask&4?2:5;
  for(unsigned i=0;i<5;++i){refs[m][i]=(CEffect*)fx[m][i];refs[m][i]->m_eType=static_cast<EEFFECT_TYPE>((c.mask&32)&&i==(m?0:3)?61:62);}
 }
 item->m_pEffectManager=c.mask&1?managers[0]:0;
 new(&item->m_ElementalDamageTypes)std::vector<EDAMAGE_TYPES>;
 new(&item->m_ElementalDamageBonuses)std::vector<int>;
 for(unsigned i=0;i<c.profile%4;++i){item->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>(i));item->m_ElementalDamageBonuses.push_back((c.mask&64)&&i==1?-17:0);}
 void* expectedVectors[2][3];std::memcpy(expectedVectors[0],&item->m_ElementalDamageTypes,24);std::memcpy(expectedVectors[1],&item->m_ElementalDamageBonuses,24);
 detour::Set d;TL_REDIRECT(d,isaFn,&isa);if(d.failed())_exit(60);
 if(c.mode==0){if(ours)autotest::invoke(out,&candidateEffects,item);else autotest::invoke(out,&originalEffects,item);}
 else {if(ours)autotest::invoke(out,&candidateMagic,item);else autotest::invoke(out,&originalMagic,item);}
 unsigned char snapshot[sizeof(em)];std::memcpy(snapshot,em,sizeof(em));
 ptr(snapshot,0x1b8,!item->m_pEffectManager?0:item->m_pEffectManager==managers[0]?1:item->m_pEffectManager==managers[1]?2:99);
 // Normalize only the exact three saved storage pointers for each vector.
 for(unsigned vector=0;vector<2;++vector)for(unsigned j=0;j<3;++j){unsigned off=0x350+vector*0x18+j*8;void* value;std::memcpy(&value,snapshot+off,8);uintptr_t code=(uintptr_t)value;if(!value)code=0;else for(unsigned k=0;k<3;++k)if(value==expectedVectors[vector][k]){code=k+1;break;}ptr(snapshot,off,code);}
 out.add(snapshot,sizeof(snapshot));for(unsigned m=0;m<2;++m){unsigned char managerSnapshot[sizeof(CEffectManager)];std::memcpy(managerSnapshot,managers[m],sizeof(managerSnapshot));void* value;std::memcpy(&value,managerSnapshot+0x28,8);if(value==refs[m])ptr(managerSnapshot,0x28,m+1);out.add(managerSnapshot,sizeof(managerSnapshot));}out.add(fx,sizeof(fx));for(unsigned i=0;i<item->m_ElementalDamageTypes.size();++i)n(item->m_ElementalDamageTypes[i]);for(unsigned i=0;i<item->m_ElementalDamageBonuses.size();++i)n(item->m_ElementalDamageBonuses[i]);
 item->m_ElementalDamageTypes.~vector();item->m_ElementalDamageBonuses.~vector();
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode){
 autotest::Coverage coverage(mode?"equipment_small_magic":"equipment_small_effects",(uint64_t)(uintptr_t)(mode?(void*)&originalMagic:(void*)&originalEffects));
 for(unsigned mask=0;mask<128;++mask)for(unsigned profile=0;profile<7;++profile)for(unsigned mutation=0;mutation<3;++mutation){
  Case c={mode,mask,profile,mutation};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);
  if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    equipment effects mismatch %u/%u/%u/%u exits %d/%d\n",mode,mask,profile,mutation,u.childStatus,v.childStatus);coverage.report(host);return 1;}
 }coverage.report(host);return 0;
}
struct StackCase{int initial,amount;unsigned pattern;};
void stack(void* data,autotest::Capture& out,bool ours){StackCase c=*(StackCase*)data;unsigned long long mm[(sizeof(CEquipment)+23)/8];std::memset(mm,c.pattern?0xa5:0x5a,sizeof(mm));CEquipment* p=(CEquipment*)mm;p->m_iUnknown238=c.initial;if(ours)autotest::invoke(out,&candidateStack,p,c.amount);else autotest::invoke(out,&originalStack,p,c.amount);out.add(mm,sizeof(mm));}
void sa(void* p,autotest::Capture& o){stack(p,o,false);}void sb(void* p,autotest::Capture& o){stack(p,o,true);}
}
TL_TEST(equipment_small_effects){return run(host,0);}
TL_TEST(equipment_small_magic){return run(host,1);}
TL_TEST(equipment_small_stack){autotest::Coverage coverage("equipment_small_stack",(uint64_t)(uintptr_t)&originalStack);const int values[]={0,1,-1,2,-2,100,-100,2147483647,(-2147483647-1),2147483646,-2147483647};for(unsigned i=0;i<11;++i)for(unsigned j=0;j<11;++j)for(unsigned pattern=0;pattern<2;++pattern){StackCase c={values[i],values[j],pattern};autotest::Outcome u,v;autotest::runChild(sa,&c,u);autotest::runChild(sb,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){coverage.report(host);return 1;}}coverage.report(host);return 0;}
