#include <cstring>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "UnitResourceList.h"
#include "MasterResourceManager.h"
TL_ORIGINAL(unsigned,oTypes,(CUnitResourceList*,unsigned,TArrayList<CDataGroup*>&),"_ZN17CUnitResourceList23getDataGroupsByUnitTypeEjR10TArrayListIP10CDataGroupE")
extern "C" unsigned nTypes(CUnitResourceList*,unsigned,TArrayList<CDataGroup*>&) __asm__("_ZN17CUnitResourceList23getDataGroupsByUnitTypeEjR10TArrayListIP10CDataGroupE");
TL_FUNCTION(masterSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(typeId,"_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(hierarchyIsa,"_ZN10CHierarchy3ISAEjj")
TL_FUNCTION(dataString,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
namespace {
autotest::Capture*cap;CMasterResourceManager*master;CDataGroup*groups[6];std::wstring names[6];unsigned seed;
int id(CDataGroup*p){if(!p)return -1;for(unsigned i=0;i<6;++i)if(groups[i]==p)return i;return -2;}
CMasterResourceManager*singleton(){return master;}unsigned type(void*,const std::wstring&s){cap->addText(s);return s.empty()?unsigned(-1):unsigned(s[0]);}bool isa(void*,unsigned a,unsigned b){cap->add(&a,4);cap->add(&b,4);return a==b||(a+seed)%3==0;}
const std::wstring&data(void*p,const std::wstring&key,const std::wstring&fallback){int i=id(static_cast<CDataGroup*>(p));cap->add(&i,4);cap->addText(key);cap->addText(fallback);return names[i];}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);cap=&out;uint64_t rs[(sizeof(CUnitResourceList)+7)/8],ms[(sizeof(CMasterResourceManager)+7)/8],ds[6][16];CUnitResourceList*self=reinterpret_cast<CUnitResourceList*>(rs);master=reinterpret_cast<CMasterResourceManager*>(ms);master->m_pHierarchy=seed&1?reinterpret_cast<CHierarchy*>(ds[0]):NULL;typedef std::map<std::wstring,std::map<std::wstring,CDataGroup*> >Map;new(&self->m_dataGroupsByResourceGroupAndName)Map();const wchar_t*texts[]={L"",L"A",L"AB",L"B",L"Ж",L"a"};for(unsigned i=0;i<6;++i){groups[i]=reinterpret_cast<CDataGroup*>(ds[i]);names[i]=texts[(seed/3+i)%6];if(i<seed%7)self->m_dataGroupsByResourceGroupAndName[texts[i%3]][texts[(i+seed/9)%6]]=groups[i];}if(seed&8)self->m_dataGroupsByResourceGroupAndName[L"empty"];
 TArrayList<CDataGroup*>output(1+seed%3);for(unsigned i=0;i<seed%3;++i)output.add(groups[i]);detour::Set patches;TL_REDIRECT(patches,masterSingleton,&singleton);TL_REDIRECT(patches,typeId,&type);TL_REDIRECT(patches,hierarchyIsa,&isa);TL_REDIRECT(patches,dataString,&data);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}unsigned(*fn)(CUnitResourceList*,unsigned,TArrayList<CDataGroup*>&)=ours?nTypes:oTypes;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(self,unsigned(texts[(seed/7)%6][0]),output);out.callCompleted=1;out.add(&result,4);unsigned n=output.size();out.add(&n,4);for(unsigned i=0;i<n;++i){int v=id(output[i]);out.add(&v,4);}if((master->m_pHierarchy&&result!=n)||(!master->m_pHierarchy&&result!=0))out.issue=autotest::Capture::InvalidReport;self->m_dataGroupsByResourceGroupAndName.~Map();}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(state_unit_resource_type){autotest::Coverage coverage("state_unit_resource_type",(uintptr_t)&oTypes);for(unsigned seed=0;seed<120;++seed){autotest::Outcome x,y;autotest::runChild(a,&seed,x);autotest::runChild(b,&seed,y);if(coverage.observe(host,x,y)){host->log("    unit resources seed %u issue %u/%u exits %d/%d\n",seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
