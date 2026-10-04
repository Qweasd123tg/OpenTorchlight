#include <cstring>
#include <limits>
#include <new>
#include <vector>
#include "AutoTest.h"
#include "Item.h"
#include "GenericModel.h"
#include "MasterResourceManager.h"

TL_ORIGINAL(void, originalItemOpacity, (CItem*, float, bool), "_ZN5CItem13updateOpacityEfb")
extern "C" void* originalItemTable[] __asm__("_ZTV5CItem");
extern CMasterResourceManager* m_pMasterResourceManager;
extern unsigned int KSETTINGS_NETBOOK_MODE;
namespace {
struct Case { unsigned int seed; };
void* modelPointer;
unsigned int modelLookups;
void* modelForItem(void*) { ++modelLookups;return modelPointer; }
void putPointer(void* object,size_t offset,void* value) {std::memcpy(static_cast<char*>(object)+offset,&value,sizeof(value));}
void putFloat(void* object,size_t offset,float value) {std::memcpy(static_cast<char*>(object)+offset,&value,sizeof(value));}
void side(Case& c,bool ours,autotest::Capture& out) {
    long long itemStorage[0x220/8],modelStorage[0x250/8],masterStorage[0x190/8],settingsStorage[0x140/8];
    std::memset(itemStorage,0,sizeof(itemStorage));std::memset(modelStorage,0,sizeof(modelStorage));
    std::memset(masterStorage,0,sizeof(masterStorage));std::memset(settingsStorage,0,sizeof(settingsStorage));
    char* self=reinterpret_cast<char*>(itemStorage);
    void* table[89];std::memcpy(table,originalItemTable+2,sizeof(table));
    table[60]=reinterpret_cast<void*>(&modelForItem);putPointer(self,0,table);
    self[0x218]=(c.seed>>0)&1;self[0x208]=(c.seed>>1)&1;
    self[0x81]=(c.seed>>2)&1;self[0x19a]=(c.seed>>3)&1;
    static const float values[]={-0.2f,0.0f,0.5f,0.999f,1.0f,2.0f,
        std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),
        -std::numeric_limits<float>::infinity(),-0.0f};
    putFloat(self,0x204,values[(c.seed/32)%10]);
    putFloat(modelStorage,0x228,-17.0f);
    modelPointer=c.seed%3?modelStorage:NULL;modelLookups=0;
    std::vector<int>* settings=new(reinterpret_cast<char*>(settingsStorage)+0x40) std::vector<int>(1,c.seed%2);
    putPointer(masterStorage,0x90,settingsStorage);
    CMasterResourceManager* saved=m_pMasterResourceManager;unsigned int savedIndex=KSETTINGS_NETBOOK_MODE;
    m_pMasterResourceManager=reinterpret_cast<CMasterResourceManager*>(masterStorage);KSETTINGS_NETBOOK_MODE=0;
    const float elapsedValues[]={0.0f,0.25f,-0.25f,2.0f};
    for(unsigned int step=0;step<4;++step) {
        float elapsed=elapsedValues[(step+c.seed)%4];bool force=((c.seed>>4)&1)!=0;
        CItem* item=reinterpret_cast<CItem*>(self);
        if(ours)item->updateOpacity(elapsed,force);else originalItemOpacity(item,elapsed,force);
        out.add(self+0x81,1);out.add(self+0x204,5);out.add(&modelLookups,sizeof(modelLookups));
        out.add(reinterpret_cast<char*>(modelStorage)+0x228,4);
    }
    settings->~vector<int>();m_pMasterResourceManager=saved;KSETTINGS_NETBOOK_MODE=savedIndex;
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(item_opacity_transitions) {
    int failures=0;
    for(unsigned int seed=0;seed<320;++seed) {
        Case c={seed};autotest::Outcome a,b;
        autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                  WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                  a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                  std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!same)host->log("    item opacity seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,
                          (unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,same);
    }
    return failures;
}
