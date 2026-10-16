#include <cstring>
#include <stdint.h>
#include <map>
#include <vector>
#include <string>
#include "AutoTest.h"
#define private public
#define protected public
#include "Descriptor.h"
#include "DescriptorController.h"
#include "DescriptorRegistry.h"
#undef private
#undef protected
extern CDescriptorController originalController __asm__("_ZL22g_DescriptorController");
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(CDescriptor*,oName,nName,(const std::wstring&),"_ZN21CDescriptorController22getNewDescriptorByNameERKSbIwSt11char_traitsIwESaIwEE")
DECL(CDescriptor*,oIndex,nIndex,(unsigned),"_ZN21CDescriptorController30getNewDescriptorByCreatedIndexEj")
DECL(CDescriptorProp*,oProp,nProp,(CDescriptor*,const std::wstring&,bool),"_ZN21CDescriptorController27getDescriptorPropertyByNameEP11CDescriptorRKSbIwSt11char_traitsIwESaIwEEb")
#undef DECL
namespace {
struct Case{unsigned mode,seed;};CDescriptor*made;autotest::Capture*cap;unsigned calls;
void*factory(){++calls;return made;}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);cap=&out;calls=0;const wchar_t*names[]={L"",L"A",L"AA",L"AB",L"Ж",L"missing"};uint64_t ds[(sizeof(CDescriptor)+7)/8],ps[5][(sizeof(CDescriptorProp)+7)/8];std::memset(ds,0,sizeof(ds));CDescriptor*d=reinterpret_cast<CDescriptor*>(ds);made=d;d->m_iID=0x89abcdef;new(&d->m_sName)std::wstring(names[(c.seed/3)%6]);TArrayList<CDescriptorProp*>list(2),defaults(2);
 for(unsigned i=0;i<5;++i){CDescriptorProp*p=reinterpret_cast<CDescriptorProp*>(ps[i]);new(&p->m_sName)std::wstring(names[(i+c.seed/7)%5]);if(i<c.seed%6)list.add(p);if(i<(c.seed/2)%6)defaults.add(p);}
 if((c.seed&16)&&list.size())list.m_nCapacity=(c.seed/8)%2;if((c.seed&32)&&defaults.size())defaults.m_nCapacity=(c.seed/8)%2;
 g_Descriptors.clear();g_DescriptorNameOrder.clear();originalController.m_Properties.clear();originalController.m_DefaultProperties.clear();for(unsigned i=0;i<c.seed%6;++i){g_Descriptors[names[i]]=&factory;g_DescriptorNameOrder.push_back(names[(i+c.seed/9)%5]);}
 if(c.seed&2)originalController.m_Properties[names[(c.seed/5)%5]]=c.seed&4?&list:NULL;if(c.seed&8)originalController.m_DefaultProperties[names[(c.seed/11)%5]]=c.seed&4?&defaults:NULL;
 const std::wstring name=names[(c.seed/6)%6];int result=-1;
 if(c.mode==0){CDescriptor*(*fn)(const std::wstring&)=ours?nName:oName;if(!autotest::beginInvocation(out,fn))return;CDescriptor*r=fn(name);out.callCompleted=1;result=r==d?1:r?2:0;}
 else if(c.mode==1){CDescriptor*(*fn)(unsigned)=ours?nIndex:oIndex;if(!autotest::beginInvocation(out,fn))return;CDescriptor*r=fn((c.seed/6)%8);out.callCompleted=1;result=r==d?1:r?2:0;}
 else{CDescriptorProp*(*fn)(CDescriptor*,const std::wstring&,bool)=ours?nProp:oProp;if(!autotest::beginInvocation(out,fn))return;CDescriptorProp*r=fn(c.seed%7==0?NULL:d,name,c.seed&1);out.callCompleted=1;result=r?9:-1;for(unsigned i=0;i<5;++i)if(r==reinterpret_cast<CDescriptorProp*>(ps[i]))result=i;}
 out.add(&result,4);out.add(&calls,4);out.add(&d->m_iID,4);d->m_sName.~basic_string();for(unsigned i=0;i<5;++i)reinterpret_cast<CDescriptorProp*>(ps[i])->m_sName.~basic_string();originalController.m_Properties.clear();originalController.m_DefaultProperties.clear();
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned m,const char*n,uintptr_t address){autotest::Coverage coverage(n,address);for(unsigned i=0;i<120;++i){Case c={m,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    descriptor lookup mode %u seed %u issue %u/%u exits %d/%d\n",m,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(state_descriptor_factory_name,0,oName)
TEST(state_descriptor_factory_index,1,oIndex)
TEST(state_descriptor_property,2,oProp)
