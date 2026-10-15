#include <cstring>
#include <map>
#include <string>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "UnitResourceList.h"
#undef private
TL_ORIGINAL(void*,oldGuid,(CUnitResourceList*,long long),"_ZN17CUnitResourceList18getDataGroupByGuidEx")
TL_ORIGINAL(void,oldNames,(CUnitResourceList*,TArrayList<std::wstring>&),"_ZN17CUnitResourceList12getUnitNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_ORIGINAL(void,oldClear,(CUnitResourceList*),"_ZN17CUnitResourceList12clearDataOutEv")
TL_ORIGINAL(void*,oldObject,(CUnitResourceList*,const std::wstring&),"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void* newGuid(CUnitResourceList*,long long) __asm__("_ZN17CUnitResourceList18getDataGroupByGuidEx");
extern "C" void newNames(CUnitResourceList*,TArrayList<std::wstring>&) __asm__("_ZN17CUnitResourceList12getUnitNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE");
extern "C" void newClear(CUnitResourceList*) __asm__("_ZN17CUnitResourceList12clearDataOutEv");
extern "C" void* newObject(CUnitResourceList*,const std::wstring&) __asm__("_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(upperString,"_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case{unsigned op,seed;};autotest::Capture*output;uint64_t values[4][12];CUnitResourceList*self;unsigned seed,calls;void**loaded;void*table[3];
void number(unsigned n){output->add(&n,4);}void invalid(){output->issue=autotest::Capture::InvalidReport;}void text(const std::wstring&s){number(s.size());output->add(s.data(),s.size()*4);}
unsigned identity(void*p){if(!p)return 0;for(unsigned i=0;i<4;++i)if(p==values[i])return i+1;invalid();return 99;}
std::wstring upper(const std::wstring&s){number(10);text(s);++calls;std::wstring result=s;for(unsigned i=0;i<result.size();++i)if(result[i]>=L'a'&&result[i]<=L'z')result[i]-=L'a'-L'A';return result;}
void destroy(void*p){unsigned id=identity(p);number(id);if(!id)invalid();for(unsigned i=0;i<calls;++i)if(loaded[i])invalid();++calls;reinterpret_cast<unsigned char*>(p)[0x58]^=0x55;if(seed&16)self->m_loadedDataGroups.m_nCount=1;}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);output=&out;seed=c.seed;calls=0;uint64_t object[(sizeof(CUnitResourceList)+7)/8];std::memset(object,0xa5,sizeof(object));std::memset(values,0x3c,sizeof(values));self=reinterpret_cast<CUnitResourceList*>(object);
 typedef std::map<std::wstring,std::map<std::wstring,CDataGroup*> >Named;typedef std::map<std::wstring,std::map<long long,CDataGroup*> >Grouped;typedef std::map<long long,CDataGroup*>GuidMap;
 Named*n1=new(&self->m_dataGroupsByResourceGroupAndName)Named;Named*n2=new(&self->m_dataGroupsByFileItemAndName)Named;Grouped*groups=new(&self->m_dataGroupsByResourceGroupAndGuid)Grouped;GuidMap*guids=new(&self->m_dataGroupsByGuid)GuidMap;
 TArrayList<std::wstring>*classes=new(&self->m_playerClassNames)TArrayList<std::wstring>(2);TArrayList<CDataGroup*>*data=new(&self->m_loadedDataGroups)TArrayList<CDataGroup*>(2);
 const std::wstring names[]={L"",L"APPLE",L"BANANA",L"мир"};const long long keys[]={-1,0,0xffffffffLL,0x100000000LL};unsigned count=seed%5;
 for(unsigned i=0;i<count;++i){(*guids)[keys[i]]=reinterpret_cast<CDataGroup*>(values[i]);(*n1)[i&1?L"B":L"A"][names[i]]=seed&8?0:reinterpret_cast<CDataGroup*>(values[i]);(*n2)[L"FILE"][names[i]]=reinterpret_cast<CDataGroup*>(values[i]);(*groups)[names[i]][keys[i]]=reinterpret_cast<CDataGroup*>(values[i]);classes->add(names[i]);}
 table[0]=0;table[1]=reinterpret_cast<void*>(&destroy);table[2]=0;void* tableAddress=table;for(unsigned i=0;i<4;++i)std::memcpy(values[i],&tableAddress,sizeof(void*));
 if(c.op==2){for(unsigned i=0;i<count;++i)data->add(seed&8&&i==1?0:reinterpret_cast<CDataGroup*>(values[i]));}loaded=reinterpret_cast<void**>(data->m_pData);
 unsigned char before[sizeof(object)];std::memcpy(before,object,sizeof(object));
 detour::Set patches;if(c.op==3)TL_REDIRECT(patches,upperString,&upper);if(patches.failed()){invalid();return;}
 if(c.op==0){typedef void*(*Fn)(CUnitResourceList*,long long);Fn fn=ours?newGuid:oldGuid;long long key=keys[(seed/5)%4];if(seed&32)key=7;if(!autotest::beginInvocation(out,fn))return;void*result=fn(self,key);out.callCompleted=1;number(identity(result));GuidMap::iterator found=guids->find(key);if(result!=(key==0xffffffffLL||found==guids->end()?0:found->second))invalid();}
 else if(c.op==1){TArrayList<std::wstring>namesOut(seed&4?1:4);if(seed&8)namesOut.add(L"prefix");typedef void(*Fn)(CUnitResourceList*,TArrayList<std::wstring>&);Fn fn=ours?newNames:oldNames;if(!autotest::beginInvocation(out,fn))return;fn(self,namesOut);out.callCompleted=1;number(namesOut.size());number(namesOut.m_nCapacity);for(unsigned i=0;i<namesOut.size();++i)text(namesOut[i]);}
 else if(c.op==2){typedef void(*Fn)(CUnitResourceList*);Fn fn=ours?newClear:oldClear;if(!autotest::beginInvocation(out,fn))return;fn(self);out.callCompleted=1;if(data->m_pData||data->m_nCount||data->m_nCapacity||classes->m_pData||classes->m_nCount||classes->m_nCapacity||!guids->empty()||!n2->empty()||!groups->empty()||n1->size()!=unsigned(count?count==1?1:2:0))invalid();number(calls);number(n1->size());for(Named::iterator i=n1->begin();i!=n1->end();++i){text(i->first);for(std::map<std::wstring,CDataGroup*>::iterator j=i->second.begin();j!=i->second.end();++j){text(j->first);number(identity(j->second));}}}
 else{std::wstring query=seed&32?L"missing":seed%4==1?L"apple":names[seed%4];typedef void*(*Fn)(CUnitResourceList*,const std::wstring&);Fn fn=ours?newObject:oldObject;if(!autotest::beginInvocation(out,fn))return;void*result=fn(self,query);out.callCompleted=1;number(identity(result));number(calls);if(calls!=1)invalid();text(query);}
 if(c.op!=2&&std::memcmp(before,object,sizeof(object)))invalid();if(c.op!=2){if(data->m_pData!=reinterpret_cast<CDataGroup**>(loaded))invalid();for(unsigned i=0;i<data->size();++i)number(identity((*data)[i]));}
 if(c.op==2){for(unsigned i=0;i<sizeof(object);++i){bool mutableByte=(i>=offsetof(CUnitResourceList,m_dataGroupsByFileItemAndName)&&i<offsetof(CUnitResourceList,m_alignmentPaddingF0))||(i>=offsetof(CUnitResourceList,m_loadedDataGroups)&&i<offsetof(CUnitResourceList,m_pMasterDataGroup));if(!mutableByte&&before[i]!=reinterpret_cast<unsigned char*>(object)[i])invalid();}if(classes->m_nGrowBy!=2||data->m_nGrowBy!=2)invalid();}
 unsigned char captured[sizeof(object)];std::memcpy(captured,object,sizeof(object));std::memset(captured+offsetof(CUnitResourceList,m_dataGroupsByResourceGroupAndName),0,sizeof(Named)*2+sizeof(Grouped)+sizeof(GuidMap)+sizeof(TArrayList<std::wstring>));std::memset(captured+offsetof(CUnitResourceList,m_loadedDataGroups),0,sizeof(TArrayList<CDataGroup*>));out.add(captured,sizeof(captured));
 for(unsigned i=0;i<4;++i){void*finalTable;std::memcpy(&finalTable,values[i],sizeof(void*));if(finalTable!=table)invalid();std::memset(values[i],0,sizeof(void*));}out.add(values,sizeof(values));
 data->~TArrayList<CDataGroup*>();classes->~TArrayList<std::wstring>();guids->~GuidMap();groups->~Grouped();n2->~Named();n1->~Named();
}
void original(void*c,autotest::Capture&out){side(c,out,false);}void candidate(void*c,autotest::Capture&out){side(c,out,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<64;++seed){Case c={op,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    unit resources op %u seed %u exits %d/%d issues %u/%u\n",op,seed,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(unit_resources_guid){return run(host,0,"unit_resources_guid",reinterpret_cast<uintptr_t>(&oldGuid));}
TL_TEST(unit_resources_names){return run(host,1,"unit_resources_names",reinterpret_cast<uintptr_t>(&oldNames));}
TL_TEST(unit_resources_clear){return run(host,2,"unit_resources_clear",reinterpret_cast<uintptr_t>(&oldClear));}
TL_TEST(unit_resources_object_name){return run(host,3,"unit_resources_object_name",reinterpret_cast<uintptr_t>(&oldObject));}
