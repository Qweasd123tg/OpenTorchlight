// PROPOSAL ONLY: not compiled or executed. Original 0xa976a0, size 1877.
// Constructor-free fixtures: none of the synthetic owners is destroyed.
#include <cstring>
#include <string>
#define private public
#define protected public
#include <CEGUI.h>
#include "EquipmentTooltip.h"
#include "GameUI.h"
#include "FileSystem.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"

#define EQUIPMENT_LOAD "_ZN17CEquipmentTooltip4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE"
TL_ORIGINAL(void, originalEquipmentLoad, (CEquipmentTooltip*, CGameUI*, std::wstring), EQUIPMENT_LOAD)
extern "C" void candidateEquipmentLoad(CEquipmentTooltip*, CGameUI*, std::wstring) __asm__(EQUIPMENT_LOAD);
TL_FUNCTION(equipmentFileSingleton, "_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(equipmentFileInfo, "_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(equipmentUnique, "_ZN7STRINGS10uniqueNameERKSs")
TL_FUNCTION(equipmentScale, "_ZN7CGameUI20convertToScreenScaleEPN5CEGUI6WindowEb")
extern "C" char equipmentLayout[] __asm__("_ZN5CEGUI13WindowManager16loadWindowLayoutERKNS_6StringES3_S3_PFbPNS_6WindowERS1_S6_PvES7_");
extern "C" char equipmentTop[] __asm__("_ZN5CEGUI6Window14setAlwaysOnTopEb");
extern "C" char equipmentMute[] __asm__("_ZN5CEGUI8EventSet13setMutedStateEb");
extern "C" void equipmentStringDestroy(CEGUI::String*) __asm__("_ZN5CEGUI6StringD1Ev");
extern "C" char equipmentSearch[] __asm__("_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE");
extern "C" CEGUI::WindowManager* equipmentWindowSingleton __asm__("_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE");

namespace equipment_load_fixture {
typedef char TooltipSize[(sizeof(CEquipmentTooltip)==0x98)?1:-1];
typedef char TooltipRoot[(__builtin_offsetof(CEquipmentTooltip,m_pRoot)==0x20)?1:-1];
typedef char TooltipLast[(__builtin_offsetof(CEquipmentTooltip,m_pPrice)==0x90)?1:-1];
// Prefix/suffix canaries remain outside the typed object, with eight-byte alignment.
template<class T> struct Raw {
    unsigned long long before[2];
    unsigned long long body[(sizeof(T)+7)/8];
    unsigned long long after[2];
    T* get() { return reinterpret_cast<T*>(body); }
    void fill(unsigned char value) { std::memset(this,value,sizeof(*this)); }
};
struct Stop { unsigned event, phase; Stop(unsigned e,unsigned p):event(e),phase(p){} };
struct Case {
    unsigned pattern, change, results, exists, poison, fault, phase;
};
// Extracted from original .rodata, in original store order +0x28..+0x90.
static const char* const names[14]={
    "ItemName", "ItemType", "ItemHanded", "BigDPS", "DPS", "Stats", "Effects",
    "Level Requirements", "Strength Requirements", "Dexterity Requirements",
    "Magic Requirements", "Defense Requirements", "Description", "Price"
};
typedef CEGUI::Window* CEquipmentTooltip::* Child;
static const Child children[14]={
    &CEquipmentTooltip::m_pItemName, &CEquipmentTooltip::m_pItemType,
    &CEquipmentTooltip::m_pItemHanded, &CEquipmentTooltip::m_pBigDPS,
    &CEquipmentTooltip::m_pDPS, &CEquipmentTooltip::m_pStats,
    &CEquipmentTooltip::m_pEffects, &CEquipmentTooltip::m_pLevelRequirement,
    &CEquipmentTooltip::m_pStrengthRequirement, &CEquipmentTooltip::m_pDexterityRequirement,
    &CEquipmentTooltip::m_pMagicRequirement, &CEquipmentTooltip::m_pDefenseRequirement,
    &CEquipmentTooltip::m_pDescription, &CEquipmentTooltip::m_pPrice
};
static Raw<CEquipmentTooltip> owner, expectedOwner;
static Raw<CGameUI> uiStore, expectedUI;
static Raw<CFileSystem> fileStore, expectedFile;
static Raw<CEGUI::WindowManager> managerStore, expectedManager;
static Raw<CEGUI::Window> windows[18], expectedWindows[18];
static CEquipmentTooltip* tip;
static CEquipmentTooltip* expectedTip;
static const Case* cs;
static autotest::Capture* out;
static unsigned eventCount, searchCount, stringDestructions, semanticErrors;
static detour::Set* stringRedirect;
static int uniqueBaseline;
template<class String> int references(const String& value);
static std::string *resource, *uniqueResult, *mod, *group;
static std::wstring *resolved, *argument;

void require(bool yes) { if(!yes) ++semanticErrors; }
void number(unsigned n) { out->add(&n,sizeof(n)); }
CEGUI::Window* window(unsigned i) { require(i<18);return windows[i%18].get(); }
unsigned windowId(const CEGUI::Window* p) {
    if(!p)return 0;
    for(unsigned i=0;i<18;++i)if(p==window(i))return i+1;
    ++semanticErrors;return 0xffffffffu;
}
unsigned indexOf(const CEGUI::Window* p) { unsigned id=windowId(p);require(id>=1&&id<=18);return id>=1&&id<=18?id-1:0; }
void text(const CEGUI::String& s) {
    number(s.length());for(unsigned i=0;i<s.length();++i)number(s[i]);
}
// Run the actual external destructor, never a no-op fake. Restoring this one
// entry avoids recursion; all functional collaborator detours stay installed.
void state();
void stringDestructor(CEGUI::String* value) {
    state(); // Publication must precede cleanup, including each child slot.
    number(90);text(*value);
    stringRedirect->restore();if(stringRedirect->failed())_exit(74);
    equipmentStringDestroy(value);
    ++stringDestructions;number(stringDestructions);
    char* entry=reinterpret_cast<char*>(&equipmentStringDestroy);
    stringRedirect->redirect(entry,entry,&stringDestructor);
    if(stringRedirect->failed())_exit(74);
}
void byteWidened(const CEGUI::String& actual,const std::string& bytes) {
    text(actual);require(actual.length()==bytes.size());
    for(unsigned i=0;i<bytes.size()&&i<actual.length();++i)require(actual[i]==static_cast<unsigned char>(bytes[i]));
}
void ascii(const CEGUI::String& actual,const char* expected) {
    text(actual);require(actual.length()==std::strlen(expected));
    for(unsigned i=0;i<actual.length()&&i<std::strlen(expected);++i)require(actual[i]==static_cast<unsigned char>(expected[i]));
}
// Compare every field, padding byte and exterior canary against the independent
// store oracle. Also capture canonical pointer values for cross-child comparison.
void state() {
    require(!std::memcmp(&owner,&expectedOwner,sizeof(owner)));
    require(!std::memcmp(&uiStore,&expectedUI,sizeof(uiStore)));
    require(!std::memcmp(&fileStore,&expectedFile,sizeof(fileStore)));
    require(!std::memcmp(&managerStore,&expectedManager,sizeof(managerStore)));
    require(!std::memcmp(windows,expectedWindows,sizeof(windows)));
    Raw<CEquipmentTooltip> copy=owner;
    copy.get()->m_pParent=reinterpret_cast<CEGUI::Window*>(uintptr_t(windowId(tip->m_pParent)));
    copy.get()->m_pRoot=reinterpret_cast<CEGUI::Window*>(uintptr_t(windowId(tip->m_pRoot)));
    for(unsigned i=0;i<14;++i)
        copy.get()->*children[i]=reinterpret_cast<CEGUI::Window*>(uintptr_t(windowId(tip->*children[i])));
    out->add(&copy,sizeof(copy));
    // Full byte equality was checked above. Keep repeated event captures bounded.
    for(unsigned i=0;i<18;++i){
        number(window(i)->d_alwaysOnTop);number(window(i)->d_muted);
        number(window(i)->d_mousePassThroughEnabled);
    }
}
void begin(unsigned kind) { ++eventCount;number(kind);number(eventCount);state(); }
void fault(unsigned phase) {
    if(cs->fault==eventCount && cs->phase==phase)throw Stop(eventCount,phase);
}
void replaceRoot(unsigned index) {
    if(cs->change)tip->m_pRoot=expectedTip->m_pRoot=window(index);
}
CFileSystem* singleton() {
    begin(1);fault(0);fault(1);return fileStore.get();
}
void fileInfo(CFileSystem* f,const std::wstring& path,CFileInfo& info,bool a,bool b,bool c) {
    begin(2);number(f==fileStore.get());out->addText(path);
    out->addText(info.m_sModName);out->addText(info.m_sResourceName);out->addText(info.m_sPath);
    number(info.m_eFormat);number(info.m_eLocation);out->addText(info.m_sResourceGroup);number(info.m_bExists);
    number(a);number(b);number(c);
    require(f==fileStore.get()&&path==*argument&&!a&&b&&!c);
    require(info.m_sModName.empty()&&info.m_sResourceName.empty()&&info.m_sPath.empty());
    require(info.m_eFormat==4&&info.m_eLocation==3&&info.m_sResourceGroup.empty()&&!info.m_bExists);
    fault(0);
    info.m_sModName=*mod;info.m_sResourceName=*resource;info.m_sPath=*resolved;
    info.m_sResourceGroup=*group;info.m_bExists=cs->exists!=0;
    info.m_eFormat=FILE_FORMAT_RAW;info.m_eLocation=FILE_LOCATION_PAK;
    fault(1);
}
std::string unique(const std::string& prefix) {
    begin(3);out->addText(prefix);require(prefix=="gui_");fault(0);fault(1);return *uniqueResult;
}
CEGUI::Window* layout(CEGUI::WindowManager* manager,const CEGUI::String& name,
    const CEGUI::String& prefix,const CEGUI::String& resourceGroup,
    bool(*callback)(CEGUI::Window*,CEGUI::String&,CEGUI::String&,void*),void* data) {
    begin(4);number(manager==managerStore.get());byteWidened(name,*resource);
    byteWidened(prefix,*uniqueResult);ascii(resourceGroup,"");number(callback==0);number(data==0);
    require(manager==managerStore.get()&&!callback&&!data);fault(0);
    // A layout callback may alter the old root; the returned root must overwrite it.
    replaceRoot(2);fault(1);expectedTip->m_pRoot=window(0);return window(0);
}
void top(CEGUI::Window* w,bool on) {
    // Original destroys layout filename, unique prefix and group temporaries
    // before the first setup callback, not merely on function exit.
    require(stringDestructions==3);
    require(references(*uniqueResult)==uniqueBaseline);
    begin(5);number(stringDestructions);number(references(*uniqueResult));number(windowId(w));number(on);require(w==tip->m_pRoot&&on);fault(0);
    unsigned id=windowId(w);
    if(id>=1&&id<=18){w->d_alwaysOnTop=on;expectedWindows[id-1].get()->d_alwaysOnTop=on;}
    replaceRoot(1);fault(1);
}
void mute(CEGUI::EventSet* e,bool on) {
    begin(6);
    CEGUI::Window* w=static_cast<CEGUI::Window*>(e);
    number(windowId(w));number(on);
    require(e==static_cast<CEGUI::EventSet*>(tip->m_pRoot)&&on);
    require(reinterpret_cast<const char*>(e)-reinterpret_cast<const char*>(w)==0x38);
    fault(0);unsigned id=windowId(w);
    if(id>=1&&id<=18){e->d_muted=on;expectedWindows[id-1].get()->d_muted=on;}
    replaceRoot(2);fault(1);
}
void scale(CGameUI* ui,CEGUI::Window* w,bool recursive) {
    // The only direct window store between mute and scale is mouse pass-through.
    expectedWindows[indexOf(expectedTip->m_pRoot)].get()->d_mousePassThroughEnabled=true;
    begin(7);number(ui==uiStore.get());number(windowId(w));number(recursive);
    unsigned id=windowId(w);
    require(ui==uiStore.get()&&w==tip->m_pRoot&&!recursive&&id>=1&&id<=18&&w->d_mousePassThroughEnabled);
    fault(0);replaceRoot(0);fault(1);
}
CEGUI::Window* search(const CEGUI::Window* w,const CEGUI::String& name) {
    require(stringDestructions==3+searchCount);
    begin(8);number(windowId(w));require(searchCount<14&&w==tip->m_pRoot);
    const unsigned index=searchCount++;ascii(name,names[index%14]);fault(0);
    replaceRoot(searchCount%3);fault(1);
    CEGUI::Window* result=cs->results==1?window(3):
        cs->results==2?0:cs->results==3 && index%3==1?0:window(3+index);
    if(index<14)expectedTip->*children[index]=result;return result;
}
// Old libstdc++ ABI is fixed by this project. Keep non-empty aliases alive and
// check their reference counts return to their pre-call values after unwind.
// This observes owned CFileInfo and uniqueName temporaries, not all CEGUI heaps.
template<class String> int references(const String& value) {
    int count;std::memcpy(&count,reinterpret_cast<const char*>(value.data())-8,sizeof(count));return count;
}
void side(const Case& c,bool recovered,autotest::Capture& capture) {
    cs=&c;out=&capture;eventCount=searchCount=stringDestructions=semanticErrors=0;
    owner.fill(c.poison?0xa5:0x5a);tip=owner.get();
    tip->m_pParent=window(17);tip->m_pRoot=window(16);
    for(unsigned i=0;i<14;++i)tip->*children[i]=window((i+4)%18);
    expectedOwner=owner;expectedTip=expectedOwner.get();
    uiStore.fill(0x69);expectedUI=uiStore;fileStore.fill(0x96);expectedFile=fileStore;
    managerStore.fill(0x3c);expectedManager=managerStore;
    for(unsigned i=0;i<18;++i){
        windows[i].fill(static_cast<unsigned char>(0x40+i));
        window(i)->d_alwaysOnTop=(i+c.poison)%2!=0;
        window(i)->d_muted=(i+c.poison)%2!=0;
        window(i)->d_mousePassThroughEnabled=(i+c.poison)%2!=0;
        expectedWindows[i]=windows[i];
    }
    // The original instruction at a9792d reads this exact original-data slot.
    // Refuse a private linked singleton copy instead of letting both sides fake it.
    if(reinterpret_cast<uintptr_t>(&equipmentWindowSingleton)!=0x1424660)_exit(75);
    equipmentWindowSingleton=managerStore.get();
    const unsigned lengths[]={0,1,31,32,33,96};
    std::string r,u;
    if(c.pattern<6){r.assign(lengths[c.pattern],'R');u.assign(lengths[5-c.pattern],'U');}
    else if(c.pattern==6){r.assign("ab\0\xc3\xa9\xff",6);u.assign("\x80\0\xc3\xa9Z",5);}
    else {for(unsigned i=0;i<256;++i){r+=static_cast<char>(i);u+=static_cast<char>(255-i);}}
    std::string m="mod-only-do-not-use-as-layout",g="group-only-do-not-use-as-layout";
    std::wstring p=L"resolved/\u03a9\u4e2d/path",arg(L"input\0\u03a9\u4e2d.layout",15);
    resource=&r;uniqueResult=&u;mod=&m;group=&g;resolved=&p;argument=&arg;
    const int refs[]={references(r),references(u),references(m),references(g),references(p),references(arg)};
    uniqueBaseline=refs[1];
    detour::Set redirects;
    detour::Set stringRedirects;stringRedirect=&stringRedirects;
    TL_REDIRECT(redirects,equipmentFileSingleton,&singleton);
    TL_REDIRECT(redirects,equipmentFileInfo,&fileInfo);
    TL_REDIRECT(redirects,equipmentUnique,&unique);
    TL_REDIRECT(redirects,equipmentScale,&scale);
    redirects.redirect(equipmentLayout,equipmentLayout,&layout);
    redirects.redirect(equipmentTop,equipmentTop,&top);
    redirects.redirect(equipmentMute,equipmentMute,&mute);
    redirects.redirect(equipmentSearch,equipmentSearch,&search);
    if(redirects.failed())_exit(74);
    char* destructorEntry=reinterpret_cast<char*>(&equipmentStringDestroy);
    stringRedirects.redirect(destructorEntry,destructorEntry,&stringDestructor);
    if(stringRedirects.failed())_exit(74);
    bool caught=false;unsigned caughtEvent=0,caughtPhase=0;
    try {
        if(recovered)autotest::invoke(capture,&candidateEquipmentLoad,tip,uiStore.get(),arg);
        else autotest::invoke(capture,&originalEquipmentLoad,tip,uiStore.get(),arg);
    } catch(const Stop& stop) {caught=true;caughtEvent=stop.event;caughtPhase=stop.phase;}
    catch(...) {++semanticErrors;caught=true;caughtEvent=caughtPhase=0xffffffffu;}
    number(caught);number(caughtEvent);number(caughtPhase);number(eventCount);number(searchCount);number(stringDestructions);
    require(caught==(c.fault!=0));
    require(caught?(caughtEvent==c.fault&&caughtPhase==c.phase&&eventCount==c.fault):
        (eventCount==21&&searchCount==14&&stringDestructions==17));
    if(caught){
        const unsigned expectedDestructions=c.fault<3?0:c.fault==3?1:
            c.fault<8?3:c.fault-4;
        require(stringDestructions==expectedDestructions);
    }
    state();
    // One final full-window capture includes every untouched byte and guard.
    out->add(windows,sizeof(windows));
    const int after[]={references(r),references(u),references(m),references(g),references(p),references(arg)};
    for(unsigned i=0;i<6;++i){number(after[i]);require(after[i]==refs[i]);}
    // Guard the constant callback input and non-ASCII/embedded-NUL path as well.
    out->addText(r);out->addText(u);out->addText(m);out->addText(g);out->addText(p);out->addText(arg);
    number(0xe017e017u);number(semanticErrors);
}
void originalSide(void* c,autotest::Capture& o){side(*static_cast<Case*>(c),false,o);}
void recoveredSide(void* c,autotest::Capture& o){side(*static_cast<Case*>(c),true,o);}
bool semanticFooter(const autotest::Capture& c) {
    if(c.length<8)return false;
    unsigned footer[2];std::memcpy(footer,c.data+c.length-8,8);
    return footer[0]==0xe017e017u&&footer[1]==0;
}
bool completedReport(const autotest::Outcome& a) {
    return a.reportValid&&a.childStatus==0&&a.capture.issue==autotest::Capture::Complete&&semanticFooter(a.capture);
}
bool sameReport(const autotest::Outcome& a,const autotest::Outcome& b) {
    return completedReport(a)&&completedReport(b)&&a.capture.length>100&&
        a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
}
}
TL_TEST(gameui_equipment_tooltip_load_differential) {
    using namespace equipment_load_fixture;
    autotest::Coverage coverage("gameui_equipment_tooltip_load_differential",(uint64_t)(uintptr_t)&originalEquipmentLoad);
    for(unsigned pattern=0;pattern<8;++pattern)for(unsigned change=0;change<2;++change)
    for(unsigned results=0;results<4;++results)for(unsigned exists=0;exists<2;++exists)
    for(unsigned poison=0;poison<2;++poison){
        Case c={pattern,change,results,exists,poison,0,0};autotest::Outcome a,b;
        autotest::runChild(originalSide,&c,a);autotest::runChild(recoveredSide,&c,b);
        if(coverage.observe(host,a,b)||!sameReport(a,b)){
            host->log("    LOAD MISMATCH pattern %u change %u results %u exists %u poison %u status %d/%d length %lu/%lu\n",
                pattern,change,results,exists,poison,a.childStatus,b.childStatus,
                (unsigned long)a.capture.length,(unsigned long)b.capture.length);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return 0;
}
TL_TEST(gameui_equipment_tooltip_load_expected_exceptions) {
    using namespace equipment_load_fixture;
    unsigned total=0;
    // Every collaborator is interrupted before and after its controlled effects.
    // These are completed exception *reports*, never normal completed-call coverage.
    for(unsigned fault=1;fault<=21;++fault)for(unsigned phase=0;phase<2;++phase)
    for(unsigned change=0;change<2;++change)for(unsigned pattern=6;pattern<8;++pattern){
        Case c={pattern,change,3,0,1,fault,phase};autotest::Outcome a,b;
        autotest::runChild(originalSide,&c,a);autotest::runChild(recoveredSide,&c,b);++total;
        if(!sameReport(a,b)||!a.capture.callStarted||!b.capture.callStarted||
           a.capture.callCompleted||b.capture.callCompleted||
           a.capture.callTarget!=(uint64_t)(uintptr_t)&originalEquipmentLoad||
           !host->comparison_pair||!host->comparison_pair(a.capture.callTarget,b.capture.callTarget)){
            host->log("    LOAD UNWIND MISMATCH fault %u phase %u change %u pattern %u status %d/%d\n",
                fault,phase,change,pattern,a.childStatus,b.childStatus);return 1;
        }
    }
    host->log("    EXPECTED EXCEPTIONS: %u completed reports, exact throw sites, partial owner/window state and COW lifetime balance; excluded from normal coverage\n",total);
    return 0;
}
