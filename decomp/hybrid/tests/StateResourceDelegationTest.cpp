#include <cstring>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "ResourceManager.h"
#include "Hierarchy.h"
#include "DataGroup.h"
#include "SpawnClass.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(int,oIsa,nIsa,(CResourceManager*,const std::wstring&,const std::wstring&),"_ZN16CResourceManager3ISAERKSbIwSt11char_traitsIwESaIwEES5_")
DECL(ERESOURCE_GROUPS,oGroup,nGroup,(CResourceManager*,CDataGroup*),"_ZN16CResourceManager29getResourceGroupFromDataGroupEP10CDataGroup")
DECL(void,oSpawn,nSpawn,(CResourceManager*,CSpawnClass*,TArrayList<CBaseUnit*>&,unsigned,CCharacter*,CCharacter*,int,int),"_ZN16CResourceManager23createUnitsBySpawnClassEP11CSpawnClassR10TArrayListIP9CBaseUnitEjP10CCharacterS8_ii")
#undef DECL
TL_FUNCTION(typeId,"_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(hierarchyIsa,"_ZN10CHierarchy3ISAEjj")
TL_FUNCTION(dataUInt,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEj")
TL_FUNCTION(dataString,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(createGuid,"_ZN16CResourceManager10createUnitExibb")
TL_FUNCTION(rollSpawn,"_ZN11CSpawnClass14rollSpawnClassER10TArrayListIP10CDataGroupEPS0_IbEP10CCharacterS8_ijiiii")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;void*objects[10];CResourceManager*manager;unsigned seed,rolls;std::wstring texts[5];
int id(void*p){if(!p)return -1;if(p==manager)return 20;for(unsigned i=0;i<10;++i)if(objects[i]==p)return i;return -2;}
void event(unsigned k,void*p){int i=id(p);cap->add(&k,4);cap->add(&i,4);}
unsigned type(void*p,const std::wstring&s){event(1,p);cap->addText(s);return s.empty()?unsigned(-1):unsigned(s[0])%31;}
// Original CHierarchy::ISA returns full EAX=0/1 on both exits (0xa531c7/0xa531d0).
unsigned isa(void*p,unsigned a,unsigned b){event(2,p);cap->add(&a,4);cap->add(&b,4);return a==b||((a+b+seed)%3==0);}
unsigned uintValue(void*p,const std::wstring&s,unsigned fallback){event(3,p);cap->addText(s);cap->add(&fallback,4);return seed%4==0?unsigned(-1):seed%4==1?unsigned(-2):seed*0x1234567;}
const std::wstring&strValue(void*p,const std::wstring&s,const std::wstring&fallback){event(4,p);cap->addText(s);cap->addText(fallback);return texts[id(p)];}
void*create(void*p,long long guid,int level,bool a,bool b){event(5,p);cap->add(&guid,8);cap->add(&level,4);cap->add(&a,1);cap->add(&b,1);return (guid+seed)%3==0?NULL:objects[5+guid%5];}
int roll(void*p,TArrayList<CDataGroup*>&groups,TArrayList<bool>*choices,void*first,void*second,int level,unsigned count,int a,int b,int c,int flags){event(6,p);event(7,first);event(8,second);cap->add(&level,4);cap->add(&count,4);cap->add(&a,4);cap->add(&b,4);cap->add(&c,4);cap->add(&flags,4);cap->add(&groups.m_nCount,4);cap->add(&choices->m_nCount,4);choices->clear();unsigned n=(seed+rolls++)%5;for(unsigned i=0;i<n;++i){groups.add(static_cast<CDataGroup*>(objects[i]));choices->add((seed+i)%2);}if((seed&8)&&n){groups.m_nCapacity=seed%2;choices->m_nCapacity=(seed/2)%2;}return n;}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;rolls=0;uint64_t ms[(sizeof(CResourceManager)+7)/8],os[10][16];std::memset(ms,0,sizeof(ms));manager=reinterpret_cast<CResourceManager*>(ms);for(unsigned i=0;i<10;++i)objects[i]=os[i];manager->m_pHierarchy=seed&1?reinterpret_cast<CHierarchy*>(objects[9]):NULL;for(unsigned i=0;i<5;++i){wchar_t buf[24];std::swprintf(buf,24,L"%u",100+i);texts[i]=buf;}
 detour::Set patches;TL_REDIRECT(patches,typeId,&type);TL_REDIRECT(patches,hierarchyIsa,&isa);TL_REDIRECT(patches,dataUInt,&uintValue);TL_REDIRECT(patches,dataString,&strValue);TL_REDIRECT(patches,createGuid,&create);TL_REDIRECT(patches,rollSpawn,&roll);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 const wchar_t*names[]={L"",L"A",L"AA",L"Ж"};if(c.mode==0){int(*fn)(CResourceManager*,const std::wstring&,const std::wstring&)=ours?nIsa:oIsa;if(!autotest::beginInvocation(out,fn))return;int r=fn(manager,names[(seed/2)%4],names[(seed/5)%4]);out.callCompleted=1;out.add(&r,4);}
 else if(c.mode==1){ERESOURCE_GROUPS(*fn)(CResourceManager*,CDataGroup*)=ours?nGroup:oGroup;if(!autotest::beginInvocation(out,fn))return;ERESOURCE_GROUPS r=fn(manager,seed%5==0?NULL:static_cast<CDataGroup*>(objects[0]));out.callCompleted=1;out.add(&r,4);}
 else{TArrayList<CBaseUnit*>units(1+seed%3);for(unsigned i=0;i<seed%3;++i)units.add(static_cast<CBaseUnit*>(objects[5+i]));void(*fn)(CResourceManager*,CSpawnClass*,TArrayList<CBaseUnit*>&,unsigned,CCharacter*,CCharacter*,int,int)=ours?nSpawn:oSpawn;if(!autotest::beginInvocation(out,fn))return;fn(manager,seed%7==0?NULL:static_cast<CSpawnClass*>(objects[9]),units,seed%4,reinterpret_cast<CCharacter*>(objects[7]),seed&1?reinterpret_cast<CCharacter*>(objects[8]):NULL,int(seed)-30,int(seed%5)-2);out.callCompleted=1;unsigned n=units.size();out.add(&n,4);for(unsigned i=0;i<n;++i){int v=id(units[i]);out.add(&v,4);}}
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned m,const char*n,uintptr_t address){autotest::Coverage coverage(n,address);for(unsigned i=0;i<120;++i){Case c={m,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    resource mode %u seed %u issue %u/%u exits %d/%d\n",m,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(state_resource_isa_names,0,oIsa)
TEST(state_resource_group,1,oGroup)
TEST(state_resource_spawn_class,2,oSpawn)
