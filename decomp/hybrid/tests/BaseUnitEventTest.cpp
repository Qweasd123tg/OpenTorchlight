#include <cstring>
#include <limits>
#include <map>
#include <new>
#include <vector>
#include "AutoTest.h"
#include "BaseUnit.h"
TL_ORIGINAL(void, originalHpThreshold, (CBaseUnit*,float,float,float,float), "_ZN9CBaseUnit27broadcastHPThreshholdEventsEffff")
extern "C" void* eventBaseTable[] __asm__("_ZTV9CBaseUnit");
namespace {
struct Case { unsigned int seed; };
std::vector<unsigned int> events;
void event(void*,unsigned int id) {events.push_back(id);}
void pointerAt(void* p,size_t offset,void* value) {std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value));}
void hpSide(Case& c,bool ours,autotest::Capture& out) {
    long long base[0x1d8/8],manager[0x48/8],hierarchy[0x100/8];
    std::memset(base,0,sizeof(base));std::memset(manager,0,sizeof(manager));std::memset(hierarchy,0,sizeof(hierarchy));
    void* table[80];std::memcpy(table,eventBaseTable+2,sizeof(table));table[6]=reinterpret_cast<void*>(&event);pointerAt(base,0,table);
    typedef std::map<unsigned int,std::vector<unsigned int> > Relations;
    Relations* relations=new(reinterpret_cast<char*>(hierarchy)+0x10)Relations;
    pointerAt(manager,0x20,hierarchy);pointerAt(base,0x68,manager);
    char* self=reinterpret_cast<char*>(base);self[0x1d0]=c.seed&1;self[0x1d1]=(c.seed>>1)&1;
    unsigned int type=c.seed&4?28:29;std::memcpy(self+0x1ac,&type,4);
    float nan=std::numeric_limits<float>::quiet_NaN(),inf=std::numeric_limits<float>::infinity();
    const float inputs[][4]={
        {100,100,100,-95},{100,90,100,-1},{100,95,100,-5},{100,30,100,-10},
        {100,20,100,-10},{100,100,90,-10},{100,100,91,-10},{100,100,100,0},
        {100,100,100,1},{100,100,100,-130},{100,0,100,-1},{0,100,100,-95},
        {100,100,100,nan},{100,nan,100,-10},{100,100,nan,-95},{nan,100,100,-95},
        {inf,100,100,-95},{100,inf,100,-inf},{100,100,100,-inf},{-100,100,100,-95},
        {100,80,100,-35},{100,50,100,-40},{100,10,100,-1},{100,11,100,-1}};
    const float* values=inputs[(c.seed/8)%24];events.clear();CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);
    if(ours)object->broadcastHPThreshholdEvents(values[0],values[1],values[2],values[3]);
    else originalHpThreshold(object,values[0],values[1],values[2],values[3]);
    size_t count=events.size();out.add(&count,sizeof(count));for(size_t i=0;i<count;++i)out.add(&events[i],4);
    relations->~Relations();
}
void hpOriginal(void* p,autotest::Capture& o) {hpSide(*static_cast<Case*>(p),false,o);}
void hpRecovered(void* p,autotest::Capture& o) {hpSide(*static_cast<Case*>(p),true,o);}
bool same(const autotest::Outcome& a,const autotest::Outcome& b) {
    return WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
        a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
}
}
TL_TEST(base_unit_hp_threshold_events) {
    int failures=0;
    for(unsigned int seed=0;seed<192;++seed) {Case c={seed};autotest::Outcome a,b;autotest::runChild(hpOriginal,&c,a);autotest::runChild(hpRecovered,&c,b);
        bool ok=same(a,b);if(!ok)host->log("    HP seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);}
    return failures;
}
