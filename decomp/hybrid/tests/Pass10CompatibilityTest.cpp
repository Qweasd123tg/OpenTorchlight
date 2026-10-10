#include <string>
#include <vector>
#include <cstring>
#include <limits>
#define private public
#define protected public
#include "Inventory.h"
#include "EquipmentRef.h"
#include "GameClient.h"
#include "GameUI.h"
#include "MouseManager.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,originalBoolText,(bool),"_ZN7STRINGS17GetValueAsWStringEb")
extern "C" std::wstring candidateBoolText(bool) __asm__("_ZN7STRINGS17GetValueAsWStringEb");
TL_ORIGINAL(int,originalPane,(CInventory*,EINVENTORY_PANES),"_ZN10CInventory11itemsInPaneE16EINVENTORY_PANES")
extern "C" int candidatePane(CInventory*,EINVENTORY_PANES) __asm__("_ZN10CInventory11itemsInPaneE16EINVENTORY_PANES");
TL_ORIGINAL(bool,originalMenuInput,(CGameClient*,void*,float,bool),"_ZN11CGameClient16processMenuInputEPvfb")
extern "C" bool candidateMenuInput(CGameClient*,void*,float,bool) __asm__("_ZN11CGameClient16processMenuInputEPvfb");
TL_FUNCTION(paneIndexFn,"_ZN10CInventory12getPaneIndexE16EINVENTORY_PANES")
TL_FUNCTION(uiProcessFn,"_ZN7CGameUI12processInputEP11CGameClientPvfb")
TL_FUNCTION(mouseHeldFn,"_ZN13CMouseManager10buttonHeldE12EMouseButton")
TL_FUNCTION(mouseUpdateFn,"_ZN13CMouseManager6updateEPv")
namespace {
struct BoolCase {bool value; unsigned allocation;};
void boolSide(void* data,autotest::Capture& out,bool ours) {
    BoolCase c=*static_cast<BoolCase*>(data);bool value=c.value;
    // Both boolean inputs across sixteen live allocation/COW contexts.
    std::vector<std::wstring> live;
    for(unsigned i=0;i<c.allocation;++i)live.push_back(std::wstring((i+1)*17,L'a'+i));
    std::vector<std::wstring> shared=live;
    if(c.allocation&1)live[0][0]=L'Z';
    autotest::invoke(out,ours?&candidateBoolText:&originalBoolText,value);
    for(unsigned i=0;i<live.size();++i){out.addText(live[i]);out.addText(shared[i]);}
}
void boolA(void*p,autotest::Capture&o){boolSide(p,o,false);} void boolB(void*p,autotest::Capture&o){boolSide(p,o,true);}
struct PaneCase {unsigned panes,index,count,capacity,profile,mutation;};
const PaneCase* pc; CInventory* inventory; autotest::Capture* capture;
void number(unsigned n){capture->add(&n,sizeof(n));}
unsigned paneIndex(CInventory* p,EINVENTORY_PANES pane) {
    number(p==inventory);number(unsigned(pane));
    if(pc->mutation) { p->m_paneStarts[pc->index]=pc->profile?7:0; p->m_equipmentRefs.m_nCount=pc->count/2; }
    return pc->index;
}
void paneSide(void* data,autotest::Capture& out,bool ours) {
    PaneCase c=*static_cast<PaneCase*>(data);pc=&c;capture=&out;
    unsigned long long memory[(sizeof(CInventory)+15)/8];std::memset(memory,0xa5,sizeof(memory));
    inventory=reinterpret_cast<CInventory*>(memory);
    new(&inventory->m_paneStarts)std::vector<unsigned int>();
    for(unsigned i=0;i<c.panes;++i)inventory->m_paneStarts.push_back(i*10);
    unsigned long long refMemory[8][(sizeof(CEquipmentRef)+7)/8];std::memset(refMemory,0x5a,sizeof(refMemory));
    CEquipmentRef* refs[8]; const unsigned slots[]={0,1,9,10,19,20,30,0xffffffffu};
    for(unsigned i=0;i<8;++i){refs[i]=reinterpret_cast<CEquipmentRef*>(refMemory[i]);refs[i]->m_slot=slots[(i+c.profile)%8];}
    inventory->m_equipmentRefs.m_pData=refs;inventory->m_equipmentRefs.m_nCount=c.count;inventory->m_equipmentRefs.m_nCapacity=c.capacity;
    detour::Set d;TL_REDIRECT(d,paneIndexFn,&paneIndex);if(d.failed())_exit(60);
    EINVENTORY_PANES pane=static_cast<EINVENTORY_PANES>(int(c.index)-2);
    autotest::invoke(out,ours?&candidatePane:&originalPane,inventory,pane);
    out.add(memory,sizeof(memory));out.add(refMemory,sizeof(refMemory));
    for(unsigned i=0;i<c.panes;++i)number(inventory->m_paneStarts[i]);
    inventory->m_paneStarts.~vector();
}
void paneA(void*p,autotest::Capture&o){paneSide(p,o,false);}void paneB(void*p,autotest::Capture&o){paneSide(p,o,true);}
struct InputCase{unsigned ui,result,held,enabled,pattern,mutation,time;};
const InputCase* ic;CGameClient* client;CGameUI* ui;void* window;
bool process(CGameUI* p,CGameClient* c,void* w,float elapsed,bool enabled) {
    number(10);number(p==ui);number(c==client);number(w==window);capture->add(&elapsed,4);number(enabled);
    if(ic->mutation==1){client->m_leftHeld=!client->m_leftHeld;client->m_rightHeld=!client->m_rightHeld;client->m_inputConsumed=!client->m_inputConsumed;client->m_pGameUI=NULL;}
    return ic->result;
}
bool held(CMouseManager* p,EMouseButton button) {
    number(20);number(p==reinterpret_cast<CMouseManager*>(reinterpret_cast<char*>(client)+0xfe8));number(unsigned(button));
    if(ic->mutation==2){client->m_leftHeld=!client->m_leftHeld;client->m_rightHeld=!client->m_rightHeld;}
    return (ic->held&(1u<<unsigned(button)))!=0;
}
void update(CMouseManager* p,void* w) {
    number(30);number(p==reinterpret_cast<CMouseManager*>(reinterpret_cast<char*>(client)+0xfe8));number(w==window);
    number(client->m_inputConsumed);number(client->m_leftHeld);number(client->m_rightHeld);
    if(ic->mutation==3)client->m_inputConsumed=false;
}
void inputSide(void* data,autotest::Capture& out,bool ours) {
    InputCase c=*static_cast<InputCase*>(data);ic=&c;capture=&out;
    unsigned long long memory[(sizeof(CGameClient)+15)/8],uiMemory[(sizeof(CGameUI)+7)/8];
    std::memset(memory,c.pattern?0xa5:0x5a,sizeof(memory));std::memset(uiMemory,0x69,sizeof(uiMemory));
    client=reinterpret_cast<CGameClient*>(memory);ui=reinterpret_cast<CGameUI*>(uiMemory);window=reinterpret_cast<void*>(uintptr_t(0x1350));
    client->m_pGameUI=c.ui?ui:NULL;client->m_inputConsumed=c.pattern;client->m_leftHeld=c.pattern;client->m_rightHeld=!c.pattern;
    detour::Set d;TL_REDIRECT(d,uiProcessFn,&process);TL_REDIRECT(d,mouseHeldFn,&held);TL_REDIRECT(d,mouseUpdateFn,&update);if(d.failed())_exit(60);
    const float times[]={0.f,-0.f,0.125f,-3.f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};
    autotest::invoke(out,ours?&candidateMenuInput:&originalMenuInput,client,window,times[c.time],bool(c.enabled));
    // Only an exact known pointer is normalized; all other bytes remain observable.
    if(client->m_pGameUI==ui)client->m_pGameUI=reinterpret_cast<CGameUI*>(uintptr_t(1));
    out.add(memory,sizeof(memory));out.add(uiMemory,sizeof(uiMemory));
}
void inputA(void*p,autotest::Capture&o){inputSide(p,o,false);}void inputB(void*p,autotest::Capture&o){inputSide(p,o,true);}
int pair(const tlhybrid_host* host,autotest::Coverage& cov,void(*a)(void*,autotest::Capture&),void(*b)(void*,autotest::Capture&),void* data) {
    autotest::Outcome x,y;autotest::runChild(a,data,x);autotest::runChild(b,data,y);
    return cov.observe(host,x,y)||autotest::incomplete(x)||autotest::incomplete(y)||x.childStatus||y.childStatus||x.capture.length!=y.capture.length||std::memcmp(x.capture.data,y.capture.data,x.capture.length);
}
}
TL_TEST(pass10_bool_text) {
    autotest::Coverage cov("pass10_bool_text",(uint64_t)(uintptr_t)&originalBoolText);
    for(unsigned allocation=0;allocation<16;++allocation)for(unsigned i=0;i<2;++i){BoolCase value={bool(i),allocation};if(pair(host,cov,boolA,boolB,&value)){cov.report(host);return 1;}}
    cov.report(host);return 0;
}
TL_TEST(pass10_inventory_pane) {
    autotest::Coverage cov("pass10_inventory_pane",(uint64_t)(uintptr_t)&originalPane);
    for(unsigned panes=1;panes<=4;++panes)for(unsigned index=0;index<panes;++index)for(unsigned count=0;count<=8;++count)for(unsigned capacity=0;capacity<=8;capacity+=2)for(unsigned profile=0;profile<8;profile+=2)for(unsigned mutation=0;mutation<2;++mutation){
        PaneCase c={panes,index,count,capacity,profile,mutation};if(pair(host,cov,paneA,paneB,&c)){host->log("    pane %u/%u/%u/%u/%u/%u\n",panes,index,count,capacity,profile,mutation);cov.report(host);return 1;}
    }cov.report(host);return 0;
}
TL_TEST(pass10_menu_input) {
    autotest::Coverage cov("pass10_menu_input",(uint64_t)(uintptr_t)&originalMenuInput);
    for(unsigned present=0;present<2;++present)for(unsigned result=0;result<2;++result)for(unsigned heldMask=0;heldMask<4;++heldMask)for(unsigned enabled=0;enabled<2;++enabled)for(unsigned pattern=0;pattern<2;++pattern)for(unsigned mutation=0;mutation<4;++mutation)for(unsigned time=0;time<6;++time){
        InputCase c={present,result,heldMask,enabled,pattern,mutation,time};if(pair(host,cov,inputA,inputB,&c)){host->log("    input %u/%u/%u/%u/%u/%u/%u\n",present,result,heldMask,enabled,pattern,mutation,time);cov.report(host);return 1;}
    }cov.report(host);return 0;
}
