#include <cstring>
#include <limits>
#include <new>
#include <vector>
#include "AutoTest.h"
#include "Item.h"
#include "GenericModel.h"
#include "Keyframe.h"

TL_ORIGINAL(void, originalItemAnimation, (CItem*, float), "_ZN5CItem15updateAnimationEf")
extern "C" void* animationItemTable[] __asm__("_ZTV5CItem");
extern "C" void* animationModelTable[] __asm__("_ZTV13CGenericModel");
namespace {
struct Case { unsigned int seed; };
void* modelPointer;
unsigned int modelLookups;
std::vector<unsigned int> calls;
void* modelForItem(void*) {++modelLookups;return modelPointer;}
void addAvoidance(void*,CLevel* level) {calls.push_back(10);calls.push_back(level!=NULL);}
void removeAvoidance(void*,CLevel* level) {calls.push_back(11);calls.push_back(level!=NULL);}
void putPointer(void* object,size_t offset,void* value) {std::memcpy(static_cast<char*>(object)+offset,&value,sizeof(value));}
void putFloat(void* object,size_t offset,float value) {std::memcpy(static_cast<char*>(object)+offset,&value,sizeof(value));}
void side(Case& c,bool ours,autotest::Capture& out) {
    long long itemStorage[0x220/8],modelStorage[0x250/8],managerStorage[0x48/8],levelStorage[0x10/8];
    long long keyStorage[5][0x60/8];
    std::memset(itemStorage,0,sizeof(itemStorage));std::memset(modelStorage,0,sizeof(modelStorage));
    std::memset(managerStorage,0,sizeof(managerStorage));std::memset(levelStorage,0,sizeof(levelStorage));
    std::memset(keyStorage,0,sizeof(keyStorage));
    char* self=reinterpret_cast<char*>(itemStorage);
    void* table[89];std::memcpy(table,animationItemTable+2,sizeof(table));
    table[60]=reinterpret_cast<void*>(&modelForItem);table[77]=reinterpret_cast<void*>(&removeAvoidance);
    table[78]=reinterpret_cast<void*>(&addAvoidance);putPointer(self,0,table);
    putPointer(modelStorage,0,animationModelTable+2);
    self[0x199]=c.seed&1;self[0x81]=(c.seed>>1)&1;self[0x208]=(c.seed>>2)&1;
    self[0x18d]=(c.seed>>3)&1;self[0x19c]=(c.seed>>4)&1;
    const float times[]={0.0f,1.0f,-1.0f,std::numeric_limits<float>::quiet_NaN()};
    putFloat(self,0x1e0,times[(c.seed/8)%4]);
    modelPointer=c.seed%7?modelStorage:NULL;modelLookups=0;calls.clear();
    if(c.seed%3) {putPointer(self,0x68,managerStorage);if(c.seed%3==1)putPointer(managerStorage,0x18,levelStorage);}
    std::vector<CKeyframe*>* events=new(reinterpret_cast<char*>(modelStorage)+0x1b0) std::vector<CKeyframe*>;
    const int codes[]={10,11,12,10,11};
    for(unsigned int i=0;i<c.seed%6;++i) {
        int code=codes[(i+c.seed)%5];std::memcpy(reinterpret_cast<char*>(keyStorage[i])+0x58,&code,sizeof(code));
        events->push_back(reinterpret_cast<CKeyframe*>(keyStorage[i]));
    }
    // Entity-less original update preserves pending events. A disabled model
    // with a non-null entity clears them without dereferencing/rendering it.
    if(c.seed%5==0)putPointer(modelStorage,0x60,levelStorage);
    CItem* item=reinterpret_cast<CItem*>(self);
    if(ours)item->CItem::updateAnimation(0.25f);else originalItemAnimation(item,0.25f);
    out.add(self+0x18d,1);out.add(self+0x199,4);out.add(self+0x208,1);
    out.add(&modelLookups,sizeof(modelLookups));size_t n=calls.size();out.add(&n,sizeof(n));
    for(size_t i=0;i<n;++i)out.add(&calls[i],sizeof(calls[i]));
    n=events->size();out.add(&n,sizeof(n));events->~vector<CKeyframe*>();
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(item_animation_event_dispatch) {
    int failures=0;
    for(unsigned int seed=0;seed<192;++seed) {
        Case c={seed};autotest::Outcome a,b;
        autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                  WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                  a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                  std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!same)host->log("    item animation seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,
                          (unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,same);
    }
    return failures;
}
