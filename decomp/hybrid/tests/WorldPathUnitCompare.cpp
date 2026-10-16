#include <string>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include "Interact.h"
#include "PathController.h"
TL_ORIGINAL(void, updateOriginal,(void*,float),"_ZN9CInteract6updateEf")
extern "C" void updateCandidate(void*,float) __asm__("_ZN9CInteract6updateEf");
TL_ORIGINAL(void, unitOriginal,(void*,unsigned,const std::wstring&),"_ZN9CInteract26setUnitInteractWithByIndexEjSbIwSt11char_traitsIwESaIwEE")
extern "C" void unitCandidate(void*,unsigned,const std::wstring&) __asm__("_ZN9CInteract26setUnitInteractWithByIndexEjSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, pathUnitOriginal,(void*,std::wstring),"_ZN15CPathController19setUnitInteractWithESbIwSt11char_traitsIwESaIwEE")
extern "C" void pathUnitCandidate(void*,std::wstring) __asm__("_ZN15CPathController19setUnitInteractWithESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(graphTarget,"_ZNK6CGraph8getValueEfj")
TL_FUNCTION(resourceListTarget,"_ZN17CUnitResourceList12getSingletonEv")
TL_FUNCTION(dataGroupTarget,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case{unsigned op,index;};Case* input;autotest::Capture* output;void* self;unsigned calls;char resourceList,dataGroup;
template<class T>T& field(void* p,unsigned offset){return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);}void invalid(){output->issue=autotest::Capture::InvalidReport;}void number(unsigned n){output->add(&n,sizeof(n));}void text(const std::wstring& s){number(s.size());output->add(s.data(),s.size()*4);}
float graph(void* p,float percent,unsigned index){if(p!=static_cast<char*>(self)+0xc8||index)invalid();number(1);output->add(&percent,4);number(index);++calls;return input->index%5*0.375f;}
void* singleton(){number(2);return &resourceList;}
void* group(void* p,const std::wstring& name){if(p!=&resourceList)invalid();number(3);text(name);++calls;return input->index%3?&dataGroup:0;}
void bind(void* weak,CRunicCore* referent){field<void*>(weak,0)=referent;field<unsigned>(weak,8)=referent->addSafePointer(reinterpret_cast<TSafePointer<void*>*>(weak));}
float bits(unsigned value){float f;std::memcpy(&f,&value,4);return f;}
void body(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=autotest::allocate(2048);void* resources=autotest::allocate(256);void* client=autotest::allocate(0x3910);TArrayList<void*>* clients=new(static_cast<char*>(resources)+0x28)TArrayList<void*>;clients->add(client);field<void*>(self,c.op==2?0x68:0x68)=c.index%13==0&&c.op!=0?0:resources;detour::Set patches;TL_REDIRECT(patches,graphTarget,&graph);TL_REDIRECT(patches,resourceListTarget,&singleton);TL_REDIRECT(patches,dataGroupTarget,&group);if(patches.failed()){invalid();return;}
 if(c.op==0){const float remain[]={0,-1,0.25f,1,2,bits(0x7fc12345),bits(0x80000000)};const float duration[]={0,0.25f,1,2};const float elapsed[]={-1,0,0.25f,1,2};field<float>(self,0xb4)=remain[c.index%7];field<float>(self,0xb0)=duration[c.index/7%4];for(unsigned i=0;i<6;++i)field<float>(self,0x98+i*4)=float(i)-2.5f;field<Ogre::Vector3>(client,0x38e0)=Ogre::Vector3(44,-55,66);void(*fn)(void*,float)=ours?updateCandidate:updateOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self,elapsed[c.index/4%5]);out.callCompleted=1;out.add(static_cast<char*>(self)+0xb4,4);out.add(static_cast<char*>(client)+0x38e0,12);number(calls);}
 else{int before=g_iTotalCountOfObjects;{
  CRunicCore referent;TSafePointer<CRunicCore> sentinel;sentinel.setObject(&referent);std::wstring name=c.index%4==0?L"PLAYER":c.index%4==1?L"":c.index%4==2?L"unit-\x4e2d":std::wstring(c.index,L'x');
  if(c.op==1){CInteract* p=static_cast<CInteract*>(self);new(&p->m_sUnknown78)std::wstring(L"before");new(&p->m_unit)TSafePointer<CBaseUnit>;if(c.index%3)bind(&p->m_unit,&referent);unsigned oldIndex=field<unsigned>(&p->m_unit,8);void(*fn)(void*,unsigned,const std::wstring&)=ours?unitCandidate:unitOriginal;if(!autotest::beginInvocation(out,fn))return;fn(p,c.index%4,name);out.callCompleted=1;text(p->m_sUnknown78);number(p->m_pUnitDataGroup==reinterpret_cast<CDataGroup*>(&dataGroup));number(p->m_unit.getObject()!=0);number(field<unsigned>(&p->m_unit,8)==oldIndex);number(sentinel.getObject()==&referent);number(calls);p->m_unit.~TSafePointer();p->m_sUnknown78.~basic_string();}
  else{CPathController* p=static_cast<CPathController*>(self);new(&p->m_sUnitInteractWith)std::wstring(L"before");new(&p->m_units)TArrayList<TSafePointer<CCharacter>*>;for(unsigned i=0;i<c.index%5;++i){if(i==1){p->m_units.add(0);continue;}TSafePointer<CRunicCore>* weak=OGRE_NEW_T(TSafePointer<CRunicCore>,Ogre::MEMCATEGORY_GENERAL)();if((c.index+i)%3)weak->setObject(&referent);p->m_units.add(reinterpret_cast<TSafePointer<CCharacter>*>(weak));}void(*fn)(void*,std::wstring)=ours?pathUnitCandidate:pathUnitOriginal;if(!autotest::beginInvocation(out,fn))return;fn(p,name);out.callCompleted=1;text(p->m_sUnitInteractWith);number(p->m_pUnitInteractDataGroup==reinterpret_cast<CDataGroup*>(&dataGroup));number(p->m_bUnknown137);number(p->m_units.size());number(sentinel.getObject()==&referent);number(calls);for(unsigned i=0;i<p->m_units.size();++i){TSafePointer<CRunicCore>* weak=reinterpret_cast<TSafePointer<CRunicCore>*>(p->m_units[i]);OGRE_DELETE_T(weak,TSafePointer<CRunicCore>,Ogre::MEMCATEGORY_GENERAL);}p->m_units.~TArrayList();p->m_sUnitInteractWith.~basic_string();}
 }number(g_iTotalCountOfObjects-before);if(g_iTotalCountOfObjects-before!=1)invalid();}
 patches.restore();clients->~TArrayList();}
void original(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),false,out);}void recovered(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned op,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<112;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    world path unit seed %u child %d/%d issue %u/%u completed %u/%u bytes %lu/%lu\n",i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=112||coverage.different||coverage.missing;}
}
TL_TEST(world_path_unit){return run(host,2,"world_path_unit",(uintptr_t)&pathUnitOriginal);}
