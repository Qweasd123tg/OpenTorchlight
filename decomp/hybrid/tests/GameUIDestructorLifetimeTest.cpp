// Full owner lifetime: original C1 establishes every embedded C++ subobject.
// Only external UI/SDL collaborators are mocks. No nontrivial object is copied.
#include <string>
#include <vector>
#include <cstring>
#include <new>
#define private public
#define protected public
#include <CEGUI.h>
#include "GameUI.h"
#include "Character.h"
#include "Equipment.h"
#include "GameUITextEventList.h"
#include "SDL.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,uiOriginalD1,(CGameUI*),"_ZN7CGameUID1Ev")
TL_ORIGINAL(void,uiOriginalD0,(CGameUI*),"_ZN7CGameUID0Ev")
extern "C" void uiCandidateD1(CGameUI*) __asm__("_ZN7CGameUID1Ev");
extern "C" void uiCandidateD0(CGameUI*) __asm__("_ZN7CGameUID0Ev");
// Construction is setup, deliberately excluded from destructor coverage.
extern "C" void uiConstruct(CGameUI*,void*,void*,void*,void*,void*,void*,void*,void*,void*) __asm__("__tlorig__ZN7CGameUIC1ER9CSettingsR11CGameClientPvPN4Ogre12RenderWindowEPNS5_6CameraEPNS5_12SceneManagerESB_SB_P16CResourceManager");
TL_FUNCTION(uiDtCreate,"_ZN7CGameUI6createEv")
TL_FUNCTION(uiDtMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(uiDtCore,"_ZN10CRunicCoreD1Ev")
TL_FUNCTION(uiDtKey,"_ZN11CKeyManagerD1Ev")
TL_FUNCTION(uiDtMouse,"_ZN13CMouseManagerD1Ev")
TL_FUNCTION(uiDtRemove,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
extern "C" char uiDtKeyboard[] __asm__("SDL_GetKeyboardState");
extern "C" char uiDtSetCursor[] __asm__("SDL_SetCursor");
extern "C" char uiDtFreeCursor[] __asm__("SDL_FreeCursor");
extern "C" char uiDtRemoveChild[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char uiDtDelete[] __asm__("_ZdlPv");
extern "C" char uiDtDeleteArray[] __asm__("_ZdaPv");
extern "C" char uiDtOgreDelete[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char uiDtStringRep[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
namespace gameui_dtor_fixture {
typedef TLinkedListNode<CTextEvent*> Node;
typedef gameui_create_detail::TextEventList List;
struct Stop {};
struct Case { unsigned mask, mode, fault; bool deleting; };
// IDs: events 0..5; submenus 6..8; dropdowns 9..11; owned fields 12..23;
// late shell events 24..25; appended submenu 26; spare dropdown 27.
struct MockWindow { char prefix[0xb0]; CEGUI::Window* parent; MockWindow():parent(0){} };
struct Mock : CRunicCore {
    char unused[0x68]; CEGUI::Window* window; unsigned id;
    explicit Mock(unsigned value):window(0),id(value){}
};
typedef char mock_window_offset[__builtin_offsetof(Mock,window)==0x78?1:-1];
static const Case* input;
static autotest::Capture* capture;
static CGameUI* ui;
static Mock* objects[36];
static MockWindow windows[6], parentWindow;
static void* table[2];
static unsigned cursorTokens[7];
static void* allocations[40];
static void* reps[7];
static unsigned frees[3][40], destroyed[36];
static int actual[512], expected[512];
static unsigned actualCount, expectedCount;
static bool logging, body, threw;
static int liveBefore;
static unsigned semanticErrors;
struct Result { unsigned magic, errors, mismatch; int got,want; unsigned actualSize,expectedSize; int counterDelta; };
static const unsigned resultMagic=0x55494454u;
static List* activeList; static List* freeList;
static Node* nodes[10];
static detour::Set *corePatch,*keyPatch,*mousePatch,*removePatch;
static std::wstring aliases[7];
static unsigned char keyboard[512];
static unsigned long long masterStorage[64], borrowedStorage[16];
static const unsigned refOffsets[8]={0x48,0x58,0x68,0x80,0x90,0xa0,0xb8,0xc8};
static CGameUI*& singleton(){return *reinterpret_cast<CGameUI**>(0x14b9c68);}
static void n(int value){capture->add(&value,sizeof(value));}
static int objectID(const void* p){if(!p)return -1;for(unsigned i=0;i<36;++i)if(p==objects[i])return i;return -2;}
static int allocationID(const void* p){for(unsigned i=0;i<40;++i)if(p&&p==allocations[i])return i;return -1;}
static bool owned(unsigned id){return (input->mask & (1u<<(id-12)))!=0;}
static void record(int value) {
    if(!logging)return;
    if(actualCount==512)_exit(71);
    actual[actualCount++]=value;n(value);
    if(body) {
        n(singleton()==0?0:singleton()==ui?1:2);
        n(ui->m_cursors.size());n(ui->m_submenus.size());n(ui->m_dropdowns.size());
        n(ui->m_guiLook==0);n(ui->m_statsImageset==0);
        n(ui->m_itemImagesets.m_nCount);n(ui->m_itemImagesets.m_nCapacity);
        n(ui->m_activeEvents==0);n(ui->m_freeEvents==0);
        const unsigned offsets[]={0x4a0,0x4a8,0x4b0,0x4b8,0x1690,0xb8,0x570,0x578,0x430,0x428,0x16a8,0x588};
        for(unsigned i=0;i<12;++i){void* p;std::memcpy(&p,(char*)ui+offsets[i],sizeof(p));n(objectID(p));}
    }
}
static void point(int value){record(value);if(input->fault==unsigned(value))throw Stop();}
static void expect(int value){if(expectedCount==512)_exit(72);expected[expectedCount++]=value;}
static void* master(){return masterStorage;}
static const unsigned char* keys(int*){return keyboard;}
static bool create(CGameUI* p) {
    for(unsigned i=0;i<6;++i)p->m_cursors.push_back(reinterpret_cast<SDL_Cursor*>(&cursorTokens[i]));
    p->m_activeEvents=new List; p->m_freeEvents=new List;
    p->m_equipmentTooltip=0;p->m_compareFirst=0;p->m_compareSecond=0;p->m_skillTooltip=0;
    p->m_console=0;p->m_interactiveMenu=0;p->m_fishingMenu=0;
    p->m_ceguiSystem=0;p->m_renderer=0;p->m_soundBank=0;p->m_menuManager=0;
    return true;
}
static void setCursor(SDL_Cursor* p){if(p)semanticErrors|=1;point(1);}
static void freeCursor(SDL_Cursor* p) {
    unsigned id=7;for(unsigned i=0;i<7;++i)if(p==reinterpret_cast<SDL_Cursor*>(&cursorTokens[i]))id=i;
    // One null cursor still requires an unconditional SDL_FreeCursor call.
    if(!p)id=6;
    if(id==7)semanticErrors|=1;point(10+id);
    if(input->mode==2&&id==0)ui->m_cursors[1]=reinterpret_cast<SDL_Cursor*>(&cursorTokens[6]);
}
static void detach(CEGUI::Window* parent,CEGUI::Window* child) {
    if(parent!=reinterpret_cast<CEGUI::Window*>(&parentWindow))semanticErrors|=2;
    int id=-1;for(unsigned i=0;i<6;++i)if(child==reinterpret_cast<CEGUI::Window*>(&windows[i]))id=i;
    if(id<0)semanticErrors|=2;point(30+id);
}
static void core(CRunicCore* p) {
    if(p==static_cast<CRunicCore*>(ui))record(1004);
    else if(p==static_cast<CRunicCore*>(&ui->m_keys))record(1003);
    else if(p==static_cast<CRunicCore*>(&ui->m_mouse))record(1002);
    corePatch->restore();reinterpret_cast<void(*)(CRunicCore*)>(uiDtCore_original)(p);
    TL_REDIRECT(*corePatch,uiDtCore,&core);if(corePatch->failed())_exit(77);
}
static void key(CKeyManager* p){record(1001);keyPatch->restore();reinterpret_cast<void(*)(CKeyManager*)>(uiDtKey_original)(p);TL_REDIRECT(*keyPatch,uiDtKey,&key);if(keyPatch->failed())_exit(78);}
static void mouse(CMouseManager* p){record(1000);mousePatch->restore();reinterpret_cast<void(*)(CMouseManager*)>(uiDtMouse_original)(p);TL_REDIRECT(*mousePatch,uiDtMouse,&mouse);if(mousePatch->failed())_exit(79);}
static void removeReference(CRunicCore* p,TSafePointer<void*>* r,unsigned index) {
    int id=-1;for(unsigned i=0;i<8;++i)if((char*)r==(char*)ui+refOffsets[i])id=i;
    if(id<0)_exit(80);record(1100+id);n(objectID(p));n(index);
    removePatch->restore();reinterpret_cast<void(*)(CRunicCore*,TSafePointer<void*>*,unsigned)>(uiDtRemove_original)(p,r,index);
    TL_REDIRECT(*removePatch,uiDtRemove,&removeReference);if(removePatch->failed())_exit(81);
}
static void registerNode(List* list,unsigned node,unsigned object) {
    list->prepend(object<36?reinterpret_cast<CTextEvent*>(objects[object]):0);
    nodes[node]=list->head;allocations[20+node]=nodes[node];
}
static void destroy(void* p) {
    int id=objectID(p);if(id<0){semanticErrors|=16;record(199);return;}
    bool duplicate=destroyed[id]++!=0;if(duplicate)semanticErrors|=16;
    point(100+id);
    if(id==6&&input->mode==3) {
        // A real vector growth changes both storage and the iteration bound.
        ui->m_submenus.push_back(reinterpret_cast<CSubMenu*>(objects[26]));
        allocations[7]=&ui->m_submenus[0];
    }
    if(id==9&&input->mode==4)ui->m_dropdowns.resize(1);
    if(id==12&&input->mode==5) {
        registerNode(activeList,6,24);registerNode(freeList,7,25);
        registerNode(activeList,8,36);registerNode(freeList,9,36);
    }
    if(id==17&&!duplicate) {
        // A real base destructor invalidates every registered alias of the
        // owned +b8 pointee, including the external witness below.
        core(static_cast<CRunicCore*>(objects[id]));
    }
}
static void globalDelete(void* p) {
    int id=allocationID(p);if(id<0)return;
    if(id==1)body=false; // Cursor storage is the first automatic subobject.
    ++frees[0][id];record(500+id);
}
static void arrayDelete(void* p){int id=allocationID(p);if(id<0)return;++frees[1][id];record(700+id);}
static void ogreDelete(void* p) {
    int id=allocationID(p);if(id<0)return;
    if(id>=20&&id<30){Node* node=nodes[id-20];if(node->m_pNext||node->m_pPrevious)semanticErrors|=4;}
    if(id==10&&activeList->head)semanticErrors|=8;
    if(id==11&&freeList->head)semanticErrors|=8;
    ++frees[2][id];record(300+id);
}
static void stringRep(void* p,const void*) {
    int id=-1;for(unsigned i=0;i<7;++i)if(reps[i]==p)id=i;
    if(id>=0)record(900+id);
}
static void setup(const Case& c) {
    std::memset(masterStorage,0,sizeof(masterStorage));std::memset(keyboard,0,sizeof(keyboard));
    std::memset(allocations,0,sizeof(allocations));std::memset(frees,0,sizeof(frees));
    std::memset(destroyed,0,sizeof(destroyed));std::memset(reps,0,sizeof(reps));
    std::memset(nodes,0,sizeof(nodes));actualCount=expectedCount=0;logging=false;body=true;threw=false;semanticErrors=0;
    new(reinterpret_cast<void*>(0x14b7d08))std::wstring;
    singleton()=0;
    ui=static_cast<CGameUI*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGameUI),0,0,0));
    std::memset(ui,0xa5,sizeof(CGameUI));
    uiConstruct(ui,borrowedStorage,borrowedStorage,0,0,0,0,0,0,0);
    activeList=ui->m_activeEvents;freeList=ui->m_freeEvents;
    allocations[0]=ui;allocations[1]=&ui->m_cursors[0];allocations[10]=activeList;allocations[11]=freeList;
    table[0]=table[1]=reinterpret_cast<void*>(&destroy);
    for(unsigned i=0;i<36;++i){objects[i]=new Mock(i);*reinterpret_cast<void***>(objects[i])=table;}
    if(c.mode!=0)for(int i=2;i>=0;--i){registerNode(activeList,i,i);registerNode(freeList,i+3,i+3);}
    for(unsigned i=0;i<6;++i){
        windows[i].parent=(i%3==2)?0:reinterpret_cast<CEGUI::Window*>(&parentWindow);
        objects[i]->window=i%3==0?0:reinterpret_cast<CEGUI::Window*>(&windows[i]);
    }
    if(c.mode==2)ui->m_cursors[3]=0;
    ui->m_submenus.reserve(3);ui->m_submenus.push_back(reinterpret_cast<CSubMenu*>(objects[6]));ui->m_submenus.push_back(0);ui->m_submenus.push_back(reinterpret_cast<CSubMenu*>(objects[8]));
    ui->m_dropdowns.reserve(3);ui->m_dropdowns.push_back(reinterpret_cast<CDropdownMenu*>(objects[9]));ui->m_dropdowns.push_back(0);ui->m_dropdowns.push_back(reinterpret_cast<CDropdownMenu*>(objects[11]));
    ui->m_queuedTips.push_back(static_cast<EContextTip>(7));
    allocations[2]=&ui->m_queuedTips[0];allocations[3]=&ui->m_dropdowns[0];allocations[4]=&ui->m_submenus[0];
    ui->m_guiLook=reinterpret_cast<CEGUI::Imageset*>(objects[30]);ui->m_statsImageset=reinterpret_cast<CEGUI::Imageset*>(objects[31]);
    ui->m_itemImagesets.add(reinterpret_cast<CEGUI::Imageset*>(objects[30]));allocations[5]=ui->m_itemImagesets.m_pData;
    ui->m_itemIconFiles.add(std::wstring(31,L'x'));ui->m_itemIconFiles.add(std::wstring(37,L'y'));
    allocations[6]=reinterpret_cast<char*>(ui->m_itemIconFiles.m_pData)-sizeof(size_t);
    const unsigned offsets[]={0x4a0,0x4a8,0x4b0,0x4b8,0x1690,0xb8,0x570,0x578,0x430,0x428,0x16a8,0x588};
    for(unsigned i=0;i<12;++i)if(i!=5){void* p=owned(12+i)?objects[12+i]:0;std::memcpy((char*)ui+offsets[i],&p,sizeof(p));}
    ui->m_hoveredCharacter.setObject(reinterpret_cast<CCharacter*>(objects[28]));
    ui->m_selectedCharacter.setObject(reinterpret_cast<CCharacter*>(objects[28]));
    ui->m_mouseOverItem.setObject(reinterpret_cast<CItem*>(objects[29]));
    ui->m_targetedItem.setObject(reinterpret_cast<CEquipment*>(c.mode==6&&owned(17)?objects[17]:objects[29]));
    ui->m_reference90.setObject(reinterpret_cast<CCharacter*>(objects[28]));
    ui->m_referenceA0.setObject(reinterpret_cast<CCharacter*>(objects[28]));
    if(owned(17))ui->m_draggedItem.setObject(reinterpret_cast<CEquipment*>(objects[17]));
    ui->m_dragOwner.setObject(reinterpret_cast<CCharacter*>(objects[28]));
    std::wstring* strings[]={&ui->m_name16B0,&ui->m_name16B8,&ui->m_text16C0,&ui->m_smallText,&ui->m_bigText,&ui->m_itemIconFiles[0],&ui->m_itemIconFiles[1]};
    for(unsigned i=0;i<7;++i){*strings[i]=std::wstring(40+i,L'a'+i);reps[i]=const_cast<char*>(reinterpret_cast<const char*>(strings[i]->c_str()))-24;if(c.mode==7||c.fault||i>=5)aliases[i]=*strings[i];}
    // Singleton must clear even when it no longer points to the dying owner.
    singleton()=(c.mode&1)?reinterpret_cast<CGameUI*>(objects[35]):ui;
}
static void automaticExpected(bool imagesRemain,bool dragLive) {
    expect(501);
    if(input->mode!=7&&!input->fault){expect(904);expect(903);}
    expect(502);expect(503);expect(input->mode==3?507:504);
    if(input->mode!=7&&!input->fault){expect(902);expect(901);expect(900);}
    expect(1000);expect(1002);expect(1001);expect(1003);
    if(imagesRemain)expect(705);
    expect(706); // Array strings retain external COW aliases; see final witnesses.
    for(int i=7;i>=0;--i){if(i==6&&!dragLive)continue;if(i==3&&input->mode==6&&owned(17)&&!dragLive)continue;expect(1100+i);}
    expect(1004);
}
// Independent normal trace from the ELF ownership/order contract, not from the
// implementation and not obtained by accepting the original's recorded trace.
static void buildExpected() {
    expect(1);for(unsigned i=0;i<5;++i)expect(10+((input->mode==2&&(i==1||i==3))?6:i));expect(705);
    if(input->mode!=0)for(unsigned pool=0;pool<2;++pool){for(unsigned i=0;i<3;++i){unsigned id=pool*3+i;if(i==1)expect(30+id);expect(100+id);}for(unsigned i=0;i<3;++i)expect(320+pool*3+i);}
    expect(106);if(input->mode==3)expect(504);expect(108);if(input->mode==3)expect(126);
    expect(109);if(input->mode!=4)expect(111);
    for(unsigned i=12;i<16;++i)if(owned(i))expect(100+i);
    if(input->mode==5&&owned(12)){expect(328);expect(124);expect(326);}expect(310);
    if(input->mode==5&&owned(12)){expect(329);expect(125);expect(327);}expect(311);
    for(unsigned i=16;i<24;++i)if(owned(i))expect(100+i);
    unsigned bodyCount=expectedCount;
    if(input->fault) {
        unsigned at=0;while(at<bodyCount&&unsigned(expected[at])!=input->fault)++at;
        if(at==bodyCount)_exit(86);expectedCount=at+1;
        // Original GCC 4.4 landing pads a94c4e/a94c53 reach member-only
        // cleanup at a949bb. An interrupted shell delete frees neither its
        // current node nor its shell; do not impose modern delete-on-throw.
        bool imagesRemain=input->fault==1||(input->fault>=10&&input->fault<20);
        bool dragLive=owned(17);for(unsigned i=0;i<at;++i)if(expected[i]==117)dragLive=false;
        // Only a mutation already reached can replace the submenu allocation.
        unsigned mode=input->mode;
        if(mode==3&&input->fault<=106)const_cast<Case*>(input)->mode=1;
        automaticExpected(imagesRemain,dragLive);
        const_cast<Case*>(input)->mode=mode;
    } else {automaticExpected(false,false);if(input->deleting)expect(300);}
}
static void side(Case c,bool ours,autotest::Capture& out) {
    input=&c;capture=&out;
    detour::Set setupPatches;TL_REDIRECT(setupPatches,uiDtCreate,&create);TL_REDIRECT(setupPatches,uiDtMaster,&master);setupPatches.redirect(uiDtKeyboard,uiDtKeyboard,&keys);if(setupPatches.failed())_exit(87);
    setup(c);buildExpected();liveBefore=*reinterpret_cast<int*>(0x150b420);
    detour::Set patches,cp,kp,mp,rp;corePatch=&cp;keyPatch=&kp;mousePatch=&mp;removePatch=&rp;
    TL_REDIRECT(cp,uiDtCore,&core);TL_REDIRECT(kp,uiDtKey,&key);TL_REDIRECT(mp,uiDtMouse,&mouse);TL_REDIRECT(rp,uiDtRemove,&removeReference);
    patches.redirect(uiDtSetCursor,uiDtSetCursor,&setCursor);patches.redirect(uiDtFreeCursor,uiDtFreeCursor,&freeCursor);patches.redirect(uiDtRemoveChild,uiDtRemoveChild,&detach);
    patches.redirect(uiDtDelete,uiDtDelete,&globalDelete);patches.redirect(uiDtDeleteArray,uiDtDeleteArray,&arrayDelete);patches.redirect(uiDtOgreDelete,uiDtOgreDelete,&ogreDelete);patches.redirect(uiDtStringRep,uiDtStringRep,&stringRep);
    if(patches.failed()||cp.failed()||kp.failed()||mp.failed()||rp.failed())_exit(88);
    logging=true;
    try {if(ours)autotest::invoke(out,c.deleting?&uiCandidateD0:&uiCandidateD1,ui);else autotest::invoke(out,c.deleting?&uiOriginalD0:&uiOriginalD1,ui);}catch(const Stop&){threw=true;}catch(...){threw=true;semanticErrors|=32;}
    logging=false;
    n(threw);if(threw!=(c.fault!=0))semanticErrors|=32;
    n(actualCount);n(expectedCount);unsigned mismatch=0;
    while(mismatch<actualCount&&mismatch<expectedCount&&actual[mismatch]==expected[mismatch])++mismatch;
    n(mismatch);if(actualCount!=expectedCount||mismatch!=actualCount)semanticErrors|=64;
    for(unsigned kind=0;kind<3;++kind)for(unsigned i=0;i<40;++i)n(frees[kind][i]);
    for(unsigned i=0;i<36;++i)n(destroyed[i]);
    n(singleton()==0); // No access through already-destroyed STL members.
    int liveDelta=liveBefore-*reinterpret_cast<int*>(0x150b420);n(liveDelta);
    // d79920 does not decrement the cumulative construction counter.
    if(liveDelta!=0)semanticErrors|=128;
    for(unsigned i=0;i<8;++i){void* p;unsigned index;std::memcpy(&p,(char*)ui+refOffsets[i],sizeof(p));std::memcpy(&index,(char*)ui+refOffsets[i]+8,sizeof(index));n(p==0);n(index==0xffffffffu);if(p||index!=0xffffffffu)semanticErrors|=256;}
    // COW aliases observe real destruction without assuming that libstdc++'s
    // internal _M_destroy goes through the game's import PLT. Array strings
    // always have aliases; exceptional member cleanup uses the out-of-line
    // string destructor too, so every string has a witness in those cases.
    for(unsigned i=0;i<7;++i)if(c.mode==7||c.fault||i>=5){
        int references;std::memcpy(&references,static_cast<char*>(reps[i])+16,sizeof(references));
        n(references);n(aliases[i].size());n(aliases[i].empty()?-1:static_cast<const std::wstring&>(aliases[i])[0]);
        if(references!=0||aliases[i].size()!=40+i||static_cast<const std::wstring&>(aliases[i])[0]!=wchar_t(L'a'+i))semanticErrors|=512;
    }
    Result result={resultMagic,semanticErrors,mismatch,mismatch<actualCount?actual[mismatch]:-1,mismatch<expectedCount?expected[mismatch]:-1,actualCount,expectedCount,liveDelta};
    capture->add(&result,sizeof(result));
}
static void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}
static void candidate(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
static bool result(const autotest::Outcome& out,Result& r){if(!out.reportValid||out.capture.length<sizeof(r))return false;std::memcpy(&r,out.capture.data+out.capture.length-sizeof(r),sizeof(r));return r.magic==resultMagic;}
static void diagnostics(const tlhybrid_host* host,const autotest::Outcome& a,const autotest::Outcome& b){Result r;const autotest::Outcome* sides[]={&a,&b};for(unsigned i=0;i<2;++i)if(result(*sides[i],r))host->log("    %s oracle errors=0x%x first=%u got=%d wanted=%d events=%u/%u counterDelta=%d\n",i?"candidate":"original",r.errors,r.mismatch,r.got,r.want,r.actualSize,r.expectedSize,r.counterDelta);}
static bool equal(const autotest::Outcome& a,const autotest::Outcome& b,bool fault){Result x,y;return result(a,x)&&result(b,y)&&!x.errors&&!y.errors&&!a.childStatus&&!b.childStatus&&a.capture.callStarted&&b.capture.callStarted&&bool(a.capture.callCompleted)==!fault&&bool(b.capture.callCompleted)==!fault&&!a.capture.issue&&!b.capture.issue&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}

static int normal(const tlhybrid_host* host,bool deleting,const char* name) {
    autotest::Coverage coverage(name,reinterpret_cast<uintptr_t>(deleting?&uiOriginalD0:&uiOriginalD1));unsigned pairs=0;
    for(unsigned mode=0;mode<8;++mode)for(unsigned variant=0;variant<26;++variant) {
        unsigned mask=variant==0?0:variant==1?4095:variant<14?1u<<(variant-2):4095u^(1u<<(variant-14));
        Case c={mask,mode,0,deleting};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);++pairs;
        int diff=coverage.observe(host,a,b);
        if(diff||!equal(a,b,false)){coverage.report(host);diagnostics(host,a,b);host->log("    GameUI D%u mask %u mode %u exits %d/%d lengths %lu/%lu\n",deleting?0:1,mask,mode,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return 1;}
    }
    coverage.report(host);host->log("    GameUI D%u: %u true-owner/independent-order pairs\n",deleting?0:1,pairs);return 0;
}
}
TL_TEST(gameui_destructor_lifetime_differential){return gameui_dtor_fixture::normal(host,false,"gameui_destructor_lifetime_differential");}
TL_TEST(gameui_deleting_destructor_lifetime_differential){return gameui_dtor_fixture::normal(host,true,"gameui_deleting_destructor_lifetime_differential");}
TL_TEST(gameui_destructor_lifetime_expected_exceptions) {
    using namespace gameui_dtor_fixture;
    const unsigned faults[]={1,10,11,12,13,14,31,34,100,101,103,106,108,109,111,112,113,114,115,124,125,116,117,118,119,120,121,122,123};unsigned pairs=0;
    for(unsigned deleting=0;deleting<2;++deleting)for(unsigned i=0;i<sizeof(faults)/sizeof(faults[0]);++i){Case c={4095,5,faults[i],bool(deleting)};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);++pairs;if(!equal(a,b,true)){diagnostics(host,a,b);host->log("    GameUI D%u expected exception %u exits %d/%d lengths %lu/%lu\n",deleting?0:1,faults[i],a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return 1;}}
    host->log("    GameUI: %u independently checked expected unwinds, excluded from normal coverage\n",pairs);return 0;
}
