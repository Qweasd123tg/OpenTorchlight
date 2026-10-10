#include <cstring>
#define private public
#define protected public
#include "Equipment.h"
#include "UnitResourceList.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalConvert,(CEquipment*,std::wstring),"_ZN10CEquipment16convertEquipmentESbIwSt11char_traitsIwESaIwEE")
extern "C" void candidateConvert(CEquipment*,std::wstring) __asm__("_ZN10CEquipment16convertEquipmentESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(masterFn,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(dataFn,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
namespace {
struct Stop{};struct Case{unsigned mask,name,mutation,fault;};const Case* cs;autotest::Capture* cap;CEquipment* item;CResourceManager* resources[2];CUnitResourceList* lists[2];CDataGroup* groups[2];unsigned events;
void n(int x){cap->add(&x,4);}int id(void* p,void* a,void* b){return !p?0:p==a?1:p==b?2:99;}
void event(int x){n(x);n(id(item->m_pDataGroup,groups[0],groups[1]));if(++events==cs->fault)throw Stop();}
CUnitResourceList* master(CResourceManager* p){event(1);n(id(p,resources[0],resources[1]));if(cs->mutation==1)item->m_pDataGroup=0;if(cs->mutation==2){item->m_pDataGroup=groups[1];item->m_pResourceManager=resources[1];}return lists[cs->mutation==3?1:0];}
CDataGroup* data(CUnitResourceList* p,const std::wstring& type,const std::wstring& name){event(2);n(id(p,lists[0],lists[1]));cap->addText(type);cap->addText(name);if(cs->mutation==3)item->m_pDataGroup=0;return cs->mask&2?groups[1]:0;}
void init(CEquipment* p,CDataGroup* g,bool value){event(3);n(p==item);n(id(g,groups[0],groups[1]));n(value);p->m_pDataGroup=g;}
void ptr(unsigned char* p,unsigned off,uintptr_t x){std::memcpy(p+off,&x,8);}
void side(void* raw,autotest::Capture& out,bool ours){
 Case c=*(Case*)raw;cs=&c;cap=&out;events=0;unsigned long long mm[(sizeof(CEquipment)+23)/8],rm[2][8]={0},lm[2][8]={0},gm[2][8]={0};std::memset(mm,0xa5,sizeof(mm));item=(CEquipment*)mm;void* vt[110]={0};vt[0x1f0/8]=(void*)&init;*(void***)item=vt;
 for(unsigned i=0;i<2;++i){resources[i]=(CResourceManager*)rm[i];lists[i]=(CUnitResourceList*)lm[i];groups[i]=(CDataGroup*)gm[i];}item->m_pResourceManager=resources[0];item->m_pDataGroup=c.mask&1?groups[0]:0;
 const wchar_t* names[]={L"",L"ITEM",L"item with spaces",L"Меч",L"long-long-long-long-long-long-equipment",L"a\tb\nc"};std::wstring name=names[c.name];if(c.name==5)name.insert(name.begin()+1,L'\0');
 detour::Set d;TL_REDIRECT(d,masterFn,&master);TL_REDIRECT(d,dataFn,&data);if(d.failed())_exit(60);bool threw=false;try{if(ours)autotest::invoke(out,&candidateConvert,item,name);else autotest::invoke(out,&originalConvert,item,name);}catch(const Stop&){threw=true;}catch(...){_exit(61);}n(threw);n(events);cap->addText(name);unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0,1);ptr(snapshot,0x68,id(item->m_pResourceManager,resources[0],resources[1]));ptr(snapshot,0x1b0,id(item->m_pDataGroup,groups[0],groups[1]));out.add(snapshot,sizeof(snapshot));
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(equipment_convert){autotest::Coverage coverage("equipment_convert",(uint64_t)(uintptr_t)&originalConvert);for(unsigned mask=0;mask<4;++mask)for(unsigned name=0;name<6;++name)for(unsigned mutation=0;mutation<4;++mutation){Case c={mask,name,mutation,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    convert mismatch %u/%u/%u exits %d/%d\n",mask,name,mutation,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
TL_TEST(equipment_convert_expected_exceptions){unsigned count=0;for(unsigned fault=1;fault<=3;++fault)for(unsigned name=0;name<6;++name)for(unsigned mutation=0;mutation<4;++mutation){Case c={3,name,mutation,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    convert unwind mismatch %u/%u/%u exits %d/%d\n",fault,name,mutation,u.childStatus,v.childStatus);return 1;}++count;}host->log("    EXPECTED CONVERT EXCEPTIONS: %u matching unwinds\n",count);return 0;}
