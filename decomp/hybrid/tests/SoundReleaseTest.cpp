#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "SoundManager.h"
#include "SoundInstance.h"
TL_ORIGINAL(void, oldReleaseSound, (CSoundManager*, CSoundInstance*), "_ZN13CSoundManager12releaseSoundEP14CSoundInstance")
extern "C" void newReleaseSound(CSoundManager*, CSoundInstance*) __asm__("_ZN13CSoundManager12releaseSoundEP14CSoundInstance");
namespace {
struct Case { unsigned references, stream, shape, absent; };
autotest::Capture* capture;
CSoundInstance* expectedSound;
unsigned deletes;
void deleted(void* object) {
    ++deletes;
    if (object != expectedSound || expectedSound->m_referenceCount != 0)
        capture->issue = autotest::Capture::InvalidReport;
}
void side(void* raw, autotest::Capture& out, bool ours) {
    const Case& c = *static_cast<Case*>(raw);
    uint64_t managerMemory[(sizeof(CSoundManager)+7)/8], soundMemory[(sizeof(CSoundInstance)+7)/8], other[3][2];
    std::memset(managerMemory, 0xa5, sizeof(managerMemory));
    std::memset(soundMemory, 0x3c, sizeof(soundMemory));
    std::memset(other, 0x69, sizeof(other));
    CSoundManager* manager = reinterpret_cast<CSoundManager*>(managerMemory);
    CSoundInstance* sound = reinterpret_cast<CSoundInstance*>(soundMemory);
    void* table[2] = { reinterpret_cast<void*>(&deleted), reinterpret_cast<void*>(&deleted) };
    // Observe virtual deletion without freeing synthetic storage.
    void** tableAddress = table;
    std::memcpy(soundMemory, &tableAddress, sizeof(tableAddress));
    static const unsigned counts[] = {0, 1, 2, 0xffffffffu};
    sound->m_referenceCount = counts[c.references];
    void* stream = c.stream ? other : 0;
    std::memcpy(reinterpret_cast<char*>(sound)+0x20, &stream, sizeof(stream));
    CSoundInstance* list[5] = {reinterpret_cast<CSoundInstance*>(other[0]), sound,
        reinterpret_cast<CSoundInstance*>(other[1]), sound, reinterpret_cast<CSoundInstance*>(other[2])};
    unsigned count = c.shape == 0 ? 0 : c.shape == 1 ? 1 : c.shape == 2 ? 3 : 5;
    if (c.shape == 1) list[0] = sound;
    if (c.shape == 4) { list[1] = list[0]; list[3] = list[2]; }
    CSoundInstance** data = list;
    unsigned capacity = 5, grow = 25;
    std::memcpy(reinterpret_cast<char*>(manager)+0x90, &data, sizeof(data));
    std::memcpy(reinterpret_cast<char*>(manager)+0x98, &count, 4);
    std::memcpy(reinterpret_cast<char*>(manager)+0x9c, &capacity, 4);
    std::memcpy(reinterpret_cast<char*>(manager)+0xa0, &grow, 4);
    unsigned char beforeManager[sizeof(managerMemory)], beforeSound[sizeof(soundMemory)];
    std::memcpy(beforeManager,managerMemory,sizeof(managerMemory));
    std::memcpy(beforeSound,soundMemory,sizeof(soundMemory));
    CSoundInstance* expected[5]; std::memcpy(expected,list,sizeof(list));
    const bool destroying = !c.absent && counts[c.references] == 1 && c.stream;
    unsigned expectedCount=count;
    if (destroying) for (unsigned i=0;i<expectedCount;++i) if (expected[i]==sound) { expected[i]=expected[--expectedCount];break; }
    capture=&out; expectedSound=sound; deletes=0;
    typedef void(*Fn)(CSoundManager*,CSoundInstance*); Fn fn=ours?newReleaseSound:oldReleaseSound;
    if (!autotest::beginInvocation(out,fn)) return;
    fn(manager,c.absent?0:sound); out.callCompleted=1;
    unsigned newCount;std::memcpy(&newCount,reinterpret_cast<char*>(manager)+0x98,4);
    if (deletes!=(destroying?1u:0u) || newCount!=expectedCount || std::memcmp(list,expected,sizeof(list)) ||
        sound->m_referenceCount!=(c.absent?counts[c.references]:counts[c.references]-1)) out.issue=autotest::Capture::InvalidReport;
    std::memcpy(beforeManager+0x98,&expectedCount,4);
    unsigned expectedReferences=c.absent?counts[c.references]:counts[c.references]-1;
    std::memcpy(beforeSound+0x48,&expectedReferences,4);
    if (std::memcmp(beforeManager,managerMemory,sizeof(managerMemory)) || std::memcmp(beforeSound,soundMemory,sizeof(soundMemory)))out.issue=autotest::Capture::InvalidReport;
    out.add(&deletes,4);out.add(&newCount,4);out.add(&sound->m_referenceCount,4);
    for(unsigned i=0;i<5;++i){unsigned id=list[i]==sound?1:list[i]==reinterpret_cast<CSoundInstance*>(other[0])?2:list[i]==reinterpret_cast<CSoundInstance*>(other[1])?3:4;out.add(&id,4);}
    out.add(other,sizeof(other));
}
void original(void* p,autotest::Capture& out){side(p,out,false);}
void candidate(void* p,autotest::Capture& out){side(p,out,true);}
}
TL_TEST(sound_manager_release_sound) {
    autotest::Coverage coverage("sound_manager_release_sound",reinterpret_cast<uintptr_t>(&oldReleaseSound));
    for(unsigned refs=0;refs<4;++refs)for(unsigned stream=0;stream<2;++stream)for(unsigned shape=0;shape<5;++shape){
        Case c={refs,stream,shape,0};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)){host->log("    release refs %u stream %u shape %u exits %d/%d\n",refs,stream,shape,a.childStatus,b.childStatus);coverage.report(host);return 1;}}
    for(unsigned shape=0;shape<5;++shape){Case c={1,1,shape,1};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
