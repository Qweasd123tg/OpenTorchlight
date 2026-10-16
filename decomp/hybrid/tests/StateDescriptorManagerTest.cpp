#include <cstring>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "DescriptorManager.h"
#include "DescriptorController.h"
#undef private
#undef protected
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(CDescriptor*,oGet,nGet,(CDescriptorManager*,unsigned,bool),"_ZN18CDescriptorManager22GetDescriptorByCreatedEjb")
DECL(void,oActivate,nActivate,(CDescriptorManager*,CEditorScene*),"_ZN18CDescriptorManager19activateDescriptorsEP12CEditorScene")
DECL(void,oSerialize,nSerialize,(CDescriptorManager*,CDataGroup*),"_ZN18CDescriptorManager20SerializeDescriptorsEP10CDataGroup")
#undef DECL
TL_FUNCTION(descriptorFactory,"_ZN21CDescriptorController30getNewDescriptorByCreatedIndexEj")
TL_FUNCTION(descriptorAdd,"_ZN18CDescriptorManager13AddDescriptorEP11CDescriptor")
TL_FUNCTION(objectHash,"_ZN17CEditorBaseObject32calculateParentHierarchyHashCodeEv")
TL_FUNCTION(descriptorSerialize,"_ZN11CDescriptor19SerializeDescriptorEP10CDataGroupj")
TL_FUNCTION(dataAdd,"_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;CDescriptorManager*manager;void*objects[12];unsigned seed;
int id(void*p){if(!p)return -1;if(p==manager)return 20;for(unsigned i=0;i<12;++i)if(p==objects[i])return i;return -2;}
void event(unsigned k,void*p){int v=id(p);cap->add(&k,4);cap->add(&v,4);}
CDescriptor*factory(unsigned index){unsigned kind=1;cap->add(&kind,4);cap->add(&index,4);return seed&8?static_cast<CDescriptor*>(objects[5]):NULL;}
unsigned add(CDescriptorManager*p,CDescriptor*d){event(2,p);event(3,d);unsigned index=p->getDescriptorVector().size();p->getDescriptorVector().push_back(d);return index;}
void hash(void*p){event(4,p);}void active(void*p,void*scene){event(5,p);event(6,scene);}
void serialize(void*p,void*group,unsigned index){event(7,p);event(8,group);cap->add(&index,4);}
CDataGroup*data(void*p,const std::wstring&name){event(9,p);cap->addText(name);return static_cast<CDataGroup*>(objects[11]);}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;uint64_t ms[(sizeof(CDescriptorManager)+7)/8],ds[6][(sizeof(CDescriptor)+7)/8],os[6][16];std::memset(ds,0,sizeof(ds));manager=reinterpret_cast<CDescriptorManager*>(ms);new(&manager->getDescriptorVector())std::vector<CDescriptor*>();void*vt[16]={0};vt[15]=reinterpret_cast<void*>(&active);for(unsigned i=0;i<6;++i){objects[i]=ds[i];objects[6+i]=os[i];}for(unsigned i=0;i<6;++i){CDescriptor*d=static_cast<CDescriptor*>(objects[i]);*reinterpret_cast<void***>(d)=vt;d->m_iID=(seed/4+i)%7;d->m_iFlags=(seed+i)%3?0x4000:0;new(&d->m_Objects)TArrayList<CEditorBaseObject*>(2);for(unsigned j=0;j<(seed+i)%4;++j)d->m_Objects.add(static_cast<CEditorBaseObject*>(objects[6+j]));if((seed&16)&&d->m_Objects.size())d->m_Objects.m_nCapacity=seed%2;}
 for(unsigned i=0;i<seed%6;++i)manager->getDescriptorVector().push_back(static_cast<CDescriptor*>(objects[i]));detour::Set patches;TL_REDIRECT(patches,descriptorFactory,&factory);TL_REDIRECT(patches,descriptorAdd,&add);TL_REDIRECT(patches,objectHash,&hash);TL_REDIRECT(patches,descriptorSerialize,&serialize);TL_REDIRECT(patches,dataAdd,&data);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.mode==0){CDescriptor*(*fn)(CDescriptorManager*,unsigned,bool)=ours?nGet:oGet;if(!autotest::beginInvocation(out,fn))return;CDescriptor*r=fn(manager,(seed/3)%9,seed&1);out.callCompleted=1;int v=id(r);out.add(&v,4);}else if(c.mode==1){void(*fn)(CDescriptorManager*,CEditorScene*)=ours?nActivate:oActivate;if(!autotest::beginInvocation(out,fn))return;fn(manager,seed%7==0?NULL:static_cast<CEditorScene*>(objects[10]));out.callCompleted=1;}else{void(*fn)(CDescriptorManager*,CDataGroup*)=ours?nSerialize:oSerialize;if(!autotest::beginInvocation(out,fn))return;fn(manager,seed%7==0?NULL:static_cast<CDataGroup*>(objects[10]));out.callCompleted=1;}unsigned n=manager->getDescriptorVector().size();out.add(&n,4);for(unsigned i=0;i<n;++i){int v=id(manager->getDescriptorVector()[i]);out.add(&v,4);}manager->getDescriptorVector().~vector();for(unsigned i=0;i<6;++i)static_cast<CDescriptor*>(objects[i])->m_Objects.~TArrayList();
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned m,const char*n,uintptr_t address){autotest::Coverage coverage(n,address);for(unsigned i=0;i<120;++i){Case c={m,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    descriptor manager mode %u seed %u issue %u/%u exits %d/%d\n",m,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(state_descriptor_manager_created,0,oGet)
TEST(state_descriptor_manager_activate,1,oActivate)
TEST(state_descriptor_manager_serialize,2,oSerialize)
