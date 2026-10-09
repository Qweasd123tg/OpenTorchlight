#include <cstring>
#include <map>
#include <new>
#include <vector>
#include "AutoTest.h"
#include "HeadlessGui.h"
#include "Equipment.h"
#include "Detour.h"
#include "GameGlobals.h"

TL_ORIGINAL(void, originalEquipmentText, (CEquipment*,bool), "_ZN10CEquipment22setItemTextHighlightedEb")
extern "C" void recoveredEquipmentText(CEquipment*,bool) __asm__("_ZN10CEquipment22setItemTextHighlightedEb");
extern "C" void* textItemTable[] __asm__("_ZTV10CEquipment");
extern CGameGlobals* textGameGlobals __asm__("_ZL14g_pGameGlobals");
TL_FUNCTION(etSet,"_ZN10CEquipment6getSetEv")
namespace {
unsigned currentSeed;autotest::Capture* trace;
std::wstring equipmentSet(CEquipment*) { int marker=42;trace->add(&marker,sizeof(marker));return (currentSeed/96)%2?L"A set":L""; }
struct Case { unsigned int seed,warm; };
struct Snapshot {std::vector<unsigned char> bytes;Snapshot(const void* p,size_t n):bytes(static_cast<const unsigned char*>(p),static_cast<const unsigned char*>(p)+n){}void pointer(size_t o,uintptr_t v){if(o+sizeof(v)>bytes.size())_exit(71);std::memcpy(&bytes[o],&v,sizeof(v));}void emit(autotest::Capture& c){c.add(&bytes[0],bytes.size());}};

bool oldHighlight,magical;
bool highlightedForItem(void*) {return oldHighlight;}
bool magicalForItem(void*) {return magical;}
void putPointer(void* object,size_t offset,void* value) {std::memcpy(static_cast<char*>(object)+offset,&value,sizeof(value));}
struct GlobalsView : CRunicCore {
    unsigned char prefix[0x268-0x10];std::wstring colors[11];unsigned char suffix[0x10];
};
typedef char globals_size[sizeof(GlobalsView)==sizeof(CGameGlobals)&&sizeof(CGameGlobals)==0x2d0?1:-1];
void side(Case& c,bool ours,autotest::Capture& out) {
    currentSeed=c.seed;trace=&out;
    detour::Set patches;TL_REDIRECT(patches,etSet,&equipmentSet);if(patches.failed())_exit(42);
    GlobalsView globals;
    const wchar_t* colors[]={L"FF112233",L"FF224466",L"FF335577",L"FF446688",L"FF557799",
        L"FF6688AA",L"FF7799BB",L"FF88AACC",L"FF99BBDD",L"FFAACC11",L"FFBBDD22"};
    for(int i=0;i<11;++i)globals.colors[i]=colors[i];
    CGameGlobals* saved=textGameGlobals;textGameGlobals=reinterpret_cast<CGameGlobals*>(&globals);
    long long itemStorage[(sizeof(CEquipment)+7)/8],managerStorage[0x48/8],hierarchyStorage[0x100/8];
    std::memset(itemStorage,0,sizeof(itemStorage));std::memset(managerStorage,0,sizeof(managerStorage));
    std::memset(hierarchyStorage,0,sizeof(hierarchyStorage));char* self=reinterpret_cast<char*>(itemStorage);
    void* table[89];std::memcpy(table,textItemTable+2,sizeof(table));
    table[66]=reinterpret_cast<void*>(&highlightedForItem);table[86]=reinterpret_cast<void*>(&magicalForItem);
    putPointer(self,0,table);oldHighlight=(c.seed&1)!=0;bool requested=(c.seed&2)!=0;magical=(c.seed&4)!=0;
    long long quest=(c.seed&8)?123:-1;std::memcpy(self+0x170,&quest,sizeof(quest));
    const unsigned int types[]={0,54,55,160,103,777};unsigned int type=types[(c.seed/16)%6];
    std::memcpy(self+0x1ac,&type,sizeof(type));
    typedef std::map<unsigned int,std::vector<unsigned int> > Relations;
    Relations* relations=new(reinterpret_cast<char*>(hierarchyStorage)+0x10) Relations;
    (*relations)[777].push_back(55);(*relations)[777].push_back(160);
    putPointer(managerStorage,0x20,hierarchyStorage);putPointer(self,0x68,managerStorage);
    CEGUI::WindowManager& windows=CEGUI::WindowManager::getSingleton();
    CEGUI::Window* root=windows.createWindow("DefaultWindow","item-test-root");
    root->setSize(CEGUI::UVector2(CEGUI::UDim(0,400),CEGUI::UDim(0,300)));
    CEGUI::System::getSingleton().setGUISheet(root);
    CEGUI::Window* label=windows.createWindow("GuiLook/ItemText","item-test-label");
    CEGUI::Window* other=windows.createWindow("DefaultWindow","item-test-other");
    label->setSize(CEGUI::UVector2(CEGUI::UDim(0,100),CEGUI::UDim(0,100)));
    other->setSize(CEGUI::UVector2(CEGUI::UDim(0,100),CEGUI::UDim(0,100)));
    label->setProperty("TextColour","FF010203");label->setText("item");
    root->addChildWindow(label);root->addChildWindow(other);
    putPointer(self,0x1e8,(c.seed/192)%2?NULL:label);
    CEquipment* item=reinterpret_cast<CEquipment*>(self);
    for(unsigned repeat=0;repeat<=c.warm;++repeat){if(repeat==c.warm){if(ours)autotest::invoke(out,&recoveredEquipmentText,item,requested);else autotest::invoke(out,&originalEquipmentText,item,requested);}else{if(ours)item->CEquipment::setItemTextHighlighted(requested);else originalEquipmentText(item,requested);}}
    std::string color=label->getProperty("TextColour").c_str();size_t n=color.size();out.add(&n,sizeof(n));out.add(color.data(),n);
    bool inFront=root->getChildAtPosition(CEGUI::Vector2(10,10))==label;out.add(&inFront,sizeof(inFront));
    out.add(self+0x1ac,sizeof(type));out.add(self+0x208,3);
    Snapshot eq(item,sizeof(*item));eq.pointer(0,*reinterpret_cast<void***>(item)==table?1:255);void* resource;std::memcpy(&resource,self+0x68,sizeof(resource));eq.pointer(0x68,resource==managerStorage?1:255);void* itemText;std::memcpy(&itemText,self+0x1e8,sizeof(itemText));eq.pointer(0x1e8,itemText==label?1:itemText?255:0);eq.emit(out);
    Snapshot mgr(managerStorage,sizeof(managerStorage));void* hierarchy;std::memcpy(&hierarchy,reinterpret_cast<char*>(managerStorage)+0x20,sizeof(hierarchy));mgr.pointer(0x20,hierarchy==hierarchyStorage?1:255);mgr.emit(out);
    size_t size=relations->size();out.add(&size,sizeof(size));for(Relations::const_iterator i=relations->begin();i!=relations->end();++i){out.add(&i->first,sizeof(i->first));size=i->second.size();out.add(&size,sizeof(size));for(size_t j=0;j<size;++j)out.add(&i->second[j],sizeof(i->second[j]));}
    for(unsigned i=0;i<11;++i){size=globals.colors[i].size();out.add(&size,sizeof(size));out.add(globals.colors[i].data(),size*sizeof(wchar_t));}
    const CEGUI::String& labelText=label->getText();size=labelText.length();out.add(&size,sizeof(size));for(size_t i=0;i<size;++i){CEGUI::utf32 ch=labelText[i];out.add(&ch,sizeof(ch));}
    bool visible=label->isVisible(),enabled=!label->isDisabled(),parent=label->getParent()==root;float alpha=label->getAlpha();out.add(&visible,sizeof(visible));out.add(&enabled,sizeof(enabled));out.add(&parent,sizeof(parent));out.add(&alpha,sizeof(alpha));
    CEGUI::System::getSingleton().setGUISheet(NULL);windows.destroyWindow(root);
    relations->~Relations();textGameGlobals=saved;
}
void guarded(void* p,bool ours,autotest::Capture& out) {
    unsigned char success=0;out.add(&success,1);
    try {side(*static_cast<Case*>(p),ours,out);out.data[0]=1;}
    catch(const CEGUI::Exception& e) {out.length=1;out.add(e.getMessage().c_str(),e.getMessage().length()+1);}
    catch(const std::exception& e) {char buffer[200];snprintf(buffer,sizeof(buffer),"%s",e.what());out.length=1;out.add(buffer,strlen(buffer)+1);}
}
void original(void* p,autotest::Capture& out) {guarded(p,false,out);}
void recovered(void* p,autotest::Capture& out) {guarded(p,true,out);}
}
TL_TEST(equipment_text_colors_and_order) {
    int failures=0;autotest::Coverage coverage("equipment_text_colors_and_order",(uint64_t)(uintptr_t)&originalEquipmentText);
    try {
        tlheadless::Environment environment;environment.loadGameSkin();
        for(unsigned int seed=0;seed<384;++seed)for(unsigned warm=0;warm<2;++warm) {
            Case c={seed,warm};autotest::Outcome a,b;
            autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
            int pair=coverage.observe(host,a,b);
            bool same=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                      WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                      a.capture.length>0&&b.capture.length>0&&a.capture.data[0]==1&&b.capture.data[0]==1&&
                      a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                      std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
            if(!same)host->log("    item text seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,
                              (unsigned long)a.capture.length,(unsigned long)b.capture.length);
            if(seed==0 && a.capture.length>1 && a.capture.data[0]==0)host->log("    original CEGUI: %s\n",a.capture.data+1);
            if(seed==0 && b.capture.length>1 && b.capture.data[0]==0)host->log("    recovered CEGUI: %s\n",b.capture.data+1);
            TL_CHECK(failures,same);if(!same){coverage.report(host);return failures;}
        }
    } catch(const CEGUI::Exception& e) {host->log("    CEGUI: %s\n",e.getMessage().c_str());return 1;}
    coverage.report(host);host->log("    equipment text: 768 completed cold/warm cases\n");return failures;
}
