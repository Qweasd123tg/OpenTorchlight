#include <cstring>
#define private public
#define protected public
#include "Equipment.h"
#include "GenericModel.h"
#include "DataGroup.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldRimlight,(CEquipment*,std::wstring),"_ZN10CEquipment11setRimlightESbIwSt11char_traitsIwESaIwEE")
extern "C" void newRimlight(CEquipment*,std::wstring) __asm__("_ZN10CEquipment11setRimlightESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(modelRim,"_ZN13CGenericModel14setRimLightingESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(modelTexture,"_ZN13CGenericModel18setTextureOverrideERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dataText,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
namespace {
struct Stop{};struct Case{unsigned mask,mutation,text,fault;};const Case*cs;autotest::Capture*cap;CEquipment*item;CGenericModel*models[3];CDataGroup*groups[2];unsigned events;std::wstring value;
void n(int x){cap->add(&x,4);}int mid(void*p){return !p?0:p==models[0]?1:p==models[1]?2:p==models[2]?3:99;}int gid(void*p){return !p?0:p==groups[0]?1:p==groups[1]?2:99;}
void event(int kind){n(kind);if(++events==cs->fault)throw Stop();}
void rim(CGenericModel*p,std::wstring texture){event(1);n(mid(p));cap->addText(texture);if(cs->mutation==1)item->m_pUnitModel=models[2];if(cs->mutation==2)item->m_pUnitModelSecondary=models[2];if(cs->mutation==3)item->m_pDataGroup=groups[1];}
const std::wstring& data(CDataGroup*p,const std::wstring&key,const std::wstring&def){event(2);n(gid(p));cap->addText(key);cap->addText(def);if(cs->mutation==4)item->m_pUnitModel=models[2];if(cs->mutation==5)item->m_pUnitModelSecondary=models[2];return value;}
void texture(CGenericModel*p,const std::wstring&v){event(3);n(mid(p));cap->addText(v);if(cs->mutation==6){item->m_pUnitModelSecondary=0;item->m_pDataGroup=groups[1];}if(cs->mutation==7)item->m_pUnitModelSecondary=models[2];}
void ptr(unsigned char*p,unsigned off,uintptr_t v){std::memcpy(p+off,&v,8);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*(Case*)raw;cs=&c;cap=&out;events=0;unsigned long long em[(sizeof(CEquipment)+7)/8],mm[3][8],gm[2][8];std::memset(em,0xa5,sizeof(em));item=(CEquipment*)em;for(unsigned i=0;i<3;++i)models[i]=(CGenericModel*)mm[i];for(unsigned i=0;i<2;++i)groups[i]=(CDataGroup*)gm[i];item->m_pDataGroup=c.mask&1?groups[0]:0;item->m_pUnitModel=c.mask&2?models[0]:0;item->m_pUnitModelSecondary=c.mask&4?models[1]:0;const wchar_t*texts[]={L"",L"texture.png",L"\x416",L"very-long-texture-name-to-exercise-copy-on-write-storage"};std::wstring input=texts[c.text];if(c.text==2)input.insert(input.begin(),L'\0');value=c.mask&8?input:std::wstring();detour::Set d;TL_REDIRECT(d,modelRim,&rim);TL_REDIRECT(d,modelTexture,&texture);TL_REDIRECT(d,dataText,&data);if(d.failed())_exit(60);bool threw=false;try{autotest::invoke(out,ours?&newRimlight:&oldRimlight,item,input);}catch(const Stop&){threw=true;}catch(...){_exit(61);}n(threw);n(events);out.addText(input);out.addText(value);unsigned char snapshot[sizeof(em)];std::memcpy(snapshot,em,sizeof(em));ptr(snapshot,0x1b0,gid(item->m_pDataGroup));ptr(snapshot,0x2b0,mid(item->m_pUnitModel));ptr(snapshot,0x2b8,mid(item->m_pUnitModelSecondary));out.add(snapshot,sizeof(snapshot));}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(equipment_rimlight_production){autotest::Coverage cv("equipment_rimlight_production",(uint64_t)(uintptr_t)&oldRimlight);for(unsigned mask=0;mask<16;++mask)for(unsigned mutation=0;mutation<8;++mutation)for(unsigned text=0;text<4;++text){Case c={mask,mutation,text,0};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(cv.observe(host,x,y)){host->log("    rimlight %u/%u/%u exits %d/%d\n",mask,mutation,text,x.childStatus,y.childStatus);cv.report(host);return 1;}}cv.report(host);return 0;}
TL_TEST(equipment_rimlight_expected_exceptions){unsigned count=0;for(unsigned fault=1;fault<=6;++fault)for(unsigned mutation=0;mutation<6;++mutation){Case c={15,mutation,1,fault};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(!x.reportValid||!y.reportValid||x.childStatus||y.childStatus||!x.capture.callStarted||!y.capture.callStarted||x.capture.callCompleted||y.capture.callCompleted||x.capture.issue||y.capture.issue||x.capture.length!=y.capture.length||std::memcmp(x.capture.data,y.capture.data,x.capture.length)){host->log("    rimlight unwind %u/%u exits %d/%d\n",fault,mutation,x.childStatus,y.childStatus);return 1;}++count;}host->log("    EXPECTED RIMLIGHT EXCEPTIONS: %u matching unwinds\n",count);return 0;}
