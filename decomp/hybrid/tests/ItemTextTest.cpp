#include <cstring>
#include <map>
#include <new>
#include <vector>
#include "AutoTest.h"
#include "HeadlessGui.h"
#include "Item.h"
#include "GameGlobals.h"

TL_ORIGINAL(void, originalItemText, (CItem*,bool), "_ZN5CItem22setItemTextHighlightedEb")
extern "C" void* textItemTable[] __asm__("_ZTV5CItem");
extern CGameGlobals* textGameGlobals __asm__("_ZL14g_pGameGlobals");
namespace {
struct Case { unsigned int seed; };
bool oldHighlight,magical;
bool highlightedForItem(void*) {return oldHighlight;}
bool magicalForItem(void*) {return magical;}
void putPointer(void* object,size_t offset,void* value) {std::memcpy(static_cast<char*>(object)+offset,&value,sizeof(value));}
struct GlobalsView : CRunicCore {
    unsigned char prefix[0x268-0x10];std::wstring colors[11];unsigned char suffix[0x10];
};
typedef char globals_size[sizeof(GlobalsView)==sizeof(CGameGlobals)&&sizeof(CGameGlobals)==0x2d0?1:-1];
void side(Case& c,bool ours,autotest::Capture& out) {
    GlobalsView globals;
    const wchar_t* colors[]={L"FF112233",L"FF224466",L"FF335577",L"FF446688",L"FF557799",
        L"FF6688AA",L"FF7799BB",L"FF88AACC",L"FF99BBDD",L"FFAACC11",L"FFBBDD22"};
    for(int i=0;i<11;++i)globals.colors[i]=colors[i];
    CGameGlobals* saved=textGameGlobals;textGameGlobals=reinterpret_cast<CGameGlobals*>(&globals);
    long long itemStorage[0x230/8],managerStorage[0x48/8],hierarchyStorage[0x100/8];
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
    putPointer(self,0x1e8,c.seed%19==0?NULL:label);
    CItem* item=reinterpret_cast<CItem*>(self);
    if(ours)item->CItem::setItemTextHighlighted(requested);else originalItemText(item,requested);
    std::string color=label->getProperty("TextColour").c_str();size_t n=color.size();out.add(&n,sizeof(n));out.add(color.data(),n);
    bool inFront=root->getChildAtPosition(CEGUI::Vector2(10,10))==label;out.add(&inFront,sizeof(inFront));
    out.add(self+0x1ac,sizeof(type));out.add(self+0x208,3);
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
TL_TEST(item_text_colors_and_order) {
    int failures=0;
    try {
        tlheadless::Environment environment;environment.loadGameSkin();
        for(unsigned int seed=0;seed<96;++seed) {
            Case c={seed};autotest::Outcome a,b;
            autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
            bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                      WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                      a.capture.length>0&&b.capture.length>0&&a.capture.data[0]==1&&b.capture.data[0]==1&&
                      a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                      std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
            if(!same)host->log("    item text seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,
                              (unsigned long)a.capture.length,(unsigned long)b.capture.length);
            if(seed==0 && a.capture.length>1 && a.capture.data[0]==0)host->log("    original CEGUI: %s\n",a.capture.data+1);
            if(seed==0 && b.capture.length>1 && b.capture.data[0]==0)host->log("    recovered CEGUI: %s\n",b.capture.data+1);
            TL_CHECK(failures,same);
        }
    } catch(const CEGUI::Exception& e) {host->log("    CEGUI: %s\n",e.getMessage().c_str());return 1;}
    return failures;
}
